#include "error.h"
#include "util/text.h"
#include "util/string_pool.h"

static bc_error_id gGlobalError = bcerror_none;
static string_view gErrorMessageV = ZERO_VIEW;
static int gErrorLineNo = -1;

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
			fmt = "parser failed --- %s";
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

		case bcerror_native_field:
			fmt = "`native` modifier is can't use for field: %s#%s";
			break;
		case bcerror_abstract_field:
			fmt = "`abstract` modifier is can't use for field: %s#%s";
			break;
		case bcerror_override_field:
			fmt = "`override` modifier is can't use for field: %s#%s";
			break;

		case bcerror_undefined_class:
			fmt = "undefined class: %s";
			break;
		case bcerror_undefined_variable:
			fmt = "undefined variable: %s";
			break;
		case bcerror_undefined_method:
			fmt = "undefined method: %s";
			break;
		case bcerror_undefined_field:
			fmt = "undefined field: %s";
			break;
		case bcerror_undefined_ctor:
			fmt = "undefined ctor: %s";
			break;
		case bcerror_undefined_operator:
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
		case bcerror_empty_method_body:
			fmt = "must be not empty statement if modifier of method is native or abstract: %s";
			break;
		case bcerror_not_empty_method_body:
			fmt = "must be empty statement if modifier of method is native or abstract: %s";
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
		case bcerror_illegal_argument_bioperator:
			fmt = "illegal of parameter count, must be binary operator argument count is one.: %s#%s";
			break;
		case bcerror_illegal_argument_uoperator:
			fmt = "illegal of parameter count, must be unary operator argument count is zero.: %s#%s";
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
	text_vfprintf(stderr, fmt, ap);
	text_fprintf(stderr, "\n");
}

void bc_error_clear() {
	gGlobalError = bcerror_none;
	gErrorMessageV = ZERO_VIEW;
	gErrorLineNo = -1;
}

void bc_error_file(const char* filename) {
	if(filename == NULL) {
		filename = "NULL";
	}
	gErrorMessageV = string_pool_intern(filename);
}

void bc_error_line(int lineno) {
	gErrorLineNo = lineno;
}

bc_error_id bc_error_last() {
	return gGlobalError;
}