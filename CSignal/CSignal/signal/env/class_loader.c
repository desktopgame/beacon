#include "class_loader.h"
#include <stdlib.h>
#include <assert.h>
//#include <uni>
//#include <uni>
#include "fqcn_cache.h"
#include "../util/mem.h"
#include "../il/il_type_interface.h"
#include "../vm/vm.h"
#include "../vm/opcode.h"
#include "../vm/opcode_buf.h"
#include "../env/native_method_ref.h"
#include "../il/il_argument.h"
#include "../util/vector.h"
#include "../util/logger.h"
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
#include <string.h>

//proto
static class_loader* class_loader_new();

static void class_loader_ilload_impl(class_loader* self, ast* source_code);
static void class_loader_ilload_import(class_loader* self, ast* import_decl);
static void class_loader_ilload_namespace(class_loader* self, vector* parent, ast* namespace_decl);
static void class_loader_ilload_namespace_path_recursive(class_loader* self, ast* namespace_path, ast* namespace_body);
static il_namespace* class_loader_ilload_ast_to_namespace(ast* a);
static void class_loader_ilload_namespace_body(class_loader* self, il_namespace* current, vector* parent, ast* namespace_body);
static void class_loader_ilload_class(class_loader* self, il_namespace* current, ast* class_decl);
static void class_loader_ilload_member_tree(class_loader* self, il_type* current, ast* tree);
static void class_loader_ilload_member(class_loader* self, il_type* current, ast* member, access_level level);
static void class_loader_ilload_field(class_loader* self, il_type* current, ast* field, access_level level);
static void class_loader_ilload_method(class_loader* self, il_type* current, ast* method, access_level level);
static void class_loader_ilload_constructor(class_loader* self, il_type* current, ast* constructor, access_level level);
static void class_loader_ilload_param(class_loader* self, vector* list, ast* source);
static void class_loader_ilload_body(class_loader* self, vector* list, ast* source);
static il_stmt_variable_decl* class_loader_ilload_variable_decl(class_loader* self, ast* source);
static il_stmt_variable_init* class_loader_ilload_variable_init(class_loader* self, ast* source);
static il_stmt_if* class_loader_ilload_if(class_loader* self, ast* source);
static il_stmt_if* class_loader_ilload_if_elif_list(class_loader* self, ast* source);
static void class_loader_ilload_elif_list(class_loader* self, vector* list, ast* source);
static il_stmt_if* class_loader_ilload_if_else(class_loader* self, ast* source);
static il_stmt_if* class_loader_ilload_if_elif_list_else(class_loader* self, ast* source);
static il_stmt_return* class_loader_ilload_return(class_loader* self, ast* source);
static il_factor* class_loader_ilload_factor(class_loader* self, ast* source);
static il_factor_unary_op* class_loader_ilload_unary(class_loader* self, ast* source, ilunary_op_type type);
static il_factor_binary_op* class_loader_ilload_binary(class_loader* self, ast* source, ilbinary_op_type type);
static il_factor_call* class_loader_ilload_call(class_loader* self, ast* source);
static il_factor_invoke* class_loader_ilload_invoke(class_loader* self, ast* source);
static il_factor_named_invoke* class_loader_ilload_named_invoke(class_loader* self, ast* source);
static il_factor_new_instance* class_loader_ilload_new_instance(class_loader* self, ast* source);
static il_factor_field_access* class_loader_ilload_field_access(class_loader* self, ast* source);
static il_factor_static_field_access* class_loader_ilload_static_field_access(class_loader* self, ast* source);
static void class_loader_ilload_fqcn(ast* fqcn, fqcn_cache* dest);
static void class_loader_ilload_fqcn_impl(ast* fqcn, fqcn_cache* dest);
static void class_loader_ilload_argument_list(class_loader* self, vector* list, ast* source);

static void class_loader_sgload_impl(class_loader* self);
static void class_loader_sgload_import(class_loader* self, vector* ilimports);
static void class_loader_sgload_namespace_list(class_loader* self, vector* ilnamespace_list, namespace_* parent);
static void class_loader_sgload_namespace(class_loader* self, il_namespace* ilnamespace, namespace_* parent);
static void class_loader_sgload_type_list(class_loader* self, vector* iltype_list, namespace_* parent);
static void class_loader_sgload_class(class_loader* self, il_type* iltype, namespace_* parent);
static void class_loader_sgload_fields(class_loader* self, il_type* iltype, class_* classz);
static void class_loader_sgload_fields_impl(class_loader* self, il_type* iltype, class_* classz, vector* ilfields);
static void class_loader_sgload_methods(class_loader* self, il_type* iltype, class_* classz);
static void class_loader_sgload_methods_impl(class_loader* self, il_type* iltype, class_* classz, vector* ilmethods);
static void class_loader_sgload_constructors(class_loader* self, il_type* iltype, class_* classz);
static void class_loader_sgload_complete(class_loader* self, il_type* iltype, type* tp);
static void class_loader_sgload_complete_fields(class_loader* self, il_type* iltype, type* tp);
static void class_loader_sgload_complete_fields_impl(class_loader* self, namespace_* scope, vector* ilfields, vector* sgfields);
static void class_loader_sgload_complete_methods(class_loader* self, il_type* iltype, type* tp);
static void class_loader_sgload_complete_methods_impl(class_loader* self, namespace_* scope, il_type* iltype, type* tp, vector* ilmethods, vector* sgmethods);
static void class_loader_sgload_complete_constructors(class_loader* self, il_type* iltype, type* tp);
static void class_loader_sgload_params(class_loader* self, namespace_* scope, vector* param_list, vector* sg_param_liste);
static void class_loader_sgload_chain(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, il_constructor_chain* ilchain, enviroment* env);
static void class_loader_sgload_attach_native_method(class_loader* self, il_type* iltype, class_* classz, il_method* ilmethod, method* me);
static void class_loader_sgload_debug_native_method(method* parent, vm* vm, enviroment* env);
static void class_loader_sgload_body(class_loader* self, vector* stmt_list, enviroment* dest, namespace_* range);

