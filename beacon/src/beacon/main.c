#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "il/il_print_layout.h"
#include "util/cmd.h"
#include "util/io.h"
#include "util/text.h"
#include "env/script_context.h"
#include "env/namespace.h"
#include "env/fqcn_cache.h"
#include "env/generic_cache.h"
#include "test.h"
#include "vm/eval.h"
#include "util/string_buffer.h"
#include "util/logger.h"
#include "util/mem.h"
#include "util/bench_mark.h"

void _start(int argc, char* argv[]) {
	il_print_layout_hide(true);

	text_set_trace(true);
	mem_set_trace(true);
	//mem_break(311);
	logger_open();
	logger_set_enabled(!true);
	//cmd_dump(argc, argv);

	bench_start();
}

void _end(int argc, char* argv[]) {
	bench_end("main", bench_simple);
	//system("cls");
	logger_close();

	mem_dump();
	mem_destroy();
	text_flush_trace();
}

int run_script(int argc, char* argv[]) {
#if defined(DEBUG)
	if(!test_run()) {
		return 0;
	}
#endif
	//script_context_bootstrap(script_context_get_current());
	//_start(argc, argv);
	//TODO:ここにbeacon起動コード
	//_end(argc, argv);
	return 0;
}

int _main(int argc, char* argv[]) {
	mem_set_trace(true);
//	mem_break(466);
	logger_set_enabled(false);
	bool test = false;
	int ret = 1;

	if(test) {
		script_context_set_bootstrap(false);
		script_context_open();
		script_context_set_bootstrap(true);

		ret = run_script(argc, argv);
		script_context_close();
	} else {
		script_context_open();
		script_context* ctx = eval_push();
		eval_top_from_file("main.signal");
		eval_pop(ctx);
		script_context_close();
		ret = 0;
	}
	mem_dump();
	mem_destroy();
	return ret;
}

int main(int argc, char* argv[]) {
	generic_cache* cc = generic_cache_new();
	return _main(argc, argv);
}