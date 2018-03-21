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
     TRUE_TOK = 303,
     FALSE_TOK = 304,
     NULL_TOK = 305,
     AS = 306,
     INTERFACE = 307,
     CLASS = 308,
     ENUM = 309,
     PUBLIC = 310,
     PRIVATE = 311,
     PROTECTED = 312,
     STATIC = 313,
     NATIVE = 314,
     NEW = 315,
     IN = 316,
     OUT = 317,
     CTOR = 318,
     DEF = 319,
     ARROW = 320,
     NAMESPACE = 321,
     RETURN = 322,
     IF = 323,
     ELIF = 324,
     ELSE = 325,
     WHILE = 326,
     BREAK = 327,
     CONTINUE = 328,
     TRY = 329,
     CATCH = 330,
     THROW = 331,
     UMINUS = 332,
     NONAME = 333
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
#define TRUE_TOK 303
#define FALSE_TOK 304
#define NULL_TOK 305
#define AS 306
#define INTERFACE 307
#define CLASS 308
#define ENUM 309
#define PUBLIC 310
#define PRIVATE 311
#define PROTECTED 312
#define STATIC 313
#define NATIVE 314
#define NEW 315
#define IN 316
#define OUT 317
#define CTOR 318
#define DEF 319
#define ARROW 320
#define NAMESPACE 321
#define RETURN 322
#define IF 323
#define ELIF 324
#define ELSE 325
#define WHILE 326
#define BREAK 327
#define CONTINUE 328
#define TRY 329
#define CATCH 330
#define THROW 331
#define UMINUS 332
#define NONAME 333




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 15 "signal.y"
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
#line 215 "signal.tab.h"
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
