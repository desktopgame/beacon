%{
//http://kmaebashi.com/programmer/devlang/diksam.html
#undef YY_INPUT
#define YY_INPUT(buf, result, max_size) (result = my_yyinput(buf, max_size))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "beacon.tab.h"
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

#define YY_NO_UNISTD_H

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
	bc_Parser* p = bc_GetCurrentParser();
	p->Result = PARSE_SYNTAX_ERROR_T;
	p->ErrorLineIndex = yylloc.last_line;
	p->ErrorColumnIndex = yylloc.last_column;
	p->ErrorMessage = bc_Strdup(err_str);
	p->ErrorLineText  = bc_GetLineAt(yaccSourceBuffer, yylloc.last_line);
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
	int result;
	bc_Parser* p = bc_GetCurrentParser();
	switch (p->InputType) {
		case YINPUT_FILE_T:
			result = file_input(buf, max_size);
			break;
		case YINPUT_STRING_T:
			result = string_input(buf, max_size);
			break;
		default:
			return 0;
	}
	return result;
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
<INITIAL>"`"				{ return (QUOTE); }



<INITIAL>"+"				{ return (ADD); }
<INITIAL>"-"				{ return (SUB); }
<INITIAL>"*"				{ return (MUL); }
<INITIAL>"/"				{ return (DIV); }
<INITIAL>"%"				{ return (MOD); }
<INITIAL>"!"				{ return (NOT); }
<INITIAL>"^"				{ return (EXC_OR); }
<INITIAL>"~"				{ return (CHILDA); }

<INITIAL>"<<"				{ return (LSHIFT); }
<INITIAL>">>"				{ return (RSHIFT); }

<INITIAL>"="				{ return (ASSIGN); }
<INITIAL>"+="				{ return (ADD_ASSIGN); }
<INITIAL>"-="				{ return (SUB_ASSIGN); }
<INITIAL>"*="				{ return (MUL_ASSIGN); }
<INITIAL>"/="				{ return (DIV_ASSIGN); }
<INITIAL>"%="				{ return (MOD_ASSIGN); }

<INITIAL>"|="				{ return (OR_ASSIGN); }
<INITIAL>"&="				{ return (AND_ASSIGN); }
<INITIAL>"^="				{ return (EXC_OR_ASSIGN); }
<INITIAL>"&="				{ return (AND_ASSIGN); }
<INITIAL>"<<="				{ return (LSHIFT_ASSIGN); }
<INITIAL>">>="				{ return (RSHIFT_ASSIGN); }

<INITIAL>"=="				{ return (EQUAL); }
<INITIAL>"!="				{ return (NOTEQUAL); }
<INITIAL>"assert"			{ return (ASSER_T); }
<INITIAL>"defer"			{ return (DEFER); }


<INITIAL>"<|"				{ return (LGEN); }
<INITIAL>"|>"				{ return (RGEN); }

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
<INITIAL>"(&)"				{ return (SUBSCRIPT_GET); }
<INITIAL>"(=)"				{ return (SUBSCRIPT_SET); }
<INITIAL>"<:"				{ return (BOUNDS_EXTENDS); }
<INITIAL>":>"				{ return (BOUNDS_SUPER); }

<INITIAL>"require"			{ return (IMPORT); }
<INITIAL>"var"				{ return (VAR); }

<INITIAL>"if"				{ return (IF); }
<INITIAL>"elif"				{ return (ELIF); }
<INITIAL>"else"				{ return (ELSE); }
<INITIAL>"final"			{ return (FINAL); }

<INITIAL>"while"			{ return (WHILE); }
<INITIAL>"break"			{ return (BREAK); }
<INITIAL>"continue"			{ return (CONTINUE); }

<INITIAL>"namespace"		{ return (NAMESPACE); }
<INITIAL>"abstract"			{ return (ABSTRACT); }
<INITIAL>"class"			{ return (CLASS); }
<INITIAL>"enum"				{ return (ENUM); }
<INITIAL>"interface"		{ return (INTERFACE); }
<INITIAL>"this"				{ return (THIS_TOK); }
<INITIAL>"super"			{ return (SUPER_TOK); }
<INITIAL>"new"				{ return (NEW); }

<INITIAL>"true"			{ return (TRUE_TOK); }
<INITIAL>"false"		{ return (FALSE_TOK); }
<INITIAL>"null"			{ return (NULL_TOK); }
<INITIAL>"as"			{ return (AS); }
<INITIAL>"is"			{ return (INSTANCEOF); }
<INITIAL>"property"		{ return (PROPERTY); }
<INITIAL>"defset"		{ return (DEFSET); }
<INITIAL>"defget"		{ return (DEFGET); }

<INITIAL>"try"			{ return (TRY); }
<INITIAL>"catch"		{ return (CATCH); }
<INITIAL>"throw"		{ return (THROW); }

<INITIAL>"public"			{ return (PUBLIC); }
<INITIAL>"private"			{ return (PRIVATE); }
<INITIAL>"protected"		{ return (PROTECTED); }
<INITIAL>"static"			{ return (STATIC); }
<INITIAL>"native"			{ return (NATIVE); }
<INITIAL>"return"			{ return (RETURN); }
<INITIAL>"yield"			{ return (YIELD); }

<INITIAL>"def"				{ return (DEF); }
<INITIAL>"operator"			{ return (OPERATOR); }
<INITIAL>"->"				{ return (ARROW); }

<INITIAL>"0"[s|S] {
	//0s
	yylval.ast_value = bc_NewASTShort(0);
	return SHORT;
}

<INITIAL>"0"[l|L] {
	//0l
	yylval.ast_value = bc_NewASTLong(0);
	return LONG;
}

<INITIAL>"0"[i|I]? {
	//0
	//0i
	yylval.ast_value = bc_NewASTInt(0);
	return INT;
}

<INITIAL>"\n" {
	bc_GetCurrentParser()->Lineno++;
}

<INITIAL>[1-9][0-9]*[s|S] {
	//100s
	yylval.ast_value = bc_NewASTShort(bc_StrToShort(yytext));
	return SHORT;
}

<INITIAL>[1-9][0-9]*[i|I]? {
	//100
	//100i
	yylval.ast_value = bc_NewASTInt(bc_StrToInt(yytext));
	return INT;
}

<INITIAL>[1-9][0-9]*[l|L] {
	//100l
	yylval.ast_value = bc_NewASTLong(bc_StrToLong(yytext));
	return LONG;
}

<INITIAL>[1-9][0-9]*[f|F] {
	//100f
	yylval.ast_value = bc_NewASTFloat(bc_StrToFloat(yytext));
	return FLOAT;
}

<INITIAL>[0-9]*\.[0-9]+[f|F] {
	//10.0f
	yylval.ast_value = bc_NewASTFloat(bc_StrToFloat(yytext));
	return FLOAT;
}

<INITIAL>[0-9]*\.[0-9]+[d|D]? {
	//10.0
	//10.0d
	yylval.ast_value = bc_NewASTDouble(bc_StrToDouble(yytext));
	return DOUBLE;
}
<INITIAL>[1-9][0-9]*[d|D] {
	//100d
	yylval.ast_value = bc_NewASTDouble(bc_StrToDouble(yytext));
	return DOUBLE;
}

<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
	yylval.stringv_value = bc_InternString(yytext);
	return IDENT;
}

