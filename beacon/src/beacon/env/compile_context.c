#include "compile_context.h"
#include "../util/mem.h"
#include "namespace.h"
#include "type_impl.h"
#include "method.h"
#include "constructor.h"
#include "fqcn_cache.h"
#include "generic_type.h"

vector* gContextVec = NULL;
static compile_context* compile_context_new();
static void compile_context_delete(compile_context* self);

void cc_push() {
	if(gContextVec == NULL) {
		gContextVec = vector_new();
	}
	compile_context* cc = compile_context_new();
	vector_push(gContextVec, cc);
}

//namespace
void ccpush_namespace(namespace_* e) {
	vector_push(cc_current()->namespace_vec, e);
}

namespace_* cctop_namespace() {
	return vector_top(cc_current()->namespace_vec);
}

namespace_* ccpop_namespace() {
	return vector_pop(cc_current()->namespace_vec);
}

//type

void ccpush_type(type* e) {
	vector_push(cc_current()->type_vec, e);
}

type* cctop_type() {
	return vector_top(cc_current()->type_vec);
}

type* ccpop_type() {
	return vector_pop(cc_current()->type_vec);
}

//method

void ccpush_method(method* e) {
	vector_push(cc_current()->method_vec, e);
}

method* cctop_method() {
	return vector_top(cc_current()->method_vec);
}

method* ccpop_method() {
	return vector_pop(cc_current()->method_vec);
}

bool cchas_method() {
	return cc_current()->method_vec->length > 0;
}

//ctor

void ccpush_ctor(constructor* e) {
	vector_push(cc_current()->ctor_vec, e);
}

constructor* cctop_ctor() {
	return vector_top(cc_current()->ctor_vec);
}

constructor* ccpop_ctor() {
	return vector_pop(cc_current()->ctor_vec);
}

bool cchas_ctor() {
	return cc_current()->ctor_vec->length > 0;
}

//receiver

void ccpush_receiver(generic_type* e) {
	vector_push(cc_current()->receiver_vec, e);
}

generic_type* cctop_receiver() {
	return vector_top(cc_current()->receiver_vec);
}

generic_type* ccpop_receiver() {
	return vector_pop(cc_current()->receiver_vec);
}

generic_type* ccat_receiver(int index) {
	return vector_at(cc_current()->receiver_vec, index);
}

//typeargs

void ccpush_type_args(vector* type_args) {
	vector_push(cc_current()->type_args_vec, type_args);
}

vector* cctop_type_args() {
	return vector_top(cc_current()->type_args_vec);
}

vector* ccpop_type_args() {
	return vector_pop(cc_current()->type_args_vec);
}

//while_start

void ccpush_while_start(label* e) {
	vector_push(cc_current()->while_start_vec, e);
}

label* cctop_while_start() {
	return vector_top(cc_current()->while_start_vec);
}

label* ccpop_while_start() {
	return vector_pop(cc_current()->while_start_vec);
}

//while_end

void ccpush_while_end(label* e) {
	vector_push(cc_current()->while_end_vec, e);
}

label* cctop_while_end() {
	return vector_top(cc_current()->while_end_vec);
}

label* ccpop_while_end() {
	return vector_pop(cc_current()->while_end_vec);
}

compile_context* cc_current() {
	return cc_top();
}

compile_context* cc_top() {
	return vector_top(gContextVec);
}

void cc_pop() {
	compile_context* c = vector_pop(gContextVec);
	compile_context_delete(c);
	//空になったら自動開放
	if(gContextVec->length == 0) {
		vector_delete(gContextVec, vector_deleter_null);
		gContextVec = NULL;
	}
}

struct namespace_* cc_namespace() {
	compile_context* cc = cc_current();
	if(cc->namespace_vec->length == 0) {
		return namespace_lang();
	}
	return cctop_namespace();
}

class_* cc_class(fqcn_cache* cache) {
	compile_context* self = cc_current();
	class_* tp = NULL;
	if (self->namespace_vec->length > 0) {
		namespace_* scope = (namespace_*)vector_top(self->namespace_vec);
		tp = fqcn_class(cache, scope);
	} else {
		tp = fqcn_class(cache, NULL);
	}
	if(tp == NULL) {
		tp = fqcn_class(cache, namespace_lang());
	}
	return tp;

}

void cc_enable(compile_state state) {
	compile_context* cc = cc_current();
	cc->state = cc->state | state;
}

void cc_disable(compile_state state) {
	compile_context* cc = cc_current();
	cc->state = cc->state & (~state);
}

bool cc_test(compile_state state) {
	return (cc_current()->state & state) > 0;
}

//private
static compile_context* compile_context_new() {
	compile_context* ret = (compile_context*)MEM_MALLOC(sizeof(compile_context));
	ret->namespace_vec = vector_new();
	ret->type_vec = vector_new();
	ret->method_vec = vector_new();
	ret->ctor_vec = vector_new();
	ret->while_start_vec = vector_new();
	ret->while_end_vec = vector_new();
	ret->receiver_vec = vector_new();
	ret->type_args_vec = vector_new();
	ret->find_instance = 0;
	ret->find_static = 0;
	ret->class_loader_ref = NULL;
	return ret;
}

static void compile_context_delete(compile_context* self) {

}