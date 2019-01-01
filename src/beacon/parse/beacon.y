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
	bc_StringView stringv_value;
	bc_AST* ast_value;
	bc_AssignOperatorType assign_otype_value;
	bc_ConstructorChainType chain_type_value;
	bc_AccessLevel access_level_value;
}


%locations
%token <ast_value>			CHAR_LITERAL
%token <ast_value>			STRING_LITERAL
%token <ast_value>			SHORT
%token <ast_value>			INT
%token <ast_value>			LONG
%token <ast_value>			FLOAT
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
					GetParameterListType
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
		bc_CompileEntryAST($1);
	}
	;
body_decl
	: stmt
	{
		bc_CompileEntryAST($1);
	}
	| namespace_decl
	{
		bc_CompileEntryAST($1);
	}
	| function_define
	{
		bc_CompileEntryAST($1);
	}
	;
namespace_decl
	: NAMESPACE namespace_path namespace_body
	{
		$$ = bc_NewASTNamespaceDecl($2, $3);
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
		$$ = bc_NewASTNamespaceNamespaceDecl($2, $3);
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
		$$ = bc_NewASTNamespaceMemberDeclList($1, $2);
	}
	;

namespace_member_decl_optional
	: /* empty */
	{
		$$ = bc_NewASTBlank();
	}
	| namespace_member_decl_list
	;

namespace_path
	: IDENT
	{
		$$ = bc_NewASTNamespacePath($1);
	}
	| namespace_path COLO_COLO IDENT
	{
		$$ = bc_NewASTNamespacePathList($1, $3);
	}
	;

import_list
	: import
	| import_list import
	{
		$$ = bc_NewASTImportDeclList($2, $1);
	}
	;

import
	: IMPORT STRING_LITERAL
	{
		$$ = bc_NewASTImportDecl(bc_NewASTImportPath($2));
	}
	;

parameterized_typename
	: IDENT type_parameter_group
	{
		$$ = bc_NewASTParameterizedTypename($1, $2);
	}
	;

type_parameter_group
	: /* empty */
	{
		$$ = bc_NewASTBlank();
	}
	| LSB GetParameterListType RSB
	{
		$$ = $2;
	}
	;

GetParameterListType
	: type_parameter
	{
		$$ = $1;
	}
	| GetParameterListType COMMA type_parameter
	{
		$$ = bc_NewASTTypeParameterList($3, $1);
	}
	;

type_parameter
	: IDENT
	{
		$$ = bc_NewASTTypeParameter($1, bc_NewASTBlank());
	}
	;
abstract_class_decl
	: ABSTRACT CLASS parameterized_typename LCB access_member_tree_opt RCB
	{
		$$ = bc_NewASTAbstractClassDecl($3, bc_NewASTBlank(), $5);
	}
	| ABSTRACT CLASS parameterized_typename COLON typename_list LCB access_member_tree_opt RCB
	{
		$$ = bc_NewASTAbstractClassDecl($3, $5, $7);
	}
	;
class_decl
	: CLASS parameterized_typename LCB access_member_tree_opt RCB
	{
		$$ = bc_NewASTClassDecl($2, bc_NewASTBlank(), $4);
	}
	| CLASS parameterized_typename COLON typename_list LCB access_member_tree_opt RCB
	{
		$$ = bc_NewASTClassDecl($2, $4, $6);
	}
	;

enum_decl
	: ENUM IDENT LCB ident_list RCB
	{
		$$ = bc_NewASTEnumDecl($2, $4);
	}
	| ENUM IDENT LCB ident_list COMMA RCB
	{
		$$ = bc_NewASTEnumDecl($2, $4);
	}
	;

interface_decl
	: INTERFACE parameterized_typename LCB access_member_tree_opt RCB
	{
		$$ = bc_NewASTInterfaceDecl($2, bc_NewASTBlank(), $4);
	}
	| INTERFACE parameterized_typename COLON typename_list LCB access_member_tree_opt RCB
	{
		$$ = bc_NewASTInterfaceDecl($2, $4, $6);
	}
	;

access_member_tree_opt
	: /* empty */
	{
		$$ = bc_NewASTBlank();
	}
	| access_member_tree
	;

access_member_tree
	: access_member_list
	| access_member_tree access_member_list
	{
		$$ = bc_NewASTAccessMemberTree($1, $2);
	}
	;

