#include "parameter.h"
#include <stdlib.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "../env/generic_type.h"

Parameter * NewParameter(StringView namev) {
	Parameter* ret = (Parameter*)MEM_MALLOC(sizeof(Parameter));
	ret->Name = namev;
	ret->GType = NULL;
	return ret;
}

void DeleteParameter(Parameter * self) {
	MEM_FREE(self);
}

bool IsOverwrappedParameterName(Vector* parameters, StringView* outName) {
	for(int i=0; i<parameters->Length; i++) {
		Parameter* e = (Parameter*)AtVector(parameters, i);
		for(int j=0; j<parameters->Length; j++) {
			if(i == j) { continue; }
			Parameter* e2 = (Parameter*)AtVector(parameters, j);
			if(e->Name == e2->Name) {
				(*outName) = e->Name;
				return true;
			}
		}
	}
	return false;
}