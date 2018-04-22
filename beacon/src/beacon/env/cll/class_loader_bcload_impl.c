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
#include "../../il/il_context.h"
#include "../type_interface.h"
#include "../type_impl.h"
#include "../../env/object.h"
#include "../type_parameter.h"
#include "../parameter.h"
#include "../field.h"
#include "../method.h"
#include "../constructor.h"
#include "class_loader_bcload_link_module_impl.h"
#include "class_loader_bcload_import_module_impl.h"
#include "../../util/mem.h"
#include "../../util/xassert.h"
#include <assert.h>
//
//sgload
//
#include "../type_cache.h"
#include <string.h>
#include "../import_info.h"
#include "../../util/logger.h"
#include "../../env/heap.h"
//proto
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
static void CLBC_debug_native_method(method* parent, vm* vm, enviroment* env);



void class_loader_bcload_impl(class_loader* self) {
	CL_ERROR(self);
	script_context* ctx = script_context_get_current();
	il_top_level* iltop = self->il_code;
	CLBC_import(self, self->il_code->import_list);
	CLBC_namespace_tree(self);
}

void class_loader_bcload_link(class_loader * self, link_type type) {
	CL_ERROR(self);
	logger_info(__FILE__, __LINE__, "link %s",self->filename);
	if(type == link_decl) {
		CLBC_excec_class_decl(self);
		CLBC_excec_interface_decl(self);
	} else if(type == link_impl) {
		CLBC_excec_class_impl(self);
		CLBC_excec_interface_impl(self);
	} else assert(false);
}

void CLBC_namespace_tree(class_loader* self) {
	CL_ERROR(self);
	CLBC_namespace_list(self, self->il_code->namespace_list, NULL);
}

//private
static void CLBC_namespace_list(class_loader* self, vector* ilnamespace_list, namespace_* parent) {
	//self->link = classlink_resume;
	CL_ERROR(self);
	for (int i = 0; i < ilnamespace_list->length; i++) {
		vector_item e = vector_at(ilnamespace_list, i);
		il_namespace* iln = (il_namespace*)e;
		CLBC_namespace(self, iln, parent);
	}
}

static void CLBC_namespace(class_loader* self, il_namespace* ilnamespace, namespace_* parent) {
	CL_ERROR(self);
	namespace_* current = NULL;
	if (parent == NULL) {
		current = namespace_create_at_root(ilnamespace->name);
	} else {
		current = namespace_add_namespace(parent, ilnamespace->name);
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
	}
}

static void CLBC_enum(class_loader * self, il_type * iltype, namespace_ * parent) {
	CL_ERROR(self);
	assert(iltype->tag == iltype_enum);
	il_enum* ilenum = iltype->u.enum_;
	type* tp = namespace_get_type(parent, iltype->u.enum_->name);
	class_* cls;
	if (tp == NULL) {
		cls = class_new(iltype->u.enum_->name);
		cls->location = parent;
		tp = type_wrap_class(cls);
		namespace_add_type(parent, tp);
	} else {
		cls = tp->u.class_;
	}
	logger_info(__FILE__, __LINE__, "register enum %s", cls->name);
	//全ての列挙子を public static final フィールドとして追加
	for (int i = 0; i < ilenum->item_vec->length; i++) {
		char* str = (char*)vector_at(ilenum->item_vec, i);
		field* f = field_new(str);
		f->modifier = modifier_static;
		f->access = access_public;
		f->static_value = object_int_new(i);
		virtual_type_nongeneric_init(&f->vtype, GEN_INT);
		f->parent = tp;
		class_add_field(cls, f);
	}
}

