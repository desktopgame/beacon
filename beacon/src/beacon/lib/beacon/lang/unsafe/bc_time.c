#include "bc_time.h"
#include "../../../../env/namespace.h"
#include "../../../../env/type_impl.h"
#include "../../../../util/string_buffer.h"
#include "../../../../util/text.h"
#include "../../../bc_library_impl.h"
#include "../bc_string.h"
#include <time.h>
#include <assert.h>

static void bc_time_nativeGetRawTime(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeToString(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeGetSecond(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeGetMinute(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeGetHour(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeGetDay(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeGetYear(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeGetDayOfWeek(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeGetDayOfYear(method* parent, frame* fr, enviroment* env);

void bc_time_init() {
	namespace_* unsafe = namespace_unsafe();
	type* timeType = class_new_preload(string_pool_intern("Time"));
	class_* timeClass = TYPE2CLASS(timeType);
	namespace_add_type(unsafe, timeType);
	class_define_native_method(timeClass, "nativeRawTime", bc_time_nativeGetRawTime);
	class_define_native_method(timeClass, "nativeToString", bc_time_nativeToString);
	class_define_native_method(timeClass, "nativeGetSecond", bc_time_nativeGetSecond);
	class_define_native_method(timeClass, "nativeGetMinute", bc_time_nativeGetMinute);
	class_define_native_method(timeClass, "nativeGetHour", bc_time_nativeGetHour);
	class_define_native_method(timeClass, "nativeGetDay", bc_time_nativeGetDay);
	class_define_native_method(timeClass, "nativeGetYear", bc_time_nativeGetYear);
	class_define_native_method(timeClass, "nativeGetDayOfWeek", bc_time_nativeGetDayOfWeek);
	class_define_native_method(timeClass, "nativeGetDayOfYear", bc_time_nativeGetDayOfYear);
}

type* bc_time_type() {
	namespace_* unsafe = namespace_unsafe();
	return namespace_get_type(unsafe, string_pool_intern("Time"));
}
//private
static void bc_time_nativeGetRawTime(method* parent, frame* fr, enviroment* env) {
	time_t tref;
	time(&tref);
	//FIXME:long型を導入する
	vector_push(fr->value_stack, object_long_new(tref));
}

static void bc_time_nativeToString(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	int temp;
	class_find_field(TYPE2CLASS(bc_time_type()), string_pool_intern("rawTime"), &temp);
	object* rawTime = (object*)vector_at(self->u.field_vec, temp);
	vector_push(fr->value_stack, object_string_new(ctime(&(rawTime->u.long_))));
}

static void bc_time_nativeGetSecond(method* parent, frame* fr, enviroment* env) {
	object* rawTime = vector_at(fr->ref_stack, 1);
	vector_push(fr->value_stack, object_int_get(localtime(&(rawTime->u.long_))->tm_sec));
}

static void bc_time_nativeGetMinute(method* parent, frame* fr, enviroment* env) {
	object* rawTime = vector_at(fr->ref_stack, 1);
	vector_push(fr->value_stack, object_int_get(localtime(&(rawTime->u.long_))->tm_min));
}

static void bc_time_nativeGetHour(method* parent, frame* fr, enviroment* env) {
	object* rawTime = vector_at(fr->ref_stack, 1);
	vector_push(fr->value_stack, object_int_get(localtime(&(rawTime->u.long_))->tm_hour));
}

static void bc_time_nativeGetDay(method* parent, frame* fr, enviroment* env) {
	object* rawTime = vector_at(fr->ref_stack, 1);
	vector_push(fr->value_stack, object_int_get(localtime(&(rawTime->u.long_))->tm_mday));
}

static void bc_time_nativeGetYear(method* parent, frame* fr, enviroment* env) {
	object* rawTime = vector_at(fr->ref_stack, 1);
	vector_push(fr->value_stack, object_int_get(localtime(&(rawTime->u.long_))->tm_year));
}

static void bc_time_nativeGetDayOfWeek(method* parent, frame* fr, enviroment* env) {
	object* rawTime = vector_at(fr->ref_stack, 1);
	vector_push(fr->value_stack, object_int_get(localtime(&(rawTime->u.long_))->tm_wday));
}

static void bc_time_nativeGetDayOfYear(method* parent, frame* fr, enviroment* env) {
	object* rawTime = vector_at(fr->ref_stack, 1);
	vector_push(fr->value_stack, object_int_get(localtime(&(rawTime->u.long_))->tm_yday));
}
