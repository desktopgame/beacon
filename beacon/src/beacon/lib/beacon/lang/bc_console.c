#include "bc_console.h"
#include "../../bc_library_impl.h"
#include "../../../util/text.h"
#include "bc_string.h"
#include <stdio.h>
#include "../../../env/generic_type.h"

//proto
static void bc_console_writeLine(method* parent, frame* fr, enviroment* env);
static void bc_console_write(method* parent, frame* fr, enviroment* env);
static void bc_console_readLine(method* parent, frame* fr, enviroment* env);
static void bc_console_read(method* parent, frame* fr, enviroment* env);

void bc_console_init() {
	namespace_* lang = namespace_lang();
	type* consoleType = class_new_preload(string_pool_intern("Console"));
	class_* consoleClass = TYPE2CLASS(consoleType);
	namespace_add_type(lang, consoleType);
	class_define_native_method(consoleClass, "writeLine", bc_console_writeLine);
	class_define_native_method(consoleClass, "write", bc_console_write);
	class_define_native_method(consoleClass, "readLine", bc_console_readLine);
	class_define_native_method(consoleClass, "read", bc_console_read);
}

type* bc_console_type() {
	namespace_* lang = namespace_lang();
	return namespace_get_type(lang, string_pool_intern("Console"));
}

//private
static void bc_console_writeLine(method* parent, frame* fr, enviroment* env) {
	object* o = vector_at(fr->ref_stack, 1);
	if (o->tag == object_int_T) {
		printf("%d\n", o->u.int_);
	} else if(o->tag == object_double_T) {
		printf("%f\n", o->u.double_);
	} else if (o->tag == object_string_T) {
		printf("%s\n", bc_string_raw(o)->text);
	} else if (o->tag == object_ref_T) {
		generic_type_print(o->gtype);
		printf("\n");
	} else if (o->tag == object_char_T) {
		printf("%c\n", o->u.char_);
	} else if (o->tag == object_bool_T) {
		printf("%s\n", o->u.bool_ ? "true" : "false");
	} else if(o->tag == object_null_T) {
		printf("null\n");
	}
}

static void bc_console_write(method* parent, frame* fr, enviroment* env) {
	object* o = vector_at(fr->ref_stack, 1);
	if (o->tag == object_int_T) {
		printf("%d", o->u.int_);
	}  else if (o->tag == object_double_T) {
		printf("%f", o->u.double_);
	} else if (o->tag == object_string_T) {
		printf("%s", bc_string_raw(o)->text);
	} else if (o->tag == object_ref_T) {
		generic_type_print(o->gtype);
		//printf("\n");
	} else if (o->tag == object_char_T) {
		printf("%c", o->u.char_);
	} else if (o->tag == object_bool_T) {
		printf("%s", o->u.bool_ ? "true" : "false");
	} else if(o->tag == object_null_T) {
		printf("null");
	}
}

static void bc_console_read(method* parent, frame* fr, enviroment* env) {
	char c = getchar();
	object* o = object_char_new(c);
	vector_push(fr->value_stack, o);
}

static void bc_console_readLine(method* parent, frame* fr, enviroment* env) {
	char* s = text_gets();
	object* o = object_string_new(s);
	vector_push(fr->value_stack, o);
}