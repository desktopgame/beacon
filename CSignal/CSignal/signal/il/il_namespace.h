#ifndef SIGNAL_IL_IL_NAMESPACE_H
#define SIGNAL_IL_IL_NAMESPACE_H
struct il_namespace_list;
struct il_class_list;

/**
 * 名前空間の宣言を表す要素.
 */
typedef struct il_namespace {
	char* name;
	struct il_namespace* parent;
	struct il_namespace_list* namespace_list;
	struct il_class_list* class_list;
} il_namespace;

/**
 * 名前空間を表す要素を作成します.
 * @param name
 * @return
 */
il_namespace* il_namespace_new(const char* name);

/**
 * 最も上の要素を返します.
 * @param self
 * @return
 */
il_namespace* il_namespace_root(il_namespace* self);

/**
 * この名前空間とその子要素を出力します.
 * @param self
 * @param depth
 */
void il_namespace_dump(il_namespace* self, int depth);

/**
 * 名前空間を表す要素を解放します.
 * @param self
 */
void il_namespace_delete(il_namespace* self);
#endif // !SIGNAL_IL_IL_NAMESPACE_H