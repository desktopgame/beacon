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

int type_distance(type * a, type * b) {
	if (a == b) {
		return 0;
	}
	if (a->tag == type_class &&
		b->tag == type_class) {
		return class_distance(a->u.class_, b->u.class_);
	}
	return -1;
}

bool type_castable(type * self, type * other) {
	if (self->tag != other->tag) {
		return false;
	}
	if (self->tag == type_class) {
		return class_castable(self->u.class_, other->u.class_);
	}
	return false;
}

void type_delete(type * self) {
}
