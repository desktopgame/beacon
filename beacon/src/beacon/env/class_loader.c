#include "class_loader.h"
#include <stdlib.h>
#include <assert.h>
#include "fqcn_cache.h"
#include "../util/mem.h"
#include "../il/il_type_interface.h"
#include "../il/il_function.h"
#include "../vm/vm.h"
#include "../vm/opcode.h"
#include "../vm/opcode_buf.h"
#include "../env/native_method_ref.h"
#include "../env/type_parameter.h"
#include "../il/il_argument.h"
#include "../util/vector.h"
#include "script_context.h"
#include "../util/text.h"
#include "../util/io.h"
#include "../parse/parser.h"
#include "namespace.h"
#include "TYPE_IMPL.h"
#include "field.h"
#include "method.h"
#include "parameter.h"
#include "constructor.h"
#include "../il/il_constructor.h"
#include "../il/il_constructor_chain.h"
#include "../il/il_TYPE_IMPL.h"
#include "../il/il_field.h"
#include "../il/il_method.h"
#include "../il/il_stmt_impl.h"
#include "../il/il_factor_impl.h"
#include "../il/il_parameter.h"
#include "../il/il_import.h"
#include "../il/il_namespace.h"
#include "../error.h"
#include <string.h>

#include "cll/class_loader_ilload_impl.h"
#include "cll/class_loader_ilload_type_module_impl.h"
#include "cll/class_loader_bcload_impl.h"
#include "cll/class_loader_bcload_import_module_impl.h"
#include "cll/class_loader_bcload_member_module_impl.h"
#include "cll/class_loader_link_impl.h"
#include "import_info.h"
#include "type_cache.h"
#include "heap.h"

//proto
static void class_loader_load_impl(class_loader* self);
static void class_loader_link_recursive(class_loader* self, link_type type);
static void class_loader_cache_delete(VectorItem item);
static class_loader* class_loader_load_specialImpl(class_loader* self, class_loader* cll, char* full_path);
static void class_loader_load_toplevel(class_loader* self);
static void class_loader_load_linkall(class_loader* self);
static void class_loader_load_toplevel_function(class_loader* self);
static bool check_parser_error(parser* p);

class_loader* class_loader_new(const char* filename, content_type type) {
	class_loader* ret = (class_loader*)MEM_MALLOC(sizeof(class_loader));
	ret->source_code = NULL;
	ret->il_code = NULL;
	ret->parent = NULL;
	ret->type = type;
	ret->link = LINK_NONE_T;
	ret->import_manager = NewImportManager();
	ret->env = NewEnviroment();
	ret->level = 0;
	ret->type_cache_vec = NewVector();
	ret->filename = Strdup(filename);
	ret->env->context_ref = ret;
	return ret;
}

void class_loader_load(class_loader * self) {
	//ASTを読み込む
	parser* p = ParseFile(self->filename);
	//解析に失敗した場合
	if (check_parser_error(p)) {
		return;
	}
	ast* a = ReleaseParserAST(p);
	DestroyParser(p);
	class_loader_load_pass_ast(self, a);
}

void class_loader_load_pass_ast(class_loader* self, ast* a) {
	ClearBCError();
	heap* hee = GetHeap();
	hee->accept_blocking++;
	self->source_code = a;
	class_loader_load_impl(self);
	hee->accept_blocking--;
}

void class_loader_special(class_loader* self, char* relativePath) {
	char* fullP = ResolveScriptPath(relativePath);
	script_context* ctx = GetCurrentScriptContext();
	heap* he = GetHeap();
	class_loader* cll = GetTreeMapValue(ctx->class_loader_map, fullP);
	he->accept_blocking++;
	if(cll == NULL) {
		cll = class_loader_load_specialImpl(self, cll, fullP);
	}
	he->accept_blocking--;
	MEM_FREE(fullP);
}

