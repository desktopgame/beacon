#include "cl.h"
#include "env/script_context.h"
#include "vm/eval.h"
#include "test.h"
#include <stdio.h>

int cl_test(int argc, char* argv[]) {
#if defined(DEBUG) || (defined(_MSC_VER) && defined(_DEBUG))
	script_context_open();
	int ret = test_run(argc, argv);
	script_context_close();
	return ret;
#else
	fprintf(stderr, "not supported operation\n");
	abort();
	return 0;
#endif
}

int cl_bug(int argc, char* argv[]) {
	script_context_open();
	int ret = 0;
	script_context_close();
	return ret;
}

int cl_ast(const char* filename) {
	int ret = EvalAST(filename);
	return ret;
}

int cl_il(const char* filename){
	script_context_open();
	int ret = EvalIL(filename);
	script_context_close();
	return ret;
}

int cl_op(const char* filename) {
	script_context_open();
	int ret = EvalOp(filename);
	script_context_close();
	return ret;
}

int cl_run(const char* filename) {
	script_context_open();
	int ret = EvalFile(filename);
	script_context_close();
	return ret;
}