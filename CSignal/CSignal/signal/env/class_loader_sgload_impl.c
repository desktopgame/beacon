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
#include "parameter.h"
#include "field.h"
#include "method.h"
#include "constructor.h"
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
		}
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
	//TEST(!strcmp(type->u.class_->name, "Console"));
	class_loader_sgload_fields(self, iltype, tp);
	class_loader_sgload_methods(self, iltype, tp);
	class_loader_sgload_constructors(self, iltype, tp);
//	class_linkall(cls);
//	class_loader_sgload_complete(self, iltype, tp);

	class_loader_sgload_complete_fields(self, iltype, tp);
	class_loader_sgload_complete_methods(self, iltype, tp);
	class_loader_sgload_complete_constructors(self, iltype, tp);
	class_create_vtable(tp->u.class_);
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
	class_loader_sgload_methods(self, iltype, tp);
	class_loader_sgload_complete_methods_impl(self, parent, iltype, tp, iltype->u.interface_->method_list, tp->u.interface_->method_list);
}

void class_loader_sgload_fields(class_loader* self, il_type* iltype, type* tp) {
	assert(iltype->tag == iltype_class);
	class_loader_sgload_fields_impl(self, iltype, tp, iltype->u.class_->field_list);
	class_loader_sgload_fields_impl(self, iltype, tp, iltype->u.class_->sfield_list);
}

void class_loader_sgload_fields_impl(class_loader* self, il_type* iltype, type* tp, vector* ilfields) {
	//class_* cls = tp->u.class_;
	for (int i = 0; i < ilfields->length; i++) {
		vector_item e = vector_at(ilfields, i);
		il_field* ilfield = (il_field*)e;
		field* field = field_new(ilfield->name);
		field->access = ilfield->access;
		field->modifier = ilfield->modifier;
		field->parent = tp;
		//NOTE:ここではフィールドの型を設定しません
		//     class_loader_sgload_complete参照
		//vector_push(classz->field_list, field);
		//class_add_field(cls, field);
		type_add_field(tp, field);
	}
}

void class_loader_sgload_methods(class_loader* self, il_type* iltype, type* tp) {
	assert(iltype->tag == iltype_class ||
		   iltype->tag == iltype_interface);
	//TEST(!strcmp(iltype->u.class_->name, "Console"));
	if (iltype->tag == iltype_class) {
		class_loader_sgload_methods_impl(self, iltype, tp, iltype->u.class_->method_list);
		class_loader_sgload_methods_impl(self, iltype, tp, iltype->u.class_->smethod_list);
	} else if (iltype->tag == iltype_interface) {
		class_loader_sgload_methods_impl(self, iltype, tp, iltype->u.interface_->method_list);
	}
	//TEST(iltype->u.class_->method_list->length != classz->method_list->length);
	//TEST(iltype->u.class_->smethod_list->length != classz->smethod_list->length);
}

void class_loader_sgload_methods_impl(class_loader* self, il_type* iltype, type* tp, vector* ilmethods) {
	//class_* classz = tp->u.class_;
	for (int i = 0; i < ilmethods->length; i++) {
		//メソッド一覧から取り出す
		vector_item e = vector_at(ilmethods, i);
		il_method* ilmethod = (il_method*)e;
		//メソッドから仮引数一覧を取りだす
		vector* ilparams = ilmethod->parameter_list;
		//実行時のメソッド情報を作成する
		method* method = method_new(ilmethod->name);
		vector* parameter_list = method->parameter_list;
		method->type = modifier_is_native(ilmethod->modifier) ? method_type_native : method_type_script;
		method->access = ilmethod->access;
		method->modifier = ilmethod->modifier;
		method->u.script_method = script_method_new();
		method->parent = tp;
		//インターフェースなら
		if (tp->tag == type_interface) {
			method->type = method_type_abstract;
		}
		//ILパラメータを実行時パラメータへ変換
		//NOTE:ここでは戻り値の型,引数の型を設定しません
		//     class_loader_sgload_complete参照
		for (int i = 0; i < ilparams->length; i++) {
			vector_item e = vector_at(ilparams, i);
			il_parameter* ilp = (il_parameter*)e;
			parameter* param = parameter_new(ilp->name);
			vector_push(parameter_list, param);
		}
		//NOTE:クラスの登録が終わったらオペコードを作成する
		type_add_method(tp, method);
	}
}

