#pragma once
#ifndef SIGNAL_IL_IL_STMT_INTERFACE_H
#define SIGNAL_IL_IL_STMT_INTERFACE_H
/**
 * 文の種類を表す列挙型.
 */
typedef enum il_stmt_type {
	stmt_proc,
	stmt_if,
	stmt_while,
} il_stmt_type;

//詳細は il_stmt_impl.h を参照してください。
struct il_stmt_proc;
struct il_stmt_if;
struct il_stmt_while;

/**
 * 文を表す要素です.
 */
typedef struct il_stmt {
	il_stmt_type type;
	union {
		struct il_stmt_proc* proc_;
		struct il_stmt_if* if_;
		struct il_stmt_while* while_;
	} u;
} il_stmt;

/**
 * 文を出力します.
 * @param self
 * @param depth
 */
void il_stmt_dump(il_stmt* self, int depth);

/**
 * 文を開放します.
 * @param self
 */
void il_stmt_delete(il_stmt* self);
#endif // !SIGNAL_IL_IL_STMT_INTERFACE_H
