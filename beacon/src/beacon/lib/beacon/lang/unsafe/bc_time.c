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

static void bc_time_nativeGetRawTime(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_time_nativeToString(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_time_nativeGetSecond(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_time_nativeGetMinute(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_time_nativeGetHour(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_time_nativeGetDay(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_time_nativeGetYear(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_time_nativeGetDayOfWeek(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_time_nativeGetDayOfYear(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);

void InitTime() {
	bc_Namespace* unsafe = bc_GetUnsafeNamespace();
	bc_Type* timeType = bc_NewPreloadClass(InternString("Time"));
	bc_Class* timeClass = BC_TYPE2CLASS(timeType);
	bc_AddTypeNamespace(unsafe, timeType);
	bc_DefineNativeMethodClass(timeClass, "nativeRawTime", bc_time_nativeGetRawTime);
	bc_DefineNativeMethodClass(timeClass, "nativeToString", bc_time_nativeToString);
	bc_DefineNativeMethodClass(timeClass, "nativeGetSecond", bc_time_nativeGetSecond);
	bc_DefineNativeMethodClass(timeClass, "nativeGetMinute", bc_time_nativeGetMinute);
	bc_DefineNativeMethodClass(timeClass, "nativeGetHour", bc_time_nativeGetHour);
	bc_DefineNativeMethodClass(timeClass, "nativeGetDay", bc_time_nativeGetDay);
	bc_DefineNativeMethodClass(timeClass, "nativeGetYear", bc_time_nativeGetYear);
	bc_DefineNativeMethodClass(timeClass, "nativeGetDayOfWeek", bc_time_nativeGetDayOfWeek);
	bc_DefineNativeMethodClass(timeClass, "nativeGetDayOfYear", bc_time_nativeGetDayOfYear);
}

bc_Type* GetTimeType() {
	bc_Namespace* unsafe = bc_GetUnsafeNamespace();
	return bc_FindTypeFromNamespace(unsafe, InternString("Time"));
}
//private
static void bc_time_nativeGetRawTime(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	time_t tref;
	time(&tref);
	//FIXME:long型を導入する
	PushVector(fr->ValueStack, NewLong(tref));
}

static void bc_time_nativeToString(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = AtVector(fr->VariableTable, 0);
	int temp;
	bc_FindFieldClass(BC_TYPE2CLASS(GetTimeType()), InternString("rawTime"), &temp);
	bc_Object* rawTime = (bc_Object*)AtVector(self->Fields, temp);
	PushVector(fr->ValueStack, NewString(ctime(&(((Long*)rawTime)->Value))));
}

static void bc_time_nativeGetSecond(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, bc_GetIntObject(localtime(&(((Long*)rawTime)->Value))->tm_sec));
}

static void bc_time_nativeGetMinute(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, bc_GetIntObject(localtime(&(((Long*)rawTime)->Value))->tm_min));
}

static void bc_time_nativeGetHour(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, bc_GetIntObject(localtime(&(((Long*)rawTime)->Value))->tm_hour));
}

static void bc_time_nativeGetDay(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, bc_GetIntObject(localtime(&(((Long*)rawTime)->Value))->tm_mday));
}

static void bc_time_nativeGetYear(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, bc_GetIntObject(localtime(&(((Long*)rawTime)->Value))->tm_year));
}

static void bc_time_nativeGetDayOfWeek(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, bc_GetIntObject(localtime(&(((Long*)rawTime)->Value))->tm_wday));
}

static void bc_time_nativeGetDayOfYear(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* rawTime = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, bc_GetIntObject(localtime(&(((Long*)rawTime)->Value))->tm_yday));
}
