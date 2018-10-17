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
#include "../TYPE_IMPL.h"
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
static void CreateVTableClass_top(class_* self);
static void CreateVTableClass_override(class_* self);
static void CreateVTableClass_interface(class_* self);
static void class_impl_delete(VectorItem item);
static void class_DeleteField(VectorItem item);
static void class_DeleteMethod(VectorItem item);
static void class_ctor_delete(VectorItem item);
static void class_DeleteNativeMethodRef(NumericMapKey key, NumericMapItem item);
static method* class_find_impl_method(class_* self, method* virtualMethod);
static void class_vtable_vec_delete(VectorItem item);
static void class_DeleteTypeParameter(VectorItem item);
static void class_generic_type_list_delete(VectorItem item);
static void DeleteClass_operator_overload(VectorItem item);
static void DeleteClass_property(VectorItem item);

type * WrapClass(class_ * self) {
	type* ret = NewType();
	ret->tag = TYPE_CLASS_T;
	ret->u.class_ = self;
	self->parent = ret;
	return ret;
}

class_ * NewClass(StringView namev) {
	class_* ret = (class_*)MEM_MALLOC(sizeof(class_));
	ret->namev = namev;
	ret->parent = NULL;
	ret->location = NULL;
	ret->ref_count = 0;
	ret->super_class = NULL;
	ret->impl_list = NewVector();
	ret->field_list = NewVector();
	ret->sfield_list = NewVector();
	ret->prop_list = NewVector();
	ret->sprop_list = NewVector();
	ret->method_list = NewVector();
	ret->smethod_list = NewVector();
	ret->constructor_list = NewVector();
	ret->native_method_ref_nmap = NewNumericMap();
	ret->vt_vec = NewVector();
	ret->GetParameterListType = NewVector();
	ret->vt = NULL;
	ret->ovt = NULL;
	ret->is_abstract = false;
	ret->operator_overload_list = NewVector();
	return ret;
}

class_* NewClassProxy(generic_type* gt, StringView namev) {
	assert(gt->core_type->tag == TYPE_INTERFACE_T);
	class_* ret = NewClass(namev);
	ret->super_class = GENERIC_OBJECT;
	PushVector(ret->impl_list, gt);
	return ret;
}

type* NewPreloadClass(StringView namev) {
	class_* cl = NewClass(namev);
	type* tp = WrapClass(cl);
	tp->state = TYPE_PENDING;
	if (TYPE_OBJECT == NULL) {
		return tp;
	}
	class_* objCls = TYPE_OBJECT->u.class_;
	if (cl != objCls) {
		InitGenericSelf(objCls->parent, 0);
		cl->super_class = objCls->parent->generic_self;
	}
	return tp;
}

void AllocFieldsClass(class_ * self, object * o, frame* fr) {
	assert(o->tag == OBJECT_REF_T);
	heap* he = GetHeap();
	for (int i = 0; i < self->field_list->length; i++) {
		field* f = (field*)AtVector(self->field_list, i);
		object* a = GetDefaultObject(f->gtype);
		//静的フィールドは別の場所に確保
		if (IsStaticModifier(f->modifier)) {
			continue;
		}
		he->collect_blocking++;
		if(f->initial_value != NULL) {
			frame* sub = SubFrame(fr);
			for(int i=0; i<fr->type_args_vec->length; i++) {
				PushVector(sub->type_args_vec, AtVector(fr->type_args_vec, i));
			}
			sub->receiver = self->parent;
			CopyVector(fr->ref_stack, sub->ref_stack);
			ExecuteVM(sub, f->initial_value_env);
			a = PopVector(sub->value_stack);
			DeleteFrame(sub);
		}
		PushVector(o->u.field_vec, a);
		he->collect_blocking--;
	}
}

void FreeClassFields(class_ * self, object * o) {
}

