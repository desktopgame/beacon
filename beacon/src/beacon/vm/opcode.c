#include "opcode.h"
#include "opcode_buf.h"
#include <stdio.h>
#include "../util/text.h"

int PrintOpcode(Vector* source, int index) {
	return FprintOpcode(stdout, source, index);
}

int FprintOpcode(FILE* fp, Vector* source, int index) {
	VectorItem e = AtVector(source, index);
	Opcode code = (Opcode)e;
	fprintf(fp,"%d: ", index);
	switch (code) {
		//int & int
		case OP_IADD:
			fprintf(fp,"iadd");
			break;
		case OP_ISUB:
			fprintf(fp,"isub");
			break;
		case OP_IMUL:
			fprintf(fp,"imul");
			break;
		case OP_IDIV:
			fprintf(fp,"idiv");
			break;
		case OP_IMOD:
			fprintf(fp,"imod");
			break;
		case OP_IBIT_OR:
			fprintf(fp,"ibit or");
			break;
		case OP_ILOGIC_OR:
			fprintf(fp,"ilogic or");
			break;
		case OP_IBIT_AND:
			fprintf(fp,"ibit and");
			break;
		case OP_ILOGIC_AND:
			fprintf(fp,"ilogic and");
			break;
		case OP_IEQ:
			fprintf(fp,"ieq");
			break;
		case OP_INOTEQ:
			fprintf(fp,"inoteq");
			break;
		case OP_IGT:
			fprintf(fp,"igt");
			break;
		case OP_IGE:
			fprintf(fp,"ige");
			break;
		case OP_ILT:
			fprintf(fp,"ilt");
			break;
		case OP_ILE:
			fprintf(fp,"ile");
			break;
		case OP_ILSH:
			fprintf(fp,"ilsh");
			break;
		case OP_IRSH:
			fprintf(fp,"irsh");
			break;
		case OP_IEXCOR:
			fprintf(fp,"iexcor");
			break;
		case OP_IFLIP:
			fprintf(fp, "iflip");
			break;
		case OP_CEQ:
			fprintf(fp, "ceq");
			break;
		case OP_CNOTEQ:
			fprintf(fp, "cnoteq");
			break;
		case OP_CGT:
			fprintf(fp, "cgt");
			break;
		case OP_CGE:
			fprintf(fp, "cge");
			break;
		case OP_CLT:
			fprintf(fp, "clt");
			break;
		case OP_CLE:
			fprintf(fp, "cle");
			break;
		//double & double
		case OP_DADD:
			fprintf(fp,"dadd");
			break;
		case OP_DSUB:
			fprintf(fp,"dsub");
			break;
		case OP_DMUL:
			fprintf(fp,"mul");
			break;
		case OP_DDIV:
			fprintf(fp,"ddiv");
			break;
		case OP_DMOD:
			fprintf(fp,"dmod");
			break;
		case OP_DEQ:
			fprintf(fp,"deq");
			break;
		case OP_DNOTEQ:
			fprintf(fp,"dnoteq");
			break;
		case OP_DGT:
			fprintf(fp,"dgt");
			break;
		case OP_DGE:
			fprintf(fp,"dge");
			break;
		case OP_DLT:
			fprintf(fp,"dlt");
			break;
		case OP_DLE:
			fprintf(fp,"dle");
			break;
		case OP_INEG:
			fprintf(fp,"ineg");
			break;
		case OP_DNEG:
			fprintf(fp,"dneg");
			break;
		case OP_BNOT:
			fprintf(fp,"bnot");
			break;
		case OP_BBIT_OR:
			fprintf(fp,"bbit_or");
			break;
		case OP_BLOGIC_OR:
			fprintf(fp,"blogic_or");
			break;
		case OP_BBIT_AND:
			fprintf(fp,"bbit_and");
			break;
		case OP_BLOGIC_AND:
			fprintf(fp,"blogic_and");
			break;
		case OP_BEXCOR:
			fprintf(fp, "bexcor");
			break;
		case OP_BFLIP:
			fprintf(fp, "bflip");
			break;
		//push const
		case OP_ICONST:
		{
			int a = AtVector(source, ++index);
			fprintf(fp,"push iconst(%d)", a);
			break;
		}
		case OP_DCONST:
		{
			int a = AtVector(source, ++index);
			fprintf(fp,"push dconst(%d)", a);
			break;
		}
		case OP_CCONST:
		{
			int a = AtVector(source, ++index);
			fprintf(fp,"push cconst(%d)", a);
			break;
		}
		case OP_SCONST:
		{
			int a = AtVector(source, ++index);
			fprintf(fp,"push sconst(%d)", a);
			break;
		}
		case OP_TRUE:
		{
			fprintf(fp,"true");
			break;
		}
		case OP_FALSE:
		{
			fprintf(fp,"false");
			break;
		}
		case OP_NULL:
		{
			fprintf(fp,"null");
			break;
		}
		case OP_DUP:
		{
			fprintf(fp,"dup");
			break;
		}
		case OP_POP:
		{
			fprintf(fp,"pop");
			break;
		}
		case OP_NOP:
		{
			fprintf(fp,"nop");
			break;
		}
		//store,load
		case OP_PUT_FIELD:
		{
			int a = (int)AtVector(source, ++index);
			fprintf(fp,"put field(%d)", a);
			break;
		}
		case OP_GET_FIELD:
		{
			//int a = (int)AtVector(source, ++index);
			int b = (int)AtVector(source, ++index);
			fprintf(fp,"get field(%d)", b);
			break;
		}
		case OP_PUT_STATIC:
		{
			int a = (int)AtVector(source, ++index);
			int b = (int)AtVector(source, ++index);
			fprintf(fp,"put static(%d %d)", a, b);
			break;
		}
		case OP_GET_STATIC:
		{
			int a = (int)AtVector(source, ++index);
			int b = (int)AtVector(source, ++index);
			fprintf(fp,"get static(%d %d)", a, b);
			break;
		}
		case OP_PUT_PROPERTY:
		{
			int a = (int)AtVector(source, ++index);
			fprintf(fp,"put property(%d)", a);
			break;
		}
		case OP_GET_PROPERTY:
		{
			//int a = (int)AtVector(source, ++index);
			int b = (int)AtVector(source, ++index);
			fprintf(fp,"get property(%d)", b);
			break;
		}
		case OP_PUT_STATIC_PROPERTY:
		{
			int a = (int)AtVector(source, ++index);
			int b = (int)AtVector(source, ++index);
			fprintf(fp,"put static_property(%d %d)", a, b);
			break;
		}
		case OP_GET_STATIC_PROPERTY:
		{
			int a = (int)AtVector(source, ++index);
			int b = (int)AtVector(source, ++index);
			fprintf(fp,"get static_property(%d %d)", a, b);
			break;
		}
		case OP_STORE:
		{
			int a = (int)AtVector(source, ++index);
			fprintf(fp,"store %d", a);
			break;
		}
		case OP_LOAD:
		{
			int a = (int)AtVector(source, ++index);
			fprintf(fp,"load %d", a);
			break;
		}
		case OP_DOWN_AS:
		{
			fprintf(fp,"down as");
			break;
		}
		case OP_UP_AS:
		{
			fprintf(fp,"up as");
			break;
		}
		//invoke
		case OP_CHAIN_THIS:
		{
			int a = (int)AtVector(source, ++index);
			int b = (int)AtVector(source, ++index);
			fprintf(fp,"chain this(%d %d)", a, b);
			break;
		}
		case OP_CHAIN_SUPER:
		{
			int a = (int)AtVector(source, ++index);
			int b = (int)AtVector(source, ++index);
			fprintf(fp,"chain super(%d %d)", a, b);
			break;
		}
		case OP_NEW_OBJECT:
		{
			fprintf(fp,"new object");
			break;
		}
		case OP_ALLOC_FIELD:
		{
			int a = (int)AtVector(source, ++index);
			fprintf(fp,"alloc field(%d)", a);
			break;
		}
		case OP_NEW_INSTANCE:
		{
			int a = (int)AtVector(source, ++index);
			int b = (int)AtVector(source, ++index);
			fprintf(fp,"new instance(%d %d)", a, b);
			break;
		}
		case OP_THIS:
		{
			fprintf(fp,"this");
			break;
		}
		case OP_SUPER:
		{
			fprintf(fp,"super");
			break;
		}
		case OP_INVOKEVIRTUAL:
		{
			int a = (int)AtVector(source, ++index);
			fprintf(fp,"invoke virtual(%d)", a);
			break;
		}
		case OP_INVOKESTATIC:
		{
			int a = (int)AtVector(source, ++index);
			int b = (int)AtVector(source, ++index);
			fprintf(fp,"invoke static(%d %d)", a, b);
			break;
		}
		case OP_INVOKESPECIAL:
		{
			int a = (int)AtVector(source, ++index);
			fprintf(fp,"invoke special(%d)", a);
			break;
		}
		case OP_INVOKEINTERFACE:
		{
			int a = (int)AtVector(source, ++index);
			int b = (int)AtVector(source, ++index);
			fprintf(fp,"invoke interface(%d %d)", a, b);
			break;
		}
		case OP_INVOKEOPERATOR:
		{
			int a = (int)AtVector(source, ++index);
			fprintf(fp,"invoke operator(%d)", a);
			break;
		}

		case OP_CORO_INIT:
		{
			int a = (int)AtVector(source, ++index);
			printf("coro init(%d)", a);
			break;
		}
		case OP_CORO_NEXT:
		{
			printf("coro next");
			break;
		}
		case OP_CORO_EXIT:
		{
			printf("coro exit");
			break;
		}
		case OP_CORO_RESUME:
		{
			printf("coro resume");
			break;
		}
		case OP_CORO_CURRENT:
		{
			printf("core current");
			break;
		}
		case OP_CORO_SWAP_SELF:
		{
			printf("core swap");
			break;
		}
		case OP_GENERIC_ADD:
		{
			fprintf(fp, "generic add");
			break;
		}
		case OP_GENERIC_ENTER:
		{
			int a = (int)AtVector(source, ++index);
			fprintf(fp, "generic enter(%d)", a);
			break;
		}
		case OP_GENERIC_UNIQUE_TYPE:
		{
			int a = (int)AtVector(source, ++index);
			fprintf(fp, "generic unique_type(%d)", a);
			break;
		}
		case OP_GENERIC_INSTANCE_TYPE:
		{
			int a = (int)AtVector(source, ++index);
			fprintf(fp, "generic instance_type(%d)", a);
			break;
		}
		case OP_GENERIC_STATIC_TYPE:
		{
			int a = (int)AtVector(source, ++index);
			fprintf(fp, "generic static_type(%d)", a);
			break;
		}
		case OP_GENERIC_EXIT:
		{
			fprintf(fp, "generic exit");
			break;
		}
		case OP_RETURN:
		{
			fprintf(fp,"return");
			break;
		}
		case OP_THROW:
		{
			fprintf(fp,"throw");
			//int a = (int)AtVector(source, ++index);
			break;
		}
		case OP_TRY_ENTER:
		{
			fprintf(fp,"try enter");
			break;
		}
		case OP_TRY_EXIT:
		{
			fprintf(fp,"try exit");
			break;
		}
		case OP_TRY_CLEAR:
		{
			fprintf(fp,"try clear");
			break;
		}
		case OP_DEFER_ENTER:
		{
			fprintf(fp, "defer enter");
			break;
		}
		case OP_DEFER_REGISTER:
		{
			Label* l = (Label*)AtVector(source, ++index);
			fprintf(fp, "defer enter(%d)", l->Cursor);
			break;
		}
		case OP_DEFER_EXIT:
		{
			fprintf(fp, "defer exit");
			break;
		}
		case OP_HEXCEPTION:
		{
			fprintf(fp,"hexception");
			break;
		}
		case OP_INSTANCEOF:
		{
			fprintf(fp,"instanceof");
			break;
		}
		case OP_BREAKPOINT:
		{
			fprintf(fp,"breakpoint");
			break;
		}
		//goto
		case OP_GOTO:
		{
			Label* l = (Label*)AtVector(source, ++index);
			fprintf(fp,"goto(%d)", l->Cursor);
			break;
		}
		case OP_GOTO_IF_TRUE:
		{
			Label* l = (Label*)AtVector(source, ++index);
			fprintf(fp,"goto if true(%d)", l->Cursor);
			break;
		}
		case OP_GOTO_IF_FALSE:
		{
			Label* l = (Label*)AtVector(source, ++index);
			fprintf(fp,"goto if false(%d)", l->Cursor);
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
