#pragma once
#ifndef BEACON_ENV_IMPORT_INFO_H
#define BEACON_ENV_IMPORT_INFO_H
#include <stdbool.h>
struct class_loader;

typedef struct ImportInfo {
	struct class_loader* Context;
	bool IsConsume;
} ImportInfo;

ImportInfo* NewImportInfo();

void DeleteImportInfo(ImportInfo* self);
#endif // !SIGNAL_ENV_IMPORT_INFO_H
