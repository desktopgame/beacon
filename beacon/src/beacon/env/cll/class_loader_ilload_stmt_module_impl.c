#include "class_loader_ilload_stmt_module_impl.h"
#include "class_loader_ilload_factor_module_impl.h"
#include "class_loader_ilload_type_module_impl.h"
#include "../../il/il_stmt_impl.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../class_loader.h"
//proto
static bc_ILStatement* CLILBodyImpl(bc_ClassLoader* self, bc_AST* asource);
static bc_ILInferencedTypeInit* CLIL_inferenced_type_init(bc_ClassLoader* self, bc_AST* asource);
static bc_ILVariableDecl* CLIL_variable_decl(bc_ClassLoader* self, bc_AST* asource);
static bc_ILVariableInit* CLIL_variable_init(bc_ClassLoader* self, bc_AST* asource);
static bc_ILIf* CLIL_if(bc_ClassLoader* self, bc_AST* asource);
static bc_ILIf* CLIL_if_elif_list(bc_ClassLoader* self, bc_AST* asource);
static void CLIL_elif_list(bc_ClassLoader* self, bc_Vector* list, bc_AST* asource);
static bc_ILIf* CLIL_if_else(bc_ClassLoader* self, bc_AST* asource);
static bc_ILIf* CLIL_if_elif_list_else(bc_ClassLoader* self, bc_AST* asource);
static bc_ILWhile* CLIL_while(bc_ClassLoader* self, bc_AST* asource);
static bc_ILReturn* CLIL_return(bc_ClassLoader* self, bc_AST* asource);
static bc_ILTry* CLIL_try(bc_ClassLoader* self, bc_AST* asource);
static void CLIL_catch_list(bc_ClassLoader* self, bc_Vector* dest, bc_AST* asource);
static bc_ILThrow* CLIL_throw(bc_ClassLoader* self, bc_AST* asource);
static bc_ILAssert* CLIL_assert(bc_ClassLoader* self, bc_AST* asource);
static bc_ILDefer* CLIL_defer(bc_ClassLoader* self, bc_AST* asource);
static bc_ILYieldReturn* CLIL_yield_return(bc_ClassLoader* self, bc_AST* asource);

bc_ILStatement* CLILStmt(bc_ClassLoader* self, bc_AST* source) {
	bc_ILStatement* ret = CLILBodyImpl(self, source);
	assert(source->Lineno >= 0);
	ret->Lineno = source->Lineno;
	return ret;
}

void CLILBody(bc_ClassLoader* self, bc_Vector* list, bc_AST* source) {
	if(source == NULL) {
		return;
	}
	if (source->Tag == AST_STMT_LIST_T || source->Tag == AST_SCOPE_T) {
		for (int i = 0; i < source->Children->Length; i++) {
			CLILBody(self, list, bc_AtAST(source, i));
		}
	} else {
		bc_ILStatement* stmt = CLILBodyImpl(self, source);
		if (stmt != NULL) {
			stmt->Lineno = source->Lineno;
			assert(source->Lineno >= 0);
			bc_PushVector(list, stmt);
		}
	}
}


