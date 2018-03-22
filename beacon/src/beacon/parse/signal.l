%{
//http://kmaebashi.com/programmer/devlang/diksam.html
#undef YY_INPUT
#define YY_INPUT(buf, result, max_size) (result = my_yyinput(buf, max_size))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "signal.tab.h"
#include "parser.h"
#include "../ast/ast.h"
#include "../ast/ast_new_literal.h"
#include "../ast/constructor_chain_type.h"
#include "../util/text.h"
#include "../util/mem.h"

//for C4996
#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif

static char* yaccSourceBuffer;
static int yaccSourceOffset;
static char* yaccErrorBuf;

static int curr_line;
static int curr_col;
 
int yymain(void) {
	//yyparse();
	return(0);
}

//for clang
#ifndef SIGNAL_YYWRAP_PART
#define SIGNAL_YYWRAP_PART
int yywrap(void) {
	return 1;
}
#endif SIGNAL_YYWRAP_PART

int yyerror(char * err_str) {
	printf("%s", err_str);
	printf("\n");

	return 1;
}

void yyexit() {
}

static int file_input(char *buf, int max_size) {
	int ch;
	int len;

	if (feof(yyin)) {
		return 0;
	}

	for (len = 0; len < max_size; len++) {
		ch = getc(yyin);
		if (ch == EOF)
			break;
		buf[len] = ch;
	}
    return len;
}

void yy_setstr(char* source) {
	yaccSourceBuffer = source;
	yaccSourceOffset = 0;
	yylineno = 0;
	curr_line = 0;
	curr_col = 0;
}

void yy_clearstr() {
	free(yaccSourceBuffer);
	yaccSourceBuffer = NULL;
	yaccSourceOffset = 0;
}

static int string_input(char *buf, int max_size) {
	int len = 0;
	int startOffset = yaccSourceOffset;
	for(; (yaccSourceOffset < yaccSourceOffset + max_size); yaccSourceOffset++) {
		if(yaccSourceBuffer[yaccSourceOffset] == '\0') {
			break;
		}
		buf[yaccSourceOffset - startOffset] = yaccSourceBuffer[yaccSourceOffset];
		len++;
	}
	return len;
}

static int my_yyinput(char *buf, int max_size) {
return string_input(buf, max_size);

}
//error position
static void update_loc() {
  yylloc.first_line   = curr_line;
  yylloc.first_column = curr_col;

  {char * s; for(s = yytext; *s != '\0'; s++){
    if(*s == '\n'){
      curr_line++;
      curr_col = 1;
    }else{
      curr_col++;
    }
  }}

  yylloc.last_line   = curr_line;
  yylloc.last_column = curr_col-1;
}

//#define YY_USER_ACTION update_loc();
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
%}
%option yylineno
%option yy_scan_string
%option yy_scan_buffer
%option yy_scan_bytes
%start ML_COMMENT L_COMMENT STRING_LITERAL_STATE
%%

<INITIAL>"."				{ return (DOT); }
<INITIAL>","				{ return (COMMA); }
<INITIAL>":"				{ return (COLON); }
<INITIAL>"::"				{ return (COLO_COLO); }
<INITIAL>";"				{ return (SEMI); }
<INITIAL>"in"				{ return (IN); }
<INITIAL>"out"				{ return (OUT); }


<INITIAL>"+"				{ return (ADD); }
<INITIAL>"-"				{ return (SUB); }
<INITIAL>"*"				{ return (MUL); }
<INITIAL>"/"				{ return (DIV); }
<INITIAL>"%"				{ return (MOD); }
<INITIAL>"!"				{ return (NOT); }


<INITIAL>"="				{ return (ASSIGN); }
<INITIAL>"+="				{ return (ADD_ASSIGN); }
<INITIAL>"-="				{ return (SUB_ASSIGN); }
<INITIAL>"*="				{ return (MUL_ASSIGN); }
<INITIAL>"/="				{ return (DIV_ASSIGN); }
<INITIAL>"%="				{ return (MOD_ASSIGN); }

<INITIAL>"=="				{ return (EQUAL); }
<INITIAL>"!="				{ return (NOTEQUAL); }


<INITIAL>"++"				{ return (INC); }
<INITIAL>"--"				{ return (DEC); }

