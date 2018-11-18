#include "class_loader_link_impl.h"
#include "../type_cache.h"
#include "../../error.h"
#include "../TYPE_IMPL.h"
#include "../field.h"
#include "../../il/il_TYPE_IMPL.h"
#include "../../error.h"
#include "../../env/constructor.h"
#include "../../env/object.h"
#include "../../env/property.h"
#include "../../util/text.h"
#include "class_loader_bcload_member_module_impl.h"
#include "class_loader_bcload_import_module_impl.h"
#include "class_loader_bcload_impl.h"
#include <assert.h>

static void CLBC_class_decl(ClassLoader* self, ILType* iltype, Type* tp, Namespace* scope);
static void CLBC_class_impl(ClassLoader* self, ILType* iltype, Type* tp, Namespace* scope);

static void CLBC_interface_decl(ClassLoader* self, ILType* iltype, Type* tp, Namespace* scope);
static void CLBC_interface_impl(ClassLoader* self, ILType* iltype, Type* tp, Namespace* scope);

static void CLBC_enum_decl(ClassLoader * self, ILType * iltype, Type* tp, Namespace * scope);
static void CLBC_enum_impl(ClassLoader * self, ILType * iltype, Type* tp, Namespace * scope);

static void CLBC_excec_class_decl(ClassLoader* self);
static void CLBC_excec_class_impl(ClassLoader* self);
static void CLBC_excec_interface_decl(ClassLoader* self);
static void CLBC_excec_interface_impl(ClassLoader* self);
static void CLBC_excec_enum_decl(ClassLoader* self);
static void CLBC_excec_enum_impl(ClassLoader* self);
static void CLBC_check_class(ClassLoader * self, ILType * iltype, Type* tp, Namespace * scope);
static void CLBC_check_interface(ClassLoader * self, ILType * iltype, Type* tp, Namespace * scope);

void LinkClassLoader(ClassLoader* self, LinkType type) {
	CL_ERROR(self);
	bc_SetPanicFile(self->FileName);
	if(type == LINK_DECL_T) {
		CLBC_excec_class_decl(self);
		CL_ERROR(self);
		CLBC_excec_interface_decl(self);
		CL_ERROR(self);
		CLBC_excec_enum_decl(self);
	} else if(type == LINK_IMPL_T) {
		CLBC_excec_class_impl(self);
		CL_ERROR(self);
		CLBC_excec_interface_impl(self);
		CL_ERROR(self);
		CLBC_excec_enum_impl(self);
	} else assert(false);
}

//private
static void CLBC_class_decl(ClassLoader * self, ILType * iltype, Type* tp, Namespace * scope) {
	if((tp->State & TYPE_DECL) > 0) {
		return;
	}
	#if defined(DEBUG)
	const char* name = Ref2Str(GetTypeName(tp));
	#endif
	CL_ERROR(self);
	CLBC_fields_decl(self, iltype, tp, iltype->Kind.Class->Fields, scope);
	CLBC_fields_decl(self, iltype, tp, iltype->Kind.Class->StaticFields, scope);
	CL_ERROR(self);
	CLBC_properties_decl(self, iltype, tp, iltype->Kind.Class->Properties, scope);
	CLBC_properties_decl(self, iltype, tp, iltype->Kind.Class->StaticProperties, scope);
	CL_ERROR(self);

	CLBC_methods_decl(self, iltype, tp, iltype->Kind.Class->Methods, scope);
	CLBC_methods_decl(self, iltype, tp, iltype->Kind.Class->StaticMethods, scope);
	CL_ERROR(self);

	CLBC_ctors_decl(self, iltype, tp, scope);
	CL_ERROR(self);

	CLBC_operator_overloads_decl(self, iltype, tp, scope);
	CL_ERROR(self);

	CL_ERROR(self);
	tp->State = tp->State | TYPE_DECL;
}

