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
static ILStatement_variable_decl* CLIL_variable_decl(ClassLoader* self, AST* asource);
static ILStatement_variable_init* CLIL_variable_init(ClassLoader* self, AST* asource);
static ILIf* CLIL_if(ClassLoader* self, AST* asource);
static ILIf* CLIL_if_elif_list(ClassLoader* self, AST* asource);
static void CLIL_elif_list(ClassLoader* self, Vector* list, AST* asource);
static ILIf* CLIL_if_else(ClassLoader* self, AST* asource);
static ILIf* CLIL_if_elif_list_else(ClassLoader* self, AST* asource);
static ILStatement_while* CLIL_while(ClassLoader* self, AST* asource);
static ILReturn* CLIL_return(ClassLoader* self, AST* asource);
static ILStatement_try* CLIL_try(ClassLoader* self, AST* asource);
static void CLIL_catch_list(ClassLoader* self, Vector* dest, AST* asource);
static ILThrow* CLIL_throw(ClassLoader* self, AST* asource);
static ILAssert* CLIL_assert(ClassLoader* self, AST* asource);
static ILDefer* CLIL_defer(ClassLoader* self, AST* asource);
static ILStatement_yield_return* CLIL_yield_return(ClassLoader* self, AST* asource);

ILStatement* CLILStmt(ClassLoader* self, AST* source) {
	ILStatement* ret = CLILBodyImpl(self, source);
	assert(source->Lineno >= 0);
	ret->lineno = source->Lineno;
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
			stmt->lineno = source->Lineno;
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
			ILStatement_variable_decl* ilvardecl = CLIL_variable_decl(self, asource);
			return WrapILVariableDecl(ilvardecl);
		}
		case AST_STMT_VARIABLE_INIT_T:
		{
			ILStatement_variable_init* ilvarinit = CLIL_variable_init(self, asource);
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
			ILStatement_while* ilwh = CLIL_while(self, asource);
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
			ret->u.return_empty = NULL;
			return ret;
		}
		case AST_STMT_TRY_T:
		{
			ILStatement_try* iltry = CLIL_try(self, asource);
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
			ret->u.yield_break = NULL;
			return ret;
		}
		case AST_INJECT_JNI_VALUE_T:
		{
			ILInjectJNI* jni = NewILInjectJNI(asource->Attr.StringVValue);
			AST* afact = FirstAST(asource);
			jni->Value = CLILFactor(self, afact);
			jni->Value->lineno = 0;
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

static ILStatement_variable_decl* CLIL_variable_decl(ClassLoader* self, AST* asource) {
	AST* afqcn = FirstAST(asource);
	AST* aname = SecondAST(asource);
	ILStatement_variable_decl* ret = NewILVariableDecl(aname->Attr.StringVValue);
	ret->namev = aname->Attr.StringVValue;
	CLILGenericCache(FirstAST(afqcn), ret->fqcn);
	return ret;
}

static ILStatement_variable_init* CLIL_variable_init(ClassLoader* self, AST* asource) {
	AST* afqcn = FirstAST(asource);
	AST* aident = SecondAST(asource);
	AST* afact = AtAST(asource, 2);
	ILStatement_variable_init* ret = NewILVariableInit(aident->Attr.StringVValue);
	CLILGenericCache(afqcn, ret->fqcn);
	ret->fact = CLILFactor(self, afact);
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

static ILStatement_while * CLIL_while(ClassLoader * self, AST* asource) {
	AST* acond = FirstAST(asource);
	AST* abody = SecondAST(asource);
	ILStatement_while* ilwhile = NewILWhile();
	ilwhile->condition = CLILFactor(self, acond);
	CLILBody(self, ilwhile->statement_list, abody);
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

static ILStatement_try* CLIL_try(ClassLoader* self, AST* asource) {
	AST* abody = FirstAST(asource);
	AST* acatch_list = SecondAST(asource);
	ILStatement_try* ret = NewILTry();
	CLILBody(self, ret->statement_list, abody);
	CLIL_catch_list(self, ret->catch_list, acatch_list);
	return ret;
}

static void CLIL_catch_list(ClassLoader* self, Vector* dest, AST* asource) {
	if(asource->Tag == AST_STMT_CATCH_T) {
		AST* atypename = FirstAST(asource);
		AST* aname = SecondAST(asource);
		AST* abody = AtAST(asource, 2);
		ILStatement_catch* ilcatch = NewILCatch(aname->Attr.StringVValue);
		CLILGenericCache(FirstAST(atypename), ilcatch->fqcn);
		CLILBody(self, ilcatch->statement_list, abody);
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

static ILStatement_yield_return* CLIL_yield_return(ClassLoader* self, AST* asource) {
	ILStatement_yield_return* ret = ILStatement_yield_return_new();
	ret->fact = CLILFactor(self, FirstAST(asource));
	return ret;
}