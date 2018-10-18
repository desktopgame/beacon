#ifndef BEACON_IL_STMT_INJECT_JNI_H
#define BEACON_IL_STMT_INJECT_JNI_H
#include "../../util/string_pool.h"
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
struct symbol_entry;

typedef struct il_stmt_inject_jni {
	StringView namev;
	il_factor* fact;
	struct symbol_entry* se;
} il_stmt_inject_jni;

il_stmt* WrapILInjectJNI(il_stmt_inject_jni* self);

il_stmt_inject_jni* NewILInjectJNI(StringView namev);

void GenerateILInjectJNI(il_stmt_inject_jni* self, Enviroment* env, call_context* cctx);

void LoadILInjectJNI(il_stmt_inject_jni * self, Enviroment* env, call_context* cctx);

void DeleteILInjectJni(il_stmt_inject_jni* self);
#endif