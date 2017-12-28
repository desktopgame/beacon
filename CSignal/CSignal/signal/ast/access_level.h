#pragma once
#ifndef SIGNAL_AST_ACCESS_LEVEL_H
#define SIGNAL_AST_ACCESS_LEVEL_H
/**
 * アクセスレベルを定義する列挙型.
 */
typedef enum access_level {
	access_public,
	access_private,
	access_protected,
} access_level;

/**
 * アクセスレベルを出力します.
 * @param level
 */
void access_print(access_level level);
#endif // !SIGNAL_AST_ACCESS_LEVEL_H
