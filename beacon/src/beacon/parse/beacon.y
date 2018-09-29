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
#include "../util/string_pool.h"

#define YYDEBUG 1
#define YYERROR_VERBOSE 1
%}
%union {
	char char_value;
	string_view stringv_value;
	ast* ast_value;
	assign_operator_type assign_otype_value;
	constructor_chain_type chain_type_value;
	access_level access_level_value;
}


%locations
%token <ast_value>			CHAR_LITERAL
%token <ast_value>			STRING_LITERAL
%token <ast_value>			INT
%token <ast_value>			DOUBLE
%token <stringv_value>		IDENT
%type <chain_type_value>	constructor_chain_type_T
%type <access_level_value>	access_level_T
%token DOT COMMA COLON COLO_COLO LINE
		ADD SUB MUL DIV MOD NOT LSHIFT RSHIFT CHILDA
		EQUAL NOTEQUAL
		GT GE LT LE LGEN RGEN
		BIT_AND LOGIC_AND BIT_OR LOGIC_OR FINAL

		ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
		AND_ASSIGN OR_ASSIGN LSHIFT_ASSIGN RSHIFT_ASSIGN EXC_OR_ASSIGN

		INC DEC EXC_OR

		LCB RCB LRB RRB LSB RSB
		SEMI IMPORT VAR PROPERTY DEFSET DEFGET

		THIS_TOK SUPER_TOK TRUE_TOK FALSE_TOK NULL_TOK AS

		ABSTRACT INTERFACE CLASS ENUM PUBLIC PRIVATE PROTECTED STATIC NATIVE NEW
		DEF ARROW NAMESPACE RETURN YIELD
		IF ELIF ELSE WHILE BREAK CONTINUE TRY CATCH THROW
		ASSER_T DEFER INSTANCEOF OPERATOR
		BOUNDS_EXTENDS BOUNDS_SUPER SUBSCRIPT_SET SUBSCRIPT_GET
%type <ast_value> compilation_unit 
					init_decl
					body_decl
					namespace_decl
					namespace_body
					namespace_member_decl_list
					namespace_member_decl
					namespace_member_decl_optional
					namespace_path
					import_list
					import 
					parameterized_typename
					type_parameter_group
					type_parameter_list
					type_parameter
					abstract_class_decl
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
						operator_define
						method_define
						field_define
						prop_set
						prop_get
						prop_define
						modifier_type_T_list
						modifier_type_T
						ident_list
						parameter_list
						argument_list
						typename_group
						typename_list
						typename_T
						fqcn_part
					expression
						expression_nobrace
						primary
						lhs
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
						assert_stmt
						defer_stmt
						yield_return_stmt
						yield_break_stmt
						scope
						scope_optional
%left COMMA
%right ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN OR_ASSIGN LSHIFT_ASSIGN RSHIFT_ASSIGN EXC_OR_ASSIGN
%left QUOTE
%left LOGIC_OR
%left LOGIC_AND
%left BIT_OR
%left EXC_OR
%left BIT_AND
%left EQUAL NOTEQUAL
%left GT GE LT LE INSTANCEOF
%left LSHIFT RSHIFT
%left ADD SUB
%left MUL DIV MOD
%right CHILDA NOT NEGATIVE POSITIVE NEW REF
%left DOT FUNCCALL ARRAY_SUBSCRIPT
%right AS
%token FORM_TYPE
%start compilation_unit
%%


compilation_unit
	: init_decl body_decl
	| compilation_unit body_decl
	| error '\n'
	{
		yyclearin;
	}
	;

init_decl
	: /* empty */
	| import_list
	{
		CompileEntryAST($1);
	}
	;
body_decl
	: stmt
	{
		CompileEntryAST($1);
	}
	| namespace_decl
	{
		CompileEntryAST($1);
	}
	| function_define
	{
		CompileEntryAST($1);
	}
	;
