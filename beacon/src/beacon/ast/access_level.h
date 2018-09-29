#pragma once
#ifndef BEACON_AST_ACCESS_LEVEL_H
#define BEACON_AST_ACCESS_LEVEL_H
#include <stdbool.h>
/**
 * アクセスレベルを定義する列挙型.
 */
typedef enum access_level {
	ACCESS_PUBLIC_T = 0,
	ACCESS_PROTECTED_T,
	ACCESS_PRIVATE_T,
} access_level;

/**
 * アクセスレベルを出力します.
 * @param level
 */
void PrintAccess(access_level level);

bool IsSecureAccess(access_level self, access_level other);

bool IsWeakAccess(access_level self, access_level other);
#endif // !SIGNAL_AST_ACCESS_LEVEL_H
