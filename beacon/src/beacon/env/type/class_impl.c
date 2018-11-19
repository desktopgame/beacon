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
static void create_vtable_top(bc_Class* self);
static void create_vtable_override(bc_Class* self);
static void create_vtable_interface(bc_Class* self);
static void class_impl_delete(VectorItem item);
static void delete_field(VectorItem item);
static void delete_method(VectorItem item);
static void class_ctor_delete(VectorItem item);
static void delete_native_method_ref(NumericMapKey key, NumericMapItem item);
static bc_Method* class_find_impl_method(bc_Class* self, bc_Method* virtualMethod);
static void delete_vtable(VectorItem item);
static void delete_type_parameter(VectorItem item);
static void delete_generic_type(VectorItem item);
static void delete_operator_overload(VectorItem item);
static void delete_property(VectorItem item);

bc_Type* bc_WrapClass(bc_Class* self) {
	bc_Type* ret = bc_NewType();
	ret->Tag = TYPE_CLASS_T;
	ret->Kind.Class = self;
	self->Parent = ret;
	return ret;
}

bc_Class* bc_NewClass(StringView namev) {
	bc_Class* ret = (bc_Class*)MEM_MALLOC(sizeof(bc_Class));
	ret->Name = namev;
	ret->Parent = NULL;
	ret->Location = NULL;
	ret->RefCount = 0;
	ret->SuperClass = NULL;
	ret->Implements = NewVector();
	ret->Fields = NewVector();
	ret->StaticFields = NewVector();
	ret->Properties = NewVector();
	ret->StaticProperties = NewVector();
	ret->Methods = NewVector();
	ret->StaticMethods = NewVector();
	ret->Constructors = NewVector();
	ret->NativeMethodRefMap = NewNumericMap();
	ret->VTTable = NewVector();
	ret->TypeParameters = NewVector();
	ret->VT = NULL;
	ret->OVT = NULL;
	ret->IsAbstract = false;
	ret->OperatorOverloads = NewVector();
	return ret;
}

bc_Class* bc_NewClassProxy(bc_GenericType* gt, StringView namev) {
	assert(gt->CoreType->Tag == TYPE_INTERFACE_T);
	bc_Class* ret = bc_NewClass(namev);
	ret->SuperClass = BC_GENERIC_OBJECT;
	PushVector(ret->Implements, gt);
	return ret;
}

bc_Type* bc_NewPreloadClass(StringView namev) {
	bc_Class* cl = bc_NewClass(namev);
	bc_Type* tp = bc_WrapClass(cl);
	tp->State = TYPE_PENDING;
	if (BC_TYPE_OBJECT == NULL) {
		return tp;
	}
	bc_Class* objCls = BC_TYPE_OBJECT->Kind.Class;
	if (cl != objCls) {
		bc_InitGenericSelf(objCls->Parent, 0);
		cl->SuperClass = objCls->Parent->GenericSelf;
	}
	return tp;
}

void bc_AllocFieldsClass(bc_Class* self, bc_Object * o, Frame* fr) {
	//assert(o->Tag == OBJECT_REF_T);
	bc_Heap* he = bc_GetHeap();
	for (int i = 0; i < self->Fields->Length; i++) {
		bc_Field* f = (bc_Field*)AtVector(self->Fields, i);
		bc_Object* a = bc_GetDefaultObject(f->GType);
		//静的フィールドは別の場所に確保
		if (bc_IsStaticModifier(f->Modifier)) {
			continue;
		}
		he->CollectBlocking++;
		if(f->InitialValue != NULL) {
			Frame* sub = SubFrame(fr);
			for(int i=0; i<fr->TypeArgs->Length; i++) {
				PushVector(sub->TypeArgs, AtVector(fr->TypeArgs, i));
			}
			sub->Receiver = self->Parent;
			CopyVector(fr->VariableTable, sub->VariableTable);
			ExecuteVM(sub, f->InitialValueEnv);
			a = PopVector(sub->ValueStack);
			DeleteFrame(sub);
		}
		PushVector(o->Fields, a);
		he->CollectBlocking--;
	}
}

void bc_FreeClassFields(bc_Class* self, bc_Object * o) {
}

void bc_AddFieldClass(bc_Class* self, bc_Field* f) {
	assert(f != NULL);
	if (bc_IsStaticModifier(f->Modifier)) {
		PushVector(self->StaticFields, f);
	} else {
		PushVector(self->Fields, f);
	}
}

