#include "script_context.h"
#include "../util/logger.h"
#include <stdlib.h>
#include <assert.h>
//proto
static script_context* script_context_check_init(void);
static script_context* script_context_malloc(void);
static script_context* script_context_free(script_context* self);

static script_context* gScriptContext = NULL;
static script_context* gScriptContextCurrent = NULL;

void script_context_open() {
	script_context_check_init();
	INFO("script-context open");
}

script_context* script_context_new() {
	script_context* ret = script_context_malloc();
	ret->prev = script_context_back();
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
	script_context_free(self);
}

void script_context_close() {
	script_context* pointee = gScriptContext;
	while (1) {
		if (!pointee) {
			break;
		}
		script_context* temp = pointee;
		pointee = pointee->next;
		script_context_free(temp);
		//free(temp);
	}
	gScriptContext = NULL;
	gScriptContextCurrent = NULL;
	INFO("script-context close");
}

//private
static script_context* script_context_check_init(void) {
	if (gScriptContext == NULL) {
		gScriptContext = script_context_malloc();
		gScriptContextCurrent = gScriptContext;
	}
	return gScriptContext;
}

static script_context* script_context_malloc(void) {
	script_context* ret = (script_context*)malloc(sizeof(script_context));
	ret->parserStack = NULL;
	ret->prev = NULL;
	ret->next = NULL;
	return ret;
}

static script_context* script_context_free(script_context* self) {
	free(self);
}