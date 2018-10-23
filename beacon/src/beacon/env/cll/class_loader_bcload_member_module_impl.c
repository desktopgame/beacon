#include "class_loader_bcload_member_module_impl.h"
#include "../../il/il_TYPE_IMPL.h"
#include "../../il/il_field.h"
#include "../../il/il_property.h"
#include "../../il/il_method.h"
#include "../../il/il_constructor.h"
#include "../../il/il_constructor_chain.h"
#include "../../il/il_parameter.h"
#include "../../il/il_argument.h"
#include "../../il/il_stmt_interface.h"
#include "../../il/il_operator_overload.h"
#include "../../env/TYPE_IMPL.h"
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
#include "../../thread/thread.h"
#include "../../vm/symbol_entry.h"
#include "../../util/text.h"
#include "class_loader_ilload_stmt_module_impl.h"
#include <assert.h>
#include <string.h>

//proto
static void CLBC_parameter_list(class_loader* self, namespace_* scope, Vector* param_list, Vector* sg_param_liste, CallContext* cctx);
static void CLBC_parameter_list_ctor(Vector* param_list);

static void CLBC_chain(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, ILConstructorChain* ilchain, Enviroment* env);
static void CLBC_chain_root(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, ILConstructorChain* ilchain, Enviroment* env);
static void CLBC_chain_auto(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, ILConstructorChain* ilchain, Enviroment* env);
static void CLBC_chain_super(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, ILConstructorChain* ilchain, Enviroment* env);
static bool CLBC_test_operator_overlaod(class_loader* self, il_type* iltype, type* tp, operator_overload* opov);

//
//field
//
//
bool CLBC_field_decl(class_loader* self, il_type* iltype, type* tp, il_field* ilfi, namespace_* scope, CallContext* cctx) {
	field* fi = NewField(ilfi->namev);
	fi->access = ilfi->access;
	fi->modifier = ilfi->modifier;
	fi->parent = tp;
	fi->gtype = ResolveImportManager(scope, ilfi->fqcn, cctx);
	AddFieldType(tp, fi);
	//フィールドの初期値
	fi->initial_value = ilfi->initial_value;
	ilfi->initial_value = NULL;
	//フィールドの修飾子に native が使用されている
	if(IsNativeModifier(fi->modifier)) {
		ThrowBCError(BCERROR_NATIVE_FIELD_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(fi->namev)
		);
		return false;
	}
	//.. abstractが使用されている
	if(IsAbstractModifier(fi->modifier)) {
		ThrowBCError(BCERROR_ABSTRACT_FIELD_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(fi->namev)
		);
		return false;
	}
	//.. overrideが使用されている
	if(IsOverrideModifier(fi->modifier)) {
		ThrowBCError(BCERROR_OVERRIDE_FIELD_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(fi->namev)
		);
		return false;
	}
	//static finalなのに、
	//初期値が存在しない
	if(IsStaticModifier(fi->modifier) &&
	   IsFinalModifier(fi->modifier) &&
	   fi->initial_value == NULL) {
		ThrowBCError(BCERROR_NOT_DEFAULT_VALUE_STATIC_FINAL_FIELD_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(fi->namev)
		);
		return false;
	}
	return true;
}

bool CLBC_field_impl(class_loader* self, type* tp, field* fi, namespace_* scope, CallContext* cctx) {
	fi->static_value = GetDefaultObject(fi->gtype);
	if(fi->initial_value == NULL) {
		return true;
	}
	//フィールドの初期値を設定する
	Enviroment* env = NewEnviroment();
	env->ContextRef = self;
	fi->initial_value_env = env;
	LoadILFactor(fi->initial_value, env, cctx);
	GenerateILFactor(fi->initial_value, env, cctx);
	//フィールドの型と互換性がない
	generic_type* gf = EvalILFactor(fi->initial_value, env, cctx);
	if(DistanceGenericType(fi->gtype, gf, cctx) < 0) {
		PrintGenericType(fi->gtype); Println();
		PrintGenericType(gf); Println();
		ThrowBCError(BCERROR_FIELD_DEFAULT_VALUE_NOT_COMPATIBLE_TO_FIELD_TYPE_T,
			Ref2Str(GetTypeName(fi->parent)),
			Ref2Str(fi->namev)
		);
		return false;
	}
	//静的フィールドならついでに初期化
	//静的フィールドでものすごいでかいオブジェクトを確保すると重くなるかも
	Heap* he = GetHeap();
	int abtmp = he->AcceptBlocking;
	he->CollectBlocking++;
	he->AcceptBlocking = 0;
	if(IsStaticModifier(fi->modifier)) {
		Frame* f = NewFrame();
		SetSGThreadFrameRef(GetMainSGThread(), f);
		ExecuteVM(f, env);
		fi->static_value = PopVector(f->ValueStack);
		ReleaseSGThreadFrameRef(GetMainSGThread());
		DeleteFrame(f);
	}
	he->AcceptBlocking = abtmp;
	he->CollectBlocking--;
	return true;
}

