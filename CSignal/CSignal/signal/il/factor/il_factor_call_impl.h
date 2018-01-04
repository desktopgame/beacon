#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_CALL_H
#define SIGNAL_IL_IL_FACTOR_CALL_H
#include "../../util/vector.h"
#include "../il_factor_interface.h"
struct method;
//struct opcode_buf;
/**
 * 関数呼び出しを表す要素.
 */
typedef struct il_factor_call {
	char* name;
	vector* argument_list;
	struct method* m;
	int methodIndex;
} il_factor_call;

/**
 * 関数呼び出しをスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_call(il_factor_call* self);

/**
 * 関数呼び出しを表す要素を作成します.
 * @param name
 * @return
 */
il_factor_call* il_factor_call_new(const char* name);

/**
 * 関数呼び出しを出力します.
 * @param self
 * @param depth
 */
void il_factor_call_dump(il_factor_call* self, int depth);

/**
 * 関数呼び出しを生成します.
 * @param self
 * @param env
 */
void il_factor_call_generate(il_factor_call* self, struct enviroment* env);

/**
 * 関数呼び出しを読み込みます.
 * @param self
 * @param env
 * @param eh
 */
void il_factor_call_load(il_factor_call* self, struct enviroment* env, il_ehandler* eh);

/**
 * 関数呼び出しの戻り値の型を返します.
 * @param self
 * @param env
 * @return
 */
struct class_* il_factor_call_eval(il_factor_call* self, struct enviroment* env);

/**
 * 関数呼び出しを開放します.
 * @param self
 */
void il_factor_call_delete(il_factor_call* self);
#endif // !SIGNAL_IL_IL_FACTOR_CALL_H
