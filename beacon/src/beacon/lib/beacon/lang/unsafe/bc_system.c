#include "bc_system.h"
#include "../../../../env/namespace.h"
#include "../../../../env/TYPE_IMPL.h"
#include "../../../../util/string_buffer.h"
#include "../../../../util/text.h"
#include "../../../bc_library_impl.h"
#include "../bc_string.h"
#include <assert.h>
/**
 * created by rbtools/rnative.rb
 * time: 2018-08-17
 */
static void bc_system_nativeExit(bc_Method* parent, Frame* fr, Enviroment* env);
static void bc_system_nativeAbort(bc_Method* parent, Frame* fr, Enviroment* env);
static void bc_system_nativeExec(bc_Method* parent, Frame* fr, Enviroment* env);

void InitSystem() {
	bc_Namespace* unsafe = bc_GetUnsafeNamespace();
	bc_Type* systemType = bc_NewPreloadClass(InternString("System"));
	bc_Class* systemClass = BC_TYPE2CLASS(systemType);
	bc_AddTypeNamespace(unsafe, systemType);
	bc_DefineNativeMethodClass(systemClass, "nativeExit", bc_system_nativeExit);
	bc_DefineNativeMethodClass(systemClass, "nativeAbort", bc_system_nativeAbort);
	bc_DefineNativeMethodClass(systemClass, "nativeExec", bc_system_nativeExec);
}

bc_Type* GetSystemType() {
	bc_Namespace* unsafe = bc_GetUnsafeNamespace();
	return bc_FindTypeFromNamespace(unsafe, InternString("System"));
}

//private
static void bc_system_nativeExit(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_Object* returnCodeObj = AtVector(fr->VariableTable, 1);
	int returnCode = bc_ObjectToInt(returnCodeObj);
	exit(returnCode);
}

static void bc_system_nativeAbort(bc_Method* parent, Frame* fr, Enviroment* env) {
	abort();
}

static void bc_system_nativeExec(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_Object* cmd = AtVector(fr->VariableTable, 1);
	const char* str = GetRawString(cmd)->Text;
	int ret = system(str);
	PushVector(fr->ValueStack, bc_GetIntObject(ret));
}