#include "class_impl.h"
#include "../../util/text.h"
#include "../../util/logger.h"
#include "../parameter.h"
#include "../../il/il_argument.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../util/mem.h"
#include "../object.h"
#include "../../vm/enviroment.h"
#include "../../util/text.h"
#include "../field.h"
#include "../method.h"
#include "../constructor.h"
#include "../type_impl.h"
#include "../../env/vtable.h"
#include "../../util/logger.h"
#include "meta_impl.h"

//http://jumble-note.blogspot.jp/2012/09/c-vacopy.html
#ifndef va_copy
#    define va_copy(dest, src) ((dest) = (src))
#endif

//private
static method* class_find_method_impl(vector* elements, const char * name, vector * args, enviroment * env, int * outIndex);
static constructor* class_find_constructor_impl(vector* v, vector * args, enviroment* env, int * outIndex);
static constructor* class_find_rconstructor_impl(vector* v,vector * args, int * outIndex);
static void class_field_delete(vector_item item);
static void class_method_delete(vector_item item);
static void class_ctor_delete(vector_item item);

type * type_wrap_class(class_ * self) {
	type* ret = type_new();
	ret->tag = type_class;
	ret->u.class_ = self;
	self->parent = ret;
	return ret;
}

class_ * class_new(const char * name) {
	assert(name != NULL);
	class_* ret = (class_*)MEM_MALLOC(sizeof(class_));
	ret->name = text_strdup(name);
	ret->parent = NULL;
	ret->location = NULL;
	ret->state = class_none;
	ret->ref_count = 0;
	ret->super_class = NULL;
	ret->impl_list = vector_new();
	ret->field_list = vector_new();
	ret->sfield_list = vector_new();
	ret->method_list = vector_new();
	ret->smethod_list = vector_new();
	ret->constructor_list = vector_new();
	ret->native_method_ref_map = tree_map_new();
	//FIXME:ここで持つ必要はない
	ret->classIndex = -1;
	//ret->absoluteIndex = -1;
	ret->vt = NULL;
	return ret;
}

class_ * class_new_preload(const char * name) {
	class_* cl = class_new(name);
	cl->state = class_pending;
	if (CL_OBJECT == NULL) {
		return cl;
	}
	class_* objCls = CL_OBJECT->u.class_;
	if (cl != objCls) {
		cl->super_class = objCls;
	}
	return cl;
}

void class_alloc_fields(class_ * self, object * o) {
	assert(o->tag == object_ref);
	for (int i = 0; i < self->field_list->length; i++) {
		field* f = (field*)vector_at(self->field_list, i);
		object* a = object_ref_new();
		a->type = f->type;
		//静的フィールドは別の場所に確保
		if (modifier_is_static(f->modifier)) {
			continue;
		}
		vector_push(o->u.field_vec, a);
	}
	class_create_vtable(self);
	o->type = self->parent;
	o->vptr = self->vt;
}

void class_free_fields(class_ * self, object * o) {
}

void class_add_field(class_ * self, field * f) {
	if (modifier_is_static(f->modifier)) {
		vector_push(self->sfield_list, f);
	} else {
		vector_push(self->field_list, f);
	}
}

void class_add_method(class_ * self, method * m) {
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
	text_printf("class %s", self->name);
	text_putline();
	//親クラスがあるなら表示
	if (self->super_class != NULL) {
		text_putindent(depth + 1);
		text_printf("super %s", self->super_class->name);
		text_putline();
	}
	//実装インターフェースがあるなら表示
	for (int i = 0; i < self->impl_list->length; i++) {
		interface_* inter = (interface_*)vector_at(self->impl_list, i);
		text_putindent(depth + 1);
		text_printf("impl %s", inter->name);
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

void class_define_native_method(class_ * self, const char * name, native_impl impl) {
	native_method_ref* ref = native_method_ref_new(impl);
	tree_map_put(self->native_method_ref_map, name, ref);
}

field * class_find_field(class_* self, const char * name, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->field_list->length; i++) {
		vector_item e = vector_at(self->field_list, i);
		field* f = (field*)e;
		if (!strcmp(name, f->name)) {
			(*outIndex) = (class_count_fieldall(self) - self->field_list->length) + i;
			return f;
		}
	}
	return NULL;
}

field * class_find_field_tree(class_ * self, const char * name, int * outIndex) {
	class_* pointee = self;
	do {
		field* f = class_find_field(pointee, name, outIndex);
		if (f != NULL) {
			return f;
		}
		pointee = pointee->super_class;
	} while (pointee != NULL);
	return NULL;
}

field * class_find_sfield(class_ * self, const char * name, int * outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->sfield_list->length; i++) {
		vector_item e = vector_at(self->sfield_list, i);
		field* f = (field*)e;
		if (!strcmp(name, f->name)) {
			(*outIndex) = (class_count_sfieldall(self) - self->sfield_list->length) + i;
			return f;
		}
	}
	return NULL;
}

