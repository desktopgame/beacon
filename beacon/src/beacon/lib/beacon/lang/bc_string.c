#include "bc_string.h"
#include "../../bc_library_impl.h"
#include "../../bc_library_interface.h"
#include <assert.h>
#include <string.h>

//proto
static void* handle_obj_message(Object* self, ObjectMessage msg, int argc, ObjectMessageArgument argv[]);
static void bc_string_nativeInit(Method* parent, Frame* fr, Enviroment* env);

Object* NewString(const char* str) {
	Object* ret = ConstructObject(sizeof(String), GENERIC_STRING);
	ret->OnMessage = handle_obj_message;
	//ret->u.string_ = s;
	//ret->u.field_vec = NewVector();
	//ret->GType = GENERIC_STRING;
	//ret->VPtr = GetVTableType(TYPE_STRING);

	//配列を生成
	Object* arr = NewArray(strlen(str), GENERIC_CHAR);
	//arr->Tag = OBJECT_ARRAY_T;
	Type* arrType = GetArrayType();
	Type* strType = FindTypeFromNamespace(GetLangNamespace(), InternString("String"));
	//arr->GType = NewGenericType(arrType);
	//arr->VPtr = GetVTableType(arrType);
	//arr->Tag = OBJECT_ARRAY_T;
	//AddArgsGenericType(arr->GType, GENERIC_CHAR);
	//ボックス化
	const char* itr = str;
	Buffer* sb = NewBuffer();
	for(int i=0;; i++) {
		char c = str[i];
		if(c == '\0') {
			break;
		}
		SetElementAt((Object*)arr, i, (Object*)NewChar(c));
		AppendBuffer(sb, c);
	}
	ShrinkBuffer(sb);
	//String#charArrayを埋める
	int temp = 0;
	FindFieldClass(strType->Kind.Class, InternString("charArray"), &temp);
	AssignVector(ret->Fields, temp, arr);
	VectorItem* test = AtVector(ret->Fields, temp);
	assert(test != NULL);
	//Array#lengthを埋める
	temp = 0;
	FindFieldClass(arrType->Kind.Class, InternString("length"), &temp);
	AssignVector(arr->Fields, temp, NewInteger(sb->Length));
	//C形式の文字列でも保存
	//AssignVector(ret->NativeSlotVec, 0, sb);
	((String*)ret)->Buffer = sb;
	return (Object*)ret;
}

void InitString() {
	Namespace* lang = GetLangNamespace();
	Type* stringType = NewPreloadClass(InternString("String"));
	Class* stringClass = TYPE2CLASS(stringType);
	stringType->AllocSize = sizeof(String);
	AddTypeNamespace(lang, stringType);
	DefineNativeMethodClass(stringClass, "nativeInit", bc_string_nativeInit);
}

Buffer * GetRawString(Object* self) {
	//VectorItem e = AtVector(self->NativeSlotVec, 0);
	//assert(self->Tag == OBJECT_STRING_T);
	return ((String*)self)->Buffer;
}

Type* GetStringType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("String"));
}

//private
static void* handle_obj_message(Object* self, ObjectMessage msg, int argc, ObjectMessageArgument argv[]) {
	if(msg == OBJECT_MSG_DELETE) {
		DeleteBuffer(((String*)self)->Buffer);
		MEM_FREE(self);
		return NULL;
	} else {
		return HandleObjectMessage(self, msg, argc, argv);
	}
}

static void bc_string_nativeInit(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	//プログラムの中で ダブルクォート("HelloWorld") によって
	//文字列が作成された場合には Object_string_new() 
	//によって生成されます。
	//こちらの場合では Object#nativeSlotVec に C形式の文字列を格納します。
	//これはコンストラクタによって String が作成された場合には
	//呼び出されないので、その部分の処理をここで行います。
	self->OnMessage = handle_obj_message;
	//String#charArrayを取得
	int temp = 0;
	FindFieldClass(TYPE_STRING->Kind.Class, InternString("charArray"), &temp);
	Array* charArr = (Array*)AtVector(self->Fields, temp);
	//これを char* へ変換
	Buffer* sb = NewBuffer();
	for (int i = 0; i < charArr->Elements->Length; i++) {
		Object* e = (Object*)AtVector(charArr->Elements, i);
		assert(IsCharValue(e));
		AppendBuffer(sb, ((Char*)e)->Value);
	}
	//AssignVector(self->NativeSlotVec, 0, sb);
	((String*)self)->Buffer = sb;
	//self->Tag = OBJECT_STRING_T;
}