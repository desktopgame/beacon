#include "type_interface.h"
#include <assert.h>
#include <string.h>
#include "../util/mem.h"
#include "../util/text.h"
#include "TYPE_IMPL.h"
#include "field.h"
#include "generic_type.h"
#include "method.h"
#include "object.h"
#include "property.h"
#include "type_parameter.h"

bc_Type* bc_NewType() {
        bc_Type* ret = (bc_Type*)MEM_MALLOC(sizeof(bc_Type));
        ret->AllocSize = sizeof(bc_Object);
        ret->Tag = TYPE_CLASS_T;
        ret->Location = NULL;
        ret->AbsoluteIndex = -1;
        ret->GenericSelf = NULL;
        ret->State = TYPE_NONE;
        return ret;
}

bc_GenericType* bc_InitGenericSelf(bc_Type* self, int counts) {
        if (self == NULL) {
                return NULL;
        }
        if (self->GenericSelf == NULL) {
                self->GenericSelf = bc_NewGenericType(self);
                for (int i = 0; i < counts; i++) {
                        bc_GenericType* arg = bc_NewGenericType(NULL);
                        arg->Tag = GENERIC_TYPE_TAG_CLASS_T;
                        arg->VirtualTypeIndex = i;
                        arg->Kind.Type = self;
                        bc_AddArgsGenericType(self->GenericSelf, arg);
                }
        }
        return self->GenericSelf;
}

bc_StringView bc_GetTypeName(bc_Type* self) {
        if (self == NULL) {
                return bc_InternString("NULL");
        }
        if (self->Tag == TYPE_CLASS_T) {
                return self->Kind.Class->Name;
        } else if (self->Tag == TYPE_INTERFACE_T) {
                return self->Kind.Interface->Name;
        }
        return 0;
}

bc_StringView bc_GetTypeFullName(bc_Type* self) {
        if (self == NULL) {
                return bc_InternString("NULL");
        }
        bc_StringView Namespacestr = bc_NamespaceToString(self->Location);
        bc_StringView self_str = bc_GetTypeName(self);
        return bc_ConcatIntern(bc_Ref2Str(Namespacestr),
                               bc_ConcatIntern(".", self_str));
}

void bc_AddFieldType(bc_Type* self, bc_Field* f) {
        assert(self->Tag == TYPE_CLASS_T);
        bc_AddFieldClass(self->Kind.Class, f);
}

void bc_AddPropertyType(bc_Type* self, bc_Property* p) {
        if (self->Tag == TYPE_CLASS_T) {
                bc_AddPropertyClass(self->Kind.Class, p);
        } else if (self->Tag == TYPE_INTERFACE_T) {
                bc_AddPropertyInterface(self->Kind.Interface, p);
        }
}

void bc_AddMethodType(bc_Type* self, bc_Method* m) {
        if (self->Tag == TYPE_CLASS_T) {
                bc_AddMethodClass(self->Kind.Class, m);
        } else if (self->Tag == TYPE_INTERFACE_T) {
                bc_AddMethodInterface(self->Kind.Interface, m);
        }
}

bc_VTable* bc_GetVTableType(bc_Type* self) {
        if (self->Tag == TYPE_CLASS_T) {
                bc_CreateVTableClass(self->Kind.Class);
                return self->Kind.Class->VT;
        } else if (self->Tag == TYPE_INTERFACE_T) {
                return self->Kind.Interface->VT;
        }
        return NULL;
}

