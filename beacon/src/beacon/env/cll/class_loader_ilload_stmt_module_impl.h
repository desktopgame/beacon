#ifndef BEACON_ENV_CLL_CLASS_LOADER_ILLOAD_STMT_MODULE_IMPL_H
#define BEACON_ENV_CLL_CLASS_LOADER_ILLOAD_STMT_MODULE_IMPL_H
#include "../../util/vector.h"
struct class_loader;
struct ast;
struct il_stmt;

struct il_stmt* CLIL_stmt(struct class_loader* self, struct ast* source);

void CLIL_body(struct class_loader* self, vector* list, struct ast* source);
#endif