#include "class_find.h"
#include "../../il/il_argument.h"
#include "../../il/il_factor_impl.h"
#include "../../util/vector.h"
#include "../field.h"
#include "../generic_type.h"
#include "../object.h"
#include "../parameter.h"
#include "../property.h"
#include "../property_body.h"
#include "interface_impl.h"
#include "meta_impl.h"

static bool IsContainsFieldClassImpl(bc_Vector* fields, bc_Field* f);
static bool IsContainsPropertyClassImpl(bc_Vector* props, bc_Property* p);

bc_Field* bc_FindFieldClass(bc_Class* self, bc_StringView namev,
                            int* outIndex) {
        (*outIndex) = -1;
        for (int i = 0; i < self->Fields->Length; i++) {
                bc_VectorItem e = bc_AtVector(self->Fields, i);
                bc_Field* f = (bc_Field*)e;
                if (namev == f->Name) {
                        (*outIndex) = (bc_CountAllFieldClass(self) -
                                       self->Fields->Length) +
                                      i;
                        return f;
                }
        }
        return NULL;
}

bc_Field* bc_FindTreeFieldClass(bc_Class* self, bc_StringView namev,
                                int* outIndex) {
        bc_Class* pointee = self;
        do {
                bc_Field* f = bc_FindFieldClass(pointee, namev, outIndex);
                if (f != NULL) {
                        return f;
                }
                bc_GenericType* supergtype = pointee->SuperClass;
                if (supergtype == NULL) {
                        break;
                }
                pointee = supergtype->CoreType->Kind.Class;
        } while (pointee != NULL);
        return NULL;
}

bc_Field* bc_FindSFieldClass(bc_Class* self, bc_StringView namev,
                             int* outIndex) {
        (*outIndex) = -1;
        for (int i = 0; i < self->StaticFields->Length; i++) {
                bc_VectorItem e = bc_AtVector(self->StaticFields, i);
                bc_Field* f = (bc_Field*)e;
                if (namev == f->Name) {
                        (*outIndex) = (bc_CountAllSFieldClass(self) -
                                       self->StaticFields->Length) +
                                      i;
                        return f;
                }
        }
        return NULL;
}

bc_Field* bc_FindTreeSFieldClass(bc_Class* self, bc_StringView namev,
                                 int* outIndex) {
        bc_Class* pointee = self;
        do {
                bc_Field* f = bc_FindSFieldClass(pointee, namev, outIndex);
                if (f != NULL) {
                        return f;
                }
                if (pointee->SuperClass == NULL) {
                        break;
                }
                pointee = pointee->SuperClass->CoreType->Kind.Class;
        } while (pointee != NULL);
        return NULL;
}

bool bc_IsContainsFieldClass(bc_Class* self, bc_Field* f) {
        return IsContainsFieldClassImpl(self->Fields, f);
}

bool bc_IsContainsSFieldClass(bc_Class* self, bc_Field* f) {
        return IsContainsFieldClassImpl(self->StaticFields, f);
}

bool bc_IsAccessibleFieldClass(bc_Class* self, bc_Field* f) {
        assert(f != NULL);
        if (BC_MEMBER_ACCESS(f) == ACCESS_PUBLIC_T) {
                return true;
        }
        if (BC_MEMBER_ACCESS(f) == ACCESS_PRIVATE_T) {
                return self == BC_TYPE2CLASS(BC_MEMBER_TYPE(f));
        }
        bc_Type* ty = self->Parent;
        bc_Class* fcl = BC_TYPE2CLASS(BC_MEMBER_TYPE(f));
        while (true) {
                bc_Class* c = BC_TYPE2CLASS(ty);
                if (c == fcl) {
                        return true;
                }
                //次へ
                if (c->SuperClass == NULL) {
                        break;
                }
                ty = c->SuperClass->CoreType;
        }
        return false;
}

