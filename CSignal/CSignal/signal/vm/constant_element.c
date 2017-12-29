#include "constant_element.h"
#include <stdlib.h>
#include "../util/text.h"

//proto
constant_element* constant_element_malloc(constant_type type);

constant_element * constant_int_new(int i) {
	constant_element* ret = constant_element_malloc(constant_int);
	ret->u.int_ = i;
	return ret;
}

constant_element * constant_double_new(double d) {
	constant_element* ret = constant_element_malloc(constant_double);
	ret->u.double_ = d;
	return ret;
}

constant_element * constant_char_new(char c) {
	constant_element* ret = constant_element_malloc(constant_char);
	ret->u.char_ = c;
	return ret;
}

constant_element * constant_string_new(const char * s) {
	constant_element* ret = constant_element_malloc(constant_string);
	ret->u.string_ = text_strdup(s);
	return ret;
}

void constant_element_delete(constant_element * self) {
	if (self->type == constant_string) {
		free(self->u.string_);
	}
	free(self);
}

//private
constant_element* constant_element_malloc(constant_type type) {
	constant_element* ret = (constant_element*)malloc(sizeof(constant_element));
	ret->type = type;
	return ret;
}