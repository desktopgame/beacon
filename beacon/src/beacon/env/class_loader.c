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
#include "lazy_resolve.h"
#include "../env/native_method_ref.h"
#include "../il/il_argument.h"
#include "../util/vector.h"
#include "script_context.h"
#include "../util/text.h"
#include "../util/io.h"
#include "../util/panic.h"
#include "../util/xassert.h"
#include "../parse/parser.h"
#include "namespace.h"
#include "type_impl.h"
#include "field.h"
#include "method.h"
#include "parameter.h"
#include "constructor.h"
#include "compile_context.h"
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
#include "../il/il_error.h"
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
static void class_loader_cache_delete(vector_item item);
static void class_loader_lazy_resolve_delete(vector_item item);
static void class_loader_lazy_resolve(class_loader* self);
static void class_loader_lazy_resolve_all(class_loader* self);
static void class_loader_lazy_resolve_at(char* name, tree_item item);
static class_loader* class_loader_load_specialImpl(class_loader* self, class_loader* cll, char* fullP);
static void class_loader_load_toplevel(class_loader* self);
static void class_loader_load_linkall(class_loader* self);
static void class_loader_load_toplevel_function(class_loader* self);

class_loader* class_loader_new(content_type type) {
	class_loader* ret = (class_loader*)MEM_MALLOC(sizeof(class_loader));
	ret->source_code = NULL;
	ret->il_code = NULL;
	ret->parent = NULL;
	ret->type = type;
	ret->link = link_none;
	ret->import_manager = import_manager_new();
	ret->env = enviroment_new();
	ret->error = false;
	ret->level = 0;
	ret->type_cache_vec = vector_new();
	ret->lazy_resolve_vec = vector_new();
	ret->env->context_ref = ret;
	return ret;
}

class_loader * class_loader_new_entry_point_from_file(const char * filename) {
	char* text = io_read_text(filename);
	class_loader* ret = class_loader_new_entry_point_from_source(text, filename);
	MEM_FREE(text);
	return ret;
}

class_loader * class_loader_new_entry_point_from_source(const char * source, const char* contextDescription) {
	parser* p = parser_parse_from_source_swap(source, contextDescription);
	class_loader* ret = class_loader_new_entry_point_from_parser(p);
	parser_pop();
	ret->filename = text_strdup(contextDescription);
	return ret;
}

class_loader * class_loader_new_entry_point_from_parser(parser * p) {
	class_loader* ret = class_loader_new(content_entry_point);
	//解析に失敗した場合
	if (p->fail) {
		class_loader_report(ret, clerror_parse, p->source_name);
		return ret;
	}
	ret->source_code = p->root;
	p->root = NULL;
	return ret;
}

void class_loader_load(class_loader * self) {
	heap* hee = heap_get();
	hee->accept_blocking++;
	class_loader_load_impl(self);
	hee->accept_blocking--;
}

void class_loader_sub(class_loader * self, char * fullPath) {
	CLBC_new_load(self, fullPath);
}

void class_loader_rsub(class_loader * self, char * relativePath) {
	char* a = io_absolute_path(relativePath);
	class_loader_sub(self, a);
	MEM_FREE(a);
}

void class_loader_special(class_loader* self, char* relativePath) {
	char* fullP = io_absolute_path(relativePath);
	script_context* ctx = script_context_get_current();
	heap* he = heap_get();
	class_loader* cll = tree_map_get(ctx->class_loader_map, fullP);
	he->accept_blocking++;
	if(cll == NULL) {
		cll = class_loader_load_specialImpl(self, cll, fullP);
	}
	he->accept_blocking--;
	//MEM_FREE(fullP);
}

void class_loader_delete(class_loader * self) {
	if(self == NULL) {
		return;
	}
	ast_delete(self->source_code);
	il_top_level_delete(self->il_code);
	vector_delete(self->type_cache_vec, class_loader_cache_delete);
	vector_delete(self->lazy_resolve_vec, class_loader_lazy_resolve_delete);
	import_manager_delete(self->import_manager);
	enviroment_delete(self->env);
	MEM_FREE(self->filename);
	MEM_FREE(self);
}

int class_loader_report(class_loader* self, cl_error_id id, ...) {
	va_list ap;
	va_start(ap, id);
	int ret = class_loader_vreport(self, id, ap);
	va_end(ap);
	return ret;
}

