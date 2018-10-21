#include "ast.h"
#include "../util/text.h"
#include "../parse/parser.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../env/fqcn_cache.h"
#include "../util/mem.h"
//proto
static void DeleteAST_impl(AST* self);
static modifier_type ASTCastToModifierImpl(AST* self, bool* error);
static void DeleteAST_self(VectorItem item);

void CompileEntryAST(AST* self) {
	Parser* p = GetCurrentParser();
	PushAST(p->Root, self);
}

AST* MallocAST(ASTTag tag, const char* filename, int lineno) {
	AST* ret = (AST*)mem_malloc(sizeof(AST), filename, lineno);
	assert(ret != NULL);
	ret->Tag = tag;
	ret->Children = NULL;
	//行番号を取得
	Parser* p = GetCurrentParser();
	if (p != NULL) {
		ret->Lineno = p->Lineno;
		assert(p->Lineno >= 0);
		PushVector(p->LinenoTable, p->Lineno);
	} else {
		ret->Lineno = -1;
	}
	return ret;
}

AST* NewASTNamespacePath(StringView namev) {
	AST* ret = ast_new(AST_NAMESPACE_PATH_T);
	ret->Attr.StringVValue = namev;
	return ret;
}

AST* NewASTNamespacePathList(AST* aforward, StringView namev) {
	AST* ret = ast_new(AST_NAMESPACE_PATH_LIST_T);
	PushAST(ret, aforward);
	PushAST(ret, NewASTNamespacePath(namev));
	return ret;
}

AST* NewASTImportPath(AST* astr) {
	AST* ret = ast_new(AST_IMPORT_PATH_T);
	ret->Attr.StringVValue = astr->Attr.StringVValue;
	astr->Attr.StringVValue = 0;
	MEM_FREE(astr);
	return ret;
}

AST* NewASTImportDecl(AST* aimport_path) {
	AST* ret = ast_new(AST_IMPORT_DECL_T);
	PushAST(ret, aimport_path);
	return ret;
}

AST* NewASTImportDeclList(AST* aimport, AST* aimport_list) {
	AST* ret = ast_new(AST_IMPORT_DECL_LIST_T);
	PushAST(ret, aimport);
	PushAST(ret, aimport_list);
	return ret;
}

AST* NewASTScope(AST* astmt_list) {
	AST* ret = ast_new(AST_SCOPE_T);
	PushAST(ret, astmt_list);
	return ret;
}

AST* NewASTScopeEmpty() {
	return NewASTScope(NewASTBlank());
}

AST* NewASTBlank() {
	return ast_new(AST_BLANK_T);
}

AST* NewASTIdentifier(StringView strv) {
	AST* ret = ast_new(AST_IDENTIFIER_T);
	ret->Attr.StringVValue = strv;
	return ret;
}

AST* NewASTIdentifierList(StringView strv, AST* aident_list) {
	AST* ret = ast_new(AST_IDENTIFIER_LIST_T);
	PushAST(ret, aident_list);
	PushAST(ret, NewASTIdentifier(strv));
	return ret;
}

AST* NewASTProc(AST* aexpr) {
	AST* ret = ast_new(AST_PROC_T);
	PushAST(ret, aexpr);
	return ret;
}

AST* PushAST(AST* self, AST* achild) {
	assert(self != NULL);
	assert(achild != NULL);
	if (self->Children == NULL) {
		self->Children = NewVector();
	}
	PushVector(self->Children, achild);
	//行番号を補正
	Parser* p = GetCurrentParser();
	if (p != NULL) {
		if (!IsEmptyVector(p->LinenoTable)) {
			int lineno = (int)PopVector(p->LinenoTable);
			assert(lineno >= 0);
			self->Lineno = lineno;
		}
	}
	return self;
}

AST* AtAST(AST* self, int index) {
	assert(self != NULL);
	return (AST*)AtVector(self->Children, index);
}

AST* FirstAST(AST* self) {
	return AtAST(self, 0);
}

AST* SecondAST(AST* self) {
	return AtAST(self, 1);
}

void DeleteAST(AST* self) {
	if (self == NULL) {
		return;
	}
	DeleteAST_impl(self);
}

bool IsBlankAST(AST* self) {
	return self == NULL || self->Tag == AST_BLANK_T;
}

bool IsAccessAST(AST* self) {
	return self->Tag == AST_ACCESS_LEVEL_T;
}

bool IsModifierAST(AST* self) {
	return self->Tag == AST_MOD_Tifier;
}

bool IsStmtAST(AST* self) {
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

AccessLevel ASTCastToAccess(AST* self) {
	assert(IsAccessAST(self));
	return self->Attr.AccessValue;
}

modifier_type ASTCastToModifier(AST* self, bool* error) {
	(*error) = false;
	if(self->Tag == AST_MOD_Tifier_list) {
		return ASTCastToModifierImpl(self, error);
	}
	assert(IsModifierAST(self));
	return self->Attr.ModifierValue;
}

ConstructorChainType ASTCastToChainType(AST* self) {
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
static void DeleteAST_impl(AST* self) {
	ASTTag tag = self->Tag;
	DeleteVector(self->Children, DeleteAST_self);
	self->Children = NULL;
	MEM_FREE(self);
}

static modifier_type ASTCastToModifierImpl(AST* self, bool* error) {
	int ret = -1;
	for(int i=0; i<self->Children->Length; i++) {
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
	AST* e = (AST*)item;
	DeleteAST(e);
}