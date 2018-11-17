#include "generic_type.h"
#include "type_interface.h"
#include "TYPE_IMPL.h"
#include "script_context.h"
#include "type_parameter.h"
#include "constructor.h"
#include "../env/object.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../il/il_type_argument.h"
#include "../vm/frame.h"
#include "fqcn_cache.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

//proto
static GenericType* apply_impl(GenericType* self, CallContext* cctx, Frame* fr);
static int distance_impl(GenericType* self, GenericType* other, Frame* fr, CallContext* cctx);
static int distance_nogeneric(GenericType* self, GenericType* other, Frame* fr, CallContext* cctx);
static int distance_class(int dist, GenericType* self, GenericType* other, Frame* fr, CallContext* cctx);
static int distance_interface(int dist, GenericType* self, GenericType* other, Frame* fr, CallContext* cctx);
static Vector* apply_by_hierarchy(GenericType* impl_baseline, GenericType* impl);
static GenericType* typeargs_at(CallContext* cctx, Frame* fr, int index);
static GenericType* receiver_at(CallContext* cctx, Frame* fr, int index);
static void delete_self(VectorItem item);
static void delete_recursive_self(VectorItem item);
static void recursive_mark(GenericType* a);
static GenericType* get_generic(GenericType* a);
/*
GenericType * NewGenericType(Type* CoreType) {

}
*/

GenericType* RefGenericType(Type* CoreType) {
	if(CoreType == NULL) {
		return NewGenericType(CoreType);
	}
	return CoreType->GenericSelf;
}

GenericType* MallocGenericType(struct Type* CoreType, const char* filename, int lineno) {
	GenericType* ret = (GenericType*)bc_MXMalloc(sizeof(GenericType), filename, lineno);
	ret->CoreType = CoreType;
	ret->TypeArgs = NewVector();
	ret->VirtualTypeIndex = -1;
	ret->Tag = GENERIC_TYPE_TAG_NONE_T;
	ret->IsCtor = false;
	//現在のスクリプトコンテキストに登録
	ScriptContext* ctx = GetCurrentScriptContext();
	PushVector(ctx->AllGenericList, ret);
	return ret;
}

GenericType* CloneGenericType(GenericType* self) {
	GenericType* a = NewGenericType(self->CoreType);
	for(int i=0; i<self->TypeArgs->Length; i++) {
		GenericType* e = AtVector(self->TypeArgs, i);
		AddArgsGenericType(a, CloneGenericType(e));
	}
	a->Tag = self->Tag;
	a->VirtualTypeIndex = self->VirtualTypeIndex;
	if(a->Tag == GENERIC_TYPE_TAG_CLASS_T) {
		a->Kind.Type = self->Kind.Type;
	} else if(a->Tag == GENERIC_TYPE_TAG_METHOD_T) {
		a->Kind.Method = self->Kind.Method;
	}
	return a;
}

void CollectGenericType() {
	ScriptContext* ctx = GetCurrentScriptContext();
	//マークを外す
	for(int i=0; i<ctx->AllGenericList->Length; i++) {
		GenericType* e= (GenericType*)AtVector(ctx->AllGenericList, i);
		e->IsMark = false;
	}
	//全ての型に定義された自身を参照するための generic をマーク
	for(int i=0; i<ctx->TypeList->Length; i++) {
		Type* e= (Type*)AtVector(ctx->TypeList, i);
		recursive_mark(e->GenericSelf);
	}
	Vector* alive = NewVector();
	Vector* dead = NewVector();
	for(int i=0; i<ctx->AllGenericList->Length; i++) {
		GenericType* e= (GenericType*)AtVector(ctx->AllGenericList, i);
		PushVector((!e->IsMark ? dead : alive), e);
	}
	DeleteVector(ctx->AllGenericList, VectorDeleterOfNull);
	DeleteVector(dead, delete_self);
	ctx->AllGenericList = alive;
}

void LostownershipGenericType(GenericType* a) {
	//enumはクラスの一種だが、
	//generic_Selfを持たない
	if(a == NULL) {
		return;
	}
	assert(a->CoreType != NULL);
	assert(a->CoreType->GenericSelf == a);
	delete_recursive_self(a);
}

