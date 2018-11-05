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
static void bc_Object_nativeToString(Method* parent, Frame* fr, Enviroment* env);
static void bc_Object_nativeReferenceEquals(Method* parent, Frame* fr, Enviroment* env);

void InitBCObject() {
	Namespace* lang = GetLangNamespace();
	Type* ObjectType = NewPreloadClass(InternString("Object"));
	Class* ObjectClass = TYPE2CLASS(ObjectType);
	AddTypeNamespace(lang, ObjectType);
	DefineNativeMethodClass(ObjectClass, "nativeToString", bc_Object_nativeToString);
	DefineNativeMethodClass(ObjectClass, "nativeReferenceEquals", bc_Object_nativeReferenceEquals);
}

Type* GetBCObjectType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Object"));
}

//private
static void bc_Object_nativeToString(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = (Object*)AtVector(fr->VariableTable, 0);
	Buffer* sb = NewBuffer();
	//参照型
	if (self->Tag == OBJECT_REF_T) {
		//char* name = GetTypeName(self->type);
		AppendBuffer(sb, '[');
		AppendsBuffer(sb, "Ref");
		AppendBuffer(sb, ']');
		ShrinkBuffer(sb);
	//真偽型
	} else if (self->Tag == OBJECT_BOOL_T) {
		if (self == GetTrueObject()) {
			AppendsBuffer(sb, "true");
		} else if (self == GetFalseObject()) {
			AppendsBuffer(sb, "false");
		}
	//整数型
	} else if (self->Tag == OBJECT_INT_T) {
#define BUFF_LEN 256
		char buff[256];
		int res = sprintf(buff, "%d", OBJ2INT(self));
		AppendsBuffer(sb, buff);
#undef BUFF_LEN
	}
	char* str = ReleaseBuffer(sb);
	Object* ret = (Object*)NewString(str);
	PushVector(fr->ValueStack, ret);
	MEM_FREE(str);
}

static void bc_Object_nativeReferenceEquals(Method* parent, Frame* fr, Enviroment* env) {
	Object* a = (Object*)AtVector(fr->VariableTable, 1);
	Object* b = (Object*)AtVector(fr->VariableTable, 2);
	PushVector(fr->ValueStack, GetBoolObject(a == b));
}