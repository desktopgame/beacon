#include "bc_locale.h"
#include "../../../../env/namespace.h"
#include "../../../../env/type_impl.h"
#include "../../../../util/string_buffer.h"
#include "../../../../util/text.h"
#include "../../../bc_library_impl.h"
#include "../bc_string.h"
#include <assert.h>
#include <locale.h>

static void bc_locale_nativeSetLocale(method* parent, frame* fr, enviroment* env);
static void bc_locale_nativeGetDecimalPoint(method* parent, frame* fr, enviroment* env);
static void bc_locale_nativeGetThousandsSep(method* parent, frame* fr, enviroment* env);
static void bc_locale_nativeGetIntCurrSymbol(method* parent, frame* fr, enviroment* env);
static void bc_locale_nativeGetCurrencySymbol(method* parent, frame* fr, enviroment* env);
static void bc_locale_nativeGetMonDecimalPoint(method* parent, frame* fr, enviroment* env);
static void bc_locale_nativeGetMonThousandsSep(method* parent, frame* fr, enviroment* env);
static void bc_locale_nativeGetPositiveSign(method* parent, frame* fr, enviroment* env);
static void bc_locale_nativeGetNegativeSign(method* parent, frame* fr, enviroment* env);
static void bc_locale_nativeGetIntFracDigits(method* parent, frame* fr, enviroment* env);
static void bc_locale_nativeGetFracDigits(method* parent, frame* fr, enviroment* env);

void bc_locale_init() {
	namespace_* unsafe = namespace_unsafe();
	type* localeType = class_new_preload(string_pool_intern("Locale"));
	class_* localeClass = TYPE2CLASS(localeType);
	namespace_add_type(unsafe, localeType);
	class_define_native_method(localeClass, "nativeSetLocale", bc_locale_nativeSetLocale);
	class_define_native_method(localeClass, "nativeGetDecimalPoint", bc_locale_nativeGetDecimalPoint);
	class_define_native_method(localeClass, "nativeGetThousandsSep", bc_locale_nativeGetThousandsSep);
	class_define_native_method(localeClass, "nativeGetIntCurrSymbol", bc_locale_nativeGetIntCurrSymbol);
	class_define_native_method(localeClass, "nativeGetCurrencySymbol", bc_locale_nativeGetCurrencySymbol);
	class_define_native_method(localeClass, "nativeGetMonDecimalPoint", bc_locale_nativeGetMonDecimalPoint);
	class_define_native_method(localeClass, "nativeGetMonThousandsSep", bc_locale_nativeGetMonThousandsSep);
	class_define_native_method(localeClass, "nativeGetPositiveSign", bc_locale_nativeGetPositiveSign);
	class_define_native_method(localeClass, "nativeGetNegativeSign", bc_locale_nativeGetNegativeSign);
	class_define_native_method(localeClass, "nativeGetIntFracDigits", bc_locale_nativeGetIntFracDigits);
	class_define_native_method(localeClass, "nativeGetFracDigits", bc_locale_nativeGetFracDigits);
}

type* bc_locale_type() {
	namespace_* unsafe = namespace_unsafe();
	return namespace_get_type(unsafe, string_pool_intern("Locale"));
}
//private
static void bc_locale_nativeSetLocale(method* parent, frame* fr, enviroment* env) {
	object* categoryObj = vector_at(fr->ref_stack, 1);
	object* localeObj = vector_at(fr->ref_stack, 2);
	int category = OBJ2INT(categoryObj);
	switch(category) {
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
	const char* locale = bc_string_raw(localeObj)->text;
	assert(setlocale(category, locale) != NULL);
}

static void bc_locale_nativeGetDecimalPoint(method* parent, frame* fr, enviroment* env) {
	struct lconv* lc = localeconv();
	vector_push(fr->value_stack, object_string_T_new(lc->decimal_point));
}

static void bc_locale_nativeGetThousandsSep(method* parent, frame* fr, enviroment* env) {
	struct lconv* lc = localeconv();
	vector_push(fr->value_stack, object_string_T_new(lc->thousands_sep));
}

static void bc_locale_nativeGetIntCurrSymbol(method* parent, frame* fr, enviroment* env) {
	struct lconv* lc = localeconv();
	vector_push(fr->value_stack, object_string_T_new(lc->int_curr_symbol));
}

static void bc_locale_nativeGetCurrencySymbol(method* parent, frame* fr, enviroment* env) {
	struct lconv* lc = localeconv();
	vector_push(fr->value_stack, object_string_T_new(lc->currency_symbol));
}

static void bc_locale_nativeGetMonDecimalPoint(method* parent, frame* fr, enviroment* env) {
	struct lconv* lc = localeconv();
	vector_push(fr->value_stack, object_string_T_new(lc->mon_decimal_point));
}

static void bc_locale_nativeGetMonThousandsSep(method* parent, frame* fr, enviroment* env) {
	struct lconv* lc = localeconv();
	vector_push(fr->value_stack, object_string_T_new(lc->mon_thousands_sep));
}

static void bc_locale_nativeGetPositiveSign(method* parent, frame* fr, enviroment* env) {
	struct lconv* lc = localeconv();
	vector_push(fr->value_stack, object_string_T_new(lc->positive_sign));
}

static void bc_locale_nativeGetNegativeSign(method* parent, frame* fr, enviroment* env) {
	struct lconv* lc = localeconv();
	vector_push(fr->value_stack, object_string_T_new(lc->negative_sign));
}

static void bc_locale_nativeGetIntFracDigits(method* parent, frame* fr, enviroment* env) {
	struct lconv* lc = localeconv();
	vector_push(fr->value_stack, object_int_T_get(lc->int_frac_digits));
}

static void bc_locale_nativeGetFracDigits(method* parent, frame* fr, enviroment* env) {
	struct lconv* lc = localeconv();
	vector_push(fr->value_stack, object_int_T_get(lc->frac_digits));
}
