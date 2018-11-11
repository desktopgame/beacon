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
static Namespace* malloc_namespace(StringView namev);

static void unlink_namespace(NumericMapKey key, NumericMapItem item);
static void delete_namespace(NumericMapKey key, NumericMapItem item);

static void unlink_type(NumericMapKey key, NumericMapItem item);
static void delete_type(NumericMapKey key, NumericMapItem item);

static void dump_root(NumericMap* root, bool callSelf, int depth);
static void dump_impl(Namespace* root, int depth);
static void put_indent(int depth);
static void dump_class(NumericMap* root, bool isRoot, int depth);

Namespace * CreateNamespaceAtRoot(StringView namev) {
	ScriptContext* ctx = GetCurrentScriptContext();
	if (ctx->NamespaceMap == NULL) {
		ctx->NamespaceMap = NewNumericMap();
	}
	TreeItem item = GetNumericMapValue(ctx->NamespaceMap, namev);
	if (item == NULL) {
		Namespace* newNamespace = malloc_namespace(namev);
		PutNumericMap(ctx->NamespaceMap, namev, newNamespace);
		return newNamespace;
	} else return (Namespace*)item;
}

Namespace * FindNamespaceFromRoot(StringView namev) {
	ScriptContext* ctx = GetCurrentScriptContext();
	return CFindNamespaceFromRoot(ctx, namev);
}

Namespace* CFindNamespaceFromRoot(ScriptContext* sctx, StringView namev) {
	if (sctx->NamespaceMap == NULL) {
		return NULL;
	}
	return (Namespace*)GetNumericMapValue(sctx->NamespaceMap, namev);
}

Namespace * AddNamespaceNamespace(Namespace * self, StringView namev) {
	assert(self != NULL);
	Namespace* child = FindNamespaceFromNamespace(self, namev);
	if (child == NULL) {
		Namespace* newNamespace = malloc_namespace(namev);
		newNamespace->Parent = self;
		child = newNamespace;
		PutNumericMap(self->NamespaceMap, namev, child);
		//PushVector(self->Namespacevec, child);
		self->RefCount++;
	}
	return child;
}

struct Type* AddTypeNamespace(Namespace* self, Type* type) {
	ScriptContext* ctx = GetCurrentScriptContext();
	type->Location = self;
	PutNumericMap(self->TypeMap, GetTypeName(type), type);
	type->AbsoluteIndex = ctx->TypeList->Length;
	PushVector(ctx->TypeList, type);
	return type;
}

Namespace * FindNamespaceFromNamespace(Namespace * self, StringView namev) {
	assert(self != NULL);
	return GetNumericMapValue(self->NamespaceMap, namev);
}

Type* FindTypeFromNamespace(Namespace * self, StringView namev) {
	assert(self != NULL);
	return GetNumericMapValue(self->TypeMap, namev);
}

Class* FindClassFromNamespace(Namespace * self, StringView namev) {
	return TypeToClass(FindTypeFromNamespace(self, namev));
}

Interface* FindInterfaceFromNamespace(Namespace * self, StringView namev) {
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

Type* GetObjectTypeNamespace() {
	return GetBCObjectType();
}

Type* GetIntTypeNamespace() {
	return GetBCIntType();
}

Type* GetDoubleTypeNamespace() {
	return GetDoubleType();
}

Type* GetCharTypeNamespace() {
	return GetCharType();
}

Type* GetStringTypeNamespace() {
	return GetBCStringType();
}

Type* GetBoolTypeNamespace() {
	return GetBoolType();
}

Type* GetVoidTypeNamespace() {
	return GetBCVoidType();
}

Type* GetNullTypeNamespace() {
	return GetBCNullType();
}

Type* GetExceptionTypeNamespace() {
	return GetExceptionType();
}

void UnlinkNamespace(Namespace * self) {
	EachNumericMap(self->NamespaceMap, unlink_namespace);
	EachNumericMap(self->TypeMap, unlink_type);
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
	DeleteNumericMap(self->NamespaceMap, delete_namespace);
	DeleteNumericMap(self->TypeMap, delete_type);
	MEM_FREE(self);
}

//private
static Namespace* malloc_namespace(StringView namev) {
	Namespace* ret = (Namespace*)MEM_MALLOC(sizeof(Namespace));
	ret->NamespaceMap = NewNumericMap();
	ret->TypeMap = NewNumericMap();
	ret->Parent = NULL;
	ret->Name = namev;
	ret->RefCount = 0;
	return ret;
}

static void unlink_namespace(NumericMapKey key, NumericMapItem item) {
	Namespace* e = (Namespace*)item;
	UnlinkNamespace(e);
}

static void delete_namespace(NumericMapKey key, NumericMapItem item) {
	Namespace* e = (Namespace*)item;
	DeleteNamespace(e);
}

static void unlink_type(NumericMapKey key, NumericMapItem item) {
	Type* e = (Type*)item;
	UnlinkType(e);
}

static void delete_type(NumericMapKey key, NumericMapItem item) {
	Type* e = (Type*)item;
	DeleteType(e);
}

static void dump_root(NumericMap* root, bool callSelf, int depth) {
	if (root == NULL) {
		return;
	}
	if (callSelf) {
		dump_impl((Namespace*)root->Item, depth);
	}
	if (root->Left != NULL) {
		dump_root(root->Left, true, depth);
	}
	if (root->Right != NULL) {
		dump_root(root->Right, true, depth);
	}
}

static void dump_impl(Namespace* root, int depth) {
	put_indent(depth);
	printf("%s", Ref2Str(root->Name));
	Println();
	dump_class(root->TypeMap, true, depth + 1);
	dump_root(root->NamespaceMap, false, depth + 1);
}

static void put_indent(int depth) {
	for (int i = 0; i < depth; i++) {
		printf("    ");
	}
}

static void dump_class(NumericMap* root, bool isRoot, int depth) {
	if (!isRoot && (root == NULL || root->Item == NULL)) {
		return;
	}
	if (!isRoot) {
		Type* e = ((Type*)root->Item);
		//type_dump(e, depth);
		assert(false);
	}
	dump_class(root->Left, false, depth);
	dump_class(root->Right, false, depth);
}