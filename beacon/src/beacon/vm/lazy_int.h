#ifndef BEACON_VM_LAZY_INT_H
#define BEACON_VM_LAZY_INT_H
typedef struct lazy_int {
	int value;
} lazy_int;

lazy_int* lazy_int_new(int value);

void lazy_int_delete(lazy_int* self);
#endif