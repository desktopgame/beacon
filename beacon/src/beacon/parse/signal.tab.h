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
     BIT_AND = 283,
     LOGIC_AND = 284,
     BIT_OR = 285,
     LOGIC_OR = 286,
     ASSIGN = 287,
     ADD_ASSIGN = 288,
     SUB_ASSIGN = 289,
     MUL_ASSIGN = 290,
     DIV_ASSIGN = 291,
     MOD_ASSIGN = 292,
     AND_ASSIGN = 293,
     OR_ASSIGN = 294,
     LSHIFT_ASSIGN = 295,
     RSHIFT_ASSIGN = 296,
     EXC_OR_ASSIGN = 297,
     INC = 298,
     DEC = 299,
     EXC_OR = 300,
     LCB = 301,
     RCB = 302,
     LRB = 303,
     RRB = 304,
     LSB = 305,
     RSB = 306,
     SEMI = 307,
     IMPORT = 308,
     VAR = 309,
     THIS = 310,
     SUPER = 311,
     TRUE_TOK = 312,
     FALSE_TOK = 313,
     NULL_TOK = 314,
     AS = 315,
     INTERFACE = 316,
     CLASS = 317,
     ENUM = 318,
     PUBLIC = 319,
     PRIVATE = 320,
     PROTECTED = 321,
     STATIC = 322,
     NATIVE = 323,
     NEW = 324,
     IN = 325,
     OUT = 326,
     CTOR = 327,
     DEF = 328,
     ARROW = 329,
     NAMESPACE = 330,
     RETURN = 331,
     IF = 332,
     ELIF = 333,
     ELSE = 334,
     WHILE = 335,
     BREAK = 336,
     CONTINUE = 337,
     TRY = 338,
     CATCH = 339,
     THROW = 340,
     QUOTE = 341,
     POST_DEC = 342,
     POST_INC = 343,
     FUNCCALL = 344,
     POSITIVE = 345,
     NEGATIVE = 346,
     PRE_DEC = 347,
     PRE_INC = 348,
     FORM_TYPE = 349
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
#define COLON 265
#define COLO_COLO 266
#define LINE 267
#define ADD 268
#define SUB 269
#define MUL 270
#define DIV 271
#define MOD 272
#define NOT 273
#define LSHIFT 274
#define RSHIFT 275
#define CHILDA 276
#define EQUAL 277
#define NOTEQUAL 278
#define GT 279
#define GE 280
#define LT 281
#define LE 282
#define BIT_AND 283
#define LOGIC_AND 284
#define BIT_OR 285
#define LOGIC_OR 286
#define ASSIGN 287
#define ADD_ASSIGN 288
#define SUB_ASSIGN 289
#define MUL_ASSIGN 290
#define DIV_ASSIGN 291
#define MOD_ASSIGN 292
#define AND_ASSIGN 293
#define OR_ASSIGN 294
#define LSHIFT_ASSIGN 295
#define RSHIFT_ASSIGN 296
#define EXC_OR_ASSIGN 297
#define INC 298
#define DEC 299
#define EXC_OR 300
#define LCB 301
#define RCB 302
#define LRB 303
#define RRB 304
#define LSB 305
#define RSB 306
#define SEMI 307
#define IMPORT 308
#define VAR 309
#define THIS 310
#define SUPER 311
#define TRUE_TOK 312
#define FALSE_TOK 313
#define NULL_TOK 314
#define AS 315
#define INTERFACE 316
#define CLASS 317
#define ENUM 318
#define PUBLIC 319
#define PRIVATE 320
#define PROTECTED 321
#define STATIC 322
#define NATIVE 323
#define NEW 324
#define IN 325
#define OUT 326
#define CTOR 327
#define DEF 328
#define ARROW 329
#define NAMESPACE 330
#define RETURN 331
#define IF 332
#define ELIF 333
#define ELSE 334
#define WHILE 335
#define BREAK 336
#define CONTINUE 337
#define TRY 338
#define CATCH 339
#define THROW 340
#define QUOTE 341
#define POST_DEC 342
#define POST_INC 343
#define FUNCCALL 344
#define POSITIVE 345
#define NEGATIVE 346
#define PRE_DEC 347
#define PRE_INC 348
#define FORM_TYPE 349




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
#line 247 "signal.tab.h"
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
