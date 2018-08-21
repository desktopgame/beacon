#include "class_impl.h"
#include "../../util/text.h"
#include "../parameter.h"
#include "../../il/il_argument.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../util/mem.h"
#include "../object.h"
#include "../../vm/enviroment.h"
#include "../../vm/frame.h"
#include "../../util/text.h"
#include "../field.h"
#include "../property.h"
#include "../method.h"
#include "../constructor.h"
#include "../type_impl.h"
#include "../../env/vtable.h"
#include "../../env/heap.h"
#include "../../env/operator_overload.h"
#include "meta_impl.h"
#include "class_find.h"
#include "../type_parameter.h"
#include "../generic_type.h"
#include "../generic_type.h"
#include "../operator_overload.h"

//http://jumble-note.blogspot.jp/2012/09/c-vacopy.html
#ifndef va_copy
#    define va_copy(dest, src) ((dest) = (src))
#endif

//private
static void class_create_vtable_top(class_* self);
static void class_create_vtable_override(class_* self);
static void class_create_vtable_interface(class_* self);
static void class_impl_delete(vector_item item);
static void class_field_delete(vector_item item);
static void class_method_delete(vector_item item);
static void class_ctor_delete(vector_item item);
static void class_native_method_ref_delete(numeric_key key, numeric_map_item item);
static method* class_find_impl_method(class_* self, method* virtualMethod);
static void class_vtable_vec_delete(vector_item item);
static void class_type_parameter_delete(vector_item item);
static void class_generic_type_list_delete(vector_item item);
static void class_delete_operator_overload(vector_item item);
static void class_delete_property(vector_item item);

type * type_wrap_class(class_ * self) {
	type* ret = type_new();
	ret->tag = type_class_T;
	ret->u.class_ = self;
	self->parent = ret;
	return ret;
}

class_ * class_new(string_view namev) {
	class_* ret = (class_*)MEM_MALLOC(sizeof(class_));
	ret->namev = namev;
	ret->parent = NULL;
	ret->location = NULL;
	ret->ref_count = 0;
	ret->super_class = NULL;
	ret->impl_list = vector_new();
	ret->field_list = vector_new();
	ret->sfield_list = vector_new();
	ret->prop_list = vector_new();
	ret->sprop_list = vector_new();
	ret->method_list = vector_new();
	ret->smethod_list = vector_new();
	ret->constructor_list = vector_new();
	ret->native_method_ref_nmap = numeric_map_new();
	ret->vt_vec = vector_new();
	ret->type_parameter_list = vector_new();
	ret->vt = NULL;
	ret->ovt = NULL;
	ret->is_abstract = false;
	ret->operator_overload_list = vector_new();
	return ret;
}

class_* class_new_proxy(generic_type* gt, string_view namev) {
	assert(gt->core_type->tag == type_interface_T);
	class_* ret = class_new(namev);
	ret->super_class = GENERIC_OBJECT;
	vector_push(ret->impl_list, gt);
	return ret;
}

type* class_new_preload(string_view namev) {
	class_* cl = class_new(namev);
	type* tp = type_wrap_class(cl);
	tp->state = type_pending;
	if (TYPE_OBJECT == NULL) {
		return tp;
	}
	class_* objCls = TYPE_OBJECT->u.class_;
	if (cl != objCls) {
		type_init_generic(objCls->parent, 0);
		cl->super_class = objCls->parent->generic_self;
	}
	return tp;
}

void class_alloc_fields(class_ * self, object * o, frame* fr) {
	assert(o->tag == object_ref_T);
	heap* he = heap_get();
	for (int i = 0; i < self->field_list->length; i++) {
		field* f = (field*)vector_at(self->field_list, i);
		object* a = object_default(f->gtype);
		//静的フィールドは別の場所に確保
		if (modifier_is_static(f->modifier)) {
			continue;
		}
		he->collect_blocking++;
		if(f->initial_value != NULL) {
			frame* sub = frame_sub(fr);
			for(int i=0; i<fr->type_args_vec->length; i++) {
				vector_push(sub->type_args_vec, vector_at(fr->type_args_vec, i));
			}
			sub->receiver = self->parent;
			vector_copy(fr->ref_stack, sub->ref_stack);
			vm_execute(sub, f->initial_value_env);
			a = vector_pop(sub->value_stack);
			frame_delete(sub);
		}
		vector_push(o->u.field_vec, a);
		he->collect_blocking--;
	}
}

