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
#include "../../env/compile_context.h"
#include <stdio.h>

//proto
static void il_stmt_catch_stmt_delete(void* item);
static void il_stmt_try_catch_delete(void* item);

il_stmt* il_stmt_wrap_try(il_stmt_try* self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt_try));
	ret->type = ilstmt_try;
	ret->u.try_ = self;
	return ret;
}

il_stmt_try* il_stmt_try_new() {
	il_stmt_try* ret = (il_stmt_try*)MEM_MALLOC(sizeof(il_stmt_try));
	ret->statement_list = vector_new();
	ret->catch_list = vector_new();
	return ret;
}

il_stmt_catch* il_stmt_catch_new(string_view namev) {
	il_stmt_catch* ret = (il_stmt_catch*)MEM_MALLOC(sizeof(il_stmt_catch));
	ret->namev = namev;
	ret->fqcn = generic_cache_new();
	ret->statement_list = vector_new();
	return ret;
}

void il_stmt_try_dump(il_stmt_try* self, int depth) {
	text_putindent(depth);
	text_printf("try");
	text_putline();
	for(int i=0; i<self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_list, i);
		il_stmt_dump(e, depth + 1);
	}
	for(int i=0; i<self->catch_list->length; i++) {
		il_stmt_catch* e = (il_stmt_catch*)vector_at(self->catch_list, i);
		il_stmt_catch_dump(e, depth + 1);
	}
}

void il_stmt_catch_dump(il_stmt_catch* self, int depth) {
	text_putindent(depth);
	text_printf("catch(");
	generic_cache_print(self->fqcn);
	text_printf(" %s)", string_pool_ref2str(self->namev));
	text_putline();
	for(int i=0; i<self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_list, i);
		il_stmt_dump(e, depth + 1);
	}
}

void il_stmt_try_generate(il_stmt_try* self, enviroment* env) {
	label* try_end = opcode_buf_label(env->buf, -1);
	label* catch_start = opcode_buf_label(env->buf, -1);
	opcode_buf_add(env->buf, op_try_enter);
	//ここでcatchの開始に飛ばしますが、
	//op_try_enterからはこの部分はスキップされます。
	opcode_buf_add(env->buf, op_goto);
	opcode_buf_add(env->buf, catch_start);
	//例外が発生するかもしれない
	//ステートメントの一覧
	for (int i = 0; i < self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_list, i);
		il_stmt_generate(e, env);
	}
	opcode_buf_add(env->buf, op_try_exit);
	//例外が発生しなかったならcatchをスキップ
	opcode_buf_add(env->buf, op_goto);
	opcode_buf_add(env->buf, try_end);
	//例外を捕捉したらここに飛ぶように
	catch_start->cursor = opcode_buf_nop(env->buf);
	//全てのcatch節に対して
	label* nextCause = NULL;
	for (int i = 0; i < self->catch_list->length; i++) {
		//例外を指定の名前でアクセス出来るように
		il_stmt_catch* ilcatch = (il_stmt_catch*)vector_at(self->catch_list, i);
		generic_type* exgType = import_manager_resolve(ccget_class_loader()->import_manager, cc_namespace(), ilcatch->fqcn);
		int exIndex = symbol_table_entry(env->sym_table, exgType, ilcatch->namev)->index;
		//直前のケースのジャンプ先をここに
		if (nextCause != NULL) {
			int head = opcode_buf_nop(env->buf);
			nextCause->cursor = head;
		}
		nextCause = opcode_buf_label(env->buf, -1);
		//現在の例外と catch節 の型に互換性があるなら続行
		opcode_buf_add(env->buf, op_hexception);;
		opcode_buf_add(env->buf, op_generic_add);
		generic_type_generate(exgType, env);
		opcode_buf_add(env->buf, op_instanceof);
		//互換性がないので次のケースへ
		opcode_buf_add(env->buf, op_goto_if_false);
		opcode_buf_add(env->buf, nextCause);
		//指定の名前で例外を宣言
		opcode_buf_add(env->buf, op_hexception);
		opcode_buf_add(env->buf, op_store);
		opcode_buf_add(env->buf, exIndex);
		//catchの内側のステートメントを生成
		for (int j = 0; j < ilcatch->statement_list->length; j++) {
			il_stmt* e = (il_stmt*)vector_at(ilcatch->statement_list, j);
			il_stmt_generate(e, env);
		}
		//catchされたので、
		//例外フラグをクリアする
		opcode_buf_add(env->buf, op_try_clear);
		//最後のcatchの後ろへ
		opcode_buf_add(env->buf, op_goto);
		opcode_buf_add(env->buf, try_end);
	}
	//try-catchの最後
	nextCause->cursor = opcode_buf_nop(env->buf);
	//どのcatchにも引っかからなかった
	opcode_buf_add(env->buf, op_try_exit);
	//catchを処理したらここに
	try_end->cursor = opcode_buf_nop(env->buf);
}

void il_stmt_catch_generate(il_stmt_catch* self, enviroment* env) {

}

void il_stmt_try_load(il_stmt_try* self, enviroment* env) {
	for(int i=0; i<self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_list, i);
		il_stmt_load(e, env);
	}
	for(int i=0; i<self->catch_list->length; i++) {
		il_stmt_catch* e = (il_stmt_catch*)vector_at(self->catch_list, i);
		il_stmt_catch_load(e, env);
	}
}

void il_stmt_catch_load(il_stmt_catch* self, enviroment* env) {
	generic_type* exgType = import_manager_resolve(ccget_class_loader()->import_manager, cc_namespace(), self->fqcn);
	symbol_table_entry(env->sym_table, exgType, self->namev);
	for(int i=0; i<self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_list, i);
		il_stmt_load(e, env);
	}
}

void il_stmt_catch_delete(il_stmt_catch* self) {
	generic_cache_delete(self->fqcn);
	vector_delete(self->statement_list, il_stmt_catch_stmt_delete);
	MEM_FREE(self);
}

void il_stmt_try_delete(il_stmt_try* self) {
	vector_delete(self->statement_list, il_stmt_catch_stmt_delete);
	vector_delete(self->catch_list, il_stmt_try_catch_delete);
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