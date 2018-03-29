#pragma once
#ifndef BEACON_ENV_IMPORT_INFO_H
#define BEACON_ENV_IMPORT_INFO_H
#include <stdbool.h>
struct class_loader;

typedef struct import_info {
	struct class_loader* context;
	bool consume;
} import_info;

import_info* import_info_new();

void import_info_delete(import_info* self);
#endif // !SIGNAL_ENV_IMPORT_INFO_H
