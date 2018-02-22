#include "test.h"
#include <stdio.h>
#include "ast/ast.h"
#include "env/namespace.h"
#include "env/class_loader.h"
#include "parse/parser.h"
#include "vm/vm.h"
#include "vm/opcode_buf.h"
#include "util/list.h"
#include "util/stack.h"
#include "util/tree_map.h"
#include "util/io.h"
#include "util/props.h"
#include "util/text.h"
#include "util/file_path.h"
#include "util/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include "util/mem.h"
#include "thread/thread.h"
#include "env/script_context.h"
#include "env/heap.h"
#include "vm/eval.h"

//proto
static void person_free(vector_item item);
static void tree_map_test(char* name, tree_item item);

void test_stack(void) {
#if defined(_MSC_VER)
	stack* st = stack_new();
	for (int i = 1; i < 4; i++) {
		text_printf("%d\n", i * 10);
		stack_push(st, (stack_item)(i * 10));
	}
	text_printf("pop\n");
	while (!stack_empty(st)) {
		//FIXME:macではここがコンパイル出来ない
		text_printf("%d ", stack_empty(st));
		int i = (int)stack_pop(st);
		text_printf("%d", i);
		text_printf(" %d\n", stack_empty(st));
	}
	stack_delete(st, stack_deleter_null);
#endif
}

