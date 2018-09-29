#include "error.h"
#include "env/script_context.h"
#include "util/mem.h"
#include "util/text.h"
#include "util/system.h"
#include "util/string_buffer.h"

#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif
static bc_error_id gGlobalError = bcerror_none_T;
static string_view gErrorFile = ZERO_VIEW;
static string_view gLastMessage = ZERO_VIEW;
static int gErrorLineNo = -1;
static int gErrorColumn = -1;
static void check_abort(script_context* sctx);

void bc_error_throw(bc_error_id id, ...) {
	va_list ap;
	va_start(ap, id);
	bc_error_vthrow(id, ap);
	va_end(ap);
}

void bc_error_vthrow(bc_error_id id, va_list ap) {
	char* fmt = bc_error_vformat(id, ap);
	gGlobalError = id;
	gLastMessage = InternString(fmt);
	script_context* sctx = script_context_get_current();
	if(sctx->print_error) {
		fprintf(stderr, "%s", fmt);
	}
	MEM_FREE(fmt);
#if defined(_MSC_VER)
	#if !defined(_DEBUG)
		check_abort(sctx);
	#endif
#else
	#if !defined(DEBUG)
		check_abort(sctx);
	#endif
#endif
}

char* bc_error_format(bc_error_id id, ...) {
	va_list ap;
	va_start(ap, id);
	char* ret = bc_error_vformat(id, ap);
	va_end(ap);
	MEM_FREE(ret);
	return ret;
}