static void class_loader_error(class_loader* self, const char* message);
static void class_loader_errors(class_loader* self, const char* message, const char* a);

class_loader * class_loader_new_entry_point(const char * filename) {
	class_loader* cll = class_loader_new();
	char* text = io_read_text(filename);
	parser* p = parser_parse_from_source_swap(text, filename);
	//解析に失敗した場合
	if (p->fail) {
		class_loader_errors(cll, "parse failed --- %s", p->source_name);
		MEM_FREE(text);
		parser_pop();
		return cll;
	}
	cll->source_code = p->root;
	p->root = NULL;
	MEM_FREE(text);
	parser_pop();
	return cll;
}

void class_loader_load(class_loader * self) {
	assert(self != NULL);
	assert(self->source_code != NULL);
	system("cls");
	//ast_print_tree(self->source_code);
	class_loader_ilload_impl(self, self->source_code);
	if (self->error) { return; }

	class_loader_sgload_impl(self);
	if (self->error) { return; }

	class_loader_sgload_body(self, self->il_code->statement_list, self->env, NULL);
	//このクラスローダーがライブラリをロードしているなら
	//必要最低限の情報を残して後は開放
	if (self->type == content_lib) {
		ast_delete(self->source_code);
		il_top_level_delete(self->il_code);
		self->source_code = NULL;
		self->il_code = NULL;
	}
}

void class_loader_delete(class_loader * self) {
	assert(self != NULL);
	assert(self->ref_count == 0);
	if (self->parent != NULL) {
		self->parent->ref_count--;
	}
	//free(self->source_code);
	ast_delete(self->source_code);
	self->source_code = NULL;

	il_top_level_delete(self->il_code);
	self->il_code = NULL;

	MEM_FREE(self->errorMessage);
	MEM_FREE(self);
}

//private
static class_loader* class_loader_new() {
	class_loader* ret = (class_loader*)MEM_MALLOC(sizeof(class_loader));
	ret->source_code = NULL;
	ret->il_code = NULL;
	ret->parent = NULL;
	ret->ref_count = 0;
	ret->type = content_entry_point;
	ret->import_manager = import_manager_new();
	ret->env = enviroment_new();
	ret->error = false;
	ret->errorMessage = NULL;
	ret->env->context_cll = ret;
	ret->env->toplevel = true;
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
		//print();
		} else if (child->tag == ast_stmt ||
				   child->tag == ast_stmt_list) {
			class_loader_ilload_body(self, self->il_code->statement_list, child);
		} else {
			ast_print(child);
			text_putline();
		}
	}
	//il_top_level_dump(self->il_code, 0);
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
	ast* member_tree = ast_second(class_decl);
	il_class* classz = il_class_new(class_decl->u.string_value);
	il_type* type = il_type_wrap_class(classz);
	//親クラスが宣言されていない
	if(ast_is_blank(super_class)) {
		classz->super = NULL;
	} else {
		ast* atypename = ast_first(super_class);
		class_loader_ilload_fqcn(ast_first(atypename), classz->super);
	}
	//public:
	//    ....
	//    ....
	if (!ast_is_blank(member_tree)) {
		class_loader_ilload_member_tree(self, type, member_tree);
	}
	vector_push(current->type_list, type);
	//il_namespace_add_entity(current, classz);
	//vector_push(current->class_list, classz);
}

static void class_loader_ilload_interface(class_loader* self, il_namespace* current, ast* interface_decl) {
	ast* member_tree = ast_first(interface_decl);
	il_interface* inter = il_interface_new(interface_decl->u.string_value);
	if (!ast_is_blank(member_tree)) {
	}
	vector_push(current->type_list, il_type_wrap_interface(inter));
//	vector_push(current->interface_list, inter);
//	il_namespace_add_entity(inter);
}

