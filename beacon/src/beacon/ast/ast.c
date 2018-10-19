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
	Parser* p = GetCurrentParser();
	PushAST(p->Root, self);
}

ast * MallocAST(ast_tag tag, const char* filename, int lineno) {
	ast* ret = (ast*)mem_malloc(sizeof(ast), filename, lineno);
	assert(ret != NULL);
	ret->tag = tag;
	ret->vchildren = NULL;
	//行番号を取得
	Parser* p = GetCurrentParser();
	if (p != NULL) {
		ret->lineno = p->Lineno;
		assert(p->Lineno >= 0);
		PushVector(p->LinenoTable, p->Lineno);
	} else {
		ret->lineno = -1;
	}
	return ret;
}

ast * NewASTNamespacePath(StringView namev) {
	ast* ret = ast_new(AST_NAMESPACE_PATH_T);
	ret->u.stringv_value = namev;
	return ret;
}

ast * NewASTNamespacePathList(ast * aforward, StringView namev) {
	ast* ret = ast_new(AST_NAMESPACE_PATH_LIST_T);
	PushAST(ret, aforward);
	PushAST(ret, NewASTNamespacePath(namev));
	return ret;
}

ast * NewASTImportPath(ast* astr) {
	ast* ret = ast_new(AST_IMPORT_PATH_T);
	ret->u.stringv_value = astr->u.stringv_value;
	astr->u.stringv_value = 0;
	MEM_FREE(astr);
	return ret;
}

ast * NewASTImportDecl(ast * aimport_path) {
	ast* ret = ast_new(AST_IMPORT_DECL_T);
	PushAST(ret, aimport_path);
	return ret;
}

ast* NewASTImportDeclList(ast* aimport, ast* aimport_list) {
	ast* ret = ast_new(AST_IMPORT_DECL_LIST_T);
	PushAST(ret, aimport);
	PushAST(ret, aimport_list);
	return ret;
}

ast * NewASTScope(ast * astmt_list) {
	ast* ret = ast_new(AST_SCOPE_T);
	PushAST(ret, astmt_list);
	return ret;
}

ast * NewASTScopeEmpty() {
	return NewASTScope(NewASTBlank());
}

ast * NewASTBlank() {
	return ast_new(AST_BLANK_T);
}

ast * NewASTIdentifier(StringView strv) {
	ast* ret = ast_new(AST_IDENTIFIER_T);
	ret->u.stringv_value = strv;
	return ret;
}

ast * NewASTIdentifierList(StringView strv, ast * aident_list) {
	ast* ret = ast_new(AST_IDENTIFIER_LIST_T);
	PushAST(ret, aident_list);
	PushAST(ret, NewASTIdentifier(strv));
	return ret;
}

ast * NewASTProc(ast * aexpr) {
	ast* ret = ast_new(AST_PROC_T);
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
	Parser* p = GetCurrentParser();
	if (p != NULL) {
		if (!IsEmptyVector(p->LinenoTable)) {
			int lineno = (int)PopVector(p->LinenoTable);
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
	return self == NULL || self->tag == AST_BLANK_T;
}

bool IsAccessAST(ast * self) {
	return self->tag == AST_ACCESS_LEVEL_T;
}

bool IsModifierAST(ast * self) {
	return self->tag == AST_MOD_Tifier;
}

bool IsStmtAST(ast* self) {
	switch(self->tag) {
		case AST_STMT_T:
		case AST_STMT_LIST_T:
		case AST_STMT_VARIABLE_DECL_T:
		case AST_STMT_VARIABLE_INIT_T:
		case AST_INFERENCED_TYPE_INIT_T:
		case AST_IF_T:
		case AST_IF_ELSE_T:
		case AST_IF_ELIF_LIST_T:
		case AST_IF_ELIF_LIST_ELSE_T:
		case AST_ELIF_T:
		case AST_ELSE_T:
		case AST_WHILE_T:
		case AST_CONTINUE_T:
		case AST_BREAK_T:
		case AST_PROC_T:
		case AST_STMT_ASSERT_T:
		case AST_STMT_TRY_T:
		case AST_STMT_CATCH_T:
		case AST_STMT_CATCH_LIST_T:
		case AST_STMT_DEFER_T:
		case AST_INJECT_JNI_VALUE_T:
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
	if(self->tag == AST_MOD_Tifier_list) {
		return ASTCastToModifierImpl(self, error);
	}
	assert(IsModifierAST(self));
	return self->u.modifier_value;
}

constructor_chain_type ASTCastToChainType(ast * self) {
	switch (self->tag) {
		case AST_CONSTRUCTOR_CHAIN_THIS_T:
			return CHAIN_TYPE_THIS_T;
		case AST_CONSTRUCTOR_CHAIN_SUPER_T:
			return CHAIN_TYPE_SUPER_T;
		default:
			break;
	}
	return CHAIN_TYPE_SUPER_T;
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
	for(int i=0; i<self->vchildren->Length; i++) {
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