void AddArgsGenericType(GenericType* self, GenericType* a) {
	assert(a != NULL);
	PushVector(self->TypeArgs, a);
}

int DistanceGenericType(GenericType * self, GenericType * other, CallContext* cctx) {
	return distance_impl(self, other, NULL, cctx);
}

int RDistanceGenericType(GenericType* self, GenericType* other, Frame* fr) {
	return distance_impl(self, other, fr, NULL);
}

void PrintGenericType(GenericType * self) {
	assert(self != NULL);
	//タグを出力
	switch(self->Tag) {
		case GENERIC_TYPE_TAG_NONE_T:
			printf("::");
			break;
		case GENERIC_TYPE_TAG_CLASS_T:
			printf("@@");
			break;
		case GENERIC_TYPE_TAG_METHOD_T:
			printf("##");
			break;
	}
	//T, Uなど
	if (self->VirtualTypeIndex != -1) {
		//(Array)[0]
		if(self->Tag == GENERIC_TYPE_TAG_CLASS_T) {
			printf("(%s)", Ref2Str(GetTypeName(self->Kind.Type)));
		//copy[0]
		} else if(self->Tag == GENERIC_TYPE_TAG_METHOD_T) {
			printf("(%s)", Ref2Str(self->Kind.Method->Name));
		}
		printf("[%d]", self->VirtualTypeIndex);
	//Intなど
	} else {
		printf("%s", Ref2Str(GetTypeName(self->CoreType)));
	}
	if(self->IsCtor) {
		printf("!!");
	}
	if (self->TypeArgs->Length == 0) {
		return;
	}
	//[...]
	printf("[");
	for (int i = 0; i < self->TypeArgs->Length; i++) {
		GenericType* e = (GenericType*)AtVector(self->TypeArgs, i);
		PrintGenericType(e);
		if (i != self->TypeArgs->Length - 1) {
			printf(",");
		}
	}
	printf("]");
}

void GenerateGenericType(GenericType* self, Enviroment* env) {
	AddOpcodeBuf(env->Bytecode, OP_GENERIC_ENTER);
	AddOpcodeBuf(env->Bytecode, self->TypeArgs->Length);
	if(self->CoreType == NULL) {
		if(self->Tag == GENERIC_TYPE_TAG_CLASS_T) {
			AddOpcodeBuf(env->Bytecode, OP_GENERIC_INSTANCE_TYPE);
			AddOpcodeBuf(env->Bytecode, self->VirtualTypeIndex);
			//assert(self->VirtualTypeIndex != -1);
		} else {
			AddOpcodeBuf(env->Bytecode, OP_GENERIC_STATIC_TYPE);
			AddOpcodeBuf(env->Bytecode, self->VirtualTypeIndex);
		}
	} else {
		AddOpcodeBuf(env->Bytecode, OP_GENERIC_UNIQUE_TYPE);
		AddOpcodeBuf(env->Bytecode, self->CoreType->AbsoluteIndex);
	}
	for(int i=0; i<self->TypeArgs->Length; i++) {
		GenericType* e = (GenericType*)AtVector(self->TypeArgs, i);
		GenerateGenericType(e, env);
	}
	AddOpcodeBuf(env->Bytecode, OP_GENERIC_EXIT);
}

//Hash<String,List<Int>>
GenericType* ApplyGenericType(GenericType* self, CallContext* cctx) {
	return apply_impl(self, cctx, NULL);
}

GenericType* RApplyGenericType(GenericType* self, CallContext* cctx, Frame* fr) {
	return apply_impl(self, cctx, fr);
}

struct Type* GenericTypeToType(GenericType* self) {
	return self->CoreType;
}

