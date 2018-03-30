#include "il_factor_call_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../il_argument.h"
#include "../il_type_argument.h"
#include "../il_factor_impl.h"
#include "../../env/namespace.h"
#include <string.h>
#include <assert.h>

//proto
static void il_factor_call_op_argument_delete(vector_item item);
static void il_factor_call_op_type_argument_delete(vector_item item);

il_factor* il_factor_wrap_call_op(il_factor_call_op* self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_call_op;
	ret->u.op_call_ = self;
	self->parent = ret;
	return ret;
}

il_factor_call_op* il_factor_call_op_new() {
	il_factor_call_op* ret = (il_factor_call_op*)MEM_MALLOC(sizeof(il_factor_call_op));
	ret->receiver = NULL;
	ret->argument_list = vector_new();
	return ret;
}

void il_factor_call_op_load(il_factor_call_op* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh) {
	/*
	assert(self->receiver != NULL);
	//もし receiver が il_factor_name_reference
	//なら、ここでより具体的な型に決定する
	il_factor_load(self->receiver, env, cache, eh);
	//getFoo().a ()
	if(self->receiver->type == ilfactor_field_access) {
		il_factor_field_access* temp = self->receiver->u.field_access_;
		//静的メソッドの呼び出しかもしれないので
		if(temp->fact->type == ilfactor_variable) {
			namespace_* scope = il_load_cache_namespace(cache);
			char* type_name = temp->fact->u.variable_->name;
			char* access_name = temp->name;
			type* tp = namespace_get_type(scope, type_name);
			if(tp != NULL) {
				il_factor_named_invoke* namedinvoke = il_factor_named_invoke_new(access_name);
				//入れ替える
				vector_delete(namedinvoke->type_argument_list, vector_deleter_free);
				vector_delete(namedinvoke->argument_list, vector_deleter_free);

				namedinvoke->argument_list = self->argument_list;
				namedinvoke->type_argument_list = temp->type_argument_list;
				namedinvoke->fqcn->fqcn->name = text_strdup(type_name);
				//古いのを削除
				self->argument_list = NULL;
				temp->type_argument_list = NULL;

				self->parent->type = ilfactor_named_invoke;
				self->parent->u.named_invoke_ = namedinvoke;

				il_factor_load(self->parent, env, cache, eh);
				il_factor_call_op_delete(self);
				return;
			}
		}

		il_factor_invoke* ilinvoke = il_factor_invoke_new(temp->name);
		//入れ替える
		vector_delete(ilinvoke->type_argument_list, vector_deleter_free);
		vector_delete(ilinvoke->argument_list, vector_deleter_free);

 		ilinvoke->receiver = temp->fact;
		ilinvoke->type_argument_list = temp->type_argument_list;
		ilinvoke->argument_list = self->argument_list;
		//古いのを削除
		temp->fact = NULL;
		temp->type_argument_list = NULL;
		self->argument_list = NULL;

		self->parent->type = ilfactor_invoke;
		self->parent->u.invoke_ = ilinvoke;

		il_factor_load(self->parent, env, cache, eh);
		il_factor_call_op_delete(self);
	//Hoge::Huga.Piyo ()
	} else if(self->receiver->type == ilfactor_static_field_access) {
		il_factor_static_field_access* temp = self->receiver->u.static_field_access;
		il_factor_named_invoke* ilnamedinvoke = il_factor_named_invoke_new(temp->name);
		//入れ替える
		vector_delete(ilnamedinvoke->argument_list, vector_deleter_free);
		vector_delete(ilnamedinvoke->type_argument_list, vector_deleter_free);

		ilnamedinvoke->fqcn = temp->fqcn;
		ilnamedinvoke->argument_list = self->argument_list;
		ilnamedinvoke->type_argument_list = temp->type_argument_list;

		//古いのを削除
		temp->fqcn = NULL;
		self->argument_list = NULL;
		temp->type_argument_list = NULL;
		self->parent->type = ilfactor_named_invoke;
		self->parent->u.named_invoke_ = ilnamedinvoke;

		il_factor_load(self->parent, env, cache, eh);
		il_factor_call_op_delete(self);
	//call ()
	} else if(self->receiver->type == ilfactor_variable) {
		il_factor_variable* ilvar = self->receiver->u.variable_;
		il_factor_call* ilcall = il_factor_call_new(ilvar->name);
		//入れ替える
		vector_delete(ilcall->argument_list, vector_deleter_free);
		vector_delete(ilcall->type_argument_list, vector_deleter_free);

		ilcall->argument_list = self->argument_list;
		ilcall->type_argument_list = ilvar->type_argument_list;
		self->argument_list = NULL;
		ilvar->type_argument_list = NULL;
		//古いのを消す
		self->parent->type = ilfactor_call;
		self->parent->u.call_ = ilcall;

		il_factor_load(self->parent, env, cache, eh);
		il_factor_call_op_delete(self);
	//C#のデリゲート呼び出しは今の所実装する予定なし。
	} else assert(false);
	*/
}

generic_type* il_factor_call_op_eval(il_factor_call_op* self, struct enviroment* env, il_load_cache* cache) {
	il_factor_call_op_load(self, env, cache, NULL);
	return il_factor_eval(self->parent, env, cache);
}

void il_factor_call_op_generate(il_factor_call_op* self, struct enviroment* env, il_load_cache* cache) {
	il_factor_call_op_load(self, env, cache, NULL);
	il_factor_generate(self->parent, env, cache);
}

void il_factor_call_op_delete(il_factor_call_op* self) {
	il_factor_delete(self->receiver);
	MEM_FREE(self);
}

il_factor_call_op* il_factor_cast_call_op(il_factor* fact) {
	assert(fact->type == ilfactor_call_op);
	return fact->u.call_;
}

//private
static void il_factor_call_op_argument_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_call_op_type_argument_delete(vector_item item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}