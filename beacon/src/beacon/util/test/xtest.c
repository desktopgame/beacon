#include "xtest.h"
#include "../mem.h"
#include "../text.h"
#include <setjmp.h>
#include <assert.h>

static xtest* gXTest = NULL;
static jmp_buf gXBuf;

xtest* xtest_new(const char* name, xtest_runner runner) {
	xtest* ret = (xtest*)MEM_MALLOC(sizeof(xtest));
	ret->name = text_strdup(name);
	ret->runner = runner;
	ret->log_vec = vector_new();
	return ret;
}

xlog* xlog_new(const char* filename, int lineno) {
	xlog* ret = (xlog*)MEM_MALLOC(sizeof(xlog));
	ret->filename = filename;
	ret->lineno = lineno;
	return ret;
}

bool xtest_run(xtest* self) {
	gXTest = self;
	bool thrown = false;
	if(setjmp(gXBuf) == 0) {
		self->runner();
	} else {
		thrown = true;
	}
	//ログを出力
	bool ret = self->log_vec->length == 0;
	const char* mark = ret ? "::" : "!!";
	text_printr(' ', 4);
	text_printf(mark);
	text_printf("%s", self->name);
	text_printf(mark);
	text_printf("\n");
	for(int i=0; i<self->log_vec->length; i++) {
		xlog* e = (xlog*)vector_at(self->log_vec, i);
		text_printr(' ', 8);
		text_printf("%s<%d>\n", e->filename, e->lineno);
	}
	return ret;
}

xtest* xtest_get() {
	return gXTest;
}

bool xtest_expect_true(xtest* self, bool condition, bool isThrow, const char* filename, int lineno) {
	if(condition) {
		return condition;
	}
	xlog* xl = xlog_new(filename, lineno);
	vector_push(self->log_vec, xl);
	if(isThrow) {
		longjmp(gXBuf, 1);
	}
	return condition;
}

void xlog_delete(xlog* self) {
	MEM_FREE(self);
}

void xtest_delete(xtest* self) {
	MEM_FREE(self->name);
	MEM_FREE(self);
}