#ifndef BEACON_LIB_BEACON_LANG_BC_FILE_H
#define BEACON_LIB_BEACON_LANG_BC_FILE_H
struct frame;
struct type;
struct object;
struct generic_type;

struct type;
/**
 * beacon::unsafe::Fileクラスを初期化します.
 */
void bc_file_init();

/**
 * beacon::unsafe::Fileを返します.
 * @return
 */
struct type* bc_file_type();
#endif