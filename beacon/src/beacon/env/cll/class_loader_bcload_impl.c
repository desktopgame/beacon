#include "class_loader_bcload_impl.h"
#include "../script_context.h"
#include "../../util/text.h"
#include "../../util/io.h"
#include "../../parse/parser.h"
#include "../../il/il_TYPE_IMPL.h"
#include "../../il/il_import.h"
#include "../../il/il_parameter.h"
#include "../../il/il_argument.h"
#include "../../il/il_field.h"
#include "../../il/il_method.h"
#include "../../il/il_constructor.h"
#include "../../il/il_stmt_interface.h"
#include "../../il/il_type_parameter.h"
#include "../../il/il_namespace.h"
#include "../../il/il_type_interface.h"
#include "../../il/il_constructor.h"
#include "../../il/il_constructor_chain.h"
#include "../../il/il_method.h"
#include "../type_interface.h"
#include "../TYPE_IMPL.h"
#include "../../env/object.h"
#include "../type_parameter.h"
#include "../parameter.h"
#include "../field.h"
#include "../method.h"
#include "../constructor.h"
#include "class_loader_bcload_import_module_impl.h"
#include "../../util/mem.h"
#include <assert.h>
//
//sgload
//
#include "../type_cache.h"
#include <string.h>
#include "../import_info.h"
#include "../../env/heap.h"
//proto
static void CLBC_Namespacetree(ClassLoader* self);
/**
 * 名前空間の一覧を読み込みます.
 * @param self
 * @param ilNamespacelist
 * @param parent
 */
static void CLBC_Namespacelist(ClassLoader* self, Vector* ilNamespacelist, Namespace* parent);

/**
 * 名前空間と含まれるエントリの一覧を読み込みます.
 * @param self
 * @param ilnamespace
 * @param parent
 */
static void CLBC_namespace(ClassLoader* self, ILNamespace* ilnamespace, Namespace* parent);

/**
 * 型宣言の一覧を読み込みます.
 * @param self
 * @param iltype_list
 * @param parent
 */
static void CLBC_type_list(ClassLoader* self, Vector* iltype_list, Namespace* parent);

/**
 * 列挙宣言を読み込んで名前空間に登録します.
 * @param self
 * @param iltype
 * @param parent
 */
static void CLBC_enum(ClassLoader* self, ILType* iltype, Namespace* parent);

/**
 * クラス宣言を読み込んで名前空間に登録します.
 * @param self
 * @param iltype
 * @param parent
 */
static void CLBC_class(ClassLoader* self, ILType* iltype, Namespace* parent);

/**
 * インターフェース宣言を読み込んで名前空間に登録します.
 * @param self
 * @param iltype
 * @param parent
 */
static void CLBC_interface(ClassLoader* self, ILType* iltype, Namespace* parent);

static void CLBC_attach_NativeMethod(ClassLoader* self, ILType* iltype, Class* classz, ILMethod* ilmethod, Method* me);
static void CLBC_debug_NativeMethod(Method* parent, Frame* fr, Enviroment* env);

static void CLBC_check_superclass(Class* cls);
static Type* CLBC_get_or_load_enum(Namespace* parent, ILType* iltype);
static Type* CLBC_get_or_load_class(ClassLoader* self, Namespace* parent, ILType* iltype);
static void CLBC_register_class(ClassLoader* self, Namespace* parent, ILType* iltype, Type* tp, Class* cls);
static Type* CLBC_get_or_load_interface(ClassLoader* self, Namespace* parent, ILType* iltype);
static void CLBC_register_interface(ClassLoader* self, Namespace* parent, ILType* iltype, Type* tp, Interface* inter);

void BCLoadClassLoader(ClassLoader* self) {
	CL_ERROR(self);
	ScriptContext* ctx = GetCurrentScriptContext();
	ILToplevel* iltop = self->ILCode;
	CLBC_import(self, self->ILCode->ImportList);
	CLBC_Namespacetree(self);
}

void SpecialBCLoadClassLoader(ClassLoader* self) {
	CL_ERROR(self);
	ScriptContext* ctx = GetCurrentScriptContext();
	ILToplevel* iltop = self->ILCode;
//	CLBC_import(self, self->ILCode->import_list);
	CLBC_Namespacetree(self);
}