//private
static GenericType* apply_impl(GenericType* self, CallContext* cctx, Frame* fr) {
	int count = 0;
	//型変数なら変換
	GenericType* ret = NULL;
	if(self->VirtualTypeIndex != -1) {
		count++;
		if(self->Tag == GENERIC_TYPE_TAG_CLASS_T) {
			if(self->IsCtor) {
				ret = CloneGenericType(typeargs_at(cctx, fr, self->VirtualTypeIndex));
			} else {
				ret = CloneGenericType(receiver_at(cctx, fr, self->VirtualTypeIndex));
			}
		} else if(self->Tag == GENERIC_TYPE_TAG_METHOD_T) {
			ret = CloneGenericType(typeargs_at(cctx, fr, self->VirtualTypeIndex));
		}
	} else {
		ret = NewGenericType(self->CoreType);
		ret->Tag = self->Tag;
		ret->VirtualTypeIndex = self->VirtualTypeIndex;
	}
	assert(ret != NULL);
	for(int i=0; i<self->TypeArgs->Length; i++) {
		AddArgsGenericType(ret, ApplyGenericType(AtVector(self->TypeArgs, i), cctx));
	}
	return ret;
}

static int distance_impl(GenericType* self, GenericType* other, Frame* fr, CallContext* cctx) {
	if(fr != NULL) {
		return distance_nogeneric(self, other, fr, cctx);
	}
	//要求されている型は T
	if(self->CoreType == NULL) {
		//提供されているのは T
		if(other->CoreType == NULL) {
			return 0;
		//提供されているのは具体的な型
		} else {
			//具体的な型が T のルールを満たしているか？
			return 0;
		}
	//提供している型は T
	} else if(other->CoreType == NULL) {
		//要求されているのは具体的な型
		if(self->CoreType != NULL) {
			//Object型にのみ変換可能
			if(self->CoreType == TYPE_OBJECT) {
				return 0;
			}
			//T が 具体的な型の要件を満たしているか？
			return -1;
		//要求されているのは T
		} else {
			return 0;
		}
	//どちらも具体的な型
	} else {
		return distance_nogeneric(self, other, fr, cctx);
	}
}

static int distance_nogeneric(GenericType* self, GenericType* other, Frame* fr, CallContext* cctx) {
	assert(self->CoreType != NULL);
	assert(other->CoreType != NULL);
	int dist = DistanceType(self->CoreType, other->CoreType);
	assert(self->CoreType != NULL);
	assert(other->CoreType != NULL);
	#if defined(DEBUG)
	const char* sname = Ref2Str(GetTypeName(self->CoreType));
	const char* oname = Ref2Str(GetTypeName(other->CoreType));
	#endif
	//List : Dict みたいな型ならもうこの時点で次へ
	if(dist == -1) {
		return dist;
	}
	if(other->CoreType == TYPE_NULL) {
		return 1;
	}
	if (self->CoreType->Tag == TYPE_CLASS_T) {
		return distance_class(dist, self, other, fr, cctx);
	} else if (self->CoreType->Tag == TYPE_INTERFACE_T) {
		return distance_interface(dist, self, other, fr, cctx);
	}
	return dist;
}

static int distance_class(int dist, GenericType* self, GenericType* other, Frame* fr, CallContext* cctx) {
	//otherからselfまで辿る
	Class* baseline = self->CoreType->Kind.Class;
	Class* ptr = other->CoreType->Kind.Class;
	GenericType* target = other;
	while (baseline != ptr) {
		target = ptr->SuperClass;
		ptr = ptr->SuperClass->CoreType->Kind.Class;
	}
	assert(target != NULL);
	assert(self->TypeArgs->Length == target->TypeArgs->Length);
	for (int i = 0; i<self->TypeArgs->Length; i++) {
		GenericType* a = AtVector(self->TypeArgs, i);
		GenericType* b = AtVector(target->TypeArgs, i);
		int calc = distance_impl(a, b, fr, cctx);
		if (calc == -1 || calc > 0) {
			dist = -1;
			break;
		}
	}
	return dist;
}

