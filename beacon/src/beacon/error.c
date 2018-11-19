#include "error.h"
#include "env/script_context.h"
#include "util/mem.h"
#include "util/text.h"
#include "util/string_buffer.h"

#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif
static BCErrorID gGlobalPanic = BCERROR_NONE_T;
static StringView gPanicFile = ZERO_VIEW;
static StringView gLastMessage = ZERO_VIEW;
static int gPanicLineNo = -1;
static int gPanicColumn = -1;
static void check_abort(bc_ScriptContext* sctx);

void bc_Panic(BCErrorID id, ...) {
	va_list ap;
	va_start(ap, id);
	bc_Vpanic(id, ap);
	va_end(ap);
}

void bc_Vpanic(BCErrorID id, va_list ap) {
	char* fmt = bc_Vfpanic(id, ap);
	gGlobalPanic = id;
	gLastMessage = InternString(fmt);
	bc_ScriptContext* sctx = bc_GetCurrentScriptContext();
	if(sctx->IsPrintError) {
		fprintf(stderr, "%s", fmt);
	}
	MEM_FREE(fmt);
#if defined(_MSC_VER)
	#if !defined(DEBUG)
		check_abort(sctx);
	#endif
#else
	#if !defined(DEBUG)
		check_abort(sctx);
	#endif
#endif
}

char* bc_Fpanic(BCErrorID id, ...) {
	va_list ap;
	va_start(ap, id);
	char* ret = bc_Vfpanic(id, ap);
	va_end(ap);
	MEM_FREE(ret);
	return ret;
}

