%{
//http://kmaebashi.com/programmer/devlang/diksam.html
#undef YY_INPUT
#define YY_INPUT(buf, result, max_size) (result = my_yyinput(buf, max_size))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "signal.tab.h"
#include "parser.h"
#include "../ast/ast.h"
#include "../ast/ast_new_literal.h"
#include "../ast/constructor_chain_type.h"
#include "../util/text.h"

//for C4996
#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif

static char* yaccSourceBuffer;
static int yaccSourceOffset;
 
int yymain(void) {
	yyparse();
	return(0);
}

int yywrap(void) {
	return 1;
}

int yyerror(char * err_str) {
	system("cls");
	parser* p = parser_top();
	p->errorLineIndex = yylloc.last_line;
	p->errorColumnIndex = yylloc.last_column;
	//put filename
	printf("file=%s ", p->source_name);
	//put line
	printf("line=%d ", yylloc.last_line);
	//put column
	printf("column=%d", yylloc.last_column);
	text_putline();
	//put message
	fprintf (stderr, "%s\n", err_str);
	if(yaccSourceBuffer == NULL) {
		return 0;
	}
	int len = strlen(yaccSourceBuffer);
	int line = 1;
	int startOffset = 0;
	int endOffset = 0;
	//find startoffset in error line
	for(int i=0; i<len; i++) {
		char ch = yaccSourceBuffer[i];
		//FIXME:windows only?
		if(ch == '\n') {
			line++;
		}
		if(line == yylloc.last_line) {
		startOffset++;
			break;
		}
		startOffset++;
	}
	//find endoffset in error line
	endOffset = startOffset;
	for(int i=startOffset+1; i<len; i++) {
		char ch = yaccSourceBuffer[i];
		//FIXME:windows only?
		if(ch == '\n') {
			break;
		}
		endOffset++;
	}
	//extract error text
	int errorLen = endOffset - startOffset;
	char* errorLineText = (char*)malloc(sizeof(char) * errorLen);
	char* rulerLineText = (char*)malloc(sizeof(char) * errorLen);
	for(int i=startOffset; i<endOffset; i++) {
		errorLineText[i-startOffset] = yaccSourceBuffer[i];
		rulerLineText[i-startOffset] = ' ';
	}
	//highlight at cursor
	if(errorLen > 3) {
		rulerLineText[errorLen - 1] = '^';
		rulerLineText[errorLen - 2] = '^';
		rulerLineText[errorLen - 3] = '^';
	} else {
		rulerLineText[errorLen - 1] = '^';
	}
	printf(errorLineText);
	text_putline();
	printf(rulerLineText);
	text_putline();
	free(errorLineText);
	free(rulerLineText);
	return 0;
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
	parser* p = parser_top();
	switch (p->input_type) {
		case yinput_file:
			result = file_input(buf, max_size);
			break;
		case yinput_string:
			result = string_input(buf, max_size);
			break;
		default:
			return 0;
	}
	return result;
}
//error position
static void update_loc() {
  static int curr_line = 1;
  static int curr_col  = 1;

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

#define YY_USER_ACTION update_loc();
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

<INITIAL>"if"				{ return (IF); }
<INITIAL>"elif"				{ return (ELIF); }
<INITIAL>"else"				{ return (ELSE); }

<INITIAL>"namespace"		{ return (NAMESPACE); }
<INITIAL>"class"			{ return (CLASS); }
<INITIAL>"this"				{ return (THIS); }
<INITIAL>"super"			{ return (SUPER); }
<INITIAL>"new"				{ return (NEW); }

<INITIAL>"public"			{ return (PUBLIC); }
<INITIAL>"private"			{ return (PRIVATE); }
<INITIAL>"protected"		{ return (PROTECTED); }
<INITIAL>"static"			{ return (STATIC); }

<INITIAL>"def"				{ return (DEF); }
<INITIAL>"->"				{ return (ARROW); }

<INITIAL>"0" {
	yylval.ast_value = ast_new_int(0);
	return INT;
}

<INITIAL>[1-9][0-9]* {
	yylval.ast_value = ast_new_int(atoi(yytext));
	return INT;
}

<INITIAL>[0-9]+\.[0-9]+ {
	yylval.ast_value = ast_new_double(atof(yytext));
	return DOUBLE;
}

<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
	yylval.string_value = text_strdup(yytext);
	return IDENT;
}

<INITIAL>\" {
	parser_clear_buffer(parser_top());
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
	yylval.ast_value = ast_new_char('\r');
	return CHAR_LITERAL;
}
<INITIAL>\'\\n\' {
	yylval.ast_value = ast_new_char('\n');
	return CHAR_LITERAL;
}
<INITIAL>\'\\t\' {
	yylval.ast_value = ast_new_char('\t');
	return CHAR_LITERAL;
}
<INITIAL>\'\\b\' {
	yylval.ast_value = ast_new_char('\b');
	return CHAR_LITERAL;
}
<INITIAL>\'.\' {
	yylval.ast_value = ast_new_char(yytext[1]);
	return CHAR_LITERAL;
}
<STRING_LITERAL_STATE>\" {
	yylval.ast_value = parser_reduce_buffer(parser_top());
    BEGIN INITIAL;
	return STRING_LITERAL;
}
<STRING_LITERAL_STATE>\\\"	parser_append_buffer(parser_top(), '"');
<STRING_LITERAL_STATE>\\\'	parser_append_buffer(parser_top(), '\'');
<STRING_LITERAL_STATE>\\r	parser_append_buffer(parser_top(), '\r');
<STRING_LITERAL_STATE>\\n	parser_append_buffer(parser_top(), '\n');
<STRING_LITERAL_STATE>\\t	parser_append_buffer(parser_top(), '\t');
<STRING_LITERAL_STATE>\\\\	parser_append_buffer(parser_top(), '\\');
<STRING_LITERAL_STATE>.	{
	parser_append_buffer(parser_top(), yytext[0]);
}
%%