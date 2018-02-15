#pragma once
#ifndef SIGNAL_VM_EVAL_H
#define SIGNAL_VM_EVAL_H

/**
 * ファイルの中身を別のコンテキストで実行します.
 * @param filename
 */
void eval_top_from_file(const char* filename);

/**
 * 指定のソースを別のコンテキストで実行します.
 * @param source
 */
void eval_top_from_source(const char* source);

/**
 * すべての行を連結して eval_top_from_source で実行します.
 * @param lines
 * @param lineCount
 */
void eval_top_from_lines(const char** lines, int lineCount);

void eval_interactive();
#endif // !SIGNAL_VM_EVAL_H
