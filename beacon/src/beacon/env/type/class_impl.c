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
#include "../method.h"
#include "../constructor.h"
#include "../type_impl.h"
#include "../../env/vtable.h"
#include "../../env/heap.h"
#include "../../env/operator_overload.h"
#include "meta_impl.h"
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
static bool class_field_validImpl(vector* field_vec, field** out);
static void class_delete_operator_overload(vector_item item);

type * type_wrap_class(class_ * self) {
	type* ret = type_new();
	ret->tag = type_class;
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
	ret->method_list = vector_new();
	ret->smethod_list = vector_new();
	ret->constructor_list = vector_new();
	ret->native_method_ref_nmap = numeric_map_new();
	ret->vt_vec = vector_new();
	ret->type_parameter_list = vector_new();
	//FIXME:ここで持つ必要はない
	ret->classIndex = -1;
	//ret->absoluteIndex = -1;
	ret->vt = NULL;
	ret->is_abstract = false;
	ret->operator_overload_list = vector_new();
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

void class_alloc_fields(class_ * self, object * o) {
	assert(o->tag == object_ref);
	for (int i = 0; i < self->field_list->length; i++) {
		//*
		field* f = (field*)vector_at(self->field_list, i);
		object* a = object_get_null();
		//プリミティブ型のときはデフォルト値を入れておく
		if (f->gtype == TYPE_INT->generic_self) {
			a = object_int_get(0);
		} else if (f->gtype == TYPE_DOUBLE->generic_self) {
			a = object_double_new(0.0);
		} else if (f->gtype == TYPE_BOOL->generic_self) {
			a = object_bool_get(false);
		} else if (f->gtype == TYPE_CHAR->generic_self) {
			a = object_char_new('\0');
		}
		//静的フィールドは別の場所に確保
		if (modifier_is_static(f->modifier)) {
			continue;
		}
		vector_push(o->u.field_vec, a);
		//*/
	}
	class_create_vtable(self);
	o->gtype = generic_type_ref(self->parent);
	o->vptr = self->vt;
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

void class_dump(class_ * self, int depth) {
	text_putindent(depth);
	text_printf("class %s", string_pool_ref2str(self->namev));
	type_parameter_print(self->type_parameter_list);
	text_putline();
	//親クラスがあるなら表示
	if (self->super_class != NULL) {
		text_putindent(depth + 1);
		text_printf("super ");
		text_printf("%s", type_name(self->super_class->core_type));
//		generic_type_print(self->super_class->);
		text_putline();
	}
	//実装インターフェースがあるなら表示
	for (int i = 0; i < self->impl_list->length; i++) {
		generic_type* e = (generic_type*)vector_at(self->impl_list, i);
		interface_* inter = e->core_type->u.interface_;
		text_putindent(depth + 1);
		text_printf("impl %s", string_pool_ref2str(inter->namev));
		text_putline();
	}
	//フィールドの一覧をダンプ
	for (int i = 0; i < self->field_list->length; i++) {
		vector_item e = vector_at(self->field_list, i);
		field* f = (field*)e;
		field_dump(f, depth + 1);
	}
	for (int i = 0; i < self->sfield_list->length; i++) {
		vector_item e = vector_at(self->sfield_list, i);
		field* f = (field*)e;
		field_dump(f, depth + 1);
	}
	//メソッドの一覧をダンプ
	for (int i = 0; i < self->method_list->length; i++) {
		vector_item e = vector_at(self->method_list, i);
		method* m = (method*)e;
		method_dump(m, depth + 1);
	}
	for (int i = 0; i < self->smethod_list->length; i++) {
		vector_item e = vector_at(self->smethod_list, i);
		method* m = (method*)e;
		method_dump(m, depth + 1);
	}
	//コンストラクタの一覧をダンプ
	for (int i = 0; i < self->constructor_list->length; i++) {
		vector_item e = vector_at(self->constructor_list, i);
		constructor* c = (constructor*)e;
		constructor_dump(c, depth + 1);
	}
}

void class_define_native_method(class_* self, const char* name, native_impl impl) {
	class_define_native_method_by_ref(self, string_pool_intern(name), impl);
}

void class_define_native_method_by_ref(class_ * self, string_view namev, native_impl impl) {
	native_method_ref* ref = native_method_ref_new(impl);
	numeric_map_put(self->native_method_ref_nmap, namev, ref);
}

field * class_find_field(class_* self, string_view namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->field_list->length; i++) {
		vector_item e = vector_at(self->field_list, i);
		field* f = (field*)e;
		if (namev == f->namev) {
			(*outIndex) = (class_count_fieldall(self) - self->field_list->length) + i;
			return f;
		}
	}
	return NULL;
}

field * class_find_field_tree(class_ * self, string_view namev, int * outIndex) {
	class_* pointee = self;
	do {
		field* f = class_find_field(pointee, namev, outIndex);
		if (f != NULL) {
			return f;
		}
		generic_type* supergtype = pointee->super_class;
		if(supergtype == NULL) {
			break;
		}
		pointee = supergtype->core_type->u.class_;
	} while (pointee != NULL);
	return NULL;
}

field * class_find_sfield(class_ * self, string_view namev, int * outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->sfield_list->length; i++) {
		vector_item e = vector_at(self->sfield_list, i);
		field* f = (field*)e;
		if (namev == f->namev) {
			(*outIndex) = (class_count_sfieldall(self) - self->sfield_list->length) + i;
			return f;
		}
	}
	return NULL;
}

