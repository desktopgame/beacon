#include "sg_console.h"
#include "../../sg_library_impl.h"
#include "../../../util/text.h"
#include "sg_string.h"
#include <stdio.h>
#include "../../../env/generic_type.h"

//proto
static void sg_console_writeLine(method* parent, vm* vm, enviroment* env);
static void sg_console_write(method* parent, vm* vm, enviroment* env);
static void sg_console_readLine(method* parent, vm* vm, enviroment* env);
static void sg_console_read(method* parent, vm* vm, enviroment* env);

void sg_console_init() {
	namespace_* lang = namespace_lang();
	class_* cls = class_new_preload("Console");
	namespace_add_type(lang, type_wrap_class(cls));
	class_define_native_method(cls, "writeLine", sg_console_writeLine);
	class_define_native_method(cls, "write", sg_console_write);
	class_define_native_method(cls, "readLine", sg_console_readLine);
	class_define_native_method(cls, "read", sg_console_read);
}

//private
static void sg_console_writeLine(method* parent, vm* vm, enviroment* env) {
	object* o = (object*)vector_pop(vm->value_stack);
	if (o->tag == object_int) {
		text_printf("%d\n", o->u.int_);
	} else if(o->tag == object_double) {
		text_printf("%f\n", o->u.double_);
	} else if (o->tag == object_string) {
		text_printf("%s\n", sg_string_raw(o)->text);
	} else if (o->tag == object_ref) {
		generic_type_print(o->gtype);
		text_printf("\n");
	} else if (o->tag == object_char) {
		text_printf("%c\n", o->u.char_);
	} else if (o->tag == object_bool) {
		text_printf("%s\n", o->u.bool_ ? "true" : "false");
	}
}

static void sg_console_write(method* parent, vm* vm, enviroment* env) {
	object* o = (object*)vector_pop(vm->value_stack);
	if (o->tag == object_int) {
		text_printf("%d", o->u.int_);
	}  else if (o->tag == object_double) {
		text_printf("%f", o->u.double_);
	} else if (o->tag == object_string) {
		text_printf("%s", sg_string_raw(o)->text);
	} else if (o->tag == object_ref) {
		generic_type_print(o->gtype);
		//text_printf("\n");
	} else if (o->tag == object_char) {
		text_printf("%c", o->u.char_);
	} else if (o->tag == object_bool) {
		text_printf("%s", o->u.bool_ ? "true" : "false");
	}
}

static void sg_console_read(method* parent, vm* vm, enviroment* env) {
	char c = getchar();
	object* o = object_char_new(c);
	vector_push(vm->value_stack, o);
}

static void sg_console_readLine(method* parent, vm* vm, enviroment* env) {
	char* s = text_gets();
	object* o = object_string_new(s);
	vector_push(vm->value_stack, o);
}