namespace_decl
	: NAMESPACE namespace_path namespace_body
	{
		$$ = NewASTNamespaceDecl($2, $3);
	}
	;

namespace_body
	: LCB namespace_member_decl_optional RCB
	{
		$$ = $2;
	}
	;

namespace_member_decl
	: NAMESPACE namespace_path namespace_body
	{
		$$ = NewASTNamespaceNamespaceDecl($2, $3);
	}
	| abstract_class_decl
	| class_decl
	| interface_decl
	| enum_decl
	;

namespace_member_decl_list
	: namespace_member_decl
	{
		$$ = $1;
	}
	| namespace_member_decl_list namespace_member_decl
	{
		$$ = NewASTNamespaceMemberDeclList($1, $2);
	}
	;

namespace_member_decl_optional
	: /* empty */
	{
		$$ = NewASTBlank();
	}
	| namespace_member_decl_list
	;

namespace_path
	: IDENT
	{
		$$ = NewASTNamespacePath($1);
	}
	| namespace_path COLO_COLO IDENT
	{
		$$ = NewASTNamespacePathList($1, $3);
	}
	;

import_list
	: import
	| import_list import
	{
		$$ = NewASTImportDeclList($2, $1);
	}
	;

import
	: IMPORT STRING_LITERAL
	{
		$$ = NewASTImportDecl(NewASTImportPath($2));
	}
	;

parameterized_typename
	: IDENT type_parameter_group
	{
		$$ = NewASTParameterized_typename($1, $2);
	}
	;

type_parameter_group
	: /* empty */
	{
		$$ = NewASTBlank();
	}
	| LSB type_parameter_list RSB
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
		$$ = NewASTTypeParameterList($3, $1);
	}
	;

type_parameter
	: IDENT
	{
		$$ = NewASTTypeParameter($1, NewASTBlank());
	}
	;
abstract_class_decl
	: ABSTRACT CLASS parameterized_typename LCB access_member_tree_opt RCB
	{
		$$ = NewASTAbstractClassDecl($3, NewASTBlank(), $5);
	}
	| ABSTRACT CLASS parameterized_typename COLON typename_list LCB access_member_tree_opt RCB
	{
		$$ = NewASTAbstractClassDecl($3, $5, $7);
	}
	;
class_decl
	: CLASS parameterized_typename LCB access_member_tree_opt RCB
	{
		$$ = NewASTClassDecl($2, NewASTBlank(), $4);
	}
	| CLASS parameterized_typename COLON typename_list LCB access_member_tree_opt RCB
	{
		$$ = NewASTClassDecl($2, $4, $6);
	}
	;

enum_decl
	: ENUM IDENT LCB ident_list RCB
	{
		$$ = NewASTEnumDecl($2, $4);
	}
	| ENUM IDENT LCB ident_list COMMA RCB
	{
		$$ = NewASTEnumDecl($2, $4);
	}
	;

interface_decl
	: INTERFACE parameterized_typename LCB access_member_tree_opt RCB
	{
		$$ = NewASTInterface_decl($2, NewASTBlank(), $4);
	}
	| INTERFACE parameterized_typename COLON typename_list LCB access_member_tree_opt RCB
	{
		$$ = NewASTInterface_decl($2, $4, $6);
	}
	;

access_member_tree_opt
	: /* empty */
	{
		$$ = NewASTBlank();
	}
	| access_member_tree
	;

access_member_tree
	: access_member_list
	| access_member_tree access_member_list
	{
		$$ = NewASTAccess_member_tree($1, $2);
	}
	;

access_member_list
	: access_level_T COLON member_define_list
	{
		$$ = NewASTAccessMemberList($1, $3);
	}
	;

member_define_list
	: member_define
	{
		$$ = NewASTMemberDecl($1);
	}
	| member_define_list member_define
	{
		$$ = NewASTMemberDeclList($1, NewASTMemberDecl($2));
	}
	;

member_define
	: constructor_define
	| method_define
	| operator_define
	| field_define
	| prop_define
	;