void class_loader_sgload_constructors(class_loader* self, il_type* iltype, type* tp) {
	class_* classz = tp->u.class_;
	vector* ilcons_list = iltype->u.class_->constructor_list;
	for (int i = 0; i < ilcons_list->length; i++) {
		vector_item e = vector_at(ilcons_list, i);
		il_constructor* ilcons = (il_constructor*)e;
		//メソッドから仮引数一覧を取りだす
		vector* ilparams = ilcons->parameter_list;
		//実行時のメソッド情報を作成する
		constructor* cons = constructor_new();
		vector* parameter_list = cons->parameter_list;
		cons->access = ilcons->access;
		cons->parent = tp;
		//NOTE:ここでは戻り値の型,引数の型を設定しません
		//     class_loader_sgload_complete参照
		for (int i = 0; i < ilparams->length; i++) {
			vector_item e = vector_at(ilparams, i);
			il_parameter* ilp = (il_parameter*)e;
			parameter* param = parameter_new(ilp->name);
			vector_push(parameter_list, param);
		}
		//vector_push(classz->constructor_list, cons);
		class_add_constructor(classz, cons);
	}
}

void class_loader_sgload_complete_fields(class_loader* self, il_type* iltype, type* tp) {
	namespace_* scope = tp->location;
	assert(tp->tag == type_class);
	class_* classz = tp->u.class_;
	vector* fields = classz->field_list;
	if (iltype->tag == iltype_interface) {
		return;
	}
	class_loader_sgload_complete_fields_impl(self, scope, iltype->u.class_->field_list, classz->field_list);
	class_loader_sgload_complete_fields_impl(self, scope, iltype->u.class_->sfield_list, classz->sfield_list);
}

void class_loader_sgload_complete_fields_impl(class_loader* self, namespace_* scope, vector* ilfields, vector* sgfields) {
//	namespace_* scope = classz->location;
	for (int i = 0; i < sgfields->length; i++) {
		vector_item e = vector_at(sgfields, i);
		field* fi = (field*)e;
		//FIXME:ILフィールドと実行時フィールドのインデックスが同じなのでとりあえず動く
		il_field* ilfield = ((il_field*)vector_at(ilfields, i));
		fi->type = import_manager_resolve(self->import_manager, scope, ilfield->fqcn);
	}
}

void class_loader_sgload_complete_methods(class_loader* self, il_type* iltype, type* tp) {
	assert(tp->tag == type_class);
	class_* classz = tp->u.class_;
	namespace_* scope = classz->location;
	class_loader_sgload_complete_methods_impl(self, scope, iltype, tp, il_type_method_vec(iltype), classz->method_list);
	class_loader_sgload_complete_methods_impl(self, scope, iltype, tp, il_type_smethod_vec(iltype), classz->smethod_list);
}

void class_loader_sgload_complete_methods_impl(class_loader* self, namespace_* scope, il_type* iltype, type* tp, vector* ilmethods, vector* sgmethods) {
	//assert(tp->tag == type_class);
	//class_* classz = tp->u.class_;
	for (int i = 0; i < sgmethods->length; i++) {
		vector_item e = vector_at(sgmethods, i);
		method* me = (method*)e;
		il_method* ilmethod = (il_method*)vector_at(ilmethods, i);
		//戻り値と仮引数に型を設定
		me->return_type = import_manager_resolve(
			self->import_manager,
			scope,
			ilmethod->return_fqcn
			);
		//TEST(!strcmp(me->name, "main"));
		class_loader_sgload_params(self, scope, ilmethod->parameter_list, me->parameter_list);
		//ネイティブメソッドならオペコードは不要
		if (me->type == method_type_native ||
			me->type == method_type_abstract) {
			//class_loader_sgload_attach_native_method(self, iltype, classz, ilmethod, me);
			continue;
		}
		//オペコードを作成
		//FIXME:ILメソッドと実行時メソッドのインデックスが同じなのでとりあえず動く
		//まずは仮引数の一覧にインデックスを割り振る
		enviroment* env = enviroment_new();
		vector_push(env->class_vec, tp);
		env->context_cll = self;
		for (int i = 0; i < ilmethod->parameter_list->length; i++) {
			il_parameter* ilparam = (il_parameter*)vector_at(ilmethod->parameter_list, i);
			symbol_table_entry(
				env->sym_table,
				fqcn_type(ilparam->fqcn, scope),
				ilparam->name
				);
			//実引数を保存
			//0番目は this のために開けておく
			opcode_buf_add(env->buf, (vector_item)op_store);
			opcode_buf_add(env->buf, (vector_item)(i + 1));
		}
		//インスタンスメソッドなら
		//0番目を this で埋める
		if (!modifier_is_static(me->modifier)) {
			opcode_buf_add(env->buf, (vector_item)op_store);
			opcode_buf_add(env->buf, (vector_item)0);
		}
		//NOTE:ここなら名前空間を設定出来る		
		class_loader_sgload_body(self, ilmethod->statement_list, env, scope);
		me->u.script_method->env = env;
		vector_pop(env->class_vec);
	}
}

