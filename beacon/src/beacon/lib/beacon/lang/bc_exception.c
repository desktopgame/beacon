#include "bc_exception.h"
#include "../../bc_library_impl.h"
#include "../../../env/constructor.h"
#include "../../../env/class_loader.h"
#include "../../../vm/line_range.h"
#include "../../../vm/frame.h"
#include "../../../env/field.h"
#include "../../../env/heap.h"
#include "bc_array.h"
//proto
static void bc_exception_nativeInit(method* parent, frame* fr, enviroment* env);

void bc_exception_init() {
	namespace_* lang = namespace_lang();
	class_* excClass = class_new_preload("Exception");
	namespace_add_type(lang, type_wrap_class(excClass));
	class_define_native_method(excClass, "nativeInit", bc_exception_nativeInit);
}
//private
static void bc_exception_nativeInit(method* parent, frame* fr, enviroment* env) {
	namespace_* lang = namespace_lang();
	class_* stackTraceElementClass = namespace_get_class(lang, "StackTraceElement");
	class_* exceptionClass = namespace_get_class(lang, "Exception");
	object* self= (object*)vector_at(fr->ref_stack, 0);
	heap* h = heap_get();
	h->collect_blocking++;
	//スタックトレースを作成する
	frame* temp = fr;
	vector* stackTraceElementVec = vector_new();
	do {
		//実行中のインストラクションの行番号を取得
		line_range* lr = line_range_find(temp->context_ref->line_rangeVec, temp->pc);
		//スタックトレースを作成
		object* trace = class_new_rinstance(
			stackTraceElementClass,
			fr,
			2,
			object_string_new(temp->context_ref->context_ref->filename),
			object_int_new(lr == NULL ? -1 : lr->lineno)
		);
		vector_push(stackTraceElementVec, trace);
		temp = temp->parent;
	} while (temp != NULL);
	//配列へ
	object* arr = bc_array_new(stackTraceElementVec->length, fr);
	for (int i = 0; i < stackTraceElementVec->length; i++) {
		bc_array_set(arr, i, vector_at(stackTraceElementVec, i));
	}
	//Exception#stackTraceをここで初期化する
	int tempi = 0;
	field* stackTraceF = class_find_field(exceptionClass, "stackTrace", &tempi);
	vector_assign(self->u.field_vec, tempi, arr);
	vector_delete(stackTraceElementVec, vector_deleter_null);
	h->collect_blocking--;
}