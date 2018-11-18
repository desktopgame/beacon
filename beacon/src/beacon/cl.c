#include "cl.h"
#include "env/script_context.h"
#include "vm/eval.h"
#include "test.h"
#include <stdio.h>

int TestCmd(int argc, char* argv[]) {
#if defined(DEBUG) || (defined(_MSC_VER) && defined(DEBUG))
	OpenScriptContext();
	int ret = RunTest(argc, argv);
	CloseScriptContext();
	return ret;
#else
	fprintf(stderr, "not supported operation\n");
	abort();
	return 0;
#endif
}

int DumpASTCmd(const char* filename) {
	int ret = bc_EvalAST(filename);
	return ret;
}

int DumpILCmd(const char* filename){
	OpenScriptContext();
	int ret = bc_EvalIL(filename);
	CloseScriptContext();
	return ret;
}

int DumpOpCodeCmd(const char* filename) {
	OpenScriptContext();
	int ret = bc_EvalOp(filename);
	CloseScriptContext();
	return ret;
}

int RunCmd(const char* filename) {
	OpenScriptContext();
	int ret = bc_EvalFile(filename);
	CloseScriptContext();
	return ret;
}