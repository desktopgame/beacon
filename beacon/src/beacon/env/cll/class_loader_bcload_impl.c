#include "class_loader_bcload_impl.h"
#include "../script_context.h"
#include "../../util/text.h"
#include "../../util/io.h"
#include "../../util/xassert.h"
#include "../../parse/parser.h"
#include "../../il/il_type_impl.h"
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
#include "../type_impl.h"
#include "../../env/object.h"
#include "../type_parameter.h"
#include "../parameter.h"
#include "../field.h"
#include "../method.h"
#include "../compile_context.h"
#include "../constructor.h"
#include "class_loader_bcload_import_module_impl.h"
#include "../../util/mem.h"
#include "../../util/xassert.h"
#include "../../debug.h"
#include <assert.h>
//
//sgload
//
#include "../type_cache.h"
#include <string.h>
#include "../import_info.h"
#include "../../env/heap.h"
//proto
static void CLBC_namespace_tree(class_loader* self);
/**
 * 名前空間の一覧を読み込みます.
 * @param self
 * @param ilnamespace_list
 * @param parent
 */
static void CLBC_namespace_list(class_loader* self, vector* ilnamespace_list, namespace_* parent);

/**
 * 名前空間と含まれるエントリの一覧を読み込みます.
 * @param self
 * @param ilnamespace
 * @param parent
 */
static void CLBC_namespace(class_loader* self, il_namespace* ilnamespace, namespace_* parent);

/**
 * 型宣言の一覧を読み込みます.
 * @param self
 * @param iltype_list
 * @param parent
 */
static void CLBC_type_list(class_loader* self, vector* iltype_list, namespace_* parent);

/**
 * 列挙宣言を読み込んで名前空間に登録します.
 * @param self
 * @param iltype
 * @param parent
 */
static void CLBC_enum(class_loader* self, il_type* iltype, namespace_* parent);

/**
 * クラス宣言を読み込んで名前空間に登録します.
 * @param self
 * @param iltype
 * @param parent
 */
static void CLBC_class(class_loader* self, il_type* iltype, namespace_* parent);

/**
 * インターフェース宣言を読み込んで名前空間に登録します.
 * @param self
 * @param iltype
 * @param parent
 */
static void CLBC_interface(class_loader* self, il_type* iltype, namespace_* parent);

static void CLBC_attach_native_method(class_loader* self, il_type* iltype, class_* classz, il_method* ilmethod, method* me);
static void CLBC_debug_native_method(method* parent, frame* fr, enviroment* env);

static void CLBC_check_superclass(class_* cls);
static type* CLBC_get_or_load_enum(namespace_* parent, il_type* iltype);
static type* CLBC_get_or_load_class(class_loader* self, namespace_* parent, il_type* iltype);
static void CLBC_register_class(class_loader* self, namespace_* parent, il_type* iltype, type* tp, class_* cls);
static type* CLBC_get_or_load_interface(class_loader* self, namespace_* parent, il_type* iltype);
static void CLBC_register_interface(class_loader* self, namespace_* parent, il_type* iltype, type* tp, interface_* inter);

void class_loader_bcload_impl(class_loader* self) {
	CL_ERROR(self);
	script_context* ctx = script_context_get_current();
	il_top_level* iltop = self->il_code;
	CLBC_import(self, self->il_code->import_list);
	CLBC_namespace_tree(self);
}

void class_loader_bcload_special(class_loader* self) {
	CL_ERROR(self);
	script_context* ctx = script_context_get_current();
	il_top_level* iltop = self->il_code;
//	CLBC_import(self, self->il_code->import_list);
	CLBC_namespace_tree(self);
}

//private
static void CLBC_namespace_tree(class_loader* self) {
	CL_ERROR(self);
	CLBC_namespace_list(self, self->il_code->namespace_list, NULL);
}

static void CLBC_namespace_list(class_loader* self, vector* ilnamespace_list, namespace_* parent) {
	//self->link = classlink_resume;
	CL_ERROR(self);
	for (int i = 0; i < ilnamespace_list->length; i++) {
		vector_item e = vector_at(ilnamespace_list, i);
		il_namespace* iln = (il_namespace*)e;
		CLBC_namespace(self, iln, parent);
		CL_ERROR(self);
	}
}

static void CLBC_namespace(class_loader* self, il_namespace* ilnamespace, namespace_* parent) {
	CL_ERROR(self);
	namespace_* current = NULL;
	if (parent == NULL) {
		current = namespace_create_at_root(ilnamespace->namev);
	} else {
		current = namespace_add_namespace(parent, ilnamespace->namev);
	}
	CLBC_namespace_list(self, ilnamespace->namespace_list, current);
	CLBC_type_list(self, ilnamespace->type_list, current);
}

static void CLBC_type_list(class_loader* self, vector* iltype_list, namespace_* parent) {
	CL_ERROR(self);
	for (int i = 0; i < iltype_list->length; i++) {
		vector_item e = vector_at(iltype_list, i);
		il_type* ilt = (il_type*)e;
		if (ilt->tag == iltype_class) {
			CLBC_class(self, ilt, parent);
		} else if (ilt->tag == iltype_interface) {
			CLBC_interface(self, ilt, parent);
		} else if (ilt->tag == iltype_enum) {
			CLBC_enum(self, ilt, parent);
		}
		CL_ERROR(self);
	}
}