//private
static void CLBC_Namespacetree(ClassLoader* self) {
	CL_ERROR(self);
	CLBC_Namespacelist(self, self->ILCode->NamespaceList, NULL);
}

static void CLBC_Namespacelist(ClassLoader* self, Vector* ilNamespacelist, Namespace* parent) {
	//self->link = classlink_resume;
	CL_ERROR(self);
	for (int i = 0; i < ilNamespacelist->Length; i++) {
		VectorItem e = AtVector(ilNamespacelist, i);
		ILNamespace* iln = (ILNamespace*)e;
		CLBC_namespace(self, iln, parent);
		CL_ERROR(self);
	}
}

static void CLBC_namespace(ClassLoader* self, ILNamespace* ilnamespace, Namespace* parent) {
	CL_ERROR(self);
	Namespace* current = NULL;
	if (parent == NULL) {
		current = CreateNamespaceAtRoot(ilnamespace->Name);
	} else {
		current = AddNamespaceNamespace(parent, ilnamespace->Name);
	}
	CLBC_Namespacelist(self, ilnamespace->NamespaceList, current);
	CLBC_type_list(self, ilnamespace->TypeList, current);
}

static void CLBC_type_list(ClassLoader* self, Vector* iltype_list, Namespace* parent) {
	CL_ERROR(self);
	for (int i = 0; i < iltype_list->Length; i++) {
		VectorItem e = AtVector(iltype_list, i);
		ILType* ilt = (ILType*)e;
		if (ilt->Tag == ILTYPE_CLASS_T) {
			CLBC_class(self, ilt, parent);
		} else if (ilt->Tag == ILTYPE_INTERFACE_T) {
			CLBC_interface(self, ilt, parent);
		} else if (ilt->Tag == ILTYPE_ENUM_T) {
			CLBC_enum(self, ilt, parent);
		}
		CL_ERROR(self);
	}
}

static void CLBC_enum(ClassLoader * self, ILType * iltype, Namespace * parent) {
	CL_ERROR(self);
	assert(iltype->Tag == ILTYPE_ENUM_T);
	ILEnum* ilenum = iltype->Kind.Enum;
	Type* tp = CLBC_get_or_load_enum(parent, iltype);
	CL_ERROR(self);
	Class* cls = TYPE2CLASS(tp);
	if((tp->State & TYPE_REGISTER) > 0) {
		return;
	}
	InitGenericSelf(tp, 0);
	//全ての列挙子を public static final フィールドとして追加
	for (int i = 0; i < ilenum->Items->Length; i++) {
		StringView str = (StringView)AtVector(ilenum->Items, i);
		Field* f = NewField(str);
		f->Modifier = MODIFIER_STATIC_T;
		f->Access = ACCESS_PUBLIC_T;
		f->StaticValue = NULL;
		f->GType = TYPE_INT->GenericSelf;
		//virtual_type_nongeneric_init(&f->vtype, GENERIC_INT);
		f->Parent = tp;
		//f->static_value->paint = PAINT_MARKED_T;
		AddFieldClass(cls, f);
	}
	//宣言のロードを予約
	TypeCache* tc = InitTypeCache(
		NewTypeCache(),
		self,
		iltype,
		tp,
		parent,
		CACHEKIND_ENUM_DECL_T
	);
	PushVector(self->TypeCaches, tc);
	//実装のロードを予約
	TypeCache* mtc = InitTypeCache(
		NewTypeCache(),
		self,
		iltype,
		tp,
		parent,
		CACHEKIND_ENUM_IMPL_T
	);
	PushVector(self->TypeCaches, mtc);
	tp->State = tp->State | TYPE_REGISTER;
}

