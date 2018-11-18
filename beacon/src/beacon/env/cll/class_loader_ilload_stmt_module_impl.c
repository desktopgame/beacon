#include "class_loader_ilload_stmt_module_impl.h"
#include "class_loader_ilload_factor_module_impl.h"
#include "class_loader_ilload_type_module_impl.h"
#include "../../il/il_stmt_impl.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../class_loader.h"
//proto
static ILStatement* CLILBodyImpl(ClassLoader* self, bc_AST* asource);
static ILInferencedTypeInit* CLIL_inferenced_type_init(ClassLoader* self, bc_AST* asource);
static ILVariableDecl* CLIL_variable_decl(ClassLoader* self, bc_AST* asource);
static ILVariableInit* CLIL_variable_init(ClassLoader* self, bc_AST* asource);
static ILIf* CLIL_if(ClassLoader* self, bc_AST* asource);
static ILIf* CLIL_if_elif_list(ClassLoader* self, bc_AST* asource);
static void CLIL_elif_list(ClassLoader* self, Vector* list, bc_AST* asource);
static ILIf* CLIL_if_else(ClassLoader* self, bc_AST* asource);
static ILIf* CLIL_if_elif_list_else(ClassLoader* self, bc_AST* asource);
static ILWhile* CLIL_while(ClassLoader* self, bc_AST* asource);
static ILReturn* CLIL_return(ClassLoader* self, bc_AST* asource);
static ILTry* CLIL_try(ClassLoader* self, bc_AST* asource);
static void CLIL_catch_list(ClassLoader* self, Vector* dest, bc_AST* asource);
static ILThrow* CLIL_throw(ClassLoader* self, bc_AST* asource);
static ILAssert* CLIL_assert(ClassLoader* self, bc_AST* asource);
static ILDefer* CLIL_defer(ClassLoader* self, bc_AST* asource);
static ILYieldReturn* CLIL_yield_return(ClassLoader* self, bc_AST* asource);

ILStatement* CLILStmt(ClassLoader* self, bc_AST* source) {
	ILStatement* ret = CLILBodyImpl(self, source);
	assert(source->Lineno >= 0);
	ret->Lineno = source->Lineno;
	return ret;
}

void CLILBody(ClassLoader* self, Vector* list, bc_AST* source) {
	if(source == NULL) {
		return;
	}
	if (source->Tag == AST_STMT_LIST_T || source->Tag == AST_SCOPE_T) {
		for (int i = 0; i < source->Children->Length; i++) {
			CLILBody(self, list, bc_AtAST(source, i));
		}
	} else {
		ILStatement* stmt = CLILBodyImpl(self, source);
		if (stmt != NULL) {
			stmt->Lineno = source->Lineno;
			assert(source->Lineno >= 0);
			PushVector(list, stmt);
		}
	}
}


