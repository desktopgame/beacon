#ifndef BEACON_ENV_CLL_CLASS_LOADER_MODULE_H
#define BEACON_ENV_CLL_CLASS_LOADER_MODULE_H
#include "../../util/vector.h"
//このファイルは非公開ヘッダーか .c からのみインクルードして下さい。
struct AST;
struct FQCNCache;
struct GenericCache;
struct class_loader;

void CLILFQCNCache(struct AST* afqcn, struct FQCNCache* fqcn);

void CLILGenericCache(struct AST* afqcn, struct GenericCache* dest);

/**
 * 型名の一覧を dst へ出力します.
 * @param self
 * @param dst
 * @param typename_list
 */
void CLILTypenameList(struct class_loader* self, Vector* dst, struct AST* atypename_list);


void CLILTypeParameter(struct class_loader* self, struct AST* asource, Vector* dest);

void CLILTypeArgument(struct class_loader* self, struct AST* atype_args, Vector* dest);

void CLILParameterList(struct class_loader* self, Vector* list, struct AST* asource);

void CLILArgumentList(struct class_loader* self, Vector* list, struct AST* asource);
#endif