char* bc_Vfpanic(BCErrorID id, va_list ap) {
	char* fmt = NULL;
	//bool aa = cc_test(ccstate_toplevel);
	switch(id) {
		case BCERROR_NONE_T:
			break;
		case BCERROR_GENERIC_T:
			fmt = "%s";
			break;
		case BCERROR_PARSE_T:
			fmt = "%s";
			break;
		case BCERROR_REQUIRE_NOT_FOUND_T:
			fmt = "not found of required file: %s";
			break;
		case BCERROR_OVERWRAP_PARAMETER_NAME_T:
			fmt = "overwrap of parameter name: %s#%s(%s)";
			break;
		case BCERROR_OVERWRAP_TYPE_TYPE_PARAMETER_NAME_T:
			fmt = "overwrap of type parameter name: %s[%s]";
			break;
		case BCERROR_OVERWRAP_METHOD_TYPE_PARAMETER_NAME_T:
			fmt = "overwrap of type parameter name: %s#%s[%s]";
			break;
		case BCERROR_OVERWRAP_VARIABLE_NAME_T:
			fmt = "overwrap of variable name: %s";
			break;
		case BCERROR_OVERWRAP_MODIFIER_T:
			fmt = "overwrap of modifier: %s";
			break;
		case BCERROR_OVERWRAP_FIELD_NAME_T:
			fmt = "overwrap of field name: %s @%s";
			break;
		case BCERROR_OVERWRAP_PROPERTY_NAME_T:
			fmt = "overwrap of Property name: %s @%s";
			break;


		case BCERROR_NATIVE_FIELD_T:
			fmt = "`native` modifier is can't use for field: %s#%s";
			break;
		case BCERROR_ABSTRACT_FIELD_T:
			fmt = "`abstract` modifier is can't use for field: %s#%s";
			break;
		case BCERROR_OVERRIDE_FIELD_T:
			fmt = "`override` modifier is can't use for field: %s#%s";
			break;


		case BCERROR_STATIC_OVERRIDE_METHOD_T:
			fmt = "`static` and `override` modifier is can't use with: %s#%s";
			break;
		case BCERROR_ABSTRACT_OVERRIDE_METHOD_T:
			fmt = "`abstract` and `override` modifier is can't use with: %s#%s";
			break;
		case BCERROR_ABSTRACT_STATIC_METHOD_T:
			fmt = "`abstract` and `static` modifier is can't use with: %s#%s";
			break;


		case BCERROR_EMPTY_STMT_METHOD_T:
			fmt = "must be not empty statement if modifier of method is native or abstract: %s";
			break;
		case BCERROR_NOT_EMPTY_STMT_METHOD_T:
			fmt = "must be empty statement if modifier of method is native or abstract: %s";
			break;


		case BCERROR_RETURN_VALUE_VOID_METHOD_T:
			fmt = "must be not return a value if return type of Void: %s#%s";
			break;
		case BCERROR_NOT_RETURN_VALUE_NOT_VOID_METHOD_T:
			fmt = "must be return a value if return type of not Void: %s#%s";
			break;
		case BCERROR_RETURN_VALUE_TYPE_IS_NOT_COMPATIBLE_NOT_VOID_METHOD_T:
			fmt = "return value is must be compatible to method return type: %s#%s";
			break;


		case BCERROR_YIELD_RETURN_VALUE_TYPE_IS_NOT_COMPATIBLE_T:
			fmt = "yield return value is must be compatible to method return type: %s#%s";
			break;


		case BCERROR_IF_EXPR_TYPE_OF_NOT_BOOL_T:
			fmt = "must be condition formula is bool: %s";
			break;
		case BCERROR_WHILE_EXPR_TYPE_OF_NOT_BOOL_T:
			fmt = "must be condition formula is bool: %s";
			break;

		case BCERROR_BREAK_AT_NOT_LOOP_T:
			fmt = "can use `break` only in loop statement";
			break;
		case BCERROR_CONTINUE_AT_NOT_LOOP_T:
			fmt = "can use `continue` only in loop statement";
			break;


		case BCERROR_ACCESS_TO_THIS_AT_STATIC_METHOD_T:
			fmt = "access to `this` at static method: %s#%s";
			break;
		case BCERROR_ACCESS_TO_SUPER_AT_STATIC_METHOD_T:
			fmt = "access to `super` at static method: %s#%s";
			break;


		case BCERROR_ASSIGN_TO_FINAL_FIELD_T:
			fmt = "can't assign to `final` attributed field: %s#%s";
			break;
		case BCERROR_NOT_DEFAULT_VALUE_STATIC_FINAL_FIELD_T:
			fmt = "need default value: %s#%s";
			break;
		case BCERROR_NOT_INITIAL_FIELD_NOT_INITIALIZED_AT_CTOR_T:
			fmt = "must be initialize a `final` attributed field: %s#%s";
			break;
		case BCERROR_FIELD_DEFAULT_VALUE_NOT_COMPATIBLE_TO_FIELD_TYPE_T:
			fmt = "field initializer result type is not compatible to field type: %s#%s";
			break;
		case BCERROR_LHS_IS_NOT_SUBSCRIPT_T:
			fmt = "lhs is not subscript: %s";
			break;



		case BCERROR_ARG_COUNT_NOT2_BIOPERATOR_T:
			fmt = "illegal of parameter count, must be binary operator argument count is one.: %s#%s";
			break;
		case BCERROR_ARG_COUNT_NOT1_UOPERATOR_T:
			fmt = "illegal of parameter count, must be unary operator argument count is zero.: %s#%s";
			break;
		case BCERROR_ARG_COUNT_NOT2_SUBSCRIPT_SET_OP_T:
			fmt = "set";
			break;
		case BCERROR_ARG_COUNT_NOT1_SUBSCRIPT_GET_OP_T:
			fmt = "get";
			break;
		case BCERROR_RETURN_TYPE_NOT_BOOL_COMPARE_OPERATOR_T:
			fmt = "return type of `compare` operator is must be bool: %s#%s";
			break;
		case BCERROR_RETURN_TYPE_NOT_BOOL_NOT_OPERATOR_T:
			fmt = "return type of `not` operator is must be bool: %s#%s";
			break;
		case BCERROR_RETURN_TYPE_NOT_EQUAL_NEGATIVE_OPERATOR_T:
			fmt = "return type of `negative` operator is must be equal from declared type: %s#%s";
			break;


		case BCERROR_THROWN_NOT_EXCEPTION_TYPE_T:
			fmt = "must be thrown Object type compatible to `exception`: %s";
			break;


		case BCERROR_ASSIGN_NOT_COMPATIBLE_LOCAL_T:
			fmt = "assign expression is has not type compatible: %s";
			break;
		case BCERROR_ASSIGN_NOT_COMPATIBLE_FIELD_T:
			fmt = "assign expression is has not type compatible: %s#%s";
			break;
		case BCERROR_ASSIGN_NOT_COMPATIBLE_PROPERTY_T:
			fmt = "assign expression is has not type compatible: %s#%s";
			break;


		case BCERROR_AUTO_CHAIN_CTOR_NOT_FOUND_T:
			fmt = "need chain constructor if not found of super class empty constructor: %s#new";
			break;
		case BCERROR_EXPLICIT_CHAIN_CTOR_NOT_FOUND_T:
			fmt = "not found chain constructor: %s#new";
			break;


		case BCERROR_NEW_INSTANCE_UNDEFINED_CLASS_T:
			fmt = "undefined class: %s";
			break;
		case BCERROR_REF_UNDEFINED_LOCAL_VARIABLE_T:
			fmt = "undefined variable: %s";
			break;
		case BCERROR_UNDEFINED_PROPERTY_T:
			fmt = "undefined Property: %s#%s";
			break;

		case BCERROR_ASSIGN_TO_INVOKE_T:
			fmt = "can't assign to invoke: %s";
			break;

		case BCERROR_INTERFACE_HAS_FIELD_T:
			fmt = "interface can't has not field: %s#%s";
			break;
		case BCERROR_INTERFACE_HAS_CTOR_T:
			fmt = "interface can't has not constructor: %s#new";
			break;
		case BCERROR_INTERFACE_HAS_OPOV_T:
			fmt = "interface can't has not operator: %s#%s";
			break;
		case BCERROR_INTERFACE_HAS_PRIVATE_MEMBER_T:
			fmt = "interface can't has not private member: %s#%s";
			break;

		case BCERROR_INVOKE_BOUND_UNDEFINED_METHOD_T:
			fmt = "undefined method: %s#%s";
			break;
		case BCERROR_INVOKE_INSTANCE_UNDEFINED_METHOD_T:
			fmt = "undefined method: %s#%s";
			break;
		case BCERROR_INVOKE_STATIC_UNDEFINED_METHOD_T:
			fmt = "undefined method: %s#%s";
			break;

		case BCERROR_NEW_INSTANCE_UNDEFINED_CTOR_T:
			fmt = "undefined ctor: %s";
			break;

		case BCERROR_UNDEFINED_COMPARE_OPERATOR_T:
		case BCERROR_UNDEFINED_ARITHMETIC_OPERATOR_T:
		case BCERROR_UNDEFINED_SHIFT_OPERATOR_T:
		case BCERROR_UNDEFINED_BIT_OPERATOR_T:
		case BCERROR_UNDEFINED_LOGIC_OPERATOR_T:
		case BCERROR_UNDEFINED_EXCOR_OPERATOR_T:
			fmt = "undefined operator: %s";
			break;

		case BCERROR_VOID_ASSIGN_T:
			fmt = "can't assign. type is void.";
			break;
		case BCERROR_VOID_DECL_T:
			fmt = "can't decl. type is void.";
			break;

		case BCERROR_CAST_NOT_COMPATIBLE_T:
			fmt = "not compatible types: %s as %s";
			break;

		case BCERROR_UNDEFINED_TYPE_DECL_T:
			fmt = "undefined type: %s";
			break;

		case BCERROR_UNDEFINED_TYPE_STATIC_INVOKE_T:
			fmt = "static method not found: %s#%s";
			break;

		case BCERROR_UNDEFINED_NAME_BOUND_INVOKE_T:
			fmt = "instance method not found: %s#%s";
			break;

		case BCERROR_CONSTRUCT_ABSTRACT_TYPE_T:
			fmt = "can't construct a abstract type by new operator: %s";
			break;
		case BCERROR_CAN_T_RESOLVE_LAMBDA_T:
			fmt = "can't resolve lambda interface type: %s@%s";
			break;
		case BCERROR_NOT_FUNCTIONAL_INTERFACE_T:
			fmt = "not functional interface: %s";
			break;
		case BCERROR_CLASS_FIRST_T:
			fmt = "must be class first: %s";
			break;
		case BCERROR_MULTI_EQINTERFACE_T:
			fmt = "should'nt implement equal interface a multiple: %s";
			break;
		case BCERROR_INTERFACE_ONLY_T:
			fmt = "must be interface only: %s";
			break;
		case BCERROR_CHAIN_T:
			fmt = "error %s";
			break;
		case BCERROR_ABSTRACT_METHOD_BY_T:
			fmt = "abstract method should be defined on the abstract class: %s";
			break;
		case BCERROR_NOT_IMPLEMENT_INTERFACE_T:
			fmt = "must be implement: %s @%s";
			break;
		case BCERROR_NOT_IMPLEMENT_ABSTRACT_METHOD_T:
			fmt = "must be implement: %s @%s";
			break;
		case BCERROR_PRIVATE_OPERATOR_T:
			fmt = "must be public a access level of operator: %s";
			break;
		case BCERROR_INVALID_PROPERTY_DECL_T:
			fmt = "can't use abbrev expression for only one Property accessor: %s#%s";
			break;
		case BCERROR_CAN_T_ACCESS_FIELD_T:
			fmt = "can't access field: %s#%s";
			break;
		case BCERROR_CAN_T_ACCESS_PROPERTY_T:
			fmt = "can't access Property: %s#%s";
			break;
		case BCERROR_INVALID_ACCESS_LEVEL_OF_PROPERTY_T:
			fmt = "access level of Property accessor must be secure level more than Property: %s#%s";
			break;
		case BCERROR_SPECIFIED_BOTH_PROPERTY_ACCESSOR_T:
			fmt = "specified both access level of Property accessor: %s#%s";
			break;
		default:
			{
				return bc_Strdup("if shown this message, it compiler bug\n");
			}
	}
	Buffer* sbuf = NewBuffer();
	//メインメッセージを出力
	char block[256] = {0};
	vsprintf(block, fmt, ap);
	AppendsBuffer(sbuf, block);
	AppendBuffer(sbuf, '\n');
	//行番号など出力
	sprintf(block, "file=%s line=%d column=%d\n",
		Ref2Str(gPanicFile),
		gPanicLineNo,
		gPanicColumn
	);
	AppendsBuffer(sbuf, block);
	return ReleaseBuffer(sbuf);
}

void bc_Recover() {
	gGlobalPanic = BCERROR_NONE_T;
	gPanicFile = ZERO_VIEW;
	gPanicLineNo = -1;
	gPanicColumn = -1;
	gLastMessage = ZERO_VIEW;
}

void bc_SetPanicFile(const char* filename) {
	if(filename == NULL) {
		filename = "NULL";
	}
	gPanicFile = InternString(filename);
}

void bc_SetPanicLine(int lineno) {
	gPanicLineNo = lineno;
}

void bc_SetPanicColumn(int column) {
	gPanicColumn = column;
}

StringView bc_GetPanicMessage() {
	return gLastMessage;
}

BCErrorID bc_GetLastPanic() {
	return gGlobalPanic;
}
//private
static void check_abort(bc_ScriptContext* sctx) {
	if(sctx->IsAbortOnError) {
		abort();
	}
}