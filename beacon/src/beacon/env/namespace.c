#include "namespace.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/bc_library_interface.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "TYPE_IMPL.h"
#include "script_context.h"
#include "type_interface.h"

// static TreeMap* TreeMap_root = NULL;
// proto
static bc_Namespace* malloc_namespace(bc_StringView namev);

static void unlink_namespace(bc_NumericMapKey key, bc_NumericMapItem item);
static void delete_namespace(bc_NumericMapKey key, bc_NumericMapItem item);

static void unlink_type(bc_NumericMapKey key, bc_NumericMapItem item);
static void delete_type(bc_NumericMapKey key, bc_NumericMapItem item);

static void dump_root(bc_NumericMap* root, bool callSelf, int depth);
static void dump_impl(bc_Namespace* root, int depth);
static void put_indent(int depth);
static void dump_class(bc_NumericMap* root, bool isRoot, int depth);

bc_Namespace* bc_CreateNamespaceAtRoot(bc_ScriptContext* sctx,
                                       bc_StringView name) {
        if (sctx == NULL) {
                sctx = bc_GetScriptContext();
        }
        if (sctx->NamespaceMap == NULL) {
                sctx->NamespaceMap = bc_NewNumericMap();
        }
        bc_TreeItem item = bc_GetNumericMapValue(sctx->NamespaceMap, name);
        if (item == NULL) {
                bc_Namespace* newNamespace = malloc_namespace(name);
                bc_PutNumericMap(sctx->NamespaceMap, name, newNamespace);
                return newNamespace;
        } else
                return (bc_Namespace*)item;
}

bc_Namespace* bc_FindNamespaceFromRoot(bc_ScriptContext* sctx,
                                       bc_StringView name) {
        if (sctx == NULL) {
                sctx = bc_GetScriptContext();
        }
        return bc_CFindNamespaceFromRoot(sctx, name);
}

bc_Namespace* bc_CFindNamespaceFromRoot(bc_ScriptContext* sctx,
                                        bc_StringView namev) {
        if (sctx->NamespaceMap == NULL) {
                return NULL;
        }
        return (bc_Namespace*)bc_GetNumericMapValue(sctx->NamespaceMap, namev);
}

bc_Namespace* bc_AddNamespaceNamespace(bc_Namespace* self,
                                       bc_StringView namev) {
        assert(self != NULL);
        bc_Namespace* child = bc_FindNamespaceFromNamespace(self, namev);
        if (child == NULL) {
                bc_Namespace* newNamespace = malloc_namespace(namev);
                newNamespace->Parent = self;
                child = newNamespace;
                bc_PutNumericMap(self->NamespaceMap, namev, child);
                // PushVector(self->Namespacevec, child);
        }
        return child;
}

struct bc_Type* bc_AddTypeNamespace(bc_Namespace* self, bc_Type* type) {
        bc_ScriptContext* ctx = bc_GetScriptContext();
        type->Location = self;
        bc_PutNumericMap(self->TypeMap, bc_GetTypeName(type), type);
        type->AbsoluteIndex = ctx->TypeList->Length;
        bc_PushVector(ctx->TypeList, type);
        return type;
}

bc_Namespace* bc_FindNamespaceFromNamespace(bc_Namespace* self,
                                            bc_StringView namev) {
        assert(self != NULL);
        return bc_GetNumericMapValue(self->NamespaceMap, namev);
}

bc_Type* bc_FindTypeFromNamespace(bc_Namespace* self, bc_StringView namev) {
        assert(self != NULL);
        return bc_GetNumericMapValue(self->TypeMap, namev);
}

bc_Class* bc_FindClassFromNamespace(bc_Namespace* self, bc_StringView namev) {
        return bc_TypeToClass(bc_FindTypeFromNamespace(self, namev));
}

bc_Interface* bc_FindInterfaceFromNamespace(bc_Namespace* self,
                                            bc_StringView namev) {
        return bc_TypeToInterface(bc_FindTypeFromNamespace(self, namev));
}

bc_Namespace* bc_GetBeaconNamespace(bc_ScriptContext* sctx) {
        return bc_FindNamespaceFromRoot(sctx, bc_InternString("beacon"));
}

bc_Namespace* bc_GetLangNamespace(bc_ScriptContext* sctx) {
        return bc_FindNamespaceFromNamespace(bc_GetBeaconNamespace(sctx),
                                             bc_InternString("lang"));
}

