#include "il_error.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "../env/compile_context.h"
#include "../util/vector.h"
#include "../util/mem.h"

//proto
static void il_error_print(FILE* fp, il_error_id error_id, va_list ap);
static vector* gPanicStateVec = NULL;
static int gLine = -1;
static const char* gFile = NULL;

typedef struct panic_state {
	bool panic;
} panic_state;


void il_error_report(il_error_id error_id, ...) {
	va_list ap;
	va_start(ap, error_id);
	il_error_vreport(error_id, ap);
	va_end(ap);
}

void il_error_vreport(il_error_id error_id, va_list ap) {
	il_error_print(stderr, error_id, ap);
	assert(gPanicStateVec != NULL);
	assert(gPanicStateVec->length > 0);
	panic_state* ps = (panic_state*)vector_top(gPanicStateVec);
	ps->panic = true;
}

void il_error_enter() {
	if(gPanicStateVec == NULL) {
		gPanicStateVec = vector_new();
	}
	panic_state* ps = (panic_state*)MEM_MALLOC(sizeof(panic_state));
	ps->panic = false;
	vector_push(gPanicStateVec, ps);
}

void il_error_exit() {
	assert(gPanicStateVec != NULL);
	assert(gPanicStateVec->length > 0);
	panic_state* ps = (panic_state*)vector_pop(gPanicStateVec);
	MEM_FREE(ps);
	if(gPanicStateVec->length == 0) {
		vector_delete(gPanicStateVec, vector_deleter_null);
		gPanicStateVec = NULL;
	}
}

void il_error_clear() {
	assert(gPanicStateVec->length > 0);
	panic_state* ps = (panic_state*)vector_top(gPanicStateVec);
	ps->panic = false;
}

bool il_error_panic() {
	assert(gPanicStateVec->length > 0);
	panic_state* ps = (panic_state*)vector_top(gPanicStateVec);
	return ps->panic;
}

int il_error_line(int line) {
	gLine = line;
	return line;
}

const char* il_error_file(const char* filename) {
	gFile = filename;
	return gFile;
}
//private
static void il_error_print(FILE* fp, il_error_id error_id, va_list ap) {
	char* fmt = NULL;
	bool aa = cc_test(ccstate_toplevel);
	switch(error_id) {
		case ilerror_undefined_class:
			fmt = "undefined class: %s";
			break;
		case ilerror_undefined_variable:
			fmt = "undefined variable: %s";
			break;
		case ilerror_undefined_method:
			fmt = "undefined method: %s";
			break;
		case ilerror_undefined_field:
			fmt = "undefined field: %s";
			break;
		case ilerror_undefined_ctor:
			fmt = "undefined ctor: %s";
			break;
		case ilerror_undefined_operator:
			fmt = "undefined operator: %s";
			break;
		case ilerror_construct_abstract_type:
			fmt = "can't construct a abstract type by new operator: %s";
			break;
		default:
			fmt = "if shown this message, it compiler bug";
			break;
	}
	fprintf(fp, "%s<%d>\n", gFile, gLine);
	vfprintf(fp, fmt, ap);
	fprintf(fp, "\n");
}