constructor_define
	: DEF NEW LRB parameter_list RRB constructor_chain_optional scope_optional
	{
		$$ = NewASTConstructorDecl($4, $6, $7);
	}
	| DEF NEW LRB RRB constructor_chain_optional scope_optional
	{
		$$ = NewASTConstructorDecl(NewASTBlank(), $5, $6);
	}
	;

constructor_chain
	: COLON constructor_chain_type_T LRB argument_list RRB
	{
		$$ = NewASTConstructorChain($2, $4);
	}
	| COLON constructor_chain_type_T LRB RRB
	{
		$$ = NewASTConstructorChain($2, NewASTBlank());
	}
	;

constructor_chain_type_T
	: SUPER_TOK
	{
		$$ = chain_type_super_T;
	}
	| THIS_TOK
	{
		$$ = chain_type_this_T;
	}
	;

constructor_chain_optional
	: /* empty */
	{
		$$ = NewASTBlank();
	}
	| constructor_chain
	;

function_define
	: DEF IDENT type_parameter_group LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTFunctionDecl($2, $3, $5, $9, $8);
	}
	| DEF IDENT type_parameter_group LRB RRB ARROW typename_T scope_optional
	{
		$$ = NewASTFunctionDeclEmptyParams($2, $3, $8, $7);
	}
	;

method_define
	: DEF modifier_type_T_list IDENT type_parameter_group LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTMethodDecl($2, $3, $4, $6, $10, $9);
	}
	| DEF modifier_type_T_list IDENT type_parameter_group LRB RRB ARROW typename_T scope_optional
	{
		$$ = NewASTMethodDeclEmptyParams($2, $3, $4, $9, $8);
	}
	| DEF IDENT type_parameter_group LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTMethodDecl(NewASTModifier(modifier_none_T), $2, $3, $5, $9, $8);
	}
	| DEF IDENT type_parameter_group LRB RRB ARROW typename_T scope_optional
	{
		$$ = NewASTMethodDeclEmptyParams(NewASTModifier(modifier_none_T), $2, $3, $8, $7);
	}
	;

operator_define
	: OPERATOR ADD LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_add_T, $4, $8, $7);
	}
	| OPERATOR SUB LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_sub_T, $4, $8, $7);
	}
	| OPERATOR MUL LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_mul_T, $4, $8, $7);
	}
	| OPERATOR DIV LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_div_T, $4, $8, $7);
	}
	| OPERATOR MOD LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_mod_T, $4, $8, $7);
	}
	| OPERATOR GT LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_gt_T, $4, $8, $7);
	}
	| OPERATOR GE LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_ge_T, $4, $8, $7);
	}
	| OPERATOR LT LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_lt_T, $4, $8, $7);
	}
	| OPERATOR LE LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_le_T, $4, $8, $7);
	}
	//== !=
	| OPERATOR EQUAL LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_eq_T, $4, $8, $7);
	}
	| OPERATOR NOTEQUAL LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_not_eq_T, $4, $8, $7);
	}
	//| &
	| OPERATOR BIT_OR LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_bit_or_T, $4, $8, $7);
	}
	| OPERATOR BIT_AND LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_bit_and_T, $4, $8, $7);
	}
	//|| &&
	| OPERATOR LOGIC_OR LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_logic_or_T, $4, $8, $7);
	}
	| OPERATOR LOGIC_AND LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_logic_and_T, $4, $8, $7);
	}
	//<< >>
	| OPERATOR LSHIFT LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_lshift_T, $4, $8, $7);
	}
	| OPERATOR RSHIFT LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_rshift_T, $4, $8, $7);
	}
	//^
	| OPERATOR EXC_OR LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_excor_T, $4, $8, $7);
	}
	//!
	| OPERATOR NOT LRB RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_not_T, NewASTBlank(), $7, $6);
	}
	//~
	| OPERATOR CHILDA LRB RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_childa_T, NewASTBlank(), $7, $6);
	}
	| OPERATOR SUB LRB RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_negative_T, NewASTBlank(), $7, $6);
	}
	//[]
	| OPERATOR SUBSCRIPT_GET LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_sub_script_get_T, $4, $8, $7);
	}
	//[]=
	| OPERATOR SUBSCRIPT_SET LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = NewASTOperatorOverload(operator_sub_script_set_T, $4, $8, $7);
	}
	;

