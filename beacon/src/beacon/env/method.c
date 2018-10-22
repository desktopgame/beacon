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
#include "../env/class_loader.h"
#include "../util/mem.h"
#include "../thread/thread.h"
#include "../il/call_context.h"
#include "../il/il_stmt_impl.h"
#include "../vm/vm.h"
#include "TYPE_IMPL.h"
#include "type_parameter.h"
#include "generic_type.h"
#include "constructor.h"
#include <assert.h>

#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

//proto
static void method_DeleteParameter(VectorItem item);
static void method_DeleteTypeParameter(VectorItem item);
static void method_count(il_stmt* s, int* yeild_ret, int* ret);
static constructor* create_delegate_ctor(method* self, type* ty, class_loader* cll,int op_len);
static method* create_has_next(method* self, type* ty,class_loader* cll, Vector* stmt_list, int* out_op_len);
static method* create_next(method* self, type* ty,class_loader* cll, generic_type* a, Vector* stmt_list, int* out_op_len);
static Vector* method_vm_args(method* self, frame* fr, frame* a);
static Vector* method_vm_typeargs(method* self, frame* fr, frame* a);

method* MallocMethod(StringView namev, const char* filename, int lineno) {
	method* ret = (method*)mem_malloc(sizeof(method), filename, lineno);
	ret->namev = namev;
	ret->parameters = MallocVector(filename, lineno);
	ret->type = METHOD_TYPE_SCRIPT_T;
	ret->access = ACCESS_PUBLIC_T;
	ret->modifier = MODIFIER_NONE_T;
	ret->parent = NULL;
	ret->type_parameters = MallocVector(filename, lineno);
	ret->return_gtype = NULL;
	return ret;
}

void ExecuteMethod(method* self, frame * fr, Enviroment* env) {
	#if defined(DEBUG)
	const char* namestr = Ref2Str(self->namev);
	if(self->namev == InternString("writeLine")) {
		int a = 0;
	}
	#endif
	if (self->type == METHOD_TYPE_SCRIPT_T) {
		ExecuteScriptMethod(self->u.script_method, self, fr, env);
	} else if (self->type == METHOD_TYPE_NATIVE_T) {
		frame* a = SubFrame(fr);
		call_frame* cfr = NULL;
		Vector* aArgs = NULL;
		Vector* aTArgs = NULL;
		//レシーバも
		if(!IsStaticModifier(self->modifier)) {
			object* receiver_obj = PopVector(fr->value_stack);
			AssignVector(a->ref_stack, 0, receiver_obj);
			cfr = PushCallContext(GetSGThreadCContext(), FRAME_INSTANCE_INVOKE_T);
			cfr->u.instance_invoke.Receiver = receiver_obj->gtype;
			aArgs = cfr->u.instance_invoke.Args = method_vm_args(self, fr, a);
			aTArgs = cfr->u.instance_invoke.TypeArgs = method_vm_typeargs(self, fr, a);
		} else {
			cfr = PushCallContext(GetSGThreadCContext(), FRAME_STATIC_INVOKE_T);
			aArgs = cfr->u.static_invoke.Args = method_vm_args(self, fr, a);
			aTArgs = cfr->u.static_invoke.TypeArgs = method_vm_typeargs(self, fr, a);
		}
		ExecuteNativeMethod(self->u.native_method, self, a, env);
		//戻り値を残す
		//例外によって終了した場合には戻り値がない
		if(self->return_gtype != TYPE_VOID->generic_self &&
	  		 a->value_stack->Length > 0) {
			PushVector(fr->value_stack, PopVector(a->value_stack));
		}
		DeleteVector(aArgs, VectorDeleterOfNull);
		DeleteVector(aTArgs, VectorDeleterOfNull);
		PopCallContext(GetSGThreadCContext());
		DeleteFrame(a);
	}
}