static void CLBC_class_impl(ClassLoader * self, ILType * iltype, Type* tp, Namespace * scope) {
	if((tp->State & TYPE_IMPL) > 0) {
		return;
	}
	#if defined(DEBUG)
	const char* tyname = Ref2Str(GetTypeName(tp));
	#endif
	CreateVTableClass(tp->Kind.Class);
	CreateOperatorVTClass(tp->Kind.Class);
	CL_ERROR(self);
	CLBC_fields_impl(self, scope, tp, iltype->Kind.Class->Fields, (TYPE2CLASS(tp))->Fields);
	CLBC_fields_impl(self, scope, tp, iltype->Kind.Class->StaticFields, (TYPE2CLASS(tp))->StaticFields);
	CL_ERROR(self);
	CLBC_properties_impl(self, iltype, tp, iltype->Kind.Class->Properties, tp->Kind.Class->Properties, scope);
	CLBC_properties_impl(self, iltype, tp, iltype->Kind.Class->StaticProperties, tp->Kind.Class->StaticProperties, scope);
	CL_ERROR(self);

	CLBC_methods_impl(self, scope, iltype, tp, iltype->Kind.Class->Methods, ((TYPE2CLASS(tp))->Methods));
	CLBC_methods_impl(self, scope, iltype, tp, iltype->Kind.Class->StaticMethods, ((TYPE2CLASS(tp))->StaticMethods));
	CL_ERROR(self);

	CLBC_ctors_impl(self, iltype, tp);
	CL_ERROR(self);

	CLBC_operator_overloads_impl(self, iltype, tp, scope);
	CL_ERROR(self);
	tp->State = tp->State | TYPE_IMPL;
	CLBC_check_class(self, iltype, tp, scope);
}

static void CLBC_interface_decl(ClassLoader * self, ILType * iltype, Type* tp, Namespace * scope) {
	if((tp->State & TYPE_DECL) > 0) {
		return;
	}
	assert(tp->Kind.Interface->Methods->Length == 0);
	CL_ERROR(self);
	CLBC_methods_decl(self, iltype, tp, iltype->Kind.Interface->Methods, scope);
	CLBC_properties_decl(self, iltype, tp, iltype->Kind.Interface->Properties, scope);
	//privateなメンバーは定義できない
	for(int i=0; i<tp->Kind.Interface->Methods->Length; i++) {
		Method* e = AtVector(tp->Kind.Interface->Methods, i);
		if(e->Access == ACCESS_PRIVATE_T) {
			bc_Panic(
				BCERROR_INTERFACE_HAS_PRIVATE_MEMBER_T,
				Ref2Str(GetTypeName(tp)),
				Ref2Str(e->Name)
			);
		}
	}
	for(int i=0; i<tp->Kind.Interface->Properties->Length; i++) {
		Property* e = AtVector(tp->Kind.Interface->Properties, i);
		if(e->Access == ACCESS_PRIVATE_T) {
			bc_Panic(
				BCERROR_INTERFACE_HAS_PRIVATE_MEMBER_T,
				Ref2Str(GetTypeName(tp)),
				Ref2Str(e->Name)
			);
		}
	}
	CL_ERROR(self);
	CreateVTableInterface(tp->Kind.Interface);
	tp->State = tp->State | TYPE_DECL;
	CLBC_check_interface(self, iltype, tp, scope);
}

static void CLBC_interface_impl(ClassLoader * self, ILType * iltype, Type* tp, Namespace * scope) {
	if((tp->State & TYPE_IMPL) > 0) {
		return;
	}
	CL_ERROR(self);
	CLBC_methods_impl(self, scope, iltype, tp, iltype->Kind.Interface->Methods, tp->Kind.Interface->Methods);
	tp->State = tp->State | TYPE_IMPL;
}

static void CLBC_enum_decl(ClassLoader * self, ILType * iltype, Type* tp, Namespace * scope) {
	if((tp->State & TYPE_DECL) > 0) {
		return;
	}
	//重複するフィールドを確認する
	Field* outField = NULL;
	if((tp->Tag == TYPE_ENUM_T ||
	   tp->Tag == TYPE_CLASS_T) &&
	   !IsValidFieldClass(tp->Kind.Class, &outField)) {
		bc_Panic(BCERROR_OVERWRAP_FIELD_NAME_T, Ref2Str(tp->Kind.Class->Name), Ref2Str(outField->Name));
	}
	tp->State = tp->State | TYPE_DECL;
}

static void CLBC_enum_impl(ClassLoader * self, ILType * iltype, Type* tp, Namespace * scope) {
	if((tp->State & TYPE_IMPL) > 0) {
		return;
	}
	for(int i=0; i<tp->Kind.Class->StaticFields->Length; i++) {
		Field* f = AtVector(tp->Kind.Class->StaticFields, i);
		f->StaticValue = GetIntObject(i);
	}
	tp->State = tp->State | TYPE_IMPL;
}

