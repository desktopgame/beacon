//insert by compile.rb
#include "../ast/ast.h"
#include "../ast/ast_new_factor.h"
#include "../ast/constructor_chain_type.h"
#include "../ast/assign_operator_type.h"
#include "../ast/modifier_type.h"
#include "../ast/access_level.h"
#include "../util/mem.h"
/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CHAR_LITERAL = 258,
     STRING_LITERAL = 259,
     INT = 260,
     DOUBLE = 261,
     IDENT = 262,
     DOT = 263,
     COMMA = 264,
     COMMA_OPT = 265,
     COLON = 266,
     COLO_COLO = 267,
     ADD = 268,
     SUB = 269,
     MUL = 270,
     DIV = 271,
     MOD = 272,
     NOT = 273,
     ASSIGN = 274,
     ADD_ASSIGN = 275,
     SUB_ASSIGN = 276,
     MUL_ASSIGN = 277,
     DIV_ASSIGN = 278,
     MOD_ASSIGN = 279,
     EQUAL = 280,
     NOTEQUAL = 281,
     INC = 282,
     DEC = 283,
     GT = 284,
     GE = 285,
     LT = 286,
     LE = 287,
     BIT_AND = 288,
     LOGIC_AND = 289,
     BIT_OR = 290,
     LOGIC_OR = 291,
     LCB = 292,
     RCB = 293,
     LRB = 294,
     RRB = 295,
     LSB = 296,
     RSB = 297,
     SEMI = 298,
     IMPORT = 299,
     VAR = 300,
     THIS = 301,
     SUPER = 302,
     TRUE = 303,
     FALSE = 304,
     INTERFACE = 305,
     CLASS = 306,
     ENUM = 307,
     PUBLIC = 308,
     PRIVATE = 309,
     PROTECTED = 310,
     STATIC = 311,
     NATIVE = 312,
     NEW = 313,
     CTOR = 314,
     DEF = 315,
     ARROW = 316,
     NAMESPACE = 317,
     RETURN = 318,
     IF = 319,
     ELIF = 320,
     ELSE = 321,
     WHILE = 322,
     BREAK = 323,
     CONTINUE = 324
   };
#endif
/* Tokens.  */
#define CHAR_LITERAL 258
#define STRING_LITERAL 259
#define INT 260
#define DOUBLE 261
#define IDENT 262
#define DOT 263
#define COMMA 264
#define COMMA_OPT 265
#define COLON 266
#define COLO_COLO 267
#define ADD 268
#define SUB 269
#define MUL 270
#define DIV 271
#define MOD 272
#define NOT 273
#define ASSIGN 274
#define ADD_ASSIGN 275
#define SUB_ASSIGN 276
#define MUL_ASSIGN 277
#define DIV_ASSIGN 278
#define MOD_ASSIGN 279
#define EQUAL 280
#define NOTEQUAL 281
#define INC 282
#define DEC 283
#define GT 284
#define GE 285
#define LT 286
#define LE 287
#define BIT_AND 288
#define LOGIC_AND 289
#define BIT_OR 290
#define LOGIC_OR 291
#define LCB 292
#define RCB 293
#define LRB 294
#define RRB 295
#define LSB 296
#define RSB 297
#define SEMI 298
#define IMPORT 299
#define VAR 300
#define THIS 301
#define SUPER 302
#define TRUE 303
#define FALSE 304
#define INTERFACE 305
#define CLASS 306
#define ENUM 307
#define PUBLIC 308
#define PRIVATE 309
#define PROTECTED 310
#define STATIC 311
#define NATIVE 312
#define NEW 313
#define CTOR 314
#define DEF 315
#define ARROW 316
#define NAMESPACE 317
#define RETURN 318
#define IF 319
#define ELIF 320
#define ELSE 321
#define WHILE 322
#define BREAK 323
#define CONTINUE 324




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 15 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
{
	char char_value;
	const char* string_value;
	ast* ast_value;
	assign_operator_type assign_otype_value;
	constructor_chain_type chain_type_value;
	modifier_type modifier_type_value;
	access_level access_level_value;
}
/* Line 1529 of yacc.c.  */
#line 197 "signal.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
