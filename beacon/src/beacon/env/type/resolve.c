#include "resolve.h"
#include "../../il/il_argument.h"
#include "../../il/il_type_argument.h"
#include "../object.h"
#include "../parameter.h"
#include "../type_impl.h"
#include "../type_parameter.h"
// private
static bool match_option(bc_AccessLevel access, bc_SearchOption option);
static int calc_argument_distance(bc_Vector* parameters, int args_count,
                                  bc_GenericType* args[], bc_Vector* type_args,
                                  bc_CallContext* cctx);
static bc_Field* resolve_field_base(bc_Class* self, bc_StringView namev,
                                    int* outIndex);
static bc_Property* resolve_property_base(bc_Class* self, bc_StringView namev,
                                          int* outIndex);

void bc_CevaluateArguments(bc_Vector* args, bc_GenericType* result[],
                           bc_Enviroment* env, bc_CallContext* cctx) {
        for (int i = 0; i < args->Length; i++) {
                bc_ILArgument* e = bc_AtVector(args, i);
                bc_GenericType* gtype = bc_EvalILFactor(e->Factor, env, cctx);
                result[i] = gtype;
                if (bc_GetLastPanic()) {
                        break;
                }
        }
}

void bc_RevaluateArguments(bc_Vector* args, bc_GenericType* result[]) {
        for (int i = 0; i < args->Length; i++) {
                result[i] = ((bc_Object*)bc_AtVector(args, i))->GType;
                if (bc_GetLastPanic()) {
                        break;
                }
        }
}

//
// Find
//
bc_OperatorOverload* bc_FindOperatorOverload(
    bc_Vector* operator_overloads, bc_OperatorType type, int args_count,
    bc_GenericType* args[], bc_SearchOption option, bc_CallContext* cctx,
    int* outIndex) {
        (*outIndex) = -1;
        bc_OperatorOverload* ret = NULL;
        int maxDistance = 1024;
        for (int i = 0; i < operator_overloads->Length; i++) {
                bc_OperatorOverload* e = bc_AtVector(operator_overloads, i);
                //種類か引数の数が違う
                if (e->Type != type || e->Parameters->Length != args_count) {
                        continue;
                }
                //検索オプションにマッチしない
                if (!match_option(BC_MEMBER_ACCESS(e), option)) {
                        continue;
                }
                int sumDistance = calc_argument_distance(
                    e->Parameters, args_count, args, NULL, cctx);
                if (sumDistance == -1) {
                        continue;
                }
                if (sumDistance < maxDistance) {
                        maxDistance = sumDistance;
                        ret = e;
                        (*outIndex) = i;
                }
        }
        return ret;
}

bc_Method* bc_FindMethod(bc_Vector* methods, bc_StringView name, int args_count,
                         bc_GenericType* args[], bc_Vector* type_args,
                         bc_SearchOption option, bc_CallContext* cctx,
                         int* outIndex) {
        (*outIndex) = -1;
        bc_Method* ret = NULL;
        int maxDistance = 1024;
        for (int i = 0; i < methods->Length; i++) {
                bc_Method* e = bc_AtVector(methods, i);
                //名前、引数の個数、型引数の数で判別する
                if (name != e->Name || args_count != e->Parameters->Length ||
                    type_args->Length != e->TypeParameters->Length) {
                        continue;
                }
                //検索オプションにマッチしない
                if (!match_option(BC_MEMBER_ACCESS(e), option)) {
                        continue;
                }
                int sumDistance = calc_argument_distance(
                    e->Parameters, args_count, args, type_args, cctx);
                if (sumDistance == -1) {
                        continue;
                }
                if (sumDistance < maxDistance) {
                        maxDistance = sumDistance;
                        ret = e;
                        (*outIndex) = i;
                }
        }
        return ret;
}

bc_Constructor* bc_FindConstructor(bc_Vector* constructors, int args_count,
                                   bc_GenericType* args[], bc_Vector* type_args,
                                   bc_SearchOption option, bc_CallContext* cctx,
                                   int* outIndex) {
        (*outIndex) = -1;
        bc_Constructor* ret = NULL;
        int maxDistance = 1024;
        for (int i = 0; i < constructors->Length; i++) {
                bc_Constructor* e = bc_AtVector(constructors, i);
                //引数の数が違う
                if (e->Parameters->Length != args_count) {
                        continue;
                }
                //検索オプションにマッチしない
                if (!match_option(BC_MEMBER_ACCESS(e), option)) {
                        continue;
                }
                int sumDistance = calc_argument_distance(
                    e->Parameters, args_count, args, type_args, cctx);
                if (sumDistance == -1) {
                        continue;
                }
                if (sumDistance < maxDistance) {
                        maxDistance = sumDistance;
                        ret = e;
                        (*outIndex) = i;
                }
        }
        return ret;
}

bc_Field* bc_FindField(bc_Vector* fields, bc_StringView name,
                       bc_SearchOption option, int* outIndex) {
        (*outIndex) = -1;
        for (int i = 0; i < fields->Length; i++) {
                bc_Field* e = (bc_Field*)bc_AtVector(fields, i);
                if (name == e->Name) {
                        (*outIndex) = i;
                        return e;
                }
        }
        return NULL;
}

