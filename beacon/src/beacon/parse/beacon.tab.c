/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



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
     THIS_TOK = 312,
     SUPER_TOK = 313,
     TRUE_TOK = 314,
     FALSE_TOK = 315,
     NULL_TOK = 316,
     AS = 317,
     ABSTRACT = 318,
     OVERRIDE = 319,
     INTERFACE = 320,
     CLASS = 321,
     ENUM = 322,
     PUBLIC = 323,
     PRIVATE = 324,
     PROTECTED = 325,
     STATIC = 326,
     NATIVE = 327,
     NEW = 328,
     DEF = 329,
     ARROW = 330,
     NAMESPACE = 331,
     RETURN = 332,
     IF = 333,
     ELIF = 334,
     ELSE = 335,
     WHILE = 336,
     BREAK = 337,
     CONTINUE = 338,
     TRY = 339,
     CATCH = 340,
     THROW = 341,
     ASSERT_T = 342,
     DEFER = 343,
     INSTANCEOF = 344,
     OPERATOR = 345,
     BOUNDS_EXTENDS = 346,
     BOUNDS_SUPER = 347,
     PRE_DEC = 348,
     PRE_INC = 349,
     QUOTE = 350,
     POST_DEC = 351,
     POST_INC = 352,
     FUNCCALL = 353,
     REF = 354,
     POSITIVE = 355,
     NEGATIVE = 356,
     FORM_TYPE = 357
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
#define THIS_TOK 312
#define SUPER_TOK 313
#define TRUE_TOK 314
#define FALSE_TOK 315
#define NULL_TOK 316
#define AS 317
#define ABSTRACT 318
#define OVERRIDE 319
#define INTERFACE 320
#define CLASS 321
#define ENUM 322
#define PUBLIC 323
#define PRIVATE 324
#define PROTECTED 325
#define STATIC 326
#define NATIVE 327
#define NEW 328
#define DEF 329
#define ARROW 330
#define NAMESPACE 331
#define RETURN 332
#define IF 333
#define ELIF 334
#define ELSE 335
#define WHILE 336
#define BREAK 337
#define CONTINUE 338
#define TRY 339
#define CATCH 340
#define THROW 341
#define ASSERT_T 342
#define DEFER 343
#define INSTANCEOF 344
#define OPERATOR 345
#define BOUNDS_EXTENDS 346
#define BOUNDS_SUPER 347
#define PRE_DEC 348
#define PRE_INC 349
#define QUOTE 350
#define POST_DEC 351
#define POST_INC 352
#define FUNCCALL 353
#define REF 354
#define POSITIVE 355
#define NEGATIVE 356
#define FORM_TYPE 357




