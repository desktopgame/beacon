#include "class_loader_sgload_impl.h"
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
#include "../../env/object.h"
#include "../type_parameter.h"
#include "../parameter.h"
#include "../field.h"
#include "../method.h"
#include "../constructor.h"
#include "class_loader_sgload_helper.h"
#include "../../util/mem.h"
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
static void class_loader_sgload_subImpl(class_loader * self, char * fullPath);
static void class_loader_sgload_namespace_tree(class_loader* self);
static void class_loader_sgload_importImpl(class_loader* self, vector* ilimports, int i);
static void class_loader_sgload_importImplAlready(class_loader* self, class_loader* cll);
static class_loader* class_loader_sgload_importImplNew(class_loader* self, char* fullPath);
static void class_loader_sgload_excecClassDecl(class_loader* self);
static void class_loader_sgload_excecClassImpl(class_loader* self);
static void class_loader_sgload_excecInterfaceDecl(class_loader* self);
static void class_loader_sgload_excecInterfaceImpl(class_loader* self);
static void class_loader_sgload_yield(class_loader* parent, class_loader* target);

void class_loader_sgload_impl(class_loader* self) {
	script_context* ctx = script_context_get_current();
	il_top_level* iltop = self->il_code;
	class_loader_sgload_import(self, self->il_code->import_list);
	class_loader_sgload_namespace_tree(self);

	class_loader_sgload_excecClassDecl(self);
	class_loader_sgload_excecInterfaceDecl(self);
}

void class_loader_sgload_link(class_loader * self) {
	logger_info(__FILE__, __LINE__, "link %s",self->filename);

	class_loader_sgload_import(self, self->il_code->import_list);
	class_loader_sgload_namespace_tree(self);

	class_loader_sgload_excecClassDecl(self);
	class_loader_sgload_excecInterfaceDecl(self);

	class_loader_sgload_excecClassImpl(self);
	class_loader_sgload_excecInterfaceImpl(self);
}

void class_loader_sgload_sub(class_loader * self, char * fullPath) {
	script_context* ctx = script_context_get_current();
	ctx->heap->blocking++;
	class_loader_sgload_subImpl(self, fullPath);
	ctx->heap->blocking--;
}

void class_loader_sgload_import(class_loader* self, vector* ilimports) {
//	TEST(self->import_manager->infoVec->length > 0);
	for (int i = self->import_manager->info_vec->length; i < ilimports->length; i++) {
		class_loader_sgload_importImpl(self, ilimports, i);
	}
}

void class_loader_sgload_namespace_list(class_loader* self, vector* ilnamespace_list, namespace_* parent) {
	//self->link = classlink_resume;
	if (self->error) { return; }
	for (int i = 0; i < ilnamespace_list->length; i++) {
		vector_item e = vector_at(ilnamespace_list, i);
		il_namespace* iln = (il_namespace*)e;
		class_loader_sgload_namespace(self, iln, parent);
	}
}

void class_loader_sgload_namespace(class_loader* self, il_namespace* ilnamespace, namespace_* parent) {
	namespace_* current = NULL;
	if (parent == NULL) {
		current = namespace_create_at_root(ilnamespace->name);
	} else {
		current = namespace_add_namespace(parent, ilnamespace->name);
	}
	class_loader_sgload_namespace_list(self, ilnamespace->namespace_list, current);
	class_loader_sgload_type_list(self, ilnamespace->type_list, current);
}

void class_loader_sgload_type_list(class_loader* self, vector* iltype_list, namespace_* parent) {
	for (int i = 0; i < iltype_list->length; i++) {
		vector_item e = vector_at(iltype_list, i);
		il_type* ilt = (il_type*)e;
		if (ilt->tag == iltype_class) {
			class_loader_sgload_class(self, ilt, parent);
		} else if (ilt->tag == iltype_interface) {
			class_loader_sgload_interface(self, ilt, parent);
		} else if (ilt->tag == iltype_enum) {
			class_loader_sgload_enum(self, ilt, parent);
		}
	}
}

void class_loader_sgload_enum(class_loader * self, il_type * iltype, namespace_ * parent) {
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
		virtual_type_nongeneric_init(&f->vtype, CL_INT->generic_self);
		f->parent = tp;
		class_add_field(cls, f);
	}
}

