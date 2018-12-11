#ifndef BEACON_LIB_BEACON_LANG_MONITOR_H
#define BEACON_LIB_BEACON_LANG_MONITOR_H
#include "../../bc_library_impl.h"

/**
 * beacon::lang::Monitorクラスを初期化します.
 */
void bc_InitMonitor();

/**
 * beacon::lang::Monitorクラスを返します.
 * @return
 */
struct bc_Type* bc_GetMonitorType();
#endif