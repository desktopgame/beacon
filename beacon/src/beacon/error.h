#ifndef BEACON_ERROR_H
#define BEACON_ERROR_H
#include <stdarg.h>
#include <stdio.h>

typedef enum bc_error_id {
	bcerror_none = 0,
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
} bc_error_id;

void bc_error_throw(bc_error_id id, ...);

void bc_error_vthrow(bc_error_id id, va_list ap);

void bc_error_clear();

void bc_error_file(const char* filename);

void bc_error_line(int lineno);

bc_error_id bc_error_last();
#endif