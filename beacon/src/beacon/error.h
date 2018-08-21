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
	bcerror_none_T = 0,
	bcerror_generic_T,
	bcerror_parse_T,
	bcerror_require_not_found_T,
	bcerror_overwrap_parameter_name_T,
	bcerror_overwrap_type_type_parameter_name_T,
	bcerror_overwrap_method_type_parameter_name_T,
	bcerror_overwrap_variable_name_T,
	bcerror_overwrap_modifier_T,
	bcerror_overwrap_field_name_T,
	bcerror_overwrap_property_name_T,

	bcerror_native_field_T,
	bcerror_abstract_field_T,
	bcerror_override_field_T,

	bcerror_static_override_method_T,
	bcerror_abstract_override_method_T,
	bcerror_abstract_static_method_T,

	bcerror_empty_stmt_method_T,
	bcerror_not_empty_stmt_method_T,

	bcerror_return_value_void_method_T,
	bcerror_not_return_value_not_void_method_T,
	bcerror_return_value_type_is_not_compatible_not_void_method_T,

	bcerror_yield_return_value_type_is_not_compatible_T,

	bcerror_if_expr_type_of_not_bool_T,
	bcerror_while_expr_type_of_not_bool_T,

	bcerror_break_at_not_loop_T,
	bcerror_continue_at_not_loop_T,

	bcerror_access_to_this_at_static_method_T,
	bcerror_access_to_super_at_static_method_T,

	bcerror_assign_to_final_field_T,
	bcerror_not_default_value_static_final_field_T,
	bcerror_not_initial_field_not_initialized_at_ctor_T,
	bcerror_field_default_value_not_compatible_to_field_type_T,
	bcerror_lhs_is_not_subscript_T,

	bcerror_arg_count_not2_bioperator_T,
	bcerror_arg_count_not1_uoperator_T,
	bcerror_arg_count_not2_subscript_set_op_T,
	bcerror_arg_count_not1_subscript_get_op_T,
	bcerror_return_type_not_bool_compare_operator_T,
	bcerror_return_type_not_bool_not_operator_T,
	bcerror_return_type_not_equal_negative_operator_T,

	bcerror_thrown_not_exception_type_T,

	bcerror_assign_not_compatible_local_T,
	bcerror_assign_not_compatible_field_T,
	bcerror_assign_not_compatible_property_T,

	bcerror_auto_chain_ctor_not_found_T,
	bcerror_explicit_chain_ctor_not_found_T,

	bcerror_new_instance_undefined_class_T,
	bcerror_ref_undefined_local_variable_T,

	bcerror_invoke_bound_undefined_method_T,
	bcerror_invoke_instance_undefined_method_T,
	bcerror_invoke_static_undefined_method_T,

	bcerror_new_instance_undefined_ctor_T,

	bcerror_undefined_compare_operator_T,
	bcerror_undefined_arithmetic_operator_T,
	bcerror_undefined_shift_operator_T,
	bcerror_undefined_bit_operator_T,
	bcerror_undefined_logic_operator_T,
	bcerror_undefined_excor_operator_T,

	bcerror_void_assign_T,
	bcerror_void_decl_T,

	bcerror_cast_not_compatible_T,

	bcerror_undefined_type_decl_T,
	bcerror_undefined_type_static_invoke_T,
	bcerror_undefined_name_bound_invoke_T,
	bcerror_undefined_property_T,
	bcerror_assign_to_invoke_T,

	bcerror_interface_has_field_T,
	bcerror_interface_has_ctor_T,
	bcerror_interface_has_opov_T,

	bcerror_interface_has_private_member_T,

	bcerror_construct_abstract_type_T,
	bcerror_can_t_resolve_lambda_T,
	bcerror_not_functional_interface_T,
	bcerror_class_first_T,
	bcerror_multi_eqinterface_T,
	bcerror_interface_only_T,
	bcerror_chain_T,
	bcerror_abstract_method_by_T,
	bcerror_not_implement_interface_T,
	bcerror_not_implement_abstract_method_T,
	bcerror_private_operator_T,
	bcerror_invalid_property_decl_T,
	bcerror_can_t_access_field_T,
	bcerror_can_t_access_property_T,
	bcerror_invalid_access_level_of_property_T,
	bcerror_specified_both_property_accessor_T,
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