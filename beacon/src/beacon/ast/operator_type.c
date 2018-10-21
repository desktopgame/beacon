#include "operator_type.h"

void FprintfOperator(FILE* fp, OperatorType self) {
	fprintf(fp, "%s", OperatorToString(self));
}

char* OperatorToString(OperatorType self) {
	switch(self) {
		case OPERATOR_ADD_T: return "+";
		case OPERATOR_SUB_T: return "-";
		case OPERATOR_MUL_T: return "*";
		case OPERATOR_DIV_T: return "/";
		case OPERATOR_MOD_T: return "%%";

		case OPERATOR_BIT_OR_T: return "|";
		case OPERATOR_BIT_AND_T: return "&";

		case OPERATOR_LOGIC_OR_T: return "||";
		case OPERATOR_LOGIC_AND_T: return "&&";

		case OPERATOR_EQ_T: return "==";
		case OPERATOR_NOT_EQ_T: return "!=";

		case OPERATOR_GT_T: return ">";
		case OPERATOR_GE_T: return ">=";
		case OPERATOR_LT_T: return "<";
		case OPERATOR_LE_T: return "<=";

		case OPERATOR_LSHIFT_T: return "<<";
		case OPERATOR_RSHIFT_T: return ">>";
		case OPERATOR_EXCOR_T: return "^";

		case OPERATOR_NOT_T: return "!";
		case OPERATOR_NEGATIVE_T: return "-";
		case OPERATOR_CHILDA_T: return "~";

		case OPERATOR_SUB_SCRIPT_GET_T: return "[]";
		case OPERATOR_SUB_SCRIPT_SET_T: return "[]=";
	}
}

bool IsArithmeticOperator(OperatorType self) {
	switch(self) {
		case OPERATOR_ADD_T:
		case OPERATOR_SUB_T:
		case OPERATOR_MUL_T:
		case OPERATOR_DIV_T:
		case OPERATOR_MOD_T:
			return true;
	}
	return false;
}

bool IsBitOperator(OperatorType self) {
	switch(self) {
		case OPERATOR_BIT_OR_T:
		case OPERATOR_BIT_AND_T:
			return true;
	}
	return false;
}

bool IsLogicOperator(OperatorType self) {
	switch(self) {
		case OPERATOR_LOGIC_OR_T:
		case OPERATOR_LOGIC_AND_T:
			return true;
	}
	return false;
}

bool IsCompareOperator(OperatorType self) {
	switch(self) {
		case OPERATOR_EQ_T:
		case OPERATOR_NOT_EQ_T:
		case OPERATOR_GT_T:
		case OPERATOR_GE_T:
		case OPERATOR_LT_T:
		case OPERATOR_LE_T:
			return true;
	}
	return false;
}

bool IsShiftOperator(OperatorType self) {
	switch(self) {
		case OPERATOR_LSHIFT_T:
		case OPERATOR_RSHIFT_T:
			return true;
	}
	return false;
}

bool Is2ArgOperator(OperatorType self) {
	switch(self) {
		case OPERATOR_ADD_T:
		case OPERATOR_SUB_T:
		case OPERATOR_MUL_T:
		case OPERATOR_DIV_T:
		case OPERATOR_MOD_T:
		case OPERATOR_BIT_OR_T:
		case OPERATOR_BIT_AND_T:
		case OPERATOR_LOGIC_OR_T:
		case OPERATOR_LOGIC_AND_T:
		case OPERATOR_LSHIFT_T:
		case OPERATOR_RSHIFT_T:
		case OPERATOR_EQ_T:
		case OPERATOR_NOT_EQ_T:
		case OPERATOR_SUB_SCRIPT_GET_T:
			return true;
	}
	return false;
}

bool Is1ArgOperator(OperatorType self) {
	return false;
}