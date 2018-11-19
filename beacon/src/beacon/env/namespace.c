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
static bc_Namespace* malloc_namespace(StringView namev);

static void unlink_namespace(NumericMapKey key, NumericMapItem item);
static void delete_namespace(NumericMapKey key, NumericMapItem item);

static void unlink_type(NumericMapKey key, NumericMapItem item);
static void delete_type(NumericMapKey key, NumericMapItem item);

static void dump_root(NumericMap* root, bool callSelf, int depth);
static void dump_impl(bc_Namespace* root, int depth);
static void put_indent(int depth);
static void dump_class(NumericMap* root, bool isRoot, int depth);

bc_Namespace * bc_CreateNamespaceAtRoot(StringView namev) {
	bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
	if (ctx->NamespaceMap == NULL) {
		ctx->NamespaceMap = NewNumericMap();
	}
	TreeItem item = GetNumericMapValue(ctx->NamespaceMap, namev);
	if (item == NULL) {
		bc_Namespace* newNamespace = malloc_namespace(namev);
		PutNumericMap(ctx->NamespaceMap, namev, newNamespace);
		return newNamespace;
	} else return (bc_Namespace*)item;
}

bc_Namespace * bc_FindNamespaceFromRoot(StringView namev) {
	bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
	return bc_CFindNamespaceFromRoot(ctx, namev);
}

bc_Namespace* bc_CFindNamespaceFromRoot(bc_ScriptContext* sctx, StringView namev) {
	if (sctx->NamespaceMap == NULL) {
		return NULL;
	}
	return (bc_Namespace*)GetNumericMapValue(sctx->NamespaceMap, namev);
}

bc_Namespace * bc_AddNamespaceNamespace(bc_Namespace * self, StringView namev) {
	assert(self != NULL);
	bc_Namespace* child = bc_FindNamespaceFromNamespace(self, namev);
	if (child == NULL) {
		bc_Namespace* newNamespace = malloc_namespace(namev);
		newNamespace->Parent = self;
		child = newNamespace;
		PutNumericMap(self->NamespaceMap, namev, child);
		//PushVector(self->Namespacevec, child);
		self->RefCount++;
	}
	return child;
}

struct bc_Type* bc_AddTypeNamespace(bc_Namespace* self, bc_Type* type) {
	bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
	type->Location = self;
	PutNumericMap(self->TypeMap, bc_GetTypeName(type), type);
	type->AbsoluteIndex = ctx->TypeList->Length;
	PushVector(ctx->TypeList, type);
	return type;
}

bc_Namespace * bc_FindNamespaceFromNamespace(bc_Namespace * self, StringView namev) {
	assert(self != NULL);
	return GetNumericMapValue(self->NamespaceMap, namev);
}

bc_Type* bc_FindTypeFromNamespace(bc_Namespace * self, StringView namev) {
	assert(self != NULL);
	return GetNumericMapValue(self->TypeMap, namev);
}

bc_Class* bc_FindClassFromNamespace(bc_Namespace * self, StringView namev) {
	return bc_TypeToClass(bc_FindTypeFromNamespace(self, namev));
}

bc_Interface* bc_FindInterfaceFromNamespace(bc_Namespace * self, StringView namev) {
	return bc_TypeToInterface(bc_FindTypeFromNamespace(self, namev));
}

bc_Namespace * bc_GetBeaconNamespace() {
	return bc_FindNamespaceFromRoot(InternString("beacon"));
}

bc_Namespace * bc_GetLangNamespace() {
	return bc_FindNamespaceFromNamespace(bc_GetBeaconNamespace(), InternString("lang"));
}

bc_Namespace* bc_GetUnsafeNamespace() {
	return bc_FindNamespaceFromNamespace(bc_GetBeaconNamespace(), InternString("unsafe"));
}

bc_Namespace* bc_GetPlaceholderNamespace() {
	return bc_FindNamespaceFromRoot(InternString("$placeholder"));
}

bc_Type* bc_GetObjectTypeNamespace() {
	return GetObjectType();
}

bc_Type* bc_GetIntTypeNamespace() {
	return GetIntType();
}

bc_Type* bc_GetDoubleTypeNamespace() {
	return GetDoubleType();
}

bc_Type* bc_GetCharTypeNamespace() {
	return GetCharType();
}

bc_Type* bc_GetStringTypeNamespace() {
	return GetStringType();
}

bc_Type* bc_GetBoolTypeNamespace() {
	return GetBoolType();
}

bc_Type* bc_GetVoidTypeNamespace() {
	return GetVoidType();
}

bc_Type* bc_GetNullTypeNamespace() {
	return GetNullType();
}

bc_Type* bc_GetExceptionTypeNamespace() {
	return GetExceptionType();
}

void bc_UnlinkNamespace(bc_Namespace * self) {
	EachNumericMap(self->NamespaceMap, unlink_namespace);
	EachNumericMap(self->TypeMap, unlink_type);
}

StringView bc_NamespaceToString(bc_Namespace* self) {
	if(self->Parent == NULL) {
		return self->Name;
	}
	return ConcatIntern(
		Ref2Str(ConcatIntern(
			Ref2Str(bc_NamespaceToString(self->Parent)),
			InternString("::")
		)),
		self->Name
	);
}

void bc_DeleteNamespace(bc_Namespace * self) {
	DeleteNumericMap(self->NamespaceMap, delete_namespace);
	DeleteNumericMap(self->TypeMap, delete_type);
	MEM_FREE(self);
}

//private
static bc_Namespace* malloc_namespace(StringView namev) {
	bc_Namespace* ret = (bc_Namespace*)MEM_MALLOC(sizeof(bc_Namespace));
	ret->NamespaceMap = NewNumericMap();
	ret->TypeMap = NewNumericMap();
	ret->Parent = NULL;
	ret->Name = namev;
	ret->RefCount = 0;
	return ret;
}

static void unlink_namespace(NumericMapKey key, NumericMapItem item) {
	bc_Namespace* e = (bc_Namespace*)item;
	bc_UnlinkNamespace(e);
}

static void delete_namespace(NumericMapKey key, NumericMapItem item) {
	bc_Namespace* e = (bc_Namespace*)item;
	bc_DeleteNamespace(e);
}

static void unlink_type(NumericMapKey key, NumericMapItem item) {
	bc_Type* e = (bc_Type*)item;
	bc_UnlinkType(e);
}

static void delete_type(NumericMapKey key, NumericMapItem item) {
	bc_Type* e = (bc_Type*)item;
	bc_DeleteType(e);
}

static void dump_root(NumericMap* root, bool callSelf, int depth) {
	if (root == NULL) {
		return;
	}
	if (callSelf) {
		dump_impl((bc_Namespace*)root->Item, depth);
	}
	if (root->Left != NULL) {
		dump_root(root->Left, true, depth);
	}
	if (root->Right != NULL) {
		dump_root(root->Right, true, depth);
	}
}

static void dump_impl(bc_Namespace* root, int depth) {
	put_indent(depth);
	printf("%s", Ref2Str(root->Name));
	bc_Println();
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
		bc_Type* e = ((bc_Type*)root->Item);
		//type_dump(e, depth);
		assert(false);
	}
	dump_class(root->Left, false, depth);
	dump_class(root->Right, false, depth);
}