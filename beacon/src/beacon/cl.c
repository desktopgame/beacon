#include "cl.h"
#include "env/script_context.h"
#include "vm/eval.h"
#include "test.h"
#include <stdio.h>

int TestCmd(int argc, char* argv[]) {
#if defined(DEBUG) || (defined(_MSC_VER) && defined(_DEBUG))
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
	int ret = EvalAST(filename);
	return ret;
}

int DumpILCmd(const char* filename){
	OpenScriptContext();
	int ret = EvalIL(filename);
	CloseScriptContext();
	return ret;
}

int DumpOpCodeCmd(const char* filename) {
	OpenScriptContext();
	int ret = EvalOp(filename);
	CloseScriptContext();
	return ret;
}

int RunCmd(const char* filename) {
	OpenScriptContext();
	int ret = EvalFile(filename);
	CloseScriptContext();
	return ret;
}