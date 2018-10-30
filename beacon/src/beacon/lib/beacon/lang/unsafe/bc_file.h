#ifndef BEACON_LIB_BEACON_LANG_BC_FILE_H
#define BEACON_LIB_BEACON_LANG_BC_FILE_H
struct Frame;
struct Type;
struct Object;
struct GenericType;

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