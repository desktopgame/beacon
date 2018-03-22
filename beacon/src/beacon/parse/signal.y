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
%type <assign_otype_value>	assign_type_T
%type <chain_type_value>	constructor_chain_type_T
%type <access_level_value>	access_level_T
%type <modifier_type_value> modifier_type_T;
%token DOT COMMA COMMA_OPT COLON COLO_COLO
		ADD SUB MUL DIV MOD NOT
		ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
		EQUAL NOTEQUAL
		INC DEC
		GT GE LT LE
		BIT_AND LOGIC_AND BIT_OR LOGIC_OR
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
						fqcn_part
					expression 
						assign 
						or 
						and 
						equal 
						compare 
						addsub 
						muldiv 
						unary 
						prefix 
						postfix 
						primary
						primary_nobrace
						primary_literal
						primary_assoc
						primary_faccess
						primary_mcall
						primary_maccess
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
%left UMINUS
%left NONAME
%%


compilation_unit
	: program
	| error '\n'
	{
	}
	;

program
	: stmt_list
	{
	}
	| import
	{
	}
	| namespace_decl
	{
	}
	| function_define
	{
	}
	;

namespace_decl
	: NAMESPACE namespace_path namespace_body
	{
	}
	;

namespace_body
	: LCB namespace_member_decl_optional RCB
	{
	}
	;

namespace_member_decl
	: NAMESPACE namespace_path namespace_body
	{
	}
	| class_decl
	| interface_decl
	| enum_decl
	;

namespace_member_decl_list
	: namespace_member_decl
	{
	}
	| namespace_member_decl_list namespace_member_decl
	{
	}
	;

namespace_member_decl_optional
	: /* empty */
	{
	}
	| namespace_member_decl_list
	;

namespace_path
	: IDENT
	{
	}
	| namespace_path DOT IDENT
	{
	}
	;

import
	: IMPORT STRING_LITERAL
	{
	}
	;

parameterized_typename
	: IDENT type_parameter_group
	{
	}
	;

type_parameter_group
	: /* empty */
	{
	}
	| LT type_parameter_list GT
	{
	}
	;

type_parameter_list
	: type_parameter
	{
	}
	| type_parameter_list COMMA type_parameter
	{
	}
	;

type_parameter
	: IDENT type_parameter_rule_list
	{
	}
	| IN IDENT type_parameter_rule_list
	{
	}
	| OUT IDENT type_parameter_rule_list
	{
	}
	;

type_parameter_rule_list
	: /* empty */
	{
	}
	| LRB typename_list RRB
	{
	}
	;

class_decl
	: CLASS parameterized_typename LCB access_member_tree_opt RCB
	{
	}
	| CLASS parameterized_typename COLON typename_list LCB access_member_tree_opt RCB
	{
	}
	;

enum_decl
	: ENUM IDENT LCB ident_list RCB
	{
	}
	| ENUM IDENT LCB ident_list COMMA RCB
	{
	}
	;

interface_decl
	: INTERFACE parameterized_typename LCB access_member_tree_opt RCB
	{
	}
	| INTERFACE parameterized_typename COLON typename_list LCB access_member_tree_opt RCB
	{
	}
	;

access_member_tree_opt
	: /* empty */
	{
	}
	| access_member_tree
	;

access_member_tree
	: access_member_list
	| access_member_tree access_member_list
	{
	}
	;

access_member_list
	: access_level_T COLON member_define_list
	{
	}
	;

member_define_list
	: member_define
	{
	}
	| member_define_list member_define
	{
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
	}
	| CTOR NEW LRB RRB constructor_chain_optional scope_optional
	{
	}
	;

constructor_chain
	: COLON constructor_chain_type_T LRB argument_list RRB
	{
	}
	| COLON constructor_chain_type_T LRB RRB
	{
	}
	;

constructor_chain_type_T
	: SUPER
	{
	}
	| THIS
	{
	}
	;

constructor_chain_optional
	: /* empty */
	{
	}
	| constructor_chain
	;

function_define
	: DEF IDENT LRB parameter_list RRB ARROW typename_T scope_optional
	{
	}
	| DEF IDENT LRB RRB ARROW typename_T scope_optional
	{
	}
	;

method_define
	: modifier_type_T DEF IDENT type_parameter_group LRB parameter_list RRB ARROW typename_T scope_optional
	{
	}
	| modifier_type_T DEF IDENT type_parameter_group LRB RRB ARROW typename_T scope_optional
	{
	}
	;

field_define
	: modifier_type_T typename_T IDENT SEMI
	{
	}
	;

modifier_type_T
	: /* empty */
	{
	}
	| STATIC NATIVE
	{
	}
	| NATIVE STATIC
	{
	}
	| STATIC
	{
	}
	| NATIVE
	{
	}
	;

access_level_T
	: PUBLIC
	{
	}
	| PRIVATE
	{
	}
	| PROTECTED
	{
	}
	;

