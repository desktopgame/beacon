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
static void bc_system_nativeExit(method* parent, frame* fr, enviroment* env);
static void bc_system_nativeAbort(method* parent, frame* fr, enviroment* env);
static void bc_system_nativeExec(method* parent, frame* fr, enviroment* env);

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
static void bc_system_nativeExit(method* parent, frame* fr, enviroment* env) {
	object* returnCodeObj = AtVector(fr->ref_stack, 1);
	int returnCode = OBJ2INT(returnCodeObj);
	exit(returnCode);
}

static void bc_system_nativeAbort(method* parent, frame* fr, enviroment* env) {
	abort();
}

static void bc_system_nativeExec(method* parent, frame* fr, enviroment* env) {
	object* cmd = AtVector(fr->ref_stack, 1);
	const char* str = GetRawBCString(cmd)->text;
	int ret = system(str);
	PushVector(fr->value_stack, GetIntObject(ret));
}