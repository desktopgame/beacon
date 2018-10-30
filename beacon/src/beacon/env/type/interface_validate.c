#include "interface_validate.h"
#include "../TYPE_IMPL.h"
#include "../parameter.h"
#include "../type_parameter.h"

bool IsMethodParameterValidInterface(Interface* inter, Method** out_method, StringView* out_name) {
	for(int i=0; i<inter->method_list->Length; i++) {
		Method* m = (Method*)AtVector(inter->method_list, i);
		if(IsOverwrappedParameterName(m->Parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}

bool IsTypeParameterValidInterface(Interface* inter, StringView* out_name) {
	return !IsOverwrappedTypeParameterName(inter->GetParameterListType, out_name);
}

bool IsMethodTypeParameterValidInterface(Interface* inter, Method** out_method, StringView* out_name) {
	for(int i=0; i<inter->method_list->Length; i++) {
		Method* m = (Method*)AtVector(inter->method_list, i);
		if(IsOverwrappedParameterName(m->TypeParameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}
