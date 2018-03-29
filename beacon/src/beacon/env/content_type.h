#pragma once
#ifndef SIGNAL_ENV_CONTENT_TYPE_H
#define SIGNAL_ENV_CONTENT_TYPE_H
/**
 * クラスローダーによって読み込まれるコンテンツの種類を表す列挙型.
 */
typedef enum content_type {
	content_entry_point,
	content_lib
} content_type;
#endif // !SIGNAL_ENV_CONTENT_TYPE_H