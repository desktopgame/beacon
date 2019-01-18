#ifndef BEACON_ENV_CLASS_LOADER_IL_H
#define BEACON_ENV_CLASS_LOADER_IL_H
struct bc_ClassLoader;
struct bc_ILTOplevel;
struct bc_AST;

struct bc_ILToplevel* bc_LoadAST(struct bc_ClassLoader* self, struct bc_AST* a);
#endif