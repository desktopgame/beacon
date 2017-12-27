#include "opcode.h"
#include "opcode_buf.h"
#include <stdio.h>

int opcode_print(vector* source, int index) {
	vector_item e = vector_at(source, index);
	opcode code = (opcode)e;
	switch (code) {
		//eval
		case op_add:
		{
			printf("add");
			break;
		}
		case op_sub:
		{
			printf("sub");
			break;
		}
		case op_mul:
		{
			printf("mul");
			break;
		}
		case op_div:
		{
			printf("div");
			break;
		}
		case op_mod:
		{
			printf("mod");
			break;
		}
		case op_bit_or:
			printf("bit or");
			break;

		case op_logic_or:
			printf("logic or");
			break;

		case op_bit_and:
			printf("bit and");
			break;

		case op_logic_and:
			printf("logic and");
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
		case op_method:
		{
			int a = (int)vector_at(source, ++index);
			printf("push method(%d)", a);
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
			int a = (int)vector_at(source, ++index);
			printf("get field(%d)", a);
			break;
		}
		case op_put_static:
		{
			int a = (int)vector_at(source, ++index);
			printf("put static(%d)", a);
			break;
		}
		case op_get_static:
		{
			int a = (int)vector_at(source, ++index);
			printf("get static(%d)", a);
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
		case op_invokevirtual:
		{
			printf("invoke virtual");
			break;
		}
		case op_invokestatic:
		{
			printf("invoke static");
			break;
		}
		case op_invokespecial:
		{
			printf("invoke special");
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