field * class_find_sfield_tree(class_ * self, string_view namev, int * outIndex) {
	class_* pointee = self;
	do {
		field* f = class_find_sfield(pointee, namev, outIndex);
		if (f != NULL) {
			return f;
		}
		if(pointee->super_class == NULL) {
			break;
		}
		pointee = pointee->super_class->core_type->u.class_;
	} while (pointee != NULL);
	return NULL;
}

field * class_get_field(class_ * self, int index) {
	assert(index >= 0);
	int all = class_count_fieldall(self);
	if (index >= (all - self->field_list->length) &&
		index < all) {
		return vector_at(self->field_list, self->field_list->length - (all - index));
	}
	return class_get_field(self->super_class->core_type->u.class_, index);
}

field * class_get_sfield(class_ * self, int index) {
	assert(index >= 0);
	int all = class_count_sfieldall(self);
	if (index >= (all - self->sfield_list->length) &&
		index < all) {
//		return vector_at(self->sfield_list, all - index);
		return vector_at(self->sfield_list, self->sfield_list->length - (all - index));
	}
	return class_get_sfield(self->super_class->core_type->u.class_, index);
}

constructor * class_rfind_constructor(class_ * self, vector * args, vector* typeargs, frame* fr, int* outIndex) {
	return meta_scoped_rfind_ctor(self, self->constructor_list, args, typeargs, fr, outIndex);
}

constructor * class_ilfind_constructor(class_ * self, vector * args, enviroment * env, int* outIndex) {
	//	vector* v = meta_find_constructors(self, args, env, ilctx);
	//	(*outIndex) = -1;
	//	return class_find_constructor_impl(v, args, env, ilctx, outIndex);
	return meta_scoped_ilfind_ctor(self, self->constructor_list, args, env, outIndex);
}

constructor * class_ilfind_empty_constructor(class_ * self, enviroment * env, int * outIndex) {
	vector* emptyArgs = vector_new();
	constructor* ret = class_ilfind_constructor(self, emptyArgs, env, outIndex);
	vector_delete(emptyArgs, vector_deleter_null);
	return ret;
}

