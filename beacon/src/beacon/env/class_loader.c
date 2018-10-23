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
static void LoadClassLoader_impl(class_loader* self);
static void LinkClassLoader_recursive(class_loader* self, LinkType type);
static void class_loader_cache_delete(VectorItem item);
static class_loader* LoadClassLoader_specialImpl(class_loader* self, class_loader* cll, char* full_path);
static void LoadClassLoader_toplevel(class_loader* self);
static void LoadClassLoader_linkall(class_loader* self);
static void LoadClassLoader_toplevel_function(class_loader* self);
static bool check_parser_error(Parser* p);

class_loader* NewClassLoader(const char* filename, ContentType type) {
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
	ret->env->ContextRef = ret;
	return ret;
}

void LoadClassLoader(class_loader * self) {
	//ASTを読み込む
	Parser* p = ParseFile(self->filename);
	//解析に失敗した場合
	if (check_parser_error(p)) {
		return;
	}
	AST* a = ReleaseParserAST(p);
	DestroyParser(p);
	LoadPassASTClassLoader(self, a);
}

void LoadPassASTClassLoader(class_loader* self, AST* a) {
	ClearBCError();
	Heap* hee = GetHeap();
	hee->AcceptBlocking++;
	self->source_code = a;
	LoadClassLoader_impl(self);
	hee->AcceptBlocking--;
}

void SpecialLoadClassLoader(class_loader* self, char* relativePath) {
	char* fullP = ResolveScriptPath(relativePath);
	script_context* ctx = GetCurrentScriptContext();
	Heap* he = GetHeap();
	class_loader* cll = GetTreeMapValue(ctx->class_loader_map, fullP);
	he->AcceptBlocking++;
	if(cll == NULL) {
		cll = LoadClassLoader_specialImpl(self, cll, fullP);
	}
	he->AcceptBlocking--;
	MEM_FREE(fullP);
}

