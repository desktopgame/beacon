#ifndef BEACON_ENV_CLASS_LOADER_BC_H
#define BEACON_ENV_CLASS_LOADER_BC_H
struct bc_ClassLoader;

void bc_LoadIL(struct bc_ClassLoader* self);

void bc_SpecialLoadIL(struct bc_ClassLoader* self);
#endif