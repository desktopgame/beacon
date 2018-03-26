%{
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast_new_factor.h"
#include "../ast/ast_new_operator.h"
#include "../ast/ast_new_stmt.h"
#include "../ast/ast_new_decl.h"
#include "../ast/constructor_chain_type.h"
#include "../ast/assign_operator_type.h"
#include "../ast/modifier_type.h"
#include "../ast/access_level.h"
#define YYDEBUG 1
#define YYERROR_VERBOSE 1
%}
%union {
	char char_value;
	const char* string_value;
	ast* ast_value;
	assign_operator_type assign_otype_value;
	constructor_chain_type chain_type_value;
	modifier_type modifier_type_value;
	access_level access_level_value;
}


%locations
%token <ast_value>			CHAR_LITERAL
%token <ast_value>			STRING_LITERAL
%token <ast_value>			INT
%token <ast_value>			DOUBLE
%token <string_value>		IDENT
%type <chain_type_value>	constructor_chain_type_T
%type <access_level_value>	access_level_T
%type <modifier_type_value> modifier_type_T;
%token DOT COMMA COMMA_OPT COLON COLO_COLO
		ADD SUB MUL DIV MOD NOT LSHIFT RSHIFT CHILDA
		EQUAL NOTEQUAL
		GT GE LT LE
		BIT_AND LOGIC_AND BIT_OR LOGIC_OR

		ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
		AND_ASSIGN OR_ASSIGN LSHIFT_ASSIGN RSHIFT_ASSIGN EXC_OR_ASSIGN

		INC DEC EXC_OR

		LCB RCB LRB RRB LSB RSB
		SEMI IMPORT VAR

		THIS SUPER TRUE_TOK FALSE_TOK NULL_TOK AS

		INTERFACE CLASS ENUM PUBLIC PRIVATE PROTECTED STATIC NATIVE NEW
		IN OUT
		CTOR DEF ARROW NAMESPACE RETURN
		IF ELIF ELSE WHILE BREAK CONTINUE TRY CATCH THROW
%type <ast_value> compilation_unit 
					program 
					namespace_decl
					namespace_body
					namespace_member_decl_list
					namespace_member_decl
					namespace_member_decl_optional
					namespace_path
					import 
					parameterized_typename
					type_parameter_group
					type_parameter_list
					type_parameter
					type_parameter_rule_list
					class_decl 
					enum_decl
					interface_decl
						access_member_tree_opt
						access_member_tree
						access_member_list
						member_define_list
						member_define
						constructor_define
						constructor_chain
						constructor_chain_optional
						function_define
						method_define
						field_define
						ident_list
						parameter_list
						argument_list
						typename_group
						typename_list
						typename_T
					expression
						expression_nobrace
						primary
					stmt_list
						stmt
						variable_decl_stmt
						variable_init_stmt
						inferenced_type_init_stmt
						if_stmt
							elif_list
							elif
						while_stmt
						break_stmt
						continue_stmt
						return_stmt
						throw_stmt
						try_stmt
						catch_stmt_list
						catch_stmt
						scope
						scope_optional
%left EQUAL NOTEQUAL
%left GT GE LT LE
%left LOGIC_AND
%left LOGIC_OR
%left BIT_AND
%left BIT_OR
%left EXC_OR
%left LSHIFT RSHIFT
%left ADD SUB
%left MUL DIV MOD
%left DOT FUNCCALL
%right CHILDA NOT NEGATIVE POSITIVE
%right ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN OR_ASSIGN LSHIFT_ASSIGN RSHIFT_ASSIGN EXC_OR_ASSIGN
%%


compilation_unit
	: program
	| error '\n'
	{
		$$ = ast_new_blank();
	}
	;

program
	: stmt_list
	{
		ast_compile_entry($1);
	}
	| import
	{
		ast_compile_entry($1);
	}
	| namespace_decl
	{
		ast_compile_entry($1);
	}
	| function_define
	{
		ast_compile_entry($1);
	}
	;

namespace_decl
	: NAMESPACE namespace_path namespace_body
	{
		$$ = ast_new_namespace_decl($2, $3);
	}
	;

namespace_body
	: LCB namespace_member_decl_optional RCB
	{
		$$ = $2
	}
	;

namespace_member_decl
	: NAMESPACE namespace_path namespace_body
	{
		$$ = ast_new_namespace_namespace_decl($2, $3);
	}
	| class_decl
	| interface_decl
	| enum_decl
	;

namespace_member_decl_list
	: namespace_member_decl
	{
		$$ = $1
	}
	| namespace_member_decl_list namespace_member_decl
	{
		$$ = ast_new_namespace_member_decl_list($1, $2);
	}
	;

namespace_member_decl_optional
	: /* empty */
	{
		$$ = ast_new_blank();
	}
	| namespace_member_decl_list
	;

