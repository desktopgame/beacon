#ifndef BEACON_LIB_BEACON_LANG_BC_FILE_H
#define BEACON_LIB_BEACON_LANG_BC_FILE_H
struct Frame;
struct type;
struct object;
struct generic_type;

struct type;
/**
 * beacon::unsafe::Fileクラスを初期化します.
 */
void InitBCFile();

/**
 * beacon::unsafe::Fileを返します.
 * @return
 */
struct type* GetBCFileType();
#endif