#include "class_loader_bcload_member_module_impl.h"
#include "../../il/il_type_impl.h"
#include "../../il/il_field.h"
#include "../../il/il_property.h"
#include "../../il/il_method.h"
#include "../../il/il_constructor.h"
#include "../../il/il_constructor_chain.h"
#include "../../il/il_parameter.h"
#include "../../il/il_argument.h"
#include "../../il/il_stmt_interface.h"
#include "../../il/il_operator_overload.h"
#include "../../env/type_impl.h"
#include "../../env/object.h"
#include "../../env/heap.h"
#include "../../env/field.h"
#include "../../env/property.h"
#include "../../env/method.h"
#include "../../env/constructor.h"
#include "../../env/parameter.h"
#include "../../env/type_parameter.h"
#include "../../env/operator_overload.h"
#include "../../env/type/meta_impl.h"
#include "../../env/cll/class_loader_link_impl.h"
#include "../../vm/symbol_entry.h"
#include "../../util/text.h"
#include "../../util/logger.h"
#include "../lazy_resolve.h"
#include "../resolve/default_eqoperator_resolve.h"
#include "../resolve/default_noteqoperator_resolve.h"
#include "class_loader_ilload_stmt_module_impl.h"
#include <assert.h>
#include <string.h>

//proto
static void CLBC_parameter_list(class_loader* self, namespace_* scope, vector* param_list, vector* sg_param_liste, call_context* cctx);
static void CLBC_parameter_list_ctor(vector* param_list);

static void CLBC_chain(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, il_constructor_chain* ilchain, enviroment* env);
static void CLBC_chain_root(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, il_constructor_chain* ilchain, enviroment* env);
static void CLBC_chain_auto(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, il_constructor_chain* ilchain, enviroment* env);
static void CLBC_chain_super(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, il_constructor_chain* ilchain, enviroment* env);
static bool CLBC_test_operator_overlaod(class_loader* self, il_type* iltype, type* tp, operator_overload* opov);
static void CLBC_default_operator_overload(class_loader* self, type* tp);
static void CLBC_default_eqoperator_overload(class_loader* self, type* tp);
static void CLBC_default_noteqoperator_overload(class_loader* self, type* tp);

//
//field
//
//
bool CLBC_field_decl(class_loader* self, il_type* iltype, type* tp, il_field* ilfi, namespace_* scope, call_context* cctx) {
	field* fi = field_new(ilfi->namev);
	fi->access = ilfi->access;
	fi->modifier = ilfi->modifier;
	fi->parent = tp;
	fi->gtype = import_manager_resolve(self->import_manager, scope, ilfi->fqcn, cctx);
	type_add_field(tp, fi);
	//フィールドの初期値
	fi->initial_value = ilfi->initial_value;
	ilfi->initial_value = NULL;
	//フィールドの修飾子に native が使用されている
	if(modifier_is_native(fi->modifier)) {
		bc_error_throw(bcerror_native_field,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(fi->namev)
		);
		return false;
	}
	//.. abstractが使用されている
	if(modifier_is_abstract(fi->modifier)) {
		bc_error_throw(bcerror_abstract_field,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(fi->namev)
		);
		return false;
	}
	//.. overrideが使用されている
	if(modifier_is_override(fi->modifier)) {
		bc_error_throw(bcerror_override_field,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(fi->namev)
		);
		return false;
	}
	//static finalなのに、
	//初期値が存在しない
	if(modifier_is_static(fi->modifier) &&
	   modifier_is_final(fi->modifier) &&
	   fi->initial_value == NULL) {
		bc_error_throw(bcerror_not_default_value_static_final_field,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(fi->namev)
		);
		return false;
	}
	return true;
}

