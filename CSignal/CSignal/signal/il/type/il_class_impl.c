#include "il_class_impl.h"
#include <stdlib.h>
#include "../../util/text.h"
//#include "../../env/field.h"
//#include "../../env/method.h"
#include "../il_field.h"
#include "../il_method.h"
#include "../il_constructor.h"
#include "../../util/mem.h"

//proto
static void il_class_field_delete(vector_item item);
static void il_class_method_delete(vector_item item);
static void il_class_ctor_delete(vector_item item);

il_type * il_type_wrap_class(il_class * self) {
	il_type* ret = il_type_new();
	ret->tag = iltype_class;
	ret->u.class_ = self;
	return ret;
}

il_class* il_class_new(const char* name) {
	il_class* ret = (il_class*)MEM_MALLOC(sizeof(il_class));
	ret->name = text_strdup(name);
	ret->extend_list = vector_new();
	ret->field_list = vector_new();
	ret->sfield_list = vector_new();
	ret->method_list = vector_new();
	ret->smethod_list = vector_new();
	ret->constructor_list = vector_new();
	return ret;
}

void il_class_add_field(il_class * self, il_field * f) {
	if (modifier_is_static(f->modifier)) {
		vector_push(self->sfield_list, f);
	} else {
		vector_push(self->field_list, f);
	}
}

void il_class_add_method(il_class * self, il_method * m) {
	if (modifier_is_static(m->modifier)) {
		vector_push(self->smethod_list, m);
	} else {
		vector_push(self->method_list, m);
	}
}

void il_class_dump(il_class * self, int depth) {
	text_putindent(depth);
	printf("class %s", self->name);
	text_putline();
	//ここでは親クラスとインターフェースをごちゃまぜで表示
	for (int i = 0; i < self->extend_list->length; i++) {
		fqcn_cache* e = (fqcn_cache*)vector_at(self->extend_list, i);
		fqcn_cache_dump(e, depth + 1);
	}
	for (int i = 0; i < self->field_list->length; i++) {
		vector_item e = vector_at(self->field_list, i);
		il_field* ilf = (il_field*)e;
		il_field_dump(ilf, depth + 1);
	}
	for (int i = 0; i < self->method_list->length; i++) {
		vector_item e = vector_at(self->method_list, i);
		il_method* ilm = (il_method*)e;
		il_method_dump(ilm, depth + 1);
	}
	for (int i = 0; i < self->constructor_list->length; i++) {
		vector_item e = vector_at(self->constructor_list, i);
		il_constructor* ilcons = (il_constructor*)e;
		il_constructor_dump(ilcons, depth + 1);
	}
}

void il_class_delete(il_class * self) {
	if (self == NULL) {
		return;
	}
	//printf("free class %s\n", self->name);
	MEM_FREE(self->name);
	//MEM_FREE(self->super);
	vector_delete(self->field_list, il_class_field_delete);
	vector_delete(self->sfield_list, il_class_field_delete);
	vector_delete(self->method_list, il_class_method_delete);
	vector_delete(self->smethod_list, il_class_method_delete);
	vector_delete(self->constructor_list, il_class_ctor_delete);
	MEM_FREE(self);
}

//private
static void il_class_field_delete(vector_item item) {
	il_field* e = (il_field*)item;
	il_field_delete(e);
}

static void il_class_method_delete(vector_item item) {
	il_method* e = (il_method*)item;
	il_method_delete(e);
}

static void il_class_ctor_delete(vector_item item) {
	il_constructor* e = (il_constructor*)item;
	il_constructor_delete(e);
}