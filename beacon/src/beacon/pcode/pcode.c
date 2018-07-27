#include "pcode.h"
#include "../util/mem.h"

static void pcode_delete_delete(vector_item item);

pcode* pcode_new(pcode_tag tag) {
	pcode* ret = MEM_MALLOC(sizeof(pcode));
	ret->args_vec = vector_new();
	ret->tag = tag;
	return ret;
}

void pcode_push(pcode* self, pcode* arg) {
	vector_push(self->args_vec, arg);
}

int pcode_print(pcode* self, FILE* fp) {
	switch(self->tag) {
		case pcode_none_T:
			return fprintf(fp, "none");
	}
	return 0;
}

void pcode_delete(pcode* self) {
	vector_delete(self->args_vec, pcode_delete_delete);
	MEM_FREE(self);
}
//private
static void pcode_delete_delete(vector_item item) {
	pcode* e = (pcode*)item;
	pcode_delete(e);
}