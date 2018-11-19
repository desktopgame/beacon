#include "parameter.h"
#include <stdlib.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "../env/generic_type.h"

bc_Parameter * bc_NewParameter(StringView namev) {
	bc_Parameter* ret = (bc_Parameter*)MEM_MALLOC(sizeof(bc_Parameter));
	ret->Name = namev;
	ret->GType = NULL;
	return ret;
}

void bc_DeleteParameter(bc_Parameter * self) {
	MEM_FREE(self);
}

bool bc_IsOverwrappedParameterName(Vector* parameters, StringView* outName) {
	for(int i=0; i<parameters->Length; i++) {
		bc_Parameter* e = (bc_Parameter*)AtVector(parameters, i);
		for(int j=0; j<parameters->Length; j++) {
			if(i == j) { continue; }
			bc_Parameter* e2 = (bc_Parameter*)AtVector(parameters, j);
			if(e->Name == e2->Name) {
				(*outName) = e->Name;
				return true;
			}
		}
	}
	return false;
}