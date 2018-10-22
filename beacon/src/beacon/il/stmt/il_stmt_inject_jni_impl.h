#ifndef BEACON_IL_STMT_INJECT_JNI_H
#define BEACON_IL_STMT_INJECT_JNI_H
#include "../../util/string_pool.h"
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
struct SymbolEntry;

typedef struct il_stmt_inject_jni {
	StringView namev;
	il_factor* fact;
	struct SymbolEntry* se;
} il_stmt_inject_jni;

il_stmt* WrapILInjectJNI(il_stmt_inject_jni* self);

il_stmt_inject_jni* NewILInjectJNI(StringView namev);

void GenerateILInjectJNI(il_stmt_inject_jni* self, Enviroment* env, CallContext* cctx);

void LoadILInjectJNI(il_stmt_inject_jni * self, Enviroment* env, CallContext* cctx);

void DeleteILInjectJni(il_stmt_inject_jni* self);
#endif