#include "class_loader.h"
#include <stdlib.h>
#include <assert.h>
//#include <uni>
//#include <uni>
#include "../vm/opcode.h"
#include "../vm/opcode_buf.h"
#include "../il/il_argument.h"
#include "../util/vector.h"
#include "script_context.h"
#include "../util/text.h"
#include "../util/io.h"
#include "../parse/parser.h"
#include "namespace.h"
#include "class.h"
#include "field.h"
#include "method.h"
#include "parameter.h"
#include "../il/il_class.h"
#include "../il/il_field.h"
#include "../il/il_method.h"
#include "../il/il_stmt_impl.h"
#include "../il/il_factor_impl.h"
#include "../il/il_parameter.h"
#include "../il/il_import.h"
#include "../il/il_namespace.h"

//proto
static class_loader* class_loader_new();

static void class_loader_ilload_impl(class_loader* self, ast* source_code);
static void class_loader_ilload_import(class_loader* self, ast* import_decl);
static void class_loader_ilload_namespace(class_loader* self, vector* parent, ast* namespace_decl);
static void class_loader_ilload_namespace_path_recursive(class_loader* self, ast* namespace_path, ast* namespace_body);
static il_namespace* class_loader_ilload_ast_to_namespace(ast* a);
static void class_loader_ilload_namespace_body(class_loader* self, il_namespace* current, vector* parent, ast* namespace_body);
static void class_loader_ilload_class(class_loader* self, il_namespace* current, ast* class_decl);
static void class_loader_ilload_member(class_loader* self, il_class* current, ast* member);
static void class_loader_ilload_field(class_loader* self, il_class* current, ast* field);
static void class_loader_ilload_method(class_loader* self, il_class* current, ast* method);
static void class_loader_ilload_param(class_loader* self, vector* list, ast* source);
static void class_loader_ilload_body(class_loader* self, vector* list, ast* source);
static il_stmt_if* class_loader_ilload_if(class_loader* self, ast* source);
static il_stmt_if* class_loader_ilload_if_elif_list(class_loader* self, ast* source);
static void class_loader_ilload_elif_list(class_loader* self, vector* list, ast* source);
static il_stmt_if* class_loader_ilload_if_else(class_loader* self, ast* source);
static il_stmt_if* class_loader_ilload_if_elif_list_else(class_loader* self, ast* source);
static il_factor* class_loader_ilload_factor(class_loader* self, ast* source);
static il_factor_unary_op* class_loader_ilload_unary(class_loader* self, ast* source, ilunary_op_type type);
static il_factor_binary_op* class_loader_ilload_binary(class_loader* self, ast* source, ilbinary_op_type type);
static il_factor_call* class_loader_ilload_call(class_loader* self, ast* source);
static il_factor_invoke* class_loader_ilload_invoke(class_loader* self, ast* source);
static void class_loader_ilload_argument_list(class_loader* self, vector* list, ast* source);
static void class_loader_ilload_constructor(class_loader* self, il_class* current, ast* constructor);

static void class_loader_sgload_impl(class_loader* self);
static void class_loader_sgload_import(class_loader* self, vector* ilimports);
static void class_loader_sgload_namespace_list(class_loader* self, vector* ilnamespace_list, namespace_* parent);
static void class_loader_sgload_namespace(class_loader* self, il_namespace* ilnamespace, namespace_* parent);
static void class_loader_sgload_class_list(class_loader* self, vector* ilclass_list, namespace_* parent);
static void class_loader_sgload_class(class_loader* self, il_class* classz, namespace_* parent);
static void class_loader_sgload_fields(class_loader* self, il_class* ilclass, class_* classz);
static void class_loader_sgload_methods(class_loader* self, il_class* ilclass, class_* classz);
static opcode_buf* class_loader_sgload_body(class_loader* self, vector* stmt_list);


class_loader * class_loader_new_entry_point(const char * filename) {
	class_loader* cll = class_loader_new();
	char* text = io_read_text(filename);
	parser* p = parser_parse_from_source(text);
	//解析に失敗した場合
	if (p->fail) {
		cll->fail = true;
		free(text);
		parser_pop();
		return cll;
	}
	cll->source_code = p->root;
	p->root = NULL;
	free(text);
	parser_pop();
	return cll;
}

