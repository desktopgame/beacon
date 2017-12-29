#include "import_manager.h"
#include "class_loader.h"
#include "class.h"
#include "namespace.h"
#include "../util/mem.h"
#include <string.h>
#include <stdlib.h>

import_manager * import_manager_new() {
	import_manager* ret = (import_manager*)MEM_MALLOC(sizeof(import_manager));
	ret->class_loader_list = vector_new();
	return ret;
}

void import_manager_import(import_manager * self, class_loader * target) {
	vector_push(self->class_loader_list, target);
}

class_ * import_manager_resolve(import_manager* self, const char * name) {
	//プリミティブ型はどこからでも参照できる
	if (!strcmp(name, "Int")) {
		return CL_INT;
	} else if (!strcmp(name, "Double")) {
		return CL_DOUBLE;
	} else if (!strcmp(name, "Char")) {
		return CL_CHAR;
	} else if (!strcmp(name, "String")) {
		return CL_STRING;
	} else if (!strcmp(name, "Void")) {
		return CL_VOID;
	}
	return NULL;
}

void import_manager_delete(import_manager * self) {
	vector_delete(self->class_loader_list, vector_deleter_null);
	MEM_FREE(self);
}
