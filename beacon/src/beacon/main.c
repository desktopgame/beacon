#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "il/il_print_layout.h"
#include "util/cmd.h"
#include "util/io.h"
#include "util/text.h"
#include "env/script_context.h"
#include "test.h"
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

int main(int argc, char* argv[]) {
	mem_set_trace(true);

	script_context_set_bootstrap(false);
	script_context_open();
	script_context_set_bootstrap(true);

	int ret = run_script(argc, argv);
	script_context_close();
	mem_dump();
	mem_destroy();
	return ret;
}