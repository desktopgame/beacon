#include "interface_validate.h"
#include "../TYPE_IMPL.h"
#include "../parameter.h"
#include "../type_parameter.h"

bool bc_IsMethodParameterValidInterface(bc_Interface* inter, bc_Method** out_method, StringView* out_name) {
	for(int i=0; i<inter->Methods->Length; i++) {
		bc_Method* m = (bc_Method*)AtVector(inter->Methods, i);
		if(bc_IsOverwrappedParameterName(m->Parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}

bool bc_IsTypeParameterValidInterface(bc_Interface* inter, StringView* out_name) {
	return !bc_IsOverwrappedTypeParameterName(inter->TypeParameters, out_name);
}

bool bc_IsMethodTypeParameterValidInterface(bc_Interface* inter, bc_Method** out_method, StringView* out_name) {
	for(int i=0; i<inter->Methods->Length; i++) {
		bc_Method* m = (bc_Method*)AtVector(inter->Methods, i);
		if(bc_IsOverwrappedParameterName(m->TypeParameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}
