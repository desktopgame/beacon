#include "class_loader_link_impl.h"
#include "../type_cache.h"
#include "../type_impl.h"
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

static void CLBC_excec_class_decl(class_loader* self);
static void CLBC_excec_class_impl(class_loader* self);
static void CLBC_excec_interface_decl(class_loader* self);
static void CLBC_excec_interface_impl(class_loader* self);
static void CLBC_yield(class_loader* parent, class_loader* target);

void class_loader_link(class_loader* self, link_type type) {
	CL_ERROR(self);
	if(type == link_decl) {
		CLBC_excec_class_decl(self);
		CLBC_excec_interface_decl(self);
	} else if(type == link_impl) {
		CLBC_excec_class_impl(self);
		CLBC_excec_interface_impl(self);
	} else assert(false);
}

//private
static void CLBC_class_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	assert(tp->u.class_->method_list->length == 0);
	assert(tp->u.class_->smethod_list->length == 0);
	CL_ERROR(self);
	CLBC_fields_decl(self, iltype, tp, iltype->u.class_->field_list, scope);
	CLBC_fields_decl(self, iltype, tp, iltype->u.class_->sfield_list, scope);

	CLBC_methods_decl(self, iltype, tp, iltype->u.class_->method_list, scope);
	CLBC_methods_decl(self, iltype, tp, iltype->u.class_->smethod_list, scope);

	CLBC_ctor_decl(self, iltype, tp, scope);
	class_create_vtable(tp->u.class_);
}

static void CLBC_class_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	CL_ERROR(self);
	CLBC_fields_impl(self, scope, iltype->u.class_->field_list, (TYPE2CLASS(tp))->field_list);
	CLBC_fields_impl(self, scope, iltype->u.class_->sfield_list, (TYPE2CLASS(tp))->sfield_list);
	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.class_->method_list, ((TYPE2CLASS(tp))->method_list));
	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.class_->smethod_list, ((TYPE2CLASS(tp))->smethod_list));
	CLBC_ctor_impl(self, iltype, tp);
	//text_printf("impl class %s\n", type_name(tp));
}

static void CLBC_interface_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	assert(tp->u.interface_->method_list->length == 0);
	CL_ERROR(self);
	CLBC_methods_decl(self, iltype, tp, iltype->u.interface_->method_list, scope);
	interface_create_vtable(tp->u.interface_);
}

static void CLBC_interface_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	CL_ERROR(self);
	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.interface_->method_list, tp->u.interface_->method_list);
}

static void CLBC_excec_class_decl(class_loader* self) {
	CL_ERROR(self);
	//*
	int count = 0;
	//text_printfln("CLASS_DECL %s ==", self->filename);
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_class_decl || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_class_decl(e->context, e->iltype, e->tp, e->scope);
	}
	//*/
}

static void CLBC_excec_class_impl(class_loader* self) {
	//*
	int count = 0;
	//text_printfln("CLASS_IMPL %s ==", self->filename);
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_class_impl || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_class_impl(e->context, e->iltype, e->tp, e->scope);
	}
	//*/
}

static void CLBC_excec_interface_decl(class_loader* self) {
	CL_ERROR(self);
	//*
	int count = 0;
	//text_printfln("INTERFACE_DECL %s ==", self->filename);
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_interface_decl || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_interface_decl(e->context, e->iltype, e->tp, e->scope);
	}
	//*/
}

static void CLBC_excec_interface_impl(class_loader* self) {
	CL_ERROR(self);
	int count = 0;
	//*
	//text_printfln("INTERFACE_IMPL %s ==", self->filename);
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_interface_impl || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_interface_impl(e->context, e->iltype, e->tp, e->scope);
	}
	//*/
}

static void CLBC_yield(class_loader* parent, class_loader* target) {
	CL_ERROR(parent);
	CL_ERROR(target);
	assert(target->source_code != NULL);
	CLBC_import(target, target->il_code->import_list);
	CLBC_namespace_tree(target);
}