namespace_path
	: IDENT
	{
		$$ = ast_new_namespace_path($1);
	}
	| namespace_path DOT IDENT
	{
		$$ = ast_new_namespace_path_list($1, $3);
	}
	;

import
	: IMPORT STRING_LITERAL
	{
		$$ = ast_new_import_decl(ast_new_import_path($2));
	}
	;

parameterized_typename
	: IDENT type_parameter_group
	{
		$$ = ast_new_parameterized_typename($1, $2);
	}
	;

type_parameter_group
	: /* empty */
	{
		$$ = ast_new_blank();
	}
	| LT type_parameter_list GT
	{
		$$ = $2;
	}
	;

type_parameter_list
	: type_parameter
	{
		$$ = $1;
	}
	| type_parameter_list COMMA type_parameter
	{
		$$ = ast_new_type_parameter_list($3, $1);
	}
	;

type_parameter
	: IDENT type_parameter_rule_list
	{
		$$ = ast_new_type_parameter($1, $2);
	}
	| IN IDENT type_parameter_rule_list
	{
		$$ = ast_new_type_in_parameter($2, $3);
	}
	| OUT IDENT type_parameter_rule_list
	{
		$$ = ast_new_type_out_parameter($2, $3);
	}
	;

type_parameter_rule_list
	: /* empty */
	{
		$$ = ast_new_blank();
	}
	| LRB typename_list RRB
	{
		$$ = ast_new_type_parameter_rule_list($2);
	}
	;

class_decl
	: CLASS parameterized_typename LCB access_member_tree_opt RCB
	{
		$$ = ast_new_class_decl($2, ast_new_blank(), $4);
	}
	| CLASS parameterized_typename COLON typename_list LCB access_member_tree_opt RCB
	{
		$$ = ast_new_class_decl($2, $4, $6);
	}
	;

enum_decl
	: ENUM IDENT LCB ident_list RCB
	{
		$$ = ast_new_enum_decl($2, $4);
	}
	| ENUM IDENT LCB ident_list COMMA RCB
	{
		$$ = ast_new_enum_decl($2, $4);
	}
	;

interface_decl
	: INTERFACE parameterized_typename LCB access_member_tree_opt RCB
	{
		$$ = ast_new_interface_decl($2, ast_new_blank(), $4);
	}
	| INTERFACE parameterized_typename COLON typename_list LCB access_member_tree_opt RCB
	{
		$$ = ast_new_interface_decl($2, $4, $6);
	}
	;

access_member_tree_opt
	: /* empty */
	{
		$$ = ast_new_blank();
	}
	| access_member_tree
	;

access_member_tree
	: access_member_list
	| access_member_tree access_member_list
	{
		$$ = ast_new_access_member_tree($1, $2);
	}
	;

access_member_list
	: access_level_T COLON member_define_list
	{
		$$ = ast_new_access_member_list($1, $3);
	}
	;

member_define_list
	: member_define
	{
		$$ = ast_new_member_decl($1);
	}
	| member_define_list member_define
	{
		$$ = ast_new_member_decl_list($1, ast_new_member_decl($2));
	}
	;

member_define
	: constructor_define
	| method_define
	| field_define
	;

constructor_define
	: CTOR NEW LRB parameter_list RRB constructor_chain_optional scope_optional
	{
		$$ = ast_new_constructor_decl($4, $6, $7);
	}
	| CTOR NEW LRB RRB constructor_chain_optional scope_optional
	{
		$$ = ast_new_constructor_decl(ast_new_blank(), $5, $6);
	}
	;

constructor_chain
	: COLON constructor_chain_type_T LRB argument_list RRB
	{
		$$ = ast_new_constructor_chain($2, $4);
	}
	| COLON constructor_chain_type_T LRB RRB
	{
		$$ = ast_new_constructor_chain($2, ast_new_blank());
	}
	;

constructor_chain_type_T
	: SUPER
	{
		$$ = chain_type_super;
	}
	| THIS
	{
		$$ = chain_type_this;
	}
	;

constructor_chain_optional
	: /* empty */
	{
		$$ = ast_new_blank();
	}
	| constructor_chain
	;

function_define
	: DEF IDENT LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = ast_new_function_decl($2, $4, $8, $7);
	}
	| DEF IDENT LRB RRB ARROW typename_T scope_optional
	{
		$$ = ast_new_function_decl_empty_params($2, $7, $6);
	}
	;

method_define
	: modifier_type_T DEF IDENT type_parameter_group LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = ast_new_method_decl($1, $3, $4, $6, $10, $9);
	}
	| modifier_type_T DEF IDENT type_parameter_group LRB RRB ARROW typename_T scope_optional
	{
		$$ = ast_new_method_decl_empty_params($1, $3, $4, $9, $8);
	}
	;