void bc_AddPropertyClass(bc_Class* self, bc_Property* p) {
	if (bc_IsStaticModifier(p->Modifier)) {
		PushVector(self->StaticProperties, p);
	} else {
		PushVector(self->Properties, p);
	}
	//プロパティが単純な省略形として記述されているなら、
	//それはフィールドと同じなのでフィールドも定義する
	#if defined(DEBUG)
	const char* name = Ref2Str(p->Name);
	#endif
	if(p->IsShort) {
		bc_Field* f = bc_NewField(ConcatIntern("$propery.", p->Name));
		f->Access = ACCESS_PRIVATE_T;
		f->GType = p->GType;
		f->Modifier = p->Modifier;
		f->Parent = self->Parent;
		f->StaticValue = bc_GetNullObject();
		p->SourceRef = f;
		bc_AddFieldClass(self, f);
	}
}

void bc_AddMethodClass(bc_Class* self, bc_Method * m) {
	assert(m != NULL);
	if (bc_IsStaticModifier(m->Modifier)) {
		PushVector(self->StaticMethods, m);
	} else {
		PushVector(self->Methods, m);
	}
}

void bc_AddConstructorClass(bc_Class* self, bc_Constructor* c) {
	PushVector(self->Constructors, c);
}

void bc_DefineNativeMethodClass(bc_Class* self, const char* name, bc_NativeImpl impl) {
	bc_DefineNativeMethodByRefClass(self, InternString(name), impl);
}

void bc_DefineNativeMethodByRefClass(bc_Class* self, StringView namev, bc_NativeImpl impl) {
	bc_NativeMethodRef* ref = bc_NewNativeMethodRef(impl);
	PutNumericMap(self->NativeMethodRefMap, namev, ref);
}

int bc_DistanceClass(bc_Class* super, bc_Class* sub) {
	if (super == sub) {
		return 0;
	}
	int depth = 0;
	bc_Class* pointee = sub;
	do {
		if (pointee == super) {
			return depth;
		}
		bc_GenericType* super_gtype = pointee->SuperClass;
		if(super_gtype == NULL) {
			depth = -1;
			break;
		}
		pointee = super_gtype->CoreType->Kind.Class;
		depth++;
		if (pointee == NULL) {
			depth = -1;
			break;
		}
	} while (1);
	return depth;
}

void bc_CreateVTableClass(bc_Class* self) {
	//TEST(!strcmp(self->name, "Int"));
	#if defined(DEBUG)
	const char* str = Ref2Str(self->Name);
	#endif
	assert(self != NULL);
	//初期化済み
	if (self->VT != NULL) {
		return;
	}
	self->VT = bc_NewVTable();
	//トップレベルではメソッドの一覧を配列に入れるだけ
	if (self->SuperClass == NULL) {
		create_vtable_top(self);
	//あるクラスを継承する場合には、
	//重複するメソッドを上書きするように
	} else {
		create_vtable_override(self);
	}
	create_vtable_interface(self);
	assert(self->VT->Elements->Length != 0);
}

void bc_CreateOperatorVTClass(bc_Class* self) {
	if(self->OVT != NULL) {
		return;
	}
	if(self->SuperClass != NULL) {
		bc_CreateOperatorVTClass(BC_TYPE2CLASS(bc_GENERIC2TYPE(self->SuperClass)));
	}
	self->OVT = bc_NewOperatorVt();
	if(self->SuperClass == NULL) {
		for(int i=0; i<self->OperatorOverloads->Length; i++) {
			bc_OperatorOverload* opov = AtVector(self->OperatorOverloads, i);
			PushVector(self->OVT->Operators, opov);
		}
	} else {
		bc_OperatorVT* super_vt = BC_TYPE2CLASS(bc_GENERIC2TYPE(self->SuperClass))->OVT;
		for(int i=0; i<super_vt->Operators->Length; i++) {
			bc_OperatorOverload* opov = AtVector(super_vt->Operators, i);
			PushVector(self->OVT->Operators, opov);
		}
		for(int i=0; i<self->OperatorOverloads->Length; i++) {
			bc_OperatorOverload* opov = AtVector(self->OperatorOverloads, i);
			bc_ReplaceOperatorVt(self->OVT, opov);
		}
	}
}

int bc_CountAllFieldClass(bc_Class* self) {
	bc_Class* pt = self;
	int sum = 0;
	do {
		sum += (pt->Fields->Length);
		if(pt->SuperClass == NULL) {
			break;
		}
		pt = pt->SuperClass->CoreType->Kind.Class;
	} while (pt != NULL);
	return sum;
}

int bc_CountAllSFieldClass(bc_Class* self) {
	bc_Class* pt = self;
	int sum = 0;
	do {
		sum += (pt->StaticFields->Length);
		if(pt->SuperClass == NULL) {
			break;
		}
		pt = pt->SuperClass->CoreType->Kind.Class;
	} while (pt != NULL);
	return sum;
}

int bc_CountAllPropertyClass(bc_Class* self) {
	bc_Class* pt = self;
	int sum = 0;
	do {
		sum += (pt->Properties->Length);
		if(pt->SuperClass == NULL) {
			break;
		}
		pt = pt->SuperClass->CoreType->Kind.Class;
	} while (pt != NULL);
	return sum;
}

