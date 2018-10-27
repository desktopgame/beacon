#ifndef BEACON_IL_STMT_INJECT_JNI_H
#define BEACON_IL_STMT_INJECT_JNI_H
#include "../../util/string_pool.h"
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
struct SymbolEntry;

typedef struct ILStatement_inject_jni {
	StringView namev;
	ILFactor* fact;
	struct SymbolEntry* se;
} ILStatement_inject_jni;

ILStatement* WrapILInjectJNI(ILStatement_inject_jni* self);

ILStatement_inject_jni* NewILInjectJNI(StringView namev);

void GenerateILInjectJNI(ILStatement_inject_jni* self, Enviroment* env, CallContext* cctx);

void LoadILInjectJNI(ILStatement_inject_jni * self, Enviroment* env, CallContext* cctx);

void DeleteILInjectJni(ILStatement_inject_jni* self);
#endif