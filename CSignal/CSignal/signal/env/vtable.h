#pragma once
#ifndef SIGNAL_ENV_VTABLE_H
#define SIGNAL_ENV_VTABLE_H
#include "../util/vector.h"
struct method;
/**
 * メソッドの一覧をフラットに格納する配列です.
 * 同じシグネチャのメソッドが複数現れる場合には、
 * 親クラスで現れた時点の添え字をサブクラスの実装で上書きします。
 */
typedef struct vtable {
	//恐らくアップキャストのときに必要
	struct vtable* parent;
	vector* elements;
} vtable;

/**
 * vtableを作成します.
 * @return
 */
vtable* vtable_new();

/**
 * src の中身を dst へ複製します.
 * @param src
 * @param dst
 */
void vtable_copy(vtable* src, vtable* dst);

/**
 * メソッド一覧に m を追加します.
 * 重複は検査されません。
 * 静的メソッドの場合は無視されます。
 * @param self
 * @param m
 */
void vtable_add(vtable* self, struct method* m);

/**
 * メソッド一覧に m を追加します.
 * 重複する場合には上書きします。
 * 静的メソッドの場合は無視されます。
 * @param self
 * @param m
 */
void vtable_replace(vtable* self, struct method* m);

/**
 * この仮想関数テーブルを指定のインターフェイス型の関数へキャストします.
 * @param self
 * @param castTo
 * @return
 */
vtable* vtable_lookup(vtable* self, vtable* castTo);

/**
 * vtableを開放します.
 * @param self
 */
void vtable_delete(vtable* self);
#endif // !SIGNAL_ENV_VTABLE_H
