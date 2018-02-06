#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util/cmd.h"
#include "util/io.h"
#include "util/text.h"
#include "env/script_context.h"
#include "test.h"
#include "util/string_buffer.h"
#include "util/logger.h"

#ifdef _MSC_VER
#include <crtdbg.h>
#endif

void _start(int argc, char* argv[]) {
#ifdef _MSC_VER
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(103280);
#endif
	sg_lopen();
	sg_lset_enabled(false);
	script_context_open();
	//cmd_dump(argc, argv);

}

void _end(int argc, char* argv[]) {
	//system("cls");
	script_context_close();
	sg_lclose();
}

int main(int argc, char* argv[]) {
	text_printf("aa %s", "vvv");

	char block[100];
	text_sprintf(block, 100, "Hoge %d", 100);
	text_printf("\n%s", block);

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