field_define
	: modifier_type_T typename_T IDENT SEMI
	{
		$$ = ast_new_field_decl($1, $2, $3);
	}
	;

modifier_type_T
	: /* empty */
	{
		$$ = modifier_none;
	}
	| STATIC NATIVE
	{
		$$ = modifier_static_native();
	}
	| NATIVE STATIC
	{
		$$ = modifier_static_native();
	}
	| STATIC
	{
		$$ = modifier_static;
	}
	| NATIVE
	{
		$$ = modifier_native;
	}
	;

access_level_T
	: PUBLIC
	{
		$$ = access_public;
	}
	| PRIVATE
	{
		$$ = access_private;
	}
	| PROTECTED
	{
		$$ = access_protected;
	}
	;

ident_list
	: IDENT
	{
		$$ = ast_new_identifier($1);
	}
	| ident_list COMMA IDENT
	{
		$$ = ast_new_identifier_list($3, $1);
	}
	;

parameter_list
	: typename_T IDENT
	{
		$$ = ast_new_parameter($1, $2);
	}
	| parameter_list COMMA typename_T IDENT
	{
		$$ = ast_new_parameter_list($3, $4, $1)
	}
	;

argument_list
	: expression
	{
		$$ = ast_new_argument($1);
	}
	| argument_list COMMA expression
	{
		$$ = ast_new_argument_list(ast_new_argument($3), $1);
	}
	;

typename_group
	: /* empty */
	{
		$$ = ast_new_blank();
	}
	| '<' typename_list '>'
	{
		$$ = $2;
	}
	;

typename_list
	: typename_T
	{
		$$ = $1;
	}
	| typename_list COMMA typename_T
	{
		$$ = ast_new_typename_list($3, $1);
	}
	;

typename_T
	: IDENT typename_group
	{
		$$ = ast_new_blank();
	}
	;




expression
	: LRB expression RRB
	{
		$$ = $2;
	}
	| expression_nobrace
	;
expression_nobrace
	: primary
	| ADD expression %prec POSITIVE
	{
		$$ = ast_new_unary(ast_pos, $2);
	}
	| SUB expression %prec NEGATIVE
	{
		$$ = ast_new_unary(ast_neg, $2);
	}
	| expression ADD expression
	{
		$$ = ast_new_binary(ast_add, $1, $3);
	}
	| expression SUB expression
	{
		$$ = ast_new_binary(ast_sub, $1, $3);
	}
	| expression MUL expression
	{
		$$ = ast_new_binary(ast_mul, $1, $3);
	}
	| expression DIV expression
	{
		$$ = ast_new_binary(ast_div, $1, $3);
	}
	| expression MOD expression
	{
		$$ = ast_new_binary(ast_mod, $1, $3);
	}
	| expression BIT_OR expression
	{
		$$ = ast_new_binary(ast_bit_or, $1, $3);
	}
	| expression EQUAL expression
	{
		$$ = ast_new_binary(ast_equal, $1, $3);
	}
	| expression NOTEQUAL expression
	{
		$$ = ast_new_binary(ast_notequal, $1, $3);
	}
	| expression BIT_AND expression
	{
		$$ = ast_new_binary(ast_bit_and, $1, $3);
	}
	| expression EXC_OR expression
	{
		$$ = ast_new_binary(ast_exc_or, $1, $3);
	}
	| expression LOGIC_OR expression
	{
		$$ = ast_new_binary(ast_logic_or, $1, $3);
	}
	| expression LOGIC_AND expression
	{
		$$ = ast_new_binary(ast_logic_and, $1, $3);
	}
	| expression ASSIGN expression
	{
		$$ = ast_new_binary(ast_assign, $1, $3);
	}
	| expression ADD_ASSIGN expression
	{
		$$ = ast_new_binary(ast_add_assign, $1, $3);
	}
	| expression SUB_ASSIGN expression
	{
		$$ = ast_new_binary(ast_sub_assign, $1, $3);
	}
	| expression MUL_ASSIGN expression
	{
		$$ = ast_new_binary(ast_mul_assign, $1, $3);
	}
	| expression DIV_ASSIGN expression
	{
		$$ = ast_new_binary(ast_div_assign, $1, $3);
	}
	| expression MOD_ASSIGN expression
	{
		$$ = ast_new_binary(ast_mod_assign, $1, $3);
	}
	| expression AND_ASSIGN expression
	{
		$$ = ast_new_binary(ast_and_assign, $1, $3);
	}
	| expression OR_ASSIGN expression
	{
		$$ = ast_new_binary(ast_or_assign, $1, $3);
	}
	| expression EXC_OR_ASSIGN expression
	{
		$$ = ast_new_binary(ast_exc_or_assign, $1, $3);
	}
	| expression LSHIFT_ASSIGN expression
	{
		$$ = ast_new_binary(ast_lshift_assign, $1, $3);
	}
	| expression RSHIFT_ASSIGN expression
	{
		$$ = ast_new_binary(ast_rshift_assign, $1, $3);
	}
	| expression GT expression
	{
		$$ = ast_new_binary(ast_gt, $1, $3);
	}
	| expression GE expression
	{
		$$ = ast_new_binary(ast_ge, $1, $3);
	}
	| expression LT expression
	{
		$$ = ast_new_binary(ast_lt, $1, $3);
	}
	| expression LE expression
	{
		$$ = ast_new_binary(ast_le, $1, $3);
	}
	| expression LSHIFT expression
	{
		$$ = ast_new_binary(ast_lshift, $1, $3);
	}
	| expression RSHIFT expression
	{
		$$ = ast_new_binary(ast_rshift, $1, $3);
	}
	| expression DOT IDENT
	{
		$$ = ast_new_blank();
	}
	| CHILDA expression
	{
		$$ = ast_new_unary(ast_childa, $2);
	}
	| NOT expression
	{
		$$ = ast_new_unary(ast_not, $2);
	}
	| expression_nobrace LRB RRB %prec FUNCCALL
	{
		$$ = ast_new_blank();
	}
	| expression_nobrace LRB argument_list RRB %prec FUNCCALL
	{
		$$ = ast_new_blank();
	}
	;
