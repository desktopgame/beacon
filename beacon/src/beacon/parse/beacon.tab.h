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
     OVERRIDE = 323,
     INTERFACE = 324,
     CLASS = 325,
     ENUM = 326,
     PUBLIC = 327,
     PRIVATE = 328,
     PROTECTED = 329,
     STATIC = 330,
     NATIVE = 331,
     NEW = 332,
     DEF = 333,
     ARROW = 334,
     NAMESPACE = 335,
     RETURN = 336,
     YIELD = 337,
     IF = 338,
     ELIF = 339,
     ELSE = 340,
     WHILE = 341,
     BREAK = 342,
     CONTINUE = 343,
     TRY = 344,
     CATCH = 345,
     THROW = 346,
     ASSERT_T = 347,
     DEFER = 348,
     INSTANCEOF = 349,
     OPERATOR = 350,
     BOUNDS_EXTENDS = 351,
     BOUNDS_SUPER = 352,
     PRE_DEC = 353,
     PRE_INC = 354,
     QUOTE = 355,
     POST_DEC = 356,
     POST_INC = 357,
     FUNCCALL = 358,
     REF = 359,
     POSITIVE = 360,
     NEGATIVE = 361,
     FORM_TYPE = 362
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
#define LGEN 283
#define RGEN 284
#define BIT_AND 285
#define LOGIC_AND 286
#define BIT_OR 287
#define LOGIC_OR 288
#define FINAL 289
#define ASSIGN 290
#define ADD_ASSIGN 291
#define SUB_ASSIGN 292
#define MUL_ASSIGN 293
#define DIV_ASSIGN 294
#define MOD_ASSIGN 295
#define AND_ASSIGN 296
#define OR_ASSIGN 297
#define LSHIFT_ASSIGN 298
#define RSHIFT_ASSIGN 299
#define EXC_OR_ASSIGN 300
#define INC 301
#define DEC 302
#define EXC_OR 303
#define LCB 304
#define RCB 305
#define LRB 306
#define RRB 307
#define LSB 308
#define RSB 309
#define SEMI 310
#define IMPORT 311
#define VAR 312
#define PROPERTY 313
#define DEFSET 314
#define DEFGET 315
#define THIS_TOK 316
#define SUPER_TOK 317
#define TRUE_TOK 318
#define FALSE_TOK 319
#define NULL_TOK 320
#define AS 321
#define ABSTRACT 322
#define OVERRIDE 323
#define INTERFACE 324
#define CLASS 325
#define ENUM 326
#define PUBLIC 327
#define PRIVATE 328
#define PROTECTED 329
#define STATIC 330
#define NATIVE 331
#define NEW 332
#define DEF 333
#define ARROW 334
#define NAMESPACE 335
#define RETURN 336
#define YIELD 337
#define IF 338
#define ELIF 339
#define ELSE 340
#define WHILE 341
#define BREAK 342
#define CONTINUE 343
#define TRY 344
#define CATCH 345
#define THROW 346
#define ASSERT_T 347
#define DEFER 348
#define INSTANCEOF 349
#define OPERATOR 350
#define BOUNDS_EXTENDS 351
#define BOUNDS_SUPER 352
#define PRE_DEC 353
#define PRE_INC 354
#define QUOTE 355
#define POST_DEC 356
#define POST_INC 357
#define FUNCCALL 358
#define REF 359
#define POSITIVE 360
#define NEGATIVE 361
#define FORM_TYPE 362




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 17 "beacon.y"
{
	char char_value;
	string_view stringv_value;
	ast* ast_value;
	assign_operator_type assign_otype_value;
	constructor_chain_type chain_type_value;
	access_level access_level_value;
}
/* Line 1529 of yacc.c.  */
#line 272 "beacon.tab.h"
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
