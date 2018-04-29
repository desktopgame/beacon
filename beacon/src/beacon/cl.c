#include "cl.h"
#include "env/script_context.h"
#include "vm/eval.h"
#include "test.h"

int cl_test(int argc, char* argv[]) {
	script_context_set_bootstrap(false);
	script_context_open();
	script_context_set_bootstrap(true);

	int ret = test_run(argc, argv);
	script_context_close();
	return ret;
}

int cl_ast(const char* filename) {
	script_context_open();
	int ret = eval_ast(filename);
	script_context_close();
	return ret;
}

int cl_il(const char* filename){
	script_context_open();
	int ret = eval_il(filename);
	script_context_close();
	return ret;
}

int cl_run(const char* filename) {
	script_context_open();
	int ret = eval_file(filename);
	script_context_close();
	return ret;
}