<INITIAL>[ \t] {
}

<INITIAL>\" {
	bc_ClearParserBuffer(bc_GetCurrentParser());
    BEGIN STRING_LITERAL_STATE;
}
<INITIAL>"/*"     BEGIN ML_COMMENT;
<INITIAL>"//"     BEGIN L_COMMENT;
<ML_COMMENT>\n     {
	bc_GetCurrentParser()->Lineno++;
}
<ML_COMMENT>"*/"     {
    BEGIN INITIAL;
}
<ML_COMMENT>.      ;
<L_COMMENT>\n  {
	bc_GetCurrentParser()->Lineno++;
	BEGIN INITIAL;
}
<L_COMMENT><<EOF>>   {
	BEGIN INITIAL;
}
<L_COMMENT>.   ;
<INITIAL>\'\\r\' {
	yylval.ast_value = bc_NewASTChar('\r');
	return CHAR_LITERAL;
}
<INITIAL>\'\\n\' {
	yylval.ast_value = bc_NewASTChar('\n');
	return CHAR_LITERAL;
}
<INITIAL>\'\\t\' {
	yylval.ast_value = bc_NewASTChar('\t');
	return CHAR_LITERAL;
}
<INITIAL>\'\\b\' {
	yylval.ast_value = bc_NewASTChar('\b');
	return CHAR_LITERAL;
}
<INITIAL>\'.\' {
	yylval.ast_value = bc_NewASTChar(yytext[1]);
	return CHAR_LITERAL;
}
<STRING_LITERAL_STATE>\" {
	yylval.ast_value = bc_ReduceParserBuffer(bc_GetCurrentParser());
    BEGIN INITIAL;
	return STRING_LITERAL;
}
<STRING_LITERAL_STATE>\\\"	{
	bc_AppendParserBuffer(bc_GetCurrentParser(), '"');
}
<STRING_LITERAL_STATE>\\\'	{
	bc_AppendParserBuffer(bc_GetCurrentParser(), '\'');
}
<STRING_LITERAL_STATE>\\r	{
	bc_AppendParserBuffer(bc_GetCurrentParser(), '\r');
}
<STRING_LITERAL_STATE>\\n	{
	bc_AppendParserBuffer(bc_GetCurrentParser(), '\n');
}
<STRING_LITERAL_STATE>\\t	{
	bc_AppendParserBuffer(bc_GetCurrentParser(), '\t');
}
<STRING_LITERAL_STATE>\\\\	{
	bc_AppendParserBuffer(bc_GetCurrentParser(), '\\');
}
<STRING_LITERAL_STATE>.	{
	bc_AppendParserBuffer(bc_GetCurrentParser(), yytext[0]);
}
%%
