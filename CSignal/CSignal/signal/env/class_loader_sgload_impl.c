#include "class_loader_sgload_impl.h"
#include "script_context.h"
#include "../util/text.h"
#include "../util/io.h"
#include "../parse/parser.h"
#include "../il/il_type_impl.h"
#include "../il/il_import.h"
#include "../il/il_parameter.h"
#include "../il/il_argument.h"
#include "../il/il_field.h"
#include "../il/il_method.h"
#include "../il/il_constructor.h"
#include "../il/il_stmt_interface.h"
#include "../env/object.h"
#include "parameter.h"
#include "field.h"
#include "method.h"
#include "constructor.h"
#include "class_loader_sgload_helper.h"
#include "../util/mem.h"
#include <assert.h>
//
//sgload
//
#include "type_cache.h"
#include <string.h>
#include "import_info.h"
#include "../util/logger.h"
//proto
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

//	class_loader_sgload_excecClassImpl(self);
//	class_loader_sgload_excecInterfaceImpl(self);
}

void class_loader_sgload_link(class_loader * self) {
	sg_info(__FILE__, __LINE__, "link %s",self->filename);

	class_loader_sgload_import(self, self->il_code->import_list);
	class_loader_sgload_namespace_tree(self);

	class_loader_sgload_excecClassDecl(self);
	class_loader_sgload_excecInterfaceDecl(self);

	class_loader_sgload_excecClassImpl(self);
	class_loader_sgload_excecInterfaceImpl(self);
}

