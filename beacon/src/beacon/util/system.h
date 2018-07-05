#ifndef BEACON_UTIL_SYSTEM_H
#define BEACON_UTIL_SYSTEM_H

/**
 * アプリケーションを終了させます.
 * @param status
 */
void system_exit(int status);

/**
 * アプリケーションを終了させます.
 */
void system_abort();
#endif