#include "../ast/ast.h"
#include "../ast/ast_new_factor.h"
#include "../ast/constructor_chain_type.h"
#include "../ast/assign_operator_type.h"
#include "../ast/modifier_type.h"
#include "../ast/access_level.h"
#include "../util/mem.h"
/* A Bison parser, made by GNU Bison 3.0.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_BEACON_TAB_H_INCLUDED
# define YY_YY_BEACON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHAR_LITERAL = 258,
    STRING_LITERAL = 259,
    SHORT = 260,
    INT = 261,
    LONG = 262,
    FLOAT = 263,
    DOUBLE = 264,
    IDENT = 265,
    DOT = 266,
    COMMA = 267,
    COLON = 268,
    COLO_COLO = 269,
    LINE = 270,
    ADD = 271,
    SUB = 272,
    MUL = 273,
    DIV = 274,
    MOD = 275,
    NOT = 276,
    LSHIFT = 277,
    RSHIFT = 278,
    CHILDA = 279,
    EQUAL = 280,
    NOTEQUAL = 281,
    GT = 282,
    GE = 283,
    LT = 284,
    LE = 285,
    LGEN = 286,
    RGEN = 287,
    BIT_AND = 288,
    LOGIC_AND = 289,
    BIT_OR = 290,
    LOGIC_OR = 291,
    FINAL = 292,
    ASSIGN = 293,
    ADD_ASSIGN = 294,
    SUB_ASSIGN = 295,
    MUL_ASSIGN = 296,
    DIV_ASSIGN = 297,
    MOD_ASSIGN = 298,
    AND_ASSIGN = 299,
    OR_ASSIGN = 300,
    LSHIFT_ASSIGN = 301,
    RSHIFT_ASSIGN = 302,
    EXC_OR_ASSIGN = 303,
    INC = 304,
    DEC = 305,
    EXC_OR = 306,
    LCB = 307,
    RCB = 308,
    LRB = 309,
    RRB = 310,
    LSB = 311,
    RSB = 312,
    SEMI = 313,
    IMPORT = 314,
    VAR = 315,
    PROPERTY = 316,
    DEFSET = 317,
    DEFGET = 318,
    THIS_TOK = 319,
    SUPER_TOK = 320,
    TRUE_TOK = 321,
    FALSE_TOK = 322,
    NULL_TOK = 323,
    AS = 324,
    ABSTRACT = 325,
    INTERFACE = 326,
    CLASS = 327,
    ENUM = 328,
    PUBLIC = 329,
    PRIVATE = 330,
    PROTECTED = 331,
    STATIC = 332,
    NATIVE = 333,
    NEW = 334,
    DEF = 335,
    ARROW = 336,
    NAMESPACE = 337,
    RETURN = 338,
    YIELD = 339,
    IF = 340,
    ELIF = 341,
    ELSE = 342,
    WHILE = 343,
    BREAK = 344,
    CONTINUE = 345,
    TRY = 346,
    CATCH = 347,
    THROW = 348,
    ASSER_T = 349,
    DEFER = 350,
    INSTANCEOF = 351,
    OPERATOR = 352,
    BOUNDS_EXTENDS = 353,
    BOUNDS_SUPER = 354,
    SUBSCRIPT_SET = 355,
    SUBSCRIPT_GET = 356,
    QUOTE = 357,
    NEGATIVE = 358,
    POSITIVE = 359,
    REF = 360,
    FUNCCALL = 361,
    ARRAY_SUBSCRIPT = 362,
    FORM_TYPE = 363
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "beacon.y" /* yacc.c:1916  */

	char char_value;
	bc_StringView stringv_value;
	bc_AST* ast_value;
	bc_AssignOperatorType assign_otype_value;
	bc_ConstructorChainType chain_type_value;
	bc_AccessLevel access_level_value;

#line 172 "beacon.tab.h" /* yacc.c:1916  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_BEACON_TAB_H_INCLUDED  */
