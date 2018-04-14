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
#include "util/string_buffer.h"
#include "util/tree_map.h"
#include "util/io.h"
#include "util/file_entry.h"
#include "util/props.h"
#include "util/text.h"
#include "util/file_path.h"
#include "util/vector.h"
#include "util/test/xtest.h"
#include "util/test/xtest_group.h"
#include <stdio.h>
#include <stdlib.h>
#include "util/mem.h"
#include "thread/thread.h"
#include "env/script_context.h"
#include "env/heap.h"
#include "vm/enviroment.h"
#include "vm/eval.h"

//proto
static void test_cll(void);
static void test_parse_err_hdr(parser* p);

//semantics
static void test_semanticsImpl(const char* dirname, bool require) {
	vector* files = io_list_files(dirname);
	for(int i=0; i<files->length; i++) {
		file_entry* e = (file_entry*)vector_at(files, i);
		if(!io_extension(e->filename, "bc")) {
			continue;
		}
		script_context* ctx = eval_push();
		xtest_must_true(eval_top_from_file(e->filename) == require, e->filename);
		eval_pop(ctx);
	}
}

static void test_semantics() {
	const char* rundir = "./semantics_test/run";
	const char* errdir = "./semantics_test/err";
	test_semanticsImpl(rundir, false);
	test_semanticsImpl(errdir, true);
}

//bison grammer
static void test_bison_grammerImpl(const char* dirname, bool require) {
	vector* files = io_list_files(dirname);
	for(int i=0; i<files->length; i++) {
		file_entry* e = (file_entry*)vector_at(files, i);
		if(!io_extension(e->filename, "cn")) {
			continue;
		}
		xtest_printf("%s\n", e->filename);
		char* input = io_read_text(e->filename);
		char* iter = input;
		//最初の行を取り出す
		string_buffer* sb = string_buffer_new();
		while(1) {
			char ch = (*iter);
			if(ch == -1 || ch == '\n') {
				break;
			}
			string_buffer_append(sb, ch);
			iter++;
		}
		//最初の行に --dump が含まれるならASTをダンプ
		char* firstline = string_buffer_release(sb);
		bool isDump = false;
		if(text_contains(firstline, "--dump")) {
			isDump = true;
		} else iter = input;
		parser* p = parser_parse_from_source(iter);
		if(isDump) {
			ast_print_tree(p->root);
		}
		MEM_FREE(firstline);
		xtest_must_true(p->fail == require, "%s", e->filename);
		parser_pop();
		MEM_FREE(input);
	}
	io_list_files_delete(files);
}

static void test_bison_grammer() {
	const char* rundir = "./grammer_test/run";
	const char* errdir = "./grammer_test/err";
	parser_set_err_hdr(test_parse_err_hdr);
	//xtest_printf("-%s-\n", rundir);
	//成功するはず
	test_bison_grammerImpl(rundir, false);
	test_bison_grammerImpl(errdir, true);
	parser_set_err_hdr(parser_default_err_hdr);
}

bool test_run() {
	xtest_group* gr = xtest_group_new("basic");
	xtest_group_add(gr, "grammer", test_bison_grammer);
	xtest_group_add(gr, "semantics", test_semantics);
	bool ret = xtest_group_run(gr);
	xtest_group_delete(gr);
	return ret;
}

static void test_cll(void) {
	class_loader* cll = class_loader_new_entry_point_from_file("main.signal");
	system("clear");
//	ast_print_tree(cll->source_code);
	class_loader_load(cll);
//	il_top_level_dump(cll->il_code, 0);
//	namespace_dump();
	enviroment_op_dump(cll->env, 0);
	vm* v = vm_new();
	sg_thread_set_vm_ref(sg_thread_current(), v);
	vm_execute(v, cll->env);
	vm_delete(v);
	sg_thread_release_vm_ref(sg_thread_current());
	class_loader_delete(cll);
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

//FIXME:parser.cからのコピペ
static void test_parse_err_hdr(parser* p) {
	//system("cls");
	//put filename
	for(int i=0; i<4; i++) {
		xtest_printf(" ");
	}
	xtest_printf("file=%s ", p->source_name);
	//put line
	xtest_printf("line=%d ", p->error_line_index);
	//put column
	xtest_printf("column=%d", p->error_column_index);
	xtest_printf("\n");
	//put str
	for(int i=0; i<4; i++) {
		xtest_printf(" ");
	}
	xtest_printf("%s", p->error_message);
	xtest_printf("\n");
	//put line
	for(int i=0; i<4; i++) {
		xtest_printf(" ");
	}
	xtest_printf("%s", p->error_line_text);
	xtest_printf("\n");
	fflush(stdout);
}