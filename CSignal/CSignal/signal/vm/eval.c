#include "eval.h"
#include "../env/class_loader.h"
#include "../env/script_context.h"
#include "../env/heap.h"
#include "../thread/thread.h"
#include "../vm/vm.h"
#include "../util/string_buffer.h"
#include "../util/text.h"
#include "../util/mem.h"
#include <assert.h>

//proto
static void eval_top_from_cll(class_loader* cll);

script_context * eval_push() {
	script_context* cur = script_context_get_current();
	assert(cur != NULL);
	//現在のコンテキストを入れ替える
	script_context* ctx = script_context_add();
	script_context_set_current(ctx);
	return ctx;
}

void eval_pop(script_context * ctx) {
	script_context_remove(ctx);
}

void eval_top_from_file(const char * filename) {
	class_loader* cll = class_loader_new_entry_point_from_file(filename);
	eval_top_from_cll(cll);
}

void eval_top_from_source(const char * source) {
	class_loader* cll = class_loader_new_entry_point_from_source(source, "eval-top");
	eval_top_from_cll(cll);
}

void eval_top_from_lines(const char ** lines, int lineCount) {
	string_buffer* sb = string_buffer_new();
	for (int i = 0; i < lineCount; i++) {
		char* line = lines[i];
		string_buffer_appends(sb, line);
		string_buffer_append(sb, '\n');
	}
	string_buffer_shrink(sb);
	eval_top_from_source(sb->text);
	string_buffer_delete(sb);
}

void eval_interactive() {
}

//private
static void eval_top_from_cll(class_loader* cll) {
	script_context* ctx = script_context_get_current();

	//ソースコードを読み込む
	ctx->heap->blocking++;
	class_loader_load(cll);
	ctx->heap->blocking--;
	//実行
	vm* vm = vm_new();
	sg_thread_set_vm_ref(sg_thread_current(), vm);
	vm_execute(vm, cll->env);
	vm_delete(vm);
	sg_thread_release_vm_ref(sg_thread_current());

	class_loader_delete(cll);
}