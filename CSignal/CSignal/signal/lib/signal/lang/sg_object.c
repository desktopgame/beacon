#include "sg_object.h"
#include "../../sg_library_impl.h"
#include "../../../util/string_buffer.h"
#include "../../../util/mem.h"

//proto
static void sg_object_nativeToString(method* parent, vm* vm, enviroment* env);


void sg_object_init() {
	namespace_* lang = namespace_lang();
	class_* objClass = class_new_preload("Object");
	namespace_add_type(lang, type_wrap_class(objClass));
	class_define_native_method(objClass, "nativeToString", sg_object_nativeToString);
}

//private
static void sg_object_nativeToString(method* parent, vm* vm, enviroment* env) {
	object* self = (object*)vector_top(vm->value_stack);
	string_buffer* sb = string_buffer_new();
	char* name = type_name(self->type);
	string_buffer_append(sb, '[');
	string_buffer_appends(sb, name);
	string_buffer_append(sb, ']');
	string_buffer_shrink(sb);
	object* ret = object_string_new(sb->text);
	MEM_FREE(sb);
	vector_push(vm->value_stack, ret);
}