char* bc_error_vformat(bc_error_id id, va_list ap) {
	char* fmt = NULL;
	//bool aa = cc_test(ccstate_toplevel);
	switch(id) {
		case bcerror_none_T:
			break;
		case bcerror_generic_T:
			fmt = "%s";
			break;
		case bcerror_parse_T:
			fmt = "%s";
			break;
		case bcerror_require_not_found_T:
			fmt = "not found of required file: %s";
			break;
		case bcerror_overwrap_parameter_name_T:
			fmt = "overwrap of parameter name: %s#%s(%s)";
			break;
		case bcerror_overwrap_type_type_parameter_name_T:
			fmt = "overwrap of type parameter name: %s[%s]";
			break;
		case bcerror_overwrap_method_type_parameter_name_T:
			fmt = "overwrap of type parameter name: %s#%s[%s]";
			break;
		case bcerror_overwrap_variable_name_T:
			fmt = "overwrap of variable name: %s";
			break;
		case bcerror_overwrap_modifier_T:
			fmt = "overwrap of modifier: %s";
			break;
		case bcerror_overwrap_field_name_T:
			fmt = "overwrap of field name: %s @%s";
			break;
		case bcerror_overwrap_property_name_T:
			fmt = "overwrap of property name: %s @%s";
			break;


		case bcerror_native_field_T:
			fmt = "`native` modifier is can't use for field: %s#%s";
			break;
		case bcerror_abstract_field_T:
			fmt = "`abstract` modifier is can't use for field: %s#%s";
			break;
		case bcerror_override_field_T:
			fmt = "`override` modifier is can't use for field: %s#%s";
			break;


		case bcerror_static_override_method_T:
			fmt = "`static` and `override` modifier is can't use with: %s#%s";
			break;
		case bcerror_abstract_override_method_T:
			fmt = "`abstract` and `override` modifier is can't use with: %s#%s";
			break;
		case bcerror_abstract_static_method_T:
			fmt = "`abstract` and `static` modifier is can't use with: %s#%s";
			break;


		case bcerror_empty_stmt_method_T:
			fmt = "must be not empty statement if modifier of method is native or abstract: %s";
			break;
		case bcerror_not_empty_stmt_method_T:
			fmt = "must be empty statement if modifier of method is native or abstract: %s";
			break;


		case bcerror_return_value_void_method_T:
			fmt = "must be not return a value if return type of Void: %s#%s";
			break;
		case bcerror_not_return_value_not_void_method_T:
			fmt = "must be return a value if return type of not Void: %s#%s";
			break;
		case bcerror_return_value_type_is_not_compatible_not_void_method_T:
			fmt = "return value is must be compatible to method return type: %s#%s";
			break;


		case bcerror_yield_return_value_type_is_not_compatible_T:
			fmt = "yield return value is must be compatible to method return type: %s#%s";
			break;


		case bcerror_if_expr_type_of_not_bool_T:
			fmt = "must be condition formula is bool: %s";
			break;
		case bcerror_while_expr_type_of_not_bool_T:
			fmt = "must be condition formula is bool: %s";
			break;

		case bcerror_break_at_not_loop_T:
			fmt = "can use `break` only in loop statement";
			break;
		case bcerror_continue_at_not_loop_T:
			fmt = "can use `continue` only in loop statement";
			break;


		case bcerror_access_to_this_at_static_method_T:
			fmt = "access to `this` at static method: %s#%s";
			break;
		case bcerror_access_to_super_at_static_method_T:
			fmt = "access to `super` at static method: %s#%s";
			break;


		case bcerror_assign_to_final_field_T:
			fmt = "can't assign to `final` attributed field: %s#%s";
			break;
		case bcerror_not_default_value_static_final_field_T:
			fmt = "need default value: %s#%s";
			break;
		case bcerror_not_initial_field_not_initialized_at_ctor_T:
			fmt = "must be initialize a `final` attributed field: %s#%s";
			break;
		case bcerror_field_default_value_not_compatible_to_field_type_T:
			fmt = "field initializer result type is not compatible to field type: %s#%s";
			break;
		case bcerror_lhs_is_not_subscript_T:
			fmt = "lhs is not subscript: %s";
			break;



		case bcerror_arg_count_not2_bioperator_T:
			fmt = "illegal of parameter count, must be binary operator argument count is one.: %s#%s";
			break;
		case bcerror_arg_count_not1_uoperator_T:
			fmt = "illegal of parameter count, must be unary operator argument count is zero.: %s#%s";
			break;
		case bcerror_arg_count_not2_subscript_set_op_T:
			fmt = "set";
			break;
		case bcerror_arg_count_not1_subscript_get_op_T:
			fmt = "get";
			break;
		case bcerror_return_type_not_bool_compare_operator_T:
			fmt = "return type of `compare` operator is must be bool: %s#%s";
			break;
		case bcerror_return_type_not_bool_not_operator_T:
			fmt = "return type of `not` operator is must be bool: %s#%s";
			break;
		case bcerror_return_type_not_equal_negative_operator_T:
			fmt = "return type of `negative` operator is must be equal from declared type: %s#%s";
			break;


		case bcerror_thrown_not_exception_type_T:
			fmt = "must be thrown object type compatible to `exception`: %s";
			break;


		case bcerror_assign_not_compatible_local_T:
			fmt = "assign expression is has not type compatible: %s";
			break;
		case bcerror_assign_not_compatible_field_T:
			fmt = "assign expression is has not type compatible: %s#%s";
			break;
		case bcerror_assign_not_compatible_property_T:
			fmt = "assign expression is has not type compatible: %s#%s";
			break;


		case bcerror_auto_chain_ctor_not_found_T:
			fmt = "need chain constructor if not found of super class empty constructor: %s#new";
			break;
		case bcerror_explicit_chain_ctor_not_found_T:
			fmt = "not found chain constructor: %s#new";
			break;


		case bcerror_new_instance_undefined_class_T:
			fmt = "undefined class: %s";
			break;
		case bcerror_ref_undefined_local_variable_T:
			fmt = "undefined variable: %s";
			break;
		case bcerror_undefined_property_T:
			fmt = "undefined property: %s#%s";
			break;

		case bcerror_assign_to_invoke_T:
			fmt = "can't assign to invoke: %s";
			break;

		case bcerror_interface_has_field_T:
			fmt = "interface can't has not field: %s#%s";
			break;
		case bcerror_interface_has_ctor_T:
			fmt = "interface can't has not constructor: %s#new";
			break;
		case bcerror_interface_has_opov_T:
			fmt = "interface can't has not operator: %s#%s";
			break;
		case bcerror_interface_has_private_member_T:
			fmt = "interface can't has not private member: %s#%s";
			break;

		case bcerror_invoke_bound_undefined_method_T:
			fmt = "undefined method: %s#%s";
			break;
		case bcerror_invoke_instance_undefined_method_T:
			fmt = "undefined method: %s#%s";
			break;
		case bcerror_invoke_static_undefined_method_T:
			fmt = "undefined method: %s#%s";
			break;

		case bcerror_new_instance_undefined_ctor_T:
			fmt = "undefined ctor: %s";
			break;

		case bcerror_undefined_compare_operator_T:
		case bcerror_undefined_arithmetic_operator_T:
		case bcerror_undefined_shift_operator_T:
		case bcerror_undefined_bit_operator_T:
		case bcerror_undefined_logic_operator_T:
		case bcerror_undefined_excor_operator_T:
			fmt = "undefined operator: %s";
			break;

		case bcerror_void_assign_T:
			fmt = "can't assign. type is void.";
			break;
		case bcerror_void_decl_T:
			fmt = "can't decl. type is void.";
			break;

		case bcerror_cast_not_compatible_T:
			fmt = "not compatible types: %s as %s";
			break;

		case bcerror_undefined_type_decl_T:
			fmt = "undefined type: %s";
			break;

		case bcerror_undefined_type_static_invoke_T:
			fmt = "static method not found: %s#%s";
			break;

		case bcerror_undefined_name_bound_invoke_T:
			fmt = "instance method not found: %s#%s";
			break;

		case bcerror_construct_abstract_type_T:
			fmt = "can't construct a abstract type by new operator: %s";
			break;
		case bcerror_can_t_resolve_lambda_T:
			fmt = "can't resolve lambda interface type: %s@%s";
			break;
		case bcerror_not_functional_interface_T:
			fmt = "not functional interface: %s";
			break;
		case bcerror_class_first_T:
			fmt = "must be class first: %s";
			break;
		case bcerror_multi_eqinterface_T:
			fmt = "should'nt implement equal interface a multiple: %s";
			break;
		case bcerror_interface_only_T:
			fmt = "must be interface only: %s";
			break;
		case bcerror_chain_T:
			fmt = "error %s";
			break;
		case bcerror_abstract_method_by_T:
			fmt = "abstract method should be defined on the abstract class: %s";
			break;
		case bcerror_not_implement_interface_T:
			fmt = "must be implement: %s @%s";
			break;
		case bcerror_not_implement_abstract_method_T:
			fmt = "must be implement: %s @%s";
			break;
		case bcerror_private_operator_T:
			fmt = "must be public a access level of operator: %s";
			break;
		case bcerror_invalid_property_decl_T:
			fmt = "can't use abbrev expression for only one property accessor: %s#%s";
			break;
		case bcerror_can_t_access_field_T:
			fmt = "can't access field: %s#%s";
			break;
		case bcerror_can_t_access_property_T:
			fmt = "can't access property: %s#%s";
			break;
		case bcerror_invalid_access_level_of_property_T:
			fmt = "access level of property accessor must be secure level more than property: %s#%s";
			break;
		case bcerror_specified_both_property_accessor_T:
			fmt = "specified both access level of property accessor: %s#%s";
			break;
		default:
			{
				return text_strdup("if shown this message, it compiler bug\n");
			}
	}
	string_buffer* sbuf = string_buffer_new();
	//メインメッセージを出力
	char block[256] = {0};
	vsprintf(block, fmt, ap);
	string_buffer_appends(sbuf, block);
	string_buffer_append(sbuf, '\n');
	//行番号など出力
	sprintf(block, "file=%s line=%d column=%d\n",
		Ref2Str(gErrorFile),
		gErrorLineNo,
		gErrorColumn
	);
	string_buffer_appends(sbuf, block);
	return string_buffer_release(sbuf);
}

void bc_error_clear() {
	gGlobalError = bcerror_none_T;
	gErrorFile = ZERO_VIEW;
	gErrorLineNo = -1;
	gErrorColumn = -1;
	gLastMessage = ZERO_VIEW;
}

void bc_error_file(const char* filename) {
	if(filename == NULL) {
		filename = "NULL";
	}
	gErrorFile = InternString(filename);
}

void bc_error_line(int lineno) {
	gErrorLineNo = lineno;
}

void bc_error_column(int column) {
	gErrorColumn = column;
}

string_view bc_error_message() {
	return gLastMessage;
}

bc_error_id bc_error_last() {
	return gGlobalError;
}
//private
static void check_abort(script_context* sctx) {
	if(sctx->abort_on_error) {
		system_abort();
	}
}