ident_list
	: IDENT
	{
	}
	| ident_list COMMA IDENT
	{
	}
	;

parameter_list
	: typename_T IDENT
	{
	}
	| parameter_list COMMA typename_T IDENT
	{
	}
	;

argument_list
	: expression
	{
	}
	| argument_list COMMA expression
	{
	}
	;

typename_group
	: /* empty */
	{
	}
	| '<' typename_list '>'
	{
	}
	;

typename_list
	: typename_T
	{
	}
	| typename_list COMMA typename_T
	{
	}
	;

typename_T
	: fqcn_part typename_group
	{
	}
	;

fqcn_part
	: IDENT
	{
	}
	| fqcn_part COLO_COLO IDENT
	{
	}
	;






expression
	: assign
	;
assign
	: or
	| primary assign_type_T assign
	{
	}
	;
assign_type_T
	: ASSIGN
	{
	}
	| ADD_ASSIGN
	{
	}
	| SUB_ASSIGN
	{
	}
	| MUL_ASSIGN
	{
	}
	| DIV_ASSIGN
	{
	}
	| MOD_ASSIGN
	{
	}
	;
or
	: and
	| or LOGIC_OR and
	{
	}
	;
and
	: equal
	| and LOGIC_AND equal
	{
	}
	;
equal
	: compare
	| equal EQUAL compare
	{
	}
	| equal NOTEQUAL compare
	{
	}
	;
compare
	: addsub
	| compare GT addsub
	{
	}
	| compare GE addsub
	{
	}
	| compare LT addsub
	{
	}
	| compare LE addsub
	{
	}
	;
addsub
	: muldiv
	| addsub ADD muldiv
	{
	}
	| addsub SUB muldiv
	{
	}
	;
muldiv
	: unary
	| muldiv MUL unary
	{
	}
	| muldiv DIV unary
	{
	}
	| muldiv MOD unary
	{
	}
	;
unary
	: prefix
	| NOT unary
	{
	}
	| '-' unary %prec UMINUS
	{
	}
	;
prefix
	: postfix
	| INC postfix
	{
	}
	| DEC postfix
	{
	}
	;
postfix
	: primary
	| primary INC
	{
	}
	| primary DEC
	{
	}
	| primary AS typename_T
	{
	}
	;
primary
	: primary_nobrace
	| '(' expression ')'
	{
	}
	;
primary_nobrace
	: primary_literal
	| primary_assoc
	| THIS
	{
	}
	| SUPER
	{
	}
	| NEW typename_T LRB argument_list RRB
	{
	}
	| NEW typename_T LRB RRB
	{
	}
	;

primary_literal
	: INT
	| DOUBLE
	| CHAR_LITERAL
	| STRING_LITERAL
	| TRUE_TOK
	{
	}
	| FALSE_TOK
	{
	}
	| NULL_TOK
	{
	}
	;
primary_assoc
	: primary_faccess
	| primary_mcall
	{
	}
	;

primary_faccess
	: primary DOT IDENT
	{
	}
	;

primary_mcall
	: primary_maccess typename_group LRB argument_list RRB
	{
	}
	| primary_maccess typename_group LRB RRB
	{
	}
	;
primary_maccess
	: primary_nobrace
	;


stmt_list
	: stmt
	{
	}
	| stmt_list stmt
	{
	}
	;
stmt
	: expression stmt_term
	{
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
	}
	;
variable_init_stmt
	: typename_T IDENT ASSIGN expression stmt_term
	{
	}
	;
inferenced_type_init_stmt
	: VAR IDENT ASSIGN expression stmt_term
	{
	}
	;
if_stmt
	: IF LRB expression RRB scope
	{
	}
	| IF LRB expression RRB scope ELSE scope
	{
	}
	| IF LRB expression RRB scope elif_list
	{
	}
	| IF LRB expression RRB scope elif_list ELSE scope
	{
	}
	;
elif_list
	: elif
	| elif_list elif
	{
	}
	;
elif
	: ELIF LRB expression RRB scope
	{
	}
	;
while_stmt
	: WHILE LRB expression RRB scope_optional
	{
	}
	;
break_stmt
	: BREAK stmt_term
	{
	}
	;
continue_stmt
	: CONTINUE stmt_term
	{
	}
	;
return_stmt
	: RETURN expression stmt_term
	{
	}
	;
throw_stmt
	: THROW expression stmt_term
	{
	}
	;
try_stmt
	: TRY scope catch_stmt_list
	{
	}
	;
catch_stmt_list
	: catch_stmt
	{
	}
	| catch_stmt_list catch_stmt
	{
	}
	;
catch_stmt
	: CATCH LRB typename_T IDENT RRB scope
	{
	}
	;





scope
	: LCB stmt_list RCB
	{
	}
	| LCB RCB
	{
	}
	;
scope_optional
	: SEMI
	{
	}
	| scope
	;
stmt_term
	: SEMI
	| /* empty */
	;
%%



