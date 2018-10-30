#include "interface_validate.h"
#include "../TYPE_IMPL.h"
#include "../parameter.h"
#include "../type_parameter.h"

bool IsMethodParameterValidInterface(Interface* inter, Method** out_method, StringView* out_name) {
	for(int i=0; i<inter->Methods->Length; i++) {
		Method* m = (Method*)AtVector(inter->Methods, i);
		if(IsOverwrappedParameterName(m->Parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}

bool IsTypeParameterValidInterface(Interface* inter, StringView* out_name) {
	return !IsOverwrappedTypeParameterName(inter->TypeParameters, out_name);
}

bool IsMethodTypeParameterValidInterface(Interface* inter, Method** out_method, StringView* out_name) {
	for(int i=0; i<inter->Methods->Length; i++) {
		Method* m = (Method*)AtVector(inter->Methods, i);
		if(IsOverwrappedParameterName(m->TypeParameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}
