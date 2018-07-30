#include "class_loader_link_impl.h"
#include "../type_cache.h"
#include "../type_impl.h"
#include "../field.h"
#include "../../il/il_type_impl.h"
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
//	assert(tp->u.class_->method_list->length == 0);
//	assert(tp->u.class_->smethod_list->length == 0);
	CL_ERROR(self);
	CLBC_fields_decl(self, iltype, tp, iltype->u.class_->field_list, scope);
	CLBC_fields_decl(self, iltype, tp, iltype->u.class_->sfield_list, scope);
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
	interface_create_vtable(tp->u.interface_);
	tp->state = tp->state | type_decl;
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
		class_loader_report(self, clerror_field_name_a_overlapped, string_pool_ref2str(tp->u.class_->namev), string_pool_ref2str(outField->namev));
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