static void CLBC_enum(class_loader * self, il_type * iltype, namespace_ * parent) {
	CL_ERROR(self);
	assert(iltype->tag == iltype_enum);
	il_enum* ilenum = iltype->u.enum_;
	type* tp = CLBC_get_or_load_enum(parent, iltype);
	CL_ERROR(self);
	class_* cls = TYPE2CLASS(tp);
	if((tp->state & type_register) > 0) {
		return;
	}
	//全ての列挙子を public static final フィールドとして追加
	for (int i = 0; i < ilenum->item_vec->length; i++) {
		string_view str = (string_view)vector_at(ilenum->item_vec, i);
		field* f = field_new(str);
		f->modifier = modifier_static;
		f->access = access_public;
		f->static_value = object_int_get(i);
		f->gtype = TYPE_INT->generic_self;
		//virtual_type_nongeneric_init(&f->vtype, GENERIC_INT);
		f->parent = tp;
		//f->static_value->paint = paint_marked;
		class_add_field(cls, f);
	}
	//宣言のロードを予約
	type_cache* tc = type_cache_init(
		type_cache_new(),
		self,
		iltype,
		tp,
		parent,
		cachekind_enum_decl
	);
	vector_push(self->type_cache_vec, tc);
	//実装のロードを予約
	type_cache* mtc = type_cache_init(
		type_cache_new(),
		self,
		iltype,
		tp,
		parent,
		cachekind_enum_decl
	);
	vector_push(self->type_cache_vec, mtc);
	tp->state = tp->state | type_register;
}

static void CLBC_class(class_loader* self, il_type* iltype, namespace_* parent) {
	CL_ERROR(self);
	//*
	//既に登録されていたら二重に登録しないように
	//例えば、ネイティブメソッドを登録するために一時的にクラスが登録されている場合がある
	assert(iltype->tag == iltype_class);
	//FIXME:あとで親関数から渡すようにする
	ccpush_namespace(parent);
	ccset_class_loader(self);
	//すでに宣言されているならそれを取得
	type* tp = CLBC_get_or_load_class(self, parent, iltype);
	CL_ERROR(self);
	class_* cls = TYPE2CLASS(tp);
	if((tp->state & type_register) > 0) {
		return;
	}
	cls->is_abstract = iltype->u.class_->is_abstract;
	type_init_generic(tp, iltype->u.class_->type_parameter_list->length);
	//デフォルトで親に Object を持つように
	CLBC_check_superclass(cls);
	//宣言のロードを予約
	type_cache* tc = type_cache_init(
		type_cache_new(),
		self,
		iltype,
		tp,
		parent,
		cachekind_class_decl
	);
	vector_push(self->type_cache_vec, tc);
	//実装のロードを予約
	type_cache* mtc = type_cache_init(
		type_cache_new(),
		self,
		iltype,
		tp,
		parent,
		cachekind_class_impl
	);
	vector_push(self->type_cache_vec, mtc);
	ccpop_type();
	ccpop_namespace();
	ccset_class_loader(NULL);
	tp->state = tp->state | type_register;
}

static void CLBC_interface(class_loader * self, il_type * iltype, namespace_ * parent) {
	CL_ERROR(self);
	assert(iltype->tag == iltype_interface);
	//NOTE:後で親関数から渡すようにする
	ccpush_namespace(parent);
	ccset_class_loader(self);
	type* tp = CLBC_get_or_load_interface(self, parent, iltype);
	CL_ERROR(self);
	interface_* inter = TYPE2INTERFACE(tp);
	if((tp->state & type_register) > 0) {
		return;
	}
	type_init_generic(tp, iltype->u.interface_->type_parameter_list->length);
	//宣言のロードを予約
	type_cache* tc = type_cache_init(
		type_cache_new(),
		self,
		iltype,
		tp,
		parent,
		cachekind_interface_decl
	);
	vector_push(self->type_cache_vec, tc);
	//実装のロードを予約
	type_cache* mtc = type_cache_init(
		type_cache_new(),
		self,
		iltype,
		tp,
		parent,
		cachekind_interface_impl
	);
	vector_push(self->type_cache_vec, mtc);
	ccpop_type();
	ccpop_namespace();
	ccset_class_loader(NULL);
	tp->state = tp->state | type_register;
}

static void CLBC_attach_native_method(class_loader* self, il_type* ilclass, class_* classz, il_method* ilmethod, method* me) {
//	native_method.h で、実行時にリンクするようにしたので不要
//	me->u.native_method->ref = native_method_ref_new(class_loader_sgload_debug_native_method);
}

static void CLBC_debug_native_method(method* parent, frame*fr, enviroment* env) {

}

static void CLBC_check_superclass(class_* cls) {
	class_* objClass = TYPE_OBJECT->u.class_;
	if (cls != objClass) {
		if (cls->super_class == NULL) {
			cls->super_class = GENERIC_OBJECT;
		}
	}
}

