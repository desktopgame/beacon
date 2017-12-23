#include "class.h"
#include "../util/text.h"
#include <assert.h>
#include <stdlib.h>

class_ * class_new(const char * name, class_type type) {
	assert(name != NULL);
	class_* ret = (class_*)malloc(sizeof(class_));
	ret->name = text_strdup(name);
	ret->type = type;
	ret->location = NULL;
	ret->ref_count = 0;
	ret->super_class = NULL;
	return ret;
}

void class_delete(class_ * self) {
	assert(self->ref_count == 0);
	free(self->name);
	if (self->super_class != NULL) {
		self->super_class->ref_count--;
	}
	free(self);
}
