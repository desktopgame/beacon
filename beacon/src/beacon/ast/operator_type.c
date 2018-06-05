#include "operator_type.h"

void operator_fprintf(operator_type self, FILE* fp) {
	switch(self) {
		case operator_add:
			fprintf(fp, "+");
			break;
		case operator_sub:
			fprintf(fp, "-");
			break;
		case operator_mul:
			fprintf(fp, "*");
			break;
		case operator_div:
			fprintf(fp, "/");
			break;
		case operator_mod:
			fprintf(fp, "%%");
			break;
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