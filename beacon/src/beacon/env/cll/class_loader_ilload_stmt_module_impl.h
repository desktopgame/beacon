#ifndef BEACON_ENV_CLL_CLASS_LOADER_ILLOAD_STMT_MODULE_IMPL_H
#define BEACON_ENV_CLL_CLASS_LOADER_ILLOAD_STMT_MODULE_IMPL_H
#include "../../util/vector.h"
struct ClassLoader;
struct AST;
struct il_stmt;

struct il_stmt* CLILStmt(struct ClassLoader* self, struct AST* source);

void CLILBody(struct ClassLoader* self, Vector* list, struct AST* source);
#endif