<INITIAL>">"				{ return (GT); }
<INITIAL>">="				{ return (GE); }
<INITIAL>"<"				{ return (LT); }
<INITIAL>"<="				{ return (LE); }

<INITIAL>"&"				{ return (BIT_AND); }
<INITIAL>"&&"			{ return (LOGIC_AND); }
<INITIAL>"|"				{ return (BIT_OR); }
<INITIAL>"||"			{ return (LOGIC_OR); }


<INITIAL>"{"				{ return (LCB); }
<INITIAL>"}"				{ return (RCB); }
<INITIAL>"("				{ return (LRB); }
<INITIAL>")"				{ return (RRB); }
<INITIAL>"["				{ return (LSB); }
<INITIAL>"]"				{ return (RSB); }

<INITIAL>"import"			{ return (IMPORT); }
<INITIAL>"var"				{ return (VAR); }

<INITIAL>"if"				{ return (IF); }
<INITIAL>"elif"				{ return (ELIF); }
<INITIAL>"else"				{ return (ELSE); }

<INITIAL>"while"			{ return (WHILE); }
<INITIAL>"break"			{ return (BREAK); }
<INITIAL>"continue"			{ return (CONTINUE); }

<INITIAL>"namespace"		{ return (NAMESPACE); }
<INITIAL>"class"			{ return (CLASS); }
<INITIAL>"enum"				{ return (ENUM); }
<INITIAL>"interface"		{ return (INTERFACE); }
<INITIAL>"this"				{ return (THIS); }
<INITIAL>"super"			{ return (SUPER); }
<INITIAL>"new"				{ return (NEW); }

<INITIAL>"true"			{ return (TRUE_TOK); }
<INITIAL>"false"		{ return (FALSE_TOK); }
<INITIAL>"null"			{ return (NULL_TOK); }
<INITIAL>"as"			{ return (AS); }

<INITIAL>"try"			{ return (TRY); }
<INITIAL>"catch"		{ return (CATCH); }
<INITIAL>"throw"		{ return (THROW); }

<INITIAL>"public"			{ return (PUBLIC); }
<INITIAL>"private"			{ return (PRIVATE); }
<INITIAL>"protected"		{ return (PROTECTED); }
<INITIAL>"static"			{ return (STATIC); }
<INITIAL>"native"			{ return (NATIVE); }
<INITIAL>"return"			{ return (RETURN); }

<INITIAL>"ctor"				{ return (CTOR); }
<INITIAL>"def"				{ return (DEF); }
<INITIAL>"->"				{ return (ARROW); }

<INITIAL>"0" {
	return INT;
}

<INITIAL>"\n" {
}

<INITIAL>[1-9][0-9]* {
	return INT;
}

<INITIAL>[0-9]+\.[0-9]+ {
	return DOUBLE;
}

<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
	return IDENT;
}

<INITIAL>\" {
    BEGIN STRING_LITERAL_STATE;
}
<INITIAL>"/*"     BEGIN ML_COMMENT;
<INITIAL>"//"     BEGIN L_COMMENT;
<ML_COMMENT>\n     {
}
<ML_COMMENT>"*/"     {
    BEGIN INITIAL;
}
<ML_COMMENT>.      ;
<L_COMMENT>\n  {
	BEGIN INITIAL;
}
<L_COMMENT><<EOF>>   {
	BEGIN INITIAL;
}
<L_COMMENT>.   ;
<INITIAL>\'\\r\' {
	return CHAR_LITERAL;
}
<INITIAL>\'\\n\' {
	return CHAR_LITERAL;
}
<INITIAL>\'\\t\' {
	return CHAR_LITERAL;
}
<INITIAL>\'\\b\' {
	return CHAR_LITERAL;
}
<INITIAL>\'.\' {
	return CHAR_LITERAL;
}
<STRING_LITERAL_STATE>\" {
    BEGIN INITIAL;
	return STRING_LITERAL;
}
<STRING_LITERAL_STATE>\\\"	{
}
<STRING_LITERAL_STATE>\\\'	{
}
<STRING_LITERAL_STATE>\\r	{
}
<STRING_LITERAL_STATE>\\n	{
}
<STRING_LITERAL_STATE>\\t	{
}
<STRING_LITERAL_STATE>\\\\	{
}
<STRING_LITERAL_STATE>.	{
}
%%