void class_free_fields(class_ * self, object * o) {
}

void class_add_field(class_ * self, field * f) {
	assert(f != NULL);
	if (modifier_is_static(f->modifier)) {
		vector_push(self->sfield_list, f);
	} else {
		vector_push(self->field_list, f);
	}
}

void class_add_property(class_* self, property* p) {
	if (modifier_is_static(p->modifier)) {
		vector_push(self->sprop_list, p);
	} else {
		vector_push(self->prop_list, p);
	}
	//プロパティが単純な省略形として記述されているなら、
	//それはフィールドと同じなのでフィールドも定義する
	#if defined(DEBUG)
	const char* name = string_pool_ref2str(p->namev);
	#endif
	if(p->is_short) {
		field* f = field_new(string_pool_concat("$propery.", p->namev));
		f->access = access_private_T;
		f->gtype = p->gtype;
		f->modifier = p->modifier;
		f->parent = self->parent;
		f->static_value = object_get_null();
		p->source_ref = f;
		class_add_field(self, f);
	}
}

void class_add_method(class_ * self, method * m) {
	assert(m != NULL);
	if (modifier_is_static(m->modifier)) {
		vector_push(self->smethod_list, m);
	} else {
		vector_push(self->method_list, m);
	}
}

void class_add_constructor(class_ * self, constructor * c) {
	vector_push(self->constructor_list, c);
}

void class_define_native_method(class_* self, const char* name, native_impl impl) {
	class_define_native_method_by_ref(self, string_pool_intern(name), impl);
}

void class_define_native_method_by_ref(class_ * self, string_view namev, native_impl impl) {
	native_method_ref* ref = native_method_ref_new(impl);
	numeric_map_put(self->native_method_ref_nmap, namev, ref);
}

int class_distance(class_ * super, class_ * sub) {
	if (super == sub) {
		return 0;
	}
	int depth = 0;
	class_* pointee = sub;
	do {
		if (pointee == super) {
			return depth;
		}
		generic_type* super_gtype = pointee->super_class;
		if(super_gtype == NULL) {
			depth = -1;
			break;
		}
		pointee = super_gtype->core_type->u.class_;
		depth++;
		if (pointee == NULL) {
			depth = -1;
			break;
		}
	} while (1);
	return depth;
}

void class_create_vtable(class_ * self) {
	//TEST(!strcmp(self->name, "Int"));
	#if defined(DEBUG)
	const char* str = string_pool_ref2str(self->namev);
	#endif
	assert(self != NULL);
	//初期化済み
	if (self->vt != NULL) {
		return;
	}
	self->vt = vtable_new();
	//トップレベルではメソッドの一覧を配列に入れるだけ
	if (self->super_class == NULL) {
		class_create_vtable_top(self);
	//あるクラスを継承する場合には、
	//重複するメソッドを上書きするように
	} else {
		class_create_vtable_override(self);
	}
	class_create_vtable_interface(self);
	assert(self->vt->elements->length != 0);
}

void class_create_operator_vt(class_* self) {
	if(self->ovt != NULL) {
		return;
	}
	if(self->super_class != NULL) {
		class_create_operator_vt(TYPE2CLASS(GENERIC2TYPE(self->super_class)));
	}
	self->ovt = operator_vt_new();
	if(self->super_class == NULL) {
		for(int i=0; i<self->operator_overload_list->length; i++) {
			operator_overload* opov = vector_at(self->operator_overload_list, i);
			vector_push(self->ovt->vec, opov);
		}
	} else {
		operator_vt* super_vt = TYPE2CLASS(GENERIC2TYPE(self->super_class))->ovt;
		for(int i=0; i<super_vt->vec->length; i++) {
			operator_overload* opov = vector_at(super_vt->vec, i);
			vector_push(self->ovt->vec, opov);
		}
		for(int i=0; i<self->operator_overload_list->length; i++) {
			operator_overload* opov = vector_at(self->operator_overload_list, i);
			operator_vt_replace(self->ovt, opov);
		}
	}
}

int class_count_fieldall(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->field_list->length);
		if(pt->super_class == NULL) {
			break;
		}
		pt = pt->super_class->core_type->u.class_;
	} while (pt != NULL);
	return sum;
}

