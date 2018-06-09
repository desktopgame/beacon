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

		case operator_bit_or: return "|";
		case operator_bit_and: return "&";

		case operator_logic_or: return "||";
		case operator_logic_and: return "&&";

		case operator_eq: return "==";
		case operator_noteq: return "!=";

		case operator_gt: return ">";
		case operator_ge: return ">=";
		case operator_lt: return "<";
		case operator_le: return "<=";

		case operator_lshift: return "<<";
		case operator_rshift: return ">>";
		case operator_excor: return "^";

		case operator_not: return "!";
		case operator_negative: return "-";
		case operator_childa: return "~";
	}
}

bool operator_arithmetic(operator_type self) {
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

bool operator_bit(operator_type self) {
	switch(self) {
		case operator_bit_or:
		case operator_bit_and:
			return true;
	}
	return false;
}

bool operator_logic(operator_type self) {
	switch(self) {
		case operator_logic_or:
		case operator_logic_and:
			return true;
	}
	return false;
}

bool operator_compare(operator_type self) {
	switch(self) {
		case operator_eq:
		case operator_noteq:
		case operator_gt:
		case operator_ge:
		case operator_lt:
		case operator_le:
			return true;
	}
	return false;
}

bool operator_shift(operator_type self) {
	switch(self) {
		case operator_lshift:
		case operator_rshift:
			return true;
	}
	return false;
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