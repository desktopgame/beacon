#include "sg_console.h"
#include "../../sg_library_impl.h"
#include "../../../env/type/class_impl.h"
#include <stdio.h>

//proto
static void sg_console_writeLine(method* parent, vm* vm, enviroment* env);
static void sg_console_write(method* parent, vm* vm, enviroment* env);

void sg_console_init() {
	namespace_* lang = namespace_lang();
	class_* cls = class_new("Console");
	namespace_add_type(lang, type_wrap_class(cls));
	class_define_native_method(cls, "writeLine", sg_console_writeLine);
	class_define_native_method(cls, "write", sg_console_write);
}

//private
static void sg_console_writeLine(method* parent, vm* vm, enviroment* env) {
	object* o = (object*)vector_pop(vm->value_stack);
	if (o->type == object_int) {
		printf("%d\n", o->u.int_);
	} else if (o->type == object_string) {
		printf("%s\n", o->u.string_);
	}
}

static void sg_console_write(method* parent, vm* vm, enviroment* env) {
	object* o = (object*)vector_pop(vm->value_stack);
	if (o->type == object_int) {
		printf("%d", o->u.int_);
	} else if (o->type == object_string) {
		printf("%s", o->u.string_);
	}
}