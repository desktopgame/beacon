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
    INT = 260,
    DOUBLE = 261,
    IDENT = 262,
    DOT = 263,
    COMMA = 264,
    COLON = 265,
    COLO_COLO = 266,
    LINE = 267,
    ADD = 268,
    SUB = 269,
    MUL = 270,
    DIV = 271,
    MOD = 272,
    NOT = 273,
    LSHIFT = 274,
    RSHIFT = 275,
    CHILDA = 276,
    EQUAL = 277,
    NOTEQUAL = 278,
    GT = 279,
    GE = 280,
    LT = 281,
    LE = 282,
    LGEN = 283,
    RGEN = 284,
    BIT_AND = 285,
    LOGIC_AND = 286,
    BIT_OR = 287,
    LOGIC_OR = 288,
    FINAL = 289,
    ASSIGN = 290,
    ADD_ASSIGN = 291,
    SUB_ASSIGN = 292,
    MUL_ASSIGN = 293,
    DIV_ASSIGN = 294,
    MOD_ASSIGN = 295,
    AND_ASSIGN = 296,
    OR_ASSIGN = 297,
    LSHIFT_ASSIGN = 298,
    RSHIFT_ASSIGN = 299,
    EXC_OR_ASSIGN = 300,
    INC = 301,
    DEC = 302,
    EXC_OR = 303,
    LCB = 304,
    RCB = 305,
    LRB = 306,
    RRB = 307,
    LSB = 308,
    RSB = 309,
    SEMI = 310,
    IMPORT = 311,
    VAR = 312,
    PROPERTY = 313,
    DEFSET = 314,
    DEFGET = 315,
    THIS_TOK = 316,
    SUPER_TOK = 317,
    TRUE_TOK = 318,
    FALSE_TOK = 319,
    NULL_TOK = 320,
    AS = 321,
    ABSTRACT = 322,
    INTERFACE = 323,
    CLASS = 324,
    ENUM = 325,
    PUBLIC = 326,
    PRIVATE = 327,
    PROTECTED = 328,
    STATIC = 329,
    NATIVE = 330,
    NEW = 331,
    DEF = 332,
    ARROW = 333,
    NAMESPACE = 334,
    RETURN = 335,
    YIELD = 336,
    IF = 337,
    ELIF = 338,
    ELSE = 339,
    WHILE = 340,
    BREAK = 341,
    CONTINUE = 342,
    TRY = 343,
    CATCH = 344,
    THROW = 345,
    ASSER_T = 346,
    DEFER = 347,
    INSTANCEOF = 348,
    OPERATOR = 349,
    BOUNDS_EXTENDS = 350,
    BOUNDS_SUPER = 351,
    SUBSCRIPT_SET = 352,
    SUBSCRIPT_GET = 353,
    QUOTE = 354,
    FUNCCALL = 355,
    ARRAY_SUBSCRIPT = 356,
    NEGATIVE = 357,
    POSITIVE = 358,
    REF = 359,
    FORM_TYPE = 360
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "beacon.y" /* yacc.c:1916  */

	char char_value;
	string_view stringv_value;
	ast* ast_value;
	assign_operator_type assign_otype_value;
	constructor_chain_type chain_type_value;
	access_level access_level_value;

#line 169 "beacon.tab.h" /* yacc.c:1916  */
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
