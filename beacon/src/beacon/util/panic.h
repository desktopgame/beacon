#ifndef BEACON_UTIL_PANIC_H
#define BEACON_UTIL_PANIC_H
#include "string_pool.h"

void save(string_view filenamev);

void panic();

string_view load();
#endif