#pragma once
#ifndef BEACON_IL_IL_TYPE_INTERFACE_H
#define BEACON_IL_IL_TYPE_INTERFACE_H
#include "../util/vector.h"
/**
 * 型の種類を判別する列挙.
 */
typedef enum il_type_tag {
	ilTYPE_CLASS_T,
	ilTYPE_INTERFACE_T,
	ilTYPE_ENUM_T,
} il_type_tag;

struct il_class;
struct il_interface;
struct il_enum;
struct ILField;
struct ILMethod;
struct ILProperty;
struct ILConstructor;

/**
 * 名前空間に含めることが出来る型.
 */
typedef struct il_type {
	il_type_tag tag;
	union {
		struct il_class* class_;
		struct il_interface* interface_;
		struct il_enum* enum_;
	} u;
} il_type;

/**
 * 型を作成します.
 * @return
 */
il_type* NewILType();

/**
 * メソッドの一覧を返します.
 * @param self
 * @return
 */
Vector* GetMethodsILType(il_type* self);

/**
 * 静的メソッドの一覧を返します.
 * @param self
 * @return
 */
Vector* GetSMethodsILType(il_type* self);

/**
 * コンストラクタを追加します.
 * @param self
 * @param ctor
 */
void AddConstructorILType(il_type* self, struct ILConstructor* ctor);

/**
 * フィールドを追加します.
 * @param self
 * @param field
 */
void AddFieldILType(il_type* self, struct ILField* field);

/**
 * プロパティを追加します.
 * @param self
 * @param prop
 */
void AddPropertyILType(il_type* self, struct ILProperty* prop);

/**
 * メソッドを追加します.
 * @param self
 * @param field
 */
void AddMethodILType(il_type* self, struct ILMethod* method);

/**
 * 型を開放します.
 * @param self
 */
void DeleteILType(il_type* self);

/**
 * 型変数の一覧を返します.
 * @param self
 * @return
 */
Vector* GetTypeParametersILType(il_type* self);
#endif // !SIGNAL_IL_IL_TYPE_INTERFACE_H
