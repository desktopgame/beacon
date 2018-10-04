#ifndef BEACON_ENV_CLL_CLASS_LOADER_MODULE_H
#define BEACON_ENV_CLL_CLASS_LOADER_MODULE_H
#include "../../util/vector.h"
//このファイルは非公開ヘッダーか .c からのみインクルードして下さい。
struct ast;
struct fqcn_cache;
struct generic_cache;
struct class_loader;

void CLILFQCNCache(struct ast* afqcn, struct fqcn_cache* fqcn);

void CLILGenericCache(struct ast* afqcn, struct generic_cache* dest);

/**
 * 型名の一覧を dst へ出力します.
 * @param self
 * @param dst
 * @param typename_list
 */
void CLILTypenameList(struct class_loader* self, Vector* dst, struct ast* atypename_list);


void CLILTypeParameter(struct class_loader* self, struct ast* asource, Vector* dest);

void CLILTypeArgument(struct class_loader* self, struct ast* atype_args, Vector* dest);

void CLILParameterList(struct class_loader* self, Vector* list, struct ast* asource);

void CLILArgumentList(struct class_loader* self, Vector* list, struct ast* asource);
#endif