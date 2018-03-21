#pragma once
#ifndef SIGNAL_UTIL_FILE_PATH_H
#define SIGNAL_UTIL_FILE_PATH_H
#include <stdint.h>
//define path separator char
#if defined(_WIN32)
#define PATH_SEPARATOR_CHAR '/'

#elif defined(__linux__) || defined(__GNUC__)
#define PATH_SEPARATOR_CHAR '/'

#else
#define PATH_SEPARATOR_CHAR '/'

#endif // defined(_WIN32)



/**
 * ファイルパスの一階層を表す構造体.
 */
typedef struct file_path {
	char* name;
	struct file_path* parent;
	uint32_t ref_count;
} file_path;
/**
 * 指定の名前でルートのパスを作成します.
 * @param name 複製されます。
 * @return
 */
file_path* file_path_new(const char* name);

/**
 * 指定の名前でルートのパスを作成します.
 * @param name 複製されません.
 *             このパスが削除されるときに一緒に削除されるので、
 *             呼び出し側では削除しないでください。
 * @return
 */
file_path* file_path_new_nodup(char* name);

/**
 * 指定のパスを構造体の一覧に変換します.
 * @param source
 * @param separator
 * @return
 */
file_path* file_path_parse(const char* source, char separator);

/**
 * file_path_append(file_path*, file_path*) のカバーメソッドです.
 * 文字列が複製されても構わない場合にはこちらを使用出来ます。
 * @param self
 * @param name
 * @return
 */
file_path* file_path_append(file_path* self, const char* name);

/**
 * 指定のパスを現在位置として、
 * 新たなパスを作成します.
 * 相対位置でパスを参照するのに利用出来ます。
 * @param self
 * @param next
 * @return
 */
file_path* file_path_append_path(file_path* self, file_path* next);

/**
 * 全てのパスを連結して返します.
 * @param self
 * @param separator
 * @return
 */
char* file_path_to_string(file_path* self, char separator);

/**
 * 指定のパスを標準出力へダンプします.
 * @param self
 * @param separator
 */
void file_path_dump(file_path* self, char separator);

/**
 * 指定のパスを削除します.
 * 親要素があるなら、親のカウントを減らします。
 * @param self
 */
void file_path_delete(file_path* self);

/**
 * 指定のパスを削除します.
 * 親要素があるなら、親のカウントを減らします。
 * また、この呼び出しで親のカウントが 0 になったなら親も削除します。
 * @param self
 */
void file_path_delete_tree(file_path* self);
#endif // !SIGNAL_UTIL_FILE_PATH_H
