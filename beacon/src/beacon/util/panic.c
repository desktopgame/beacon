#include "panic.h"
#include "stack.h"
#include "mem.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static jmpbuf_trace* malloc_trace(const char* filename, int lineno);
static void stack_flush(int kind, int kind2);
#define new_trace() malloc_trace(__FILE__, __LINE__)

stack* gPanicStack = NULL;

jmpbuf_trace* begin_panic() {
	if(gPanicStack == NULL) {
		gPanicStack = stack_new();
	}
	jmpbuf_trace* ret = new_trace();
	ret->kind = EXCEPTION_EMPTY;
	stack_push(gPanicStack, ret);
	return ret;
}

void panic(int kind) {
	stack_flush(EXCEPTION_GENERIC, kind);
	//キャッチされない例外
	if(stack_empty(gPanicStack)) {
		fprintf(stderr, "unhandled exception: %d\n", kind);
		exit(1);
		return;
	}
	jmpbuf_trace* E = NULL;
	while(!stack_empty(gPanicStack)) {
		E = stack_pop(gPanicStack);
		if(E->kind == EXCEPTION_EMPTY) {
			break;
		}
	}
	if(E->kind != EXCEPTION_EMPTY) {
		fprintf(stderr, "invalid try statement: %d\n", kind);
		exit(1);
		return;
	}
	longjmp(E->buf, kind);
}

void handle_panic(int kind) {
	jmpbuf_trace* ret = new_trace();
	ret->kind = kind;
	stack_push(gPanicStack, ret);
}

void end_panic() {
	assert(gPanicStack != NULL);
	stack_flush(EXCEPTION_EMPTY, EXCEPTION_EMPTY);
}

void finally() {
	if(stack_empty(gPanicStack)) {
		stack_delete(gPanicStack, stack_deleter_null);
		gPanicStack = NULL;
	}
}
//private
static jmpbuf_trace* malloc_trace(const char* filename, int lineno) {
	jmpbuf_trace* ret = (jmpbuf_trace*)mem_malloc(sizeof(jmpbuf_trace), filename, lineno);
	return ret;
}
static void stack_flush(int kind, int kind2) {
	while(!stack_empty(gPanicStack)) {
		jmpbuf_trace* e = stack_pop(gPanicStack);
		if(e->kind == kind ||
		   e->kind == kind2) {
			MEM_FREE(e);
			break;
		}
		MEM_FREE(e);
	}
}