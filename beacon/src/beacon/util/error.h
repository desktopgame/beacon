#ifndef BEACON_UTIL_ERROR_H
#define BEACON_UTIL_ERROR_H
/**
 * 戻り値でエラーを表現する場合に使用する列挙型.
 */
typedef enum error_tag {
	noerror,
	error_basic,
} error_tag;
#endif