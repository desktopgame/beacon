#include "class_loader_ilload_stmt_module_impl.h"
#include "class_loader_ilload_factor_module_impl.h"
#include "class_loader_ilload_type_module_impl.h"
#include "../../il/il_stmt_impl.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../class_loader.h"
//proto
static il_stmt* CLIL_bodyImpl(class_loader* self, ast* source);
static il_stmt_inferenced_type_init* CLIL_inferenced_type_init(class_loader* self, ast* source);
static il_stmt_variable_decl* CLIL_variable_decl(class_loader* self, ast* source);
static il_stmt_variable_init* CLIL_variable_init(class_loader* self, ast* source);
static il_stmt_if* CLIL_if(class_loader* self, ast* source);
static il_stmt_if* CLIL_if_elif_list(class_loader* self, ast* source);
static void CLIL_elif_list(class_loader* self, vector* list, ast* source);
static il_stmt_if* CLIL_if_else(class_loader* self, ast* source);
static il_stmt_if* CLIL_if_elif_list_else(class_loader* self, ast* source);
static il_stmt_while* CLIL_while(class_loader* self, ast* source);
static il_stmt_return* CLIL_return(class_loader* self, ast* source);
static il_stmt_try* CLIL_try(class_loader* self, ast* source);
static void CLIL_catch_list(class_loader* self, vector* dest, ast* source);
static il_stmt_throw* CLIL_throw(class_loader* self, ast* source);
static il_stmt_assert* CLIL_assert(class_loader* self, ast* source);

il_stmt* CLIL_stmt(class_loader* self, ast* source) {
	return CLIL_bodyImpl(self, source);
}

void CLIL_body(class_loader* self, vector* list, ast* source) {
	if (source->tag == ast_stmt_list || source->tag == ast_scope) {
		for (int i = 0; i < source->child_count; i++) {
			CLIL_body(self, list, ast_at(source, i));
		}
	} else {
		il_stmt* stmt = CLIL_bodyImpl(self, source);
		if (stmt != NULL) {
			stmt->lineno = source->lineno;
			vector_push(list, stmt);
		}
	}
}


//private
static il_stmt* CLIL_bodyImpl(class_loader* self, ast* source) {
	//text_printf("    ");
	//ast_print(source);
	//text_printf("\n");
	switch (source->tag) {
		case ast_stmt:
		{
			return CLIL_bodyImpl(self, ast_first(source));
		}
		case ast_proc:
		{
			ast* afact = ast_first(source);
			il_factor* ilfact = CLIL_factor(self, afact);
			il_stmt_proc* ilproc = il_stmt_proc_new();
			ilproc->factor = ilfact;
			assert(ilfact != NULL);
			return il_stmt_wrap_proc(ilproc);
		}
		case ast_stmt_variable_decl:
		{
			il_stmt_variable_decl* ilvardecl = CLIL_variable_decl(self, source);
			return il_stmt_wrap_variable_decl(ilvardecl);
		}
		case ast_stmt_variable_init:
		{
			il_stmt_variable_init* ilvarinit = CLIL_variable_init(self, source);
			return il_stmt_wrap_variable_init(ilvarinit);
		}
		case ast_inferenced_type_init:
		{
			il_stmt_inferenced_type_init* ilinfer = CLIL_inferenced_type_init(self, source);
			return il_stmt_wrap_inferenced_type_init(ilinfer);
		}
		case ast_if:
		{
			il_stmt_if* ilif = CLIL_if(self, source);
			return il_stmt_wrap_if(ilif);
		}
		case ast_if_elif_list:
		{
			il_stmt_if* ilif = CLIL_if_elif_list(self, source);
			return il_stmt_wrap_if(ilif);
		}
		case ast_if_else:
		{
			il_stmt_if* ilif = CLIL_if_else(self, source);
			return il_stmt_wrap_if(ilif);
		}
		case ast_if_elif_list_else:
		{
			il_stmt_if* ilif = CLIL_if_elif_list_else(self, source);
			return il_stmt_wrap_if(ilif);
		}
		case ast_while:
		{
			il_stmt_while* ilwh = CLIL_while(self, source);
			return il_stmt_wrap_while(ilwh);
		}
		case ast_break:
		{
			return il_stmt_wrap_break();
		}
		case ast_continue:
		{
			return il_stmt_wrap_continue();
		}
		case ast_return:
		{
			il_stmt_return* ilret = CLIL_return(self, source);
			return il_stmt_wrap_return(ilret);
		}
		case ast_stmt_try:
		{
			il_stmt_try* iltry = CLIL_try(self, source);
			return il_stmt_wrap_try(iltry);
		}
		case ast_stmt_throw:
		{
			il_stmt_throw* ilthrow = CLIL_throw(self, source);
			return il_stmt_wrap_throw(ilthrow);
		}
		case ast_stmt_assert:
		{
			il_stmt_assert* ilas = CLIL_assert(self, source);
			return il_stmt_wrap_assert(ilas);
		}
		default:
			break;
	}
	return NULL;
}

static il_stmt_inferenced_type_init * CLIL_inferenced_type_init(class_loader * self, ast * source) {
	ast* aname = ast_first(source);
	ast* afact = ast_second(source);
	il_stmt_inferenced_type_init* ret = il_stmt_inferenced_type_init_new(aname->u.string_value);
	ret->fact = CLIL_factor(self, afact);
	return ret;
}

