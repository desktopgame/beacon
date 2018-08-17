#include "bc_system.h"
#include "../../../../env/namespace.h"
#include "../../../../env/type_impl.h"
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

void bc_system_init() {
	namespace_* unsafe = namespace_unsafe();
	type* systemType = class_new_preload(string_pool_intern("System"));
	class_* systemClass = TYPE2CLASS(systemType);
	namespace_add_type(unsafe, systemType);
	class_define_native_method(systemClass, "nativeExit", bc_system_nativeExit);
	class_define_native_method(systemClass, "nativeAbort", bc_system_nativeAbort);
	class_define_native_method(systemClass, "nativeExec", bc_system_nativeExec);
}

type* bc_system_type() {
	namespace_* unsafe = namespace_unsafe();
	return namespace_get_type(unsafe, string_pool_intern("System"));
}

//private
static void bc_system_nativeExit(method* parent, frame* fr, enviroment* env) {
	object* returnCodeObj = vector_at(fr->ref_stack, 1);
	int returnCode = OBJ2INT(returnCodeObj);
	exit(returnCode);
}

static void bc_system_nativeAbort(method* parent, frame* fr, enviroment* env) {
	abort();
}

static void bc_system_nativeExec(method* parent, frame* fr, enviroment* env) {
	object* cmd = vector_at(fr->ref_stack, 1);
	const char* str = bc_string_raw(cmd)->text;
	int ret = system(str);
	vector_push(fr->value_stack, object_int_get(ret));
}