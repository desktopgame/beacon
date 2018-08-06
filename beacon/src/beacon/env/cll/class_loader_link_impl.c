#include "class_loader_link_impl.h"
#include "../type_cache.h"
#include "../../error.h"
#include "../type_impl.h"
#include "../field.h"
#include "../../il/il_type_impl.h"
#include "../../error.h"
#include "../../env/constructor.h"
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
static void CLBC_yield(class_loader* parent, class_loader* target);
static void CLBC_check_class(class_loader * self, il_type * iltype, type * tp, namespace_ * scope);
static void CLBC_check_interface(class_loader * self, il_type * iltype, type * tp, namespace_ * scope);

void class_loader_link(class_loader* self, link_type type) {
	CL_ERROR(self);
	if(type == link_decl) {
		CLBC_excec_class_decl(self);
		CL_ERROR(self);
		CLBC_excec_interface_decl(self);
		CL_ERROR(self);
		CLBC_excec_enum_decl(self);
	} else if(type == link_impl) {
		CLBC_excec_class_impl(self);
		CL_ERROR(self);
		CLBC_excec_interface_impl(self);
		CL_ERROR(self);
		CLBC_excec_enum_impl(self);
	} else assert(false);
}

//private
static void CLBC_class_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & type_decl) > 0) {
		return;
	}
	#if defined(DEBUG)
	const char* name = string_pool_ref2str(type_name(tp));
	#endif
	CL_ERROR(self);
	CLBC_fields_decl(self, iltype, tp, iltype->u.class_->field_list, scope);
	CLBC_fields_decl(self, iltype, tp, iltype->u.class_->sfield_list, scope);
	CL_ERROR(self);
	CLBC_property_decl(self, iltype, tp, iltype->u.class_->prop_list, scope);
	CLBC_property_decl(self, iltype, tp, iltype->u.class_->sprop_list, scope);
	CL_ERROR(self);

	CLBC_methods_decl(self, iltype, tp, iltype->u.class_->method_list, scope);
	CLBC_methods_decl(self, iltype, tp, iltype->u.class_->smethod_list, scope);
	CL_ERROR(self);

	CLBC_ctor_decl(self, iltype, tp, scope);
	CL_ERROR(self);

	CLBC_operator_overload_decl(self, iltype, tp, scope);
	CL_ERROR(self);

	CL_ERROR(self);
	tp->state = tp->state | type_decl;
	CLBC_check_class(self, iltype, tp, scope);
}

static void CLBC_class_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & type_impl) > 0) {
		return;
	}
	#if defined(DEBUG)
	const char* tyname = string_pool_ref2str(type_name(tp));
	#endif
	class_create_vtable(tp->u.class_);
	CL_ERROR(self);
	CLBC_fields_impl(self, scope, iltype->u.class_->field_list, (TYPE2CLASS(tp))->field_list);
	CLBC_fields_impl(self, scope, iltype->u.class_->sfield_list, (TYPE2CLASS(tp))->sfield_list);
	CL_ERROR(self);
	CLBC_property_impl(self, iltype, tp, iltype->u.class_->prop_list, tp->u.class_->prop_list, scope);
	CLBC_property_impl(self, iltype, tp, iltype->u.class_->sprop_list, tp->u.class_->sprop_list, scope);
	CL_ERROR(self);

	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.class_->method_list, ((TYPE2CLASS(tp))->method_list));
	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.class_->smethod_list, ((TYPE2CLASS(tp))->smethod_list));
	CL_ERROR(self);

	CLBC_ctor_impl(self, iltype, tp);
	CL_ERROR(self);

	CLBC_operator_overload_impl(self, iltype, tp, scope);
	CL_ERROR(self);
	tp->state = tp->state | type_impl;
}

static void CLBC_interface_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & type_decl) > 0) {
		return;
	}
	assert(tp->u.interface_->method_list->length == 0);
	CL_ERROR(self);
	CLBC_methods_decl(self, iltype, tp, iltype->u.interface_->method_list, scope);
	CLBC_property_decl(self, iltype, tp, iltype->u.interface_->prop_list, scope);
	CL_ERROR(self);
	interface_create_vtable(tp->u.interface_);
	tp->state = tp->state | type_decl;
	CLBC_check_interface(self, iltype, tp, scope);
}

static void CLBC_interface_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & type_impl) > 0) {
		return;
	}
	CL_ERROR(self);
	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.interface_->method_list, tp->u.interface_->method_list);
	tp->state = tp->state | type_impl;
}

static void CLBC_enum_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & type_decl) > 0) {
		return;
	}
	//重複するフィールドを確認する
	field* outField = NULL;
	if((tp->tag == type_enum ||
	   tp->tag == type_class) &&
	   !class_field_valid(tp->u.class_, &outField)) {
		bc_error_throw(bcerror_overwrap_field_name, string_pool_ref2str(tp->u.class_->namev), string_pool_ref2str(outField->namev));
	}
	tp->state = tp->state | type_decl;
}

