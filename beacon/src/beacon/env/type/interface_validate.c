#include "interface_validate.h"
#include "../TYPE_IMPL.h"
#include "../parameter.h"
#include "../type_parameter.h"

bool IsMethodParameterValidInterface(interface_* inter, method** out_method, string_view* out_name) {
	for(int i=0; i<inter->method_list->length; i++) {
		method* m = (method*)AtVector(inter->method_list, i);
		if(IsOverwrappedParameterName(m->parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}

bool IsTypeParameterValidInterface(interface_* inter, string_view* out_name) {
	return !IsOverwrappedTypeParameterName(inter->GetParameterListType, out_name);
}

bool IsMethodTypeParameterValidInterface(interface_* inter, method** out_method, string_view* out_name) {
	for(int i=0; i<inter->method_list->length; i++) {
		method* m = (method*)AtVector(inter->method_list, i);
		if(IsOverwrappedParameterName(m->type_parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}
