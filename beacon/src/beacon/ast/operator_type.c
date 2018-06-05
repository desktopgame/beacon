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