static void class_loader_ilload_member_tree(class_loader* self, il_type* current, ast* tree) {
	if (tree->tag == ast_access_member_tree) {
		for (int i = 0; i < tree->childCount; i++) {
			class_loader_ilload_member_tree(self, current, ast_at(tree, i));
		}
	} else if (tree->tag == ast_access_member_list) {
		ast* access = ast_first(tree);
		ast* member_list = ast_second(tree);
		access_level level = ast_cast_to_access(access);
		class_loader_ilload_member(self, current, member_list, level);
	}
}

static void class_loader_ilload_member(class_loader* self, il_type* current, ast* member, access_level level) {
	if(member->tag == ast_member_decl_list) {
		for(int i=0; i<member->childCount; i++) {
			class_loader_ilload_member(self, current, ast_at(member, i), level);
		}
	} else if(member->tag == ast_member_decl) {
		ast* child = ast_first(member);
		if (child->tag == ast_field_decl) {
			class_loader_ilload_field(self, current, child, level);
		} else if (child->tag == ast_func_decl) {
			class_loader_ilload_method(self, current, child, level);
		} else if (child->tag == ast_constructor_decl) {
			class_loader_ilload_constructor(self, current, child, level);
		}
	}
}

static void class_loader_ilload_field(class_loader* self, il_type* current, ast* field, access_level level) {
	assert(current->tag == iltype_class);
	ast* modifier = ast_first(field);
	ast* type_name = ast_second(field);
	ast* access_name = ast_at(field, 2);
	il_field* v = il_field_new(access_name->u.string_value);
	class_loader_ilload_fqcn(ast_first(type_name), v->fqcn);
	//v->type = il_type_new(type_name->u.string_value);
	v->access = level;
	v->modifier = ast_cast_to_modifier(modifier);
	il_class_add_field(current->u.class_, v);
	//vector_push(current->u.class_->field_list, v);
}

static void class_loader_ilload_method(class_loader* self, il_type* current, ast* method, access_level level) {
	assert(current->tag == iltype_class || current->tag == iltype_interface);
	ast* modifier = ast_at(method, 0);
	ast* func_name = ast_at(method, 1);
	ast* param_list = ast_at(method, 2);
	ast* func_body = ast_at(method, 3);
	ast* ret_name = ast_at(method, 4);
	il_method* v = il_method_new(func_name->u.string_value);
	class_loader_ilload_fqcn(ast_first(ret_name), v->return_fqcn);
//	v->return_type = il_type_new(ret_name->u.string_value);
	v->access = level;
	v->modifier = ast_cast_to_modifier(modifier);
	//TEST((!strcmp(v->name, "main")));
	class_loader_ilload_param(self, v->parameter_list, param_list);
	class_loader_ilload_body(self, v->statement_list, func_body);
	il_class_add_method(current->u.class_, v);
	//vector_push(il_type_method_vec(current), v);
}

static void class_loader_ilload_constructor(class_loader* self, il_type* current, ast* constructor, access_level level) {
	assert(current->tag == iltype_class);
	//ast* amodifier = ast_at(constructor, 0);
	ast* aparams = ast_at(constructor, 0);
	ast* achain = ast_at(constructor, 1);
	ast* abody = ast_at(constructor, 2);
	il_constructor_chain* ilchain = NULL;
	if (!ast_is_blank(achain)) {
		ast* achain_type = ast_first(achain);
		ast* aargs = ast_second(achain);
		ilchain = il_constructor_chain_new();
		ilchain->type = ast_cast_to_chain_type(achain_type);
		class_loader_ilload_argument_list(self, ilchain->argument_list, aargs);
	}
	il_constructor* ilcons = il_constructor_new();
	ilcons->access = level;
	ilcons->chain = ilchain;
	//ilcons->modifier = ast_cast_to_modifier(amodifier);
	class_loader_ilload_param(self, ilcons->parameter_list, aparams);
	class_loader_ilload_body(self, ilcons->statement_list, abody);
	vector_push(current->u.class_->constructor_list, ilcons);
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
		class_loader_ilload_fqcn(ast_first(type_name), p->fqcn);
		//p->type = il_type_new(type_name->u.string_value);
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
				assert(ilfact != NULL);
				vector_push(list, il_stmt_wrap_proc(ilproc));
				break;
			}
			case ast_stmt_variable_decl:
			{
				il_stmt_variable_decl* ilvardecl = class_loader_ilload_variable_decl(self, source);
				vector_push(list, il_stmt_wrap_variable_decl(ilvardecl));
				break;
			}
			case ast_stmt_variable_init:
			{
				il_stmt_variable_init* ilvarinit = class_loader_ilload_variable_init(self, source);
				vector_push(list, il_stmt_wrap_variable_init(ilvarinit));
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
			case ast_return:
			{
				il_stmt_return* ilret = class_loader_ilload_return(self, source);
				vector_push(list, il_stmt_wrap_return(ilret));
				break;
			}
			default:
				break;
		}
	}
}