void class_loader_load(class_loader * self) {
	assert(self != NULL);
	assert(self->source_code != NULL);
	system("cls");
	//ast_print_tree(self->source_code);
	class_loader_ilload_impl(self, self->source_code);
	class_loader_sgload_impl(self);
}

void class_loader_delete(class_loader * self) {
	assert(self != NULL);
	assert(self->ref_count == 0);
	if (self->parent != NULL) {
		self->parent->ref_count--;
	}
	//free(self->source_code);
	ast_delete(self->source_code);
	il_top_level_delete(self->il_code);
	free(self);
}

//private
static class_loader* class_loader_new() {
	class_loader* ret = (class_loader*)malloc(sizeof(class_loader));
	ret->source_code = NULL;
	ret->il_code = NULL;
	ret->parent = NULL;
	ret->ref_count = 0;
	ret->type = content_entry_point;
	ret->fail = false;
	return ret;
}

//
//ilload
//
static void class_loader_ilload_impl(class_loader* self, ast* source_code) {
	self->il_code = il_top_level_new();
	for (int i = 0; i < source_code->childCount; i++) {
		ast* child = ast_at(self->source_code, i);
		//import a
		if (child->tag == ast_import_decl) {
			class_loader_ilload_import(self, child);
		//namespace Foo { ... }
		} else if (child->tag == ast_namespace_decl) {
			class_loader_ilload_namespace(self, self->il_code->namespace_list, child);
		}
	}
	il_top_level_dump(self->il_code, 0);
}

static void class_loader_ilload_import(class_loader* self, ast* import_decl) {
	assert(import_decl->tag == ast_import_decl);
	ast* path = ast_first(import_decl);
	vector_push(self->il_code->import_list, il_import_new(path->u.string_value));
	printf("import %s\n", path->u.string_value);
}

static void class_loader_ilload_namespace(class_loader* self, vector* parent, ast* namespace_decl) {
	assert(namespace_decl->tag == ast_namespace_decl);
	//printf("namespace");
	ast* namespace_path = ast_first(namespace_decl);
	ast* namespace_body = ast_second(namespace_decl);
	il_namespace* iln = class_loader_ilload_ast_to_namespace(namespace_path);
	il_namespace* top = il_namespace_root(iln);
	//printf("%s", top->name);
	vector_push(parent, top);
	class_loader_ilload_namespace_path_recursive(self, namespace_path, namespace_body);
	//printf("\n");
	class_loader_ilload_namespace_body(self, iln, iln->namespace_list, namespace_body);
	//printf("\n");
}

static void class_loader_ilload_namespace_path_recursive(class_loader* self, ast* namespace_path, ast* namespace_body) {
	assert(namespace_path->tag == ast_namespace_path ||
		   namespace_path->tag == ast_namespace_path_list);
	if (namespace_path->tag == ast_namespace_path) {
	//	printf(" %s", namespace_path->u.string_value);
	} else if (namespace_path->tag == ast_namespace_path_list) {
		for (int i = 0; i < namespace_path->childCount; i++) {
			class_loader_ilload_namespace_path_recursive(self, ast_at(namespace_path, i), namespace_body);
		}
	}
}

static il_namespace* class_loader_ilload_ast_to_namespace(ast* a) {
	assert(a->tag == ast_namespace_path ||
	       a->tag == ast_namespace_path_list);
	if(a->tag == ast_namespace_path) {
		//printf("-  %s", a->u.string_value);
		text_putline();
		il_namespace* ret = il_namespace_new(a->u.string_value);
		return ret;
	} else if(a->tag == ast_namespace_path_list) {
		ast* l = ast_first(a);
		ast* r = ast_second(a);
		il_namespace* parent = class_loader_ilload_ast_to_namespace(l);
		il_namespace* child = class_loader_ilload_ast_to_namespace(r);
		child->parent = parent;
		vector_push(parent->namespace_list, child);
		return child;
	}
}

