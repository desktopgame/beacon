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
#include <assert.h>
#include <string.h>

//proto
static bool eval_top_from_cll(class_loader* cll);
static void eval_clear_ast(class_loader* cll);
static void eval_clear_il(class_loader* cll);
static void eval_clear_env(class_loader* cll);

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

bool eval_top_from_file(const char * filename) {
	class_loader* cll = class_loader_new_entry_point_from_file(filename);
	return eval_top_from_cll(cll);
}

bool eval_top_from_source(const char * source) {
	class_loader* cll = class_loader_new_entry_point_from_source(source, "eval-top");
	return eval_top_from_cll(cll);
}

bool eval_top_from_lines(const char ** lines, int lineCount) {
	string_buffer* sb = string_buffer_new();
	for (int i = 0; i < lineCount; i++) {
		char* line = lines[i];
		string_buffer_appends(sb, line);
		string_buffer_append(sb, '\n');
	}
	string_buffer_shrink(sb);
	bool ret = eval_top_from_source(sb->text);
	string_buffer_delete(sb);
	return ret;
}

void eval_interactive() {
	//入力を実行するためのクラスローダー
	script_context* ctx = script_context_get_current();
	class_loader* cll = class_loader_new(content_entry_point);
	cll->filename = text_strdup("interactive");
	//行ごとに実行するためのVM
	//最後の実行位置を記憶する
	vm* xvm = vm_new();
	int pc = 0;
	sg_thread_set_vm_ref(sg_thread_current(), xvm);
	//すべての入力を記憶しておくバッファー
	string_buffer* buff = string_buffer_new();
	ctx->heap->blocking++;
	while (true) {
		//1行入力する
		char* line = text_gets();
		if (!strcmp(line, "exit")) {
			MEM_FREE(line);
			break;
		}
		//バッファと連結
		string_buffer_appends(buff, line);
		string_buffer_append(buff, '\n');
		string_buffer_shrink(buff);
		parser* p = parser_parse_from_source(buff->text);
		//構文エラー
		if (p->fail) {
			parser_pop();
			//バッファーを開放
			string_buffer_delete(buff);
			buff = NULL;
		//実行可能
		} else {
			//前回の解析データを削除
			eval_clear_ast(cll);
			eval_clear_il(cll);
			eval_clear_env(cll);
			//バッファと今回の入力行を連結したソース
			//を解析する
			cll->source_code = p->root;
			ctx->heap->blocking++;
			class_loader_load(cll);
			ctx->heap->blocking--;
			//以前の最後の実行位置から開始
			opcode_buf_add(cll->env->buf, op_nop);
			vm_resume(xvm, cll->env, pc);
			pc = cll->env->buf->source->length - 1;
			//値が残っているなら表示
			if (!vector_empty(xvm->value_stack)) {
				object* o = vector_pop(xvm->value_stack);
				text_printf(">> ");
				object_print(o);
				text_printfln(" :");
			}
			//パーサを捨てる
			p->root = NULL;
			parser_pop();
		}
		MEM_FREE(line);
	}
	//すべて開放する
	//インタラクティブモードでは
	//GCを行わないよう保護していますが、
	//ここではその保護を無効にしてGCを動作させます。
	ctx->heap->blocking--;
	vm_delete(xvm);
	sg_thread_release_vm_ref(sg_thread_current());
	class_loader_delete(cll);
	string_buffer_delete(buff);
}

//private
static bool eval_top_from_cll(class_loader* cll) {
	script_context* ctx = script_context_get_current();

	//ソースコードを読み込む
	ctx->heap->blocking++;
	class_loader_load(cll);
	ctx->heap->blocking--;
	opcode_buf_dump(cll->env->buf, 0);
	//実行
	vm* vm = vm_new();
	sg_thread_set_vm_ref(sg_thread_current(), vm);
	vm_execute(vm, cll->env);
	if(vm->terminate) {
		cll->error = true;
	}
	vm_delete(vm);
	sg_thread_release_vm_ref(sg_thread_current());

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