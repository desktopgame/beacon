#include "ast.h"
#include "../util/text.h"
#include "../parse/parser.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../env/fqcn_cache.h"
#include "../util/mem.h"
//proto
static void ast_delete_impl(ast* self);
static modifier_type ast_cast_to_modifierImpl(ast * self, bool* error);
static void ast_delete_self(VectorItem item);

void ast_compile_entry(ast * self) {
	parser* p = parser_current();
	ast_push(p->root, self);
}

ast * ast_malloc(ast_tag tag, const char* filename, int lineno) {
	ast* ret = (ast*)mem_malloc(sizeof(ast), filename, lineno);
	assert(ret != NULL);
	ret->tag = tag;
	ret->vchildren = NULL;
	//行番号を取得
	parser* p = parser_current();
	if (p != NULL) {
		ret->lineno = p->lineno;
		assert(p->lineno >= 0);
		PushVector(p->lineno_vec, p->lineno);
	} else {
		ret->lineno = -1;
	}
	return ret;
}

ast * ast_new_namespace_path(string_view namev) {
	ast* ret = ast_new(ast_namespace_path_T);
	ret->u.stringv_value = namev;
	return ret;
}

ast * ast_new_namespace_path_list(ast * aforward, string_view namev) {
	ast* ret = ast_new(ast_namespace_path_list_T);
	ast_push(ret, aforward);
	ast_push(ret, ast_new_namespace_path(namev));
	return ret;
}

ast * ast_new_import_path(ast* astr) {
	ast* ret = ast_new(ast_import_path_T);
	ret->u.stringv_value = astr->u.stringv_value;
	astr->u.stringv_value = 0;
	MEM_FREE(astr);
	return ret;
}

ast * ast_new_import_decl(ast * aimport_path) {
	ast* ret = ast_new(ast_import_decl_T);
	ast_push(ret, aimport_path);
	return ret;
}

ast* ast_new_import_decl_list(ast* aimport, ast* aimport_list) {
	ast* ret = ast_new(ast_import_decl_list_T);
	ast_push(ret, aimport);
	ast_push(ret, aimport_list);
	return ret;
}

ast * ast_new_scope(ast * astmt_list) {
	ast* ret = ast_new(ast_scope_T);
	ast_push(ret, astmt_list);
	return ret;
}

ast * ast_new_scope_empty() {
	return ast_new_scope(ast_new_blank());
}

ast * ast_new_blank() {
	return ast_new(ast_blank_T);
}

ast * ast_new_identifier(string_view strv) {
	ast* ret = ast_new(ast_identifier_T);
	ret->u.stringv_value = strv;
	return ret;
}

ast * ast_new_identifier_list(string_view strv, ast * aident_list) {
	ast* ret = ast_new(ast_identifier_list_T);
	ast_push(ret, aident_list);
	ast_push(ret, ast_new_identifier(strv));
	return ret;
}

ast * ast_new_proc(ast * aexpr) {
	ast* ret = ast_new(ast_proc_T);
	ast_push(ret, aexpr);
	return ret;
}

ast * ast_push(ast * self, ast * achild) {
	assert(self != NULL);
	assert(achild != NULL);
	if (self->vchildren == NULL) {
		self->vchildren = NewVector();
	}
	PushVector(self->vchildren, achild);
	//行番号を補正
	parser* p = parser_current();
	if (p != NULL) {
		if (!IsEmptyVector(p->lineno_vec)) {
			int lineno = (int)PopVector(p->lineno_vec);
			assert(lineno >= 0);
			self->lineno = lineno;
		}
	}
	return self;
}

ast* ast_at(ast * self, int index) {
	assert(self != NULL);
	return (ast*)AtVector(self->vchildren, index);
}

ast * ast_first(ast * self) {
	return ast_at(self, 0);
}

ast * ast_second(ast * self) {
	return ast_at(self, 1);
}

void ast_delete(ast * self) {
	if (self == NULL) {
		return;
	}
	ast_delete_impl(self);
}

bool ast_is_blank(ast * self) {
	return self == NULL || self->tag == ast_blank_T;
}

bool ast_is_access(ast * self) {
	return self->tag == ast_access_level_T;
}

bool ast_is_modifier(ast * self) {
	return self->tag == ast_mod_Tifier;
}

bool ast_is_stmt(ast* self) {
	switch(self->tag) {
		case ast_stmt_T:
		case ast_stmt_list_T:
		case ast_stmt_variable_decl_T:
		case ast_stmt_variable_init_T:
		case ast_inferenced_type_init_T:
		case ast_if_T:
		case ast_if_else_T:
		case ast_if_elif_list_T:
		case ast_if_elif_list_else_T:
		case ast_elif_T:
		case ast_else_T:
		case ast_while_T:
		case ast_continue_T:
		case ast_break_T:
		case ast_proc_T:
		case ast_stmt_assert_T:
		case ast_stmt_try_T:
		case ast_stmt_catch_T:
		case ast_stmt_catch_list_T:
		case ast_stmt_defer_T:
		case ast_inject_jni_value_T:
			return true;
	}
	return false;
}

access_level ast_cast_to_access(ast * self) {
	assert(ast_is_access(self));
	return self->u.access_value;
}

modifier_type ast_cast_to_modifier(ast * self, bool* error) {
	(*error) = false;
	if(self->tag == ast_mod_Tifier_list) {
		return ast_cast_to_modifierImpl(self, error);
	}
	assert(ast_is_modifier(self));
	return self->u.modifier_value;
}

constructor_chain_type ast_cast_to_chain_type(ast * self) {
	switch (self->tag) {
		case ast_constructor_chain_this_T:
			return chain_type_this_T;
		case ast_constructor_chain_super_T:
			return chain_type_super_T;
		default:
			break;
	}
	return chain_type_super_T;
}

//private
static void ast_delete_impl(ast* self) {
	ast_tag tag =self->tag;
	DeleteVector(self->vchildren, ast_delete_self);
	self->vchildren = NULL;
	MEM_FREE(self);
}

static modifier_type ast_cast_to_modifierImpl(ast * self, bool* error) {
	int ret = -1;
	for(int i=0; i<self->vchildren->length; i++) {
		if((*error)) {
			break;
		}
		//フラグを合体させる
		if(ret == -1) {
			ret = ast_cast_to_modifier(ast_at(self, i), error);
		} else {
			//追加の属性がすでに含まれているかどうか
			modifier_type add = ast_cast_to_modifier(ast_at(self, i), error);
			if((ret & add) > 0) {
				(*error) = true;
			}
			ret |= add;
		}
	}
	modifier_type mt = (modifier_type)ret;
	return mt;
}

static void ast_delete_self(VectorItem item) {
	ast* e = (ast*)item;
	ast_delete(e);
}