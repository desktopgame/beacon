#include "eval.h"
#include "../env/class_loader.h"
#include "../env/script_context.h"
#include "../env/heap.h"
#include "../parse/parser.h"
#include "../thread/thread.h"
#include "../vm/vm.h"
#include "../util/string_buffer.h"
#include "../util/text.h"
#include "../util/mem.h"
#include "../error.h"
#include <assert.h>
#include <string.h>

//proto
static bool eval_top_from_cll(class_loader* cll, ast* aOpt);


bool EvalAST(const char* filename) {
	fprintf(stderr, "this command is deleted\n");
	abort();
	return false;
	/*
	if (!ExistsFile(filename)) {
		fprintf(stderr, "file is not found: %s", filename);
		abort();
		return false;
	}
	parser* p = ParseFile(filename);
	ast_print_tree(p->root);
	if(p->result != PARSE_COMPLETE_T) {
		printf("error: %s<%d>\n    %s\n", p->source_name, p->lineno, p->error_message);
	} else {
		printf("sucess!\n");
	}
	//パーサーを破棄
	bool ret = p->result != PARSE_COMPLETE_T;
	DestroyParser(p);
	return ret;
	//*/
}

bool EvalIL(const char* filename) {
	fprintf(stderr, "this command is deleted\n");
	abort();
	return false;
	/*
	class_loader* cl = class_loader_new(filename, CONTENT_ENTRY_POINT_T);
	class_loader_load(cl);

	if(!GetLastBCError()) {
		il_top_level* il = cl->il_code;
		il_top_level_dump(il, 0);
	}
	class_loader_delete(cl);
	return true;
	//*/
}

bool EvalOp(const char* filename) {
	class_loader* cl = class_loader_new(filename, CONTENT_ENTRY_POINT_T);
	class_loader_load(cl);

	if(!GetLastBCError()) {
		DumpEnviromentOp(cl->env, 0);
	}
	class_loader_delete(cl);
	return true;
}

bool EvalFile(const char * filename) {
	class_loader* cll = class_loader_new(filename, CONTENT_ENTRY_POINT_T);
	return eval_top_from_cll(cll, NULL);
}

bool EvalString(const char* source) {
	parser* p = ParseString(source);
	if (p->result != PARSE_COMPLETE_T) {
		ThrowBCError(BCERROR_PARSE_T, p->error_message);
		DestroyParser(p);
		return false;
	}
	class_loader* cll = class_loader_new("", CONTENT_ENTRY_POINT_T);
	ast* a = ReleaseParserAST(p);
	DestroyParser(p);
	return eval_top_from_cll(cll, a);
}

//private
static bool eval_top_from_cll(class_loader* cll, ast* aOpt) {
	script_context* ctx = script_context_get_current();
	if(aOpt == NULL) {
		class_loader_load(cll);
	} else {
		class_loader_load_pass_ast(cll, aOpt);
	}
	//実行
	frame* fr = NewFrame();
	sg_thread_set_frame_ref(sg_thread_current(script_context_get_current()), fr);
	//エラーによって中断された場合のため、ここで戻す
	heap* he = GetHeap();
	he->accept_blocking = 0;
#if defined(DEBUG)
	Printfln("start");
#endif
	if(!GetLastBCError()) {
		ExecuteVM(fr, cll->env);
	}
	if(fr->terminate) {
		ThrowBCError(BCERROR_GENERIC_T, "unexpected terminate");
	}
	CatchVM(fr);
	CollectHeap(GetHeap());
	DeleteFrame(fr);
	sg_thread_release_frame_ref(sg_thread_current(script_context_get_current()));

	bool ret = GetLastBCError();
	class_loader_delete(cll);
	return ret;
}