bc_Namespace* bc_GetUnsafeNamespace(bc_ScriptContext* sctx) {
        return bc_FindNamespaceFromNamespace(bc_GetBeaconNamespace(sctx),
                                             bc_InternString("unsafe"));
}

bc_Namespace* bc_GetPlaceholderNamespace(bc_ScriptContext* sctx) {
        return bc_FindNamespaceFromRoot(sctx, bc_InternString("$placeholder"));
}

bc_Type* bc_GetObjectTypeNamespace() { return bc_GetObjectType(); }

bc_Type* bc_GetShortTypeNamespace() { return bc_GetShortType(); }

bc_Type* bc_GetIntTypeNamespace() { return bc_GetIntType(); }

bc_Type* bc_GetLongTypeNamespace() { return bc_GetLongType(); }

bc_Type* bc_GetFloatTypeNamespace() { return bc_GetFloatType(); }

bc_Type* bc_GetDoubleTypeNamespace() { return bc_GetDoubleType(); }

bc_Type* bc_GetCharTypeNamespace() { return bc_GetCharType(); }

bc_Type* bc_GetStringTypeNamespace() { return bc_GetStringType(); }

bc_Type* bc_GetBoolTypeNamespace(bc_ScriptContext* sctx) {
        return bc_GetBoolType(sctx);
}

bc_Type* bc_GetVoidTypeNamespace() { return bc_GetVoidType(); }

bc_Type* bc_GetNullTypeNamespace(bc_ScriptContext* sctx) {
        return bc_GetNullType(sctx);
}

bc_Type* bc_GetExceptionTypeNamespace() { return bc_GetExceptionType(); }

void bc_UnlinkNamespace(bc_Namespace* self) {
        bc_EachNumericMap(self->NamespaceMap, unlink_namespace);
        bc_EachNumericMap(self->TypeMap, unlink_type);
}

bc_StringView bc_NamespaceToString(bc_Namespace* self) {
        if (self->Parent == NULL) {
                return self->Name;
        }
        return bc_ConcatIntern(
            bc_Ref2Str(
                bc_ConcatIntern(bc_Ref2Str(bc_NamespaceToString(self->Parent)),
                                bc_InternString("::"))),
            self->Name);
}

void bc_DeleteNamespace(bc_Namespace* self) {
        bc_DeleteNumericMap(self->NamespaceMap, delete_namespace);
        bc_DeleteNumericMap(self->TypeMap, delete_type);
        MEM_FREE(self);
}

// private
static bc_Namespace* malloc_namespace(bc_StringView namev) {
        bc_Namespace* ret = (bc_Namespace*)MEM_MALLOC(sizeof(bc_Namespace));
        ret->NamespaceMap = bc_NewNumericMap();
        ret->TypeMap = bc_NewNumericMap();
        ret->Parent = NULL;
        ret->Name = namev;
        return ret;
}

static void unlink_namespace(bc_NumericMapKey key, bc_NumericMapItem item) {
        bc_Namespace* e = (bc_Namespace*)item;
        bc_UnlinkNamespace(e);
}

static void delete_namespace(bc_NumericMapKey key, bc_NumericMapItem item) {
        bc_Namespace* e = (bc_Namespace*)item;
        bc_DeleteNamespace(e);
}

static void unlink_type(bc_NumericMapKey key, bc_NumericMapItem item) {
        bc_Type* e = (bc_Type*)item;
        bc_UnlinkType(e);
}

static void delete_type(bc_NumericMapKey key, bc_NumericMapItem item) {
        bc_Type* e = (bc_Type*)item;
        bc_DeleteType(e);
}

static void dump_root(bc_NumericMap* root, bool callSelf, int depth) {
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
        printf("%s", bc_Ref2Str(root->Name));
        bc_Println();
        dump_class(root->TypeMap, true, depth + 1);
        dump_root(root->NamespaceMap, false, depth + 1);
}

static void put_indent(int depth) {
        for (int i = 0; i < depth; i++) {
                printf("    ");
        }
}

static void dump_class(bc_NumericMap* root, bool isRoot, int depth) {
        if (!isRoot && (root == NULL || root->Item == NULL)) {
                return;
        }
        if (!isRoot) {
                bc_Type* e = ((bc_Type*)root->Item);
                // type_dump(e, depth);
                assert(false);
        }
        dump_class(root->Left, false, depth);
        dump_class(root->Right, false, depth);
}