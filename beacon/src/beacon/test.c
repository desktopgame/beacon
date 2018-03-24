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

static void test_bison_grammer() {
	const char* topdir = "grammer_test";
	const char* rundir = "./grammer_test/run";
	const char* errdir = "./grammer_test/err";
	vector* files = io_list_files(rundir);
	xtest_printf("-%s-\n", rundir);
	for(int i=0; i<files->length; i++) {
		file_entry* e = (file_entry*)vector_at(files, i);
		xtest_printf("    %s\n", e->filename);
	}
}

bool test_run() {
	xtest_group* gr = xtest_group_new("basic");
	xtest_group_add(gr, "grammer", test_bison_grammer);
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