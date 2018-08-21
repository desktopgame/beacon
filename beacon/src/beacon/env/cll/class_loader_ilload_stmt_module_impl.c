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
static void CLIL_elif_list(class_loader* self, vector* list, ast* asource);
static il_stmt_if* CLIL_if_else(class_loader* self, ast* asource);
static il_stmt_if* CLIL_if_elif_list_else(class_loader* self, ast* asource);
static il_stmt_while* CLIL_while(class_loader* self, ast* asource);
static il_stmt_return* CLIL_return(class_loader* self, ast* asource);
static il_stmt_try* CLIL_try(class_loader* self, ast* asource);
static void CLIL_catch_list(class_loader* self, vector* dest, ast* asource);
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

void CLIL_body(class_loader* self, vector* list, ast* source) {
	if(source == NULL) {
		return;
	}
	if (source->tag == ast_stmt_list_T || source->tag == ast_scope_T) {
		for (int i = 0; i < source->vchildren->length; i++) {
			CLIL_body(self, list, ast_at(source, i));
		}
	} else {
		il_stmt* stmt = CLIL_bodyImpl(self, source);
		if (stmt != NULL) {
			stmt->lineno = source->lineno;
			assert(source->lineno >= 0);
			vector_push(list, stmt);
		}
	}
}


//private
static il_stmt* CLIL_bodyImpl(class_loader* self, ast* asource) {
	switch (asource->tag) {
		case ast_stmt_T:
		{
			return CLIL_bodyImpl(self, ast_first(asource));
		}
		case ast_proc_T:
		{
			ast* afact = ast_first(asource);
			il_factor* ilfact = CLIL_factor(self, afact);
			il_stmt_proc* ilproc = il_stmt_proc_new();
			ilproc->factor = ilfact;
			assert(ilfact != NULL);
			return il_stmt_wrap_proc(ilproc);
		}
		case ast_stmt_variable_decl_T:
		{
			il_stmt_variable_decl* ilvardecl = CLIL_variable_decl(self, asource);
			return il_stmt_wrap_variable_decl(ilvardecl);
		}
		case ast_stmt_variable_init_T:
		{
			il_stmt_variable_init* ilvarinit = CLIL_variable_init(self, asource);
			return il_stmt_wrap_variable_init(ilvarinit);
		}
		case ast_inferenced_type_init_T:
		{
			il_stmt_inferenced_type_init* ilinfer = CLIL_inferenced_type_init(self, asource);
			return il_stmt_wrap_inferenced_type_init(ilinfer);
		}
		case ast_if_T:
		{
			il_stmt_if* ilif = CLIL_if(self, asource);
			return il_stmt_wrap_if(ilif);
		}
		case ast_if_elif_list_T:
		{
			il_stmt_if* ilif = CLIL_if_elif_list(self, asource);
			return il_stmt_wrap_if(ilif);
		}
		case ast_if_else_T:
		{
			il_stmt_if* ilif = CLIL_if_else(self, asource);
			return il_stmt_wrap_if(ilif);
		}
		case ast_if_elif_list_else_T:
		{
			il_stmt_if* ilif = CLIL_if_elif_list_else(self, asource);
			return il_stmt_wrap_if(ilif);
		}
		case ast_while_T:
		{
			il_stmt_while* ilwh = CLIL_while(self, asource);
			return il_stmt_wrap_while(ilwh);
		}
		case ast_break_T:
		{
			return il_stmt_wrap_break();
		}
		case ast_continue_T:
		{
			return il_stmt_wrap_continue();
		}
		case ast_return_T:
		{
			il_stmt_return* ilret = CLIL_return(self, asource);
			return il_stmt_wrap_return(ilret);
		}
		case ast_return_empty_T:
		{
			il_stmt* ret = il_stmt_new(ilstmt_return_empty_T);
			ret->u.return_empty = NULL;
			return ret;
		}
		case ast_stmt_try_T:
		{
			il_stmt_try* iltry = CLIL_try(self, asource);
			return il_stmt_wrap_try(iltry);
		}
		case ast_stmt_throw_T:
		{
			il_stmt_throw* ilthrow = CLIL_throw(self, asource);
			return il_stmt_wrap_throw(ilthrow);
		}
		case ast_stmt_assert_T:
		{
			il_stmt_assert* ilas = CLIL_assert(self, asource);
			return il_stmt_wrap_assert(ilas);
		}
		case ast_stmt_defer_T:
		{
			il_stmt_defer* ildef = CLIL_defer(self, asource);
			return il_stmt_wrap_defer(ildef);
		}
		case ast_yield_return_T:
		{
			return il_stmt_wrap_yield_return(CLIL_yield_return(self, asource));
		}
		case ast_yield_break_T:
		{
			il_stmt* ret = il_stmt_new(ilstmt_yield_break_T);
			ret->u.yield_break = NULL;
			return ret;
		}
		default:
			break;
	}
	return NULL;
}

static il_stmt_inferenced_type_init * CLIL_inferenced_type_init(class_loader * self, ast * asource) {
	ast* aname = ast_first(asource);
	ast* afact = ast_second(asource);
	il_stmt_inferenced_type_init* ret = il_stmt_inferenced_type_init_new(aname->u.stringv_value);
	ret->fact = CLIL_factor(self, afact);
	return ret;
}

static il_stmt_variable_decl* CLIL_variable_decl(class_loader* self, ast* asource) {
	ast* afqcn = ast_first(asource);
	ast* aname = ast_second(asource);
	il_stmt_variable_decl* ret = il_stmt_variable_decl_new(aname->u.stringv_value);
	ret->namev = aname->u.stringv_value;
	CLIL_generic_cache(ast_first(afqcn), ret->fqcn);
	return ret;
}