static il_stmt_variable_decl* class_loader_ilload_variable_decl(class_loader* self, ast* source) {
	ast* afqcn = ast_first(source);
	ast* aname = ast_second(source);
	il_stmt_variable_decl* ret = il_stmt_variable_decl_new(aname->u.string_value);
	ret->name = text_strdup(aname->u.string_value);
	class_loader_ilload_fqcn(ast_first(afqcn), ret->fqcn);
	return ret;
}

static il_stmt_variable_init* class_loader_ilload_variable_init(class_loader* self, ast* source) {
	ast* afqcn = ast_first(source);
	ast* aident = ast_second(source);
	ast* afact = ast_at(source, 2);
	il_stmt_variable_init* ret = il_stmt_variable_init_new(aident->u.string_value);
	class_loader_ilload_fqcn(ast_first(afqcn), ret->fqcn);
	ret->fact = class_loader_ilload_factor(self, afact);
	return ret;
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
	class_loader_ilload_body(self, ilif->else_body->body, ast_first(aelse));
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

static il_stmt_return* class_loader_ilload_return(class_loader* self, ast* source) {
	assert(source->tag == ast_return);
	ast* afact = ast_first(source);
	il_factor* ilfact = class_loader_ilload_factor(self, afact);
	il_stmt_return* ret = il_stmt_return_new();
	ret->fact = ilfact;
	return ret;
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
	} else if(source->tag == ast_static_invoke) {
		return il_factor_wrap_named_invoke(class_loader_ilload_named_invoke(self, source));
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
	//operator(= += -= *= /= %=)
	} else if (source->tag == ast_assign) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_assign));
	} else if (source->tag == ast_add_assign) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_add_assign));
	} else if (source->tag == ast_sub_assign) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_sub_assign));
	} else if (source->tag == ast_mul_assign) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_mul_assign));
	} else if (source->tag == ast_div_assign) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_div_assign));
	} else if (source->tag == ast_mod_assign) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_mod_assign));
	} else if (source->tag == ast_not) {
		return il_factor_wrap_unary(class_loader_ilload_unary(self, source, ilunary_not));
	} else if(source->tag == ast_neg) {
		return il_factor_wrap_unary(class_loader_ilload_unary(self, source, ilunary_neg));
	//this super
	} else if (source->tag == ast_this) {
		il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
		ret->type = ilfactor_this;
		ret->u.this_ = 0;
		return ret;
	} else if (source->tag == ast_super) {
		il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
		ret->type = ilfactor_super;
		ret->u.super_ = 0;
		return ret;
	} else if (source->tag == ast_new_instance) {
		return il_factor_wrap_new_instance(class_loader_ilload_new_instance(self, source));
	} else if (source->tag == ast_field_access) {
		return il_factor_wrap_field_access(class_loader_ilload_field_access(self, source));
	} else if (source->tag == ast_static_field_access) {
		return il_factor_wrap_static_field_access(class_loader_ilload_static_field_access(self, source));
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

static il_factor_named_invoke* class_loader_ilload_named_invoke(class_loader* self, ast* source) {
	assert(source->tag == ast_static_invoke);
	ast* afqcn = ast_at(source, 0);
	ast* aname = ast_at(source, 1);
	ast* aargs = ast_at(source, 2);
	il_factor_named_invoke* ret = il_factor_named_invoke_new(aname->u.string_value);
	if (afqcn->tag == ast_fqcn_class_name) {
		ret->fqcn->name = text_strdup(afqcn->u.string_value);
	} else  class_loader_ilload_fqcn(afqcn, ret->fqcn);
	class_loader_ilload_argument_list(self, ret->argument_list, aargs);
	return ret;
}

static il_factor_new_instance* class_loader_ilload_new_instance(class_loader* self, ast* source) {
	assert(source->tag == ast_new_instance);
	ast* afqcn = ast_first(source);
	ast* aargs = ast_second(source);
	il_factor_new_instance* ret = il_factor_new_instance_new();
	class_loader_ilload_fqcn(ast_first(afqcn), ret->fqcn);
	class_loader_ilload_argument_list(self, ret->argument_list, aargs);
	return ret;
}

static il_factor_field_access* class_loader_ilload_field_access(class_loader* self, ast* source) {
	ast* afact = ast_first(source);
	ast* aident = ast_second(source);
	il_factor_field_access* ret = il_factor_field_access_new(aident->u.string_value);
	ret->fact = class_loader_ilload_factor(self, afact);
	return ret;
}

static il_factor_static_field_access* class_loader_ilload_static_field_access(class_loader* self, ast* source) {
	ast* afqcn = ast_first(source);
	ast* aident = ast_second(source);
	il_factor_static_field_access* ret = il_factor_static_field_access_new(aident->u.string_value);
	class_loader_ilload_fqcn(afqcn, ret->fqcn);
	return ret;
}

static void class_loader_ilload_fqcn(ast* fqcn, fqcn_cache* dest) {
	class_loader_ilload_fqcn_impl(fqcn, dest);
	//FIXME: Int のような文字パースで失敗してしまうので対策
	if (dest->name == NULL &&
		dest->scope_vec->length > 0) {
		dest->name = (char*)vector_pop(dest->scope_vec);
	}
}

static void class_loader_ilload_fqcn_impl(ast* fqcn, fqcn_cache* dest) {
	if (fqcn->tag == ast_fqcn ||
		fqcn->tag == ast_fqcn_part_list) {
		if (fqcn->tag == ast_fqcn_part_list &&
			fqcn->childCount == 0) {
			//FIXME:もうちょっと高速に出来る
			//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
			fqcn->tag = ast_fqcn_class_name;
			dest->name = text_strdup(fqcn->u.string_value);
			return;
		}
		for (int i = 0; i < fqcn->childCount; i++) {
			ast* c = ast_at(fqcn, i);
			class_loader_ilload_fqcn_impl(c, dest);
		}
	} else {
		//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
		vector_push(dest->scope_vec, text_strdup(fqcn->u.string_value));
		fqcn->tag = ast_fqcn_part;
	}
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
			import_manager_import(self->import_manager, cll);
			//そのローダーが破損しているなら
			if (cll->error) {
				class_loader_error(self, cll->errorMessage);
			}
			continue;
		//新たに読みこんだなら親に設定
		} else {
			cll = class_loader_new();
			cll->ref_count++;
			cll->parent = self;
			cll->type = content_lib;
			import_manager_import(self->import_manager, cll);
			tree_map_put(ctx->classLoaderMap, fullPath, cll);
		}
		//そのローダーが破損しているなら
		if (cll->error) {
			class_loader_error(self, cll->errorMessage);
		}
		//パースをキャンセル
		if (self->error) {
			return;
		}
		//パース
		char* text = io_read_text(fullPath);
		parser* p = parser_parse_from_source_swap(text, fullPath);
		//パースに失敗
		if (p->fail) {
			//class_loader_errors(cll, "parse failed --- %s", p->source_name);
			MEM_FREE(text);
			parser_pop();
			return;
		//成功
		} else {
			cll->source_code = p->root;
			p->root = NULL;
			MEM_FREE(text);
			parser_pop();
		}
		//ロード
		class_loader_load(cll);
		MEM_FREE(withExt);
		MEM_FREE(fullPath);
	}
}

