#include "cl.h"
#include <stdio.h>
#include "env/script_context.h"
#include "error.h"
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
        bc_FatalError();
        return 0;
#endif
}

int bc_RunCmd(const char* filename) {
        bc_OpenScriptContext();
        int ret = bc_EvalFile(filename);
        bc_CloseScriptContext();
        return ret;
}