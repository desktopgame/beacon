#include "cl.h"
#include <stdio.h>
#include "env/script_context.h"
#include "test.h"
#include "vm/eval.h"

int bc_TestCmd(int argc, char* argv[]) {
#if defined(DEBUG) || (defined(_MSC_VER) && defined(DEBUG))
        bc_OpenScriptContext();
        int ret = bc_RunTest(argc, argv);
        bc_CloseScriptContext();
        return ret;
#else
        fprintf(stderr, "not supported operation\n");
        abort();
        return 0;
#endif
}

int bc_DumpASTCmd(const char* filename) {
        int ret = bc_EvalAST(filename);
        return ret;
}

int bc_DumpILCmd(const char* filename) {
        bc_OpenScriptContext();
        int ret = bc_EvalIL(filename);
        bc_CloseScriptContext();
        return ret;
}

int bc_DumpOpCodeCmd(const char* filename) {
        bc_OpenScriptContext();
        int ret = bc_EvalOp(filename);
        bc_CloseScriptContext();
        return ret;
}

int bc_RunCmd(const char* filename) {
        bc_OpenScriptContext();
        int ret = bc_EvalFile(filename);
        bc_CloseScriptContext();
        return ret;
}