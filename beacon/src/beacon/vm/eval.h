#pragma once
#ifndef BEACON_VM_EVAL_H
#define BEACON_VM_EVAL_H
#include <stdbool.h>
struct script_context;

/**
 * 新しいコンテキストをプッシュします.
 * 必ず eval_pop を呼び出してください。
 * @return 現在のコンテキスト
 */
struct script_context* eval_push();

/**
 * 指定のコンテキストを削除します.
 * @param ctx
 */
void eval_pop(struct script_context* ctx);

/**
 * ファイルの中身を現在のコンテキストで実行します.
 * @param filename
 * @return 解析に成功したなら false
 */
bool eval_top_from_file(const char* filename);

/**
 * 指定のソースを現在のコンテキストで実行します.
 * @param source
 * @return 解析に成功したなら false
 */
bool eval_top_from_source(const char* source);

/**
 * すべての行を連結して eval_top_from_source で実行します.
 * @param lines
 * @param lineCount
 * @return 解析に成功したなら false
 */
bool eval_top_from_lines(const char** lines, int lineCount);

void eval_interactive();
#endif // !SIGNAL_VM_EVAL_H
