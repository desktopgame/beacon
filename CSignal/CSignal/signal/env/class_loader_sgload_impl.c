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
void class_loader_sgload_impl(class_loader* self) {
	script_context* ctx = script_context_get_current();
	il_top_level* iltop = self->il_code;
	class_loader_sgload_import(self, self->il_code->import_list);
	class_loader_sgload_namespace_list(self, self->il_code->namespace_list, NULL);
}

void class_loader_sgload_import(class_loader* self, vector* ilimports) {
	script_context* ctx = script_context_get_current();
	for (int i = 0; i < ilimports->length; i++) {
		vector_item e = vector_at(ilimports, i);
		il_import* import = (il_import*)e;
		char* withExt = text_concat(import->path, ".signal");
		char* fullPath = io_absolute_path(withExt);
		//printf("%s\n", fullPath);
		//そのファイルパスに対応した
		//クラスローダが既に存在するなら無視
		class_loader* cll = tree_map_get(ctx->classLoaderMap, fullPath);
		if (cll != NULL) {
			cll->ref_count++;
			import_manager_import(self->import_manager, cll);
			//そのローダーが破損しているなら
			if (cll->error) {
				class_loader_error(self, cll->errorMessage);
			}
			continue;
		//新たに読みこんだなら親に設定
		} else {
			cll = class_loader_new();
			cll->ref_count++;
			cll->parent = self;
			cll->type = content_lib;
			import_manager_import(self->import_manager, cll);
			tree_map_put(ctx->classLoaderMap, fullPath, cll);
		}
		//そのローダーが破損しているなら
		if (cll->error) {
			class_loader_error(self, cll->errorMessage);
		}
		//パースをキャンセル
		if (self->error) {
			return;
		}
		//パース
		char* text = io_read_text(fullPath);
		parser* p = parser_parse_from_source_swap(text, fullPath);
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
		MEM_FREE(withExt);
		MEM_FREE(fullPath);
	}
}

void class_loader_sgload_namespace_list(class_loader* self, vector* ilnamespace_list, namespace_* parent) {
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
	class_loader_sgload_members(self, iltype, tp, parent);
	///*/
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
	class_loader_sgload_methods(self, iltype, tp, parent);
	class_loader_sgload_complete_methods_impl(self, parent, iltype, tp, iltype->u.interface_->method_list, tp->u.interface_->method_list);
	interface_create_vtable(inter);
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
