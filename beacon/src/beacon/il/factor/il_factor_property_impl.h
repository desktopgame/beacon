// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_property_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_PROPERTY_H
#define BEACON_IL_FACTOR_PROPERTY_H
#include "../../env/property.h"
#include "../il_factor_interface.h"

struct bc_Enviroment;
struct bc_GenericType;

typedef struct bc_ILPropertyAccess {
        bc_ILFactor* Source;
        bc_StringView Name;
        int Index;
        bc_Property* Property;
} bc_ILPropertyAccess;

#define bc_NewILPropertyAccess() (bc_MallocILPropertyAccess(__FILE__, __LINE__))
bc_ILPropertyAccess* bc_MallocILPropertyAccess(const char* filename,
                                               int lineno);

void bc_GenerateILPropertyAccess(bc_ILPropertyAccess* self, bc_Enviroment* env,
                                 bc_CallContext* cctx);

void bc_LoadILProperty(bc_ILPropertyAccess* self, bc_Enviroment* env,
                       bc_CallContext* cctx);

struct bc_GenericType* bc_EvalILProperty(bc_ILPropertyAccess* self,
                                         bc_Enviroment* env,
                                         bc_CallContext* cctx);

char* bc_ILPropertyToString(bc_ILPropertyAccess* self, bc_Enviroment* env);

void bc_DeleteILPropertyAccess(bc_ILPropertyAccess* self);
#endif