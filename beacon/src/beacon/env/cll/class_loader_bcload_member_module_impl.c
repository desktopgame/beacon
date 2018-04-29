#include "class_loader_bcload_member_module_impl.h"
#include "../../il/il_type_impl.h"
#include "../../il/il_field.h"
#include "../../il/il_method.h"
#include "../../il/il_constructor.h"
#include "../../il/il_constructor_chain.h"
#include "../../il/il_parameter.h"
#include "../../il/il_argument.h"
#include "../../il/il_stmt_interface.h"
#include "../../env/type_impl.h"
#include "../../env/field.h"
#include "../../env/method.h"
#include "../../env/constructor.h"
#include "../../env/parameter.h"
#include "../../env/type_parameter.h"
#include "../../util/xassert.h"
#include <assert.h>

//proto
static void CLBC_parameter_list(class_loader* self, namespace_* scope, vector* param_list, vector* sg_param_liste, il_context* ilctx);

static void CLBC_chain(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, il_constructor_chain* ilchain, enviroment* env);
static void CLBC_chain_root(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, il_constructor_chain* ilchain, enviroment* env);
static void CLBC_chain_auto(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, il_constructor_chain* ilchain, enviroment* env);
static void CLBC_chain_super(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, il_constructor_chain* ilchain, enviroment* env);

void CLBC_fields_decl(class_loader* self, il_type* iltype, type* tp, vector* ilfields, namespace_* scope) {
	//class_* cls = tp->u.class_;
	CL_ERROR(self);
	il_context* ilctx = il_context_new();
	vector_push(ilctx->namespace_vec, scope);
	vector_push(ilctx->type_vec, tp);
	for (int i = 0; i < ilfields->length; i++) {
		vector_item e = vector_at(ilfields, i);
		il_field* ilfield = (il_field*)e;
		field* field = field_new(ilfield->name);
		//XSTREQ(ilfield->name, "charArray");
		field->access = ilfield->access;
		field->modifier = ilfield->modifier;
		field->parent = tp;
//		import_manager_resolve(self->import_manager, scope, ilfield->fqcn, ilctx, &field->vtype);
		//NOTE:ここではフィールドの型を設定しません
		//     class_loader_sgload_complete参照
		//vector_push(classz->field_list, field);
		//class_add_field(cls, field);
		type_add_field(tp, field);
	}
	vector_pop(ilctx->namespace_vec);
	vector_pop(ilctx->type_vec);
	il_context_delete(ilctx);
}

void CLBC_fields_impl(class_loader* self, namespace_* scope, vector* ilfields, vector* sgfields) {
	CL_ERROR(self);
	//	namespace_* scope = classz->location;
	il_context* ilctx = il_context_new();
	for (int i = 0; i < sgfields->length; i++) {
		vector_item e = vector_at(sgfields, i);
		field* fi = (field*)e;

		vector_push(ilctx->type_vec, fi->parent);
		//FIXME:ILフィールドと実行時フィールドのインデックスが同じなのでとりあえず動く
		il_field* ilfield = ((il_field*)vector_at(ilfields, i));
	//	import_manager_resolve(self->import_manager, scope, ilfield->fqcn, ilctx, &fi->vtype);
		vector_pop(ilctx->type_vec);
	}
	il_context_delete(ilctx);
}

