#include "test.h"
#include <stdio.h>
#include "ast/ast.h"
#include "env/namespace.h"
#include "env/class_loader.h"
#include "parse/parser.h"
#include "vm/vm.h"
#include "vm/opcode_buf.h"
#include "util/stack.h"
#include "util/string_buffer.h"
#include "util/tree_map.h"
#include "util/io.h"
#include "util/file_entry.h"
#include "util/text.h"
#include "util/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include "util/mem.h"
#include "thread/thread.h"
#include "env/script_context.h"
#include "env/heap.h"
#include "vm/enviroment.h"
#include "vm/eval.h"
#include "error.h"
#include <assert.h>

#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

//proto
static void test_cll(void);
static void test_semanticsImpl(const char* dirname, bool require, char** outFileName, bool* outFail);
static int test_semantics();
static void test_bison_grammerImpl(const char* dirname, bool require);
static void test_bison_grammer();
static bool gTest = false;

int bc_RunTest() {
	gTest = true;
	int ret = test_semantics();
	gTest = false;
	return ret;
}

bool bc_IsTestNow() {
	return gTest;
}

//semantics
static void test_semanticsImpl(const char* dirname, bool require, char** outFileName, bool* outFail) {
#if defined(_MSC_VER)
	//stdoutを入れ替える
	char* filename = NULL;
	bool fail = false;
	//全てのテストファイルを訪問する
	Vector* files = bc_GetFiles(dirname);
	for (int i = 0; i<files->Length; i++) {
		//.bc以外は無視する
		FileEntry* e = (FileEntry*)AtVector(files, i);
		if (!bc_IsMatchExtension(e->FileName, "bc")) {
			continue;
		}
		//これから実行するファイルを記録
		bc_Recover();
		filename = e->FileName;
		//標準出力を入れ替えて実行
		fprintf(stdout, "[%s]\n", e->FileName);
		bool result = bc_EvalFile(e->FileName);
		//期待していた結果でないなら終了
		if (result != require) {
			fail = true;
			break;
		}
		//ここで静的領域を解放しないと、
		//enviromentの削除後も静的フィールドが定数を掴んだまま
		bc_ClearScriptContext(bc_GetCurrentScriptContext());
	}
	(*outFileName) = bc_Strdup(filename);
	(*outFail) = fail;
	bc_DeleteFiles(files);
	//元に戻す
	fflush(stdout);
#else
	//stdoutを入れ替える
	char* filename = NULL;
	FILE* out = tmpfile();
	FILE* STDOUT = stdout;
	stdout = out;
	bool fail = false;
	//全てのテストファイルを訪問する
	Vector* files = bc_GetFiles(dirname);
	for(int i=0; i<files->Length; i++) {
		//.bc以外は無視する
		FileEntry* e = (FileEntry*)AtVector(files, i);
		if(!bc_IsMatchExtension(e->FileName, "bc")) {
			continue;
		}
		//これから実行するファイルを記録
		bc_Recover();
		filename = e->FileName;
		//標準出力を入れ替えて実行
		fprintf(STDOUT, "[%s]\n", e->FileName);
		bool result = bc_EvalFile(e->FileName);
		rewind(out);
		while(!feof(out)) {
			char* line = bc_FreadLine(out);
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
		//ここで静的領域を解放しないと、
		//enviromentの削除後も静的フィールドが定数を掴んだまま
		bc_ClearScriptContext(bc_GetCurrentScriptContext());
	}
	(*outFileName) = bc_Strdup(filename);
	(*outFail) = fail;
	bc_DeleteFiles(files);
	//元に戻す
	stdout = STDOUT;
	fclose(out);
	fflush(stdout);
#endif
}

static int test_semantics() {
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
		MEM_FREE(runFN);
	} else {
		fprintf(stdout, "[RUN]SUCCEESS!");
		MEM_FREE(runFN);
	}
	fprintf(stdout, "\n");
	if(errRL) {
		fprintf(stdout, "[ERR]FAIL. %s", errFN);
		MEM_FREE(errFN);
	} else {
		fprintf(stdout, "[ERR]SUCCEESS!");
		MEM_FREE(errFN);
	}
	fprintf(stdout, "\n");
	return runRL || errRL ? 1 : 0;
}