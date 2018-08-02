#include "method.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../util/text.h"
#include "../util/string_buffer.h"
#include "type_interface.h"
#include "parameter.h"
#include "namespace.h"
#include "object.h"
#include "../util/mem.h"
#include "../il/call_context.h"
#include "../vm/vm.h"
#include "type_parameter.h"
#include "generic_type.h"
#include <assert.h>

//proto
static void method_parameter_delete(vector_item item);
static void method_type_parameter_delete(vector_item item);

method* method_malloc(string_view namev, const char* filename, int lineno) {
	method* ret = (method*)mem_malloc(sizeof(method), filename, lineno);
	ret->namev = namev;
	ret->parameter_list = vector_malloc(filename, lineno);
	ret->type = method_type_script;
	ret->access = access_public;
	ret->modifier = modifier_none;
	ret->parent = NULL;
	ret->type_parameter_list = vector_malloc(filename, lineno);
	ret->return_gtype = NULL;
	return ret;
}

void method_execute(method* self, frame * fr, enviroment* env) {
	if (self->type == method_type_script) {
		script_method_execute(self->u.script_method, self, fr, env);
	} else if (self->type == method_type_native) {
		frame* a = frame_sub(fr);
		//レシーバも
		if(!modifier_is_static(self->modifier)) {
			vector_assign(a->ref_stack, 0, vector_pop(fr->value_stack));
		}
		//引数を引き継ぐ
		int len = self->parameter_list->length;
		for(int i=0; i<len; i++) {
			object* ARG = vector_pop(fr->value_stack);
			assert(ARG != NULL);
			vector_assign(a->ref_stack, (len - i), ARG);
		}
		//メソッドに渡された型引数を引き継ぐ
		int typeparams = self->type_parameter_list->length;
		for(int i=0; i<typeparams; i++) {
			vector_assign(a->type_args_vec, (typeparams - i) - 1, vector_pop(fr->type_args_vec));
		}
		native_method_execute(self->u.native_method, self, a, env);
		//戻り値を残す
		if(self->return_gtype != TYPE_VOID->generic_self) {
			vector_push(fr->value_stack, vector_pop(a->value_stack));
		}
		frame_delete(a);
	}
}

bool method_override(method* superM, method* subM, call_context* cctx) {
	//名前が違うか引数の数が違う
	if (superM->namev != subM->namev ||
		superM->parameter_list->length != subM->parameter_list->length) {
		return false;
	}
	generic_type* bl = type_baseline(superM->parent, subM->parent);
	assert(bl != NULL);
	//全ての引数を比較
	for (int i = 0; i < superM->parameter_list->length; i++) {
		parameter* superP = ((parameter*)vector_at(superM->parameter_list, i));
		parameter* subP = ((parameter*)vector_at(subM->parameter_list, i));
		generic_type* superGT = superP->gtype;
		generic_type* subGT = subP->gtype;

		call_frame* cfr = call_context_push(cctx, call_resolve_T);
		cfr->u.resolve.gtype = bl;
		generic_type* superGT2 = generic_type_apply(superGT, cctx);
		call_context_pop(cctx);
//		assert(!generic_type_equals(superGT, superGT2));

//		generic_type_diff(superGT, superGT2);
		if(generic_type_distance(superGT2, subGT) != 0) {
			return false;
		}
	}
	generic_type* superRet = superM->return_gtype;
	generic_type* subRet = subM->return_gtype;
	call_frame* cfr = call_context_push(cctx, call_resolve_T);
	cfr->u.resolve.gtype = bl;
	generic_type* superRet2 = generic_type_apply(superRet, cctx);
//	generic_type_diff(superRet, superRet2);
//	assert(!generic_type_equals(superRet, superRet2));
	int ret =generic_type_distance(superRet2, subRet);
	call_context_pop(cctx);
	return ret != -1;
}

int method_for_generic_index(method * self, string_view namev) {
	int ret = -1;
	for (int i = 0; i < self->type_parameter_list->length; i++) {
		type_parameter* e = (type_parameter*)vector_at(self->type_parameter_list, i);
		if (e->namev == namev) {
			ret = i;
			break;
		}
	}
	return ret;
}

void method_delete(method * self) {
	vector_delete(self->type_parameter_list, method_type_parameter_delete);
	vector_delete(self->parameter_list, method_parameter_delete);
	if (self->type == method_type_script) {
		script_method_delete(self->u.script_method);
	} else if (self->type == method_type_native) {
		native_method_delete(self->u.native_method);
	}
	MEM_FREE(self);
}

string_view method_mangle(method* self) {
	string_buffer* ret = string_buffer_new();
	string_buffer_appends(ret, string_pool_ref2str(self->namev));
	//引数が一つもないので終了
	if(self->parameter_list->length == 0) {
		char* raw = string_buffer_release(ret);
		string_view sv = string_pool_intern(raw);
		MEM_FREE(raw);
		return sv;
	}
	for(int i=0; i<self->parameter_list->length; i++) {
		parameter* e = (parameter*)vector_at(self->parameter_list, i);
		generic_type* gt = e->gtype;
		string_buffer_append(ret, '_');
		if(gt->core_type == NULL) {
			//ジェネリックの場合は methodname_c0 のように
			//何番目の型変数であるかを入れる
			if(gt->tag == generic_type_tag_class) {
				string_buffer_append(ret, 'c');
			} else if(gt->tag == generic_type_tag_method) {
				string_buffer_append(ret, 'm');
			} else {
				assert(false);
			}
			//数値 -> 文字
			char buff[256];
			memset(buff, '\0', 256);
			sprintf(buff, "%d", gt->virtual_type_index);
			string_buffer_appends(ret, buff);
		} else {
			string_buffer_appends(ret, string_pool_ref2str(type_full_name(gt->core_type)));
		}
	}
	char* raw = string_buffer_release(ret);
	string_view sv = string_pool_intern(raw);
	MEM_FREE(raw);
	return sv;
}

generic_type* method_diff(method* abstract, method* concrete) {
	type* abstractT = abstract->parent;
	type* implT = concrete->parent;
	generic_type* bounds = type_baseline(abstractT, implT);
	return bounds;
}

//private
static void method_parameter_delete(vector_item item) {
	parameter* e = (parameter*)item;
	parameter_delete(e);
}

static void method_type_parameter_delete(vector_item item) {
	type_parameter* e = (type_parameter*)item;
	type_parameter_delete(e);
}