#include "class_loader_ilload_stmt_module_impl.h"
#include "class_loader_ilload_factor_module_impl.h"
#include "class_loader_ilload_type_module_impl.h"
#include "../../il/il_stmt_impl.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../class_loader.h"
//proto
static il_stmt* CLIL_bodyImpl(class_loader* self, ast* asource);
static il_stmt_inferenced_type_init* CLIL_inferenced_type_init(class_loader* self, ast* asource);
static il_stmt_variable_decl* CLIL_variable_decl(class_loader* self, ast* asource);
static il_stmt_variable_init* CLIL_variable_init(class_loader* self, ast* asource);
static il_stmt_if* CLIL_if(class_loader* self, ast* asource);
static il_stmt_if* CLIL_if_elif_list(class_loader* self, ast* asource);
static void CLIL_elif_list(class_loader* self, Vector* list, ast* asource);
static il_stmt_if* CLIL_if_else(class_loader* self, ast* asource);
static il_stmt_if* CLIL_if_elif_list_else(class_loader* self, ast* asource);
static il_stmt_while* CLIL_while(class_loader* self, ast* asource);
static il_stmt_return* CLIL_return(class_loader* self, ast* asource);
static il_stmt_try* CLIL_try(class_loader* self, ast* asource);
static void CLIL_catch_list(class_loader* self, Vector* dest, ast* asource);
static il_stmt_throw* CLIL_throw(class_loader* self, ast* asource);
static il_stmt_assert* CLIL_assert(class_loader* self, ast* asource);
static il_stmt_defer* CLIL_defer(class_loader* self, ast* asource);
static il_stmt_yield_return* CLIL_yield_return(class_loader* self, ast* asource);

il_stmt* CLIL_stmt(class_loader* self, ast* source) {
	il_stmt* ret = CLIL_bodyImpl(self, source);
	assert(source->lineno >= 0);
	ret->lineno = source->lineno;
	return ret;
}

void CLIL_body(class_loader* self, Vector* list, ast* source) {
	if(source == NULL) {
		return;
	}
	if (source->tag == AST_STMT_LIST_T || source->tag == AST_SCOPE_T) {
		for (int i = 0; i < source->vchildren->length; i++) {
			CLIL_body(self, list, AtAST(source, i));
		}
	} else {
		il_stmt* stmt = CLIL_bodyImpl(self, source);
		if (stmt != NULL) {
			stmt->lineno = source->lineno;
			assert(source->lineno >= 0);
			PushVector(list, stmt);
		}
	}
}


