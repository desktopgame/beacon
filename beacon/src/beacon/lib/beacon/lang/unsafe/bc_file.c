#include "bc_file.h"
#include "../../../../env/namespace.h"
#include "../../../../env/TYPE_IMPL.h"
#include "../../../../util/string_buffer.h"
#include "../../../../util/text.h"
#include "../../../bc_library_impl.h"
#include "../bc_string.h"
#include <assert.h>
#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

static void bc_file_nativeOpen(method* parent, Frame* fr, Enviroment* env);
static void bc_file_nativePut(method* parent, Frame* fr, Enviroment* env);
static void bc_file_nativeGet(method* parent, Frame* fr, Enviroment* env);
static void bc_file_nativeAvailable(method* parent, Frame* fr, Enviroment* env);
static void bc_file_nativeGetStdIn(method* parent, Frame* fr, Enviroment* env);
static void bc_file_nativeGetStdOut(method* parent, Frame* fr, Enviroment* env);
static void bc_file_nativeGetStdErr(method* parent, Frame* fr, Enviroment* env);
static void bc_file_nativeClose(method* parent, Frame* fr, Enviroment* env);
static object* file_new(FILE* fp, bool std);

void InitBCFile() {
	namespace_* unsafe = GetUnsafeNamespace();
	type* fileType = NewPreloadClass(InternString("File"));
	class_* fileClass = TYPE2CLASS(fileType);
	AddTypeNamespace(unsafe, fileType);
	DefineNativeMethodClass(fileClass, "nativeOpen", bc_file_nativeOpen);
	DefineNativeMethodClass(fileClass, "nativePut", bc_file_nativePut);
	DefineNativeMethodClass(fileClass, "nativeGet", bc_file_nativeGet);
	DefineNativeMethodClass(fileClass, "nativeAvailable", bc_file_nativeAvailable);
	DefineNativeMethodClass(fileClass, "nativeGetStdIn", bc_file_nativeGetStdIn);
	DefineNativeMethodClass(fileClass, "nativeGetStdOut", bc_file_nativeGetStdOut);
	DefineNativeMethodClass(fileClass, "nativeGetStdErr", bc_file_nativeGetStdErr);
	DefineNativeMethodClass(fileClass, "nativeClose", bc_file_nativeClose);
}

type* GetBCFileType() {
	namespace_* unsafe = GetUnsafeNamespace();
	return FindTypeFromNamespace(unsafe, InternString("File"));
}
//private
static void bc_file_nativeOpen(method* parent, Frame* fr, Enviroment* env) {
	object* fileObj = AtVector(fr->VariableTable, 1);
	object* modeObj = AtVector(fr->VariableTable, 2);
	Buffer* fileStr = GetRawBCString(fileObj);
	Buffer* modeStr = GetRawBCString(modeObj);
	//Printfln("%s : %s", fileStr->text, modeStr->text);

	FILE* fp = fopen(fileStr->Text, modeStr->Text);
	if(fp == NULL) {
		//ひらけなかった
		PushVector(fr->ValueStack, GetNullObject());
		return;
	}
	object* file = file_new(fp, false);
	PushVector(fr->ValueStack, file);
}

static void bc_file_nativePut(method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* ch = AtVector(fr->VariableTable, 1);
	FILE* fp = AtVector(self->native_slot_vec, 0);
	assert(fp != NULL);
	fputc(ch->u.char_, fp);
}

static void bc_file_nativeGet(method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	FILE* fp = AtVector(self->native_slot_vec, 0);
	assert(fp != NULL);
	char ret = fgetc(fp);
	PushVector(fr->ValueStack, object_char_new(ret));
}

static void bc_file_nativeAvailable(method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	FILE* fp = AtVector(self->native_slot_vec, 0);
	assert(fp != NULL);
	PushVector(fr->ValueStack, GetBoolObject(!feof(fp)));
}

static void bc_file_nativeGetStdIn(method* parent, Frame* fr, Enviroment* env) {
	object* file = file_new(stdin, true);
	PushVector(fr->ValueStack, file);
}

static void bc_file_nativeGetStdOut(method* parent, Frame* fr, Enviroment* env) {
	object* file = file_new(stdout, true);
	PushVector(fr->ValueStack, file);
}

static void bc_file_nativeGetStdErr(method* parent, Frame* fr, Enviroment* env) {
	object* file = file_new(stderr, true);
	PushVector(fr->ValueStack, file);
}

static void bc_file_nativeClose(method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	FILE* fp = AtVector(self->native_slot_vec, 0);
	assert(fp != NULL);
	fclose(fp);
}

static object* file_new(FILE* fp, bool std) {
	object* file = object_ref_new();
	assert(file->paint != PAINT_ONEXIT_T);
	type* fileType = GetBCFileType();
	file->gtype = fileType->generic_self;
	file->vptr = TYPE2CLASS(fileType)->vt;
	AssignVector(file->native_slot_vec, 0, fp);
	return file;
}