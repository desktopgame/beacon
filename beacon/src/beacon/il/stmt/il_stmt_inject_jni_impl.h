// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_stmt_inject_jni_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_STMT_INJECT_JNI_H
#define BEACON_IL_STMT_INJECT_JNI_H
#include "../../util/string_pool.h"
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
struct bc_SymbolEntry;

typedef struct bc_ILInjectJNI {
        bc_StringView Name;
        bc_ILFactor* Value;
        struct bc_SymbolEntry* Symbol;
} bc_ILInjectJNI;

bc_ILStatement* bc_WrapILInjectJNI(bc_ILInjectJNI* self);

bc_ILInjectJNI* bc_NewILInjectJNI(bc_StringView namev);

void bc_GenerateILInjectJNI(bc_ILInjectJNI* self, bc_Enviroment* env,
                            bc_CallContext* cctx);

void bc_LoadILInjectJNI(bc_ILInjectJNI* self, bc_Enviroment* env,
                        bc_CallContext* cctx);

void bc_DeleteILInjectJni(bc_ILInjectJNI* self);
#endif