void CLBC_methods_decl(class_loader* self, il_type* iltype, type* tp, vector* ilmethods, namespace_* scope) {
	CL_ERROR(self);
	il_context* ilctx = il_context_new();
	vector_push(ilctx->namespace_vec, scope);
	vector_push(ilctx->type_vec, tp);
	//class_* classz = tp->u.class_;
	for (int i = 0; i < ilmethods->length; i++) {
		//メソッド一覧から取り出す
		vector_item e = vector_at(ilmethods, i);
		il_method* ilmethod = (il_method*)e;
		//メソッドから仮引数一覧を取りだす
		vector* ilparams = ilmethod->parameter_list;
		//実行時のメソッド情報を作成する
		method* method = method_new(ilmethod->name);
		//XSTREQ(ilmethod->name, "sub");
		vector_push(ilctx->method_vec, method);
		vector* parameter_list = method->parameter_list;
		method->type = modifier_is_native(ilmethod->modifier) ? method_type_native : method_type_script;
		method->access = ilmethod->access;
		method->modifier = ilmethod->modifier;
		type_parameter_list_dup(ilmethod->type_parameter_list, method->type_parameter_list, ilctx);
		//インターフェースなら空
		if (tp->tag == type_interface) {
			method->type = method_type_abstract;
			method->u.script_method = NULL;
		} else {
			method->u.script_method = script_method_new();
		}
		method->parent = tp;
	//	import_manager_resolve(self->import_manager, scope, ilmethod->return_fqcn, ilctx, &method->return_vtype);
		//ILパラメータを実行時パラメータへ変換
		//NOTE:ここでは戻り値の型,引数の型を設定しません
		//     class_loader_sgload_complete参照
		for (int i = 0; i < ilparams->length; i++) {
			vector_item e = vector_at(ilparams, i);
			il_parameter* ilp = (il_parameter*)e;
			parameter* param = parameter_new(ilp->name);
			vector_push(parameter_list, param);
		}
		//XSTREQ(method->name, "copy");
		//XSTREQ(method->name, "copy");
		CLBC_parameter_list(self, scope, ilmethod->parameter_list, method->parameter_list, ilctx);
		//NOTE:クラスの登録が終わったらオペコードを作成する
		type_add_method(tp, method);
		vector_pop(ilctx->method_vec);
	}
	vector_pop(ilctx->type_vec);
	vector_pop(ilctx->namespace_vec);
	il_context_delete(ilctx);
}

void CLBC_methods_impl(class_loader* self, namespace_* scope, il_type* iltype, type* tp, vector* ilmethods, vector* sgmethods) {
	//assert(tp->tag == type_class);
	//class_* classz = tp->u.class_;
	CL_ERROR(self);
	il_context* ilctx = il_context_new();
	for (int i = 0; i < sgmethods->length; i++) {
		vector_item e = vector_at(sgmethods, i);
		method* me = (method*)e;
		il_method* ilmethod = (il_method*)vector_at(ilmethods, i);
		//TEST(!strcmp(me->name, "main"));
		//class_loader_sgload_params(self, scope, ilmethod->parameter_list, me->parameter_list);
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
		vector_push(ilctx->type_vec, tp);
		env->context_ref = self;
		for (int i = 0; i < ilmethod->parameter_list->length; i++) {
			il_parameter* ilparam = (il_parameter*)vector_at(ilmethod->parameter_list, i);
			symbol_table_entry(
				env->sym_table,
				generic_cache_gtype(ilparam->fqcn, scope, ilctx),
				ilparam->name
			);
			//text_printf("%s ", ilparam->name);
			//実引数を保存
			//0番目は this のために開けておく
			opcode_buf_add(env->buf, (vector_item)op_store);
			opcode_buf_add(env->buf, (vector_item)(i + 1));
		}
		//text_printf("\n");
		//インスタンスメソッドなら
		//0番目を this で埋める
		if (!modifier_is_static(me->modifier)) {
			opcode_buf_add(env->buf, (vector_item)op_store);
			opcode_buf_add(env->buf, (vector_item)0);
		}
		//NOTE:ここなら名前空間を設定出来る
		vector_push(ilctx->method_vec, me);
		CLBC_body(self, ilmethod->statement_list, env, scope, ilctx);
		me->u.script_method->env = env;
		vector_pop(ilctx->method_vec);
		vector_pop(ilctx->type_vec);
	}
	il_context_delete(ilctx);
}


void CLBC_ctor_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope) {
	CL_ERROR(self);
	class_* classz = tp->u.class_;
	vector* ilcons_list = iltype->u.class_->constructor_list;
	il_context* ilctx = il_context_new();
	vector_push(ilctx->type_vec, tp);
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
		CLBC_parameter_list(self, scope, ilcons->parameter_list, cons->parameter_list, ilctx);
		//vector_push(classz->constructor_list, cons);
		class_add_constructor(classz, cons);
	}
	vector_pop(ilctx->type_vec);
	il_context_delete(ilctx);
}