void test_list(void) {
#if defined(_MSC_VER)
	list* li = list_new();
	for (int i = 1; i < 4; i++) {
		text_printf("%d\n", i * 10);
		list_add(li, (stack_item)(i * 10));
	}
	text_printf("at\n");
	for (int i = 0; i < 3; i++) {
		//FIXME:macではここがコンパイル出来ない
		text_printf("%d\n", (int)list_at(li, i));
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
		text_printf("%s = %d\n", arr[i], (int)tree_map_get(m, arr[i]));
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
	/*
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
	*/
}

void test_cll(void) {
	class_loader* cll = class_loader_new_entry_point_from_file("main.signal");
	ast_print_tree(cll->source_code);
//	script_context* temp = eval_push();
//	char* lines[2] = {
//		{ " import \"lib\" " },
//		{ " Console.writeLine(\"Hello\") " }
//	};
	//	eval_interactive();
//		eval_top_from_file("main.signal");
	//	eval_top_from_source("import \"lib\"\nConsole.writeLine(\"Hello\")");
	//	eval_top_from_lines(lines, 2);
//	eval_pop(temp);
}

void test_struct(void) {
	OBJ* o = (OBJ*)MEM_MALLOC(sizeof(OBJ) * 10);
	for (int i = 0; i < 10; i++) {
		o[i].index = i;
	}
	for (int i = 0; i < 10; i++) {
		text_printf("index %d", (o + i)->index);
	}
	MEM_FREE(o);
}

void test_vector(void) {
#if defined(_MSC_VER)
	vector* v = vector_new();
	for (int i = 0; i < 10; i++) {
		vector_push(v, i);
	}
	for (int i = 0; i < v->length; i++) {
		int e = (int)vector_at(v, i);
		text_printf("vector[%d] = %d\n", i, e);
	}
	vector_delete(v, vector_deleter_null);
	text_printf("\n");

	vector* v2 = vector_new();
	for (int i = 0; i < 20; i++) {
		PERSON* p = (PERSON*)MEM_MALLOC(sizeof(PERSON));
		char buff[100];
		int x = text_sprintf(buff, 100, "name %d", i);
		p->name = text_strdup(buff);
		p->age = (i * 5);
		vector_push(v2, p);
//		text_printf("%p\n", x);
//		perror("%p");
	}
	for (int i = 0; i < v2->length; i++) {
		vector_item e = vector_at(v2, i);
		PERSON* p = (PERSON*)e;
		text_printf("person[%d] = %s %d\n", i, p->name, p->age);
	}
	vector_delete(v2, person_free);
#endif
}

void test_vector2(void) {
	vector* v = vector_new();
	vector_push(v, 10);
	vector_push(v, 20);
	vector_push(v, 30);
	//出力テスト
	for (int i = 0; i < v->length; i++) {
		text_printf("%d\n", vector_at(v, i));
	}
	text_printf("\n");
	vector_insert(v, 3, 5);
	//出力テスト
	for (int i = 0; i < v->length; i++) {
		text_printf("%d\n", vector_at(v, i));
	}
	text_printf("\n");
}

void test_vector3(void) {
	vector* v = vector_new();
	vector_push(v, 10);
	vector_push(v, 20);
	vector_push(v, 30);
	//出力テスト
	for (int i = 0; i < v->length; i++) {
		text_printf("%d\n", vector_at(v, i));
	}
	text_printf("\n");
	vector_remove(v, 2);
	//出力テスト
	for (int i = 0; i < v->length; i++) {
		text_printf("%d\n", vector_at(v, i));
	}
	text_printf("\n");
}

void test_vector4(void) {
	vector* v = vector_new();
	vector_push(v, 10);
	vector_push(v, 20);
	vector_push(v, 30);
//	FOREACH(item, v)
//	}
}

void test_map(void) {
	tree_map* map = tree_map_new();
	tree_map_put(map, "AAA", 10);
	tree_map_put(map, "ABB", 20);
	tree_map_put(map, "ACD", 30);
	tree_map_put(map, "FAE", 40);
	tree_map_each(map, tree_map_test);
}

void test_vm(void) {
	vm* vm = vm_new();
	enviroment* env = enviroment_new();
	//定数プールに登録
	enviroment_add_constant_int(env, 10);
	enviroment_add_constant_int(env, 5);

	//定数プールの 0 番目をプッシュ
	opcode_buf_add(env->buf, op_iconst);
	opcode_buf_add(env->buf, 0);
	//定数プールの 1 番目をプッシュ
	opcode_buf_add(env->buf, op_iconst);
	opcode_buf_add(env->buf, 1);
	//演算子 + で還元
	opcode_buf_add(env->buf, op_iadd);
	//実行
	vm_execute(vm, env);
	int res = (int)vector_top(vm->value_stack);
	text_printf("res = %d\n", res);
	enviroment_delete(env);
	vm_delete(vm);
}

void test_vm2(void) {
	vm* vm = vm_new();
	enviroment* env = enviroment_new();
	//定数プールに登録
	enviroment_add_constant_string(env, "HelloWorld");


	//定数プールの 0 番目をプッシュ
	opcode_buf_add(env->buf, op_sconst);
	opcode_buf_add(env->buf, 0);
	//スタックのトップを参照一覧 0 番目に格納
	opcode_buf_add(env->buf, op_store);
	opcode_buf_add(env->buf, 0);
	//参照一覧の 0 番目をスタックへプッシュ
	opcode_buf_add(env->buf, op_load);
	opcode_buf_add(env->buf, 0);
	//スタックのトップを表示
	opcode_buf_add(env->buf, op_prints);

	vm_execute(vm, env);
	enviroment_delete(env);
	vm_delete(vm);
}

void test_string_table(void) {
	/*
	string_table* st = string_table_new();
	int a = string_table_index(st, "a");
	int b = string_table_index(st, "d");
	int c = string_table_index(st, "y");

	int d = string_table_index(st, "x");
	int e = string_table_index(st, "t");

	text_printf("[%d] = %s\n", a, string_table_string(st, a));
	text_printf("[%d] = %s\n", b, string_table_string(st, b));
	text_printf("[%d] = %s\n", c, string_table_string(st, c));
	text_printf("[%d] = %s\n", d, string_table_string(st, d));
	text_printf("[%d] = %s\n", e, string_table_string(st, e));
	*/
}

void test_preload(void) {
	namespace_dump();
}

void test_props(void) {
	props* p = props_new();
	props_puti(p, "int", 100);
	props_putd(p, "double", 180.0);
	props_putc(p, "char", 'a');
	props_puts(p, "string", "aaa");
	props_puts(p, "string", "aaaxxxx");

	text_printf("int=%d\n", props_geti(p, "int", 0));
	text_printf("double=%f\n", props_getd(p, "double", 0));
	text_printf("char=%c\n", props_getc(p, "char", 'd'));
	text_printf("string=%s\n", props_gets(p, "string", "ddd"));
	props_delete(p);
}

void test_malloc(void) {
	int size = 16;
	void* block = malloc(size);
	while (true) {
		//最後に確保したブロックを開放
		free(block);
		block = NULL;
		//二倍の領域を確保
		size = size + 1;
		void* tmp = malloc(size);
		if (tmp == NULL) {
			break;
		}
	}
	text_printfln("malloc limit: %d", size);
}

void test_dup(void) {
	char* src = "HelloWor";
	char* a = text_strdup(src);
	char* b = text_strdup(a);
	char* c = text_strdup(b);
	HOLDER* hA = (HOLDER*)malloc(sizeof(HOLDER));
	HOLDER* hB = (HOLDER*)malloc(sizeof(HOLDER));
	HOLDER* hC = (HOLDER*)malloc(sizeof(HOLDER));
	hA->u.s = a;
	hB->u.s = b;
	hC->u.s = c;
	free(hA->u.s);
	free(hA);

	free(hB->u.s);
	free(hB);

	free(hC->u.s);
	free(hC);
}

//private
static void person_free(vector_item item) {
	PERSON* p = (PERSON*)item;
	MEM_FREE(p->name);
	MEM_FREE(p);
}

static void tree_map_test(char* name, tree_item item) {
	text_printf("name %s\n", name);
}