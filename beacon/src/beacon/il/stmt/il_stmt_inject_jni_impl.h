#ifndef BEACON_IL_STMT_INJECT_JNI_H
#define BEACON_IL_STMT_INJECT_JNI_H
#include "../../util/string_pool.h"
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
struct symbol_entry;

typedef struct il_stmt_inject_jni {
	string_view namev;
	il_factor* fact;
	struct symbol_entry* se;
} il_stmt_inject_jni;

il_stmt* il_stmt_wrap_inject_jni(il_stmt_inject_jni* self);

il_stmt_inject_jni* il_stmt_inject_jni_new(string_view namev);

void il_stmt_inject_jni_dump(il_stmt_inject_jni* self, int depth);

void il_stmt_inject_jni_generate(il_stmt_inject_jni* self, enviroment* env, call_context* cctx);

void il_stmt_inject_jni_load(il_stmt_inject_jni * self, enviroment* env, call_context* cctx);

void il_stmt_inject_jni_delete(il_stmt_inject_jni* self);
#endif