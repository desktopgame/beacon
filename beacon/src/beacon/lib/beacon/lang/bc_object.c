#include "bc_object.h"
#include "../../bc_library_impl.h"
#include "../../../util/string_buffer.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include <stdio.h>

//proto
static void bc_object_nativeToString(method* parent, frame* fr, enviroment* env);
static type* gBCObjectType = NULL;

void bc_object_init() {
	namespace_* lang = namespace_lang();
	class_* objClass = class_new_preload("Object");
	namespace_add_type(lang, type_wrap_class(objClass));
	class_define_native_method(objClass, "nativeToString", bc_object_nativeToString);
}

type* bc_object_type() {
	if(gBCObjectType == NULL) {
		namespace_* lang = namespace_lang();
		gBCObjectType = namespace_get_type(lang, "Object");
	}
	return gBCObjectType;
}

//private
static void bc_object_nativeToString(method* parent, frame* fr, enviroment* env) {
	object* self = (object*)vector_at(fr->ref_stack, 0);
	string_buffer* sb = string_buffer_new();
	//参照型
	if (self->tag == object_ref) {
		//char* name = type_name(self->type);
		string_buffer_append(sb, '[');
		string_buffer_appends(sb, "Ref");
		string_buffer_append(sb, ']');
		string_buffer_shrink(sb);
	//真偽型
	} else if (self->tag == object_bool) {
		if (self == object_get_true()) {
			string_buffer_appends(sb, "true");
		} else if (self == object_get_false()) {
			string_buffer_appends(sb, "false");
		}
	//整数型
	} else if (self->tag == object_int) {
#define BUFF_LEN 256
		char buff[256];
		int res = text_sprintf(buff, BUFF_LEN, "%d", self->u.int_);
		string_buffer_appends(sb, buff);
#undef BUFF_LEN
	}
	object* ret = object_string_new(sb->text);
	MEM_FREE(sb);
	vector_push(fr->value_stack, ret);
}