bool CLBC_field_impl(class_loader* self, type* tp, field* fi, namespace_* scope, call_context* cctx) {
	fi->static_value = object_default(fi->gtype);
	//FIXME:ILフィールドと実行時フィールドのインデックスが同じなのでとりあえず動く
	//プロパティが追加されたタイミングで対応する
	//バッキングフィールドが追加されることもある
	//il_field* ilfield = ((il_field*)vector_at(ilfields, i));
	if(fi->initial_value == NULL) {
		return true;
	}
	enviroment* env = enviroment_new();
	env->context_ref = self;
	fi->initial_value_env = env;
	il_factor_load(fi->initial_value, env, cctx);
	il_factor_generate(fi->initial_value, env, cctx);
	//フィールドの型と互換性がない
	generic_type* gf = il_factor_eval(fi->initial_value, env, cctx);
	if(generic_type_distance(fi->gtype, gf) < 0) {
		generic_type_print(fi->gtype); io_println();
		generic_type_print(gf); io_println();
		bc_error_throw(bcerror_field_default_value_not_compatible_to_field_type,
			string_pool_ref2str(type_name(fi->parent)),
			string_pool_ref2str(fi->namev)
		);
		return false;
	}
	//静的フィールドならついでに初期化
	//FIXME:sg_threadをちゃんと設定すればいいんだけどとりあえずこれで
	//静的フィールドでものすごいでかいオブジェクトを確保すると重くなるかも
	heap* he = heap_get();
	int abtmp = he->accept_blocking;
	he->collect_blocking++;
	he->accept_blocking = 0;
	if(modifier_is_static(fi->modifier)) {
		frame* f = frame_new();
		vm_execute(f, env);
		fi->static_value = vector_pop(f->value_stack);
		frame_delete(f);
	}
	he->accept_blocking = abtmp;
	he->collect_blocking--;
	return true;
}

void CLBC_fields_decl(class_loader* self, il_type* iltype, type* tp, vector* ilfields, namespace_* scope) {
	CL_ERROR(self);
	call_context* cctx = call_context_new(call_decl_T);
	cctx->space = scope;
	cctx->ty = tp;
	for (int i = 0; i < ilfields->length; i++) {
		if(!CLBC_field_decl(self, iltype, tp, vector_at(ilfields, i), scope, cctx)) {
			break;
		}
	}
	call_context_delete(cctx);
}

void CLBC_fields_impl(class_loader* self, namespace_* scope, type* tp,vector* ilfields, vector* sgfields) {
	CL_ERROR(self);
	call_context* cctx = call_context_new(call_ctor_T);
	cctx->space = scope;
	cctx->ty = tp;
	for (int i = 0; i < sgfields->length; i++) {
		if(!CLBC_field_impl(self, tp, vector_at(sgfields, i), scope, cctx)) {
			break;
		}
	}
	call_context_delete(cctx);
}

//
//property
//
//
bool CLBC_property_decl(class_loader* self, il_type* iltype, type* tp, il_property* ilprop, namespace_* scope, call_context* cctx) {
	//vector_item e = vector_at(ilprops, i);
	//il_property* ilprop = e;
	property* prop = property_new(ilprop->namev);
	prop->access = ilprop->access;
	prop->modifier = ilprop->modifier;
	prop->set->access = ilprop->set->access;
	prop->get->access = ilprop->get->access;
	prop->parent = tp;
	prop->gtype = import_manager_resolve(self->import_manager, scope, ilprop->fqcn, cctx);
	prop->is_short = ilprop->set->is_short && ilprop->get->is_short;
	   type_add_property(tp, prop);
	if(modifier_is_abstract(prop->modifier) ||
	   modifier_is_override(prop->modifier) ||
	   modifier_is_native(prop->modifier)) {
		   bc_error_throw(bcerror_native_field, string_pool_ref2str(prop->namev));
			call_context_delete(cctx);
		   return false;
	   }
	//プロパティアクセサの方がプロパティよりも緩いアクセスになっている
	if(access_weak(ilprop->access, ilprop->set->access) ||
	   access_weak(ilprop->access, ilprop->get->access)) {
		bc_error_throw(bcerror_invalid_access_level_of_property,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(ilprop->namev)
		);
		   return false;
	}
	//二つのアクセサがどちらもプロパティと異なるアクセスレベル
	if((ilprop->access != ilprop->set->access) &&
	    ilprop->access != ilprop->get->access) {
		bc_error_throw(bcerror_specified_both_property_accessor,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(ilprop->namev)
		);
		   return false;
	}
	return true;
}

bool CLBC_property_impl(class_loader* self, il_type* iltype, type* tp, il_property* ilprop, property* prop, namespace_* scope, call_context* cctx) {
	//vector_item e = vector_at(sgprops, i);
	property* pr = prop;
	il_property* ilpr = ilprop;
	pr->static_value = object_get_null();
	if(pr->is_short) { return true; }
	property_body* set = pr->set;
	property_body* get = pr->get;
	vector* set_stmt_list = ilpr->set->statement_list;
	vector* get_stmt_list = ilpr->get->statement_list;
	set->env->context_ref = self;
	get->env->context_ref = self;
	//setterのオペコードを生成
	symbol_entry* valueE = symbol_table_entry(set->env->sym_table, pr->gtype, string_pool_intern("value"));
	if(!modifier_is_static(pr->modifier)) {
		opcode_buf_add(set->env->buf, op_store);
		opcode_buf_add(set->env->buf, 0);
	}
	opcode_buf_add(set->env->buf, op_store);
	opcode_buf_add(set->env->buf, valueE->index);
	CLBC_body(self, set_stmt_list, set->env, cctx, scope);
	//getterのオペコードを生成
	if(!modifier_is_static(pr->modifier)) {
		opcode_buf_add(get->env->buf, op_store);
		opcode_buf_add(get->env->buf, 0);
	}
	CLBC_body(self, get_stmt_list, get->env, cctx, scope);
	return true;
}

