#pragma once
#ifndef BEACON_VM_OPCODE_H
#define BEACON_VM_OPCODE_H
#include "../util/vector.h"
#include <stdio.h>

/**
 * 命令の一覧です.
 */
typedef enum opcode {
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
	op_ilsh,
	op_irsh,
	op_iexcor,
	op_iflip,

	op_ceq,
	op_cnoteq,
	op_cgt,
	op_cge,
	op_clt,
	op_cle,

	op_dadd,
	op_dsub,
	op_dmul,
	op_ddiv,
	op_dmod,

	op_deq,
	op_dnoteq,
	op_dgt,
	op_dge,
	op_dlt,
	op_dle,

	op_ineg,

	op_dneg,

	op_bnot,
	op_bbit_or,
	op_blogic_or,
	op_bbit_and,
	op_blogic_and,
	op_bexcor,
	op_bflip,

	op_iconst,
	op_dconst,
	op_cconst,
	op_sconst,
	op_true,
	op_false,
	op_null,
	op_return,
	op_try_enter,
	op_try_exit,
	op_throw,
	op_try_clear,
	op_defer_enter,
	op_defer_exit,
	op_defer_register,
	op_hexception,
	op_instanceof,

	op_dup,
	op_pop,
	op_nop,

	op_put_field,
	op_get_field,

	op_put_static,
	op_get_static,

	op_put_property,
	op_get_property,
	op_put_static_property,
	op_get_static_property,

	//op_lookup,
	//op_glookup,
	op_store,
	op_load,
	op_down_as,
	op_up_as,

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
	op_invokeoperator,

	op_coro_init,
	op_coro_next,
	op_coro_exit,
	op_coro_resume,
	op_coro_current,
	op_coro_parameter,
	op_coro_swap_self,

	op_generic_add,
	op_generic_enter,
	op_generic_unique_type,
	op_generic_instance_type,
	op_generic_static_type,
	op_generic_exit,

	op_breakpoint,

	op_goto,
	op_goto_if_true,
	op_goto_if_false,
	op_size,
} opcode;

/**
 * オペコードを出力します.
 * @param source
 * @param index
 */
int opcode_print(Vector* source, int index);

/**
 * オペコードを出力します.
 * @param fp
 * @param source
 * @param index
 */
int opcode_fprint(FILE* fp, Vector* source, int index);
#endif // !SIGNAL_VM_OPCODE_H