int class_loader_vreport(class_loader* self, cl_error_id id, va_list ap) {
	self->error = true;
	char* fmt = NULL;
	switch(id) {
		case clerror_parse:
			fmt = "parser failed --- %s";
			break;
		case clerror_class_first:
			fmt = "must be class first: %s";
			break;
		case clerror_multi_eqinterface:
			fmt = "should'nt implement equal interface a multiple: %s";
			break;
		case clerror_interface_only:
			fmt = "must be interface only: %s";
			break;
		case clerror_chain:
			fmt = "error %s";
			break;
		case clerror_modifier_a_overlapped:
			fmt = "invalid modifier: %s";
			break;
		case clerror_field_name_a_overlapped:
			fmt = "invalid field declaration: %s @%s";
			break;
		case clerror_native_field:
			fmt = "shouldn't define field of abstract or native: %s";
			break;
		case clerror_abstract_method_by:
			fmt = "abstract method should be defined on the abstract class: %s";
			break;
		case clerror_empty_method_body:
			fmt = "must be not empty statement if modifier of method is native or abstract: %s";
			break;
		case clerror_not_empty_method_body:
			fmt = "must be empty statement if modifier of method is native or abstract: %s";
			break;
		case clerror_not_implement_interface:
			fmt = "invalid implement: %s @%s";
			break;
		case clerror_not_implement_abstract_method:
			fmt = "invalid implement: %s @%s";
			break;
		case clerror_private_operator:
			fmt = "must be public a access level of operator: %s";
			break;
		case clerror_illegal_argument_bioperator:
			fmt = "illegal of parameter count, must be binary operator argument count is one.: %s#%s";
			break;
		case clerror_illegal_argument_uoperator:
			fmt = "illegal of parameter count, must be unary operator argument count is zero.: %s#%s";
			break;
		default:
			{
				fprintf(stderr, "if shown this message, it compiler bug\n");
				return 0;
			}
			break;
	}
	fprintf(stderr, "%s\n", self->filename);
	int res = vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	return res;
}

//private
static void class_loader_load_impl(class_loader* self) {
	assert(self != NULL);
	assert(self->source_code != NULL);
	//AST -> IL へ
	class_loader_ilload_impl(self, self->source_code);
	if (self->error) { return; }
	//IL -> SG へ
	class_loader_bcload_impl(self);
	if (self->error) { return; }
	//他のクラスローダーとリンク
	class_loader_load_linkall(self);
	class_loader_load_toplevel_function(self);
	class_loader_load_toplevel(self);
}

static void class_loader_link_recursive(class_loader* self, link_type type) {
	if (self->link == type) {
		return;
	}
	self->link = type;
	import_manager* importMgr = self->import_manager;
	for (int i = 0; i < importMgr->info_vec->length; i++) {
		import_info* info = (import_info*)vector_at(importMgr->info_vec, i);
		if (info->consume) {
			continue;
		}
		class_loader_link_recursive(info->context, type);
	}
	class_loader_link(self, type);
}

static void class_loader_cache_delete(vector_item item) {
	type_cache* e = (type_cache*)item;
	type_cache_delete(e);
}

static void class_loader_lazy_resolve_delete(vector_item item) {
	lazy_resolve* e = (lazy_resolve*)item;
	lazy_resolve_delete(e);
}

static void class_loader_lazy_resolve(class_loader* self) {
	for(int i=0; i<self->lazy_resolve_vec->length; i++) {
		lazy_resolve* lr = (lazy_resolve*)vector_at(self->lazy_resolve_vec, i);
		if(!lr->active) {
			continue;
		}
		lazy_resolve_apply(lr);
		lr->active = false;
	}
}

static void class_loader_lazy_resolve_all(class_loader* self) {
	script_context* sc = script_context_get_current();
	tree_map_each(sc->class_loader_map, class_loader_lazy_resolve_at);
}

static void class_loader_lazy_resolve_at(char* name, tree_item item) {
	class_loader* cl = (class_loader*)item;
	class_loader_lazy_resolve(cl);
}

static class_loader* class_loader_load_specialImpl(class_loader* self, class_loader* cll, char* fullP) {
	cll = CLBC_import_new(self,fullP);
	//parser
	char* text = io_read_text(fullP);
	parser* p = parser_parse_from_source_swap(text, fullP);
	assert(p->root != NULL);
	assert(!p->fail);
	//ASTをclassloaderへ
	cll->source_code = p->root;
	p->root = NULL;
	MEM_FREE(text);
	parser_pop();
	//AST -> IL へ
	class_loader_ilload_impl(cll, cll->source_code);
	if (cll->error) { return cll; }
	//IL -> SG へ
	class_loader_bcload_special(cll);
	if (cll->error) { return cll; }
	assert(cll->type == content_lib);
	return cll;
}

