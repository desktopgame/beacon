#include "cl.h"
#include "env/script_context.h"
#include "vm/eval.h"
#include "test.h"
#include <stdio.h>

int bc_TestCmd(int argc, char* argv[]) {
#if defined(DEBUG) || (defined(_MSC_VER) && defined(DEBUG))
	OpenScriptContext();
	int ret = bc_RunTest(argc, argv);
	CloseScriptContext();
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

int bc_DumpILCmd(const char* filename){
	OpenScriptContext();
	int ret = bc_EvalIL(filename);
	CloseScriptContext();
	return ret;
}

int bc_DumpOpCodeCmd(const char* filename) {
	OpenScriptContext();
	int ret = bc_EvalOp(filename);
	CloseScriptContext();
	return ret;
}

int bc_RunCmd(const char* filename) {
	OpenScriptContext();
	int ret = bc_EvalFile(filename);
	CloseScriptContext();
	return ret;
}