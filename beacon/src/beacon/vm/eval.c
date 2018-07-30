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
static bool eval_top_from_cll(class_loader* cll);
static void eval_clear_ast(class_loader* cll);
static void eval_clear_il(class_loader* cll);
static void eval_clear_env(class_loader* cll);

bool eval_ast(const char* filename) {
	parser* p = parser_parse_from_file(filename);
	//結果を表示
	if(!p->fail) {
		ast_print_tree(p->root);
	}
	//パーサーを破棄
	bool ret = p->fail;
	parser_pop();
	return ret;
}

bool eval_il(const char* filename) {
	parser* p = parser_parse_from_file(filename);
	if(p->fail) {
		parser_pop();
		return false;
	}
	class_loader* cl = class_loader_new(content_entry_point);
	cl->source_code = p->root;
	p->root = NULL;
	class_loader_load(cl);

	il_top_level* il = cl->il_code;
	il_top_level_dump(il, 0);
	parser_pop();
	class_loader_delete(cl);
	return true;
}

bool eval_op(const char* filename) {
	parser* p = parser_parse_from_file(filename);
	if(p->fail) {
		parser_pop();
		return false;
	}
	class_loader* cl = class_loader_new(content_entry_point);
	cl->source_code = p->root;
	p->root = NULL;
	class_loader_load(cl);

	enviroment_op_dump(cl->env, 0);
	parser_pop();
	class_loader_delete(cl);
	return true;
}

bool eval_file(const char * filename) {
	class_loader* cll = class_loader_new_entry_point_from_file(filename);
	return eval_top_from_cll(cll);
}

bool eval_string(const char * source) {
	class_loader* cll = class_loader_new_entry_point_from_source(source, "eval-top");
	return eval_top_from_cll(cll);
}

bool eval_lines(const char ** lines, int lineCount) {
	string_buffer* sb = string_buffer_new();
	for (int i = 0; i < lineCount; i++) {
		char* line = (char*)lines[i];
		string_buffer_appends(sb, line);
		string_buffer_append(sb, '\n');
	}
	string_buffer_shrink(sb);
	bool ret = eval_string(sb->text);
	string_buffer_delete(sb);
	return ret;
}

//private
static bool eval_top_from_cll(class_loader* cll) {
	script_context* ctx = script_context_get_current();
	heap* he = heap_get();
	//ソースコードを読み込む
	assert(he->accept_blocking == 0);
	he->accept_blocking++;
	class_loader_load(cll);
	he->accept_blocking--;
	//opcode_buf_dump(cll->env->buf, 0);
	//実行
	frame* fr = frame_new();
	sg_thread_set_frame_ref(sg_thread_current(), fr);
	fpurge(stdout);
	he->accept_blocking = 0;
	if(!bc_error_last()) {
		vm_execute(fr, cll->env);
	}
	if(fr->terminate) {
		cll->error = true;
	}
	vm_catch(fr);
	heap_gc(heap_get(), gc_full);
	frame_delete(fr);
	heap_get()->accept_blocking = 0;
	//heap_dump(heap_get());
	sg_thread_release_frame_ref(sg_thread_current());

	bool ret = cll->error;
	class_loader_delete(cll);
	return ret;
}

static void eval_clear_ast(class_loader* cll) {
	if (cll->source_code != NULL) {
		ast_delete(cll->source_code);
		cll->source_code = NULL;
	}
}

static void eval_clear_il(class_loader* cll) {
	if (cll->il_code != NULL) {
		il_top_level_delete(cll->il_code);
		cll->il_code = NULL;
	}
}

static void eval_clear_env(class_loader* cll) {
	if (cll->env != NULL) {
		enviroment_delete(cll->env);
		cll->env = enviroment_new();
	}
}