field * class_find_sfield_tree(class_ * self, const char * name, int * outIndex) {
	class_* pointee = self;
	do {
		field* f = class_find_sfield(pointee, name, outIndex);
		if (f != NULL) {
			return f;
		}
		pointee = pointee->super_class;
	} while (pointee != NULL);
	return NULL;
}

field * class_get_field(class_ * self, int index) {
	assert(index >= 0);
	int all = class_count_fieldall(self);
	if (index >= (all - self->field_list->length) &&
		index < all) {
//		return vector_at(self->field_list, all - index);
		return vector_at(self->field_list, self->field_list->length - (all - index));
	}
	return class_get_field(self->super_class, index);
}

field * class_get_sfield(class_ * self, int index) {
	assert(index >= 0);
	int all = class_count_sfieldall(self);
	if (index >= (all - self->sfield_list->length) &&
		index < all) {
//		return vector_at(self->sfield_list, all - index);
		return vector_at(self->sfield_list, self->sfield_list->length - (all - index));
	}
	return class_get_sfield(self->super_class, index);
}

constructor * class_find_rconstructor(class_ * self, vector * args, int* outIndex) {
	vector* v = meta_find_rconstructors(self, args);
	(*outIndex) = -1;
	return class_find_rconstructor_impl(v, args, outIndex);
}

constructor * class_find_constructor(class_ * self, vector * args, enviroment * env, int* outIndex) {
	vector* v = meta_find_constructors(self, args, env);
	(*outIndex) = -1;
	return class_find_constructor_impl(v, args, env, outIndex);
}

constructor * class_find_empty_constructor(class_ * self, enviroment * env, int * outIndex) {
	vector* emptyArgs = vector_new();
	constructor* ret = class_find_constructor(self, emptyArgs, env, outIndex);
	vector_delete(emptyArgs, vector_deleter_null);

	return ret;
}

method * class_find_method(class_ * self, const char * name, vector * args, enviroment * env, int * outIndex) {
	(*outIndex) = -1;
	class_create_vtable(self);
	assert(self->vt->elements->length > 0);
	return class_find_method_impl(self->vt->elements, name, args, env, outIndex);
}

method * class_find_smethod(class_ * self, const char * name, vector * args, enviroment * env, int * outIndex) {
	(*outIndex) = -1;
	class_create_vtable(self);
	int temp = 0;
	method* ret = class_find_method_impl(self->smethod_list, name, args, env, &temp);
	temp += (class_count_smethodall(self) - self->smethod_list->length);
	(*outIndex) = temp;
	return ret;
}

method * class_get_method(object * o, int index) {
	assert(index >= 0);
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
	return class_get_smethod(self->super_class, index);
}

bool class_castable(class_ * self, class_ * other) {
	assert(self != NULL && other != NULL);
	if (self == other) {
		return true;
	}
	class_* pointee = self;
	do {
		if (pointee == other) {
			return true;
		}
		pointee = pointee->super_class;
	} while (pointee != NULL);
	return false;
}

int class_distance(class_ * self, class_ * other) {
	if (self == other) {
		return 0;
	}
	int depth = 0;
	class_* pointee = self;
	do {
		if (pointee == other) {
			return depth;
		}
		pointee = pointee->super_class;
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
		for (int i = 0; i < self->method_list->length; i++) {
			vtable_add(self->vt, vector_at(self->method_list, i));
		}
	//あるクラスを継承する場合には、
	//重複するメソッドを上書きするように
	} else {
		class_create_vtable(self->super_class);
		vtable_copy(self->super_class->vt, self->vt);
		for (int i = 0; i < self->method_list->length; i++) {
			method* m = (method*)vector_at(self->method_list, i);
			vtable_replace(self->vt, m);
		}
	}
	//assert(self->vt->elements->length > 0);
}

int class_count_fieldall(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->field_list->length);
		pt = pt->super_class;
	} while (pt != NULL);
	return sum;
}

int class_count_sfieldall(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->sfield_list->length);
		pt = pt->super_class;
	} while (pt != NULL);
	return sum;
}

int class_count_methodall(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->method_list->length);
		pt = pt->super_class;
	} while (pt != NULL);
	return sum;
}

int class_count_smethodall(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->smethod_list->length);
		pt = pt->super_class;
	} while (pt != NULL);
	return sum;
}

