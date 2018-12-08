
#if defined(_MSC_VER)
#include <crtdbg.h>
#include "util/getopt.h"
#else
#include <getopt.h>
#include <unistd.h>
#endif

#include <glib.h>
#include <stdio.h>
#include <string.h>
#include "cl.h"
#include "env/script_context.h"
#include "il/il_print_layout.h"
#include "test.h"
#include "thread/native_thread.h"
#include "util/mem.h"
#include "util/string_pool.h"

/**
 * コマンドライン文字列を解析します.
 * @param argc
 * @param argv
 * @return
 */
int main_cl(int argc, char *argv[]) {
        struct option longopts[] = {{"test", no_argument, NULL, 't'},
                                    {"run", required_argument, NULL, 'r'},
                                    {0, 0, 0, 0}};
        extern char *optarg;
        extern int optind, opterr;
        int opt = 0;
        int longindex = 0;
        int ret = 0;
        while ((opt = getopt_long(argc, argv, "tr:", longopts, &longindex)) !=
               -1) {
                switch (opt) {
                        case 't':
                                printf(":t :test\n");
                                ret = bc_TestCmd(argc, argv);
                                break;
                        case 'r':
                                printf(":r :run\n");
                                ret = bc_RunCmd(optarg);
                                break;
                        default:
                                printf("error! :%c :%c\n", opt, optopt);
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
            _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        //_CrtSetBreakAlloc(36862);
#endif
        bc_InitMX();
        bc_InitNativeThread();
        bc_InitStringPool();
        bc_HideILPrintLayout(true);
        // mem_break(16066);
        //コマンドライン引数を解析して実行
        int ret = main_cl(argc, argv);
        //設定を元に戻す
        // DumpStringPool(stdout);
        bc_DestroyStringPool();
        bc_DestroyNativeThread();
        bc_DestroyMX();
#if defined(_MSC_VER) && defined(DEBUG)
        _CrtDumpMemoryLeaks();
#endif
        return ret;
}