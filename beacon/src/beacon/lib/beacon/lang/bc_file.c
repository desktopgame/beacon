#include "bc_file.h"
#include "../../../env/namespace.h"
#include "../../../env/type_impl.h"
#include "../../../util/string_buffer.h"
#include "../../../util/text.h"
#include "../../bc_library_impl.h"
#include "bc_string.h"

static void bc_file_nativeOpen(method* parent, frame* fr, enviroment* env);
static void bc_file_nativePut(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeGet(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeGetStdIn(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeGetStdOut(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeGetStdErr(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeGetClose(method* parent, frame* fr, enviroment* env);

void bc_file_init() {
	namespace_* unsafe = namespace_unsafe();
	type* fileType = class_new_preload("File");
	class_* fileClass = TYPE2CLASS(fileType);
	namespace_add_type(unsafe, fileType);
	class_define_native_method(fileClass, "nativeOpen", bc_file_nativeOpen);
	class_define_native_method(fileClass, "nativePut", bc_file_nativePut);
	class_define_native_method(fileClass, "nativeGet", bc_file_nativeGet);
	class_define_native_method(fileClass, "nativeStdIn", bc_file_nativeGetStdIn);
	class_define_native_method(fileClass, "nativeStdOut", bc_file_nativeGetStdOut);
	class_define_native_method(fileClass, "nativeStdErr", bc_file_nativeGetStdErr);
}

type* bc_file_type() {
	namespace_* unsafe = namespace_unsafe();
	return namespace_get_type(unsafe, "File");
}
//private
static void bc_file_nativeOpen(method* parent, frame* fr, enviroment* env) {
	object* fileObj = vector_at(fr->ref_stack, 1);
	object* modeObj = vector_at(fr->ref_stack, 2);
	string_buffer* fileStr = bc_string_raw(fileObj);
	string_buffer* modeStr = bc_string_raw(modeObj);
	text_printfln("%s : %s", fileStr->text, modeStr->text);
	int a = 0;
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