void class_loader_delete(class_loader * self) {
	if(self == NULL) {
		return;
	}
	DeleteAST(self->source_code);
	DeleteILToplevel(self->il_code);
	DeleteVector(self->type_cache_vec, class_loader_cache_delete);
	DeleteImportManager(self->import_manager);
	DeleteEnviroment(self->env);
	MEM_FREE(self->filename);
	MEM_FREE(self);
}


//private
static void class_loader_load_impl(class_loader* self) {
	assert(self != NULL);
	//AST -> IL へ
	class_loader_ilload_impl(self, self->source_code);
	if (GetLastBCError()) { return; }
	//IL -> SG へ
	class_loader_bcload_impl(self);
	if (GetLastBCError()) { return; }
	//他のクラスローダーとリンク
	class_loader_load_linkall(self);
	class_loader_load_toplevel_function(self);
	class_loader_load_toplevel(self);
}

static void class_loader_link_recursive(class_loader* self, link_type type) {
	if (self->link == type) {
		return;
	}
	if(GetLastBCError()) {
		return;
	}
	self->link = type;
	import_manager* importMgr = self->import_manager;
	for (int i = 0; i < importMgr->info_vec->length; i++) {
		import_info* info = (import_info*)AtVector(importMgr->info_vec, i);
		if (info->consume) {
			continue;
		}
		class_loader_link_recursive(info->context, type);
	}
	class_loader_link(self, type);
}

static void class_loader_cache_delete(VectorItem item) {
	type_cache* e = (type_cache*)item;
	DeleteTypeCache(e);
}

static class_loader* class_loader_load_specialImpl(class_loader* self, class_loader* cll, char* full_path) {
	cll = CLBC_import_new(self, full_path);
	//parser
	parser* p = ParseFile(full_path);
	if(check_parser_error(p)) {
		return cll;
	}
	//ASTをclassloaderへ
	cll->source_code = ReleaseParserAST(p);
	DestroyParser(p);
	//AST -> IL へ
	class_loader_ilload_impl(cll, cll->source_code);
	if (GetLastBCError()) { return cll; }
	//IL -> SG へ
	class_loader_bcload_special(cll);
	if (GetLastBCError()) { return cll; }
	assert(cll->type == CONTENT_LIB_T);
	return cll;
}

static void class_loader_load_linkall(class_loader* self) {
	if(self->type != CONTENT_ENTRY_POINT_T) {
		return;
	}
	class_loader_link_recursive(self, LINK_DECL_T);
	class_loader_link_recursive(self, LINK_IMPL_T);
}

static void class_loader_load_toplevel(class_loader* self) {
	//トップレベルのステートメントを読み込む
	if(self->type != CONTENT_ENTRY_POINT_T) {
		return;
	}
	//var $world = new beacon::lang::World();
	il_stmt_inferenced_type_init* createWorldStmt = NewILInferencedTypeInit(InternString("$world"));
	il_factor_new_instance* newWorldInstance = NewILNewInstance();
	newWorldInstance->fqcnc->namev = InternString("World");
	createWorldStmt->fact = WrapILNewInstance(newWorldInstance);
	il_stmt* body = WrapILInferencedTypeInit(createWorldStmt);
	//これをやらないと -1 のまま
	body->lineno = 0;
	createWorldStmt->fact->lineno = 0;
	//worldをselfにする
	call_context* cctx = NewCallContext(CALL_TOP_T);
	cctx->ty = FindTypeFromNamespace(GetLangNamespace(), InternString("World"));
	LoadILStmt(body, self->env, cctx);
	GenerateILStmt(body, self->env, cctx);
	//$worldをthisにする
	AddOpcodeBuf(self->env->buf, OP_LOAD);
	AddOpcodeBuf(self->env->buf, 1);
	AddOpcodeBuf(self->env->buf, OP_STORE);
	AddOpcodeBuf(self->env->buf, 0);
	//以下読み込み
	CLBC_body(self, self->il_code->statement_list, self->env, cctx, NULL);
	DeleteILStmt(body);
	DeleteCallContext(cctx);
	CacheScriptContext();
}