static void CLBC_class(ClassLoader* self, ILType* iltype, Namespace* parent) {
	CL_ERROR(self);
	//既に登録されていたら二重に登録しないように
	//例えば、ネイティブメソッドを登録するために一時的にクラスが登録されている場合がある
	assert(iltype->Tag == ILTYPE_CLASS_T);
	Type* tp = CLBC_get_or_load_class(self, parent, iltype);
	CL_ERROR(self);
	Class* cls = TYPE2CLASS(tp);
	if((tp->State & TYPE_REGISTER) > 0) {
		return;
	}
	cls->IsAbstract = iltype->Kind.Class->IsAbstract;
	InitGenericSelf(tp, iltype->Kind.Class->TypeParameters->Length);
	//デフォルトで親に Object を持つように
	CLBC_check_superclass(cls);
	//宣言のロードを予約
	TypeCache* tc = InitTypeCache(
		NewTypeCache(),
		self,
		iltype,
		tp,
		parent,
		CACHEKIND_CLASS_DECL_T
	);
	PushVector(self->TypeCaches, tc);
	//実装のロードを予約
	TypeCache* mtc = InitTypeCache(
		NewTypeCache(),
		self,
		iltype,
		tp,
		parent,
		CACHEKIND_CLASS_IMPL_T
	);
	PushVector(self->TypeCaches, mtc);
	tp->State = tp->State | TYPE_REGISTER;
}

static void CLBC_interface(ClassLoader * self, ILType * iltype, Namespace * parent) {
	CL_ERROR(self);
	assert(iltype->Tag == ILTYPE_INTERFACE_T);
	//NOTE:後で親関数から渡すようにする
	Type* tp = CLBC_get_or_load_interface(self, parent, iltype);
	CL_ERROR(self);
	Interface* inter = TYPE2INTERFACE(tp);
	if((tp->State & TYPE_REGISTER) > 0) {
		return;
	}
	InitGenericSelf(tp, iltype->Kind.Interface->TypeParameters->Length);
	//宣言のロードを予約
	TypeCache* tc = InitTypeCache(
		NewTypeCache(),
		self,
		iltype,
		tp,
		parent,
		CACHEKIND_INTERFACE_DECL_T
	);
	PushVector(self->TypeCaches, tc);
	//実装のロードを予約
	TypeCache* mtc = InitTypeCache(
		NewTypeCache(),
		self,
		iltype,
		tp,
		parent,
		CACHEKIND_INTERFACE_IMPL_T
	);
	PushVector(self->TypeCaches, mtc);
	tp->State = tp->State | TYPE_REGISTER;
}

static void CLBC_attach_NativeMethod(ClassLoader* self, ILType* ilclass, Class* classz, ILMethod* ilmethod, Method* me) {
//	native_method.h で、実行時にリンクするようにしたので不要
//	me->u.NativeMethod->ref = NewNativeMethodRef(class_loader_sgload_debug_NativeMethod);
}

static void CLBC_debug_NativeMethod(Method* parent, Frame*fr, Enviroment* env) {

}

static void CLBC_check_superclass(Class* cls) {
	Class* objClass = TYPE_OBJECT->Kind.Class;
	if (cls != objClass) {
		if (cls->SuperClass == NULL) {
			cls->SuperClass = GENERIC_OBJECT;
		}
	}
}

static Type* CLBC_get_or_load_enum(Namespace* parent, ILType* iltype) {
	Class* outClass = NULL;
	Type* tp = FindTypeFromNamespace(parent, iltype->Kind.Enum->Name);
	if (tp == NULL) {
		outClass = NewClass(iltype->Kind.Enum->Name);
		outClass->Location = parent;
		tp = WrapClass(outClass);
		AddTypeNamespace(parent, tp);
	} else {
		outClass = tp->Kind.Class;
	}
	return tp;
}

static Type* CLBC_get_or_load_class(ClassLoader* self, Namespace* parent, ILType* iltype) {
	Type* tp = FindTypeFromNamespace(parent, iltype->Kind.Class->Name);
	Class* outClass = NULL;
	//取得できなかった
	if (tp == NULL) {
		outClass = NewClass(iltype->Kind.Class->Name);
		tp = WrapClass(outClass);
		CLBC_register_class(self, parent, iltype, tp, outClass);
		CL_ERROR_RET(self, tp);
	} else {
		outClass = tp->Kind.Class;
		if((tp->State & TYPE_REGISTER) == 0) {
			//もしネイティブメソッドのために
			//既に登録されていたならここが型変数がNULLになってしまう
			DupTypeParameterList(iltype->Kind.Class->TypeParameters, outClass->TypeParameters);
		}
	}
	return tp;
}

