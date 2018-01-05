#include "object.h"
#include "namespace.h"
#include <stdlib.h>
#include "../util/mem.h"

//proto
static object* object_malloc(object_type type);

object * object_int_new(int i) {
	object* ret = object_malloc(object_int);
	ret->u.int_ = i;
	ret->classz = CL_INT;
	return ret;
}

object * object_double_new(double d) {
	object* ret = object_malloc(object_double);
	ret->u.double_ = d;
	ret->classz = CL_DOUBLE;
	return ret;
}

object * object_char_new(char c) {
	object* ret = object_malloc(object_char);
	ret->u.char_ = c;
	ret->classz = CL_CHAR;
	return ret;
}

object * object_string_new(const char * s) {
	object* ret = object_malloc(object_string);
	ret->u.string_ = s;
	ret->classz = CL_STRING;
	return ret;
}

object * object_bool_new(bool b) {
	object* ret = object_malloc(object_bool);
	ret->u.bool_ = b;
	ret->classz = CL_BOOL;
	return ret;
}

object * object_ref_new() {
	object* ret= object_malloc(object_ref);
	ret->u.field_vec = vector_new();
	return ret;
}

void object_delete(object * self) {
	MEM_FREE(self);
}

//private
static object* object_malloc(object_type type) {
	object* ret = (object*)MEM_MALLOC(sizeof(object));
	ret->classz = NULL;
	ret->paint = paint_unmarked;
	ret->type = type;
	return ret;
}