field_define
	: modifier_type_T_list typename_T IDENT SEMI
	{
		$$ = NewASTFieldDecl($1, $2, $3, NewASTBlank());
	}
	| typename_T IDENT SEMI
	{
		$$ = NewASTFieldDecl(NewASTModifier(modifier_none_T), $1, $2, NewASTBlank());
	}
	| modifier_type_T_list typename_T IDENT ASSIGN expression SEMI
	{
		$$ = NewASTFieldDecl($1, $2, $3, $5);
	}
	| typename_T IDENT ASSIGN expression SEMI
	{
		$$ = NewASTFieldDecl(NewASTModifier(modifier_none_T), $1, $2, $4);
	}
	;

prop_set
	: DEFSET SEMI
	{
		$$ = NewASTPropSet(NewASTBlank(), NewASTBlank());
	}
	| DEFSET scope
	{
		$$ = NewASTPropSet(NewASTBlank(), $2);
	}
	| access_level_T DEFSET SEMI
	{
		$$ = NewASTPropSet(NewASTAccess($1), NewASTBlank());
	}
	| access_level_T DEFSET scope
	{
		$$ = NewASTPropSet(NewASTAccess($1), NewASTBlank());
	}
	;

prop_get
	: DEFGET SEMI
	{
		$$ = NewASTPropGet(NewASTBlank(), NewASTBlank());
	}
	| DEFGET scope
	{
		$$ = NewASTPropGet(NewASTBlank(), $2);
	}
	| access_level_T DEFGET SEMI
	{
		$$ = NewASTPropGet(NewASTAccess($1), NewASTBlank());
	}
	| access_level_T DEFGET scope
	{
		$$ = NewASTPropGet(NewASTAccess($1), NewASTBlank());
	}
	;

prop_define
	: PROPERTY modifier_type_T_list typename_T IDENT LCB prop_set prop_get RCB
	{
		$$ = NewASTPropDecl($2, $3, $4, $6, $7);
	}
	| PROPERTY typename_T IDENT LCB prop_set prop_get RCB
	{
		$$ = NewASTPropDecl(NewASTModifier(modifier_none_T), $2, $3, $5, $6);
	}
	;

modifier_type_T_list
	: modifier_type_T
	{
		$$ = $1;
	}
	| modifier_type_T_list modifier_type_T
	{
		$$ = NewASTModifierList($2, $1);
	}
	;

modifier_type_T
	: STATIC
	{
		$$ = NewASTModifier(modifier_static_T);
	}
	| NATIVE
	{
		$$ = NewASTModifier(modifier_native_T);
	}
	| ABSTRACT
	{
		$$ = NewASTModifier(modifier_abstract_T);
	}
	| FINAL
	{
		$$ = NewASTModifier(modifier_final_T);
	}
	;

access_level_T
	: PUBLIC
	{
		$$ = access_public_T;
	}
	| PRIVATE
	{
		$$ = access_private_T;
	}
	| PROTECTED
	{
		$$ = access_protected_T;
	}
	;

ident_list
	: IDENT
	{
		$$ = NewASTIdentifier($1);
	}
	| ident_list COMMA IDENT
	{
		$$ = NewASTIdentifierList($3, $1);
	}
	;

parameter_list
	: typename_T IDENT
	{
		$$ = NewASTParameter($1, $2);
	}
	| parameter_list COMMA typename_T IDENT
	{
		$$ = NewASTParameterList($3, $4, $1);
	}
	;