static void class_loader_sgload_namespace_list(class_loader* self, vector* ilnamespace_list, namespace_* parent) {
	if (self->error) { return; }
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
	class_loader_sgload_type_list(self, ilnamespace->type_list, current);
}

static void class_loader_sgload_type_list(class_loader* self, vector* iltype_list, namespace_* parent) {
	for (int i = 0; i < iltype_list->length; i++) {
		vector_item e = vector_at(iltype_list, i);
		il_type* ilt = (il_type*)e;
		if (ilt->tag == iltype_class) {
			class_loader_sgload_class(self, ilt, parent);
		} else if (ilt->tag == iltype_interface) {

		}
	}
}

static void class_loader_sgload_class(class_loader* self, il_type* iltype, namespace_* parent) {
	//*
	//既に登録されていたら二重に登録しないように
	//例えば、ネイティブメソッドを登録するために一時的にクラスが登録されている場合がある
	assert(iltype->tag == iltype_class);
	type* tp = namespace_get_type(parent, iltype->u.class_->name);
	class_* cls;
//	class_* cls = namespace_get_type(parent, iltype->u.class_->name);
	if (tp == NULL) {
		cls = class_new(iltype->u.class_->name);
		if (iltype->u.class_->super != NULL) {
			cls->super_class = fqcn_class(iltype->u.class_->super, parent);
		}
		cls->location = parent;
		tp = type_wrap_class(cls);
		namespace_add_type(parent, tp);
	} else {
		cls = tp->u.class_;
	}
	//TEST(!strcmp(type->u.class_->name, "Console"));
	class_loader_sgload_fields(self, iltype, cls);
	class_loader_sgload_methods(self, iltype, cls);
	class_loader_sgload_constructors(self, iltype, cls);
//	class_linkall(cls);
	for (int i = 0; i < cls->field_list->length; i++) {
		field* e = (field*)vector_at(cls->field_list, i);
		e->parent = tp;
	}
	for (int i = 0; i < cls->sfield_list->length; i++) {
		field* e = (field*)vector_at(cls->sfield_list, i);
		e->parent = tp;
	}
	for (int i = 0; i < cls->method_list->length; i++) {
		method* e = (method*)vector_at(cls->method_list, i);
		e->parent = tp;
	}
	for (int i = 0; i < cls->smethod_list->length; i++) {
		method* e = (method*)vector_at(cls->smethod_list, i);
		e->parent = tp;
	}
	for (int i = 0; i < cls->constructor_list->length; i++) {
		constructor* e = (constructor*)vector_at(cls->constructor_list, i);
		e->parent = tp;
	}
	class_loader_sgload_complete(self, iltype, tp);
	///*/
}

