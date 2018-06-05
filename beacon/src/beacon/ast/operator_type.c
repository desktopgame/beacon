#include "operator_type.h"

void operator_fprintf(operator_type self, FILE* fp) {
	fprintf(fp, "%s", operator_tostring(self));
}

char* operator_tostring(operator_type self) {
	switch(self) {
		case operator_add: return "+";
		case operator_sub: return "-";
		case operator_mul: return "*";
		case operator_div: return "/";
		case operator_mod: return "%%";
	}
}

bool operator_arg2(operator_type self) {
	switch(self) {
		case operator_add:
		case operator_sub:
		case operator_mul:
		case operator_div:
		case operator_mod:
			return true;
	}
	return false;
}

bool operator_arg1(operator_type self) {
	return false;
}