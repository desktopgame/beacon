#pragma once
#ifndef BEACON_UTIL_IO_H
#define BEACON_UTIL_IO_H
#include <stdio.h>
#include <stdbool.h>
#include "vector.h"

/**
 * 指定の数だけ標準出力にスペースを出力します.
 * @param depth
 */
void Printi(int depth);

/**
 * 指定の数だけスペースを出力します.
 * @param fp
 * @param depth
 */
void Fprinti(FILE* fp, int depth);

/**
 * @param fp
 * @param fmt
 */
void Printfln(const char* fmt, ...);

/**
 * 改行文字を出力します.
 */
void Println();

/**
 * 新しいファイルを作成します.
 * @param filename
 * @return
 */
void NewFile(const char* filename);

/**
 * 指定のファイルが既に存在するなら true.
 * @param filename
 * @return
 */
bool ExistsFile(const char* filename);

/**
 * 指定のファイルを削除します.
 * @param filename
 * @return
 */
bool DeleteFile(const char* filename);

/**
 * 指定のファイルを読み込んで返します.
 * @param filename
 * @return 呼び出し側で開放してください.
 */
char* ReadText(const char* filename);

/**
 * 指定のファイルのテキストを上書きします.
 * @param filename
 * @param text
 * @return
 */
void WriteText(const char* filename, const char* text);

/**
 * 現在のパスを取得します.
 * 末尾は / で終わります。
 * @param block
 * @param len
 */
void GetCurrentPath(char* block, int len);

/**
 * 実行時ディレクトリを基準として、
 * targetに表される位置を絶対パスに変換します.
 * @param target
 * @return 呼び出し側で開放してください.
 */
char* GetAbsolutePath(const char* target);

/**
 * 指定のファイルをスクリプトパスで解決してフルパスへ変換します.
 * @param target
 * @return
 */
char* ResolveScriptPath(const char* target);

/**
 * dirnameの直下のファイル名一覧を返します.
 * @param dirname
 * @return
 */
vector* GetFiles(const char* dirname);

/**
 * ファイル一覧をソートするための比較関数.
 * @param a
 * @param b
 * @return
 */
int SortFiles(const void* a, const void* b);

/**
 * io_list_files によって確保された vector を解放します.s
 * @param files
 */
void DeleteFiles(vector* files);

/**
 * filename の拡張子が ext なら true.
 * @param filename
 * @param ext ドットを含まない
 * @return
 */
bool IsMatchExtension(const char* filename, const char* ext);

/**
 * a と b をパス区切り文字で連結して返します.
 * @param a
 * @param b
 * @return
 */
char* ConcatPath(const char* a, const char* b);
#endif // !SIGNAL_UTIL_IO_H
