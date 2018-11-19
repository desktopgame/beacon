#include "bc_object.h"
#include "../../bc_library_interface.h"
#include "../../bc_library_impl.h"
#include "../../../util/string_buffer.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include <stdio.h>

#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

//proto
static void bc_Object_nativeToString(bc_Method* parent, Frame* fr, Enviroment* env);
static void bc_Object_nativeReferenceEquals(bc_Method* parent, Frame* fr, Enviroment* env);

void InitObject() {
	bc_Namespace* lang = bc_GetLangNamespace();
	bc_Type* ObjectType = bc_NewPreloadClass(InternString("Object"));
	bc_Class* ObjectClass = BC_TYPE2CLASS(ObjectType);
	bc_AddTypeNamespace(lang, ObjectType);
	bc_DefineNativeMethodClass(ObjectClass, "nativeToString", bc_Object_nativeToString);
	bc_DefineNativeMethodClass(ObjectClass, "nativeReferenceEquals", bc_Object_nativeReferenceEquals);
}

bc_Type* GetObjectType() {
	bc_Namespace* lang = bc_GetLangNamespace();
	return bc_FindTypeFromNamespace(lang, InternString("Object"));
}

//private
static void bc_Object_nativeToString(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_Object* self = (bc_Object*)AtVector(fr->VariableTable, 0);
	Buffer* sb = NewBuffer();
	AppendfBuffer(sb, "%p", self);
	char* str = ReleaseBuffer(sb);
	bc_Object* ret = (bc_Object*)NewString(str);
	PushVector(fr->ValueStack, ret);
	MEM_FREE(str);
}

static void bc_Object_nativeReferenceEquals(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_Object* a = (bc_Object*)AtVector(fr->VariableTable, 1);
	bc_Object* b = (bc_Object*)AtVector(fr->VariableTable, 2);
	PushVector(fr->ValueStack, bc_GetBoolObject(a == b));
}