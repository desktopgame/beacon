#include "interface_validate.h"
#include "../type_impl.h"
#include "../parameter.h"
#include "../type_parameter.h"

bool interface_method_parameter_valid(interface_* inter, method** out_method, string_view* out_name) {
	for(int i=0; i<inter->method_list->length; i++) {
		method* m = (method*)vector_at(inter->method_list, i);
		if(parameter_is_overwrapped_name(m->parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}

bool interface_type_type_parameter_valid(interface_* inter, string_view* out_name) {
	return !type_parameter_is_overwrapped_name(inter->type_parameter_list, out_name);
}

bool interface_method_type_parameter_valid(interface_* inter, method** out_method, string_view* out_name) {
	for(int i=0; i<inter->method_list->length; i++) {
		method* m = (method*)vector_at(inter->method_list, i);
		if(parameter_is_overwrapped_name(m->type_parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}
