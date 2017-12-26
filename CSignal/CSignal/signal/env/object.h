#pragma once
#ifndef SIGNAL_ENV_OBJECT_H
#define SIGNAL_ENV_OBJECT_H
struct class_;


typedef struct object {
	//宣言時の型, 代入時の型を持つ
	//代入されるたびに更新される
	//代入されるとき、インデックスをどうにか変換
	struct class_* classz;
} object;
#endif // !SIGNAL_ENV_OBJECT_H
