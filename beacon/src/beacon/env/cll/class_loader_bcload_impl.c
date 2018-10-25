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
static void CLBC_Namespacetree(class_loader* self);
/**
 * 名前空間の一覧を読み込みます.
 * @param self
 * @param ilNamespacelist
 * @param parent
 */
static void CLBC_Namespacelist(class_loader* self, Vector* ilNamespacelist, Namespace* parent);

/**
 * 名前空間と含まれるエントリの一覧を読み込みます.
 * @param self
 * @param ilnamespace
 * @param parent
 */
static void CLBC_namespace(class_loader* self, ILNamespace* ilnamespace, Namespace* parent);

/**
 * 型宣言の一覧を読み込みます.
 * @param self
 * @param iltype_list
 * @param parent
 */
static void CLBC_type_list(class_loader* self, Vector* iltype_list, Namespace* parent);

/**
 * 列挙宣言を読み込んで名前空間に登録します.
 * @param self
 * @param iltype
 * @param parent
 */
static void CLBC_enum(class_loader* self, il_type* iltype, Namespace* parent);

/**
 * クラス宣言を読み込んで名前空間に登録します.
 * @param self
 * @param iltype
 * @param parent
 */
static void CLBC_class(class_loader* self, il_type* iltype, Namespace* parent);

/**
 * インターフェース宣言を読み込んで名前空間に登録します.
 * @param self
 * @param iltype
 * @param parent
 */
static void CLBC_interface(class_loader* self, il_type* iltype, Namespace* parent);

static void CLBC_attach_NativeMethod(class_loader* self, il_type* iltype, class_* classz, ILMethod* ilmethod, Method* me);
static void CLBC_debug_NativeMethod(Method* parent, Frame* fr, Enviroment* env);

static void CLBC_check_superclass(class_* cls);
static type* CLBC_get_or_load_enum(Namespace* parent, il_type* iltype);
static type* CLBC_get_or_load_class(class_loader* self, Namespace* parent, il_type* iltype);
static void CLBC_register_class(class_loader* self, Namespace* parent, il_type* iltype, type* tp, class_* cls);
static type* CLBC_get_or_load_interface(class_loader* self, Namespace* parent, il_type* iltype);
static void CLBC_register_interface(class_loader* self, Namespace* parent, il_type* iltype, type* tp, interface_* inter);

void BCLoadClassLoader(class_loader* self) {
	CL_ERROR(self);
	ScriptContext* ctx = GetCurrentScriptContext();
	ILToplevel* iltop = self->il_code;
	CLBC_import(self, self->il_code->ImportList);
	CLBC_Namespacetree(self);
}

void SpecialBCLoadClassLoader(class_loader* self) {
	CL_ERROR(self);
	ScriptContext* ctx = GetCurrentScriptContext();
	ILToplevel* iltop = self->il_code;
//	CLBC_import(self, self->il_code->import_list);
	CLBC_Namespacetree(self);
}

//private
static void CLBC_Namespacetree(class_loader* self) {
	CL_ERROR(self);
	CLBC_Namespacelist(self, self->il_code->NamespaceList, NULL);
}

static void CLBC_Namespacelist(class_loader* self, Vector* ilNamespacelist, Namespace* parent) {
	//self->link = classlink_resume;
	CL_ERROR(self);
	for (int i = 0; i < ilNamespacelist->Length; i++) {
		VectorItem e = AtVector(ilNamespacelist, i);
		ILNamespace* iln = (ILNamespace*)e;
		CLBC_namespace(self, iln, parent);
		CL_ERROR(self);
	}
}

