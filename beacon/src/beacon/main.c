
#if defined(_MSC_VER)
#include "util/getopt.h"
#include <crtdbg.h> 
#else
#include <unistd.h>
#include <getopt.h>
#endif

#include <stdio.h>
#include <string.h>
#include "test.h"
#include "cl.h"
#include "il/il_print_layout.h"
#include "env/script_context.h"
#include "util/string_pool.h"
#include "util/mem.h"
#include "thread/native_thread.h"


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
	int ret = 0;
	while ((opt = getopt_long(argc, argv, "ta:i:r:o:", longopts, &longindex)) != -1) {
		switch(opt) {
			case 't':
				printf(":t :test\n");
				ret = TestCmd(argc, argv);
				break;
			case 'a':
				printf(":a :ast\n");
				ret = DumpASTCmd(optarg);
				break;
			case 'i':
				printf(":i :il\n");
				ret = DumpILCmd(optarg);
				break;
			case 'r':
				printf(":r :run\n");
				ret = RunCmd(optarg);
				break;
			case 'o':
				printf(":o :op\n");
				ret = DumpOpCodeCmd(optarg);
				break;
			default:
				printf("error! :%c :%c", opt, optopt);
				break;
		}
	}
	return ret;
}

int main(int argc, char *argv[]) {
#if defined(_MSC_VER) && defined(DEBUG)
	_CrtSetDbgFlag(
		/*
		_CRTDBG_DELAY_FREE_MEM_DF |
		_CRTDBG_CHECK_ALWAYS_DF |
		//*/
		_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF
	);
	//_CrtSetBreakAlloc(36862);
#endif
bc_InitMX();
	InitNativeThread();
	InitStringPool();
	HideILPrintLayout(true);
	//mem_break(16066);
	//コマンドライン引数を解析して実行
	int ret = main_cl(argc, argv);
	//設定を元に戻す
	//DumpStringPool(stdout);
	DestroyStringPool();
	DestroyNativeThread();
bc_DestroyMX();
#if defined(_MSC_VER) && defined(DEBUG)
	_CrtDumpMemoryLeaks();
#endif
	return ret;
}