static void CLBC_register_class(ClassLoader* self, Namespace* parent, ILType* iltype, Type* tp, Class* cls) {
	InitGenericSelf(tp, iltype->Kind.Class->TypeParameters->Length);
	DupTypeParameterList(iltype->Kind.Class->TypeParameters, cls->TypeParameters);
	CallContext* cctx = NewCallContext(CALL_DECL_T);
	cctx->Scope = parent;
	cctx->Ty = tp;
	for (int i = 0; i < iltype->Kind.Class->Extends->Length; i++) {
		GenericCache* e = (GenericCache*)AtVector(iltype->Kind.Class->Extends, i);
		//最初の一つはクラスでもインターフェースでもよい
		if (i == 0) {
			GenericType* gtp = ResolveImportManager(parent, e, cctx);
			assert(gtp != NULL);
			if (gtp->CoreType->Tag == TYPE_CLASS_T) {
				cls->SuperClass = gtp;
			} else if (gtp->CoreType->Tag == TYPE_INTERFACE_T) {
				PushVector(cls->Implements, gtp);
			} else assert(false);
		//二つ目以降はインターフェースのみ
		} else {
			GenericType* gtp = ResolveImportManager(parent, e, cctx);
			Type* E = GENERIC2TYPE(gtp);
			#if defined(DEBUG)
			const char* Estr = Ref2Str(GetTypeName(E));
			#endif
			PushVector(cls->Implements, gtp);
			if(E->Tag != TYPE_INTERFACE_T) {
				ThrowBCError(BCERROR_CLASS_FIRST_T, Ref2Str(GetTypeName(tp)));
				AddTypeNamespace(parent, tp);
				DeleteCallContext(cctx);
				return;
			}
		}
	}
	DeleteCallContext(cctx);
	cls->Location = parent;
	AddTypeNamespace(parent, tp);
	//重複するインターフェイスを検出
	Interface* inter = NULL;
	if((inter = IsValidInterface(tp))) {
		ThrowBCError(BCERROR_MULTI_EQINTERFACE_T, Ref2Str(inter->Name));
	}
}

static Type* CLBC_get_or_load_interface(ClassLoader* self, Namespace* parent, ILType* iltype) {
	Type* tp = FindTypeFromNamespace(parent, iltype->Kind.Interface->Name);
	Interface* inter = NULL;
	if (tp == NULL) {
		inter = NewInterface(iltype->Kind.Interface->Name);
		tp = WrapInterface(inter);
		CLBC_register_interface(self, parent, iltype, tp, inter);
		CL_ERROR_RET(self, tp);
	} else {
		inter = tp->Kind.Interface;
		if((tp->State & TYPE_REGISTER) == 0) {
			//もしネイティブメソッドのために
			//既に登録されていたならここが型変数がNULLになってしまう
			DupTypeParameterList(GetTypeParametersILType(iltype), inter->TypeParameters);
		}
	}
	return tp;
}

static void CLBC_register_interface(ClassLoader* self, Namespace* parent, ILType* iltype, Type* tp, Interface* inter) {
	InitGenericSelf(tp, iltype->Kind.Interface->TypeParameters->Length);
	DupTypeParameterList(iltype->Kind.Interface->TypeParameters, inter->TypeParameters);
	CallContext* cctx = NewCallContext(CALL_DECL_T);
	cctx->Scope = parent;
	cctx->Ty = tp;
	for (int i = 0; i < iltype->Kind.Interface->Extends->Length; i++) {
		GenericCache* e = (GenericCache*)AtVector(iltype->Kind.Interface->Extends, i);
		//インターフェースはインターフェースのみ継承
		GenericType* gtp = ResolveImportManager(parent, e, cctx);
		Type* E = GENERIC2TYPE(gtp);
		if(E->Tag != TYPE_INTERFACE_T) {
			ThrowBCError(BCERROR_INTERFACE_ONLY_T, Ref2Str(GetTypeName(tp)));
			AddTypeNamespace(parent, tp);
			DeleteCallContext(cctx);
			return;
		//インターフェイスの時のみ追加
		} else {
			PushVector(inter->Implements, gtp);
		}
	}
	//場所を設定
	inter->Location = parent;
	DeleteCallContext(cctx);
	AddTypeNamespace(parent, tp);
	//重複するインターフェイスを検出
	Interface* ovinter = NULL;
	if((ovinter = IsValidInterface(tp))) {
		ThrowBCError(BCERROR_MULTI_EQINTERFACE_T, Ref2Str(ovinter->Name));
	}
}