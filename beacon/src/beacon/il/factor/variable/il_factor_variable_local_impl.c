#include "il_factor_variable_local_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../il_type_argument.h"
#include "../../../env/field.h"
#include "../../../env/property.h"
#include "../../../vm/enviroment.h"
#include "../../../vm/generate.h"
#include "../../../vm/symbol_entry.h"
#include "../../il_argument.h"
#include <string.h>
#include <stdio.h>

static void il_factor_variable_local_delete_typeargs(VectorItem item);
static void il_factor_variable_local_loadImpl(il_factor_variable_local * self, enviroment * env, call_context* cctx);
static void il_factor_variable_local_load_field(il_factor_variable_local * self, enviroment * env, call_context* cctx);
static void il_factor_variable_local_load_property(il_factor_variable_local * self, enviroment * env, call_context* cctx);
static void set_gtype(il_factor_variable_local * self, generic_type* gt);

il_factor_variable_local* il_factor_variable_local_new(string_view namev) {
	il_factor_variable_local* ret = (il_factor_variable_local*)MEM_MALLOC(sizeof(il_factor_variable_local));
	ret->namev = namev;
	ret->type = VARIABLE_LOCAL_UNDEFINED_T;
	ret->type_args = NULL;
	ret->gt = NULL;
	return ret;
}

void il_factor_variable_local_generate(il_factor_variable_local* self, enviroment* env, call_context* cctx) {
	il_factor_variable_local_load(self, env, cctx);
	assert(self->type != VARIABLE_LOCAL_UNDEFINED_T);
	if(self->type == VARIABLE_LOCAL_SCOPE_T) {
		//より深くネストされたブロックで定義された変数
		if(self->u.entry_->scope_depth > env->sym_table->scope_depth) {
			bc_error_throw(
				BCERROR_REF_UNDEFINED_LOCAL_VARIABLE_T,
				Ref2Str(self->namev)
			);
			return;
		}
		opcode_buf_add(env->buf, (VectorItem)OP_LOAD);
		opcode_buf_add(env->buf, (VectorItem)self->u.entry_->index);
	} else if(self->type == VARIABLE_LOCAL_FIELD_T) {
		field* f = self->u.f_with_i.fi;
		if(!IsStaticModifier(f->modifier)) {
			opcode_buf_add(env->buf, OP_THIS);
		}
		generate_get_field(env->buf, f, self->u.f_with_i.index);
	} else if(self->type == VARIABLE_LOCAL_PROPERTY_T) {
		property* p = self->u.p_with_i.p;
		if(!IsStaticModifier(p->modifier)) {
			opcode_buf_add(env->buf, OP_THIS);
		}
		generate_get_property(env->buf, p, self->u.p_with_i.index);
	}
}

void il_factor_variable_local_load(il_factor_variable_local * self, enviroment * env, call_context* cctx) {
	if(self->type != VARIABLE_LOCAL_UNDEFINED_T) {
		return;
	}
	il_factor_variable_local_loadImpl(self, env, cctx);
}

generic_type* il_factor_variable_local_eval(il_factor_variable_local * self, enviroment * env, call_context* cctx) {
	il_factor_variable_local_load(self, env, cctx);
	assert(self->type != VARIABLE_LOCAL_UNDEFINED_T);
	return self->gt;
}

char* il_factor_variable_local_tostr(il_factor_variable_local * self, enviroment * env) {
	return Strdup(Ref2Str(self->namev));
}

void il_factor_variable_local_delete(il_factor_variable_local* self) {
	DeleteVector(self->type_args, il_factor_variable_local_delete_typeargs);
//	generic_type_delete(self->gt);
	MEM_FREE(self);
}
//private
static void il_factor_variable_local_delete_typeargs(VectorItem item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}

static void il_factor_variable_local_loadImpl(il_factor_variable_local * self, enviroment * env, call_context* cctx) {
	//NOTE:変数宣言の後にその変数を使用する場合、
	//factorはload時点でシンボルエントリーを取得しようとするが、
	//stmtはgenerate時点でシンボルテーブルへ書き込むので、
	//NULLになることがある。
	self->type = VARIABLE_LOCAL_SCOPE_T;
	symbol_entry* ent = symbol_table_entry(env->sym_table, NULL, self->namev);
	//ローカル変数として解決出来なかったので、
	//フィールドとして解決する
	if(ent == NULL) {
		il_factor_variable_local_load_field(self, env, cctx);
	} else {
		self->u.entry_ = ent;
		self->gt = ent->gtype;
	}
}

