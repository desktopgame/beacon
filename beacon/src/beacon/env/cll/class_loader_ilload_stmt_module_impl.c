#include "class_loader_ilload_stmt_module_impl.h"
#include "class_loader_ilload_factor_module_impl.h"
#include "class_loader_ilload_type_module_impl.h"
#include "../../il/il_stmt_impl.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../class_loader.h"
//proto
static ILStatement* CLILBodyImpl(ClassLoader* self, AST* asource);
static ILInferencedTypeInit* CLIL_inferenced_type_init(ClassLoader* self, AST* asource);
static ILVariableDecl* CLIL_variable_decl(ClassLoader* self, AST* asource);
static ILVariableInit* CLIL_variable_init(ClassLoader* self, AST* asource);
static ILIf* CLIL_if(ClassLoader* self, AST* asource);
static ILIf* CLIL_if_elif_list(ClassLoader* self, AST* asource);
static void CLIL_elif_list(ClassLoader* self, Vector* list, AST* asource);
static ILIf* CLIL_if_else(ClassLoader* self, AST* asource);
static ILIf* CLIL_if_elif_list_else(ClassLoader* self, AST* asource);
static ILWhile* CLIL_while(ClassLoader* self, AST* asource);
static ILReturn* CLIL_return(ClassLoader* self, AST* asource);
static ILTry* CLIL_try(ClassLoader* self, AST* asource);
static void CLIL_catch_list(ClassLoader* self, Vector* dest, AST* asource);
static ILThrow* CLIL_throw(ClassLoader* self, AST* asource);
static ILAssert* CLIL_assert(ClassLoader* self, AST* asource);
static ILDefer* CLIL_defer(ClassLoader* self, AST* asource);
static ILYieldReturn* CLIL_yield_return(ClassLoader* self, AST* asource);

ILStatement* CLILStmt(ClassLoader* self, AST* source) {
	ILStatement* ret = CLILBodyImpl(self, source);
	assert(source->Lineno >= 0);
	ret->Lineno = source->Lineno;
	return ret;
}