void CLBC_fields_decl(class_loader* self, il_type* iltype, type* tp, Vector* ilfields, namespace_* scope) {
	CL_ERROR(self);
	CallContext* cctx = NewCallContext(CALL_DECL_T);
	cctx->Scope = scope;
	cctx->Ty = tp;
	for (int i = 0; i < ilfields->Length; i++) {
		if(!CLBC_field_decl(self, iltype, tp, AtVector(ilfields, i), scope, cctx)) {
			break;
		}
	}
	DeleteCallContext(cctx);
}

void CLBC_fields_impl(class_loader* self, namespace_* scope, type* tp,Vector* ilfields, Vector* sgfields) {
	CL_ERROR(self);
	CallContext* cctx = NewCallContext(CALL_CTOR_T);
	cctx->Scope = scope;
	cctx->Ty = tp;
	for (int i = 0; i < sgfields->Length; i++) {
		if(!CLBC_field_impl(self, tp, AtVector(sgfields, i), scope, cctx)) {
			break;
		}
	}
	DeleteCallContext(cctx);
}

//
//property
//
//
bool CLBC_property_decl(class_loader* self, il_type* iltype, type* tp, il_property* ilprop, namespace_* scope, CallContext* cctx) {
	//VectorItem e = AtVector(ilprops, i);
	//il_property* ilprop = e;
	property* prop = property_new(ilprop->namev);
	prop->access = ilprop->access;
	prop->modifier = ilprop->modifier;
	prop->set->access = ilprop->set->access;
	prop->get->access = ilprop->get->access;
	prop->parent = tp;
	prop->gtype = ResolveImportManager(scope, ilprop->fqcn, cctx);
	prop->is_short = ilprop->set->is_short && ilprop->get->is_short;
	   AddPropertyType(tp, prop);
	if(IsAbstractModifier(prop->modifier) ||
	   IsOverrideModifier(prop->modifier) ||
	   IsNativeModifier(prop->modifier)) {
		   ThrowBCError(BCERROR_NATIVE_FIELD_T, Ref2Str(prop->namev));
			DeleteCallContext(cctx);
		   return false;
	   }
	//プロパティアクセサの方がプロパティよりも緩いアクセスになっている
	if(IsWeakAccess(ilprop->access, ilprop->set->access) ||
	   IsWeakAccess(ilprop->access, ilprop->get->access)) {
		ThrowBCError(BCERROR_INVALID_ACCESS_LEVEL_OF_PROPERTY_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(ilprop->namev)
		);
		   return false;
	}
	//二つのアクセサがどちらもプロパティと異なるアクセスレベル
	if((ilprop->access != ilprop->set->access) &&
	    ilprop->access != ilprop->get->access) {
		ThrowBCError(BCERROR_SPECIFIED_BOTH_PROPERTY_ACCESSOR_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(ilprop->namev)
		);
		   return false;
	}
	return true;
}

bool CLBC_property_impl(class_loader* self, il_type* iltype, type* tp, il_property* ilprop, property* prop, namespace_* scope, CallContext* cctx) {
	//VectorItem e = AtVector(sgprops, i);
	property* pr = prop;
	il_property* ilpr = ilprop;
	if(pr->is_short) { return true; }
	property_body* set = pr->set;
	property_body* get = pr->get;
	Vector* set_stmt_list = ilpr->set->statement_list;
	Vector* get_stmt_list = ilpr->get->statement_list;
	set->env->ContextRef = self;
	get->env->ContextRef = self;
	//setterのオペコードを生成
	SymbolEntry* valueE = EntrySymbolTable(set->env->Symboles, pr->gtype, InternString("value"));
	if(!IsStaticModifier(pr->modifier)) {
		AddOpcodeBuf(set->env->Bytecode, OP_STORE);
		AddOpcodeBuf(set->env->Bytecode, 0);
	}
	AddOpcodeBuf(set->env->Bytecode, OP_STORE);
	AddOpcodeBuf(set->env->Bytecode, valueE->Index);
	CLBC_body(self, set_stmt_list, set->env, cctx, scope);
	//getterのオペコードを生成
	if(!IsStaticModifier(pr->modifier)) {
		AddOpcodeBuf(get->env->Bytecode, OP_STORE);
		AddOpcodeBuf(get->env->Bytecode, 0);
	}
	CLBC_body(self, get_stmt_list, get->env, cctx, scope);
	return true;
}