static void CLBC_namespace(class_loader* self, ILNamespace* ilnamespace, Namespace* parent) {
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

static void CLBC_type_list(class_loader* self, Vector* iltype_list, Namespace* parent) {
	CL_ERROR(self);
	for (int i = 0; i < iltype_list->Length; i++) {
		VectorItem e = AtVector(iltype_list, i);
		il_type* ilt = (il_type*)e;
		if (ilt->tag == ilTYPE_CLASS_T) {
			CLBC_class(self, ilt, parent);
		} else if (ilt->tag == ilTYPE_INTERFACE_T) {
			CLBC_interface(self, ilt, parent);
		} else if (ilt->tag == ilTYPE_ENUM_T) {
			CLBC_enum(self, ilt, parent);
		}
		CL_ERROR(self);
	}
}

static void CLBC_enum(class_loader * self, il_type * iltype, Namespace * parent) {
	CL_ERROR(self);
	assert(iltype->tag == ilTYPE_ENUM_T);
	il_enum* ilenum = iltype->u.enum_;
	type* tp = CLBC_get_or_load_enum(parent, iltype);
	CL_ERROR(self);
	class_* cls = TYPE2CLASS(tp);
	if((tp->state & TYPE_REGISTER) > 0) {
		return;
	}
	InitGenericSelf(tp, 0);
	//全ての列挙子を public static final フィールドとして追加
	for (int i = 0; i < ilenum->item_vec->Length; i++) {
		StringView str = (StringView)AtVector(ilenum->item_vec, i);
		field* f = NewField(str);
		f->modifier = MODIFIER_STATIC_T;
		f->access = ACCESS_PUBLIC_T;
		f->static_value = NULL;
		f->gtype = TYPE_INT->generic_self;
		//virtual_type_nongeneric_init(&f->vtype, GENERIC_INT);
		f->parent = tp;
		//f->static_value->paint = PAINT_MARKED_T;
		AddFieldClass(cls, f);
	}
	//宣言のロードを予約
	type_cache* tc = InitTypeCache(
		NewTypeCache(),
		self,
		iltype,
		tp,
		parent,
		CACHEKIND_ENUM_DECL_T
	);
	PushVector(self->type_cache_vec, tc);
	//実装のロードを予約
	type_cache* mtc = InitTypeCache(
		NewTypeCache(),
		self,
		iltype,
		tp,
		parent,
		CACHEKIND_ENUM_IMPL_T
	);
	PushVector(self->type_cache_vec, mtc);
	tp->state = tp->state | TYPE_REGISTER;
}

static void CLBC_class(class_loader* self, il_type* iltype, Namespace* parent) {
	CL_ERROR(self);
	//既に登録されていたら二重に登録しないように
	//例えば、ネイティブメソッドを登録するために一時的にクラスが登録されている場合がある
	assert(iltype->tag == ilTYPE_CLASS_T);
	type* tp = CLBC_get_or_load_class(self, parent, iltype);
	CL_ERROR(self);
	class_* cls = TYPE2CLASS(tp);
	if((tp->state & TYPE_REGISTER) > 0) {
		return;
	}
	cls->is_abstract = iltype->u.class_->is_abstract;
	InitGenericSelf(tp, iltype->u.class_->GetParameterListType->Length);
	//デフォルトで親に Object を持つように
	CLBC_check_superclass(cls);
	//宣言のロードを予約
	type_cache* tc = InitTypeCache(
		NewTypeCache(),
		self,
		iltype,
		tp,
		parent,
		CACHEKIND_CLASS_DECL_T
	);
	PushVector(self->type_cache_vec, tc);
	//実装のロードを予約
	type_cache* mtc = InitTypeCache(
		NewTypeCache(),
		self,
		iltype,
		tp,
		parent,
		CACHEKIND_CLASS_IMPL_T
	);
	PushVector(self->type_cache_vec, mtc);
	tp->state = tp->state | TYPE_REGISTER;
}

static void CLBC_interface(class_loader * self, il_type * iltype, Namespace * parent) {
	CL_ERROR(self);
	assert(iltype->tag == ilTYPE_INTERFACE_T);
	//NOTE:後で親関数から渡すようにする
	type* tp = CLBC_get_or_load_interface(self, parent, iltype);
	CL_ERROR(self);
	interface_* inter = TYPE2INTERFACE(tp);
	if((tp->state & TYPE_REGISTER) > 0) {
		return;
	}
	InitGenericSelf(tp, iltype->u.interface_->GetParameterListType->Length);
	//宣言のロードを予約
	type_cache* tc = InitTypeCache(
		NewTypeCache(),
		self,
		iltype,
		tp,
		parent,
		CACHEKIND_INTERFACE_DECL_T
	);
	PushVector(self->type_cache_vec, tc);
	//実装のロードを予約
	type_cache* mtc = InitTypeCache(
		NewTypeCache(),
		self,
		iltype,
		tp,
		parent,
		CACHEKIND_INTERFACE_IMPL_T
	);
	PushVector(self->type_cache_vec, mtc);
	tp->state = tp->state | TYPE_REGISTER;
}

static void CLBC_attach_NativeMethod(class_loader* self, il_type* ilclass, class_* classz, ILMethod* ilmethod, Method* me) {
//	native_method.h で、実行時にリンクするようにしたので不要
//	me->u.NativeMethod->ref = NewNativeMethodRef(class_loader_sgload_debug_NativeMethod);
}

static void CLBC_debug_NativeMethod(Method* parent, Frame*fr, Enviroment* env) {

}

static void CLBC_check_superclass(class_* cls) {
	class_* objClass = TYPE_OBJECT->u.class_;
	if (cls != objClass) {
		if (cls->super_class == NULL) {
			cls->super_class = GENERIC_OBJECT;
		}
	}
}

static type* CLBC_get_or_load_enum(Namespace* parent, il_type* iltype) {
	class_* outClass = NULL;
	type* tp = FindTypeFromNamespace(parent, iltype->u.enum_->namev);
	if (tp == NULL) {
		outClass = NewClass(iltype->u.enum_->namev);
		outClass->location = parent;
		tp = WrapClass(outClass);
		AddTypeNamespace(parent, tp);
	} else {
		outClass = tp->u.class_;
	}
	return tp;
}

static type* CLBC_get_or_load_class(class_loader* self, Namespace* parent, il_type* iltype) {
	type* tp = FindTypeFromNamespace(parent, iltype->u.class_->namev);
	class_* outClass = NULL;
	//取得できなかった
	if (tp == NULL) {
		outClass = NewClass(iltype->u.class_->namev);
		tp = WrapClass(outClass);
		CLBC_register_class(self, parent, iltype, tp, outClass);
		CL_ERROR_RET(self, tp);
	} else {
		outClass = tp->u.class_;
		if((tp->state & TYPE_REGISTER) == 0) {
			//もしネイティブメソッドのために
			//既に登録されていたならここが型変数がNULLになってしまう
			DupTypeParameterList(iltype->u.class_->GetParameterListType, outClass->GetParameterListType);
		}
	}
	return tp;
}

static void CLBC_register_class(class_loader* self, Namespace* parent, il_type* iltype, type* tp, class_* cls) {
	InitGenericSelf(tp, iltype->u.class_->GetParameterListType->Length);
	DupTypeParameterList(iltype->u.class_->GetParameterListType, cls->GetParameterListType);
	CallContext* cctx = NewCallContext(CALL_DECL_T);
	cctx->Scope = parent;
	cctx->Ty = tp;
	for (int i = 0; i < iltype->u.class_->extend_list->Length; i++) {
		GenericCache* e = (GenericCache*)AtVector(iltype->u.class_->extend_list, i);
		//最初の一つはクラスでもインターフェースでもよい
		if (i == 0) {
			generic_type* gtp = ResolveImportManager(parent, e, cctx);
			assert(gtp != NULL);
			if (gtp->core_type->tag == TYPE_CLASS_T) {
				cls->super_class = gtp;
			} else if (gtp->core_type->tag == TYPE_INTERFACE_T) {
				PushVector(cls->impl_list, gtp);
			} else assert(false);
		//二つ目以降はインターフェースのみ
		} else {
			generic_type* gtp = ResolveImportManager(parent, e, cctx);
			type* E = GENERIC2TYPE(gtp);
			#if defined(DEBUG)
			const char* Estr = Ref2Str(GetTypeName(E));
			#endif
			PushVector(cls->impl_list, gtp);
			if(E->tag != TYPE_INTERFACE_T) {
				ThrowBCError(BCERROR_CLASS_FIRST_T, Ref2Str(GetTypeName(tp)));
				AddTypeNamespace(parent, tp);
				DeleteCallContext(cctx);
				return;
			}
		}
	}
	DeleteCallContext(cctx);
	cls->location = parent;
	AddTypeNamespace(parent, tp);
	//重複するインターフェイスを検出
	interface_* inter = NULL;
	if((inter = IsValidInterface(tp))) {
		ThrowBCError(BCERROR_MULTI_EQINTERFACE_T, Ref2Str(inter->namev));
	}
}

static type* CLBC_get_or_load_interface(class_loader* self, Namespace* parent, il_type* iltype) {
	type* tp = FindTypeFromNamespace(parent, iltype->u.interface_->namev);
	interface_* inter = NULL;
	if (tp == NULL) {
		inter = NewInterface(iltype->u.interface_->namev);
		tp = WrapInterface(inter);
		CLBC_register_interface(self, parent, iltype, tp, inter);
		CL_ERROR_RET(self, tp);
	} else {
		inter = tp->u.interface_;
		if((tp->state & TYPE_REGISTER) == 0) {
			//もしネイティブメソッドのために
			//既に登録されていたならここが型変数がNULLになってしまう
			DupTypeParameterList(GetTypeParametersILType(iltype), inter->GetParameterListType);
		}
	}
	return tp;
}

static void CLBC_register_interface(class_loader* self, Namespace* parent, il_type* iltype, type* tp, interface_* inter) {
	InitGenericSelf(tp, iltype->u.interface_->GetParameterListType->Length);
	DupTypeParameterList(iltype->u.interface_->GetParameterListType, inter->GetParameterListType);
	CallContext* cctx = NewCallContext(CALL_DECL_T);
	cctx->Scope = parent;
	cctx->Ty = tp;
	for (int i = 0; i < iltype->u.interface_->extends_list->Length; i++) {
		GenericCache* e = (GenericCache*)AtVector(iltype->u.interface_->extends_list, i);
		//インターフェースはインターフェースのみ継承
		generic_type* gtp = ResolveImportManager(parent, e, cctx);
		type* E = GENERIC2TYPE(gtp);
		if(E->tag != TYPE_INTERFACE_T) {
			ThrowBCError(BCERROR_INTERFACE_ONLY_T, Ref2Str(GetTypeName(tp)));
			AddTypeNamespace(parent, tp);
			DeleteCallContext(cctx);
			return;
		//インターフェイスの時のみ追加
		} else {
			PushVector(inter->impl_list, gtp);
		}
	}
	//場所を設定
	inter->location = parent;
	DeleteCallContext(cctx);
	AddTypeNamespace(parent, tp);
	//重複するインターフェイスを検出
	interface_* ovinter = NULL;
	if((ovinter = IsValidInterface(tp))) {
		ThrowBCError(BCERROR_MULTI_EQINTERFACE_T, Ref2Str(ovinter->namev));
	}
}