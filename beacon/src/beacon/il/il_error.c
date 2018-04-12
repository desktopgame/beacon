#include "il_error.h"
#include <stdio.h>

//proto
static void il_error_print(FILE* fp, il_error_id error_id, va_list ap);
static bool gPanic = false;


void il_error_report(il_error_id error_id, ...) {
	va_list ap;
	va_start(ap, error_id);
	il_error_vreport(error_id, ap);
	va_end(ap);
}

void il_error_vreport(il_error_id error_id, va_list ap) {
	il_error_print(stdout, error_id, ap);
	gPanic = true;
}

void il_error_clear() {
	gPanic = false;
}

bool il_error_panic() {
	return gPanic;
}
//private
static void il_error_print(FILE* fp, il_error_id error_id, va_list ap) {
	char* fmt = NULL;
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
		default:
			fmt = "if shown this message, it compiler bug";
			break;
	}
}