void CLBC_properties_decl(class_loader* self, il_type* iltype, type* tp, Vector* ilprops, namespace_* scope) {
	CL_ERROR(self);
	CallContext* cctx = NewCallContext(CALL_DECL_T);
	cctx->Scope = scope;
	cctx->Ty = tp;
	for (int i = 0; i < ilprops->Length; i++) {
		if(!CLBC_property_decl(self, iltype, tp, AtVector(ilprops, i), scope, cctx)) {
			break;
		}
	}
	DeleteCallContext(cctx);
}

void CLBC_properties_impl(class_loader* self,  il_type* iltype, type* tp, Vector* ilprops, Vector* sgprops, namespace_* scope) {
	CL_ERROR(self);
	CallContext* cctx = NewCallContext(CALL_DECL_T);
	cctx->Scope = scope;
	cctx->Ty = tp;
	for (int i = 0; i < sgprops->Length; i++) {
		if(!CLBC_property_impl(self, iltype, tp, AtVector(ilprops, i), AtVector(sgprops, i), scope, cctx)) {
			break;
		}
	}
	DeleteCallContext(cctx);
}

//
//method
//
//
bool CLBC_method_decl(class_loader* self, il_type* iltype, type* tp, il_method* ilmt, namespace_* scope) {
	//メソッド一覧から取り出す
	il_method* ilmethod = ilmt;
	//メソッドから仮引数一覧を取りだす
	Vector* ilparams = ilmethod->parameter_list;
	//実行時のメソッド情報を作成する
	method* method = method_new(ilmethod->namev);
	Vector* parameter_list = method->parameters;
	method->type = IsNativeModifier(ilmethod->modifier) ? METHOD_TYPE_NATIVE_T : METHOD_TYPE_SCRIPT_T;
	method->access = ilmethod->access;
	method->modifier = ilmethod->modifier;
	DupTypeParameterList(ilmethod->GetParameterListType, method->type_parameters);
	CallContext* cctx = NewCallContext(CALL_METHOD_T);
	cctx->Scope = scope;
	cctx->Ty = tp;
	cctx->Kind.Method = method;
	//インターフェースなら空
	if (tp->tag == TYPE_INTERFACE_T ||
	   IsAbstractModifier(method->modifier)) {
		method->type = METHOD_TYPE_ABSTRACT_T;
		method->u.script_method = NULL;
	} else {
		if(IsNativeModifier(method->modifier)) {
			method->u.native_method = NewNativeMethod();
		} else {
			method->u.script_method = NewScriptMethod();
		}
	}
	//メソッドが抽象メソッドだが、
	//インターフェイスでも抽象クラスでもない
	if(IsAbstractModifier(method->modifier) &&
	  (tp->tag == TYPE_CLASS_T &&
	  !TYPE2CLASS(tp)->is_abstract)) {
		ThrowBCError(BCERROR_ABSTRACT_METHOD_BY_T, Ref2Str(method->namev));
		DeleteMethod(method);
		DeleteCallContext(cctx);
		return false;
	}
	//メソッドの本文が省略されているが、
	//ネイティブメソッドでも抽象メソッドでもない
	if(tp->tag == TYPE_CLASS_T &&
	   ilmethod->no_stmt &&
		(!IsAbstractModifier(method->modifier) && !IsNativeModifier(method->modifier))
	) {
		ThrowBCError(BCERROR_EMPTY_STMT_METHOD_T, Ref2Str(method->namev));
		DeleteMethod(method);
		DeleteCallContext(cctx);
		return false;
	}
	//ネイティブメソッドもしくは抽象メソッドなのに本文が書かれている
	if(tp->tag == TYPE_CLASS_T &&
	   !ilmethod->no_stmt &&
		(IsAbstractModifier(method->modifier) || IsNativeModifier(method->modifier))
	) {
		ThrowBCError(BCERROR_NOT_EMPTY_STMT_METHOD_T, Ref2Str(method->namev));
		DeleteMethod(method);
		DeleteCallContext(cctx);
		return false;
	}
	//メソッドの修飾子が static override
	if(IsStaticModifier(method->modifier) &&
	   IsOverrideModifier(method->modifier)) {
		ThrowBCError(BCERROR_STATIC_OVERRIDE_METHOD_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(method->namev)
		);
		DeleteMethod(method);
		DeleteCallContext(cctx);
		return false;
	}
	//.. abstract override
	if(IsAbstractModifier(method->modifier) &&
	   IsOverrideModifier(method->modifier)) {
		ThrowBCError(BCERROR_ABSTRACT_OVERRIDE_METHOD_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(method->namev)
		);
		DeleteMethod(method);
		DeleteCallContext(cctx);
		return false;
	}
	//.. abstract static
	if(IsAbstractModifier(method->modifier) &&
	   IsStaticModifier(method->modifier)) {
		ThrowBCError(BCERROR_ABSTRACT_STATIC_METHOD_T,
			Ref2Str(GetTypeName(tp)),
			Ref2Str(method->namev)
		);
		DeleteMethod(method);
		DeleteCallContext(cctx);
		return false;
	}
	method->parent = tp;
	method->return_gtype = ResolveImportManager(scope, ilmethod->return_fqcn, cctx);
	//ILパラメータを実行時パラメータへ変換
	//NOTE:ここでは戻り値の型,引数の型を設定しません
	//     class_loader_sgload_complete参照
	for (int i = 0; i < ilparams->Length; i++) {
		VectorItem e = AtVector(ilparams, i);
		il_parameter* ilp = (il_parameter*)e;
		Parameter* param = NewParameter(ilp->namev);
		PushVector(parameter_list, param);
	}
	CLBC_parameter_list(self, scope, ilmethod->parameter_list, method->parameters, cctx);
	AddMethodType(tp, method);
	DeleteCallContext(cctx);
	return true;
}