void CLBC_properties_decl(class_loader* self, il_type* iltype, type* tp, vector* ilprops, namespace_* scope) {
	CL_ERROR(self);
	call_context* cctx = call_context_new(call_decl_T);
	cctx->space = scope;
	cctx->ty = tp;
	for (int i = 0; i < ilprops->length; i++) {
		if(!CLBC_property_decl(self, iltype, tp, vector_at(ilprops, i), scope, cctx)) {
			break;
		}
	}
	call_context_delete(cctx);
}

void CLBC_properties_impl(class_loader* self,  il_type* iltype, type* tp, vector* ilprops, vector* sgprops, namespace_* scope) {
	CL_ERROR(self);
	call_context* cctx = call_context_new(call_decl_T);
	cctx->space = scope;
	cctx->ty = tp;
	for (int i = 0; i < sgprops->length; i++) {
		if(!CLBC_property_impl(self, iltype, tp, vector_at(ilprops, i), vector_at(sgprops, i), scope, cctx)) {
			break;
		}
	}
	call_context_delete(cctx);
}

//
//method
//
//
bool CLBC_method_decl(class_loader* self, il_type* iltype, type* tp, il_method* ilmt, namespace_* scope) {
	//メソッド一覧から取り出す
	il_method* ilmethod = ilmt;
	//メソッドから仮引数一覧を取りだす
	vector* ilparams = ilmethod->parameter_list;
	//実行時のメソッド情報を作成する
	method* method = method_new(ilmethod->namev);
	vector* parameter_list = method->parameter_list;
	method->type = modifier_is_native(ilmethod->modifier) ? method_type_native : method_type_script;
	method->access = ilmethod->access;
	method->modifier = ilmethod->modifier;
	type_parameter_list_dup(ilmethod->type_parameter_list, method->type_parameter_list);
	call_context* cctx = call_context_new(call_method_T);
	cctx->space = scope;
	cctx->ty = tp;
	cctx->u.mt = method;
	//インターフェースなら空
	if (tp->tag == type_interface ||
	   modifier_is_abstract(method->modifier)) {
		method->type = method_type_abstract;
		method->u.script_method = NULL;
	} else {
		method->u.script_method = script_method_new();
	}
	//メソッドが抽象メソッドだが、
	//インターフェイスでも抽象クラスでもない
	if(modifier_is_abstract(method->modifier) &&
	  (tp->tag == type_class &&
	  !TYPE2CLASS(tp)->is_abstract)) {
		bc_error_throw(bcerror_abstract_method_by, string_pool_ref2str(method->namev));
		method_delete(method);
		call_context_delete(cctx);
		return false;
	}
	//メソッドの本文が省略されているが、
	//ネイティブメソッドでも抽象メソッドでもない
	if(tp->tag == type_class &&
	   ilmethod->no_stmt &&
		(!modifier_is_abstract(method->modifier) && !modifier_is_native(method->modifier))
	) {
		bc_error_throw(bcerror_empty_stmt_method, string_pool_ref2str(method->namev));
		method_delete(method);
		call_context_delete(cctx);
		return false;
	}
	//ネイティブメソッドもしくは抽象メソッドなのに本文が書かれている
	if(tp->tag == type_class &&
	   !ilmethod->no_stmt &&
		(modifier_is_abstract(method->modifier) || modifier_is_native(method->modifier))
	) {
		bc_error_throw(bcerror_not_empty_stmt_method, string_pool_ref2str(method->namev));
		method_delete(method);
		call_context_delete(cctx);
		return false;
	}
	//メソッドの修飾子が static override
	if(modifier_is_static(method->modifier) &&
	   modifier_is_override(method->modifier)) {
		bc_error_throw(bcerror_static_override_method,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(method->namev)
		);
		method_delete(method);
		call_context_delete(cctx);
		return false;
	}
	//.. abstract override
	if(modifier_is_abstract(method->modifier) &&
	   modifier_is_override(method->modifier)) {
		bc_error_throw(bcerror_abstract_override_method,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(method->namev)
		);
		method_delete(method);
		call_context_delete(cctx);
		return false;
	}
	//.. abstract static
	if(modifier_is_abstract(method->modifier) &&
	   modifier_is_static(method->modifier)) {
		bc_error_throw(bcerror_abstract_static_method,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(method->namev)
		);
		method_delete(method);
		call_context_delete(cctx);
		return false;
	}
	method->parent = tp;
	method->return_gtype = import_manager_resolve(self->import_manager, scope, ilmethod->return_fqcn, cctx);
	//ILパラメータを実行時パラメータへ変換
	//NOTE:ここでは戻り値の型,引数の型を設定しません
	//     class_loader_sgload_complete参照
	for (int i = 0; i < ilparams->length; i++) {
		vector_item e = vector_at(ilparams, i);
		il_parameter* ilp = (il_parameter*)e;
		parameter* param = parameter_new(ilp->namev);
		vector_push(parameter_list, param);
	}
	CLBC_parameter_list(self, scope, ilmethod->parameter_list, method->parameter_list, cctx);
	//NOTE:クラスの登録が終わったらオペコードを作成する
	LOG("%s@%s", string_pool_ref2str(type_name(tp)), string_pool_ref2str(method->namev));
	type_add_method(tp, method);
	call_context_delete(cctx);
	return true;
}

