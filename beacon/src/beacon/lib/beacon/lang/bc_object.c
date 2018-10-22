#include "bc_object.h"
#include "../../bc_library_impl.h"
#include "../../../util/string_buffer.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include <stdio.h>

#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

//proto
static void bc_object_nativeToString(method* parent, Frame* fr, Enviroment* env);
static void bc_object_nativeReferenceEquals(method* parent, Frame* fr, Enviroment* env);

void InitBCObject() {
	namespace_* lang = GetLangNamespace();
	type* objectType = NewPreloadClass(InternString("Object"));
	class_* objectClass = TYPE2CLASS(objectType);
	AddTypeNamespace(lang, objectType);
	DefineNativeMethodClass(objectClass, "nativeToString", bc_object_nativeToString);
	DefineNativeMethodClass(objectClass, "nativeReferenceEquals", bc_object_nativeReferenceEquals);
}

type* GetBCObjectType() {
	namespace_* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Object"));
}

//private
static void bc_object_nativeToString(method* parent, Frame* fr, Enviroment* env) {
	object* self = (object*)AtVector(fr->VariableTable, 0);
	Buffer* sb = NewBuffer();
	//参照型
	if (self->tag == OBJECT_REF_T) {
		//char* name = GetTypeName(self->type);
		AppendBuffer(sb, '[');
		AppendsBuffer(sb, "Ref");
		AppendBuffer(sb, ']');
		ShrinkBuffer(sb);
	//真偽型
	} else if (self->tag == OBJECT_BOOL_T) {
		if (self == GetTrueObject()) {
			AppendsBuffer(sb, "true");
		} else if (self == GetFalseObject()) {
			AppendsBuffer(sb, "false");
		}
	//整数型
	} else if (self->tag == OBJECT_INT_T) {
#define BUFF_LEN 256
		char buff[256];
		int res = sprintf(buff, "%d", self->u.int_);
		AppendsBuffer(sb, buff);
#undef BUFF_LEN
	}
	char* str = ReleaseBuffer(sb);
	object* ret = object_string_new(str);
	PushVector(fr->ValueStack, ret);
	MEM_FREE(str);
}

static void bc_object_nativeReferenceEquals(method* parent, Frame* fr, Enviroment* env) {
	object* a = (object*)AtVector(fr->VariableTable, 1);
	object* b = (object*)AtVector(fr->VariableTable, 2);
	PushVector(fr->ValueStack, GetBoolObject(a == b));
}