#include "test.h"
#include "ast/ast.h"
#include "env/namespace.h"
#include "env/class_loader.h"
#include "parse/parser.h"
#include "vm/vm.h"
#include "util/list.h"
#include "util/stack.h"
#include "util/tree_map.h"
#include "util/io.h"
#include "util/text.h"
#include "util/file_path.h"
#include "util/vector.h"
#include <stdio.h>
#include <stdlib.h>

//proto
static void person_free(vector_item item);

void test_stack(void) {
#if defined(_MSC_VER)
	stack* st = stack_new();
	for (int i = 1; i < 4; i++) {
		printf("%d\n", i * 10);
		stack_push(st, (stack_item)(i * 10));
	}
	printf("pop\n");
	while (!stack_empty(st)) {
		//FIXME:macではここがコンパイル出来ない
		printf("%d ", stack_empty(st));
		int i = (int)stack_pop(st);
		printf("%d", i);
		printf(" %d\n", stack_empty(st));
	}
	stack_delete(st, stack_deleter_null);
#endif
}

void test_list(void) {
#if defined(_MSC_VER)
	list* li = list_new();
	for (int i = 1; i < 4; i++) {
		printf("%d\n", i * 10);
		list_add(li, (stack_item)(i * 10));
	}
	printf("at\n");
	for (int i = 0; i < 3; i++) {
		//FIXME:macではここがコンパイル出来ない
		printf("%d\n", (int)list_at(li, i));
	}
	list_delete(li, list_deleter_null);
#endif
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
#if defined(_MSC_VER)
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
		//FIXME:macではここがコンパイル出来ない
		printf("%s = %d\n", arr[i], (int)tree_map_get(m, arr[i]));
	}
	tree_map_delete(m, tree_map_deleter_null);
#endif
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
#if defined(_MSC_VER)
	class_loader* cll = class_loader_new_entry_point("main.signal");
#else
	class_loader* cll = class_loader_new_entry_point("../../main.signal");
#endif
	class_loader_load(cll);
	class_loader_delete(cll);
	system("cls");
	namespace_dump();
}

void test_struct(void) {
	OBJ* o = (OBJ*)malloc(sizeof(OBJ) * 10);
	for (int i = 0; i < 10; i++) {
		o[i].index = i;
	}
	for (int i = 0; i < 10; i++) {
		printf("index %d", (o + i)->index);
	}
	free(o);
}

void test_vector(void) {
	vector* v = vector_new();
	for (int i = 0; i < 10; i++) {
		vector_push(v, i);
	}
	for (int i = 0; i < v->length; i++) {
		int e = (int)vector_at(v, i);
		printf("vector[%d] = %d\n", i, e);
	}
	vector_delete(v, vector_deleter_null);
	printf("\n");

	vector* v2 = vector_new();
	for (int i = 0; i < 20; i++) {
		PERSON* p = (PERSON*)malloc(sizeof(PERSON));
		char buff[100];
		int x = sprintf_s(buff, 100, "name %d", i);
		p->name = text_strdup(buff);
		p->age = (i * 5);
		vector_push(v2, p);
//		printf("%p\n", x);
//		perror("%p");
	}
	for (int i = 0; i < v2->length; i++) {
		vector_item e = vector_at(v2, i);
		PERSON* p = (PERSON*)e;
		printf("person[%d] = %s %d\n", i, p->name, p->age);
	}
	vector_delete(v2, person_free);
}

void test_vm(void) {
	vm* vm = vm_new();
	//定数プールに登録
	vector_push(vm->constant_pool, 10);
	vector_push(vm->constant_pool, 5);

	vector* source = vector_new();
	//定数プールの 0 番目をプッシュ
	vector_push(source, op_consti);
	vector_push(source, 0);
	//定数プールの 1 番目をプッシュ
	vector_push(source, op_consti);
	vector_push(source, 1);
	//演算子 + で還元
	vector_push(source, op_add);
	//実行
	vm_execute(vm, source);
	int res = (int)vector_top(vm->value_stack);
	printf("res = %d\n", res);
	vector_delete(source, vector_deleter_null);
	vm_delete(vm);
}

//private
static void person_free(vector_item item) {
	PERSON* p = (PERSON*)item;
	free(p->name);
	free(p);
}