access_member_list
	: access_level_T COLON member_define_list
	{
		$$ = bc_NewASTAccessMemberList($1, $3);
	}
	;

member_define_list
	: member_define
	{
		$$ = bc_NewASTMemberDecl($1);
	}
	| member_define_list member_define
	{
		$$ = bc_NewASTMemberDeclList($1, bc_NewASTMemberDecl($2));
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
		$$ = bc_NewASTConstructorDecl($4, $6, $7);
	}
	| DEF NEW LRB RRB constructor_chain_optional scope_optional
	{
		$$ = bc_NewASTConstructorDecl(bc_NewASTBlank(), $5, $6);
	}
	;

constructor_chain
	: COLON constructor_chain_type_T LRB argument_list RRB
	{
		$$ = bc_NewASTConstructorChain($2, $4);
	}
	| COLON constructor_chain_type_T LRB RRB
	{
		$$ = bc_NewASTConstructorChain($2, bc_NewASTBlank());
	}
	;

constructor_chain_type_T
	: SUPER_TOK
	{
		$$ = CHAIN_TYPE_SUPER_T;
	}
	| THIS_TOK
	{
		$$ = CHAIN_TYPE_THIS_T;
	}
	;

constructor_chain_optional
	: /* empty */
	{
		$$ = bc_NewASTBlank();
	}
	| constructor_chain
	;

function_define
	: DEF IDENT type_parameter_group LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTFunctionDecl($2, $3, $5, $9, $8);
	}
	| DEF IDENT type_parameter_group LRB RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTFunctionDeclEmptyParams($2, $3, $8, $7);
	}
	;

method_define
	: DEF modifier_type_T_list IDENT type_parameter_group LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTMethodDecl($2, $3, $4, $6, $10, $9);
	}
	| DEF modifier_type_T_list IDENT type_parameter_group LRB RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTMethodDeclEmptyParams($2, $3, $4, $9, $8);
	}
	| DEF IDENT type_parameter_group LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTMethodDecl(bc_NewASTModifier(MODIFIER_NONE_T), $2, $3, $5, $9, $8);
	}
	| DEF IDENT type_parameter_group LRB RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTMethodDeclEmptyParams(bc_NewASTModifier(MODIFIER_NONE_T), $2, $3, $8, $7);
	}
	;

operator_define
	: OPERATOR ADD LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_ADD_T, $4, $8, $7);
	}
	| OPERATOR SUB LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_SUB_T, $4, $8, $7);
	}
	| OPERATOR MUL LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_MUL_T, $4, $8, $7);
	}
	| OPERATOR DIV LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_DIV_T, $4, $8, $7);
	}
	| OPERATOR MOD LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_MOD_T, $4, $8, $7);
	}
	| OPERATOR GT LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_GT_T, $4, $8, $7);
	}
	| OPERATOR GE LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_GE_T, $4, $8, $7);
	}
	| OPERATOR LT LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_LT_T, $4, $8, $7);
	}
	| OPERATOR LE LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_LE_T, $4, $8, $7);
	}
	//== !=
	| OPERATOR EQUAL LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_EQ_T, $4, $8, $7);
	}
	| OPERATOR NOTEQUAL LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_NOT_EQ_T, $4, $8, $7);
	}
	//| &
	| OPERATOR BIT_OR LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_BIT_OR_T, $4, $8, $7);
	}
	| OPERATOR BIT_AND LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_BIT_AND_T, $4, $8, $7);
	}
	//|| &&
	| OPERATOR LOGIC_OR LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_LOGIC_OR_T, $4, $8, $7);
	}
	| OPERATOR LOGIC_AND LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_LOGIC_AND_T, $4, $8, $7);
	}
	//<< >>
	| OPERATOR LSHIFT LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_LSHIFT_T, $4, $8, $7);
	}
	| OPERATOR RSHIFT LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_RSHIFT_T, $4, $8, $7);
	}
	//^
	| OPERATOR EXC_OR LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_EXCOR_T, $4, $8, $7);
	}
	//!
	| OPERATOR NOT LRB RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_NOT_T, bc_NewASTBlank(), $7, $6);
	}
	//~
	| OPERATOR CHILDA LRB RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_CHILDA_T, bc_NewASTBlank(), $7, $6);
	}
	| OPERATOR SUB LRB RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_NEGATIVE_T, bc_NewASTBlank(), $7, $6);
	}
	//[]
	| OPERATOR SUBSCRIPT_GET LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_SUB_SCRIPT_GET_T, $4, $8, $7);
	}
	//[]=
	| OPERATOR SUBSCRIPT_SET LRB parameter_list RRB ARROW typename_T scope_optional
	{
		$$ = bc_NewASTOperatorOverload(OPERATOR_SUB_SCRIPT_SET_T, $4, $8, $7);
	}
	;

