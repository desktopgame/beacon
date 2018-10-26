#pragma once
#ifndef BEACON_ENV_IMPORT_INFO_H
#define BEACON_ENV_IMPORT_INFO_H
#include <stdbool.h>
struct ClassLoader;

typedef struct ImportInfo {
	struct ClassLoader* Context;
	bool IsConsume;
} ImportInfo;

ImportInfo* NewImportInfo();

void DeleteImportInfo(ImportInfo* self);
#endif // !SIGNAL_ENV_IMPORT_INFO_H
