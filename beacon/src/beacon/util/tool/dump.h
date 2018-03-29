#pragma once
#ifndef BEACON_UTIL_DUMP_H
#define BEACON_UTIL_DUMP_H
#include <stdbool.h>

typedef struct dump_option {
	char* filename;
	bool ast;
	bool il;
	bool sg;
} dump_option;

void cmd_tool_dump(dump_option* option);
#endif // !SIGNAL_UTIL_DUMP_H