bool IsOverridedMethod(method* superM, method* subM, call_context* cctx) {
	//名前が違うか引数の数が違う
	if (superM->namev != subM->namev ||
		superM->parameters->Length != subM->parameters->Length) {
		return false;
	}
	generic_type* bl = BaselineType(superM->parent, subM->parent);
	assert(bl != NULL);
	//全ての引数を比較
	for (int i = 0; i < superM->parameters->Length; i++) {
		Parameter* superP = ((Parameter*)AtVector(superM->parameters, i));
		Parameter* subP = ((Parameter*)AtVector(subM->parameters, i));
		generic_type* superGT = superP->GType;
		generic_type* subGT = subP->GType;

		call_frame* cfr = PushCallContext(cctx, FRAME_RESOLVE_T);
		cfr->u.resolve.GType = bl;
		generic_type* superGT2 = ApplyGenericType(superGT, cctx);
		PopCallContext(cctx);
//		assert(!generic_type_equals(superGT, superGT2));

//		generic_type_diff(superGT, superGT2);
		if(DistanceGenericType(superGT2, subGT, cctx) != 0) {
			return false;
		}
	}
	generic_type* superRet = superM->return_gtype;
	generic_type* subRet = subM->return_gtype;
	call_frame* cfr = PushCallContext(cctx, FRAME_RESOLVE_T);
	cfr->u.resolve.GType = bl;
	generic_type* superRet2 = ApplyGenericType(superRet, cctx);
//	generic_type_diff(superRet, superRet2);
//	assert(!generic_type_equals(superRet, superRet2));
	int ret =DistanceGenericType(superRet2, subRet, cctx);
	PopCallContext(cctx);
	return ret != -1;
}

int GetGenericIndexForMethod(method * self, StringView namev) {
	int ret = -1;
	for (int i = 0; i < self->type_parameters->Length; i++) {
		TypeParameter* e = (TypeParameter*)AtVector(self->type_parameters, i);
		if (e->Name == namev) {
			ret = i;
			break;
		}
	}
	return ret;
}

void DeleteMethod(method * self) {
	DeleteVector(self->type_parameters, method_DeleteTypeParameter);
	DeleteVector(self->parameters, method_DeleteParameter);
	if (self->type == METHOD_TYPE_SCRIPT_T) {
		DeleteScriptMethod(self->u.script_method);
	} else if (self->type == METHOD_TYPE_NATIVE_T) {
		DeleteNativeMethod(self->u.native_method);
	}
	MEM_FREE(self);
}

StringView MangleMethod(method* self) {
	Buffer* ret = NewBuffer();
	AppendsBuffer(ret, Ref2Str(self->namev));
	//引数が一つもないので終了
	if(self->parameters->Length == 0) {
		char* raw = ReleaseBuffer(ret);
		StringView sv = InternString(raw);
		MEM_FREE(raw);
		return sv;
	}
	for(int i=0; i<self->parameters->Length; i++) {
		Parameter* e = (Parameter*)AtVector(self->parameters, i);
		generic_type* gt = e->GType;
		AppendBuffer(ret, '_');
		if(gt->core_type == NULL) {
			//ジェネリックの場合は methodname_c0 のように
			//何番目の型変数であるかを入れる
			if(gt->tag == GENERIC_TYPE_TAG_CLASS_T) {
				AppendBuffer(ret, 'c');
			} else if(gt->tag == GENERIC_TYPE_TAG_METHOD_T) {
				AppendBuffer(ret, 'm');
			} else {
				assert(false);
			}
			//数値 -> 文字
			char buff[256];
			memset(buff, '\0', 256);
			sprintf(buff, "%d", gt->virtual_type_index);
			AppendsBuffer(ret, buff);
		} else {
			AppendsBuffer(ret, Ref2Str(GetTypeFullName(gt->core_type)));
		}
	}
	char* raw = ReleaseBuffer(ret);
	StringView sv = InternString(raw);
	MEM_FREE(raw);
	return sv;
}

StringView GetMethodUniqueName(method* self) {
	Buffer* ret = NewBuffer();
	AppendsBuffer(ret, Ref2Str(GetTypeFullName(self->parent)));
	AppendsBuffer(ret, Ref2Str(MangleMethod(self)));
	char* raw = ReleaseBuffer(ret);
	StringView sv = InternString(raw);
	MEM_FREE(raw);
	return sv;
}

bool IsCoroutineMethod(method* self) {
	type* iteratorT = FindTypeFromNamespace(GetLangNamespace(), InternString("Iterator"));
	return (iteratorT && self->return_gtype->core_type == iteratorT);
}