static void class_loader_sgload_fields(class_loader* self, il_type* iltype, class_* classz) {
	assert(iltype->tag == iltype_class);
	class_loader_sgload_fields_impl(self, iltype, classz, iltype->u.class_->field_list);
	class_loader_sgload_fields_impl(self, iltype, classz, iltype->u.class_->sfield_list);
}

static void class_loader_sgload_fields_impl(class_loader* self, il_type* iltype, class_* classz, vector* ilfields) {
	for (int i = 0; i < ilfields->length; i++) {
		vector_item e = vector_at(ilfields, i);
		il_field* ilfield = (il_field*)e;
		field* field = field_new(ilfield->name);
		field->access = ilfield->access;
		field->modifier = ilfield->modifier;
		field->parent = classz;
		//NOTE:ここではフィールドの型を設定しません
		//     class_loader_sgload_complete参照
		//vector_push(classz->field_list, field);
		class_add_field(classz, field);
	}
}

static void class_loader_sgload_methods(class_loader* self, il_type* iltype, class_* classz) {
	assert(iltype->tag == iltype_class);
	//TEST(!strcmp(iltype->u.class_->name, "Console"));
	class_loader_sgload_methods_impl(self, iltype, classz, iltype->u.class_->method_list);
	class_loader_sgload_methods_impl(self, iltype, classz, iltype->u.class_->smethod_list);
	//TEST(iltype->u.class_->method_list->length != classz->method_list->length);
	//TEST(iltype->u.class_->smethod_list->length != classz->smethod_list->length);
}

static void class_loader_sgload_methods_impl(class_loader* self, il_type* iltype, class_* classz, vector* ilmethods) {
	for (int i = 0; i < ilmethods->length; i++) {
		//メソッド一覧から取り出す
		vector_item e = vector_at(ilmethods, i);
		il_method* ilmethod = (il_method*)e;
		//メソッドから仮引数一覧を取りだす
		vector* ilparams = ilmethod->parameter_list;
		//実行時のメソッド情報を作成する
		method* method = method_new(ilmethod->name);
		vector* parameter_list = method->parameter_list;
		method->type = modifier_is_native(ilmethod->modifier) ? method_type_native : method_type_script;
		method->access = ilmethod->access;
		method->modifier = ilmethod->modifier;
		method->u.script_method = script_method_new();
		method->parent = classz;
		//ILパラメータを実行時パラメータへ変換
		//NOTE:ここでは戻り値の型,引数の型を設定しません
		//     class_loader_sgload_complete参照
		for (int i = 0; i < ilparams->length; i++) {
			vector_item e = vector_at(ilparams, i);
			il_parameter* ilp = (il_parameter*)e;
			parameter* param = parameter_new(ilp->name);
			vector_push(parameter_list, param);
		}
		//NOTE:クラスの登録が終わったらオペコードを作成する
		//     class_loader_sgload_complete参照
		//enviroment* env = class_loader_sgload_body(self, ilmethod->statement_list);
		//opcode_buf_delete(e->u.script_method->env);
		//method->u.script_method->env = NULL;
		//vector_push(classz->method_list, method);
		class_add_method(classz, method);
	}
}

static void class_loader_sgload_constructors(class_loader* self, il_type* iltype, class_* classz) {
	vector* ilcons_list = iltype->u.class_->constructor_list;
	for (int i = 0; i < ilcons_list->length; i++) {
		vector_item e = vector_at(ilcons_list, i);
		il_constructor* ilcons = (il_constructor*)e;
		//メソッドから仮引数一覧を取りだす
		vector* ilparams = ilcons->parameter_list;
		//実行時のメソッド情報を作成する
		constructor* cons = constructor_new();
		vector* parameter_list = cons->parameter_list;
		cons->access = ilcons->access;
		cons->parent = classz;
		//NOTE:ここでは戻り値の型,引数の型を設定しません
		//     class_loader_sgload_complete参照
		for (int i = 0; i < ilparams->length; i++) {
			vector_item e = vector_at(ilparams, i);
			il_parameter* ilp = (il_parameter*)e;
			parameter* param = parameter_new(ilp->name);
			vector_push(parameter_list, param);
		}
		//vector_push(classz->constructor_list, cons);
		class_add_constructor(classz, cons);
	}
}

/**
 * クラスの登録を行ったあとに呼び出します.
 * 実際には、便宜上終わっていなければいけないいくつかの登録を終えてから
 * オペコードの生成を開始します。
 * 例えば、メソッド呼び出しをオペコードに変換するためには、
 * 既にメソッドの一覧がクラスに登録されている必要があります。
 * ここではそれらの作業を実行します。
 * @param self
 * @param ilclass
 * @param classz
 */
static void class_loader_sgload_complete(class_loader* self, il_type* iltype, type* tp) {
	class_loader_sgload_complete_fields(self, iltype, tp);
	class_loader_sgload_complete_methods(self, iltype, tp);
	class_loader_sgload_complete_constructors(self, iltype, tp);
	class_create_vtable(tp->u.class_);
}

