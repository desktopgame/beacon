#ifndef BEACON_UTIL_MACRO_H
#define BEACON_UTIL_MACRO_H
//https://kmc.hatenablog.jp/entry/2015/12/09/051358

#define bcMAX(a, b) (a > b ? a : b)
#define bcMIN(a, b) (a < b ? a : b)

#define bcCONCAT_HELPER(x, y) x ## y
#define bcCONCAT(x, y) bcCONCAT_HELPER(x, y)

#endif