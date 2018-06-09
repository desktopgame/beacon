#include "bc_file.h"
#include "../../../env/namespace.h"
#include "../../../env/type_impl.h"

static void bc_file_nativeOpen(method* parent, frame* fr, enviroment* env);
static void bc_file_nativePut(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeGet(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeGetStdIn(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeGetStdOut(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeGetStdErr(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeGetClose(method* parent, frame* fr, enviroment* env);

void bc_file_init() {
	namespace_* unsafe = namespace_unsafe();
	type* arrayType = class_new_preload("File");
	class_* arrayClass = TYPE2CLASS(arrayType);
	namespace_add_type(unsafe, arrayType);
	class_define_native_method(arrayClass, "nativeOpen", bc_file_nativeOpen);
	class_define_native_method(arrayClass, "nativePut", bc_file_nativePut);
	class_define_native_method(arrayClass, "nativeGet", bc_file_nativeGet);
	class_define_native_method(arrayClass, "nativeStdIn", bc_file_nativeGetStdIn);
	class_define_native_method(arrayClass, "nativeStdOut", bc_file_nativeGetStdOut);
	class_define_native_method(arrayClass, "nativeStdErr", bc_file_nativeGetStdErr);
}

type* bc_file_type() {
	namespace_* unsafe = namespace_unsafe();
	return namespace_get_type(unsafe, "File");
}
//private
static void bc_file_nativeOpen(method* parent, frame* fr, enviroment* env) {
}

static void bc_file_nativePut(method* parent, frame* fr, enviroment* env) {
}

static void bc_file_nativeGet(method* parent, frame* fr, enviroment* env) {
}

static void bc_file_nativeGetStdIn(method* parent, frame* fr, enviroment* env) {
}

static void bc_file_nativeGetStdOut(method* parent, frame* fr, enviroment* env) {
}

static void bc_file_nativeGetStdErr(method* parent, frame* fr, enviroment* env) {
}

static void bc_file_nativeClose(method* parent, frame* fr, enviroment* env) {
}