//private
static il_stmt* CLIL_bodyImpl(class_loader* self, ast* asource) {
	switch (asource->tag) {
		case AST_STMT_T:
		{
			return CLIL_bodyImpl(self, FirstAST(asource));
		}
		case AST_PROC_T:
		{
			ast* afact = FirstAST(asource);
			il_factor* ilfact = CLIL_factor(self, afact);
			il_stmt_proc* ilproc = NewILProc();
			ilproc->factor = ilfact;
			assert(ilfact != NULL);
			return WrapILProc(ilproc);
		}
		case AST_STMT_VARIABLE_DECL_T:
		{
			il_stmt_variable_decl* ilvardecl = CLIL_variable_decl(self, asource);
			return WrapILVariableDecl(ilvardecl);
		}
		case AST_STMT_VARIABLE_INIT_T:
		{
			il_stmt_variable_init* ilvarinit = CLIL_variable_init(self, asource);
			return WrapILVariableInit(ilvarinit);
		}
		case AST_INFERENCED_TYPE_INIT_T:
		{
			il_stmt_inferenced_type_init* ilinfer = CLIL_inferenced_type_init(self, asource);
			return il_stmt_wrap_inferenced_type_init(ilinfer);
		}
		case AST_IF_T:
		{
			il_stmt_if* ilif = CLIL_if(self, asource);
			return WrapILIf(ilif);
		}
		case AST_IF_ELIF_LIST_T:
		{
			il_stmt_if* ilif = CLIL_if_elif_list(self, asource);
			return WrapILIf(ilif);
		}
		case AST_IF_ELSE_T:
		{
			il_stmt_if* ilif = CLIL_if_else(self, asource);
			return WrapILIf(ilif);
		}
		case AST_IF_ELIF_LIST_ELSE_T:
		{
			il_stmt_if* ilif = CLIL_if_elif_list_else(self, asource);
			return WrapILIf(ilif);
		}
		case AST_WHILE_T:
		{
			il_stmt_while* ilwh = CLIL_while(self, asource);
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
			il_stmt_return* ilret = CLIL_return(self, asource);
			return WrapILReturn(ilret);
		}
		case AST_RETURN_EMPTY_T:
		{
			il_stmt* ret = il_stmt_new(ILSTMT_RETURN_EMPTY_T);
			ret->u.return_empty = NULL;
			return ret;
		}
		case AST_STMT_TRY_T:
		{
			il_stmt_try* iltry = CLIL_try(self, asource);
			return WrapILTry(iltry);
		}
		case AST_STMT_THROW_T:
		{
			il_stmt_throw* ilthrow = CLIL_throw(self, asource);
			return WrapILThrow(ilthrow);
		}
		case AST_STMT_ASSERT_T:
		{
			il_stmt_assert* ilas = CLIL_assert(self, asource);
			return WrapILAssert(ilas);
		}
		case AST_STMT_DEFER_T:
		{
			il_stmt_defer* ildef = CLIL_defer(self, asource);
			return WrapILDefer(ildef);
		}
		case AST_YIELD_RETURN_T:
		{
			return WrapILYieldReturn(CLIL_yield_return(self, asource));
		}
		case AST_YIELD_BREAK_T:
		{
			il_stmt* ret = il_stmt_new(ILSTMT_YIELD_BREAK_T);
			ret->u.yield_break = NULL;
			return ret;
		}
		case AST_INJECT_JNI_VALUE_T:
		{
			il_stmt_inject_jni* jni = NewILInjectJNI(asource->u.stringv_value);
			ast* afact = FirstAST(asource);
			jni->fact = CLIL_factor(self, afact);
			jni->fact->lineno = 0;
			return WrapILInjectJNI(jni);
		}
		default:
			break;
	}
	return NULL;
}

static il_stmt_inferenced_type_init * CLIL_inferenced_type_init(class_loader * self, ast * asource) {
	ast* aname = FirstAST(asource);
	ast* afact = SecondAST(asource);
	il_stmt_inferenced_type_init* ret = il_stmt_inferenced_type_init_new(aname->u.stringv_value);
	ret->fact = CLIL_factor(self, afact);
	return ret;
}

static il_stmt_variable_decl* CLIL_variable_decl(class_loader* self, ast* asource) {
	ast* afqcn = FirstAST(asource);
	ast* aname = SecondAST(asource);
	il_stmt_variable_decl* ret = NewILVariableDecl(aname->u.stringv_value);
	ret->namev = aname->u.stringv_value;
	CLIL_generic_cache(FirstAST(afqcn), ret->fqcn);
	return ret;
}

static il_stmt_variable_init* CLIL_variable_init(class_loader* self, ast* asource) {
	ast* afqcn = FirstAST(asource);
	ast* aident = SecondAST(asource);
	ast* afact = AtAST(asource, 2);
	il_stmt_variable_init* ret = NewILVariableInit(aident->u.stringv_value);
	CLIL_generic_cache(afqcn, ret->fqcn);
	ret->fact = CLIL_factor(self, afact);
	return ret;
}

static il_stmt_if* CLIL_if(class_loader* self, ast* asource) {
	assert(asource->tag == AST_IF_T);
	il_stmt_if* ret = NewILIf();
	ast* acond = FirstAST(asource);
	ast* abody = SecondAST(asource);
	il_factor* ilcond = CLIL_factor(self, acond);
	CLIL_body(self, ret->body, abody);
	ret->condition = ilcond;
	return ret;
}

static il_stmt_if* CLIL_if_elif_list(class_loader* self, ast* asource) {
	ast* aif = FirstAST(asource);
	ast* aelif_list = SecondAST(asource);
	il_stmt_if* ilif = CLIL_if(self, aif);
	CLIL_elif_list(self, ilif->elif_list, aelif_list);
	return ilif;
}

static il_stmt_if* CLIL_if_else(class_loader* self, ast* asource) {
	ast* aif = FirstAST(asource);
	ast* aelse = SecondAST(asource);
	ast* abody = FirstAST(aelse);
	il_stmt_if* ilif = CLIL_if(self, aif);
	CLIL_body(self, ilif->else_body->body, abody);
	return ilif;
}

