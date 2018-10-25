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
	namespace_* unsafe = GetUnsafeNamespace();
	type* systemType = NewPreloadClass(InternString("System"));
	class_* systemClass = TYPE2CLASS(systemType);
	AddTypeNamespace(unsafe, systemType);
	DefineNativeMethodClass(systemClass, "nativeExit", bc_system_nativeExit);
	DefineNativeMethodClass(systemClass, "nativeAbort", bc_system_nativeAbort);
	DefineNativeMethodClass(systemClass, "nativeExec", bc_system_nativeExec);
}

type* GetBCSystemType() {
	namespace_* unsafe = GetUnsafeNamespace();
	return FindTypeFromNamespace(unsafe, InternString("System"));
}

//private
static void bc_system_nativeExit(Method* parent, Frame* fr, Enviroment* env) {
	object* returnCodeObj = AtVector(fr->VariableTable, 1);
	int returnCode = OBJ2INT(returnCodeObj);
	exit(returnCode);
}

static void bc_system_nativeAbort(Method* parent, Frame* fr, Enviroment* env) {
	abort();
}

static void bc_system_nativeExec(Method* parent, Frame* fr, Enviroment* env) {
	object* cmd = AtVector(fr->VariableTable, 1);
	const char* str = GetRawBCString(cmd)->Text;
	int ret = system(str);
	PushVector(fr->ValueStack, GetIntObject(ret));
}