#include "bc_console.h"
#include "../../bc_library_interface.h"
#include "../../bc_library_impl.h"
#include "../../../util/text.h"
#include "bc_string.h"
#include <stdio.h>
#include "../../../env/generic_type.h"

//proto
static void bc_console_writeLine(bc_Method* parent, Frame* fr, Enviroment* env);
static void bc_console_write(bc_Method* parent, Frame* fr, Enviroment* env);
static void bc_console_readLine(bc_Method* parent, Frame* fr, Enviroment* env);
static void bc_console_read(bc_Method* parent, Frame* fr, Enviroment* env);

void InitConsole() {
	bc_Namespace* lang = bc_GetLangNamespace();
	bc_Type* consoleType = bc_NewPreloadClass(InternString("Console"));
	bc_Class* consoleClass = BC_TYPE2CLASS(consoleType);
	bc_AddTypeNamespace(lang, consoleType);
	bc_DefineNativeMethodClass(consoleClass, "writeLine", bc_console_writeLine);
	bc_DefineNativeMethodClass(consoleClass, "write", bc_console_write);
	bc_DefineNativeMethodClass(consoleClass, "readLine", bc_console_readLine);
	bc_DefineNativeMethodClass(consoleClass, "read", bc_console_read);
}

bc_Type* GetConsoleType() {
	bc_Namespace* lang = bc_GetLangNamespace();
	return bc_FindTypeFromNamespace(lang, InternString("Console"));
}

//private
static void bc_console_writeLine(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_console_write(parent, fr, env);
	printf("\n");
}

static void bc_console_write(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_Object* o = AtVector(fr->VariableTable, 1);
	if (bc_IsIntValue(o)) {
		printf("%d", bc_ObjectToInt(o));
	}  else if (bc_IsDoubleValue(o)) {
		printf("%f", bc_ObjectToDouble(o));
	} else if (bc_IsStringValue(o)) {
		printf("%s", GetRawString(o)->Text);
	} else if (bc_IsCharValue(o)) {
		printf("%c", bc_ObjectToChar(o));
	} else if (bc_IsBoolValue(o)) {
		printf("%s", bc_ObjectToBool(o) ? "true" : "false");
	} else if(bc_IsNullValue(o)) {
		printf("null");
	} else {
		bc_PrintGenericType(o->GType);
	}
}

static void bc_console_read(bc_Method* parent, Frame* fr, Enviroment* env) {
	char c = getchar();
	bc_Object* o = (bc_Object*)NewChar(c);
	PushVector(fr->ValueStack, o);
}

static void bc_console_readLine(bc_Method* parent, Frame* fr, Enviroment* env) {
	char* s = bc_ReadLine();
	bc_Object* o = (bc_Object*)NewString(s);
	PushVector(fr->ValueStack, o);
}