#include "time.h"
#include <assert.h>
#include <time.h>
#include "../../../../env/TYPE_IMPL.h"
#include "../../../../env/namespace.h"
#include "../../../../util/string_buffer.h"
#include "../../../../util/text.h"
#include "../../../bc_library_impl.h"
#include "../../../bc_library_interface.h"
#include "../string.h"

#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif

static void bc_time_nativeGetRawTime(bc_Method* parent, bc_Frame* fr,
                                     bc_Enviroment* env);
static void bc_time_nativeToString(bc_Method* parent, bc_Frame* fr,
                                   bc_Enviroment* env);
static void bc_time_nativeGetSecond(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env);
static void bc_time_nativeGetMinute(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env);
static void bc_time_nativeGetHour(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env);
static void bc_time_nativeGetDay(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env);
static void bc_time_nativeGetYear(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env);
static void bc_time_nativeGetDayOfWeek(bc_Method* parent, bc_Frame* fr,
                                       bc_Enviroment* env);
static void bc_time_nativeGetDayOfYear(bc_Method* parent, bc_Frame* fr,
                                       bc_Enviroment* env);

void bc_InitTime() {
        bc_Namespace* unsafe = bc_GetUnsafeNamespace();
        bc_Type* timeType = bc_NewPreloadClass(bc_InternString("Time"));
        bc_Class* timeClass = BC_TYPE2CLASS(timeType);
        bc_AddTypeNamespace(unsafe, timeType);
        bc_DefineNativeMethodClass(timeClass, "nativeRawTime",
                                   bc_time_nativeGetRawTime);
        bc_DefineNativeMethodClass(timeClass, "nativeToString",
                                   bc_time_nativeToString);
        bc_DefineNativeMethodClass(timeClass, "nativeGetSecond",
                                   bc_time_nativeGetSecond);
        bc_DefineNativeMethodClass(timeClass, "nativeGetMinute",
                                   bc_time_nativeGetMinute);
        bc_DefineNativeMethodClass(timeClass, "nativeGetHour",
                                   bc_time_nativeGetHour);
        bc_DefineNativeMethodClass(timeClass, "nativeGetDay",
                                   bc_time_nativeGetDay);
        bc_DefineNativeMethodClass(timeClass, "nativeGetYear",
                                   bc_time_nativeGetYear);
        bc_DefineNativeMethodClass(timeClass, "nativeGetDayOfWeek",
                                   bc_time_nativeGetDayOfWeek);
        bc_DefineNativeMethodClass(timeClass, "nativeGetDayOfYear",
                                   bc_time_nativeGetDayOfYear);
}

bc_Type* bc_GetTimeType() {
        bc_Namespace* unsafe = bc_GetUnsafeNamespace();
        return bc_FindTypeFromNamespace(unsafe, bc_InternString("Time"));
}
// private
static void bc_time_nativeGetRawTime(bc_Method* parent, bc_Frame* fr,
                                     bc_Enviroment* env) {
        time_t tref;
        time(&tref);
        // FIXME:long型を導入する
        bc_PushVector(fr->ValueStack, bc_NewLong(tref));
}

static void bc_time_nativeToString(bc_Method* parent, bc_Frame* fr,
                                   bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        int temp;
        bc_ResolveField(BC_TYPE2CLASS(bc_GetTimeType()),
                        bc_InternString("rawTime"), &temp);
        bc_Object* rawTime = (bc_Object*)bc_AtVector(self->Fields, temp);
        bc_PushVector(fr->ValueStack,
                      bc_NewString(ctime(&(((bc_Long*)rawTime)->Value))));
}

static void bc_time_nativeGetSecond(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env) {
        bc_Object* rawTime = bc_AtVector(fr->VariableTable, 1);
        bc_PushVector(
            fr->ValueStack,
            bc_GetIntObject(localtime(&(((bc_Long*)rawTime)->Value))->tm_sec));
}

static void bc_time_nativeGetMinute(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env) {
        bc_Object* rawTime = bc_AtVector(fr->VariableTable, 1);
        bc_PushVector(
            fr->ValueStack,
            bc_GetIntObject(localtime(&(((bc_Long*)rawTime)->Value))->tm_min));
}

static void bc_time_nativeGetHour(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env) {
        bc_Object* rawTime = bc_AtVector(fr->VariableTable, 1);
        bc_PushVector(
            fr->ValueStack,
            bc_GetIntObject(localtime(&(((bc_Long*)rawTime)->Value))->tm_hour));
}

static void bc_time_nativeGetDay(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env) {
        bc_Object* rawTime = bc_AtVector(fr->VariableTable, 1);
        bc_PushVector(
            fr->ValueStack,
            bc_GetIntObject(localtime(&(((bc_Long*)rawTime)->Value))->tm_mday));
}

static void bc_time_nativeGetYear(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env) {
        bc_Object* rawTime = bc_AtVector(fr->VariableTable, 1);
        bc_PushVector(
            fr->ValueStack,
            bc_GetIntObject(localtime(&(((bc_Long*)rawTime)->Value))->tm_year));
}

static void bc_time_nativeGetDayOfWeek(bc_Method* parent, bc_Frame* fr,
                                       bc_Enviroment* env) {
        bc_Object* rawTime = bc_AtVector(fr->VariableTable, 1);
        bc_PushVector(
            fr->ValueStack,
            bc_GetIntObject(localtime(&(((bc_Long*)rawTime)->Value))->tm_wday));
}

static void bc_time_nativeGetDayOfYear(bc_Method* parent, bc_Frame* fr,
                                       bc_Enviroment* env) {
        bc_Object* rawTime = bc_AtVector(fr->VariableTable, 1);
        bc_PushVector(
            fr->ValueStack,
            bc_GetIntObject(localtime(&(((bc_Long*)rawTime)->Value))->tm_yday));
}