bool CLBC_method_impl(class_loader* self, namespace_* scope, il_type* iltype, type* tp, il_method* ilmt, method* mt) {
	//	vector_item e = vector_at(sgmethods, i);
	method* me = mt;
	il_method* ilmethod = ilmt;
	//ネイティブメソッドならオペコードは不要
	if (me->type == method_type_native ||
		me->type == method_type_abstract) {
		return true;
	}
	//オペコードを作成
	//FIXME:ILメソッドと実行時メソッドのインデックスが同じなのでとりあえず動く
	//まずは仮引数の一覧にインデックスを割り振る
	enviroment* env = enviroment_new();
	env->context_ref = self;
	call_context* cctx = call_context_new(call_method_T);
	cctx->space = scope;
	cctx->ty = tp;
	cctx->u.mt = me;
	//引数を保存
	for (int i = 0; i < ilmethod->parameter_list->length; i++) {
		il_parameter* ilparam = (il_parameter*)vector_at(ilmethod->parameter_list, i);
		symbol_table_entry(
			env->sym_table,
			import_manager_resolve(self->import_manager, scope, ilparam->fqcn, cctx),
			ilparam->namev
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
	CLBC_corutine(self, me, env, ilmethod->parameter_list, ilmethod->statement_list, cctx, scope);
	call_context_delete(cctx);
	return true;
}

void CLBC_methods_decl(class_loader* self, il_type* iltype, type* tp, vector* ilmethods, namespace_* scope) {
	CL_ERROR(self);
	for (int i = 0; i < ilmethods->length; i++) {
		if(!CLBC_method_decl(self, iltype, tp, vector_at(ilmethods,i),scope)) {
			break;
		}
	}
}

void CLBC_methods_impl(class_loader* self, namespace_* scope, il_type* iltype, type* tp, vector* ilmethods, vector* sgmethods) {
	CL_ERROR(self);
	for (int i = 0; i < ilmethods->length; i++) {
		if(!CLBC_method_impl(self, scope, iltype, tp, vector_at(ilmethods, i), vector_at(sgmethods, i))) {
			break;
		}
	}
}

//
//ctor
//
//
bool CLBC_ctor_decl(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, namespace_* scope) {
	//メソッドから仮引数一覧を取りだす
	vector* ilparams = ilcons->parameter_list;
	class_* classz = tp->u.class_;
	//実行時のメソッド情報を作成する
	constructor* cons = constructor_new();
	vector* parameter_list = cons->parameter_list;
	cons->access = ilcons->access;
	cons->parent = tp;
	call_context* cctx = call_context_new(call_ctor_T);
	cctx->space = scope;
	cctx->ty = tp;
	cctx->u.ctor = cons;
	//NOTE:ここでは戻り値の型,引数の型を設定しません
	//     class_loader_sgload_complete参照
	for (int i = 0; i < ilparams->length; i++) {
		vector_item e = vector_at(ilparams, i);
		il_parameter* ilp = (il_parameter*)e;
		parameter* param = parameter_new(ilp->namev);
		vector_push(parameter_list, param);
	}
	CLBC_parameter_list(self, scope, ilcons->parameter_list, cons->parameter_list, cctx);
	CLBC_parameter_list_ctor(cons->parameter_list);
	class_add_constructor(classz, cons);
	call_context_delete(cctx);
	return true;
}

bool CLBC_ctor_impl(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, constructor* cons, namespace_* scope) {
	//仮引数に型を設定する
	//class_loader_sgload_params(self, scope, ilcons->parameter_list, cons->parameter_list);
	//まずは仮引数の一覧にインデックスを割り振る
	enviroment* env = enviroment_new();
	env->context_ref = self;
	call_context* cctx = call_context_new(call_ctor_T);
	cctx->space = scope;
	cctx->ty = tp;
	cctx->u.ctor = cons;
	for (int i = 0; i < cons->parameter_list->length; i++) {
		il_parameter* ilparam = (il_parameter*)vector_at(ilcons->parameter_list, i);
		symbol_table_entry(
			env->sym_table,
			import_manager_resolve(self->import_manager, scope, ilparam->fqcn, cctx),
			ilparam->namev
		);
		//実引数を保存
		//0番目は this のために開けておく
		opcode_buf_add(env->buf, op_store);
		opcode_buf_add(env->buf, (i + 1));
	}
	CLBC_chain(self, iltype, tp, ilcons, ilcons->chain, env);
	//NOTE:ここなら名前空間を設定出来る
	CLBC_body(self, ilcons->statement_list, env, cctx, scope);
	cons->env = env;
	call_context_delete(cctx);
	return true;
}

void CLBC_ctors_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope) {
	CL_ERROR(self);
	class_* classz = tp->u.class_;
	vector* ilcons_list = iltype->u.class_->constructor_list;
	for (int i = 0; i < ilcons_list->length; i++) {
		if(!CLBC_ctor_decl(self, iltype, tp, vector_at(ilcons_list, i), scope)) {
			break;
		}
	}
}

void CLBC_ctors_impl(class_loader* self, il_type* iltype, type* tp) {
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
	for (int i = 0; i < constructors->length; i++) {
		if(!CLBC_ctor_impl(self, iltype, tp, vector_at(iltype->u.class_->constructor_list,i),vector_at(constructors, i), scope)) {
			break;
		}
	}
}

//
//operator overload
//
//
bool CLBC_operator_overload_decl(class_loader* self, il_type* iltype, type* tp, il_operator_overload* ilopov, namespace_* scope) {
	//演算子オーバーロード一覧から取り出す
	operator_overload* opov = operator_overload_new(ilopov->op);
	opov->access = ilopov->access;
	//call_contextの設定
	call_context* cctx = call_context_new(call_opov_T);
	cctx->space = scope;
	cctx->ty = tp;
	cctx->u.opov = opov;
	//戻り値読み込み
	opov->parent = tp;
	opov->return_gtype = import_manager_resolve(self->import_manager, scope, ilopov->return_fqcn, cctx);
	//パラメータ読み込み
	for(int j=0; j<ilopov->parameter_list->length; j++) {
		il_parameter* ilparam = vector_at(ilopov->parameter_list, j);
		parameter* param = parameter_new(ilparam->namev);
		vector_push(opov->parameter_list, param);
	}
	CLBC_parameter_list(self, scope, ilopov->parameter_list, opov->parameter_list, cctx);
	vector_push(tp->u.class_->operator_overload_list, opov);
	//オペレータオーバロードの妥当性をテストする
	if(CLBC_test_operator_overlaod(self, iltype, tp, opov)) {
		call_context_delete(cctx);
		return false;
	}
	call_context_delete(cctx);
	return true;
}

bool CLBC_operator_overload_impl(class_loader* self, il_type* iltype, type* tp, il_operator_overload* ilopov, operator_overload* opov, namespace_* scope) {
	//オペコードを作成
	//FIXME:ILメソッドと実行時メソッドのインデックスが同じなのでとりあえず動く
	//まずは仮引数の一覧にインデックスを割り振る
	enviroment* env = enviroment_new();
	call_context* cctx = call_context_new(call_opov_T);
	cctx->space = scope;
	cctx->ty = tp;
	cctx->u.opov = opov;
	//ccpush_method(me);
	env->context_ref = self;
	for (int i = 0; i < ilopov->parameter_list->length; i++) {
		il_parameter* ilparam = (il_parameter*)vector_at(ilopov->parameter_list, i);
		symbol_table_entry(
			env->sym_table,
			import_manager_resolve(self->import_manager, scope, ilparam->fqcn, cctx),
			ilparam->namev
		);
		//実引数を保存
		//0番目は this のために開けておく
		opcode_buf_add(env->buf, (vector_item)op_store);
		opcode_buf_add(env->buf, (vector_item)(i + 1));
	}
	//0番目をthisで埋める
	opcode_buf_add(env->buf, (vector_item)op_store);
	opcode_buf_add(env->buf, (vector_item)0);
	//NOTE:ここなら名前空間を設定出来る
	CLBC_body(self, ilopov->statement_list, env, cctx, scope);
	call_context_delete(cctx);
	//ccpop_method();
	opov->env = env;
	return true;
}

void CLBC_operator_overloads_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope) {
	CL_ERROR(self);
	vector* opov_list = iltype->u.class_->operator_overload_list;
	for (int i = 0; i < opov_list->length; i++) {
		if(!CLBC_operator_overload_decl(self, iltype, tp, vector_at(opov_list, i), scope)) {
			break;
		}
	}
	CLBC_default_operator_overload(self, tp);
}

