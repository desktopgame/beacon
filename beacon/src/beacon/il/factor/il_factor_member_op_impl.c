#include "il_factor_member_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/generic_cache.h"
#include "../../env/type_interface.h"
#include "../../env/type/class_impl.h"
#include "../../env/field.h"
#include "../../env/class_loader.h"
#include "../../env/property.h"
#include "../../env/import_manager.h"
#include "../../vm/enviroment.h"
#include "../../vm/generate.h"
#include "../../il/il_type_argument.h"
#include "../../il/il_factor_impl.h"

//proto
static void il_factor_member_op_check(il_factor_member_op* self, enviroment* env, call_context* cctx, bool* swap);
static void il_factor_member_op_check_static(il_factor_member_op* self, enviroment* env, call_context* cctx, generic_type* receiver_type, bool* swap);
static void il_factor_member_op_check_prop(il_factor_member_op* self, enviroment* env, call_context* cctx, generic_type* receiver_type,bool* swap);
static void il_factor_member_op_check_static_prop(il_factor_member_op* self, enviroment* env, call_context* cctx, generic_type* receiver_type,bool* swap);
static void il_factor_member_op_typearg_delete(VectorItem item);

il_factor* il_factor_wrap_member_op(il_factor_member_op* self) {
	il_factor* ret = il_factor_new(ILFACTOR_MEMBER_OP_T);
	ret->u.member_ = self;
	self->parent = ret;
	return ret;
}

il_factor_member_op* il_factor_member_op_new(string_view namev) {
	il_factor_member_op* ret = (il_factor_member_op*)MEM_MALLOC(sizeof(il_factor_member_op));
	ret->fact = NULL;
	ret->type_args = NewVector();
	ret->namev = namev;
	ret->index = -1;
	ret->parent = NULL;
	return ret;
}

void il_factor_member_OP_LOAD(il_factor_member_op* self, enviroment* env, call_context* cctx) {
	bool swap;
	il_factor_load(self->fact, env, cctx);
	il_factor_member_op_check(self, env, cctx, &swap);
}

void il_factor_member_op_generate(il_factor_member_op* self, enviroment* env, call_context* cctx) {
	if(!IsStaticModifier(self->f->modifier)) {
		il_factor_generate(self->fact, env, cctx);
	}
	GenerateGetField(env->buf, self->f, self->index);
}

generic_type* il_factor_member_op_eval(il_factor_member_op* self, enviroment* env, call_context* cctx) {
	//il_factor_member_op_checkは、
	//フィールドアクセスとプロパティアクセスを区別して、
	//プロパティなら木構造を入れ替える
	//入れ替えられたなら swap は true になる
	bool swap = false;
	il_factor* parent = self->parent;
	il_factor_member_op_check(self, env, cctx, &swap);
	if(swap) {
		return il_factor_eval(parent, env, cctx);
	}
//	XSTREQ(self->name, "charArray");
	assert(self->fact != NULL);
	if(self->f->gtype->tag == GENERIC_TYPE_TAG_NONE_T) {
		generic_type* a = self->f->gtype;
		return a;
	}
	generic_type* a = il_factor_eval(self->fact, env, cctx);
	return AtVector(a->type_args_list, self->f->gtype->virtual_type_index);
}

char* il_factor_member_op_tostr(il_factor_member_op* self, enviroment* env) {
	string_buffer* sb = NewBuffer();
	char* name = il_factor_tostr(self->fact, env);
	AppendsBuffer(sb, name);
	AppendBuffer(sb, '.');
	AppendsBuffer(sb, Ref2Str(self->namev));
	MEM_FREE(name);
	return ReleaseBuffer(sb);
}

void il_factor_member_op_delete(il_factor_member_op* self) {
	il_factor_delete(self->fact);
	DeleteVector(self->type_args, il_factor_member_op_typearg_delete);
	MEM_FREE(self);
}
//private
static void il_factor_member_op_check(il_factor_member_op* self, enviroment* env, call_context* cctx, bool* swap) {
	(*swap) = false;
	if(self->index != -1) {
		return;
	}
	//レシーバの型を取得
	il_factor* fact = self->fact;
	generic_type* gtype = il_factor_eval(fact, env, cctx);
	BC_ERROR();
	//レシーバの型が特定できない場合は
	//変数名を型として静的フィールドで解決する
	if(gtype == NULL) {
		return il_factor_member_op_check_static(self, env, cctx, gtype, swap);
	}
	//レシーバのインスタンスフィールドを検索
	type* ctype = gtype->core_type;
	assert(ctype->tag == TYPE_CLASS_T);
	int temp = -1;
	self->f = class_find_field_tree(TYPE2CLASS(ctype), self->namev, &temp);
	self->index = temp;
	//インスタンスフィールドではない場合プロパティを検索
	if(temp == -1) {
		il_factor_member_op_check_prop(self, env, cctx, gtype, swap);
	} else {
		#if defined(DEBUG)
		const char* clname = Ref2Str(call_context_class(cctx)->namev);
		#endif
		//フィールドの可視性を確認
		if(!class_accessible_field(call_context_class(cctx), self->f)) {
			ThrowBCError(BCERROR_CAN_T_ACCESS_FIELD_T, Ref2Str(type_name(ctype)), Ref2Str(self->f->namev));
		}
	}
}