field_define
	: modifier_type_T_list typename_T IDENT SEMI
	{
		$$ = bc_NewASTFieldDecl($1, $2, $3, bc_NewASTBlank());
	}
	| typename_T IDENT SEMI
	{
		$$ = bc_NewASTFieldDecl(bc_NewASTModifier(MODIFIER_NONE_T), $1, $2, bc_NewASTBlank());
	}
	| modifier_type_T_list typename_T IDENT ASSIGN expression SEMI
	{
		$$ = bc_NewASTFieldDecl($1, $2, $3, $5);
	}
	| typename_T IDENT ASSIGN expression SEMI
	{
		$$ = bc_NewASTFieldDecl(bc_NewASTModifier(MODIFIER_NONE_T), $1, $2, $4);
	}
	;

prop_set
	: DEFSET SEMI
	{
		$$ = bc_NewASTPropSet(bc_NewASTBlank(), bc_NewASTBlank());
	}
	| DEFSET scope
	{
		$$ = bc_NewASTPropSet(bc_NewASTBlank(), $2);
	}
	| access_level_T DEFSET SEMI
	{
		$$ = bc_NewASTPropSet(bc_NewASTAccess($1), bc_NewASTBlank());
	}
	| access_level_T DEFSET scope
	{
		$$ = bc_NewASTPropSet(bc_NewASTAccess($1), bc_NewASTBlank());
	}
	;

prop_get
	: DEFGET SEMI
	{
		$$ = bc_NewASTPropGet(bc_NewASTBlank(), bc_NewASTBlank());
	}
	| DEFGET scope
	{
		$$ = bc_NewASTPropGet(bc_NewASTBlank(), $2);
	}
	| access_level_T DEFGET SEMI
	{
		$$ = bc_NewASTPropGet(bc_NewASTAccess($1), bc_NewASTBlank());
	}
	| access_level_T DEFGET scope
	{
		$$ = bc_NewASTPropGet(bc_NewASTAccess($1), bc_NewASTBlank());
	}
	;

prop_define
	: PROPERTY modifier_type_T_list typename_T IDENT LCB prop_set prop_get RCB
	{
		$$ = bc_NewASTPropDecl($2, $3, $4, $6, $7);
	}
	| PROPERTY typename_T IDENT LCB prop_set prop_get RCB
	{
		$$ = bc_NewASTPropDecl(bc_NewASTModifier(MODIFIER_NONE_T), $2, $3, $5, $6);
	}
	;

modifier_type_T_list
	: modifier_type_T
	{
		$$ = $1;
	}
	| modifier_type_T_list modifier_type_T
	{
		$$ = bc_NewASTModifierList($2, $1);
	}
	;

modifier_type_T
	: STATIC
	{
		$$ = bc_NewASTModifier(MODIFIER_STATIC_T);
	}
	| NATIVE
	{
		$$ = bc_NewASTModifier(MODIFIER_NATIVE_T);
	}
	| ABSTRACT
	{
		$$ = bc_NewASTModifier(MODIFIER_ABSTRACT_T);
	}
	| FINAL
	{
		$$ = bc_NewASTModifier(MODIFIER_FINAL_T);
	}
	;

access_level_T
	: PUBLIC
	{
		$$ = ACCESS_PUBLIC_T;
	}
	| PRIVATE
	{
		$$ = ACCESS_PRIVATE_T;
	}
	| PROTECTED
	{
		$$ = ACCESS_PROTECTED_T;
	}
	;

ident_list
	: IDENT
	{
		$$ = bc_NewASTIdentifier($1);
	}
	| ident_list COMMA IDENT
	{
		$$ = bc_NewASTIdentifierList($3, $1);
	}
	;

