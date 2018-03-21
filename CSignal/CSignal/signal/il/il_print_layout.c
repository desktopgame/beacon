#include "il_print_layout.h"
#include "../util/text.h"
#include <assert.h>

static int gLineNo = -1;
static bool gHideLineNo = false;

bool il_print_layout_lineno(int lineno) {
	if (gHideLineNo) {
		return true;
	}
	if (gLineNo == lineno) {
		return true;
	}
	gLineNo = lineno;
	return false;
}

void il_print_layout_form(int lineno) {
	if (gHideLineNo) {
		return;
	}
	if (!il_print_layout_lineno(lineno)) {
		text_printf("<%d> ", lineno);
	} else {
#define LEN 100
		char buff[LEN];
		int res = text_sprintf(buff, LEN, "<%d> ", lineno);
		assert(res != -1);
		for (int i = 0; i < strlen(buff); i++) {
			text_printf(" ");
		}
#undef LEN
	}
}

void il_print_layout_hide(bool is_hide) {
	gHideLineNo = is_hide;
}