void class_loader_sgload_class(class_loader* self, il_type* iltype, namespace_* parent) {
	//*
	//既に登録されていたら二重に登録しないように
	//例えば、ネイティブメソッドを登録するために一時的にクラスが登録されている場合がある
	assert(iltype->tag == iltype_class);
	type* tp = namespace_get_type(parent, iltype->u.class_->name);
	class_* cls;
	//FIXME:あとで親関数から渡すようにする
	il_load_cache* cache = il_load_cache_new();
	vector_push(cache->namespace_vec, parent);
	type_init_generic(tp, iltype->u.class_->type_parameter_list->length);
	if (tp == NULL) {
		cls = class_new(iltype->u.class_->name);
		tp = type_wrap_class(cls);
		vector_push(cache->type_vec, tp);
		type_init_generic(tp, iltype->u.class_->type_parameter_list->length);
		type_parameter_list_dup(iltype->u.class_->type_parameter_list, cls->type_parameter_list, cache);
		for (int i = 0; i < iltype->u.class_->extend_list->length; i++) {
			generic_cache* e = (generic_cache*)vector_at(iltype->u.class_->extend_list, i);
			//最初の一つはクラスでもインターフェースでもよい
			if (i == 0) {
				generic_type* gtp = generic_cache_gtype(e, parent, cache);
				assert(gtp != NULL);
				if (gtp->core_type->tag == type_class) {
					cls->super_class = gtp;
				} else if (gtp->core_type->tag == type_interface) {
					vector_push(cls->impl_list, gtp);
				}
			//二つ目以降はインターフェースのみ
			} else {
				generic_type* gtp = generic_cache_gtype(e, parent, cache);
				vector_push(cls->impl_list, gtp);
				assert(gtp->core_type->tag == type_interface);
			}
		}
		//場所を設定
		if (!strcmp(cls->name, "ArrayIterator")) {
			int a = 0;
		}
		cls->location = parent;
		namespace_add_type(parent, tp);
	} else {
		if (!strcmp(tp->u.class_->name, "ArrayIterator")) {
			int a = 0;
		}
		vector_push(cache->type_vec, tp);
		cls = tp->u.class_;
		//もしネイティブメソッドのために
		//既に登録されていたならここが型変数がNULLになってしまう
		type_parameter_list_dup(iltype->u.class_->type_parameter_list, cls->type_parameter_list, cache);
	}
	//デフォルトで親に Object を持つように
	class_* objClass = CL_OBJECT->u.class_;
	if (cls != objClass) {
		if (cls->super_class == NULL) {
			cls->super_class = CL_OBJECT->generic_self;
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
	vector_pop(cache->type_vec);
	vector_pop(cache->namespace_vec);
	il_load_cache_delete(cache);
}

void class_loader_sgload_interface(class_loader * self, il_type * iltype, namespace_ * parent) {
	assert(iltype->tag == iltype_interface);
	type* tp = namespace_get_type(parent, iltype->u.interface_->name);
	interface_* inter = NULL;
	//NOTE:後で親関数から渡すようにする
	il_load_cache* cache = il_load_cache_new();
	vector_push(cache->namespace_vec, parent);
	type_init_generic(tp, iltype->u.interface_->type_parameter_list->length);
	if (tp == NULL) {
		inter = interface_new(iltype->u.interface_->name);
		tp = type_wrap_interface(inter);
		vector_push(cache->type_vec, tp);
		type_init_generic(tp, iltype->u.interface_->type_parameter_list->length);
		type_parameter_list_dup(iltype->u.interface_->type_parameter_list, inter->type_parameter_list, cache);
		for (int i = 0; i < iltype->u.interface_->extends_list->length; i++) {
			generic_cache* e = (generic_cache*)vector_at(iltype->u.interface_->extends_list, i);
			//インターフェースはインターフェースのみ継承
			generic_type* gtp = generic_cache_gtype(e, parent, cache);
			assert(gtp->core_type->tag == type_interface);
			vector_push(inter->impl_list, gtp);
		}
		//場所を設定
		inter->location = parent;
		namespace_add_type(parent, tp);
	} else {
		vector_push(cache->type_vec, tp);
		inter = tp->u.interface_;
		//もしネイティブメソッドのために
		//既に登録されていたならここが型変数がNULLになってしまう
		type_parameter_list_dup(iltype->u.class_->type_parameter_list, inter->type_parameter_list, cache);
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
	vector_pop(cache->type_vec);
	vector_pop(cache->namespace_vec);
	il_load_cache_delete(cache);
}

void class_loader_sgload_attach_native_method(class_loader* self, il_type* ilclass, class_* classz, il_method* ilmethod, method* me) {
//	native_method.h で、実行時にリンクするようにしたので不要
//	me->u.native_method->ref = native_method_ref_new(class_loader_sgload_debug_native_method);
}

void class_loader_sgload_debug_native_method(method* parent, vm* vm, enviroment* env) {

}

void class_loader_sgload_body(class_loader* self, vector* stmt_list, enviroment* dest, namespace_* range, il_load_cache* cache) {
//	enviroment* ret = enviroment_new();
	il_ehandler* eh = il_ehandler_new();
	vector_push(cache->namespace_vec, range);
	for (int i = 0; i < stmt_list->length; i++) {
		vector_item e = vector_at(stmt_list, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_load(s, dest, cache, eh);
	}
	for (int i = 0; i < stmt_list->length; i++) {
		vector_item e = vector_at(stmt_list, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_generate(s, dest, cache);
	}
	vector_pop(cache->namespace_vec);
	il_ehandler_delete(eh);
//	return ret;
}

//private
static void class_loader_sgload_subImpl(class_loader * self, char * fullPath) {
	script_context* ctx = script_context_get_current();
	//text_printf("%s\n", fullPath);
	//そのファイルパスに対応した
	//クラスローダが既に存在するなら無視
	class_loader* cll = tree_map_get(ctx->class_loader_map, fullPath);
	if (cll != NULL) {
		class_loader_sgload_importImplAlready(self, cll);
		return;
		//新たに読みこんだなら親に設定
	} else {
		logger_info(__FILE__, __LINE__, "import new %s", fullPath);
		cll = class_loader_sgload_importImplNew(self, fullPath);
	}
	//そのローダーが破損しているなら
	if (cll->error) {
		class_loader_error(self, cll->error_message);
	}
	//パースをキャンセル
	if (self->error) {
		return;
	}
	cll->filename = text_strdup(fullPath);
	cll->level = (self->level + 1);
	//cll->link = classlink_unlinked;
	char* text = io_read_text(fullPath);
	parser* p = parser_parse_from_source_swap(text, fullPath);
	assert(p->root != NULL);
	assert(!p->fail);
	//パースに失敗
	if (p->fail) {
		//class_loader_errors(cll, "parse failed --- %s", p->source_name);
		MEM_FREE(text);
		parser_pop();
		return;
		//成功
	} else {
		cll->source_code = p->root;
		p->root = NULL;
		MEM_FREE(text);
		parser_pop();
	}
	//ロード
	class_loader_load(cll);
	assert(cll->source_code != NULL);
	assert(cll->il_code != NULL);
}

static void class_loader_sgload_namespace_tree(class_loader* self) {
	if (self->loaded_namespace) {
		return;
	}
	class_loader_sgload_namespace_list(self, self->il_code->namespace_list, NULL);
	self->loaded_namespace = true;
}

static void class_loader_sgload_importImpl(class_loader* self, vector* ilimports, int i) {
	if (i >= ilimports->length ||
	    import_manager_loaded(self->import_manager, i)) {
		return;
	}
	vector_item e = vector_at(ilimports, i);
	il_import* import = (il_import*)e;
	char* withExt = text_concat(import->path, ".signal");
	char* fullPath = io_absolute_path(withExt);
	class_loader_sgload_sub(self, fullPath);
	MEM_FREE(withExt);
	MEM_FREE(fullPath);
}

static void class_loader_sgload_importImplAlready(class_loader* self, class_loader* cll) {
	//self -> cll への参照を与える
	import_info* info = import_manager_import(self->import_manager, cll);
	info->consume = true;
	assert(cll->source_code != NULL);
	assert(cll->il_code != NULL);
	//text_printf("aimport %s\n", cll->filename);
	//そのローダーが破損しているなら
	if (cll->error) {
		class_loader_error(self, cll->error_message);
		return;
	}
	class_loader_sgload_yield(self, cll);
}

static class_loader* class_loader_sgload_importImplNew(class_loader* self, char* fullPath) {
	script_context* ctx = script_context_get_current();
	class_loader* cll = class_loader_new();
	cll->type = content_lib;
	cll->filename = fullPath;
	cll->parent = self;
	//text_printf("nimport %s\n", cll->filename);
	import_info* info = import_manager_import(self->import_manager, cll);
	info->consume = false;
	logger_info(__FILE__, __LINE__, "import put %s", fullPath);
	tree_map_put(ctx->class_loader_map, fullPath, cll);
	return cll;
}

//FIXME:コピペ
static void class_loader_sgload_excecClassDecl(class_loader* self) {
	int count = 0;
	//text_printfln("CLASS_DECL %s ==", self->filename);
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_class_decl || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		class_loader_sgload_class_decl(e->context, e->iltype, e->tp, e->scope);
	}
	if (count > 0) {
		logger_info(__FILE__, __LINE__, "loaded class decl %s", self->filename);
	}
}

static void class_loader_sgload_excecClassImpl(class_loader* self) {
	int count = 0;
	//text_printfln("CLASS_IMPL %s ==", self->filename);
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_class_impl || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		class_loader_sgload_class_impl(e->context, e->iltype, e->tp, e->scope);
	}
	if (count > 0) {
		logger_info(__FILE__, __LINE__, "loaded class impl %s", self->filename);
	}
}

static void class_loader_sgload_excecInterfaceDecl(class_loader* self) {
	int count = 0;
	//text_printfln("INTERFACE_DECL %s ==", self->filename);
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_interface_decl || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		class_loader_sgload_interface_decl(e->context, e->iltype, e->tp, e->scope);
	}
	if(count > 0) {
		logger_info(__FILE__, __LINE__, "loaded interface decl %s", self->filename);
	}
}

static void class_loader_sgload_excecInterfaceImpl(class_loader* self) {
	int count = 0;
	//text_printfln("INTERFACE_IMPL %s ==", self->filename);
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_interface_impl || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		class_loader_sgload_interface_impl(e->context, e->iltype, e->tp, e->scope);
	}
	if(count > 0) {
		logger_info(__FILE__, __LINE__, "loaded interface impl %s", self->filename);
	}
}

static void class_loader_sgload_yield(class_loader* parent, class_loader* target) {
	assert(target->source_code != NULL);
	class_loader_sgload_import(target, target->il_code->import_list);
	class_loader_sgload_namespace_tree(target);

	class_loader_sgload_excecClassDecl(target);
	class_loader_sgload_excecInterfaceDecl(target);
}