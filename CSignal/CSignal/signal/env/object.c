#include "object.h"
#include "namespace.h"
#include <stdlib.h>
#include "vtable.h"
#include "../util/mem.h"
#include "type_interface.h"

//proto
static object* object_malloc(object_tag type);
static object* gObjectTrue = NULL;
static object* gObjectFalse = NULL;
static object* gObjectNull = NULL;


object * object_int_new(int i) {
	object* ret = object_malloc(object_int);
	ret->u.int_ = i;
	ret->type = CL_INT;
	ret->vptr = type_vtable(CL_INT);
	return ret;
}

object * object_double_new(double d) {
	object* ret = object_malloc(object_double);
	ret->u.double_ = d;
	ret->type = CL_DOUBLE;
	ret->vptr = type_vtable(CL_DOUBLE);
	return ret;
}

object * object_char_new(char c) {
	object* ret = object_malloc(object_char);
	ret->u.char_ = c;
	ret->type = CL_CHAR;
	ret->vptr = type_vtable(CL_CHAR);
	return ret;
}

object * object_string_new(const char * s) {
	object* ret = object_malloc(object_string);
	ret->u.string_ = s;
	ret->type = CL_STRING;
	ret->vptr = type_vtable(CL_STRING);
	return ret;
}

object * object_bool_new(bool b) {
	object* ret = object_malloc(object_bool);
	ret->u.bool_ = b;
	ret->type = CL_BOOL;
	ret->vptr = type_vtable(CL_BOOL);
	return ret;
}

object * object_ref_new() {
	object* ret= object_malloc(object_ref);
	ret->u.field_vec = vector_new();
	return ret;
}

object * object_bool_get(bool b) {
	return (b ? object_get_true() : object_get_false());
}

object * object_get_true() {
	if (gObjectTrue == NULL) {
		gObjectTrue = object_malloc(object_bool);
		gObjectTrue->u.bool_ = !false;
		gObjectTrue->type = CL_BOOL;
	}
	return gObjectTrue;
}

object * object_get_false() {
	if (gObjectFalse == NULL) {
		gObjectFalse = object_malloc(object_bool);
		gObjectFalse->u.bool_ = false;
		gObjectFalse->type = CL_BOOL;
	}
	return gObjectFalse;
}

object * object_get_null() {
	if (gObjectNull == NULL) {
		gObjectNull = object_malloc(object_null);
		gObjectNull->type = CL_NULL;
	}
	return gObjectNull;
}

void object_delete(object * self) {
	MEM_FREE(self);
}

//private
static object* object_malloc(object_tag type) {
	object* ret = (object*)MEM_MALLOC(sizeof(object));
	ret->type = NULL;
	ret->paint = paint_unmarked;
	ret->tag = type;
	ret->vptr = NULL;
	ret->nativeSlotVec = vector_new();
	return ret;
}