static void il_factor_member_op_check_static(il_factor_member_op* self, enviroment* env, call_context* cctx, generic_type* receiver_type, bool* swap) {
	il_factor* fact = self->fact;
	il_factor_variable* ilvar = fact->u.variable_;
	#if defined(DEBUG)
	const char* ilvarname = Ref2Str(ilvar->u.static_->fqcn->namev);
	#endif
	//Name.call
	//の Name を型名として解決する
	generic_type* ref = import_manager_resolvef(cctx->scope, ilvar->u.static_->fqcn, cctx);
	receiver_type = ref;
	//Name.call
	//の call をフィールドとして解決する
	type* ccT = receiver_type->core_type;
	assert(ccT->tag == TYPE_CLASS_T);
	int temp = -1;
	self->f = class_find_sfield_tree(TYPE2CLASS(ccT), self->namev, &temp);
	self->index = temp;
	if(temp == -1) {
		il_factor_member_op_check_static_prop(self, env, cctx, receiver_type, swap);
	}
}

static void il_factor_member_op_check_prop(il_factor_member_op* self, enviroment* env, call_context* cctx, generic_type* receiver_type,bool* swap) {
	int temp = -1;
	#if defined(DEBUG)
	const char* name = Ref2Str(self->namev);
	#endif
	type* ctype = receiver_type->core_type;
	property* p = class_find_property_tree(TYPE2CLASS(ctype), self->namev, &temp);
	il_factor_property* factp = il_factor_property_new();
	factp->fact = self->fact;
	factp->namev = self->namev;
	factp->p = p;
	factp->index = temp;
	self->fact = NULL;
	self->parent->type = ILFACTOR_PROPERTY_T;
	self->parent->u.prop = factp;
	//プロパティの可視性を確認
	if(temp == -1) {
		ThrowBCError(BCERROR_UNDEFINED_PROPERTY_T, Ref2Str(type_name(ctype)), Ref2Str(self->namev));
		il_factor_delete(factp->fact);
		factp->fact = NULL;
	} else if(!class_accessible_property(call_context_class(cctx), p)) {
		ThrowBCError(BCERROR_CAN_T_ACCESS_PROPERTY_T, Ref2Str(type_name(ctype)), Ref2Str(p->namev));
		il_factor_delete(factp->fact);
		factp->fact = NULL;
	}
	il_factor_member_op_delete(self);
	(*swap) = true;
}

static void il_factor_member_op_check_static_prop(il_factor_member_op* self, enviroment* env, call_context* cctx, generic_type* receiver_type,bool* swap) {
	int temp = -1;
	type* ctype = receiver_type->core_type;
	property* p = class_find_sproperty_tree(TYPE2CLASS(ctype), self->namev, &temp);
	il_factor_property* factp = il_factor_property_new();
	factp->fact = self->fact;
	factp->namev = self->namev;
	factp->p = p;
	factp->index = temp;
	self->fact = NULL;
	self->parent->type = ILFACTOR_PROPERTY_T;
	self->parent->u.prop = factp;
	//プロパティの可視性を確認
	if(!class_accessible_property(call_context_class(cctx), p)) {
		ThrowBCError(BCERROR_CAN_T_ACCESS_PROPERTY_T, Ref2Str(type_name(ctype)), Ref2Str(p->namev));
		il_factor_delete(factp->fact);
		factp->fact = NULL;
	}
	il_factor_member_op_delete(self);
	assert(temp != -1);
	(*swap) = true;
	assert(temp != -1);
}


static void il_factor_member_op_typearg_delete(VectorItem item) {
//	generic_cache* e = (generic_cache*)item;
//	generic_cache_delete(e);
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}