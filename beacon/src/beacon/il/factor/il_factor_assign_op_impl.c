#include "il_factor_assign_op_impl.h"
#include "../il_factor_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/property.h"
#include "../../env/property_body.h"
#include "../../vm/symbol_entry.h"
#include "../../vm/generate.h"
#include "../../il/il_argument.h"
#include "../../env/field.h"

static void assign_by_namebase(ILAssignOp* self, Enviroment* env, CallContext* cctx);
static void assign_to_field(ILAssignOp* self,ILFactor* receiver, ILFactor* source, StringView namev, Enviroment* env, CallContext* cctx);
static void assign_to_Property(ILAssignOp* self, Enviroment* env, CallContext* cctx);
static void assign_to_array(ILAssignOp* self, Enviroment* env, CallContext* cctx);
static void assign_by_call(ILAssignOp* self, Enviroment* env, CallContext* cctx);
static void assign_by_invoke(ILInvoke* lhs, ILFactor* rhs, Enviroment* env, CallContext* cctx);
static void assign_by_invoke_bound(ILInvokeBound* lhs, ILFactor* rhs, Enviroment* env, CallContext* cctx);
static void check_final(ILFactor* receiver, ILFactor* source, StringView namev, Enviroment* env, CallContext* cctx);
static bool can_assign_to_field(bc_Field* f, ILAssignOp* self, Enviroment* env, CallContext* cctx);
static void generate_assign_to_variable(ILAssignOp* self, Enviroment* env, CallContext* cctx);
static void generate_assign_to_variable_local(ILAssignOp* self, Enviroment* env, CallContext* cctx);

ILFactor* WrapILAssignOp(ILAssignOp* self) {
	ILFactor* ret = NewILFactor(ILFACTOR_ASSIGN_T);
	ret->Kind.AssignOp = self;
	return ret;
}

ILAssignOp* NewILAssignOp() {
	ILAssignOp* ret = (ILAssignOp*)MEM_MALLOC(sizeof(ILAssignOp));
	ret->Left = NULL;
	ret->Right = NULL;
	return ret;
}

void LoadILAssignOp(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->Left, env, cctx);
	LoadILFactor(self->Right, env, cctx);
	//voidは代入できない
	bc_GenericType* gret = EvalILFactor(self->Right, env, cctx);
	BC_ERROR();
	if(gret->CoreType != NULL &&
	   gret->CoreType == BC_TYPE_VOID) {
		   bc_Panic(BCERROR_VOID_ASSIGN_T);
		return;
	}
}

void GenerateILAssignOp(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	if(self->Left->Type == ILFACTOR_VARIABLE_T) {
		generate_assign_to_variable(self, env, cctx);
		//NOTE:constかどうかの検査
	//foo.bar = xxx
	} else if(self->Left->Type == ILFACTOR_MEMBER_OP_T) {
		ILMemberOp* ilmem = self->Left->Kind.MemberOp;
		ILFactor* ilsrc = ilmem->Source;
		if(ilsrc->Type == ILFACTOR_VARIABLE_T) {
			assign_by_namebase(self, env, cctx);
		//インスタンスフィールドへの代入
		} else {
			assign_to_field(self, ilmem->Source, self->Right, ilmem->Name, env, cctx);
		}
	} else if(self->Left->Type == ILFACTOR_PROPERTY_T) {
		assign_to_Property(self, env, cctx);
	} else if(self->Left->Type == ILFACTOR_SUBSCRIPT_T) {
		assign_to_array(self, env, cctx);
	} else if(self->Left->Type == ILFACTOR_CALL_OP_T) {
		assign_by_call(self, env, cctx);
	} else {
		assert(false);
	}
}

bc_GenericType* EvalILAssignOp(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	return EvalILFactor(self->Right, env, cctx);
}

