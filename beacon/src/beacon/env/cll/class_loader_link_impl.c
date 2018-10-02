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

static void CLBC_class_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);
static void CLBC_class_impl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);

static void CLBC_interface_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);
static void CLBC_interface_impl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);

static void CLBC_enum_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope);
static void CLBC_enum_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope);

static void CLBC_excec_class_decl(class_loader* self);
static void CLBC_excec_class_impl(class_loader* self);
static void CLBC_excec_interface_decl(class_loader* self);
static void CLBC_excec_interface_impl(class_loader* self);
static void CLBC_excec_enum_decl(class_loader* self);
static void CLBC_excec_enum_impl(class_loader* self);
static void CLBC_check_class(class_loader * self, il_type * iltype, type * tp, namespace_ * scope);
static void CLBC_check_interface(class_loader * self, il_type * iltype, type * tp, namespace_ * scope);

void class_loader_link(class_loader* self, link_type type) {
	CL_ERROR(self);
	SetBCErrorFile(self->filename);
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
static void CLBC_class_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & TYPE_DECL) > 0) {
		return;
	}
	#if defined(DEBUG)
	const char* name = Ref2Str(GetTypeName(tp));
	#endif
	CL_ERROR(self);
	CLBC_fields_decl(self, iltype, tp, iltype->u.class_->field_list, scope);
	CLBC_fields_decl(self, iltype, tp, iltype->u.class_->sfield_list, scope);
	CL_ERROR(self);
	CLBC_properties_decl(self, iltype, tp, iltype->u.class_->prop_list, scope);
	CLBC_properties_decl(self, iltype, tp, iltype->u.class_->sprop_list, scope);
	CL_ERROR(self);

	CLBC_methods_decl(self, iltype, tp, iltype->u.class_->method_list, scope);
	CLBC_methods_decl(self, iltype, tp, iltype->u.class_->smethod_list, scope);
	CL_ERROR(self);

	CLBC_ctors_decl(self, iltype, tp, scope);
	CL_ERROR(self);

	CLBC_operator_overloads_decl(self, iltype, tp, scope);
	CL_ERROR(self);

	CL_ERROR(self);
	tp->state = tp->state | TYPE_DECL;
}

static void CLBC_class_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & TYPE_IMPL) > 0) {
		return;
	}
	#if defined(DEBUG) || defined(_DEBUG)
	const char* tyname = Ref2Str(GetTypeName(tp));
	#endif
	class_create_vtable(tp->u.class_);
	class_create_operator_vt(tp->u.class_);
	CL_ERROR(self);
	CLBC_fields_impl(self, scope, tp, iltype->u.class_->field_list, (TYPE2CLASS(tp))->field_list);
	CLBC_fields_impl(self, scope, tp, iltype->u.class_->sfield_list, (TYPE2CLASS(tp))->sfield_list);
	CL_ERROR(self);
	CLBC_properties_impl(self, iltype, tp, iltype->u.class_->prop_list, tp->u.class_->prop_list, scope);
	CLBC_properties_impl(self, iltype, tp, iltype->u.class_->sprop_list, tp->u.class_->sprop_list, scope);
	CL_ERROR(self);

	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.class_->method_list, ((TYPE2CLASS(tp))->method_list));
	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.class_->smethod_list, ((TYPE2CLASS(tp))->smethod_list));
	CL_ERROR(self);

	CLBC_ctors_impl(self, iltype, tp);
	CL_ERROR(self);

	CLBC_operator_overloads_impl(self, iltype, tp, scope);
	CL_ERROR(self);
	tp->state = tp->state | TYPE_IMPL;
	CLBC_check_class(self, iltype, tp, scope);
}

static void CLBC_interface_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & TYPE_DECL) > 0) {
		return;
	}
	assert(tp->u.interface_->method_list->length == 0);
	CL_ERROR(self);
	CLBC_methods_decl(self, iltype, tp, iltype->u.interface_->method_list, scope);
	CLBC_properties_decl(self, iltype, tp, iltype->u.interface_->prop_list, scope);
	//privateなメンバーは定義できない
	for(int i=0; i<tp->u.interface_->method_list->length; i++) {
		method* e = AtVector(tp->u.interface_->method_list, i);
		if(e->access == ACCESS_PRIVATE_T) {
			ThrowBCError(
				BCERROR_INTERFACE_HAS_PRIVATE_MEMBER_T,
				Ref2Str(GetTypeName(tp)),
				Ref2Str(e->namev)
			);
		}
	}
	for(int i=0; i<tp->u.interface_->prop_list->length; i++) {
		property* e = AtVector(tp->u.interface_->prop_list, i);
		if(e->access == ACCESS_PRIVATE_T) {
			ThrowBCError(
				BCERROR_INTERFACE_HAS_PRIVATE_MEMBER_T,
				Ref2Str(GetTypeName(tp)),
				Ref2Str(e->namev)
			);
		}
	}
	CL_ERROR(self);
	interface_create_vtable(tp->u.interface_);
	tp->state = tp->state | TYPE_DECL;
	CLBC_check_interface(self, iltype, tp, scope);
}

