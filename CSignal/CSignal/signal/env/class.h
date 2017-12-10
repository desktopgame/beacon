#pragma once
#ifndef SIGNAL_ENV_CLASS_H
#define SIGNAL_ENV_CLASS_H
#include "namespace.h"
#include "class_type.h"
#include <stdint.h>

typedef struct class_ {
	char* name;
	namespace_* location;
	struct class_* super_class;
	class_type type;
	uint32_t ref_count;
} class_;
#endif // !SIGNAL_ENV_CLASS_H
