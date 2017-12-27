#pragma once
#ifndef SIGNAL_UTIL_PROPS_H
#define SIGNAL_UTIL_PROPS_H
#include <stdbool.h>
#include "tree_map.h"
/**
 * プロパティ一覧の中に含められたコンテンツの種類を表す列挙.
 */
typedef enum props_type {
	props_int,
	props_double,
	props_char,
	props_string,
} props_type;

/**
 * プロパティの要素を表す構造体.
 */
typedef struct props_entry {
	props_type type;
	union {
		int int_;
		double double_;
		char char_;
		char* string_;
	} u;
} props_entry;

/**
 * プロパティの一覧.
 */
typedef struct props {
	tree_map* map;
} props;

/**
 * 新しいエントリを作成します.
 * @param type
 * @return
 */
props_entry* props_entry_new(props_type type);

/** 
 * プロパティ一覧を作成します.
 * @return
 */
props* props_new();

/**
 * 整数型のプロパティを追加します.
 * @param self
 * @param key
 * @param i
 */
void props_puti(props* self, const char* key, int i);

/**
 * 浮動小数型のプロパティを追加します.
 * @param self
 * @param key
 * @param d
 */
void props_putd(props* self, const char* key, double d);

/**
 * 文字型のプロパティを追加します.
 * @param self
 * @param key
 * @param c
 */
void props_putc(props* self, const char* key, char c);

/**
 * 文字列型のプロパティを追加します.
 * @param self
 * @param key
 * @param s 複製されます.
 *          props_delete で一緒に開放されます。
 */
void props_puts(props* self, const char* key, const char* s);

/**
 * 指定のキーに対応する値を整数型で返します.
 * 存在しない場合はデフォルト値を返します。
 * @param self
 * @param key
 * @param defaultValue
 * @return
 */
int props_geti(props* self, const char* key, int defaultValue);

/**
 * 指定のキーに対応する値を浮動小数型で返します.
 * 存在しない場合はデフォルト値を返します。
 * @param self
 * @param key
 * @param defaultValue
 * @return
 */
double props_getd(props* self, const char* key, double defaultValue);

/**
 * 指定のキーに対応する値を文字型で返します.
 * 存在しない場合はデフォルト値を返します。
 * @param self
 * @param key
 * @param defaultValue
 * @return
 */
char props_getc(props* self, const char* key, char defaultValue);

/**
 * 指定のキーに対応する値を文字列型で返します.
 * 存在しない場合はデフォルト値を返します。
 * @param self
 * @param key
 * @param defaultValue
 * @return
 */
char* props_gets(props* self, const char* key, const char* defaultValue);

/**
 * 指定のキーが含まれるなら true.
 * @param self
 * @param key
 * @return
 */
bool props_contains(props* self, const char* key);

/**
 * プロパティの一覧を開放します.
 * @param self
 */
void props_delete(props* self);
#endif // !SIGNAL_UTIL_PROPS_H