void class_loader_sgload_sub(class_loader * self, char * fullPath) {
	script_context* ctx = script_context_get_current();
	//text_printf("%s\n", fullPath);
	//そのファイルパスに対応した
	//クラスローダが既に存在するなら無視
	class_loader* cll = tree_map_get(ctx->classLoaderMap, fullPath);
	if (cll != NULL) {
		class_loader_sgload_importImplAlready(self, cll);
		return;
		//新たに読みこんだなら親に設定
	} else {
		sg_info(__FILE__, __LINE__, "import new %s", fullPath);
		cll = class_loader_sgload_importImplNew(self, fullPath);
	}
	//そのローダーが破損しているなら
	if (cll->error) {
		class_loader_error(self, cll->errorMessage);
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

void class_loader_sgload_import(class_loader* self, vector* ilimports) {
	for (int i = 0; i < ilimports->length; i++) {
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
	sg_info(__FILE__, __LINE__, "register enum %s", cls->name);
	//全ての列挙子を public static final フィールドとして追加
	for (int i = 0; i < ilenum->item_vec->length; i++) {
		char* str = (char*)vector_at(ilenum->item_vec, i);
		field* f = field_new(str);
		f->modifier = modifier_static;
		f->access = access_public;
		f->static_value = object_int_new(i);
		f->type = CL_INT;
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
//	class_* cls = namespace_get_type(parent, iltype->u.class_->name);
	if (tp == NULL) {
		cls = class_new(iltype->u.class_->name);
		for (int i = 0; i < iltype->u.class_->extend_list->length; i++) {
			fqcn_cache* e = (fqcn_cache*)vector_at(iltype->u.class_->extend_list, i);
			//最初の一つはクラスでもインターフェースでもよい
			if (i == 0) {
				class_* c = fqcn_class(e, parent);
				if (c != NULL) {
					cls->super_class = c;
				} else {
					//クラスではなかったのでインターフェースとして扱う
					interface_* inter = fqcn_interface(e, parent);
					assert(inter != NULL);
					vector_push(cls->impl_list, inter);
				}
			//二つ目以降はインターフェースのみ
			} else {
				interface_* inter = fqcn_interface(e, parent);
				assert(inter != NULL);
				vector_push(cls->impl_list, inter);
			}
		}
//		if (iltype->u.class_->super != NULL) {
//			cls->super_class = fqcn_class(iltype->u.class_->super, parent);
//		}
		cls->location = parent;
		tp = type_wrap_class(cls);
		namespace_add_type(parent, tp);
	} else {
		cls = tp->u.class_;
	}
	//デフォルトで親に Object を持つように
	class_* objClass = CL_OBJECT->u.class_;
	if (cls != objClass) {
		if (cls->super_class == NULL) {
			cls->super_class = objClass;
		}
	}
	sg_info(__FILE__, __LINE__, "register class %s", cls->name);
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
	vector_push(self->type_cacheVec, tc);
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
	vector_push(self->type_cacheVec, mtc);
}

void class_loader_sgload_interface(class_loader * self, il_type * iltype, namespace_ * parent) {
	assert(iltype->tag == iltype_interface);
	type* tp = namespace_get_type(parent, iltype->u.interface_->name);
	interface_* inter = NULL;
	if (tp == NULL) {
		inter = interface_new(iltype->u.interface_->name);
		for (int i = 0; i < iltype->u.interface_->extends_list->length; i++) {
			fqcn_cache* e = (fqcn_cache*)vector_at(iltype->u.interface_->extends_list, i);
			//インターフェースはインターフェースのみ継承
			interface_* interI = fqcn_interface(e, parent);
			assert(interI != NULL);
			vector_push(inter->impl_list, interI);
		}
		inter->location = parent;
		tp = type_wrap_interface(inter);
		namespace_add_type(parent, tp);
	} else {
		inter = tp->u.interface_;
	}
	sg_info(log_info, __FILE__, __LINE__, "register interface %s", inter->name);
	//宣言のロードを予約
	type_cache* tc = type_cache_init(
		type_cache_new(),
		self,
		iltype,
		tp,
		parent,
		cachekind_interface_decl
	);
	vector_push(self->type_cacheVec, tc);
	//実装のロードを予約
	type_cache* mtc = type_cache_init(
		type_cache_new(),
		self,
		iltype,
		tp,
		parent,
		cachekind_interface_impl
	);
	vector_push(self->type_cacheVec, mtc);
}

void class_loader_sgload_attach_native_method(class_loader* self, il_type* ilclass, class_* classz, il_method* ilmethod, method* me) {
//	native_method.h で、実行時にリンクするようにしたので不要
//	me->u.native_method->ref = native_method_ref_new(class_loader_sgload_debug_native_method);
}

void class_loader_sgload_debug_native_method(method* parent, vm* vm, enviroment* env) {

}

void class_loader_sgload_body(class_loader* self, vector* stmt_list, enviroment* dest, namespace_* range) {
//	enviroment* ret = enviroment_new();
	il_ehandler* eh = il_ehandler_new();
	vector_push(dest->namespace_vec, range);
	for (int i = 0; i < stmt_list->length; i++) {
		vector_item e = vector_at(stmt_list, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_load(s, dest, eh);
	}
	for (int i = 0; i < stmt_list->length; i++) {
		vector_item e = vector_at(stmt_list, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_generate(s, dest);
	}
	vector_pop(dest->namespace_vec);
	il_ehandler_delete(eh);
//	return ret;
}

//private
static void class_loader_sgload_namespace_tree(class_loader* self) {
	if (self->loadedNamespace) {
		return;
	}
	class_loader_sgload_namespace_list(self, self->il_code->namespace_list, NULL);
	self->loadedNamespace = true;
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
		class_loader_error(self, cll->errorMessage);
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
	info->consume = true;
	sg_info(__FILE__, __LINE__, "import put %s", fullPath);
	tree_map_put(ctx->classLoaderMap, fullPath, cll);
	return cll;
}

//FIXME:コピペ
static void class_loader_sgload_excecClassDecl(class_loader* self) {
	sg_info(__FILE__, __LINE__, "loaded class decl %s", self->filename);
	//text_printfln("CLASS_DECL %s ==", self->filename);
	for (int i = 0; i < self->type_cacheVec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cacheVec, i);
		if (e->kind != cachekind_class_decl || e->consume) {
			continue;
		}
		e->consume = true;
		class_loader_sgload_class_decl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void class_loader_sgload_excecClassImpl(class_loader* self) {
	sg_info(__FILE__, __LINE__, "loaded class impl %s", self->filename);
	//text_printfln("CLASS_IMPL %s ==", self->filename);
	for (int i = 0; i < self->type_cacheVec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cacheVec, i);
		if (e->kind != cachekind_class_impl || e->consume) {
			continue;
		}
		e->consume = true;
		class_loader_sgload_class_impl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void class_loader_sgload_excecInterfaceDecl(class_loader* self) {
	sg_info(__FILE__, __LINE__, "loaded interface decl %s", self->filename);
	//text_printfln("INTERFACE_DECL %s ==", self->filename);
	for (int i = 0; i < self->type_cacheVec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cacheVec, i);
		if (e->kind != cachekind_interface_decl || e->consume) {
			continue;
		}
		e->consume = true;
		class_loader_sgload_interface_decl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void class_loader_sgload_excecInterfaceImpl(class_loader* self) {
	sg_info(__FILE__, __LINE__, "loaded interface impl %s", self->filename);
	//text_printfln("INTERFACE_IMPL %s ==", self->filename);
	for (int i = 0; i < self->type_cacheVec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cacheVec, i);
		if (e->kind != cachekind_interface_impl || e->consume) {
			continue;
		}
		e->consume = true;
		class_loader_sgload_interface_impl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void class_loader_sgload_yield(class_loader* parent, class_loader* target) {
	if (target->source_code == NULL) {

	}
	class_loader_sgload_import(target, target->il_code->import_list);
	class_loader_sgload_namespace_tree(target);

	class_loader_sgload_excecClassDecl(target);
	class_loader_sgload_excecInterfaceDecl(target);
}