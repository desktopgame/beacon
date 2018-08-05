#pragma once
#ifndef BEACON_AST_ACCESS_LEVEL_H
#define BEACON_AST_ACCESS_LEVEL_H
#include <stdbool.h>
/**
 * アクセスレベルを定義する列挙型.
 */
typedef enum access_level {
	access_public = 0,
	access_protected,
	access_private,
} access_level;

/**
 * アクセスレベルを出力します.
 * @param level
 */
void access_print(access_level level);

bool access_secure(access_level self, access_level other);

bool access_weak(access_level self, access_level other);
#endif // !SIGNAL_AST_ACCESS_LEVEL_H
