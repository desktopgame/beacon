#ifndef BEACON_ERROR_H
#define BEACON_ERROR_H
#include <stdarg.h>
#include <stdio.h>

#define BC_ERROR() if(bc_error_last()) return
#define BC_ERROR_RET(a) if(bc_error_last()) return a
/**
 * beaconインタプリタがソース解析中に検出したエラーを表す列挙.
 */
typedef enum bc_error_id {
	bcerror_none = 0,
	bcerror_generic,
	bcerror_parse,
	bcerror_require_not_found,
	bcerror_overwrap_parameter_name,
	bcerror_overwrap_type_type_parameter_name,
	bcerror_overwrap_method_type_parameter_name,
	bcerror_overwrap_variable_name,
	bcerror_overwrap_modifier,
	bcerror_overwrap_field_name,
	bcerror_overwrap_property_name,

	bcerror_native_field,
	bcerror_abstract_field,
	bcerror_override_field,

	bcerror_static_override_method,
	bcerror_abstract_override_method,
	bcerror_abstract_static_method,

	bcerror_empty_stmt_method,
	bcerror_not_empty_stmt_method,

	bcerror_return_value_void_method,
	bcerror_not_return_value_not_void_method,
	bcerror_return_value_type_is_not_compatible_not_void_method,

	bcerror_yield_return_value_type_is_not_compatible,

	bcerror_if_expr_type_of_not_bool,
	bcerror_while_expr_type_of_not_bool,

	bcerror_break_at_not_loop,
	bcerror_continue_at_not_loop,

	bcerror_access_to_this_at_static_method,
	bcerror_access_to_super_at_static_method,

	bcerror_assign_to_final_field,
	bcerror_not_default_value_static_final_field,
	bcerror_not_initial_field_not_initialized_at_ctor,
	bcerror_field_default_value_not_compatible_to_field_type,
	bcerror_lhs_is_not_subscript,

	bcerror_arg_count_not2_bioperator,
	bcerror_arg_count_not1_uoperator,
	bcerror_arg_count_not2_subscript_set_op,
	bcerror_arg_count_not1_subscript_get_op,
	bcerror_return_type_not_bool_compare_operator,
	bcerror_return_type_not_bool_not_operator,
	bcerror_return_type_not_equal_negative_operator,

	bcerror_thrown_not_exception_type,

	bcerror_assign_not_compatible_local,
	bcerror_assign_not_compatible_field,
	bcerror_assign_not_compatible_property,

	bcerror_auto_chain_ctor_not_found,
	bcerror_explicit_chain_ctor_not_found,

	bcerror_new_instance_undefined_class,
	bcerror_ref_undefined_local_variable,

	bcerror_invoke_bound_undefined_method,
	bcerror_invoke_instance_undefined_method,
	bcerror_invoke_static_undefined_method,

	bcerror_new_instance_undefined_ctor,

	bcerror_undefined_compare_operator,

	bcerror_cast_not_compatible,

	bcerror_undefined_type_static_invoke,
	bcerror_undefined_name_bound_invoke,
	bcerror_undefined_property,

	bcerror_construct_abstract_type,
	bcerror_can_t_resolve_lambda,
	bcerror_not_functional_interface,
	bcerror_class_first,
	bcerror_multi_eqinterface,
	bcerror_interface_only,
	bcerror_chain,
	bcerror_abstract_method_by,
	bcerror_not_implement_interface,
	bcerror_not_implement_abstract_method,
	bcerror_private_operator,
	bcerror_invalid_property_decl,
	bcerror_can_t_access_field,
	bcerror_can_t_access_property,
	bcerror_invalid_access_level_of_property,
	bcerror_specified_both_property_accessor,
} bc_error_id;

/**
 * 指定のIDでエラーを発生させます.
 * @param id
 * @param ...
 */
void bc_error_throw(bc_error_id id, ...);

/**
 * 指定のIDでエラーを発生させます.
 * @param id
 * @param ap
 */
void bc_error_vthrow(bc_error_id id, va_list ap);

/**
 * エラーフラグをクリアします.
 */
void bc_error_clear();

/**
 * エラーが発生したファイルを記録します.
 * @param filename
 */
void bc_error_file(const char* filename);

/**
 * エラーが発生した行を記録します.
 * @param lineno
 */
void bc_error_line(int lineno);

/**
 * エラーが発生した列を記録します.
 * @param column
 */
void bc_error_column(int column);

/**
 * 現在発生中のエラーを返します.
 * @return
 */
bc_error_id bc_error_last();
#endif