int bc_CountAllSPropertyClass(bc_Class* self) {
	bc_Class* pt = self;
	int sum = 0;
	do {
		sum += (pt->StaticProperties->Length);
		if(pt->SuperClass == NULL) {
			break;
		}
		pt = pt->SuperClass->CoreType->Kind.Class;
	} while (pt != NULL);
	return sum;
}

int bc_CountAllMethodClass(bc_Class* self) {
	bc_Class* pt = self;
	int sum = 0;
	do {
		sum += (pt->Methods->Length);
		if(pt->SuperClass == NULL) {
			break;
		}
		pt = pt->SuperClass->CoreType->Kind.Class;
	} while (pt != NULL);
	return sum;
}

int bc_CountAllSMethodClass(bc_Class* self) {
	bc_Class* pt = self;
	int sum = 0;
	do {
		sum += (pt->StaticMethods->Length);
		if(pt->SuperClass == NULL) {
			break;
		}
		pt = pt->SuperClass->CoreType->Kind.Class;
	} while (pt != NULL);
	return sum;
}

bc_Object * bc_NewInstanceClass(bc_Class* self, Frame* fr, Vector* args, Vector* type_args) {
	//コンストラクタを検索
	int temp = 0;
	bc_Constructor* ctor = bc_RFindConstructorClass(self, args, NULL, fr, &temp);
	assert(temp != -1);
	//コンストラクタを実行
	Frame* sub = SubFrame(fr);
	bc_Heap* h = bc_GetHeap();
	if(args != NULL) {
		for (int i = args->Length-1; i>=0; i--) {
			bc_Object* o = AtVector(args, i);
			PushVector(sub->ValueStack, o);
		}
	}
	if(type_args != NULL) {
		for(int i = 0; i<type_args->Length; i++) {
			PushVector(sub->TypeArgs, AtVector(type_args, i));
		}
	}
	ExecuteVM(sub, ctor->Env);
	bc_Object* inst = PopVector(sub->ValueStack);
	h->CollectBlocking++;
	DeleteFrame(sub);
	h->CollectBlocking--;
	return inst;
}

void bc_LinkAllClass(bc_Class* self) {
	for (int i = 0; i < self->Fields->Length; i++) {
		bc_Field* f = (bc_Field*)AtVector(self->Fields, i);
		f->Parent = self->Parent;
	}
	for (int i = 0; i < self->Methods->Length; i++) {
		bc_Method* m = (bc_Method*)AtVector(self->Methods, i);
		m->Parent = self->Parent;
	}
	for (int i = 0; i < self->Constructors->Length; i++) {
		bc_Constructor* ctor = (bc_Constructor*)AtVector(self->Constructors, i);
		ctor->Parent = self->Parent;
	}
}

void bc_UnlinkClass(bc_Class* self) {
	if (self->SuperClass != NULL) {
		self->SuperClass->CoreType->Kind.Class->RefCount--;
	}
	//XSTREQ(self->name, "Object");
	//generic_DeleteType(self->SuperClass);
	DeleteNumericMap(self->NativeMethodRefMap, delete_native_method_ref);
	DeleteVector(self->Implements, class_impl_delete);
	DeleteVector(self->Fields, delete_field);
	DeleteVector(self->StaticFields, delete_field);
	DeleteVector(self->Methods, delete_method);
	DeleteVector(self->StaticMethods, delete_method);
	DeleteVector(self->Constructors, class_ctor_delete);
	DeleteVector(self->OperatorOverloads, delete_operator_overload);
	DeleteVector(self->Properties, delete_property);
	DeleteVector(self->StaticProperties, delete_property);
	bc_DeleteVTable(self->VT);
	bc_DeleteOperatorVt(self->OVT);
	DeleteVector(self->VTTable, delete_vtable);
}

void bc_DeleteClass(bc_Class* self) {
//	printf("unlink %s\n", Ref2Str(self->Name));
//	assert(self->RefCount == 0);
//	MEM_FREE(self->name);
	//printf("delete %s\n", self->name);
	DeleteVector(self->TypeParameters, delete_type_parameter);
	MEM_FREE(self);
}

//private
static void create_vtable_top(bc_Class* self) {
	for (int i = 0; i < self->Methods->Length; i++) {
		bc_Method* m = (bc_Method*)AtVector(self->Methods, i);
		if(m->Access != ACCESS_PRIVATE_T &&
		   !bc_IsStaticModifier(m->Modifier)) {
			bc_AddVTable(self->VT, m);
		}
	}
}

