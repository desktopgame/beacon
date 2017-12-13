#ifndef SIGNAL_IL_IL_TYPE_H
#define SIGNAL_IL_IL_TYPE_H
/**
 * 型を表す要素.
 */
typedef struct il_type {
	char* name;
} il_type;

/**
 * 型を表す要素を作成します.
 * @param name
 * @return
 */
il_type* il_type_new(const char* name);

/**
 * 型を表す要素を解放します.
 * @param self
 */
void il_type_delete(il_type* self);
#endif // !SIGNAL_IL_IL_TYPE_H