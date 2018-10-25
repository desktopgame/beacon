#ifndef BEACON_IL_IL_NAMESPACE_H
#define BEACON_IL_IL_NAMESPACE_H
#include "../util/vector.h"
#include "../util/string_pool.h"
#include "il_type_interface.h"

/**
 * 名前空間の宣言を表す要素.
 */
typedef struct ILNamespace {
	StringView namev;
	struct ILNamespace* parent;
	Vector* Namespacelist;
	Vector* type_list;
} ILNamespace;

/**
 * 名前空間を表す要素を作成します.
 * @param namev
 * @return
 */
ILNamespace* NewILNamespace(StringView namev);

/**
 * 最も上の要素を返します.
 * @param self
 * @return
 */
ILNamespace* GetRootILNamespace(ILNamespace* self);

/**
 * 名前空間を表す要素を解放します.
 * @param self
 */
void DeleteILNamespace(ILNamespace* self);
#endif // !SIGNAL_IL_IL_NAMESPACE_H
