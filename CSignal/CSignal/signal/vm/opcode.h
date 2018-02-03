#pragma once
#ifndef SIGNAL_VM_OPCODE_H
#define SIGNAL_VM_OPCODE_H
#include "../util/vector.h"
/**
 * バイトコードの中で、一つの命令を表すのに必要な領域を定義する型です.
 * 256種類の命令を使用出来ます。
 */
typedef unsigned char op_byte;

/**
 * 命令の一覧です.
 */
typedef enum opcode {
	//{{{ binary operator
		//{{{ int
		op_iadd = 1,
		op_isub,
		op_imul,
		op_idiv,
		op_imod,
		op_ibit_or,
		op_ilogic_or,
		op_ibit_and,
		op_ilogic_and,
		op_ieq,
		op_inoteq,
		op_igt,
		op_ige,
		op_ilt,
		op_ile,
		//}}}

		//{{{ double
		op_dadd,
		op_dsub,
		op_dmul,
		op_ddiv,
		op_dmod,
		/*
			明示的に int にキャストする必要があります。
			op_dbit_or,
			op_dlogic_or,
			op_dbit_and,
			op_dlogic_and,
		*/
		op_deq,
		op_dnoteq,
		op_dgt,
		op_dge,
		op_dlt,
		op_dle,
		//}}}
	//}}}

	//{{{ unary
		//{{{ int
		op_ineg,
		//}}}

		//{{{ double
		op_dneg,
		//}}}

		//{{{ bool
		op_bnot,
		//}}}
	//}}}

	op_consti,
	op_constd,
	op_constc,
	op_consts,
	op_true,
	op_false,
	op_return,
	op_try_enter,
	op_try_exit,
	op_throw,
	op_try_clear,
	op_hexception,
	op_instanceof,

	op_dup,
	op_pop,
	op_nop,

	op_put_field,
	op_get_field,

	op_put_static,
	op_get_static,

	op_lookup,
	op_store,
	op_load,

	op_chain_this,
	op_chain_super,
	op_new_object,
	op_alloc_field,
	op_new_instance,
	op_this,
	op_super,
	op_invokevirtual,
	op_invokestatic,
	op_invokespecial,
	op_invokeinterface,

	op_printi,
	op_printd,
	op_prints,
	op_breakpoint,

	op_goto,
	op_goto_if_true,
	op_goto_if_false,
} opcode;

/**
 * オペコードを出力します.
 * @param source
 * @param index
 */
int opcode_print(vector* source, int index);
#endif // !SIGNAL_VM_OPCODE_H
