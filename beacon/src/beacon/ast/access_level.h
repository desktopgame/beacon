#pragma once
#ifndef BEACON_AST_ACCESS_LEVEL_H
#define BEACON_AST_ACCESS_LEVEL_H
#include <stdbool.h>
/**
 * アクセスレベルを定義する列挙型.
 */
typedef enum AccessLevel {
	ACCESS_PUBLIC_T = 0,
	ACCESS_PROTECTED_T,
	ACCESS_PRIVATE_T,
} AccessLevel;

/**
 * アクセスレベルを出力します.
 * @param level
 */
void PrintAccess(AccessLevel level);

bool IsSecureAccess(AccessLevel self, AccessLevel other);

bool IsWeakAccess(AccessLevel self, AccessLevel other);
#endif // !SIGNAL_AST_ACCESS_LEVEL_H
