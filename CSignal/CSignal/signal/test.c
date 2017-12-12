#include "test.h"
#include "util/list.h"
#include "util/stack.h"
#include "util/tree_map.h"
#include "util/io.h"
#include "util/file_path.h"
#include "ast/ast.h"
#include "parse/parser.h"
#include "env/namespace.h"
#include "env/class_loader.h"
#include <stdio.h>

void test_stack(void) {
	stack* st = stack_new();
	for (int i = 1; i < 4; i++) {
		printf("%d\n", i * 10);
		stack_push(st, (stack_item)(i * 10));
	}
	printf("pop\n");
	while (!stack_empty(st)) {
		printf("%d ", stack_empty(st));
		int i = (int)stack_pop(st);
		printf("%d", i);
		printf(" %d\n", stack_empty(st));
	}
	stack_delete(st, stack_deleter_null);
}

void test_list(void) {
	list* li = list_new();
	for (int i = 1; i < 4; i++) {
		printf("%d\n", i * 10);
		list_add(li, (stack_item)(i * 10));
	}
	printf("at\n");
	for (int i = 0; i < 3; i++) {
		printf("%d\n", (int)list_at(li, i));
	}
	list_delete(li, list_deleter_null);
}

void test_ast(void) {
	ast* a = ast_new(ast_add_assign);
	ast_push(a, ast_new(ast_add));
	ast_push(a, ast_new(ast_sub));
	ast_push(a, ast_new(ast_mul));
	ast_push(a, ast_new(ast_div));
	ast_push(a, ast_new(ast_mod));

	ast* b = ast_new(ast_bit_and);
	ast_push(b, ast_new(ast_add));
	ast_push(b, ast_new(ast_sub));
	ast_push(a, b);

	ast_print_tree(a);
	ast_delete(a);
}

void test_ast2(void) {
	char* text = io_read_text("main.signal");
	parser* p = parser_parse_from_source(text);
	ast_print_tree(p->root);
	parser_pop();
}

void test_tree_map(void) {
	tree_map* m = tree_map_new();
	tree_map_put(m, "KeyA", 10);
	tree_map_put(m, "KeyB", 5);
	tree_map_put(m, "KeyC", 2);
	tree_map_put(m, "KeyXC", 99);
	tree_map_put(m, "KeyYB", 98);
	tree_map_put(m, "KeyZA", 97);
	char* arr[] = {
		"KeyA",
		"KeyB",
		"KeyC",
		"KeyXC",
		"KeyYB",
		"KeyZA",
	};
	int arrCount = 6;
	for (int i = 0; i < arrCount; i++) {
		printf("%s = %d\n", arr[i], (int)tree_map_get(m, arr[i]));
	}
	tree_map_delete(m, tree_map_deleter_null);
}

void test_namespace(void) {
	namespace_* signal = namespace_create_at_root("signal");
	namespace_* lang = namespace_add_namespace(signal, "lang");
	namespace_* text = namespace_add_namespace(lang, "text");
	namespace_* io = namespace_add_namespace(lang, "io");
	namespace_dump();
}

void test_io(void) {
	io_new_file("io_file.text");
}

void test_io2(void) {
	io_write_text("io_file.text", "hello, world!\n c java");
}

void test_file_path(void) {
	file_path* root = file_path_new("root");
	file_path* sub = file_path_append(root, "sub");
	file_path* yy = file_path_append(sub, "yy");
	file_path_dump(yy, PATH_SEPARATOR_CHAR);
	file_path_delete(yy);
	file_path_delete(sub);
	file_path_delete(root);

	file_path* t = file_path_parse("root_xxxx_yyyy_eeee/sub_subsub_beemy_/yyzzzzzzzzzzzzzzzzz", '/');
	file_path_dump(t, PATH_SEPARATOR_CHAR);
	file_path_delete_tree(t);
}

void test_cll(void) {
	class_loader* cll = class_loader_new_entry_point("main.signal");
	class_loader_load(cll);
	class_loader_delete(cll);
}