static void create_vtable_override(bc_Class* self) {
	#if defined(DEBUG)
	const char* clname = Ref2Str(self->Name);
	#endif
	CallContext* cctx = NewCallContext(CALL_DECL_T);
	cctx->Scope = self->Parent->Location;
	cctx->Ty = self->SuperClass->CoreType;
	bc_CreateVTableClass(self->SuperClass->CoreType->Kind.Class);
	bc_CopyVTable(self->SuperClass->CoreType->Kind.Class->VT, self->VT);
	for (int i = 0; i < self->Methods->Length; i++) {
		bc_Method* m = (bc_Method*)AtVector(self->Methods, i);
		if(m->Access != ACCESS_PRIVATE_T &&
		   !bc_IsStaticModifier(m->Modifier)) {
			bc_ReplaceVTable(self->VT, m, cctx);
		}
	}
	DeleteCallContext(cctx);
}

static void create_vtable_interface(bc_Class* self) {
	#if defined(DEBUG)
	const char* clname = Ref2Str(bc_GetTypeName(self->Parent));
	#endif
	Vector* tbl = bc_GetInterfaceTreeClass(self);
	//もしインターフェースを実装しているなら、
	//インターフェースに対応する同じ並びのメソッドテーブルも作る
	for (int i = 0; i < tbl->Length; i++) {
		//GenericType* gtp = (GenericType*)AtVector(tbl, i);
		bc_Interface* inter = (bc_Interface*)AtVector(tbl, i);
		bc_VTable* interVT = inter->VT;
		bc_VTable* newVT = bc_NewVTable();
		assert(interVT != NULL);
		//そのインターフェースに定義されたテーブルの一覧
		//これはスーパーインターフェースも含む。
		for (int j = 0; j < interVT->Elements->Length; j++) {
			//実装クラスの中の、
			//シグネチャが同じメソッドをテーブルへ。
			bc_Method* interVTM = AtVector(interVT->Elements, j);
			bc_Method* classVTM = class_find_impl_method(self, interVTM);
			if(!self->IsAbstract && classVTM == NULL) {
				PushVector(self->VTTable, newVT);
				bc_Panic(BCERROR_NOT_IMPLEMENT_INTERFACE_T,
					Ref2Str(bc_GetTypeName(interVTM->Parent)),
					Ref2Str(interVTM->Name)
				);
				DeleteVector(tbl, VectorDeleterOfNull);
				return;
			}
			//assert(self->IsAbstract || classVTM != NULL);
			//例えば抽象クラスがインターフェイスを実装していない場合
			//空っぽの実装を持たせる
			if(self->IsAbstract && classVTM == NULL) {
				classVTM = interVTM;
			}
			bc_AddVTable(newVT, classVTM);
		}
		PushVector(self->VTTable, newVT);
	}
	DeleteVector(tbl, VectorDeleterOfNull);
}

static void class_impl_delete(VectorItem item) {
	bc_GenericType* e = (bc_GenericType*)item;
	//generic_DeleteType(e);
}

static void delete_field(VectorItem item) {
	bc_Field* e = (bc_Field*)item;
	bc_DeleteField(e);
}

static void delete_method(VectorItem item) {
	bc_Method* e = (bc_Method*)item;
	bc_DeleteMethod(e);
}

static void class_ctor_delete(VectorItem item) {
	bc_Constructor* e = (bc_Constructor*)item;
	bc_DeleteConstructor(e);
}

static void delete_native_method_ref(NumericMapKey key, NumericMapItem item) {
	bc_NativeMethodRef* e = (bc_NativeMethodRef*)item;
	bc_DeleteNativeMethodRef(e);
}

static bc_Method* class_find_impl_method(bc_Class* self, bc_Method* virtualMethod) {
	CallContext* cctx = NewCallContext(CALL_DECL_T);
	cctx->Scope = self->Parent->Location;
	cctx->Ty = self->Parent;
	bc_Method* ret = NULL;
	bc_VTable* clVT = self->VT;
	for (int i = 0; i < clVT->Elements->Length; i++) {
		bc_Method* clM = AtVector(clVT->Elements, i);
		if (bc_IsOverridedMethod(virtualMethod, clM, cctx)) {
			ret = clM;
			break;
		}
	}
	DeleteCallContext(cctx);
	return ret;
}

static void delete_vtable(VectorItem item) {
	bc_VTable* e = (bc_VTable*)item;
	bc_DeleteVTable(e);
}

static void delete_type_parameter(VectorItem item) {
	bc_TypeParameter* e = (bc_TypeParameter*)item;
	bc_DeleteTypeParameter(e);
}

static void delete_generic_type(VectorItem item) {
	bc_GenericType* e = (bc_GenericType*)item;
//	generic_DeleteType(e);
}

static void delete_operator_overload(VectorItem item) {
	bc_OperatorOverload* e = (bc_OperatorOverload*)item;
	bc_DeleteOperatorOverload(e);
}

static void delete_property(VectorItem item) {
	bc_Property* e = (bc_Property*)item;
	bc_DeleteProperty(e);
}