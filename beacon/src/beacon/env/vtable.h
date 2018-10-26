#pragma once
#ifndef BEACON_ENV_VTABLE_H
#define BEACON_ENV_VTABLE_H
#include "../util/vector.h"
struct Method;
struct CallContext;
/**
 * メソッドの一覧をフラットに格納する配列です.
 * 同じシグネチャのメソッドが複数現れる場合には、
 * 親クラスで現れた時点の添え字をサブクラスの実装で上書きします。
 */
typedef struct VTable {
	//恐らくアップキャストのときに必要
	struct VTable* Parent;
	Vector* Elements;
} VTable;

/**
 * VTableを作成します.
 * @return
 */
VTable* NewVTable();

/**
 * src の中身を dst へ複製します.
 * @param src
 * @param dst
 */
void CopyVTable(VTable* src, VTable* dst);

/**
 * メソッド一覧に m を追加します.
 * 重複は検査されません。
 * 静的メソッドの場合は無視されます。
 * @param self
 * @param m
 */
void AddVTable(VTable* self, struct Method* m);

/**
 * メソッド一覧に m を追加します.
 * 重複する場合には上書きします。
 * 静的メソッドの場合は無視されます。
 * @param self
 * @param m
 * @param cctx
 */
void ReplaceVTable(VTable* self, struct Method* m, struct CallContext* cctx);

/**
 * VTableを開放します.
 * @param self
 */
void DeleteVTable(VTable* self);
#endif // !SIGNAL_ENV_VTABLE_H
