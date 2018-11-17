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

void InitConsole() {
	Namespace* lang = GetLangNamespace();
	Type* consoleType = NewPreloadClass(InternString("Console"));
	Class* consoleClass = TYPE2CLASS(consoleType);
	AddTypeNamespace(lang, consoleType);
	DefineNativeMethodClass(consoleClass, "writeLine", bc_console_writeLine);
	DefineNativeMethodClass(consoleClass, "write", bc_console_write);
	DefineNativeMethodClass(consoleClass, "readLine", bc_console_readLine);
	DefineNativeMethodClass(consoleClass, "read", bc_console_read);
}

Type* GetConsoleType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Console"));
}

//private
static void bc_console_writeLine(Method* parent, Frame* fr, Enviroment* env) {
	bc_console_write(parent, fr, env);
	printf("\n");
}

static void bc_console_write(Method* parent, Frame* fr, Enviroment* env) {
	Object* o = AtVector(fr->VariableTable, 1);
	if (IsIntValue(o)) {
		printf("%d", ObjectToInt(o));
	}  else if (IsDoubleValue(o)) {
		printf("%f", ObjectToDouble(o));
	} else if (IsStringValue(o)) {
		printf("%s", GetRawString(o)->Text);
	} else if (IsCharValue(o)) {
		printf("%c", ObjectToChar(o));
	} else if (IsBoolValue(o)) {
		printf("%s", ObjectToBool(o) ? "true" : "false");
	} else if(IsNullValue(o)) {
		printf("null");
	} else {
		PrintGenericType(o->GType);
	}
}

static void bc_console_read(Method* parent, Frame* fr, Enviroment* env) {
	char c = getchar();
	Object* o = (Object*)NewChar(c);
	PushVector(fr->ValueStack, o);
}

static void bc_console_readLine(Method* parent, Frame* fr, Enviroment* env) {
	char* s = bc_ReadLine();
	Object* o = (Object*)NewString(s);
	PushVector(fr->ValueStack, o);
}