bc_Property* bc_FindProperty(bc_Vector* properties, bc_StringView name,
                             bc_SearchOption option, int* outIndex) {
        (*outIndex) = -1;
        for (int i = 0; i < properties->Length; i++) {
                bc_Property* e = (bc_Property*)bc_AtVector(properties, i);
                if (name == e->Name) {
                        (*outIndex) = i;
                        return e;
                }
        }
        return NULL;
}

//
// Resolve
//
bc_Field* bc_ResolveField(bc_Class* classz, bc_StringView name, int* outIndex) {
        bc_Class* pointee = classz;
        do {
                bc_Field* f = resolve_field_base(pointee, name, outIndex);
                if (f != NULL) {
                        return f;
                }
                pointee = bc_GetSuperClass(pointee);
        } while (pointee != NULL);
        return NULL;
}

bc_Property* bc_ResolveProperty(bc_Class* classz, bc_StringView name,
                                int* outIndex) {
        bc_Class* pointee = classz;
        do {
                bc_Property* p = resolve_property_base(pointee, name, outIndex);
                if (p != NULL) {
                        return p;
                }
                pointee = bc_GetSuperClass(pointee);
        } while (pointee != NULL);
        return NULL;
}

//
// Other
//
bc_Vector* bc_GetOverideMethods(bc_Class* classz, bc_Method* method) {
        assert(classz != NULL);
        assert(method != NULL);
        bc_Class* ptr = classz;
        bc_Vector* ret = bc_NewVector();
#if defined(DEBUG)
        const char* ptrname = bc_Ref2Str(ptr->Name);
#endif
        do {
                bc_Method* tmp = NULL;
                if (bc_IsOverrideAny(ptr->Methods, method, &tmp)) {
                        bc_PushVector(ret, tmp);
                }
                //親クラスへ
                ptr = bc_GetSuperClass(ptr);
        } while (ptr != NULL);
        return ret;
}

bool bc_IsOverrideAny(bc_Vector* methods, bc_Method* super,
                      bc_Method** outOverride) {
        assert(!bc_IsStaticModifier(BC_MEMBER_MODIFIER(super)));
        (*outOverride) = NULL;
        bool ret = false;
        bc_CallContext* cctx = bc_NewNameContext(
            BC_MEMBER_TYPE(super)->Location, BC_MEMBER_TYPE(super));
        cctx->Scope = BC_MEMBER_TYPE(super)->Location;
        cctx->Ty = BC_MEMBER_TYPE(super);
        for (int i = 0; i < methods->Length; i++) {
                bc_Method* mE = bc_AtVector(methods, i);
                if (bc_IsOverridedMethod(super, mE, cctx)) {
                        (*outOverride) = mE;
                        ret = true;
                        break;
                }
        }
        bc_DeleteCallContext(cctx);
        return ret;
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

// private
static bool match_option(bc_AccessLevel access, bc_SearchOption option) {
        if (option == MATCH_ALL) {
                return true;
        }
        switch (access) {
                case ACCESS_PUBLIC_T:
                        return option == MATCH_PUBLIC_ONLY ||
                               option == MATCH_PUBLIC_OR_PROTECTED;
                case ACCESS_PRIVATE_T:
                        return false;
                case ACCESS_PROTECTED_T:
                        return option == MATCH_PUBLIC_OR_PROTECTED;
        }
        return false;
}

static int calc_argument_distance(bc_Vector* parameters, int args_count,
                                  bc_GenericType* args[], bc_Vector* type_args,
                                  bc_CallContext* cctx) {
        int sumDistance = 0;
        for (int i = 0; i < parameters->Length; i++) {
                bc_Parameter* parameter = bc_AtVector(parameters, i);
                bc_GenericType* argument = args[i];
                bc_GenericType* paramGtype =
                    bc_CapplyGenericType(parameter->GType, cctx);
                int distance = bc_CdistanceGenericType(paramGtype, argument);
                if (distance == -1) {
                        sumDistance = -1;
                        break;
                }
                sumDistance += distance;
        }
        return sumDistance;
}

static bc_Field* resolve_field_base(bc_Class* self, bc_StringView namev,
                                    int* outIndex) {
        (*outIndex) = -1;
        for (int i = 0; i < self->Fields->Length; i++) {
                bc_Field* e = (bc_Field*)bc_AtVector(self->Fields, i);
                if (namev == e->Name) {
                        (*outIndex) = (bc_CountAllFieldClass(self) -
                                       self->Fields->Length) +
                                      i;
                        return e;
                }
        }
        return NULL;
}

static bc_Property* resolve_property_base(bc_Class* self, bc_StringView namev,
                                          int* outIndex) {
        (*outIndex) = -1;
        for (int i = 0; i < self->Properties->Length; i++) {
                bc_Property* e = (bc_Property*)bc_AtVector(self->Properties, i);
                if (namev == e->Name) {
                        (*outIndex) = (bc_CountAllPropertyClass(self) -
                                       self->Properties->Length) +
                                      i;
                        return e;
                }
        }
        return NULL;
}