static void class_loader_ilload_namespace_body(class_loader* self, il_namespace* current, vector* parent, ast* namespace_body) {
	if (ast_is_blank(namespace_body)) {
		return;
	}
	//assert(namespace_body->tag == ast_namespace_member_decl_list);
	//namespace xxx { ...
	//namespace xxx { namespace yyy { ...
	if (namespace_body->tag == ast_namespace_decl) {
		class_loader_ilload_namespace(self, parent, namespace_body);
		//namespace xxx { class yyy { ...
	} else if (namespace_body->tag == ast_class_decl) {
		//printf("class decl\n");
		class_loader_ilload_class(self, current, namespace_body);
		//namespace xxx { any yyy { ...
	} else if (namespace_body->tag == ast_namespace_member_decl_list) {
		for (int i = 0; i < namespace_body->childCount; i++) {
			ast* member = ast_at(namespace_body, i);
			class_loader_ilload_namespace_body(self, current, parent, member);
		}
	}
}

static void class_loader_ilload_class(class_loader* self, il_namespace* current, ast* class_decl) {
	ast* super_class = ast_first(class_decl);
	ast* member_list = ast_second(class_decl);
	il_class* classz = il_class_new(class_decl->u.string_value);
	//親クラスが宣言されていない
	if(ast_is_blank(super_class)) {
		classz->super = NULL;
	} else {
		classz->super = il_type_new(super_class->u.string_value);
	}
	class_loader_ilload_member(self, classz, member_list);
	vector_push(current->class_list, classz);
}

static void class_loader_ilload_member(class_loader* self, il_class* current, ast* member) {
	if(member->tag == ast_member_decl_list) {
		for(int i=0; i<member->childCount; i++) {
			class_loader_ilload_member(self, current, ast_at(member, i));
		}
	} else if(member->tag == ast_member_decl) {
		ast* child = ast_first(member);
		if (child->tag == ast_field_decl) {
			class_loader_ilload_field(self, current, child);
		} else if (child->tag == ast_func_decl) {
			class_loader_ilload_method(self, current, child);
		} else if (child->tag == ast_constructor_decl) {
			class_loader_ilload_constructor(self, current, child);
		}
	}
}

static void class_loader_ilload_field(class_loader* self, il_class* current, ast* field) {
	ast* type_name = ast_first(field);
	ast* access_name = ast_second(field);
	il_field* v = il_field_new(access_name->u.string_value);
	v->type = il_type_new(type_name->u.string_value);
	vector_push(current->field_list, v);
}

static void class_loader_ilload_method(class_loader* self, il_class* current, ast* method) {
	ast* func_name = ast_at(method, 0);
	ast* param_list = ast_at(method, 1);
	ast* func_body = ast_at(method, 2);
	ast* ret_name = ast_at(method, 3);
	il_method* v = il_method_new(func_name->u.string_value);
	v->return_type = il_type_new(ret_name->u.string_value);
	class_loader_ilload_param(self, v->parameter_list, param_list);
	class_loader_ilload_body(self, v->statement_list, func_body);
	vector_push(current->method_list, v);
}

static void class_loader_ilload_param(class_loader* self, vector* list, ast* source) {
	if (source->tag == ast_parameter_list) {
		for (int i = 0; i < source->childCount; i++) {
			class_loader_ilload_param(self, list, ast_at(source, i));
		}
	} else if (source->tag == ast_parameter) {
		ast* type_name = ast_first(source);
		ast* access_name = ast_second(source);
		il_parameter* p = il_parameter_new(access_name->u.string_value);
		p->type = il_type_new(type_name->u.string_value);
		vector_push(list, p);
	}
}

