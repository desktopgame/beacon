#pragma once
#ifndef SIGNAL_ENV_CLASS_H
#define SIGNAL_ENV_CLASS_H
#include "namespace.h"
#include "class_type.h"
#include <stdint.h>

/**
 * クラスを表す構造体です.
 */
typedef struct class_ {
	char* name;
	namespace_* location;
	struct class_* super_class;
	class_type type;
	uint32_t ref_count;
} class_;

/**
 * 新しいクラスを作成します.
 * 呼び出し側で対応する名前空間を紐づけてください。
 * @param name これは呼び出し側で開放してください。
 * @param type
 * @return
 */
class_* class_new(const char* name, class_type type);

/**
 * このクラスを開放します.
 * ただし先にこのクラスを参照するサブクラスを開放する必要があります。
 * @param self
 */
void class_delete(class_* self);
#endif // !SIGNAL_ENV_CLASS_H