static void CLBC_class(class_loader* self, il_type* iltype, namespace_* parent) {
	CL_ERROR(self);
	//*
	//既に登録されていたら二重に登録しないように
	//例えば、ネイティブメソッドを登録するために一時的にクラスが登録されている場合がある
	assert(iltype->tag == iltype_class);
	type* tp = namespace_get_type(parent, iltype->u.class_->name);
	class_* cls;
	//FIXME:あとで親関数から渡すようにする
	il_context* ilctx = il_context_new();
	vector_push(ilctx->namespace_vec, parent);
	type_init_generic(tp, iltype->u.class_->type_parameter_list->length);
	//type_init_generic(tp, iltype->u.class_->type_parameter_list->length);
	if (tp == NULL) {
		cls = class_new(iltype->u.class_->name);
		tp = type_wrap_class(cls);
		vector_push(ilctx->type_vec, tp);
		type_init_generic(tp, iltype->u.class_->type_parameter_list->length);
		//type_init_generic(tp, iltype->u.class_->type_parameter_list->length);
		type_parameter_list_dup(iltype->u.class_->type_parameter_list, cls->type_parameter_list, ilctx);
		for (int i = 0; i < iltype->u.class_->extend_list->length; i++) {
			generic_cache* e = (generic_cache*)vector_at(iltype->u.class_->extend_list, i);
			//最初の一つはクラスでもインターフェースでもよい
			if (i == 0) {
				generic_type* gtp = generic_cache_gtype(e, parent, ilctx);
				assert(gtp != NULL);
				if (gtp->core_type->tag == type_class) {
					cls->super_class = gtp;
				} else if (gtp->core_type->tag == type_interface) {
					vector_push(cls->impl_list, gtp);
				}
			//二つ目以降はインターフェースのみ
			} else {
				generic_type* gtp = generic_cache_gtype(e, parent, ilctx);
				vector_push(cls->impl_list, gtp);
				assert(gtp->core_type->tag == type_interface);
			}
		}
		cls->location = parent;
		namespace_add_type(parent, tp);
	} else {
		vector_push(ilctx->type_vec, tp);
		cls = tp->u.class_;
		//もしネイティブメソッドのために
		//既に登録されていたならここが型変数がNULLになってしまう
		type_parameter_list_dup(iltype->u.class_->type_parameter_list, cls->type_parameter_list, ilctx);
	}
	//デフォルトで親に Object を持つように
	//XSTREQ(cls->name, "String");
	class_* objClass = CL_OBJECT->u.class_;
	if (cls != objClass) {
		if (cls->super_class == NULL) {
			cls->super_class = GEN_OBJECT;
		}
	}
	logger_info(__FILE__, __LINE__, "register class %s", cls->name);
	//text_printfln("(( %s ))", type_name(tp));
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
//	class_loader_sgload_class_decl(self, iltype, tp, parent);
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
	vector_pop(ilctx->type_vec);
	vector_pop(ilctx->namespace_vec);
	il_context_delete(ilctx);
	//text_printf("loaded %s\n", type_name(tp));
}

static void CLBC_interface(class_loader * self, il_type * iltype, namespace_ * parent) {
	CL_ERROR(self);
	assert(iltype->tag == iltype_interface);
	type* tp = namespace_get_type(parent, iltype->u.interface_->name);
	interface_* inter = NULL;
	//NOTE:後で親関数から渡すようにする
	il_context* ilctx = il_context_new();
	vector_push(ilctx->namespace_vec, parent);
	type_init_generic(tp, iltype->u.interface_->type_parameter_list->length);
	//type_init_generic(tp, iltype->u.interface_->type_parameter_list->length);
	if (tp == NULL) {
		inter = interface_new(iltype->u.interface_->name);
		tp = type_wrap_interface(inter);
		vector_push(ilctx->type_vec, tp);
		type_init_generic(tp, iltype->u.interface_->type_parameter_list->length);
		//type_init_generic(tp, iltype->u.interface_->type_parameter_list->length);
		type_parameter_list_dup(iltype->u.interface_->type_parameter_list, inter->type_parameter_list, ilctx);
		for (int i = 0; i < iltype->u.interface_->extends_list->length; i++) {
			generic_cache* e = (generic_cache*)vector_at(iltype->u.interface_->extends_list, i);
			//インターフェースはインターフェースのみ継承
			generic_type* gtp = generic_cache_gtype(e, parent, ilctx);
			assert(gtp->core_type->tag == type_interface);
			vector_push(inter->impl_list, gtp);
		}
		//場所を設定
		inter->location = parent;
		namespace_add_type(parent, tp);
	} else {
		vector_push(ilctx->type_vec, tp);
		inter = tp->u.interface_;
		//もしネイティブメソッドのために
		//既に登録されていたならここが型変数がNULLになってしまう
		type_parameter_list_dup(iltype->u.class_->type_parameter_list, inter->type_parameter_list, ilctx);
	}
	logger_info(__FILE__, __LINE__, "register interface %s", inter->name);
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
	vector_pop(ilctx->type_vec);
	vector_pop(ilctx->namespace_vec);
	il_context_delete(ilctx);
	//text_printf("loaded %s\n", type_name(tp));
}

static void CLBC_attach_native_method(class_loader* self, il_type* ilclass, class_* classz, il_method* ilmethod, method* me) {
//	native_method.h で、実行時にリンクするようにしたので不要
//	me->u.native_method->ref = native_method_ref_new(class_loader_sgload_debug_native_method);
}

static void CLBC_debug_native_method(method* parent, vm* vm, enviroment* env) {

}