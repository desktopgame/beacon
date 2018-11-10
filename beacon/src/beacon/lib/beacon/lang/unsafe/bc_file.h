//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file bc_file.h
 * @brief ファイルポインターのラッパー。
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_LIB_BEACON_LANG_BC_FILE_H
#define BEACON_LIB_BEACON_LANG_BC_FILE_H
#include "../../../bc_library_impl.h"
#include <stdio.h>
struct Frame;
struct Type;
struct Object;
struct GenericType;

typedef struct File {
	Object Super;
	FILE* Pointer;
} File;
struct Type;
/**
 * beacon::unsafe::Fileクラスを初期化します.
 */
void InitBCFile();

/**
 * beacon::unsafe::Fileを返します.
 * @return
 */
struct Type* GetBCFileType();
#endif