bool IsYieldMethod(method* self, Vector* stmt_list, bool* error) {
	(*error) = false;
	if(self->type != METHOD_TYPE_SCRIPT_T || !IsCoroutineMethod(self)) {
		return false;
	}
	int yield_ret = 0;
	int ret = 0;
	for(int i=0; i<stmt_list->Length; i++) {
		int yrtemp = 0;
		int rtemp = 0;
		il_stmt* e = (il_stmt*)AtVector(stmt_list, i);
		method_count(e, &yrtemp, &rtemp);
		yield_ret += yrtemp;
		ret += rtemp;
	}
	//yield return, return の混在
	if(yield_ret > 0 && ret > 0) {
		(*error) = true;
		return true;
	}
	return yield_ret > 0 ? true : false;
}

type* CreateIteratorTypeFromMethod(method* self,  class_loader* cll, Vector* stmt_list) {
	call_context* lCctx = NewCallContext(CALL_CTOR_T);
	call_frame* lCfr = PushCallContext(lCctx, FRAME_RESOLVE_T);
	lCfr->u.resolve.GType = self->return_gtype;
	StringView iterName = GetMethodUniqueName(self);
	type* iterT = FindTypeFromNamespace(GetLangNamespace(), InternString("Iterator"));
	//イテレータの実装クラスを登録
	generic_type* iterImplGT = ApplyGenericType(self->return_gtype, lCctx);
	class_* iterImplC = NewClassProxy(iterImplGT, iterName);
	type* iterImplT = WrapClass(iterImplC);
	AddTypeNamespace(GetPlaceholderNamespace(), iterImplT);
	InitGenericSelf(iterImplT, 0);
	//イテレータのコンストラクタ追加
	int op_len = 0;
	AddMethodClass(iterImplC, create_has_next(self,  iterImplT, cll, stmt_list, &op_len));
	AddMethodClass(iterImplC, create_next(self, iterImplT, cll, AtVector(self->return_gtype->type_args_list, 0), stmt_list, &op_len));
	AddConstructorClass(iterImplC, create_delegate_ctor(self, iterImplT, cll, op_len));
	PopCallContext(lCctx);
	DeleteCallContext(lCctx);
	return iterImplT;
}

//private
static void method_DeleteParameter(VectorItem item) {
	Parameter* e = (Parameter*)item;
	DeleteParameter(e);
}

static void method_DeleteTypeParameter(VectorItem item) {
	TypeParameter* e = (TypeParameter*)item;
	DeleteTypeParameter(e);
}

static void method_count(il_stmt* s, int* yield_ret, int* ret) {
	switch (s->type) {
		case ILSTMT_IF_T:
		{
			//if() { ... }
			il_stmt_if* sif = s->u.if_;
			for(int i=0; i<sif->body->Length; i++) {
				method_count((il_stmt*)AtVector(sif->body, i), yield_ret, ret);
			}
			for(int i=0; i<sif->elif_list->Length; i++) {
				il_stmt_elif* seif = (il_stmt_elif*)AtVector(sif->elif_list, i);
				Vector* body = seif->body;
				for(int j=0; j<body->Length; j++) {
					method_count((il_stmt*)AtVector(body, j), yield_ret, ret);
				}
			}
			for(int i=0; i<sif->else_body->body->Length; i++) {
				il_stmt* e = AtVector(sif->else_body->body, i);
				method_count(e, yield_ret, ret);
			}
			break;
		}
		case ILSTMT_PROC_T:
		case ILSTMT_VARIABLE_DECL_T:
		case ILSTMT_VARIABLE_INIT_T:
			break;
		case ILSTMT_RETURN_T:
			(*ret)++;
			break;
		case ILSTMT_WHILE_T:
		{
			il_stmt_while* whi = s->u.while_;
			for(int i=0; i<whi->statement_list->Length; i++) {
				il_stmt* e = AtVector(whi->statement_list, i);
				method_count(e, yield_ret, ret);
			}
			break;
		}
		case ILSTMT_BREAK_T:
		case ILSTMT_CONTINUE_T:
		case ILSTMT_INFERENCED_TYPE_INIT_T:
			break;
		case ILSTMT_TRY_T:
		{
			il_stmt_try* tr = s->u.try_;
			for(int i=0; i<tr->statement_list->Length; i++) {
				il_stmt* e = (il_stmt*)AtVector(tr->statement_list, i);
				method_count(e, yield_ret, ret);
			}
			Vector* catches = tr->catch_list;
			for(int i=0; i<catches->Length; i++) {
				il_stmt_catch* ce = (il_stmt_catch*)AtVector(catches, i);
				for(int j=0; j<ce->statement_list->Length; j++) {
					il_stmt* e = (il_stmt*)AtVector(ce->statement_list, j);
					method_count(e, yield_ret, ret);
				}
			}
			break;
		}
		case ILSTMT_THROW_T:
		case ILSTMT_ASSERT_T:
		case ILSTMT_DEFER_T:
			break;
		case ILSTMT_YIELD_RETURN_T:
			(*yield_ret)++;
			break;
		case ILSTMT_YIELD_BREAK_T:
		default:
			//ERROR("ステートメントをダンプ出来ませんでした。");
			break;
	}
}

