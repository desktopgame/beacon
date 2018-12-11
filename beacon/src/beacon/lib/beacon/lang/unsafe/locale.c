#include "locale.h"
#include <assert.h>
#include <locale.h>
#include "../../../../env/TYPE_IMPL.h"
#include "../../../../env/namespace.h"
#include "../../../../util/string_buffer.h"
#include "../../../../util/text.h"
#include "../../../bc_library_impl.h"
#include "../string.h"

static void bc_locale_nativeSetLocale(bc_Method* parent, bc_Frame* fr,
                                      bc_Enviroment* env);
static void bc_locale_nativeGetDecimalPoint(bc_Method* parent, bc_Frame* fr,
                                            bc_Enviroment* env);
static void bc_locale_nativeGetThousandsSep(bc_Method* parent, bc_Frame* fr,
                                            bc_Enviroment* env);
static void bc_locale_nativeGetIntCurrSymbol(bc_Method* parent, bc_Frame* fr,
                                             bc_Enviroment* env);
static void bc_locale_nativeGetCurrencySymbol(bc_Method* parent, bc_Frame* fr,
                                              bc_Enviroment* env);
static void bc_locale_nativeGetMonDecimalPoint(bc_Method* parent, bc_Frame* fr,
                                               bc_Enviroment* env);
static void bc_locale_nativeGetMonThousandsSep(bc_Method* parent, bc_Frame* fr,
                                               bc_Enviroment* env);
static void bc_locale_nativeGetPositiveSign(bc_Method* parent, bc_Frame* fr,
                                            bc_Enviroment* env);
static void bc_locale_nativeGetNegativeSign(bc_Method* parent, bc_Frame* fr,
                                            bc_Enviroment* env);
static void bc_locale_nativeGetIntFracDigits(bc_Method* parent, bc_Frame* fr,
                                             bc_Enviroment* env);
static void bc_locale_nativeGetFracDigits(bc_Method* parent, bc_Frame* fr,
                                          bc_Enviroment* env);

void bc_InitLocaleType() {
        bc_Namespace* unsafe = bc_GetUnsafeNamespace(NULL);
        bc_Type* localeType = bc_NewPreloadClass(bc_InternString("Locale"));
        bc_Class* localeClass = BC_TYPE2CLASS(localeType);
        bc_AddTypeNamespace(unsafe, localeType);
        bc_DefineNativeMethodClass(localeClass, "nativeSetLocale",
                                   bc_locale_nativeSetLocale);
        bc_DefineNativeMethodClass(localeClass, "nativeGetDecimalPoint",
                                   bc_locale_nativeGetDecimalPoint);
        bc_DefineNativeMethodClass(localeClass, "nativeGetThousandsSep",
                                   bc_locale_nativeGetThousandsSep);
        bc_DefineNativeMethodClass(localeClass, "nativeGetIntCurrSymbol",
                                   bc_locale_nativeGetIntCurrSymbol);
        bc_DefineNativeMethodClass(localeClass, "nativeGetCurrencySymbol",
                                   bc_locale_nativeGetCurrencySymbol);
        bc_DefineNativeMethodClass(localeClass, "nativeGetMonDecimalPoint",
                                   bc_locale_nativeGetMonDecimalPoint);
        bc_DefineNativeMethodClass(localeClass, "nativeGetMonThousandsSep",
                                   bc_locale_nativeGetMonThousandsSep);
        bc_DefineNativeMethodClass(localeClass, "nativeGetPositiveSign",
                                   bc_locale_nativeGetPositiveSign);
        bc_DefineNativeMethodClass(localeClass, "nativeGetNegativeSign",
                                   bc_locale_nativeGetNegativeSign);
        bc_DefineNativeMethodClass(localeClass, "nativeGetIntFracDigits",
                                   bc_locale_nativeGetIntFracDigits);
        bc_DefineNativeMethodClass(localeClass, "nativeGetFracDigits",
                                   bc_locale_nativeGetFracDigits);
}

