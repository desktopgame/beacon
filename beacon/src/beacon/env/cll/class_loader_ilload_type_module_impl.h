#ifndef BEACON_ENV_CLL_CLASS_LOADER_MODULE_H
#define BEACON_ENV_CLL_CLASS_LOADER_MODULE_H
#include "../../util/vector.h"
//このファイルは非公開ヘッダーか .c からのみインクルードして下さい。
struct ast;
struct fqcn_cache;
struct generic_cache;
struct class_loader;

void CLIL_fqcn_cache(struct ast* afqcn, struct fqcn_cache* fqcn);

void CLIL_generic_cache(struct ast* fqcn, struct generic_cache* dest);

/**
 * 型名の一覧を dst へ出力します.
 * @param self
 * @param dst
 * @param typename_list
 */
void CLIL_typename_list(struct class_loader* self, vector* dst, struct ast* typename_list);


void CLIL_type_parameter(struct class_loader* self, struct ast* source, vector* dest);

void CLIL_type_argument(struct class_loader* self, struct ast* atype_args, vector* dest);

void CLIL_parameter_list(struct class_loader* self, vector* list, struct ast* source);

void CLIL_argument_list(struct class_loader* self, vector* list, struct ast* source);
#endif