void DeleteClassLoader(class_loader * self) {
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
static void LoadClassLoader_impl(class_loader* self) {
	assert(self != NULL);
	//AST -> IL へ
	ILLoadClassLoader(self, self->source_code);
	if (GetLastBCError()) { return; }
	//IL -> SG へ
	BCLoadClassLoader(self);
	if (GetLastBCError()) { return; }
	//他のクラスローダーとリンク
	LoadClassLoader_linkall(self);
	LoadClassLoader_toplevel_function(self);
	LoadClassLoader_toplevel(self);
}

static void LinkClassLoader_recursive(class_loader* self, LinkType type) {
	if (self->link == type) {
		return;
	}
	if(GetLastBCError()) {
		return;
	}
	self->link = type;
	import_manager* importMgr = self->import_manager;
	for (int i = 0; i < importMgr->info_vec->Length; i++) {
		ImportInfo* info = (ImportInfo*)AtVector(importMgr->info_vec, i);
		if (info->IsConsume) {
			continue;
		}
		LinkClassLoader_recursive(info->Context, type);
	}
	LinkClassLoader(self, type);
}

static void class_loader_cache_delete(VectorItem item) {
	type_cache* e = (type_cache*)item;
	DeleteTypeCache(e);
}

static class_loader* LoadClassLoader_specialImpl(class_loader* self, class_loader* cll, char* full_path) {
	cll = CLBC_import_new(self, full_path);
	//parser
	Parser* p = ParseFile(full_path);
	if(check_parser_error(p)) {
		return cll;
	}
	//ASTをclassloaderへ
	cll->source_code = ReleaseParserAST(p);
	DestroyParser(p);
	//AST -> IL へ
	ILLoadClassLoader(cll, cll->source_code);
	if (GetLastBCError()) { return cll; }
	//IL -> SG へ
	SpecialBCLoadClassLoader(cll);
	if (GetLastBCError()) { return cll; }
	assert(cll->type == CONTENT_LIB_T);
	return cll;
}

static void LoadClassLoader_linkall(class_loader* self) {
	if(self->type != CONTENT_ENTRY_POINT_T) {
		return;
	}
	LinkClassLoader_recursive(self, LINK_DECL_T);
	LinkClassLoader_recursive(self, LINK_IMPL_T);
}

static void LoadClassLoader_toplevel(class_loader* self) {
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
	CallContext* cctx = NewCallContext(CALL_TOP_T);
	cctx->Ty = FindTypeFromNamespace(GetLangNamespace(), InternString("World"));
	LoadILStmt(body, self->env, cctx);
	GenerateILStmt(body, self->env, cctx);
	//$worldをthisにする
	AddOpcodeBuf(self->env->Bytecode, OP_LOAD);
	AddOpcodeBuf(self->env->Bytecode, 1);
	AddOpcodeBuf(self->env->Bytecode, OP_STORE);
	AddOpcodeBuf(self->env->Bytecode, 0);
	//以下読み込み
	CLBC_body(self, self->il_code->statement_list, self->env, cctx, NULL);
	DeleteILStmt(body);
	DeleteCallContext(cctx);
	CacheScriptContext();
}

static void LoadClassLoader_toplevel_function(class_loader* self) {
	if(self->level != 0 || self->type != CONTENT_ENTRY_POINT_T) {
		return;
	}
	Vector* funcs = self->il_code->function_list;
	type* worldT = FindTypeFromNamespace(GetLangNamespace(), InternString("World"));
	//前回の実行で作成されたメソッドを解放
	Vector* methods = TYPE2CLASS(worldT)->method_list;
	if(methods->Length > 0) {
		DeleteVector(methods, DeleteMethod);
		TYPE2CLASS(worldT)->method_list = NewVector();
	}
	//メソッドの宣言のみロード
	for(int i=0; i<funcs->Length; i++) {
		ILFunction* ilfunc = AtVector(funcs, i);
		method* m = method_new(ilfunc->namev);
		DupTypeParameterList(ilfunc->type_parameter_vec, m->type_parameters);
		script_method* sm = NewScriptMethod();
		Enviroment* env = NewEnviroment();
		//CallContextの設定
		CallContext* cctx = NewCallContext(CALL_METHOD_T);
		cctx->Scope = GetLangNamespace();
		cctx->Ty = worldT;
		cctx->Kind.Method = m;
		namespace_* loc = GetNamespaceCContext(cctx);
		env->ContextRef = self;
		sm->env = env;
		m->access = ACCESS_PRIVATE_T;
		m->u.script_method = sm;
		m->parent = worldT;
		//戻り値を指定
		m->return_gtype = ResolveImportManager(loc, ilfunc->return_fqcn, cctx);
	//	PrintGenericType(m->return_gtype);
	//	Println();
		//引数を指定
		for(int j=0; j<ilfunc->parameter_list->Length; j++) {
			il_parameter* ilparam = AtVector(ilfunc->parameter_list, j);
			Parameter* param = NewParameter(ilparam->namev);
			PushVector(m->parameters, param);
			param->GType = ResolveImportManager(loc, ilparam->fqcn, cctx);
			EntrySymbolTable(
				env->Symboles,
				ResolveImportManager(loc, ilparam->fqcn, cctx),
				ilparam->namev
			);
			//実引数を保存
			//0番目は this のために開けておく
			AddOpcodeBuf(env->Bytecode, OP_STORE);
			AddOpcodeBuf(env->Bytecode, (j + 1));
		}
		AddOpcodeBuf(env->Bytecode, (VectorItem)OP_STORE);
		AddOpcodeBuf(env->Bytecode, (VectorItem)0);
		PushVector(worldT->u.class_->method_list, m);
		//CLBC_corutine(self, m, env, ilfunc->parameter_list, ilfunc->statement_list, cctx, GetLangNamespace());
		DeleteCallContext(cctx);
	}
	//実装のロード
	for(int i=0; i<funcs->Length; i++) {
		ILFunction* ilfunc = AtVector(funcs, i);
		method* m = AtVector(TYPE2CLASS(worldT)->method_list, i);
		script_method* sm = m->u.script_method;
		CallContext* cctx = NewCallContext(CALL_METHOD_T);
		cctx->Scope = GetLangNamespace();
		cctx->Ty = worldT;
		cctx->Kind.Method = m;
		CLBC_corutine(self, m, sm->env, ilfunc->parameter_list, ilfunc->statement_list, cctx, GetLangNamespace());
		DeleteCallContext(cctx);
	}
}

static bool check_parser_error(Parser* p) {
	if(p->Result == PARSE_SYNTAX_ERROR_T) {
		ThrowBCError(BCERROR_PARSE_T, p->ErrorMessage);
		DestroyParser(p);
		return true;
	} else if(p->Result == PARSE_OPEN_ERROR_T) {
		ThrowBCError(BCERROR_REQUIRE_NOT_FOUND_T, p->SourceName);
		DestroyParser(p);
		return true;
	}
	return false;
}