//private
static bc_ILStatement* CLILBodyImpl(bc_ClassLoader* self, bc_AST* asource) {
	switch (asource->Tag) {
		case AST_STMT_T:
		{
			return CLILBodyImpl(self, bc_FirstAST(asource));
		}
		case AST_PROC_T:
		{
			bc_AST* afact = bc_FirstAST(asource);
			bc_ILFactor* ilfact = CLILFactor(self, afact);
			bc_ILProc* ilproc = bc_NewILProc();
				ilproc->Factor = ilfact;
			assert(ilfact != NULL);
			return bc_WrapILProc(ilproc);
		}
		case AST_STMT_VARIABLE_DECL_T:
		{
			bc_ILVariableDecl* ilvardecl = CLIL_variable_decl(self, asource);
			return bc_WrapILVariableDecl(ilvardecl);
		}
		case AST_STMT_VARIABLE_INIT_T:
		{
			bc_ILVariableInit* ilvarinit = CLIL_variable_init(self, asource);
			return bc_WrapILVariableInit(ilvarinit);
		}
		case AST_INFERENCED_TYPE_INIT_T:
		{
			bc_ILInferencedTypeInit* ilinfer = CLIL_inferenced_type_init(self, asource);
			return bc_WrapILInferencedTypeInit(ilinfer);
		}
		case AST_IF_T:
		{
			bc_ILIf* ilif = CLIL_if(self, asource);
			return bc_WrapILIf(ilif);
		}
		case AST_IF_ELIF_LIST_T:
		{
			bc_ILIf* ilif = CLIL_if_elif_list(self, asource);
			return bc_WrapILIf(ilif);
		}
		case AST_IF_ELSE_T:
		{
			bc_ILIf* ilif = CLIL_if_else(self, asource);
			return bc_WrapILIf(ilif);
		}
		case AST_IF_ELIF_LIST_ELSE_T:
		{
			bc_ILIf* ilif = CLIL_if_elif_list_else(self, asource);
			return bc_WrapILIf(ilif);
		}
		case AST_WHILE_T:
		{
			bc_ILWhile* ilwh = CLIL_while(self, asource);
			return bc_WrapILWhile(ilwh);
		}
		case AST_BREAK_T:
		{
			return bc_WrapILBreak();
		}
		case AST_CONTINUE_T:
		{
			return bc_WrapILContinue();
		}
		case AST_RETURN_T:
		{
			bc_ILReturn* ilret = CLIL_return(self, asource);
			return bc_WrapILReturn(ilret);
		}
		case AST_RETURN_EMPTY_T:
		{
			bc_ILStatement* ret = bc_NewILStatement(ILSTMT_RETURN_EMPTY_T);
			ret->Kind.ReturnEmpty = NULL;
			return ret;
		}
		case AST_STMT_TRY_T:
		{
			bc_ILTry* iltry = CLIL_try(self, asource);
			return bc_WrapILTry(iltry);
		}
		case AST_STMT_THROW_T:
		{
			bc_ILThrow* ilthrow = CLIL_throw(self, asource);
			return bc_WrapILThrow(ilthrow);
		}
		case AST_STMT_ASSERT_T:
		{
			bc_ILAssert* ilas = CLIL_assert(self, asource);
			return bc_WrapILAssert(ilas);
		}
		case AST_STMT_DEFER_T:
		{
			bc_ILDefer* ildef = CLIL_defer(self, asource);
			return bc_WrapILDefer(ildef);
		}
		case AST_YIELD_RETURN_T:
		{
			return bc_WrapILYieldReturn(CLIL_yield_return(self, asource));
		}
		case AST_YIELD_BREAK_T:
		{
			bc_ILStatement* ret = bc_NewILStatement(ILSTMT_YIELD_BREAK_T);
			ret->Kind.YieldBreak = NULL;
			return ret;
		}
		case AST_INJECT_JNI_VALUE_T:
		{
			bc_ILInjectJNI* jni = bc_NewILInjectJNI(asource->Attr.StringVValue);
			bc_AST* afact = bc_FirstAST(asource);
			jni->Value = CLILFactor(self, afact);
			jni->Value->Lineno = 0;
			return bc_WrapILInjectJNI(jni);
		}
		default:
			break;
	}
	return NULL;
}

static bc_ILInferencedTypeInit * CLIL_inferenced_type_init(bc_ClassLoader * self, bc_AST* asource) {
	bc_AST* aname = bc_FirstAST(asource);
	bc_AST* afact = bc_SecondAST(asource);
	bc_ILInferencedTypeInit* ret = bc_NewILInferencedTypeInit(aname->Attr.StringVValue);
	ret->Value = CLILFactor(self, afact);
	return ret;
}

static bc_ILVariableDecl* CLIL_variable_decl(bc_ClassLoader* self, bc_AST* asource) {
	bc_AST* afqcn = bc_FirstAST(asource);
	bc_AST* aname = bc_SecondAST(asource);
	bc_ILVariableDecl* ret = bc_NewILVariableDecl(aname->Attr.StringVValue);
	ret->Name = aname->Attr.StringVValue;
	CLILGenericCache(bc_FirstAST(afqcn), ret->GCache);
	return ret;
}

static bc_ILVariableInit* CLIL_variable_init(bc_ClassLoader* self, bc_AST* asource) {
	bc_AST* afqcn = bc_FirstAST(asource);
	bc_AST* aident = bc_SecondAST(asource);
	bc_AST* afact = bc_AtAST(asource, 2);
	bc_ILVariableInit* ret = bc_NewILVariableInit(aident->Attr.StringVValue);
	CLILGenericCache(afqcn, ret->GCache);
	ret->Value = CLILFactor(self, afact);
	return ret;
}

static bc_ILIf* CLIL_if(bc_ClassLoader* self, bc_AST* asource) {
	assert(asource->Tag == AST_IF_T);
	bc_ILIf* ret = bc_NewILIf();
	bc_AST* acond = bc_FirstAST(asource);
	bc_AST* abody = bc_SecondAST(asource);
	bc_ILFactor* ilcond = CLILFactor(self, acond);
	CLILBody(self, ret->Body, abody);
	ret->Condition = ilcond;
	return ret;
}

static bc_ILIf* CLIL_if_elif_list(bc_ClassLoader* self, bc_AST* asource) {
	bc_AST* aif = bc_FirstAST(asource);
	bc_AST* aelif_list = bc_SecondAST(asource);
	bc_ILIf* ilif = CLIL_if(self, aif);
	CLIL_elif_list(self, ilif->ElifList, aelif_list);
	return ilif;
}

