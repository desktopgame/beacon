// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file mem.h
 * @brief malloc/realloc/freeのラッパーを定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_MEM_H
#define BEACON_ENV_MEM_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../config.h"
#if defined(_MSC_VER)
#include <crtdbg.h>
#endif

//#define bc_MXMalloc(size, file, line) (malloc(size))

#if (defined(_MSC_VER) && defined(BC_DEBUG))
#define NON_NULL(m) (bc_NonNull(m))
#define MEM_MALLOC(size) (_malloc_dbg(size, _NORMAL_BLOCK, __FILE__, __LINE__))
#define MEM_FREE(size) (_free_dbg(size, _NORMAL_BLOCK))
#define MEM_REALLOC(block, size) \
        (_realloc_dbg(block, size, _NORMAL_BLOCK, __FILE__, __LINE__))
#else
#define NON_NULL(m) (bc_NonNull(m))
#define MEM_MALLOC(size) (bc_MXMalloc(size, __FILE__, __LINE__))
#define MEM_FREE(size) (bc_MXFree(size, __FILE__, __LINE__))
#define MEM_REALLOC(block, size) (bc_MXRealloc(block, size, __FILE__, __LINE__))
#endif

typedef struct bc_Slot {
        size_t Size;
        void* UserArea;
        const char* FileName;
        int Lineno;
        int Count;
        struct bc_Slot* Next;
} bc_Slot;

void bc_InitMX();

void* bc_MXMalloc(size_t size, const char* filename, int lineno);

void* bc_MXRealloc(void* block, size_t size, const char* filename, int lineno);

void bc_MXFree(void* block, const char* filename, int lineno);

void* bc_MXBind(const void* block, size_t size, const char* filename,
                int lineno);

void bc_ValidateMX();

void bc_DestroyMX();

/**
 * メモリを指定のサイズ分確保して返します。
 * 確保できない場合には abort() します。
 * @param size
 * @return
 */
void* bc_SafeMalloc(size_t size);

/**
 * メモリを指定のサイズ分確保して返します。
 * 確保できない場合には abort() します。
 * @param block
 * @paran new_size
 * @return
 */
void* bc_SafeRealloc(void* block, size_t new_size);

/**
 * blockが NULL なら終了します。
 * @param block
 * @return
 */
void* bc_NonNull(void* block);
#endif  // !SIGNAL_ENV_MEM_H
