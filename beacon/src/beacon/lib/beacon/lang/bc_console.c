#include "bc_console.h"
#include "../../bc_library_impl.h"
#include "../../../util/text.h"
#include "bc_string.h"
#include <stdio.h>
#include "../../../env/generic_type.h"

//proto
static void bc_console_writeLine(Method* parent, Frame* fr, Enviroment* env);
static void bc_console_write(Method* parent, Frame* fr, Enviroment* env);
static void bc_console_readLine(Method* parent, Frame* fr, Enviroment* env);
static void bc_console_read(Method* parent, Frame* fr, Enviroment* env);

void InitBCConsole() {
	Namespace* lang = GetLangNamespace();
	type* consoleType = NewPreloadClass(InternString("Console"));
	class_* consoleClass = TYPE2CLASS(consoleType);
	AddTypeNamespace(lang, consoleType);
	DefineNativeMethodClass(consoleClass, "writeLine", bc_console_writeLine);
	DefineNativeMethodClass(consoleClass, "write", bc_console_write);
	DefineNativeMethodClass(consoleClass, "readLine", bc_console_readLine);
	DefineNativeMethodClass(consoleClass, "read", bc_console_read);
}

type* GetBCConsoleType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Console"));
}

//private
static void bc_console_writeLine(Method* parent, Frame* fr, Enviroment* env) {
	Object* o = AtVector(fr->VariableTable, 1);
	if (o->Tag == OBJECT_INT_T) {
		printf("%d\n", o->u.int_);
	} else if(o->Tag == OBJECT_DOUBLE_T) {
		printf("%f\n", o->u.double_);
	} else if (o->Tag == OBJECT_STRING_T) {
		printf("%s\n", GetRawBCString(o)->Text);
	} else if (o->Tag == OBJECT_REF_T) {
		PrintGenericType(o->GType);
		printf("\n");
	} else if (o->Tag == OBJECT_CHAR_T) {
		printf("%c\n", o->u.char_);
	} else if (o->Tag == OBJECT_BOOL_T) {
		printf("%s\n", o->u.bool_ ? "true" : "false");
	} else if(o->Tag == OBJECT_NULL_T) {
		printf("null\n");
	}
}

static void bc_console_write(Method* parent, Frame* fr, Enviroment* env) {
	Object* o = AtVector(fr->VariableTable, 1);
	if (o->Tag == OBJECT_INT_T) {
		printf("%d", o->u.int_);
	}  else if (o->Tag == OBJECT_DOUBLE_T) {
		printf("%f", o->u.double_);
	} else if (o->Tag == OBJECT_STRING_T) {
		printf("%s", GetRawBCString(o)->Text);
	} else if (o->Tag == OBJECT_REF_T) {
		PrintGenericType(o->GType);
		//printf("\n");
	} else if (o->Tag == OBJECT_CHAR_T) {
		printf("%c", o->u.char_);
	} else if (o->Tag == OBJECT_BOOL_T) {
		printf("%s", o->u.bool_ ? "true" : "false");
	} else if(o->Tag == OBJECT_NULL_T) {
		printf("null");
	}
}

static void bc_console_read(Method* parent, Frame* fr, Enviroment* env) {
	char c = getchar();
	Object* o = Object_char_new(c);
	PushVector(fr->ValueStack, o);
}

static void bc_console_readLine(Method* parent, Frame* fr, Enviroment* env) {
	char* s = ReadLine();
	Object* o = Object_string_new(s);
	PushVector(fr->ValueStack, o);
}