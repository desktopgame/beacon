#pragma once
#ifndef BEACON_IL_IL_STMT_RETURN_H
#define BEACON_IL_IL_STMT_RETURN_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
struct Enviroment;
/**
 * 値の返却を表す要素.
 */
typedef struct ILReturn {
	ILFactor* Factor;
} ILReturn;

/**
 * 式を返却する文をスーパーセットにラップします.
 * @param self
 * @return
 */
ILStatement* WrapILReturn(ILReturn* self);

/**
 * 式を返却する文を作成します.
 * @return
 */
ILReturn* NewILReturn();

/**
 * 式を返却する文を生成します.
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILReturn(ILReturn* self, Enviroment* env, CallContext* cctx);

/**
 * 式を返却する文を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILReturn(ILReturn* self, Enviroment* env, CallContext* cctx);

/**
 * 式を返却する文を開放します.
 * @param self
 */
void DeleteILReturn(ILReturn* self);
#endif // !SIGNAL_IL_IL_STMT_RETURN_H