void DeleteILAssignOp(ILAssignOp* self) {
	DeleteILFactor(self->Left);
	DeleteILFactor(self->Right);
	MEM_FREE(self);
}
//private
static void assign_by_namebase(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	ILMemberOp* ilmem = self->Left->Kind.MemberOp;
	ILFactor* ilsrc = ilmem->Source;
	ILVariable* ilvar = ilsrc->Kind.Variable;
	//staticなフィールドへの代入
	if(ilvar->Type == ILVARIABLE_TYPE_STATIC_T) {
		bc_Class* cls = BC_TYPE2CLASS(GetEvalTypeCContext(cctx, ilvar->Kind.Static->FQCN));
		int temp = -1;
		bc_Field* sf = bc_FindSFieldClass(cls, ilmem->Name, &temp);
		assert(temp != -1);
		GenerateILFactor(self->Right, env, cctx);
		GeneratePutField(env->Bytecode, sf, temp);
		//指定の静的フィールドにアクセスできない
		if(!bc_IsAccessibleFieldClass(GetClassCContext(cctx), sf)) {
			bc_Panic(BCERROR_CAN_T_ACCESS_FIELD_T,
				Ref2Str(bc_GetTypeName(cls->Parent)),
				Ref2Str(sf->Name)
			);
			return;
		}
		//finalなので書き込めない
		if(bc_IsFinalModifier(sf->Modifier)) {
			bc_Panic(BCERROR_ASSIGN_TO_FINAL_FIELD_T,
				Ref2Str(bc_GetTypeName(cls->Parent)),
				Ref2Str(sf->Name)
			);
			return;
		}
		//型の互換性を検査
		if(!can_assign_to_field(sf, self, env, cctx)) {
			return;
		}
	} else {
		assign_to_field(self, ilmem->Source, self->Right, ilmem->Name, env, cctx);
	}
}

static void assign_to_field(ILAssignOp* self, ILFactor* receiver, ILFactor* source, StringView namev, Enviroment* env, CallContext* cctx) {
	bc_GenericType* gt = EvalILFactor(receiver, env, cctx);
	bc_Class* cls = BC_TYPE2CLASS(gt->CoreType);
	int temp = -1;
	bc_Field* f = bc_FindTreeFieldClass(cls, namev, &temp);
	assert(temp != -1);
	GenerateILFactor(receiver, env, cctx);
	GenerateILFactor(source, env, cctx);
	GeneratePutField(env->Bytecode, f, temp);
	//型の互換性を検査
	if(!can_assign_to_field(f, self, env, cctx)) {
		return;
	}
	//指定のインスタンスフィールドにアクセスできない
	if(!bc_IsAccessibleFieldClass(GetClassCContext(cctx), f)) {
		bc_Panic(BCERROR_CAN_T_ACCESS_FIELD_T,
			Ref2Str(bc_GetTypeName(cls->Parent)),
			Ref2Str(f->Name)
		);
	}
	check_final(receiver, source, namev, env, cctx);
}

static void assign_to_Property(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	ILPropertyAccess* prop = self->Left->Kind.PropertyAccess;
	bc_Property* pp = prop->Property;
	bool is_static = bc_IsStaticModifier(prop->Property->Modifier);
	BC_ERROR();
	//プロパティへアクセスできない
	if(!bc_IsAccessiblePropertyClass(GetClassCContext(cctx), pp)) {
		bc_Panic(BCERROR_CAN_T_ACCESS_FIELD_T,
			Ref2Str(bc_GetTypeName(pp->Parent)),
			Ref2Str(pp->Name)
		);
		return;
	}
	if(!bc_IsAccessiblePropertyAccessorClass(GetClassCContext(cctx), pp->Set)) {
		bc_Panic(BCERROR_CAN_T_ACCESS_FIELD_T,
			Ref2Str(bc_GetTypeName(pp->Parent)),
			Ref2Str(pp->Name)
		);
		return;
	}
	if(bc_DistanceGenericType(prop->Property->GType, EvalILFactor(self->Right, env, cctx), cctx) < 0) {
		bc_Panic(BCERROR_ASSIGN_NOT_COMPATIBLE_PROPERTY_T,
			Ref2Str(bc_GetTypeName(prop->Property->Parent)),
			Ref2Str(prop->Property->Name)
		);
		return;
	}
	//省略記法なら初期化されてるかチェック
	if(pp->IsShort && !bc_IsStaticModifier(pp->Modifier)) {
		check_final(prop->Source, self->Right, prop->Property->SourceRef->Name, env, cctx);
	}
	BC_ERROR();
	if(!is_static) {
		GenerateILFactor(prop->Source, env, cctx);
	}
	GenerateILFactor(self->Right, env, cctx);
	GeneratePutProperty(env->Bytecode, pp, prop->Index);
}

