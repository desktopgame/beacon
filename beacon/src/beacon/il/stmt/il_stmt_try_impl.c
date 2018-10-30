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
static void ILCatch_stmt_delete(void* item);
static void ILTry_catch_delete(void* item);

ILStatement* WrapILTry(ILTry* self) {
	ILStatement* ret = (ILStatement*)MEM_MALLOC(sizeof(ILStatement));
	ret->Type = ILSTMT_TRY_T;
	ret->Kind.Try = self;
	return ret;
}

ILTry* NewILTry() {
	ILTry* ret = (ILTry*)MEM_MALLOC(sizeof(ILTry));
	ret->Statements = NewVector();
	ret->Catches = NewVector();
	return ret;
}

ILCatch* NewILCatch(StringView namev) {
	ILCatch* ret = (ILCatch*)MEM_MALLOC(sizeof(ILCatch));
	ret->Name = namev;
	ret->GCache = NewGenericCache();
	ret->Statements = NewVector();
	return ret;
}

void GenerateILTry(ILTry* self, Enviroment* env, CallContext* cctx) {
	Label* try_end = AddLabelOpcodeBuf(env->Bytecode, -1);
	Label* catch_start = AddLabelOpcodeBuf(env->Bytecode, -1);
	AddOpcodeBuf(env->Bytecode, OP_TRY_ENTER);
	//ここでcatchの開始に飛ばしますが、
	//OP_TRY_ENTERからはこの部分はスキップされます。
	AddOpcodeBuf(env->Bytecode, OP_GOTO);
	AddOpcodeBuf(env->Bytecode, catch_start);
	//例外が発生するかもしれない
	//ステートメントの一覧
	for (int i = 0; i < self->Statements->Length; i++) {
		ILStatement* e = (ILStatement*)AtVector(self->Statements, i);
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
	for (int i = 0; i < self->Catches->Length; i++) {
		//例外を指定の名前でアクセス出来るように
		ILCatch* ilcatch = (ILCatch*)AtVector(self->Catches, i);
		GenericType* exgType = ResolveImportManager(NULL, ilcatch->GCache, cctx);
		int exIndex = EntrySymbolTable(env->Symboles, exgType, ilcatch->Name)->Index;
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
		for (int j = 0; j < ilcatch->Statements->Length; j++) {
			ILStatement* e = (ILStatement*)AtVector(ilcatch->Statements, j);
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

void GenerateILCatch(ILCatch* self, Enviroment* env, CallContext* cctx) {

}

void LoadILTry(ILTry* self, Enviroment* env, CallContext* cctx) {
	for(int i=0; i<self->Statements->Length; i++) {
		ILStatement* e = (ILStatement*)AtVector(self->Statements, i);
		LoadILStmt(e, env, cctx);
	}
	for(int i=0; i<self->Catches->Length; i++) {
		ILCatch* e = (ILCatch*)AtVector(self->Catches, i);
		LoadILCatch(e, env, cctx);
	}
}

void LoadILCatch(ILCatch* self, Enviroment* env, CallContext* cctx) {
	GenericType* exgType = ResolveImportManager(NULL, self->GCache, cctx);
	EntrySymbolTable(env->Symboles, exgType, self->Name);
	for(int i=0; i<self->Statements->Length; i++) {
		ILStatement* e = (ILStatement*)AtVector(self->Statements, i);
		LoadILStmt(e, env, cctx);
	}
}

void DeleteILCatch(ILCatch* self) {
	DeleteGenericCache(self->GCache);
	DeleteVector(self->Statements, ILCatch_stmt_delete);
	MEM_FREE(self);
}

void DeleteILTry(ILTry* self) {
	DeleteVector(self->Statements, ILCatch_stmt_delete);
	DeleteVector(self->Catches, ILTry_catch_delete);
	MEM_FREE(self);
}
//private
static void ILCatch_stmt_delete(void* item) {
	ILStatement* e = (ILStatement*)item;
	DeleteILStmt(e);
}

static void ILTry_catch_delete(void* item) {
	ILCatch* e = (ILCatch*)item;
	DeleteILCatch(e);
}