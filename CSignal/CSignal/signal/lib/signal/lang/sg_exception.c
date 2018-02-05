#include "sg_exception.h"
#include "../../sg_library_impl.h"
#include "../../../env/constructor.h"
#include "../../../env/class_loader.h"
#include "../../../vm/line_range.h"
#include "../../../env/field.h"
#include "sg_array.h"
//proto
static void sg_exception_nativeInit(method* parent, vm* vm, enviroment* env);

void sg_exception_init() {
	namespace_* lang = namespace_lang();
	class_* excClass = class_new_preload("Exception");
	namespace_add_type(lang, type_wrap_class(excClass));
	class_define_native_method(excClass, "nativeInit", sg_exception_nativeInit);
}
//private
static void sg_exception_nativeInit(method* parent, vm* vmc, enviroment* env) {
	namespace_* lang = namespace_lang();
	class_* stackTraceElementClass = namespace_get_class(lang, "StackTraceElement");
	object* self = (object*)vector_at(vmc->ref_stack, 0);
	//スタックトレースを作成する
	vm* temp = vmc;
	vector* stackTraceElementVec = vector_new();
	do {
		//実行中のインストラクションの行番号を取得
		line_range* lr = line_range_find(temp->contextRef->line_rangeVec, temp->pc);
		//スタックトレースを作成
		object* trace = class_new_rinstance(
			stackTraceElementClass,
			vmc,
			2,
			object_string_new(temp->contextRef->context_cll->filename),
			object_int_new(lr->lineno)
		);
		vector_push(stackTraceElementVec, trace);
		temp = temp->parent;
	} while (temp != NULL);
	//配列へ
	object* arr = sg_array_new(stackTraceElementVec->length, vmc);
	for (int i = 0; i < stackTraceElementVec->length; i++) {
		sg_array_set(arr, i, vector_at(stackTraceElementVec, i));
	}
	//Exception#stackTraceをここで初期化する
	int tempi = 0;
	field* stackTraceF = class_find_field(stackTraceElementClass, "stackTrace", &tempi);
	vector_assign(self->u.field_vec, temp, arr);

}