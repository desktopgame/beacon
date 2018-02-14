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
#endif // !SIGNAL_VM_EVAL_H