bool CLBC_method_impl(class_loader* self, namespace_* scope, il_type* iltype, type* tp, il_method* ilmt, method* mt) {
	//	VectorItem e = AtVector(sgmethods, i);
	method* me = mt;
	il_method* ilmethod = ilmt;
	//ネイティブメソッドならオペコードは不要
	if (me->type == METHOD_TYPE_NATIVE_T ||
		me->type == METHOD_TYPE_ABSTRACT_T) {
		return true;
	}
	//オペコードを作成
	//FIXME:ILメソッドと実行時メソッドのインデックスが同じなのでとりあえず動く
	//まずは仮引数の一覧にインデックスを割り振る
	Enviroment* env = NewEnviroment();
	env->ContextRef = self;
	CallContext* cctx = NewCallContext(CALL_METHOD_T);
	cctx->Scope = scope;
	cctx->Ty = tp;
	cctx->Kind.Method = me;
	//引数を保存
	for (int i = 0; i < ilmethod->parameter_list->Length; i++) {
		il_parameter* ilparam = (il_parameter*)AtVector(ilmethod->parameter_list, i);
		EntrySymbolTable(
			env->Symboles,
			ResolveImportManager(scope, ilparam->fqcn, cctx),
			ilparam->namev
		);
		//実引数を保存
		//0番目は this のために開けておく
		AddOpcodeBuf(env->Bytecode, (VectorItem)OP_STORE);
		AddOpcodeBuf(env->Bytecode, (VectorItem)(i + 1));
	}
	//インスタンスメソッドなら
	//0番目を this で埋める
	if (!IsStaticModifier(me->modifier)) {
		AddOpcodeBuf(env->Bytecode, (VectorItem)OP_STORE);
		AddOpcodeBuf(env->Bytecode, (VectorItem)0);
	}
	CLBC_corutine(self, me, env, ilmethod->parameter_list, ilmethod->statement_list, cctx, scope);
	DeleteCallContext(cctx);
	return true;
}

void CLBC_methods_decl(class_loader* self, il_type* iltype, type* tp, Vector* ilmethods, namespace_* scope) {
	CL_ERROR(self);
	for (int i = 0; i < ilmethods->Length; i++) {
		if(!CLBC_method_decl(self, iltype, tp, AtVector(ilmethods,i),scope)) {
			break;
		}
	}
}

void CLBC_methods_impl(class_loader* self, namespace_* scope, il_type* iltype, type* tp, Vector* ilmethods, Vector* sgmethods) {
	CL_ERROR(self);
	for (int i = 0; i < ilmethods->Length; i++) {
		if(!CLBC_method_impl(self, scope, iltype, tp, AtVector(ilmethods, i), AtVector(sgmethods, i))) {
			break;
		}
		BC_ERROR();
	}
}

