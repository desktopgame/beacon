#pragma once
#ifndef SIGNAL_ENV_PARAMETER_H
#define SIGNAL_ENV_PARAMETER_H
struct class_;
/**
 * メソッドの仮引数を表す構造体です.
 */
typedef struct parameter {
	char* name;
	struct class_* classz;
} parameter;

/**
 * 新しいパラメータを作成します.
 * @param name
 * @return
 */
parameter* parameter_new(const char* name);

/**
 * パラメータを開放します.
 * @param self
 */
void parameter_delete(parameter* self);
#endif // !SIGNAL_ENV_PARAMETER_H
