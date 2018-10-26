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

static void bc_file_nativeOpen(Method* parent, Frame* fr, Enviroment* env);
static void bc_file_nativePut(Method* parent, Frame* fr, Enviroment* env);
static void bc_file_nativeGet(Method* parent, Frame* fr, Enviroment* env);
static void bc_file_nativeAvailable(Method* parent, Frame* fr, Enviroment* env);
static void bc_file_nativeGetStdIn(Method* parent, Frame* fr, Enviroment* env);
static void bc_file_nativeGetStdOut(Method* parent, Frame* fr, Enviroment* env);
static void bc_file_nativeGetStdErr(Method* parent, Frame* fr, Enviroment* env);
static void bc_file_nativeClose(Method* parent, Frame* fr, Enviroment* env);
static Object* file_new(FILE* fp, bool std);

void InitBCFile() {
	Namespace* unsafe = GetUnsafeNamespace();
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
	Namespace* unsafe = GetUnsafeNamespace();
	return FindTypeFromNamespace(unsafe, InternString("File"));
}
//private
static void bc_file_nativeOpen(Method* parent, Frame* fr, Enviroment* env) {
	Object* fileObj = AtVector(fr->VariableTable, 1);
	Object* modeObj = AtVector(fr->VariableTable, 2);
	Buffer* fileStr = GetRawBCString(fileObj);
	Buffer* modeStr = GetRawBCString(modeObj);
	//Printfln("%s : %s", fileStr->text, modeStr->text);

	FILE* fp = fopen(fileStr->Text, modeStr->Text);
	if(fp == NULL) {
		//ひらけなかった
		PushVector(fr->ValueStack, GetNullObject());
		return;
	}
	Object* file = file_new(fp, false);
	PushVector(fr->ValueStack, file);
}

static void bc_file_nativePut(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* ch = AtVector(fr->VariableTable, 1);
	FILE* fp = AtVector(self->NativeSlotVec, 0);
	assert(fp != NULL);
	fputc(ch->u.char_, fp);
}

static void bc_file_nativeGet(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	FILE* fp = AtVector(self->NativeSlotVec, 0);
	assert(fp != NULL);
	char ret = fgetc(fp);
	PushVector(fr->ValueStack, Object_char_new(ret));
}

static void bc_file_nativeAvailable(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	FILE* fp = AtVector(self->NativeSlotVec, 0);
	assert(fp != NULL);
	PushVector(fr->ValueStack, GetBoolObject(!feof(fp)));
}

static void bc_file_nativeGetStdIn(Method* parent, Frame* fr, Enviroment* env) {
	Object* file = file_new(stdin, true);
	PushVector(fr->ValueStack, file);
}

static void bc_file_nativeGetStdOut(Method* parent, Frame* fr, Enviroment* env) {
	Object* file = file_new(stdout, true);
	PushVector(fr->ValueStack, file);
}

static void bc_file_nativeGetStdErr(Method* parent, Frame* fr, Enviroment* env) {
	Object* file = file_new(stderr, true);
	PushVector(fr->ValueStack, file);
}

static void bc_file_nativeClose(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	FILE* fp = AtVector(self->NativeSlotVec, 0);
	assert(fp != NULL);
	fclose(fp);
}

static Object* file_new(FILE* fp, bool std) {
	Object* file = Object_ref_new();
	assert(file->Paint != PAINT_ONEXIT_T);
	type* fileType = GetBCFileType();
	file->GType = fileType->generic_self;
	file->VPtr = TYPE2CLASS(fileType)->vt;
	AssignVector(file->NativeSlotVec, 0, fp);
	return file;
}