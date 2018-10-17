#pragma once
#ifndef BEACON_ENV_MEM_H
#define BEACON_ENV_MEM_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#if defined(_MSC_VER)
#include <crtdbg.h>
#endif

#define mem_malloc(size, file, line) (malloc(size))
typedef unsigned char muchar_t;
#if defined(_MSC_VER)
	#if defined(_DEBUG)
		#define NON_NULL(m) (m)
		#define MEM_MALLOC(size) (_malloc_dbg(size,_NORMAL_BLOCK,__FILE__,__LINE__))
		#define MEM_FREE(size) (_free_dbg(size, _NORMAL_BLOCK))
		#define MEM_REALLOC(block, size) (_realloc_dbg(block, size, _NORMAL_BLOCK, __FILE__, __LINE__))
		#define MEM_MARK(block, size) ((void)0)
	#else
		#define NON_NULL(m) (m)
		#define MEM_MALLOC(size) (malloc(size))
		#define MEM_FREE(size) (free(size))
		#define MEM_REALLOC(block, size) (realloc(block, size))
		#define MEM_MARK(block, size) ((void)0)
	#endif
#else
		#define NON_NULL(m) (m)
		#define MEM_MALLOC(size) (malloc(size))
		#define MEM_FREE(size) (free(size))
		#define MEM_REALLOC(block, size) (realloc(block, size))
		#define MEM_MARK(block, size) ((void)0)
#endif
#endif // !SIGNAL_ENV_MEM_H