//private
static ILStatement* CLILBodyImpl(ClassLoader* self, bc_AST* asource) {
	switch (asource->Tag) {
		case AST_STMT_T:
		{
			return CLILBodyImpl(self, bc_FirstAST(asource));
		}
		case AST_PROC_T:
		{
			bc_AST* afact = bc_FirstAST(asource);
			ILFactor* ilfact = CLILFactor(self, afact);
			ILProc* ilproc = NewILProc();
				ilproc->Factor = ilfact;
			assert(ilfact != NULL);
			return WrapILProc(ilproc);
		}
		case AST_STMT_VARIABLE_DECL_T:
		{
			ILVariableDecl* ilvardecl = CLIL_variable_decl(self, asource);
			return WrapILVariableDecl(ilvardecl);
		}
		case AST_STMT_VARIABLE_INIT_T:
		{
			ILVariableInit* ilvarinit = CLIL_variable_init(self, asource);
			return WrapILVariableInit(ilvarinit);
		}
		case AST_INFERENCED_TYPE_INIT_T:
		{
			ILInferencedTypeInit* ilinfer = CLIL_inferenced_type_init(self, asource);
			return WrapILInferencedTypeInit(ilinfer);
		}
		case AST_IF_T:
		{
			ILIf* ilif = CLIL_if(self, asource);
			return WrapILIf(ilif);
		}
		case AST_IF_ELIF_LIST_T:
		{
			ILIf* ilif = CLIL_if_elif_list(self, asource);
			return WrapILIf(ilif);
		}
		case AST_IF_ELSE_T:
		{
			ILIf* ilif = CLIL_if_else(self, asource);
			return WrapILIf(ilif);
		}
		case AST_IF_ELIF_LIST_ELSE_T:
		{
			ILIf* ilif = CLIL_if_elif_list_else(self, asource);
			return WrapILIf(ilif);
		}
		case AST_WHILE_T:
		{
			ILWhile* ilwh = CLIL_while(self, asource);
			return WrapILWhile(ilwh);
		}
		case AST_BREAK_T:
		{
			return WrapILBreak();
		}
		case AST_CONTINUE_T:
		{
			return WrapILContinue();
		}
		case AST_RETURN_T:
		{
			ILReturn* ilret = CLIL_return(self, asource);
			return WrapILReturn(ilret);
		}
		case AST_RETURN_EMPTY_T:
		{
			ILStatement* ret = NewILStatement(ILSTMT_RETURN_EMPTY_T);
			ret->Kind.ReturnEmpty = NULL;
			return ret;
		}
		case AST_STMT_TRY_T:
		{
			ILTry* iltry = CLIL_try(self, asource);
			return WrapILTry(iltry);
		}
		case AST_STMT_THROW_T:
		{
			ILThrow* ilthrow = CLIL_throw(self, asource);
			return WrapILThrow(ilthrow);
		}
		case AST_STMT_ASSERT_T:
		{
			ILAssert* ilas = CLIL_assert(self, asource);
			return WrapILAssert(ilas);
		}
		case AST_STMT_DEFER_T:
		{
			ILDefer* ildef = CLIL_defer(self, asource);
			return WrapILDefer(ildef);
		}
		case AST_YIELD_RETURN_T:
		{
			return WrapILYieldReturn(CLIL_yield_return(self, asource));
		}
		case AST_YIELD_BREAK_T:
		{
			ILStatement* ret = NewILStatement(ILSTMT_YIELD_BREAK_T);
			ret->Kind.YieldBreak = NULL;
			return ret;
		}
		case AST_INJECT_JNI_VALUE_T:
		{
			ILInjectJNI* jni = NewILInjectJNI(asource->Attr.StringVValue);
			bc_AST* afact = bc_FirstAST(asource);
			jni->Value = CLILFactor(self, afact);
			jni->Value->Lineno = 0;
			return WrapILInjectJNI(jni);
		}
		default:
			break;
	}
	return NULL;
}

static ILInferencedTypeInit * CLIL_inferenced_type_init(ClassLoader * self, bc_AST* asource) {
	bc_AST* aname = bc_FirstAST(asource);
	bc_AST* afact = bc_SecondAST(asource);
	ILInferencedTypeInit* ret = NewILInferencedTypeInit(aname->Attr.StringVValue);
	ret->Value = CLILFactor(self, afact);
	return ret;
}

static ILVariableDecl* CLIL_variable_decl(ClassLoader* self, bc_AST* asource) {
	bc_AST* afqcn = bc_FirstAST(asource);
	bc_AST* aname = bc_SecondAST(asource);
	ILVariableDecl* ret = NewILVariableDecl(aname->Attr.StringVValue);
	ret->Name = aname->Attr.StringVValue;
	CLILGenericCache(bc_FirstAST(afqcn), ret->GCache);
	return ret;
}

static ILVariableInit* CLIL_variable_init(ClassLoader* self, bc_AST* asource) {
	bc_AST* afqcn = bc_FirstAST(asource);
	bc_AST* aident = bc_SecondAST(asource);
	bc_AST* afact = bc_AtAST(asource, 2);
	ILVariableInit* ret = NewILVariableInit(aident->Attr.StringVValue);
	CLILGenericCache(afqcn, ret->GCache);
	ret->Value = CLILFactor(self, afact);
	return ret;
}

static ILIf* CLIL_if(ClassLoader* self, bc_AST* asource) {
	assert(asource->Tag == AST_IF_T);
	ILIf* ret = NewILIf();
	bc_AST* acond = bc_FirstAST(asource);
	bc_AST* abody = bc_SecondAST(asource);
	ILFactor* ilcond = CLILFactor(self, acond);
	CLILBody(self, ret->Body, abody);
	ret->Condition = ilcond;
	return ret;
}

static ILIf* CLIL_if_elif_list(ClassLoader* self, bc_AST* asource) {
	bc_AST* aif = bc_FirstAST(asource);
	bc_AST* aelif_list = bc_SecondAST(asource);
	ILIf* ilif = CLIL_if(self, aif);
	CLIL_elif_list(self, ilif->ElifList, aelif_list);
	return ilif;
}

