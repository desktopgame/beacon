#include "il_stmt_try_impl.h"
#include <stdio.h>
#include "../../env/class_loader.h"
#include "../../env/generic_type.h"
#include "../../env/import_manager.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../vm/symbol_entry.h"

// proto
static void ILCatch_stmt_delete(void* item);
static void ILTry_catch_delete(void* item);

bc_ILStatement* bc_WrapILTry(bc_ILTry* self) {
        bc_ILStatement* ret =
            (bc_ILStatement*)MEM_MALLOC(sizeof(bc_ILStatement));
        ret->Type = ILSTMT_TRY_T;
        ret->Kind.Try = self;
        return ret;
}

bc_ILTry* bc_NewILTry() {
        bc_ILTry* ret = (bc_ILTry*)MEM_MALLOC(sizeof(bc_ILTry));
        ret->Statements = bc_NewVector();
        ret->Catches = bc_NewVector();
        return ret;
}

bc_ILCatch* bc_NewILCatch(bc_StringView namev) {
        bc_ILCatch* ret = (bc_ILCatch*)MEM_MALLOC(sizeof(bc_ILCatch));
        ret->Name = namev;
        ret->GCache = bc_NewGenericCache();
        ret->Statements = bc_NewVector();
        return ret;
}

void bc_GenerateILTry(bc_ILTry* self, bc_Enviroment* env,
                      bc_CallContext* cctx) {
        bc_Label* try_end = bc_AddLabelOpcodeBuf(env->Bytecode, -1);
        bc_Label* catch_start = bc_AddLabelOpcodeBuf(env->Bytecode, -1);
        bc_AddOpcodeBuf(env->Bytecode, OP_TRY_ENTER);
        //ここでcatchの開始に飛ばしますが、
        // OP_TRY_ENTERからはこの部分はスキップされます。
        bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
        bc_AddOpcodeBuf(env->Bytecode, catch_start);
        //例外が発生するかもしれない
        //ステートメントの一覧
        for (int i = 0; i < self->Statements->Length; i++) {
                bc_ILStatement* e =
                    (bc_ILStatement*)bc_AtVector(self->Statements, i);
                bc_GenerateILStmt(e, env, cctx);
        }
        bc_AddOpcodeBuf(env->Bytecode, OP_TRY_EXIT);
        //例外が発生しなかったならcatchをスキップ
        bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
        bc_AddOpcodeBuf(env->Bytecode, try_end);
        //例外を捕捉したらここに飛ぶように
        catch_start->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
        //全てのcatch節に対して
        bc_Label* nextCause = NULL;
        for (int i = 0; i < self->Catches->Length; i++) {
                //例外を指定の名前でアクセス出来るように
                bc_ILCatch* ilcatch =
                    (bc_ILCatch*)bc_AtVector(self->Catches, i);
                bc_GenericType* exgType =
                    bc_ResolveImportManager(NULL, ilcatch->GCache, cctx);
                int exIndex =
                    bc_EntrySymbolTable(env->Symboles, exgType, ilcatch->Name)
                        ->Index;
                //直前のケースのジャンプ先をここに
                if (nextCause != NULL) {
                        int head = bc_AddNOPOpcodeBuf(env->Bytecode);
                        nextCause->Cursor = head;
                }
                nextCause = bc_AddLabelOpcodeBuf(env->Bytecode, -1);
                //現在の例外と catch節 の型に互換性があるなら続行
                bc_AddOpcodeBuf(env->Bytecode, OP_HEXCEPTION);
                ;
                bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
                bc_GenerateGenericType(exgType, env);
                bc_AddOpcodeBuf(env->Bytecode, OP_INSTANCEOF);
                //互換性がないので次のケースへ
                bc_AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_FALSE);
                bc_AddOpcodeBuf(env->Bytecode, nextCause);
                //指定の名前で例外を宣言
                bc_AddOpcodeBuf(env->Bytecode, OP_HEXCEPTION);
                bc_AddOpcodeBuf(env->Bytecode, OP_STORE);
                bc_AddOpcodeBuf(env->Bytecode, exIndex);
                // catchの内側のステートメントを生成
                for (int j = 0; j < ilcatch->Statements->Length; j++) {
                        bc_ILStatement* e = (bc_ILStatement*)bc_AtVector(
                            ilcatch->Statements, j);
                        bc_GenerateILStmt(e, env, cctx);
                }
                // catchされたので、
                //例外フラグをクリアする
                bc_AddOpcodeBuf(env->Bytecode, OP_TRY_CLEAR);
                //最後のcatchの後ろへ
                bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
                bc_AddOpcodeBuf(env->Bytecode, try_end);
        }
        // try-catchの最後
        nextCause->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
        //どのcatchにも引っかからなかった
        bc_AddOpcodeBuf(env->Bytecode, OP_TRY_EXIT);
        // catchを処理したらここに
        try_end->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
}

void bc_GenerateILCatch(bc_ILCatch* self, bc_Enviroment* env,
                        bc_CallContext* cctx) {}

void bc_LoadILTry(bc_ILTry* self, bc_Enviroment* env, bc_CallContext* cctx) {
        for (int i = 0; i < self->Statements->Length; i++) {
                bc_ILStatement* e =
                    (bc_ILStatement*)bc_AtVector(self->Statements, i);
                bc_LoadILStmt(e, env, cctx);
        }
        for (int i = 0; i < self->Catches->Length; i++) {
                bc_ILCatch* e = (bc_ILCatch*)bc_AtVector(self->Catches, i);
                bc_LoadILCatch(e, env, cctx);
        }
}

void bc_LoadILCatch(bc_ILCatch* self, bc_Enviroment* env,
                    bc_CallContext* cctx) {
        bc_GenericType* exgType =
            bc_ResolveImportManager(NULL, self->GCache, cctx);
        bc_EntrySymbolTable(env->Symboles, exgType, self->Name);
        for (int i = 0; i < self->Statements->Length; i++) {
                bc_ILStatement* e =
                    (bc_ILStatement*)bc_AtVector(self->Statements, i);
                bc_LoadILStmt(e, env, cctx);
        }
}

void bc_DeleteILCatch(bc_ILCatch* self) {
        bc_DeleteGenericCache(self->GCache);
        bc_DeleteVector(self->Statements, ILCatch_stmt_delete);
        MEM_FREE(self);
}

void bc_DeleteILTry(bc_ILTry* self) {
        bc_DeleteVector(self->Statements, ILCatch_stmt_delete);
        bc_DeleteVector(self->Catches, ILTry_catch_delete);
        MEM_FREE(self);
}
// private
static void ILCatch_stmt_delete(void* item) {
        bc_ILStatement* e = (bc_ILStatement*)item;
        bc_DeleteILStmt(e);
}

static void ILTry_catch_delete(void* item) {
        bc_ILCatch* e = (bc_ILCatch*)item;
        bc_DeleteILCatch(e);
}