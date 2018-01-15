#include "dump.h"
#include <stdlib.h>
#include "../../parse/parser.h"

void cmd_tool_dump(dump_option * option) {
	if (option->filename == NULL) {
		text_putline();
		return;
	}
	//パース
	parser* p = parser_parse_from_file(option->filename);
	if (p->fail) {
		return;
	}
	system("cls");
	//対象を出力
	printf("対象: %s", option->filename);
	text_putline();
	//オプションを出力
	printf("オプション: ");
	if (option->ast) { printf("ast "); }
	if (option->il) { printf("il "); }
	if (option->sg) { printf("sg "); }
	text_putline();
	ast_print_tree(p->root);
	parser_pop();
}
