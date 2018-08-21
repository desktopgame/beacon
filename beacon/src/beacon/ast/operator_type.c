#include "operator_type.h"

void operator_fprintf(FILE* fp, operator_type self) {
	fprintf(fp, "%s", operator_tostring(self));
}

char* operator_tostring(operator_type self) {
	switch(self) {
		case operator_add_T: return "+";
		case operator_sub_T: return "-";
		case operator_mul_T: return "*";
		case operator_div_T: return "/";
		case operator_mod_T: return "%%";

		case operator_bit_or_T: return "|";
		case operator_bit_and_T: return "&";

		case operator_logic_or_T: return "||";
		case operator_logic_and_T: return "&&";

		case operator_eq_T: return "==";
		case operator_not_eq_T: return "!=";

		case operator_gt_T: return ">";
		case operator_ge_T: return ">=";
		case operator_lt_T: return "<";
		case operator_le_T: return "<=";

		case operator_lshift_T: return "<<";
		case operator_rshift_T: return ">>";
		case operator_excor_T: return "^";

		case operator_not_T: return "!";
		case operator_negative_T: return "-";
		case operator_childa_T: return "~";

		case operator_sub_script_get_T: return "[]";
		case operator_sub_script_set_T: return "[]=";
	}
}

bool operator_arithmetic(operator_type self) {
	switch(self) {
		case operator_add_T:
		case operator_sub_T:
		case operator_mul_T:
		case operator_div_T:
		case operator_mod_T:
			return true;
	}
	return false;
}

bool operator_bit(operator_type self) {
	switch(self) {
		case operator_bit_or_T:
		case operator_bit_and_T:
			return true;
	}
	return false;
}

bool operator_logic(operator_type self) {
	switch(self) {
		case operator_logic_or_T:
		case operator_logic_and_T:
			return true;
	}
	return false;
}

bool operator_compare(operator_type self) {
	switch(self) {
		case operator_eq_T:
		case operator_not_eq_T:
		case operator_gt_T:
		case operator_ge_T:
		case operator_lt_T:
		case operator_le_T:
			return true;
	}
	return false;
}

bool operator_shift(operator_type self) {
	switch(self) {
		case operator_lshift_T:
		case operator_rshift_T:
			return true;
	}
	return false;
}

bool operator_arg2(operator_type self) {
	switch(self) {
		case operator_add_T:
		case operator_sub_T:
		case operator_mul_T:
		case operator_div_T:
		case operator_mod_T:
		case operator_bit_or_T:
		case operator_bit_and_T:
		case operator_logic_or_T:
		case operator_logic_and_T:
		case operator_lshift_T:
		case operator_rshift_T:
		case operator_eq_T:
		case operator_not_eq_T:
		case operator_sub_script_get_T:
			return true;
	}
	return false;
}

bool operator_arg1(operator_type self) {
	return false;
}