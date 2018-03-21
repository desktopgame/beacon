#include "opcode.h"
#include "opcode_buf.h"
#include <stdio.h>

int opcode_print(vector* source, int index) {
	vector_item e = vector_at(source, index);
	opcode code = (opcode)e;
	text_printf("%d: ", index);
	switch (code) {
		//int & int
		case op_iadd:
			text_printf("iadd");
			break;
		case op_isub:
			text_printf("isub");
			break;
		case op_imul:
			text_printf("imul");
			break;
		case op_idiv:
			text_printf("idiv");
			break;
		case op_imod:
			text_printf("imod");
			break;
		case op_ibit_or:
			text_printf("ibit or");
			break;
		case op_ilogic_or:
			text_printf("ilogic or");
			break;
		case op_ibit_and:
			text_printf("ibit and");
			break;
		case op_ilogic_and:
			text_printf("ilogic and");
			break;
		case op_ieq:
			text_printf("ieq");
			break;
		case op_inoteq:
			text_printf("inoteq");
			break;
		case op_igt:
			text_printf("igt");
			break;
		case op_ige:
			text_printf("ige");
			break;
		case op_ilt:
			text_printf("ilt");
			break;
		case op_ile:
			text_printf("ile");
			break;
		//double & double
		case op_dadd:
			text_printf("dadd");
			break;
		case op_dsub:
			text_printf("dsub");
			break;
		case op_dmul:
			text_printf("mul");
			break;
		case op_ddiv:
			text_printf("ddiv");
			break;
		case op_dmod:
			text_printf("dmod");
			break;
		case op_deq:
			text_printf("deq");
			break;
		case op_dnoteq:
			text_printf("dnoteq");
			break;
		case op_dgt:
			text_printf("dgt");
			break;
		case op_dge:
			text_printf("dge");
			break;
		case op_dlt:
			text_printf("dlt");
			break;
		case op_dle:
			text_printf("dle");
			break;
		case op_ineg:
			text_printf("ineg");
			break;
		case op_dneg:
			text_printf("dneg");
			break;
		case op_bnot:
			text_printf("bnot");
			break;
		case op_bbit_or:
			text_printf("bbit_or");
			break;
		case op_blogic_or:
			text_printf("blogic_or");
			break;
		case op_bbit_and:
			text_printf("bbit_and");
			break;
		case op_blogic_and:
			text_printf("blogic_and");
			break;
		//push const
		case op_iconst:
		{
			int a = vector_at(source, ++index);
			text_printf("push iconst(%d)", a);
			break;
		}
		case op_dconst:
		{
			int a = vector_at(source, ++index);
			text_printf("push dconst(%d)", a);
			break;
		}
		case op_cconst:
		{
			int a = vector_at(source, ++index);
			text_printf("push cconst(%d)", a);
			break;
		}
		case op_sconst:
		{
			int a = vector_at(source, ++index);
			text_printf("push sconst(%d)", a);
			break;
		}
		case op_true:
		{
			text_printf("true");
			break;
		}
		case op_false:
		{
			text_printf("false");
			break;
		}
		case op_null:
		{
			text_printf("null");
			break;
		}
		case op_dup:
		{
			text_printf("dup");
			break;
		}
		case op_pop:
		{
			text_printf("pop");
			break;
		}
		case op_nop:
		{
			text_printf("nop");
			break;
		}
		//store,load
		case op_put_field:
		{
			int a = (int)vector_at(source, ++index);
			text_printf("put field(%d)", a);
			break;
		}
		case op_get_field:
		{
			//int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_printf("get field(%d)", b);
			break;
		}
		case op_put_static:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_printf("put static(%d %d)", a, b);
			break;
		}
		case op_get_static:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_printf("get static(%d %d)", a, b);
			break;
		}
		case op_store:
		{
			int a = (int)vector_at(source, ++index);
			text_printf("store %d", a);
			break;
		}
		case op_load:
		{
			int a = (int)vector_at(source, ++index);
			text_printf("load %d", a);
			break;
		}
		case op_inc:
		{
			text_printf("inc");
			break;
		}
		case op_dec:
		{
			text_printf("inc");
			break;
		}
		case op_copy:
		{
			text_printf("copy");
			break;
		}
		case op_swap:
		{
			text_printf("swap");
			break;
		}
		//invoke
		case op_chain_this:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_printf("chain this(%d %d)", a, b);
			break;
		}
		case op_chain_super:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_printf("chain super(%d %d)", a, b);
			break;
		}
		case op_new_object:
		{
			text_printf("new object");
			break;
		}
		case op_alloc_field:
		{
			int a = (int)vector_at(source, ++index);
			text_printf("alloc field(%d)", a);
			break;
		}
		case op_new_instance:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_printf("new instance(%d %d)", a, b);
			break;
		}
		case op_this:
		{
			text_printf("this");
			break;
		}
		case op_super:
		{
			text_printf("super");
			break;
		}
		case op_invokevirtual:
		{
			int a = (int)vector_at(source, ++index);
			text_printf("invoke virtual(%d)", a);
			break;
		}
		case op_invokestatic:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_printf("invoke static(%d %d)", a, b);
			break;
		}
		case op_invokespecial:
		{
			int a = (int)vector_at(source, ++index);
			text_printf("invoke special(%d)", a);
			break;
		}
		case op_invokeinterface:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_printf("invoke interface(%d %d)", a, b);
			break;
		}
		case op_return:
		{
			text_printf("return");
			break;
		}
		case op_throw:
		{
			text_printf("throw");
			//int a = (int)vector_at(source, ++index);
			break;
		}
		case op_try_enter:
		{
			text_printf("try enter");
			break;
		}
		case op_try_exit:
		{
			text_printf("try exit");
			break;
		}
		case op_try_clear:
		{
			text_printf("try clear");
			break;
		}
		case op_hexception:
		{
			text_printf("hexception");
			break;
		}
		case op_instanceof:
		{
			int a = (int)vector_at(source, ++index);
			text_printf("instanceof(%d)", a);
			break;
		}
		//debug
		case op_printi:
		{
			text_printf("printi");
			break;
		}
		case op_printd:
		{
			text_printf("printd");
			break;
		}
		case op_prints:
		{
			text_printf("prints");
			break;
		}
		case op_breakpoint:
		{
			text_printf("breakpoint");
			break;
		}
		//goto
		case op_goto:
		{
			label* l = (label*)vector_at(source, ++index);
			text_printf("goto(%d)", l->cursor);
			break;
		}
		case op_goto_if_true:
		{
			label* l = (label*)vector_at(source, ++index);
			text_printf("goto if true(%d)", l->cursor);
			break;
		}
		case op_goto_if_false:
		{
			label* l = (label*)vector_at(source, ++index);
			text_printf("goto if false(%d)", l->cursor);
			break;
		}
		default:
		{
			text_printf("not implemented");
			break;
		}
	}
	return index;
}
