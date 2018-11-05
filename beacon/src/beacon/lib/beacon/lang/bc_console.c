#include "bc_console.h"
#include "../../bc_library_interface.h"
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
	Type* consoleType = NewPreloadClass(InternString("Console"));
	Class* consoleClass = TYPE2CLASS(consoleType);
	AddTypeNamespace(lang, consoleType);
	DefineNativeMethodClass(consoleClass, "writeLine", bc_console_writeLine);
	DefineNativeMethodClass(consoleClass, "write", bc_console_write);
	DefineNativeMethodClass(consoleClass, "readLine", bc_console_readLine);
	DefineNativeMethodClass(consoleClass, "read", bc_console_read);
}

Type* GetBCConsoleType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Console"));
}

//private
static void bc_console_writeLine(Method* parent, Frame* fr, Enviroment* env) {
	Object* o = AtVector(fr->VariableTable, 1);
	if (o->Tag == OBJECT_INT_T) {
		printf("%d\n", OBJ2INT(o));
	} else if(o->Tag == OBJECT_DOUBLE_T) {
		printf("%f\n", OBJ2DOUBLE(o));
	} else if (o->Tag == OBJECT_STRING_T) {
		printf("%s\n", GetRawBCString(o)->Text);
	} else if (o->Tag == OBJECT_REF_T) {
		PrintGenericType(o->GType);
		printf("\n");
	} else if (o->Tag == OBJECT_CHAR_T) {
		printf("%c\n", OBJ2CHAR(o));
	} else if (o->Tag == OBJECT_BOOL_T) {
		printf("%s\n", OBJ2BOOL(o) ? "true" : "false");
	} else if(o->Tag == OBJECT_NULL_T) {
		printf("null\n");
	}
}

static void bc_console_write(Method* parent, Frame* fr, Enviroment* env) {
	Object* o = AtVector(fr->VariableTable, 1);
	if (o->Tag == OBJECT_INT_T) {
		printf("%d", OBJ2INT(o));
	}  else if (o->Tag == OBJECT_DOUBLE_T) {
		printf("%f", OBJ2DOUBLE(o));
	} else if (o->Tag == OBJECT_STRING_T) {
		printf("%s", GetRawBCString(o)->Text);
	} else if (o->Tag == OBJECT_REF_T) {
		PrintGenericType(o->GType);
		//printf("\n");
	} else if (o->Tag == OBJECT_CHAR_T) {
		printf("%c", OBJ2CHAR(o));
	} else if (o->Tag == OBJECT_BOOL_T) {
		printf("%s", OBJ2BOOL(o) ? "true" : "false");
	} else if(o->Tag == OBJECT_NULL_T) {
		printf("null");
	}
}

static void bc_console_read(Method* parent, Frame* fr, Enviroment* env) {
	char c = getchar();
	Object* o = (Object*)NewChar(c);
	PushVector(fr->ValueStack, o);
}

static void bc_console_readLine(Method* parent, Frame* fr, Enviroment* env) {
	char* s = ReadLine();
	Object* o = (Object*)NewString(s);
	PushVector(fr->ValueStack, o);
}