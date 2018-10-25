#include "bc_time.h"
#include "../../../../env/namespace.h"
#include "../../../../env/TYPE_IMPL.h"
#include "../../../../util/string_buffer.h"
#include "../../../../util/text.h"
#include "../../../bc_library_impl.h"
#include "../bc_string.h"
#include <time.h>
#include <assert.h>

#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

static void bc_time_nativeGetRawTime(Method* parent, Frame* fr, Enviroment* env);
static void bc_time_nativeToString(Method* parent, Frame* fr, Enviroment* env);
static void bc_time_nativeGetSecond(Method* parent, Frame* fr, Enviroment* env);
static void bc_time_nativeGetMinute(Method* parent, Frame* fr, Enviroment* env);
static void bc_time_nativeGetHour(Method* parent, Frame* fr, Enviroment* env);
static void bc_time_nativeGetDay(Method* parent, Frame* fr, Enviroment* env);
static void bc_time_nativeGetYear(Method* parent, Frame* fr, Enviroment* env);
static void bc_time_nativeGetDayOfWeek(Method* parent, Frame* fr, Enviroment* env);
static void bc_time_nativeGetDayOfYear(Method* parent, Frame* fr, Enviroment* env);

void InitBCTime() {
	namespace_* unsafe = GetUnsafeNamespace();
	type* timeType = NewPreloadClass(InternString("Time"));
	class_* timeClass = TYPE2CLASS(timeType);
	AddTypeNamespace(unsafe, timeType);
	DefineNativeMethodClass(timeClass, "nativeRawTime", bc_time_nativeGetRawTime);
	DefineNativeMethodClass(timeClass, "nativeToString", bc_time_nativeToString);
	DefineNativeMethodClass(timeClass, "nativeGetSecond", bc_time_nativeGetSecond);
	DefineNativeMethodClass(timeClass, "nativeGetMinute", bc_time_nativeGetMinute);
	DefineNativeMethodClass(timeClass, "nativeGetHour", bc_time_nativeGetHour);
	DefineNativeMethodClass(timeClass, "nativeGetDay", bc_time_nativeGetDay);
	DefineNativeMethodClass(timeClass, "nativeGetYear", bc_time_nativeGetYear);
	DefineNativeMethodClass(timeClass, "nativeGetDayOfWeek", bc_time_nativeGetDayOfWeek);
	DefineNativeMethodClass(timeClass, "nativeGetDayOfYear", bc_time_nativeGetDayOfYear);
}

type* GetBCTimeType() {
	namespace_* unsafe = GetUnsafeNamespace();
	return FindTypeFromNamespace(unsafe, InternString("Time"));
}
//private
static void bc_time_nativeGetRawTime(Method* parent, Frame* fr, Enviroment* env) {
	time_t tref;
	time(&tref);
	//FIXME:long型を導入する
	PushVector(fr->ValueStack, object_long_new(tref));
}

static void bc_time_nativeToString(Method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	int temp;
	FindFieldClass(TYPE2CLASS(GetBCTimeType()), InternString("rawTime"), &temp);
	object* rawTime = (object*)AtVector(self->u.field_vec, temp);
	PushVector(fr->ValueStack, object_string_new(ctime(&(rawTime->u.long_))));
}

static void bc_time_nativeGetSecond(Method* parent, Frame* fr, Enviroment* env) {
	object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, GetIntObject(localtime(&(rawTime->u.long_))->tm_sec));
}

static void bc_time_nativeGetMinute(Method* parent, Frame* fr, Enviroment* env) {
	object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, GetIntObject(localtime(&(rawTime->u.long_))->tm_min));
}

static void bc_time_nativeGetHour(Method* parent, Frame* fr, Enviroment* env) {
	object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, GetIntObject(localtime(&(rawTime->u.long_))->tm_hour));
}

static void bc_time_nativeGetDay(Method* parent, Frame* fr, Enviroment* env) {
	object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, GetIntObject(localtime(&(rawTime->u.long_))->tm_mday));
}

static void bc_time_nativeGetYear(Method* parent, Frame* fr, Enviroment* env) {
	object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, GetIntObject(localtime(&(rawTime->u.long_))->tm_year));
}

static void bc_time_nativeGetDayOfWeek(Method* parent, Frame* fr, Enviroment* env) {
	object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, GetIntObject(localtime(&(rawTime->u.long_))->tm_wday));
}

static void bc_time_nativeGetDayOfYear(Method* parent, Frame* fr, Enviroment* env) {
	object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, GetIntObject(localtime(&(rawTime->u.long_))->tm_yday));
}