static void class_loader_ilload_body(class_loader* self, vector* list, ast* source) {
	if (source->tag == ast_stmt_list || source->tag == ast_scope) {
		for (int i = 0; i < source->childCount; i++) {
			class_loader_ilload_body(self, list, ast_at(source, i));
		}
	} else {
		//printf("    ");
		//ast_print(source);
		//printf("\n");
		switch (source->tag) {
			case ast_stmt:
			{
				class_loader_ilload_body(self, list, ast_first(source));
				break;
			}
			case ast_proc:
			{
				ast* afact = ast_first(source);
				il_factor* ilfact = class_loader_ilload_factor(self, afact);
				il_stmt_proc* ilproc = il_stmt_proc_new();
				ilproc->factor = ilfact;
				vector_push(list, il_stmt_wrap_proc(ilproc));
				break;
			}
			case ast_if:
			{
				il_stmt_if* ilif = class_loader_ilload_if(self, source);
				vector_push(list, il_stmt_wrap_if(ilif));
				break;
			}
			case ast_if_elif_list:
			{
				il_stmt* ilif = class_loader_ilload_if_elif_list(self, source);
				vector_push(list, il_stmt_wrap_if(ilif));
				break;
			}
			case ast_if_else:
			{
				il_stmt* ilif = class_loader_ilload_if_else(self, source);
				vector_push(list, il_stmt_wrap_if(ilif));
				break;
			}
			case ast_if_elif_list_else:
			{
				il_stmt_if* ilif = class_loader_ilload_if_elif_list_else(self, source);
				vector_push(list, il_stmt_wrap_if(ilif));
				break;
			}
			default:
				break;
		}
	}
}

static il_stmt_if* class_loader_ilload_if(class_loader* self, ast* source) {
	assert(source->tag == ast_if);
	il_stmt_if* ret = il_stmt_if_new();
	ast* acond = ast_first(source);
	ast* abody = ast_second(source);
	il_factor* ilcond = class_loader_ilload_factor(self, acond);
	//il_stmt_list* ilbody = il_stmt_list_new();
	class_loader_ilload_body(self, ret->body, abody);
	ret->condition = ilcond;
	//ret->body = ilbody;
	if (ret->condition == NULL) {
		int a = 0;
	}
	return ret;
}

static il_stmt_if* class_loader_ilload_if_elif_list(class_loader* self, ast* source) {
	ast* aif = ast_first(source);
	ast* aelif_list = ast_second(source);
	il_stmt_if* ilif = class_loader_ilload_if(self, aif);
	class_loader_ilload_elif_list(self, ilif->elif_list, aelif_list);
	//il_stmt_list_push(list, ilif);
	return ilif;
}

static il_stmt_if* class_loader_ilload_if_else(class_loader* self, ast* source) {
	ast* aif = ast_first(source);
	ast* aelse = ast_second(source);
	ast* abody = ast_first(aelse);
	il_stmt_if* ilif = class_loader_ilload_if(self, aif);
	class_loader_ilload_body(self, ilif->else_body, abody);
	return ilif;
}

static il_stmt_if* class_loader_ilload_if_elif_list_else(class_loader* self, ast* source) {
	ast* aif_eliflist = ast_first(source);
	ast* aelse = ast_second(source);
	il_stmt_if* ilif = class_loader_ilload_if_elif_list(self, aif_eliflist);
	class_loader_ilload_body(self, ilif->else_body, ast_first(aelse));
	return ilif;
}

static void class_loader_ilload_elif_list(class_loader* self, vector* list, ast* source) {
	if (source->tag == ast_elif_list) {
		for (int i = 0; i < source->childCount; i++) {
			class_loader_ilload_elif_list(self, list, ast_at(source, i));
		}
	} else if (source->tag == ast_elif) {
		ast* acond = ast_first(source);
		ast* abody = ast_second(source);
		//il_stmt* ilif = il_stmt_if_new();
		il_stmt_elif* ilelif = il_stmt_elif_new();
		ilelif->condition = class_loader_ilload_factor(self, acond);
		class_loader_ilload_body(self, ilelif->body, abody);
		//il_stmt_list_push(list, ilelif);
		il_stmt_elif_list_push(list, ilelif);
	}
}