static bc_ILIf* CLIL_if_else(bc_ClassLoader* self, bc_AST* asource) {
	bc_AST* aif = bc_FirstAST(asource);
	bc_AST* aelse = bc_SecondAST(asource);
	bc_AST* abody = bc_FirstAST(aelse);
	bc_ILIf* ilif = CLIL_if(self, aif);
	CLILBody(self, ilif->Else->Body, abody);
	return ilif;
}

static bc_ILIf* CLIL_if_elif_list_else(bc_ClassLoader* self, bc_AST* asource) {
	bc_AST* aif_eliflist = bc_FirstAST(asource);
	bc_AST* aelse = bc_SecondAST(asource);
	bc_ILIf* ilif = CLIL_if_elif_list(self, aif_eliflist);
	CLILBody(self, ilif->Else->Body, bc_FirstAST(aelse));
	return ilif;
}

static bc_ILWhile * CLIL_while(bc_ClassLoader * self, bc_AST* asource) {
	bc_AST* acond = bc_FirstAST(asource);
	bc_AST* abody = bc_SecondAST(asource);
	bc_ILWhile* ilwhile = bc_NewILWhile();
	ilwhile->Condition = CLILFactor(self, acond);
	CLILBody(self, ilwhile->Statements, abody);
	return ilwhile;
}

static void CLIL_elif_list(bc_ClassLoader* self, bc_Vector* list, bc_AST* asource) {
	if (asource->Tag == AST_ELIF_LIST_T) {
		for (int i = 0; i < asource->Children->Length; i++) {
			CLIL_elif_list(self, list, bc_AtAST(asource, i));
		}
	} else if (asource->Tag == AST_ELIF_T) {
		bc_AST* acond = bc_FirstAST(asource);
		bc_AST* abody = bc_SecondAST(asource);
		bc_ILElif* ilelif = bc_NewILElif();
		ilelif->Condition = CLILFactor(self, acond);
		CLILBody(self, ilelif->Body, abody);
		bc_PushILElifList(list, ilelif);
	}
}

static bc_ILReturn* CLIL_return(bc_ClassLoader* self, bc_AST* asource) {
	assert(asource->Tag == AST_RETURN_T);
	bc_AST* afact = bc_FirstAST(asource);
	bc_ILFactor* ilfact = CLILFactor(self, afact);
	bc_ILReturn* ret = bc_NewILReturn();
	ret->Factor = ilfact;
	return ret;
}

static bc_ILTry* CLIL_try(bc_ClassLoader* self, bc_AST* asource) {
	bc_AST* abody = bc_FirstAST(asource);
	bc_AST* acatch_list = bc_SecondAST(asource);
	bc_ILTry* ret = bc_NewILTry();
	CLILBody(self, ret->Statements, abody);
	CLIL_catch_list(self, ret->Catches, acatch_list);
	return ret;
}

static void CLIL_catch_list(bc_ClassLoader* self, bc_Vector* dest, bc_AST* asource) {
	if(asource->Tag == AST_STMT_CATCH_T) {
		bc_AST* atypename = bc_FirstAST(asource);
		bc_AST* aname = bc_SecondAST(asource);
		bc_AST* abody = bc_AtAST(asource, 2);
		bc_ILCatch* ilcatch = bc_NewILCatch(aname->Attr.StringVValue);
		CLILGenericCache(bc_FirstAST(atypename), ilcatch->GCache);
		CLILBody(self, ilcatch->Statements, abody);
		bc_PushVector(dest, ilcatch);

	} else if(asource->Tag == AST_STMT_CATCH_LIST_T) {
		for(int i=0; i<asource->Children->Length; i++) {
			CLIL_catch_list(self, dest, bc_AtAST(asource, i));
		}
	}
}

static bc_ILThrow* CLIL_throw(bc_ClassLoader* self, bc_AST* asource) {
	bc_ILThrow* ret = bc_NewILThrow();
	ret->Factor = CLILFactor(self, bc_FirstAST(asource));
	return ret;
}

static bc_ILAssert* CLIL_assert(bc_ClassLoader* self, bc_AST* asource) {
	bc_ILAssert* ret = bc_NewILAssert();
	bc_AST* afact = bc_FirstAST(asource);
	bc_AST* amsg = bc_SecondAST(asource);
	ret->Condition = CLILFactor(self, afact);
	if(bc_IsBlankAST(amsg)) {
		ret->Message = NULL;
	} else {
		ret->Message = CLILFactor(self, amsg);
	}
	return ret;
}

static bc_ILDefer* CLIL_defer(bc_ClassLoader* self, bc_AST* asource) {
	assert(asource->Tag == AST_STMT_DEFER_T);
	bc_AST* astmt = bc_FirstAST(asource);
	bc_ILDefer* ret = bc_NewILDefer();
	ret->Task = CLILStmt(self, astmt);
	return ret;
}

static bc_ILYieldReturn* CLIL_yield_return(bc_ClassLoader* self, bc_AST* asource) {
	bc_ILYieldReturn* ret = bc_NewILYieldReturn();
	ret->Value = CLILFactor(self, bc_FirstAST(asource));
	return ret;
}