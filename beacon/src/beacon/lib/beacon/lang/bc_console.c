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
	namespace_* lang = GetLangNamespace();
	type* consoleType = NewPreloadClass(InternString("Console"));
	class_* consoleClass = TYPE2CLASS(consoleType);
	AddTypeNamespace(lang, consoleType);
	DefineNativeMethodClass(consoleClass, "writeLine", bc_console_writeLine);
	DefineNativeMethodClass(consoleClass, "write", bc_console_write);
	DefineNativeMethodClass(consoleClass, "readLine", bc_console_readLine);
	DefineNativeMethodClass(consoleClass, "read", bc_console_read);
}

type* bc_console_type() {
	namespace_* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Console"));
}

//private
static void bc_console_writeLine(method* parent, frame* fr, enviroment* env) {
	object* o = AtVector(fr->ref_stack, 1);
	if (o->tag == OBJECT_INT_T) {
		printf("%d\n", o->u.int_);
	} else if(o->tag == OBJECT_DOUBLE_T) {
		printf("%f\n", o->u.double_);
	} else if (o->tag == OBJECT_STRING_T) {
		printf("%s\n", bc_string_raw(o)->text);
	} else if (o->tag == OBJECT_REF_T) {
		PrintGenericType(o->gtype);
		printf("\n");
	} else if (o->tag == OBJECT_CHAR_T) {
		printf("%c\n", o->u.char_);
	} else if (o->tag == OBJECT_BOOL_T) {
		printf("%s\n", o->u.bool_ ? "true" : "false");
	} else if(o->tag == OBJECT_NULL_T) {
		printf("null\n");
	}
}

static void bc_console_write(method* parent, frame* fr, enviroment* env) {
	object* o = AtVector(fr->ref_stack, 1);
	if (o->tag == OBJECT_INT_T) {
		printf("%d", o->u.int_);
	}  else if (o->tag == OBJECT_DOUBLE_T) {
		printf("%f", o->u.double_);
	} else if (o->tag == OBJECT_STRING_T) {
		printf("%s", bc_string_raw(o)->text);
	} else if (o->tag == OBJECT_REF_T) {
		PrintGenericType(o->gtype);
		//printf("\n");
	} else if (o->tag == OBJECT_CHAR_T) {
		printf("%c", o->u.char_);
	} else if (o->tag == OBJECT_BOOL_T) {
		printf("%s", o->u.bool_ ? "true" : "false");
	} else if(o->tag == OBJECT_NULL_T) {
		printf("null");
	}
}

static void bc_console_read(method* parent, frame* fr, enviroment* env) {
	char c = getchar();
	object* o = object_char_new(c);
	PushVector(fr->value_stack, o);
}

static void bc_console_readLine(method* parent, frame* fr, enviroment* env) {
	char* s = ReadLine();
	object* o = object_string_new(s);
	PushVector(fr->value_stack, o);
}