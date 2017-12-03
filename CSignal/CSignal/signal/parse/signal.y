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
%type <ast_value> root top_level expression assign 
					or and equal compare addsub muldiv 
					unary prefix postfix primary
%%
root
	: top_level
	| root top_level
	;
top_level
	: expression
	{
		ast_compile_entry($1);
	}
	;
expression
	: assign
	;
assign
	: or
	| or ASSIGN assign
	{
		$$ = ast_new_assign($1, $3);
	}
	| or ADD_ASSIGN assign
	{
		$$ = ast_new_add_assign($1, $3);
	}
	| or SUB_ASSIGN assign
	{
		$$ = ast_new_sub_assign($1, $3);
	}
	| or MUL_ASSIGN assign
	{
		$$ = ast_new_mul_assign($1, $3);
	}
	| or DIV_ASSIGN assign
	{
		$$ = ast_new_div_assign($1, $3);
	}
	| or MOD_ASSIGN assign
	{
		$$ = ast_new_mod_assign($1, $3);
	}
	;
or
	: and
	| or BIT_OR and
	{
		$$ = ast_new_bit_or($1, $3);
	}
	| or LOGIC_OR and
	{
		$$ = ast_new_logic_or($1, $3);
	}
	;
and
	: equal
	| and BIT_AND equal
	{
		$$ = ast_new_bit_and($1, $3);
	}
	| and LOGIC_AND equal
	{
		$$ = ast_new_logic_and($1, $3);
	}
	;
equal
	: compare
	| equal EQUAL compare
	{
		$$ = ast_new_equal($1, $3);
	}
	| equal NOTEQUAL compare
	{
		$$ = ast_new_notequal($1, $3);
	}
	;
compare
	: addsub
	| compare GT addsub
	{
		$$ = ast_new_gt($1, $3);
	}
	| compare GE addsub
	{
		$$ = ast_new_ge($1, $3);
	}
	| compare LT addsub
	{
		$$ = ast_new_lt($1, $3);
	}
	| compare LE addsub
	{
		$$ = ast_new_le($1, $3);
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
	: unary
	| muldiv MUL unary
	{
		$$ = ast_new_mul($1, $3);
	}
	| muldiv DIV unary
	{
		$$ = ast_new_div($1, $3);
	}
	| muldiv MOD unary
	{
		$$ = ast_new_mod($1, $3);
	}
	;
unary
	: prefix
	| NOT unary
	{
		$$ = ast_new_not($2);
	}
	| SUB unary
	{
		$$ = ast_new_neg($2);
	}
	;
prefix
	: postfix
	| INC postfix
	{
		$$ = ast_new_pre_inc($2);
	}
	| DEC postfix
	{
		$$ = ast_new_pre_dec($2);
	}
	;
postfix
	: primary
	| postfix INC
	{
		$$ = ast_new_post_inc($1);
	}
	| postfix DEC
	{
		$$ = ast_new_post_dec($1);
	}
	;
primary
	: INT
	| DOUBLE
	| LRB expression RRB
	{
		$$ = $2;
	}
	;
%%