argument_list
	: expression
	{
		$$ = NewASTArgument($1);
	}
	| argument_list COMMA expression
	{
		$$ = NewASTArgumentList(NewASTArgument($3), $1);
	}
	;

typename_group
	: /* empty */
	{
		$$ = NewASTBlank();
	}
	| LSB typename_list RSB
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
		$$ = NewASTTypenameList($3, $1);
	}
	;

typename_T
	: fqcn_part typename_group
	{
		$$ = NewASTTypename($1, $2);
	}
	;

fqcn_part
	: IDENT
	{
		$$ = NewASTFQCN_part($1);
	}
	| fqcn_part COLO_COLO IDENT
	{
		$$ = NewASTFQCNPartList(NewASTFQCN_part($3), $1);
	}
	;



expression
	: LRB expression RRB
	{
		$$ = $2;
	}
	| primary
	|  expression_nobrace
	;
expression_nobrace
	: ADD expression %prec POSITIVE
	{
		$$ = NewASTUnary(ast_pos_T, $2);
	}
	| SUB expression %prec NEGATIVE
	{
		$$ = NewASTUnary(ast_neg_T, $2);
	}
	| expression ADD expression
	{
		$$ = NewASTBinary(ast_add_T, $1, $3);
	}
	| expression SUB expression
	{
		$$ = NewASTBinary(ast_sub_T, $1, $3);
	}
	| expression MUL expression
	{
		$$ = NewASTBinary(ast_mul_T, $1, $3);
	}
	| expression DIV expression
	{
		$$ = NewASTBinary(ast_div_T, $1, $3);
	}
	| expression MOD expression
	{
		$$ = NewASTBinary(ast_mod_T, $1, $3);
	}
	| expression BIT_OR expression
	{
		$$ = NewASTBinary(ast_bit_or_T, $1, $3);
	}
	| expression EQUAL expression
	{
		$$ = NewASTBinary(ast_equal_T, $1, $3);
	}
	| expression NOTEQUAL expression
	{
		$$ = NewASTBinary(ast_not_Tequal_T, $1, $3);
	}
	| expression BIT_AND expression
	{
		$$ = NewASTBinary(ast_bit_and_T, $1, $3);
	}
	| expression EXC_OR expression
	{
		$$ = NewASTBinary(ast_exc_or_T, $1, $3);
	}
	| expression LOGIC_OR expression
	{
		$$ = NewASTBinary(ast_logic_or_T, $1, $3);
	}
	| expression LOGIC_AND expression
	{
		$$ = NewASTBinary(ast_logic_and_T, $1, $3);
	}
	| lhs ASSIGN expression
	{
		$$ = NewASTBinary(ast_as_Tsign_T, $1, $3);
	}
	| lhs ADD_ASSIGN expression
	{
		$$ = NewASTBinary(ast_add_assign_T, $1, $3);
	}
	| lhs SUB_ASSIGN expression
	{
		$$ = NewASTBinary(ast_sub_assign_T, $1, $3);
	}
	| lhs MUL_ASSIGN expression
	{
		$$ = NewASTBinary(ast_mul_assign_T, $1, $3);
	}
	| lhs DIV_ASSIGN expression
	{
		$$ = NewASTBinary(ast_div_assign_T, $1, $3);
	}
	| lhs MOD_ASSIGN expression
	{
		$$ = NewASTBinary(ast_mod_assign_T, $1, $3);
	}
	| lhs AND_ASSIGN expression
	{
		$$ = NewASTBinary(ast_and_assign_T, $1, $3);
	}
	| lhs OR_ASSIGN expression
	{
		$$ = NewASTBinary(ast_or_assign_T, $1, $3);
	}
	| lhs EXC_OR_ASSIGN expression
	{
		$$ = NewASTBinary(ast_exc_or_assign_T, $1, $3);
	}
	| lhs LSHIFT_ASSIGN expression
	{
		$$ = NewASTBinary(ast_lshift_assign_T, $1, $3);
	}
	| lhs RSHIFT_ASSIGN expression
	{
		$$ = NewASTBinary(ast_rshift_assign_T, $1, $3);
	}
	| expression GT expression
	{
		$$ = NewASTBinary(ast_gt_T, $1, $3);
	}
	| expression GE expression
	{
		$$ = NewASTBinary(ast_ge_T, $1, $3);
	}
	| expression LT expression
	{
		$$ = NewASTBinary(ast_lt_T, $1, $3);
	}
	| expression LE expression
	{
		$$ = NewASTBinary(ast_le_T, $1, $3);
	}
	| expression LSHIFT expression
	{
		$$ = NewASTBinary(ast_lshift_T, $1, $3);
	}
	| expression RSHIFT expression
	{
		$$ = NewASTBinary(ast_rshift_T, $1, $3);
	}

	| expression DOT ADD LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_add_T, $5);
	}
	| expression DOT SUB LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_sub_T, $5);
	}
	| expression DOT MUL LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_mul_T, $5);
	}
	| expression DOT DIV LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_div_T, $5);
	}
	| expression DOT MOD LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_mod_T, $5);
	}
	| expression DOT GT LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_gt_T, $5);
	}
	| expression DOT GE LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_ge_T, $5);
	}
	| expression DOT LT LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_lt_T, $5);
	}
	| expression DOT LE LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_le_T, $5);
	}
	| expression DOT EQUAL LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_eq_T, $5);
	}
	| expression DOT NOTEQUAL LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_not_eq_T, $5);
	}
	| expression DOT BIT_OR LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_bit_or_T, $5);
	}
	| expression DOT BIT_AND LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_bit_and_T, $5);
	}
	| expression DOT LOGIC_OR LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_logic_or_T, $5);
	}
	| expression DOT LOGIC_AND LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_logic_and_T, $5);
	}
	| expression DOT LSHIFT LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_lshift_T, $5);
	}
	| expression DOT RSHIFT LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_rshift_T, $5);
	}
	| expression DOT EXC_OR LRB expression RRB
	{
		$$ = NewASTExplicitBiOperator($1, operator_excor_T, $5);
	}
	| expression DOT NOT LRB RRB
	{
		$$ = NewASTExplicitUOperator($1, operator_not_T);
	}
	| expression DOT CHILDA LRB RRB
	{
		$$ = NewASTExplicitUOperator($1, operator_childa_T);
	}
	| expression DOT SUB LRB RRB
	{
		$$ = NewASTExplicitUOperator($1, operator_negative_T);
	}
	| expression INSTANCEOF typename_T
	{
		$$ = NewASTInstanceTof($1, $3);
	}
	| expression AS typename_T
	{
		$$ = NewASTAs($1, $3);
	}
	| CHILDA expression
	{
		$$ = NewASTUnary(ast_childa_T, $2);
	}
	| NOT expression
	{
		$$ = NewASTUnary(ast_not_T, $2);
	}
	| NEW fqcn_part typename_group LRB argument_list RRB
	{
		$$ = NewASTNewInstance($2, $3, $5);
	}
	| NEW fqcn_part typename_group LRB RRB
	{
		$$ = NewASTNewInstance($2, $3, NewASTBlank());
	}
	| THIS_TOK
	{
		$$ = NewASTThis();
	}
	| SUPER_TOK
	{
		$$ = NewASTSuper();
	}
	| lhs
	;