parameter_list
	: typename_T IDENT
	{
		$$ = bc_NewASTParameter($1, $2);
	}
	| parameter_list COMMA typename_T IDENT
	{
		$$ = bc_NewASTParameterList($3, $4, $1);
	}
	;

argument_list
	: expression
	{
		$$ = bc_NewASTArgument($1);
	}
	| argument_list COMMA expression
	{
		$$ = bc_NewASTArgumentList(bc_NewASTArgument($3), $1);
	}
	;

typename_group
	: /* empty */
	{
		$$ = bc_NewASTBlank();
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
		$$ = bc_NewASTTypenameList($3, $1);
	}
	;

typename_T
	: fqcn_part typename_group
	{
		$$ = bc_NewASTTypename($1, $2);
	}
	;

fqcn_part
	: IDENT
	{
		$$ = bc_NewASTFQCNPart($1);
	}
	| fqcn_part COLO_COLO IDENT
	{
		$$ = bc_NewASTFQCNPartList(bc_NewASTFQCNPart($3), $1);
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
		$$ = bc_NewASTUnary(AST_POS_T, $2);
	}
	| SUB expression %prec NEGATIVE
	{
		$$ = bc_NewASTUnary(AST_NEG_T, $2);
	}
	| expression ADD expression
	{
		$$ = bc_NewASTBinary(AST_ADD_T, $1, $3);
	}
	| expression SUB expression
	{
		$$ = bc_NewASTBinary(AST_SUB_T, $1, $3);
	}
	| expression MUL expression
	{
		$$ = bc_NewASTBinary(AST_MUL_T, $1, $3);
	}
	| expression DIV expression
	{
		$$ = bc_NewASTBinary(AST_DIV_T, $1, $3);
	}
	| expression MOD expression
	{
		$$ = bc_NewASTBinary(AST_MOD_T, $1, $3);
	}
	| expression BIT_OR expression
	{
		$$ = bc_NewASTBinary(AST_BIT_OR_T, $1, $3);
	}
	| expression EQUAL expression
	{
		$$ = bc_NewASTBinary(AST_EQUAL_T, $1, $3);
	}
	| expression NOTEQUAL expression
	{
		$$ = bc_NewASTBinary(AST_NOT_TEQUAL_T, $1, $3);
	}
	| expression BIT_AND expression
	{
		$$ = bc_NewASTBinary(AST_BIT_AND_T, $1, $3);
	}
	| expression EXC_OR expression
	{
		$$ = bc_NewASTBinary(AST_EXC_OR_T, $1, $3);
	}
	| expression LOGIC_OR expression
	{
		$$ = bc_NewASTBinary(AST_LOGIC_OR_T, $1, $3);
	}
	| expression LOGIC_AND expression
	{
		$$ = bc_NewASTBinary(AST_LOGIC_AND_T, $1, $3);
	}
	| lhs ASSIGN expression
	{
		$$ = bc_NewASTBinary(AST_AS_TSIGN_T, $1, $3);
	}
	| lhs ADD_ASSIGN expression
	{
		$$ = bc_NewASTBinary(AST_ADD_ASSIGN_T, $1, $3);
	}
	| lhs SUB_ASSIGN expression
	{
		$$ = bc_NewASTBinary(AST_SUB_ASSIGN_T, $1, $3);
	}
	| lhs MUL_ASSIGN expression
	{
		$$ = bc_NewASTBinary(AST_MUL_ASSIGN_T, $1, $3);
	}
	| lhs DIV_ASSIGN expression
	{
		$$ = bc_NewASTBinary(AST_DIV_ASSIGN_T, $1, $3);
	}
	| lhs MOD_ASSIGN expression
	{
		$$ = bc_NewASTBinary(AST_MOD_ASSIGN_T, $1, $3);
	}
	| lhs AND_ASSIGN expression
	{
		$$ = bc_NewASTBinary(AST_AND_ASSIGN_T, $1, $3);
	}
	| lhs OR_ASSIGN expression
	{
		$$ = bc_NewASTBinary(AST_OR_ASSIGN_T, $1, $3);
	}
	| lhs EXC_OR_ASSIGN expression
	{
		$$ = bc_NewASTBinary(AST_EXC_OR_ASSIGN_T, $1, $3);
	}
	| lhs LSHIFT_ASSIGN expression
	{
		$$ = bc_NewASTBinary(AST_LSHIFT_ASSIGN_T, $1, $3);
	}
	| lhs RSHIFT_ASSIGN expression
	{
		$$ = bc_NewASTBinary(AST_RSHIFT_ASSIGN_T, $1, $3);
	}
	| expression GT expression
	{
		$$ = bc_NewASTBinary(AST_GT_T, $1, $3);
	}
	| expression GE expression
	{
		$$ = bc_NewASTBinary(AST_GE_T, $1, $3);
	}
	| expression LT expression
	{
		$$ = bc_NewASTBinary(AST_LT_T, $1, $3);
	}
	| expression LE expression
	{
		$$ = bc_NewASTBinary(AST_LE_T, $1, $3);
	}
	| expression LSHIFT expression
	{
		$$ = bc_NewASTBinary(AST_LSHIFT_T, $1, $3);
	}
	| expression RSHIFT expression
	{
		$$ = bc_NewASTBinary(AST_RSHIFT_T, $1, $3);
	}

	| expression DOT ADD LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_ADD_T, $5);
	}
	| expression DOT SUB LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_SUB_T, $5);
	}
	| expression DOT MUL LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_MUL_T, $5);
	}
	| expression DOT DIV LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_DIV_T, $5);
	}
	| expression DOT MOD LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_MOD_T, $5);
	}
	| expression DOT GT LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_GT_T, $5);
	}
	| expression DOT GE LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_GE_T, $5);
	}
	| expression DOT LT LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_LT_T, $5);
	}
	| expression DOT LE LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_LE_T, $5);
	}
	| expression DOT EQUAL LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_EQ_T, $5);
	}
	| expression DOT NOTEQUAL LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_NOT_EQ_T, $5);
	}
	| expression DOT BIT_OR LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_BIT_OR_T, $5);
	}
	| expression DOT BIT_AND LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_BIT_AND_T, $5);
	}
	| expression DOT LOGIC_OR LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_LOGIC_OR_T, $5);
	}
	| expression DOT LOGIC_AND LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_LOGIC_AND_T, $5);
	}
	| expression DOT LSHIFT LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_LSHIFT_T, $5);
	}
	| expression DOT RSHIFT LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_RSHIFT_T, $5);
	}
	| expression DOT EXC_OR LRB expression RRB
	{
		$$ = bc_NewASTExplicitBiOperator($1, OPERATOR_EXCOR_T, $5);
	}
	| expression DOT NOT LRB RRB
	{
		$$ = bc_NewASTExplicitUOperator($1, OPERATOR_NOT_T);
	}
	| expression DOT CHILDA LRB RRB
	{
		$$ = bc_NewASTExplicitUOperator($1, OPERATOR_CHILDA_T);
	}
	| expression DOT SUB LRB RRB
	{
		$$ = bc_NewASTExplicitUOperator($1, OPERATOR_NEGATIVE_T);
	}
	| expression INSTANCEOF typename_T
	{
		$$ = bc_NewASTInstanceTof($1, $3);
	}
	| expression AS typename_T
	{
		$$ = bc_NewASTAs($1, $3);
	}
	| CHILDA expression
	{
		$$ = bc_NewASTUnary(AST_CHILDA_T, $2);
	}
	| NOT expression
	{
		$$ = bc_NewASTUnary(AST_NOT_T, $2);
	}
	| NEW fqcn_part typename_group LRB argument_list RRB
	{
		$$ = bc_NewASTNewInstance($2, $3, $5);
	}
	| NEW fqcn_part typename_group LRB RRB
	{
		$$ = bc_NewASTNewInstance($2, $3, bc_NewASTBlank());
	}
	| THIS_TOK
	{
		$$ = bc_NewASTThis();
	}
	| SUPER_TOK
	{
		$$ = bc_NewASTSuper();
	}
	| lhs
	;
