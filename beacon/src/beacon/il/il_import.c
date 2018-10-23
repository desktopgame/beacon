#include "il_import.h"
#include "../util/text.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/mem.h"

ILImport* NewILImport(StringView path) {
	ILImport* ret = (ILImport*)MEM_MALLOC(sizeof(ILImport));
	ret->Path = path;
	return ret;
}

void DeleteILImport(ILImport* self) {
	if(self == NULL) {
		return;
	}
	MEM_FREE(self);
}