static void assign_to_array(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	ILSubscript* subs = self->Left->Kind.Subscript;
	GenerateILFactor(subs->Receiver, env, cctx);
	GenerateILFactor(subs->Position, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, subs->Operator);
}

static void assign_by_call(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	ILCallOp* call = self->Left->Kind.Call;
	if(call->Type == ILCALL_TYPE_INVOKE_STATIC_T) {
		bc_Panic(
			BCERROR_LHS_IS_NOT_SUBSCRIPT_T,
			Ref2Str(call->Kind.InvokeStatic->Name)
		);
		return;
	}
	if(call->Type == ILCALL_TYPE_INVOKE_T) {
		assign_by_invoke(call->Kind.Invoke, self->Right, env, cctx);
	} else if(call->Type == ILCALL_TYPE_INVOKE_BOUND_T) {
		assign_by_invoke_bound(call->Kind.InvokeBound, self->Right, env, cctx);
	} else {
		assert(false);
	}
}

static void assign_by_invoke(ILInvoke* lhs, ILFactor* rhs, Enviroment* env, CallContext* cctx) {
	int temp = -1;
	if(lhs->tag != INSTANCE_INVOKE_SUBSCRIPT_T) {
		bc_Panic(BCERROR_ASSIGN_TO_INVOKE_T,
			Ref2Str(lhs->namev)
		);
		return;
	}
	FindSetILInvoke(lhs, rhs, env, cctx, &temp);
	for(int i=0; i<lhs->args->Length; i++) {
		ILArgument* arg = AtVector(lhs->args, i);
		GenerateILFactor(arg->Factor, env, cctx);
	}
	GenerateILFactor(rhs, env, cctx);
	GenerateILFactor(lhs->receiver, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, temp);
	AddOpcodeBuf(env->Bytecode, OP_NOP);
}

static void assign_by_invoke_bound(ILInvokeBound* lhs, ILFactor* rhs, Enviroment* env, CallContext* cctx) {
	int temp = -1;
	FindSetILInvokeBound(lhs, rhs, env, cctx, &temp);
	assert(lhs->Arguments->Length == 1);
	for(int i=0; i<lhs->Arguments->Length; i++) {
		ILArgument* arg = AtVector(lhs->Arguments, i);
		GenerateILFactor(arg->Factor, env, cctx);
	}
	GenerateILFactor(rhs, env, cctx);
	//GenerateILFactor(lhs->receiver, env, cctx);
	SubscriptDescriptor subs = lhs->Kind.Subscript;
	if(subs.Tag == SUBSCRIPT_LOCAL_T) {
		AddOpcodeBuf(env->Bytecode, OP_LOAD);
		AddOpcodeBuf(env->Bytecode, subs.Index);
	} else if(subs.Tag == SUBSCRIPT_FIELD_T) {
		AddOpcodeBuf(env->Bytecode, OP_THIS);
		GenerateGetField(env->Bytecode, subs.Kind.Field, subs.Index);
	} else if(subs.Tag == SUBSCRIPT_PROPERTY_T) {
		AddOpcodeBuf(env->Bytecode, OP_THIS);
		GenerateGetProperty(env->Bytecode, subs.Kind.Property, subs.Index);
	}
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, temp);
}

static bool can_assign_to_field(bc_Field* f, ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	bc_GenericType* gt = EvalILFactor(self->Right, env, cctx);
	int dist = bc_DistanceGenericType(f->GType, gt, cctx);
	if(dist >= 0) {
		return true;
	} else {
		bc_Panic(BCERROR_ASSIGN_NOT_COMPATIBLE_FIELD_T,
			Ref2Str(bc_GetTypeName(f->Parent)),
			Ref2Str(f->Name)
		);
		return false;
	}
}

