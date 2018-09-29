#include "ast.h"
#include "../util/text.h"
#include "../parse/parser.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../env/fqcn_cache.h"
#include "../util/mem.h"
//proto
static void DeleteAST_impl(ast* self);
static modifier_type ASTCastToModifierImpl(ast * self, bool* error);
static void DeleteAST_self(VectorItem item);

void CompileEntryAST(ast * self) {
	parser* p = GetCurrentParser();
	PushAST(p->root, self);
}

ast * MallocAST(ast_tag tag, const char* filename, int lineno) {
	ast* ret = (ast*)mem_malloc(sizeof(ast), filename, lineno);
	assert(ret != NULL);
	ret->tag = tag;
	ret->vchildren = NULL;
	//行番号を取得
	parser* p = GetCurrentParser();
	if (p != NULL) {
		ret->lineno = p->lineno;
		assert(p->lineno >= 0);
		PushVector(p->lineno_vec, p->lineno);
	} else {
		ret->lineno = -1;
	}
	return ret;
}

ast * NewASTNamespacePath(string_view namev) {
	ast* ret = ast_new(ast_namespace_path_T);
	ret->u.stringv_value = namev;
	return ret;
}

ast * NewASTNamespacePathList(ast * aforward, string_view namev) {
	ast* ret = ast_new(ast_namespace_path_list_T);
	PushAST(ret, aforward);
	PushAST(ret, NewASTNamespacePath(namev));
	return ret;
}

ast * NewASTImportPath(ast* astr) {
	ast* ret = ast_new(ast_import_path_T);
	ret->u.stringv_value = astr->u.stringv_value;
	astr->u.stringv_value = 0;
	MEM_FREE(astr);
	return ret;
}

ast * NewASTImportDecl(ast * aimport_path) {
	ast* ret = ast_new(ast_import_decl_T);
	PushAST(ret, aimport_path);
	return ret;
}

ast* NewASTImportDeclList(ast* aimport, ast* aimport_list) {
	ast* ret = ast_new(ast_import_decl_list_T);
	PushAST(ret, aimport);
	PushAST(ret, aimport_list);
	return ret;
}

ast * NewASTScope(ast * astmt_list) {
	ast* ret = ast_new(ast_scope_T);
	PushAST(ret, astmt_list);
	return ret;
}

ast * NewASTScopeEmpty() {
	return NewASTScope(NewASTBlank());
}

ast * NewASTBlank() {
	return ast_new(ast_blank_T);
}

ast * NewASTIdentifier(string_view strv) {
	ast* ret = ast_new(ast_identifier_T);
	ret->u.stringv_value = strv;
	return ret;
}

ast * NewASTIdentifierList(string_view strv, ast * aident_list) {
	ast* ret = ast_new(ast_identifier_list_T);
	PushAST(ret, aident_list);
	PushAST(ret, NewASTIdentifier(strv));
	return ret;
}

ast * NewASTProc(ast * aexpr) {
	ast* ret = ast_new(ast_proc_T);
	PushAST(ret, aexpr);
	return ret;
}

ast * PushAST(ast * self, ast * achild) {
	assert(self != NULL);
	assert(achild != NULL);
	if (self->vchildren == NULL) {
		self->vchildren = NewVector();
	}
	PushVector(self->vchildren, achild);
	//行番号を補正
	parser* p = GetCurrentParser();
	if (p != NULL) {
		if (!IsEmptyVector(p->lineno_vec)) {
			int lineno = (int)PopVector(p->lineno_vec);
			assert(lineno >= 0);
			self->lineno = lineno;
		}
	}
	return self;
}

ast* AtAST(ast * self, int index) {
	assert(self != NULL);
	return (ast*)AtVector(self->vchildren, index);
}

ast * FirstAST(ast * self) {
	return AtAST(self, 0);
}

ast * SecondAST(ast * self) {
	return AtAST(self, 1);
}

void DeleteAST(ast * self) {
	if (self == NULL) {
		return;
	}
	DeleteAST_impl(self);
}

bool IsBlankAST(ast * self) {
	return self == NULL || self->tag == ast_blank_T;
}

bool IsAccessAST(ast * self) {
	return self->tag == ast_access_level_T;
}

bool IsModifierAST(ast * self) {
	return self->tag == ast_mod_Tifier;
}

bool IsStmtAST(ast* self) {
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

access_level ASTCastToAccess(ast * self) {
	assert(IsAccessAST(self));
	return self->u.access_value;
}

modifier_type ASTCastToModifier(ast * self, bool* error) {
	(*error) = false;
	if(self->tag == ast_mod_Tifier_list) {
		return ASTCastToModifierImpl(self, error);
	}
	assert(IsModifierAST(self));
	return self->u.modifier_value;
}

constructor_chain_type ASTCastToChainType(ast * self) {
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
static void DeleteAST_impl(ast* self) {
	ast_tag tag =self->tag;
	DeleteVector(self->vchildren, DeleteAST_self);
	self->vchildren = NULL;
	MEM_FREE(self);
}

static modifier_type ASTCastToModifierImpl(ast * self, bool* error) {
	int ret = -1;
	for(int i=0; i<self->vchildren->length; i++) {
		if((*error)) {
			break;
		}
		//フラグを合体させる
		if(ret == -1) {
			ret = ASTCastToModifier(AtAST(self, i), error);
		} else {
			//追加の属性がすでに含まれているかどうか
			modifier_type add = ASTCastToModifier(AtAST(self, i), error);
			if((ret & add) > 0) {
				(*error) = true;
			}
			ret |= add;
		}
	}
	modifier_type mt = (modifier_type)ret;
	return mt;
}

static void DeleteAST_self(VectorItem item) {
	ast* e = (ast*)item;
	DeleteAST(e);
}