static void class_loader_sgload_complete_fields(class_loader* self, il_type* iltype, type* tp) {
	namespace_* scope = tp->location;
	assert(tp->tag == type_class);
	class_* classz = tp->u.class_;
	vector* fields = classz->field_list;
	if (iltype->tag == iltype_interface) {
		return;
	}
	class_loader_sgload_complete_fields_impl(self, scope, iltype->u.class_->field_list, classz->field_list);
	class_loader_sgload_complete_fields_impl(self, scope, iltype->u.class_->sfield_list, classz->sfield_list);
}

static void class_loader_sgload_complete_fields_impl(class_loader* self, namespace_* scope, vector* ilfields, vector* sgfields) {
//	namespace_* scope = classz->location;
	for (int i = 0; i < sgfields->length; i++) {
		vector_item e = vector_at(sgfields, i);
		field* fi = (field*)e;
		//FIXME:ILフィールドと実行時フィールドのインデックスが同じなのでとりあえず動く
		il_field* ilfield = ((il_field*)vector_at(ilfields, i));
		fi->type = import_manager_resolve(self->import_manager, scope, ilfield->fqcn);
	}
}

static void class_loader_sgload_complete_methods(class_loader* self, il_type* iltype, type* tp) {
	assert(tp->tag == type_class);
	class_* classz = tp->u.class_;
	namespace_* scope = classz->location;
	class_loader_sgload_complete_methods_impl(self, scope, iltype, tp, il_type_method_vec(iltype), classz->method_list);
	class_loader_sgload_complete_methods_impl(self, scope, iltype, tp, il_type_smethod_vec(iltype), classz->smethod_list);
}

static void class_loader_sgload_complete_methods_impl(class_loader* self, namespace_* scope, il_type* iltype, type* tp, vector* ilmethods, vector* sgmethods) {
	assert(tp->tag == type_class);
	class_* classz = tp->u.class_;
	for (int i = 0; i < sgmethods->length; i++) {
		vector_item e = vector_at(sgmethods, i);
		method* me = (method*)e;
		il_method* ilmethod = (il_method*)vector_at(ilmethods, i);
		//戻り値と仮引数に型を設定
		me->return_type = import_manager_resolve(
			self->import_manager,
			scope,
			ilmethod->return_fqcn
			);
		//TEST(!strcmp(me->name, "main"));
		class_loader_sgload_params(self, scope, ilmethod->parameter_list, me->parameter_list);
		//ネイティブメソッドならオペコードは不要
		if (me->type == method_type_native) {
			class_loader_sgload_attach_native_method(self, iltype, classz, ilmethod, me);
			continue;
		}
		//オペコードを作成
		//FIXME:ILメソッドと実行時メソッドのインデックスが同じなのでとりあえず動く
		//まずは仮引数の一覧にインデックスを割り振る
		enviroment* env = enviroment_new();
		vector_push(env->class_vec, tp);
		env->context_cll = self;
		for (int i = 0; i < ilmethod->parameter_list->length; i++) {
			il_parameter* ilparam = (il_parameter*)vector_at(ilmethod->parameter_list, i);
			symbol_table_entry(
				env->sym_table,
				fqcn_type(ilparam->fqcn, scope),
				ilparam->name
				);
			//実引数を保存
			//0番目は this のために開けておく
			opcode_buf_add(env->buf, op_store);
			opcode_buf_add(env->buf, (i + 1));
		}
		//インスタンスメソッドなら
		//0番目を this で埋める
		if (!modifier_is_static(me->modifier)) {
			opcode_buf_add(env->buf, op_store);
			opcode_buf_add(env->buf, 0);
		}
		//NOTE:ここなら名前空間を設定出来る		
		class_loader_sgload_body(self, ilmethod->statement_list, env, scope);
		me->u.script_method->env = env;
		vector_pop(env->class_vec);
	}
}

static void class_loader_sgload_complete_constructors(class_loader* self, il_type* iltype, type* tp) {
	assert(tp->tag == type_class);
	class_* classz = tp->u.class_;
	namespace_* scope = classz->location;
	vector* constructors = classz->constructor_list;
	if (iltype->tag != iltype_class) {
		return;
	}
	//既に登録されたが、
	//オペコードが空っぽになっているコンストラクタの一覧
	for (int i = 0; i < constructors->length; i++) {
		vector_item e = vector_at(constructors, i);
		constructor* cons = (constructor*)e;
		il_constructor* ilcons = (il_constructor*)vector_at(iltype->u.class_->constructor_list, i);
		//仮引数に型を設定する
		class_loader_sgload_params(self, scope, ilcons->parameter_list, cons->parameter_list);
		//まずは仮引数の一覧にインデックスを割り振る
		enviroment* env = enviroment_new();
		vector_push(env->class_vec, tp);
		env->context_cll = self;
		for (int i = 0; i < cons->parameter_list->length; i++) {
			il_parameter* ilparam = (il_parameter*)vector_at(ilcons->parameter_list, i);
			symbol_table_entry(
				env->sym_table,
				fqcn_type(ilparam->fqcn, scope),
				ilparam->name
				);
			//実引数を保存
			//0番目は this のために開けておく
			opcode_buf_add(env->buf, op_store);
			opcode_buf_add(env->buf, (i + 1));
		}
		class_loader_sgload_chain(self, iltype, tp, ilcons, ilcons->chain, env);
		//NOTE:ここなら名前空間を設定出来る		
		class_loader_sgload_body(self, ilcons->statement_list, env, scope);
		cons->env = env;
		vector_pop(env->class_vec);
	}
}