int class_count_sfieldall(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->sfield_list->length);
		if(pt->super_class == NULL) {
			break;
		}
		pt = pt->super_class->core_type->u.class_;
	} while (pt != NULL);
	return sum;
}

int class_count_propertyall(class_* self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->prop_list->length);
		if(pt->super_class == NULL) {
			break;
		}
		pt = pt->super_class->core_type->u.class_;
	} while (pt != NULL);
	return sum;
}

int class_count_spropertyall(class_* self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->sprop_list->length);
		if(pt->super_class == NULL) {
			break;
		}
		pt = pt->super_class->core_type->u.class_;
	} while (pt != NULL);
	return sum;
}

int class_count_methodall(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->method_list->length);
		if(pt->super_class == NULL) {
			break;
		}
		pt = pt->super_class->core_type->u.class_;
	} while (pt != NULL);
	return sum;
}

int class_count_smethodall(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->smethod_list->length);
		if(pt->super_class == NULL) {
			break;
		}
		pt = pt->super_class->core_type->u.class_;
	} while (pt != NULL);
	return sum;
}

object * class_new_instance(class_* self, frame* fr, vector* args, vector* type_args) {
	//コンストラクタを検索
	int temp = 0;
	constructor* ctor = class_rfind_constructor(self, args, NULL, fr, &temp);
	assert(temp != -1);
	//コンストラクタを実行
	frame* sub = frame_sub(fr);
	heap* h = heap_get();
	if(args != NULL) {
		for (int i = args->length-1; i>=0; i--) {
			object* o = vector_at(args, i);
			vector_push(sub->value_stack, o);
		}
	}
	if(type_args != NULL) {
		for(int i = 0; i<type_args->length; i++) {
			vector_push(sub->type_args_vec, vector_at(type_args, i));
		}
	}
	vm_execute(sub, ctor->env);
	object* inst = vector_pop(sub->value_stack);
	h->collect_blocking++;
	frame_delete(sub);
	h->collect_blocking--;
	return inst;
}

void class_linkall(class_ * self) {
	for (int i = 0; i < self->field_list->length; i++) {
		field* f = (field*)vector_at(self->field_list, i);
		f->parent = self->parent;
	}
	for (int i = 0; i < self->method_list->length; i++) {
		method* m = (method*)vector_at(self->method_list, i);
		m->parent = self->parent;
	}
	for (int i = 0; i < self->constructor_list->length; i++) {
		constructor* ctor = (constructor*)vector_at(self->constructor_list, i);
		ctor->parent = self->parent;
	}
}

void class_unlink(class_ * self) {
	if (self->super_class != NULL) {
		self->super_class->core_type->u.class_->ref_count--;
	}
	//XSTREQ(self->name, "Object");
	//generic_type_delete(self->super_class);
	//printf("unlink %s\n", self->name);
	numeric_map_delete(self->native_method_ref_nmap, class_native_method_ref_delete);
	vector_delete(self->impl_list, class_impl_delete);
	vector_delete(self->field_list, class_field_delete);
	vector_delete(self->sfield_list, class_field_delete);
	vector_delete(self->method_list, class_method_delete);
	vector_delete(self->smethod_list, class_method_delete);
	vector_delete(self->constructor_list, class_ctor_delete);
	vector_delete(self->operator_overload_list, class_delete_operator_overload);
	vector_delete(self->prop_list, class_delete_property);
	vector_delete(self->sprop_list, class_delete_property);
	vtable_delete(self->vt);
	operator_vt_delete(self->ovt);
	vector_delete(self->vt_vec, class_vtable_vec_delete);
}

void class_delete(class_ * self) {
//	assert(self->ref_count == 0);
//	MEM_FREE(self->name);
	//printf("delete %s\n", self->name);
	vector_delete(self->type_parameter_list, class_type_parameter_delete);
	MEM_FREE(self);
}

//private
static void class_create_vtable_top(class_* self) {
	for (int i = 0; i < self->method_list->length; i++) {
		method* m = (method*)vector_at(self->method_list, i);
		if(m->access != access_private_T &&
		   !modifier_is_static(m->modifier)) {
			vtable_add(self->vt, m);
		}
	}
}