void CLBC_ctor_impl(class_loader* self, il_type* iltype, type* tp) {
	CL_ERROR(self);
	assert(tp->tag == type_class);
	class_* classz = tp->u.class_;
	namespace_* scope = classz->location;
	vector* constructors = classz->constructor_list;
	if (iltype->tag != iltype_class) {
		return;
	}
	//既に登録されたが、
	//オペコードが空っぽになっているコンストラクタの一覧

	il_context* ilctx = il_context_new();
	for (int i = 0; i < constructors->length; i++) {
		vector_item e = vector_at(constructors, i);
		constructor* cons = (constructor*)e;
		il_constructor* ilcons = (il_constructor*)vector_at(iltype->u.class_->constructor_list, i);
		//仮引数に型を設定する
		//class_loader_sgload_params(self, scope, ilcons->parameter_list, cons->parameter_list);
		//まずは仮引数の一覧にインデックスを割り振る
		enviroment* env = enviroment_new();
		vector_push(ilctx->type_vec, tp);
		env->context_ref = self;
		for (int i = 0; i < cons->parameter_list->length; i++) {
			il_parameter* ilparam = (il_parameter*)vector_at(ilcons->parameter_list, i);
			symbol_table_entry(
				env->sym_table,
				generic_cache_gtype(ilparam->fqcn, scope, ilctx),
				ilparam->name
			);
			//実引数を保存
			//0番目は this のために開けておく
			opcode_buf_add(env->buf, op_store);
			opcode_buf_add(env->buf, (i + 1));
		}
		CLBC_chain(self, iltype, tp, ilcons, ilcons->chain, env);
		//NOTE:ここなら名前空間を設定出来る
		CLBC_body(self, ilcons->statement_list, env, scope, ilctx);
		cons->env = env;
		vector_pop(ilctx->type_vec);
	}
	il_context_delete(ilctx);
}

