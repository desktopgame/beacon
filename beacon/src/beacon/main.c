#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "il/il_print_layout.h"
#include "env/script_context.h"
#include "test.h"
#include "cl.h"
#include "debug.h"
#include "util/mem.h"
#include "util/text.h"
#include "util/io.h"
#include "util/file_entry.h"

/**
 * コマンドライン文字列を解析します.
 * @param argc
 * @param argv
 * @return
 */
int main_cl(int argc, char *argv[]) {
	struct option longopts[] = {
		{ "test", no_argument, NULL, 't' },
		{ "ast", required_argument, NULL, 'a' },
		{ "il", required_argument, NULL, 'i' },
		{ "run", required_argument, NULL, 'r' },
		{ "op", required_argument, NULL, 'o' },
		{ 0, 0, 0, 0 }
	};
	extern char *optarg;
	extern int optind, opterr;
	int opt = 0;
	int longindex = 0;
	while ((opt = getopt_long(argc, argv, "ta:i:r:o:", longopts, &longindex)) != -1) {
		switch(opt) {
			case 't':
				printf(":t :test\n");
				cl_test(argc, argv);
				break;
			case 'a':
				printf(":a :ast\n");
				cl_ast(optarg);
				break;
			case 'i':
				printf(":i :il\n");
				cl_il(optarg);
				break;
			case 'r':
				printf(":r :run\n");
				cl_run(optarg);
				break;
			case 'o':
				printf(":o :op\n");
				cl_op(optarg);
				break;
			default:
				printf("error! :%c :%c", opt, optopt);
				break;
		}
	}
}

int main(int argc, char *argv[]) {
	double a = 0;
	double b = 0;
	//先んじて設定を行っておく
	mem_set_trace(true);
	il_print_layout_hide(true);
	//コマンドライン引数を解析して実行
	int ret = main_cl(argc, argv);
	//設定を元に戻す
	mem_dump();
	mem_destroy();
	return ret;
}