lhs
	: fqcn_part typename_group
	{
		$$ = bc_NewASTVariable($1, $2);
	}
	| expression DOT IDENT typename_group
	{
		$$ = bc_NewASTFieldAccess($1, $3, $4);
	}
	| expression_nobrace LRB argument_list RRB %prec FUNCCALL
	{
		$$ = bc_NewASTOpCall($1, $3);
	}
	| expression_nobrace LRB RRB %prec FUNCCALL
	{
		$$ = bc_NewASTOpCall($1, bc_NewASTBlank());
	}
	;
primary
	: SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| CHAR_LITERAL
	| STRING_LITERAL
	| TRUE_TOK
	{
		$$ = bc_NewASTTrue();
	}
	| FALSE_TOK
	{
		$$ = bc_NewASTFalse();
	}
	| NULL_TOK
	{
		$$ = bc_NewASTNull();
	}
	;



stmt_list
	: stmt
	{
		$$ = bc_NewASTStmt($1);
	}
	| stmt_list stmt
	{
		$$ = bc_NewASTStmtList($1, $2);
	}
	;
stmt
	: expression stmt_term
	{
		$$ = bc_NewASTProc($1);
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
		$$ = bc_NewASTVariableDecl($1, $2);
	}
	;
variable_init_stmt
	: typename_T IDENT ASSIGN expression stmt_term
	{
		$$ = bc_NewASTVariableInit($1, $2, $4);
	}
	;
