#include "bc_file.h"
#include "../../../../env/namespace.h"
#include "../../../../env/type_impl.h"
#include "../../../../util/string_buffer.h"
#include "../../../../util/text.h"
#include "../../../bc_library_impl.h"
#include "../bc_string.h"
#include <assert.h>
#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

static void bc_file_nativeOpen(method* parent, frame* fr, enviroment* env);
static void bc_file_nativePut(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeGet(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeAvailable(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeGetStdIn(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeGetStdOut(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeGetStdErr(method* parent, frame* fr, enviroment* env);
static void bc_file_nativeClose(method* parent, frame* fr, enviroment* env);
static object* file_new(FILE* fp, bool std);

void bc_file_init() {
	namespace_* unsafe = namespace_unsafe();
	type* fileType = class_new_preload(InternString("File"));
	class_* fileClass = TYPE2CLASS(fileType);
	namespace_add_type(unsafe, fileType);
	class_define_native_method(fileClass, "nativeOpen", bc_file_nativeOpen);
	class_define_native_method(fileClass, "nativePut", bc_file_nativePut);
	class_define_native_method(fileClass, "nativeGet", bc_file_nativeGet);
	class_define_native_method(fileClass, "nativeAvailable", bc_file_nativeAvailable);
	class_define_native_method(fileClass, "nativeGetStdIn", bc_file_nativeGetStdIn);
	class_define_native_method(fileClass, "nativeGetStdOut", bc_file_nativeGetStdOut);
	class_define_native_method(fileClass, "nativeGetStdErr", bc_file_nativeGetStdErr);
	class_define_native_method(fileClass, "nativeClose", bc_file_nativeClose);
}

type* bc_file_type() {
	namespace_* unsafe = namespace_unsafe();
	return namespace_get_type(unsafe, InternString("File"));
}
//private
static void bc_file_nativeOpen(method* parent, frame* fr, enviroment* env) {
	object* fileObj = AtVector(fr->ref_stack, 1);
	object* modeObj = AtVector(fr->ref_stack, 2);
	string_buffer* fileStr = bc_string_raw(fileObj);
	string_buffer* modeStr = bc_string_raw(modeObj);
	//Printfln("%s : %s", fileStr->text, modeStr->text);

	FILE* fp = fopen(fileStr->text, modeStr->text);
	if(fp == NULL) {
		//ひらけなかった
		PushVector(fr->value_stack, object_get_null());
		return;
	}
	object* file = file_new(fp, false);
	PushVector(fr->value_stack, file);
}

static void bc_file_nativePut(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* ch = AtVector(fr->ref_stack, 1);
	FILE* fp = AtVector(self->native_slot_vec, 0);
	assert(fp != NULL);
	fputc(ch->u.char_, fp);
}

static void bc_file_nativeGet(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	FILE* fp = AtVector(self->native_slot_vec, 0);
	assert(fp != NULL);
	char ret = fgetc(fp);
	PushVector(fr->value_stack, object_char_new(ret));
}

static void bc_file_nativeAvailable(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	FILE* fp = AtVector(self->native_slot_vec, 0);
	assert(fp != NULL);
	PushVector(fr->value_stack, object_bool_get(!feof(fp)));
}

static void bc_file_nativeGetStdIn(method* parent, frame* fr, enviroment* env) {
	object* file = file_new(stdin, true);
	PushVector(fr->value_stack, file);
}

static void bc_file_nativeGetStdOut(method* parent, frame* fr, enviroment* env) {
	object* file = file_new(stdout, true);
	PushVector(fr->value_stack, file);
}

static void bc_file_nativeGetStdErr(method* parent, frame* fr, enviroment* env) {
	object* file = file_new(stderr, true);
	PushVector(fr->value_stack, file);
}

static void bc_file_nativeClose(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	FILE* fp = AtVector(self->native_slot_vec, 0);
	assert(fp != NULL);
	fclose(fp);
}

static object* file_new(FILE* fp, bool std) {
	object* file = object_ref_new();
	assert(file->paint != paint_onexit_T);
	type* fileType = bc_file_type();
	file->gtype = fileType->generic_self;
	file->vptr = TYPE2CLASS(fileType)->vt;
	AssignVector(file->native_slot_vec, 0, fp);
	return file;
}