bool bc_IsContainsPropertyClass(bc_Class* self, bc_Property* p) {
        return IsContainsPropertyClassImpl(self->Properties, p);
}

bool bc_IsContainsSPropertyClass(bc_Class* self, bc_Property* p) {
        return IsContainsPropertyClassImpl(self->StaticProperties, p);
}

bool bc_IsAccessiblePropertyClass(bc_Class* self, bc_Property* p) {
        assert(p != NULL);
        if (BC_MEMBER_ACCESS(p) == ACCESS_PUBLIC_T) {
                return true;
        }
        if (BC_MEMBER_ACCESS(p) == ACCESS_PRIVATE_T) {
                return self == BC_TYPE2CLASS(BC_MEMBER_TYPE(p));
        }
        bc_Type* ty = self->Parent;
        bc_Class* fcl = BC_TYPE2CLASS(BC_MEMBER_TYPE(p));
        while (true) {
                bc_Class* c = BC_TYPE2CLASS(ty);
                if (c == fcl) {
                        return true;
                }
                //次へ
                if (c->SuperClass == NULL) {
                        break;
                }
                ty = c->SuperClass->CoreType;
        }
        return false;
}

bool bc_IsAccessiblePropertyAccessorClass(bc_Class* self, bc_PropertyBody* pb) {
        assert(pb != NULL);
        if (pb->Access == ACCESS_PUBLIC_T) {
                return true;
        }
        if (pb->Access == ACCESS_PRIVATE_T) {
                return self == BC_TYPE2CLASS(BC_MEMBER_TYPE(pb->Parent));
        }
        bc_Type* ty = self->Parent;
        bc_Class* fcl = BC_TYPE2CLASS(BC_MEMBER_TYPE(pb->Parent));
        while (true) {
                bc_Class* c = BC_TYPE2CLASS(ty);
                if (c == fcl) {
                        return true;
                }
                //次へ
                if (c->SuperClass == NULL) {
                        break;
                }
                ty = c->SuperClass->CoreType;
        }
        return false;
}

int bc_GetFieldByPropertyClass(bc_Class* self, bc_Property* p) {
        int temp = -1;
        assert(p->SourceRef != NULL);
        if (bc_IsStaticModifier(BC_MEMBER_MODIFIER(p))) {
                bc_FindSFieldClass(self, p->SourceRef->Name, &temp);
        } else {
                bc_FindFieldClass(self, p->SourceRef->Name, &temp);
        }
        return temp;
}

bc_Method* bc_GetImplMethodClass(bc_Class* self, bc_Type* interType,
                                 int interMIndex) {
#if defined(DEBUG)
        const char* str = bc_Ref2Str(self->Name);
#endif
        assert(self->VTTable->Length > 0);
        bc_Vector* tbl = bc_GetGenericInterfaceTreeClass(self);
        //指定のインターフェイスが
        //このクラスにおいて何番目かを調べる
        int declIndex = -1;
        for (int i = 0; i < tbl->Length; i++) {
                bc_GenericType* e = bc_AtVector(tbl, i);
                bc_Interface* inter = e->CoreType->Kind.Interface;
                if (inter == interType->Kind.Interface) {
                        declIndex = i;
                        break;
                }
        }
        //仮想関数テーブルの一覧から引く
        assert(declIndex != -1);
        bc_DeleteVector(tbl, bc_VectorDeleterOfNull);
        bc_VTable* vtAt = bc_AtVector(self->VTTable, declIndex);
        return bc_AtVector(vtAt->Elements, interMIndex);
}

bc_OperatorOverload* bc_GetOperatorOverloadClass(bc_Class* self, int index) {
        return bc_AtVector(self->OVT->Operators, index);
}

