#include "script_context.h"
#include <stdlib.h>
#include <assert.h>
//proto
static script_context* script_context_check_init(void);

static script_context* gScriptContext = NULL;
static script_context* gScriptContextCurrent = NULL;

void script_context_open() {
	script_context_check_init();
}

script_context* script_context_new() {
	script_context* ret = (script_context*)malloc(sizeof(script_context));
	ret->prev = script_context_back();
	ret->next = NULL;
	return ret;
}

script_context * script_context_back() {
	script_context* g = script_context_check_init();
	if (g->next == NULL) {
		return g;
	}
	script_context* pointee = g;
	while (1) {
		if (pointee->next == NULL) {
			break;
		}
		pointee = pointee->next;
	}
	return pointee;
}

void script_context_set_current(script_context * self) {
	gScriptContextCurrent = self;
}

script_context * script_context_get_current() {
	return gScriptContextCurrent;
}

void script_context_delete(script_context * self) {
	assert(self != NULL);
	assert(self != gScriptContext);
	//前の要素がある
	if (self->prev != NULL) {
		//次の要素がある
		if (self->next != NULL) {
			self->prev->next = self->next;
		} else {
			self->prev->next = NULL;
		}
	}
	//次の要素がある
	if (self->next != NULL) {
		//前の要素がある
		if (self->prev != NULL) {
			self->next->prev = self->prev;
		} else {
			self->next->prev = NULL;
		}
	}
	free(self);
}

void script_context_close() {
	script_context* pointee = gScriptContext;
	while (1) {
		if (!pointee) {
			break;
		}
		script_context* temp = pointee;
		pointee = pointee->next;
		free(temp);
	}
	gScriptContext = NULL;
	gScriptContextCurrent = NULL;
}

//private
static script_context* script_context_check_init(void) {
	if (gScriptContext == NULL) {
		gScriptContext = (script_context*)malloc(sizeof(script_context));
		gScriptContext->prev = NULL;
		gScriptContext->next = NULL;
		gScriptContextCurrent = gScriptContext;
	}
	return gScriptContext;
}