void CLBC_operator_overloads_impl(class_loader* self, il_type* iltype, type* tp, namespace_* scope) {
	CL_ERROR(self);
	vector* opov_list = tp->u.class_->operator_overload_list;
	//ここで暗黙的に作成される == != によって長さが合わなくなる
	for (int i = 0; i < iltype->u.class_->operator_overload_list->length; i++) {
		if(!CLBC_operator_overload_impl(self, iltype, tp, vector_at(iltype->u.class_->operator_overload_list, i), vector_at(opov_list, i), scope)) {
			break;
		}
	}
}

bool CLBC_corutine(class_loader* self, method* mt, enviroment* env,  vector* ilparams, vector* ilstmts, call_context* cctx, namespace_* range) {
	//戻り値が iterator なら、
	//コルーチンとして使えるようにする
	bool yield_err = false;
	if(method_yield(mt, ilstmts, &yield_err)) {
		if(yield_err) {
			abort();
			return false;
		}
		//メソッド名からクラス名を作成して、
		//beacon::$placeholderへ肩を格納する
		type* iterT = method_create_iterator_type(mt, self, ilstmts);
		opcode_buf_add(env->buf, op_this);
		for(int i=0; i<ilparams->length; i++) {
			opcode_buf_add(env->buf, op_load);
			opcode_buf_add(env->buf, i + 1);
		}
		mt->u.script_method->env = env;
		opcode_buf_add(env->buf, op_new_instance);
		opcode_buf_add(env->buf, iterT->absolute_index);
		opcode_buf_add(env->buf, 0);
		opcode_buf_add(env->buf, op_return);
		return true;
	}
	//NOTE:ここなら名前空間を設定出来る
	CLBC_body(self, ilstmts, env, cctx, range);
	mt->u.script_method->env = env;
	return true;
}

