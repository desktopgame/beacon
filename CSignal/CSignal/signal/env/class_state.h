#pragma once
#ifndef SIGNAL_ENV_CLASS_STATE_H
#define SIGNAL_ENV_CLASS_STATE_H
/**
 * クラスの読み込み状態.
 */
typedef enum class_state {
	/**
	 * 生成直後.
	 */
	class_none,
	/**
	 * 言語仕様のためにプリロードされるクラス.
	 * 後で正式に読み込まれるまで "保留" 状態とします。
	 */
	class_pending,
	/**
	 * 正式に読み込みの完了したクラス.
	 */
	class_complete,
} class_state;
#endif // !SIGNAL_ENV_CLASS_STATE_H