void AddFieldClass(class_ * self, field * f) {
	assert(f != NULL);
	if (IsStaticModifier(f->modifier)) {
		PushVector(self->sfield_list, f);
	} else {
		PushVector(self->field_list, f);
	}
}

void AddPropertyClass(class_* self, property* p) {
	if (IsStaticModifier(p->modifier)) {
		PushVector(self->sprop_list, p);
	} else {
		PushVector(self->prop_list, p);
	}
	//プロパティが単純な省略形として記述されているなら、
	//それはフィールドと同じなのでフィールドも定義する
	#if defined(DEBUG)
	const char* name = Ref2Str(p->namev);
	#endif
	if(p->is_short) {
		field* f = NewField(ConcatIntern("$propery.", p->namev));
		f->access = ACCESS_PRIVATE_T;
		f->gtype = p->gtype;
		f->modifier = p->modifier;
		f->parent = self->parent;
		f->static_value = GetNullObject();
		p->source_ref = f;
		AddFieldClass(self, f);
	}
}

void AddMethodClass(class_ * self, method * m) {
	assert(m != NULL);
	if (IsStaticModifier(m->modifier)) {
		PushVector(self->smethod_list, m);
	} else {
		PushVector(self->method_list, m);
	}
}

void AddConstructorClass(class_ * self, constructor * c) {
	PushVector(self->constructor_list, c);
}

void DefineNativeMethodClass(class_* self, const char* name, native_impl impl) {
	DefineNativeMethodByRefClass(self, InternString(name), impl);
}

void DefineNativeMethodByRefClass(class_ * self, StringView namev, native_impl impl) {
	native_method_ref* ref = NewNativeMethodRef(impl);
	PutNumericMap(self->native_method_ref_nmap, namev, ref);
}

