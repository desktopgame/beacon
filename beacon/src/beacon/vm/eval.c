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


bool eval_ast(const char* filename) {
	if (!io_exists(filename)) {
		fprintf(stderr, "file is not found: %s", filename);
		abort();
		return false;
	}
	parser* p = parse_file(filename);
	ast_print_tree(p->root);
	if(p->result != parse_complete_T) {
		printf("error: %s<%d>\n    %s\n", p->source_name, p->lineno, p->error_message);
	} else {
		printf("sucess!\n");
	}
	//パーサーを破棄
	bool ret = p->result != parse_complete_T;
	parser_destroy(p);
	return ret;
}

bool eval_il(const char* filename) {
	class_loader* cl = class_loader_new(filename, content_entry_point_T);
	class_loader_load(cl);

	if(!bc_error_last()) {
		il_top_level* il = cl->il_code;
		il_top_level_dump(il, 0);
	}
	class_loader_delete(cl);
	return true;
}

bool eval_op(const char* filename) {
	class_loader* cl = class_loader_new(filename, content_entry_point_T);
	class_loader_load(cl);

	if(!bc_error_last()) {
		enviroment_op_dump(cl->env, 0);
	}
	class_loader_delete(cl);
	return true;
}

bool eval_file(const char * filename) {
	class_loader* cll = class_loader_new(filename, content_entry_point_T);
	return eval_top_from_cll(cll, NULL);
}

bool eval_string(const char* source) {
	parser* p = parse_string(source);
	if (p->result != parse_complete_T) {
		bc_error_throw(bcerror_parse_T, p->error_message);
		parser_destroy(p);
		return false;
	}
	class_loader* cll = class_loader_new("", content_entry_point_T);
	ast* a = parser_release_ast(p);
	parser_destroy(p);
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
	frame* fr = frame_new();
	sg_thread_set_frame_ref(sg_thread_current(script_context_get_current()), fr);
#if !defined(_MSC_VER)
	fpurge(stdout);
#endif
	//エラーによって中断された場合のため、ここで戻す
	heap* he = heap_get();
	he->accept_blocking = 0;
#if defined(DEBUG)
	io_printfln("start");
#endif
	if(!bc_error_last()) {
		vm_execute(fr, cll->env);
	}
	if(fr->terminate) {
		bc_error_throw(bcerror_generic_T, "unexpected terminate");
	}
	vm_catch(fr);
	heap_gc(heap_get());
	frame_delete(fr);
	sg_thread_release_frame_ref(sg_thread_current(script_context_get_current()));

	bool ret = bc_error_last();
	class_loader_delete(cll);
	return ret;
}