static il_factor* class_loader_ilload_factor(class_loader* self, ast* source) {
	if (source->tag == ast_int) {
		return il_factor_wrap_int(il_factor_int_new(source->u.int_value));
	} else if (source->tag == ast_double) {
		return il_factor_wrap_double(il_factor_double_new(source->u.double_value));
	} else if (source->tag == ast_char) {
		return il_factor_wrap_char(il_factor_char_new(source->u.char_value));
	} else if (source->tag == ast_string) {
		return il_factor_wrap_string(il_factor_string_new(source->u.string_value));
	} else if (source->tag == ast_call) {
		return il_factor_wrap_call(class_loader_ilload_call(self, source));
	} else if (source->tag == ast_invoke) {
		return il_factor_wrap_invoke(class_loader_ilload_invoke(self, source));
	} else if (source->tag == ast_variable) {
		return il_factor_wrap_variable(il_factor_variable_new(source->u.string_value));
	//operator(+ - * / %)
	} else if (source->tag == ast_add) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_add));
	} else if (source->tag == ast_sub) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_sub));
	} else if (source->tag == ast_mul) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_mul));
	} else if (source->tag == ast_div) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_div));
	} else if (source->tag == ast_mod) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_mod));
	//operator(| || & &&)
	} else if (source->tag == ast_bit_or) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_bit_or));
	} else if (source->tag == ast_logic_or) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_logic_or));
	} else if (source->tag == ast_bit_and) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_bit_and));
	} else if (source->tag == ast_logic_and) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_logic_and));
	//operator(== != > >= < <=)
	} else if (source->tag == ast_equal) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_eq));
	} else if (source->tag == ast_notequal) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_noteq));
	} else if (source->tag == ast_gt) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_gt));
	} else if (source->tag == ast_ge) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_ge));
	} else if (source->tag == ast_lt) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_lt));
	} else if (source->tag == ast_le) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_le));
	}
	return NULL;
}

static il_factor_unary_op* class_loader_ilload_unary(class_loader* self, ast* source, ilunary_op_type type) {
	il_factor_unary_op* ret = il_factor_unary_op_new(type);
	ast* a = ast_first(source);
	ret->a = class_loader_ilload_factor(self, a);
	return ret;
}

static il_factor_binary_op* class_loader_ilload_binary(class_loader* self, ast* source, ilbinary_op_type type) {
	il_factor_binary_op* ret = il_factor_binary_op_new(type);
	ast* aleft = ast_first(source);
	ast* aright = ast_second(source);
	ret->left = class_loader_ilload_factor(self, aleft);
	ret->right = class_loader_ilload_factor(self, aright);
	return ret;
}

static il_factor_call* class_loader_ilload_call(class_loader* self, ast* source) {
	assert(source->tag == ast_call);
	ast* aname = ast_first(source);
	ast* aargs = ast_second(source);
	il_factor_call* ilcall = il_factor_call_new(aname->u.string_value);
	class_loader_ilload_argument_list(self, ilcall->argument_list, aargs);
	return ilcall;
}

static il_factor_invoke* class_loader_ilload_invoke(class_loader* self, ast* source) {
	assert(source->tag == ast_invoke);
	ast* areceiver = ast_at(source, 0);
	ast* aname = ast_at(source, 1);
	ast* aargs = ast_at(source, 2);
	il_factor_invoke* ilinvoke = il_factor_invoke_new(aname->u.string_value);
	ilinvoke->receiver = class_loader_ilload_factor(self, areceiver);
	class_loader_ilload_argument_list(self, ilinvoke->argument_list, aargs);
	return ilinvoke;
}

static void class_loader_ilload_argument_list(class_loader* self, vector* list, ast* source) {
	if (source->tag == ast_argument_list) {
		for (int i = 0; i < source->childCount; i++) {
			class_loader_ilload_argument_list(self, list, ast_at(source, i));
		}
	} else if (source->tag == ast_argument) {
		ast* primary = ast_first(source);
		il_argument* ilarg = il_argument_new();
		ilarg->factor = class_loader_ilload_factor(self, primary);
		//il_argument_list_push(list, ilarg);
		vector_push(list, ilarg);
	}
}

static void class_loader_ilload_constructor(class_loader* self, il_class* current, ast* constructor) {
}

//
//sgload
//
static void class_loader_sgload_impl(class_loader* self) {
	script_context* ctx = script_context_get_current();
	il_top_level* iltop = self->il_code;
	class_loader_sgload_import(self, self->il_code->import_list);
	class_loader_sgload_namespace_list(self, self->il_code->namespace_list, NULL);
}