static void class_loader_load_linkall(class_loader* self) {
	if(self->type != content_entry_point) {
		return;
	}
	il_error_enter();
	class_loader_link_recursive(self, link_decl);
	class_loader_link_recursive(self, link_impl);
	class_loader_lazy_resolve_all(self);
	il_error_exit();
}

static void class_loader_load_toplevel(class_loader* self) {
	//トップレベルのステートメントを読み込む
	if(self->level != 0) {
		return;
	}
	ccset_class_loader(self);
	cc_enable(ccstate_toplevel);
	//var $world = new beacon::lang::World();
	il_stmt_inferenced_type_init* createWorldStmt = il_stmt_inferenced_type_init_new("$world");
	il_factor_new_instance* newWorldInstance = il_factor_new_instance_new();
	newWorldInstance->fqcnc->name = text_strdup("World");
	createWorldStmt->fact = il_factor_wrap_new_instance(newWorldInstance);
	il_stmt* body = il_stmt_wrap_inferenced_type_init(createWorldStmt);
	//worldをselfにする
	ccpush_type(namespace_get_type(namespace_lang(), "World"));
	il_error_enter();
	il_stmt_load(body, self->env);
	il_stmt_generate(body, self->env);
	il_error_exit();
	//$worldをthisにする
	opcode_buf_add(self->env->buf, op_load);
	opcode_buf_add(self->env->buf, 1);
	opcode_buf_add(self->env->buf, op_store);
	opcode_buf_add(self->env->buf, 0);
	//以下読み込み
	CLBC_body(self, self->il_code->statement_list, self->env, NULL);
	il_stmt_delete(body);
	ccpop_type();
	cc_disable(ccstate_toplevel);
	ccset_class_loader(NULL);
	script_context_cache();
}

static void class_loader_load_toplevel_function(class_loader* self) {
	if(self->level != 0) {
		return;
	}
	vector* funcs = self->il_code->function_list;
	type* worldT = namespace_get_type(namespace_lang(), "World");
	ccpush_type(worldT);
	ccset_class_loader(self);
	for(int i=0; i<funcs->length; i++) {
		il_function* ilfunc = vector_at(funcs, i);
		method* m = method_new(ilfunc->name);
		script_method* sm = script_method_new();
		enviroment* env = enviroment_new();
		env->context_ref = self;
		sm->env = env;
		m->access = access_private;
		m->u.script_method = sm;
		ccpush_method(m);
		//戻り値を指定
		m->return_gtype = import_manager_resolve(self->import_manager, cc_namespace(), ilfunc->return_fqcn);
		//引数を指定
		for(int j=0; j<ilfunc->parameter_list->length; j++) {
			il_parameter* ilparam = vector_at(ilfunc->parameter_list, j);
			parameter* param = parameter_new(ilparam->name);
			vector_push(m->parameter_list, param);
			param->gtype = import_manager_resolve(self->import_manager, cc_namespace(), ilparam->fqcn);
			symbol_table_entry(
				env->sym_table,
				import_manager_resolve(self->import_manager, cc_namespace(), ilparam->fqcn),
				ilparam->name
			);
			//実引数を保存
			//0番目は this のために開けておく
			opcode_buf_add(env->buf, op_store);
			opcode_buf_add(env->buf, (j + 1));
		}
		opcode_buf_add(env->buf, (vector_item)op_store);
		opcode_buf_add(env->buf, (vector_item)0);
		vector_push(worldT->u.class_->method_list, m);
		il_error_enter();
		//中身をロード
		for(int j=0; j<ilfunc->statement_list->length; j++) {
			il_stmt* stmt = vector_at(ilfunc->statement_list, j);
			il_stmt_load(stmt, env);
		}
		//生成
		for(int j=0; j<ilfunc->statement_list->length; j++) {
			il_stmt* stmt = vector_at(ilfunc->statement_list, j);
			il_stmt_generate(stmt, env);
		}
		il_error_exit();
		ccpop_method();
	}
	ccset_class_loader(NULL);
	ccpop_type();
}