int bc_DistanceType(bc_Type* super, bc_Type* sub) {
        if (super == sub) {
                return 0;
        }
        // nullはあらゆる型のサブクラス
        if (sub == BC_TYPE_NULL) {
                return 1;
        }
        if (super->Tag == TYPE_INTERFACE_T && sub->Tag == TYPE_CLASS_T) {
                bool found = false;
                bc_Vector* gimpl_list =
                    bc_GetGenericInterfaceListClass(BC_TYPE2CLASS(sub));
                for (int i = 0; i < gimpl_list->Length; i++) {
                        bc_GenericType* e =
                            (bc_GenericType*)bc_AtVector(gimpl_list, i);
                        if (e->CoreType == super) {
                                found = true;
                                break;
                        }
                }
                bc_DeleteVector(gimpl_list, bc_VectorDeleterOfNull);
                return found ? 0 : -1;
        }
        if (super->Tag == TYPE_CLASS_T && sub->Tag == TYPE_CLASS_T) {
                int dist = bc_DistanceClass(super->Kind.Class, sub->Kind.Class);
                return dist;
        }
        if (super->Tag == TYPE_CLASS_T && sub->Tag == TYPE_INTERFACE_T) {
                if (super == BC_TYPE_OBJECT) {
                        return 0;
                }
                // TODO:ここで実装しているかどうかを調べる
                return -1;
        }
        return -1;
}

void bc_UnlinkType(bc_Type* self) {
        if (self->Tag == TYPE_CLASS_T) {
                bc_UnlinkClass(self->Kind.Class);
        } else if (self->Tag == TYPE_INTERFACE_T) {
                bc_UnlinkInterface(self->Kind.Interface);
        }
}

int bc_GetGenericIndexType(bc_Type* self, bc_StringView namev) {
        assert(self->Tag != TYPE_ENUM_T);
        bc_Vector* v = NULL;
        if (self->Tag == TYPE_CLASS_T) v = self->Kind.Class->TypeParameters;
        if (self->Tag == TYPE_INTERFACE_T)
                v = self->Kind.Interface->TypeParameters;
        //全ての型変数と比べる
        int ret = -1;
        for (int i = 0; i < v->Length; i++) {
                bc_TypeParameter* e = (bc_TypeParameter*)bc_AtVector(v, i);
                if (e->Name == namev) {
                        ret = i;
                        break;
                }
        }
        if (ret == -1) {
                int a = 0;
        }
        return ret;
}

bc_GenericType* bc_FindImplementType(bc_Type* self, bc_Type* a) {
        // selfがクラスなら
        if (self->Tag == TYPE_CLASS_T) {
                bc_Class* ptr = self->Kind.Class;
                while (ptr != NULL) {
                        if (a->Tag == TYPE_CLASS_T && ptr == a->Kind.Class) {
                                return bc_RefGenericType(ptr->Parent);
                        }
                        if (a->Tag == TYPE_INTERFACE_T) {
                                for (int i = 0; i < ptr->Implements->Length;
                                     i++) {
                                        bc_GenericType* inter =
                                            (bc_GenericType*)bc_AtVector(
                                                ptr->Implements, i);
                                        if (inter->CoreType == a) {
                                                return inter;
                                        }
                                }
                        }
                        ptr = ptr->SuperClass->CoreType->Kind.Class;
                }
        } else if (self->Tag == TYPE_INTERFACE_T) {
                bc_Interface* inter = self->Kind.Interface;
                for (int i = 0; i < inter->Implements->Length; i++) {
                        bc_GenericType* e =
                            (bc_GenericType*)bc_AtVector(inter->Implements, i);
                        if (e->CoreType == a) {
                                return e;
                        }
                }
        }
        return NULL;
}

bc_Vector* bc_GetParameterListType(bc_Type* self) {
        assert(self != NULL);
        if (self->Tag == TYPE_CLASS_T) {
                return self->Kind.Class->TypeParameters;
        } else if (self->Tag == TYPE_INTERFACE_T) {
                return self->Kind.Interface->TypeParameters;
        }
}

bc_Vector* bc_GetImplementList(bc_Type* self) {
        assert(self != NULL);
        if (self->Tag == TYPE_CLASS_T) {
                return self->Kind.Class->Implements;
        } else if (self->Tag == TYPE_INTERFACE_T) {
                return self->Kind.Interface->Implements;
        }
}

