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
#include "../util/string_pool.h"

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
#line 17 "beacon.y"
{
	char char_value;
	string_view stringv_value;
	ast* ast_value;
	assign_operator_type assign_otype_value;
	constructor_chain_type chain_type_value;
	access_level access_level_value;
}
/* Line 193 of yacc.c.  */
#line 336 "beacon.tab.c"
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
#line 361 "beacon.tab.c"

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
#define YYLAST   2422

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  110
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  244
/* YYNRULES -- Number of states.  */
#define YYNSTATES  637

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   362

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     109,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     104,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      95,    96,    97,    98,    99,   100,   101,   102,   103,   105,
     106,   107,   108
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
     159,   161,   163,   171,   178,   184,   189,   191,   193,   194,
     196,   205,   213,   224,   234,   244,   253,   262,   271,   280,
     289,   298,   307,   316,   325,   334,   343,   352,   361,   370,
     379,   388,   397,   406,   415,   423,   431,   439,   444,   448,
     451,   454,   458,   462,   465,   468,   472,   476,   485,   493,
     495,   498,   500,   502,   504,   506,   508,   510,   512,   514,
     516,   520,   523,   528,   530,   538,   542,   543,   547,   549,
     553,   556,   558,   562,   566,   568,   570,   573,   576,   580,
     584,   588,   592,   596,   600,   604,   608,   612,   616,   620,
     624,   628,   632,   636,   640,   644,   648,   652,   656,   660,
     664,   668,   672,   676,   680,   684,   688,   692,   696,   700,
     703,   706,   711,   715,   722,   728,   730,   732,   734,   737,
     742,   749,   756,   763,   770,   777,   784,   791,   798,   805,
     812,   819,   826,   833,   840,   847,   854,   861,   868,   874,
     880,   886,   888,   890,   892,   894,   896,   898,   900,   902,
     905,   908,   910,   912,   914,   916,   918,   920,   922,   924,
     926,   928,   930,   932,   934,   936,   940,   946,   952,   956,
     962,   967,   974,   976,   979,   983,   987,   990,   993,   997,
    1000,  1004,  1008,  1010,  1013,  1020,  1026,  1030,  1033,  1038,
    1042,  1046,  1049,  1051,  1053
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     111,     0,    -1,   112,   113,    -1,   111,   113,    -1,     1,
     109,    -1,    -1,   120,    -1,   161,    -1,   114,    -1,   139,
      -1,    80,   119,   115,    -1,    49,   118,    50,    -1,    80,
     119,   115,    -1,   126,    -1,   127,    -1,   129,    -1,   128,
      -1,   116,    -1,   117,   116,    -1,    -1,   117,    -1,     7,
      -1,   119,    11,     7,    -1,   121,    -1,   120,   121,    -1,
      56,     4,    -1,     7,   123,    -1,    -1,    53,   124,    54,
      -1,   125,    -1,   124,     9,   125,    -1,     7,    -1,    67,
      70,   122,    49,   130,    50,    -1,    67,    70,   122,    10,
     153,    49,   130,    50,    -1,    70,   122,    49,   130,    50,
      -1,    70,   122,    10,   153,    49,   130,    50,    -1,    71,
       7,    49,   149,    50,    -1,    71,     7,    49,   149,     9,
      50,    -1,    69,   122,    49,   130,    50,    -1,    69,   122,
      10,   153,    49,   130,    50,    -1,    -1,   131,    -1,   132,
      -1,   131,   132,    -1,   148,    10,   133,    -1,   134,    -1,
     133,   134,    -1,   135,    -1,   140,    -1,   141,    -1,   142,
      -1,   145,    -1,    78,    77,    51,   150,    52,   138,   181,
      -1,    78,    77,    51,    52,   138,   181,    -1,    10,   137,
      51,   151,    52,    -1,    10,   137,    51,    52,    -1,    62,
      -1,    61,    -1,    -1,   136,    -1,    78,     7,    51,   150,
      52,    79,   154,   181,    -1,    78,     7,    51,    52,    79,
     154,   181,    -1,    78,   146,     7,   123,    51,   150,    52,
      79,   154,   181,    -1,    78,   146,     7,   123,    51,    52,
      79,   154,   181,    -1,    78,     7,   123,    51,   150,    52,
      79,   154,   181,    -1,    78,     7,   123,    51,    52,    79,
     154,   181,    -1,    95,    13,    51,   150,    52,    79,   154,
     181,    -1,    95,    14,    51,   150,    52,    79,   154,   181,
      -1,    95,    15,    51,   150,    52,    79,   154,   181,    -1,
      95,    16,    51,   150,    52,    79,   154,   181,    -1,    95,
      17,    51,   150,    52,    79,   154,   181,    -1,    95,    24,
      51,   150,    52,    79,   154,   181,    -1,    95,    25,    51,
     150,    52,    79,   154,   181,    -1,    95,    26,    51,   150,
      52,    79,   154,   181,    -1,    95,    27,    51,   150,    52,
      79,   154,   181,    -1,    95,    22,    51,   150,    52,    79,
     154,   181,    -1,    95,    23,    51,   150,    52,    79,   154,
     181,    -1,    95,    32,    51,   150,    52,    79,   154,   181,
      -1,    95,    30,    51,   150,    52,    79,   154,   181,    -1,
      95,    33,    51,   150,    52,    79,   154,   181,    -1,    95,
      31,    51,   150,    52,    79,   154,   181,    -1,    95,    19,
      51,   150,    52,    79,   154,   181,    -1,    95,    20,    51,
     150,    52,    79,   154,   181,    -1,    95,    48,    51,   150,
      52,    79,   154,   181,    -1,    95,    18,    51,    52,    79,
     154,   181,    -1,    95,    21,    51,    52,    79,   154,   181,
      -1,    95,    14,    51,    52,    79,   154,   181,    -1,   146,
     154,     7,    55,    -1,   154,     7,    55,    -1,    59,    55,
      -1,    59,   180,    -1,   148,    59,    55,    -1,   148,    59,
     180,    -1,    60,    55,    -1,    60,   180,    -1,   148,    60,
      55,    -1,   148,    60,   180,    -1,    58,   146,   154,     7,
      49,   143,   144,    50,    -1,    58,   154,     7,    49,   143,
     144,    50,    -1,   147,    -1,   146,   147,    -1,    75,    -1,
      76,    -1,    67,    -1,    68,    -1,    34,    -1,    72,    -1,
      73,    -1,    74,    -1,     7,    -1,   149,     9,     7,    -1,
     154,     7,    -1,   150,     9,   154,     7,    -1,   156,    -1,
     100,    51,   150,    52,    79,   154,   180,    -1,   151,     9,
     156,    -1,    -1,    53,   153,    54,    -1,   154,    -1,   153,
       9,   154,    -1,   155,   152,    -1,     7,    -1,   155,    11,
       7,    -1,    51,   156,    52,    -1,   159,    -1,   157,    -1,
      13,   156,    -1,    14,   156,    -1,   156,    13,   156,    -1,
     156,    14,   156,    -1,   156,    15,   156,    -1,   156,    16,
     156,    -1,   156,    17,   156,    -1,   156,    32,   156,    -1,
     156,    22,   156,    -1,   156,    23,   156,    -1,   156,    30,
     156,    -1,   156,    48,   156,    -1,   156,    33,   156,    -1,
     156,    31,   156,    -1,   158,    35,   156,    -1,   158,    36,
     156,    -1,   158,    37,   156,    -1,   158,    38,   156,    -1,
     158,    39,   156,    -1,   158,    40,   156,    -1,   158,    41,
     156,    -1,   158,    42,   156,    -1,   158,    45,   156,    -1,
     158,    43,   156,    -1,   158,    44,   156,    -1,   156,    24,
     156,    -1,   156,    25,   156,    -1,   156,    26,   156,    -1,
     156,    27,   156,    -1,   156,    19,   156,    -1,   156,    20,
     156,    -1,   156,    94,   154,    -1,   156,    66,   154,    -1,
      21,   156,    -1,    18,   156,    -1,   157,    51,   151,    52,
      -1,   157,    51,    52,    -1,    77,   155,   152,    51,   151,
      52,    -1,    77,   155,   152,    51,    52,    -1,    61,    -1,
      62,    -1,   158,    -1,   155,   152,    -1,   156,     8,     7,
     152,    -1,   156,     8,    13,    51,   156,    52,    -1,   156,
       8,    14,    51,   156,    52,    -1,   156,     8,    15,    51,
     156,    52,    -1,   156,     8,    16,    51,   156,    52,    -1,
     156,     8,    17,    51,   156,    52,    -1,   156,     8,    24,
      51,   156,    52,    -1,   156,     8,    25,    51,   156,    52,
      -1,   156,     8,    26,    51,   156,    52,    -1,   156,     8,
      27,    51,   156,    52,    -1,   156,     8,    22,    51,   156,
      52,    -1,   156,     8,    23,    51,   156,    52,    -1,   156,
       8,    32,    51,   156,    52,    -1,   156,     8,    30,    51,
     156,    52,    -1,   156,     8,    33,    51,   156,    52,    -1,
     156,     8,    31,    51,   156,    52,    -1,   156,     8,    19,
      51,   156,    52,    -1,   156,     8,    20,    51,   156,    52,
      -1,   156,     8,    48,    51,   156,    52,    -1,   156,     8,
      18,    51,    52,    -1,   156,     8,    21,    51,    52,    -1,
     156,     8,    14,    51,    52,    -1,     5,    -1,     6,    -1,
       3,    -1,     4,    -1,    63,    -1,    64,    -1,    65,    -1,
     161,    -1,   160,   161,    -1,   156,   182,    -1,   162,    -1,
     163,    -1,   164,    -1,   165,    -1,   168,    -1,   169,    -1,
     170,    -1,   171,    -1,   172,    -1,   173,    -1,   176,    -1,
     177,    -1,   178,    -1,   179,    -1,   154,     7,    55,    -1,
     154,     7,    35,   156,   182,    -1,    57,     7,    35,   156,
     182,    -1,    83,   156,   180,    -1,    83,   156,   180,    85,
     180,    -1,    83,   156,   180,   166,    -1,    83,   156,   180,
     166,    85,   180,    -1,   167,    -1,   166,   167,    -1,    84,
     156,   180,    -1,    86,   156,   181,    -1,    87,   182,    -1,
      88,   182,    -1,    81,   156,   182,    -1,    81,   182,    -1,
      91,   156,   182,    -1,    89,   180,   174,    -1,   175,    -1,
     174,   175,    -1,    90,    51,   154,     7,    52,   180,    -1,
      92,   156,    10,   156,   182,    -1,    92,   156,   182,    -1,
      93,   161,    -1,    82,    81,   156,   182,    -1,    82,    87,
     182,    -1,    49,   160,    50,    -1,    49,    50,    -1,    55,
      -1,   180,    -1,    55,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   149,   149,   150,   151,   157,   159,   165,   169,   173,
     179,   186,   193,   197,   198,   199,   200,   204,   208,   216,
     219,   223,   227,   234,   235,   242,   249,   257,   260,   267,
     271,   278,   284,   288,   294,   298,   305,   309,   316,   320,
     328,   331,   335,   336,   343,   350,   354,   361,   362,   363,
     364,   365,   369,   373,   380,   384,   391,   395,   403,   406,
     410,   414,   421,   425,   429,   433,   440,   444,   448,   452,
     456,   460,   464,   468,   472,   477,   481,   486,   490,   495,
     499,   504,   508,   513,   518,   523,   527,   534,   538,   545,
     549,   553,   557,   564,   568,   572,   576,   583,   587,   594,
     598,   605,   609,   613,   617,   621,   628,   632,   636,   643,
     647,   654,   658,   665,   669,   673,   681,   684,   691,   695,
     702,   709,   713,   722,   726,   727,   730,   734,   738,   742,
     746,   750,   754,   758,   762,   766,   770,   774,   778,   782,
     786,   790,   794,   798,   802,   806,   810,   814,   818,   822,
     826,   830,   834,   838,   842,   846,   850,   854,   858,   862,
     866,   870,   874,   878,   882,   886,   890,   894,   897,   901,
     905,   909,   913,   917,   921,   925,   929,   933,   937,   941,
     945,   949,   953,   957,   961,   965,   969,   973,   977,   981,
     985,   991,   992,   993,   994,   995,   999,  1003,  1012,  1016,
    1022,  1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,
    1035,  1036,  1037,  1038,  1039,  1042,  1048,  1054,  1060,  1064,
    1068,  1072,  1078,  1079,  1085,  1091,  1097,  1103,  1109,  1113,
    1119,  1125,  1131,  1135,  1141,  1147,  1151,  1157,  1163,  1169,
    1175,  1179,  1185,  1189,  1192
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
  "LOGIC_AND", "BIT_OR", "LOGIC_OR", "FINAL", "ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "AND_ASSIGN",
  "OR_ASSIGN", "LSHIFT_ASSIGN", "RSHIFT_ASSIGN", "EXC_OR_ASSIGN", "INC",
  "DEC", "EXC_OR", "LCB", "RCB", "LRB", "RRB", "LSB", "RSB", "SEMI",
  "IMPORT", "VAR", "PROPERTY", "DEFSET", "DEFGET", "THIS_TOK", "SUPER_TOK",
  "TRUE_TOK", "FALSE_TOK", "NULL_TOK", "AS", "ABSTRACT", "OVERRIDE",
  "INTERFACE", "CLASS", "ENUM", "PUBLIC", "PRIVATE", "PROTECTED", "STATIC",
  "NATIVE", "NEW", "DEF", "ARROW", "NAMESPACE", "RETURN", "YIELD", "IF",
  "ELIF", "ELSE", "WHILE", "BREAK", "CONTINUE", "TRY", "CATCH", "THROW",
  "ASSERT_T", "DEFER", "INSTANCEOF", "OPERATOR", "BOUNDS_EXTENDS",
  "BOUNDS_SUPER", "PRE_DEC", "PRE_INC", "QUOTE", "POST_DEC", "POST_INC",
  "FUNCCALL", "'<'", "REF", "POSITIVE", "NEGATIVE", "FORM_TYPE", "'\\n'",
  "$accept", "compilation_unit", "init_decl", "body_decl",
  "namespace_decl", "namespace_body", "namespace_member_decl",
  "namespace_member_decl_list", "namespace_member_decl_optional",
  "namespace_path", "import_list", "import", "parameterized_typename",
  "type_parameter_group", "type_parameter_list", "type_parameter",
  "abstract_class_decl", "class_decl", "enum_decl", "interface_decl",
  "access_member_tree_opt", "access_member_tree", "access_member_list",
  "member_define_list", "member_define", "constructor_define",
  "constructor_chain", "constructor_chain_type_T",
  "constructor_chain_optional", "function_define", "method_define",
  "operator_define", "field_define", "prop_set", "prop_get", "prop_define",
  "modifier_type_T_list", "modifier_type_T", "access_level_T",
  "ident_list", "parameter_list", "argument_list", "typename_group",
  "typename_list", "typename_T", "fqcn_part", "expression",
  "expression_nobrace", "lhs", "primary", "stmt_list", "stmt",
  "variable_decl_stmt", "variable_init_stmt", "inferenced_type_init_stmt",
  "if_stmt", "elif_list", "elif", "while_stmt", "break_stmt",
  "continue_stmt", "return_stmt", "throw_stmt", "try_stmt",
  "catch_stmt_list", "catch_stmt", "assert_stmt", "defer_stmt",
  "yield_return_stmt", "yield_break_stmt", "scope", "scope_optional",
  "stmt_term", 0
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
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,    60,   359,   360,   361,   362,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   110,   111,   111,   111,   112,   112,   113,   113,   113,
     114,   115,   116,   116,   116,   116,   116,   117,   117,   118,
     118,   119,   119,   120,   120,   121,   122,   123,   123,   124,
     124,   125,   126,   126,   127,   127,   128,   128,   129,   129,
     130,   130,   131,   131,   132,   133,   133,   134,   134,   134,
     134,   134,   135,   135,   136,   136,   137,   137,   138,   138,
     139,   139,   140,   140,   140,   140,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   142,   142,   143,
     143,   143,   143,   144,   144,   144,   144,   145,   145,   146,
     146,   147,   147,   147,   147,   147,   148,   148,   148,   149,
     149,   150,   150,   151,   151,   151,   152,   152,   153,   153,
     154,   155,   155,   156,   156,   156,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   159,   159,   159,   159,   159,   159,   159,   160,   160,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   162,   163,   164,   165,   165,
     165,   165,   166,   166,   167,   168,   169,   170,   171,   171,
     172,   173,   174,   174,   175,   176,   176,   177,   178,   179,
     180,   180,   181,   181,   182
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     1,     1,     1,     1,
       3,     3,     3,     1,     1,     1,     1,     1,     2,     0,
       1,     1,     3,     1,     2,     2,     2,     0,     3,     1,
       3,     1,     6,     8,     5,     7,     5,     6,     5,     7,
       0,     1,     1,     2,     3,     1,     2,     1,     1,     1,
       1,     1,     7,     6,     5,     4,     1,     1,     0,     1,
       8,     7,    10,     9,     9,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     7,     7,     7,     4,     3,     2,
       2,     3,     3,     2,     2,     3,     3,     8,     7,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     4,     1,     7,     3,     0,     3,     1,     3,
       2,     1,     3,     3,     1,     1,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     4,     3,     6,     5,     1,     1,     1,     2,     4,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     5,     5,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     5,     5,     3,     5,
       4,     6,     1,     2,     3,     3,     2,     2,     3,     2,
       3,     3,     1,     2,     6,     5,     3,     2,     4,     3,
       3,     2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,    23,     4,    25,     1,
     193,   194,   191,   192,   121,     0,     0,     0,     0,     0,
       0,   165,   166,   195,   196,   197,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       8,     9,     0,   116,     0,   125,   167,   124,     7,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,     2,    24,   116,   126,   127,   160,   159,
       0,     0,   116,     0,    21,     0,   244,     0,   229,     0,
       0,     0,     0,   226,   227,     0,     0,     0,     0,   237,
       0,     0,     0,   168,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   200,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   168,   123,
       0,     0,     0,     0,    19,    10,   228,     0,   239,   218,
     242,   243,   225,   241,     0,   198,     0,   231,   232,   230,
       0,   236,     0,   215,   122,     0,   118,   116,   116,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   128,
     129,   130,   131,   132,   155,   156,   134,   135,   151,   152,
     153,   154,   136,   139,   133,   138,   137,   158,   157,   162,
       0,     0,   113,   140,   141,   142,   143,   144,   145,   146,
     147,   149,   150,   148,     0,     0,     0,     0,     0,    22,
       0,     0,     0,     0,     0,    17,    20,     0,    13,    14,
      16,    15,   238,     0,     0,   220,   222,   240,   199,     0,
     233,     0,     0,     0,   117,   120,   169,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   161,
     217,   164,     0,     0,     0,     0,   111,     0,    27,     0,
       0,     0,     0,    18,    11,     0,   219,     0,   223,     0,
     235,   216,   119,     0,   190,     0,     0,     0,     0,   188,
       0,     0,   189,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   163,     0,     0,     0,
       0,     0,    26,     0,    40,     0,    40,     0,    12,   224,
     221,     0,   170,   171,   172,   173,   174,   185,   186,   179,
     180,   175,   176,   177,   178,   182,   184,   181,   183,   187,
       0,    61,   112,     0,     0,    40,    31,     0,    29,     0,
     106,   107,   108,     0,    41,    42,     0,     0,     0,   109,
       0,     0,     0,    60,     0,     0,     0,    28,    40,    38,
      43,     0,    40,    34,     0,    36,   234,     0,    40,    32,
      30,     0,   105,     0,   103,   104,   101,   102,     0,     0,
      44,    45,    47,    48,    49,    50,    51,     0,    99,     0,
       0,   110,    37,   114,     0,    39,     0,     0,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    46,   100,     0,     0,    35,    33,     0,     0,     0,
       0,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    88,     0,     0,     0,    58,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    87,     0,     0,     0,     0,     0,     0,     0,    59,
       0,    58,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    89,    90,     0,     0,     0,
       0,     0,     0,    57,    56,     0,    53,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    93,    94,    98,     0,    91,    92,     0,     0,
       0,    52,     0,     0,     0,    86,     0,     0,     0,     0,
      84,     0,     0,    85,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    97,    95,    96,    65,     0,
      55,     0,     0,     0,    66,    67,    68,    69,    70,    81,
      82,    75,    76,    71,    72,    73,    74,    78,    80,    77,
      79,    83,    64,    54,    63,     0,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    39,    40,   135,   225,   226,   227,    75,
       5,     6,   279,   322,   357,   358,   228,   229,   230,   231,
     363,   364,   365,   400,   401,   402,   509,   545,   510,    41,
     403,   404,   405,   504,   538,   406,   407,   408,   366,   370,
     217,   201,    93,   155,   218,    65,    44,    45,    46,    47,
     144,    48,    49,    50,    51,    52,   235,   236,    53,    54,
      55,    56,    57,    58,   147,   148,    59,    60,    61,    62,
     141,   142,    78
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -368
static const yytype_int16 yypact[] =
{
     792,   -93,    23,   699,   883,    69,  -368,  -368,  -368,  -368,
    -368,  -368,  -368,  -368,  -368,  2309,  2309,  2309,  2309,  2309,
     179,  -368,  -368,  -368,  -368,  -368,   180,   210,   217,   519,
     154,  2309,  2309,   188,   188,   184,  2309,  2309,  1156,  -368,
    -368,  -368,   251,    -6,  1077,   208,   379,  -368,  -368,  -368,
    -368,  -368,  -368,  -368,  -368,  -368,  -368,  -368,  -368,  -368,
    -368,  -368,  -368,  -368,  -368,    -6,   196,   196,   196,   196,
    1275,   257,    -6,   260,  -368,    75,  -368,  1077,  -368,  2309,
     188,  1323,  1238,  -368,  -368,   974,   234,  1077,   986,  -368,
      67,   322,   180,   329,   893,  2309,  2309,  2309,  2309,  2309,
    2309,  2309,  2309,  2309,  2309,  2309,  2309,  2309,  2309,  2309,
    2309,  2309,  2309,   180,   180,  -368,    36,  2309,  2309,  2309,
    2309,  2309,  2309,  2309,  2309,  2309,  2309,  2309,  -368,  -368,
    2309,   274,     7,   330,   316,  -368,  -368,  1077,  -368,    43,
    -368,  -368,  -368,  -368,  1065,  -368,   295,   234,  -368,  -368,
    2309,  -368,  2309,  -368,  -368,     1,  -368,    -6,   324,   297,
     311,   331,   338,   340,   343,   347,   349,   351,   352,   357,
     358,   359,   382,   394,   420,   421,   424,   426,   427,     4,
       4,     3,     3,     3,   318,   318,  2196,  2196,   142,   142,
     142,   142,  2252,  2226,   811,  1184,   118,  -368,  -368,  -368,
     428,    13,  2170,  2170,  2170,  2170,  2170,  2170,  2170,  2170,
    2170,  2170,  2170,  2170,  1077,   102,   284,    21,   360,  -368,
     410,   474,   474,   475,   217,  -368,   316,   434,  -368,  -368,
    -368,  -368,  -368,  2309,   184,    91,  -368,  -368,  -368,   180,
    -368,  1077,  1077,   180,  -368,  -368,  -368,  2309,  2290,  2309,
    2309,  2309,   433,  2309,  2309,   435,  2309,  2309,  2309,  2309,
    2309,  2309,  2309,  2309,  2309,  2309,  2309,   180,  2309,  -368,
    -368,  -368,    87,   180,   180,   407,  -368,   474,   436,   120,
     172,   439,    75,  -368,  -368,  1323,  -368,   184,  -368,   484,
    -368,  -368,  -368,  1360,  -368,  1405,  1450,  1495,  1540,  -368,
    1585,  1630,  -368,  1675,  1720,  1765,  1810,  1855,  1900,  1945,
    1990,  2035,  2080,  2125,    95,  2170,  -368,   198,   486,   180,
     206,   487,  -368,   180,   333,   180,   333,   488,  -368,  -368,
    -368,   444,  -368,  -368,  -368,  -368,  -368,  -368,  -368,  -368,
    -368,  -368,  -368,  -368,  -368,  -368,  -368,  -368,  -368,  -368,
     418,  -368,  -368,   198,   180,   333,  -368,    20,  -368,    28,
    -368,  -368,  -368,   448,   333,  -368,   489,   202,   450,  -368,
      53,   184,   180,  -368,   298,   451,   487,  -368,   333,  -368,
    -368,     0,   333,  -368,     2,  -368,  -368,   184,   333,  -368,
    -368,   452,  -368,   170,  -368,  -368,  -368,  -368,    17,  2374,
       0,  -368,  -368,  -368,  -368,  -368,  -368,   170,  -368,   496,
     455,  -368,  -368,  -368,   456,  -368,   170,   501,   436,   459,
     193,   461,   462,   463,   464,   466,   467,   469,   470,   476,
     477,   478,   479,   480,   483,   485,   490,   492,   493,   494,
     495,  -368,  -368,   528,   498,  -368,  -368,   532,   499,   505,
      29,   436,   180,    31,   180,   180,   180,   516,   180,   180,
     517,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   518,  -368,   522,   299,    38,   562,   131,   524,
     140,   506,   151,   153,   182,   190,   507,   197,   204,   508,
     213,   214,   239,   241,   254,   300,   301,   303,   304,   305,
     308,  -368,   299,   310,   267,   529,   510,   309,    90,  -368,
     198,   562,    39,   512,   180,   513,   514,   515,   520,   180,
     521,   523,   180,   525,   526,   527,   530,   533,   534,   535,
     536,   537,   539,   540,   267,  -368,  -368,   321,   547,   541,
     325,   180,   542,  -368,  -368,   552,  -368,   198,   543,   312,
     180,   198,   180,   180,   180,   180,   198,   180,   180,   198,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   557,  -368,  -368,  -368,   326,  -368,  -368,   198,   180,
     167,  -368,   180,   544,   198,  -368,   198,   198,   198,   198,
    -368,   198,   198,  -368,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,  -368,  -368,  -368,  -368,   198,
    -368,   314,   198,   180,  -368,  -368,  -368,  -368,  -368,  -368,
    -368,  -368,  -368,  -368,  -368,  -368,  -368,  -368,  -368,  -368,
    -368,  -368,  -368,  -368,  -368,   198,  -368
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -368,  -368,  -368,   573,  -368,   296,   385,  -368,  -368,   384,
    -368,   615,  -214,  -179,  -368,   248,  -368,  -368,  -368,  -368,
    -322,  -368,   261,  -368,   227,  -368,  -368,  -368,   121,  -368,
    -368,  -368,  -368,   133,   114,  -368,  -367,   -28,  -356,  -368,
     207,  -212,   -40,  -310,    76,    -3,   178,  -368,  -368,  -368,
    -368,   -32,  -368,  -368,  -368,  -368,  -368,   414,  -368,  -368,
    -368,  -368,  -368,  -368,  -368,   503,  -368,  -368,  -368,  -368,
     -33,   137,   -16
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -121
static const yytype_int16 yytable[] =
{
      43,    43,    86,   272,   368,    91,    89,    14,   280,   411,
     243,    94,    94,   359,    14,   367,     7,    83,    84,    97,
      98,    99,   268,    72,   418,   128,   416,     8,   115,   376,
     274,   420,   131,   375,   392,    43,    14,   243,    14,    10,
      11,    12,    13,    14,   374,    14,    14,    92,   139,    15,
      16,   392,   412,   145,    17,   244,   391,    18,   393,   216,
     410,   136,   384,   320,   138,   269,   414,   394,   395,   113,
     113,   149,   151,   275,   377,   396,   397,   378,   398,    42,
      42,   477,    43,   481,   394,   395,   133,    19,   199,   157,
     506,   548,   396,   397,   419,   399,   268,    21,    22,    23,
      24,    25,   152,   385,   274,    10,    11,    12,    13,    14,
     157,   157,   238,    26,    42,    15,    16,   245,   246,   505,
      17,   232,   153,    18,   134,     2,    94,   233,   234,   157,
     323,    95,    96,    97,    98,    99,   200,   100,   101,   316,
     274,    43,   104,   105,   106,   107,   505,   350,   539,   274,
      94,   543,   544,    19,   271,    95,    96,    97,    98,    99,
     274,    42,   274,    21,    22,    23,    24,    25,   156,   324,
      10,    11,    12,    13,    14,   233,   287,    14,   539,    26,
      15,    16,   325,   511,   113,    17,    71,    14,    18,   197,
     198,   274,   513,    66,    67,    68,    69,    70,   270,   274,
     451,   286,   200,   515,   392,   516,   274,    77,   113,    81,
      82,   243,   114,   274,    87,    88,   354,    73,    19,   610,
      42,   326,   274,   274,    74,   290,   291,   392,    21,    22,
      23,    24,    25,    85,   517,    79,   157,   394,   395,   449,
     157,    80,   518,    76,    26,   396,   397,    85,   274,   520,
     274,   382,   329,   140,   330,   355,   521,   137,    90,   116,
     394,   395,   113,   274,   157,   523,   524,   200,   396,   397,
     157,   157,   479,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   525,   130,   526,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   527,   243,   214,   274,
     274,   132,   274,   274,   274,   289,   157,   274,   274,   292,
     157,   274,   157,   268,   146,   215,    94,   537,   241,   154,
     242,    95,    96,    97,    98,    99,  -120,   219,   386,   360,
     361,   362,   104,   105,   106,   107,   239,   388,   247,   317,
     318,   157,   528,   529,   413,   530,   531,   532,   503,    85,
     533,   542,   248,   273,   583,   535,   633,   276,   611,   157,
      85,   360,   361,   362,    85,    85,   572,    92,   157,   442,
     576,   606,   249,   220,   113,   221,   222,   223,   442,   250,
     157,   251,   442,   202,   252,   353,   224,   157,   253,   156,
     254,   156,   255,   256,   157,   360,   361,   362,   257,   258,
     259,   285,   114,   157,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   293,   295,   296,   297,   298,
     156,   300,   301,   260,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   261,   315,   157,   387,   157,
     157,   157,   157,   157,   351,   157,   157,   409,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   417,
     536,   262,   263,   157,   314,   264,   409,   265,   266,   267,
     277,   278,   281,   443,   284,   299,   319,   302,   327,   321,
     373,   331,   447,   352,   356,   369,   371,   372,   379,   381,
     383,   389,   415,   444,   573,   445,   446,   577,   448,   157,
     450,   157,   452,   453,   454,   455,   157,   456,   457,   157,
     458,   459,    10,    11,    12,    13,    14,   460,   461,   462,
     463,   464,    15,    16,   465,   472,   466,    17,   157,   474,
      18,   467,   607,   468,   469,   470,   471,   157,   475,   157,
     157,   157,   157,   473,   157,   157,   476,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   486,   489,
      19,   502,   508,   501,    76,   512,   157,    63,   328,   157,
      21,    22,    23,    24,    25,   514,   519,   522,   540,   541,
     551,   550,   552,   553,   554,   556,    26,   574,   559,   555,
     557,   575,   558,   580,   560,   561,   562,   605,   282,   563,
     157,   283,   564,   565,   566,   567,   568,   578,   569,   570,
      64,   579,   582,   613,   390,   380,   584,   441,   586,   587,
     588,   589,   547,   591,   592,   534,   594,   595,   596,   597,
     598,   599,   600,   601,   602,   603,   604,   546,   571,   288,
     240,     0,     0,     0,     0,   609,     0,   478,   612,   480,
     482,   483,   484,   485,     0,   487,   488,     0,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   499,   500,     0,
       0,     0,     0,   507,   581,     0,     0,     0,   585,   635,
       0,     0,     0,   590,     0,     0,   593,     0,     0,     9,
       0,     0,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,    15,    16,     0,   608,     0,    17,     0,   549,
      18,   614,     0,   615,   616,   617,   618,     0,   619,   620,
       0,   621,   622,   623,   624,   625,   626,   627,   628,   629,
     630,   631,     0,     0,     0,     0,   632,     0,     0,   634,
      19,     0,     0,     0,     0,     0,    20,     0,   202,     0,
      21,    22,    23,    24,    25,     0,     0,     0,     0,     0,
       0,     0,   636,     0,     0,     0,    26,    27,     0,    28,
      29,    30,    31,     0,     0,    32,    33,    34,    35,     0,
      36,    37,    38,     1,     0,    -5,    -5,    -5,    -5,    -5,
       0,     0,     0,     0,     0,    -5,    -5,     0,     0,     0,
      -5,     0,     0,    -5,     0,     0,     0,     0,     0,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,     0,
     100,   101,     0,     0,     0,   104,   105,   106,   107,     0,
       0,     0,     0,    -5,     0,     0,     0,     0,     2,    -5,
       0,     0,     0,    -5,    -5,    -5,    -5,    -5,     0,   112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    -5,
      -5,     0,    -5,    -5,    -5,    -5,     0,   113,    -5,    -5,
      -5,    -5,     0,    -5,    -5,    -5,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,    15,    16,     0,     0,
     158,    17,     0,     0,    18,   114,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,     0,     0,   174,   175,   176,   177,     0,     0,     0,
       0,     0,     0,     0,    19,     0,     0,     0,     0,     0,
      20,   178,     0,     0,    21,    22,    23,    24,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26,    27,     0,    28,    29,    30,    31,     0,     0,    32,
      33,    34,    35,     0,    36,    37,    38,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,    15,    16,     0,
       0,     0,    17,     0,    94,    18,   150,     0,     0,    95,
      96,    97,    98,    99,     0,   100,   101,     0,   102,   103,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,   143,    19,     0,     0,     0,     0,
       0,    20,     0,     0,   112,    21,    22,    23,    24,    25,
       0,    76,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    26,   113,     0,     0,    29,    30,    31,     0,     0,
      32,    33,    34,    35,     0,    36,    37,    38,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,    15,    16,
     114,     0,     0,    17,     0,    94,    18,     0,     0,     0,
      95,    96,    97,    98,    99,     0,   100,   101,     0,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,   237,    19,     0,     0,     0,
       0,     0,    20,     0,     0,   112,    21,    22,    23,    24,
      25,     0,    76,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    26,   113,     0,     0,    29,    30,    31,     0,
       0,    32,    33,    34,    35,     0,    36,    37,    38,    10,
      11,    12,    13,    14,     0,     0,     0,     0,     0,    15,
      16,   114,     0,     0,    17,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    94,     0,     0,     0,     0,    95,    96,    97,
      98,    99,     0,   100,   101,     0,     0,    19,   104,   105,
     106,   107,     0,    20,   108,   109,   110,    21,    22,    23,
      24,    25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   112,    26,     0,     0,     0,    29,    30,    31,
       0,     0,    32,    33,    34,    35,    94,    36,    37,    38,
     113,    95,    96,    97,    98,    99,     0,   100,   101,     0,
     102,   103,   104,   105,   106,   107,     0,     0,   108,   109,
     110,   111,     0,     0,     0,     0,     0,     0,   114,     0,
       0,     0,     0,    94,     0,     0,   112,    85,    95,    96,
      97,    98,    99,   140,   100,   101,     0,   102,   103,   104,
     105,   106,   107,     0,   113,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,     0,     0,     0,   129,     0,     0,
       0,    94,   114,     0,     0,     0,    95,    96,    97,    98,
      99,   113,   100,   101,     0,   102,   103,   104,   105,   106,
     107,     0,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,   114,
       0,   112,    85,    95,    96,    97,    98,    99,     0,   100,
     101,     0,   102,   103,   104,   105,   106,   107,     0,   113,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,     0,
       0,     0,   332,    94,     0,     0,     0,   114,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   333,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   334,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   335,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   336,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   337,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   338,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   339,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   340,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   341,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   342,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   343,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   344,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   345,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   346,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   347,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   348,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   349,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,    94,     0,     0,     0,     0,    95,
      96,    97,    98,    99,     0,   100,   101,     0,   112,   114,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,    94,     0,   113,     0,     0,    95,
      96,    97,    98,    99,   112,   100,   101,     0,     0,     0,
     104,   105,   106,   107,     0,     0,   108,     0,   110,     0,
      94,     0,   113,     0,   114,    95,    96,    97,    98,    99,
       0,   100,   101,     0,   112,     0,   104,   105,   106,   107,
       0,     0,     0,     0,   110,     0,     0,     0,     0,     0,
     114,     0,   113,    10,    11,    12,    13,    14,     0,     0,
     112,     0,     0,    15,    16,     0,     0,     0,    17,     0,
       0,    18,    10,    11,    12,    13,    14,     0,   113,     0,
     114,     0,    15,    16,     0,     0,     0,    17,     0,     0,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,   294,     0,     0,     0,   114,     0,     0,     0,
       0,    21,    22,    23,    24,    25,     0,     0,     0,     0,
      19,     0,     0,     0,     0,     0,     0,    26,     0,     0,
      21,    22,    23,    24,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,   421,   422,   423,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     434,   435,     0,     0,   436,   437,   438,   439,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   440
};

static const yytype_int16 yycheck[] =
{
       3,     4,    35,   215,   326,    11,    38,     7,   222,     7,
       9,     8,     8,   323,     7,   325,   109,    33,    34,    15,
      16,    17,     9,    26,     7,    65,   393,     4,    44,     9,
       9,   398,    72,   355,    34,    38,     7,     9,     7,     3,
       4,     5,     6,     7,   354,     7,     7,    53,    81,    13,
      14,    34,    50,    85,    18,    54,   378,    21,    58,    52,
     382,    77,     9,   277,    80,    52,   388,    67,    68,    66,
      66,    87,    88,    52,    54,    75,    76,    49,    78,     3,
       4,    52,    85,    52,    67,    68,    11,    51,    52,    92,
      52,    52,    75,    76,    77,    95,     9,    61,    62,    63,
      64,    65,    35,    50,     9,     3,     4,     5,     6,     7,
     113,   114,   144,    77,    38,    13,    14,   157,   158,   475,
      18,   137,    55,    21,    49,    56,     8,    84,    85,   132,
      10,    13,    14,    15,    16,    17,   100,    19,    20,    52,
       9,   144,    24,    25,    26,    27,   502,    52,   504,     9,
       8,    61,    62,    51,    52,    13,    14,    15,    16,    17,
       9,    85,     9,    61,    62,    63,    64,    65,    92,    49,
       3,     4,     5,     6,     7,    84,    85,     7,   534,    77,
      13,    14,    10,    52,    66,    18,     7,     7,    21,   113,
     114,     9,    52,    15,    16,    17,    18,    19,   214,     9,
       7,   234,   100,    52,    34,    52,     9,    29,    66,    31,
      32,     9,    94,     9,    36,    37,    10,     7,    51,    52,
     144,    49,     9,     9,     7,   241,   242,    34,    61,    62,
      63,    64,    65,    49,    52,    81,   239,    67,    68,   418,
     243,    87,    52,    55,    77,    75,    76,    49,     9,    52,
       9,    49,   285,    55,   287,    49,    52,    79,     7,    51,
      67,    68,    66,     9,   267,    52,    52,   100,    75,    76,
     273,   274,   451,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,    52,    35,    52,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    52,     9,   130,     9,
       9,    51,     9,     9,     9,   239,   319,     9,     9,   243,
     323,     9,   325,     9,    90,    51,     8,    60,   150,     7,
     152,    13,    14,    15,    16,    17,     7,     7,   371,    72,
      73,    74,    24,    25,    26,    27,    51,    49,    51,   273,
     274,   354,    52,    52,   387,    52,    52,    52,    59,    49,
      52,    52,    51,    79,    52,    55,    52,     7,   580,   372,
      49,    72,    73,    74,    49,    49,    55,    53,   381,   407,
      55,    55,    51,    67,    66,    69,    70,    71,   416,    51,
     393,    51,   420,   215,    51,   319,    80,   400,    51,   323,
      51,   325,    51,    51,   407,    72,    73,    74,    51,    51,
      51,   233,    94,   416,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,   247,   248,   249,   250,   251,
     354,   253,   254,    51,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,    51,   268,   450,   372,   452,
     453,   454,   455,   456,   317,   458,   459,   381,   461,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   393,
     503,    51,    51,   476,   267,    51,   400,    51,    51,    51,
      70,     7,     7,   407,    50,    52,    79,    52,    49,    53,
     353,     7,   416,     7,     7,     7,    52,    79,    50,    10,
      50,    50,    50,     7,   537,    50,    50,   540,     7,   512,
      51,   514,    51,    51,    51,    51,   519,    51,    51,   522,
      51,    51,     3,     4,     5,     6,     7,    51,    51,    51,
      51,    51,    13,    14,    51,     7,    51,    18,   541,     7,
      21,    51,   575,    51,    51,    51,    51,   550,    49,   552,
     553,   554,   555,    55,   557,   558,    51,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   569,   570,    52,    52,
      51,    49,    10,    55,    55,    51,   579,     4,   282,   582,
      61,    62,    63,    64,    65,    79,    79,    79,    59,    79,
     514,    79,    79,    79,    79,   519,    77,    50,   522,    79,
      79,    60,    79,    51,    79,    79,    79,    50,   224,    79,
     613,   226,    79,    79,    79,    79,    79,   541,    79,    79,
       5,    79,    79,    79,   376,   364,   550,   400,   552,   553,
     554,   555,   511,   557,   558,   502,   560,   561,   562,   563,
     564,   565,   566,   567,   568,   569,   570,   510,   534,   235,
     147,    -1,    -1,    -1,    -1,   579,    -1,   450,   582,   452,
     453,   454,   455,   456,    -1,   458,   459,    -1,   461,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   471,    -1,
      -1,    -1,    -1,   476,   547,    -1,    -1,    -1,   551,   613,
      -1,    -1,    -1,   556,    -1,    -1,   559,    -1,    -1,     0,
      -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    13,    14,    -1,   578,    -1,    18,    -1,   512,
      21,   584,    -1,   586,   587,   588,   589,    -1,   591,   592,
      -1,   594,   595,   596,   597,   598,   599,   600,   601,   602,
     603,   604,    -1,    -1,    -1,    -1,   609,    -1,    -1,   612,
      51,    -1,    -1,    -1,    -1,    -1,    57,    -1,   580,    -1,
      61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   635,    -1,    -1,    -1,    77,    78,    -1,    80,
      81,    82,    83,    -1,    -1,    86,    87,    88,    89,    -1,
      91,    92,    93,     1,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    -1,    -1,    13,    14,    -1,    -1,    -1,
      18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    -1,    -1,    -1,    24,    25,    26,    27,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    56,    57,
      -1,    -1,    -1,    61,    62,    63,    64,    65,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      78,    -1,    80,    81,    82,    83,    -1,    66,    86,    87,
      88,    89,    -1,    91,    92,    93,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    13,    14,    -1,    -1,
       7,    18,    -1,    -1,    21,    94,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      57,    48,    -1,    -1,    61,    62,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    78,    -1,    80,    81,    82,    83,    -1,    -1,    86,
      87,    88,    89,    -1,    91,    92,    93,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,    -1,
      -1,    -1,    18,    -1,     8,    21,    10,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,
      -1,    57,    -1,    -1,    48,    61,    62,    63,    64,    65,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    66,    -1,    -1,    81,    82,    83,    -1,    -1,
      86,    87,    88,    89,    -1,    91,    92,    93,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,
      94,    -1,    -1,    18,    -1,     8,    21,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    -1,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    50,    51,    -1,    -1,    -1,
      -1,    -1,    57,    -1,    -1,    48,    61,    62,    63,    64,
      65,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    66,    -1,    -1,    81,    82,    83,    -1,
      -1,    86,    87,    88,    89,    -1,    91,    92,    93,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,
      14,    94,    -1,    -1,    18,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    -1,    19,    20,    -1,    -1,    51,    24,    25,
      26,    27,    -1,    57,    30,    31,    32,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    77,    -1,    -1,    -1,    81,    82,    83,
      -1,    -1,    86,    87,    88,    89,     8,    91,    92,    93,
      66,    13,    14,    15,    16,    17,    -1,    19,    20,    -1,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,
      -1,    -1,    -1,     8,    -1,    -1,    48,    49,    13,    14,
      15,    16,    17,    55,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    66,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    52,    -1,    -1,
      -1,     8,    94,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    66,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    94,
      -1,    48,    49,    13,    14,    15,    16,    17,    -1,    19,
      20,    -1,    22,    23,    24,    25,    26,    27,    -1,    66,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    52,     8,    -1,    -1,    -1,    94,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    48,    94,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,     8,    -1,    66,    -1,    -1,    13,
      14,    15,    16,    17,    48,    19,    20,    -1,    -1,    -1,
      24,    25,    26,    27,    -1,    -1,    30,    -1,    32,    -1,
       8,    -1,    66,    -1,    94,    13,    14,    15,    16,    17,
      -1,    19,    20,    -1,    48,    -1,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      94,    -1,    66,     3,     4,     5,     6,     7,    -1,    -1,
      48,    -1,    -1,    13,    14,    -1,    -1,    -1,    18,    -1,
      -1,    21,     3,     4,     5,     6,     7,    -1,    66,    -1,
      94,    -1,    13,    14,    -1,    -1,    -1,    18,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    52,    -1,    -1,    -1,    94,    -1,    -1,    -1,
      -1,    61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    56,   111,   112,   120,   121,   109,     4,     0,
       3,     4,     5,     6,     7,    13,    14,    18,    21,    51,
      57,    61,    62,    63,    64,    65,    77,    78,    80,    81,
      82,    83,    86,    87,    88,    89,    91,    92,    93,   113,
     114,   139,   154,   155,   156,   157,   158,   159,   161,   162,
     163,   164,   165,   168,   169,   170,   171,   172,   173,   176,
     177,   178,   179,   113,   121,   155,   156,   156,   156,   156,
     156,     7,   155,     7,     7,   119,    55,   156,   182,    81,
      87,   156,   156,   182,   182,    49,   180,   156,   156,   161,
       7,    11,    53,   152,     8,    13,    14,    15,    16,    17,
      19,    20,    22,    23,    24,    25,    26,    27,    30,    31,
      32,    33,    48,    66,    94,   182,    51,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,   152,    52,
      35,   152,    51,    11,    49,   115,   182,   156,   182,   180,
      55,   180,   181,    50,   160,   161,    90,   174,   175,   182,
      10,   182,    35,    55,     7,   153,   154,   155,     7,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    30,    31,    32,    33,    48,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   154,   154,    52,
     100,   151,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,    51,    52,   150,   154,     7,
      67,    69,    70,    71,    80,   116,   117,   118,   126,   127,
     128,   129,   182,    84,    85,   166,   167,    50,   161,    51,
     175,   156,   156,     9,    54,   152,   152,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,     9,    52,
     182,    52,   151,    79,     9,    52,     7,    70,     7,   122,
     122,     7,   119,   116,    50,   156,   180,    85,   167,   154,
     182,   182,   154,   156,    52,   156,   156,   156,   156,    52,
     156,   156,    52,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   150,   156,    52,   154,   154,    79,
     122,    53,   123,    10,    49,    10,    49,    49,   115,   180,
     180,     7,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,   181,     7,   154,    10,    49,     7,   124,   125,   153,
      72,    73,    74,   130,   131,   132,   148,   153,   130,     7,
     149,    52,    79,   181,   153,   130,     9,    54,    49,    50,
     132,    10,    49,    50,     9,    50,   180,   154,    49,    50,
     125,   130,    34,    58,    67,    68,    75,    76,    78,    95,
     133,   134,   135,   140,   141,   142,   145,   146,   147,   154,
     130,     7,    50,   180,   130,    50,   146,   154,     7,    77,
     146,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    30,    31,    32,    33,
      48,   134,   147,   154,     7,    50,    50,   154,     7,   123,
      51,     7,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,     7,    55,     7,    49,    51,    52,   150,   123,
     150,    52,   150,   150,   150,   150,    52,   150,   150,    52,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,    55,    49,    59,   143,   148,    52,   150,    10,   136,
     138,    52,    51,    52,    79,    52,    52,    52,    52,    79,
      52,    52,    79,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,   143,    55,   180,    60,   144,   148,
      59,    79,    52,    61,    62,   137,   181,   138,    52,   150,
      79,   154,    79,    79,    79,    79,   154,    79,    79,   154,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,   144,    55,   180,    50,    60,    55,   180,   154,    79,
      51,   181,    79,    52,   154,   181,   154,   154,   154,   154,
     181,   154,   154,   181,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,    50,    55,   180,   181,   154,
      52,   151,   154,    79,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,    52,   181,   154,   181
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
#line 152 "beacon.y"
    {
		yyclearin;
	;}
    break;

  case 6:
#line 160 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 7:
#line 166 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 8:
#line 170 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 9:
#line 174 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 10:
#line 180 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 11:
#line 187 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value)
	;}
    break;

  case 12:
#line 194 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 17:
#line 205 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 18:
#line 209 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 19:
#line 216 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 21:
#line 224 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[(1) - (1)].stringv_value));
	;}
    break;

  case 22:
#line 228 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].stringv_value));
	;}
    break;

  case 24:
#line 236 "beacon.y"
    {
		(yyval.ast_value) = ast_new_import_decl_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 25:
#line 243 "beacon.y"
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 26:
#line 250 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameterized_typename((yyvsp[(1) - (2)].stringv_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 27:
#line 257 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 28:
#line 261 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 29:
#line 268 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 30:
#line 272 "beacon.y"
    {
		(yyval.ast_value) = ast_new_type_parameter_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 31:
#line 279 "beacon.y"
    {
		(yyval.ast_value) = ast_new_type_parameter((yyvsp[(1) - (1)].stringv_value), ast_new_blank());
	;}
    break;

  case 32:
#line 285 "beacon.y"
    {
		(yyval.ast_value) = ast_new_abstract_class_decl((yyvsp[(3) - (6)].ast_value), ast_new_blank(), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 33:
#line 289 "beacon.y"
    {
		(yyval.ast_value) = ast_new_abstract_class_decl((yyvsp[(3) - (8)].ast_value), (yyvsp[(5) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 34:
#line 295 "beacon.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 35:
#line 299 "beacon.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 36:
#line 306 "beacon.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (5)].stringv_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 37:
#line 310 "beacon.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (6)].stringv_value), (yyvsp[(4) - (6)].ast_value));
	;}
    break;

  case 38:
#line 317 "beacon.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 39:
#line 321 "beacon.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 40:
#line 328 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 43:
#line 337 "beacon.y"
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 44:
#line 344 "beacon.y"
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[(1) - (3)].access_level_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 45:
#line 351 "beacon.y"
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 46:
#line 355 "beacon.y"
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[(1) - (2)].ast_value), ast_new_member_decl((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 52:
#line 370 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 53:
#line 374 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 54:
#line 381 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (5)].chain_type_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 55:
#line 385 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (4)].chain_type_value), ast_new_blank());
	;}
    break;

  case 56:
#line 392 "beacon.y"
    {
		(yyval.chain_type_value) = chain_type_super;
	;}
    break;

  case 57:
#line 396 "beacon.y"
    {
		(yyval.chain_type_value) = chain_type_this;
	;}
    break;

  case 58:
#line 403 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 60:
#line 411 "beacon.y"
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[(2) - (8)].stringv_value), (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 61:
#line 415 "beacon.y"
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[(2) - (7)].stringv_value), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 62:
#line 422 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl((yyvsp[(2) - (10)].ast_value), (yyvsp[(3) - (10)].stringv_value), (yyvsp[(4) - (10)].ast_value), (yyvsp[(6) - (10)].ast_value), (yyvsp[(10) - (10)].ast_value), (yyvsp[(9) - (10)].ast_value));
	;}
    break;

  case 63:
#line 426 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[(2) - (9)].ast_value), (yyvsp[(3) - (9)].stringv_value), (yyvsp[(4) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 64:
#line 430 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl(ast_new_modifier(modifier_none), (yyvsp[(2) - (9)].stringv_value), (yyvsp[(3) - (9)].ast_value), (yyvsp[(5) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 65:
#line 434 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params(ast_new_modifier(modifier_none), (yyvsp[(2) - (8)].stringv_value), (yyvsp[(3) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 66:
#line 441 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_add, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 67:
#line 445 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_sub, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 68:
#line 449 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_mul, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 69:
#line 453 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_div, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 70:
#line 457 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_mod, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 71:
#line 461 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_gt, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 72:
#line 465 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_ge, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 73:
#line 469 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_lt, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 74:
#line 473 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_le, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 75:
#line 478 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_eq, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 76:
#line 482 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_noteq, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 77:
#line 487 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_bit_or, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 78:
#line 491 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_bit_and, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 79:
#line 496 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_logic_or, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 80:
#line 500 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_logic_and, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 81:
#line 505 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_lshift, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 82:
#line 509 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_rshift, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 83:
#line 514 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_excor, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 84:
#line 519 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_not, ast_new_blank(), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 85:
#line 524 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_childa, ast_new_blank(), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 86:
#line 528 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_negative, ast_new_blank(), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 87:
#line 535 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[(1) - (4)].ast_value), (yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].stringv_value));
	;}
    break;

  case 88:
#line 539 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_decl(ast_new_modifier(modifier_none), (yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].stringv_value));
	;}
    break;

  case 89:
#line 546 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_blank(), ast_new_blank());
	;}
    break;

  case 90:
#line 550 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_blank(), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 91:
#line 554 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_access((yyvsp[(1) - (3)].access_level_value)), ast_new_blank());
	;}
    break;

  case 92:
#line 558 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_access((yyvsp[(1) - (3)].access_level_value)), ast_new_blank());
	;}
    break;

  case 93:
#line 565 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_blank(), ast_new_blank());
	;}
    break;

  case 94:
#line 569 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_blank(), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 95:
#line 573 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_access((yyvsp[(1) - (3)].access_level_value)), ast_new_blank());
	;}
    break;

  case 96:
#line 577 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_access((yyvsp[(1) - (3)].access_level_value)), ast_new_blank());
	;}
    break;

  case 97:
#line 584 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_decl((yyvsp[(2) - (8)].ast_value), (yyvsp[(3) - (8)].ast_value), (yyvsp[(4) - (8)].stringv_value), (yyvsp[(6) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 98:
#line 588 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_decl(ast_new_modifier(modifier_none), (yyvsp[(2) - (7)].ast_value), (yyvsp[(3) - (7)].stringv_value), (yyvsp[(5) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 99:
#line 595 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 100:
#line 599 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 101:
#line 606 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_static);
	;}
    break;

  case 102:
#line 610 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_native);
	;}
    break;

  case 103:
#line 614 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_abstract);
	;}
    break;

  case 104:
#line 618 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_override);
	;}
    break;

  case 105:
#line 622 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_final);
	;}
    break;

  case 106:
#line 629 "beacon.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 107:
#line 633 "beacon.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 108:
#line 637 "beacon.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 109:
#line 644 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[(1) - (1)].stringv_value));
	;}
    break;

  case 110:
#line 648 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[(3) - (3)].stringv_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 111:
#line 655 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].stringv_value));
	;}
    break;

  case 112:
#line 659 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].stringv_value), (yyvsp[(1) - (4)].ast_value))
	;}
    break;

  case 113:
#line 666 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 114:
#line 670 "beacon.y"
    {
		(yyval.ast_value) = ast_new_lambda((yyvsp[(3) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 115:
#line 674 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(3) - (3)].ast_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 116:
#line 681 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 117:
#line 685 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 118:
#line 692 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 119:
#line 696 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 120:
#line 703 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 121:
#line 710 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].stringv_value));
	;}
    break;

  case 122:
#line 714 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(3) - (3)].stringv_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 123:
#line 723 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 126:
#line 731 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_pos, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 127:
#line 735 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_neg, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 128:
#line 739 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 129:
#line 743 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 130:
#line 747 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 131:
#line 751 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 132:
#line 755 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 133:
#line 759 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 134:
#line 763 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_equal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 135:
#line 767 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_notequal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 136:
#line 771 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 137:
#line 775 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 138:
#line 779 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 139:
#line 783 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 140:
#line 787 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 141:
#line 791 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 142:
#line 795 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 143:
#line 799 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 144:
#line 803 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 145:
#line 807 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 146:
#line 811 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_and_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 147:
#line 815 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 148:
#line 819 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 149:
#line 823 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 150:
#line 827 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 151:
#line 831 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_gt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 152:
#line 835 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_ge, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 153:
#line 839 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 154:
#line 843 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_le, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 155:
#line 847 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 156:
#line 851 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 157:
#line 855 "beacon.y"
    {
		(yyval.ast_value) = ast_new_instanceof((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 158:
#line 859 "beacon.y"
    {
		(yyval.ast_value) = ast_new_as((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 159:
#line 863 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_childa, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 160:
#line 867 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_not, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 161:
#line 871 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 162:
#line 875 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 163:
#line 879 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 164:
#line 883 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), ast_new_blank());
	;}
    break;

  case 165:
#line 887 "beacon.y"
    {
		(yyval.ast_value) = ast_new_this();
	;}
    break;

  case 166:
#line 891 "beacon.y"
    {
		(yyval.ast_value) = ast_new_super();
	;}
    break;

  case 168:
#line 898 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 169:
#line 902 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].stringv_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 170:
#line 906 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_add, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 171:
#line 910 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_sub, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 172:
#line 914 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_mul, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 173:
#line 918 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_div, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 174:
#line 922 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_mod, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 175:
#line 926 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_gt, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 176:
#line 930 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_ge, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 177:
#line 934 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_lt, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 178:
#line 938 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_le, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 179:
#line 942 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_eq, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 180:
#line 946 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_noteq, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 181:
#line 950 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_bit_or, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 182:
#line 954 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_bit_and, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 183:
#line 958 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_logic_or, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 184:
#line 962 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_logic_and, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 185:
#line 966 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_lshift, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 186:
#line 970 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_rshift, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 187:
#line 974 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_excor, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 188:
#line 978 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_not);
	;}
    break;

  case 189:
#line 982 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_childa);
	;}
    break;

  case 190:
#line 986 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_negative);
	;}
    break;

  case 195:
#line 996 "beacon.y"
    {
		(yyval.ast_value) = ast_new_true();
	;}
    break;

  case 196:
#line 1000 "beacon.y"
    {
		(yyval.ast_value) = ast_new_false();
	;}
    break;

  case 197:
#line 1004 "beacon.y"
    {
		(yyval.ast_value) = ast_new_null();
	;}
    break;

  case 198:
#line 1013 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 199:
#line 1017 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 200:
#line 1023 "beacon.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 215:
#line 1043 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].stringv_value));
	;}
    break;

  case 216:
#line 1049 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].stringv_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 217:
#line 1055 "beacon.y"
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[(2) - (5)].stringv_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 218:
#line 1061 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 219:
#line 1065 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 220:
#line 1069 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 221:
#line 1073 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 223:
#line 1080 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 224:
#line 1086 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 225:
#line 1092 "beacon.y"
    {
		(yyval.ast_value) = ast_new_while((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 226:
#line 1098 "beacon.y"
    {
		(yyval.ast_value) = ast_new_break();
	;}
    break;

  case 227:
#line 1104 "beacon.y"
    {
		(yyval.ast_value) = ast_new_continue();
	;}
    break;

  case 228:
#line 1110 "beacon.y"
    {
		(yyval.ast_value) = ast_new_return((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 229:
#line 1114 "beacon.y"
    {
		(yyval.ast_value) = ast_new_return_empty();
	;}
    break;

  case 230:
#line 1120 "beacon.y"
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 231:
#line 1126 "beacon.y"
    {
		(yyval.ast_value) = ast_new_try((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 232:
#line 1132 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 233:
#line 1136 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 234:
#line 1142 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].stringv_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 235:
#line 1148 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (5)].ast_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 236:
#line 1152 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 237:
#line 1158 "beacon.y"
    {
		(yyval.ast_value) = ast_new_defer((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 238:
#line 1164 "beacon.y"
    {
		(yyval.ast_value) = ast_new_yield_return((yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 239:
#line 1170 "beacon.y"
    {
		(yyval.ast_value) = ast_new_yield_break();
	;}
    break;

  case 240:
#line 1176 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 241:
#line 1180 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 242:
#line 1186 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3922 "beacon.tab.c"
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


#line 1194 "beacon.y"