bc_Type* bc_GetLocaleType() {
        bc_Namespace* unsafe = bc_GetUnsafeNamespace(NULL);
        return bc_FindTypeFromNamespace(unsafe, bc_InternString("Locale"));
}
// private
static void bc_locale_nativeSetLocale(bc_Method* parent, bc_Frame* fr,
                                      bc_Enviroment* env) {
        bc_Object* categoryObj = bc_AtVector(fr->VariableTable, 1);
        bc_Object* localeObj = bc_AtVector(fr->VariableTable, 2);
        int category = bc_ObjectToInt(categoryObj);
        switch (category) {
                case 0:
                        category = LC_ALL;
                        break;
                case 1:
                        category = LC_COLLATE;
                        break;
                case 2:
                        category = LC_CTYPE;
                        break;
                case 3:
                        category = LC_MONETARY;
                        break;
                case 4:
                        category = LC_NUMERIC;
                        break;
                case 5:
                        category = LC_TIME;
                        break;
        }
        const char* locale = bc_GetRawString(localeObj)->Text;
        assert(setlocale(category, locale) != NULL);
}

static void bc_locale_nativeGetDecimalPoint(bc_Method* parent, bc_Frame* fr,
                                            bc_Enviroment* env) {
        struct lconv* lc = localeconv();
        bc_PushVector(fr->ValueStack, bc_NewString(lc->decimal_point));
}

static void bc_locale_nativeGetThousandsSep(bc_Method* parent, bc_Frame* fr,
                                            bc_Enviroment* env) {
        struct lconv* lc = localeconv();
        bc_PushVector(fr->ValueStack, bc_NewString(lc->thousands_sep));
}

static void bc_locale_nativeGetIntCurrSymbol(bc_Method* parent, bc_Frame* fr,
                                             bc_Enviroment* env) {
        struct lconv* lc = localeconv();
        bc_PushVector(fr->ValueStack, bc_NewString(lc->int_curr_symbol));
}

static void bc_locale_nativeGetCurrencySymbol(bc_Method* parent, bc_Frame* fr,
                                              bc_Enviroment* env) {
        struct lconv* lc = localeconv();
        bc_PushVector(fr->ValueStack, bc_NewString(lc->currency_symbol));
}

static void bc_locale_nativeGetMonDecimalPoint(bc_Method* parent, bc_Frame* fr,
                                               bc_Enviroment* env) {
        struct lconv* lc = localeconv();
        bc_PushVector(fr->ValueStack, bc_NewString(lc->mon_decimal_point));
}

static void bc_locale_nativeGetMonThousandsSep(bc_Method* parent, bc_Frame* fr,
                                               bc_Enviroment* env) {
        struct lconv* lc = localeconv();
        bc_PushVector(fr->ValueStack, bc_NewString(lc->mon_thousands_sep));
}

static void bc_locale_nativeGetPositiveSign(bc_Method* parent, bc_Frame* fr,
                                            bc_Enviroment* env) {
        struct lconv* lc = localeconv();
        bc_PushVector(fr->ValueStack, bc_NewString(lc->positive_sign));
}

static void bc_locale_nativeGetNegativeSign(bc_Method* parent, bc_Frame* fr,
                                            bc_Enviroment* env) {
        struct lconv* lc = localeconv();
        bc_PushVector(fr->ValueStack, bc_NewString(lc->negative_sign));
}

static void bc_locale_nativeGetIntFracDigits(bc_Method* parent, bc_Frame* fr,
                                             bc_Enviroment* env) {
        struct lconv* lc = localeconv();
        bc_PushVector(fr->ValueStack, bc_GetIntObject(lc->int_frac_digits));
}

static void bc_locale_nativeGetFracDigits(bc_Method* parent, bc_Frame* fr,
                                          bc_Enviroment* env) {
        struct lconv* lc = localeconv();
        bc_PushVector(fr->ValueStack, bc_GetIntObject(lc->frac_digits));
}
