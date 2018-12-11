#include "file.h"
#include <assert.h>
#include "../../../../env/TYPE_IMPL.h"
#include "../../../../env/namespace.h"
#include "../../../../util/string_buffer.h"
#include "../../../../util/text.h"
#include "../../../bc_library_impl.h"
#include "../../../bc_library_interface.h"
#include "../string.h"
#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif

static void bc_file_nativeOpen(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_file_nativePut(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_file_nativeGet(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_file_nativeAvailable(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env);
static void bc_file_nativeGetStdIn(bc_Method* parent, bc_Frame* fr,
                                   bc_Enviroment* env);
static void bc_file_nativeGetStdOut(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env);
static void bc_file_nativeGetStdErr(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env);
static void bc_file_nativeClose(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env);

bc_Object* bc_NewFile(FILE* fp) {
        bc_File* file =
            bc_ConstructObject(sizeof(bc_File), bc_GetFileType()->GenericSelf);
        assert(file->Super.Paint != PAINT_ONEXIT_T);
        file->Pointer = fp;
        return (bc_Object*)file;
}

FILE* bc_GetFilePointer(bc_Object* self) { return ((bc_File*)self)->Pointer; }

void bc_InitFile() {
        bc_Namespace* unsafe = bc_GetUnsafeNamespace(NULL);
        bc_Type* fileType = bc_NewPreloadClass(bc_InternString("File"));
        bc_Class* fileClass = BC_TYPE2CLASS(fileType);
        fileType->AllocSize = sizeof(bc_File);
        bc_AddTypeNamespace(unsafe, fileType);
        bc_DefineNativeMethodClass(fileClass, "nativeOpen", bc_file_nativeOpen);
        bc_DefineNativeMethodClass(fileClass, "nativePut", bc_file_nativePut);
        bc_DefineNativeMethodClass(fileClass, "nativeGet", bc_file_nativeGet);
        bc_DefineNativeMethodClass(fileClass, "nativeAvailable",
                                   bc_file_nativeAvailable);
        bc_DefineNativeMethodClass(fileClass, "nativeGetStdIn",
                                   bc_file_nativeGetStdIn);
        bc_DefineNativeMethodClass(fileClass, "nativeGetStdOut",
                                   bc_file_nativeGetStdOut);
        bc_DefineNativeMethodClass(fileClass, "nativeGetStdErr",
                                   bc_file_nativeGetStdErr);
        bc_DefineNativeMethodClass(fileClass, "nativeClose",
                                   bc_file_nativeClose);
}

bc_Type* bc_GetFileType() {
        bc_Namespace* unsafe = bc_GetUnsafeNamespace(NULL);
        return bc_FindTypeFromNamespace(unsafe, bc_InternString("File"));
}
// private
static void bc_file_nativeOpen(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* fileObj = bc_AtVector(fr->VariableTable, 1);
        bc_Object* modeObj = bc_AtVector(fr->VariableTable, 2);
        bc_Buffer* fileStr = bc_GetRawString(fileObj);
        bc_Buffer* modeStr = bc_GetRawString(modeObj);
        // bc_Printfln("%s : %s", fileStr->text, modeStr->text);

        FILE* fp = fopen(fileStr->Text, modeStr->Text);
        if (fp == NULL) {
                //ひらけなかった
                bc_PushVector(fr->ValueStack, bc_GetNullObject());
                return;
        }
        bc_Object* file = bc_NewFile(fp);
        bc_PushVector(fr->ValueStack, file);
}

static void bc_file_nativePut(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* ch = bc_AtVector(fr->VariableTable, 1);
        FILE* fp = bc_GetFilePointer(self);
        assert(fp != NULL);
        fputc(bc_ObjectToChar(ch), fp);
}

static void bc_file_nativeGet(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        FILE* fp = bc_GetFilePointer(self);
        assert(fp != NULL);
        char ret = fgetc(fp);
        bc_PushVector(fr->ValueStack, bc_NewChar(ret));
}

static void bc_file_nativeAvailable(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        FILE* fp = bc_GetFilePointer(self);
        assert(fp != NULL);
        bc_PushVector(fr->ValueStack, bc_GetBoolObject(!feof(fp)));
}

static void bc_file_nativeGetStdIn(bc_Method* parent, bc_Frame* fr,
                                   bc_Enviroment* env) {
        bc_Object* file = bc_NewFile(stdin);
        bc_PushVector(fr->ValueStack, file);
}

static void bc_file_nativeGetStdOut(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env) {
        bc_Object* file = bc_NewFile(stdout);
        bc_PushVector(fr->ValueStack, file);
}

static void bc_file_nativeGetStdErr(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env) {
        bc_Object* file = bc_NewFile(stderr);
        bc_PushVector(fr->ValueStack, file);
}

static void bc_file_nativeClose(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        FILE* fp = bc_GetFilePointer(self);
        assert(fp != NULL);
        fclose(fp);
}