/* Copy the first part of user declarations.  */
#line 1 "beacon.y"

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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 15 "beacon.y"
{
	char char_value;
	const char* string_value;
	ast* ast_value;
	assign_operator_type assign_otype_value;
	constructor_chain_type chain_type_value;
	access_level access_level_value;
}
/* Line 193 of yacc.c.  */
#line 324 "beacon.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 349 "beacon.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2351

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  105
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  227
/* YYNRULES -- Number of states.  */
#define YYNSTATES  598

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   357

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     104,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      99,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,   100,   101,   102,   103
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    13,    15,    17,    19,
      21,    25,    29,    33,    35,    37,    39,    41,    43,    46,
      47,    49,    51,    55,    57,    60,    63,    66,    67,    71,
      73,    77,    79,    86,    95,   101,   109,   115,   122,   128,
     136,   137,   139,   141,   144,   148,   150,   153,   155,   157,
     159,   161,   169,   176,   182,   187,   189,   191,   192,   194,
     203,   211,   222,   232,   242,   251,   260,   269,   278,   287,
     296,   305,   314,   323,   332,   341,   350,   359,   368,   377,
     386,   395,   404,   413,   421,   429,   437,   442,   446,   448,
     451,   453,   455,   457,   459,   461,   463,   465,   467,   471,
     474,   479,   481,   489,   493,   494,   498,   500,   504,   507,
     509,   513,   517,   519,   521,   524,   527,   531,   535,   539,
     543,   547,   551,   555,   559,   563,   567,   571,   575,   579,
     583,   587,   591,   595,   599,   603,   607,   611,   615,   619,
     623,   627,   631,   635,   639,   643,   647,   651,   654,   657,
     662,   666,   673,   679,   681,   683,   685,   688,   693,   700,
     707,   714,   721,   728,   735,   742,   749,   756,   763,   770,
     777,   784,   791,   798,   805,   812,   819,   825,   831,   837,
     839,   841,   843,   845,   847,   849,   851,   853,   856,   859,
     861,   863,   865,   867,   869,   871,   873,   875,   877,   879,
     881,   883,   887,   893,   899,   903,   909,   914,   921,   923,
     926,   930,   934,   937,   940,   944,   948,   952,   954,   957,
     964,   970,   974,   977,   981,   984,   986,   988
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     106,     0,    -1,   107,   108,    -1,   106,   108,    -1,     1,
     104,    -1,    -1,   115,    -1,   153,    -1,   109,    -1,   134,
      -1,    76,   114,   110,    -1,    48,   113,    49,    -1,    76,
     114,   110,    -1,   121,    -1,   122,    -1,   124,    -1,   123,
      -1,   111,    -1,   112,   111,    -1,    -1,   112,    -1,     7,
      -1,   114,    11,     7,    -1,   116,    -1,   115,   116,    -1,
      55,     4,    -1,     7,   118,    -1,    -1,    52,   119,    53,
      -1,   120,    -1,   119,     9,   120,    -1,     7,    -1,    63,
      66,   117,    48,   125,    49,    -1,    63,    66,   117,    10,
     145,    48,   125,    49,    -1,    66,   117,    48,   125,    49,
      -1,    66,   117,    10,   145,    48,   125,    49,    -1,    67,
       7,    48,   141,    49,    -1,    67,     7,    48,   141,     9,
      49,    -1,    65,   117,    48,   125,    49,    -1,    65,   117,
      10,   145,    48,   125,    49,    -1,    -1,   126,    -1,   127,
      -1,   126,   127,    -1,   140,    10,   128,    -1,   129,    -1,
     128,   129,    -1,   130,    -1,   135,    -1,   136,    -1,   137,
      -1,    74,    73,    50,   142,    51,   133,   171,    -1,    74,
      73,    50,    51,   133,   171,    -1,    10,   132,    50,   143,
      51,    -1,    10,   132,    50,    51,    -1,    58,    -1,    57,
      -1,    -1,   131,    -1,    74,     7,    50,   142,    51,    75,
     146,   171,    -1,    74,     7,    50,    51,    75,   146,   171,
      -1,    74,   138,     7,   118,    50,   142,    51,    75,   146,
     171,    -1,    74,   138,     7,   118,    50,    51,    75,   146,
     171,    -1,    74,     7,   118,    50,   142,    51,    75,   146,
     171,    -1,    74,     7,   118,    50,    51,    75,   146,   171,
      -1,    90,    13,    50,   142,    51,    75,   146,   171,    -1,
      90,    14,    50,   142,    51,    75,   146,   171,    -1,    90,
      15,    50,   142,    51,    75,   146,   171,    -1,    90,    16,
      50,   142,    51,    75,   146,   171,    -1,    90,    17,    50,
     142,    51,    75,   146,   171,    -1,    90,    24,    50,   142,
      51,    75,   146,   171,    -1,    90,    25,    50,   142,    51,
      75,   146,   171,    -1,    90,    26,    50,   142,    51,    75,
     146,   171,    -1,    90,    27,    50,   142,    51,    75,   146,
     171,    -1,    90,    22,    50,   142,    51,    75,   146,   171,
      -1,    90,    23,    50,   142,    51,    75,   146,   171,    -1,
      90,    32,    50,   142,    51,    75,   146,   171,    -1,    90,
      30,    50,   142,    51,    75,   146,   171,    -1,    90,    33,
      50,   142,    51,    75,   146,   171,    -1,    90,    31,    50,
     142,    51,    75,   146,   171,    -1,    90,    19,    50,   142,
      51,    75,   146,   171,    -1,    90,    20,    50,   142,    51,
      75,   146,   171,    -1,    90,    47,    50,   142,    51,    75,
     146,   171,    -1,    90,    18,    50,    51,    75,   146,   171,
      -1,    90,    21,    50,    51,    75,   146,   171,    -1,    90,
      14,    50,    51,    75,   146,   171,    -1,   139,   146,     7,
      54,    -1,   146,     7,    54,    -1,   139,    -1,   138,   139,
      -1,    71,    -1,    72,    -1,    63,    -1,    64,    -1,    68,
      -1,    69,    -1,    70,    -1,     7,    -1,   141,     9,     7,
      -1,   146,     7,    -1,   142,     9,   146,     7,    -1,   148,
      -1,    95,    50,   142,    51,    75,   146,   170,    -1,   143,
       9,   148,    -1,    -1,    52,   145,    53,    -1,   146,    -1,
     145,     9,   146,    -1,   147,   144,    -1,     7,    -1,   147,
      11,     7,    -1,    50,   148,    51,    -1,   151,    -1,   149,
      -1,    13,   148,    -1,    14,   148,    -1,   148,    13,   148,
      -1,   148,    14,   148,    -1,   148,    15,   148,    -1,   148,
      16,   148,    -1,   148,    17,   148,    -1,   148,    32,   148,
      -1,   148,    22,   148,    -1,   148,    23,   148,    -1,   148,
      30,   148,    -1,   148,    47,   148,    -1,   148,    33,   148,
      -1,   148,    31,   148,    -1,   150,    34,   148,    -1,   150,
      35,   148,    -1,   150,    36,   148,    -1,   150,    37,   148,
      -1,   150,    38,   148,    -1,   150,    39,   148,    -1,   150,
      40,   148,    -1,   150,    41,   148,    -1,   150,    44,   148,
      -1,   150,    42,   148,    -1,   150,    43,   148,    -1,   148,
      24,   148,    -1,   148,    25,   148,    -1,   148,    26,   148,
      -1,   148,    27,   148,    -1,   148,    19,   148,    -1,   148,
      20,   148,    -1,   148,    89,   146,    -1,   148,    62,   146,
      -1,    21,   148,    -1,    18,   148,    -1,   149,    50,   143,
      51,    -1,   149,    50,    51,    -1,    73,   147,   144,    50,
     143,    51,    -1,    73,   147,   144,    50,    51,    -1,    57,
      -1,    58,    -1,   150,    -1,   147,   144,    -1,   148,     8,
       7,   144,    -1,   148,     8,    13,    50,   148,    51,    -1,
     148,     8,    14,    50,   148,    51,    -1,   148,     8,    15,
      50,   148,    51,    -1,   148,     8,    16,    50,   148,    51,
      -1,   148,     8,    17,    50,   148,    51,    -1,   148,     8,
      24,    50,   148,    51,    -1,   148,     8,    25,    50,   148,
      51,    -1,   148,     8,    26,    50,   148,    51,    -1,   148,
       8,    27,    50,   148,    51,    -1,   148,     8,    22,    50,
     148,    51,    -1,   148,     8,    23,    50,   148,    51,    -1,
     148,     8,    32,    50,   148,    51,    -1,   148,     8,    30,
      50,   148,    51,    -1,   148,     8,    33,    50,   148,    51,
      -1,   148,     8,    31,    50,   148,    51,    -1,   148,     8,
      19,    50,   148,    51,    -1,   148,     8,    20,    50,   148,
      51,    -1,   148,     8,    47,    50,   148,    51,    -1,   148,
       8,    18,    50,    51,    -1,   148,     8,    21,    50,    51,
      -1,   148,     8,    14,    50,    51,    -1,     5,    -1,     6,
      -1,     3,    -1,     4,    -1,    59,    -1,    60,    -1,    61,
      -1,   153,    -1,   152,   153,    -1,   148,   172,    -1,   154,
      -1,   155,    -1,   156,    -1,   157,    -1,   160,    -1,   161,
      -1,   162,    -1,   163,    -1,   164,    -1,   165,    -1,   168,
      -1,   169,    -1,   146,     7,    54,    -1,   146,     7,    34,
     148,   172,    -1,    56,     7,    34,   148,   172,    -1,    78,
     148,   170,    -1,    78,   148,   170,    80,   170,    -1,    78,
     148,   170,   158,    -1,    78,   148,   170,   158,    80,   170,
      -1,   159,    -1,   158,   159,    -1,    79,   148,   170,    -1,
      81,   148,   171,    -1,    82,   172,    -1,    83,   172,    -1,
      77,   148,   172,    -1,    86,   148,   172,    -1,    84,   170,
     166,    -1,   167,    -1,   166,   167,    -1,    85,    50,   146,
       7,    51,   170,    -1,    87,   148,    10,   148,    54,    -1,
      87,   148,    54,    -1,    88,   153,    -1,    48,   152,    49,
      -1,    48,    49,    -1,    54,    -1,   170,    -1,    54,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   142,   142,   143,   144,   150,   152,   158,   162,   166,
     172,   179,   186,   190,   191,   192,   193,   197,   201,   209,
     212,   216,   220,   227,   228,   235,   242,   250,   253,   260,
     264,   271,   277,   281,   287,   291,   298,   302,   309,   313,
     321,   324,   328,   329,   336,   343,   347,   354,   355,   356,
     357,   361,   365,   372,   376,   383,   387,   395,   398,   402,
     406,   413,   417,   421,   425,   432,   436,   440,   444,   448,
     452,   456,   460,   464,   469,   473,   478,   482,   487,   491,
     496,   500,   505,   510,   515,   519,   526,   530,   537,   541,
     548,   552,   556,   560,   567,   571,   575,   582,   586,   593,
     597,   604,   608,   612,   620,   623,   630,   634,   641,   648,
     652,   661,   665,   666,   669,   673,   677,   681,   685,   689,
     693,   697,   701,   705,   709,   713,   717,   721,   725,   729,
     733,   737,   741,   745,   749,   753,   757,   761,   765,   769,
     773,   777,   781,   785,   789,   793,   797,   801,   805,   809,
     813,   817,   821,   825,   829,   833,   836,   840,   844,   848,
     852,   856,   860,   864,   868,   872,   876,   880,   884,   888,
     892,   896,   900,   904,   908,   912,   916,   920,   924,   930,
     931,   932,   933,   934,   938,   942,   951,   955,   961,   965,
     966,   967,   968,   969,   970,   971,   972,   973,   974,   975,
     976,   979,   985,   991,   997,  1001,  1005,  1009,  1015,  1016,
    1022,  1028,  1034,  1040,  1046,  1052,  1058,  1064,  1068,  1074,
    1080,  1084,  1090,  1097,  1101,  1107,  1111,  1114
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR_LITERAL", "STRING_LITERAL", "INT",
  "DOUBLE", "IDENT", "DOT", "COMMA", "COLON", "COLO_COLO", "LINE", "ADD",
  "SUB", "MUL", "DIV", "MOD", "NOT", "LSHIFT", "RSHIFT", "CHILDA", "EQUAL",
  "NOTEQUAL", "GT", "GE", "LT", "LE", "LGEN", "RGEN", "BIT_AND",
  "LOGIC_AND", "BIT_OR", "LOGIC_OR", "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN",
  "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "AND_ASSIGN", "OR_ASSIGN",
  "LSHIFT_ASSIGN", "RSHIFT_ASSIGN", "EXC_OR_ASSIGN", "INC", "DEC",
  "EXC_OR", "LCB", "RCB", "LRB", "RRB", "LSB", "RSB", "SEMI", "IMPORT",
  "VAR", "THIS_TOK", "SUPER_TOK", "TRUE_TOK", "FALSE_TOK", "NULL_TOK",
  "AS", "ABSTRACT", "OVERRIDE", "INTERFACE", "CLASS", "ENUM", "PUBLIC",
  "PRIVATE", "PROTECTED", "STATIC", "NATIVE", "NEW", "DEF", "ARROW",
  "NAMESPACE", "RETURN", "IF", "ELIF", "ELSE", "WHILE", "BREAK",
  "CONTINUE", "TRY", "CATCH", "THROW", "ASSERT_T", "DEFER", "INSTANCEOF",
  "OPERATOR", "BOUNDS_EXTENDS", "BOUNDS_SUPER", "PRE_DEC", "PRE_INC",
  "QUOTE", "POST_DEC", "POST_INC", "FUNCCALL", "'<'", "REF", "POSITIVE",
  "NEGATIVE", "FORM_TYPE", "'\\n'", "$accept", "compilation_unit",
  "init_decl", "body_decl", "namespace_decl", "namespace_body",
  "namespace_member_decl", "namespace_member_decl_list",
  "namespace_member_decl_optional", "namespace_path", "import_list",
  "import", "parameterized_typename", "type_parameter_group",
  "type_parameter_list", "type_parameter", "abstract_class_decl",
  "class_decl", "enum_decl", "interface_decl", "access_member_tree_opt",
  "access_member_tree", "access_member_list", "member_define_list",
  "member_define", "constructor_define", "constructor_chain",
  "constructor_chain_type_T", "constructor_chain_optional",
  "function_define", "method_define", "operator_define", "field_define",
  "modifier_type_T_list", "modifier_type_T", "access_level_T",
  "ident_list", "parameter_list", "argument_list", "typename_group",
  "typename_list", "typename_T", "fqcn_part", "expression",
  "expression_nobrace", "lhs", "primary", "stmt_list", "stmt",
  "variable_decl_stmt", "variable_init_stmt", "inferenced_type_init_stmt",
  "if_stmt", "elif_list", "elif", "while_stmt", "break_stmt",
  "continue_stmt", "return_stmt", "throw_stmt", "try_stmt",
  "catch_stmt_list", "catch_stmt", "assert_stmt", "defer_stmt", "scope",
  "scope_optional", "stmt_term", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,    60,
     354,   355,   356,   357,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   105,   106,   106,   106,   107,   107,   108,   108,   108,
     109,   110,   111,   111,   111,   111,   111,   112,   112,   113,
     113,   114,   114,   115,   115,   116,   117,   118,   118,   119,
     119,   120,   121,   121,   122,   122,   123,   123,   124,   124,
     125,   125,   126,   126,   127,   128,   128,   129,   129,   129,
     129,   130,   130,   131,   131,   132,   132,   133,   133,   134,
     134,   135,   135,   135,   135,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   137,   137,   138,   138,
     139,   139,   139,   139,   140,   140,   140,   141,   141,   142,
     142,   143,   143,   143,   144,   144,   145,   145,   146,   147,
     147,   148,   148,   148,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   151,
     151,   151,   151,   151,   151,   151,   152,   152,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   154,   155,   156,   157,   157,   157,   157,   158,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   166,   167,
     168,   168,   169,   170,   170,   171,   171,   172
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     1,     1,     1,     1,
       3,     3,     3,     1,     1,     1,     1,     1,     2,     0,
       1,     1,     3,     1,     2,     2,     2,     0,     3,     1,
       3,     1,     6,     8,     5,     7,     5,     6,     5,     7,
       0,     1,     1,     2,     3,     1,     2,     1,     1,     1,
       1,     7,     6,     5,     4,     1,     1,     0,     1,     8,
       7,    10,     9,     9,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     7,     7,     7,     4,     3,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       4,     1,     7,     3,     0,     3,     1,     3,     2,     1,
       3,     3,     1,     1,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     4,
       3,     6,     5,     1,     1,     1,     2,     4,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     5,     5,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     5,     5,     3,     5,     4,     6,     1,     2,
       3,     3,     2,     2,     3,     3,     3,     1,     2,     6,
       5,     3,     2,     3,     2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,    23,     4,    25,     1,
     181,   182,   179,   180,   109,     0,     0,     0,     0,     0,
       0,   153,   154,   183,   184,   185,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     8,
       9,     0,   104,     0,   113,   155,   112,     7,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
       2,    24,   104,   114,   115,   148,   147,     0,     0,   104,
       0,    21,     0,     0,     0,     0,   227,   212,   213,     0,
       0,     0,     0,   222,     0,     0,     0,   156,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   188,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   156,   111,     0,     0,     0,     0,    19,    10,
     214,   204,   225,   226,   211,   224,     0,   186,     0,   216,
     217,   215,     0,   221,     0,   201,   110,     0,   106,   104,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   116,   117,   118,   119,   120,   143,   144,   122,   123,
     139,   140,   141,   142,   124,   127,   121,   126,   125,   146,
     145,   150,     0,     0,   101,   128,   129,   130,   131,   132,
     133,   134,   135,   137,   138,   136,     0,     0,     0,     0,
       0,    22,     0,     0,     0,     0,     0,    17,    20,     0,
      13,    14,    16,    15,     0,     0,   206,   208,   223,   187,
       0,   218,     0,     0,     0,   105,   108,   157,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     149,   203,   152,     0,     0,     0,     0,    99,     0,    27,
       0,     0,     0,     0,    18,    11,     0,   205,     0,   209,
       0,   220,   202,   107,     0,   178,     0,     0,     0,     0,
     176,     0,     0,   177,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   103,   151,     0,     0,
       0,     0,     0,    26,     0,    40,     0,    40,     0,    12,
     210,   207,     0,   158,   159,   160,   161,   162,   173,   174,
     167,   168,   163,   164,   165,   166,   170,   172,   169,   171,
     175,     0,    60,   100,     0,     0,    40,    31,     0,    29,
       0,    94,    95,    96,     0,    41,    42,     0,     0,     0,
      97,     0,     0,     0,    59,     0,     0,     0,    28,    40,
      38,    43,     0,    40,    34,     0,    36,   219,     0,    40,
      32,    30,     0,    92,    93,    90,    91,     0,     0,    44,
      45,    47,    48,    49,    50,     0,     0,     0,    98,    37,
     102,     0,    39,    27,     0,     0,    88,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,     0,     0,
      35,    33,     0,     0,    27,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    87,     0,    57,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    86,     0,     0,     0,    58,     0,    57,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    56,    55,     0,    52,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,    85,
       0,     0,     0,     0,    83,     0,     0,    84,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
       0,    54,     0,     0,     0,    65,    66,    67,    68,    69,
      80,    81,    74,    75,    70,    71,    72,    73,    77,    79,
      76,    78,    82,    63,    53,    62,     0,    61
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    38,    39,   129,   217,   218,   219,    72,
       5,     6,   270,   313,   348,   349,   220,   221,   222,   223,
     354,   355,   356,   389,   390,   391,   487,   516,   488,    40,
     392,   393,   394,   405,   395,   357,   361,   209,   193,    87,
     147,   210,    62,    43,    44,    45,    46,   136,    47,    48,
      49,    50,    51,   226,   227,    52,    53,    54,    55,    56,
      57,   139,   140,    58,    59,   133,   134,    77
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -359
static const yytype_int16 yypact[] =
{
     897,   -73,    41,   809,   983,    75,  -359,  -359,  -359,  -359,
    -359,  -359,  -359,  -359,  -359,  2278,  2278,  2278,  2278,  2278,
      63,  -359,  -359,  -359,  -359,  -359,   125,   137,   140,  2278,
    2278,  2278,    81,    81,    91,  2278,  2278,  1241,  -359,  -359,
    -359,   145,    29,  1318,   176,   313,  -359,  -359,  -359,  -359,
    -359,  -359,  -359,  -359,  -359,  -359,  -359,  -359,  -359,  -359,
    -359,  -359,    29,   166,   166,   166,   166,  1344,   196,    29,
     183,  -359,   111,  1318,  1395,   452,  -359,  -359,  -359,  1069,
     150,  1318,   739,  -359,   -10,   147,   125,   231,   532,  2278,
    2278,  2278,  2278,  2278,  2278,  2278,  2278,  2278,  2278,  2278,
    2278,  2278,  2278,  2278,  2278,  2278,  2278,   125,   125,  -359,
       7,  2278,  2278,  2278,  2278,  2278,  2278,  2278,  2278,  2278,
    2278,  2278,  -359,  -359,  2278,   191,    10,   235,   230,  -359,
    -359,   -28,  -359,  -359,  -359,  -359,  1155,  -359,   193,   150,
    -359,  -359,  2278,  -359,  2278,  -359,  -359,    18,  -359,    29,
     195,   215,   225,   240,   248,   250,   251,   252,   254,   255,
     258,   259,   260,   262,   265,   266,   272,   274,   275,   276,
     279,    74,    74,    -2,    -2,    -2,   559,   559,   391,   391,
      22,    22,    22,    22,  1258,  1000,   661,   914,   148,  -359,
    -359,  -359,   281,    23,  2218,  2218,  2218,  2218,  2218,  2218,
    2218,  2218,  2218,  2218,  2218,  2218,  1318,   314,   175,    44,
     282,  -359,   270,   330,   330,   331,   140,  -359,   230,   290,
    -359,  -359,  -359,  -359,  2278,    91,    70,  -359,  -359,  -359,
     125,  -359,  1436,  1318,   125,  -359,  -359,  -359,  2278,  2254,
    2278,  2278,  2278,   292,  2278,  2278,   293,  2278,  2278,  2278,
    2278,  2278,  2278,  2278,  2278,  2278,  2278,  2278,   125,  2278,
    -359,  -359,  -359,    66,   125,   125,   283,  -359,   330,   289,
     219,   224,   297,   111,  -359,  -359,  1395,  -359,    91,  -359,
     352,  -359,  -359,  -359,  1480,  -359,  1521,  1562,  1603,  1644,
    -359,  1685,  1726,  -359,  1767,  1808,  1849,  1890,  1931,  1972,
    2013,  2054,  2095,  2136,  2177,    83,  2218,  -359,    92,   354,
     125,   239,   355,  -359,   125,   154,   125,   154,   356,  -359,
    -359,  -359,   315,  -359,  -359,  -359,  -359,  -359,  -359,  -359,
    -359,  -359,  -359,  -359,  -359,  -359,  -359,  -359,  -359,  -359,
    -359,   295,  -359,  -359,    92,   125,   154,  -359,    24,  -359,
       6,  -359,  -359,  -359,   318,   154,  -359,   358,   204,   327,
    -359,   104,    91,   125,  -359,   216,   328,   355,  -359,   154,
    -359,  -359,    36,   154,  -359,    94,  -359,  -359,    91,   154,
    -359,  -359,   329,  -359,  -359,  -359,  -359,    15,  1084,    36,
    -359,  -359,  -359,  -359,  -359,   125,   373,   332,  -359,  -359,
    -359,   333,  -359,   289,   334,    48,  -359,   338,   339,   340,
     341,   343,   344,   345,   346,   347,   348,   350,   351,   353,
     362,   363,   369,   370,   375,   376,   377,  -359,   395,   374,
    -359,  -359,   379,    12,   289,  -359,   125,    34,   125,   125,
     125,   380,   125,   125,   403,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   402,  -359,    42,   447,
     100,   409,   106,   386,   107,   109,   115,   118,   387,   119,
     120,   388,   128,   129,   132,   133,   169,   181,   200,   202,
     203,   205,   206,  -359,   398,   207,   161,  -359,    92,   447,
      43,   406,   125,   411,   413,   415,   416,   125,   417,   418,
     125,   420,   421,   423,   426,   427,   428,   429,   430,   432,
     433,   435,   125,   436,  -359,  -359,   462,  -359,    92,   438,
     208,   125,    92,   125,   125,   125,   125,    92,   125,   125,
      92,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,    92,   125,   723,  -359,   125,   440,    92,  -359,
      92,    92,    92,    92,  -359,    92,    92,  -359,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,  -359,
      92,  -359,   212,    92,   125,  -359,  -359,  -359,  -359,  -359,
    -359,  -359,  -359,  -359,  -359,  -359,  -359,  -359,  -359,  -359,
    -359,  -359,  -359,  -359,  -359,  -359,    92,  -359
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -359,  -359,  -359,   466,  -359,   243,   299,  -359,  -359,   303,
    -359,   519,  -209,  -289,  -359,   160,  -359,  -359,  -359,  -359,
    -248,  -359,   187,  -359,   155,  -359,  -359,  -359,    71,  -359,
    -359,  -359,  -359,  -359,  -358,  -359,  -359,  -251,  -204,   -53,
     -22,    69,    -3,   601,  -359,  -359,  -359,  -359,   -33,  -359,
    -359,  -359,  -359,  -359,   342,  -359,  -359,  -359,  -359,  -359,
    -359,  -359,   431,  -359,  -359,   -32,  -282,   -25
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -109
static const yytype_int16 yytable[] =
{
      42,    42,    80,   263,    83,   271,    88,   305,    78,   122,
      10,    11,    12,    13,    14,   234,   125,    14,   109,    14,
      15,    16,   403,    69,   144,    17,   342,   234,    18,   406,
      88,     7,   259,   367,    42,    89,    90,    91,    92,    93,
      85,    14,   131,    14,   145,     8,   137,   435,   130,    14,
      14,   224,   225,   265,   369,   434,   141,    19,   191,   311,
     107,   208,   364,   459,    21,    22,    23,    24,    25,   359,
      68,   235,    41,    41,   260,   259,    42,   368,   383,   384,
      26,    86,    88,   149,   107,   463,   385,   386,   404,    91,
      92,    93,   265,   484,   519,   266,   236,   237,   366,   383,
     384,   398,   192,   229,   149,   149,    41,   385,   386,   265,
     387,   383,   384,   375,   432,   265,   265,   307,   265,   385,
     386,   382,   127,   149,   265,   397,   388,   265,   265,   265,
       2,   401,    14,    42,   341,    76,   107,   265,   265,    79,
      79,   265,   265,   399,    70,   461,   132,    71,    41,   224,
     278,   489,    84,   376,   146,   148,    88,   491,   493,   128,
     494,    89,    90,    91,    92,    93,   495,    94,    95,   496,
     498,   499,    98,    99,   100,   101,   189,   190,   265,   501,
     502,   261,   460,   503,   504,   462,   464,   465,   466,   467,
     265,   469,   470,   277,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,    41,   517,   485,   282,   265,
     107,   265,   265,   234,   265,   265,   265,   265,   514,   515,
     505,   259,   351,   352,   353,   234,   110,   149,   107,   314,
     124,   149,   506,   126,   316,   138,   545,   108,  -108,   520,
     549,   207,   211,   230,   320,   554,   321,    86,   557,   345,
     264,   507,   373,   508,   509,   149,   510,   511,   513,   547,
     569,   149,   149,   594,   379,   238,   575,   315,   576,   577,
     578,   579,   317,   580,   581,   239,   582,   583,   584,   585,
     586,   587,   588,   589,   590,   591,   592,   346,   593,   267,
     240,   595,   350,   212,   358,   213,   214,   215,   241,   280,
     242,   243,   244,   283,   245,   246,   216,   149,   247,   248,
     249,   149,   250,   149,   597,   251,   252,    10,    11,    12,
      13,    14,   253,   365,   254,   255,   256,    15,    16,   257,
     377,   258,    17,   308,   309,    18,   268,   269,   272,   275,
     572,   312,   149,   290,   293,   318,   400,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   310,   322,
     149,   343,   347,   360,    19,   262,   362,   370,   372,   149,
     363,    21,    22,    23,    24,    25,   374,   380,   402,   344,
     429,   430,   431,   148,   433,   148,   149,    26,   436,   437,
     438,   439,   149,   440,   441,   442,   443,   444,   445,    88,
     446,   447,   456,   448,    89,    90,    91,    92,    93,   192,
      94,    95,   449,   450,   148,    98,    99,   100,   101,   451,
     452,   102,   103,   104,   105,   453,   454,   455,   457,   458,
     149,   468,   378,   149,   149,   149,   149,   149,   106,   149,
     149,   396,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   107,   471,   149,   483,   486,   396,   490,
      88,   492,   497,   500,   428,    89,    90,    91,    92,    93,
      60,    94,    95,   512,    96,    97,    98,    99,   100,   101,
     108,   521,   102,   103,   104,   105,   523,   149,   524,   149,
     525,   526,   528,   529,   149,   531,   532,   149,   533,   106,
      79,   534,   535,   536,   537,   538,   132,   539,   540,   149,
     541,   543,   544,   546,   107,   574,   319,   274,   149,   273,
     149,   149,   149,   149,    61,   149,   149,   381,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   150,
     149,   108,   371,   149,   427,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     518,   522,   166,   167,   168,   169,   527,    88,   279,   530,
     231,   149,    89,    90,    91,    92,    93,     0,     0,   170,
       0,   542,     0,    98,    99,   100,   101,     0,     0,     0,
     548,     0,   550,   551,   552,   553,     0,   555,   556,     0,
     558,   559,   560,   561,   562,   563,   564,   565,   566,   567,
     568,     0,   570,     0,     0,   573,    63,    64,    65,    66,
      67,   107,     0,     0,     0,     0,     0,     0,     0,     0,
      73,    74,    75,     0,     0,     0,    81,    82,     0,     0,
       0,     0,     0,   596,     0,     0,     0,     0,   108,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    88,
       0,     0,     0,     0,    89,    90,    91,    92,    93,     0,
      94,    95,     0,     0,     0,    98,    99,   100,   101,     0,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   106,     0,
       0,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   107,     0,   206,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,    15,    16,     0,     0,
       0,    17,     0,   232,    18,   233,     0,    88,     0,   142,
     108,     0,    89,    90,    91,    92,    93,     0,    94,    95,
       0,    96,    97,    98,    99,   100,   101,     0,     0,   102,
     103,   104,   105,    19,   571,     0,     0,     0,     0,     0,
      21,    22,    23,    24,    25,     0,   106,     0,     0,     0,
       0,     0,     0,   143,     0,     0,    26,     0,     0,     0,
       0,   107,     0,     0,     0,     0,     0,     0,   194,     9,
       0,     0,    10,    11,    12,    13,    14,     0,   192,     0,
       0,     0,    15,    16,     0,   276,     0,    17,   108,     0,
      18,     0,     0,     0,     0,     0,     0,     0,     0,   284,
     286,   287,   288,   289,     0,   291,   292,     0,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,    19,
     306,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    26,    27,     0,    28,    29,    30,     0,     0,
      31,    32,    33,    34,     0,    35,    36,    37,     1,     0,
      -5,    -5,    -5,    -5,    -5,     0,     0,     0,     0,     0,
      -5,    -5,     0,     0,     0,    -5,     0,     0,    -5,     0,
       0,     0,    88,     0,     0,     0,     0,    89,    90,    91,
      92,    93,     0,    94,    95,     0,     0,     0,    98,    99,
     100,   101,     0,     0,   102,   103,   104,    -5,     0,     0,
       0,     0,     2,    -5,    -5,    -5,    -5,    -5,    -5,     0,
       0,   106,     0,     0,     0,     0,     0,     0,     0,     0,
      -5,    -5,     0,    -5,    -5,    -5,   107,     0,    -5,    -5,
      -5,    -5,     0,    -5,    -5,    -5,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,    15,    16,     0,     0,
       0,    17,     0,   108,    18,     0,     0,     0,    88,     0,
       0,     0,     0,    89,    90,    91,    92,    93,     0,    94,
      95,     0,     0,     0,    98,    99,   100,   101,     0,     0,
     102,     0,   104,    19,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,     0,     0,   106,     0,     0,
       0,     0,     0,     0,     0,     0,    26,    27,     0,    28,
      29,    30,   107,     0,    31,    32,    33,    34,     0,    35,
      36,    37,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,    15,    16,     0,     0,     0,    17,     0,   108,
      18,     0,     0,     0,     0,     0,     0,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,     0,     0,   422,   423,   424,   425,   135,    19,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,   426,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    26,     0,     0,   194,    29,    30,     0,     0,
      31,    32,    33,    34,     0,    35,    36,    37,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,    15,    16,
       0,     0,     0,    17,     0,     0,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   228,    19,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,     0,
       0,     0,    29,    30,     0,     0,    31,    32,    33,    34,
       0,    35,    36,    37,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,    15,    16,     0,     0,     0,    17,
       0,     0,    18,     0,     0,     0,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,     0,    94,    95,     0,
       0,     0,    98,    99,   100,   101,     0,     0,     0,     0,
     104,    19,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,     0,     0,   106,     0,     0,     0,     0,
       0,     0,     0,     0,    26,     0,     0,     0,    29,    30,
     107,     0,    31,    32,    33,    34,    88,    35,    36,    37,
       0,    89,    90,    91,    92,    93,     0,    94,    95,     0,
      96,    97,    98,    99,   100,   101,     0,   108,   102,   103,
     104,   105,    88,     0,     0,     0,     0,    89,    90,    91,
      92,    93,     0,    94,    95,   106,    96,    97,    98,    99,
     100,   101,    76,     0,   102,   103,   104,   105,     0,     0,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   106,     0,     0,     0,   123,     0,     0,     0,     0,
       0,     0,     0,    88,     0,     0,   107,   108,    89,    90,
      91,    92,    93,     0,    94,    95,     0,    96,    97,    98,
      99,   100,   101,     0,     0,   102,   103,   104,   105,     0,
       0,     0,     0,   108,     0,     0,     0,     0,     0,     0,
       0,     0,   106,    79,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,     0,    94,    95,   107,    96,    97,
      98,    99,   100,   101,     0,     0,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   106,   108,     0,     0,     0,    88,     0,
     281,     0,     0,    89,    90,    91,    92,    93,   107,    94,
      95,     0,    96,    97,    98,    99,   100,   101,     0,     0,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,     0,   106,     0,    88,
       0,   323,     0,     0,    89,    90,    91,    92,    93,     0,
      94,    95,   107,    96,    97,    98,    99,   100,   101,     0,
       0,   102,   103,   104,   105,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   106,   108,
      88,     0,   324,     0,     0,    89,    90,    91,    92,    93,
       0,    94,    95,   107,    96,    97,    98,    99,   100,   101,
       0,     0,   102,   103,   104,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   106,
     108,    88,     0,   325,     0,     0,    89,    90,    91,    92,
      93,     0,    94,    95,   107,    96,    97,    98,    99,   100,
     101,     0,     0,   102,   103,   104,   105,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     106,   108,    88,     0,   326,     0,     0,    89,    90,    91,
      92,    93,     0,    94,    95,   107,    96,    97,    98,    99,
     100,   101,     0,     0,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   106,   108,    88,     0,   327,     0,     0,    89,    90,
      91,    92,    93,     0,    94,    95,   107,    96,    97,    98,
      99,   100,   101,     0,     0,   102,   103,   104,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   106,   108,    88,     0,   328,     0,     0,    89,
      90,    91,    92,    93,     0,    94,    95,   107,    96,    97,
      98,    99,   100,   101,     0,     0,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   106,   108,    88,     0,   329,     0,     0,
      89,    90,    91,    92,    93,     0,    94,    95,   107,    96,
      97,    98,    99,   100,   101,     0,     0,   102,   103,   104,
     105,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   106,   108,    88,     0,   330,     0,
       0,    89,    90,    91,    92,    93,     0,    94,    95,   107,
      96,    97,    98,    99,   100,   101,     0,     0,   102,   103,
     104,   105,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   106,   108,    88,     0,   331,
       0,     0,    89,    90,    91,    92,    93,     0,    94,    95,
     107,    96,    97,    98,    99,   100,   101,     0,     0,   102,
     103,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   106,   108,    88,     0,
     332,     0,     0,    89,    90,    91,    92,    93,     0,    94,
      95,   107,    96,    97,    98,    99,   100,   101,     0,     0,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   106,   108,    88,
       0,   333,     0,     0,    89,    90,    91,    92,    93,     0,
      94,    95,   107,    96,    97,    98,    99,   100,   101,     0,
       0,   102,   103,   104,   105,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   106,   108,
      88,     0,   334,     0,     0,    89,    90,    91,    92,    93,
       0,    94,    95,   107,    96,    97,    98,    99,   100,   101,
       0,     0,   102,   103,   104,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   106,
     108,    88,     0,   335,     0,     0,    89,    90,    91,    92,
      93,     0,    94,    95,   107,    96,    97,    98,    99,   100,
     101,     0,     0,   102,   103,   104,   105,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     106,   108,    88,     0,   336,     0,     0,    89,    90,    91,
      92,    93,     0,    94,    95,   107,    96,    97,    98,    99,
     100,   101,     0,     0,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   106,   108,    88,     0,   337,     0,     0,    89,    90,
      91,    92,    93,     0,    94,    95,   107,    96,    97,    98,
      99,   100,   101,     0,     0,   102,   103,   104,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   106,   108,    88,     0,   338,     0,     0,    89,
      90,    91,    92,    93,     0,    94,    95,   107,    96,    97,
      98,    99,   100,   101,     0,     0,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   106,   108,    88,     0,   339,     0,     0,
      89,    90,    91,    92,    93,     0,    94,    95,   107,    96,
      97,    98,    99,   100,   101,     0,     0,   102,   103,   104,
     105,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   106,   108,    88,     0,   340,     0,
       0,    89,    90,    91,    92,    93,     0,    94,    95,   107,
      96,    97,    98,    99,   100,   101,     0,     0,   102,   103,
     104,   105,     0,     0,     0,     0,     0,    10,    11,    12,
      13,    14,     0,     0,     0,   106,   108,    15,    16,     0,
       0,     0,    17,     0,     0,    18,     0,     0,     0,     0,
     107,    10,    11,    12,    13,    14,     0,     0,     0,     0,
       0,    15,    16,     0,     0,     0,    17,     0,     0,    18,
       0,     0,     0,     0,    19,   285,     0,   108,     0,     0,
       0,    21,    22,    23,    24,    25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    26,    19,     0,
       0,     0,     0,     0,     0,    21,    22,    23,    24,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    26
};

static const yytype_int16 yycheck[] =
{
       3,     4,    34,   207,    37,   214,     8,   258,    33,    62,
       3,     4,     5,     6,     7,     9,    69,     7,    43,     7,
      13,    14,     7,    26,    34,    18,   308,     9,    21,   387,
       8,   104,     9,     9,    37,    13,    14,    15,    16,    17,
      11,     7,    74,     7,    54,     4,    79,   405,    73,     7,
       7,    79,    80,     9,    48,     7,    81,    50,    51,   268,
      62,    51,   344,    51,    57,    58,    59,    60,    61,   317,
       7,    53,     3,     4,    51,     9,    79,    53,    63,    64,
      73,    52,     8,    86,    62,    51,    71,    72,    73,    15,
      16,    17,     9,    51,    51,    51,   149,   150,   346,    63,
      64,     7,    95,   136,   107,   108,    37,    71,    72,     9,
      74,    63,    64,     9,   403,     9,     9,    51,     9,    71,
      72,   369,    11,   126,     9,   373,    90,     9,     9,     9,
      55,   379,     7,   136,    51,    54,    62,     9,     9,    48,
      48,     9,     9,    49,     7,   434,    54,     7,    79,    79,
      80,    51,     7,    49,     7,    86,     8,    51,    51,    48,
      51,    13,    14,    15,    16,    17,    51,    19,    20,    51,
      51,    51,    24,    25,    26,    27,   107,   108,     9,    51,
      51,   206,   433,    51,    51,   436,   437,   438,   439,   440,
       9,   442,   443,   225,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   136,   488,   458,   233,     9,
      62,     9,     9,     9,     9,     9,     9,     9,    57,    58,
      51,     9,    68,    69,    70,     9,    50,   230,    62,    10,
      34,   234,    51,    50,    10,    85,   518,    89,     7,   490,
     522,    50,     7,    50,   276,   527,   278,    52,   530,    10,
      75,    51,    48,    51,    51,   258,    51,    51,    51,    51,
     542,   264,   265,    51,    48,    50,   548,    48,   550,   551,
     552,   553,    48,   555,   556,    50,   558,   559,   560,   561,
     562,   563,   564,   565,   566,   567,   568,    48,   570,     7,
      50,   573,   314,    63,   316,    65,    66,    67,    50,   230,
      50,    50,    50,   234,    50,    50,    76,   310,    50,    50,
      50,   314,    50,   316,   596,    50,    50,     3,     4,     5,
       6,     7,    50,   345,    50,    50,    50,    13,    14,    50,
     362,    50,    18,   264,   265,    21,    66,     7,     7,    49,
     544,    52,   345,    51,    51,    48,   378,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    75,     7,
     363,     7,     7,     7,    50,    51,    51,    49,    10,   372,
      75,    57,    58,    59,    60,    61,    49,    49,    49,   310,
       7,    49,    49,   314,    50,   316,   389,    73,    50,    50,
      50,    50,   395,    50,    50,    50,    50,    50,    50,     8,
      50,    50,     7,    50,    13,    14,    15,    16,    17,    95,
      19,    20,    50,    50,   345,    24,    25,    26,    27,    50,
      50,    30,    31,    32,    33,    50,    50,    50,    54,    50,
     433,    51,   363,   436,   437,   438,   439,   440,    47,   442,
     443,   372,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,    62,    51,   458,    54,    10,   389,    50,
       8,    75,    75,    75,   395,    13,    14,    15,    16,    17,
       4,    19,    20,    75,    22,    23,    24,    25,    26,    27,
      89,    75,    30,    31,    32,    33,    75,   490,    75,   492,
      75,    75,    75,    75,   497,    75,    75,   500,    75,    47,
      48,    75,    75,    75,    75,    75,    54,    75,    75,   512,
      75,    75,    50,    75,    62,    75,   273,   218,   521,   216,
     523,   524,   525,   526,     5,   528,   529,   367,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,     7,
     543,    89,   355,   546,   389,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
     489,   492,    30,    31,    32,    33,   497,     8,   226,   500,
     139,   574,    13,    14,    15,    16,    17,    -1,    -1,    47,
      -1,   512,    -1,    24,    25,    26,    27,    -1,    -1,    -1,
     521,    -1,   523,   524,   525,   526,    -1,   528,   529,    -1,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   540,
     541,    -1,   543,    -1,    -1,   546,    15,    16,    17,    18,
      19,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    30,    31,    -1,    -1,    -1,    35,    36,    -1,    -1,
      -1,    -1,    -1,   574,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    -1,    -1,    -1,    24,    25,    26,    27,    -1,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,    47,    -1,
      -1,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,    62,    -1,   124,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    13,    14,    -1,    -1,
      -1,    18,    -1,   142,    21,   144,    -1,     8,    -1,    10,
      89,    -1,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    50,    51,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    -1,    -1,    73,    -1,    -1,    -1,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,   207,     0,
      -1,    -1,     3,     4,     5,     6,     7,    -1,    95,    -1,
      -1,    -1,    13,    14,    -1,   224,    -1,    18,    89,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   238,
     239,   240,   241,   242,    -1,   244,   245,    -1,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,    50,
     259,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    -1,    76,    77,    78,    -1,    -1,
      81,    82,    83,    84,    -1,    86,    87,    88,     1,    -1,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,
      13,    14,    -1,    -1,    -1,    18,    -1,    -1,    21,    -1,
      -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    -1,    19,    20,    -1,    -1,    -1,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    50,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    -1,    76,    77,    78,    62,    -1,    81,    82,
      83,    84,    -1,    86,    87,    88,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    13,    14,    -1,    -1,
      -1,    18,    -1,    89,    21,    -1,    -1,    -1,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    -1,    -1,    -1,    24,    25,    26,    27,    -1,    -1,
      30,    -1,    32,    50,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    76,
      77,    78,    62,    -1,    81,    82,    83,    84,    -1,    86,
      87,    88,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    13,    14,    -1,    -1,    -1,    18,    -1,    89,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    49,    50,
      -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      61,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    -1,    -1,   544,    77,    78,    -1,    -1,
      81,    82,    83,    84,    -1,    86,    87,    88,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,
      -1,    -1,    -1,    18,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    50,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,
      -1,    -1,    77,    78,    -1,    -1,    81,    82,    83,    84,
      -1,    86,    87,    88,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    -1,    13,    14,    -1,    -1,    -1,    18,
      -1,    -1,    21,    -1,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    13,    14,    15,    16,    17,    -1,    19,    20,    -1,
      -1,    -1,    24,    25,    26,    27,    -1,    -1,    -1,    -1,
      32,    50,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    -1,    -1,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    -1,    -1,    -1,    77,    78,
      62,    -1,    81,    82,    83,    84,     8,    86,    87,    88,
      -1,    13,    14,    15,    16,    17,    -1,    19,    20,    -1,
      22,    23,    24,    25,    26,    27,    -1,    89,    30,    31,
      32,    33,     8,    -1,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    -1,    19,    20,    47,    22,    23,    24,    25,
      26,    27,    54,    -1,    30,    31,    32,    33,    -1,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     8,    -1,    -1,    62,    89,    13,    14,
      15,    16,    17,    -1,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    62,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    89,    -1,    -1,    -1,     8,    -1,
      54,    -1,    -1,    13,    14,    15,    16,    17,    62,    19,
      20,    -1,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    47,    -1,     8,
      -1,    51,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    62,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    89,
       8,    -1,    51,    -1,    -1,    13,    14,    15,    16,    17,
      -1,    19,    20,    62,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      89,     8,    -1,    51,    -1,    -1,    13,    14,    15,    16,
      17,    -1,    19,    20,    62,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    89,     8,    -1,    51,    -1,    -1,    13,    14,    15,
      16,    17,    -1,    19,    20,    62,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    89,     8,    -1,    51,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    62,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    89,     8,    -1,    51,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    62,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    89,     8,    -1,    51,    -1,    -1,
      13,    14,    15,    16,    17,    -1,    19,    20,    62,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    89,     8,    -1,    51,    -1,
      -1,    13,    14,    15,    16,    17,    -1,    19,    20,    62,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    89,     8,    -1,    51,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    19,    20,
      62,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    89,     8,    -1,
      51,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    62,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    89,     8,
      -1,    51,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    62,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    89,
       8,    -1,    51,    -1,    -1,    13,    14,    15,    16,    17,
      -1,    19,    20,    62,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      89,     8,    -1,    51,    -1,    -1,    13,    14,    15,    16,
      17,    -1,    19,    20,    62,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    89,     8,    -1,    51,    -1,    -1,    13,    14,    15,
      16,    17,    -1,    19,    20,    62,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    89,     8,    -1,    51,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    62,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    89,     8,    -1,    51,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    62,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    89,     8,    -1,    51,    -1,    -1,
      13,    14,    15,    16,    17,    -1,    19,    20,    62,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    89,     8,    -1,    51,    -1,
      -1,    13,    14,    15,    16,    17,    -1,    19,    20,    62,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    47,    89,    13,    14,    -1,
      -1,    -1,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      62,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      -1,    13,    14,    -1,    -1,    -1,    18,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    50,    51,    -1,    89,    -1,    -1,
      -1,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    55,   106,   107,   115,   116,   104,     4,     0,
       3,     4,     5,     6,     7,    13,    14,    18,    21,    50,
      56,    57,    58,    59,    60,    61,    73,    74,    76,    77,
      78,    81,    82,    83,    84,    86,    87,    88,   108,   109,
     134,   146,   147,   148,   149,   150,   151,   153,   154,   155,
     156,   157,   160,   161,   162,   163,   164,   165,   168,   169,
     108,   116,   147,   148,   148,   148,   148,   148,     7,   147,
       7,     7,   114,   148,   148,   148,    54,   172,   172,    48,
     170,   148,   148,   153,     7,    11,    52,   144,     8,    13,
      14,    15,    16,    17,    19,    20,    22,    23,    24,    25,
      26,    27,    30,    31,    32,    33,    47,    62,    89,   172,
      50,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,   144,    51,    34,   144,    50,    11,    48,   110,
     172,   170,    54,   170,   171,    49,   152,   153,    85,   166,
     167,   172,    10,    54,    34,    54,     7,   145,   146,   147,
       7,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    30,    31,    32,    33,
      47,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   146,
     146,    51,    95,   143,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,    50,    51,   142,
     146,     7,    63,    65,    66,    67,    76,   111,   112,   113,
     121,   122,   123,   124,    79,    80,   158,   159,    49,   153,
      50,   167,   148,   148,     9,    53,   144,   144,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,     9,
      51,   172,    51,   143,    75,     9,    51,     7,    66,     7,
     117,   117,     7,   114,   111,    49,   148,   170,    80,   159,
     146,    54,   172,   146,   148,    51,   148,   148,   148,   148,
      51,   148,   148,    51,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   142,   148,    51,   146,   146,
      75,   117,    52,   118,    10,    48,    10,    48,    48,   110,
     170,   170,     7,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,   171,     7,   146,    10,    48,     7,   119,   120,
     145,    68,    69,    70,   125,   126,   127,   140,   145,   125,
       7,   141,    51,    75,   171,   145,   125,     9,    53,    48,
      49,   127,    10,    48,    49,     9,    49,   170,   146,    48,
      49,   120,   125,    63,    64,    71,    72,    74,    90,   128,
     129,   130,   135,   136,   137,   139,   146,   125,     7,    49,
     170,   125,    49,     7,    73,   138,   139,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    30,    31,    32,    33,    47,   129,   146,     7,
      49,    49,   118,    50,     7,   139,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,     7,    54,    50,    51,
     142,   118,   142,    51,   142,   142,   142,   142,    51,   142,
     142,    51,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,    54,    51,   142,    10,   131,   133,    51,
      50,    51,    75,    51,    51,    51,    51,    75,    51,    51,
      75,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    75,    51,    57,    58,   132,   171,   133,    51,
     142,    75,   146,    75,    75,    75,    75,   146,    75,    75,
     146,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,   146,    75,    50,   171,    75,    51,   146,   171,
     146,   146,   146,   146,   171,   146,   146,   171,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   171,
     146,    51,   143,   146,    75,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,    51,   171,   146,   171
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 145 "beacon.y"
    {
		yyclearin;
	;}
    break;

  case 6:
#line 153 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 7:
#line 159 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 8:
#line 163 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 9:
#line 167 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 10:
#line 173 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 11:
#line 180 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value)
	;}
    break;

  case 12:
#line 187 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 17:
#line 198 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 18:
#line 202 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 19:
#line 209 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 21:
#line 217 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 22:
#line 221 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 24:
#line 229 "beacon.y"
    {
		(yyval.ast_value) = ast_new_import_decl_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 25:
#line 236 "beacon.y"
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 26:
#line 243 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameterized_typename((yyvsp[(1) - (2)].string_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 27:
#line 250 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 28:
#line 254 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 29:
#line 261 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 30:
#line 265 "beacon.y"
    {
		(yyval.ast_value) = ast_new_type_parameter_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 31:
#line 272 "beacon.y"
    {
		(yyval.ast_value) = ast_new_type_parameter((yyvsp[(1) - (1)].string_value), ast_new_blank());
	;}
    break;

  case 32:
#line 278 "beacon.y"
    {
		(yyval.ast_value) = ast_new_abstract_class_decl((yyvsp[(3) - (6)].ast_value), ast_new_blank(), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 33:
#line 282 "beacon.y"
    {
		(yyval.ast_value) = ast_new_abstract_class_decl((yyvsp[(3) - (8)].ast_value), (yyvsp[(5) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 34:
#line 288 "beacon.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 35:
#line 292 "beacon.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 36:
#line 299 "beacon.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 37:
#line 303 "beacon.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (6)].string_value), (yyvsp[(4) - (6)].ast_value));
	;}
    break;

  case 38:
#line 310 "beacon.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 39:
#line 314 "beacon.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 40:
#line 321 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 43:
#line 330 "beacon.y"
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 44:
#line 337 "beacon.y"
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[(1) - (3)].access_level_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 45:
#line 344 "beacon.y"
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 46:
#line 348 "beacon.y"
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[(1) - (2)].ast_value), ast_new_member_decl((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 51:
#line 362 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 52:
#line 366 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 53:
#line 373 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (5)].chain_type_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 54:
#line 377 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (4)].chain_type_value), ast_new_blank());
	;}
    break;

  case 55:
#line 384 "beacon.y"
    {
		(yyval.chain_type_value) = chain_type_super;
	;}
    break;

  case 56:
#line 388 "beacon.y"
    {
		(yyval.chain_type_value) = chain_type_this;
	;}
    break;

  case 57:
#line 395 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 59:
#line 403 "beacon.y"
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[(2) - (8)].string_value), (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 60:
#line 407 "beacon.y"
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[(2) - (7)].string_value), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 61:
#line 414 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl((yyvsp[(2) - (10)].ast_value), (yyvsp[(3) - (10)].string_value), (yyvsp[(4) - (10)].ast_value), (yyvsp[(6) - (10)].ast_value), (yyvsp[(10) - (10)].ast_value), (yyvsp[(9) - (10)].ast_value));
	;}
    break;

  case 62:
#line 418 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[(2) - (9)].ast_value), (yyvsp[(3) - (9)].string_value), (yyvsp[(4) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 63:
#line 422 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl(ast_new_modifier(modifier_none), (yyvsp[(2) - (9)].string_value), (yyvsp[(3) - (9)].ast_value), (yyvsp[(5) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 64:
#line 426 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params(ast_new_modifier(modifier_none), (yyvsp[(2) - (8)].string_value), (yyvsp[(3) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 65:
#line 433 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_add, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 66:
#line 437 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_sub, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 67:
#line 441 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_mul, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 68:
#line 445 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_div, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 69:
#line 449 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_mod, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 70:
#line 453 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_gt, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 71:
#line 457 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_ge, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 72:
#line 461 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_lt, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 73:
#line 465 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_le, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 74:
#line 470 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_eq, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 75:
#line 474 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_noteq, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 76:
#line 479 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_bit_or, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 77:
#line 483 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_bit_and, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 78:
#line 488 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_logic_or, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 79:
#line 492 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_logic_and, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 80:
#line 497 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_lshift, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 81:
#line 501 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_rshift, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 82:
#line 506 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_excor, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 83:
#line 511 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_not, ast_new_blank(), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 84:
#line 516 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_childa, ast_new_blank(), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 85:
#line 520 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_negative, ast_new_blank(), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 86:
#line 527 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[(1) - (4)].ast_value), (yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].string_value));
	;}
    break;

  case 87:
#line 531 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_decl(ast_new_modifier(modifier_none), (yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].string_value));
	;}
    break;

  case 88:
#line 538 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 89:
#line 542 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 90:
#line 549 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_static);
	;}
    break;

  case 91:
#line 553 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_native);
	;}
    break;

  case 92:
#line 557 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_abstract);
	;}
    break;

  case 93:
#line 561 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_override);
	;}
    break;

  case 94:
#line 568 "beacon.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 95:
#line 572 "beacon.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 96:
#line 576 "beacon.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 97:
#line 583 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 98:
#line 587 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[(3) - (3)].string_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 99:
#line 594 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].string_value));
	;}
    break;

  case 100:
#line 598 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].string_value), (yyvsp[(1) - (4)].ast_value))
	;}
    break;

  case 101:
#line 605 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 102:
#line 609 "beacon.y"
    {
		(yyval.ast_value) = ast_new_lambda((yyvsp[(3) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 103:
#line 613 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(3) - (3)].ast_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 104:
#line 620 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 105:
#line 624 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 106:
#line 631 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 107:
#line 635 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 108:
#line 642 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 109:
#line 649 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 110:
#line 653 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(3) - (3)].string_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 111:
#line 662 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 114:
#line 670 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_pos, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 115:
#line 674 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_neg, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 116:
#line 678 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 117:
#line 682 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 118:
#line 686 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 119:
#line 690 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 120:
#line 694 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 121:
#line 698 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 122:
#line 702 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_equal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 123:
#line 706 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_notequal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 124:
#line 710 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 125:
#line 714 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 126:
#line 718 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 127:
#line 722 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 128:
#line 726 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 129:
#line 730 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 130:
#line 734 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 131:
#line 738 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 132:
#line 742 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 133:
#line 746 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 134:
#line 750 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_and_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 135:
#line 754 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 136:
#line 758 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 137:
#line 762 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 138:
#line 766 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 139:
#line 770 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_gt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 140:
#line 774 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_ge, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 141:
#line 778 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 142:
#line 782 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_le, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 143:
#line 786 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 144:
#line 790 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 145:
#line 794 "beacon.y"
    {
		(yyval.ast_value) = ast_new_instanceof((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 146:
#line 798 "beacon.y"
    {
		(yyval.ast_value) = ast_new_as((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 147:
#line 802 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_childa, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 148:
#line 806 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_not, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 149:
#line 810 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 150:
#line 814 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 151:
#line 818 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 152:
#line 822 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), ast_new_blank());
	;}
    break;

  case 153:
#line 826 "beacon.y"
    {
		(yyval.ast_value) = ast_new_this();
	;}
    break;

  case 154:
#line 830 "beacon.y"
    {
		(yyval.ast_value) = ast_new_super();
	;}
    break;

  case 156:
#line 837 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 157:
#line 841 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].string_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 158:
#line 845 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_add, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 159:
#line 849 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_sub, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 160:
#line 853 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_mul, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 161:
#line 857 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_div, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 162:
#line 861 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_mod, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 163:
#line 865 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_gt, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 164:
#line 869 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_ge, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 165:
#line 873 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_lt, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 166:
#line 877 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_le, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 167:
#line 881 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_eq, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 168:
#line 885 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_noteq, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 169:
#line 889 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_bit_or, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 170:
#line 893 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_bit_and, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 171:
#line 897 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_logic_or, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 172:
#line 901 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_logic_and, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 173:
#line 905 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_lshift, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 174:
#line 909 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_rshift, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 175:
#line 913 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_excor, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 176:
#line 917 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_not);
	;}
    break;

  case 177:
#line 921 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_childa);
	;}
    break;

  case 178:
#line 925 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_negative);
	;}
    break;

  case 183:
#line 935 "beacon.y"
    {
		(yyval.ast_value) = ast_new_true();
	;}
    break;

  case 184:
#line 939 "beacon.y"
    {
		(yyval.ast_value) = ast_new_false();
	;}
    break;

  case 185:
#line 943 "beacon.y"
    {
		(yyval.ast_value) = ast_new_null();
	;}
    break;

  case 186:
#line 952 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 187:
#line 956 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 188:
#line 962 "beacon.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 201:
#line 980 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].string_value));
	;}
    break;

  case 202:
#line 986 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 203:
#line 992 "beacon.y"
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 204:
#line 998 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 205:
#line 1002 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 206:
#line 1006 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 207:
#line 1010 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 209:
#line 1017 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 210:
#line 1023 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 211:
#line 1029 "beacon.y"
    {
		(yyval.ast_value) = ast_new_while((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 212:
#line 1035 "beacon.y"
    {
		(yyval.ast_value) = ast_new_break();
	;}
    break;

  case 213:
#line 1041 "beacon.y"
    {
		(yyval.ast_value) = ast_new_continue();
	;}
    break;

  case 214:
#line 1047 "beacon.y"
    {
		(yyval.ast_value) = ast_new_return((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 215:
#line 1053 "beacon.y"
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 216:
#line 1059 "beacon.y"
    {
		(yyval.ast_value) = ast_new_try((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 217:
#line 1065 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 218:
#line 1069 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 219:
#line 1075 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].string_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 220:
#line 1081 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (5)].ast_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 221:
#line 1085 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 222:
#line 1091 "beacon.y"
    {
		(yyval.ast_value) = ast_new_defer((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 223:
#line 1098 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 224:
#line 1102 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 225:
#line 1108 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3766 "beacon.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1116 "beacon.y"





