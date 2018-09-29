#include "parameter.h"
#include <stdlib.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "../env/generic_type.h"

parameter * parameter_new(string_view namev) {
	parameter* ret = (parameter*)MEM_MALLOC(sizeof(parameter));
	ret->namev = namev;
	ret->gtype = NULL;
	return ret;
}

void parameter_delete(parameter * self) {
	MEM_FREE(self);
}

bool parameter_is_overwrapped_name(Vector* parameters, string_view* namev) {
	for(int i=0; i<parameters->length; i++) {
		parameter* e = (parameter*)AtVector(parameters, i);
		for(int j=0; j<parameters->length; j++) {
			if(i == j) { continue; }
			parameter* e2 = (parameter*)AtVector(parameters, j);
			if(e->namev == e2->namev) {
				(*namev) = e->namev;
				return true;
			}
		}
	}
	return false;
}