#include "bc_time.h"
#include "../../../../env/namespace.h"
#include "../../../../env/TYPE_IMPL.h"
#include "../../../../util/string_buffer.h"
#include "../../../../util/text.h"
#include "../../../bc_library_interface.h"
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

void InitTime() {
	Namespace* unsafe = GetUnsafeNamespace();
	Type* timeType = NewPreloadClass(InternString("Time"));
	Class* timeClass = TYPE2CLASS(timeType);
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

Type* GetTimeType() {
	Namespace* unsafe = GetUnsafeNamespace();
	return FindTypeFromNamespace(unsafe, InternString("Time"));
}
//private
static void bc_time_nativeGetRawTime(Method* parent, Frame* fr, Enviroment* env) {
	time_t tref;
	time(&tref);
	//FIXME:long型を導入する
	PushVector(fr->ValueStack, NewLong(tref));
}

static void bc_time_nativeToString(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	int temp;
	FindFieldClass(TYPE2CLASS(GetTimeType()), InternString("rawTime"), &temp);
	Object* rawTime = (Object*)AtVector(self->Fields, temp);
	PushVector(fr->ValueStack, NewString(ctime(&(((Long*)rawTime)->Value))));
}

static void bc_time_nativeGetSecond(Method* parent, Frame* fr, Enviroment* env) {
	Object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, GetIntObject(localtime(&(((Long*)rawTime)->Value))->tm_sec));
}

static void bc_time_nativeGetMinute(Method* parent, Frame* fr, Enviroment* env) {
	Object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, GetIntObject(localtime(&(((Long*)rawTime)->Value))->tm_min));
}

static void bc_time_nativeGetHour(Method* parent, Frame* fr, Enviroment* env) {
	Object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, GetIntObject(localtime(&(((Long*)rawTime)->Value))->tm_hour));
}

static void bc_time_nativeGetDay(Method* parent, Frame* fr, Enviroment* env) {
	Object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, GetIntObject(localtime(&(((Long*)rawTime)->Value))->tm_mday));
}

static void bc_time_nativeGetYear(Method* parent, Frame* fr, Enviroment* env) {
	Object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, GetIntObject(localtime(&(((Long*)rawTime)->Value))->tm_year));
}

static void bc_time_nativeGetDayOfWeek(Method* parent, Frame* fr, Enviroment* env) {
	Object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, GetIntObject(localtime(&(((Long*)rawTime)->Value))->tm_wday));
}

static void bc_time_nativeGetDayOfYear(Method* parent, Frame* fr, Enviroment* env) {
	Object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, GetIntObject(localtime(&(((Long*)rawTime)->Value))->tm_yday));
}
