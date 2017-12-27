#pragma once
#ifndef SIGNAL_VM_OPCODE_H
#define SIGNAL_VM_OPCODE_H
typedef union {
	int int_;
	char char_;
	const char* string_;
} operand;
/**
 * バイトコードの中で、一つの命令を表すのに必要な領域を定義する型です.
 * 256種類の命令を使用出来ます。
 */
typedef unsigned char op_byte;

/**
 * 命令の一覧です.
 */
typedef enum opcode {
	op_add = 1,
	op_sub,
	op_mul,
	op_div,
	op_mod,

	op_bit_or,
	op_logic_or,

	op_bit_and,
	op_logic_and,

	op_eq,
	op_noteq,
	op_gt,
	op_ge,
	op_lt,
	op_le,

	op_not,
	op_neg,

	op_consti,
	op_constd,
	op_constc,
	op_consts,
	op_method,

	op_dup,
	op_pop,
	op_nop,

	op_put_field,
	op_get_field,

	op_put_static,
	op_get_static,

	op_store,
	op_load,

	op_invokevirtual,
	op_invokestatic,
	op_invokespecial,
	op_invokeinterface,
	op_return,

	op_printi,
	op_printd,
	op_prints,

	op_goto,
	op_goto_if_true,
	op_goto_if_false,
} opcode;

/**
 * オペコードを出力します.
 * @param source
 * @param index
 */
int opcode_print(struct vector* source, int index);
#endif // !SIGNAL_VM_OPCODE_H