method * class_ilfind_method(class_ * self, string_view namev, vector * args, enviroment * env, int * outIndex) {
	(*outIndex) = -1;
	class_create_vtable(self);
	//assert(self->vt->elements->length > 0);
	method* ret = NULL;
	if((ret = meta_scoped_ilfind_method(self, self->vt->elements, namev, args, env, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = meta_scoped_ilfind_method(self, self->method_list, namev, args, env, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = meta_scoped_ilfind_method(self, self->smethod_list, namev, args, env, outIndex))
	   != NULL) {
		   return ret;
	}
	return NULL;
}

struct method* class_gfind_method(class_* self, string_view namev, vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	class_create_vtable(self);
	//assert(self->vt->elements->length > 0);
	method* ret = NULL;
	if((ret = meta_scoped_gfind_method(self, self->vt->elements, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = meta_scoped_gfind_method(self, self->method_list, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = meta_scoped_gfind_method(self, self->smethod_list, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	return NULL;
}

method* class_gfind_eqmethod(class_* self, int* outIndex) {
	vector* gargs = vector_new();
	vector_push(gargs, TYPE_OBJECT->generic_self);
	method* ret = class_gfind_method(self, string_pool_intern("equals"), gargs, outIndex);
	vector_delete(gargs, vector_deleter_null);
	return ret;
}

method * class_ilfind_smethod(class_ * self, string_view namev, vector * args, enviroment * env, int * outIndex) {
	(*outIndex) = -1;
	class_create_vtable(self);
	int temp = 0;
	method* ret = meta_ilfind_method(self->smethod_list, namev, args, env, &temp);
	temp += (class_count_smethodall(self) - self->smethod_list->length);
	(*outIndex) = temp;
	return ret;
}

method* class_gfind_smethod(class_* self, string_view namev, vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	class_create_vtable(self);
	int temp = 0;
	method* ret = meta_gfind_method(self->smethod_list, namev, gargs, &temp);
	temp += (class_count_smethodall(self) - self->smethod_list->length);
	(*outIndex) = temp;
	return ret;
}

method * class_get_method(object * o, int index) {
	assert(index >= 0);
	if(o->tag == object_null) {
		o->vptr = TYPE2CLASS(TYPE_OBJECT)->vt;
	}
	vtable* vx = (o->vptr);
	return (method*)vector_at(vx->elements, index);
}

method * class_get_smethod(class_* self, int index) {
	assert(index >= 0);
	//class_* self = o->classz;
	int all = class_count_smethodall(self);
	if (index >= (all - self->smethod_list->length) &&
		index < all) {
//		return vector_at(self->smethod_list, all - index);
		return vector_at(self->smethod_list, self->smethod_list->length - (all - index));
	}
	return class_get_smethod(self->super_class->core_type->u.class_, index);
}

method * class_get_impl_method(class_ * self, type * interType, int interMIndex) {
	assert(self->vt_vec->length > 0);
	//指定のインターフェイスが
	//このクラスにおいて何番目かを調べる
	int declIndex = -1;
	for (int i = 0; i < self->impl_list->length; i++) {
		generic_type* e = vector_at(self->impl_list, i);
		interface_* inter = e->core_type->u.interface_;
		if (inter == interType->u.interface_) {
			declIndex = i;
			break;
		}
	}
	//仮想関数テーブルの一覧から引く
	assert(declIndex != -1);
	vtable* vtAt = vector_at(self->vt_vec, declIndex);
	return vector_at(vtAt->elements, interMIndex);
}

operator_overload* class_find_operator_overload(class_* self, operator_type type, vector* args, enviroment* env, int* outIndex) {
	(*outIndex) = -1;
	operator_overload* ret = NULL;
	for(int i=0; i<self->operator_overload_list->length; i++) {
		operator_overload* operator_ov = vector_at(self->operator_overload_list, i);
		if(operator_ov->type != type) {
			continue;
		}
		bool nomatch = false;
		int score = 1024;
		int sum = 0;
		vector* params = operator_ov->parameter_list;
		for(int j=0; j<params->length; j++) {
			parameter* param = vector_at(params, j);
			generic_type* arg = vector_at(args, j);
			int dist = generic_type_distance(param->gtype, arg);
			if(dist == -1) {
				nomatch = true;
				break;
			}
			sum += dist;
		}
		if(nomatch) {
			continue;
		}
		if(sum < score) {
			score = sum;
			(*outIndex) = i;
			ret = operator_ov;
		}
	}
	return ret;
}

operator_overload* class_get_operator_overload(class_* self, int index) {
	return vector_at(self->operator_overload_list, index);
}

bool class_contains_method_tree(class_* self, method* m) {
	assert(self != NULL);
	assert(m != NULL);
	class_* ptr = self;
	bool ret = false;
	do {
		if(class_contains_method(ptr->method_list, m)) {
			ret = true;
			break;
		}
		//親クラスへ
		if(ptr->super_class != NULL) {
			ptr = ptr->super_class->core_type->u.class_;
		} else {
			ptr = NULL;
		}
	} while(ptr != NULL);
	return ret;
}

bool class_contains_method(vector* method_list, method* m) {
	assert(!modifier_is_static(m->modifier));
	bool ret = false;
	for(int i=0; i<method_list->length; i++) {
		method* mE = vector_at(method_list, i);
		if(method_override(m, mE)) {
			ret = true;
			break;
		}
	}
	return ret;
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
	//text_printf("unlink %s\n", self->name);
	numeric_map_delete(self->native_method_ref_nmap, class_native_method_ref_delete);
	vector_delete(self->impl_list, class_impl_delete);
	vector_delete(self->field_list, class_field_delete);
	vector_delete(self->sfield_list, class_field_delete);
	vector_delete(self->method_list, class_method_delete);
	vector_delete(self->smethod_list, class_method_delete);
	vector_delete(self->constructor_list, class_ctor_delete);
	vector_delete(self->operator_overload_list, class_delete_operator_overload);
	vtable_delete(self->vt);
	vector_delete(self->vt_vec, class_vtable_vec_delete);
}

void class_delete(class_ * self) {
//	assert(self->ref_count == 0);
//	MEM_FREE(self->name);
	//text_printf("delete %s\n", self->name);
	vector_delete(self->type_parameter_list, class_type_parameter_delete);
	MEM_FREE(self);
}

vector* class_generic_type_list_to_class_list(vector* list) {
	vector* ret = vector_new();
	for(int i=0; i<list->length; i++) {
		generic_type* gE = (generic_type*)vector_at(list, i);
		vector_push(ret, TYPE2CLASS(gE->core_type));
	}
	return ret;
}

vector* class_generic_type_list_to_interface_list(vector* list) {
	vector* ret = vector_new();
	for(int i=0; i<list->length; i++) {
		generic_type* gE = (generic_type*)vector_at(list, i);
		vector_push(ret, TYPE2INTERFACE(gE->core_type));
	}
	return ret;
}

bool class_interface_implement_valid(class_* cls, method** out) {
	(*out) = NULL;
	if(cls->impl_list->length == 0 || cls->is_abstract) {
		return true;
	}
	bool contains = true;
	//全ての実装インターフェイスを取得する
	vector* inter_list = class_generic_type_list_to_interface_list(cls->impl_list);
	vector* methods = interface_method_flatten_list(inter_list);
	for(int i=0; i<methods->length; i++) {
		method* m = vector_at(methods, i);
		if(!class_contains_method_tree(cls, m)) {
			(*out) = m;
			contains = false;
			break;
		}
	}
	vector_delete(inter_list, vector_deleter_null);
	vector_delete(methods, vector_deleter_null);
	return contains;
}

bool class_abstract_class_implement_valid(class_* cls, method** out) {
	(*out) = NULL;
	//これ自体が抽象クラス
	if(cls->is_abstract) {
		return true;
	}
	//Objectクラス
	generic_type* gsuper = cls->super_class;
	if(gsuper == NULL) {
		return true;
	}
	class_* csuper = TYPE2CLASS(GENERIC2TYPE(gsuper));
	//親が具象クラスならtrue
	if(!csuper->is_abstract) {
		return true;
	}
	bool ret = true;
	for(int i=0; i<csuper->method_list->length; i++) {
		method* me = vector_at(csuper->method_list, i);
		if(((me->modifier & modifier_abstract) > 0) &&
		   !class_contains_method(cls->method_list, me)) {
			   (*out) = me;
			   ret = false;
			   break;
		}
	}
	return ret;
}

bool class_field_valid(class_* cls, field** out) {
	return class_field_validImpl(cls->field_list, out) &&
		   class_field_validImpl(cls->sfield_list, out);
}

//private
static void class_create_vtable_top(class_* self) {
	for (int i = 0; i < self->method_list->length; i++) {
		method* m = (method*)vector_at(self->method_list, i);
		if(m->access != access_private &&
		   !modifier_is_static(m->modifier)) {
			vtable_add(self->vt, m);
		}
	}
}

static void class_create_vtable_override(class_* self) {
	class_create_vtable(self->super_class->core_type->u.class_);
	vtable_copy(self->super_class->core_type->u.class_->vt, self->vt);
	for (int i = 0; i < self->method_list->length; i++) {
		method* m = (method*)vector_at(self->method_list, i);
		if(m->access != access_private &&
		   !modifier_is_static(m->modifier)) {
			vtable_replace(self->vt, m);
		}
	}
}

static void class_create_vtable_interface(class_* self) {
	//もしインターフェースを実装しているなら、
	//インターフェースに対応する同じ並びのメソッドテーブルも作る
	for (int i = 0; i < self->impl_list->length; i++) {
		generic_type* gtp = (generic_type*)vector_at(self->impl_list, i);
		interface_* inter = (interface_*)gtp->core_type->u.interface_;
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
			assert(classVTM != NULL);
			vtable_add(newVT, classVTM);
		}
		vector_push(self->vt_vec, newVT);
	}
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
	method* ret = NULL;
	vtable* clVT = self->vt;
	for (int i = 0; i < clVT->elements->length; i++) {
		method* clM = vector_at(clVT->elements, i);
		if (method_override(virtualMethod, clM)) {
			ret = clM;
			break;
		}
	}
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


static bool class_field_validImpl(vector* field_vec, field** out) {
	(*out) = NULL;
	bool ret = true;
	for(int i=0; i<field_vec->length; i++) {
		field* f = (field*)vector_at(field_vec, i);
		for(int j=0; j<field_vec->length; j++) {
			field* fE = (field*)vector_at(field_vec, j);
			if(f == fE) { continue; }
			if(f->namev == fE->namev) {
				ret = false;
				(*out) = fE;
				break;
			}
		}
	}
	return ret;
}

static void class_delete_operator_overload(vector_item item) {
	operator_overload* e = (operator_overload*)item;
	operator_overload_delete(e);
}