static void CLBC_interface_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & TYPE_IMPL) > 0) {
		return;
	}
	CL_ERROR(self);
	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.interface_->method_list, tp->u.interface_->method_list);
	tp->state = tp->state | TYPE_IMPL;
}

static void CLBC_enum_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & TYPE_DECL) > 0) {
		return;
	}
	//重複するフィールドを確認する
	field* outField = NULL;
	if((tp->tag == TYPE_ENUM_T ||
	   tp->tag == TYPE_CLASS_T) &&
	   !class_field_valid(tp->u.class_, &outField)) {
		ThrowBCError(BCERROR_OVERWRAP_FIELD_NAME_T, Ref2Str(tp->u.class_->namev), Ref2Str(outField->namev));
	}
	tp->state = tp->state | TYPE_DECL;
}

static void CLBC_enum_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & TYPE_IMPL) > 0) {
		return;
	}
	for(int i=0; i<tp->u.class_->sfield_list->length; i++) {
		field* f = AtVector(tp->u.class_->sfield_list, i);
		f->static_value = GetIntObject(i);
	}
	tp->state = tp->state | TYPE_IMPL;
}

static void CLBC_excec_class_decl(class_loader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)AtVector(self->type_cache_vec, i);
		if (e->kind != CACHEKIND_CLASS_DECL_T || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_class_decl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void CLBC_excec_class_impl(class_loader* self) {
	int count = 0;
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)AtVector(self->type_cache_vec, i);
		if (e->kind != CACHEKIND_CLASS_IMPL_T || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_class_impl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void CLBC_excec_interface_decl(class_loader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)AtVector(self->type_cache_vec, i);
		if (e->kind != CACHEKIND_INTERFACE_DECL_T || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_interface_decl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void CLBC_excec_interface_impl(class_loader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)AtVector(self->type_cache_vec, i);
		if (e->kind != CACHEKIND_INTERFACE_IMPL_T || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_interface_impl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void CLBC_excec_enum_decl(class_loader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)AtVector(self->type_cache_vec, i);
		if (e->kind != CACHEKIND_ENUM_DECL_T || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_enum_decl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void CLBC_excec_enum_impl(class_loader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)AtVector(self->type_cache_vec, i);
		if (e->kind != CACHEKIND_ENUM_IMPL_T || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_enum_impl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void CLBC_check_class(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	//実装されていないインターフェイスを確認する
	method* outiMethod = NULL;
	if(tp->tag == TYPE_CLASS_T &&
	  !class_interface_method_implement_valid(TYPE2CLASS(tp), &outiMethod)) {
		ThrowBCError(BCERROR_NOT_IMPLEMENT_INTERFACE_T, Ref2Str(tp->u.class_->namev), Ref2Str(outiMethod->namev));
		return;
	}
	//実装されていないプロパティを確認する
	property* outiProperty = NULL;
	if(tp->tag == TYPE_CLASS_T &&
	  !class_interface_property_implement_valid(TYPE2CLASS(tp), &outiProperty)) {
		ThrowBCError(BCERROR_NOT_IMPLEMENT_ABSTRACT_METHOD_T, Ref2Str(tp->u.class_->namev), Ref2Str(outiProperty->namev));
		return;
	}
	//実装されていない抽象メソッドを確認する
	method* outaMethod = NULL;
	if(tp->tag == TYPE_CLASS_T &&
	   !class_abstract_class_implement_valid(TYPE2CLASS(tp), &outaMethod)) {
		ThrowBCError(BCERROR_NOT_IMPLEMENT_ABSTRACT_METHOD_T, Ref2Str(tp->u.class_->namev), Ref2Str(outaMethod->namev));
		return;
	   }
	//重複するプロパティを確認する
	property* outProp = NULL;
	if(!class_property_valid(tp->u.class_, &outProp)) {
		ThrowBCError(BCERROR_OVERWRAP_PROPERTY_NAME_T,
			Ref2Str(tp->u.class_->namev),
			Ref2Str(outProp->namev)
		);
		return;
	}
	//重複するフィールドを確認する
	field* outField = NULL;
	if(!class_field_valid(tp->u.class_, &outField)) {
		ThrowBCError(BCERROR_OVERWRAP_FIELD_NAME_T,
			Ref2Str(tp->u.class_->namev),
			Ref2Str(outField->namev)
		);
		return;
	}
	//メソッドの重複するパラメータ名を検出する
	method* out_overwrap_m = NULL;
	string_view out_overwrap_mname;
	if(!class_method_parameter_valid(tp->u.class_, &out_overwrap_m, &out_overwrap_mname)) {
		ThrowBCError(BCERROR_OVERWRAP_PARAMETER_NAME_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(out_overwrap_m->namev),
			Ref2Str(out_overwrap_mname)
		);
		return;
	}
	//コンストラクタの重複するパラメータ名を検出する
	constructor* out_overwrap_c = NULL;
	string_view out_overwrap_cname;
	if(!class_ctor_parameter_valid(tp->u.class_, &out_overwrap_c, &out_overwrap_cname)) {
		ThrowBCError(BCERROR_OVERWRAP_PARAMETER_NAME_T,
			Ref2Str(GetTypeName(tp)),
			"new",
			Ref2Str(out_overwrap_cname)
		);
		return;
	}
	//クラスの重複する型パラメータ名を検出する
	string_view out_overwrap_tpname;
	if(!class_type_type_parameter_valid(tp->u.class_, &out_overwrap_tpname)) {
		ThrowBCError(BCERROR_OVERWRAP_TYPE_TYPE_PARAMETER_NAME_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(out_overwrap_tpname)
		);
		return;
	}
	//メソッドの重複する型パラメータ名を検出する
	method* out_overwrap_tpm = NULL;
	string_view out_overwrap_tpmname;
	if(!class_method_type_parameter_valid(tp->u.class_, &out_overwrap_tpm, &out_overwrap_tpmname)) {
		ThrowBCError(BCERROR_OVERWRAP_METHOD_TYPE_PARAMETER_NAME_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(out_overwrap_tpm->namev),
			Ref2Str(out_overwrap_tpmname)
		);
		return;
	}
	//コンストラクタで初期化されていない final フィールドの確認
	//これはコンストラクタが生成されてからでないといけない
	class_* cls = TYPE2CLASS(tp);
	for(int i=0; i<cls->field_list->length; i++) {
		field* fi = AtVector(cls->field_list, i);
		//インスタンス定数が
		//フィールドでもコンストラクタでも初期化されない
		if(!IsStaticModifier(fi->modifier) &&
			IsFinalModifier(fi->modifier) &&
			!fi->not_initialized_at_ctor) {
			ThrowBCError(BCERROR_NOT_INITIAL_FIELD_NOT_INITIALIZED_AT_CTOR_T,
				Ref2Str(GetTypeName(tp)),
				Ref2Str(fi->namev)
			);
			return;
		}
	}
}

static void CLBC_check_interface(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	//重複するパラメータ名を検出する
	method* out_overwrap_m = NULL;
	string_view out_overwrap_name;
	if(!interface_method_parameter_valid(tp->u.interface_, &out_overwrap_m, &out_overwrap_name)) {
		ThrowBCError(BCERROR_OVERWRAP_PARAMETER_NAME_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(out_overwrap_m->namev),
			Ref2Str(out_overwrap_name)
		);
	}
	//インターフェイスの重複する型パラメータ名を検出する
	string_view out_overwrap_tpname;
	if(!interface_type_type_parameter_valid(tp->u.interface_, &out_overwrap_tpname)) {
		ThrowBCError(BCERROR_OVERWRAP_TYPE_TYPE_PARAMETER_NAME_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(out_overwrap_tpname)
		);
	}
	//メソッドの重複する型パラメータ名を検出する
	method* out_overwrap_tpm = NULL;
	string_view out_overwrap_tpmname;
	if(!interface_method_type_parameter_valid(tp->u.interface_, &out_overwrap_tpm, &out_overwrap_tpmname)) {
		ThrowBCError(BCERROR_OVERWRAP_METHOD_TYPE_PARAMETER_NAME_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(out_overwrap_tpm->namev),
			Ref2Str(out_overwrap_tpmname)
		);
	}
}