#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util/cmd.h"
#include "util/io.h"
#include "util/text.h"
#include "env/script_context.h"
#include "test.h"
#include "util/logger.h"

#ifdef _MSC_VER
#include <crtdbg.h>
#endif

int main(int argc, char* argv[]) {
#ifdef _MSC_VER
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(103280);
#endif
	sg_lopen();
	script_context_open();
	cmd_dump(argc, argv);
	test_vm();
//	test_namespace();
//	test_vector();
//	test_io2();
//	test_file_path();
//	test_tree_map();
//	char* c = io_read_text("main.signal");
//	printf("%s", c);
//	free(c);
	script_context_close();
	sg_lclose();
	return 0;
}