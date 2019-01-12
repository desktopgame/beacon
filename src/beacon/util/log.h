#ifndef BEACON_UTIL_LOG_H
#define BEACON_UTIL_LOG_H

/**
 * beaconのロガーを初期化します。
 * ログの呼び出しは g_XXX マクロを使用します。
 * @see https://developer.gnome.org/glib/stable/glib-Message-Logging.html
 */
void bc_InitLog();

/**
 * ロガーを破棄します。
 */
void bc_DestroyLog();
#endif