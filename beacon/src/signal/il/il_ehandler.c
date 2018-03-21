#include "il_ehandler.h"
#include "../util/mem.h"
#include "../util/text.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

il_ehandler * il_ehandler_new() {
	il_ehandler* ret = (il_ehandler*)MEM_MALLOC(sizeof(il_ehandler));
	ret->errorCount = 0;
	ret->message_vec = vector_new();
	return ret;
}

void il_ehandler_throw(il_ehandler* self, const char * src, ...) {
	assert(src != NULL);
	self->errorCount++;
	va_list ap;
	va_start(ap, src);
	//エラーメッセージをフォーマットして追加
	char buff[256];
	int res = text_sprintf(buff, 256, src, ap);
	assert(res != -1);
	vector_push(self->message_vec, text_strdup(buff));

	va_end(ap);
}

void il_ehandler_disp(il_ehandler * self, int depth) {
	for (int i = 0; i < self->message_vec->length; i++) {
		char* s = (char*)vector_at(self->message_vec, i);
		text_putindent(depth);
		text_printf("%s", s);
		text_putline();
	}
}

void il_ehandler_delete(il_ehandler * self) {
	vector_delete(self->message_vec, vector_deleter_free);
	MEM_FREE(self);
}