static void class_loader_sgload_params(class_loader* self, namespace_* scope, vector* param_list, vector* sg_param_list) {
//	for (int j = 0; j < ilmethod->parameter_list->length; j++) {
	for (int j = 0; j < param_list->length; j++) {
		//vector_item d = vector_at(ilmethod->parameter_list, j);
		vector_item e = vector_at(param_list, j);
		il_parameter* ilparam = (il_parameter*)e;
		//FIXME:ILパラメータと実行時パラメータのインデックスが同じなのでとりあえず動く
		//parameter* mep = (parameter*)vector_at(me->parameter_list, j);
		parameter* mep = (parameter*)vector_at(sg_param_list, j);
		type* c = import_manager_resolve(
			self->import_manager,
			scope,
			ilparam->fqcn
			);
		TEST(c == NULL);
		mep->type = c;
	}
}

static void class_loader_sgload_chain(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, il_constructor_chain* ilchain, enviroment* env) {
	//親クラスがないなら作成
	class_* classz = tp->u.class_;
	if (classz->super_class == NULL &&
		ilcons->chain == NULL) {
		opcode_buf_add(env->buf, op_new_object);
	}
	if (ilcons->chain == NULL) {
		opcode_buf_add(env->buf, op_alloc_field);
		opcode_buf_add(env->buf, tp->absoluteIndex);
		return;
	}
	//チェインコンストラクタの実引数をプッシュ
	il_constructor_chain* chain = ilcons->chain;
	for (int i = 0; i < chain->argument_list->length; i++) {
		il_argument* ilarg = (il_argument*)vector_at(chain->argument_list, i);
		il_factor_generate(ilarg->factor, env);
	}
	//連鎖先のコンストラクタを検索する
	constructor* chainTarget = NULL;
	int temp = 0;
	if (chain->type == chain_type_this) {
		chainTarget = class_find_constructor(classz, chain->argument_list, env, &temp);
		opcode_buf_add(env->buf, op_chain_this);
		opcode_buf_add(env->buf, tp->absoluteIndex);
	} else if (chain->type == chain_type_super) {
		chainTarget = class_find_constructor(classz->super_class, chain->argument_list, env, &temp);
		opcode_buf_add(env->buf, op_chain_super);
		opcode_buf_add(env->buf, classz->super_class->classIndex);
	}
	chain->c = chainTarget;
	chain->constructorIndex = temp;
	opcode_buf_add(env->buf, temp);
	//親クラスへのチェインなら即座にフィールドを確保
	opcode_buf_add(env->buf, op_alloc_field);
	opcode_buf_add(env->buf, tp->absoluteIndex);
}

static void class_loader_sgload_attach_native_method(class_loader* self, il_type* ilclass, class_* classz, il_method* ilmethod, method* me) {
//	native_method.h で、実行時にリンクするようにしたので不要
//	me->u.native_method->ref = native_method_ref_new(class_loader_sgload_debug_native_method);
}

static void class_loader_sgload_debug_native_method(method* parent, vm* vm, enviroment* env) {

}

static void class_loader_sgload_body(class_loader* self, vector* stmt_list, enviroment* dest, namespace_* range) {
//	enviroment* ret = enviroment_new();
	il_ehandler* eh = il_ehandler_new();
	vector_push(dest->namespace_vec, range);
	for (int i = 0; i < stmt_list->length; i++) {
		vector_item e = vector_at(stmt_list, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_load(s, dest, eh);
	}
	for (int i = 0; i < stmt_list->length; i++) {
		vector_item e = vector_at(stmt_list, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_generate(s, dest);
	}
	vector_pop(dest->namespace_vec);
	il_ehandler_delete(eh);
//	return ret;
}

//utilitiy
static void class_loader_error(class_loader* self, const char* message) {
	self->errorMessage = text_strdup(message);
	self->error = true;
}

static void class_loader_errors(class_loader* self, const char* message, const char* a) {
#if defined(_MSC_VER)
	char buff[100];
	int res = sprintf_s(buff, 100, message, a);
	if (res == -1) {
		class_loader_error(self, text_strdup("internal error: format failed"));
		ERROR("format error");
	} else {
		class_loader_error(self, buff);
	}
#endif
}