static constructor* create_delegate_ctor(method* self, type* ty, class_loader* cll,int op_len) {
	//イテレータのコンストラクタを作成
	constructor* iterCons = NewConstructor();
	Enviroment* envIterCons = NewEnviroment();
	//コルーチンを生成したオブジェクトを受け取るパラメータ追加
	Parameter* coroOwnerParam = NewParameter(InternString("owner"));
	PushVector(iterCons->parameter_list, coroOwnerParam);
	envIterCons->ContextRef = cll;
	//コルーチンに渡された引数を引き継ぐパラメータ追加
	for(int i=0; i<self->parameters->Length; i++) {
		Parameter* methP = (Parameter*)AtVector(self->parameters, i);
		Parameter* consP = NewParameter(methP->Name);
		consP->GType = methP->GType;
		PushVector(iterCons->parameter_list, consP);
	}
	for (int i = 0; i < iterCons->parameter_list->Length; i++) {
		Parameter* e = (Parameter*)AtVector(iterCons->parameter_list, i);
		EntrySymbolTable(
			envIterCons->Symboles,
			e->GType,
			e->Name
		);
		//実引数を保存
		//0番目は this のために開けておく
		AddOpcodeBuf(envIterCons->Bytecode, (VectorItem)OP_STORE);
		AddOpcodeBuf(envIterCons->Bytecode, (VectorItem)(i + 1));
	}
	//親クラスへ連鎖
	AddOpcodeBuf(envIterCons->Bytecode, (VectorItem)OP_CHAIN_SUPER);
	AddOpcodeBuf(envIterCons->Bytecode, (VectorItem)0);
	AddOpcodeBuf(envIterCons->Bytecode, (VectorItem)0);
	//このクラスのフィールドを確保
	AddOpcodeBuf(envIterCons->Bytecode, (VectorItem)OP_ALLOC_FIELD);
	AddOpcodeBuf(envIterCons->Bytecode, (VectorItem)ty->absolute_index);
	AddOpcodeBuf(envIterCons->Bytecode, OP_CORO_INIT);
	AddOpcodeBuf(envIterCons->Bytecode, iterCons->parameter_list->Length);
	AddOpcodeBuf(envIterCons->Bytecode, op_len);
	iterCons->env = envIterCons;
	return iterCons;
}

