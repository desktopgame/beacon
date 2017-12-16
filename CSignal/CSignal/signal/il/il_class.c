#include "il_class.h"
#include <stdlib.h>
#include "../util/text.h"

il_class* il_class_new(const char* name) {
	il_class* ret = (il_class*)malloc(sizeof(il_class));
	ret->name = text_strdup(name);
	ret->super = NULL;
	return ret;
}