static void class_loader_sgload_import(class_loader* self, vector* ilimports) {
	script_context* ctx = script_context_get_current();
	for (int i = 0; i < ilimports->length; i++) {
		vector_item e = vector_at(ilimports, i);
		il_import* import = (il_import*)e;
		char* withExt = text_concat(import->path, ".signal");
		char* fullPath = io_absolute_path(withExt);
		printf("%s\n", fullPath);
		//そのファイルパスに対応した
		//クラスローダが既に存在するなら無視
		class_loader* cll = tree_map_get(ctx->classLoaderMap, fullPath);
		if (cll != NULL) {
			cll->ref_count++;
			continue;
			//新たに読みこんだなら親に設定
		} else {
			cll = class_loader_new();
			cll->ref_count++;
			cll->parent = self;
			cll->type = content_lib;
			tree_map_put(ctx->classLoaderMap, fullPath, cll);
		}
		//パース
		char* text = io_read_text(fullPath);
		parser* p = parser_parse_from_source(text);
		//パースに失敗
		if (p->fail) {
			self->fail = true;
			free(text);
			parser_pop();
			return;
		//成功
		} else {
			cll->source_code = p->root;
			p->root = NULL;
			free(text);
			parser_pop();
		}
		//ロード
		class_loader_load(cll);
		free(withExt);
		free(fullPath);
	}
}

static void class_loader_sgload_namespace_list(class_loader* self, vector* ilnamespace_list, namespace_* parent) {
	for (int i = 0; i < ilnamespace_list->length; i++) {
		vector_item e = vector_at(ilnamespace_list, i);
		il_namespace* iln = (il_namespace*)e;
		class_loader_sgload_namespace(self, iln, parent);
	}
}

static void class_loader_sgload_namespace(class_loader* self, il_namespace* ilnamespace, namespace_* parent) {
	namespace_* current = NULL;
	if (parent == NULL) {
		current = namespace_create_at_root(ilnamespace->name);
	} else {
		current = namespace_add_namespace(parent, ilnamespace->name);
	}
	class_loader_sgload_namespace_list(self, ilnamespace->namespace_list, current);
	class_loader_sgload_class_list(self, ilnamespace->class_list, current);
}

static void class_loader_sgload_class_list(class_loader* self, vector* ilclass_list, namespace_* parent) {
	for (int i = 0; i < ilclass_list->length; i++) {
		vector_item e = vector_at(ilclass_list, i);
		il_class* ilc = (il_class*)e;
		class_loader_sgload_class(self, ilc, parent);
	}
}

static void class_loader_sgload_class(class_loader* self, il_class* classz, namespace_* parent) {
	class_* cls = class_new(classz->name, class_type_class);
	class_loader_sgload_fields(self, classz, cls);
	class_loader_sgload_methods(self, classz, cls);
	namespace_add_class(parent, cls);
}

static void class_loader_sgload_fields(class_loader* self, il_class* ilclass, class_* classz) {
	vector* ilfield_list = ilclass->field_list;
	for (int i = 0; i < ilfield_list->length; i++) {
		vector_item e = vector_at(ilfield_list, i);
		il_field* ilfield = (il_field*)e;
		field* field = field_new(ilfield->name);
		vector_push(classz->field_list, field);
	}
}

static void class_loader_sgload_methods(class_loader* self, il_class* ilclass, class_* classz) {
	vector* ilmethod_list = ilclass->method_list;
	for (int i = 0; i < ilmethod_list->length; i++) {
		vector_item ep = vector_at(ilmethod_list, i);
		il_method* ilmethod = (il_method*)ep;
		vector* ilparams = ilmethod->parameter_list;
		method* e = method_new(ilmethod->name);
		vector* parameter_list = e->parameter_list;
		e->type = method_type_script;
		e->u.script_method = script_method_new();
		for (int i = 0; i < ilparams->length; i++) {
			vector_item e = vector_at(ilparams, i);
			il_parameter* ilp = (il_parameter*)e;
			parameter* param = parameter_new(ilp->name);
			vector_push(parameter_list, param);
		}
		opcode_buf* buf = class_loader_sgload_body(self, ilmethod->statement_list);
		opcode_buf_delete(e->u.script_method->buf);
		e->u.script_method->buf = buf;
		vector_push(classz->method_list, e);
	}
}

static opcode_buf* class_loader_sgload_body(class_loader* self, vector* stmt_list) {
	opcode_buf* ret = opcode_buf_new();
	for (int i = 0; i < stmt_list->length; i++) {
		vector_item e = vector_at(stmt_list, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_generate(s, ret);
	}
	return ret;
}
