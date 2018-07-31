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
     DEFSET = 312,
     DEFGET = 313,
     THIS_TOK = 314,
     SUPER_TOK = 315,
     TRUE_TOK = 316,
     FALSE_TOK = 317,
     NULL_TOK = 318,
     AS = 319,
     ABSTRACT = 320,
     OVERRIDE = 321,
     INTERFACE = 322,
     CLASS = 323,
     ENUM = 324,
     PUBLIC = 325,
     PRIVATE = 326,
     PROTECTED = 327,
     STATIC = 328,
     NATIVE = 329,
     NEW = 330,
     DEF = 331,
     ARROW = 332,
     NAMESPACE = 333,
     RETURN = 334,
     IF = 335,
     ELIF = 336,
     ELSE = 337,
     WHILE = 338,
     BREAK = 339,
     CONTINUE = 340,
     TRY = 341,
     CATCH = 342,
     THROW = 343,
     ASSERT_T = 344,
     DEFER = 345,
     INSTANCEOF = 346,
     OPERATOR = 347,
     BOUNDS_EXTENDS = 348,
     BOUNDS_SUPER = 349,
     PRE_DEC = 350,
     PRE_INC = 351,
     QUOTE = 352,
     POST_DEC = 353,
     POST_INC = 354,
     FUNCCALL = 355,
     REF = 356,
     POSITIVE = 357,
     NEGATIVE = 358,
     FORM_TYPE = 359
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
#define DEFSET 312
#define DEFGET 313
#define THIS_TOK 314
#define SUPER_TOK 315
#define TRUE_TOK 316
#define FALSE_TOK 317
#define NULL_TOK 318
#define AS 319
#define ABSTRACT 320
#define OVERRIDE 321
#define INTERFACE 322
#define CLASS 323
#define ENUM 324
#define PUBLIC 325
#define PRIVATE 326
#define PROTECTED 327
#define STATIC 328
#define NATIVE 329
#define NEW 330
#define DEF 331
#define ARROW 332
#define NAMESPACE 333
#define RETURN 334
#define IF 335
#define ELIF 336
#define ELSE 337
#define WHILE 338
#define BREAK 339
#define CONTINUE 340
#define TRY 341
#define CATCH 342
#define THROW 343
#define ASSERT_T 344
#define DEFER 345
#define INSTANCEOF 346
#define OPERATOR 347
#define BOUNDS_EXTENDS 348
#define BOUNDS_SUPER 349
#define PRE_DEC 350
#define PRE_INC 351
#define QUOTE 352
#define POST_DEC 353
#define POST_INC 354
#define FUNCCALL 355
#define REF 356
#define POSITIVE 357
#define NEGATIVE 358
#define FORM_TYPE 359




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
#line 330 "beacon.tab.c"
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
#line 355 "beacon.tab.c"

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
#define YYLAST   2434

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  236
/* YYNRULES -- Number of states.  */
#define YYNSTATES  620

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   359

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     106,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     101,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      95,    96,    97,    98,    99,   100,   102,   103,   104,   105
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
     451,   454,   457,   460,   468,   475,   482,   488,   490,   493,
     495,   497,   499,   501,   503,   505,   507,   509,   513,   516,
     521,   523,   531,   535,   536,   540,   542,   546,   549,   551,
     555,   559,   561,   563,   566,   569,   573,   577,   581,   585,
     589,   593,   597,   601,   605,   609,   613,   617,   621,   625,
     629,   633,   637,   641,   645,   649,   653,   657,   661,   665,
     669,   673,   677,   681,   685,   689,   693,   696,   699,   704,
     708,   715,   721,   723,   725,   727,   730,   735,   742,   749,
     756,   763,   770,   777,   784,   791,   798,   805,   812,   819,
     826,   833,   840,   847,   854,   861,   867,   873,   879,   881,
     883,   885,   887,   889,   891,   893,   895,   898,   901,   903,
     905,   907,   909,   911,   913,   915,   917,   919,   921,   923,
     925,   929,   935,   941,   945,   951,   956,   963,   965,   968,
     972,   976,   979,   982,   986,   990,   994,   996,   999,  1006,
    1012,  1016,  1019,  1023,  1026,  1028,  1030
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     108,     0,    -1,   109,   110,    -1,   108,   110,    -1,     1,
     106,    -1,    -1,   117,    -1,   158,    -1,   111,    -1,   136,
      -1,    78,   116,   112,    -1,    48,   115,    49,    -1,    78,
     116,   112,    -1,   123,    -1,   124,    -1,   126,    -1,   125,
      -1,   113,    -1,   114,   113,    -1,    -1,   114,    -1,     7,
      -1,   116,    11,     7,    -1,   118,    -1,   117,   118,    -1,
      55,     4,    -1,     7,   120,    -1,    -1,    52,   121,    53,
      -1,   122,    -1,   121,     9,   122,    -1,     7,    -1,    65,
      68,   119,    48,   127,    49,    -1,    65,    68,   119,    10,
     150,    48,   127,    49,    -1,    68,   119,    48,   127,    49,
      -1,    68,   119,    10,   150,    48,   127,    49,    -1,    69,
       7,    48,   146,    49,    -1,    69,     7,    48,   146,     9,
      49,    -1,    67,   119,    48,   127,    49,    -1,    67,   119,
      10,   150,    48,   127,    49,    -1,    -1,   128,    -1,   129,
      -1,   128,   129,    -1,   145,    10,   130,    -1,   131,    -1,
     130,   131,    -1,   132,    -1,   137,    -1,   138,    -1,   139,
      -1,   142,    -1,    76,    75,    50,   147,    51,   135,   176,
      -1,    76,    75,    50,    51,   135,   176,    -1,    10,   134,
      50,   148,    51,    -1,    10,   134,    50,    51,    -1,    60,
      -1,    59,    -1,    -1,   133,    -1,    76,     7,    50,   147,
      51,    77,   151,   176,    -1,    76,     7,    50,    51,    77,
     151,   176,    -1,    76,   143,     7,   120,    50,   147,    51,
      77,   151,   176,    -1,    76,   143,     7,   120,    50,    51,
      77,   151,   176,    -1,    76,     7,   120,    50,   147,    51,
      77,   151,   176,    -1,    76,     7,   120,    50,    51,    77,
     151,   176,    -1,    92,    13,    50,   147,    51,    77,   151,
     176,    -1,    92,    14,    50,   147,    51,    77,   151,   176,
      -1,    92,    15,    50,   147,    51,    77,   151,   176,    -1,
      92,    16,    50,   147,    51,    77,   151,   176,    -1,    92,
      17,    50,   147,    51,    77,   151,   176,    -1,    92,    24,
      50,   147,    51,    77,   151,   176,    -1,    92,    25,    50,
     147,    51,    77,   151,   176,    -1,    92,    26,    50,   147,
      51,    77,   151,   176,    -1,    92,    27,    50,   147,    51,
      77,   151,   176,    -1,    92,    22,    50,   147,    51,    77,
     151,   176,    -1,    92,    23,    50,   147,    51,    77,   151,
     176,    -1,    92,    32,    50,   147,    51,    77,   151,   176,
      -1,    92,    30,    50,   147,    51,    77,   151,   176,    -1,
      92,    33,    50,   147,    51,    77,   151,   176,    -1,    92,
      31,    50,   147,    51,    77,   151,   176,    -1,    92,    19,
      50,   147,    51,    77,   151,   176,    -1,    92,    20,    50,
     147,    51,    77,   151,   176,    -1,    92,    47,    50,   147,
      51,    77,   151,   176,    -1,    92,    18,    50,    51,    77,
     151,   176,    -1,    92,    21,    50,    51,    77,   151,   176,
      -1,    92,    14,    50,    51,    77,   151,   176,    -1,   144,
     151,     7,    54,    -1,   151,     7,    54,    -1,    57,    54,
      -1,    57,   175,    -1,    58,    54,    -1,    58,   175,    -1,
     143,   151,     7,    48,   140,   141,    49,    -1,   143,   151,
       7,    48,   141,    49,    -1,   151,     7,    48,   140,   141,
      49,    -1,   151,     7,    48,   141,    49,    -1,   144,    -1,
     143,   144,    -1,    73,    -1,    74,    -1,    65,    -1,    66,
      -1,    70,    -1,    71,    -1,    72,    -1,     7,    -1,   146,
       9,     7,    -1,   151,     7,    -1,   147,     9,   151,     7,
      -1,   153,    -1,    97,    50,   147,    51,    77,   151,   175,
      -1,   148,     9,   153,    -1,    -1,    52,   150,    53,    -1,
     151,    -1,   150,     9,   151,    -1,   152,   149,    -1,     7,
      -1,   152,    11,     7,    -1,    50,   153,    51,    -1,   156,
      -1,   154,    -1,    13,   153,    -1,    14,   153,    -1,   153,
      13,   153,    -1,   153,    14,   153,    -1,   153,    15,   153,
      -1,   153,    16,   153,    -1,   153,    17,   153,    -1,   153,
      32,   153,    -1,   153,    22,   153,    -1,   153,    23,   153,
      -1,   153,    30,   153,    -1,   153,    47,   153,    -1,   153,
      33,   153,    -1,   153,    31,   153,    -1,   155,    34,   153,
      -1,   155,    35,   153,    -1,   155,    36,   153,    -1,   155,
      37,   153,    -1,   155,    38,   153,    -1,   155,    39,   153,
      -1,   155,    40,   153,    -1,   155,    41,   153,    -1,   155,
      44,   153,    -1,   155,    42,   153,    -1,   155,    43,   153,
      -1,   153,    24,   153,    -1,   153,    25,   153,    -1,   153,
      26,   153,    -1,   153,    27,   153,    -1,   153,    19,   153,
      -1,   153,    20,   153,    -1,   153,    91,   151,    -1,   153,
      64,   151,    -1,    21,   153,    -1,    18,   153,    -1,   154,
      50,   148,    51,    -1,   154,    50,    51,    -1,    75,   152,
     149,    50,   148,    51,    -1,    75,   152,   149,    50,    51,
      -1,    59,    -1,    60,    -1,   155,    -1,   152,   149,    -1,
     153,     8,     7,   149,    -1,   153,     8,    13,    50,   153,
      51,    -1,   153,     8,    14,    50,   153,    51,    -1,   153,
       8,    15,    50,   153,    51,    -1,   153,     8,    16,    50,
     153,    51,    -1,   153,     8,    17,    50,   153,    51,    -1,
     153,     8,    24,    50,   153,    51,    -1,   153,     8,    25,
      50,   153,    51,    -1,   153,     8,    26,    50,   153,    51,
      -1,   153,     8,    27,    50,   153,    51,    -1,   153,     8,
      22,    50,   153,    51,    -1,   153,     8,    23,    50,   153,
      51,    -1,   153,     8,    32,    50,   153,    51,    -1,   153,
       8,    30,    50,   153,    51,    -1,   153,     8,    33,    50,
     153,    51,    -1,   153,     8,    31,    50,   153,    51,    -1,
     153,     8,    19,    50,   153,    51,    -1,   153,     8,    20,
      50,   153,    51,    -1,   153,     8,    47,    50,   153,    51,
      -1,   153,     8,    18,    50,    51,    -1,   153,     8,    21,
      50,    51,    -1,   153,     8,    14,    50,    51,    -1,     5,
      -1,     6,    -1,     3,    -1,     4,    -1,    61,    -1,    62,
      -1,    63,    -1,   158,    -1,   157,   158,    -1,   153,   177,
      -1,   159,    -1,   160,    -1,   161,    -1,   162,    -1,   165,
      -1,   166,    -1,   167,    -1,   168,    -1,   169,    -1,   170,
      -1,   173,    -1,   174,    -1,   151,     7,    54,    -1,   151,
       7,    34,   153,   177,    -1,    56,     7,    34,   153,   177,
      -1,    80,   153,   175,    -1,    80,   153,   175,    82,   175,
      -1,    80,   153,   175,   163,    -1,    80,   153,   175,   163,
      82,   175,    -1,   164,    -1,   163,   164,    -1,    81,   153,
     175,    -1,    83,   153,   176,    -1,    84,   177,    -1,    85,
     177,    -1,    79,   153,   177,    -1,    88,   153,   177,    -1,
      86,   175,   171,    -1,   172,    -1,   171,   172,    -1,    87,
      50,   151,     7,    51,   175,    -1,    89,   153,    10,   153,
      54,    -1,    89,   153,    54,    -1,    90,   158,    -1,    48,
     157,    49,    -1,    48,    49,    -1,    54,    -1,   175,    -1,
      54,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   147,   147,   148,   149,   155,   157,   163,   167,   171,
     177,   184,   191,   195,   196,   197,   198,   202,   206,   214,
     217,   221,   225,   232,   233,   240,   247,   255,   258,   265,
     269,   276,   282,   286,   292,   296,   303,   307,   314,   318,
     326,   329,   333,   334,   341,   348,   352,   359,   360,   361,
     362,   363,   367,   371,   378,   382,   389,   393,   401,   404,
     408,   412,   419,   423,   427,   431,   438,   442,   446,   450,
     454,   458,   462,   466,   470,   475,   479,   484,   488,   493,
     497,   502,   506,   511,   516,   521,   525,   532,   536,   543,
     547,   554,   558,   565,   569,   573,   577,   584,   588,   595,
     599,   603,   607,   614,   618,   622,   629,   633,   640,   644,
     651,   655,   659,   667,   670,   677,   681,   688,   695,   699,
     708,   712,   713,   716,   720,   724,   728,   732,   736,   740,
     744,   748,   752,   756,   760,   764,   768,   772,   776,   780,
     784,   788,   792,   796,   800,   804,   808,   812,   816,   820,
     824,   828,   832,   836,   840,   844,   848,   852,   856,   860,
     864,   868,   872,   876,   880,   883,   887,   891,   895,   899,
     903,   907,   911,   915,   919,   923,   927,   931,   935,   939,
     943,   947,   951,   955,   959,   963,   967,   971,   977,   978,
     979,   980,   981,   985,   989,   998,  1002,  1008,  1012,  1013,
    1014,  1015,  1016,  1017,  1018,  1019,  1020,  1021,  1022,  1023,
    1026,  1032,  1038,  1044,  1048,  1052,  1056,  1062,  1063,  1069,
    1075,  1081,  1087,  1093,  1099,  1105,  1111,  1115,  1121,  1127,
    1131,  1137,  1144,  1148,  1154,  1158,  1161
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
  "VAR", "DEFSET", "DEFGET", "THIS_TOK", "SUPER_TOK", "TRUE_TOK",
  "FALSE_TOK", "NULL_TOK", "AS", "ABSTRACT", "OVERRIDE", "INTERFACE",
  "CLASS", "ENUM", "PUBLIC", "PRIVATE", "PROTECTED", "STATIC", "NATIVE",
  "NEW", "DEF", "ARROW", "NAMESPACE", "RETURN", "IF", "ELIF", "ELSE",
  "WHILE", "BREAK", "CONTINUE", "TRY", "CATCH", "THROW", "ASSERT_T",
  "DEFER", "INSTANCEOF", "OPERATOR", "BOUNDS_EXTENDS", "BOUNDS_SUPER",
  "PRE_DEC", "PRE_INC", "QUOTE", "POST_DEC", "POST_INC", "FUNCCALL", "'<'",
  "REF", "POSITIVE", "NEGATIVE", "FORM_TYPE", "'\\n'", "$accept",
  "compilation_unit", "init_decl", "body_decl", "namespace_decl",
  "namespace_body", "namespace_member_decl", "namespace_member_decl_list",
  "namespace_member_decl_optional", "namespace_path", "import_list",
  "import", "parameterized_typename", "type_parameter_group",
  "type_parameter_list", "type_parameter", "abstract_class_decl",
  "class_decl", "enum_decl", "interface_decl", "access_member_tree_opt",
  "access_member_tree", "access_member_list", "member_define_list",
  "member_define", "constructor_define", "constructor_chain",
  "constructor_chain_type_T", "constructor_chain_optional",
  "function_define", "method_define", "operator_define", "field_define",
  "prop_set", "prop_get", "prop_define", "modifier_type_T_list",
  "modifier_type_T", "access_level_T", "ident_list", "parameter_list",
  "argument_list", "typename_group", "typename_list", "typename_T",
  "fqcn_part", "expression", "expression_nobrace", "lhs", "primary",
  "stmt_list", "stmt", "variable_decl_stmt", "variable_init_stmt",
  "inferenced_type_init_stmt", "if_stmt", "elif_list", "elif",
  "while_stmt", "break_stmt", "continue_stmt", "return_stmt", "throw_stmt",
  "try_stmt", "catch_stmt_list", "catch_stmt", "assert_stmt", "defer_stmt",
  "scope", "scope_optional", "stmt_term", 0
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
     355,    60,   356,   357,   358,   359,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   107,   108,   108,   108,   109,   109,   110,   110,   110,
     111,   112,   113,   113,   113,   113,   113,   114,   114,   115,
     115,   116,   116,   117,   117,   118,   119,   120,   120,   121,
     121,   122,   123,   123,   124,   124,   125,   125,   126,   126,
     127,   127,   128,   128,   129,   130,   130,   131,   131,   131,
     131,   131,   132,   132,   133,   133,   134,   134,   135,   135,
     136,   136,   137,   137,   137,   137,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   139,   139,   140,
     140,   141,   141,   142,   142,   142,   142,   143,   143,   144,
     144,   144,   144,   145,   145,   145,   146,   146,   147,   147,
     148,   148,   148,   149,   149,   150,   150,   151,   152,   152,
     153,   153,   153,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   156,   156,
     156,   156,   156,   156,   156,   157,   157,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     159,   160,   161,   162,   162,   162,   162,   163,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   171,   172,   173,
     173,   174,   175,   175,   176,   176,   177
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
       2,     2,     2,     7,     6,     6,     5,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     4,
       1,     7,     3,     0,     3,     1,     3,     2,     1,     3,
       3,     1,     1,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     4,     3,
       6,     5,     1,     1,     1,     2,     4,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     5,     5,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     5,     5,     3,     5,     4,     6,     1,     2,     3,
       3,     2,     2,     3,     3,     3,     1,     2,     6,     5,
       3,     2,     3,     2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,    23,     4,    25,     1,
     190,   191,   188,   189,   118,     0,     0,     0,     0,     0,
       0,   162,   163,   192,   193,   194,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     8,
       9,     0,   113,     0,   122,   164,   121,     7,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
       2,    24,   113,   123,   124,   157,   156,     0,     0,   113,
       0,    21,     0,     0,     0,     0,   236,   221,   222,     0,
       0,     0,     0,   231,     0,     0,     0,   165,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   197,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   165,   120,     0,     0,     0,     0,    19,    10,
     223,   213,   234,   235,   220,   233,     0,   195,     0,   225,
     226,   224,     0,   230,     0,   210,   119,     0,   115,   113,
     113,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   125,   126,   127,   128,   129,   152,   153,   131,   132,
     148,   149,   150,   151,   133,   136,   130,   135,   134,   155,
     154,   159,     0,     0,   110,   137,   138,   139,   140,   141,
     142,   143,   144,   146,   147,   145,     0,     0,     0,     0,
       0,    22,     0,     0,     0,     0,     0,    17,    20,     0,
      13,    14,    16,    15,     0,     0,   215,   217,   232,   196,
       0,   227,     0,     0,     0,   114,   117,   166,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     158,   212,   161,     0,     0,     0,     0,   108,     0,    27,
       0,     0,     0,     0,    18,    11,     0,   214,     0,   218,
       0,   229,   211,   116,     0,   187,     0,     0,     0,     0,
     185,     0,     0,   186,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   112,   160,     0,     0,
       0,     0,     0,    26,     0,    40,     0,    40,     0,    12,
     219,   216,     0,   167,   168,   169,   170,   171,   182,   183,
     176,   177,   172,   173,   174,   175,   179,   181,   178,   180,
     184,     0,    61,   109,     0,     0,    40,    31,     0,    29,
       0,   103,   104,   105,     0,    41,    42,     0,     0,     0,
     106,     0,     0,     0,    60,     0,     0,     0,    28,    40,
      38,    43,     0,    40,    34,     0,    36,   228,     0,    40,
      32,    30,     0,   101,   102,    99,   100,     0,     0,    44,
      45,    47,    48,    49,    50,    51,     0,    97,     0,     0,
     107,    37,   111,     0,    39,    27,     0,     0,    97,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
      98,     0,     0,     0,    35,    33,     0,     0,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    88,     0,    58,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    87,
       0,     0,     0,     0,     0,     0,     0,    59,     0,    58,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,    90,    91,    92,     0,    96,
       0,     0,    57,    56,     0,    53,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,    95,     0,     0,     0,    52,     0,     0,     0,
      86,     0,     0,     0,     0,    84,     0,     0,    85,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,    65,     0,    55,     0,     0,     0,    66,    67,    68,
      69,    70,    81,    82,    75,    76,    71,    72,    73,    74,
      78,    80,    77,    79,    83,    64,    54,    63,     0,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    38,    39,   129,   217,   218,   219,    72,
       5,     6,   270,   313,   348,   349,   220,   221,   222,   223,
     354,   355,   356,   389,   390,   391,   497,   534,   498,    40,
     392,   393,   394,   492,   493,   395,   396,   397,   357,   361,
     209,   193,    87,   147,   210,    62,    43,    44,    45,    46,
     136,    47,    48,    49,    50,    51,   226,   227,    52,    53,
      54,    55,    56,    57,   139,   140,    58,    59,   133,   134,
      77
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -369
static const yytype_int16 yypact[] =
{
     837,   -84,    46,   747,   925,   -18,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  2359,  2359,  2359,  2359,  2359,
      67,  -369,  -369,  -369,  -369,  -369,    80,   142,   172,  2359,
    2359,  2359,    99,    99,   176,  2359,  2359,  1193,  -369,  -369,
    -369,   190,    30,  1334,   106,   654,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,    30,   164,   164,   164,   164,  1360,   201,    30,
     191,  -369,   204,  1334,  1413,  1272,  -369,  -369,  -369,  1013,
     182,  1334,  1308,  -369,   179,   265,    80,   277,   653,  2359,
    2359,  2359,  2359,  2359,  2359,  2359,  2359,  2359,  2359,  2359,
    2359,  2359,  2359,  2359,  2359,  2359,  2359,    80,    80,  -369,
      39,  2359,  2359,  2359,  2359,  2359,  2359,  2359,  2359,  2359,
    2359,  2359,  -369,  -369,  2359,   237,    10,   297,   276,  -369,
    -369,    37,  -369,  -369,  -369,  -369,  1105,  -369,   256,   182,
    -369,  -369,  2359,  -369,  2359,  -369,  -369,    11,  -369,    30,
     258,   269,   273,   286,   302,   305,   306,   307,   308,   309,
     313,   314,   316,   317,   318,   320,   321,   322,   323,   324,
     325,    -2,    -2,     2,     2,     2,   570,   570,  2305,  2305,
      16,    16,    16,    16,   146,  1210,   469,   942,   301,  -369,
    -369,  -369,   326,    17,   498,   498,   498,   498,   498,   498,
     498,   498,   498,   498,   498,   498,  1334,   124,   170,    26,
     370,  -369,   310,   373,   373,   374,   172,  -369,   276,   333,
    -369,  -369,  -369,  -369,  2359,   176,   215,  -369,  -369,  -369,
      80,  -369,  1449,  1334,    80,  -369,  -369,  -369,  2359,  2340,
    2359,  2359,  2359,   336,  2359,  2359,   337,  2359,  2359,  2359,
    2359,  2359,  2359,  2359,  2359,  2359,  2359,  2359,    80,  2359,
    -369,  -369,  -369,   100,    80,    80,   312,  -369,   373,   338,
      86,   216,   343,   204,  -369,  -369,  1413,  -369,   176,  -369,
     388,  -369,  -369,  -369,  1475,  -369,  1528,  1574,  1620,  1666,
    -369,  1712,  1758,  -369,  1804,  1850,  1896,  1942,  1988,  2034,
    2080,  2126,  2172,  2218,  2264,   101,   498,  -369,    78,   389,
      80,   240,   390,  -369,    80,   259,    80,   259,   391,  -369,
    -369,  -369,   348,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,   328,  -369,  -369,    78,    80,   259,  -369,    12,  -369,
       7,  -369,  -369,  -369,   351,   259,  -369,   392,    27,   352,
    -369,    94,   176,    80,  -369,    40,   354,   390,  -369,   259,
    -369,  -369,     5,   259,  -369,   108,  -369,  -369,   176,   259,
    -369,  -369,   362,  -369,  -369,  -369,  -369,    20,   757,     5,
    -369,  -369,  -369,  -369,  -369,  -369,    47,    80,   419,   378,
    -369,  -369,  -369,   379,  -369,   338,   381,    51,  -369,   383,
     385,   394,   406,   407,   409,   411,   412,   418,   420,   421,
     422,   423,   424,   425,   426,   428,   429,   430,   431,  -369,
    -369,   462,   480,    87,  -369,  -369,   440,    18,   338,    80,
      33,    80,    80,    80,   441,    80,    80,   447,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,   443,
     375,   162,  -369,    56,   490,   113,   451,   131,   432,   137,
     138,   149,   158,   433,   160,   171,   442,   181,   185,   187,
     193,   194,   195,   197,   203,   205,   207,   208,   162,  -369,
      96,   175,   444,   454,   449,   209,   280,  -369,    78,   490,
      60,   455,    80,   457,   458,   460,   465,    80,   481,   482,
      80,   486,   488,   489,   491,   492,   493,   495,   496,   497,
     500,   503,   444,   456,  -369,  -369,  -369,  -369,   459,  -369,
      80,   504,  -369,  -369,   507,  -369,    78,   505,   234,    80,
      78,    80,    80,    80,    80,    78,    80,    80,    78,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
     518,  -369,  -369,    78,    80,   287,  -369,    80,   511,    78,
    -369,    78,    78,    78,    78,  -369,    78,    78,  -369,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
    -369,  -369,    78,  -369,   244,    78,    80,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,    78,  -369
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -369,  -369,  -369,   571,  -369,   319,   372,  -369,  -369,   382,
    -369,   586,  -209,  -198,  -369,   233,  -369,  -369,  -369,  -369,
    -178,  -369,   246,  -369,   213,  -369,  -369,  -369,   104,  -369,
    -369,  -369,  -369,   116,  -190,  -369,   218,  -368,  -369,  -369,
     -33,  -204,   -58,     8,    69,    -3,   622,  -369,  -369,  -369,
    -369,   -28,  -369,  -369,  -369,  -369,  -369,   380,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,   468,  -369,  -369,   -27,  -306,
     -25
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -118
static const yytype_int16 yytable[] =
{
      42,    42,   342,   263,   122,   271,    88,    80,    78,    83,
      88,   125,    14,    91,    92,    93,   234,    14,   109,   408,
     234,   367,     7,    69,    88,    14,   259,   405,   430,    89,
      90,    91,    92,    93,    42,   265,   234,     2,   364,   430,
      14,    85,    10,    11,    12,    13,    14,   131,   130,   234,
       8,   137,    15,    16,    14,   369,   141,    17,   438,   311,
      18,   208,   107,    14,   235,   368,   107,    14,   260,   464,
     383,   384,    41,    41,    68,   373,    42,   266,   385,   386,
     107,   387,    86,   149,   468,   383,   384,    14,   379,    19,
     191,   236,   237,   385,   386,   406,   314,   388,    21,    22,
      23,    24,    25,   375,   149,   149,    41,   494,   229,   259,
     265,   537,   383,   384,    26,   400,   383,   384,   224,   225,
     385,   386,   265,   149,   385,   386,    79,    10,    11,    12,
      13,    14,   132,    42,   315,   461,   192,    15,    16,   359,
     265,   462,    17,   376,    79,    18,   265,   265,    41,    70,
     524,   307,   341,    76,    88,   148,   110,   401,   265,    89,
      90,    91,    92,    93,   499,    94,    95,   265,   366,   265,
      98,    99,   100,   101,    19,   262,   189,   190,   104,    71,
     265,   261,   501,    21,    22,    23,    24,    25,   503,   504,
     265,   382,   535,   106,   265,   399,   265,    84,   277,    26,
     505,   403,   265,   265,   265,    41,   265,   436,   282,   506,
     107,   508,   265,   144,   265,   127,   265,   265,   265,   490,
     491,   192,   509,    79,    79,   305,   316,   149,   107,   526,
     566,   149,   511,   145,   570,   124,   512,   108,   513,   575,
     466,   126,   578,   265,   514,   515,   516,   264,   517,   320,
     345,   321,   128,   259,   518,   149,   519,   591,   520,   521,
     531,   149,   149,   597,   317,   598,   599,   600,   601,   138,
     602,   603,   146,   604,   605,   606,   607,   608,   609,   610,
     611,   612,   613,   614,  -117,   568,   615,   207,   346,   617,
      10,    11,    12,    13,    14,   616,   224,   278,   523,   280,
      15,    16,   528,   283,   211,    17,   230,   149,    18,    88,
      86,   149,   619,   149,    89,    90,    91,    92,    93,   238,
      94,    95,   350,   239,   358,    98,    99,   100,   101,   351,
     352,   353,   560,   308,   309,   377,   240,    19,   593,   532,
     533,   212,   149,   213,   214,   215,    21,    22,    23,    24,
      25,   402,   241,   365,   216,   242,   243,   244,   245,   246,
     149,   594,    26,   247,   248,   107,   249,   250,   251,   149,
     252,   253,   254,   255,   256,   257,   258,   267,   268,   344,
     269,   272,   275,   148,   192,   148,   149,   290,   293,   310,
     312,   318,   108,   149,   149,   322,   343,   347,   360,   362,
     370,   374,   372,   380,   465,   363,   467,   469,   470,   471,
     472,   404,   474,   475,   148,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   433,   434,   435,   489,
     495,   437,   378,   439,   149,   440,   149,   149,   149,   149,
     149,   398,   149,   149,   441,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   442,   443,   398,   444,
     149,   445,   446,   525,   527,   431,   432,   538,   447,   459,
     448,   449,   450,   451,   452,   453,   454,    88,   455,   456,
     457,   458,    89,    90,    91,    92,    93,   460,    94,    95,
     463,   488,   473,    98,    99,   100,   101,   149,   476,   149,
     496,   500,   491,   529,   149,   561,    88,   149,   562,   502,
     507,    89,    90,    91,    92,    93,   106,    94,    95,   510,
      96,    97,    98,    99,   100,   101,   530,   149,   102,   103,
     104,   105,   539,   107,   541,   542,   149,   543,   149,   149,
     149,   149,   544,   149,   149,   106,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   565,   546,   547,
     108,   149,   107,   549,   149,   550,   551,   590,   552,   553,
     554,   540,   555,   556,   557,    60,   545,   558,    88,   548,
     559,   564,   567,    89,    90,    91,    92,    93,   596,   108,
     274,    61,   319,   149,    98,    99,   100,   101,   273,   563,
     381,   371,   429,   536,   522,   407,   279,   231,   569,     0,
     571,   572,   573,   574,     0,   576,   577,     0,   579,   580,
     581,   582,   583,   584,   585,   586,   587,   588,   589,     0,
       0,     0,     0,   592,   107,     0,   595,    63,    64,    65,
      66,    67,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    73,    74,    75,     0,     0,     0,    81,    82,     0,
     150,   108,     0,     0,     0,   618,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,     0,     0,   166,   167,   168,   169,     0,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,     0,
     170,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,     0,
       0,     0,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,     0,     0,   206,     9,     0,     0,
      10,    11,    12,    13,    14,     0,     0,     0,     0,     0,
      15,    16,     0,     0,   232,    17,   233,     0,    18,     0,
     409,   410,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,     0,     0,   424,   425,   426,
     427,     0,     0,     0,     0,     0,     0,    19,     0,     0,
       0,     0,     0,    20,   428,     0,    21,    22,    23,    24,
      25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    26,    27,     0,    28,    29,    30,     0,   194,
      31,    32,    33,    34,     0,    35,    36,    37,     1,     0,
      -5,    -5,    -5,    -5,    -5,     0,   276,     0,     0,     0,
      -5,    -5,     0,     0,     0,    -5,     0,     0,    -5,     0,
     284,   286,   287,   288,   289,     0,   291,   292,     0,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
       0,   306,     0,     0,     0,     0,     0,    -5,     0,     0,
       0,     0,     2,    -5,     0,     0,    -5,    -5,    -5,    -5,
      -5,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    -5,    -5,     0,    -5,    -5,    -5,     0,     0,
      -5,    -5,    -5,    -5,     0,    -5,    -5,    -5,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,    15,    16,
       0,     0,     0,    17,     0,     0,    18,     0,     0,     0,
      88,     0,     0,     0,     0,    89,    90,    91,    92,    93,
       0,    94,    95,     0,     0,     0,    98,    99,   100,   101,
       0,     0,   102,   103,   104,    19,     0,     0,     0,     0,
       0,    20,     0,     0,    21,    22,    23,    24,    25,   106,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26,    27,     0,    28,    29,    30,   107,     0,    31,    32,
      33,    34,     0,    35,    36,    37,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,    15,    16,     0,     0,
       0,    17,     0,   108,    18,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   135,    19,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    22,    23,    24,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,     0,
       0,     0,    29,    30,     0,     0,    31,    32,    33,    34,
       0,    35,    36,    37,     0,     0,     0,     0,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,    15,    16,
       0,     0,     0,    17,     0,     0,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   228,    19,     0,     0,     0,     0,
       0,    20,     0,     0,    21,    22,    23,    24,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26,     0,     0,     0,    29,    30,     0,   194,    31,    32,
      33,    34,     0,    35,    36,    37,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,    15,    16,     0,     0,
       0,    17,     0,     0,    18,     0,     0,     0,    88,     0,
       0,     0,     0,    89,    90,    91,    92,    93,     0,    94,
      95,     0,     0,     0,    98,    99,   100,   101,     0,     0,
     102,     0,   104,    19,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    22,    23,    24,    25,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,     0,
       0,     0,    29,    30,   107,     0,    31,    32,    33,    34,
      88,    35,    36,    37,     0,    89,    90,    91,    92,    93,
       0,    94,    95,     0,    96,    97,    98,    99,   100,   101,
       0,   108,   102,   103,   104,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    88,     0,   142,   106,
      79,    89,    90,    91,    92,    93,   132,    94,    95,     0,
      96,    97,    98,    99,   100,   101,   107,     0,   102,   103,
     104,   105,    88,     0,     0,     0,     0,    89,    90,    91,
      92,    93,     0,    94,    95,   106,    96,    97,    98,    99,
     100,   101,   143,   108,   102,   103,   104,   105,    88,     0,
       0,     0,   107,    89,    90,    91,    92,    93,     0,    94,
      95,   106,    96,    97,    98,    99,   100,   101,    76,     0,
     102,   103,   104,   105,     0,     0,     0,     0,   107,   108,
       0,     0,     0,     0,     0,     0,     0,   106,     0,     0,
       0,   123,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    88,     0,     0,   107,   108,    89,    90,    91,    92,
      93,     0,    94,    95,     0,    96,    97,    98,    99,   100,
     101,     0,     0,   102,   103,   104,   105,     0,     0,     0,
       0,   108,     0,     0,     0,     0,     0,    88,     0,     0,
     106,    79,    89,    90,    91,    92,    93,     0,    94,    95,
       0,    96,    97,    98,    99,   100,   101,   107,     0,   102,
     103,   104,   105,    88,     0,     0,     0,     0,    89,    90,
      91,    92,    93,     0,    94,    95,   106,    96,    97,    98,
      99,   100,   101,   281,   108,   102,   103,   104,   105,     0,
       0,     0,     0,   107,     0,     0,     0,     0,     0,     0,
       0,     0,   106,     0,     0,     0,   323,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    88,     0,     0,   107,
     108,    89,    90,    91,    92,    93,     0,    94,    95,     0,
      96,    97,    98,    99,   100,   101,     0,     0,   102,   103,
     104,   105,     0,     0,     0,     0,   108,     0,     0,     0,
       0,     0,     0,     0,     0,   106,     0,     0,     0,   324,
       0,     0,    88,     0,     0,     0,     0,    89,    90,    91,
      92,    93,   107,    94,    95,     0,    96,    97,    98,    99,
     100,   101,     0,     0,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
       0,   106,     0,     0,     0,   325,     0,     0,    88,     0,
       0,     0,     0,    89,    90,    91,    92,    93,   107,    94,
      95,     0,    96,    97,    98,    99,   100,   101,     0,     0,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,     0,   106,     0,     0,
       0,   326,     0,     0,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,   107,    94,    95,     0,    96,    97,
      98,    99,   100,   101,     0,     0,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,     0,   106,     0,     0,     0,   327,     0,     0,
      88,     0,     0,     0,     0,    89,    90,    91,    92,    93,
     107,    94,    95,     0,    96,    97,    98,    99,   100,   101,
       0,     0,   102,   103,   104,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,     0,   106,
       0,     0,     0,   328,     0,     0,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,   107,    94,    95,     0,
      96,    97,    98,    99,   100,   101,     0,     0,   102,   103,
     104,   105,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,     0,   106,     0,     0,     0,   329,
       0,     0,    88,     0,     0,     0,     0,    89,    90,    91,
      92,    93,   107,    94,    95,     0,    96,    97,    98,    99,
     100,   101,     0,     0,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
       0,   106,     0,     0,     0,   330,     0,     0,    88,     0,
       0,     0,     0,    89,    90,    91,    92,    93,   107,    94,
      95,     0,    96,    97,    98,    99,   100,   101,     0,     0,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,     0,   106,     0,     0,
       0,   331,     0,     0,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,   107,    94,    95,     0,    96,    97,
      98,    99,   100,   101,     0,     0,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,     0,   106,     0,     0,     0,   332,     0,     0,
      88,     0,     0,     0,     0,    89,    90,    91,    92,    93,
     107,    94,    95,     0,    96,    97,    98,    99,   100,   101,
       0,     0,   102,   103,   104,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,     0,   106,
       0,     0,     0,   333,     0,     0,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,   107,    94,    95,     0,
      96,    97,    98,    99,   100,   101,     0,     0,   102,   103,
     104,   105,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,     0,   106,     0,     0,     0,   334,
       0,     0,    88,     0,     0,     0,     0,    89,    90,    91,
      92,    93,   107,    94,    95,     0,    96,    97,    98,    99,
     100,   101,     0,     0,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
       0,   106,     0,     0,     0,   335,     0,     0,    88,     0,
       0,     0,     0,    89,    90,    91,    92,    93,   107,    94,
      95,     0,    96,    97,    98,    99,   100,   101,     0,     0,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,     0,   106,     0,     0,
       0,   336,     0,     0,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,   107,    94,    95,     0,    96,    97,
      98,    99,   100,   101,     0,     0,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,     0,   106,     0,     0,     0,   337,     0,     0,
      88,     0,     0,     0,     0,    89,    90,    91,    92,    93,
     107,    94,    95,     0,    96,    97,    98,    99,   100,   101,
       0,     0,   102,   103,   104,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,     0,   106,
       0,     0,     0,   338,     0,     0,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,   107,    94,    95,     0,
      96,    97,    98,    99,   100,   101,     0,     0,   102,   103,
     104,   105,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,     0,   106,     0,     0,     0,   339,
       0,     0,    88,     0,     0,     0,     0,    89,    90,    91,
      92,    93,   107,    94,    95,     0,    96,    97,    98,    99,
     100,   101,     0,     0,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
       0,   106,     0,    88,     0,   340,     0,     0,    89,    90,
      91,    92,    93,     0,    94,    95,     0,     0,   107,    98,
      99,   100,   101,     0,     0,   102,   103,   104,   105,     0,
       0,     0,     0,    10,    11,    12,    13,    14,     0,     0,
       0,     0,   106,    15,    16,   108,     0,     0,    17,     0,
       0,    18,    10,    11,    12,    13,    14,     0,     0,   107,
       0,     0,    15,    16,     0,     0,     0,    17,     0,     0,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      19,   285,     0,     0,     0,     0,   108,     0,     0,    21,
      22,    23,    24,    25,     0,     0,     0,     0,     0,    19,
       0,     0,     0,     0,     0,    26,     0,     0,    21,    22,
      23,    24,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    26
};

static const yytype_int16 yycheck[] =
{
       3,     4,   308,   207,    62,   214,     8,    34,    33,    37,
       8,    69,     7,    15,    16,    17,     9,     7,    43,   387,
       9,     9,   106,    26,     8,     7,     9,     7,   396,    13,
      14,    15,    16,    17,    37,     9,     9,    55,   344,   407,
       7,    11,     3,     4,     5,     6,     7,    74,    73,     9,
       4,    79,    13,    14,     7,    48,    81,    18,     7,   268,
      21,    51,    64,     7,    53,    53,    64,     7,    51,    51,
      65,    66,     3,     4,     7,    48,    79,    51,    73,    74,
      64,    76,    52,    86,    51,    65,    66,     7,    48,    50,
      51,   149,   150,    73,    74,    75,    10,    92,    59,    60,
      61,    62,    63,     9,   107,   108,    37,    51,   136,     9,
       9,    51,    65,    66,    75,     7,    65,    66,    81,    82,
      73,    74,     9,   126,    73,    74,    48,     3,     4,     5,
       6,     7,    54,   136,    48,    48,    97,    13,    14,   317,
       9,    54,    18,    49,    48,    21,     9,     9,    79,     7,
      54,    51,    51,    54,     8,    86,    50,    49,     9,    13,
      14,    15,    16,    17,    51,    19,    20,     9,   346,     9,
      24,    25,    26,    27,    50,    51,   107,   108,    32,     7,
       9,   206,    51,    59,    60,    61,    62,    63,    51,    51,
       9,   369,   498,    47,     9,   373,     9,     7,   225,    75,
      51,   379,     9,     9,     9,   136,     9,   405,   233,    51,
      64,    51,     9,    34,     9,    11,     9,     9,     9,    57,
      58,    97,    51,    48,    48,   258,    10,   230,    64,    54,
     536,   234,    51,    54,   540,    34,    51,    91,    51,   545,
     438,    50,   548,     9,    51,    51,    51,    77,    51,   276,
      10,   278,    48,     9,    51,   258,    51,   563,    51,    51,
      51,   264,   265,   569,    48,   571,   572,   573,   574,    87,
     576,   577,     7,   579,   580,   581,   582,   583,   584,   585,
     586,   587,   588,   589,     7,    51,   592,    50,    48,   595,
       3,     4,     5,     6,     7,    51,    81,    82,   488,   230,
      13,    14,   492,   234,     7,    18,    50,   310,    21,     8,
      52,   314,   618,   316,    13,    14,    15,    16,    17,    50,
      19,    20,   314,    50,   316,    24,    25,    26,    27,    70,
      71,    72,   522,   264,   265,   362,    50,    50,    51,    59,
      60,    65,   345,    67,    68,    69,    59,    60,    61,    62,
      63,   378,    50,   345,    78,    50,    50,    50,    50,    50,
     363,   565,    75,    50,    50,    64,    50,    50,    50,   372,
      50,    50,    50,    50,    50,    50,    50,     7,    68,   310,
       7,     7,    49,   314,    97,   316,   389,    51,    51,    77,
      52,    48,    91,   396,   397,     7,     7,     7,     7,    51,
      49,    49,    10,    49,   437,    77,   439,   440,   441,   442,
     443,    49,   445,   446,   345,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,     7,    49,    49,    54,
     463,    50,   363,    50,   437,    50,   439,   440,   441,   442,
     443,   372,   445,   446,    50,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,    50,    50,   389,    50,
     463,    50,    50,   490,   491,   396,   397,   500,    50,     7,
      50,    50,    50,    50,    50,    50,    50,     8,    50,    50,
      50,    50,    13,    14,    15,    16,    17,     7,    19,    20,
      50,    48,    51,    24,    25,    26,    27,   500,    51,   502,
      10,    50,    58,    49,   507,    49,     8,   510,    49,    77,
      77,    13,    14,    15,    16,    17,    47,    19,    20,    77,
      22,    23,    24,    25,    26,    27,    77,   530,    30,    31,
      32,    33,    77,    64,    77,    77,   539,    77,   541,   542,
     543,   544,    77,   546,   547,    47,   549,   550,   551,   552,
     553,   554,   555,   556,   557,   558,   559,    50,    77,    77,
      91,   564,    64,    77,   567,    77,    77,    49,    77,    77,
      77,   502,    77,    77,    77,     4,   507,    77,     8,   510,
      77,    77,    77,    13,    14,    15,    16,    17,    77,    91,
     218,     5,   273,   596,    24,    25,    26,    27,   216,   530,
     367,   355,   389,   499,   488,   387,   226,   139,   539,    -1,
     541,   542,   543,   544,    -1,   546,   547,    -1,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   558,   559,    -1,
      -1,    -1,    -1,   564,    64,    -1,   567,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    30,    31,    -1,    -1,    -1,    35,    36,    -1,
       7,    91,    -1,    -1,    -1,   596,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,    -1,
      -1,    -1,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,    -1,    -1,   124,     0,    -1,    -1,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,
      13,    14,    -1,    -1,   142,    18,   144,    -1,    21,    -1,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    56,    47,    -1,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    -1,    78,    79,    80,    -1,   207,
      83,    84,    85,    86,    -1,    88,    89,    90,     1,    -1,
       3,     4,     5,     6,     7,    -1,   224,    -1,    -1,    -1,
      13,    14,    -1,    -1,    -1,    18,    -1,    -1,    21,    -1,
     238,   239,   240,   241,   242,    -1,   244,   245,    -1,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
      -1,   259,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    55,    56,    -1,    -1,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    -1,    78,    79,    80,    -1,    -1,
      83,    84,    85,    86,    -1,    88,    89,    90,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,
      -1,    -1,    -1,    18,    -1,    -1,    21,    -1,    -1,    -1,
       8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,
      -1,    19,    20,    -1,    -1,    -1,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    50,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    59,    60,    61,    62,    63,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    76,    -1,    78,    79,    80,    64,    -1,    83,    84,
      85,    86,    -1,    88,    89,    90,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    13,    14,    -1,    -1,
      -1,    18,    -1,    91,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    50,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    59,    60,    61,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    79,    80,    -1,    -1,    83,    84,    85,    86,
      -1,    88,    89,    90,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,
      -1,    -1,    -1,    18,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    50,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    -1,    -1,    -1,    79,    80,    -1,   565,    83,    84,
      85,    86,    -1,    88,    89,    90,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    13,    14,    -1,    -1,
      -1,    18,    -1,    -1,    21,    -1,    -1,    -1,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    -1,    -1,    -1,    24,    25,    26,    27,    -1,    -1,
      30,    -1,    32,    50,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    59,    60,    61,    62,    63,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    79,    80,    64,    -1,    83,    84,    85,    86,
       8,    88,    89,    90,    -1,    13,    14,    15,    16,    17,
      -1,    19,    20,    -1,    22,    23,    24,    25,    26,    27,
      -1,    91,    30,    31,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,    10,    47,
      48,    13,    14,    15,    16,    17,    54,    19,    20,    -1,
      22,    23,    24,    25,    26,    27,    64,    -1,    30,    31,
      32,    33,     8,    -1,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    -1,    19,    20,    47,    22,    23,    24,    25,
      26,    27,    54,    91,    30,    31,    32,    33,     8,    -1,
      -1,    -1,    64,    13,    14,    15,    16,    17,    -1,    19,
      20,    47,    22,    23,    24,    25,    26,    27,    54,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    64,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     8,    -1,    -1,    64,    91,    13,    14,    15,    16,
      17,    -1,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    91,    -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,
      47,    48,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    64,    -1,    30,
      31,    32,    33,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    47,    22,    23,    24,
      25,    26,    27,    54,    91,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    64,
      91,    13,    14,    15,    16,    17,    -1,    19,    20,    -1,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    51,
      -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    64,    19,    20,    -1,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    47,    -1,    -1,    -1,    51,    -1,    -1,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    64,    19,
      20,    -1,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    47,    -1,    -1,
      -1,    51,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    64,    19,    20,    -1,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    47,    -1,    -1,    -1,    51,    -1,    -1,
       8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,
      64,    19,    20,    -1,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    47,
      -1,    -1,    -1,    51,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    13,    14,    15,    16,    17,    64,    19,    20,    -1,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    47,    -1,    -1,    -1,    51,
      -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    64,    19,    20,    -1,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    47,    -1,    -1,    -1,    51,    -1,    -1,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    64,    19,
      20,    -1,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    47,    -1,    -1,
      -1,    51,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    64,    19,    20,    -1,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    47,    -1,    -1,    -1,    51,    -1,    -1,
       8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,
      64,    19,    20,    -1,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    47,
      -1,    -1,    -1,    51,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    13,    14,    15,    16,    17,    64,    19,    20,    -1,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    47,    -1,    -1,    -1,    51,
      -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    64,    19,    20,    -1,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    47,    -1,    -1,    -1,    51,    -1,    -1,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    64,    19,
      20,    -1,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    47,    -1,    -1,
      -1,    51,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    64,    19,    20,    -1,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    47,    -1,    -1,    -1,    51,    -1,    -1,
       8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,
      64,    19,    20,    -1,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    47,
      -1,    -1,    -1,    51,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    13,    14,    15,    16,    17,    64,    19,    20,    -1,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    47,    -1,    -1,    -1,    51,
      -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    64,    19,    20,    -1,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    47,    -1,     8,    -1,    51,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    -1,    -1,    64,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    47,    13,    14,    91,    -1,    -1,    18,    -1,
      -1,    21,     3,     4,     5,     6,     7,    -1,    -1,    64,
      -1,    -1,    13,    14,    -1,    -1,    -1,    18,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    -1,    -1,    -1,    -1,    91,    -1,    -1,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    55,   108,   109,   117,   118,   106,     4,     0,
       3,     4,     5,     6,     7,    13,    14,    18,    21,    50,
      56,    59,    60,    61,    62,    63,    75,    76,    78,    79,
      80,    83,    84,    85,    86,    88,    89,    90,   110,   111,
     136,   151,   152,   153,   154,   155,   156,   158,   159,   160,
     161,   162,   165,   166,   167,   168,   169,   170,   173,   174,
     110,   118,   152,   153,   153,   153,   153,   153,     7,   152,
       7,     7,   116,   153,   153,   153,    54,   177,   177,    48,
     175,   153,   153,   158,     7,    11,    52,   149,     8,    13,
      14,    15,    16,    17,    19,    20,    22,    23,    24,    25,
      26,    27,    30,    31,    32,    33,    47,    64,    91,   177,
      50,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,   149,    51,    34,   149,    50,    11,    48,   112,
     177,   175,    54,   175,   176,    49,   157,   158,    87,   171,
     172,   177,    10,    54,    34,    54,     7,   150,   151,   152,
       7,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    30,    31,    32,    33,
      47,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   151,
     151,    51,    97,   148,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,    50,    51,   147,
     151,     7,    65,    67,    68,    69,    78,   113,   114,   115,
     123,   124,   125,   126,    81,    82,   163,   164,    49,   158,
      50,   172,   153,   153,     9,    53,   149,   149,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,     9,
      51,   177,    51,   148,    77,     9,    51,     7,    68,     7,
     119,   119,     7,   116,   113,    49,   153,   175,    82,   164,
     151,    54,   177,   151,   153,    51,   153,   153,   153,   153,
      51,   153,   153,    51,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   147,   153,    51,   151,   151,
      77,   119,    52,   120,    10,    48,    10,    48,    48,   112,
     175,   175,     7,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,   176,     7,   151,    10,    48,     7,   121,   122,
     150,    70,    71,    72,   127,   128,   129,   145,   150,   127,
       7,   146,    51,    77,   176,   150,   127,     9,    53,    48,
      49,   129,    10,    48,    49,     9,    49,   175,   151,    48,
      49,   122,   127,    65,    66,    73,    74,    76,    92,   130,
     131,   132,   137,   138,   139,   142,   143,   144,   151,   127,
       7,    49,   175,   127,    49,     7,    75,   143,   144,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    30,    31,    32,    33,    47,   131,
     144,   151,   151,     7,    49,    49,   120,    50,     7,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,     7,
       7,    48,    54,    50,    51,   147,   120,   147,    51,   147,
     147,   147,   147,    51,   147,   147,    51,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,    48,    54,
      57,    58,   140,   141,    51,   147,    10,   133,   135,    51,
      50,    51,    77,    51,    51,    51,    51,    77,    51,    51,
      77,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,   140,   141,    54,   175,    54,   175,   141,    49,
      77,    51,    59,    60,   134,   176,   135,    51,   147,    77,
     151,    77,    77,    77,    77,   151,    77,    77,   151,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
     141,    49,    49,   151,    77,    50,   176,    77,    51,   151,
     176,   151,   151,   151,   151,   176,   151,   151,   176,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
      49,   176,   151,    51,   148,   151,    77,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,    51,   176,   151,   176
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
#line 150 "beacon.y"
    {
		yyclearin;
	;}
    break;

  case 6:
#line 158 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 7:
#line 164 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 8:
#line 168 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 9:
#line 172 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 10:
#line 178 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 11:
#line 185 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value)
	;}
    break;

  case 12:
#line 192 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 17:
#line 203 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 18:
#line 207 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 19:
#line 214 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 21:
#line 222 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[(1) - (1)].stringv_value));
	;}
    break;

  case 22:
#line 226 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].stringv_value));
	;}
    break;

  case 24:
#line 234 "beacon.y"
    {
		(yyval.ast_value) = ast_new_import_decl_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 25:
#line 241 "beacon.y"
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 26:
#line 248 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameterized_typename((yyvsp[(1) - (2)].stringv_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 27:
#line 255 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 28:
#line 259 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 29:
#line 266 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 30:
#line 270 "beacon.y"
    {
		(yyval.ast_value) = ast_new_type_parameter_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 31:
#line 277 "beacon.y"
    {
		(yyval.ast_value) = ast_new_type_parameter((yyvsp[(1) - (1)].stringv_value), ast_new_blank());
	;}
    break;

  case 32:
#line 283 "beacon.y"
    {
		(yyval.ast_value) = ast_new_abstract_class_decl((yyvsp[(3) - (6)].ast_value), ast_new_blank(), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 33:
#line 287 "beacon.y"
    {
		(yyval.ast_value) = ast_new_abstract_class_decl((yyvsp[(3) - (8)].ast_value), (yyvsp[(5) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 34:
#line 293 "beacon.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 35:
#line 297 "beacon.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 36:
#line 304 "beacon.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (5)].stringv_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 37:
#line 308 "beacon.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (6)].stringv_value), (yyvsp[(4) - (6)].ast_value));
	;}
    break;

  case 38:
#line 315 "beacon.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 39:
#line 319 "beacon.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 40:
#line 326 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 43:
#line 335 "beacon.y"
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 44:
#line 342 "beacon.y"
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[(1) - (3)].access_level_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 45:
#line 349 "beacon.y"
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 46:
#line 353 "beacon.y"
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[(1) - (2)].ast_value), ast_new_member_decl((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 52:
#line 368 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 53:
#line 372 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 54:
#line 379 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (5)].chain_type_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 55:
#line 383 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (4)].chain_type_value), ast_new_blank());
	;}
    break;

  case 56:
#line 390 "beacon.y"
    {
		(yyval.chain_type_value) = chain_type_super;
	;}
    break;

  case 57:
#line 394 "beacon.y"
    {
		(yyval.chain_type_value) = chain_type_this;
	;}
    break;

  case 58:
#line 401 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 60:
#line 409 "beacon.y"
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[(2) - (8)].stringv_value), (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 61:
#line 413 "beacon.y"
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[(2) - (7)].stringv_value), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 62:
#line 420 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl((yyvsp[(2) - (10)].ast_value), (yyvsp[(3) - (10)].stringv_value), (yyvsp[(4) - (10)].ast_value), (yyvsp[(6) - (10)].ast_value), (yyvsp[(10) - (10)].ast_value), (yyvsp[(9) - (10)].ast_value));
	;}
    break;

  case 63:
#line 424 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[(2) - (9)].ast_value), (yyvsp[(3) - (9)].stringv_value), (yyvsp[(4) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 64:
#line 428 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl(ast_new_modifier(modifier_none), (yyvsp[(2) - (9)].stringv_value), (yyvsp[(3) - (9)].ast_value), (yyvsp[(5) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 65:
#line 432 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params(ast_new_modifier(modifier_none), (yyvsp[(2) - (8)].stringv_value), (yyvsp[(3) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 66:
#line 439 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_add, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 67:
#line 443 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_sub, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 68:
#line 447 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_mul, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 69:
#line 451 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_div, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 70:
#line 455 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_mod, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 71:
#line 459 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_gt, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 72:
#line 463 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_ge, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 73:
#line 467 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_lt, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 74:
#line 471 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_le, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 75:
#line 476 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_eq, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 76:
#line 480 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_noteq, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 77:
#line 485 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_bit_or, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 78:
#line 489 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_bit_and, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 79:
#line 494 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_logic_or, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 80:
#line 498 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_logic_and, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 81:
#line 503 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_lshift, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 82:
#line 507 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_rshift, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 83:
#line 512 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_excor, (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 84:
#line 517 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_not, ast_new_blank(), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 85:
#line 522 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_childa, ast_new_blank(), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 86:
#line 526 "beacon.y"
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_negative, ast_new_blank(), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 87:
#line 533 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[(1) - (4)].ast_value), (yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].stringv_value));
	;}
    break;

  case 88:
#line 537 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_decl(ast_new_modifier(modifier_none), (yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].stringv_value));
	;}
    break;

  case 89:
#line 544 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_blank());
	;}
    break;

  case 90:
#line 548 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_set((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 91:
#line 555 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_blank());
	;}
    break;

  case 92:
#line 559 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_get((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 93:
#line 566 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_decl((yyvsp[(1) - (7)].ast_value), (yyvsp[(2) - (7)].ast_value), (yyvsp[(3) - (7)].stringv_value), (yyvsp[(5) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 94:
#line 570 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_decl((yyvsp[(1) - (6)].ast_value), (yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].stringv_value), ast_new_blank(), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 95:
#line 574 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_decl(ast_new_modifier(modifier_none), (yyvsp[(1) - (6)].ast_value), (yyvsp[(2) - (6)].stringv_value), (yyvsp[(4) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 96:
#line 578 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_decl(ast_new_modifier(modifier_none), (yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].stringv_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 97:
#line 585 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 98:
#line 589 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 99:
#line 596 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_static);
	;}
    break;

  case 100:
#line 600 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_native);
	;}
    break;

  case 101:
#line 604 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_abstract);
	;}
    break;

  case 102:
#line 608 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_override);
	;}
    break;

  case 103:
#line 615 "beacon.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 104:
#line 619 "beacon.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 105:
#line 623 "beacon.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 106:
#line 630 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[(1) - (1)].stringv_value));
	;}
    break;

  case 107:
#line 634 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[(3) - (3)].stringv_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 108:
#line 641 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].stringv_value));
	;}
    break;

  case 109:
#line 645 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].stringv_value), (yyvsp[(1) - (4)].ast_value))
	;}
    break;

  case 110:
#line 652 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 111:
#line 656 "beacon.y"
    {
		(yyval.ast_value) = ast_new_lambda((yyvsp[(3) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 112:
#line 660 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(3) - (3)].ast_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 113:
#line 667 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 114:
#line 671 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 115:
#line 678 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 116:
#line 682 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 117:
#line 689 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 118:
#line 696 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].stringv_value));
	;}
    break;

  case 119:
#line 700 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(3) - (3)].stringv_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 120:
#line 709 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 123:
#line 717 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_pos, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 124:
#line 721 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_neg, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 125:
#line 725 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 126:
#line 729 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 127:
#line 733 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 128:
#line 737 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 129:
#line 741 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 130:
#line 745 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 131:
#line 749 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_equal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 132:
#line 753 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_notequal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 133:
#line 757 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 134:
#line 761 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 135:
#line 765 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 136:
#line 769 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 137:
#line 773 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 138:
#line 777 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 139:
#line 781 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 140:
#line 785 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 141:
#line 789 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 142:
#line 793 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 143:
#line 797 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_and_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 144:
#line 801 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 145:
#line 805 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 146:
#line 809 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 147:
#line 813 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 148:
#line 817 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_gt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 149:
#line 821 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_ge, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 150:
#line 825 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 151:
#line 829 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_le, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 152:
#line 833 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 153:
#line 837 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 154:
#line 841 "beacon.y"
    {
		(yyval.ast_value) = ast_new_instanceof((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 155:
#line 845 "beacon.y"
    {
		(yyval.ast_value) = ast_new_as((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 156:
#line 849 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_childa, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 157:
#line 853 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_not, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 158:
#line 857 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 159:
#line 861 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 160:
#line 865 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 161:
#line 869 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), ast_new_blank());
	;}
    break;

  case 162:
#line 873 "beacon.y"
    {
		(yyval.ast_value) = ast_new_this();
	;}
    break;

  case 163:
#line 877 "beacon.y"
    {
		(yyval.ast_value) = ast_new_super();
	;}
    break;

  case 165:
#line 884 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 166:
#line 888 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].stringv_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 167:
#line 892 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_add, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 168:
#line 896 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_sub, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 169:
#line 900 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_mul, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 170:
#line 904 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_div, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 171:
#line 908 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_mod, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 172:
#line 912 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_gt, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 173:
#line 916 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_ge, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 174:
#line 920 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_lt, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 175:
#line 924 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_le, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 176:
#line 928 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_eq, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 177:
#line 932 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_noteq, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 178:
#line 936 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_bit_or, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 179:
#line 940 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_bit_and, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 180:
#line 944 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_logic_or, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 181:
#line 948 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_logic_and, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 182:
#line 952 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_lshift, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 183:
#line 956 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_rshift, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 184:
#line 960 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_excor, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 185:
#line 964 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_not);
	;}
    break;

  case 186:
#line 968 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_childa);
	;}
    break;

  case 187:
#line 972 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_negative);
	;}
    break;

  case 192:
#line 982 "beacon.y"
    {
		(yyval.ast_value) = ast_new_true();
	;}
    break;

  case 193:
#line 986 "beacon.y"
    {
		(yyval.ast_value) = ast_new_false();
	;}
    break;

  case 194:
#line 990 "beacon.y"
    {
		(yyval.ast_value) = ast_new_null();
	;}
    break;

  case 195:
#line 999 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 196:
#line 1003 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 197:
#line 1009 "beacon.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 210:
#line 1027 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].stringv_value));
	;}
    break;

  case 211:
#line 1033 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].stringv_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 212:
#line 1039 "beacon.y"
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[(2) - (5)].stringv_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 213:
#line 1045 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 214:
#line 1049 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 215:
#line 1053 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 216:
#line 1057 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 218:
#line 1064 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 219:
#line 1070 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 220:
#line 1076 "beacon.y"
    {
		(yyval.ast_value) = ast_new_while((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 221:
#line 1082 "beacon.y"
    {
		(yyval.ast_value) = ast_new_break();
	;}
    break;

  case 222:
#line 1088 "beacon.y"
    {
		(yyval.ast_value) = ast_new_continue();
	;}
    break;

  case 223:
#line 1094 "beacon.y"
    {
		(yyval.ast_value) = ast_new_return((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 224:
#line 1100 "beacon.y"
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 225:
#line 1106 "beacon.y"
    {
		(yyval.ast_value) = ast_new_try((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 226:
#line 1112 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 227:
#line 1116 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 228:
#line 1122 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].stringv_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 229:
#line 1128 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (5)].ast_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 230:
#line 1132 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 231:
#line 1138 "beacon.y"
    {
		(yyval.ast_value) = ast_new_defer((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 232:
#line 1145 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 233:
#line 1149 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 234:
#line 1155 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3861 "beacon.tab.c"
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


#line 1163 "beacon.y"