object * class_new_rinstance(class_ * self, vm* vmc, int count, ...) {
	va_list ap;
	va_start(ap, count);
	//可変長引数をベクターへ
	vector* args = vector_new();
	for (int i = 0; i < count; i++) {
		object* o = va_arg(ap, object*);
		vector_push(args, o);
	}
	//コンストラクタを検索
	int temp = 0;
	constructor* ctor = class_find_rconstructor(self, args, &temp);
	assert(temp != -1);
	//コンストラクタを実行
	vm* sub = vm_sub(vmc);
	for (int i = args->length-1; i>=0; i--) {
		object* o = vector_at(args, i);
		vector_push(sub->value_stack, o);
	}
	vm_execute(sub, ctor->env);
	object* inst = vector_pop(sub->value_stack);
	//開放
	vm_delete(sub);
	vector_delete(args, vector_deleter_null);
	va_end(ap);
	return inst;
}

void class_linkall(class_ * self) {
	for (int i = 0; i < self->field_list->length; i++) {
		field* f = (field*)vector_at(self->field_list, i);
		f->parent = self;
	}
	for (int i = 0; i < self->method_list->length; i++) {
		method* m = (method*)vector_at(self->method_list, i);
		m->parent = self;
	}
	for (int i = 0; i < self->constructor_list->length; i++) {
		constructor* ctor = (constructor*)vector_at(self->constructor_list, i);
		ctor->parent = self;
	}
}

void class_delete(class_ * self) {
//	assert(self->ref_count == 0);
//	MEM_FREE(self->name);
	sg_info(__FILE__, __LINE__, "deleted class %s", self->name);
	if (self->super_class != NULL) {
		self->super_class->ref_count--;
	}
	vector_delete(self->impl_list, vector_deleter_null);
	vector_delete(self->field_list, class_field_delete);
	vector_delete(self->sfield_list, class_field_delete);
	vector_delete(self->method_list, class_method_delete);
	vector_delete(self->smethod_list, class_method_delete);
	vector_delete(self->constructor_list, class_ctor_delete);
	tree_map_delete(self->native_method_ref_map, tree_map_deleter_null);
	vtable_delete(self->vt);
	MEM_FREE(self->name);
	MEM_FREE(self);
}

//private
static method* class_find_method_impl(vector* elements, const char * name, vector * args, enviroment * env, int * outIndex) {
	return meta_find_method(elements, name, args, env, outIndex);
}

static constructor* class_find_constructor_impl(vector* v, vector * args, enviroment* env, int * outIndex) {
	//コンストラクタが一つも見つからなかった
	if (v->length == 0) {
		vector_delete(v, vector_deleter_null);
		return NULL;
	}
	//見つかった中からもっとも一致するコンストラクタを選択する
	int min = 1024;
	constructor* ret = NULL;
	for (int i = 0; i < v->length; i++) {
		vector_item e = vector_at(v, i);
		constructor* c = (constructor*)e;
		int score = 0;
		bool illegal = false;
		for (int j = 0; j < c->parameter_list->length; j++) {
			vector_item d = vector_at(args, j);
			vector_item d2 = vector_at(c->parameter_list, j);
			il_argument* p = (il_argument*)d;
			parameter* p2 = (parameter*)d2;
			//NULL以外なら型の互換性を調べる
			int dist = 0;
			type* argType = il_factor_eval(p->factor, env);
			type* parType = p2->type;
			if (argType != CL_NULL) {
				dist = type_distance(argType, parType);
			}
			if (dist == -1) {
				illegal = true;
				break;
			}
			score += dist;
		}
		if (score < min && !illegal) {
			min = score;
			ret = c;
			(*outIndex) = i;
		}
	}
	vector_delete(v, vector_deleter_null);
	return ret;
}

static constructor* class_find_rconstructor_impl(vector* v, vector * args, int * outIndex) {
	//コンストラクタが一つも見つからなかった
	if (v->length == 0) {
		vector_delete(v, vector_deleter_null);
		return NULL;
	}
	//見つかった中からもっとも一致するコンストラクタを選択する
	int min = 1024;
	constructor* ret = NULL;
	for (int i = 0; i < v->length; i++) {
		vector_item e = vector_at(v, i);
		constructor* c = (constructor*)e;
		int score = 0;
		bool illegal = false;
		for (int j = 0; j < c->parameter_list->length; j++) {
			vector_item d = vector_at(args, j);
			vector_item d2 = vector_at(c->parameter_list, j);
			object* p = (object*)d;
			parameter* p2 = (parameter*)d2;
			//NULL以外なら型の互換性を調べる
			int dist = 0;
			type* argType = p->type;
			type* parType = p2->type;
			if (argType != CL_NULL) {
				dist = type_distance(argType, parType);
			}
			if (dist == -1) {
				illegal = true;
				break;
			}
			score += dist;
		}
		if (score < min && !illegal) {
			min = score;
			ret = c;
			(*outIndex) = i;
		}
	}
	vector_delete(v, vector_deleter_null);
	return ret;
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
