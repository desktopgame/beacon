#include "bc_string.h"
#include "../../bc_library_impl.h"
#include <assert.h>

//proto
static void bc_string_nativeInit(method* parent, frame* fr, enviroment* env);

void bc_string_init() {
	namespace_* lang = namespace_lang();
	type* stringType = class_new_preload(string_pool_intern("String"));
	class_* stringClass = TYPE2CLASS(stringType);
	namespace_add_type(lang, stringType);
	class_define_native_method(stringClass, "nativeInit", bc_string_nativeInit);
}

string_buffer * bc_string_raw(object* self) {
	vector_item e = vector_at(self->native_slot_vec, 0);
	assert(self->tag == object_string_T);
	return (string_buffer*)e;
}

type* bc_string_type() {
	namespace_* lang = namespace_lang();
	return namespace_get_type(lang, string_pool_intern("String"));
}

//private
static void bc_string_nativeInit(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	//プログラムの中で ダブルクォート("HelloWorld") によって
	//文字列が作成された場合には object_string_new() 
	//によって生成されます。
	//こちらの場合では object#nativeSlotVec に C形式の文字列を格納します。
	//これはコンストラクタによって String が作成された場合には
	//呼び出されないので、その部分の処理をここで行います。

	//String#charArrayを取得
	int temp = 0;
	class_find_field(TYPE_STRING->u.class_, string_pool_intern("charArray"), &temp);
	object* charArr = vector_at(self->u.field_vec, temp);
	//これを char* へ変換
	string_buffer* sb = string_buffer_new();
	for (int i = 0; i < charArr->native_slot_vec->length; i++) {
		object* e = (object*)vector_at(charArr->native_slot_vec, i);
		assert(e->tag == object_char_T);
		string_buffer_append(sb, e->u.char_);
	}
	vector_assign(self->native_slot_vec, 0, sb);
	self->tag = object_string_T;
}