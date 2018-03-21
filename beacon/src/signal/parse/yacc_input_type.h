#pragma once
#ifndef SIGNAL_PARSE_YACC_INPUT_TYPE_H
#define SIGNAL_PARSE_YACC_INPUT_TYPE_H
/**
 * Yacc/Bisonの入力タイプを表す列挙型.
 */
typedef enum yacc_input_type {
	yinput_file,
	yinput_string
} yacc_input_type;
#endif // !SIGNAL_PARSE_YACC_INPUT_TYPE_H