void CLILBody(ClassLoader* self, Vector* list, AST* source) {
	if(source == NULL) {
		return;
	}
	if (source->Tag == AST_STMT_LIST_T || source->Tag == AST_SCOPE_T) {
		for (int i = 0; i < source->Children->Length; i++) {
			CLILBody(self, list, AtAST(source, i));
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
static ILStatement* CLILBodyImpl(ClassLoader* self, AST* asource) {
	switch (asource->Tag) {
		case AST_STMT_T:
		{
			return CLILBodyImpl(self, FirstAST(asource));
		}
		case AST_PROC_T:
		{
			AST* afact = FirstAST(asource);
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
			ILStatement* ret = ILStatement_new(ILSTMT_RETURN_EMPTY_T);
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
			ILStatement* ret = ILStatement_new(ILSTMT_YIELD_BREAK_T);
			ret->Kind.YieldBreak = NULL;
			return ret;
		}
		case AST_INJECT_JNI_VALUE_T:
		{
			ILInjectJNI* jni = NewILInjectJNI(asource->Attr.StringVValue);
			AST* afact = FirstAST(asource);
			jni->Value = CLILFactor(self, afact);
			jni->Value->Lineno = 0;
			return WrapILInjectJNI(jni);
		}
		default:
			break;
	}
	return NULL;
}

static ILInferencedTypeInit * CLIL_inferenced_type_init(ClassLoader * self, AST* asource) {
	AST* aname = FirstAST(asource);
	AST* afact = SecondAST(asource);
	ILInferencedTypeInit* ret = NewILInferencedTypeInit(aname->Attr.StringVValue);
	ret->Value = CLILFactor(self, afact);
	return ret;
}

static ILVariableDecl* CLIL_variable_decl(ClassLoader* self, AST* asource) {
	AST* afqcn = FirstAST(asource);
	AST* aname = SecondAST(asource);
	ILVariableDecl* ret = NewILVariableDecl(aname->Attr.StringVValue);
	ret->Name = aname->Attr.StringVValue;
	CLILGenericCache(FirstAST(afqcn), ret->GCache);
	return ret;
}

static ILVariableInit* CLIL_variable_init(ClassLoader* self, AST* asource) {
	AST* afqcn = FirstAST(asource);
	AST* aident = SecondAST(asource);
	AST* afact = AtAST(asource, 2);
	ILVariableInit* ret = NewILVariableInit(aident->Attr.StringVValue);
	CLILGenericCache(afqcn, ret->GCache);
	ret->Value = CLILFactor(self, afact);
	return ret;
}

static ILIf* CLIL_if(ClassLoader* self, AST* asource) {
	assert(asource->Tag == AST_IF_T);
	ILIf* ret = NewILIf();
	AST* acond = FirstAST(asource);
	AST* abody = SecondAST(asource);
	ILFactor* ilcond = CLILFactor(self, acond);
	CLILBody(self, ret->Body, abody);
	ret->Condition = ilcond;
	return ret;
}

static ILIf* CLIL_if_elif_list(ClassLoader* self, AST* asource) {
	AST* aif = FirstAST(asource);
	AST* aelif_list = SecondAST(asource);
	ILIf* ilif = CLIL_if(self, aif);
	CLIL_elif_list(self, ilif->ElifList, aelif_list);
	return ilif;
}

static ILIf* CLIL_if_else(ClassLoader* self, AST* asource) {
	AST* aif = FirstAST(asource);
	AST* aelse = SecondAST(asource);
	AST* abody = FirstAST(aelse);
	ILIf* ilif = CLIL_if(self, aif);
	CLILBody(self, ilif->Else->Body, abody);
	return ilif;
}

static ILIf* CLIL_if_elif_list_else(ClassLoader* self, AST* asource) {
	AST* aif_eliflist = FirstAST(asource);
	AST* aelse = SecondAST(asource);
	ILIf* ilif = CLIL_if_elif_list(self, aif_eliflist);
	CLILBody(self, ilif->Else->Body, FirstAST(aelse));
	return ilif;
}

static ILWhile * CLIL_while(ClassLoader * self, AST* asource) {
	AST* acond = FirstAST(asource);
	AST* abody = SecondAST(asource);
	ILWhile* ilwhile = NewILWhile();
	ilwhile->Condition = CLILFactor(self, acond);
	CLILBody(self, ilwhile->Statements, abody);
	return ilwhile;
}

static void CLIL_elif_list(ClassLoader* self, Vector* list, AST* asource) {
	if (asource->Tag == AST_ELIF_LIST_T) {
		for (int i = 0; i < asource->Children->Length; i++) {
			CLIL_elif_list(self, list, AtAST(asource, i));
		}
	} else if (asource->Tag == AST_ELIF_T) {
		AST* acond = FirstAST(asource);
		AST* abody = SecondAST(asource);
		ILElif* ilelif = NewILElif();
		ilelif->Condition = CLILFactor(self, acond);
		CLILBody(self, ilelif->Body, abody);
		PushILElifList(list, ilelif);
	}
}

static ILReturn* CLIL_return(ClassLoader* self, AST* asource) {
	assert(asource->Tag == AST_RETURN_T);
	AST* afact = FirstAST(asource);
	ILFactor* ilfact = CLILFactor(self, afact);
	ILReturn* ret = NewILReturn();
	ret->Factor = ilfact;
	return ret;
}

static ILTry* CLIL_try(ClassLoader* self, AST* asource) {
	AST* abody = FirstAST(asource);
	AST* acatch_list = SecondAST(asource);
	ILTry* ret = NewILTry();
	CLILBody(self, ret->Statements, abody);
	CLIL_catch_list(self, ret->Catches, acatch_list);
	return ret;
}

static void CLIL_catch_list(ClassLoader* self, Vector* dest, AST* asource) {
	if(asource->Tag == AST_STMT_CATCH_T) {
		AST* atypename = FirstAST(asource);
		AST* aname = SecondAST(asource);
		AST* abody = AtAST(asource, 2);
		ILCatch* ilcatch = NewILCatch(aname->Attr.StringVValue);
		CLILGenericCache(FirstAST(atypename), ilcatch->GCache);
		CLILBody(self, ilcatch->Statements, abody);
		PushVector(dest, ilcatch);

	} else if(asource->Tag == AST_STMT_CATCH_LIST_T) {
		for(int i=0; i<asource->Children->Length; i++) {
			CLIL_catch_list(self, dest, AtAST(asource, i));
		}
	}
}

static ILThrow* CLIL_throw(ClassLoader* self, AST* asource) {
	ILThrow* ret = NewILThrow();
	ret->Factor = CLILFactor(self, FirstAST(asource));
	return ret;
}

static ILAssert* CLIL_assert(ClassLoader* self, AST* asource) {
	ILAssert* ret = NewILAssert();
	AST* afact = FirstAST(asource);
	AST* amsg = SecondAST(asource);
	ret->Condition = CLILFactor(self, afact);
	if(IsBlankAST(amsg)) {
		ret->Message = NULL;
	} else {
		ret->Message = CLILFactor(self, amsg);
	}
	return ret;
}

static ILDefer* CLIL_defer(ClassLoader* self, AST* asource) {
	assert(asource->Tag == AST_STMT_DEFER_T);
	AST* astmt = FirstAST(asource);
	ILDefer* ret = NewILDefer();
	ret->Task = CLILStmt(self, astmt);
	return ret;
}

static ILYieldReturn* CLIL_yield_return(ClassLoader* self, AST* asource) {
	ILYieldReturn* ret = ILYieldReturn_new();
	ret->Value = CLILFactor(self, FirstAST(asource));
	return ret;
}