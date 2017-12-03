%{
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast_new_operator.h"
#define YYDEBUG 1
#define YYERROR_VERBOSE 1
%}
%union {
	char char_value;
	const char* string_value;
	ast* ast_value;
}
%token <ast_value>			INT
%token <ast_value>			DOUBLE
%token DOT COMMA COLON COLO_COLO
		ADD SUB MUL DIV MOD NOT
		ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
		EQUAL NOTEQUAL
		INC DEC
		GT GE LT LE
		BIT_AND LOGIC_AND BIT_OR LOGIC_OR
		LCB RCB LRB RRB LSB RSB
%type <ast_value> root top_level addsub muldiv primary
%%
root
	: top_level
	| root top_level
	;
top_level
	: addsub
	{
		ast_compile_entry($1);
	}
	;
addsub
	: muldiv
	| addsub ADD muldiv
	{
		$$ = ast_new_add($1, $3);
	}
	| addsub SUB muldiv
	{
		$$ = ast_new_sub($1, $3);
	}
	;
muldiv
	: primary
	| muldiv MUL primary
	{
		$$ = ast_new_mul($1, $3);
	}
	| muldiv DIV primary
	{
		$$ = ast_new_div($1, $3);
	}
	| muldiv MOD primary
	{
		$$ = ast_new_mod($1, $3);
	}
	;
primary
	: INT
	| DOUBLE
	| LRB addsub RRB
	{
		$$ = $2;
	}
	;
%%