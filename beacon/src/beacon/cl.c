#include "cl.h"
#include "env/script_context.h"
#include "vm/eval.h"
#include "test.h"
#include <stdio.h>

int cl_test(int argc, char* argv[]) {
#if defined(DEBUG) || (defined(_MSC_VER) && defined(_DEBUG))
	OpenScriptContext();
	int ret = test_run(argc, argv);
	CloseScriptContext();
	return ret;
#else
	fprintf(stderr, "not supported operation\n");
	abort();
	return 0;
#endif
}

int cl_bug(int argc, char* argv[]) {
	OpenScriptContext();
	int ret = 0;
	CloseScriptContext();
	return ret;
}

int cl_ast(const char* filename) {
	int ret = EvalAST(filename);
	return ret;
}

int cl_il(const char* filename){
	OpenScriptContext();
	int ret = EvalIL(filename);
	CloseScriptContext();
	return ret;
}

int cl_op(const char* filename) {
	OpenScriptContext();
	int ret = EvalOp(filename);
	CloseScriptContext();
	return ret;
}

int cl_run(const char* filename) {
	OpenScriptContext();
	int ret = EvalFile(filename);
	CloseScriptContext();
	return ret;
}