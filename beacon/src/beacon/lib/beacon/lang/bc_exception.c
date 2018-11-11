#include "bc_exception.h"
#include "../../bc_library_interface.h"
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
static void bc_exception_nativeInit(Method* parent, Frame* fr, Enviroment* env);

void InitException() {
	Namespace* lang = GetLangNamespace();
	Type* exceptionType = NewPreloadClass(InternString("Exception"));
	Class* exceptionClass = TYPE2CLASS(exceptionType);
	AddTypeNamespace(lang, exceptionType);
	DefineNativeMethodClass(exceptionClass, "nativeInit", bc_exception_nativeInit);
}

Type* GetExceptionType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Exception"));
}
//private
static void bc_exception_nativeInit(Method* parent, Frame* fr, Enviroment* env) {
	Namespace* lang = GetLangNamespace();
	Class* stackTraceElementClass = FindClassFromNamespace(lang, InternString("StackTraceElement"));
	Class* exceptionClass = FindClassFromNamespace(lang, InternString("Exception"));
	Object* self= (Object*)AtVector(fr->VariableTable, 0);
	//FXIME:???
	Heap* h = GetHeap();
	h->CollectBlocking++;
	//スタックトレースを作成する
	Frame* temp = fr;
	Vector* stackTraceElementVec = NewVector();
	char* lfilename = NULL;
	int llineno = -1;
	do {
		//実行中のインストラクションの行番号を取得
		LineRange* lr = FindLineRange(temp->ContextRef->LineRangeTable, temp->PC);
		int lineno = lr == NULL ? -1 : lr->Lineno;
		//assert(lineno != -1);
		//直前の表示と同じ
		if(lfilename != NULL &&
		   !strcmp(temp->ContextRef->ContextRef->FileName, lfilename) &&
		   llineno == lineno) {
			temp = temp->Parent;
			continue;
		}
		//スタックトレースを作成
		//assert(lineno >= 0);
		Vector* args = NewVector();
		PushVector(args, NewString(temp->ContextRef->ContextRef->FileName));
		PushVector(args, NewInteger(lineno));
		Object* trace = NewInstanceClass(
			stackTraceElementClass,
			//ilctx,
			fr,
			args,
			NULL
		);
		DeleteVector(args, VectorDeleterOfNull);
		PushVector(stackTraceElementVec, trace);
		temp = temp->Parent;
		//今回の表示情報を記録
		if(temp != NULL) {
			lfilename = temp->ContextRef->ContextRef->FileName;
			llineno = lineno;
		}
	} while (temp != NULL);
	//配列へ
	Object* arr = DynamicNewArray(stackTraceElementClass->Parent->GenericSelf, stackTraceElementVec->Length, fr);
	for (int i = 0; i < stackTraceElementVec->Length; i++) {
		SetElementAt(arr, i, AtVector(stackTraceElementVec, i));
	}
	//Exception#stackTraceをここで初期化する
	int tempi = 0;
	Field* stackTraceF = FindFieldClass(exceptionClass, InternString("stackTrace"), &tempi);
	AssignVector(self->Fields, tempi, arr);
	DeleteVector(stackTraceElementVec, VectorDeleterOfNull);
	h->CollectBlocking--;
}