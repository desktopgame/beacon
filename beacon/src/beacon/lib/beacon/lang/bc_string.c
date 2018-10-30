#include "bc_string.h"
#include "../../bc_library_impl.h"
#include <assert.h>

//proto
static void bc_string_nativeInit(Method* parent, Frame* fr, Enviroment* env);

void InitBCString() {
	Namespace* lang = GetLangNamespace();
	Type* stringType = NewPreloadClass(InternString("String"));
	class_* stringClass = TYPE2CLASS(stringType);
	AddTypeNamespace(lang, stringType);
	DefineNativeMethodClass(stringClass, "nativeInit", bc_string_nativeInit);
}

Buffer * GetRawBCString(Object* self) {
	VectorItem e = AtVector(self->NativeSlotVec, 0);
	assert(self->Tag == OBJECT_STRING_T);
	return (Buffer*)e;
}

Type* GetBCStringType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("String"));
}

//private
static void bc_string_nativeInit(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	//プログラムの中で ダブルクォート("HelloWorld") によって
	//文字列が作成された場合には Object_string_new() 
	//によって生成されます。
	//こちらの場合では Object#nativeSlotVec に C形式の文字列を格納します。
	//これはコンストラクタによって String が作成された場合には
	//呼び出されないので、その部分の処理をここで行います。

	//String#charArrayを取得
	int temp = 0;
	FindFieldClass(TYPE_STRING->Kind.Class, InternString("charArray"), &temp);
	Object* charArr = AtVector(self->u.field_vec, temp);
	//これを char* へ変換
	Buffer* sb = NewBuffer();
	for (int i = 0; i < charArr->NativeSlotVec->Length; i++) {
		Object* e = (Object*)AtVector(charArr->NativeSlotVec, i);
		assert(e->Tag == OBJECT_CHAR_T);
		AppendBuffer(sb, e->u.char_);
	}
	AssignVector(self->NativeSlotVec, 0, sb);
	self->Tag = OBJECT_STRING_T;
}