static void class_create_vtable_override(class_* self) {
	#if defined(DEBUG)
	const char* clname = string_pool_ref2str(self->namev);
	#endif
	call_context* cctx = call_context_new(call_decl_T);
	cctx->space = self->parent->location;
	cctx->ty = self->super_class->core_type;
	class_create_vtable(self->super_class->core_type->u.class_);
	vtable_copy(self->super_class->core_type->u.class_->vt, self->vt);
	for (int i = 0; i < self->method_list->length; i++) {
		method* m = (method*)vector_at(self->method_list, i);
		if(m->access != access_private_T &&
		   !modifier_is_static(m->modifier)) {
			vtable_replace(self->vt, m, cctx);
		}
	}
	call_context_delete(cctx);
}

static void class_create_vtable_interface(class_* self) {
	#if defined(DEBUG)
	const char* clname = string_pool_ref2str(type_name(self->parent));
	#endif
	vector* tbl = class_get_interface_tree(self);
	//もしインターフェースを実装しているなら、
	//インターフェースに対応する同じ並びのメソッドテーブルも作る
	for (int i = 0; i < tbl->length; i++) {
		//generic_type* gtp = (generic_type*)vector_at(tbl, i);
		interface_* inter = (interface_*)vector_at(tbl, i);
		vtable* interVT = inter->vt;
		vtable* newVT = vtable_new();
		assert(interVT != NULL);
		//そのインターフェースに定義されたテーブルの一覧
		//これはスーパーインターフェースも含む。
		for (int j = 0; j < interVT->elements->length; j++) {
			//実装クラスの中の、
			//シグネチャが同じメソッドをテーブルへ。
			method* interVTM = vector_at(interVT->elements, j);
			method* classVTM = class_find_impl_method(self, interVTM);
			if(!self->is_abstract && classVTM == NULL) {
				vector_push(self->vt_vec, newVT);
				bc_error_throw(bcerror_not_implement_interface_T,
					string_pool_ref2str(type_name(interVTM->parent)),
					string_pool_ref2str(interVTM->namev)
				);
				vector_delete(tbl, vector_deleter_null);
				return;
			}
			//assert(self->is_abstract || classVTM != NULL);
			//例えば抽象クラスがインターフェイスを実装していない場合
			//空っぽの実装を持たせる
			if(self->is_abstract && classVTM == NULL) {
				classVTM = interVTM;
			}
			vtable_add(newVT, classVTM);
		}
		vector_push(self->vt_vec, newVT);
	}
	vector_delete(tbl, vector_deleter_null);
}

static void class_impl_delete(vector_item item) {
	generic_type* e = (generic_type*)item;
	//generic_type_delete(e);
}

static void class_field_delete(vector_item item) {
	field* e = (field*)item;
	field_delete(e);
}

static void class_method_delete(vector_item item) {
	method* e = (method*)item;
	method_delete(e);
}

static void class_ctor_delete(vector_item item) {
	constructor* e = (constructor*)item;
	constructor_delete(e);
}

static void class_native_method_ref_delete(numeric_key key, numeric_map_item item) {
	native_method_ref* e = (native_method_ref*)item;
	native_method_ref_delete(e);
}

static method* class_find_impl_method(class_* self, method* virtualMethod) {
	call_context* cctx = call_context_new(call_decl_T);
	cctx->space = self->parent->location;
	cctx->ty = self->parent;
	method* ret = NULL;
	vtable* clVT = self->vt;
	for (int i = 0; i < clVT->elements->length; i++) {
		method* clM = vector_at(clVT->elements, i);
		if (method_override(virtualMethod, clM, cctx)) {
			ret = clM;
			break;
		}
	}
	call_context_delete(cctx);
	return ret;
}

static void class_vtable_vec_delete(vector_item item) {
	vtable* e = (vtable*)item;
	vtable_delete(e);
}

static void class_type_parameter_delete(vector_item item) {
	type_parameter* e = (type_parameter*)item;
	type_parameter_delete(e);
}

static void class_generic_type_list_delete(vector_item item) {
	generic_type* e = (generic_type*)item;
//	generic_type_delete(e);
}

static void class_delete_operator_overload(vector_item item) {
	operator_overload* e = (operator_overload*)item;
	operator_overload_delete(e);
}

static void class_delete_property(vector_item item) {
	property* e = (property*)item;
	property_delete(e);
}