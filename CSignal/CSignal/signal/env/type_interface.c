#include "type_interface.h"
#include "../util/mem.h"
#include "type_impl.h"
#include <assert.h>

type * type_new() {
	type* ret = (type*)MEM_MALLOC(sizeof(type));
	ret->tag = type_class;
	ret->location = NULL;
	ret->absoluteIndex = -1;
	return ret;
}

char * type_name(type * self) {
	assert(self->tag == type_class);
	return self->u.class_->name;
}

void type_dump(type * self, int depth) {
	assert(self->tag == type_class);
	if (self->tag == type_class) {
		class_dump(self->u.class_, depth);
	}
}

void type_delete(type * self) {
}
