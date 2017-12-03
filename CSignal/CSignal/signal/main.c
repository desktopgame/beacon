#include <stdlib.h>
#include <stdio.h>
#include "util/cmd.h"
#include "util/io.h"
#include "test.h"

#ifdef _MSC_VER
#include <crtdbg.h>
#endif

int main(int argc, char* argv[]) {
#ifdef _MSC_VER
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(103280);
#endif
	cmd_dump(argc, argv);
	test_list();
//	char* c = io_read_text("main.signal");
//	printf("%s", c);
//	free(c);
	return 0;
}