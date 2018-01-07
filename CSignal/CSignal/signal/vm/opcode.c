#include "opcode.h"
#include "opcode_buf.h"
#include <stdio.h>

int opcode_print(vector* source, int index) {
	vector_item e = vector_at(source, index);
	opcode code = (opcode)e;
	printf("%d: ", index);
	switch (code) {
		//int & int
		case op_iadd:
			printf("iadd");
			break;
		case op_isub:
			printf("isub");
			break;
		case op_imul:
			printf("imul");
			break;
		case op_idiv:
			printf("idiv");
			break;
		case op_imod:
			printf("imod");
			break;
		case op_ibit_or:
			printf("ibit or");
			break;
		case op_ilogic_or:
			printf("ilogic or");
			break;
		case op_ibit_and:
			printf("ibit and");
			break;
		case op_ilogic_and:
			printf("ilogic and");
			break;
		case op_ieq:
			printf("ieq");
			break;
		case op_inoteq:
			printf("inoteq");
			break;
		case op_igt:
			printf("igt");
			break;
		case op_ige:
			printf("ige");
			break;
		case op_ilt:
			printf("ilt");
			break;
		case op_ile:
			printf("ile");
			break;
		//double & double
		case op_dadd:
			printf("dadd");
			break;
		case op_dsub:
			printf("dsub");
			break;
		case op_dmul:
			printf("mul");
			break;
		case op_ddiv:
			printf("ddiv");
			break;
		case op_dmod:
			printf("dmod");
			break;
		case op_deq:
			printf("deq");
			break;
		case op_dnoteq:
			printf("dnoteq");
			break;
		case op_dgt:
			printf("dgt");
			break;
		case op_dge:
			printf("dge");
			break;
		case op_dlt:
			printf("dlt");
			break;
		case op_dle:
			printf("dle");
			break;
		case op_ineg:
			printf("ineg");
			break;
		case op_dneg:
			printf("dneg");
			break;
		case op_bnot:
			printf("bnot");
			break;
		//push const
		case op_consti:
		{
			int a = vector_at(source, ++index);
			printf("push consti(%d)", a);
			break;
		}
		case op_constd:
		{
			int a = vector_at(source, ++index);
			printf("push constd(%d)", a);
			break;
		}
		case op_constc:
		{
			int a = vector_at(source, ++index);
			printf("push constc(%d)", a);
			break;
		}
		case op_consts:
		{
			int a = vector_at(source, ++index);
			printf("push consts(%d)", a);
			break;
		}
		case op_dup:
		{
			printf("dup");
			break;
		}
		case op_pop:
		{
			printf("pop");
			break;
		}
		case op_nop:
		{
			printf("nop");
			break;
		}
		//store,load
		case op_put_field:
		{
			int a = (int)vector_at(source, ++index);
			printf("put field(%d)", a);
			break;
		}
		case op_get_field:
		{
			//int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			printf("get field(%d)", b);
			break;
		}
		case op_put_static:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			printf("put static(%d %d)", a, b);
			break;
		}
		case op_get_static:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			printf("get static(%d %d)", a, b);
			break;
		}
		case op_store:
		{
			int a = (int)vector_at(source, ++index);
			printf("store %d", a);
			break;
		}
		case op_load:
		{
			int a = (int)vector_at(source, ++index);
			printf("load %d", a);
			break;
		}
		//invoke
		case op_chain_this:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			printf("chain this(%d %d)", a, b);
			break;
		}
		case op_chain_super:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			printf("chain super(%d %d)", a, b);
			break;
		}
		case op_new_object:
		{
			printf("new object");
			break;
		}
		case op_alloc_field:
		{
			int a = (int)vector_at(source, ++index);
			printf("alloc field(%d)", a);
			break;
		}
		case op_new_instance:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			printf("new instance(%d %d)", a, b);
			break;
		}
		case op_this:
		{
			printf("this");
			break;
		}
		case op_super:
		{
			printf("super");
			break;
		}
		case op_invokevirtual:
		{
			int a = (int)vector_at(source, ++index);
			printf("invoke virtual(%d)", a);
			break;
		}
		case op_invokestatic:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			printf("invoke static(%d %d)", a, b);
			break;
		}
		case op_invokespecial:
		{
			int a = (int)vector_at(source, ++index);
			printf("invoke special(%d)", a);
			break;
		}
		case op_invokeinterface:
		{
			printf("invoke interface");
			break;
		}
		case op_return:
		{
			printf("return");
			break;
		}
		//debug
		case op_printi:
		{
			printf("printi");
			break;
		}
		case op_printd:
		{
			printf("printd");
			break;
		}
		case op_prints:
		{
			printf("prints");
			break;
		}
		case op_breakpoint:
		{
			printf("breakpoint");
			break;
		}
		//goto
		case op_goto:
		{
			label* l = (label*)vector_at(source, ++index);
			printf("goto(%d)", l->cursor);
			break;
		}
		case op_goto_if_true:
		{
			label* l = (label*)vector_at(source, ++index);
			printf("goto if true(%d)", l->cursor);
			break;
		}
		case op_goto_if_false:
		{
			label* l = (label*)vector_at(source, ++index);
			printf("goto if false(%d)", l->cursor);
			break;
		}
		default:
		{
			printf("printi");
			break;
		}
	}
	return index;
}
