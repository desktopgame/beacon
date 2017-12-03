#include "test.h"
#include "util/list.h"
#include "util/stack.h"
#include "ast/ast.h"

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
