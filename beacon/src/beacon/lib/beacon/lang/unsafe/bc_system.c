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
static void bc_system_nativeExit(Method* parent, Frame* fr, Enviroment* env);
static void bc_system_nativeAbort(Method* parent, Frame* fr, Enviroment* env);
static void bc_system_nativeExec(Method* parent, Frame* fr, Enviroment* env);

void InitBCSystem() {
	Namespace* unsafe = GetUnsafeNamespace();
	Type* systemType = NewPreloadClass(InternString("System"));
	Class* systemClass = TYPE2CLASS(systemType);
	AddTypeNamespace(unsafe, systemType);
	DefineNativeMethodClass(systemClass, "nativeExit", bc_system_nativeExit);
	DefineNativeMethodClass(systemClass, "nativeAbort", bc_system_nativeAbort);
	DefineNativeMethodClass(systemClass, "nativeExec", bc_system_nativeExec);
}

Type* GetBCSystemType() {
	Namespace* unsafe = GetUnsafeNamespace();
	return FindTypeFromNamespace(unsafe, InternString("System"));
}

//private
static void bc_system_nativeExit(Method* parent, Frame* fr, Enviroment* env) {
	Object* returnCodeObj = AtVector(fr->VariableTable, 1);
	int returnCode = ObjectToInt(returnCodeObj);
	exit(returnCode);
}

static void bc_system_nativeAbort(Method* parent, Frame* fr, Enviroment* env) {
	abort();
}

static void bc_system_nativeExec(Method* parent, Frame* fr, Enviroment* env) {
	Object* cmd = AtVector(fr->VariableTable, 1);
	const char* str = GetRawBCString(cmd)->Text;
	int ret = system(str);
	PushVector(fr->ValueStack, GetIntObject(ret));
}