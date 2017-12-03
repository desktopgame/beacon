#include "cmd.h"
#include "text.h"

void cmd_dump(int argc, const char* const argv[]) {
	printf("--- args ---");
	text_putline();
	for (int i = 0; i < argc; i++) {
		char* e = argv[i];
		printf("argv[%d] = %s", i, argv[i]);
		text_putline();
	}
	text_putline();
}