void CLBC_body(class_loader* self, vector* stmt_list, enviroment* dest, namespace_* range, il_context* ilctx) {
	//	enviroment* ret = enviroment_new();
	CL_ERROR(self);
	vector_push(ilctx->namespace_vec, range);
	il_error_enter();
	//まずは全てのステートメントを読み込む
	for (int i = 0; i < stmt_list->length; i++) {
		if(il_error_panic()) {
			self->error = true;
			break;
		}
		vector_item e = vector_at(stmt_list, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_load(s, dest, ilctx);
	}
	//オペコードを生成
	for (int i = 0; i < stmt_list->length; i++) {
		if(il_error_panic()) {
			self->error = true;
			break;
		}
		vector_item e = vector_at(stmt_list, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_generate(s, dest, ilctx);
	}
	il_error_exit();
	vector_pop(ilctx->namespace_vec);
//	return ret;
}

//private
static void CLBC_parameter_list(class_loader* self, namespace_* scope, vector* param_list, vector* sg_param_list, il_context* ilctx) {
	//	for (int j = 0; j < ilmethod->parameter_list->length; j++) {
	for (int j = 0; j < param_list->length; j++) {
		//vector_item d = vector_at(ilmethod->parameter_list, j);
		vector_item e = vector_at(param_list, j);
		il_parameter* ilparam = (il_parameter*)e;
		//FIXME:ILパラメータと実行時パラメータのインデックスが同じなのでとりあえず動く
		//parameter* mep = (parameter*)vector_at(me->parameter_list, j);
		parameter* mep = (parameter*)vector_at(sg_param_list, j);
		/*
		import_manager_resolve(
			self->import_manager,
			scope,
			ilparam->fqcn,
			ilctx,
			&mep->vtype
		);
		*/
	}
}


static void CLBC_chain(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, il_constructor_chain* ilchain, enviroment* env) {
	//親クラスがないなら作成
	class_* classz = tp->u.class_;
	if (classz->super_class == NULL &&
		ilcons->chain == NULL) {
		CLBC_chain_root(self, iltype, tp, ilcons, ilchain, env);
		return;
	}
	//親クラスがあるのに連鎖がない
	if (classz->super_class != NULL &&
		ilcons->chain == NULL) {
		CLBC_chain_auto(self, iltype, tp, ilcons, ilchain, env);
		return;
	}
	CLBC_chain_super(self, iltype, tp, ilcons, ilchain, env);
}

static void CLBC_chain_root(class_loader * self, il_type * iltype, type * tp, il_constructor * ilcons, il_constructor_chain * ilchain, enviroment * env) {
	opcode_buf_add(env->buf, (vector_item)op_new_object);
	opcode_buf_add(env->buf, (vector_item)op_alloc_field);
	opcode_buf_add(env->buf, (vector_item)tp->absolute_index);
}

static void CLBC_chain_auto(class_loader * self, il_type * iltype, type * tp, il_constructor * ilcons, il_constructor_chain * ilchain, enviroment * env) {
	class_* classz = tp->u.class_;
	int emptyTemp = 0;
	constructor* emptyTarget = class_find_empty_constructor(classz->super_class->core_type->u.class_, env, NULL, &emptyTemp);
	//連鎖を明示的に書いていないのに、
	//親クラスにも空のコンストラクタが存在しない=エラー
	//(この場合自動的にチェインコンストラクタを補うことが出来ないため。)
	assert((emptyTarget != NULL));
	//空のコンストラクタを見つけることが出来たので、
	//自動的にそれへ連鎖するチェインをおぎなう
	il_constructor_chain* ch_empty = il_constructor_chain_new();
	ch_empty->c = emptyTarget;
	ch_empty->constructor_index = emptyTemp;
	ch_empty->type = ast_constructor_chain_super;
	ilcons->chain = ch_empty;
	//親クラスへ連鎖
	opcode_buf_add(env->buf, (vector_item)op_chain_super);
	opcode_buf_add(env->buf, (vector_item)classz->super_class->core_type->u.class_->classIndex);
	opcode_buf_add(env->buf, (vector_item)emptyTemp);
	//このクラスのフィールドを確保
	opcode_buf_add(env->buf, (vector_item)op_alloc_field);
	opcode_buf_add(env->buf, (vector_item)tp->absolute_index);
}

static void CLBC_chain_super(class_loader * self, il_type * iltype, type * tp, il_constructor * ilcons, il_constructor_chain * ilchain, enviroment * env) {
	class_* classz = tp->u.class_;
	//チェインコンストラクタの実引数をプッシュ
	il_context* ilctx = il_context_new();
	il_constructor_chain* chain = ilcons->chain;
	for (int i = 0; i < chain->argument_list->length; i++) {
		il_argument* ilarg = (il_argument*)vector_at(chain->argument_list, i);
		il_factor_generate(ilarg->factor, env, ilctx);
	}
	//連鎖先のコンストラクタを検索する
	constructor* chainTarget = NULL;
	int temp = 0;
	if (chain->type == chain_type_this) {
		chainTarget = class_find_constructor(classz, chain->argument_list, env, ilctx, &temp);
		opcode_buf_add(env->buf, (vector_item)op_chain_this);
		opcode_buf_add(env->buf, (vector_item)(tp->absolute_index));
	} else if (chain->type == chain_type_super) {
		chainTarget = class_find_constructor(classz->super_class, chain->argument_list, env, ilctx, &temp);
		opcode_buf_add(env->buf, op_chain_super);
		opcode_buf_add(env->buf, classz->super_class->core_type->u.class_->classIndex);
	}
	chain->c = chainTarget;
	chain->constructor_index = temp;
	opcode_buf_add(env->buf, (vector_item)temp);
	//親クラスへのチェインなら即座にフィールドを確保
	opcode_buf_add(env->buf, (vector_item)op_alloc_field);
	opcode_buf_add(env->buf, (vector_item)tp->absolute_index);
	il_context_delete(ilctx);
}