static il_stmt_if* CLIL_if_elif_list_else(class_loader* self, ast* asource) {
	ast* aif_eliflist = FirstAST(asource);
	ast* aelse = SecondAST(asource);
	il_stmt_if* ilif = CLIL_if_elif_list(self, aif_eliflist);
	CLIL_body(self, ilif->else_body->body, FirstAST(aelse));
	return ilif;
}

static il_stmt_while * CLIL_while(class_loader * self, ast * asource) {
	ast* acond = FirstAST(asource);
	ast* abody = SecondAST(asource);
	il_stmt_while* ilwhile = NewILWhile();
	ilwhile->condition = CLIL_factor(self, acond);
	CLIL_body(self, ilwhile->statement_list, abody);
	return ilwhile;
}

static void CLIL_elif_list(class_loader* self, Vector* list, ast* asource) {
	if (asource->tag == AST_ELIF_LIST_T) {
		for (int i = 0; i < asource->vchildren->length; i++) {
			CLIL_elif_list(self, list, AtAST(asource, i));
		}
	} else if (asource->tag == AST_ELIF_T) {
		ast* acond = FirstAST(asource);
		ast* abody = SecondAST(asource);
		il_stmt_elif* ilelif = NewILElif();
		ilelif->condition = CLIL_factor(self, acond);
		CLIL_body(self, ilelif->body, abody);
		PushILElifList(list, ilelif);
	}
}

static il_stmt_return* CLIL_return(class_loader* self, ast* asource) {
	assert(asource->tag == AST_RETURN_T);
	ast* afact = FirstAST(asource);
	il_factor* ilfact = CLIL_factor(self, afact);
	il_stmt_return* ret = NewILReturn();
	ret->fact = ilfact;
	return ret;
}

static il_stmt_try* CLIL_try(class_loader* self, ast* asource) {
	ast* abody = FirstAST(asource);
	ast* acatch_list = SecondAST(asource);
	il_stmt_try* ret = NewILTry();
	CLIL_body(self, ret->statement_list, abody);
	CLIL_catch_list(self, ret->catch_list, acatch_list);
	return ret;
}

static void CLIL_catch_list(class_loader* self, Vector* dest, ast* asource) {
	if(asource->tag == AST_STMT_CATCH_T) {
		ast* atypename = FirstAST(asource);
		ast* aname = SecondAST(asource);
		ast* abody = AtAST(asource, 2);
		il_stmt_catch* ilcatch = NewILCatch(aname->u.stringv_value);
		CLIL_generic_cache(FirstAST(atypename), ilcatch->fqcn);
		CLIL_body(self, ilcatch->statement_list, abody);
		PushVector(dest, ilcatch);

	} else if(asource->tag == AST_STMT_CATCH_LIST_T) {
		for(int i=0; i<asource->vchildren->length; i++) {
			CLIL_catch_list(self, dest, AtAST(asource, i));
		}
	}
}

static il_stmt_throw* CLIL_throw(class_loader* self, ast* asource) {
	il_stmt_throw* ret = NewILThrow();
	ret->fact = CLIL_factor(self, FirstAST(asource));
	return ret;
}

static il_stmt_assert* CLIL_assert(class_loader* self, ast* asource) {
	il_stmt_assert* ret = NewILAssert();
	ast* afact = FirstAST(asource);
	ast* amsg = SecondAST(asource);
	ret->condition = CLIL_factor(self, afact);
	if(IsBlankAST(amsg)) {
		ret->message = NULL;
	} else {
		ret->message = CLIL_factor(self, amsg);
	}
	return ret;
}

static il_stmt_defer* CLIL_defer(class_loader* self, ast* asource) {
	assert(asource->tag == AST_STMT_DEFER_T);
	ast* astmt = FirstAST(asource);
	il_stmt_defer* ret = NewILDefer();
	ret->stmt = CLIL_stmt(self, astmt);
	return ret;
}

static il_stmt_yield_return* CLIL_yield_return(class_loader* self, ast* asource) {
	il_stmt_yield_return* ret = il_stmt_yield_return_new();
	ret->fact = CLIL_factor(self, FirstAST(asource));
	return ret;
}