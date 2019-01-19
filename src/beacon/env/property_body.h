// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file property_body.h
 * @brief プロパティのset/get部分を定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_ENV_PROPERTY_BODY_H
#define BEACON_ENV_PROPERTY_BODY_H
#include "../ast/access_level.h"
struct bc_Enviroment;
struct bc_Property;

typedef enum bc_PropertyBodyTag {
        PROPERTY_SET_T,
        PROPERTY_GET_T
} bc_PropertyBodyTag;

typedef struct bc_PropertyBody {
        struct bc_Property* Parent;
        bc_AccessLevel Access;
        bc_PropertyBodyTag Tag;
        struct bc_Enviroment* Env;
} bc_PropertyBody;

#define bc_NewPropertyBody(tag) (bc_MallocPropertyBody(tag, __FILE__, __LINE__))
bc_PropertyBody* bc_MallocPropertyBody(bc_PropertyBodyTag tag,
                                       const char* filename, int lineno);

void bc_DeletePropertyBody(bc_PropertyBody* self);
#endif