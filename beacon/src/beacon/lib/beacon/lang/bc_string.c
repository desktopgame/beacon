#include "bc_string.h"
#include "../../bc_library_impl.h"
#include "../../bc_library_interface.h"
#include <assert.h>
#include <string.h>

//proto
static void* handle_obj_message(bc_Object* self, bc_ObjectMessage msg, int argc, bc_ObjectMessageArgument argv[]);
static void bc_string_nativeInit(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);

bc_Object* NewString(const char* str) {
	bc_Object* ret = bc_ConstructObject(sizeof(String), BC_GENERIC_STRING);
	ret->OnMessage = handle_obj_message;
	//ret->u.string_ = s;
	//ret->u.field_vec = NewVector();
	//ret->GType = GENERIC_STRING;
	//ret->VPtr = GetVTableType(TYPE_STRING);

	//配列を生成
	bc_Object* arr = NewArray(strlen(str), BC_GENERIC_CHAR);
	//arr->Tag = OBJECT_ARRAY_T;
	bc_Type* arrType = GetArrayType();
	bc_Type* strType = bc_FindTypeFromNamespace(bc_GetLangNamespace(), InternString("String"));
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
		SetElementAt((bc_Object*)arr, i, (bc_Object*)NewChar(c));
		AppendBuffer(sb, c);
	}
	ShrinkBuffer(sb);
	//String#charArrayを埋める
	int temp = 0;
	bc_FindFieldClass(strType->Kind.Class, InternString("charArray"), &temp);
	AssignVector(ret->Fields, temp, arr);
	VectorItem* test = AtVector(ret->Fields, temp);
	assert(test != NULL);
	//Array#lengthを埋める
	temp = 0;
	bc_FindFieldClass(arrType->Kind.Class, InternString("length"), &temp);
	AssignVector(arr->Fields, temp, NewInteger(sb->Length));
	//C形式の文字列でも保存
	//AssignVector(ret->NativeSlotVec, 0, sb);
	((String*)ret)->Buffer = sb;
	return (bc_Object*)ret;
}

void InitString() {
	bc_Namespace* lang = bc_GetLangNamespace();
	bc_Type* stringType = bc_NewPreloadClass(InternString("String"));
	bc_Class* stringClass = BC_TYPE2CLASS(stringType);
	stringType->AllocSize = sizeof(String);
	bc_AddTypeNamespace(lang, stringType);
	bc_DefineNativeMethodClass(stringClass, "nativeInit", bc_string_nativeInit);
}

Buffer * GetRawString(bc_Object* self) {
	//VectorItem e = AtVector(self->NativeSlotVec, 0);
	//assert(self->Tag == OBJECT_STRING_T);
	return ((String*)self)->Buffer;
}

bc_Type* GetStringType() {
	bc_Namespace* lang = bc_GetLangNamespace();
	return bc_FindTypeFromNamespace(lang, InternString("String"));
}

//private
static void* handle_obj_message(bc_Object* self, bc_ObjectMessage msg, int argc, bc_ObjectMessageArgument argv[]) {
	String* str = ((String*)self);
	if(msg == OBJECT_MSG_DELETE) {
		DeleteBuffer(str->Buffer); str->Buffer = NULL;
		return bc_HandleObjectMessage(self, msg, argc, argv);
	} else if(msg == OBJECT_MSG_DESTROY) {
		DeleteBuffer(str->Buffer); str->Buffer = NULL;
		return bc_HandleObjectMessage(self, msg, argc, argv);
	} else {
		return bc_HandleObjectMessage(self, msg, argc, argv);
	}
}

static void bc_string_nativeInit(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = AtVector(fr->VariableTable, 0);
	//プログラムの中で ダブルクォート("HelloWorld") によって
	//文字列が作成された場合には Object_string_new() 
	//によって生成されます。
	//こちらの場合では Object#nativeSlotVec に C形式の文字列を格納します。
	//これはコンストラクタによって String が作成された場合には
	//呼び出されないので、その部分の処理をここで行います。
	self->OnMessage = handle_obj_message;
	//String#charArrayを取得
	int temp = 0;
	bc_FindFieldClass(BC_TYPE_STRING->Kind.Class, InternString("charArray"), &temp);
	Array* charArr = (Array*)AtVector(self->Fields, temp);
	//これを char* へ変換
	Buffer* sb = NewBuffer();
	for (int i = 0; i < charArr->Elements->Length; i++) {
		bc_Object* e = (bc_Object*)AtVector(charArr->Elements, i);
		assert(bc_IsCharValue(e));
		AppendBuffer(sb, ((Char*)e)->Value);
	}
	//AssignVector(self->NativeSlotVec, 0, sb);
	((String*)self)->Buffer = sb;
	//self->Tag = OBJECT_STRING_T;
}