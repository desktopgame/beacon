#include "sg_console.h"
#include "../../sg_library_impl.h"
#include <stdio.h>

//proto
static void sg_console_writeLine(method* parent, vm* vm, enviroment* env);
static void sg_console_write(method* parent, vm* vm, enviroment* env);

void sg_console_init() {
	namespace_* lang = namespace_lang();
	class_* cls = class_new("Console", class_type_class);
	namespace_add_class(lang, cls);
	class_define_native_method(cls, "writeLine", sg_console_writeLine);
	class_define_native_method(cls, "write", sg_console_write);
}

//private
static void sg_console_writeLine(method* parent, vm* vm, enviroment* env) {
	char* s = (char*)vector_pop(vm->value_stack);
	printf("%s\n", s);
}

static void sg_console_write(method* parent, vm* vm, enviroment* env) {
	char* s = (char*)vector_pop(vm->value_stack);
	printf("%s", s);
}