primary
	: INT
	| DOUBLE
	| CHAR_LITERAL
	| STRING_LITERAL
	| TRUE_TOK
	{
		$$ = ast_new_true();
	}
	| FALSE_TOK
	{
		$$ = ast_new_false();
	}
	| NULL_TOK
	{
		$$ = ast_new_null();
	}
	;



stmt_list
	: stmt
	{
		$$ = ast_new_stmt($1);
	}
	| stmt_list stmt
	{
		$$ = ast_new_stmt_list($1, $2);
	}
	;
stmt
	: expression stmt_term
	{
		$$ = ast_new_proc($1);
	}
	| variable_decl_stmt
	| variable_init_stmt
	| inferenced_type_init_stmt
	| if_stmt
	| while_stmt
	| break_stmt
	| continue_stmt
	| return_stmt
	| throw_stmt
	| try_stmt
	;
variable_decl_stmt
	: typename_T IDENT SEMI
	{
		$$ = ast_new_variable_decl($1, $2);
	}
	;
variable_init_stmt
	: typename_T IDENT ASSIGN expression stmt_term
	{
		$$ = ast_new_variable_init($1, $2, $4);
	}
	;
inferenced_type_init_stmt
	: VAR IDENT ASSIGN expression stmt_term
	{
		$$ = ast_new_inferenced_type_init($2, $4);
	}
	;
if_stmt
	: IF LRB expression RRB scope
	{
		$$ = ast_new_if($3, $5);
	}
	| IF LRB expression RRB scope ELSE scope
	{
		$$ = ast_new_if_else($3, $5, $7);
	}
	| IF LRB expression RRB scope elif_list
	{
		$$ = ast_new_if_elif_list($3, $5, $6);
	}
	| IF LRB expression RRB scope elif_list ELSE scope
	{
		$$ = ast_new_if_elif_list_else($3, $5, $6, $8);
	}
	;
elif_list
	: elif
	| elif_list elif
	{
		$$ = ast_new_elif_list($1, $2);
	}
	;
elif
	: ELIF LRB expression RRB scope
	{
		$$ = ast_new_elif($3, $5);
	}
	;
while_stmt
	: WHILE LRB expression RRB scope_optional
	{
		$$ = ast_new_while($3, $5);
	}
	;
break_stmt
	: BREAK stmt_term
	{
		$$ = ast_new_break();
	}
	;
continue_stmt
	: CONTINUE stmt_term
	{
		$$ = ast_new_continue();
	}
	;
return_stmt
	: RETURN expression stmt_term
	{
		$$ = ast_new_return($2);
	}
	;
throw_stmt
	: THROW expression stmt_term
	{
		$$ = ast_new_throw($2);
	}
	;
try_stmt
	: TRY scope catch_stmt_list
	{
		$$ = ast_new_try($2, $3);
	}
	;
catch_stmt_list
	: catch_stmt
	{
		$$ = $1;
	}
	| catch_stmt_list catch_stmt
	{
		$$ = ast_new_catch_list($2, $1);
	}
	;
catch_stmt
	: CATCH LRB typename_T IDENT RRB scope
	{
		$$ = ast_new_catch($3, $4, $6);
	}
	;



scope
	: LCB stmt_list RCB
	{
		$$ = ast_new_scope($2);
	}
	| LCB RCB
	{
		$$ = ast_new_scope_empty();
	}
	;
scope_optional
	: SEMI
	{
		$$ = ast_new_blank();
	}
	| scope
	;
stmt_term
	: SEMI
	| '\n'
	;
%%