inferenced_type_init_stmt
	: VAR IDENT ASSIGN expression stmt_term
	{
		$$ = bc_NewASTInferencedTypeInit($2, $4);
	}
	;
if_stmt
	: IF expression scope
	{
		$$ = bc_NewASTIf($2, $3);
	}
	| IF expression scope ELSE scope
	{
		$$ = bc_NewASTIfElse($2, $3, $5);
	}
	| IF expression scope elif_list
	{
		$$ = bc_NewASTIfElifList($2, $3, $4);
	}
	| IF expression scope elif_list ELSE scope
	{
		$$ = bc_NewASTIfElifListElse($2, $3, $4, $6);
	}
	;
elif_list
	: elif
	| elif_list elif
	{
		$$ = bc_NewASTElifList($1, $2);
	}
	;
elif
	: ELIF expression scope
	{
		$$ = bc_NewASTElif($2, $3);
	}
	;
while_stmt
	: WHILE expression scope_optional
	{
		$$ = bc_NewASTWhile($2, $3);
	}
	;
break_stmt
	: BREAK stmt_term
	{
		$$ = bc_NewASTBreak();
	}
	;
continue_stmt
	: CONTINUE stmt_term
	{
		$$ = bc_NewASTContinue();
	}
	;
return_stmt
	: RETURN expression stmt_term
	{
		$$ = bc_NewASTReturn($2);
	}
	| RETURN stmt_term
	{
		$$ = bc_NewASTReturnEmpty();
	}
	;
throw_stmt
	: THROW expression stmt_term
	{
		$$ = bc_NewASTThrow($2);
	}
	;
try_stmt
	: TRY scope catch_stmt_list
	{
		$$ = bc_NewASTTry($2, $3);
	}
	;
catch_stmt_list
	: catch_stmt
	{
		$$ = $1;
	}
	| catch_stmt_list catch_stmt
	{
		$$ = bc_NewASTCatchList($2, $1);
	}
	;
catch_stmt
	: CATCH LRB typename_T IDENT RRB scope
	{
		$$ = bc_NewASTCatch($3, $4, $6);
	}
	;
assert_stmt
	: ASSER_T expression COLON expression stmt_term
	{
		$$ = bc_NewASTAssert($2, $4);
	}
	| ASSER_T expression stmt_term
	{
		$$ = bc_NewASTAssert($2, bc_NewASTBlank());
	}
	;
defer_stmt
	: DEFER stmt
	{
		$$ = bc_NewASTDefer($2);
	}
	;
yield_return_stmt
	: YIELD RETURN expression stmt_term
	{
		$$ = bc_NewASTYieldReturn($3);
	}
	;
yield_break_stmt
	: YIELD BREAK stmt_term
	{
		$$ = bc_NewASTYieldBreak();
	}
	;
scope
	: LCB stmt_list RCB
	{
		$$ = bc_NewASTScope($2);
	}
	| LCB RCB
	{
		$$ = bc_NewASTScopeEmpty();
	}
	;
scope_optional
	: SEMI
	{
		$$ = bc_NewASTBlank();
	}
	| scope
	;
stmt_term
	: SEMI
	;
%%



