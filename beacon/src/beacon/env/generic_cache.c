#include "generic_cache.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/string_buffer.h"
#include "type_impl.h"
#include "generic_type.h"
#include <assert.h>

//proto
static void generic_cache_tree_delete(vector_item item);

generic_cache * generic_cache_new() {
	generic_cache* ret = (generic_cache*)MEM_MALLOC(sizeof(generic_cache));
	ret->fqcn = fqcn_cache_new();
	ret->type_args = vector_new();
	return ret;
}

void generic_cache_print(generic_cache * self) {
	fqcn_cache_print(self->fqcn);
	if (self->type_args->length <= 0) {
		return;
	}
	printf("<");
	for (int i = 0; i < self->type_args->length; i++) {
		generic_cache* e = (generic_cache*)vector_at(self->type_args, i);
		generic_cache_print(e);
		if (i != self->type_args->length - 1) {
			printf(", ");
		}
	}
	printf(">");
}

void generic_cache_dump(generic_cache * self, int depth) {
	io_printi(depth);
	generic_cache_print(self);
	io_println();
}

char* generic_cache_tostr(generic_cache* self) {
	string_buffer* sb = string_buffer_new();
	//Namespace::Class
	char* name = fqcn_cache_tostr(self->fqcn);
	string_buffer_appends(sb, name);
	//Namespace::Class<|
	if(self->type_args->length > 0) {
		string_buffer_appends(sb, "<|");
	}
	//Namespace::Class<|...
	for(int i=0; i<self->type_args->length; i++) {
		generic_cache* e = (generic_cache*)vector_at(self->type_args, i);
		char* type = generic_cache_tostr(e);
		string_buffer_appends(sb, type);
		if(i != (self->type_args->length - 1)) {
			string_buffer_appends(sb, ", ");
		}
		MEM_FREE(type);
	}
	//Namespace::Class<|...|>
	if(self->type_args->length > 0) {
		string_buffer_appends(sb, "|>");
	}
	MEM_FREE(name);
	return string_buffer_release(sb);
}

void generic_cache_delete(generic_cache * self) {
	fqcn_cache_delete(self->fqcn);
	vector_delete(self->type_args, generic_cache_tree_delete);
	MEM_FREE(self);
}

bool generic_cache_equals(generic_cache* a, generic_cache* b) {
	if(a->type_args->length != b->type_args->length) {
		return false;
	}
	if(!fqcn_cache_equals(a->fqcn, b->fqcn)) {
		return false;
	}
	if(a == b) {
		return true;
	}
	for(int i=0; i<a->type_args->length; i++) {
		generic_cache* ag = vector_at(a->type_args, i);
		generic_cache* bg = vector_at(b->type_args, i);
		if(!generic_cache_equals(ag, bg)) {
			return false;
		}
	}
	return true;
}
//private
static void generic_cache_tree_delete(vector_item item) {
	generic_cache* e = (generic_cache*)item;
	generic_cache_delete(e);
}