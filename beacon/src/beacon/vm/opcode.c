#include "opcode.h"
#include "opcode_buf.h"
#include <stdio.h>
#include "../util/text.h"
#include "lazy_int.h"

int opcode_print(vector* source, int index) {
	return opcode_fprint(stdout, source, index);
}

int opcode_fprint(FILE* fp, vector* source, int index) {
	vector_item e = vector_at(source, index);
	opcode code = (opcode)e;
	text_fprintf(fp,"%d: ", index);
	switch (code) {
		//int & int
		case op_iadd:
			text_fprintf(fp,"iadd");
			break;
		case op_isub:
			text_fprintf(fp,"isub");
			break;
		case op_imul:
			text_fprintf(fp,"imul");
			break;
		case op_idiv:
			text_fprintf(fp,"idiv");
			break;
		case op_imod:
			text_fprintf(fp,"imod");
			break;
		case op_ibit_or:
			text_fprintf(fp,"ibit or");
			break;
		case op_ilogic_or:
			text_fprintf(fp,"ilogic or");
			break;
		case op_ibit_and:
			text_fprintf(fp,"ibit and");
			break;
		case op_ilogic_and:
			text_fprintf(fp,"ilogic and");
			break;
		case op_ieq:
			text_fprintf(fp,"ieq");
			break;
		case op_inoteq:
			text_fprintf(fp,"inoteq");
			break;
		case op_igt:
			text_fprintf(fp,"igt");
			break;
		case op_ige:
			text_fprintf(fp,"ige");
			break;
		case op_ilt:
			text_fprintf(fp,"ilt");
			break;
		case op_ile:
			text_fprintf(fp,"ile");
			break;
		case op_ilsh:
			text_fprintf(fp,"ilsh");
			break;
		case op_irsh:
			text_fprintf(fp,"irsh");
			break;
		case op_iexcor:
			text_fprintf(fp,"iexcor");
			break;
		case op_iflip:
			text_fprintf(fp, "iflip");
			break;
		case op_ceq:
			text_fprintf(fp, "ceq");
			break;
		case op_cnoteq:
			text_fprintf(fp, "cnoteq");
			break;
		case op_cgt:
			text_fprintf(fp, "cgt");
			break;
		case op_cge:
			text_fprintf(fp, "cge");
			break;
		case op_clt:
			text_fprintf(fp, "clt");
			break;
		case op_cle:
			text_fprintf(fp, "cle");
			break;
		//double & double
		case op_dadd:
			text_fprintf(fp,"dadd");
			break;
		case op_dsub:
			text_fprintf(fp,"dsub");
			break;
		case op_dmul:
			text_fprintf(fp,"mul");
			break;
		case op_ddiv:
			text_fprintf(fp,"ddiv");
			break;
		case op_dmod:
			text_fprintf(fp,"dmod");
			break;
		case op_deq:
			text_fprintf(fp,"deq");
			break;
		case op_dnoteq:
			text_fprintf(fp,"dnoteq");
			break;
		case op_dgt:
			text_fprintf(fp,"dgt");
			break;
		case op_dge:
			text_fprintf(fp,"dge");
			break;
		case op_dlt:
			text_fprintf(fp,"dlt");
			break;
		case op_dle:
			text_fprintf(fp,"dle");
			break;
		case op_ineg:
			text_fprintf(fp,"ineg");
			break;
		case op_dneg:
			text_fprintf(fp,"dneg");
			break;
		case op_bnot:
			text_fprintf(fp,"bnot");
			break;
		case op_bbit_or:
			text_fprintf(fp,"bbit_or");
			break;
		case op_blogic_or:
			text_fprintf(fp,"blogic_or");
			break;
		case op_bbit_and:
			text_fprintf(fp,"bbit_and");
			break;
		case op_blogic_and:
			text_fprintf(fp,"blogic_and");
			break;
		case op_bexcor:
			text_fprintf(fp, "bexcor");
			break;
		case op_bflip:
			text_fprintf(fp, "bflip");
			break;
		//push const
		case op_iconst:
		{
			int a = vector_at(source, ++index);
			text_fprintf(fp,"push iconst(%d)", a);
			break;
		}
		case op_dconst:
		{
			int a = vector_at(source, ++index);
			text_fprintf(fp,"push dconst(%d)", a);
			break;
		}
		case op_cconst:
		{
			int a = vector_at(source, ++index);
			text_fprintf(fp,"push cconst(%d)", a);
			break;
		}
		case op_sconst:
		{
			int a = vector_at(source, ++index);
			text_fprintf(fp,"push sconst(%d)", a);
			break;
		}
		case op_true:
		{
			text_fprintf(fp,"true");
			break;
		}
		case op_false:
		{
			text_fprintf(fp,"false");
			break;
		}
		case op_null:
		{
			text_fprintf(fp,"null");
			break;
		}
		case op_dup:
		{
			text_fprintf(fp,"dup");
			break;
		}
		case op_pop:
		{
			text_fprintf(fp,"pop");
			break;
		}
		case op_nop:
		{
			text_fprintf(fp,"nop");
			break;
		}
		//store,load
		case op_put_field:
		{
			int a = (int)vector_at(source, ++index);
			text_fprintf(fp,"put field(%d)", a);
			break;
		}
		case op_get_field:
		{
			//int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_fprintf(fp,"get field(%d)", b);
			break;
		}
		case op_put_static:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_fprintf(fp,"put static(%d %d)", a, b);
			break;
		}
		case op_get_static:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_fprintf(fp,"get static(%d %d)", a, b);
			break;
		}
		case op_put_property:
		{
			int a = (int)vector_at(source, ++index);
			text_fprintf(fp,"put property(%d)", a);
			break;
		}
		case op_get_property:
		{
			//int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_fprintf(fp,"get property(%d)", b);
			break;
		}
		case op_put_static_property:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_fprintf(fp,"put static_property(%d %d)", a, b);
			break;
		}
		case op_get_static_property:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_fprintf(fp,"get static_property(%d %d)", a, b);
			break;
		}
		case op_store:
		{
			int a = (int)vector_at(source, ++index);
			text_fprintf(fp,"store %d", a);
			break;
		}
		case op_load:
		{
			int a = (int)vector_at(source, ++index);
			text_fprintf(fp,"load %d", a);
			break;
		}
		case op_inc:
		{
			text_fprintf(fp,"inc");
			break;
		}
		case op_dec:
		{
			text_fprintf(fp,"inc");
			break;
		}
		case op_copy:
		{
			text_fprintf(fp,"copy");
			break;
		}
		case op_swap:
		{
			text_fprintf(fp,"swap");
			break;
		}
		//invoke
		case op_chain_this:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_fprintf(fp,"chain this(%d %d)", a, b);
			break;
		}
		case op_chain_super:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_fprintf(fp,"chain super(%d %d)", a, b);
			break;
		}
		case op_new_object:
		{
			text_fprintf(fp,"new object");
			break;
		}
		case op_alloc_field:
		{
			int a = (int)vector_at(source, ++index);
			text_fprintf(fp,"alloc field(%d)", a);
			break;
		}
		case op_new_instance:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_fprintf(fp,"new instance(%d %d)", a, b);
			break;
		}
		case op_this:
		{
			text_fprintf(fp,"this");
			break;
		}
		case op_super:
		{
			text_fprintf(fp,"super");
			break;
		}
		case op_invokevirtual:
		{
			int a = (int)vector_at(source, ++index);
			text_fprintf(fp,"invoke virtual(%d)", a);
			break;
		}
		case op_invokestatic:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_fprintf(fp,"invoke static(%d %d)", a, b);
			break;
		}
		case op_invokespecial:
		{
			int a = (int)vector_at(source, ++index);
			text_fprintf(fp,"invoke special(%d)", a);
			break;
		}
		case op_invokeinterface:
		{
			int a = (int)vector_at(source, ++index);
			int b = (int)vector_at(source, ++index);
			text_fprintf(fp,"invoke interface(%d %d)", a, b);
			break;
		}
		case op_invokeoperator:
		{
			int a = (int)vector_at(source, ++index);
			text_fprintf(fp,"invoke operator(%d)", a);
			break;
		}
		case op_invokevirtual_lazy:
		{
			lazy_int* a = (lazy_int*)vector_at(source, ++index);
			text_fprintf(fp,"invoke virtual(%d)", a->value);
			break;
		}

		case op_coro_init:
		{
			int a = (int)vector_at(source, ++index);
			text_printf("coro init(%d)", a);
			break;
		}
		case op_coro_next:
		{
			text_printf("coro next");
			break;
		}
		case op_coro_exit:
		{
			text_printf("coro exit");
			break;
		}
		case op_coro_resume:
		{
			text_printf("coro resume");
			break;
		}
		case op_coro_current:
		{
			text_printf("core current");
			break;
		}
		case op_coro_swap_self:
		{
			text_printf("core swap");
			break;
		}
		case op_generic_add:
		{
			text_fprintf(fp, "generic add");
			break;
		}
		case op_generic_enter:
		{
			int a = (int)vector_at(source, ++index);
			text_fprintf(fp, "generic enter(%d)", a);
			break;
		}
		case op_generic_unique_type:
		{
			int a = (int)vector_at(source, ++index);
			text_fprintf(fp, "generic unique_type(%d)", a);
			break;
		}
		case op_generic_instance_type:
		{
			int a = (int)vector_at(source, ++index);
			text_fprintf(fp, "generic instance_type(%d)", a);
			break;
		}
		case op_generic_static_type:
		{
			int a = (int)vector_at(source, ++index);
			text_fprintf(fp, "generic static_type(%d)", a);
			break;
		}
		case op_generic_exit:
		{
			text_fprintf(fp, "generic exit");
			break;
		}
		case op_return:
		{
			text_fprintf(fp,"return");
			break;
		}
		case op_return_void:
		{
			text_fprintf(fp, "return void");
			break;
		}
		case op_throw:
		{
			text_fprintf(fp,"throw");
			//int a = (int)vector_at(source, ++index);
			break;
		}
		case op_try_enter:
		{
			text_fprintf(fp,"try enter");
			break;
		}
		case op_try_exit:
		{
			text_fprintf(fp,"try exit");
			break;
		}
		case op_try_clear:
		{
			text_fprintf(fp,"try clear");
			break;
		}
		case op_defer_enter:
		{
			text_fprintf(fp, "defer enter");
			break;
		}
		case op_defer_register:
		{
			label* l = (label*)vector_at(source, ++index);
			text_fprintf(fp, "defer enter(%d)", l->cursor);
			break;
		}
		case op_defer_exit:
		{
			text_fprintf(fp, "defer exit");
			break;
		}
		case op_hexception:
		{
			text_fprintf(fp,"hexception");
			break;
		}
		case op_instanceof:
		{
			text_fprintf(fp,"instanceof");
			break;
		}
		case op_breakpoint:
		{
			text_fprintf(fp,"breakpoint");
			break;
		}
		//goto
		case op_goto:
		{
			label* l = (label*)vector_at(source, ++index);
			text_fprintf(fp,"goto(%d)", l->cursor);
			break;
		}
		case op_goto_if_true:
		{
			label* l = (label*)vector_at(source, ++index);
			text_fprintf(fp,"goto if true(%d)", l->cursor);
			break;
		}
		case op_goto_if_false:
		{
			label* l = (label*)vector_at(source, ++index);
			text_fprintf(fp,"goto if false(%d)", l->cursor);
			break;
		}
		default:
		{
			text_fprintf(fp,"not implemented");
			break;
		}
	}
	return index;
}