lhs
	: fqcn_part typename_group
	{
		$$ = NewASTVariable($1, $2);
	}
	| expression DOT IDENT typename_group
	{
		$$ = NewASTFieldAccess($1, $3, $4);
	}
	| expression_nobrace LRB argument_list RRB %prec FUNCCALL
	{
		$$ = NewASTOpCall($1, $3);
	}
	| expression_nobrace LRB RRB %prec FUNCCALL
	{
		$$ = NewASTOpCall($1, NewASTBlank());
	}
	;
primary
	: INT
	| DOUBLE
	| CHAR_LITERAL
	| STRING_LITERAL
	| TRUE_TOK
	{
		$$ = NewASTTrue();
	}
	| FALSE_TOK
	{
		$$ = NewASTFalse();
	}
	| NULL_TOK
	{
		$$ = NewASTNull();
	}
	;



stmt_list
	: stmt
	{
		$$ = ast_new_stmt($1);
	}
	| stmt_list stmt
	{
		$$ = NewASTStmtList($1, $2);
	}
	;
stmt
	: expression stmt_term
	{
		$$ = NewASTProc($1);
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
	| assert_stmt
	| defer_stmt
	| yield_return_stmt
	| yield_break_stmt
	;
variable_decl_stmt
	: typename_T IDENT SEMI
	{
		$$ = NewASTVariable_decl($1, $2);
	}
	;
variable_init_stmt
	: typename_T IDENT ASSIGN expression stmt_term
	{
		$$ = NewASTVariable_init($1, $2, $4);
	}
	;
inferenced_type_init_stmt
	: VAR IDENT ASSIGN expression stmt_term
	{
		$$ = NewASTInferencedTypeInit($2, $4);
	}
	;
if_stmt
	: IF expression scope
	{
		$$ = NewASTIf($2, $3);
	}
	| IF expression scope ELSE scope
	{
		$$ = NewASTIf_else($2, $3, $5);
	}
	| IF expression scope elif_list
	{
		$$ = NewASTIfElifList($2, $3, $4);
	}
	| IF expression scope elif_list ELSE scope
	{
		$$ = NewASTIfElifList_else($2, $3, $4, $6);
	}
	;
elif_list
	: elif
	| elif_list elif
	{
		$$ = NewASTElifList($1, $2);
	}
	;
elif
	: ELIF expression scope
	{
		$$ = NewASTElif($2, $3);
	}
	;
while_stmt
	: WHILE expression scope_optional
	{
		$$ = NewASTWhile($2, $3);
	}
	;
break_stmt
	: BREAK stmt_term
	{
		$$ = NewASTBreak();
	}
	;
continue_stmt
	: CONTINUE stmt_term
	{
		$$ = NewASTContinue();
	}
	;
return_stmt
	: RETURN expression stmt_term
	{
		$$ = NewASTReturn($2);
	}
	| RETURN stmt_term
	{
		$$ = NewASTReturnEmpty();
	}
	;
throw_stmt
	: THROW expression stmt_term
	{
		$$ = NewASTThrow($2);
	}
	;
try_stmt
	: TRY scope catch_stmt_list
	{
		$$ = NewASTTry($2, $3);
	}
	;
catch_stmt_list
	: catch_stmt
	{
		$$ = $1;
	}
	| catch_stmt_list catch_stmt
	{
		$$ = NewASTCatchList($2, $1);
	}
	;
catch_stmt
	: CATCH LRB typename_T IDENT RRB scope
	{
		$$ = NewASTCatch($3, $4, $6);
	}
	;
assert_stmt
	: ASSER_T expression COLON expression stmt_term
	{
		$$ = NewASTAssert($2, $4);
	}
	| ASSER_T expression stmt_term
	{
		$$ = NewASTAssert($2, NewASTBlank());
	}
	;
defer_stmt
	: DEFER stmt
	{
		$$ = NewASTDefer($2);
	}
	;
yield_return_stmt
	: YIELD RETURN expression stmt_term
	{
		$$ = NewASTYieldReturn($3);
	}
	;
yield_break_stmt
	: YIELD BREAK stmt_term
	{
		$$ = NewASTYieldBreak();
	}
	;
scope
	: LCB stmt_list RCB
	{
		$$ = NewASTScope($2);
	}
	| LCB RCB
	{
		$$ = NewASTScopeEmpty();
	}
	;
scope_optional
	: SEMI
	{
		$$ = NewASTBlank();
	}
	| scope
	;
stmt_term
	: SEMI
	;
%%



