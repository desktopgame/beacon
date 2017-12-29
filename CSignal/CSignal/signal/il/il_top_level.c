#include "il_top_level.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/mem.h"
#include "il_stmt_interface.h"
#include "il_import.h"
#include "il_namespace.h"

//proto
static void il_top_level_import_delete(vector_item item);
static void il_top_level_namespace_delete(vector_item item);
static void il_top_level_stmt_delete(vector_item item);

il_top_level* il_top_level_new() {
	il_top_level* ret = (il_top_level*)MEM_MALLOC(sizeof(il_top_level));
	ret->import_list = vector_new();
	ret->namespace_list = vector_new();
	ret->statement_list = vector_new();
	return ret;
}

void il_top_level_dump(il_top_level* self, int depth) {
	printf("top_level");
	text_putline();
	for (int i = 0; i < self->import_list->length; i++) {
		vector_item e = vector_at(self->import_list, i);
		il_import* ili = (il_import*)e;
		il_import_dump(ili, depth + 1);
	}
	for (int i = 0; i < self->namespace_list->length; i++) {
		vector_item e = vector_at(self->namespace_list, i);
		il_namespace* iln = (il_namespace*)e;
		il_namespace_dump(iln, depth + 1);
	}
	for (int i = 0; i < self->statement_list->length; i++) {
		vector_item e = vector_at(self->statement_list, i);
		il_stmt* ils = (il_stmt*)e;
		il_stmt_dump(ils, depth + 1);
	}
}

void il_top_level_delete(il_top_level* self) {
	if(self == NULL) {
		return;
	}
	vector_delete(self->import_list, il_top_level_import_delete);
	vector_delete(self->namespace_list, il_top_level_namespace_delete);
	vector_delete(self->statement_list, il_top_level_stmt_delete);
	MEM_FREE(self);
}

//private
static void il_top_level_import_delete(vector_item item) {
	il_import* e = (il_import*)item;
	il_import_delete(e);
}

static void il_top_level_namespace_delete(vector_item item) {
	il_namespace* e = (il_namespace*)item;
	il_namespace_delete(e);
}

static void il_top_level_stmt_delete(vector_item item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}