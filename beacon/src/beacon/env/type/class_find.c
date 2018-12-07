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

bc_Field* bc_GetFieldClass(bc_Class* self, int index) {
        assert(index >= 0);
        int all = bc_CountAllFieldClass(self);
        if (index >= (all - self->Fields->Length) && index < all) {
                return bc_AtVector(self->Fields,
                                   self->Fields->Length - (all - index));
        }
        return bc_GetFieldClass(self->SuperClass->CoreType->Kind.Class, index);
}

bc_Field* bc_GetSFieldClass(bc_Class* self, int index) {
        assert(index >= 0);
        int all = bc_CountAllSFieldClass(self);
        if (index >= (all - self->StaticFields->Length) && index < all) {
                return bc_AtVector(self->StaticFields,
                                   self->StaticFields->Length - (all - index));
        }
        return bc_GetSFieldClass(self->SuperClass->CoreType->Kind.Class, index);
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

bc_Property* bc_GetPropertyClass(bc_Class* self, int index) {
        assert(index >= 0);
        int all = bc_CountAllPropertyClass(self);
        if (index >= (all - self->Properties->Length) && index < all) {
                return bc_AtVector(self->Properties,
                                   self->Properties->Length - (all - index));
        }
        return bc_GetPropertyClass(self->SuperClass->CoreType->Kind.Class,
                                   index);
}

bc_Property* bc_GetSPropertyClass(bc_Class* self, int index) {
        assert(index >= 0);
        int all = bc_CountAllSPropertyClass(self);
        if (index >= (all - self->StaticProperties->Length) && index < all) {
                return bc_AtVector(
                    self->StaticProperties,
                    self->StaticProperties->Length - (all - index));
        }
        return bc_GetPropertyClass(self->SuperClass->CoreType->Kind.Class,
                                   index);
}

bc_Property* bc_FindPropertyClass(bc_Class* self, bc_StringView namev,
                                  int* outIndex) {
        (*outIndex) = -1;
        for (int i = 0; i < self->Properties->Length; i++) {
                bc_VectorItem e = bc_AtVector(self->Properties, i);
                bc_Property* p = (bc_Property*)e;
                if (namev == p->Name) {
                        (*outIndex) = (bc_CountAllPropertyClass(self) -
                                       self->Properties->Length) +
                                      i;
                        return p;
                }
        }
        return NULL;
}

bc_Property* bc_FindTreePropertyClass(bc_Class* self, bc_StringView namev,
                                      int* outIndex) {
        bc_Class* pointee = self;
        do {
                bc_Property* p = bc_FindPropertyClass(pointee, namev, outIndex);
                if (p != NULL) {
                        return p;
                }
                bc_GenericType* supergtype = pointee->SuperClass;
                if (supergtype == NULL) {
                        break;
                }
                pointee = supergtype->CoreType->Kind.Class;
        } while (pointee != NULL);
        return NULL;
}

bc_Property* bc_FindSPropertyClass(bc_Class* self, bc_StringView namev,
                                   int* outIndex) {
        (*outIndex) = -1;
        for (int i = 0; i < self->StaticProperties->Length; i++) {
                bc_VectorItem e = bc_AtVector(self->StaticProperties, i);
                bc_Property* p = (bc_Property*)e;
                if (namev == p->Name) {
                        (*outIndex) = (bc_CountAllSPropertyClass(self) -
                                       self->StaticProperties->Length) +
                                      i;
                        return p;
                }
        }
        return NULL;
}

bc_Property* bc_FindTreeSPropertyClass(bc_Class* self, bc_StringView namev,
                                       int* outIndex) {
        bc_Class* pointee = self;
        do {
                bc_Property* p =
                    bc_FindSPropertyClass(pointee, namev, outIndex);
                if (p != NULL) {
                        return p;
                }
                bc_GenericType* supergtype = pointee->SuperClass;
                if (supergtype == NULL) {
                        break;
                }
                pointee = supergtype->CoreType->Kind.Class;
        } while (pointee != NULL);
        return NULL;
}

bc_Constructor* bc_ILFindConstructorClass(bc_Class* self, bc_Vector* args,
                                          bc_Enviroment* env,
                                          bc_CallContext* cctx, int* outIndex) {
        //	Vector* v = meta_find_constructors(self, args, env, ilctx);
        //	(*outIndex) = -1;
        //	return class_find_constructor_impl(v, args, env, ilctx,
        // outIndex);
        bc_Constructor* ctor = bc_MetaScopedILFindConstructor(
            self, self->Constructors, args, env, cctx, outIndex);
        return ctor;
}

bc_Constructor* bc_ILFindEmptyConstructorClass(bc_Class* self,
                                               bc_Enviroment* env,
                                               bc_CallContext* cctx,
                                               int* outIndex) {
        bc_Vector* emptyArgs = bc_NewVector();
        bc_Constructor* ret =
            bc_ILFindConstructorClass(self, emptyArgs, env, cctx, outIndex);
        bc_DeleteVector(emptyArgs, bc_VectorDeleterOfNull);
        return ret;
}

bc_Method* bc_ILFindMethodClass(bc_Class* self, bc_StringView namev,
                                bc_Vector* args, bc_Enviroment* env,
                                bc_CallContext* cctx, int* outIndex) {
        (*outIndex) = -1;
        bc_CreateVTableClass(self);
#if defined(DEBUG)
        const char* str = bc_Ref2Str(self->Name);
#endif
        // assert(self->vt->elements->Length > 0);
        bc_Method* ret = NULL;
        if ((ret = bc_MetaScopedILFindMethod(self, self->VT->Elements, namev,
                                             args, env, cctx, outIndex)) !=
            NULL) {
                return ret;
        }
        if ((ret = bc_MetaScopedILFindMethod(self, self->Methods, namev, args,
                                             env, cctx, outIndex)) != NULL) {
                return ret;
        }
        if ((ret = bc_MetaScopedILFindMethod(self, self->StaticMethods, namev,
                                             args, env, cctx, outIndex)) !=
            NULL) {
                return ret;
        }
        return NULL;
}

bc_Method* bc_GFindMethodClass(bc_Class* self, bc_StringView namev,
                               bc_Vector* gargs, int* outIndex) {
        (*outIndex) = -1;
        bc_CreateVTableClass(self);
        // assert(self->vt->elements->Length > 0);
        bc_Method* ret = NULL;
        if ((ret = bc_MetaScopedGFindMethod(self, self->VT->Elements, namev,
                                            gargs, outIndex)) != NULL) {
                return ret;
        }
        if ((ret = bc_MetaScopedGFindMethod(self, self->Methods, namev, gargs,
                                            outIndex)) != NULL) {
                return ret;
        }
        if ((ret = bc_MetaScopedGFindMethod(self, self->StaticMethods, namev,
                                            gargs, outIndex)) != NULL) {
                return ret;
        }
        return NULL;
}

bc_Method* bc_GFindEqMethodClass(bc_Class* self, int* outIndex) {
        bc_Vector* gargs = bc_NewVector();
        bc_PushVector(gargs, BC_TYPE_OBJECT->GenericSelf);
        bc_Method* ret = bc_GFindMethodClass(self, bc_InternString("equals"),
                                             gargs, outIndex);
        bc_DeleteVector(gargs, bc_VectorDeleterOfNull);
        return ret;
}

bc_Method* bc_ILFindSMethodClass(bc_Class* self, bc_StringView namev,
                                 bc_Vector* args, bc_Enviroment* env,
                                 bc_CallContext* cctx, int* outIndex) {
#if defined(DEBUG)
        const char* str = bc_Ref2Str(namev);
#endif
        (*outIndex) = -1;
        bc_CreateVTableClass(self);
        int temp = 0;
        bc_Method* ret = bc_MetaILFindMethod(self->StaticMethods, namev, args,
                                             env, cctx, &temp);
        //	temp += (CountAllSMethodClass(self) -
        // self->StaticMethods->Length);
        (*outIndex) = temp;
        return ret;
}

bc_Method* bc_GFindSMethodClass(bc_Class* self, bc_StringView namev,
                                bc_Vector* gargs, int* outIndex) {
        (*outIndex) = -1;
        bc_CreateVTableClass(self);
        int temp = 0;
        bc_Method* ret =
            bc_MetaGFindMethod(self->StaticMethods, namev, gargs, &temp);
        //	temp += (CountAllSMethodClass(self) -
        // self->StaticMethods->Length);
        (*outIndex) = temp;
        return ret;
}

bc_Method* bc_GetMethodClass(bc_Object* o, int index) {
        assert(index >= 0);
#if defined(DEBUG)
        const char* name = bc_GetObjectName(o);
#endif
        if (bc_IsNullValue(o)) {
                o->VPtr = BC_TYPE2CLASS(BC_TYPE_OBJECT)->VT;
        }
        bc_VTable* vx = (o->VPtr);
        return (bc_Method*)bc_AtVector(vx->Elements, index);
}

bc_Method* bc_GetSMethodClass(bc_Class* self, int index) {
        assert(index >= 0);
        /*
        //Class* self = o->classz;
        int all = CountAllSMethodClass(self);
        if (index >= (all - self->StaticMethods->Length) &&
                index < all) {
                return AtVector(self->StaticMethods, self->StaticMethods->Length
        - (all - index));
        }
        return GetSMethodClass(self->SuperClass->CoreType->Kind.Class, index);
        //*/
        return bc_AtVector(self->StaticMethods, index);
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

bc_OperatorOverload* bc_GFindOperatorOverloadClass(
    bc_Class* self, bc_OperatorType type, bc_Vector* args, bc_Enviroment* env,
    bc_CallContext* cctx, int* outIndex) {
        (*outIndex) = -1;
        bc_OperatorOverload* ret = NULL;
        bc_CreateOperatorVTClass(self);
        for (int i = 0; i < self->OVT->Operators->Length; i++) {
                bc_OperatorOverload* operator_ov =
                    bc_AtVector(self->OVT->Operators, i);
                if (operator_ov->Type != type) {
                        continue;
                }
                bool nomatch = false;
                int score = 1024;
                int sum = 0;
                bc_Vector* params = operator_ov->Parameters;
                for (int j = 0; j < params->Length; j++) {
                        bc_Parameter* param = bc_AtVector(params, j);
                        bc_GenericType* arg = bc_AtVector(args, j);
                        int dist = bc_CdistanceGenericType(param->GType, arg);
                        if (dist == -1) {
                                nomatch = true;
                                break;
                        }
                        sum += dist;
                }
                if (nomatch) {
                        continue;
                }
                if (sum < score) {
                        score = sum;
                        (*outIndex) = i;
                        ret = operator_ov;
                }
        }
        return ret;
}

bc_OperatorOverload* bc_ILFindOperatorOverloadClass(
    bc_Class* self, bc_OperatorType type, bc_Vector* args, bc_Enviroment* env,
    bc_CallContext* cctx, int* outIndex) {
        bc_Vector* gargs = bc_NewVector();
        for (int i = 0; i < args->Length; i++) {
                bc_ILFactor* ilfact = (bc_ILFactor*)bc_AtVector(args, i);
                bc_GenericType* g = bc_EvalILFactor(ilfact, env, cctx);
                bc_PushVector(gargs, g);
        }
        bc_OperatorOverload* ret = bc_GFindOperatorOverloadClass(
            self, type, gargs, env, cctx, outIndex);
        bc_DeleteVector(gargs, bc_VectorDeleterOfNull);
        return ret;
}

bc_OperatorOverload* bc_ArgFindOperatorOverloadClass(
    bc_Class* self, bc_OperatorType type, bc_Vector* args, bc_Enviroment* env,
    bc_CallContext* cctx, int* outIndex) {
        bc_Vector* gargs = bc_NewVector();
        for (int i = 0; i < args->Length; i++) {
                // ILFactor* ilfact = (ILFactor*)AtVector(args,i);
                bc_ILArgument* ilarg = (bc_ILArgument*)bc_AtVector(args, i);
                bc_ILFactor* ilfact = ilarg->Factor;
                bc_GenericType* g = bc_EvalILFactor(ilfact, env, cctx);
                bc_PushVector(gargs, g);
        }
        bc_OperatorOverload* ret = bc_GFindOperatorOverloadClass(
            self, type, gargs, env, cctx, outIndex);
        bc_DeleteVector(gargs, bc_VectorDeleterOfNull);
        return ret;
}

bc_OperatorOverload* bc_GetOperatorOverloadClass(bc_Class* self, int index) {
        return bc_AtVector(self->OVT->Operators, index);
}

bc_Vector* bc_FindTreeMethodClass(bc_Class* self, bc_Method* m) {
        assert(self != NULL);
        assert(m != NULL);
        bc_Class* ptr = self;
        bc_Vector* ret = bc_NewVector();
#if defined(DEBUG)
        const char* ptrname = bc_Ref2Str(ptr->Name);
#endif
        do {
                bc_Method* tmp = NULL;
                if (bc_IsContainsMethod(ptr->Methods, m, &tmp)) {
                        bc_PushVector(ret, tmp);
                }
                //親クラスへ
                if (ptr->SuperClass != NULL) {
                        ptr = ptr->SuperClass->CoreType->Kind.Class;
                } else {
                        ptr = NULL;
                }
        } while (ptr != NULL);
        return ret;
}

bool bc_IsContainsMethod(bc_Vector* method_list, bc_Method* m,
                         bc_Method** outM) {
        assert(!bc_IsStaticModifier(BC_MEMBER_MODIFIER(m)));
        (*outM) = NULL;
        bool ret = false;
        bc_CallContext* cctx =
            bc_NewNameContext(BC_MEMBER_TYPE(m)->Location, BC_MEMBER_TYPE(m));
        cctx->Scope = BC_MEMBER_TYPE(m)->Location;
        cctx->Ty = BC_MEMBER_TYPE(m);
        for (int i = 0; i < method_list->Length; i++) {
                bc_Method* mE = bc_AtVector(method_list, i);
                if (bc_IsOverridedMethod(m, mE, cctx)) {
                        (*outM) = mE;
                        ret = true;
                        break;
                }
        }
        bc_DeleteCallContext(cctx);
        return ret;
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