//
//ctor
//
//
bool CLBC_ctor_decl(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, namespace_* scope) {
	//メソッドから仮引数一覧を取りだす
	Vector* ilparams = ilcons->parameter_list;
	class_* classz = tp->u.class_;
	//実行時のメソッド情報を作成する
	constructor* cons = NewConstructor();
	Vector* parameter_list = cons->parameter_list;
	cons->access = ilcons->access;
	cons->parent = tp;
	CallContext* cctx = NewCallContext(CALL_CTOR_T);
	cctx->Scope = scope;
	cctx->Ty = tp;
	cctx->Kind.Ctor = cons;
	//NOTE:ここでは戻り値の型,引数の型を設定しません
	//     class_loader_sgload_complete参照
	for (int i = 0; i < ilparams->Length; i++) {
		VectorItem e = AtVector(ilparams, i);
		il_parameter* ilp = (il_parameter*)e;
		Parameter* param = NewParameter(ilp->namev);
		PushVector(parameter_list, param);
	}
	CLBC_parameter_list(self, scope, ilcons->parameter_list, cons->parameter_list, cctx);
	CLBC_parameter_list_ctor(cons->parameter_list);
	AddConstructorClass(classz, cons);
	DeleteCallContext(cctx);
	return true;
}

bool CLBC_ctor_impl(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, constructor* cons, namespace_* scope) {
	//仮引数に型を設定する
	//class_loader_sgload_params(self, scope, ilcons->parameter_list, cons->parameter_list);
	//まずは仮引数の一覧にインデックスを割り振る
	Enviroment* env = NewEnviroment();
	env->ContextRef = self;
	CallContext* cctx = NewCallContext(CALL_CTOR_T);
	cctx->Scope = scope;
	cctx->Ty = tp;
	cctx->Kind.Ctor = cons;
	for (int i = 0; i < cons->parameter_list->Length; i++) {
		il_parameter* ilparam = (il_parameter*)AtVector(ilcons->parameter_list, i);
		EntrySymbolTable(
			env->Symboles,
			ResolveImportManager(scope, ilparam->fqcn, cctx),
			ilparam->namev
		);
		//実引数を保存
		//0番目は this のために開けておく
		AddOpcodeBuf(env->Bytecode, OP_STORE);
		AddOpcodeBuf(env->Bytecode, (i + 1));
	}
	CLBC_chain(self, iltype, tp, ilcons, ilcons->chain, env);
	//NOTE:ここなら名前空間を設定出来る
	CLBC_body(self, ilcons->statement_list, env, cctx, scope);
	cons->env = env;
	DeleteCallContext(cctx);
	return true;
}

void CLBC_ctors_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope) {
	CL_ERROR(self);
	class_* classz = tp->u.class_;
	Vector* ilcons_list = iltype->u.class_->constructor_list;
	for (int i = 0; i < ilcons_list->Length; i++) {
		if(!CLBC_ctor_decl(self, iltype, tp, AtVector(ilcons_list, i), scope)) {
			break;
		}
	}
}

