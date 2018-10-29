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
static void method_count(ILStatement* s, int* yeild_ret, int* ret);
static Constructor* create_delegate_ctor(Method* self, type* ty, ClassLoader* cll,int op_len);
static Method* create_has_next(Method* self, type* ty,ClassLoader* cll, Vector* stmt_list, int* out_op_len);
static Method* create_next(Method* self, type* ty,ClassLoader* cll, GenericType* a, Vector* stmt_list, int* out_op_len);
static Vector* method_vm_args(Method* self, Frame* fr, Frame* a);
static Vector* method_vm_typeargs(Method* self, Frame* fr, Frame* a);

Method* MallocMethod(StringView name, const char* filename, int lineno) {
	Method* ret = (Method*)mem_malloc(sizeof(Method), filename, lineno);
	ret->Name = name;
	ret->Parameters = MallocVector(filename, lineno);
	ret->Type = METHOD_TYPE_SCRIPT_T;
	ret->Access = ACCESS_PUBLIC_T;
	ret->Modifier = MODIFIER_NONE_T;
	ret->Parent = NULL;
	ret->TypeParameters = MallocVector(filename, lineno);
	ret->ReturnGType = NULL;
	return ret;
}

void ExecuteMethod(Method* self, Frame* fr, Enviroment* env) {
	#if defined(DEBUG)
	const char* namestr = Ref2Str(self->Name);
	if(self->Name == InternString("writeLine")) {
		int a = 0;
	}
	#endif
	if (self->Type == METHOD_TYPE_SCRIPT_T) {
		ExecuteScriptMethod(self->Kind.Script, self, fr, env);
	} else if (self->Type == METHOD_TYPE_NATIVE_T) {
		Frame* a = SubFrame(fr);
		CallFrame* cfr = NULL;
		Vector* aArgs = NULL;
		Vector* aTArgs = NULL;
		//レシーバも
		if(!IsStaticModifier(self->Modifier)) {
			Object* receiver_obj = PopVector(fr->ValueStack);
			AssignVector(a->VariableTable, 0, receiver_obj);
			cfr = PushCallContext(GetSGThreadCContext(), FRAME_INSTANCE_INVOKE_T);
			cfr->Kind.InstanceInvoke.Receiver = receiver_obj->GType;
			aArgs = cfr->Kind.InstanceInvoke.Args = method_vm_args(self, fr, a);
			aTArgs = cfr->Kind.InstanceInvoke.TypeArgs = method_vm_typeargs(self, fr, a);
		} else {
			cfr = PushCallContext(GetSGThreadCContext(), FRAME_STATIC_INVOKE_T);
			aArgs = cfr->Kind.StaticInvoke.Args = method_vm_args(self, fr, a);
			aTArgs = cfr->Kind.StaticInvoke.TypeArgs = method_vm_typeargs(self, fr, a);
		}
		ExecuteNativeMethod(self->Kind.Native, self, a, env);
		//戻り値を残す
		//例外によって終了した場合には戻り値がない
		if(self->ReturnGType != TYPE_VOID->generic_self &&
	  		 a->ValueStack->Length > 0) {
			PushVector(fr->ValueStack, PopVector(a->ValueStack));
		}
		DeleteVector(aArgs, VectorDeleterOfNull);
		DeleteVector(aTArgs, VectorDeleterOfNull);
		PopCallContext(GetSGThreadCContext());
		DeleteFrame(a);
	}
}

