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
static bool eval_top_from_cll(bc_ClassLoader* cll, bc_AST* aOpt);


bool bc_EvalAST(const char* filename) {
	fprintf(stderr, "this command is deleted\n");
	abort();
	return false;
	/*
	if (!bc_ExistsFile(filename)) {
		fprintf(stderr, "file is not found: %s", filename);
		abort();
		return false;
	}
	parser* p = ParseFile(filename);
	ast_print_tree(p->root);
	if(p->result != PARSE_COMPLETE_T) {
		printf("error: %s<%d>\n    %s\n", p->source_name, p->Lineno, p->error_message);
	} else {
		printf("sucess!\n");
	}
	//パーサーを破棄
	bool ret = p->result != PARSE_COMPLETE_T;
	DestroyParser(p);
	return ret;
	//*/
}

bool bc_EvalIL(const char* filename) {
	fprintf(stderr, "this command is deleted\n");
	abort();
	return false;
	/*
	ClassLoader* cl = NewClassLoader(filename, CONTENT_ENTRY_POINT_T);
	LoadClassLoader(cl);

	if(!GetLastBCError()) {
		ILToplevel* il = cl->ILCode;
		ILToplevel_dump(il, 0);
	}
	DeleteClassLoader(cl);
	return true;
	//*/
}

bool bc_EvalOp(const char* filename) {
	bc_ClassLoader* cl = bc_NewClassLoader(filename, CONTENT_ENTRY_POINT_T);
	bc_LoadClassLoader(cl);

	if(!bc_GetLastPanic()) {
		bc_DumpEnviromentOp(cl->Env, 0);
	}
	bc_DeleteClassLoader(cl);
	return true;
}

bool bc_EvalFile(const char * filename) {
	bc_ClassLoader* cll = bc_NewClassLoader(filename, CONTENT_ENTRY_POINT_T);
	return eval_top_from_cll(cll, NULL);
}

bool bc_EvalString(const char* source) {
	bc_Parser* p = bc_ParseString(source);
	if (p->Result != PARSE_COMPLETE_T) {
		bc_Panic(BCERROR_PARSE_T, p->ErrorMessage);
		bc_DestroyParser(p);
		return false;
	}
	bc_ClassLoader* cll = bc_NewClassLoader("", CONTENT_ENTRY_POINT_T);
	bc_AST* a = bc_ReleaseParserAST(p);
	bc_DestroyParser(p);
	return eval_top_from_cll(cll, a);
}

//private
static bool eval_top_from_cll(bc_ClassLoader* cll, bc_AST* aOpt) {
	bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
	if(aOpt == NULL) {
		bc_LoadClassLoader(cll);
	} else {
		bc_LoadPassASTClassLoader(cll, aOpt);
	}
	//実行
	bc_Frame* fr = bc_NewFrame();
	bc_SetScriptThreadFrameRef(bc_GetCurrentScriptThread(bc_GetCurrentScriptContext()), fr);
	//エラーによって中断された場合のため、ここで戻す
	bc_Heap* he = bc_GetHeap();
	he->AcceptBlocking = 0;
#if defined(DEBUG)
	bc_Printfln("start");
#endif
	if(!bc_GetLastPanic()) {
		bc_ExecuteVM(fr, cll->Env);
	}
	if(fr->IsTerminate) {
		bc_Panic(BCERROR_GENERIC_T, "unexpected terminate");
	}
	bc_CatchVM(fr);
	bc_CollectHeap(bc_GetHeap());
	bc_DeleteFrame(fr);
	bc_ReleaseScriptThreadFrameRef(bc_GetCurrentScriptThread(bc_GetCurrentScriptContext()));

	bool ret = bc_GetLastPanic();
	bc_DeleteClassLoader(cll);
	return ret;
}