static il_stmt_variable_init* CLIL_variable_init(class_loader* self, ast* asource) {
	ast* afqcn = ast_first(asource);
	ast* aident = ast_second(asource);
	ast* afact = ast_at(asource, 2);
	il_stmt_variable_init* ret = il_stmt_variable_init_new(aident->u.stringv_value);
	CLIL_generic_cache(afqcn, ret->fqcn);
	ret->fact = CLIL_factor(self, afact);
	return ret;
}

static il_stmt_if* CLIL_if(class_loader* self, ast* asource) {
	assert(asource->tag == ast_if_T);
	il_stmt_if* ret = il_stmt_if_new();
	ast* acond = ast_first(asource);
	ast* abody = ast_second(asource);
	il_factor* ilcond = CLIL_factor(self, acond);
	CLIL_body(self, ret->body, abody);
	ret->condition = ilcond;
	return ret;
}

static il_stmt_if* CLIL_if_elif_list(class_loader* self, ast* asource) {
	ast* aif = ast_first(asource);
	ast* aelif_list = ast_second(asource);
	il_stmt_if* ilif = CLIL_if(self, aif);
	CLIL_elif_list(self, ilif->elif_list, aelif_list);
	return ilif;
}

static il_stmt_if* CLIL_if_else(class_loader* self, ast* asource) {
	ast* aif = ast_first(asource);
	ast* aelse = ast_second(asource);
	ast* abody = ast_first(aelse);
	il_stmt_if* ilif = CLIL_if(self, aif);
	CLIL_body(self, ilif->else_body->body, abody);
	return ilif;
}

static il_stmt_if* CLIL_if_elif_list_else(class_loader* self, ast* asource) {
	ast* aif_eliflist = ast_first(asource);
	ast* aelse = ast_second(asource);
	il_stmt_if* ilif = CLIL_if_elif_list(self, aif_eliflist);
	CLIL_body(self, ilif->else_body->body, ast_first(aelse));
	return ilif;
}

static il_stmt_while * CLIL_while(class_loader * self, ast * asource) {
	ast* acond = ast_first(asource);
	ast* abody = ast_second(asource);
	il_stmt_while* ilwhile = il_stmt_while_new();
	ilwhile->condition = CLIL_factor(self, acond);
	CLIL_body(self, ilwhile->statement_list, abody);
	return ilwhile;
}

static void CLIL_elif_list(class_loader* self, vector* list, ast* asource) {
	if (asource->tag == ast_elif_list_T) {
		for (int i = 0; i < asource->vchildren->length; i++) {
			CLIL_elif_list(self, list, ast_at(asource, i));
		}
	} else if (asource->tag == ast_elif_T) {
		ast* acond = ast_first(asource);
		ast* abody = ast_second(asource);
		il_stmt_elif* ilelif = il_stmt_elif_new();
		ilelif->condition = CLIL_factor(self, acond);
		CLIL_body(self, ilelif->body, abody);
		il_stmt_elif_list_push(list, ilelif);
	}
}

static il_stmt_return* CLIL_return(class_loader* self, ast* asource) {
	assert(asource->tag == ast_return_T);
	ast* afact = ast_first(asource);
	il_factor* ilfact = CLIL_factor(self, afact);
	il_stmt_return* ret = il_stmt_return_new();
	ret->fact = ilfact;
	return ret;
}

static il_stmt_try* CLIL_try(class_loader* self, ast* asource) {
	ast* abody = ast_first(asource);
	ast* acatch_list = ast_second(asource);
	il_stmt_try* ret = il_stmt_try_new();
	CLIL_body(self, ret->statement_list, abody);
	CLIL_catch_list(self, ret->catch_list, acatch_list);
	return ret;
}

static void CLIL_catch_list(class_loader* self, vector* dest, ast* asource) {
	if(asource->tag == ast_stmt_catch_T) {
		ast* atypename = ast_first(asource);
		ast* aname = ast_second(asource);
		ast* abody = ast_at(asource, 2);
		il_stmt_catch* ilcatch = il_stmt_catch_new(aname->u.stringv_value);
		CLIL_generic_cache(ast_first(atypename), ilcatch->fqcn);
		CLIL_body(self, ilcatch->statement_list, abody);
		vector_push(dest, ilcatch);

	} else if(asource->tag == ast_stmt_catch_list_T) {
		for(int i=0; i<asource->vchildren->length; i++) {
			CLIL_catch_list(self, dest, ast_at(asource, i));
		}
	}
}

static il_stmt_throw* CLIL_throw(class_loader* self, ast* asource) {
	il_stmt_throw* ret = il_stmt_throw_new();
	ret->fact = CLIL_factor(self, ast_first(asource));
	return ret;
}

static il_stmt_assert* CLIL_assert(class_loader* self, ast* asource) {
	il_stmt_assert* ret = il_stmt_assert_new();
	ast* afact = ast_first(asource);
	ast* amsg = ast_second(asource);
	ret->condition = CLIL_factor(self, afact);
	if(ast_is_blank(amsg)) {
		ret->message = NULL;
	} else {
		ret->message = CLIL_factor(self, amsg);
	}
	return ret;
}

static il_stmt_defer* CLIL_defer(class_loader* self, ast* asource) {
	assert(asource->tag == ast_stmt_defer_T);
	ast* astmt = ast_first(asource);
	il_stmt_defer* ret = il_stmt_defer_new();
	ret->stmt = CLIL_stmt(self, astmt);
	return ret;
}

static il_stmt_yield_return* CLIL_yield_return(class_loader* self, ast* asource) {
	il_stmt_yield_return* ret = il_stmt_yield_return_new();
	ret->fact = CLIL_factor(self, ast_first(asource));
	return ret;
}