static void il_factor_variable_local_load_field(il_factor_variable_local * self, enviroment * env, call_context* cctx) {
	//対応するフィールドを検索
	self->type = VARIABLE_LOCAL_FIELD_T;
	//NOTE:トップレベルではここが空なので、
	//定義されていない変数とみなせる？
	type* tp = call_context_type(cctx);
	if(tp->tag == TYPE_INTERFACE_T/* この条件は構文規則からして満たさないはず */) {
		bc_error_throw(BCERROR_REF_UNDEFINED_LOCAL_VARIABLE_T, Ref2Str(self->namev));
		return;
	}
	int temp = -1;
#if defined(_MSC_VER)
	field_with_index fwi;
#else
	field_with_index fwi = {};
#endif
	field* f = class_find_field_tree(TYPE2CLASS(tp), self->namev, &temp);
	fwi.fi = f;
	fwi.index = temp;
	self->type = VARIABLE_LOCAL_FIELD_T;
	if(temp == -1) {
		f = class_find_sfield_tree(TYPE2CLASS(tp), self->namev, &temp);
		fwi.fi = f;
		fwi.index = temp;
		self->type = VARIABLE_LOCAL_FIELD_T;
	}
	self->u.f_with_i = fwi;
	if(temp == -1) {
		il_factor_variable_local_load_property(self, env, cctx);
		return;
	//フィールドが見つかったなら可視性を確認する
	} else if(!class_accessible_field(call_context_class(cctx), f)) {
		bc_error_throw(BCERROR_CAN_T_ACCESS_FIELD_T, Ref2Str(call_context_class(cctx)->namev), Ref2Str(f->namev));
		return;
	}
	set_gtype(self, f->gtype);
}

static void il_factor_variable_local_load_property(il_factor_variable_local * self, enviroment * env, call_context* cctx) {
	int temp = -1;
	type* tp = call_context_type(cctx);
	property* p = class_find_property_tree(TYPE2CLASS(tp), self->namev, &temp);
	if(temp == -1) {
		p = class_find_sproperty_tree(TYPE2CLASS(tp), self->namev, &temp);
	}
	if(temp == -1) {
		bc_error_throw(BCERROR_CAN_T_ACCESS_PROPERTY_T, Ref2Str(type_name(tp)), Ref2Str(self->namev));
		return;
	}
#if defined(_MSC_VER)
	property_with_index pwi;
#else
	property_with_index pwi = {};
#endif
	pwi.p = p;
	pwi.index = temp;
	self->type = VARIABLE_LOCAL_PROPERTY_T;
	self->u.p_with_i = pwi;
	//プロパティにアクセスできない
	if(!class_accessible_property(TYPE2CLASS(tp), p)) {
		bc_error_throw(BCERROR_CAN_T_ACCESS_PROPERTY_T, Ref2Str(type_name(tp)), Ref2Str(p->namev));
	}
	set_gtype(self, p->gtype);
}

static void set_gtype(il_factor_variable_local * self, generic_type* gt) {
	//generic_type* gt = f->gtype;
	//virtual_type vt = f->vtype;
	if(gt->tag == GENERIC_TYPE_TAG_NONE_T) {
		self->gt = gt;
	} else if(gt->tag == GENERIC_TYPE_TAG_CLASS_T) {
		self->gt = generic_type_new(NULL);
		self->gt->tag = GENERIC_TYPE_TAG_CLASS_T;
		self->gt->virtual_type_index = gt->virtual_type_index;
	} else if(gt->tag == GENERIC_TYPE_TAG_METHOD_T) {
		self->gt = generic_type_new(NULL);
		self->gt->tag = GENERIC_TYPE_TAG_METHOD_T;
		self->gt->virtual_type_index = gt->virtual_type_index;
	}
}
//private