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
     ASSERT_T = 346,
     DEFER = 347,
     INSTANCEOF = 348,
     OPERATOR = 349,
     BOUNDS_EXTENDS = 350,
     BOUNDS_SUPER = 351,
     PRE_DEC = 352,
     PRE_INC = 353,
     QUOTE = 354,
     POST_DEC = 355,
     POST_INC = 356,
     FUNCCALL = 357,
     REF = 358,
     POSITIVE = 359,
     NEGATIVE = 360,
     FORM_TYPE = 361
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
#define YIELD 336
#define IF 337
#define ELIF 338
#define ELSE 339
#define WHILE 340
#define BREAK 341
#define CONTINUE 342
#define TRY 343
#define CATCH 344
#define THROW 345
#define ASSERT_T 346
#define DEFER 347
#define INSTANCEOF 348
#define OPERATOR 349
#define BOUNDS_EXTENDS 350
#define BOUNDS_SUPER 351
#define PRE_DEC 352
#define PRE_INC 353
#define QUOTE 354
#define POST_DEC 355
#define POST_INC 356
#define FUNCCALL 357
#define REF 358
#define POSITIVE 359
#define NEGATIVE 360
#define FORM_TYPE 361




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
#line 334 "beacon.tab.c"
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
#line 359 "beacon.tab.c"

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
#define YYLAST   2495

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  109
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  242
/* YYNRULES -- Number of states.  */
#define YYNSTATES  635

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   361

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     108,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     103,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      95,    96,    97,    98,    99,   100,   101,   102,   104,   105,
     106,   107
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
     518,   521,   526,   528,   536,   540,   541,   545,   547,   551,
     554,   556,   560,   564,   566,   568,   571,   574,   578,   582,
     586,   590,   594,   598,   602,   606,   610,   614,   618,   622,
     626,   630,   634,   638,   642,   646,   650,   654,   658,   662,
     666,   670,   674,   678,   682,   686,   690,   694,   698,   701,
     704,   709,   713,   720,   726,   728,   730,   732,   735,   740,
     747,   754,   761,   768,   775,   782,   789,   796,   803,   810,
     817,   824,   831,   838,   845,   852,   859,   866,   872,   878,
     884,   886,   888,   890,   892,   894,   896,   898,   900,   903,
     906,   908,   910,   912,   914,   916,   918,   920,   922,   924,
     926,   928,   930,   932,   934,   938,   944,   950,   954,   960,
     965,   972,   974,   977,   981,   985,   988,   991,   995,   999,
    1003,  1005,  1008,  1015,  1021,  1025,  1028,  1033,  1037,  1041,
    1044,  1046,  1048
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     110,     0,    -1,   111,   112,    -1,   110,   112,    -1,     1,
     108,    -1,    -1,   119,    -1,   160,    -1,   113,    -1,   138,
      -1,    79,   118,   114,    -1,    48,   117,    49,    -1,    79,
     118,   114,    -1,   125,    -1,   126,    -1,   128,    -1,   127,
      -1,   115,    -1,   116,   115,    -1,    -1,   116,    -1,     7,
      -1,   118,    11,     7,    -1,   120,    -1,   119,   120,    -1,
      55,     4,    -1,     7,   122,    -1,    -1,    52,   123,    53,
      -1,   124,    -1,   123,     9,   124,    -1,     7,    -1,    66,
      69,   121,    48,   129,    49,    -1,    66,    69,   121,    10,
     152,    48,   129,    49,    -1,    69,   121,    48,   129,    49,
      -1,    69,   121,    10,   152,    48,   129,    49,    -1,    70,
       7,    48,   148,    49,    -1,    70,     7,    48,   148,     9,
      49,    -1,    68,   121,    48,   129,    49,    -1,    68,   121,
      10,   152,    48,   129,    49,    -1,    -1,   130,    -1,   131,
      -1,   130,   131,    -1,   147,    10,   132,    -1,   133,    -1,
     132,   133,    -1,   134,    -1,   139,    -1,   140,    -1,   141,
      -1,   144,    -1,    77,    76,    50,   149,    51,   137,   180,
      -1,    77,    76,    50,    51,   137,   180,    -1,    10,   136,
      50,   150,    51,    -1,    10,   136,    50,    51,    -1,    61,
      -1,    60,    -1,    -1,   135,    -1,    77,     7,    50,   149,
      51,    78,   153,   180,    -1,    77,     7,    50,    51,    78,
     153,   180,    -1,    77,   145,     7,   122,    50,   149,    51,
      78,   153,   180,    -1,    77,   145,     7,   122,    50,    51,
      78,   153,   180,    -1,    77,     7,   122,    50,   149,    51,
      78,   153,   180,    -1,    77,     7,   122,    50,    51,    78,
     153,   180,    -1,    94,    13,    50,   149,    51,    78,   153,
     180,    -1,    94,    14,    50,   149,    51,    78,   153,   180,
      -1,    94,    15,    50,   149,    51,    78,   153,   180,    -1,
      94,    16,    50,   149,    51,    78,   153,   180,    -1,    94,
      17,    50,   149,    51,    78,   153,   180,    -1,    94,    24,
      50,   149,    51,    78,   153,   180,    -1,    94,    25,    50,
     149,    51,    78,   153,   180,    -1,    94,    26,    50,   149,
      51,    78,   153,   180,    -1,    94,    27,    50,   149,    51,
      78,   153,   180,    -1,    94,    22,    50,   149,    51,    78,
     153,   180,    -1,    94,    23,    50,   149,    51,    78,   153,
     180,    -1,    94,    32,    50,   149,    51,    78,   153,   180,
      -1,    94,    30,    50,   149,    51,    78,   153,   180,    -1,
      94,    33,    50,   149,    51,    78,   153,   180,    -1,    94,
      31,    50,   149,    51,    78,   153,   180,    -1,    94,    19,
      50,   149,    51,    78,   153,   180,    -1,    94,    20,    50,
     149,    51,    78,   153,   180,    -1,    94,    47,    50,   149,
      51,    78,   153,   180,    -1,    94,    18,    50,    51,    78,
     153,   180,    -1,    94,    21,    50,    51,    78,   153,   180,
      -1,    94,    14,    50,    51,    78,   153,   180,    -1,   146,
     153,     7,    54,    -1,   153,     7,    54,    -1,    58,    54,
      -1,    58,   179,    -1,   147,    58,    54,    -1,   147,    58,
     179,    -1,    59,    54,    -1,    59,   179,    -1,   147,    59,
      54,    -1,   147,    59,   179,    -1,    57,   145,   153,     7,
      48,   142,   143,    49,    -1,    57,   153,     7,    48,   142,
     143,    49,    -1,   146,    -1,   145,   146,    -1,    74,    -1,
      75,    -1,    66,    -1,    67,    -1,    71,    -1,    72,    -1,
      73,    -1,     7,    -1,   148,     9,     7,    -1,   153,     7,
      -1,   149,     9,   153,     7,    -1,   155,    -1,    99,    50,
     149,    51,    78,   153,   179,    -1,   150,     9,   155,    -1,
      -1,    52,   152,    53,    -1,   153,    -1,   152,     9,   153,
      -1,   154,   151,    -1,     7,    -1,   154,    11,     7,    -1,
      50,   155,    51,    -1,   158,    -1,   156,    -1,    13,   155,
      -1,    14,   155,    -1,   155,    13,   155,    -1,   155,    14,
     155,    -1,   155,    15,   155,    -1,   155,    16,   155,    -1,
     155,    17,   155,    -1,   155,    32,   155,    -1,   155,    22,
     155,    -1,   155,    23,   155,    -1,   155,    30,   155,    -1,
     155,    47,   155,    -1,   155,    33,   155,    -1,   155,    31,
     155,    -1,   157,    34,   155,    -1,   157,    35,   155,    -1,
     157,    36,   155,    -1,   157,    37,   155,    -1,   157,    38,
     155,    -1,   157,    39,   155,    -1,   157,    40,   155,    -1,
     157,    41,   155,    -1,   157,    44,   155,    -1,   157,    42,
     155,    -1,   157,    43,   155,    -1,   155,    24,   155,    -1,
     155,    25,   155,    -1,   155,    26,   155,    -1,   155,    27,
     155,    -1,   155,    19,   155,    -1,   155,    20,   155,    -1,
     155,    93,   153,    -1,   155,    65,   153,    -1,    21,   155,
      -1,    18,   155,    -1,   156,    50,   150,    51,    -1,   156,
      50,    51,    -1,    76,   154,   151,    50,   150,    51,    -1,
      76,   154,   151,    50,    51,    -1,    60,    -1,    61,    -1,
     157,    -1,   154,   151,    -1,   155,     8,     7,   151,    -1,
     155,     8,    13,    50,   155,    51,    -1,   155,     8,    14,
      50,   155,    51,    -1,   155,     8,    15,    50,   155,    51,
      -1,   155,     8,    16,    50,   155,    51,    -1,   155,     8,
      17,    50,   155,    51,    -1,   155,     8,    24,    50,   155,
      51,    -1,   155,     8,    25,    50,   155,    51,    -1,   155,
       8,    26,    50,   155,    51,    -1,   155,     8,    27,    50,
     155,    51,    -1,   155,     8,    22,    50,   155,    51,    -1,
     155,     8,    23,    50,   155,    51,    -1,   155,     8,    32,
      50,   155,    51,    -1,   155,     8,    30,    50,   155,    51,
      -1,   155,     8,    33,    50,   155,    51,    -1,   155,     8,
      31,    50,   155,    51,    -1,   155,     8,    19,    50,   155,
      51,    -1,   155,     8,    20,    50,   155,    51,    -1,   155,
       8,    47,    50,   155,    51,    -1,   155,     8,    18,    50,
      51,    -1,   155,     8,    21,    50,    51,    -1,   155,     8,
      14,    50,    51,    -1,     5,    -1,     6,    -1,     3,    -1,
       4,    -1,    62,    -1,    63,    -1,    64,    -1,   160,    -1,
     159,   160,    -1,   155,   181,    -1,   161,    -1,   162,    -1,
     163,    -1,   164,    -1,   167,    -1,   168,    -1,   169,    -1,
     170,    -1,   171,    -1,   172,    -1,   175,    -1,   176,    -1,
     177,    -1,   178,    -1,   153,     7,    54,    -1,   153,     7,
      34,   155,   181,    -1,    56,     7,    34,   155,   181,    -1,
      82,   155,   179,    -1,    82,   155,   179,    84,   179,    -1,
      82,   155,   179,   165,    -1,    82,   155,   179,   165,    84,
     179,    -1,   166,    -1,   165,   166,    -1,    83,   155,   179,
      -1,    85,   155,   180,    -1,    86,   181,    -1,    87,   181,
      -1,    80,   155,   181,    -1,    90,   155,   181,    -1,    88,
     179,   173,    -1,   174,    -1,   173,   174,    -1,    89,    50,
     153,     7,    51,   179,    -1,    91,   155,    10,   155,   181,
      -1,    91,   155,   181,    -1,    92,   160,    -1,    81,    80,
     155,   181,    -1,    81,    86,   181,    -1,    48,   159,    49,
      -1,    48,    49,    -1,    54,    -1,   179,    -1,    54,    -1
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
     598,   605,   609,   613,   617,   624,   628,   632,   639,   643,
     650,   654,   661,   665,   669,   677,   680,   687,   691,   698,
     705,   709,   718,   722,   723,   726,   730,   734,   738,   742,
     746,   750,   754,   758,   762,   766,   770,   774,   778,   782,
     786,   790,   794,   798,   802,   806,   810,   814,   818,   822,
     826,   830,   834,   838,   842,   846,   850,   854,   858,   862,
     866,   870,   874,   878,   882,   886,   890,   893,   897,   901,
     905,   909,   913,   917,   921,   925,   929,   933,   937,   941,
     945,   949,   953,   957,   961,   965,   969,   973,   977,   981,
     987,   988,   989,   990,   991,   995,   999,  1008,  1012,  1018,
    1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,  1031,
    1032,  1033,  1034,  1035,  1038,  1044,  1050,  1056,  1060,  1064,
    1068,  1074,  1075,  1081,  1087,  1093,  1099,  1105,  1111,  1117,
    1123,  1127,  1133,  1139,  1143,  1149,  1155,  1161,  1167,  1171,
    1177,  1181,  1184
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
  "VAR", "PROPERTY", "DEFSET", "DEFGET", "THIS_TOK", "SUPER_TOK",
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
     355,   356,   357,    60,   358,   359,   360,   361,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   109,   110,   110,   110,   111,   111,   112,   112,   112,
     113,   114,   115,   115,   115,   115,   115,   116,   116,   117,
     117,   118,   118,   119,   119,   120,   121,   122,   122,   123,
     123,   124,   125,   125,   126,   126,   127,   127,   128,   128,
     129,   129,   130,   130,   131,   132,   132,   133,   133,   133,
     133,   133,   134,   134,   135,   135,   136,   136,   137,   137,
     138,   138,   139,   139,   139,   139,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   141,   141,   142,
     142,   142,   142,   143,   143,   143,   143,   144,   144,   145,
     145,   146,   146,   146,   146,   147,   147,   147,   148,   148,
     149,   149,   150,   150,   150,   151,   151,   152,   152,   153,
     154,   154,   155,   155,   155,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     158,   158,   158,   158,   158,   158,   158,   159,   159,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   161,   162,   163,   164,   164,   164,
     164,   165,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   173,   174,   175,   175,   176,   177,   178,   179,   179,
     180,   180,   181
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
       2,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     4,     1,     7,     3,     0,     3,     1,     3,     2,
       1,     3,     3,     1,     1,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       4,     3,     6,     5,     1,     1,     1,     2,     4,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     5,     5,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     5,     5,     3,     5,     4,
       6,     1,     2,     3,     3,     2,     2,     3,     3,     3,
       1,     2,     6,     5,     3,     2,     4,     3,     3,     2,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,    23,     4,    25,     1,
     192,   193,   190,   191,   120,     0,     0,     0,     0,     0,
       0,   164,   165,   194,   195,   196,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       8,     9,     0,   115,     0,   124,   166,   123,     7,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,     2,    24,   115,   125,   126,   159,   158,
       0,     0,   115,     0,    21,     0,     0,     0,     0,     0,
       0,   242,   225,   226,     0,     0,     0,     0,   235,     0,
       0,     0,   167,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   199,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   167,   122,     0,
       0,     0,     0,    19,    10,   227,     0,   237,   217,   240,
     241,   224,   239,     0,   197,     0,   229,   230,   228,     0,
     234,     0,   214,   121,     0,   117,   115,   115,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
     129,   130,   131,   154,   155,   133,   134,   150,   151,   152,
     153,   135,   138,   132,   137,   136,   157,   156,   161,     0,
       0,   112,   139,   140,   141,   142,   143,   144,   145,   146,
     148,   149,   147,     0,     0,     0,     0,     0,    22,     0,
       0,     0,     0,     0,    17,    20,     0,    13,    14,    16,
      15,   236,     0,     0,   219,   221,   238,   198,     0,   231,
       0,     0,     0,   116,   119,   168,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   160,   216,
     163,     0,     0,     0,     0,   110,     0,    27,     0,     0,
       0,     0,    18,    11,     0,   218,     0,   222,     0,   233,
     215,   118,     0,   189,     0,     0,     0,     0,   187,     0,
       0,   188,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   114,   162,     0,     0,     0,     0,
       0,    26,     0,    40,     0,    40,     0,    12,   223,   220,
       0,   169,   170,   171,   172,   173,   184,   185,   178,   179,
     174,   175,   176,   177,   181,   183,   180,   182,   186,     0,
      61,   111,     0,     0,    40,    31,     0,    29,     0,   105,
     106,   107,     0,    41,    42,     0,     0,     0,   108,     0,
       0,     0,    60,     0,     0,     0,    28,    40,    38,    43,
       0,    40,    34,     0,    36,   232,     0,    40,    32,    30,
       0,     0,   103,   104,   101,   102,     0,     0,    44,    45,
      47,    48,    49,    50,    51,     0,     0,     0,   109,    37,
     113,     0,    39,     0,    99,     0,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
       0,     0,    35,    33,   100,     0,     0,     0,     0,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    88,     0,     0,     0,    58,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    87,
       0,     0,     0,     0,     0,     0,     0,    59,     0,    58,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    89,    90,     0,     0,     0,     0,     0,
       0,    57,    56,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,    94,    98,     0,    91,    92,     0,     0,     0,    52,
       0,     0,     0,    86,     0,     0,     0,     0,    84,     0,
       0,    85,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    97,    95,    96,    65,     0,    55,     0,
       0,     0,    66,    67,    68,    69,    70,    81,    82,    75,
      76,    71,    72,    73,    74,    78,    80,    77,    79,    83,
      64,    54,    63,     0,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    39,    40,   134,   224,   225,   226,    75,
       5,     6,   278,   321,   356,   357,   227,   228,   229,   230,
     362,   363,   364,   398,   399,   400,   507,   543,   508,    41,
     401,   402,   403,   502,   536,   404,   413,   405,   365,   369,
     216,   200,    92,   154,   217,    65,    44,    45,    46,    47,
     143,    48,    49,    50,    51,    52,   234,   235,    53,    54,
      55,    56,    57,    58,   146,   147,    59,    60,    61,    62,
     140,   141,    82
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -461
static const yytype_int16 yypact[] =
{
     888,   -81,    35,   796,   921,    15,  -461,  -461,  -461,  -461,
    -461,  -461,  -461,  -461,  -461,  2349,  2349,  2349,  2349,  2349,
      42,  -461,  -461,  -461,  -461,  -461,    45,    97,   115,  2349,
      40,  2349,  2349,    80,    80,    90,  2349,  2349,  1134,  -461,
    -461,  -461,   193,    23,  1251,   129,   488,  -461,  -461,  -461,
    -461,  -461,  -461,  -461,  -461,  -461,  -461,  -461,  -461,  -461,
    -461,  -461,  -461,  -461,  -461,    23,   149,   149,   149,   149,
    1287,   161,    23,   174,  -461,    26,  1251,  2349,    80,  1334,
    1215,  -461,  -461,  -461,  1011,   142,  1251,  1023,  -461,   -10,
     241,    45,   242,  2413,  2349,  2349,  2349,  2349,  2349,  2349,
    2349,  2349,  2349,  2349,  2349,  2349,  2349,  2349,  2349,  2349,
    2349,  2349,    45,    45,  -461,   422,  2349,  2349,  2349,  2349,
    2349,  2349,  2349,  2349,  2349,  2349,  2349,  -461,  -461,  2349,
     203,    -1,   280,   290,  -461,  -461,  1251,  -461,   -28,  -461,
    -461,  -461,  -461,  1101,  -461,   240,   142,  -461,  -461,  2349,
    -461,  2349,  -461,  -461,     1,  -461,    23,   239,   251,   274,
     275,   279,   281,   285,   286,   292,   293,   295,   296,   298,
     299,   302,   303,   305,   307,   311,   315,   317,   172,   172,
       6,     6,     6,     4,     4,  2191,  2191,   191,   191,   191,
     191,  2275,  2246,  2301,  2220,   258,  -461,  -461,  -461,   320,
       0,  2165,  2165,  2165,  2165,  2165,  2165,  2165,  2165,  2165,
    2165,  2165,  2165,  1251,   627,   252,     7,   333,  -461,   304,
     367,   367,   368,   115,  -461,   290,   327,  -461,  -461,  -461,
    -461,  -461,  2349,    90,   145,  -461,  -461,  -461,    45,  -461,
    1251,  1251,    45,  -461,  -461,  -461,  2349,  2328,  2349,  2349,
    2349,   328,  2349,  2349,   329,  2349,  2349,  2349,  2349,  2349,
    2349,  2349,  2349,  2349,  2349,  2349,    45,  2349,  -461,  -461,
    -461,    81,    45,    45,   300,  -461,   367,   330,    63,   220,
     335,    26,  -461,  -461,  1334,  -461,    90,  -461,   374,  -461,
    -461,  -461,  1370,  -461,  1417,  1461,  1505,  1549,  -461,  1593,
    1637,  -461,  1681,  1725,  1769,  1813,  1857,  1901,  1945,  1989,
    2033,  2077,  2121,   110,  2165,  -461,    73,   377,    45,   233,
     379,  -461,    45,   291,    45,   291,   380,  -461,  -461,  -461,
     338,  -461,  -461,  -461,  -461,  -461,  -461,  -461,  -461,  -461,
    -461,  -461,  -461,  -461,  -461,  -461,  -461,  -461,  -461,   312,
    -461,  -461,    73,    45,   291,  -461,    24,  -461,    13,  -461,
    -461,  -461,   342,   291,  -461,   382,   184,   344,  -461,   201,
      90,    45,  -461,   188,   345,   379,  -461,   291,  -461,  -461,
      41,   291,  -461,   126,  -461,  -461,    90,   291,  -461,  -461,
     347,    19,  -461,  -461,  -461,  -461,    25,  2448,    41,  -461,
    -461,  -461,  -461,  -461,  -461,    45,   390,   349,  -461,  -461,
    -461,   350,  -461,    19,  -461,   393,   330,   351,    39,   353,
     354,   355,   356,   357,   358,   359,   361,   362,   363,   364,
     365,   366,   369,   370,   372,   381,   383,   384,   387,  -461,
     411,   376,  -461,  -461,  -461,   417,   391,   388,    29,   330,
      45,    31,    45,    45,    45,   395,    45,    45,   404,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
     378,  -461,   394,   255,    36,   431,   127,   418,   130,   389,
     151,   165,   168,   175,   396,   176,   182,   397,   194,   200,
     204,   206,   208,   209,   211,   214,   216,   225,   229,  -461,
     255,    75,   261,   386,   398,   235,   180,  -461,    73,   431,
      38,   399,    45,   400,   403,   409,   410,    45,   413,   414,
      45,   415,   416,   421,   423,   424,   427,   430,   432,   433,
     435,   437,   261,  -461,  -461,    77,   440,   436,   210,    45,
     441,  -461,  -461,   446,  -461,    73,   442,   237,    45,    73,
      45,    45,    45,    45,    73,    45,    45,    73,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,   451,
    -461,  -461,  -461,   244,  -461,  -461,    73,    45,   772,  -461,
      45,   455,    73,  -461,    73,    73,    73,    73,  -461,    73,
      73,  -461,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,  -461,  -461,  -461,  -461,    73,  -461,   238,
      73,    45,  -461,  -461,  -461,  -461,  -461,  -461,  -461,  -461,
    -461,  -461,  -461,  -461,  -461,  -461,  -461,  -461,  -461,  -461,
    -461,  -461,  -461,    73,  -461
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -461,  -461,  -461,   514,  -461,   253,   310,  -461,  -461,   314,
    -461,   533,  -216,  -408,  -461,   167,  -461,  -461,  -461,  -461,
    -195,  -461,   177,  -461,   141,  -461,  -461,  -461,    34,  -461,
    -461,  -461,  -461,    44,    14,  -461,   155,   -74,  -460,  -461,
     119,  -212,   -61,    -6,    99,    -3,    47,  -461,  -461,  -461,
    -461,   -31,  -461,  -461,  -461,  -461,  -461,   332,  -461,  -461,
    -461,  -461,  -461,  -461,  -461,   408,  -461,  -461,  -461,  -461,
     -32,   164,   -19
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -120
static const yytype_int16 yytable[] =
{
      43,    43,   271,    85,   127,   279,    14,    88,   447,   267,
     242,   130,    93,   503,    93,    83,   273,    94,    95,    96,
      97,    98,   242,    72,   151,   114,    14,     7,   103,   104,
     105,   106,   416,   375,    90,    43,    14,   132,    14,     8,
     503,   477,   537,    14,   152,    14,   449,   138,    14,    71,
     215,   268,    14,   144,   243,   232,   233,   135,   274,   137,
     319,   377,    66,    67,    68,    69,    70,   148,   150,   112,
       2,   112,   537,   322,   133,    91,    76,   376,    79,    80,
     475,    43,   479,    86,    87,   392,   393,   504,   156,   546,
     267,   392,   393,   394,   395,   244,   245,   113,   391,   394,
     395,   417,    42,    42,    73,   392,   393,   392,   393,   156,
     156,   323,   237,   394,   395,   394,   395,   231,   396,   273,
      77,    84,    74,    84,   136,    84,    78,   139,   156,   533,
     367,   570,   315,   408,    81,   397,   273,    42,    84,   273,
      43,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   374,
     273,   349,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   273,   409,   213,   273,   509,   115,
      93,   511,   390,    42,   273,   273,   407,    96,    97,    98,
     155,   273,   411,   242,   269,   129,   240,   242,   241,    93,
      89,   285,   513,   273,    94,    95,    96,    97,    98,   273,
     383,   196,   197,   273,   112,   273,   514,   273,   273,   515,
     273,   289,   290,   273,   131,   273,   516,   518,   232,   286,
     324,   145,   381,   519,   273,   156,   387,   112,   273,   156,
     541,   542,    42,   353,   273,   521,   273,   267,   153,  -119,
     384,   522,   328,   214,   329,   523,   112,   524,    84,   525,
     526,   201,   527,   156,   574,   528,    93,   529,   325,   156,
     156,    94,    95,    96,    97,    98,   530,    99,   100,   284,
     531,   354,   103,   104,   105,   106,   540,   218,   581,   631,
     238,    91,    84,   292,   294,   295,   296,   297,   604,   299,
     300,   246,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   501,   314,   156,   358,   414,   366,   156,
     535,   156,   414,   112,   247,   248,   359,   360,   361,   249,
     272,   250,   359,   360,   361,   251,   252,   288,   385,   444,
     275,   291,   253,   254,   444,   255,   256,   373,   257,   258,
     156,   113,   259,   260,   410,   261,   219,   262,   220,   221,
     222,   263,   359,   360,   361,   264,   609,   265,   156,   223,
     266,   316,   317,   276,   277,   280,   283,   156,   318,   298,
     301,   330,   320,   326,   351,   313,   355,   368,   156,   370,
     371,   378,   380,   382,   388,   156,   412,   441,   442,   443,
     446,   448,   156,   450,   451,   452,   453,   454,   455,   456,
     156,   457,   458,   459,   460,   461,   462,   352,   470,   463,
     464,   155,   465,   155,   472,    10,    11,    12,    13,    14,
     471,   466,   499,   467,   468,    15,    16,   469,   474,   473,
      17,   506,   500,    18,   538,   156,   484,   156,   156,   156,
     156,   156,   155,   156,   156,   487,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   512,   510,   534,
     386,   156,    19,   198,   517,   520,   539,   548,   550,   406,
     350,   551,    21,    22,    23,    24,    25,   552,   553,   572,
     415,   555,   556,   558,   559,   573,   578,   406,    26,   560,
     603,   561,   562,   571,   440,   563,   575,   156,   564,   156,
     565,   566,   445,   567,   156,   568,   372,   156,    63,   577,
     580,   199,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   611,   327,   282,   156,   281,    64,   439,
     379,   605,   389,   545,   532,   156,   569,   156,   156,   156,
     156,   418,   156,   156,   239,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   287,   476,     0,   478,
     480,   481,   482,   483,   156,   485,   486,   156,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,     0,
       0,     0,     0,   505,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   156,     0,
       0,   549,     0,     0,     0,     0,   554,     0,     0,   557,
       0,     0,     0,     0,     0,   201,     0,     0,     0,   547,
      10,    11,    12,    13,    14,     0,     0,     0,   576,     0,
      15,    16,     0,     0,     0,    17,     0,   582,    18,   584,
     585,   586,   587,     0,   589,   590,     0,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,     0,     0,
       0,     0,   544,     0,     0,     0,   607,    19,   270,   610,
       0,     0,     0,     0,     0,     0,     0,    21,    22,    23,
      24,    25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    26,     0,     0,     0,     0,     0,   579,
     633,     0,     0,   583,     0,     0,     0,     0,   588,     0,
       0,   591,     0,     0,     0,     0,   199,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     606,     0,     0,     0,     0,     0,   612,     0,   613,   614,
     615,   616,     0,   617,   618,     0,   619,   620,   621,   622,
     623,   624,   625,   626,   627,   628,   629,     0,     0,     0,
       0,   630,     0,     0,   632,    10,    11,    12,    13,    14,
       0,     0,     0,     0,     0,    15,    16,     0,     0,     0,
      17,     0,     0,    18,     0,     0,     9,   634,     0,    10,
      11,    12,    13,    14,     0,     0,     0,     0,     0,    15,
      16,     0,     0,     0,    17,     0,     0,    18,     0,     0,
       0,     0,    19,   608,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,    23,    24,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,     0,    26,     0,
       0,     0,    20,     0,     0,     0,    21,    22,    23,    24,
      25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   199,    26,    27,     0,    28,    29,    30,    31,     0,
       0,    32,    33,    34,    35,     0,    36,    37,    38,     1,
       0,    -5,    -5,    -5,    -5,    -5,     0,     0,     0,     0,
       0,    -5,    -5,     0,     0,     0,    -5,     0,     0,    -5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,    15,    16,     0,     0,    -5,    17,
       0,     0,    18,     2,    -5,     0,     0,     0,    -5,    -5,
      -5,    -5,    -5,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    -5,    -5,     0,    -5,    -5,    -5,
      -5,    19,     0,    -5,    -5,    -5,    -5,    20,    -5,    -5,
      -5,    21,    22,    23,    24,    25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    26,    27,     0,
      28,    29,    30,    31,     0,     0,    32,    33,    34,    35,
       0,    36,    37,    38,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,    15,    16,     0,     0,     0,    17,
       0,    93,    18,   149,     0,     0,    94,    95,    96,    97,
      98,     0,    99,   100,     0,   101,   102,   103,   104,   105,
     106,     0,     0,   107,   108,   109,   110,     0,     0,     0,
     142,    19,     0,     0,     0,     0,     0,    20,     0,     0,
     111,    21,    22,    23,    24,    25,     0,    81,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    26,   112,     0,
       0,    29,    30,    31,     0,     0,    32,    33,    34,    35,
       0,    36,    37,    38,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,    15,    16,   113,     0,     0,    17,
       0,     0,    18,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,    15,    16,     0,
     236,    19,    17,     0,     0,    18,     0,    20,     0,     0,
       0,    21,    22,    23,    24,    25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    29,    30,    31,    19,     0,    32,    33,    34,    35,
      20,    36,    37,    38,    21,    22,    23,    24,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26,     0,     0,     0,    29,    30,    31,     0,     0,    32,
      33,    34,    35,    93,    36,    37,    38,     0,    94,    95,
      96,    97,    98,     0,    99,   100,     0,   101,   102,   103,
     104,   105,   106,     0,     0,   107,   108,   109,   110,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    93,
       0,     0,   111,    84,    94,    95,    96,    97,    98,   139,
      99,   100,     0,   101,   102,   103,   104,   105,   106,     0,
     112,   107,   108,   109,   110,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    93,     0,     0,   111,     0,
      94,    95,    96,    97,    98,    81,    99,   100,   113,   101,
     102,   103,   104,   105,   106,     0,   112,   107,   108,   109,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   111,     0,     0,     0,   128,     0,
       0,     0,    93,     0,   113,     0,     0,    94,    95,    96,
      97,    98,   112,    99,   100,     0,   101,   102,   103,   104,
     105,   106,     0,     0,   107,   108,   109,   110,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,     0,
     113,   111,    84,    94,    95,    96,    97,    98,     0,    99,
     100,     0,   101,   102,   103,   104,   105,   106,     0,   112,
     107,   108,   109,   110,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   111,     0,     0,
       0,   331,     0,     0,     0,    93,     0,   113,     0,     0,
      94,    95,    96,    97,    98,   112,    99,   100,     0,   101,
     102,   103,   104,   105,   106,     0,     0,   107,   108,   109,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   113,   111,     0,     0,     0,   332,    93,
       0,     0,     0,     0,    94,    95,    96,    97,    98,     0,
      99,   100,   112,   101,   102,   103,   104,   105,   106,     0,
       0,   107,   108,   109,   110,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   111,     0,
     113,     0,   333,    93,     0,     0,     0,     0,    94,    95,
      96,    97,    98,     0,    99,   100,   112,   101,   102,   103,
     104,   105,   106,     0,     0,   107,   108,   109,   110,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   111,     0,   113,     0,   334,    93,     0,     0,
       0,     0,    94,    95,    96,    97,    98,     0,    99,   100,
     112,   101,   102,   103,   104,   105,   106,     0,     0,   107,
     108,   109,   110,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   111,     0,   113,     0,
     335,    93,     0,     0,     0,     0,    94,    95,    96,    97,
      98,     0,    99,   100,   112,   101,   102,   103,   104,   105,
     106,     0,     0,   107,   108,   109,   110,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     111,     0,   113,     0,   336,    93,     0,     0,     0,     0,
      94,    95,    96,    97,    98,     0,    99,   100,   112,   101,
     102,   103,   104,   105,   106,     0,     0,   107,   108,   109,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   111,     0,   113,     0,   337,    93,
       0,     0,     0,     0,    94,    95,    96,    97,    98,     0,
      99,   100,   112,   101,   102,   103,   104,   105,   106,     0,
       0,   107,   108,   109,   110,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   111,     0,
     113,     0,   338,    93,     0,     0,     0,     0,    94,    95,
      96,    97,    98,     0,    99,   100,   112,   101,   102,   103,
     104,   105,   106,     0,     0,   107,   108,   109,   110,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   111,     0,   113,     0,   339,    93,     0,     0,
       0,     0,    94,    95,    96,    97,    98,     0,    99,   100,
     112,   101,   102,   103,   104,   105,   106,     0,     0,   107,
     108,   109,   110,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   111,     0,   113,     0,
     340,    93,     0,     0,     0,     0,    94,    95,    96,    97,
      98,     0,    99,   100,   112,   101,   102,   103,   104,   105,
     106,     0,     0,   107,   108,   109,   110,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     111,     0,   113,     0,   341,    93,     0,     0,     0,     0,
      94,    95,    96,    97,    98,     0,    99,   100,   112,   101,
     102,   103,   104,   105,   106,     0,     0,   107,   108,   109,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   111,     0,   113,     0,   342,    93,
       0,     0,     0,     0,    94,    95,    96,    97,    98,     0,
      99,   100,   112,   101,   102,   103,   104,   105,   106,     0,
       0,   107,   108,   109,   110,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   111,     0,
     113,     0,   343,    93,     0,     0,     0,     0,    94,    95,
      96,    97,    98,     0,    99,   100,   112,   101,   102,   103,
     104,   105,   106,     0,     0,   107,   108,   109,   110,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   111,     0,   113,     0,   344,    93,     0,     0,
       0,     0,    94,    95,    96,    97,    98,     0,    99,   100,
     112,   101,   102,   103,   104,   105,   106,     0,     0,   107,
     108,   109,   110,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   111,     0,   113,     0,
     345,    93,     0,     0,     0,     0,    94,    95,    96,    97,
      98,     0,    99,   100,   112,   101,   102,   103,   104,   105,
     106,     0,     0,   107,   108,   109,   110,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     111,     0,   113,     0,   346,    93,     0,     0,     0,     0,
      94,    95,    96,    97,    98,     0,    99,   100,   112,   101,
     102,   103,   104,   105,   106,     0,     0,   107,   108,   109,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   111,     0,   113,     0,   347,    93,
       0,     0,     0,     0,    94,    95,    96,    97,    98,     0,
      99,   100,   112,   101,   102,   103,   104,   105,   106,     0,
       0,   107,   108,   109,   110,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   111,     0,
     113,     0,   348,    93,     0,     0,     0,     0,    94,    95,
      96,    97,    98,     0,    99,   100,   112,   101,   102,   103,
     104,   105,   106,     0,     0,   107,   108,   109,   110,    93,
       0,     0,     0,     0,    94,    95,    96,    97,    98,     0,
      99,   100,   111,     0,   113,   103,   104,   105,   106,     0,
       0,   107,   108,   109,   110,     0,     0,     0,    93,     0,
     112,     0,     0,    94,    95,    96,    97,    98,   111,    99,
     100,     0,     0,     0,   103,   104,   105,   106,     0,     0,
     107,   108,   109,     0,    93,     0,   112,     0,   113,    94,
      95,    96,    97,    98,     0,    99,   100,   111,     0,     0,
     103,   104,   105,   106,     0,     0,   107,     0,   109,     0,
       0,     0,     0,    93,   113,   112,     0,     0,    94,    95,
      96,    97,    98,   111,    99,   100,     0,     0,     0,   103,
     104,   105,   106,     0,     0,     0,     0,   109,     0,    93,
       0,   112,     0,   113,    94,    95,    96,    97,    98,     0,
      99,   100,   111,     0,     0,   103,   104,   105,   106,     0,
       0,    10,    11,    12,    13,    14,     0,     0,     0,   113,
     112,    15,    16,     0,     0,     0,    17,     0,   111,    18,
       0,     0,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,    15,    16,     0,     0,   112,    17,   113,     0,
      18,     0,     0,     0,     0,     0,     0,     0,    19,   293,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    22,
      23,    24,    25,     0,   113,     0,     0,     0,     0,    19,
       0,     0,     0,     0,    26,     0,     0,     0,     0,    21,
      22,    23,    24,    25,     0,     0,     0,     0,     0,     0,
     157,     0,     0,     0,     0,    26,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,   173,   174,   175,   176,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     177,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,     0,     0,   434,   435,
     436,   437,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   438
};

static const yytype_int16 yycheck[] =
{
       3,     4,   214,    35,    65,   221,     7,    38,   416,     9,
       9,    72,     8,   473,     8,    34,     9,    13,    14,    15,
      16,    17,     9,    26,    34,    44,     7,   108,    24,    25,
      26,    27,     7,     9,    11,    38,     7,    11,     7,     4,
     500,   449,   502,     7,    54,     7,     7,    79,     7,     7,
      51,    51,     7,    84,    53,    83,    84,    76,    51,    78,
     276,    48,    15,    16,    17,    18,    19,    86,    87,    65,
      55,    65,   532,    10,    48,    52,    29,    53,    31,    32,
      51,    84,    51,    36,    37,    66,    67,    51,    91,    51,
       9,    66,    67,    74,    75,   156,   157,    93,    57,    74,
      75,    76,     3,     4,     7,    66,    67,    66,    67,   112,
     113,    48,   143,    74,    75,    74,    75,   136,    77,     9,
      80,    48,     7,    48,    77,    48,    86,    54,   131,    54,
     325,    54,    51,     7,    54,    94,     9,    38,    48,     9,
     143,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   354,
       9,    51,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,     9,    49,   129,     9,    51,    50,
       8,    51,   377,    84,     9,     9,   381,    15,    16,    17,
      91,     9,   387,     9,   213,    34,   149,     9,   151,     8,
       7,   233,    51,     9,    13,    14,    15,    16,    17,     9,
       9,   112,   113,     9,    65,     9,    51,     9,     9,    51,
       9,   240,   241,     9,    50,     9,    51,    51,    83,    84,
      10,    89,    48,    51,     9,   238,    48,    65,     9,   242,
      60,    61,   143,    10,     9,    51,     9,     9,     7,     7,
      49,    51,   284,    50,   286,    51,    65,    51,    48,    51,
      51,   214,    51,   266,    54,    51,     8,    51,    48,   272,
     273,    13,    14,    15,    16,    17,    51,    19,    20,   232,
      51,    48,    24,    25,    26,    27,    51,     7,    51,    51,
      50,    52,    48,   246,   247,   248,   249,   250,    54,   252,
     253,    50,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,    58,   267,   318,   322,   391,   324,   322,
      59,   324,   396,    65,    50,    50,    71,    72,    73,    50,
      78,    50,    71,    72,    73,    50,    50,   238,   370,   413,
       7,   242,    50,    50,   418,    50,    50,   353,    50,    50,
     353,    93,    50,    50,   386,    50,    66,    50,    68,    69,
      70,    50,    71,    72,    73,    50,   578,    50,   371,    79,
      50,   272,   273,    69,     7,     7,    49,   380,    78,    51,
      51,     7,    52,    48,     7,   266,     7,     7,   391,    51,
      78,    49,    10,    49,    49,   398,    49,     7,    49,    49,
       7,    50,   405,    50,    50,    50,    50,    50,    50,    50,
     413,    50,    50,    50,    50,    50,    50,   318,     7,    50,
      50,   322,    50,   324,     7,     3,     4,     5,     6,     7,
      54,    50,    54,    50,    50,    13,    14,    50,    50,    48,
      18,    10,    48,    21,    58,   448,    51,   450,   451,   452,
     453,   454,   353,   456,   457,    51,   459,   460,   461,   462,
     463,   464,   465,   466,   467,   468,   469,    78,    50,   501,
     371,   474,    50,    51,    78,    78,    78,    78,    78,   380,
     316,    78,    60,    61,    62,    63,    64,    78,    78,    49,
     391,    78,    78,    78,    78,    59,    50,   398,    76,    78,
      49,    78,    78,   535,   405,    78,   538,   510,    78,   512,
      78,    78,   413,    78,   517,    78,   352,   520,     4,    78,
      78,    99,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    78,   281,   225,   539,   223,     5,   398,
     363,   573,   375,   509,   500,   548,   532,   550,   551,   552,
     553,   396,   555,   556,   146,   558,   559,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   234,   448,    -1,   450,
     451,   452,   453,   454,   577,   456,   457,   580,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,    -1,
      -1,    -1,    -1,   474,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   611,    -1,
      -1,   512,    -1,    -1,    -1,    -1,   517,    -1,    -1,   520,
      -1,    -1,    -1,    -1,    -1,   578,    -1,    -1,    -1,   510,
       3,     4,     5,     6,     7,    -1,    -1,    -1,   539,    -1,
      13,    14,    -1,    -1,    -1,    18,    -1,   548,    21,   550,
     551,   552,   553,    -1,   555,   556,    -1,   558,   559,   560,
     561,   562,   563,   564,   565,   566,   567,   568,    -1,    -1,
      -1,    -1,   508,    -1,    -1,    -1,   577,    50,    51,   580,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,   545,
     611,    -1,    -1,   549,    -1,    -1,    -1,    -1,   554,    -1,
      -1,   557,    -1,    -1,    -1,    -1,    99,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     576,    -1,    -1,    -1,    -1,    -1,   582,    -1,   584,   585,
     586,   587,    -1,   589,   590,    -1,   592,   593,   594,   595,
     596,   597,   598,   599,   600,   601,   602,    -1,    -1,    -1,
      -1,   607,    -1,    -1,   610,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    -1,    -1,    13,    14,    -1,    -1,    -1,
      18,    -1,    -1,    21,    -1,    -1,     0,   633,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,
      14,    -1,    -1,    -1,    18,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    76,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    99,    76,    77,    -1,    79,    80,    81,    82,    -1,
      -1,    85,    86,    87,    88,    -1,    90,    91,    92,     1,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      -1,    13,    14,    -1,    -1,    -1,    18,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    -1,    13,    14,    -1,    -1,    50,    18,
      -1,    -1,    21,    55,    56,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    77,    -1,    79,    80,    81,
      82,    50,    -1,    85,    86,    87,    88,    56,    90,    91,
      92,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,
      79,    80,    81,    82,    -1,    -1,    85,    86,    87,    88,
      -1,    90,    91,    92,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    -1,    13,    14,    -1,    -1,    -1,    18,
      -1,     8,    21,    10,    -1,    -1,    13,    14,    15,    16,
      17,    -1,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      49,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      47,    60,    61,    62,    63,    64,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    65,    -1,
      -1,    80,    81,    82,    -1,    -1,    85,    86,    87,    88,
      -1,    90,    91,    92,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    -1,    13,    14,    93,    -1,    -1,    18,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,    -1,
      49,    50,    18,    -1,    -1,    21,    -1,    56,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    80,    81,    82,    50,    -1,    85,    86,    87,    88,
      56,    90,    91,    92,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    80,    81,    82,    -1,    -1,    85,
      86,    87,    88,     8,    90,    91,    92,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,
      -1,    -1,    47,    48,    13,    14,    15,    16,    17,    54,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      65,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    47,    -1,
      13,    14,    15,    16,    17,    54,    19,    20,    93,    22,
      23,    24,    25,    26,    27,    -1,    65,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    51,    -1,
      -1,    -1,     8,    -1,    93,    -1,    -1,    13,    14,    15,
      16,    17,    65,    19,    20,    -1,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,
      93,    47,    48,    13,    14,    15,    16,    17,    -1,    19,
      20,    -1,    22,    23,    24,    25,    26,    27,    -1,    65,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    51,    -1,    -1,    -1,     8,    -1,    93,    -1,    -1,
      13,    14,    15,    16,    17,    65,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    93,    47,    -1,    -1,    -1,    51,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    65,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      93,    -1,    51,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    65,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    -1,    93,    -1,    51,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    19,    20,
      65,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    93,    -1,
      51,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    -1,    19,    20,    65,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    -1,    93,    -1,    51,     8,    -1,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    -1,    19,    20,    65,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    93,    -1,    51,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    65,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      93,    -1,    51,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    65,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    -1,    93,    -1,    51,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    19,    20,
      65,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    93,    -1,
      51,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    -1,    19,    20,    65,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    -1,    93,    -1,    51,     8,    -1,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    -1,    19,    20,    65,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    93,    -1,    51,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    65,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      93,    -1,    51,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    65,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    -1,    93,    -1,    51,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    19,    20,
      65,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    93,    -1,
      51,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    -1,    19,    20,    65,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    -1,    93,    -1,    51,     8,    -1,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    -1,    19,    20,    65,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    93,    -1,    51,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    65,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      93,    -1,    51,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    65,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    47,    -1,    93,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,     8,    -1,
      65,    -1,    -1,    13,    14,    15,    16,    17,    47,    19,
      20,    -1,    -1,    -1,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    -1,     8,    -1,    65,    -1,    93,    13,
      14,    15,    16,    17,    -1,    19,    20,    47,    -1,    -1,
      24,    25,    26,    27,    -1,    -1,    30,    -1,    32,    -1,
      -1,    -1,    -1,     8,    93,    65,    -1,    -1,    13,    14,
      15,    16,    17,    47,    19,    20,    -1,    -1,    -1,    24,
      25,    26,    27,    -1,    -1,    -1,    -1,    32,    -1,     8,
      -1,    65,    -1,    93,    13,    14,    15,    16,    17,    -1,
      19,    20,    47,    -1,    -1,    24,    25,    26,    27,    -1,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,    93,
      65,    13,    14,    -1,    -1,    -1,    18,    -1,    47,    21,
      -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    13,    14,    -1,    -1,    65,    18,    93,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    -1,    93,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
       7,    -1,    -1,    -1,    -1,    76,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    55,   110,   111,   119,   120,   108,     4,     0,
       3,     4,     5,     6,     7,    13,    14,    18,    21,    50,
      56,    60,    61,    62,    63,    64,    76,    77,    79,    80,
      81,    82,    85,    86,    87,    88,    90,    91,    92,   112,
     113,   138,   153,   154,   155,   156,   157,   158,   160,   161,
     162,   163,   164,   167,   168,   169,   170,   171,   172,   175,
     176,   177,   178,   112,   120,   154,   155,   155,   155,   155,
     155,     7,   154,     7,     7,   118,   155,    80,    86,   155,
     155,    54,   181,   181,    48,   179,   155,   155,   160,     7,
      11,    52,   151,     8,    13,    14,    15,    16,    17,    19,
      20,    22,    23,    24,    25,    26,    27,    30,    31,    32,
      33,    47,    65,    93,   181,    50,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,   151,    51,    34,
     151,    50,    11,    48,   114,   181,   155,   181,   179,    54,
     179,   180,    49,   159,   160,    89,   173,   174,   181,    10,
     181,    34,    54,     7,   152,   153,   154,     7,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    30,    31,    32,    33,    47,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   153,   153,    51,    99,
     150,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,    50,    51,   149,   153,     7,    66,
      68,    69,    70,    79,   115,   116,   117,   125,   126,   127,
     128,   181,    83,    84,   165,   166,    49,   160,    50,   174,
     155,   155,     9,    53,   151,   151,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,     9,    51,   181,
      51,   150,    78,     9,    51,     7,    69,     7,   121,   121,
       7,   118,   115,    49,   155,   179,    84,   166,   153,   181,
     181,   153,   155,    51,   155,   155,   155,   155,    51,   155,
     155,    51,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   149,   155,    51,   153,   153,    78,   121,
      52,   122,    10,    48,    10,    48,    48,   114,   179,   179,
       7,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
     180,     7,   153,    10,    48,     7,   123,   124,   152,    71,
      72,    73,   129,   130,   131,   147,   152,   129,     7,   148,
      51,    78,   180,   152,   129,     9,    53,    48,    49,   131,
      10,    48,    49,     9,    49,   179,   153,    48,    49,   124,
     129,    57,    66,    67,    74,    75,    77,    94,   132,   133,
     134,   139,   140,   141,   144,   146,   153,   129,     7,    49,
     179,   129,    49,   145,   146,   153,     7,    76,   145,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    30,    31,    32,    33,    47,   133,
     153,     7,    49,    49,   146,   153,     7,   122,    50,     7,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
       7,    54,     7,    48,    50,    51,   149,   122,   149,    51,
     149,   149,   149,   149,    51,   149,   149,    51,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,    54,
      48,    58,   142,   147,    51,   149,    10,   135,   137,    51,
      50,    51,    78,    51,    51,    51,    51,    78,    51,    51,
      78,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,   142,    54,   179,    59,   143,   147,    58,    78,
      51,    60,    61,   136,   180,   137,    51,   149,    78,   153,
      78,    78,    78,    78,   153,    78,    78,   153,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,   143,
      54,   179,    49,    59,    54,   179,   153,    78,    50,   180,
      78,    51,   153,   180,   153,   153,   153,   153,   180,   153,
     153,   180,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,    49,    54,   179,   180,   153,    51,   150,
     153,    78,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,    51,   180,   153,   180
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
#line 625 "beacon.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 106:
#line 629 "beacon.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 107:
#line 633 "beacon.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 108:
#line 640 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[(1) - (1)].stringv_value));
	;}
    break;

  case 109:
#line 644 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[(3) - (3)].stringv_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 110:
#line 651 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].stringv_value));
	;}
    break;

  case 111:
#line 655 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].stringv_value), (yyvsp[(1) - (4)].ast_value))
	;}
    break;

  case 112:
#line 662 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 113:
#line 666 "beacon.y"
    {
		(yyval.ast_value) = ast_new_lambda((yyvsp[(3) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 114:
#line 670 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(3) - (3)].ast_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 115:
#line 677 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 116:
#line 681 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 117:
#line 688 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 118:
#line 692 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 119:
#line 699 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 120:
#line 706 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].stringv_value));
	;}
    break;

  case 121:
#line 710 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(3) - (3)].stringv_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 122:
#line 719 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 125:
#line 727 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_pos, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 126:
#line 731 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_neg, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 127:
#line 735 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 128:
#line 739 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 129:
#line 743 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 130:
#line 747 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 131:
#line 751 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 132:
#line 755 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 133:
#line 759 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_equal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 134:
#line 763 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_notequal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 135:
#line 767 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 136:
#line 771 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 137:
#line 775 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 138:
#line 779 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 139:
#line 783 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 140:
#line 787 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 141:
#line 791 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 142:
#line 795 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 143:
#line 799 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 144:
#line 803 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 145:
#line 807 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_and_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 146:
#line 811 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 147:
#line 815 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 148:
#line 819 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 149:
#line 823 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 150:
#line 827 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_gt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 151:
#line 831 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_ge, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 152:
#line 835 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 153:
#line 839 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_le, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 154:
#line 843 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 155:
#line 847 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 156:
#line 851 "beacon.y"
    {
		(yyval.ast_value) = ast_new_instanceof((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 157:
#line 855 "beacon.y"
    {
		(yyval.ast_value) = ast_new_as((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 158:
#line 859 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_childa, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 159:
#line 863 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_not, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 160:
#line 867 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 161:
#line 871 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 162:
#line 875 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 163:
#line 879 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), ast_new_blank());
	;}
    break;

  case 164:
#line 883 "beacon.y"
    {
		(yyval.ast_value) = ast_new_this();
	;}
    break;

  case 165:
#line 887 "beacon.y"
    {
		(yyval.ast_value) = ast_new_super();
	;}
    break;

  case 167:
#line 894 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 168:
#line 898 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].stringv_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 169:
#line 902 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_add, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 170:
#line 906 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_sub, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 171:
#line 910 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_mul, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 172:
#line 914 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_div, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 173:
#line 918 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_mod, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 174:
#line 922 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_gt, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 175:
#line 926 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_ge, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 176:
#line 930 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_lt, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 177:
#line 934 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_le, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 178:
#line 938 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_eq, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 179:
#line 942 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_noteq, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 180:
#line 946 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_bit_or, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 181:
#line 950 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_bit_and, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 182:
#line 954 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_logic_or, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 183:
#line 958 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_logic_and, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 184:
#line 962 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_lshift, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 185:
#line 966 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_rshift, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 186:
#line 970 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[(1) - (6)].ast_value), operator_excor, (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 187:
#line 974 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_not);
	;}
    break;

  case 188:
#line 978 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_childa);
	;}
    break;

  case 189:
#line 982 "beacon.y"
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[(1) - (5)].ast_value), operator_negative);
	;}
    break;

  case 194:
#line 992 "beacon.y"
    {
		(yyval.ast_value) = ast_new_true();
	;}
    break;

  case 195:
#line 996 "beacon.y"
    {
		(yyval.ast_value) = ast_new_false();
	;}
    break;

  case 196:
#line 1000 "beacon.y"
    {
		(yyval.ast_value) = ast_new_null();
	;}
    break;

  case 197:
#line 1009 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 198:
#line 1013 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 199:
#line 1019 "beacon.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 214:
#line 1039 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].stringv_value));
	;}
    break;

  case 215:
#line 1045 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].stringv_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 216:
#line 1051 "beacon.y"
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[(2) - (5)].stringv_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 217:
#line 1057 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 218:
#line 1061 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 219:
#line 1065 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 220:
#line 1069 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 222:
#line 1076 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 223:
#line 1082 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 224:
#line 1088 "beacon.y"
    {
		(yyval.ast_value) = ast_new_while((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 225:
#line 1094 "beacon.y"
    {
		(yyval.ast_value) = ast_new_break();
	;}
    break;

  case 226:
#line 1100 "beacon.y"
    {
		(yyval.ast_value) = ast_new_continue();
	;}
    break;

  case 227:
#line 1106 "beacon.y"
    {
		(yyval.ast_value) = ast_new_return((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 228:
#line 1112 "beacon.y"
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 229:
#line 1118 "beacon.y"
    {
		(yyval.ast_value) = ast_new_try((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 230:
#line 1124 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 231:
#line 1128 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 232:
#line 1134 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].stringv_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 233:
#line 1140 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (5)].ast_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 234:
#line 1144 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 235:
#line 1150 "beacon.y"
    {
		(yyval.ast_value) = ast_new_defer((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 236:
#line 1156 "beacon.y"
    {
		(yyval.ast_value) = ast_new_yield_return((yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 237:
#line 1162 "beacon.y"
    {
		(yyval.ast_value) = ast_new_yield_break();
	;}
    break;

  case 238:
#line 1168 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 239:
#line 1172 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 240:
#line 1178 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3919 "beacon.tab.c"
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


#line 1186 "beacon.y"