bc_GenericType* bc_TypeParameterAtType(bc_Type* self, int index) {
        assert(self->Tag != TYPE_ENUM_T);
        if (self->Tag == TYPE_CLASS_T) {
                return (bc_GenericType*)bc_AtVector(
                    self->Kind.Class->TypeParameters, index);
        } else if (self->Tag == TYPE_INTERFACE_T) {
                return (bc_GenericType*)bc_AtVector(
                    self->Kind.Interface->TypeParameters, index);
        }
        return NULL;
}

void bc_DeleteType(bc_Type* self) {
        if (self->Tag == TYPE_CLASS_T) {
                bc_DeleteClass(self->Kind.Class);
        } else if (self->Tag == TYPE_INTERFACE_T) {
                bc_DeleteInterface(self->Kind.Interface);
        }
        bc_LostownershipGenericType(self->GenericSelf);
        MEM_FREE(self);
}

bc_Class* bc_CastClassType(bc_Type* self) {
        assert(self->Tag == TYPE_CLASS_T);
        return self->Kind.Class;
}

bc_Interface* bc_CastInterfaceType(bc_Type* self) {
        assert(self->Tag == TYPE_INTERFACE_T);
        return self->Kind.Interface;
}

bc_GenericType* bc_BaselineType(bc_Type* abstract, bc_Type* concrete) {
        if (abstract == concrete) {
                return abstract->GenericSelf;
        }
#if defined(DEBUG)
        const char* abstractname = bc_Ref2Str(bc_GetTypeName(abstract));
        const char* concretename = bc_Ref2Str(bc_GetTypeName(concrete));
#endif
        bc_Type* ptr = concrete;
        do {
                bc_Class* cls = BC_TYPE2CLASS(ptr);
                if (cls->SuperClass != NULL &&
                    cls->SuperClass->CoreType == abstract) {
                        return cls->SuperClass;
                }
                if (abstract->Tag == TYPE_INTERFACE_T) {
                        for (int i = 0; i < cls->Implements->Length; i++) {
                                bc_GenericType* gE =
                                    (bc_GenericType*)bc_AtVector(
                                        cls->Implements, i);
                                bc_GenericType* impl =
                                    bc_IsContainsTypeInterface(
                                        gE, abstract->Kind.Interface);
                                if (impl) {
                                        return impl;
                                }
                        }
                }
                //次へ
                if (cls->SuperClass == NULL) {
                        ptr = NULL;
                } else {
                        ptr = cls->SuperClass->CoreType;
                }
        } while (ptr != NULL);
        return NULL;
}

bc_Interface* bc_IsValidInterface(bc_Type* self) {
#if defined(_MSC_VER)
        //コンパイラが初期化されていないローカル変数として認識してしまうのでその対策
        bc_Vector* impl_list = NULL;
        impl_list = bc_GetImplementList(self);
#else
        bc_Vector* impl_list = bc_GetImplementList(self);
#endif
        for (int i = 0; i < impl_list->Length; i++) {
                bc_GenericType* gE = bc_AtVector(impl_list, i);
                bc_Interface* iE = BC_TYPE2INTERFACE(bc_GENERIC2TYPE(gE));
                for (int j = 0; j < impl_list->Length; j++) {
                        if (i == j) {
                                continue;
                        }
                        bc_GenericType* gE2 = bc_AtVector(impl_list, j);
                        bc_Interface* iE2 =
                            BC_TYPE2INTERFACE(bc_GENERIC2TYPE(gE2));
                        if (iE == iE2) {
                                return iE2;
                        }
                }
        }
        return NULL;
}

bool bc_IsAbstractType(bc_Type* self) {
        if (self->Tag == TYPE_CLASS_T) {
                return BC_TYPE2CLASS(self)->IsAbstract;
        }
        return self->Tag == TYPE_INTERFACE_T;
}

bc_Class* bc_TypeToClass(bc_Type* self) {
        if (self == NULL || self->Tag != TYPE_CLASS_T) {
                return NULL;
        }
        return self->Kind.Class;
}

bc_Interface* bc_TypeToInterface(bc_Type* self) {
        if (self == NULL || self->Tag != TYPE_INTERFACE_T) {
                return NULL;
        }
        return self->Kind.Interface;
}