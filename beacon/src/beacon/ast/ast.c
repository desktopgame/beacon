#include "ast.h"
#include "../util/text.h"
#include "../parse/parser.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../env/fqcn_cache.h"
#include "../util/mem.h"
//proto
static void delete_ast_impl(bc_AST* self);
static bc_ModifierType ast_to_modifier(bc_AST* self, bool* error);
static void delete_ast_self(bc_VectorItem item);

void bc_CompileEntryAST(bc_AST* self) {
	bc_Parser* p = bc_GetCurrentParser();
	bc_PushAST(p->Root, self);
}

bc_AST* bc_MallocAST(bc_ASTTag tag, const char* filename, int lineno) {
	bc_AST* ret = (bc_AST*)bc_MXMalloc(sizeof(bc_AST), filename, lineno);
	assert(ret != NULL);
	ret->Tag = tag;
	ret->Children = NULL;
	//行番号を取得
	bc_Parser* p = bc_GetCurrentParser();
	if (p != NULL) {
		ret->Lineno = p->Lineno;
		assert(p->Lineno >= 0);
		bc_PushVector(p->LinenoTable, p->Lineno);
	} else {
		ret->Lineno = -1;
	}
	return ret;
}

bc_AST* bc_NewASTNamespacePath(bc_StringView name) {
	bc_AST* ret = bc_NewAST(AST_NAMESPACE_PATH_T);
	ret->Attr.StringVValue = name;
	return ret;
}

bc_AST* bc_NewASTNamespacePathList(bc_AST* aforward, bc_StringView name) {
	bc_AST* ret = bc_NewAST(AST_NAMESPACE_PATH_LIST_T);
	bc_PushAST(ret, aforward);
	bc_PushAST(ret, bc_NewASTNamespacePath(name));
	return ret;
}

bc_AST* bc_NewASTImportPath(bc_AST* astr) {
	bc_AST* ret = bc_NewAST(AST_IMPORT_PATH_T);
	ret->Attr.StringVValue = astr->Attr.StringVValue;
	astr->Attr.StringVValue = 0;
	MEM_FREE(astr);
	return ret;
}

bc_AST* bc_NewASTImportDecl(bc_AST* aimport_path) {
	bc_AST* ret = bc_NewAST(AST_IMPORT_DECL_T);
	bc_PushAST(ret, aimport_path);
	return ret;
}

bc_AST* bc_NewASTImportDeclList(bc_AST* aimport, bc_AST* aimport_list) {
	bc_AST* ret = bc_NewAST(AST_IMPORT_DECL_LIST_T);
	bc_PushAST(ret, aimport);
	bc_PushAST(ret, aimport_list);
	return ret;
}

bc_AST* bc_NewASTScope(bc_AST* astmt_list) {
	bc_AST* ret = bc_NewAST(AST_SCOPE_T);
	bc_PushAST(ret, astmt_list);
	return ret;
}

bc_AST* bc_NewASTScopeEmpty() {
	return bc_NewASTScope(bc_NewASTBlank());
}

bc_AST* bc_NewASTBlank() {
	return bc_NewAST(AST_BLANK_T);
}

bc_AST* bc_NewASTIdentifier(bc_StringView str) {
	bc_AST* ret = bc_NewAST(AST_IDENTIFIER_T);
	ret->Attr.StringVValue = str;
	return ret;
}

bc_AST* bc_NewASTIdentifierList(bc_StringView str, bc_AST* aident_list) {
	bc_AST* ret = bc_NewAST(AST_IDENTIFIER_LIST_T);
	bc_PushAST(ret, aident_list);
	bc_PushAST(ret, bc_NewASTIdentifier(str));
	return ret;
}

bc_AST* bc_NewASTProc(bc_AST* aexpr) {
	bc_AST* ret = bc_NewAST(AST_PROC_T);
	bc_PushAST(ret, aexpr);
	return ret;
}

bc_AST* bc_PushAST(bc_AST* self, bc_AST* achild) {
	assert(self != NULL);
	assert(achild != NULL);
	if (self->Children == NULL) {
		self->Children = bc_NewVector();
	}
	bc_PushVector(self->Children, achild);
	//行番号を補正
	bc_Parser* p = bc_GetCurrentParser();
	if (p != NULL) {
		if (!bc_IsEmptyVector(p->LinenoTable)) {
			int lineno = (int)bc_PopVector(p->LinenoTable);
			assert(lineno >= 0);
			self->Lineno = lineno;
		}
	}
	return self;
}

bc_AST* bc_AtAST(bc_AST* self, int index) {
	assert(self != NULL);
	return (bc_AST*)bc_AtVector(self->Children, index);
}

bc_AST* bc_FirstAST(bc_AST* self) {
	return bc_AtAST(self, 0);
}

bc_AST* bc_SecondAST(bc_AST* self) {
	return bc_AtAST(self, 1);
}

void bc_DeleteAST(bc_AST* self) {
	if (self == NULL) {
		return;
	}
	delete_ast_impl(self);
}

bool bc_IsBlankAST(bc_AST* self) {
	return self == NULL || self->Tag == AST_BLANK_T;
}

bool bc_IsAccessAST(bc_AST* self) {
	return self->Tag == AST_ACCESS_LEVEL_T;
}

bool bc_IsModifierAST(bc_AST* self) {
	return self->Tag == AST_MOD_Tifier;
}

bool bc_IsStmtAST(bc_AST* self) {
	switch(self->Tag) {
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

bc_AccessLevel bc_ASTCastToAccess(bc_AST* self) {
	assert(bc_IsAccessAST(self));
	return self->Attr.AccessValue;
}

bc_ModifierType bc_ASTCastToModifier(bc_AST* self, bool* error) {
	(*error) = false;
	if(self->Tag == AST_MOD_Tifier_list) {
		return ast_to_modifier(self, error);
	}
	assert(bc_IsModifierAST(self));
	return self->Attr.ModifierValue;
}

bc_ConstructorChainType bc_ASTCastToChainType(bc_AST* self) {
	switch (self->Tag) {
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
static void delete_ast_impl(bc_AST* self) {
	bc_ASTTag tag = self->Tag;
	bc_DeleteVector(self->Children, delete_ast_self);
	self->Children = NULL;
	MEM_FREE(self);
}

static bc_ModifierType ast_to_modifier(bc_AST* self, bool* error) {
	int ret = -1;
	for(int i=0; i<self->Children->Length; i++) {
		if((*error)) {
			break;
		}
		//フラグを合体させる
		if(ret == -1) {
			ret = bc_ASTCastToModifier(bc_AtAST(self, i), error);
		} else {
			//追加の属性がすでに含まれているかどうか
			bc_ModifierType add = bc_ASTCastToModifier(bc_AtAST(self, i), error);
			if((ret & add) > 0) {
				(*error) = true;
			}
			ret |= add;
		}
	}
	bc_ModifierType mt = (bc_ModifierType)ret;
	return mt;
}

static void delete_ast_self(bc_VectorItem item) {
	bc_AST* e = (bc_AST*)item;
	bc_DeleteAST(e);
}