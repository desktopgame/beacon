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
#include "util/text.h"
#include "util/file_path.h"
#include "util/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include "util/mem.h"
#include "thread/thread.h"
#include "env/script_context.h"
#include "env/heap.h"
#include "vm/enviroment.h"
#include "vm/eval.h"
#include <assert.h>

//proto
static void test_cll(void);
static void test_parse_err_hdr(parser* p);
static void test_semanticsImpl(const char* dirname, bool require, char** outFileName, bool* outFail);
static void test_semantics();
static void test_bison_grammerImpl(const char* dirname, bool require);
static void test_bison_grammer();
static bool gTest = false;

bool test_run() {
	gTest = true;
	test_semantics();
	gTest = false;
	return true;
}

bool test_now() {
	return gTest;
}

//semantics
static void test_semanticsImpl(const char* dirname, bool require, char** outFileName, bool* outFail) {
	script_context* ctx = script_context_add();
	script_context_set_current(ctx);
	//stdoutを入れ替える
	char* filename = NULL;
	FILE* out = tmpfile();
	FILE* STDOUT = stdout;
	stdout = out;
	bool fail = false;
	//全てのテストファイルを訪問する
	vector* files = io_list_files(dirname);
	for(int i=0; i<files->length; i++) {
		//.bc以外は無視する
		file_entry* e = (file_entry*)vector_at(files, i);
		if(!io_extension(e->filename, "bc")) {
			continue;
		}
		filename = e->filename;
		fprintf(STDOUT, "[%s]\n", e->filename);
		bool result = eval_file(e->filename);
		rewind(out);
		while(!feof(out)) {
			char* line = text_freadline(out);
			fprintf(STDOUT, "    %s\n", line);
			MEM_FREE(line);
		}
		fclose(out);
		out = tmpfile();
		stdout = out;
		//期待していた結果でないなら終了
		if(result != require) {
			fail = true;
			break;
		}
		script_context_static_clear(ctx);
	}
	(*outFileName) = filename;
	(*outFail) = fail;
	script_context_remove(ctx);
	io_list_files_delete(files);
	//元に戻す
	stdout = STDOUT;
	fclose(out);
	fflush(stdout);
}

static void test_semantics() {
	const char* rundir = "./semantics_test/run";
	const char* errdir = "./semantics_test/err";
	char* runFN = NULL;
	char* errFN = NULL;
	bool runRL = false;
	bool errRL = false;
	test_semanticsImpl(rundir, false, &runFN, &runRL);
	test_semanticsImpl(errdir, true, &errFN, &errRL);
	if(runRL) {
		fprintf(stdout, "[RUN]FAIL. %s", runFN);
	} else {
		fprintf(stdout, "[RUN]SUCCEESS!");
	}
	fprintf(stdout, "\n");
	if(errRL) {
		fprintf(stdout, "[ERR]FAIL. %s", errFN);
	} else {
		fprintf(stdout, "[ERR]SUCCEESS!");
	}
	fprintf(stdout, "\n");
}

//FIXME:parser.cからのコピペ
static void test_parse_err_hdr(parser* p) {
	//system("cls");
	//put filename
	for(int i=0; i<4; i++) {
		text_printf(" ");
	}
	text_printf("file=%s ", p->source_name);
	//put line
	text_printf("line=%d ", p->error_line_index);
	//put column
	text_printf("column=%d", p->error_column_index);
	text_printf("\n");
	//put str
	for(int i=0; i<4; i++) {
		text_printf(" ");
	}
	text_printf("%s", p->error_message);
	text_printf("\n");
	//put line
	for(int i=0; i<4; i++) {
		text_printf(" ");
	}
	text_printf("%s", p->error_line_text);
	text_printf("\n");
	fflush(stdout);
}