static void check_final(ILFactor* receiver, ILFactor* source, StringView namev, Enviroment* env, CallContext* cctx) {
	bc_GenericType* gt = EvalILFactor(receiver, env, cctx);
	bc_Class* cls = BC_TYPE2CLASS(gt->CoreType);
	int temp = -1;
	bc_Field* f = bc_FindTreeFieldClass(cls, namev, &temp);
	assert(temp != -1);
	//コンストラクタ以外の場所では finalフィールドは初期化できない
	if(cctx->Tag != CALL_CTOR_T) {
		//finalなので書き込めない
		if(bc_IsFinalModifier(f->Modifier)) {
			bc_Panic(BCERROR_ASSIGN_TO_FINAL_FIELD_T,
				Ref2Str(bc_GetTypeName(cls->Parent)),
				Ref2Str(f->Name)
			);
		}
	} else {
		//コンストラクタであっても static final の場合は書き込めない
		if(bc_IsFinalModifier(f->Modifier) &&
		   bc_IsStaticModifier(f->Modifier)) {
			bc_Panic(BCERROR_ASSIGN_TO_FINAL_FIELD_T,
				Ref2Str(bc_GetTypeName(cls->Parent)),
				Ref2Str(f->Name)
			);
		}
		f->IsNotInitializedAtCtor = true;
	}

}

static void generate_assign_to_variable(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	assert(self->Left->Type == ILFACTOR_VARIABLE_T);
	ILVariable* ilvar = self->Left->Kind.Variable;
	if(ilvar->Type == ILVARIABLE_TYPE_LOCAL_T) {
		generate_assign_to_variable_local(self, env, cctx);
	}
}

static void generate_assign_to_variable_local(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	ILVariable* ilvar = self->Left->Kind.Variable;
	ILVariableLocal* illoc = ilvar->Kind.Local;
	//src のような名前がローカル変数を示す場合
	if(illoc->Type == VARIABLE_LOCAL_SCOPE_T) {
		#if defined(DEBUG)
		const char* vname = Ref2Str(ilvar->FQCN->Name);
		#endif
		SymbolEntry* e = EntrySymbolTable(env->Symboles, NULL, ilvar->FQCN->Name);
		//e==NULL の時変数がない
		GenerateILFactor(self->Right, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_STORE);
		AddOpcodeBuf(env->Bytecode, e->Index);
		if(bc_DistanceGenericType(e->GType, EvalILFactor(self->Right, env, cctx), cctx) < 0) {
			bc_Panic(BCERROR_ASSIGN_NOT_COMPATIBLE_LOCAL_T,
				Ref2Str(ilvar->FQCN->Name)
			);
			return;
		}
	//src のような名前がフィールドを示す場合
	} else if(illoc->Type == VARIABLE_LOCAL_FIELD_T) {
		int temp = -1;
		bc_Field* f = bc_FindTreeFieldClass(GetClassCContext(cctx), illoc->Name, &temp);
		if(temp == -1) {
			f = bc_FindTreeSFieldClass(GetClassCContext(cctx), illoc->Name, &temp);
		}
		assert(temp != -1);
		//フィールドはstaticでないが
		//現在のコンテキストはstaticなので this にアクセスできない
		if(!bc_IsStaticModifier(f->Modifier) &&
		    IsStaticCContext(cctx)) {
			bc_Panic(BCERROR_ACCESS_TO_THIS_AT_STATIC_METHOD_T,
				Ref2Str(bc_GetTypeName(f->Parent)),
				Ref2Str(f->Name)
			);
			return;
		}
		if(!bc_IsStaticModifier(f->Modifier)) {
			AddOpcodeBuf(env->Bytecode, OP_THIS);
		}
		GenerateILFactor(self->Right, env, cctx);
		GeneratePutField(env->Bytecode, f, temp);
		//assert(!IsStaticModifier(f->modifier));
	//src のような名前がプロパティを示す場合
	} else if(illoc->Type == VARIABLE_LOCAL_PROPERTY_T) {
		int temp = -1;
		bc_Property* p = bc_FindTreePropertyClass(GetClassCContext(cctx), illoc->Name, &temp);
		assert(temp != -1);
		//フィールドはstaticでないが
		//現在のコンテキストはstaticなので this にアクセスできない
		if(!bc_IsStaticModifier(p->Modifier) &&
		    IsStaticCContext(cctx)) {
			bc_Panic(BCERROR_ACCESS_TO_THIS_AT_STATIC_METHOD_T,
				Ref2Str(bc_GetTypeName(p->Parent)),
				Ref2Str(p->Name)
			);
			return;
		}
		if(!bc_IsStaticModifier(p->Modifier)) {
			AddOpcodeBuf(env->Bytecode, OP_THIS);
		}
		GenerateILFactor(self->Right, env, cctx);
		GeneratePutProperty(env->Bytecode, p, temp);
		assert(!bc_IsStaticModifier(p->Modifier));
	}
}