static void CLBC_enum_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & type_impl) > 0) {
		return;
	}
	tp->state = tp->state | type_impl;
}

static void CLBC_excec_class_decl(class_loader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_class_decl || e->consume) {
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
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_class_impl || e->consume) {
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
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_interface_decl || e->consume) {
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
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_interface_impl || e->consume) {
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
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_enum_decl || e->consume) {
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
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_enum_impl || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_enum_impl(e->context, e->iltype, e->tp, e->scope);
	}
}
//FIXME:コピペ

static void CLBC_yield(class_loader* parent, class_loader* target) {
	CL_ERROR(parent);
	CL_ERROR(target);
	assert(target->source_code != NULL);
	CLBC_import(target, target->il_code->import_list);
//	CLBC_namespace_tree(target);
}

static void CLBC_check_class(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	//実装されていないインターフェイスを確認する
	method* outiMethod = NULL;
	if(tp->tag == type_class &&
	  !class_interface_implement_valid(TYPE2CLASS(tp), &outiMethod)) {
		bc_error_throw(bcerror_not_implement_interface, string_pool_ref2str(tp->u.class_->namev), string_pool_ref2str(outiMethod->namev));
	}
	//実装されていない抽象メソッドを確認する
	method* outaMethod = NULL;
	if(tp->tag == type_class &&
	   !class_abstract_class_implement_valid(TYPE2CLASS(tp), &outaMethod)) {
		bc_error_throw(bcerror_not_implement_abstract_method, string_pool_ref2str(tp->u.class_->namev), string_pool_ref2str(outaMethod->namev));
	   }
	//重複するフィールドを確認する
	field* outField = NULL;
	if(!class_field_valid(tp->u.class_, &outField)) {
		bc_error_throw(bcerror_overwrap_field_name, string_pool_ref2str(tp->u.class_->namev), string_pool_ref2str(outField->namev));
	}
	//メソッドの重複するパラメータ名を検出する
	method* out_overwrap_m = NULL;
	string_view out_overwrap_mname;
	if(!class_method_parameter_valid(tp->u.class_, &out_overwrap_m, &out_overwrap_mname)) {
		bc_error_throw(bcerror_overwrap_parameter_name,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(out_overwrap_m->namev),
			string_pool_ref2str(out_overwrap_mname)
		);
	}
	//コンストラクタの重複するパラメータ名を検出する
	constructor* out_overwrap_c = NULL;
	string_view out_overwrap_cname;
	if(!class_ctor_parameter_valid(tp->u.class_, &out_overwrap_c, &out_overwrap_cname)) {
		bc_error_throw(bcerror_overwrap_parameter_name,
			string_pool_ref2str(type_name(tp)),
			"new",
			string_pool_ref2str(out_overwrap_cname)
		);
	}
	//クラスの重複する型パラメータ名を検出する
	string_view out_overwrap_tpname;
	if(!class_type_type_parameter_valid(tp->u.class_, &out_overwrap_tpname)) {
		bc_error_throw(bcerror_overwrap_type_type_parameter_name,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(out_overwrap_tpname)
		);
	}
	//メソッドの重複する型パラメータ名を検出する
	method* out_overwrap_tpm = NULL;
	string_view out_overwrap_tpmname;
	if(!class_method_type_parameter_valid(tp->u.class_, &out_overwrap_tpm, &out_overwrap_tpmname)) {
		bc_error_throw(bcerror_overwrap_method_type_parameter_name,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(out_overwrap_tpm->namev),
			string_pool_ref2str(out_overwrap_tpmname)
		);
	}
}

static void CLBC_check_interface(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	//重複するパラメータ名を検出する
	method* out_overwrap_m = NULL;
	string_view out_overwrap_name;
	if(!interface_method_parameter_valid(tp->u.interface_, &out_overwrap_m, &out_overwrap_name)) {
		bc_error_throw(bcerror_overwrap_parameter_name,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(out_overwrap_m->namev),
			string_pool_ref2str(out_overwrap_name)
		);
	}
	//インターフェイスの重複する型パラメータ名を検出する
	string_view out_overwrap_tpname;
	if(!interface_type_type_parameter_valid(tp->u.interface_, &out_overwrap_tpname)) {
		bc_error_throw(bcerror_overwrap_type_type_parameter_name,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(out_overwrap_tpname)
		);
	}
	//メソッドの重複する型パラメータ名を検出する
	method* out_overwrap_tpm = NULL;
	string_view out_overwrap_tpmname;
	if(!interface_method_type_parameter_valid(tp->u.interface_, &out_overwrap_tpm, &out_overwrap_tpmname)) {
		bc_error_throw(bcerror_overwrap_method_type_parameter_name,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(out_overwrap_tpm->namev),
			string_pool_ref2str(out_overwrap_tpmname)
		);
	}
}