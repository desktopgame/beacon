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
#include "type_impl.h"
#include "field.h"
#include "method.h"
#include "parameter.h"
#include "constructor.h"
#include "../il/il_constructor.h"
#include "../il/il_constructor_chain.h"
#include "../il/il_type_impl.h"
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
	ret->link = link_none_T;
	ret->import_manager = import_manager_new();
	ret->env = enviroment_new();
	ret->level = 0;
	ret->type_cache_vec = NewVector();
	ret->filename = text_strdup(filename);
	ret->env->context_ref = ret;
	return ret;
}

void class_loader_load(class_loader * self) {
	//ASTを読み込む
	parser* p = parse_file(self->filename);
	//解析に失敗した場合
	if (check_parser_error(p)) {
		return;
	}
	ast* a = parser_release_ast(p);
	parser_destroy(p);
	class_loader_load_pass_ast(self, a);
}

void class_loader_load_pass_ast(class_loader* self, ast* a) {
	bc_error_clear();
	heap* hee = heap_get();
	hee->accept_blocking++;
	self->source_code = a;
	class_loader_load_impl(self);
	hee->accept_blocking--;
}

void class_loader_special(class_loader* self, char* relativePath) {
	char* fullP = ResolveScriptPath(relativePath);
	script_context* ctx = script_context_get_current();
	heap* he = heap_get();
	class_loader* cll = tree_map_get(ctx->class_loader_map, fullP);
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
	ast_delete(self->source_code);
	il_top_level_delete(self->il_code);
	DeleteVector(self->type_cache_vec, class_loader_cache_delete);
	import_manager_delete(self->import_manager);
	enviroment_delete(self->env);
	MEM_FREE(self->filename);
	MEM_FREE(self);
}


//private
static void class_loader_load_impl(class_loader* self) {
	assert(self != NULL);
	//AST -> IL へ
	class_loader_ilload_impl(self, self->source_code);
	if (bc_error_last()) { return; }
	//IL -> SG へ
	class_loader_bcload_impl(self);
	if (bc_error_last()) { return; }
	//他のクラスローダーとリンク
	class_loader_load_linkall(self);
	class_loader_load_toplevel_function(self);
	class_loader_load_toplevel(self);
}

