#include "il_print_layout.h"
#include "../util/text.h"
#include <assert.h>

#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

static int gLineNo = -1;
static bool gHideLineNo = false;

bool bc_IsLineOfAlreadyILPrint(int lineno) {
	if (gHideLineNo) {
		return true;
	}
	if (gLineNo == lineno) {
		return true;
	}
	gLineNo = lineno;
	return false;
}

void bc_FormatILPrintLayout(int lineno) {
	if (gHideLineNo) {
		return;
	}
	if (!bc_IsLineOfAlreadyILPrint(lineno)) {
		printf("<%d> ", lineno);
	} else {
#define LEN 100
		char buff[LEN];
		int res = sprintf(buff, LEN, "<%d> ", lineno);
		assert(res != -1);
		for (int i = 0; i < strlen(buff); i++) {
			printf(" ");
		}
#undef LEN
	}
}

void bc_HideILPrintLayout(bool is_hide) {
	gHideLineNo = is_hide;
}