static void CLBC_excec_class_decl(ClassLoader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->TypeCaches->Length; i++) {
		TypeCache* e = (TypeCache*)AtVector(self->TypeCaches, i);
		if (e->Kind != CACHEKIND_CLASS_DECL_T || e->IsConsume) {
			continue;
		}
		count++;
		e->IsConsume = true;
		CLBC_class_decl(e->Context, e->ILType, e->Type, e->Scope);
	}
}

static void CLBC_excec_class_impl(ClassLoader* self) {
	int count = 0;
	for (int i = 0; i < self->TypeCaches->Length; i++) {
		TypeCache* e = (TypeCache*)AtVector(self->TypeCaches, i);
		if (e->Kind != CACHEKIND_CLASS_IMPL_T || e->IsConsume) {
			continue;
		}
		count++;
		e->IsConsume = true;
		CLBC_class_impl(e->Context, e->ILType, e->Type, e->Scope);
	}
}

static void CLBC_excec_interface_decl(ClassLoader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->TypeCaches->Length; i++) {
		TypeCache* e = (TypeCache*)AtVector(self->TypeCaches, i);
		if (e->Kind != CACHEKIND_INTERFACE_DECL_T || e->IsConsume) {
			continue;
		}
		count++;
		e->IsConsume = true;
		CLBC_interface_decl(e->Context, e->ILType, e->Type, e->Scope);
	}
}

static void CLBC_excec_interface_impl(ClassLoader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->TypeCaches->Length; i++) {
		TypeCache* e = (TypeCache*)AtVector(self->TypeCaches, i);
		if (e->Kind != CACHEKIND_INTERFACE_IMPL_T || e->IsConsume) {
			continue;
		}
		count++;
		e->IsConsume = true;
		CLBC_interface_impl(e->Context, e->ILType, e->Type, e->Scope);
	}
}

static void CLBC_excec_enum_decl(ClassLoader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->TypeCaches->Length; i++) {
		TypeCache* e = (TypeCache*)AtVector(self->TypeCaches, i);
		if (e->Kind != CACHEKIND_ENUM_DECL_T || e->IsConsume) {
			continue;
		}
		count++;
		e->IsConsume = true;
		CLBC_enum_decl(e->Context, e->ILType, e->Type, e->Scope);
	}
}

static void CLBC_excec_enum_impl(ClassLoader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->TypeCaches->Length; i++) {
		TypeCache* e = (TypeCache*)AtVector(self->TypeCaches, i);
		if (e->Kind != CACHEKIND_ENUM_IMPL_T || e->IsConsume) {
			continue;
		}
		count++;
		e->IsConsume = true;
		CLBC_enum_impl(e->Context, e->ILType, e->Type, e->Scope);
	}
}

