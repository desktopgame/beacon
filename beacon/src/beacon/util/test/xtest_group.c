#include "xtest_group.h"
#include "xtest.h"
#include "../mem.h"
#include "../text.h"

//proto
static void xtest_group_xtest_delete(vector_item item);

xtest_group* xtest_group_new(char* name) {
	xtest_group* ret = (xtest_group*)MEM_MALLOC(sizeof(xtest_group));
	ret->test_vec = vector_new();
	ret->name = text_strdup(name);
	return ret;
}

void xtest_group_add(xtest_group* self, const char* name, xtest_runner runner) {
	vector_push(self->test_vec, xtest_new(name, runner));
}

bool xtest_group_run(xtest_group* self) {
	text_printr('-', 20);
	text_printf("\n");
	text_printf("test a [%s]", self->name);
	text_printf("\n");
	text_printr('-', 20);
	text_printf("\n");
	bool ret = true;
	for(int i=0; i<self->test_vec->length; i++) {
		xtest* e = (xtest*)vector_at(self->test_vec, i);
		bool res = xtest_run(e);
		if(ret && !res) {
			ret = false;
		}
	}
	return ret;
}

void xtest_group_delete(xtest_group* self) {
	vector_delete(self->test_vec, xtest_group_xtest_delete);
	MEM_FREE(self->name);
	MEM_FREE(self);
}

//private
static void xtest_group_xtest_delete(vector_item item) {
	xtest* e = (xtest*)item;
	xtest_delete(e);
}