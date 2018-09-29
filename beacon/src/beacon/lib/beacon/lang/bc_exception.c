#include "bc_exception.h"
#include "../../bc_library_impl.h"
#include "../../../env/constructor.h"
#include "../../../env/class_loader.h"
#include "../../../vm/line_range.h"
#include "../../../vm/frame.h"
#include "../../../env/field.h"
#include "../../../env/heap.h"
#include "bc_array.h"
#include <string.h>
#include <assert.h>
//proto
static void bc_exception_nativeInit(method* parent, frame* fr, enviroment* env);

void bc_exception_init() {
	namespace_* lang = namespace_lang();
	type* exceptionType = class_new_preload(string_pool_intern("Exception"));
	class_* exceptionClass = TYPE2CLASS(exceptionType);
	namespace_add_type(lang, exceptionType);
	class_define_native_method(exceptionClass, "nativeInit", bc_exception_nativeInit);
}

type* bc_exception_type() {
	namespace_* lang = namespace_lang();
	return namespace_get_type(lang, string_pool_intern("Exception"));
}
//private
static void bc_exception_nativeInit(method* parent, frame* fr, enviroment* env) {
	namespace_* lang = namespace_lang();
	class_* stackTraceElementClass = namespace_get_class(lang, string_pool_intern("StackTraceElement"));
	class_* exceptionClass = namespace_get_class(lang, string_pool_intern("Exception"));
	object* self= (object*)AtVector(fr->ref_stack, 0);
	//FXIME:???
	heap* h = heap_get();
	h->collect_blocking++;
	//スタックトレースを作成する
	frame* temp = fr;
	Vector* stackTraceElementVec = NewVector();
	char* lfilename = NULL;
	int llineno = -1;
	do {
		//実行中のインストラクションの行番号を取得
		line_range* lr = line_range_find(temp->context_ref->line_range_vec, temp->pc);
		int lineno = lr == NULL ? -1 : lr->lineno;
		//assert(lineno != -1);
		//直前の表示と同じ
		if(lfilename != NULL &&
		   !strcmp(temp->context_ref->context_ref->filename, lfilename) &&
		   llineno == lineno) {
			temp = temp->parent;
			continue;
		}
		//スタックトレースを作成
		//assert(lineno >= 0);
		Vector* args = NewVector();
		PushVector(args, object_string_new(temp->context_ref->context_ref->filename));
		PushVector(args, object_int_new(lineno));
		object* trace = class_new_instance(
			stackTraceElementClass,
			//ilctx,
			fr,
			args,
			NULL
		);
		DeleteVector(args, VectorDeleterOfNull);
		PushVector(stackTraceElementVec, trace);
		temp = temp->parent;
		//今回の表示情報を記録
		if(temp != NULL) {
			lfilename = temp->context_ref->context_ref->filename;
			llineno = lineno;
		}
	} while (temp != NULL);
	//配列へ
	object* arr = bc_array_new(stackTraceElementClass->parent->generic_self, stackTraceElementVec->length, fr);
	for (int i = 0; i < stackTraceElementVec->length; i++) {
		bc_array_set(arr, i, AtVector(stackTraceElementVec, i));
	}
	//Exception#stackTraceをここで初期化する
	int tempi = 0;
	field* stackTraceF = class_find_field(exceptionClass, string_pool_intern("stackTrace"), &tempi);
	AssignVector(self->u.field_vec, tempi, arr);
	DeleteVector(stackTraceElementVec, VectorDeleterOfNull);
	h->collect_blocking--;
}