static void CLBC_check_class(ClassLoader * self, ILType * iltype, Type* tp, Namespace * scope) {
	//実装されていないインターフェイスを確認する
	Method* outiMethod = NULL;
	if(tp->Tag == TYPE_CLASS_T &&
	  !IsImplementInterfaceMethodValidClass(TYPE2CLASS(tp), &outiMethod)) {
		bc_Panic(BCERROR_NOT_IMPLEMENT_INTERFACE_T, Ref2Str(tp->Kind.Class->Name), Ref2Str(outiMethod->Name));
		return;
	}
	//実装されていないプロパティを確認する
	Property* outiProperty = NULL;
	if(tp->Tag == TYPE_CLASS_T &&
	  !IsImplementInterfacePropertyValidClass(TYPE2CLASS(tp), &outiProperty)) {
		bc_Panic(BCERROR_NOT_IMPLEMENT_ABSTRACT_METHOD_T, Ref2Str(tp->Kind.Class->Name), Ref2Str(outiProperty->Name));
		return;
	}
	//実装されていない抽象メソッドを確認する
	Method* outaMethod = NULL;
	if(tp->Tag == TYPE_CLASS_T &&
	   !IsImplementAbstractClassValidClass(TYPE2CLASS(tp), &outaMethod)) {
		bc_Panic(BCERROR_NOT_IMPLEMENT_ABSTRACT_METHOD_T, Ref2Str(tp->Kind.Class->Name), Ref2Str(outaMethod->Name));
		return;
	   }
	//重複するプロパティを確認する
	Property* outProp = NULL;
	if(!IsValidPropertyClass(tp->Kind.Class, &outProp)) {
		bc_Panic(BCERROR_OVERWRAP_PROPERTY_NAME_T,
			Ref2Str(tp->Kind.Class->Name),
			Ref2Str(outProp->Name)
		);
		return;
	}
	//重複するフィールドを確認する
	Field* outField = NULL;
	if(!IsValidFieldClass(tp->Kind.Class, &outField)) {
		bc_Panic(BCERROR_OVERWRAP_FIELD_NAME_T,
			Ref2Str(tp->Kind.Class->Name),
			Ref2Str(outField->Name)
		);
		return;
	}
	//メソッドの重複するパラメータ名を検出する
	Method* out_overwrap_m = NULL;
	StringView out_overwrap_mname;
	if(!IsMethodParameterValidClass(tp->Kind.Class, &out_overwrap_m, &out_overwrap_mname)) {
		bc_Panic(BCERROR_OVERWRAP_PARAMETER_NAME_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(out_overwrap_m->Name),
			Ref2Str(out_overwrap_mname)
		);
		return;
	}
	//コンストラクタの重複するパラメータ名を検出する
	Constructor* out_overwrap_c = NULL;
	StringView out_overwrap_cname;
	if(!IsConstructorParameterValidClass(tp->Kind.Class, &out_overwrap_c, &out_overwrap_cname)) {
		bc_Panic(BCERROR_OVERWRAP_PARAMETER_NAME_T,
			Ref2Str(GetTypeName(tp)),
			"new",
			Ref2Str(out_overwrap_cname)
		);
		return;
	}
	//クラスの重複する型パラメータ名を検出する
	StringView out_overwrap_tpname;
	if(!IsTypeParameterValidClass(tp->Kind.Class, &out_overwrap_tpname)) {
		bc_Panic(BCERROR_OVERWRAP_TYPE_TYPE_PARAMETER_NAME_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(out_overwrap_tpname)
		);
		return;
	}
	//メソッドの重複する型パラメータ名を検出する
	Method* out_overwrap_tpm = NULL;
	StringView out_overwrap_tpmname;
	if(!IsMethodTypeParameterValidClass(tp->Kind.Class, &out_overwrap_tpm, &out_overwrap_tpmname)) {
		bc_Panic(BCERROR_OVERWRAP_METHOD_TYPE_PARAMETER_NAME_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(out_overwrap_tpm->Name),
			Ref2Str(out_overwrap_tpmname)
		);
		return;
	}
	//コンストラクタで初期化されていない final フィールドの確認
	//これはコンストラクタが生成されてからでないといけない
	Class* cls = TYPE2CLASS(tp);
	for(int i=0; i<cls->Fields->Length; i++) {
		Field* fi = AtVector(cls->Fields, i);
		//インスタンス定数が
		//フィールドでもコンストラクタでも初期化されない
		if(!IsStaticModifier(fi->Modifier) &&
			IsFinalModifier(fi->Modifier) &&
			!fi->IsNotInitializedAtCtor) {
			bc_Panic(BCERROR_NOT_INITIAL_FIELD_NOT_INITIALIZED_AT_CTOR_T,
				Ref2Str(GetTypeName(tp)),
				Ref2Str(fi->Name)
			);
			return;
		}
	}
}

static void CLBC_check_interface(ClassLoader * self, ILType * iltype, Type* tp, Namespace * scope) {
	//重複するパラメータ名を検出する
	Method* out_overwrap_m = NULL;
	StringView out_overwrap_name;
	if(!IsMethodParameterValidInterface(tp->Kind.Interface, &out_overwrap_m, &out_overwrap_name)) {
		bc_Panic(BCERROR_OVERWRAP_PARAMETER_NAME_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(out_overwrap_m->Name),
			Ref2Str(out_overwrap_name)
		);
	}
	//インターフェイスの重複する型パラメータ名を検出する
	StringView out_overwrap_tpname;
	if(!IsTypeParameterValidInterface(tp->Kind.Interface, &out_overwrap_tpname)) {
		bc_Panic(BCERROR_OVERWRAP_TYPE_TYPE_PARAMETER_NAME_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(out_overwrap_tpname)
		);
	}
	//メソッドの重複する型パラメータ名を検出する
	Method* out_overwrap_tpm = NULL;
	StringView out_overwrap_tpmname;
	if(!IsMethodTypeParameterValidInterface(tp->Kind.Interface, &out_overwrap_tpm, &out_overwrap_tpmname)) {
		bc_Panic(BCERROR_OVERWRAP_METHOD_TYPE_PARAMETER_NAME_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(out_overwrap_tpm->Name),
			Ref2Str(out_overwrap_tpmname)
		);
	}
}