static type* CLBC_get_or_load_enum(namespace_* parent, il_type* iltype) {
	class_* outClass = NULL;
	type* tp = namespace_get_type(parent, iltype->u.enum_->namev);
	if (tp == NULL) {
		outClass = class_new(iltype->u.enum_->namev);
		outClass->location = parent;
		tp = type_wrap_class(outClass);
		namespace_add_type(parent, tp);
	} else {
		outClass = tp->u.class_;
	}
	return tp;
}

static type* CLBC_get_or_load_class(class_loader* self, namespace_* parent, il_type* iltype) {
	type* tp = namespace_get_type(parent, iltype->u.class_->namev);
	class_* outClass = NULL;
	//取得できなかった
	if (tp == NULL) {
		outClass = class_new(iltype->u.class_->namev);
		tp = type_wrap_class(outClass);
		CLBC_register_class(self, parent, iltype, tp, outClass);
		CL_ERROR_RET(self, tp);
	} else {
		ccpush_type(tp);
		outClass = tp->u.class_;
		if((tp->state & type_register) == 0) {
			//もしネイティブメソッドのために
			//既に登録されていたならここが型変数がNULLになってしまう
			type_parameter_list_dup(iltype->u.class_->type_parameter_list, outClass->type_parameter_list);
		}
	}
	return tp;
}

static void CLBC_register_class(class_loader* self, namespace_* parent, il_type* iltype, type* tp, class_* cls) {
	ccpush_type(tp);
	type_init_generic(tp, iltype->u.class_->type_parameter_list->length);
	type_parameter_list_dup(iltype->u.class_->type_parameter_list, cls->type_parameter_list);
	for (int i = 0; i < iltype->u.class_->extend_list->length; i++) {
		generic_cache* e = (generic_cache*)vector_at(iltype->u.class_->extend_list, i);
		//最初の一つはクラスでもインターフェースでもよい
		if (i == 0) {
			generic_type* gtp = import_manager_resolve(self->import_manager, parent, e);
			assert(gtp != NULL);
			if (gtp->core_type->tag == type_class) {
				cls->super_class = gtp;
			} else if (gtp->core_type->tag == type_interface) {
				vector_push(cls->impl_list, gtp);
			}
		//二つ目以降はインターフェースのみ
		} else {
			generic_type* gtp = import_manager_resolve(self->import_manager, parent, e);
			type* E = GENERIC2TYPE(gtp);
			vector_push(cls->impl_list, gtp);
			if(E->tag != type_interface) {
				class_loader_report(self, clerror_class_first, string_pool_ref2str(type_name(tp)));
				namespace_add_type(parent, tp);
				return;
			}
		}
	}
	cls->location = parent;
	namespace_add_type(parent, tp);
	//重複するインターフェイスを検出
	interface_* inter = NULL;
	if((inter = type_interface_valid(tp))) {
		class_loader_report(self, clerror_multi_eqinterface, string_pool_ref2str(inter->namev));
	}
}

static type* CLBC_get_or_load_interface(class_loader* self, namespace_* parent, il_type* iltype) {
	type* tp = namespace_get_type(parent, iltype->u.interface_->namev);
	interface_* inter = NULL;
	if (tp == NULL) {
		inter = interface_new(iltype->u.interface_->namev);
		tp = type_wrap_interface(inter);
		CLBC_register_interface(self, parent, iltype, tp, inter);
		CL_ERROR_RET(self, tp);
	} else {
		ccpush_type(tp);
		inter = tp->u.interface_;
		if((tp->state & type_register) == 0) {
			//もしネイティブメソッドのために
			//既に登録されていたならここが型変数がNULLになってしまう
			type_parameter_list_dup(il_type_type_parameter_list(iltype), inter->type_parameter_list);
		}
	}
	return tp;
}

static void CLBC_register_interface(class_loader* self, namespace_* parent, il_type* iltype, type* tp, interface_* inter) {
	ccpush_type(tp);
	type_init_generic(tp, iltype->u.interface_->type_parameter_list->length);
	type_parameter_list_dup(iltype->u.interface_->type_parameter_list, inter->type_parameter_list);
	for (int i = 0; i < iltype->u.interface_->extends_list->length; i++) {
		generic_cache* e = (generic_cache*)vector_at(iltype->u.interface_->extends_list, i);
		//インターフェースはインターフェースのみ継承
		generic_type* gtp = import_manager_resolve(self->import_manager, parent, e);
		type* E = GENERIC2TYPE(gtp);
		vector_push(inter->impl_list, gtp);
		if(E->tag != type_interface) {
			class_loader_report(self, clerror_interface_only, string_pool_ref2str(type_name(tp)));
			namespace_add_type(parent, tp);
			return;
		}
	}
	//場所を設定
	inter->location = parent;
	namespace_add_type(parent, tp);
	//重複するインターフェイスを検出
	interface_* ovinter = NULL;
	if((ovinter = type_interface_valid(tp))) {
		class_loader_report(self, clerror_multi_eqinterface, string_pool_ref2str(ovinter->namev));
	}
}