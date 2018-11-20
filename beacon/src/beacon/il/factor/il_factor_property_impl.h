//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_property_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_PROPERTY_H
#define BEACON_IL_FACTOR_PROPERTY_H
#include "../il_factor_interface.h"
#include "../../env/property.h"

struct bc_Enviroment;
struct bc_GenericType;

typedef struct ILPropertyAccess {
	ILFactor* Source;
	StringView Name;
	int Index;
	bc_Property* Property;
} ILPropertyAccess;

#define NewILPropertyAccess() (MallocILPropertyAccess(__FILE__, __LINE__))
ILPropertyAccess* MallocILPropertyAccess(const char* filename, int lineno);

void GenerateILPropertyAccess(ILPropertyAccess* self, bc_Enviroment* env, CallContext* cctx);

void LoadILProperty(ILPropertyAccess* self, bc_Enviroment* env, CallContext* cctx);

struct bc_GenericType* EvalILProperty(ILPropertyAccess* self, bc_Enviroment* env, CallContext* cctx);

char* ILPropertyToString(ILPropertyAccess* self, bc_Enviroment* env);

void DeleteILPropertyAccess(ILPropertyAccess* self);
#endif