static int distance_interface(int dist, GenericType* self, GenericType* other, Frame* fr, CallContext* cctx) {
	if (other->CoreType->Tag == TYPE_CLASS_T) {
		//クラスからインターフェイスを探す
		GenericType* impl_baseline = NULL;
		GenericType* impl = FindInterfaceTypeClass(TYPE2CLASS(GENERIC2TYPE(other)), (GENERIC2TYPE(self)), &impl_baseline);
		if (impl_baseline == NULL) {
			impl_baseline = other;
		}
		Vector* gargs = apply_by_hierarchy(impl_baseline, impl);
		for (int i = 0; i<self->TypeArgs->Length; i++) {
			GenericType* a = AtVector(self->TypeArgs, i);
			GenericType* b = AtVector(gargs, i);
			int calc = distance_impl(a, b, fr, cctx);
			if (calc == -1 || calc > 0) {
				dist = -1;
				break;
			}
		}
		DeleteVector(gargs, VectorDeleterOfNull);
		return dist;
	} else if (other->CoreType->Tag == TYPE_INTERFACE_T) {
		GenericType* impl = FindInterfaceInterface(TYPE2INTERFACE(GENERIC2TYPE(other)), (GENERIC2TYPE(self)));
		if (impl == NULL) {
			impl = other;
		}
		for (int i = 0; i<self->TypeArgs->Length; i++) {
			GenericType* a = AtVector(self->TypeArgs, i);
			GenericType* b = AtVector(impl->TypeArgs, i);
			int calc = distance_impl(a, b, fr, cctx);
			if (calc == -1 || calc > 0) {
				dist = -1;
				break;
			}
		}
		//PrintGenericType(self); bc_Println();
		//PrintGenericType(other); bc_Println();
		//bc_Printfln("---");
		return dist;
	}
	return dist;
}

static Vector* apply_by_hierarchy(GenericType* impl_baseline, GenericType* impl) {
	assert(impl_baseline->CoreType != NULL);
	Vector* gargs = NewVector();
	for (int i = 0; i < impl->TypeArgs->Length; i++) {
		GenericType* e = AtVector(impl->TypeArgs, i);
		if (e->CoreType == NULL) {
			e = AtVector(impl_baseline->TypeArgs, e->VirtualTypeIndex);
		}
		PushVector(gargs, e);
	}
	return gargs;
}

static GenericType* typeargs_at(CallContext* cctx, Frame* fr, int index) {
	if(fr == NULL) {
		Vector* type_args = GetTypeArgsCContext(cctx);
		ILTypeArgument* a = AtVector(type_args, index);
		return a->GType;
	} else {
		GenericType* a = AtVector(fr->TypeArgs, index);
		return a;
	}
	return NULL;
}

static GenericType* receiver_at(CallContext* cctx, Frame* fr, int index) {
	if(fr == NULL) {
		GenericType* tp = GetReceiverCContext(cctx);
		GenericType* instanced = AtVector(tp->TypeArgs, index);
		return instanced;
	} else {
		Object* a = AtVector(fr->VariableTable, 0);
		printf("receiver at: "); PrintGenericType(a->GType); bc_Println();
		return AtVector(a->GType->TypeArgs, index);
	}
	return NULL;
}

static GenericType* get_generic(GenericType* a) {
	/*
	if(a->VirtualTypeIndex == -1) {
		return a;
	}
	if(a->Tag == GENERIC_TYPE_TAG_CLASS_T) {
		GenericType* receiver = ccat_receiver(a->VirtualTypeIndex);
		a = receiver;
	} else if(a->Tag == GENERIC_TYPE_TAG_METHOD_T) {
		GenericType* at = AtVector(cctop_type_args(), a->VirtualTypeIndex);
		a = at;
	}
	return a;
	*/
	return NULL;
}

static void delete_self(VectorItem item) {
	GenericType* e = (GenericType*)item;
	DeleteVector(e->TypeArgs, VectorDeleterOfNull);
	MEM_FREE(e);
}

static void delete_recursive_self(VectorItem item) {
	GenericType* e = (GenericType*)item;
	DeleteVector(e->TypeArgs, delete_recursive_self);
	MEM_FREE(e);
}

static void recursive_mark(GenericType* a) {
	if(a == NULL || a->IsMark) {
		return;
	}
	a->IsMark = true;
	for(int i=0; i<a->TypeArgs->Length; i++) {
		recursive_mark((GenericType*)AtVector(a->TypeArgs, i));
	}
}