static ILIf* CLIL_if_else(ClassLoader* self, bc_AST* asource) {
	bc_AST* aif = bc_FirstAST(asource);
	bc_AST* aelse = bc_SecondAST(asource);
	bc_AST* abody = bc_FirstAST(aelse);
	ILIf* ilif = CLIL_if(self, aif);
	CLILBody(self, ilif->Else->Body, abody);
	return ilif;
}

static ILIf* CLIL_if_elif_list_else(ClassLoader* self, bc_AST* asource) {
	bc_AST* aif_eliflist = bc_FirstAST(asource);
	bc_AST* aelse = bc_SecondAST(asource);
	ILIf* ilif = CLIL_if_elif_list(self, aif_eliflist);
	CLILBody(self, ilif->Else->Body, bc_FirstAST(aelse));
	return ilif;
}

static ILWhile * CLIL_while(ClassLoader * self, bc_AST* asource) {
	bc_AST* acond = bc_FirstAST(asource);
	bc_AST* abody = bc_SecondAST(asource);
	ILWhile* ilwhile = NewILWhile();
	ilwhile->Condition = CLILFactor(self, acond);
	CLILBody(self, ilwhile->Statements, abody);
	return ilwhile;
}

static void CLIL_elif_list(ClassLoader* self, Vector* list, bc_AST* asource) {
	if (asource->Tag == AST_ELIF_LIST_T) {
		for (int i = 0; i < asource->Children->Length; i++) {
			CLIL_elif_list(self, list, bc_AtAST(asource, i));
		}
	} else if (asource->Tag == AST_ELIF_T) {
		bc_AST* acond = bc_FirstAST(asource);
		bc_AST* abody = bc_SecondAST(asource);
		ILElif* ilelif = NewILElif();
		ilelif->Condition = CLILFactor(self, acond);
		CLILBody(self, ilelif->Body, abody);
		PushILElifList(list, ilelif);
	}
}

static ILReturn* CLIL_return(ClassLoader* self, bc_AST* asource) {
	assert(asource->Tag == AST_RETURN_T);
	bc_AST* afact = bc_FirstAST(asource);
	ILFactor* ilfact = CLILFactor(self, afact);
	ILReturn* ret = NewILReturn();
	ret->Factor = ilfact;
	return ret;
}

static ILTry* CLIL_try(ClassLoader* self, bc_AST* asource) {
	bc_AST* abody = bc_FirstAST(asource);
	bc_AST* acatch_list = bc_SecondAST(asource);
	ILTry* ret = NewILTry();
	CLILBody(self, ret->Statements, abody);
	CLIL_catch_list(self, ret->Catches, acatch_list);
	return ret;
}

static void CLIL_catch_list(ClassLoader* self, Vector* dest, bc_AST* asource) {
	if(asource->Tag == AST_STMT_CATCH_T) {
		bc_AST* atypename = bc_FirstAST(asource);
		bc_AST* aname = bc_SecondAST(asource);
		bc_AST* abody = bc_AtAST(asource, 2);
		ILCatch* ilcatch = NewILCatch(aname->Attr.StringVValue);
		CLILGenericCache(bc_FirstAST(atypename), ilcatch->GCache);
		CLILBody(self, ilcatch->Statements, abody);
		PushVector(dest, ilcatch);

	} else if(asource->Tag == AST_STMT_CATCH_LIST_T) {
		for(int i=0; i<asource->Children->Length; i++) {
			CLIL_catch_list(self, dest, bc_AtAST(asource, i));
		}
	}
}

static ILThrow* CLIL_throw(ClassLoader* self, bc_AST* asource) {
	ILThrow* ret = NewILThrow();
	ret->Factor = CLILFactor(self, bc_FirstAST(asource));
	return ret;
}

static ILAssert* CLIL_assert(ClassLoader* self, bc_AST* asource) {
	ILAssert* ret = NewILAssert();
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

static ILDefer* CLIL_defer(ClassLoader* self, bc_AST* asource) {
	assert(asource->Tag == AST_STMT_DEFER_T);
	bc_AST* astmt = bc_FirstAST(asource);
	ILDefer* ret = NewILDefer();
	ret->Task = CLILStmt(self, astmt);
	return ret;
}

static ILYieldReturn* CLIL_yield_return(ClassLoader* self, bc_AST* asource) {
	ILYieldReturn* ret = NewILYieldReturn();
	ret->Value = CLILFactor(self, bc_FirstAST(asource));
	return ret;
}