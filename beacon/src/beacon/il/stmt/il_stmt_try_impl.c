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
static void il_stmt_catch_stmt_delete(void* item);
static void il_stmt_try_catch_delete(void* item);

il_stmt* il_stmt_wrap_try(il_stmt_try* self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt));
	ret->type = ILSTMT_TRY_T;
	ret->u.try_ = self;
	return ret;
}

il_stmt_try* il_stmt_try_new() {
	il_stmt_try* ret = (il_stmt_try*)MEM_MALLOC(sizeof(il_stmt_try));
	ret->statement_list = NewVector();
	ret->catch_list = NewVector();
	return ret;
}

il_stmt_catch* il_stmt_catch_new(string_view namev) {
	il_stmt_catch* ret = (il_stmt_catch*)MEM_MALLOC(sizeof(il_stmt_catch));
	ret->namev = namev;
	ret->fqcn = generic_cache_new();
	ret->statement_list = NewVector();
	return ret;
}

void il_stmt_try_generate(il_stmt_try* self, enviroment* env, call_context* cctx) {
	label* try_end = AddLabelOpcodeBuf(env->buf, -1);
	label* catch_start = AddLabelOpcodeBuf(env->buf, -1);
	AddOpcodeBuf(env->buf, OP_TRY_ENTER);
	//ここでcatchの開始に飛ばしますが、
	//OP_TRY_ENTERからはこの部分はスキップされます。
	AddOpcodeBuf(env->buf, OP_GOTO);
	AddOpcodeBuf(env->buf, catch_start);
	//例外が発生するかもしれない
	//ステートメントの一覧
	for (int i = 0; i < self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)AtVector(self->statement_list, i);
		il_stmt_generate(e, env, cctx);
	}
	AddOpcodeBuf(env->buf, OP_TRY_EXIT);
	//例外が発生しなかったならcatchをスキップ
	AddOpcodeBuf(env->buf, OP_GOTO);
	AddOpcodeBuf(env->buf, try_end);
	//例外を捕捉したらここに飛ぶように
	catch_start->cursor = AddNOPOpcodeBuf(env->buf);
	//全てのcatch節に対して
	label* nextCause = NULL;
	for (int i = 0; i < self->catch_list->length; i++) {
		//例外を指定の名前でアクセス出来るように
		il_stmt_catch* ilcatch = (il_stmt_catch*)AtVector(self->catch_list, i);
		generic_type* exgType = import_manager_resolve(NULL, ilcatch->fqcn, cctx);
		int exIndex = EntrySymbolTable(env->sym_table, exgType, ilcatch->namev)->index;
		//直前のケースのジャンプ先をここに
		if (nextCause != NULL) {
			int head = AddNOPOpcodeBuf(env->buf);
			nextCause->cursor = head;
		}
		nextCause = AddLabelOpcodeBuf(env->buf, -1);
		//現在の例外と catch節 の型に互換性があるなら続行
		AddOpcodeBuf(env->buf, OP_HEXCEPTION);;
		AddOpcodeBuf(env->buf, OP_GENERIC_ADD);
		generic_type_generate(exgType, env);
		AddOpcodeBuf(env->buf, OP_INSTANCEOF);
		//互換性がないので次のケースへ
		AddOpcodeBuf(env->buf, OP_GOTO_if_false);
		AddOpcodeBuf(env->buf, nextCause);
		//指定の名前で例外を宣言
		AddOpcodeBuf(env->buf, OP_HEXCEPTION);
		AddOpcodeBuf(env->buf, OP_STORE);
		AddOpcodeBuf(env->buf, exIndex);
		//catchの内側のステートメントを生成
		for (int j = 0; j < ilcatch->statement_list->length; j++) {
			il_stmt* e = (il_stmt*)AtVector(ilcatch->statement_list, j);
			il_stmt_generate(e, env, cctx);
		}
		//catchされたので、
		//例外フラグをクリアする
		AddOpcodeBuf(env->buf, OP_TRY_CLEAR);
		//最後のcatchの後ろへ
		AddOpcodeBuf(env->buf, OP_GOTO);
		AddOpcodeBuf(env->buf, try_end);
	}
	//try-catchの最後
	nextCause->cursor = AddNOPOpcodeBuf(env->buf);
	//どのcatchにも引っかからなかった
	AddOpcodeBuf(env->buf, OP_TRY_EXIT);
	//catchを処理したらここに
	try_end->cursor = AddNOPOpcodeBuf(env->buf);
}

void il_stmt_catch_generate(il_stmt_catch* self, enviroment* env, call_context* cctx) {

}

void il_stmt_try_load(il_stmt_try* self, enviroment* env, call_context* cctx) {
	for(int i=0; i<self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)AtVector(self->statement_list, i);
		il_stmt_load(e, env, cctx);
	}
	for(int i=0; i<self->catch_list->length; i++) {
		il_stmt_catch* e = (il_stmt_catch*)AtVector(self->catch_list, i);
		il_stmt_catch_load(e, env, cctx);
	}
}

void il_stmt_catch_load(il_stmt_catch* self, enviroment* env, call_context* cctx) {
	generic_type* exgType = import_manager_resolve(NULL, self->fqcn, cctx);
	EntrySymbolTable(env->sym_table, exgType, self->namev);
	for(int i=0; i<self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)AtVector(self->statement_list, i);
		il_stmt_load(e, env, cctx);
	}
}

void il_stmt_catch_delete(il_stmt_catch* self) {
	generic_cache_delete(self->fqcn);
	DeleteVector(self->statement_list, il_stmt_catch_stmt_delete);
	MEM_FREE(self);
}

void il_stmt_try_delete(il_stmt_try* self) {
	DeleteVector(self->statement_list, il_stmt_catch_stmt_delete);
	DeleteVector(self->catch_list, il_stmt_try_catch_delete);
	MEM_FREE(self);
}
//private
static void il_stmt_catch_stmt_delete(void* item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}

static void il_stmt_try_catch_delete(void* item) {
	il_stmt_catch* e = (il_stmt_catch*)item;
	il_stmt_catch_delete(e);
}