static method* create_has_next(method* self, type* ty, class_loader* cll, Vector* stmt_list, int* out_op_len) {
	method* mt = method_new(InternString("moveNext"));
	mt->return_gtype = GENERIC_BOOL;
	mt->modifier = MODIFIER_NONE_T;
	mt->access = ACCESS_PUBLIC_T;
	mt->type = METHOD_TYPE_SCRIPT_T;
	script_method* smt = NewScriptMethod();
	Enviroment* envSmt = NewEnviroment();
	call_context* cctx = NewCallContext(CALL_METHOD_T);
	cctx->scope = self->parent->location;
	cctx->ty = self->parent;
	cctx->u.mt = self;
	envSmt->ContextRef = cll;

	//iterate(int,int)のint,intを受け取る
	for(int i=0; i<self->parameters->Length; i++) {
		Parameter* e = AtVector(self->parameters, i);
		EntrySymbolTable(
			envSmt->Symboles,
			e->GType,
			e->Name
		);
		//実引数を保存
		//0番目は this のために開けておく
		//AddOpcodeBuf(envSmt->Bytecode, (VectorItem)OP_STORE);
		//AddOpcodeBuf(envSmt->Bytecode, (VectorItem)(i + 1));
	}
	AddOpcodeBuf(envSmt->Bytecode, (VectorItem)OP_STORE);
	AddOpcodeBuf(envSmt->Bytecode, (VectorItem)0);
	AddOpcodeBuf(envSmt->Bytecode, (VectorItem)OP_CORO_SWAP_SELF);
	AddOpcodeBuf(envSmt->Bytecode, (VectorItem)OP_CORO_RESUME);
	for(int i=0; i<stmt_list->Length; i++) {
		il_stmt* e = (il_stmt*)AtVector(stmt_list, i);
		LoadILStmt(e, envSmt, cctx);
	}
	for(int i=0; i<stmt_list->Length; i++) {
		il_stmt* e = (il_stmt*)AtVector(stmt_list, i);
		GenerateILStmt(e, envSmt, cctx);
	}
	AddOpcodeBuf(envSmt->Bytecode, OP_CORO_EXIT);
	if(GetTypeName(self->parent) == InternString("Base")) {
	//	DumpEnviromentOp(envSmt, 0);
	}
	(*out_op_len) = envSmt->Bytecode->Instructions->Length;
	DeleteCallContext(cctx);
	smt->env = envSmt;
	mt->u.script_method = smt;
	mt->parent = ty;
	return mt;
}

static method* create_next(method* self, type* ty, class_loader* cll,generic_type* a, Vector* stmt_list, int* out_op_len) {
	method* mt = method_new(InternString("current"));
	mt->return_gtype = a;
	mt->modifier = MODIFIER_NONE_T;
	mt->access = ACCESS_PUBLIC_T;
	mt->type = METHOD_TYPE_SCRIPT_T;
	script_method* smt = NewScriptMethod();
	Enviroment* envSmt = NewEnviroment();
	call_context* cctx = NewCallContext(CALL_METHOD_T);
	cctx->scope = self->parent->location;
	cctx->ty = self->parent;
	cctx->u.mt = mt;

	AddOpcodeBuf(envSmt->Bytecode, (VectorItem)OP_STORE);
	AddOpcodeBuf(envSmt->Bytecode, (VectorItem)0);
	AddOpcodeBuf(envSmt->Bytecode, (VectorItem)OP_CORO_SWAP_SELF);
	AddOpcodeBuf(envSmt->Bytecode, (VectorItem)OP_CORO_CURRENT);

	envSmt->ContextRef = cll;
	cctx->scope = self->parent->location;
	cctx->ty = self->parent;
	cctx->u.mt = self;
	
	smt->env = envSmt;
	mt->u.script_method = smt;
	mt->parent = ty;
	DeleteCallContext(cctx);
	//DumpEnviromentOp(envSmt, 0);
	return mt;
}

static Vector* method_vm_args(method* self, frame* fr, frame* a) {
	Vector* args = NewVector();
	//引数を引き継ぐ
	int len = self->parameters->Length;
	for(int i=0; i<len; i++) {
		object* ARG = PopVector(fr->value_stack);
		assert(ARG != NULL);
		AssignVector(a->ref_stack, (len - i), ARG);
		AssignVector(args, (len - i), ARG->gtype);
	}
	return args;
}

static Vector* method_vm_typeargs(method* self, frame* fr, frame* a) {
	//メソッドに渡された型引数を引き継ぐ
	Vector* typeargs = NewVector();
	int typeparams = self->type_parameters->Length;
	for(int i=0; i<typeparams; i++) {
		VectorItem e = PopVector(fr->type_args_vec);
		AssignVector(a->type_args_vec, (typeparams - i) - 1, e);
		AssignVector(typeargs, (typeparams - i) - 1, e);
	}
	return typeargs;
}