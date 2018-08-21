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
static void il_factor_member_op_typearg_delete(vector_item item);

il_factor* il_factor_wrap_member_op(il_factor_member_op* self) {
	il_factor* ret = il_factor_new(ilfactor_member_op_T);
	ret->u.member_ = self;
	self->parent = ret;
	return ret;
}

il_factor_member_op* il_factor_member_op_new(string_view namev) {
	il_factor_member_op* ret = (il_factor_member_op*)MEM_MALLOC(sizeof(il_factor_member_op));
	ret->fact = NULL;
	ret->type_args = vector_new();
	ret->namev = namev;
	ret->index = -1;
	ret->parent = NULL;
	return ret;
}

void il_factor_member_op_dump(il_factor_member_op* self, int depth) {
	io_printi(depth);
	io_printfln("member %s", string_pool_ref2str(self->namev));
	il_factor_dump(self->fact, depth + 1);
	for(int i=0; i<self->type_args->length; i++) {
		generic_cache* e = (generic_cache*)vector_at(self->type_args, i);
		generic_cache_dump(e, depth + 1);
	}
}

void il_factor_member_op_load(il_factor_member_op* self, enviroment* env, call_context* cctx) {
	bool swap;
	il_factor_load(self->fact, env, cctx);
	il_factor_member_op_check(self, env, cctx, &swap);
}

void il_factor_member_op_generate(il_factor_member_op* self, enviroment* env, call_context* cctx) {
	if(!modifier_is_static(self->f->modifier)) {
		il_factor_generate(self->fact, env, cctx);
	}
	generate_get_field(env->buf, self->f, self->index);
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
	if(self->f->gtype->tag == generic_type_tag_none_T) {
		generic_type* a = self->f->gtype;
		return a;
	}
	generic_type* a = il_factor_eval(self->fact, env, cctx);
	return vector_at(a->type_args_list, self->f->gtype->virtual_type_index);
}

char* il_factor_member_op_tostr(il_factor_member_op* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char* name = il_factor_tostr(self->fact, env);
	string_buffer_appends(sb, name);
	string_buffer_append(sb, '.');
	string_buffer_appends(sb, string_pool_ref2str(self->namev));
	MEM_FREE(name);
	return string_buffer_release(sb);
}

void il_factor_member_op_delete(il_factor_member_op* self) {
	il_factor_delete(self->fact);
	vector_delete(self->type_args, il_factor_member_op_typearg_delete);
	MEM_FREE(self);
}

il_factor_member_op* il_factor_cast_member_op(il_factor* fact) {
	assert(fact->type == ilfactor_member_op_T);
	return fact->u.member_;
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
	assert(ctype->tag == type_class_T);
	int temp = -1;
	self->f = class_find_field_tree(TYPE2CLASS(ctype), self->namev, &temp);
	self->index = temp;
	//インスタンスフィールドではない場合プロパティを検索
	if(temp == -1) {
		il_factor_member_op_check_prop(self, env, cctx, gtype, swap);
	} else {
		#if defined(DEBUG)
		const char* clname = string_pool_ref2str(call_context_class(cctx)->namev);
		#endif
		//フィールドの可視性を確認
		if(!class_accessible_field(call_context_class(cctx), self->f)) {
			bc_error_throw(bcerror_can_t_access_field_T, string_pool_ref2str(type_name(ctype)), string_pool_ref2str(self->f->namev));
		}
	}
}

static void il_factor_member_op_check_static(il_factor_member_op* self, enviroment* env, call_context* cctx, generic_type* receiver_type, bool* swap) {
	il_factor* fact = self->fact;
	il_factor_variable* ilvar = IL_FACT2VAR(fact);
	#if defined(DEBUG)
	const char* ilvarname = string_pool_ref2str(ilvar->u.static_->fqcn->namev);
	#endif
	//Name.call
	//の Name を型名として解決する
	generic_type* ref = import_manager_resolvef(cctx->space, ilvar->u.static_->fqcn, cctx);
	receiver_type = ref;
	//Name.call
	//の call をフィールドとして解決する
	type* ccT = receiver_type->core_type;
	assert(ccT->tag == type_class_T);
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
	const char* name = string_pool_ref2str(self->namev);
	#endif
	type* ctype = receiver_type->core_type;
	property* p = class_find_property_tree(TYPE2CLASS(ctype), self->namev, &temp);
	il_factor_property* factp = il_factor_property_new();
	factp->fact = self->fact;
	factp->namev = self->namev;
	factp->p = p;
	factp->index = temp;
	self->fact = NULL;
	self->parent->type = ilfactor_property_T;
	self->parent->u.prop = factp;
	//プロパティの可視性を確認
	if(temp == -1) {
		bc_error_throw(bcerror_undefined_property_T, string_pool_ref2str(type_name(ctype)), string_pool_ref2str(self->namev));
		il_factor_delete(factp->fact);
		factp->fact = NULL;
	} else if(!class_accessible_property(call_context_class(cctx), p)) {
		bc_error_throw(bcerror_can_t_access_property_T, string_pool_ref2str(type_name(ctype)), string_pool_ref2str(p->namev));
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
	self->parent->type = ilfactor_property_T;
	self->parent->u.prop = factp;
	//プロパティの可視性を確認
	if(!class_accessible_property(call_context_class(cctx), p)) {
		bc_error_throw(bcerror_can_t_access_property_T, string_pool_ref2str(type_name(ctype)), string_pool_ref2str(p->namev));
		il_factor_delete(factp->fact);
		factp->fact = NULL;
	}
	il_factor_member_op_delete(self);
	assert(temp != -1);
	(*swap) = true;
	assert(temp != -1);
}


static void il_factor_member_op_typearg_delete(vector_item item) {
//	generic_cache* e = (generic_cache*)item;
//	generic_cache_delete(e);
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}