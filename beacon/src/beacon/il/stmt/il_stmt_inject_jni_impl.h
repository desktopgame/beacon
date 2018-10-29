#ifndef BEACON_IL_STMT_INJECT_JNI_H
#define BEACON_IL_STMT_INJECT_JNI_H
#include "../../util/string_pool.h"
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
struct SymbolEntry;

typedef struct ILInjectJNI {
	StringView Name;
	ILFactor* Value;
	struct SymbolEntry* Symbol;
} ILInjectJNI;

ILStatement* WrapILInjectJNI(ILInjectJNI* self);

ILInjectJNI* NewILInjectJNI(StringView namev);

void GenerateILInjectJNI(ILInjectJNI* self, Enviroment* env, CallContext* cctx);

void LoadILInjectJNI(ILInjectJNI * self, Enviroment* env, CallContext* cctx);

void DeleteILInjectJni(ILInjectJNI* self);
#endif