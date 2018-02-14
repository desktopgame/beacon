#include "eval.h"
#include "../env/class_loader.h"
#include "../env/script_context.h"
#include "../env/heap.h"
#include "../thread/thread.h"
#include "../vm/vm.h"
#include <assert.h>

//proto
static script_context* eval_swap_ctx();
static void eval_top_from_cll(class_loader* cll);

void eval_top_from_file(const char * filename) {
	script_context* ctx = eval_swap_ctx();

	class_loader* cll = class_loader_new_entry_point_from_file(filename);
	eval_top_from_cll(cll);
	script_context_remove(ctx);
}

void eval_top_from_source(const char * source) {
	script_context* ctx = eval_swap_ctx();

	class_loader* cll = class_loader_new_entry_point_from_source(source, "eval-top");
	eval_top_from_cll(cll);
	script_context_remove(ctx);
}

//private
static script_context* eval_swap_ctx() {
	script_context* cur = script_context_get_current();
	assert(cur != NULL);
	//現在のコンテキストを入れ替える
	script_context* ctx = script_context_add();
	script_context_set_current(ctx);
	return ctx;
}

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