void CLBC_ctors_impl(class_loader* self, il_type* iltype, type* tp) {
	CL_ERROR(self);
	assert(tp->tag == TYPE_CLASS_T);
	class_* classz = tp->u.class_;
	namespace_* scope = classz->location;
	Vector* constructors = classz->constructor_list;
	if (iltype->tag != ilTYPE_CLASS_T) {
		return;
	}
	//既に登録されたが、
	//オペコードが空っぽになっているコンストラクタの一覧
	for (int i = 0; i < constructors->Length; i++) {
		if(!CLBC_ctor_impl(self, iltype, tp, AtVector(iltype->u.class_->constructor_list,i),AtVector(constructors, i), scope)) {
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
	operator_overload* opov = NewOperatorOverload(ilopov->op);
	opov->access = ilopov->access;
	//CallContextの設定
	CallContext* cctx = NewCallContext(CALL_OPOV_T);
	cctx->Scope = scope;
	cctx->Ty = tp;
	cctx->Kind.OpOv = opov;
	//戻り値読み込み
	opov->parent = tp;
	opov->return_gtype = ResolveImportManager(scope, ilopov->return_fqcn, cctx);
	//パラメータ読み込み
	for(int j=0; j<ilopov->parameter_list->Length; j++) {
		il_parameter* ilparam = AtVector(ilopov->parameter_list, j);
		Parameter* param = NewParameter(ilparam->namev);
		PushVector(opov->parameter_list, param);
	}
	CLBC_parameter_list(self, scope, ilopov->parameter_list, opov->parameter_list, cctx);
	PushVector(tp->u.class_->operator_overload_list, opov);
	//オペレータオーバロードの妥当性をテストする
	if(CLBC_test_operator_overlaod(self, iltype, tp, opov)) {
		DeleteCallContext(cctx);
		return false;
	}
	DeleteCallContext(cctx);
	return true;
}

bool CLBC_operator_overload_impl(class_loader* self, il_type* iltype, type* tp, il_operator_overload* ilopov, operator_overload* opov, namespace_* scope) {
	//オペコードを作成
	//FIXME:ILメソッドと実行時メソッドのインデックスが同じなのでとりあえず動く
	//まずは仮引数の一覧にインデックスを割り振る
	Enviroment* env = NewEnviroment();
	CallContext* cctx = NewCallContext(CALL_OPOV_T);
	cctx->Scope = scope;
	cctx->Ty = tp;
	cctx->Kind.OpOv = opov;
	//ccpush_method(me);
	env->ContextRef = self;
	for (int i = 0; i < ilopov->parameter_list->Length; i++) {
		il_parameter* ilparam = (il_parameter*)AtVector(ilopov->parameter_list, i);
		EntrySymbolTable(
			env->Symboles,
			ResolveImportManager(scope, ilparam->fqcn, cctx),
			ilparam->namev
		);
		//実引数を保存
		//0番目は this のために開けておく
		AddOpcodeBuf(env->Bytecode, (VectorItem)OP_STORE);
		AddOpcodeBuf(env->Bytecode, (VectorItem)(i + 1));
	}
	//0番目をthisで埋める
	AddOpcodeBuf(env->Bytecode, (VectorItem)OP_STORE);
	AddOpcodeBuf(env->Bytecode, (VectorItem)0);
	//NOTE:ここなら名前空間を設定出来る
	CLBC_body(self, ilopov->statement_list, env, cctx, scope);
	DeleteCallContext(cctx);
	//ccpop_method();
	opov->env = env;
	return true;
}

void CLBC_operator_overloads_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope) {
	CL_ERROR(self);
	Vector* opov_list = iltype->u.class_->operator_overload_list;
	for (int i = 0; i < opov_list->Length; i++) {
		if(!CLBC_operator_overload_decl(self, iltype, tp, AtVector(opov_list, i), scope)) {
			break;
		}
	}
	//CLBC_default_operator_overload(self, tp);
}

void CLBC_operator_overloads_impl(class_loader* self, il_type* iltype, type* tp, namespace_* scope) {
	CL_ERROR(self);
	Vector* opov_list = tp->u.class_->operator_overload_list;
	//ここで暗黙的に作成される == != によって長さが合わなくなる
	for (int i = 0; i < iltype->u.class_->operator_overload_list->Length; i++) {
		if(!CLBC_operator_overload_impl(self, iltype, tp, AtVector(iltype->u.class_->operator_overload_list, i), AtVector(opov_list, i), scope)) {
			break;
		}
	}
}

bool CLBC_corutine(class_loader* self, method* mt, Enviroment* env,  Vector* ilparams, Vector* ilstmts, CallContext* cctx, namespace_* range) {
	//戻り値が iterator なら、
	//コルーチンとして使えるようにする
	bool yield_err = false;
	if(IsYieldMethod(mt, ilstmts, &yield_err)) {
		if(yield_err) {
			abort();
			return false;
		}
		//メソッド名からクラス名を作成して、
		//beacon::$placeholderへ肩を格納する
		type* iterT = CreateIteratorTypeFromMethod(mt, self, ilstmts);
		AddOpcodeBuf(env->Bytecode, OP_THIS);
		for(int i=0; i<ilparams->Length; i++) {
			AddOpcodeBuf(env->Bytecode, OP_LOAD);
			AddOpcodeBuf(env->Bytecode, i + 1);
		}
		mt->u.script_method->env = env;
		AddOpcodeBuf(env->Bytecode, OP_NEW_INSTANCE);
		AddOpcodeBuf(env->Bytecode, iterT->absolute_index);
		AddOpcodeBuf(env->Bytecode, 0);
		AddOpcodeBuf(env->Bytecode, OP_RETURN);
		return true;
	}
	//NOTE:ここなら名前空間を設定出来る
	CLBC_body(self, ilstmts, env, cctx, range);
	mt->u.script_method->env = env;
	return true;
}

void CLBC_body(class_loader* self, Vector* stmt_list, Enviroment* dest, CallContext* cctx, namespace_* range) {
	CL_ERROR(self);
	//まずは全てのステートメントを読み込む
	for (int i = 0; i < stmt_list->Length; i++) {
		if(GetLastBCError()) {
			break;
		}
		VectorItem e = AtVector(stmt_list, i);
		il_stmt* s = (il_stmt*)e;
		LoadILStmt(s, dest, cctx);
	}
	//オペコードを生成
	for (int i = 0; i < stmt_list->Length; i++) {
		if(GetLastBCError()) {
			break;
		}
		VectorItem e = AtVector(stmt_list, i);
		il_stmt* s = (il_stmt*)e;
		GenerateILStmt(s, dest, cctx);
	}
}

//private
static void CLBC_parameter_list(class_loader* self, namespace_* scope, Vector* param_list, Vector* sg_param_list, CallContext* cctx) {
	for (int j = 0; j < param_list->Length; j++) {
		VectorItem e = AtVector(param_list, j);
		il_parameter* ilparam = (il_parameter*)e;
		//FIXME:ILパラメータと実行時パラメータのインデックスが同じなのでとりあえず動く
		Parameter* mep = (Parameter*)AtVector(sg_param_list, j);
		mep->GType = ResolveImportManager(
			scope,
			ilparam->fqcn,
			cctx
		);
	}
}

static void CLBC_parameter_list_ctor(Vector* param_list) {
	for(int i=0; i<param_list->Length; i++) {
		Parameter* param = AtVector(param_list, i);
		param->GType->is_ctor = true;
	}
}


static void CLBC_chain(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, ILConstructorChain* ilchain, Enviroment* env) {
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

static void CLBC_chain_root(class_loader * self, il_type * iltype, type * tp, il_constructor * ilcons, ILConstructorChain * ilchain, Enviroment * env) {
	AddOpcodeBuf(env->Bytecode, (VectorItem)OP_NEW_OBJECT);
	AddOpcodeBuf(env->Bytecode, (VectorItem)OP_ALLOC_FIELD);
	AddOpcodeBuf(env->Bytecode, (VectorItem)tp->absolute_index);
}

static void CLBC_chain_auto(class_loader * self, il_type * iltype, type * tp, il_constructor * ilcons, ILConstructorChain * ilchain, Enviroment * env) {
	class_* classz = tp->u.class_;
	int emptyTemp = 0;
	CallContext* cctx = NewCallContext(CALL_CTOR_ARGS_T);
	cctx->Ty = tp;
	constructor* emptyTarget = ILFindEmptyConstructorClass(classz->super_class->core_type->u.class_, env, cctx, &emptyTemp);
	DeleteCallContext(cctx);
	//連鎖を明示的に書いていないのに、
	//親クラスにも空のコンストラクタが存在しない=エラー
	//(この場合自動的にチェインコンストラクタを補うことが出来ないため。)
	if(emptyTarget == NULL) {
		ThrowBCError(BCERROR_AUTO_CHAIN_CTOR_NOT_FOUND_T,
			Ref2Str(GetTypeName(tp))
		);
		return;
	}
	assert((emptyTarget != NULL));
	//空のコンストラクタを見つけることが出来たので、
	//自動的にそれへ連鎖するチェインをおぎなう
	ILConstructorChain* ch_empty = NewILConstructorChain();
	ch_empty->c = emptyTarget;
	ch_empty->constructor_index = emptyTemp;
	ch_empty->type = AST_CONSTRUCTOR_CHAIN_SUPER_T;
	ilcons->chain = ch_empty;
	//親クラスへ連鎖
	AddOpcodeBuf(env->Bytecode, (VectorItem)OP_CHAIN_SUPER);
	AddOpcodeBuf(env->Bytecode, (VectorItem)classz->super_class->core_type->absolute_index);
	AddOpcodeBuf(env->Bytecode, (VectorItem)emptyTemp);
	//このクラスのフィールドを確保
	AddOpcodeBuf(env->Bytecode, (VectorItem)OP_ALLOC_FIELD);
	AddOpcodeBuf(env->Bytecode, (VectorItem)tp->absolute_index);
}

static void CLBC_chain_super(class_loader * self, il_type * iltype, type * tp, il_constructor * ilcons, ILConstructorChain * ilchain, Enviroment * env) {
	class_* classz = tp->u.class_;
	//チェインコンストラクタの実引数をプッシュ
	CallContext* cctx = NewCallContext(CALL_CTOR_ARGS_T);
	cctx->Ty = tp;
	ILConstructorChain* chain = ilcons->chain;
	for (int i = 0; i < chain->argument_list->Length; i++) {
		ILArgument* ilarg = (ILArgument*)AtVector(chain->argument_list, i);
		GenerateILFactor(ilarg->Factor, env, cctx);
	}
	//連鎖先のコンストラクタを検索する
	constructor* chainTarget = NULL;
	int temp = 0;
	if (chain->type == CHAIN_TYPE_THIS_T) {
		chainTarget = ILFindConstructorClass(classz, chain->argument_list, env, cctx, &temp);
		AddOpcodeBuf(env->Bytecode, (VectorItem)OP_CHAIN_THIS);
		AddOpcodeBuf(env->Bytecode, (VectorItem)(tp->absolute_index));
	} else if (chain->type == CHAIN_TYPE_SUPER_T) {
		chainTarget = ILFindConstructorClass(classz->super_class->core_type->u.class_, chain->argument_list, env, cctx, &temp);
		AddOpcodeBuf(env->Bytecode, OP_CHAIN_SUPER);
		AddOpcodeBuf(env->Bytecode, classz->super_class->core_type->absolute_index);
	}
	if(chainTarget == NULL) {
		ThrowBCError(BCERROR_EXPLICIT_CHAIN_CTOR_NOT_FOUND_T,
			Ref2Str(GetTypeName(tp))
		);
		return;
	}
	DeleteCallContext(cctx);
	chain->c = chainTarget;
	chain->constructor_index = temp;
	AddOpcodeBuf(env->Bytecode, (VectorItem)temp);
	//親クラスへのチェインなら即座にフィールドを確保
	AddOpcodeBuf(env->Bytecode, (VectorItem)OP_ALLOC_FIELD);
	AddOpcodeBuf(env->Bytecode, (VectorItem)tp->absolute_index);
}

static bool CLBC_test_operator_overlaod(class_loader* self, il_type* iltype, type* tp, operator_overload* opov) {
	//アクセスレベルを確認する
	if(opov->access != ACCESS_PUBLIC_T) {
		ThrowBCError(BCERROR_PRIVATE_OPERATOR_T, GetTypeName(tp));
		return true;
	}
	//二項演算子であるなら引数は1
	if(Is2ArgOperator(opov->type) && opov->parameter_list->Length != 1) {
		ThrowBCError(BCERROR_ARG_COUNT_NOT2_BIOPERATOR_T, GetTypeName(tp), OperatorToString(opov->type));
		return true;
	}
	//単項演算子であるなら引数は0
	if(Is1ArgOperator(opov->type) && opov->parameter_list->Length != 0) {
		ThrowBCError(BCERROR_ARG_COUNT_NOT1_UOPERATOR_T,
			GetTypeName(tp),
			OperatorToString(opov->type)
		);
		return true;
	}
	//配列参照演算子であるあんら引数は1
	if(opov->type == OPERATOR_SUB_SCRIPT_GET_T && opov->parameter_list->Length != 1) {
		ThrowBCError(BCERROR_ARG_COUNT_NOT1_SUBSCRIPT_GET_OP_T,
			GetTypeName(tp),
			OperatorToString(opov->type)
		);
		return true;
	}
	//配列書き込み演算子であるあんら引数は2
	if(opov->type == OPERATOR_SUB_SCRIPT_SET_T && opov->parameter_list->Length != 2) {
		ThrowBCError(BCERROR_ARG_COUNT_NOT2_SUBSCRIPT_SET_OP_T,
			GetTypeName(tp),
			OperatorToString(opov->type)
		);
		return true;
	}
	//== などの比較演算子の戻り値が bool ではない
	if(IsCompareOperator(opov->type) && opov->return_gtype->core_type != TYPE_BOOL) {
		ThrowBCError(BCERROR_RETURN_TYPE_NOT_BOOL_COMPARE_OPERATOR_T,
			Ref2Str(GetTypeName(tp)),
			OperatorToString(opov->type)
		);
		return true;
	}
	//! の戻り値が bool ではない
	if(opov->type == OPERATOR_NOT_T && opov->return_gtype->core_type != TYPE_BOOL) {
		ThrowBCError(BCERROR_RETURN_TYPE_NOT_BOOL_NOT_OPERATOR_T,
			Ref2Str(GetTypeName(tp)),
			OperatorToString(opov->type)
		);
		return true;
	}
	//- の戻り値がクラスと異なる
	//(IntならInt, Vector2ならVector2)
	if(opov->type == OPERATOR_NEGATIVE_T && opov->return_gtype->core_type != opov->parent) {
		ThrowBCError(BCERROR_RETURN_TYPE_NOT_EQUAL_NEGATIVE_OPERATOR_T,
			Ref2Str(GetTypeName(tp)),
			OperatorToString(opov->type)
		);
		return true;
	}
	return false;
}
