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
#define YYLAST   2385

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  240
/* YYNRULES -- Number of states.  */
#define YYNSTATES  628

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
     451,   454,   458,   462,   465,   468,   472,   476,   484,   491,
     498,   504,   506,   509,   511,   513,   515,   517,   519,   521,
     523,   525,   529,   532,   537,   539,   547,   551,   552,   556,
     558,   562,   565,   567,   571,   575,   577,   579,   582,   585,
     589,   593,   597,   601,   605,   609,   613,   617,   621,   625,
     629,   633,   637,   641,   645,   649,   653,   657,   661,   665,
     669,   673,   677,   681,   685,   689,   693,   697,   701,   705,
     709,   712,   715,   720,   724,   731,   737,   739,   741,   743,
     746,   751,   758,   765,   772,   779,   786,   793,   800,   807,
     814,   821,   828,   835,   842,   849,   856,   863,   870,   877,
     883,   889,   895,   897,   899,   901,   903,   905,   907,   909,
     911,   914,   917,   919,   921,   923,   925,   927,   929,   931,
     933,   935,   937,   939,   941,   945,   951,   957,   961,   967,
     972,   979,   981,   984,   988,   992,   995,   998,  1002,  1006,
    1010,  1012,  1015,  1022,  1028,  1032,  1035,  1039,  1042,  1044,
    1046
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
      -1,    57,   175,    -1,   145,    57,    54,    -1,   145,    57,
     175,    -1,    58,    54,    -1,    58,   175,    -1,   145,    58,
      54,    -1,   145,    58,   175,    -1,   143,   151,     7,    48,
     140,   141,    49,    -1,   143,   151,     7,    48,   141,    49,
      -1,   151,     7,    48,   140,   141,    49,    -1,   151,     7,
      48,   141,    49,    -1,   144,    -1,   143,   144,    -1,    73,
      -1,    74,    -1,    65,    -1,    66,    -1,    70,    -1,    71,
      -1,    72,    -1,     7,    -1,   146,     9,     7,    -1,   151,
       7,    -1,   147,     9,   151,     7,    -1,   153,    -1,    97,
      50,   147,    51,    77,   151,   175,    -1,   148,     9,   153,
      -1,    -1,    52,   150,    53,    -1,   151,    -1,   150,     9,
     151,    -1,   152,   149,    -1,     7,    -1,   152,    11,     7,
      -1,    50,   153,    51,    -1,   156,    -1,   154,    -1,    13,
     153,    -1,    14,   153,    -1,   153,    13,   153,    -1,   153,
      14,   153,    -1,   153,    15,   153,    -1,   153,    16,   153,
      -1,   153,    17,   153,    -1,   153,    32,   153,    -1,   153,
      22,   153,    -1,   153,    23,   153,    -1,   153,    30,   153,
      -1,   153,    47,   153,    -1,   153,    33,   153,    -1,   153,
      31,   153,    -1,   155,    34,   153,    -1,   155,    35,   153,
      -1,   155,    36,   153,    -1,   155,    37,   153,    -1,   155,
      38,   153,    -1,   155,    39,   153,    -1,   155,    40,   153,
      -1,   155,    41,   153,    -1,   155,    44,   153,    -1,   155,
      42,   153,    -1,   155,    43,   153,    -1,   153,    24,   153,
      -1,   153,    25,   153,    -1,   153,    26,   153,    -1,   153,
      27,   153,    -1,   153,    19,   153,    -1,   153,    20,   153,
      -1,   153,    91,   151,    -1,   153,    64,   151,    -1,    21,
     153,    -1,    18,   153,    -1,   154,    50,   148,    51,    -1,
     154,    50,    51,    -1,    75,   152,   149,    50,   148,    51,
      -1,    75,   152,   149,    50,    51,    -1,    59,    -1,    60,
      -1,   155,    -1,   152,   149,    -1,   153,     8,     7,   149,
      -1,   153,     8,    13,    50,   153,    51,    -1,   153,     8,
      14,    50,   153,    51,    -1,   153,     8,    15,    50,   153,
      51,    -1,   153,     8,    16,    50,   153,    51,    -1,   153,
       8,    17,    50,   153,    51,    -1,   153,     8,    24,    50,
     153,    51,    -1,   153,     8,    25,    50,   153,    51,    -1,
     153,     8,    26,    50,   153,    51,    -1,   153,     8,    27,
      50,   153,    51,    -1,   153,     8,    22,    50,   153,    51,
      -1,   153,     8,    23,    50,   153,    51,    -1,   153,     8,
      32,    50,   153,    51,    -1,   153,     8,    30,    50,   153,
      51,    -1,   153,     8,    33,    50,   153,    51,    -1,   153,
       8,    31,    50,   153,    51,    -1,   153,     8,    19,    50,
     153,    51,    -1,   153,     8,    20,    50,   153,    51,    -1,
     153,     8,    47,    50,   153,    51,    -1,   153,     8,    18,
      50,    51,    -1,   153,     8,    21,    50,    51,    -1,   153,
       8,    14,    50,    51,    -1,     5,    -1,     6,    -1,     3,
      -1,     4,    -1,    61,    -1,    62,    -1,    63,    -1,   158,
      -1,   157,   158,    -1,   153,   177,    -1,   159,    -1,   160,
      -1,   161,    -1,   162,    -1,   165,    -1,   166,    -1,   167,
      -1,   168,    -1,   169,    -1,   170,    -1,   173,    -1,   174,
      -1,   151,     7,    54,    -1,   151,     7,    34,   153,   177,
      -1,    56,     7,    34,   153,   177,    -1,    80,   153,   175,
      -1,    80,   153,   175,    82,   175,    -1,    80,   153,   175,
     163,    -1,    80,   153,   175,   163,    82,   175,    -1,   164,
      -1,   163,   164,    -1,    81,   153,   175,    -1,    83,   153,
     176,    -1,    84,   177,    -1,    85,   177,    -1,    79,   153,
     177,    -1,    88,   153,   177,    -1,    86,   175,   171,    -1,
     172,    -1,   171,   172,    -1,    87,    50,   151,     7,    51,
     175,    -1,    89,   153,    10,   153,    54,    -1,    89,   153,
      54,    -1,    90,   158,    -1,    48,   157,    49,    -1,    48,
      49,    -1,    54,    -1,   175,    -1,    54,    -1
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
     547,   551,   555,   562,   566,   570,   574,   581,   585,   589,
     593,   600,   604,   611,   615,   619,   623,   630,   634,   638,
     645,   649,   656,   660,   667,   671,   675,   683,   686,   693,
     697,   704,   711,   715,   724,   728,   729,   732,   736,   740,
     744,   748,   752,   756,   760,   764,   768,   772,   776,   780,
     784,   788,   792,   796,   800,   804,   808,   812,   816,   820,
     824,   828,   832,   836,   840,   844,   848,   852,   856,   860,
     864,   868,   872,   876,   880,   884,   888,   892,   896,   899,
     903,   907,   911,   915,   919,   923,   927,   931,   935,   939,
     943,   947,   951,   955,   959,   963,   967,   971,   975,   979,
     983,   987,   993,   994,   995,   996,   997,  1001,  1005,  1014,
    1018,  1024,  1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,
    1036,  1037,  1038,  1039,  1042,  1048,  1054,  1060,  1064,  1068,
    1072,  1078,  1079,  1085,  1091,  1097,  1103,  1109,  1115,  1121,
    1127,  1131,  1137,  1143,  1147,  1153,  1160,  1164,  1170,  1174,
    1177
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
     140,   140,   140,   141,   141,   141,   141,   142,   142,   142,
     142,   143,   143,   144,   144,   144,   144,   145,   145,   145,
     146,   146,   147,   147,   148,   148,   148,   149,   149,   150,
     150,   151,   152,   152,   153,   153,   153,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   156,   156,   156,   156,   156,   156,   156,   157,
     157,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   159,   160,   161,   162,   162,   162,
     162,   163,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   171,   172,   173,   173,   174,   175,   175,   176,   176,
     177
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
       2,     3,     3,     2,     2,     3,     3,     7,     6,     6,
       5,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     4,     1,     7,     3,     0,     3,     1,
       3,     2,     1,     3,     3,     1,     1,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     3,     6,     5,     1,     1,     1,     2,
       4,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     5,
       5,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     5,     5,     3,     5,     4,
       6,     1,     2,     3,     3,     2,     2,     3,     3,     3,
       1,     2,     6,     5,     3,     2,     3,     2,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,    23,     4,    25,     1,
     194,   195,   192,   193,   122,     0,     0,     0,     0,     0,
       0,   166,   167,   196,   197,   198,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     8,
       9,     0,   117,     0,   126,   168,   125,     7,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
       2,    24,   117,   127,   128,   161,   160,     0,     0,   117,
       0,    21,     0,     0,     0,     0,   240,   225,   226,     0,
       0,     0,     0,   235,     0,     0,     0,   169,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   201,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   169,   124,     0,     0,     0,     0,    19,    10,
     227,   217,   238,   239,   224,   237,     0,   199,     0,   229,
     230,   228,     0,   234,     0,   214,   123,     0,   119,   117,
     117,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   129,   130,   131,   132,   133,   156,   157,   135,   136,
     152,   153,   154,   155,   137,   140,   134,   139,   138,   159,
     158,   163,     0,     0,   114,   141,   142,   143,   144,   145,
     146,   147,   148,   150,   151,   149,     0,     0,     0,     0,
       0,    22,     0,     0,     0,     0,     0,    17,    20,     0,
      13,    14,    16,    15,     0,     0,   219,   221,   236,   200,
       0,   231,     0,     0,     0,   118,   121,   170,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     162,   216,   165,     0,     0,     0,     0,   112,     0,    27,
       0,     0,     0,     0,    18,    11,     0,   218,     0,   222,
       0,   233,   215,   120,     0,   191,     0,     0,     0,     0,
     189,     0,     0,   190,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   116,   164,     0,     0,
       0,     0,     0,    26,     0,    40,     0,    40,     0,    12,
     223,   220,     0,   171,   172,   173,   174,   175,   186,   187,
     180,   181,   176,   177,   178,   179,   183,   185,   182,   184,
     188,     0,    61,   113,     0,     0,    40,    31,     0,    29,
       0,   107,   108,   109,     0,    41,    42,     0,     0,     0,
     110,     0,     0,     0,    60,     0,     0,     0,    28,    40,
      38,    43,     0,    40,    34,     0,    36,   232,     0,    40,
      32,    30,     0,   105,   106,   103,   104,     0,     0,    44,
      45,    47,    48,    49,    50,    51,     0,   101,     0,     0,
     111,    37,   115,     0,    39,    27,     0,     0,   101,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
     102,     0,     0,     0,    35,    33,     0,     0,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    88,     0,    58,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    87,
       0,     0,     0,     0,     0,     0,     0,     0,    59,     0,
      58,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    89,    90,    93,    94,     0,
       0,   100,     0,     0,     0,     0,    57,    56,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    98,    99,    91,    92,    95,
      96,     0,     0,     0,    52,     0,     0,     0,    86,     0,
       0,     0,     0,    84,     0,     0,    85,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    97,    65,
       0,    55,     0,     0,     0,    66,    67,    68,    69,    70,
      81,    82,    75,    76,    71,    72,    73,    74,    78,    80,
      77,    79,    83,    64,    54,    63,     0,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    38,    39,   129,   217,   218,   219,    72,
       5,     6,   270,   313,   348,   349,   220,   221,   222,   223,
     354,   355,   356,   389,   390,   391,   498,   538,   499,    40,
     392,   393,   394,   492,   493,   395,   396,   397,   357,   361,
     209,   193,    87,   147,   210,    62,    43,    44,    45,    46,
     136,    47,    48,    49,    50,    51,   226,   227,    52,    53,
      54,    55,    56,    57,   139,   140,    58,    59,   133,   134,
      77
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -443
static const yytype_int16 yypact[] =
{
     687,   -80,    24,   341,   775,   -18,  -443,  -443,  -443,  -443,
    -443,  -443,  -443,  -443,  -443,  2275,  2275,  2275,  2275,  2275,
      35,  -443,  -443,  -443,  -443,  -443,    37,    87,   100,  2275,
    2275,  2275,    56,    56,   154,  2275,  2275,  1039,  -443,  -443,
    -443,   218,   123,  1148,   159,   954,  -443,  -443,  -443,  -443,
    -443,  -443,  -443,  -443,  -443,  -443,  -443,  -443,  -443,  -443,
    -443,  -443,   123,   184,   184,   184,   184,  1174,   204,   123,
     207,  -443,   181,  1148,  1227,   573,  -443,  -443,  -443,   863,
     164,  1148,  1122,  -443,   -14,   303,    37,   313,  1049,  2275,
    2275,  2275,  2275,  2275,  2275,  2275,  2275,  2275,  2275,  2275,
    2275,  2275,  2275,  2275,  2275,  2275,  2275,    37,    37,  -443,
      11,  2275,  2275,  2275,  2275,  2275,  2275,  2275,  2275,  2275,
    2275,  2275,  -443,  -443,  2275,   282,    -2,   331,   401,  -443,
    -443,    45,  -443,  -443,  -443,  -443,   951,  -443,   290,   164,
    -443,  -443,  2275,  -443,  2275,  -443,  -443,     3,  -443,   123,
     291,   317,   327,   330,   342,   345,   346,   348,   349,   355,
     356,   357,   358,   360,   361,   362,   364,   368,   372,   373,
     378,   166,   166,    13,    13,    13,   477,   477,  2159,  2159,
     200,   200,   200,   200,  2219,  2194,   880,   792,   960,  -443,
    -443,  -443,   382,    81,  2124,  2124,  2124,  2124,  2124,  2124,
    2124,  2124,  2124,  2124,  2124,  2124,  1148,   183,   239,    84,
     374,  -443,   285,   426,   426,   428,   100,  -443,   401,   407,
    -443,  -443,  -443,  -443,  2275,   154,    48,  -443,  -443,  -443,
      37,  -443,  1263,  1148,    37,  -443,  -443,  -443,  2275,  2256,
    2275,  2275,  2275,   406,  2275,  2275,   408,  2275,  2275,  2275,
    2275,  2275,  2275,  2275,  2275,  2275,  2275,  2275,    37,  2275,
    -443,  -443,  -443,    86,    37,    37,   381,  -443,   426,   409,
      -1,   274,   415,   181,  -443,  -443,  1227,  -443,   154,  -443,
     460,  -443,  -443,  -443,  1289,  -443,  1342,  1388,  1434,  1480,
    -443,  1526,  1572,  -443,  1618,  1664,  1710,  1756,  1802,  1848,
    1894,  1940,  1986,  2032,  2078,   105,  2124,  -443,   -21,   465,
      37,   309,   466,  -443,    37,   301,    37,   301,   467,  -443,
    -443,  -443,   424,  -443,  -443,  -443,  -443,  -443,  -443,  -443,
    -443,  -443,  -443,  -443,  -443,  -443,  -443,  -443,  -443,  -443,
    -443,   399,  -443,  -443,   -21,    37,   301,  -443,    22,  -443,
     109,  -443,  -443,  -443,   429,   301,  -443,   470,   201,   432,
    -443,   263,   154,    37,  -443,   211,   433,   466,  -443,   301,
    -443,  -443,    23,   301,  -443,   151,  -443,  -443,   154,   301,
    -443,  -443,   434,  -443,  -443,  -443,  -443,    46,  2338,    23,
    -443,  -443,  -443,  -443,  -443,  -443,    51,    37,   479,   435,
    -443,  -443,  -443,   438,  -443,   409,   439,   106,  -443,   447,
     449,   469,   482,   483,   484,   486,   487,   488,   489,   496,
     499,   511,   512,   513,   514,   515,   516,   517,   520,  -443,
    -443,   503,   509,   -13,  -443,  -443,   521,    31,   409,    37,
      47,    37,    37,    37,   523,    37,    37,   524,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    37,   528,
     525,   318,  -443,    50,   567,   168,   530,   175,   501,   185,
     186,   189,   196,   505,   202,   203,   506,   209,   212,   214,
     215,   223,   230,   232,   266,   267,   270,   277,   318,  -443,
      -9,    52,   312,   535,   292,   508,   283,   319,  -443,   -21,
     567,    80,   531,    37,   532,   534,   536,   537,    37,   538,
     539,    37,   540,   541,   542,   546,   547,   548,   549,   551,
     552,   553,   554,   312,   545,  -443,  -443,  -443,  -443,   563,
     533,  -443,    74,   174,    37,   557,  -443,  -443,   585,  -443,
     -21,   559,   286,    37,   -21,    37,    37,    37,    37,   -21,
      37,    37,   -21,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,   589,  -443,  -443,  -443,  -443,  -443,
    -443,   -21,    37,   264,  -443,    37,   562,   -21,  -443,   -21,
     -21,   -21,   -21,  -443,   -21,   -21,  -443,   -21,   -21,   -21,
     -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,  -443,  -443,
     -21,  -443,   300,   -21,    37,  -443,  -443,  -443,  -443,  -443,
    -443,  -443,  -443,  -443,  -443,  -443,  -443,  -443,  -443,  -443,
    -443,  -443,  -443,  -443,  -443,  -443,   -21,  -443
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -443,  -443,  -443,   636,  -443,   370,   423,  -443,  -443,   450,
    -443,   643,  -208,  -383,  -443,   284,  -443,  -443,  -443,  -443,
    -310,  -443,   308,  -443,   276,  -443,  -443,  -443,   167,  -443,
    -443,  -443,  -443,   180,  -157,  -443,   288,   -22,  -442,  -443,
      72,  -205,   -58,    42,    99,    -3,    49,  -443,  -443,  -443,
    -443,   -27,  -443,  -443,  -443,  -443,  -443,   443,  -443,  -443,
    -443,  -443,  -443,  -443,  -443,   544,  -443,  -443,   -26,   133,
     -30
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -122
static const yytype_int16 yytable[] =
{
      42,    42,   263,    78,   122,    14,   271,   359,    80,   314,
      83,   125,   234,   109,    10,    11,    12,    13,    14,   494,
     144,    88,   436,    69,    15,    16,     7,    79,     8,    17,
      14,   367,    18,   132,    42,   461,   366,     2,    14,    79,
     145,   462,    68,   130,    14,   525,   494,   315,   131,   208,
     530,   141,   137,   405,    14,   466,   235,    14,    14,   382,
     311,    19,   191,   399,    63,    64,    65,    66,    67,   403,
      21,    22,    23,    24,    25,   368,    42,   107,    73,    74,
      75,   530,   464,   149,    81,    82,    26,    14,   383,   384,
     259,   236,   237,   265,    70,   259,   385,   386,   468,   387,
      79,   495,    41,    41,   149,   149,   527,    71,   192,   229,
      76,   383,   384,   438,   265,   388,   383,   384,   234,   385,
     386,   406,    79,   149,   385,   386,   224,   225,   567,   224,
     278,   541,   260,    42,    85,   266,    41,   307,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   341,   369,   400,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   383,   384,   206,    88,    86,   261,   265,    41,   385,
     386,    91,    92,    93,   265,   148,    10,    11,    12,    13,
      14,   232,   127,   233,   265,   265,    15,    16,   265,   277,
     401,    17,    79,   282,    18,   265,   189,   190,    88,   110,
     234,   265,   265,    89,    90,    91,    92,    93,   265,   500,
     234,   265,    79,   265,   265,    84,   502,   149,   569,   128,
     107,   149,   265,    19,   262,    41,   504,   505,   124,   265,
     506,   265,    21,    22,    23,    24,    25,   507,   107,   373,
     320,   138,   321,   509,   510,   149,   194,   126,    26,   379,
     512,   149,   149,   513,   107,   514,   515,    10,    11,    12,
      13,    14,   375,   276,   516,   265,   265,    15,    16,   265,
     192,   517,    17,   518,   316,    18,   265,   284,   286,   287,
     288,   289,   265,   291,   292,   265,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   149,   306,   259,
     146,   149,   376,   149,    19,   601,   264,   519,   520,   345,
    -121,   521,   317,    21,    22,    23,    24,    25,   522,   280,
     305,   524,   207,   283,   535,   529,   377,   576,   211,    26,
     230,     9,   149,    86,    10,    11,    12,    13,    14,   532,
     533,   624,   402,   268,    15,    16,   350,   346,   358,    17,
     149,   192,    18,   308,   309,   408,   564,   238,   602,   149,
     491,   351,   352,   353,   430,   490,   491,   239,   536,   537,
     240,   267,   351,   352,   353,   430,   149,   365,   351,   352,
     353,    19,   241,   149,   149,   242,   243,    20,   244,   245,
      21,    22,    23,    24,    25,   246,   247,   248,   249,   344,
     250,   251,   252,   148,   253,   148,    26,    27,   254,    28,
      29,    30,   255,   256,    31,    32,    33,    34,   257,    35,
      36,    37,   258,   269,   149,   272,   149,   149,   149,   149,
     149,   342,   149,   149,   148,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   275,   290,   310,   293,
     149,   312,   378,   318,   526,   528,   212,   322,   213,   214,
     215,   398,   343,   347,   360,   362,   363,   364,   370,   216,
     372,   374,   380,   404,   434,    88,   433,   435,   398,   437,
      89,    90,    91,    92,    93,   431,   432,   439,   149,   440,
     149,    98,    99,   100,   101,   149,   568,   570,   149,   465,
     459,   467,   469,   470,   471,   472,   460,   474,   475,   441,
     477,   478,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   149,   442,   443,   444,   496,   445,   446,   447,   448,
     149,   107,   149,   149,   149,   149,   449,   149,   149,   450,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   451,   452,   453,   454,   455,   456,   457,   108,   149,
     458,   463,   149,   542,   473,   476,   488,   497,   503,   489,
     501,    88,   508,   511,   531,   534,    89,    90,    91,    92,
      93,   533,    94,    95,   565,    96,    97,    98,    99,   100,
     101,   149,   544,   102,   103,   104,   105,   549,   543,   545,
     552,   546,   566,   547,   548,   550,   551,   553,   554,   555,
     106,    79,   194,   556,   557,   558,   559,   132,   560,   561,
     562,   563,   539,   571,   572,   573,   575,   107,   598,   604,
      60,   274,   577,   319,   579,   580,   581,   582,    61,   584,
     585,   381,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   371,   108,   429,   273,   540,   523,   279,
       0,   600,     0,   574,   603,   407,     0,   578,     0,     0,
       0,     0,   583,   231,     0,   586,     0,     0,     1,     0,
      -5,    -5,    -5,    -5,    -5,     0,     0,     0,     0,     0,
      -5,    -5,     0,   626,   599,    -5,     0,     0,    -5,     0,
     605,     0,   606,   607,   608,   609,     0,   610,   611,     0,
     612,   613,   614,   615,   616,   617,   618,   619,   620,   621,
     622,     0,     0,   623,     0,     0,   625,    -5,     0,     0,
       0,     0,     2,    -5,     0,     0,    -5,    -5,    -5,    -5,
      -5,     0,     0,     0,     0,     0,     0,     0,     0,   627,
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
       0,    17,     0,   108,    18,     0,     0,     0,    88,     0,
       0,     0,     0,    89,    90,    91,    92,    93,     0,    94,
      95,     0,     0,     0,    98,    99,   100,   101,     0,     0,
       0,     0,   135,    19,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    22,    23,    24,    25,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,     0,
       0,     0,    29,    30,   107,     0,    31,    32,    33,    34,
       0,    35,    36,    37,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,    15,    16,     0,     0,    88,    17,
       0,   108,    18,    89,    90,    91,    92,    93,     0,    94,
      95,     0,     0,     0,    98,    99,   100,   101,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,     0,
     228,    19,     0,     0,     0,     0,     0,    20,     0,     0,
      21,    22,    23,    24,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   107,     0,    26,     0,     0,     0,
      29,    30,     0,     0,    31,    32,    33,    34,     0,    35,
      36,    37,    10,    11,    12,    13,    14,     0,     0,     0,
       0,   108,    15,    16,     0,     0,   150,    17,     0,     0,
      18,     0,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,     0,     0,   166,
     167,   168,   169,     0,     0,     0,     0,     0,     0,    19,
       0,     0,     0,     0,     0,    20,   170,     0,    21,    22,
      23,    24,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    26,     0,     0,     0,    29,    30,
       0,     0,    31,    32,    33,    34,     0,    35,    36,    37,
      88,     0,   142,     0,     0,    89,    90,    91,    92,    93,
       0,    94,    95,     0,    96,    97,    98,    99,   100,   101,
       0,     0,   102,   103,   104,   105,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,     0,    94,    95,   106,
      96,    97,    98,    99,   100,   101,   143,     0,   102,   103,
     104,   105,    88,     0,     0,     0,   107,    89,    90,    91,
      92,    93,     0,    94,    95,   106,    96,    97,    98,    99,
     100,   101,    76,     0,   102,   103,   104,   105,     0,     0,
       0,     0,   107,   108,     0,     0,     0,     0,     0,     0,
       0,   106,     0,     0,     0,   123,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    88,     0,     0,   107,   108,
      89,    90,    91,    92,    93,     0,    94,    95,     0,    96,
      97,    98,    99,   100,   101,     0,     0,   102,   103,   104,
     105,     0,     0,     0,     0,   108,     0,     0,     0,     0,
       0,    88,     0,     0,   106,    79,    89,    90,    91,    92,
      93,     0,    94,    95,     0,    96,    97,    98,    99,   100,
     101,   107,     0,   102,   103,   104,   105,    88,     0,     0,
       0,     0,    89,    90,    91,    92,    93,     0,    94,    95,
     106,    96,    97,    98,    99,   100,   101,   281,   108,   102,
     103,   104,   105,     0,     0,     0,     0,   107,     0,     0,
       0,     0,     0,     0,     0,     0,   106,     0,     0,     0,
     323,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      88,     0,     0,   107,   108,    89,    90,    91,    92,    93,
       0,    94,    95,     0,    96,    97,    98,    99,   100,   101,
       0,     0,   102,   103,   104,   105,     0,     0,     0,     0,
     108,     0,     0,     0,     0,     0,     0,     0,     0,   106,
       0,     0,     0,   324,     0,     0,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,   107,    94,    95,     0,
      96,    97,    98,    99,   100,   101,     0,     0,   102,   103,
     104,   105,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,     0,   106,     0,     0,     0,   325,
       0,     0,    88,     0,     0,     0,     0,    89,    90,    91,
      92,    93,   107,    94,    95,     0,    96,    97,    98,    99,
     100,   101,     0,     0,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
       0,   106,     0,     0,     0,   326,     0,     0,    88,     0,
       0,     0,     0,    89,    90,    91,    92,    93,   107,    94,
      95,     0,    96,    97,    98,    99,   100,   101,     0,     0,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,     0,   106,     0,     0,
       0,   327,     0,     0,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,   107,    94,    95,     0,    96,    97,
      98,    99,   100,   101,     0,     0,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,     0,   106,     0,     0,     0,   328,     0,     0,
      88,     0,     0,     0,     0,    89,    90,    91,    92,    93,
     107,    94,    95,     0,    96,    97,    98,    99,   100,   101,
       0,     0,   102,   103,   104,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,     0,   106,
       0,     0,     0,   329,     0,     0,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,   107,    94,    95,     0,
      96,    97,    98,    99,   100,   101,     0,     0,   102,   103,
     104,   105,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,     0,   106,     0,     0,     0,   330,
       0,     0,    88,     0,     0,     0,     0,    89,    90,    91,
      92,    93,   107,    94,    95,     0,    96,    97,    98,    99,
     100,   101,     0,     0,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
       0,   106,     0,     0,     0,   331,     0,     0,    88,     0,
       0,     0,     0,    89,    90,    91,    92,    93,   107,    94,
      95,     0,    96,    97,    98,    99,   100,   101,     0,     0,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,     0,   106,     0,     0,
       0,   332,     0,     0,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,   107,    94,    95,     0,    96,    97,
      98,    99,   100,   101,     0,     0,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,     0,   106,     0,     0,     0,   333,     0,     0,
      88,     0,     0,     0,     0,    89,    90,    91,    92,    93,
     107,    94,    95,     0,    96,    97,    98,    99,   100,   101,
       0,     0,   102,   103,   104,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,     0,   106,
       0,     0,     0,   334,     0,     0,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,   107,    94,    95,     0,
      96,    97,    98,    99,   100,   101,     0,     0,   102,   103,
     104,   105,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,     0,   106,     0,     0,     0,   335,
       0,     0,    88,     0,     0,     0,     0,    89,    90,    91,
      92,    93,   107,    94,    95,     0,    96,    97,    98,    99,
     100,   101,     0,     0,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
       0,   106,     0,     0,     0,   336,     0,     0,    88,     0,
       0,     0,     0,    89,    90,    91,    92,    93,   107,    94,
      95,     0,    96,    97,    98,    99,   100,   101,     0,     0,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,     0,   106,     0,     0,
       0,   337,     0,     0,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,   107,    94,    95,     0,    96,    97,
      98,    99,   100,   101,     0,     0,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,     0,   106,     0,     0,     0,   338,     0,     0,
      88,     0,     0,     0,     0,    89,    90,    91,    92,    93,
     107,    94,    95,     0,    96,    97,    98,    99,   100,   101,
       0,     0,   102,   103,   104,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,     0,   106,
       0,     0,     0,   339,     0,     0,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,   107,    94,    95,     0,
      96,    97,    98,    99,   100,   101,     0,     0,   102,   103,
     104,   105,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,     0,   106,     0,     0,     0,   340,
       0,     0,    88,     0,     0,     0,     0,    89,    90,    91,
      92,    93,   107,    94,    95,     0,    96,    97,    98,    99,
     100,   101,     0,     0,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,     0,   108,
       0,   106,    89,    90,    91,    92,    93,     0,    94,    95,
       0,     0,     0,    98,    99,   100,   101,     0,   107,   102,
     103,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    88,     0,     0,     0,   106,    89,    90,    91,
      92,    93,     0,    94,    95,   108,     0,     0,    98,    99,
     100,   101,     0,   107,   102,     0,   104,    88,     0,     0,
       0,     0,    89,    90,    91,    92,    93,     0,    94,    95,
       0,   106,     0,    98,    99,   100,   101,     0,     0,     0,
     108,   104,     0,     0,     0,     0,     0,     0,   107,    10,
      11,    12,    13,    14,     0,     0,   106,     0,     0,    15,
      16,     0,     0,     0,    17,     0,     0,    18,    10,    11,
      12,    13,    14,   107,     0,   108,     0,     0,    15,    16,
       0,     0,     0,    17,     0,     0,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,   285,     0,     0,
     108,     0,     0,     0,     0,    21,    22,    23,    24,    25,
       0,     0,     0,     0,     0,    19,     0,     0,     0,     0,
       0,    26,     0,     0,    21,    22,    23,    24,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,     0,     0,   424,   425,
     426,   427,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   428
};

static const yytype_int16 yycheck[] =
{
       3,     4,   207,    33,    62,     7,   214,   317,    34,    10,
      37,    69,     9,    43,     3,     4,     5,     6,     7,   461,
      34,     8,   405,    26,    13,    14,   106,    48,     4,    18,
       7,     9,    21,    54,    37,    48,   346,    55,     7,    48,
      54,    54,     7,    73,     7,    54,   488,    48,    74,    51,
     492,    81,    79,     7,     7,   438,    53,     7,     7,   369,
     268,    50,    51,   373,    15,    16,    17,    18,    19,   379,
      59,    60,    61,    62,    63,    53,    79,    64,    29,    30,
      31,   523,    51,    86,    35,    36,    75,     7,    65,    66,
       9,   149,   150,     9,     7,     9,    73,    74,    51,    76,
      48,    51,     3,     4,   107,   108,    54,     7,    97,   136,
      54,    65,    66,     7,     9,    92,    65,    66,     9,    73,
      74,    75,    48,   126,    73,    74,    81,    82,    54,    81,
      82,    51,    51,   136,    11,    51,    37,    51,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,    51,    48,     7,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,    65,    66,   124,     8,    52,   206,     9,    79,    73,
      74,    15,    16,    17,     9,    86,     3,     4,     5,     6,
       7,   142,    11,   144,     9,     9,    13,    14,     9,   225,
      49,    18,    48,   233,    21,     9,   107,   108,     8,    50,
       9,     9,     9,    13,    14,    15,    16,    17,     9,    51,
       9,     9,    48,     9,     9,     7,    51,   230,    54,    48,
      64,   234,     9,    50,    51,   136,    51,    51,    34,     9,
      51,     9,    59,    60,    61,    62,    63,    51,    64,    48,
     276,    87,   278,    51,    51,   258,   207,    50,    75,    48,
      51,   264,   265,    51,    64,    51,    51,     3,     4,     5,
       6,     7,     9,   224,    51,     9,     9,    13,    14,     9,
      97,    51,    18,    51,    10,    21,     9,   238,   239,   240,
     241,   242,     9,   244,   245,     9,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   310,   259,     9,
       7,   314,    49,   316,    50,    51,    77,    51,    51,    10,
       7,    51,    48,    59,    60,    61,    62,    63,    51,   230,
     258,   488,    50,   234,    51,   492,   362,    51,     7,    75,
      50,     0,   345,    52,     3,     4,     5,     6,     7,    57,
      58,    51,   378,    68,    13,    14,   314,    48,   316,    18,
     363,    97,    21,   264,   265,   387,   523,    50,   573,   372,
      58,    70,    71,    72,   396,    57,    58,    50,    59,    60,
      50,     7,    70,    71,    72,   407,   389,   345,    70,    71,
      72,    50,    50,   396,   397,    50,    50,    56,    50,    50,
      59,    60,    61,    62,    63,    50,    50,    50,    50,   310,
      50,    50,    50,   314,    50,   316,    75,    76,    50,    78,
      79,    80,    50,    50,    83,    84,    85,    86,    50,    88,
      89,    90,    50,     7,   437,     7,   439,   440,   441,   442,
     443,   308,   445,   446,   345,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,    49,    51,    77,    51,
     463,    52,   363,    48,   490,   491,    65,     7,    67,    68,
      69,   372,     7,     7,     7,    51,    77,   344,    49,    78,
      10,    49,    49,    49,    49,     8,     7,    49,   389,    50,
      13,    14,    15,    16,    17,   396,   397,    50,   501,    50,
     503,    24,    25,    26,    27,   508,   532,   533,   511,   437,
       7,   439,   440,   441,   442,   443,     7,   445,   446,    50,
     448,   449,   450,   451,   452,   453,   454,   455,   456,   457,
     458,   534,    50,    50,    50,   463,    50,    50,    50,    50,
     543,    64,   545,   546,   547,   548,    50,   550,   551,    50,
     553,   554,   555,   556,   557,   558,   559,   560,   561,   562,
     563,    50,    50,    50,    50,    50,    50,    50,    91,   572,
      50,    50,   575,   501,    51,    51,    48,    10,    77,    54,
      50,     8,    77,    77,    49,    77,    13,    14,    15,    16,
      17,    58,    19,    20,    49,    22,    23,    24,    25,    26,
      27,   604,   503,    30,    31,    32,    33,   508,    77,    77,
     511,    77,    49,    77,    77,    77,    77,    77,    77,    77,
      47,    48,   573,    77,    77,    77,    77,    54,    77,    77,
      77,    77,   499,   534,    77,    50,    77,    64,    49,    77,
       4,   218,   543,   273,   545,   546,   547,   548,     5,   550,
     551,   367,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,   355,    91,   389,   216,   500,   488,   226,
      -1,   572,    -1,   540,   575,   387,    -1,   544,    -1,    -1,
      -1,    -1,   549,   139,    -1,   552,    -1,    -1,     1,    -1,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,
      13,    14,    -1,   604,   571,    18,    -1,    -1,    21,    -1,
     577,    -1,   579,   580,   581,   582,    -1,   584,   585,    -1,
     587,   588,   589,   590,   591,   592,   593,   594,   595,   596,
     597,    -1,    -1,   600,    -1,    -1,   603,    50,    -1,    -1,
      -1,    -1,    55,    56,    -1,    -1,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   626,
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
      -1,    18,    -1,    91,    21,    -1,    -1,    -1,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    -1,    -1,    -1,    24,    25,    26,    27,    -1,    -1,
      -1,    -1,    49,    50,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    59,    60,    61,    62,    63,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    79,    80,    64,    -1,    83,    84,    85,    86,
      -1,    88,    89,    90,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    -1,    13,    14,    -1,    -1,     8,    18,
      -1,    91,    21,    13,    14,    15,    16,    17,    -1,    19,
      20,    -1,    -1,    -1,    24,    25,    26,    27,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      49,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    -1,    75,    -1,    -1,    -1,
      79,    80,    -1,    -1,    83,    84,    85,    86,    -1,    88,
      89,    90,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      -1,    91,    13,    14,    -1,    -1,     7,    18,    -1,    -1,
      21,    -1,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    56,    47,    -1,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,
      -1,    -1,    83,    84,    85,    86,    -1,    88,    89,    90,
       8,    -1,    10,    -1,    -1,    13,    14,    15,    16,    17,
      -1,    19,    20,    -1,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    33,     8,    -1,    -1,    -1,
      -1,    13,    14,    15,    16,    17,    -1,    19,    20,    47,
      22,    23,    24,    25,    26,    27,    54,    -1,    30,    31,
      32,    33,     8,    -1,    -1,    -1,    64,    13,    14,    15,
      16,    17,    -1,    19,    20,    47,    22,    23,    24,    25,
      26,    27,    54,    -1,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    64,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    64,    91,
      13,    14,    15,    16,    17,    -1,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,
      -1,     8,    -1,    -1,    47,    48,    13,    14,    15,    16,
      17,    -1,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    64,    -1,    30,    31,    32,    33,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    19,    20,
      47,    22,    23,    24,    25,    26,    27,    54,    91,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       8,    -1,    -1,    64,    91,    13,    14,    15,    16,    17,
      -1,    19,    20,    -1,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,    91,
      -1,    47,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    -1,    -1,    24,    25,    26,    27,    -1,    64,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     8,    -1,    -1,    -1,    47,    13,    14,    15,
      16,    17,    -1,    19,    20,    91,    -1,    -1,    24,    25,
      26,    27,    -1,    64,    30,    -1,    32,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    47,    -1,    24,    25,    26,    27,    -1,    -1,    -1,
      91,    32,    -1,    -1,    -1,    -1,    -1,    -1,    64,     3,
       4,     5,     6,     7,    -1,    -1,    47,    -1,    -1,    13,
      14,    -1,    -1,    -1,    18,    -1,    -1,    21,     3,     4,
       5,     6,     7,    64,    -1,    91,    -1,    -1,    13,    14,
      -1,    -1,    -1,    18,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47
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
      57,    58,   140,   141,   145,    51,   147,    10,   133,   135,
      51,    50,    51,    77,    51,    51,    51,    51,    77,    51,
      51,    77,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,   140,   141,    54,   175,    54,   175,   141,
     145,    49,    57,    58,    77,    51,    59,    60,   134,   176,
     135,    51,   147,    77,   151,    77,    77,    77,    77,   151,
      77,    77,   151,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,   141,    49,    49,    54,   175,    54,
     175,   151,    77,    50,   176,    77,    51,   151,   176,   151,
     151,   151,   151,   176,   151,   151,   176,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,    49,   176,
     151,    51,   148,   151,    77,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,    51,   176,   151,   176
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
		(yyval.ast_value) = ast_new_prop_set(ast_new_blank(), ast_new_blank());
	;}
    break;

  case 90:
#line 548 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_blank(), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 91:
#line 552 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_access((yyvsp[(1) - (3)].access_level_value)), ast_new_blank());
	;}
    break;

  case 92:
#line 556 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_access((yyvsp[(1) - (3)].access_level_value)), ast_new_blank());
	;}
    break;

  case 93:
#line 563 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_blank(), ast_new_blank());
	;}
    break;

  case 94:
#line 567 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_blank(), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 95:
#line 571 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_access((yyvsp[(1) - (3)].access_level_value)), ast_new_blank());
	;}
    break;

  case 96:
#line 575 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_access((yyvsp[(1) - (3)].access_level_value)), ast_new_blank());
	;}
    break;

  case 97:
#line 582 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_decl((yyvsp[(1) - (7)].ast_value), (yyvsp[(2) - (7)].ast_value), (yyvsp[(3) - (7)].stringv_value), (yyvsp[(5) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 98:
#line 586 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_decl((yyvsp[(1) - (6)].ast_value), (yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].stringv_value), ast_new_blank(), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 99:
#line 590 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_decl(ast_new_modifier(modifier_none), (yyvsp[(1) - (6)].ast_value), (yyvsp[(2) - (6)].stringv_value), (yyvsp[(4) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 100:
#line 594 "beacon.y"
    {
		(yyval.ast_value) = ast_new_prop_decl(ast_new_modifier(modifier_none), (yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].stringv_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 101:
#line 601 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 102:
#line 605 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 103:
#line 612 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_static);
	;}
    break;

  case 104:
#line 616 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_native);
	;}
    break;

  case 105:
#line 620 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_abstract);
	;}
    break;

  case 106:
#line 624 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_override);
	;}
    break;

  case 107:
#line 631 "beacon.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 108:
#line 635 "beacon.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 109:
#line 639 "beacon.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 110:
#line 646 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[(1) - (1)].stringv_value));
	;}
    break;

  case 111:
#line 650 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[(3) - (3)].stringv_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 112:
#line 657 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].stringv_value));
	;}
    break;

  case 113:
#line 661 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].stringv_value), (yyvsp[(1) - (4)].ast_value))
	;}
    break;

  case 114:
#line 668 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 115:
#line 672 "beacon.y"
    {
		(yyval.ast_value) = ast_new_lambda((yyvsp[(3) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 116:
#line 676 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(3) - (3)].ast_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 117:
#line 683 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 118:
#line 687 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 119:
#line 694 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 120:
#line 698 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 121:
#line 705 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 122:
#line 712 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].stringv_value));
	;}
    break;

  case 123:
#line 716 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(3) - (3)].stringv_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 124:
#line 725 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 127:
#line 733 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_pos, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 128:
#line 737 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_neg, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 129:
#line 741 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 130:
#line 745 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 131:
#line 749 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 132:
#line 753 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 133:
#line 757 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 134:
#line 761 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 135:
#line 765 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_equal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 136:
#line 769 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_notequal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 137:
#line 773 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 138:
#line 777 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 139:
#line 781 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 140:
#line 785 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 141:
#line 789 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 142:
#line 793 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 143:
#line 797 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 144:
#line 801 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 145:
#line 805 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 146:
#line 809 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 147:
#line 813 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_and_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 148:
#line 817 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 149:
#line 821 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 150:
#line 825 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 151:
#line 829 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 152:
#line 833 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_gt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 153:
#line 837 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_ge, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 154:
#line 841 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 155:
#line 845 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_le, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 156:
#line 849 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 157:
#line 853 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 158:
#line 857 "beacon.y"
    {
		(yyval.ast_value) = ast_new_instanceof((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 159:
#line 861 "beacon.y"
    {
		(yyval.ast_value) = ast_new_as((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 160:
#line 865 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_childa, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 161:
#line 869 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_not, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 162:
#line 873 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 163:
#line 877 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 164:
#line 881 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 165:
#line 885 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), ast_new_blank());
	;}
    break;

  case 166:
#line 889 "beacon.y"
    {
		(yyval.ast_value) = ast_new_this();
	;}
    break;

  case 167:
#line 893 "beacon.y"
    {
		(yyval.ast_value) = ast_new_super();
	;}
    break;

  case 169:
#line 900 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 170:
#line 904 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].stringv_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 171:
#line 908 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_add, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 172:
#line 912 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_sub, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 173:
#line 916 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_mul, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 174:
#line 920 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_div, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 175:
#line 924 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_mod, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 176:
#line 928 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_gt, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 177:
#line 932 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_ge, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 178:
#line 936 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_lt, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 179:
#line 940 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_le, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 180:
#line 944 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_eq, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 181:
#line 948 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_noteq, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 182:
#line 952 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_bit_or, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 183:
#line 956 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_bit_and, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 184:
#line 960 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_logic_or, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 185:
#line 964 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_logic_and, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 186:
#line 968 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_lshift, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 187:
#line 972 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_rshift, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 188:
#line 976 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_excor, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 189:
#line 980 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_not);
	;}
    break;

  case 190:
#line 984 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_childa);
	;}
    break;

  case 191:
#line 988 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_negative);
	;}
    break;

  case 196:
#line 998 "beacon.y"
    {
		(yyval.ast_value) = ast_new_true();
	;}
    break;

  case 197:
#line 1002 "beacon.y"
    {
		(yyval.ast_value) = ast_new_false();
	;}
    break;

  case 198:
#line 1006 "beacon.y"
    {
		(yyval.ast_value) = ast_new_null();
	;}
    break;

  case 199:
#line 1015 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 200:
#line 1019 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 201:
#line 1025 "beacon.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 214:
#line 1043 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].stringv_value));
	;}
    break;

  case 215:
#line 1049 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].stringv_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 216:
#line 1055 "beacon.y"
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[(2) - (5)].stringv_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 217:
#line 1061 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 218:
#line 1065 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 219:
#line 1069 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 220:
#line 1073 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 222:
#line 1080 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 223:
#line 1086 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 224:
#line 1092 "beacon.y"
    {
		(yyval.ast_value) = ast_new_while((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 225:
#line 1098 "beacon.y"
    {
		(yyval.ast_value) = ast_new_break();
	;}
    break;

  case 226:
#line 1104 "beacon.y"
    {
		(yyval.ast_value) = ast_new_continue();
	;}
    break;

  case 227:
#line 1110 "beacon.y"
    {
		(yyval.ast_value) = ast_new_return((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 228:
#line 1116 "beacon.y"
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 229:
#line 1122 "beacon.y"
    {
		(yyval.ast_value) = ast_new_try((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 230:
#line 1128 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 231:
#line 1132 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 232:
#line 1138 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].stringv_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 233:
#line 1144 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (5)].ast_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 234:
#line 1148 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 235:
#line 1154 "beacon.y"
    {
		(yyval.ast_value) = ast_new_defer((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 236:
#line 1161 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 237:
#line 1165 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 238:
#line 1171 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3887 "beacon.tab.c"
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


#line 1179 "beacon.y"