void class_loader_sgload_complete_constructors(class_loader* self, il_type* iltype, type* tp) {
	assert(tp->tag == type_class);
	class_* classz = tp->u.class_;
	namespace_* scope = classz->location;
	vector* constructors = classz->constructor_list;
	if (iltype->tag != iltype_class) {
		return;
	}
	//既に登録されたが、
	//オペコードが空っぽになっているコンストラクタの一覧
	for (int i = 0; i < constructors->length; i++) {
		vector_item e = vector_at(constructors, i);
		constructor* cons = (constructor*)e;
		il_constructor* ilcons = (il_constructor*)vector_at(iltype->u.class_->constructor_list, i);
		//仮引数に型を設定する
		class_loader_sgload_params(self, scope, ilcons->parameter_list, cons->parameter_list);
		//まずは仮引数の一覧にインデックスを割り振る
		enviroment* env = enviroment_new();
		vector_push(env->class_vec, tp);
		env->context_cll = self;
		for (int i = 0; i < cons->parameter_list->length; i++) {
			il_parameter* ilparam = (il_parameter*)vector_at(ilcons->parameter_list, i);
			symbol_table_entry(
				env->sym_table,
				fqcn_type(ilparam->fqcn, scope),
				ilparam->name
				);
			//実引数を保存
			//0番目は this のために開けておく
			opcode_buf_add(env->buf, op_store);
			opcode_buf_add(env->buf, (i + 1));
		}
		class_loader_sgload_chain(self, iltype, tp, ilcons, ilcons->chain, env);
		//NOTE:ここなら名前空間を設定出来る		
		class_loader_sgload_body(self, ilcons->statement_list, env, scope);
		cons->env = env;
		vector_pop(env->class_vec);
	}
}

void class_loader_sgload_params(class_loader* self, namespace_* scope, vector* param_list, vector* sg_param_list) {
//	for (int j = 0; j < ilmethod->parameter_list->length; j++) {
	for (int j = 0; j < param_list->length; j++) {
		//vector_item d = vector_at(ilmethod->parameter_list, j);
		vector_item e = vector_at(param_list, j);
		il_parameter* ilparam = (il_parameter*)e;
		//FIXME:ILパラメータと実行時パラメータのインデックスが同じなのでとりあえず動く
		//parameter* mep = (parameter*)vector_at(me->parameter_list, j);
		parameter* mep = (parameter*)vector_at(sg_param_list, j);
		type* c = import_manager_resolve(
			self->import_manager,
			scope,
			ilparam->fqcn
			);
		//TEST(c == NULL);
		mep->type = c;
	}
}

void class_loader_sgload_chain(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, il_constructor_chain* ilchain, enviroment* env) {
	//親クラスがないなら作成
	class_* classz = tp->u.class_;
	if (classz->super_class == NULL &&
		ilcons->chain == NULL) {
		opcode_buf_add(env->buf, op_new_object);
	}
	if (ilcons->chain == NULL) {
		opcode_buf_add(env->buf, op_alloc_field);
		opcode_buf_add(env->buf, tp->absoluteIndex);
		return;
	}
	//チェインコンストラクタの実引数をプッシュ
	il_constructor_chain* chain = ilcons->chain;
	for (int i = 0; i < chain->argument_list->length; i++) {
		il_argument* ilarg = (il_argument*)vector_at(chain->argument_list, i);
		il_factor_generate(ilarg->factor, env);
	}
	//連鎖先のコンストラクタを検索する
	constructor* chainTarget = NULL;
	int temp = 0;
	if (chain->type == chain_type_this) {
		chainTarget = class_find_constructor(classz, chain->argument_list, env, &temp);
		opcode_buf_add(env->buf, op_chain_this);
		opcode_buf_add(env->buf, tp->absoluteIndex);
	} else if (chain->type == chain_type_super) {
		chainTarget = class_find_constructor(classz->super_class, chain->argument_list, env, &temp);
		opcode_buf_add(env->buf, op_chain_super);
		opcode_buf_add(env->buf, classz->super_class->classIndex);
	}
	chain->c = chainTarget;
	chain->constructorIndex = temp;
	opcode_buf_add(env->buf, temp);
	//親クラスへのチェインなら即座にフィールドを確保
	opcode_buf_add(env->buf, op_alloc_field);
	opcode_buf_add(env->buf, tp->absoluteIndex);
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
