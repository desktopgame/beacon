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
	script_context_open();
	//cmd_dump(argc, argv);

	bench_start();
}

void _end(int argc, char* argv[]) {
	bench_end("main", bench_simple);
	//system("cls");
	script_context_close();
	logger_close();

	mem_dump();
	mem_destroy();
	text_flush_trace();
}

int main(int argc, char* argv[]) {
	//test_preload();
	//整数リテラルをオブジェクトにラップ
	//オブジェクトにベクターを持たせて、
	//インデックスがクラスのそれと一致するように
	//定数プールにdouble型を入れられるように
	//test_vm();
	_start(argc, argv);
	test_cll();
//	test_vector3();
	_end(argc, argv);
	return 0;
}