void CLBC_body(class_loader* self, vector* stmt_list, enviroment* dest, call_context* cctx, namespace_* range) {
	CL_ERROR(self);
	//まずは全てのステートメントを読み込む
	for (int i = 0; i < stmt_list->length; i++) {
		if(bc_error_last()) {
			break;
		}
		vector_item e = vector_at(stmt_list, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_load(s, dest, cctx);
	}
	//オペコードを生成
	for (int i = 0; i < stmt_list->length; i++) {
		if(bc_error_last()) {
			break;
		}
		vector_item e = vector_at(stmt_list, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_generate(s, dest, cctx);
	}
}

//private
static void CLBC_parameter_list(class_loader* self, namespace_* scope, vector* param_list, vector* sg_param_list, call_context* cctx) {
	for (int j = 0; j < param_list->length; j++) {
		vector_item e = vector_at(param_list, j);
		il_parameter* ilparam = (il_parameter*)e;
		//FIXME:ILパラメータと実行時パラメータのインデックスが同じなのでとりあえず動く
		parameter* mep = (parameter*)vector_at(sg_param_list, j);
		mep->gtype = import_manager_resolve(
			self->import_manager,
			scope,
			ilparam->fqcn,
			cctx
		);
	}
}

static void CLBC_parameter_list_ctor(vector* param_list) {
	for(int i=0; i<param_list->length; i++) {
		parameter* param = vector_at(param_list, i);
		param->gtype->is_ctor = true;
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
	call_context* cctx = call_context_new(call_ctor_args_T);
	cctx->ty = tp;
	constructor* emptyTarget = class_ilfind_empty_constructor(classz->super_class->core_type->u.class_, env, cctx, &emptyTemp);
	call_context_delete(cctx);
	//連鎖を明示的に書いていないのに、
	//親クラスにも空のコンストラクタが存在しない=エラー
	//(この場合自動的にチェインコンストラクタを補うことが出来ないため。)
	if(emptyTarget == NULL) {
		bc_error_throw(bcerror_auto_chain_ctor_not_found,
			string_pool_ref2str(type_name(tp))
		);
		return;
	}
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
	call_context* cctx = call_context_new(call_ctor_args_T);
	cctx->ty = tp;
	il_constructor_chain* chain = ilcons->chain;
	for (int i = 0; i < chain->argument_list->length; i++) {
		il_argument* ilarg = (il_argument*)vector_at(chain->argument_list, i);
		il_factor_generate(ilarg->factor, env, cctx);
	}
	//連鎖先のコンストラクタを検索する
	constructor* chainTarget = NULL;
	int temp = 0;
	if (chain->type == chain_type_this) {
		chainTarget = class_ilfind_constructor(classz, chain->argument_list, env, cctx, &temp);
		opcode_buf_add(env->buf, (vector_item)op_chain_this);
		opcode_buf_add(env->buf, (vector_item)(tp->absolute_index));
	} else if (chain->type == chain_type_super) {
		chainTarget = class_ilfind_constructor(classz->super_class->core_type->u.class_, chain->argument_list, env, cctx, &temp);
		opcode_buf_add(env->buf, op_chain_super);
		opcode_buf_add(env->buf, classz->super_class->core_type->u.class_->classIndex);
	}
	if(chainTarget == NULL) {
		bc_error_throw(bcerror_explicit_chain_ctor_not_found,
			string_pool_ref2str(type_name(tp))
		);
		return;
	}
	call_context_delete(cctx);
	chain->c = chainTarget;
	chain->constructor_index = temp;
	opcode_buf_add(env->buf, (vector_item)temp);
	//親クラスへのチェインなら即座にフィールドを確保
	opcode_buf_add(env->buf, (vector_item)op_alloc_field);
	opcode_buf_add(env->buf, (vector_item)tp->absolute_index);
}

static bool CLBC_test_operator_overlaod(class_loader* self, il_type* iltype, type* tp, operator_overload* opov) {
	//アクセスレベルを確認する
	if(opov->access != access_public) {
		bc_error_throw(bcerror_private_operator, type_name(tp));
		return true;
	}
	//二項演算子であるなら引数は1
	if(operator_arg2(opov->type) && opov->parameter_list->length != 1) {
		bc_error_throw(bcerror_arg_count_not2_bioperator, type_name(tp), operator_tostring(opov->type));
		return true;
	}
	//単項演算子であるなら引数は0
	if(operator_arg1(opov->type) && opov->parameter_list->length != 0) {
		bc_error_throw(bcerror_arg_count_not1_uoperator,
			type_name(tp),
			operator_tostring(opov->type)
		);
		return true;
	}
	//== などの比較演算子の戻り値が bool ではない
	if(operator_compare(opov->type) && opov->return_gtype->core_type != TYPE_BOOL) {
		bc_error_throw(bcerror_return_type_not_bool_compare_operator,
			string_pool_ref2str(type_name(tp)),
			operator_tostring(opov->type)
		);
		return true;
	}
	//! の戻り値が bool ではない
	if(opov->type == operator_not && opov->return_gtype->core_type != TYPE_BOOL) {
		bc_error_throw(bcerror_return_type_not_bool_not_operator,
			string_pool_ref2str(type_name(tp)),
			operator_tostring(opov->type)
		);
		return true;
	}
	//- の戻り値がクラスと異なる
	//(IntならInt, Vector2ならVector2)
	if(opov->type == operator_negative && opov->return_gtype->core_type != opov->parent) {
		bc_error_throw(bcerror_return_type_not_equal_negative_operator,
			string_pool_ref2str(type_name(tp)),
			operator_tostring(opov->type)
		);
		return true;
	}
	return false;
}

static void CLBC_default_operator_overload(class_loader* self, type* tp) {
	CLBC_default_eqoperator_overload(self, tp);
	CLBC_default_noteqoperator_overload(self, tp);
}

static void CLBC_default_eqoperator_overload(class_loader* self, type* tp) {
	if(tp->tag != type_class) {
		return;
	}
	//==(Object a)を検索する
	int outIndex = 0;
	operator_overload* opov_defeq = meta_gfind_operator_default_eq(TYPE2CLASS(tp)->operator_overload_list, &outIndex);
	if(opov_defeq != NULL) {
		//すでに存在するので何もしない
		return;
	}
	//equals(Object a)を検索する
	//これによって == を自動実装する
	int methodPos = 0;
	operator_overload* opov_eq = operator_overload_new(operator_eq);
	opov_eq->access = access_public;
	//戻り値読み込み
	opov_eq->parent = tp;
	opov_eq->return_gtype = TYPE_BOOL->generic_self;
	vector_push(TYPE2CLASS(tp)->operator_overload_list, opov_eq);
	//引数作成
	parameter* paramOBJ = parameter_new(string_pool_intern("a"));
	paramOBJ->gtype = TYPE_OBJECT->generic_self;
	vector_push(opov_eq->parameter_list, paramOBJ);
	//オペコード作成
	enviroment* env = enviroment_new();
	env->context_ref = self;
	//引数を読み取る
	symbol_table_entry(env->sym_table, paramOBJ->gtype, paramOBJ->namev);
	opcode_buf_add(env->buf, (vector_item)op_store);
	opcode_buf_add(env->buf, (vector_item)1);
	//thisを参照できるように
	opcode_buf_add(env->buf, (vector_item)op_store);
	opcode_buf_add(env->buf, (vector_item)0);
	//equalsメソッドを呼び出す
	opcode_buf_add(env->buf, (vector_item)op_load);
	opcode_buf_add(env->buf, (vector_item)1);
	opcode_buf_add(env->buf, (vector_item)op_load);
	opcode_buf_add(env->buf, (vector_item)0);
	//equalsが見つからないのであとで解決する
	opcode_buf_add(env->buf, (vector_item)op_invokevirtual_lazy);
	lazy_int* li = opcode_buf_lazy(env->buf, -1);
	lazy_resolve* resolve = lazy_resolve_new(resolve_default_eqoperator);
	resolve->u.def_eqoperator->lazyi_ref = li;
	resolve->u.def_eqoperator->type_ref = tp;
	vector_push(self->lazy_resolve_vec, resolve);
	opcode_buf_add(env->buf, (vector_item)li);
	opcode_buf_add(env->buf, (vector_item)op_return);
	opov_eq->env = env;
}

static void CLBC_default_noteqoperator_overload(class_loader* self, type* tp) {
	if(tp->tag != type_class) {
		return;
	}
	//!=(Object a)を検索する
	int outIndex = 0;
	operator_overload* opov_defnoteq = meta_gfind_operator_default_noteq(TYPE2CLASS(tp)->operator_overload_list, &outIndex);
	if(opov_defnoteq != NULL) {
		//すでに存在するので何もしない
		return;
	}
	//equals(Object a)を検索する
	//これによって != を自動実装する
	int methodPos = 0;
	operator_overload* opov_noteq = operator_overload_new(operator_noteq);
	opov_noteq->access = access_public;
	//戻り値読み込み
	opov_noteq->parent = tp;
	opov_noteq->return_gtype = TYPE_BOOL->generic_self;
	vector_push(TYPE2CLASS(tp)->operator_overload_list, opov_noteq);
	//引数作成
	parameter* paramOBJ = parameter_new(string_pool_intern("a"));
	paramOBJ->gtype = TYPE_OBJECT->generic_self;
	vector_push(opov_noteq->parameter_list, paramOBJ);
	//オペコード作成
	enviroment* env = enviroment_new();
	env->context_ref = self;
	//引数を読み取る
	symbol_table_entry(env->sym_table, paramOBJ->gtype, paramOBJ->namev);
	opcode_buf_add(env->buf, (vector_item)op_store);
	opcode_buf_add(env->buf, (vector_item)1);
	//thisを参照できるように
	opcode_buf_add(env->buf, (vector_item)op_store);
	opcode_buf_add(env->buf, (vector_item)0);
	//equalsメソッドを呼び出す
	opcode_buf_add(env->buf, (vector_item)op_load);
	opcode_buf_add(env->buf, (vector_item)1);
	opcode_buf_add(env->buf, (vector_item)op_load);
	opcode_buf_add(env->buf, (vector_item)0);
	//equalsが見つからないのであとで解決する
	opcode_buf_add(env->buf, (vector_item)op_invokevirtual_lazy);
	lazy_int* li = opcode_buf_lazy(env->buf, -1);
	lazy_resolve* resolve = lazy_resolve_new(resolve_default_noteqoperator);
	resolve->u.def_noteqoperator->lazyi_ref = li;
	resolve->u.def_noteqoperator->type_ref = tp;
	vector_push(self->lazy_resolve_vec, resolve);
	opcode_buf_add(env->buf, (vector_item)li);
	opcode_buf_add(env->buf, (vector_item)op_bnot);
	opcode_buf_add(env->buf, (vector_item)op_return);
	opov_noteq->env = env;
}