#include "eval.h"
#include <assert.h>
#include <string.h>
#include "../env/class_loader.h"
#include "../env/heap.h"
#include "../env/script_context.h"
#include "../error.h"
#include "../parse/parser.h"
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/text.h"
#include "../vm/script_thread.h"
#include "../vm/vm.h"

// proto
static bool eval_top_from_cll(bc_ClassLoader* cll, bc_AST* aOpt);

bool bc_EvalFile(const char* filename) {
        bc_ClassLoader* cll =
            bc_NewClassLoader(filename, CONTENT_ENTRY_POINT_T);
        return eval_top_from_cll(cll, NULL);
}

bool bc_EvalString(const char* source) {
        bc_Parser* p = bc_ParseString(source);
        if (p->Result != PARSE_COMPLETE_T) {
                bc_Panic(BCERROR_PARSE_T, p->ErrorMessage);
                bc_DestroyParser(p);
                return false;
        }
        bc_ClassLoader* cll = bc_NewClassLoader("", CONTENT_ENTRY_POINT_T);
        bc_AST* a = bc_ReleaseParserAST(p);
        bc_DestroyParser(p);
        return eval_top_from_cll(cll, a);
}

// private
static bool eval_top_from_cll(bc_ClassLoader* cll, bc_AST* aOpt) {
        bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
        if (aOpt == NULL) {
                bc_LoadClassLoader(cll);
        } else {
                bc_LoadPassASTClassLoader(cll, aOpt);
        }
        bc_ScriptContext* sctx = bc_GetCurrentScriptContext();
        bc_GetUniqueTrueObject(sctx);
        bc_GetUniqueFalseObject(sctx);
        bc_GetUniqueNullObject(sctx);
        //実行
        bc_Frame* fr = bc_NewFrame();
        bc_SetScriptThreadFrameRef(bc_GetCurrentScriptThread(), fr);
        //エラーによって中断された場合のため、ここで戻す
        bc_Heap* he = bc_GetHeap();
        he->AcceptBlocking = 0;
#if defined(DEBUG)
        bc_Printfln("start");
#endif
        if (!bc_GetLastPanic()) {
                bc_ExecuteVM(fr, cll->Env);
        }
        if (fr->IsTerminate) {
                bc_Panic(BCERROR_GENERIC_T, "unexpected terminate");
        }
        bc_CatchVM(fr);
        bc_ReleaseScriptThreadFrameRef(bc_GetCurrentScriptThread());
        bc_DeleteFrame(fr);
        bc_CollectHeap(bc_GetHeap());

        bool ret = bc_GetLastPanic();
        bc_DeleteClassLoader(cll);
        return ret;
}