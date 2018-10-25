#include "namespace.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "type_interface.h"
#include "TYPE_IMPL.h"
#include "script_context.h"
#include "../lib/bc_library_interface.h"
#include "../util/text.h"
#include "../util/mem.h"

//static TreeMap* TreeMap_root = NULL;
//proto
static Namespace* Namespacemalloc(StringView namev);

static void UnlinkNamespace_namespace(NumericMapKey key, NumericMapItem item);
static void DeleteNamespace_namespace(NumericMapKey key, NumericMapItem item);

static void UnlinkNamespace_type(NumericMapKey key, NumericMapItem item);
static void DeleteNamespace_type(NumericMapKey key, NumericMapItem item);

static void Namespacedump_root(NumericMap* root, bool callSelf, int depth);
static void Namespacedump_impl(Namespace* root, int depth);
static void Namespaceput_indent(int depth);
static void Namespacedump_class(NumericMap* root, bool isRoot, int depth);

Namespace * CreateNamespaceAtRoot(StringView namev) {
	ScriptContext* ctx = GetCurrentScriptContext();
	if (ctx->Namespacenmap == NULL) {
		ctx->Namespacenmap = NewNumericMap();
	}
	TreeItem item = GetNumericMapValue(ctx->Namespacenmap, namev);
	if (item == NULL) {
		Namespace* newNamespace = Namespacemalloc(namev);
		PutNumericMap(ctx->Namespacenmap, namev, newNamespace);
		return newNamespace;
	} else return (Namespace*)item;
}

Namespace * FindNamespaceFromRoot(StringView namev) {
	ScriptContext* ctx = GetCurrentScriptContext();
	return CFindNamespaceFromRoot(ctx, namev);
}

Namespace* CFindNamespaceFromRoot(ScriptContext* sctx, StringView namev) {
	if (sctx->Namespacenmap == NULL) {
		return NULL;
	}
	return (Namespace*)GetNumericMapValue(sctx->Namespacenmap, namev);
}

Namespace * AddNamespaceNamespace(Namespace * self, StringView namev) {
	assert(self != NULL);
	Namespace* child = FindNamespaceFromNamespace(self, namev);
	if (child == NULL) {
		Namespace* newNamespace = Namespacemalloc(namev);
		newNamespace->Parent = self;
		child = newNamespace;
		PutNumericMap(self->NamespaceMap, namev, child);
		//PushVector(self->Namespacevec, child);
		self->RefCount++;
	}
	return child;
}

struct type* AddTypeNamespace(Namespace* self, type* type) {
	ScriptContext* ctx = GetCurrentScriptContext();
	type->location = self;
	PutNumericMap(self->TypeMap, GetTypeName(type), type);
	type->absolute_index = ctx->type_vec->Length;
	PushVector(ctx->type_vec, type);
	return type;
}

Namespace * FindNamespaceFromNamespace(Namespace * self, StringView namev) {
	assert(self != NULL);
	return GetNumericMapValue(self->NamespaceMap, namev);
}

type * FindTypeFromNamespace(Namespace * self, StringView namev) {
	assert(self != NULL);
	return GetNumericMapValue(self->TypeMap, namev);
}

class_ * FindClassFromNamespace(Namespace * self, StringView namev) {
	return TypeToClass(FindTypeFromNamespace(self, namev));
}

interface_ * FindInterfaceFromNamespace(Namespace * self, StringView namev) {
	return TypeToInterface(FindTypeFromNamespace(self, namev));
}

Namespace * GetBeaconNamespace() {
	return FindNamespaceFromRoot(InternString("beacon"));
}

Namespace * GetLangNamespace() {
	return FindNamespaceFromNamespace(GetBeaconNamespace(), InternString("lang"));
}

Namespace* GetUnsafeNamespace() {
	return FindNamespaceFromNamespace(GetBeaconNamespace(), InternString("unsafe"));
}

Namespace* GetPlaceholderNamespace() {
	return FindNamespaceFromRoot(InternString("$placeholder"));
}

type * GetObjectTypeNamespace() {
	return GetBCObjectType();
}

type * GetIntTypeNamespace() {
	return GetBCIntType();
}

type * GetDoubleTypeNamespace() {
	return GetBCDoubleType();
}

type * GetCharTypeNamespace() {
	return GetBCCharType();
}

type * GetStringTypeNamespace() {
	return GetBCStringType();
}

type * GetBoolTypeNamespace() {
	return GetBCBoolType();
}

type * GetVoidTypeNamespace() {
	return GetBCVoidType();
}

type * GetNullTypeNamespace() {
	return GetBCNullType();
}

type* GetExceptionTypeNamespace() {
	return GetBCExceptionType();
}

void UnlinkNamespace(Namespace * self) {
	EachNumericMap(self->NamespaceMap, UnlinkNamespace_namespace);
	EachNumericMap(self->TypeMap, UnlinkNamespace_type);
}

StringView NamespaceToString(Namespace* self) {
	if(self->Parent == NULL) {
		return self->Name;
	}
	return ConcatIntern(
		Ref2Str(ConcatIntern(
			Ref2Str(NamespaceToString(self->Parent)),
			InternString("::")
		)),
		self->Name
	);
}

void DeleteNamespace(Namespace * self) {
	DeleteNumericMap(self->NamespaceMap, DeleteNamespace_namespace);
	DeleteNumericMap(self->TypeMap, DeleteNamespace_type);
	MEM_FREE(self);
}

//private
static Namespace* Namespacemalloc(StringView namev) {
	Namespace* ret = (Namespace*)MEM_MALLOC(sizeof(Namespace));
	ret->NamespaceMap = NewNumericMap();
	ret->TypeMap = NewNumericMap();
	ret->Parent = NULL;
	ret->Name = namev;
	ret->RefCount = 0;
	return ret;
}

static void UnlinkNamespace_namespace(NumericMapKey key, NumericMapItem item) {
	Namespace* e = (Namespace*)item;
	UnlinkNamespace(e);
}

static void DeleteNamespace_namespace(NumericMapKey key, NumericMapItem item) {
	Namespace* e = (Namespace*)item;
	DeleteNamespace(e);
}

static void UnlinkNamespace_type(NumericMapKey key, NumericMapItem item) {
	type* e = (type*)item;
	UnlinkType(e);
}

static void DeleteNamespace_type(NumericMapKey key, NumericMapItem item) {
	type* e = (type*)item;
	DeleteType(e);
}

static void Namespacedump_root(NumericMap* root, bool callSelf, int depth) {
	if (root == NULL) {
		return;
	}
	if (callSelf) {
		Namespacedump_impl((Namespace*)root->Item, depth);
	}
	if (root->Left != NULL) {
		Namespacedump_root(root->Left, true, depth);
	}
	if (root->Right != NULL) {
		Namespacedump_root(root->Right, true, depth);
	}
}

static void Namespacedump_impl(Namespace* root, int depth) {
	Namespaceput_indent(depth);
	printf("%s", Ref2Str(root->Name));
	Println();
	Namespacedump_class(root->TypeMap, true, depth + 1);
	Namespacedump_root(root->NamespaceMap, false, depth + 1);
}

static void Namespaceput_indent(int depth) {
	for (int i = 0; i < depth; i++) {
		printf("    ");
	}
}

static void Namespacedump_class(NumericMap* root, bool isRoot, int depth) {
	if (!isRoot && (root == NULL || root->Item == NULL)) {
		return;
	}
	if (!isRoot) {
		type* e = ((type*)root->Item);
		//type_dump(e, depth);
		assert(false);
	}
	Namespacedump_class(root->Left, false, depth);
	Namespacedump_class(root->Right, false, depth);
}