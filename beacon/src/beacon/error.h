#ifndef BEACON_ERROR_H
#define BEACON_ERROR_H
#include <stdarg.h>
#include <stdio.h>
/**
 * beaconインタプリタがソース解析中に検出したエラーを表す列挙.
 */
typedef enum bc_error_id {
	bcerror_none = 0,
	bcerror_generic,
	bcerror_undefined_class,
	bcerror_undefined_variable,
	bcerror_undefined_field,
	bcerror_undefined_method,
	bcerror_undefined_ctor,
	bcerror_undefined_operator,
	bcerror_construct_abstract_type,
	bcerror_can_t_resolve_lambda,
	bcerror_not_functional_interface,
	bcerror_parse,
	bcerror_class_first,
	bcerror_multi_eqinterface,
	bcerror_interface_only,
	bcerror_chain,
	bcerror_modifier_a_overlapped,
	bcerror_field_name_a_overlapped,
	bcerror_native_field,
	bcerror_abstract_method_by,
	bcerror_empty_method_body,
	bcerror_not_empty_method_body,
	bcerror_not_implement_interface,
	bcerror_not_implement_abstract_method,
	bcerror_private_operator,
	bcerror_illegal_argument_bioperator,
	bcerror_illegal_argument_uoperator,
	bcerror_invalid_property_decl,
	bcerror_can_t_access_field,
	bcerror_can_t_access_property,
	bcerror_invalid_access_level_of_property,
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
 * 現在発生中のエラーを返します.
 * @return
 */
bc_error_id bc_error_last();
#endif