bool IsOverridedMethod(Method* superM, Method* subM, CallContext* cctx) {
	//名前が違うか引数の数が違う
	if (superM->Name != subM->Name ||
		superM->Parameters->Length != subM->Parameters->Length) {
		return false;
	}
	GenericType* bl = BaselineType(superM->Parent, subM->Parent);
	assert(bl != NULL);
	//全ての引数を比較
	for (int i = 0; i < superM->Parameters->Length; i++) {
		Parameter* superP = ((Parameter*)AtVector(superM->Parameters, i));
		Parameter* subP = ((Parameter*)AtVector(subM->Parameters, i));
		GenericType* superGT = superP->GType;
		GenericType* subGT = subP->GType;

		CallFrame* cfr = PushCallContext(cctx, FRAME_RESOLVE_T);
		cfr->Kind.Resolve.GType = bl;
		GenericType* superGT2 = ApplyGenericType(superGT, cctx);
		PopCallContext(cctx);
//		assert(!GenericType_equals(superGT, superGT2));

//		GenericType_diff(superGT, superGT2);
		if(DistanceGenericType(superGT2, subGT, cctx) != 0) {
			return false;
		}
	}
	GenericType* superRet = superM->ReturnGType;
	GenericType* subRet = subM->ReturnGType;
	CallFrame* cfr = PushCallContext(cctx, FRAME_RESOLVE_T);
	cfr->Kind.Resolve.GType = bl;
	GenericType* superRet2 = ApplyGenericType(superRet, cctx);
//	GenericType_diff(superRet, superRet2);
//	assert(!GenericType_equals(superRet, superRet2));
	int ret =DistanceGenericType(superRet2, subRet, cctx);
	PopCallContext(cctx);
	return ret != -1;
}

int GetGenericIndexForMethod(Method * self, StringView namev) {
	int ret = -1;
	for (int i = 0; i < self->TypeParameters->Length; i++) {
		TypeParameter* e = (TypeParameter*)AtVector(self->TypeParameters, i);
		if (e->Name == namev) {
			ret = i;
			break;
		}
	}
	return ret;
}

void DeleteMethod(Method * self) {
	DeleteVector(self->TypeParameters, method_DeleteTypeParameter);
	DeleteVector(self->Parameters, method_DeleteParameter);
	if (self->Type == METHOD_TYPE_SCRIPT_T) {
		DeleteScriptMethod(self->Kind.Script);
	} else if (self->Type == METHOD_TYPE_NATIVE_T) {
		DeleteNativeMethod(self->Kind.Native);
	}
	MEM_FREE(self);
}

StringView MangleMethod(Method* self) {
	Buffer* ret = NewBuffer();
	AppendsBuffer(ret, Ref2Str(self->Name));
	//引数が一つもないので終了
	if(self->Parameters->Length == 0) {
		char* raw = ReleaseBuffer(ret);
		StringView sv = InternString(raw);
		MEM_FREE(raw);
		return sv;
	}
	for(int i=0; i<self->Parameters->Length; i++) {
		Parameter* e = (Parameter*)AtVector(self->Parameters, i);
		GenericType* gt = e->GType;
		AppendBuffer(ret, '_');
		if(gt->CoreType == NULL) {
			//ジェネリックの場合は methodname_c0 のように
			//何番目の型変数であるかを入れる
			if(gt->Tag == GENERIC_TYPE_TAG_CLASS_T) {
				AppendBuffer(ret, 'c');
			} else if(gt->Tag == GENERIC_TYPE_TAG_METHOD_T) {
				AppendBuffer(ret, 'm');
			} else {
				assert(false);
			}
			//数値 -> 文字
			char buff[256];
			memset(buff, '\0', 256);
			sprintf(buff, "%d", gt->VirtualTypeIndex);
			AppendsBuffer(ret, buff);
		} else {
			AppendsBuffer(ret, Ref2Str(GetTypeFullName(gt->CoreType)));
		}
	}
	char* raw = ReleaseBuffer(ret);
	StringView sv = InternString(raw);
	MEM_FREE(raw);
	return sv;
}

StringView GetMethodUniqueName(Method* self) {
	Buffer* ret = NewBuffer();
	AppendsBuffer(ret, Ref2Str(GetTypeFullName(self->Parent)));
	AppendsBuffer(ret, Ref2Str(MangleMethod(self)));
	char* raw = ReleaseBuffer(ret);
	StringView sv = InternString(raw);
	MEM_FREE(raw);
	return sv;
}

bool IsCoroutineMethod(Method* self) {
	type* iteratorT = FindTypeFromNamespace(GetLangNamespace(), InternString("Iterator"));
	return (iteratorT && self->ReturnGType->CoreType == iteratorT);
}

