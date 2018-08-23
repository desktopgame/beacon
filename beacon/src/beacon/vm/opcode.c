#include "opcode.h"
#include "opcode_buf.h"
#include <stdio.h>
#include "../util/text.h"

int opcode_print(vector* source, int index) {
	return opcode_fprint(stdout, source, index);
}

int opcode_fprint(FILE* fp, vector* source, int index) {
	vector_item e = vector_at(source, index);
	opcode code = (opcode)e;
	fprintf(fp,"%d: ", index);
	switch (code) {
		//int & int
		case op_iadd:
			fprintf(fp,"iadd");
			break;
		case op_isub:
			fprintf(fp,"isub");
			break;
		case op_imul:
			fprintf(fp,"imul");
			break;
		case op_idiv:
			fprintf(fp,"idiv");
			break;
		case op_imod:
			fprintf(fp,"imod");
			break;
		case op_ibit_or:
			fprintf(fp,"ibit or");
			break;
		case op_ilogic_or:
			fprintf(fp,"ilogic or");
			break;
		case op_ibit_and:
			fprintf(fp,"ibit and");
			break;
		case op_ilogic_and:
			fprintf(fp,"ilogic and");
			break;
		case op_ieq:
			fprintf(fp,"ieq");
			break;
		case op_inoteq:
			fprintf(fp,"inoteq");
			break;
		case op_igt:
			fprintf(fp,"igt");
			break;
		case op_ige:
			fprintf(fp,"ige");
			break;
		case op_ilt:
			fprintf(fp,"ilt");
			break;
		case op_ile:
			fprintf(fp,"ile");
			break;
		case op_ilsh:
			fprintf(fp,"ilsh");
			break;
		case op_irsh:
			fprintf(fp,"irsh");
			break;
		case op_iexcor:
			fprintf(fp,"iexcor");
			break;
		case op_iflip:
			fprintf(fp, "iflip");
			break;
		case op_ceq:
			fprintf(fp, "ceq");
			break;
		case op_cnoteq:
			fprintf(fp, "cnoteq");
			break;
		case op_cgt:
			fprintf(fp, "cgt");
			break;
		case op_cge:
			fprintf(fp, "cge");
			break;
		case op_clt:
			fprintf(fp, "clt");
			break;
		case op_cle:
			fprintf(fp, "cle");
			break;
		//double & double
		case op_dadd:
			fprintf(fp,"dadd");
			break;
		case op_dsub:
			fprintf(fp,"dsub");
			break;
		case op_dmul:
			fprintf(fp,"mul");
			break;
		case op_ddiv:
			fprintf(fp,"ddiv");
			break;
		case op_dmod:
			fprintf(fp,"dmod");
			break;
		case op_deq:
			fprintf(fp,"deq");
			break;
		case op_dnoteq:
			fprintf(fp,"dnoteq");
			break;
		case op_dgt:
			fprintf(fp,"dgt");
			break;
		case op_dge:
			fprintf(fp,"dge");
			break;
		case op_dlt:
			fprintf(fp,"dlt");
			break;
		case op_dle:
			fprintf(fp,"dle");
			break;
		case op_ineg:
			fprintf(fp,"ineg");
			break;
		case op_dneg:
			fprintf(fp,"dneg");
			break;
		case op_bnot:
			fprintf(fp,"bnot");
			break;
		case op_bbit_or:
			fprintf(fp,"bbit_or");
			break;
		case op_blogic_or:
			fprintf(fp,"blogic_or");
			break;
		case op_bbit_and:
			fprintf(fp,"bbit_and");
			break;
		case op_blogic_and:
			fprintf(fp,"blogic_and");
			break;
		case op_bexcor:
			fprintf(fp, "bexcor");
			break;
		case op_bflip:
			fprintf(fp, "bflip");
			break;
		//push const
		case op_iconst:
		{
			int a = vector_at(source, ++index);
			fprintf(fp,"push iconst(%d)", a);
			break;
		}
		case op_dconst:
		{
			int a = vector_at(source, ++index);
			fprintf(fp,"push dconst(%d)", a);
			break;
		}
		case op_cconst:
		{
			int a = vector_at(source, ++index);
			fprintf(fp,"push cconst(%d)", a);
			break;
		}
		case op_sconst:
		{
			int a = vector_at(source, ++index);
			fprintf(fp,"push sconst(%d)", a);
			break;
		}
		case op_true:
		{
			fprintf(fp,"true");
			break;
		}
		case op_false:
		{
			fprintf(fp,"false");
			break;
		}
		case op_null:
		{
			fprintf(fp,"null");
			break;
		}
		case op_dup:
		{
			fprintf(fp,"dup");
			break;
		}
		case op_pop:
		{
			fprintf(fp,"pop");
			break;
		}
		case op_nop:
		{
			fprintf(fp,"nop");
			break;
		}
		//store,load
		case op_put_field:
		{
			int a = (int)vector_at(source, ++index);
			fprintf(fp,"put field(%d)", a);
			break;
		}
		case op_get_field:
		{
			//int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			fprintf(fp,"get field(%d)", b);
			break;
		}
		case op_put_static:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			fprintf(fp,"put static(%d %d)", a, b);
			break;
		}
		case op_get_static:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			fprintf(fp,"get static(%d %d)", a, b);
			break;
		}
		case op_put_property:
		{
			int a = (int)vector_at(source, ++index);
			fprintf(fp,"put property(%d)", a);
			break;
		}
		case op_get_property:
		{
			//int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			fprintf(fp,"get property(%d)", b);
			break;
		}
		case op_put_static_property:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			fprintf(fp,"put static_property(%d %d)", a, b);
			break;
		}
		case op_get_static_property:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			fprintf(fp,"get static_property(%d %d)", a, b);
			break;
		}
		case op_store:
		{
			int a = (int)vector_at(source, ++index);
			fprintf(fp,"store %d", a);
			break;
		}
		case op_load:
		{
			int a = (int)vector_at(source, ++index);
			fprintf(fp,"load %d", a);
			break;
		}
		case op_inc:
		{
			fprintf(fp,"inc");
			break;
		}
		case op_dec:
		{
			fprintf(fp,"inc");
			break;
		}
		case op_copy:
		{
			fprintf(fp,"copy");
			break;
		}
		case op_swap:
		{
			fprintf(fp,"swap");
			break;
		}
		case op_down_as:
		{
			fprintf(fp,"down as");
			break;
		}
		case op_up_as:
		{
			fprintf(fp,"up as");
			break;
		}
		//invoke
		case op_chain_this:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			fprintf(fp,"chain this(%d %d)", a, b);
			break;
		}
		case op_chain_super:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			fprintf(fp,"chain super(%d %d)", a, b);
			break;
		}
		case op_new_object:
		{
			fprintf(fp,"new object");
			break;
		}
		case op_alloc_field:
		{
			int a = (int)vector_at(source, ++index);
			fprintf(fp,"alloc field(%d)", a);
			break;
		}
		case op_new_instance:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			fprintf(fp,"new instance(%d %d)", a, b);
			break;
		}
		case op_this:
		{
			fprintf(fp,"this");
			break;
		}
		case op_super:
		{
			fprintf(fp,"super");
			break;
		}
		case op_invokevirtual:
		{
			int a = (int)vector_at(source, ++index);
			fprintf(fp,"invoke virtual(%d)", a);
			break;
		}
		case op_invokestatic:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			fprintf(fp,"invoke static(%d %d)", a, b);
			break;
		}
		case op_invokespecial:
		{
			int a = (int)vector_at(source, ++index);
			fprintf(fp,"invoke special(%d)", a);
			break;
		}
		case op_invokeinterface:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			fprintf(fp,"invoke interface(%d %d)", a, b);
			break;
		}
		case op_invokeoperator:
		{
			int a = (int)vector_at(source, ++index);
			fprintf(fp,"invoke operator(%d)", a);
			break;
		}

		case op_coro_init:
		{
			int a = (int)vector_at(source, ++index);
			printf("coro init(%d)", a);
			break;
		}
		case op_coro_next:
		{
			printf("coro next");
			break;
		}
		case op_coro_exit:
		{
			printf("coro exit");
			break;
		}
		case op_coro_resume:
		{
			printf("coro resume");
			break;
		}
		case op_coro_current:
		{
			printf("core current");
			break;
		}
		case op_coro_swap_self:
		{
			printf("core swap");
			break;
		}
		case op_generic_add:
		{
			fprintf(fp, "generic add");
			break;
		}
		case op_generic_enter:
		{
			int a = (int)vector_at(source, ++index);
			fprintf(fp, "generic enter(%d)", a);
			break;
		}
		case op_generic_unique_type:
		{
			int a = (int)vector_at(source, ++index);
			fprintf(fp, "generic unique_type(%d)", a);
			break;
		}
		case op_generic_instance_type:
		{
			int a = (int)vector_at(source, ++index);
			fprintf(fp, "generic instance_type(%d)", a);
			break;
		}
		case op_generic_static_type:
		{
			int a = (int)vector_at(source, ++index);
			fprintf(fp, "generic static_type(%d)", a);
			break;
		}
		case op_generic_exit:
		{
			fprintf(fp, "generic exit");
			break;
		}
		case op_return:
		{
			fprintf(fp,"return");
			break;
		}
		case op_return_void:
		{
			fprintf(fp, "return void");
			break;
		}
		case op_throw:
		{
			fprintf(fp,"throw");
			//int a = (int)vector_at(source, ++index);
			break;
		}
		case op_try_enter:
		{
			fprintf(fp,"try enter");
			break;
		}
		case op_try_exit:
		{
			fprintf(fp,"try exit");
			break;
		}
		case op_try_clear:
		{
			fprintf(fp,"try clear");
			break;
		}
		case op_defer_enter:
		{
			fprintf(fp, "defer enter");
			break;
		}
		case op_defer_register:
		{
			label* l = (label*)vector_at(source, ++index);
			fprintf(fp, "defer enter(%d)", l->cursor);
			break;
		}
		case op_defer_exit:
		{
			fprintf(fp, "defer exit");
			break;
		}
		case op_hexception:
		{
			fprintf(fp,"hexception");
			break;
		}
		case op_instanceof:
		{
			fprintf(fp,"instanceof");
			break;
		}
		case op_breakpoint:
		{
			fprintf(fp,"breakpoint");
			break;
		}
		//goto
		case op_goto:
		{
			label* l = (label*)vector_at(source, ++index);
			fprintf(fp,"goto(%d)", l->cursor);
			break;
		}
		case op_goto_if_true:
		{
			label* l = (label*)vector_at(source, ++index);
			fprintf(fp,"goto if true(%d)", l->cursor);
			break;
		}
		case op_goto_if_false:
		{
			label* l = (label*)vector_at(source, ++index);
			fprintf(fp,"goto if false(%d)", l->cursor);
			break;
		}
		default:
		{
			fprintf(fp,"not implemented");
			break;
		}
	}
	return index;
}
