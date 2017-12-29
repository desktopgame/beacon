#include "props.h"
#include <stdlib.h>
#include "text.h"
#include "../util/mem.h"

//proto
static void props_delete_entry(tree_item item);
static void props_replace(props* self, const char* key);

props_entry * props_entry_new(props_type type) {
	props_entry* ret = (props_entry*)MEM_MALLOC(sizeof(props_entry));
	ret->type = type;
	return ret;
}

props * props_new() {
	props* ret = (props*)MEM_MALLOC(sizeof(props));
	ret->map = tree_map_new();
	return ret;
}

void props_puti(props * self, const char * key, int i) {
	props_entry* e = props_entry_new(props_int);
	e->u.int_ = i;
	props_replace(self, key);
	tree_map_put(self->map, key, e);
}

void props_putd(props * self, const char * key, double d) {
	props_entry* e = props_entry_new(props_double);
	e->u.double_ = d;
	props_replace(self, key);
	tree_map_put(self->map, key, e);
}

void props_putc(props * self, const char * key, char c) {
	props_entry* e = props_entry_new(props_char);
	e->u.char_ = c;
	props_replace(self, key);
	tree_map_put(self->map, key, e);
}

void props_puts(props * self, const char * key, const char * s) {
	props_entry* e = props_entry_new(props_string);
	e->u.string_ = text_strdup(s);
	props_replace(self, key);
	tree_map_put(self->map, key, e);
}

int props_geti(props * self, const char * key, int defaultValue) {
	tree_item item = tree_map_get(self->map, key);
	if (item == NULL) {
		return defaultValue;
	}
	return ((props_entry*)item)->u.int_;
}

double props_getd(props * self, const char * key, double defaultValue) {
	tree_item item = tree_map_get(self->map, key);
	if (item == NULL) {
		return defaultValue;
	}
	return ((props_entry*)item)->u.double_;
}

char props_getc(props * self, const char * key, char defaultValue) {
	tree_item item = tree_map_get(self->map, key);
	if (item == NULL) {
		return defaultValue;
	}
	return ((props_entry*)item)->u.char_;
}

char * props_gets(props * self, const char * key, const char * defaultValue) {
	tree_item item = tree_map_get(self->map, key);
	if (item == NULL) {
		return defaultValue;
	}
	return ((props_entry*)item)->u.string_;
}

bool props_contains(props * self, const char * key) {
	return tree_map_get(self->map, key) != NULL;
}

void props_delete(props * self) {
	tree_map_delete(self->map, props_delete_entry);
	MEM_FREE(self);
}

//private
static void props_delete_entry(tree_item item) {
	props_entry* e = (props_entry*)item;
	if (e->type == props_string) {
		MEM_FREE(e->u.string_);
	}
	MEM_FREE(e);
}

static void props_replace(props* self, const char* key) {
	tree_item e = tree_map_get(self->map, key);
	if (e != NULL) {
		props_entry* p = (props_entry*)e;
		tree_map_put(self->map, key, 1);
		if (p->type == props_string) {
			MEM_FREE(p->u.string_);
		}
		MEM_FREE(p);
	}
}