bool IsYieldMethod(Method* self, Vector* stmt_list, bool* error) {
	(*error) = false;
	if(self->Type != METHOD_TYPE_SCRIPT_T || !IsCoroutineMethod(self)) {
		return false;
	}
	int yield_ret = 0;
	int ret = 0;
	for(int i=0; i<stmt_list->Length; i++) {
		int yrtemp = 0;
		int rtemp = 0;
		ILStatement* e = (ILStatement*)AtVector(stmt_list, i);
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

type* CreateIteratorTypeFromMethod(Method* self,  ClassLoader* cll, Vector* stmt_list) {
	CallContext* lCctx = NewCallContext(CALL_CTOR_T);
	CallFrame* lCfr = PushCallContext(lCctx, FRAME_RESOLVE_T);
	lCfr->Kind.Resolve.GType = self->ReturnGType;
	StringView iterName = GetMethodUniqueName(self);
	type* iterT = FindTypeFromNamespace(GetLangNamespace(), InternString("Iterator"));
	//イテレータの実装クラスを登録
	GenericType* iterImplGT = ApplyGenericType(self->ReturnGType, lCctx);
	class_* iterImplC = NewClassProxy(iterImplGT, iterName);
	type* iterImplT = WrapClass(iterImplC);
	AddTypeNamespace(GetPlaceholderNamespace(), iterImplT);
	InitGenericSelf(iterImplT, 0);
	//イテレータのコンストラクタ追加
	int op_len = 0;
	AddMethodClass(iterImplC, create_has_next(self,  iterImplT, cll, stmt_list, &op_len));
	AddMethodClass(iterImplC, create_next(self, iterImplT, cll, AtVector(self->ReturnGType->TypeArgs, 0), stmt_list, &op_len));
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

static void method_count(ILStatement* s, int* yield_ret, int* ret) {
	switch (s->type) {
		case ILSTMT_IF_T:
		{
			//if() { ... }
			ILIf* sif = s->u.if_;
			for(int i=0; i<sif->Body->Length; i++) {
				method_count((ILStatement*)AtVector(sif->Body, i), yield_ret, ret);
			}
			for(int i=0; i<sif->ElifList->Length; i++) {
				ILElif* seif = (ILElif*)AtVector(sif->ElifList, i);
				Vector* body = seif->Body;
				for(int j=0; j<body->Length; j++) {
					method_count((ILStatement*)AtVector(body, j), yield_ret, ret);
				}
			}
			for(int i=0; i<sif->Else->Body->Length; i++) {
				ILStatement* e = AtVector(sif->Else->Body, i);
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
			ILStatement_while* whi = s->u.while_;
			for(int i=0; i<whi->statement_list->Length; i++) {
				ILStatement* e = AtVector(whi->statement_list, i);
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
			ILStatement_try* tr = s->u.try_;
			for(int i=0; i<tr->statement_list->Length; i++) {
				ILStatement* e = (ILStatement*)AtVector(tr->statement_list, i);
				method_count(e, yield_ret, ret);
			}
			Vector* catches = tr->catch_list;
			for(int i=0; i<catches->Length; i++) {
				ILStatement_catch* ce = (ILStatement_catch*)AtVector(catches, i);
				for(int j=0; j<ce->statement_list->Length; j++) {
					ILStatement* e = (ILStatement*)AtVector(ce->statement_list, j);
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

static Constructor* create_delegate_ctor(Method* self, type* ty, ClassLoader* cll,int op_len) {
	//イテレータのコンストラクタを作成
	Constructor* iterCons = NewConstructor();
	Enviroment* envIterCons = NewEnviroment();
	//コルーチンを生成したオブジェクトを受け取るパラメータ追加
	Parameter* coroOwnerParam = NewParameter(InternString("owner"));
	PushVector(iterCons->Parameters, coroOwnerParam);
	envIterCons->ContextRef = cll;
	//コルーチンに渡された引数を引き継ぐパラメータ追加
	for(int i=0; i<self->Parameters->Length; i++) {
		Parameter* methP = (Parameter*)AtVector(self->Parameters, i);
		Parameter* consP = NewParameter(methP->Name);
		consP->GType = methP->GType;
		PushVector(iterCons->Parameters, consP);
	}
	for (int i = 0; i < iterCons->Parameters->Length; i++) {
		Parameter* e = (Parameter*)AtVector(iterCons->Parameters, i);
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
	AddOpcodeBuf(envIterCons->Bytecode, iterCons->Parameters->Length);
	AddOpcodeBuf(envIterCons->Bytecode, op_len);
	iterCons->Env = envIterCons;
	return iterCons;
}

static Method* create_has_next(Method* self, type* ty, ClassLoader* cll, Vector* stmt_list, int* out_op_len) {
	Method* mt = method_new(InternString("moveNext"));
	mt->ReturnGType = GENERIC_BOOL;
	mt->Modifier = MODIFIER_NONE_T;
	mt->Access = ACCESS_PUBLIC_T;
	mt->Type = METHOD_TYPE_SCRIPT_T;
	ScriptMethod* smt = NewScriptMethod();
	Enviroment* envSmt = NewEnviroment();
	CallContext* cctx = NewCallContext(CALL_METHOD_T);
	cctx->Scope = self->Parent->location;
	cctx->Ty = self->Parent;
	cctx->Kind.Method = self;
	envSmt->ContextRef = cll;

	//iterate(int,int)のint,intを受け取る
	for(int i=0; i<self->Parameters->Length; i++) {
		Parameter* e = AtVector(self->Parameters, i);
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
		ILStatement* e = (ILStatement*)AtVector(stmt_list, i);
		LoadILStmt(e, envSmt, cctx);
	}
	for(int i=0; i<stmt_list->Length; i++) {
		ILStatement* e = (ILStatement*)AtVector(stmt_list, i);
		GenerateILStmt(e, envSmt, cctx);
	}
	AddOpcodeBuf(envSmt->Bytecode, OP_CORO_EXIT);
	if(GetTypeName(self->Parent) == InternString("Base")) {
	//	DumpEnviromentOp(envSmt, 0);
	}
	(*out_op_len) = envSmt->Bytecode->Instructions->Length;
	DeleteCallContext(cctx);
	smt->Env = envSmt;
	mt->Kind.Script = smt;
	mt->Parent = ty;
	return mt;
}

static Method* create_next(Method* self, type* ty, ClassLoader* cll,GenericType* a, Vector* stmt_list, int* out_op_len) {
	Method* mt = method_new(InternString("current"));
	mt->ReturnGType = a;
	mt->Modifier = MODIFIER_NONE_T;
	mt->Access = ACCESS_PUBLIC_T;
	mt->Type = METHOD_TYPE_SCRIPT_T;
	ScriptMethod* smt = NewScriptMethod();
	Enviroment* envSmt = NewEnviroment();
	CallContext* cctx = NewCallContext(CALL_METHOD_T);
	cctx->Scope = self->Parent->location;
	cctx->Ty = self->Parent;
	cctx->Kind.Method = mt;

	AddOpcodeBuf(envSmt->Bytecode, (VectorItem)OP_STORE);
	AddOpcodeBuf(envSmt->Bytecode, (VectorItem)0);
	AddOpcodeBuf(envSmt->Bytecode, (VectorItem)OP_CORO_SWAP_SELF);
	AddOpcodeBuf(envSmt->Bytecode, (VectorItem)OP_CORO_CURRENT);

	envSmt->ContextRef = cll;
	cctx->Scope = self->Parent->location;
	cctx->Ty = self->Parent;
	cctx->Kind.Method = self;
	smt->Env = envSmt;
	mt->Kind.Script = smt;
	mt->Parent = ty;
	DeleteCallContext(cctx);
	//DumpEnviromentOp(envSmt, 0);
	return mt;
}

static Vector* method_vm_args(Method* self, Frame* fr, Frame* a) {
	Vector* args = NewVector();
	//引数を引き継ぐ
	int len = self->Parameters->Length;
	for(int i=0; i<len; i++) {
		Object* ARG = PopVector(fr->ValueStack);
		assert(ARG != NULL);
		AssignVector(a->VariableTable, (len - i), ARG);
		AssignVector(args, (len - i), ARG->GType);
	}
	return args;
}

static Vector* method_vm_typeargs(Method* self, Frame* fr, Frame* a) {
	//メソッドに渡された型引数を引き継ぐ
	Vector* typeargs = NewVector();
	int typeparams = self->TypeParameters->Length;
	for(int i=0; i<typeparams; i++) {
		VectorItem e = PopVector(fr->TypeArgs);
		AssignVector(a->TypeArgs, (typeparams - i) - 1, e);
		AssignVector(typeargs, (typeparams - i) - 1, e);
	}
	return typeargs;
}