static void class_loader_link_recursive(class_loader* self, link_type type) {
	if (self->link == type) {
		return;
	}
	if(bc_error_last()) {
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
	type_cache_delete(e);
}

static class_loader* class_loader_load_specialImpl(class_loader* self, class_loader* cll, char* full_path) {
	cll = CLBC_import_new(self, full_path);
	//parser
	parser* p = parse_file(full_path);
	if(check_parser_error(p)) {
		return cll;
	}
	//ASTをclassloaderへ
	cll->source_code = parser_release_ast(p);
	parser_destroy(p);
	//AST -> IL へ
	class_loader_ilload_impl(cll, cll->source_code);
	if (bc_error_last()) { return cll; }
	//IL -> SG へ
	class_loader_bcload_special(cll);
	if (bc_error_last()) { return cll; }
	assert(cll->type == content_lib_T);
	return cll;
}

static void class_loader_load_linkall(class_loader* self) {
	if(self->type != content_entry_point_T) {
		return;
	}
	class_loader_link_recursive(self, link_decl_T);
	class_loader_link_recursive(self, link_impl_T);
}

static void class_loader_load_toplevel(class_loader* self) {
	//トップレベルのステートメントを読み込む
	if(self->type != content_entry_point_T) {
		return;
	}
	//var $world = new beacon::lang::World();
	il_stmt_inferenced_type_init* createWorldStmt = il_stmt_inferenced_type_init_new(string_pool_intern("$world"));
	il_factor_new_instance* newWorldInstance = il_factor_new_instance_new();
	newWorldInstance->fqcnc->namev = string_pool_intern("World");
	createWorldStmt->fact = il_factor_wrap_new_instance(newWorldInstance);
	il_stmt* body = il_stmt_wrap_inferenced_type_init(createWorldStmt);
	//これをやらないと -1 のまま
	body->lineno = 0;
	createWorldStmt->fact->lineno = 0;
	//worldをselfにする
	call_context* cctx = call_context_new(call_top_T);
	cctx->ty = namespace_get_type(namespace_lang(), string_pool_intern("World"));
	il_stmt_load(body, self->env, cctx);
	il_stmt_generate(body, self->env, cctx);
	//$worldをthisにする
	opcode_buf_add(self->env->buf, op_load);
	opcode_buf_add(self->env->buf, 1);
	opcode_buf_add(self->env->buf, op_store);
	opcode_buf_add(self->env->buf, 0);
	//以下読み込み
	CLBC_body(self, self->il_code->statement_list, self->env, cctx, NULL);
	il_stmt_delete(body);
	call_context_delete(cctx);
	script_context_cache();
}

static void class_loader_load_toplevel_function(class_loader* self) {
	if(self->level != 0 || self->type != content_entry_point_T) {
		return;
	}
	Vector* funcs = self->il_code->function_list;
	type* worldT = namespace_get_type(namespace_lang(), string_pool_intern("World"));
	//前回の実行で作成されたメソッドを解放
	Vector* methods = TYPE2CLASS(worldT)->method_list;
	if(methods->length > 0) {
		DeleteVector(methods, method_delete);
		TYPE2CLASS(worldT)->method_list = NewVector();
	}
	//メソッドの宣言のみロード
	for(int i=0; i<funcs->length; i++) {
		il_function* ilfunc = AtVector(funcs, i);
		method* m = method_new(ilfunc->namev);
		type_parameter_list_dup(ilfunc->type_parameter_vec, m->type_parameters);
		script_method* sm = script_method_new();
		enviroment* env = enviroment_new();
		//call_contextの設定
		call_context* cctx = call_context_new(call_method_T);
		cctx->scope = namespace_lang();
		cctx->ty = worldT;
		cctx->u.mt = m;
		namespace_* loc = call_context_namespace(cctx);
		env->context_ref = self;
		sm->env = env;
		m->access = access_private_T;
		m->u.script_method = sm;
		m->parent = worldT;
		//戻り値を指定
		m->return_gtype = import_manager_resolve(loc, ilfunc->return_fqcn, cctx);
	//	generic_type_print(m->return_gtype);
	//	Println();
		//引数を指定
		for(int j=0; j<ilfunc->parameter_list->length; j++) {
			il_parameter* ilparam = AtVector(ilfunc->parameter_list, j);
			parameter* param = parameter_new(ilparam->namev);
			PushVector(m->parameters, param);
			param->gtype = import_manager_resolve(loc, ilparam->fqcn, cctx);
			symbol_table_entry(
				env->sym_table,
				import_manager_resolve(loc, ilparam->fqcn, cctx),
				ilparam->namev
			);
			//実引数を保存
			//0番目は this のために開けておく
			opcode_buf_add(env->buf, op_store);
			opcode_buf_add(env->buf, (j + 1));
		}
		opcode_buf_add(env->buf, (VectorItem)op_store);
		opcode_buf_add(env->buf, (VectorItem)0);
		PushVector(worldT->u.class_->method_list, m);
		//CLBC_corutine(self, m, env, ilfunc->parameter_list, ilfunc->statement_list, cctx, namespace_lang());
		call_context_delete(cctx);
	}
	//実装のロード
	for(int i=0; i<funcs->length; i++) {
		il_function* ilfunc = AtVector(funcs, i);
		method* m = AtVector(TYPE2CLASS(worldT)->method_list, i);
		script_method* sm = m->u.script_method;
		call_context* cctx = call_context_new(call_method_T);
		cctx->scope = namespace_lang();
		cctx->ty = worldT;
		cctx->u.mt = m;
		CLBC_corutine(self, m, sm->env, ilfunc->parameter_list, ilfunc->statement_list, cctx, namespace_lang());
		call_context_delete(cctx);
	}
}

static bool check_parser_error(parser* p) {
	if(p->result == parse_syntax_error_T) {
		bc_error_throw(bcerror_parse_T, p->error_message);
		parser_destroy(p);
		return true;
	} else if(p->result == parse_open_error_T) {
		bc_error_throw(bcerror_require_not_found_T, p->source_name);
		parser_destroy(p);
		return true;
	}
	return false;
}