bc_Vector* bc_GetGenericInterfaceListClass(bc_Class* self) {
        bc_Vector* ret = bc_NewVector();
        for (int i = 0; i < self->Implements->Length; i++) {
                bc_GenericType* ginter = bc_AtVector(self->Implements, i);
                bc_Vector* inner = bc_GetGenericInterfaceTreeInterface(
                    BC_TYPE2INTERFACE(bc_GENERIC2TYPE(ginter)));
                bc_MergeVector(ret, inner);
                bc_PushVector(ret, ginter);
                bc_DeleteVector(inner, bc_VectorDeleterOfNull);
        }
        return ret;
}

bc_Vector* bc_GetGenericInterfaceTreeClass(bc_Class* self) {
        bc_Class* ptr = self;
        bc_Vector* ret = bc_NewVector();
        do {
                bc_Vector* v = bc_GetGenericInterfaceListClass(ptr);
                bc_MergeVector(v, ret);
                bc_DeleteVector(v, bc_VectorDeleterOfNull);
                if (ptr->SuperClass == NULL) {
                        break;
                }
                ptr = BC_TYPE2CLASS(bc_GENERIC2TYPE(ptr->SuperClass));
        } while (ptr != NULL);
        return ret;
}

bc_Vector* bc_GetInterfaceListClass(bc_Class* self) {
        bc_Vector* ret = bc_NewVector();
        bc_Vector* c = bc_GetGenericInterfaceListClass(self);
        for (int i = 0; i < c->Length; i++) {
                bc_GenericType* gt = bc_AtVector(c, i);
                bc_PushVector(ret, BC_TYPE2INTERFACE(bc_GENERIC2TYPE(gt)));
        }
        bc_DeleteVector(c, bc_VectorDeleterOfNull);
        return ret;
}

bc_Vector* bc_GetInterfaceTreeClass(bc_Class* self) {
        bc_Vector* ret = bc_NewVector();
        bc_Vector* c = bc_GetGenericInterfaceTreeClass(self);
        for (int i = 0; i < c->Length; i++) {
                bc_GenericType* gt = bc_AtVector(c, i);
                bc_PushVector(ret, BC_TYPE2INTERFACE(bc_GENERIC2TYPE(gt)));
        }
        bc_DeleteVector(c, bc_VectorDeleterOfNull);
        return ret;
}

bc_GenericType* bc_FindInterfaceTypeClass(bc_Class* self, bc_Type* tinter,
                                          bc_GenericType** out_baseline) {
        assert(tinter->Tag == TYPE_INTERFACE_T);
        (*out_baseline) = NULL;
        //実装インターフェイス一覧から同じのを探す
        bc_GenericType* ret = NULL;
        bc_GenericType* out = NULL;
        bc_Class* ptr = self;
        do {
                if (ptr->SuperClass == NULL) {
                        break;
                }
                bool found = false;
                // Vector* gimpl_list = GetGenericInterfaceListClass(ptr);
                bc_Vector* gimpl_list = ptr->Implements;
                for (int i = 0; i < gimpl_list->Length; i++) {
                        bc_GenericType* gimpl = bc_AtVector(gimpl_list, i);
                        if (gimpl->CoreType == tinter) {
                                found = true;
                                ret = gimpl;
                                break;
                        }
                }
                // DeleteVector(gimpl_list, VectorDeleterOfNull);
                if (found) {
                        (*out_baseline) = out;
                        break;
                }
                out = ptr->SuperClass;
                ptr = BC_TYPE2CLASS(bc_GENERIC2TYPE(ptr->SuperClass));
        } while (ptr != NULL);
        return ret;
}

// private
static bool IsContainsFieldClassImpl(bc_Vector* fields, bc_Field* f) {
        for (int i = 0; i < fields->Length; i++) {
                bc_Field* e = (bc_Field*)bc_AtVector(fields, i);
                if (e == f) {
                        return true;
                }
        }
        return false;
}

static bool IsContainsPropertyClassImpl(bc_Vector* props, bc_Property* p) {
        for (int i = 0; i < props->Length; i++) {
                bc_Property* e = (bc_Property*)bc_AtVector(props, i);
                if (e == p) {
                        return true;
                }
        }
        return false;
}