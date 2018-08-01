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
     ASSIGN = 289,
     ADD_ASSIGN = 290,
     SUB_ASSIGN = 291,
     MUL_ASSIGN = 292,
     DIV_ASSIGN = 293,
     MOD_ASSIGN = 294,
     AND_ASSIGN = 295,
     OR_ASSIGN = 296,
     LSHIFT_ASSIGN = 297,
     RSHIFT_ASSIGN = 298,
     EXC_OR_ASSIGN = 299,
     INC = 300,
     DEC = 301,
     EXC_OR = 302,
     LCB = 303,
     RCB = 304,
     LRB = 305,
     RRB = 306,
     LSB = 307,
     RSB = 308,
     SEMI = 309,
     IMPORT = 310,
     VAR = 311,
     PROPERTY = 312,
     DEFSET = 313,
     DEFGET = 314,
     THIS_TOK = 315,
     SUPER_TOK = 316,
     TRUE_TOK = 317,
     FALSE_TOK = 318,
     NULL_TOK = 319,
     AS = 320,
     ABSTRACT = 321,
     OVERRIDE = 322,
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
     IF = 336,
     ELIF = 337,
     ELSE = 338,
     WHILE = 339,
     BREAK = 340,
     CONTINUE = 341,
     TRY = 342,
     CATCH = 343,
     THROW = 344,
     ASSERT_T = 345,
     DEFER = 346,
     INSTANCEOF = 347,
     OPERATOR = 348,
     BOUNDS_EXTENDS = 349,
     BOUNDS_SUPER = 350,
     PRE_DEC = 351,
     PRE_INC = 352,
     QUOTE = 353,
     POST_DEC = 354,
     POST_INC = 355,
     FUNCCALL = 356,
     REF = 357,
     POSITIVE = 358,
     NEGATIVE = 359,
     FORM_TYPE = 360
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
#define ASSIGN 289
#define ADD_ASSIGN 290
#define SUB_ASSIGN 291
#define MUL_ASSIGN 292
#define DIV_ASSIGN 293
#define MOD_ASSIGN 294
#define AND_ASSIGN 295
#define OR_ASSIGN 296
#define LSHIFT_ASSIGN 297
#define RSHIFT_ASSIGN 298
#define EXC_OR_ASSIGN 299
#define INC 300
#define DEC 301
#define EXC_OR 302
#define LCB 303
#define RCB 304
#define LRB 305
#define RRB 306
#define LSB 307
#define RSB 308
#define SEMI 309
#define IMPORT 310
#define VAR 311
#define PROPERTY 312
#define DEFSET 313
#define DEFGET 314
#define THIS_TOK 315
#define SUPER_TOK 316
#define TRUE_TOK 317
#define FALSE_TOK 318
#define NULL_TOK 319
#define AS 320
#define ABSTRACT 321
#define OVERRIDE 322
#define INTERFACE 323
#define CLASS 324
#define ENUM 325
#define PUBLIC 326
#define PRIVATE 327
#define PROTECTED 328
#define STATIC 329
#define NATIVE 330
#define NEW 331
#define DEF 332
#define ARROW 333
#define NAMESPACE 334
#define RETURN 335
#define IF 336
#define ELIF 337
#define ELSE 338
#define WHILE 339
#define BREAK 340
#define CONTINUE 341
#define TRY 342
#define CATCH 343
#define THROW 344
#define ASSERT_T 345
#define DEFER 346
#define INSTANCEOF 347
#define OPERATOR 348
#define BOUNDS_EXTENDS 349
#define BOUNDS_SUPER 350
#define PRE_DEC 351
#define PRE_INC 352
#define QUOTE 353
#define POST_DEC 354
#define POST_INC 355
#define FUNCCALL 356
#define REF 357
#define POSITIVE 358
#define NEGATIVE 359
#define FORM_TYPE 360




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
#line 268 "beacon.tab.h"
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