static il_stmt_variable_decl* CLIL_variable_decl(class_loader* self, ast* source) {
	ast* afqcn = ast_first(source);
	ast* aname = ast_second(source);
	il_stmt_variable_decl* ret = il_stmt_variable_decl_new(aname->u.string_value);
	ret->name = text_strdup(aname->u.string_value);
	CLIL_generic_cache(ast_first(afqcn), ret->fqcn);
	return ret;
}

static il_stmt_variable_init* CLIL_variable_init(class_loader* self, ast* source) {
	ast* afqcn = ast_first(source);
	ast* aident = ast_second(source);
	ast* afact = ast_at(source, 2);
	il_stmt_variable_init* ret = il_stmt_variable_init_new(aident->u.string_value);
	CLIL_generic_cache(afqcn, ret->fqcn);
	ret->fact = CLIL_factor(self, afact);
	return ret;
}

static il_stmt_if* CLIL_if(class_loader* self, ast* source) {
	assert(source->tag == ast_if);
	il_stmt_if* ret = il_stmt_if_new();
	ast* acond = ast_first(source);
	ast* abody = ast_second(source);
	il_factor* ilcond = CLIL_factor(self, acond);
	//il_stmt_list* ilbody = il_stmt_list_new();
	CLIL_body(self, ret->body, abody);
	ret->condition = ilcond;
	//ret->body = ilbody;
	return ret;
}

static il_stmt_if* CLIL_if_elif_list(class_loader* self, ast* source) {
	ast* aif = ast_first(source);
	ast* aelif_list = ast_second(source);
	il_stmt_if* ilif = CLIL_if(self, aif);
	CLIL_elif_list(self, ilif->elif_list, aelif_list);
	//il_stmt_list_push(list, ilif);
	return ilif;
}

static il_stmt_if* CLIL_if_else(class_loader* self, ast* source) {
	ast* aif = ast_first(source);
	ast* aelse = ast_second(source);
	ast* abody = ast_first(aelse);
	il_stmt_if* ilif = CLIL_if(self, aif);
	CLIL_body(self, ilif->else_body->body, abody);
	return ilif;
}

static il_stmt_if* CLIL_if_elif_list_else(class_loader* self, ast* source) {
	ast* aif_eliflist = ast_first(source);
	ast* aelse = ast_second(source);
	il_stmt_if* ilif = CLIL_if_elif_list(self, aif_eliflist);
	CLIL_body(self, ilif->else_body->body, ast_first(aelse));
	return ilif;
}

static il_stmt_while * CLIL_while(class_loader * self, ast * source) {
	ast* acond = ast_first(source);
	ast* abody = ast_second(source);
	il_stmt_while* ilwhile = il_stmt_while_new();
	ilwhile->condition = CLIL_factor(self, acond);
	CLIL_body(self, ilwhile->statement_list, abody);
	return ilwhile;
}

static void CLIL_elif_list(class_loader* self, vector* list, ast* source) {
	if (source->tag == ast_elif_list) {
		for (int i = 0; i < source->child_count; i++) {
			CLIL_elif_list(self, list, ast_at(source, i));
		}
	} else if (source->tag == ast_elif) {
		ast* acond = ast_first(source);
		ast* abody = ast_second(source);
		//il_stmt* ilif = il_stmt_if_new();
		il_stmt_elif* ilelif = il_stmt_elif_new();
		ilelif->condition = CLIL_factor(self, acond);
		CLIL_body(self, ilelif->body, abody);
		//il_stmt_list_push(list, ilelif);
		il_stmt_elif_list_push(list, ilelif);
	}
}

static il_stmt_return* CLIL_return(class_loader* self, ast* source) {
	assert(source->tag == ast_return);
	ast* afact = ast_first(source);
	il_factor* ilfact = CLIL_factor(self, afact);
	il_stmt_return* ret = il_stmt_return_new();
	ret->fact = ilfact;
	return ret;
}

static il_stmt_try* CLIL_try(class_loader* self, ast* source) {
	ast* abody = ast_first(source);
	ast* acatch_list = ast_second(source);
	il_stmt_try* ret = il_stmt_try_new();
	CLIL_body(self, ret->statement_list, abody);
	CLIL_catch_list(self, ret->catch_list, acatch_list);
	return ret;
}

static void CLIL_catch_list(class_loader* self, vector* dest, ast* source) {
	if(source->tag == ast_stmt_catch) {
		ast* atypename = ast_first(source);
		ast* aname = ast_second(source);
		ast* abody = ast_at(source, 2);
		il_stmt_catch* ilcatch = il_stmt_catch_new(aname->u.string_value);
		CLIL_generic_cache(ast_first(atypename), ilcatch->fqcn);
		CLIL_body(self, ilcatch->statement_list, abody);
		vector_push(dest, ilcatch);

	} else if(source->tag == ast_stmt_catch_list) {
		for(int i=0; i<source->child_count; i++) {
			CLIL_catch_list(self, dest, ast_at(source, i));
		}
	}
}

static il_stmt_throw* CLIL_throw(class_loader* self, ast* source) {
	il_stmt_throw* ret = il_stmt_throw_new();
	ret->fact = CLIL_factor(self, ast_first(source));
	return ret;
}

static il_stmt_assert* CLIL_assert(class_loader* self, ast* source) {
	il_stmt_assert* ret = il_stmt_assert_new();
	ast* afact = ast_first(source);
	ast* amsg = ast_second(source);
	ret->condition = CLIL_factor(self, afact);
	ret->message = CLIL_factor(self, amsg);
	return ret;
}