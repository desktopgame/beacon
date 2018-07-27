#ifndef BEACON_PCODE_H
#define BEACON_PCODE_H
#include "../util/string_pool.h"
#include "../util/vector.h"
#include <stdio.h>

typedef long pcode_value;

typedef enum pcode_tag {
	pcode_none_T,
} pcode_tag;

typedef struct pcode {
	pcode_tag tag;
	vector* args_vec;
	union {
		int int_value;
		char char_value;
		string_view stringv_value;
	} u;
} pcode;

pcode* pcode_new(pcode_tag tag);

void pcode_push(pcode* self, pcode* arg);

int pcode_print(pcode* self, FILE* fp);

void pcode_delete(pcode* self);
#endif