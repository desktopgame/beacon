#include "bc_file.h"
#include "../../../../env/namespace.h"
#include "../../../../env/TYPE_IMPL.h"
#include "../../../../util/string_buffer.h"
#include "../../../../util/text.h"
#include "../../../bc_library_interface.h"
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

Object* NewFile(FILE* fp) {
	File* file = ConstructObject(sizeof(File), GetFileType()->GenericSelf);
	assert(file->Super.Paint != PAINT_ONEXIT_T);
	file->Pointer = fp;
	return (Object*)file;
}

FILE* GetFilePointer(Object* self) {
	return ((File*)self)->Pointer;
}

void InitFile() {
	Namespace* unsafe = GetUnsafeNamespace();
	Type* fileType = NewPreloadClass(InternString("File"));
	Class* fileClass = TYPE2CLASS(fileType);
	fileType->AllocSize = sizeof(File);
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

Type* GetFileType() {
	Namespace* unsafe = GetUnsafeNamespace();
	return FindTypeFromNamespace(unsafe, InternString("File"));
}
//private
static void bc_file_nativeOpen(Method* parent, Frame* fr, Enviroment* env) {
	Object* fileObj = AtVector(fr->VariableTable, 1);
	Object* modeObj = AtVector(fr->VariableTable, 2);
	Buffer* fileStr = GetRawString(fileObj);
	Buffer* modeStr = GetRawString(modeObj);
	//Printfln("%s : %s", fileStr->text, modeStr->text);

	FILE* fp = fopen(fileStr->Text, modeStr->Text);
	if(fp == NULL) {
		//ひらけなかった
		PushVector(fr->ValueStack, GetNullObject());
		return;
	}
	Object* file = NewFile(fp);
	PushVector(fr->ValueStack, file);
}

static void bc_file_nativePut(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* ch = AtVector(fr->VariableTable, 1);
	FILE* fp = GetFilePointer(self);
	assert(fp != NULL);
	fputc(ObjectToChar(ch), fp);
}

static void bc_file_nativeGet(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	FILE* fp = GetFilePointer(self);
	assert(fp != NULL);
	char ret = fgetc(fp);
	PushVector(fr->ValueStack, NewChar(ret));
}

static void bc_file_nativeAvailable(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	FILE* fp = GetFilePointer(self);
	assert(fp != NULL);
	PushVector(fr->ValueStack, GetBoolObject(!feof(fp)));
}

static void bc_file_nativeGetStdIn(Method* parent, Frame* fr, Enviroment* env) {
	Object* file = NewFile(stdin);
	PushVector(fr->ValueStack, file);
}

static void bc_file_nativeGetStdOut(Method* parent, Frame* fr, Enviroment* env) {
	Object* file = NewFile(stdout);
	PushVector(fr->ValueStack, file);
}

static void bc_file_nativeGetStdErr(Method* parent, Frame* fr, Enviroment* env) {
	Object* file = NewFile(stderr);
	PushVector(fr->ValueStack, file);
}

static void bc_file_nativeClose(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	FILE* fp = GetFilePointer(self);
	assert(fp != NULL);
	fclose(fp);
}