#ifndef BEACON_ENV_CLL_CLASS_LOADER_MODULE_H
#define BEACON_ENV_CLL_CLASS_LOADER_MODULE_H
//このファイルは非公開ヘッダーか .c からのみインクルードして下さい。
struct ast;
struct fqcn_cache;
struct generic_cache;

void CLIL_fqcn_cache(struct ast* afqcn, struct fqcn_cache* fqcn);

void CLIL_generic_cache(struct ast* fqcn, struct generic_cache* dest);
#endif