static void class_loader_load_toplevel_function(class_loader* self) {
	if(self->level != 0 || self->type != CONTENT_ENTRY_POINT_T) {
		return;
	}
	Vector* funcs = self->il_code->function_list;
	type* worldT = FindTypeFromNamespace(GetLangNamespace(), InternString("World"));
	//前回の実行で作成されたメソッドを解放
	Vector* methods = TYPE2CLASS(worldT)->method_list;
	if(methods->length > 0) {
		DeleteVector(methods, DeleteMethod);
		TYPE2CLASS(worldT)->method_list = NewVector();
	}
	//メソッドの宣言のみロード
	for(int i=0; i<funcs->length; i++) {
		il_function* ilfunc = AtVector(funcs, i);
		method* m = method_new(ilfunc->namev);
		DupTypeParameterList(ilfunc->type_parameter_vec, m->type_parameters);
		script_method* sm = NewScriptMethod();
		enviroment* env = NewEnviroment();
		//call_contextの設定
		call_context* cctx = NewCallContext(CALL_METHOD_T);
		cctx->scope = GetLangNamespace();
		cctx->ty = worldT;
		cctx->u.mt = m;
		namespace_* loc = GetNamespaceCContext(cctx);
		env->context_ref = self;
		sm->env = env;
		m->access = ACCESS_PRIVATE_T;
		m->u.script_method = sm;
		m->parent = worldT;
		//戻り値を指定
		m->return_gtype = ResolveImportManager(loc, ilfunc->return_fqcn, cctx);
	//	generic_type_print(m->return_gtype);
	//	Println();
		//引数を指定
		for(int j=0; j<ilfunc->parameter_list->length; j++) {
			il_parameter* ilparam = AtVector(ilfunc->parameter_list, j);
			parameter* param = NewParameter(ilparam->namev);
			PushVector(m->parameters, param);
			param->gtype = ResolveImportManager(loc, ilparam->fqcn, cctx);
			EntrySymbolTable(
				env->sym_table,
				ResolveImportManager(loc, ilparam->fqcn, cctx),
				ilparam->namev
			);
			//実引数を保存
			//0番目は this のために開けておく
			AddOpcodeBuf(env->buf, OP_STORE);
			AddOpcodeBuf(env->buf, (j + 1));
		}
		AddOpcodeBuf(env->buf, (VectorItem)OP_STORE);
		AddOpcodeBuf(env->buf, (VectorItem)0);
		PushVector(worldT->u.class_->method_list, m);
		//CLBC_corutine(self, m, env, ilfunc->parameter_list, ilfunc->statement_list, cctx, GetLangNamespace());
		DeleteCallContext(cctx);
	}
	//実装のロード
	for(int i=0; i<funcs->length; i++) {
		il_function* ilfunc = AtVector(funcs, i);
		method* m = AtVector(TYPE2CLASS(worldT)->method_list, i);
		script_method* sm = m->u.script_method;
		call_context* cctx = NewCallContext(CALL_METHOD_T);
		cctx->scope = GetLangNamespace();
		cctx->ty = worldT;
		cctx->u.mt = m;
		CLBC_corutine(self, m, sm->env, ilfunc->parameter_list, ilfunc->statement_list, cctx, GetLangNamespace());
		DeleteCallContext(cctx);
	}
}

static bool check_parser_error(parser* p) {
	if(p->result == PARSE_SYNTAX_ERROR_T) {
		ThrowBCError(BCERROR_PARSE_T, p->error_message);
		DestroyParser(p);
		return true;
	} else if(p->result == PARSE_OPEN_ERROR_T) {
		ThrowBCError(BCERROR_REQUIRE_NOT_FOUND_T, p->source_name);
		DestroyParser(p);
		return true;
	}
	return false;
}