int DistanceClass(class_ * super, class_ * sub) {
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

void CreateVTableClass(class_ * self) {
	//TEST(!strcmp(self->name, "Int"));
	#if defined(DEBUG)
	const char* str = Ref2Str(self->namev);
	#endif
	assert(self != NULL);
	//初期化済み
	if (self->vt != NULL) {
		return;
	}
	self->vt = NewVTable();
	//トップレベルではメソッドの一覧を配列に入れるだけ
	if (self->super_class == NULL) {
		CreateVTableClass_top(self);
	//あるクラスを継承する場合には、
	//重複するメソッドを上書きするように
	} else {
		CreateVTableClass_override(self);
	}
	CreateVTableClass_interface(self);
	assert(self->vt->elements->length != 0);
}

void CreateOperatorVTClass(class_* self) {
	if(self->ovt != NULL) {
		return;
	}
	if(self->super_class != NULL) {
		CreateOperatorVTClass(TYPE2CLASS(GENERIC2TYPE(self->super_class)));
	}
	self->ovt = NewOperatorVt();
	if(self->super_class == NULL) {
		for(int i=0; i<self->operator_overload_list->length; i++) {
			operator_overload* opov = AtVector(self->operator_overload_list, i);
			PushVector(self->ovt->vec, opov);
		}
	} else {
		operator_vt* super_vt = TYPE2CLASS(GENERIC2TYPE(self->super_class))->ovt;
		for(int i=0; i<super_vt->vec->length; i++) {
			operator_overload* opov = AtVector(super_vt->vec, i);
			PushVector(self->ovt->vec, opov);
		}
		for(int i=0; i<self->operator_overload_list->length; i++) {
			operator_overload* opov = AtVector(self->operator_overload_list, i);
			ReplaceOperatorVt(self->ovt, opov);
		}
	}
}

int CountAllFieldClass(class_ * self) {
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

int CountAllSFieldClass(class_ * self) {
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

int CountAllPropertyClass(class_* self) {
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

int CountAllSPropertyClass(class_* self) {
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

int CountAllMethodClass(class_ * self) {
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

int CountAllSMethodClass(class_ * self) {
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

object * NewInstanceClass(class_* self, frame* fr, Vector* args, Vector* type_args) {
	//コンストラクタを検索
	int temp = 0;
	constructor* ctor = RFindConstructorClass(self, args, NULL, fr, &temp);
	assert(temp != -1);
	//コンストラクタを実行
	frame* sub = SubFrame(fr);
	heap* h = GetHeap();
	if(args != NULL) {
		for (int i = args->length-1; i>=0; i--) {
			object* o = AtVector(args, i);
			PushVector(sub->value_stack, o);
		}
	}
	if(type_args != NULL) {
		for(int i = 0; i<type_args->length; i++) {
			PushVector(sub->type_args_vec, AtVector(type_args, i));
		}
	}
	ExecuteVM(sub, ctor->env);
	object* inst = PopVector(sub->value_stack);
	h->collect_blocking++;
	DeleteFrame(sub);
	h->collect_blocking--;
	return inst;
}

void LinkAllClass(class_ * self) {
	for (int i = 0; i < self->field_list->length; i++) {
		field* f = (field*)AtVector(self->field_list, i);
		f->parent = self->parent;
	}
	for (int i = 0; i < self->method_list->length; i++) {
		method* m = (method*)AtVector(self->method_list, i);
		m->parent = self->parent;
	}
	for (int i = 0; i < self->constructor_list->length; i++) {
		constructor* ctor = (constructor*)AtVector(self->constructor_list, i);
		ctor->parent = self->parent;
	}
}

void UnlinkClass(class_ * self) {
	if (self->super_class != NULL) {
		self->super_class->core_type->u.class_->ref_count--;
	}
	//XSTREQ(self->name, "Object");
	//generic_DeleteType(self->super_class);
	DeleteNumericMap(self->native_method_ref_nmap, class_DeleteNativeMethodRef);
	DeleteVector(self->impl_list, class_impl_delete);
	DeleteVector(self->field_list, class_DeleteField);
	DeleteVector(self->sfield_list, class_DeleteField);
	DeleteVector(self->method_list, class_DeleteMethod);
	DeleteVector(self->smethod_list, class_DeleteMethod);
	DeleteVector(self->constructor_list, class_ctor_delete);
	DeleteVector(self->operator_overload_list, DeleteClass_operator_overload);
	DeleteVector(self->prop_list, DeleteClass_property);
	DeleteVector(self->sprop_list, DeleteClass_property);
	DeleteVTable(self->vt);
	DeleteOperatorVt(self->ovt);
	DeleteVector(self->vt_vec, class_vtable_vec_delete);
}

void DeleteClass(class_ * self) {
//	printf("unlink %s\n", Ref2Str(self->namev));
//	assert(self->ref_count == 0);
//	MEM_FREE(self->name);
	//printf("delete %s\n", self->name);
	DeleteVector(self->GetParameterListType, class_DeleteTypeParameter);
	MEM_FREE(self);
}

//private
static void CreateVTableClass_top(class_* self) {
	for (int i = 0; i < self->method_list->length; i++) {
		method* m = (method*)AtVector(self->method_list, i);
		if(m->access != ACCESS_PRIVATE_T &&
		   !IsStaticModifier(m->modifier)) {
			AddVTable(self->vt, m);
		}
	}
}

static void CreateVTableClass_override(class_* self) {
	#if defined(DEBUG)
	const char* clname = Ref2Str(self->namev);
	#endif
	call_context* cctx = NewCallContext(CALL_DECL_T);
	cctx->scope = self->parent->location;
	cctx->ty = self->super_class->core_type;
	CreateVTableClass(self->super_class->core_type->u.class_);
	CopyVTable(self->super_class->core_type->u.class_->vt, self->vt);
	for (int i = 0; i < self->method_list->length; i++) {
		method* m = (method*)AtVector(self->method_list, i);
		if(m->access != ACCESS_PRIVATE_T &&
		   !IsStaticModifier(m->modifier)) {
			ReplaceVTable(self->vt, m, cctx);
		}
	}
	DeleteCallContext(cctx);
}

static void CreateVTableClass_interface(class_* self) {
	#if defined(DEBUG) || defined(_DEBUG)
	const char* clname = Ref2Str(GetTypeName(self->parent));
	#endif
	Vector* tbl = GetInterfaceTreeClass(self);
	//もしインターフェースを実装しているなら、
	//インターフェースに対応する同じ並びのメソッドテーブルも作る
	for (int i = 0; i < tbl->length; i++) {
		//generic_type* gtp = (generic_type*)AtVector(tbl, i);
		interface_* inter = (interface_*)AtVector(tbl, i);
		vtable* interVT = inter->vt;
		vtable* newVT = NewVTable();
		assert(interVT != NULL);
		//そのインターフェースに定義されたテーブルの一覧
		//これはスーパーインターフェースも含む。
		for (int j = 0; j < interVT->elements->length; j++) {
			//実装クラスの中の、
			//シグネチャが同じメソッドをテーブルへ。
			method* interVTM = AtVector(interVT->elements, j);
			method* classVTM = class_find_impl_method(self, interVTM);
			if(!self->is_abstract && classVTM == NULL) {
				PushVector(self->vt_vec, newVT);
				ThrowBCError(BCERROR_NOT_IMPLEMENT_INTERFACE_T,
					Ref2Str(GetTypeName(interVTM->parent)),
					Ref2Str(interVTM->namev)
				);
				DeleteVector(tbl, VectorDeleterOfNull);
				return;
			}
			//assert(self->is_abstract || classVTM != NULL);
			//例えば抽象クラスがインターフェイスを実装していない場合
			//空っぽの実装を持たせる
			if(self->is_abstract && classVTM == NULL) {
				classVTM = interVTM;
			}
			AddVTable(newVT, classVTM);
		}
		PushVector(self->vt_vec, newVT);
	}
	DeleteVector(tbl, VectorDeleterOfNull);
}

static void class_impl_delete(VectorItem item) {
	generic_type* e = (generic_type*)item;
	//generic_DeleteType(e);
}

static void class_DeleteField(VectorItem item) {
	field* e = (field*)item;
	DeleteField(e);
}

static void class_DeleteMethod(VectorItem item) {
	method* e = (method*)item;
	DeleteMethod(e);
}

static void class_ctor_delete(VectorItem item) {
	constructor* e = (constructor*)item;
	DeleteConstructor(e);
}

static void class_DeleteNativeMethodRef(NumericMapKey key, NumericMapItem item) {
	native_method_ref* e = (native_method_ref*)item;
	DeleteNativeMethodRef(e);
}

static method* class_find_impl_method(class_* self, method* virtualMethod) {
	call_context* cctx = NewCallContext(CALL_DECL_T);
	cctx->scope = self->parent->location;
	cctx->ty = self->parent;
	method* ret = NULL;
	vtable* clVT = self->vt;
	for (int i = 0; i < clVT->elements->length; i++) {
		method* clM = AtVector(clVT->elements, i);
		if (IsOverridedMethod(virtualMethod, clM, cctx)) {
			ret = clM;
			break;
		}
	}
	DeleteCallContext(cctx);
	return ret;
}

static void class_vtable_vec_delete(VectorItem item) {
	vtable* e = (vtable*)item;
	DeleteVTable(e);
}

static void class_DeleteTypeParameter(VectorItem item) {
	type_parameter* e = (type_parameter*)item;
	DeleteTypeParameter(e);
}

static void class_generic_type_list_delete(VectorItem item) {
	generic_type* e = (generic_type*)item;
//	generic_DeleteType(e);
}

static void DeleteClass_operator_overload(VectorItem item) {
	operator_overload* e = (operator_overload*)item;
	DeleteOperatorOverload(e);
}

static void DeleteClass_property(VectorItem item) {
	property* e = (property*)item;
	DeleteProperty(e);
}