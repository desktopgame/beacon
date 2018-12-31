#ifndef BEACON_ENV_VALUE_H
#define BEACON_ENV_VALUE_H
#include "object.h"

// beacon -> C
/**
 * beaconからCの short へ変換します.
 * @param self
 * @return
 */
short bc_ObjectToShort(bc_Object* self);

/**
 * beaconからCの int へ変換します.
 * @param self
 * @return
 */
int bc_ObjectToInt(bc_Object* self);

/**
 * beaconからCの long へ変換します.
 * @param self
 * @return
 */
long bc_ObjectToLong(bc_Object* self);

/**
 * beaconからCの float へ変換します.
 * @param self
 * @return
 */
float bc_ObjectToFloat(bc_Object* self);

/**
 * beaconからCの double へ変換します.
 * @param self
 * @return
 */
double bc_ObjectToDouble(bc_Object* self);

/**
 * beaconからCの bool へ変換します.
 * @param self
 * @return
 */
bool bc_ObjectToBool(bc_Object* self);

/**
 * beaconからCの char へ変換します.
 * @param self
 * @return
 */
char bc_ObjectToChar(bc_Object* self);

// C -> beacon
/**
 * Cからbeaconの Short へ変換します.
 * @param s
 * @return
 */
bc_Object* bc_ShortToObject(short s);

/**
 * Cからbeaconの Int へ変換します.
 * @param i
 * @return
 */
bc_Object* bc_IntToObject(int i);

/**
 * Cからbeaconの Long へ変換します.
 * @param l
 * @return
 */
bc_Object* bc_LongToObject(long l);

/**
 * Cからbeaconの Float へ変換します.
 * @param f
 * @return
 */
bc_Object* bc_FloatToObject(float f);

/**
 * Cからbeaconの Double へ変換します.
 * @param d
 * @return
 */
bc_Object* bc_DoubleToObject(double d);

/**
 * Cからbeaconの bool へ変換します.
 * @param b
 * @return
 */
bc_Object* bc_BoolToObject(bool b);

/**
 * Cからbeaconの char へ変換します.
 * @param c
 * @return
 */
bc_Object* bc_CharToObject(char c);
#endif