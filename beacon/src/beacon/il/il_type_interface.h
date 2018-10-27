#pragma once
#ifndef BEACON_IL_IL_TYPE_INTERFACE_H
#define BEACON_IL_IL_TYPE_INTERFACE_H
#include "../util/vector.h"
/**
 * 型の種類を判別する列挙.
 */
typedef enum ILTypeTag {
	ILTYPE_CLASS_T,
	ILTYPE_INTERFACE_T,
	ILTYPE_ENUM_T,
} ILTypeTag;

struct ILClass;
struct il_interface;
struct ILEnum;
struct ILField;
struct ILMethod;
struct ILProperty;
struct ILConstructor;

/**
 * 名前空間に含めることが出来る型.
 */
typedef struct ILType {
	ILTypeTag Tag;
	union {
		struct ILClass* Class;
		struct il_interface* Interface;
		struct ILEnum* Enum;
	} Kind;
} ILType;

/**
 * 型を作成します.
 * @return
 */
ILType* NewILType();

/**
 * メソッドの一覧を返します.
 * @param self
 * @return
 */
Vector* GetMethodsILType(ILType* self);

/**
 * 静的メソッドの一覧を返します.
 * @param self
 * @return
 */
Vector* GetSMethodsILType(ILType* self);

/**
 * コンストラクタを追加します.
 * @param self
 * @param ctor
 */
void AddConstructorILType(ILType* self, struct ILConstructor* ctor);

/**
 * フィールドを追加します.
 * @param self
 * @param field
 */
void AddFieldILType(ILType* self, struct ILField* field);

/**
 * プロパティを追加します.
 * @param self
 * @param prop
 */
void AddPropertyILType(ILType* self, struct ILProperty* prop);

/**
 * メソッドを追加します.
 * @param self
 * @param field
 */
void AddMethodILType(ILType* self, struct ILMethod* method);

/**
 * 型を開放します.
 * @param self
 */
void DeleteILType(ILType* self);

/**
 * 型変数の一覧を返します.
 * @param self
 * @return
 */
Vector* GetTypeParametersILType(ILType* self);
#endif // !SIGNAL_IL_IL_TYPE_INTERFACE_H
