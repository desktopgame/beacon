#include "il_stmt_try_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../vm/symbol_entry.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../env/generic_type.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"
#include <stdio.h>

//proto
static void ILStatement_catch_stmt_delete(void* item);
static void ILStatement_try_catch_delete(void* item);

ILStatement* WrapILTry(ILStatement_try* self) {
	ILStatement* ret = (ILStatement*)MEM_MALLOC(sizeof(ILStatement));
	ret->type = ILSTMT_TRY_T;
	ret->u.try_ = self;
	return ret;
}

ILStatement_try* NewILTry() {
	ILStatement_try* ret = (ILStatement_try*)MEM_MALLOC(sizeof(ILStatement_try));
	ret->statement_list = NewVector();
	ret->catch_list = NewVector();
	return ret;
}

ILStatement_catch* NewILCatch(StringView namev) {
	ILStatement_catch* ret = (ILStatement_catch*)MEM_MALLOC(sizeof(ILStatement_catch));
	ret->namev = namev;
	ret->fqcn = NewGenericCache();
	ret->statement_list = NewVector();
	return ret;
}

void GenerateILTry(ILStatement_try* self, Enviroment* env, CallContext* cctx) {
	Label* try_end = AddLabelOpcodeBuf(env->Bytecode, -1);
	Label* catch_start = AddLabelOpcodeBuf(env->Bytecode, -1);
	AddOpcodeBuf(env->Bytecode, OP_TRY_ENTER);
	//ここでcatchの開始に飛ばしますが、
	//OP_TRY_ENTERからはこの部分はスキップされます。
	AddOpcodeBuf(env->Bytecode, OP_GOTO);
	AddOpcodeBuf(env->Bytecode, catch_start);
	//例外が発生するかもしれない
	//ステートメントの一覧
	for (int i = 0; i < self->statement_list->Length; i++) {
		ILStatement* e = (ILStatement*)AtVector(self->statement_list, i);
		GenerateILStmt(e, env, cctx);
	}
	AddOpcodeBuf(env->Bytecode, OP_TRY_EXIT);
	//例外が発生しなかったならcatchをスキップ
	AddOpcodeBuf(env->Bytecode, OP_GOTO);
	AddOpcodeBuf(env->Bytecode, try_end);
	//例外を捕捉したらここに飛ぶように
	catch_start->Cursor = AddNOPOpcodeBuf(env->Bytecode);
	//全てのcatch節に対して
	Label* nextCause = NULL;
	for (int i = 0; i < self->catch_list->Length; i++) {
		//例外を指定の名前でアクセス出来るように
		ILStatement_catch* ilcatch = (ILStatement_catch*)AtVector(self->catch_list, i);
		GenericType* exgType = ResolveImportManager(NULL, ilcatch->fqcn, cctx);
		int exIndex = EntrySymbolTable(env->Symboles, exgType, ilcatch->namev)->Index;
		//直前のケースのジャンプ先をここに
		if (nextCause != NULL) {
			int head = AddNOPOpcodeBuf(env->Bytecode);
			nextCause->Cursor = head;
		}
		nextCause = AddLabelOpcodeBuf(env->Bytecode, -1);
		//現在の例外と catch節 の型に互換性があるなら続行
		AddOpcodeBuf(env->Bytecode, OP_HEXCEPTION);;
		AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
		GenerateGenericType(exgType, env);
		AddOpcodeBuf(env->Bytecode, OP_INSTANCEOF);
		//互換性がないので次のケースへ
		AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_FALSE);
		AddOpcodeBuf(env->Bytecode, nextCause);
		//指定の名前で例外を宣言
		AddOpcodeBuf(env->Bytecode, OP_HEXCEPTION);
		AddOpcodeBuf(env->Bytecode, OP_STORE);
		AddOpcodeBuf(env->Bytecode, exIndex);
		//catchの内側のステートメントを生成
		for (int j = 0; j < ilcatch->statement_list->Length; j++) {
			ILStatement* e = (ILStatement*)AtVector(ilcatch->statement_list, j);
			GenerateILStmt(e, env, cctx);
		}
		//catchされたので、
		//例外フラグをクリアする
		AddOpcodeBuf(env->Bytecode, OP_TRY_CLEAR);
		//最後のcatchの後ろへ
		AddOpcodeBuf(env->Bytecode, OP_GOTO);
		AddOpcodeBuf(env->Bytecode, try_end);
	}
	//try-catchの最後
	nextCause->Cursor = AddNOPOpcodeBuf(env->Bytecode);
	//どのcatchにも引っかからなかった
	AddOpcodeBuf(env->Bytecode, OP_TRY_EXIT);
	//catchを処理したらここに
	try_end->Cursor = AddNOPOpcodeBuf(env->Bytecode);
}

void GenerateILCatch(ILStatement_catch* self, Enviroment* env, CallContext* cctx) {

}

void LoadILTry(ILStatement_try* self, Enviroment* env, CallContext* cctx) {
	for(int i=0; i<self->statement_list->Length; i++) {
		ILStatement* e = (ILStatement*)AtVector(self->statement_list, i);
		LoadILStmt(e, env, cctx);
	}
	for(int i=0; i<self->catch_list->Length; i++) {
		ILStatement_catch* e = (ILStatement_catch*)AtVector(self->catch_list, i);
		LoadILCatch(e, env, cctx);
	}
}

void LoadILCatch(ILStatement_catch* self, Enviroment* env, CallContext* cctx) {
	GenericType* exgType = ResolveImportManager(NULL, self->fqcn, cctx);
	EntrySymbolTable(env->Symboles, exgType, self->namev);
	for(int i=0; i<self->statement_list->Length; i++) {
		ILStatement* e = (ILStatement*)AtVector(self->statement_list, i);
		LoadILStmt(e, env, cctx);
	}
}

void DeleteILCatch(ILStatement_catch* self) {
	DeleteGenericCache(self->fqcn);
	DeleteVector(self->statement_list, ILStatement_catch_stmt_delete);
	MEM_FREE(self);
}

void DeleteILTry(ILStatement_try* self) {
	DeleteVector(self->statement_list, ILStatement_catch_stmt_delete);
	DeleteVector(self->catch_list, ILStatement_try_catch_delete);
	MEM_FREE(self);
}
//private
static void ILStatement_catch_stmt_delete(void* item) {
	ILStatement* e = (ILStatement*)item;
	DeleteILStmt(e);
}

static void ILStatement_try_catch_delete(void* item) {
	ILStatement_catch* e = (ILStatement_catch*)item;
	DeleteILCatch(e);
}