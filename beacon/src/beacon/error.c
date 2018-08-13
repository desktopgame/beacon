#include "error.h"
#include "util/text.h"
#include "util/string_pool.h"

static bc_error_id gGlobalError = bcerror_none;
static string_view gErrorFile = ZERO_VIEW;
static int gErrorLineNo = -1;
static int gErrorColumn = -1;

void bc_error_throw(bc_error_id id, ...) {
	va_list ap;
	va_start(ap, id);
	bc_error_vthrow(id, ap);
	va_end(ap);
}

void bc_error_vthrow(bc_error_id id, va_list ap) {
	char* fmt = NULL;
	//bool aa = cc_test(ccstate_toplevel);
	switch(id) {
		case bcerror_none:
			break;
		case bcerror_generic:
			fmt = "%s";
			break;
		case bcerror_parse:
			fmt = "%s";
			break;
		case bcerror_require_not_found:
			fmt = "not found of required file: %s";
			break;
		case bcerror_overwrap_parameter_name:
			fmt = "overwrap of parameter name: %s#%s(%s)";
			break;
		case bcerror_overwrap_type_type_parameter_name:
			fmt = "overwrap of type parameter name: %s[%s]";
			break;
		case bcerror_overwrap_method_type_parameter_name:
			fmt = "overwrap of type parameter name: %s#%s[%s]";
			break;
		case bcerror_overwrap_variable_name:
			fmt = "overwrap of variable name: %s";
			break;
		case bcerror_overwrap_modifier:
			fmt = "overwrap of modifier: %s";
			break;
		case bcerror_overwrap_field_name:
			fmt = "overwrap of field name: %s @%s";
			break;
		case bcerror_overwrap_property_name:
			fmt = "overwrap of property name: %s @%s";
			break;


		case bcerror_native_field:
			fmt = "`native` modifier is can't use for field: %s#%s";
			break;
		case bcerror_abstract_field:
			fmt = "`abstract` modifier is can't use for field: %s#%s";
			break;
		case bcerror_override_field:
			fmt = "`override` modifier is can't use for field: %s#%s";
			break;


		case bcerror_static_override_method:
			fmt = "`static` and `override` modifier is can't use with: %s#%s";
			break;
		case bcerror_abstract_override_method:
			fmt = "`abstract` and `override` modifier is can't use with: %s#%s";
			break;
		case bcerror_abstract_static_method:
			fmt = "`abstract` and `static` modifier is can't use with: %s#%s";
			break;


		case bcerror_empty_stmt_method:
			fmt = "must be not empty statement if modifier of method is native or abstract: %s";
			break;
		case bcerror_not_empty_stmt_method:
			fmt = "must be empty statement if modifier of method is native or abstract: %s";
			break;


		case bcerror_return_value_void_method:
			fmt = "must be not return a value if return type of Void: %s#%s";
			break;
		case bcerror_not_return_value_not_void_method:
			fmt = "must be return a value if return type of not Void: %s#%s";
			break;
		case bcerror_return_value_type_is_not_compatible_not_void_method:
			fmt = "return value is must be compatible to method return type: %s#%s";
			break;


		case bcerror_yield_return_value_type_is_not_compatible:
			fmt = "yield return value is must be compatible to method return type: %s#%s";
			break;


		case bcerror_if_expr_type_of_not_bool:
			fmt = "must be condition formula is bool: %s";
			break;
		case bcerror_while_expr_type_of_not_bool:
			fmt = "must be condition formula is bool: %s";
			break;

		case bcerror_break_at_not_loop:
			fmt = "can use `break` only in loop statement";
			break;
		case bcerror_continue_at_not_loop:
			fmt = "can use `continue` only in loop statement";
			break;


		case bcerror_access_to_this_at_static_method:
			fmt = "access to `this` at static method: %s#%s";
			break;
		case bcerror_access_to_super_at_static_method:
			fmt = "access to `super` at static method: %s#%s";
			break;


		case bcerror_assign_to_final_field:
			fmt = "can't assign to `final` attributed field: %s#%s";
			break;
		case bcerror_not_default_value_static_final_field:
			fmt = "need default value: %s#%s";
			break;
		case bcerror_not_initial_field_not_initialized_at_ctor:
			fmt = "must be initialize a `final` attributed field: %s#%s";
			break;
		case bcerror_field_default_value_not_compatible_to_field_type:
			fmt = "field initializer result type is not compatible to field type: %s#%s";
			break;



		case bcerror_arg_count_not2_bioperator:
			fmt = "illegal of parameter count, must be binary operator argument count is one.: %s#%s";
			break;
		case bcerror_arg_count_not1_uoperator:
			fmt = "illegal of parameter count, must be unary operator argument count is zero.: %s#%s";
			break;
		case bcerror_return_type_not_bool_compare_operator:
			fmt = "return type of `compare` operator is must be bool: %s#%s";
			break;
		case bcerror_return_type_not_bool_not_operator:
			fmt = "return type of `not` operator is must be bool: %s#%s";
			break;
		case bcerror_return_type_not_equal_negative_operator:
			fmt = "return type of `negative` operator is must be equal from declared type: %s#%s";
			break;


		case bcerror_thrown_not_exception_type:
			fmt = "must be thrown object type compatible to `exception`: %s";
			break;


		case bcerror_assign_not_compatible_local:
			fmt = "assign expression is has not type compatible: %s";
			break;
		case bcerror_assign_not_compatible_field:
			fmt = "assign expression is has not type compatible: %s#%s";
			break;
		case bcerror_assign_not_compatible_property:
			fmt = "assign expression is has not type compatible: %s#%s";
			break;


		case bcerror_auto_chain_ctor_not_found:
			fmt = "need chain constructor if not found of super class empty constructor: %s#new";
			break;
		case bcerror_explicit_chain_ctor_not_found:
			fmt = "not found chain constructor: %s#new";
			break;


		case bcerror_new_instance_undefined_class:
			fmt = "undefined class: %s";
			break;
		case bcerror_ref_undefined_local_variable:
			fmt = "undefined variable: %s";
			break;


		case bcerror_invoke_bound_undefined_method:
			fmt = "undefined method: %s#%s";
			break;
		case bcerror_invoke_instance_undefined_method:
			fmt = "undefined method: %s#%s";
			break;
		case bcerror_invoke_static_undefined_method:
			fmt = "undefined method: %s#%s";
			break;

		case bcerror_new_instance_undefined_ctor:
			fmt = "undefined ctor: %s";
			break;

		case bcerror_undefined_compare_operator:
			fmt = "undefined operator: %s";
			break;

		case bcerror_construct_abstract_type:
			fmt = "can't construct a abstract type by new operator: %s";
			break;
		case bcerror_can_t_resolve_lambda:
			fmt = "can't resolve lambda interface type: %s@%s";
			break;
		case bcerror_not_functional_interface:
			fmt = "not functional interface: %s";
			break;
		case bcerror_class_first:
			fmt = "must be class first: %s";
			break;
		case bcerror_multi_eqinterface:
			fmt = "should'nt implement equal interface a multiple: %s";
			break;
		case bcerror_interface_only:
			fmt = "must be interface only: %s";
			break;
		case bcerror_chain:
			fmt = "error %s";
			break;
		case bcerror_abstract_method_by:
			fmt = "abstract method should be defined on the abstract class: %s";
			break;
		case bcerror_not_implement_interface:
			fmt = "invalid implement: %s @%s";
			break;
		case bcerror_not_implement_abstract_method:
			fmt = "invalid implement: %s @%s";
			break;
		case bcerror_private_operator:
			fmt = "must be public a access level of operator: %s";
			break;
		case bcerror_invalid_property_decl:
			fmt = "can't use abbrev expression for only one property accessor: %s#%s";
			break;
		case bcerror_can_t_access_field:
			fmt = "can't access field: %s#%s";
			break;
		case bcerror_can_t_access_property:
			fmt = "can't access property: %s#%s";
			break;
		case bcerror_invalid_access_level_of_property:
			fmt = "access level of property accessor must be secure level more than property: %s#%s";
			break;
		case bcerror_specified_both_property_accessor:
			fmt = "specified both access level of property accessor: %s#%s";
			break;
		default:
			{
				fprintf(stderr, "if shown this message, it compiler bug\n");
				return;
			}
	}
	gGlobalError = id;
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	fprintf(stderr, "file=%s line=%d column=%d\n",
		string_pool_ref2str(gErrorFile),
		gErrorLineNo,
		gErrorColumn
	);
}

void bc_error_clear() {
	gGlobalError = bcerror_none;
	gErrorFile = ZERO_VIEW;
	gErrorLineNo = -1;
	gErrorColumn = -1;
}

void bc_error_file(const char* filename) {
	if(filename == NULL) {
		filename = "NULL";
	}
	gErrorFile = string_pool_intern(filename);
}

void bc_error_line(int lineno) {
	gErrorLineNo = lineno;
}

void bc_error_column(int column) {
	gErrorColumn = column;
}

bc_error_id bc_error_last() {
	return gGlobalError;
}