#include "xtest.h"
#include "../mem.h"
#include "../text.h"
#include <setjmp.h>
#include <assert.h>
#include <stdio.h>

static xtest* gXTest = NULL;
static jmp_buf gXBuf;

//proto
static void xtest_xlog_delete(vector_item item);

xtest* xtest_new(const char* name, xtest_runner runner) {
	xtest* ret = (xtest*)MEM_MALLOC(sizeof(xtest));
	ret->name = text_strdup(name);
	ret->runner = runner;
	ret->log_vec = vector_new();
	ret->out = string_buffer_new();
	ret->error = false;
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
	bool ret = !self->error;
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
	//事前に出力されたバッファを表示
	bool withIndent = true;
	for(int i=0; i<self->out->length; i++) {
		char ch = self->out->text[i];
		if(withIndent) {
			text_printr(' ', 8);
			withIndent = false;
		}
		text_printf("%c", ch);
		if(ch == '\n') {
			withIndent = true;
		}
	}
	fflush(stdout);
	return ret;
}

void xtest_printf(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	xtest_vprintf(fmt, ap);
	va_end(ap);
}

void xtest_vprintf(const char* fmt, va_list ap) {
	xtest* cur = xtest_get();
	assert(cur != NULL);
	string_buffer_vappendf(cur->out, fmt, ap);
}

xtest* xtest_get() {
	return gXTest;
}

bool xtest_expect_true(xtest* self, bool condition, bool isRecord, bool isThrow, const char* filename, int lineno, const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	bool ret = xtest_expect_vtrue(self, condition, isRecord, isThrow, filename, lineno, fmt, ap);
	va_end(ap);
	return ret;
}

bool xtest_expect_vtrue(xtest* self, bool condition, bool isRecord, bool isThrow, const char* filename, int lineno, const char* fmt, va_list ap) {
	if(condition) {
		return condition;
	}
	if(isRecord) {
		xlog* xl = xlog_new(filename, lineno);
		vector_push(self->log_vec, xl);
	}
	if(fmt != NULL) {
		xtest_vprintf(fmt, ap);
	}
	if(isThrow) {
		self->error = true;
		longjmp(gXBuf, 1);
	}
	return condition;
}

void xtest_request_true(bool condition, const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	xtest_request_vtrue(condition, fmt, ap);
	va_end(ap);
}

void xtest_request_vtrue(bool condition, const char* fmt, va_list ap) {
	xtest_expect_vtrue(xtest_get(), condition, false, false, "", -1, fmt, ap);
}

void xtest_must_true(bool condition, const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	xtest_must_vtrue(condition, fmt, ap);
	va_end(ap);
}

void xtest_must_vtrue(bool condition, const char* fmt, va_list ap) {
	xtest_expect_vtrue(xtest_get(), condition, false, true, "", -1, fmt, ap);
}

void xlog_delete(xlog* self) {
	MEM_FREE(self);
}

void xtest_delete(xtest* self) {
	string_buffer_delete(self->out);
	vector_delete(self->log_vec, xtest_xlog_delete);
	MEM_FREE(self->name);
	MEM_FREE(self);
}
//private
static void xtest_xlog_delete(vector_item item) {
	xlog* e = (xlog*)item;
	xlog_delete(e);
}