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
     INTERFACE = 318,
     CLASS = 319,
     ENUM = 320,
     PUBLIC = 321,
     PRIVATE = 322,
     PROTECTED = 323,
     STATIC = 324,
     NATIVE = 325,
     NEW = 326,
     IN = 327,
     OUT = 328,
     CTOR = 329,
     DEF = 330,
     ARROW = 331,
     NAMESPACE = 332,
     RETURN = 333,
     IF = 334,
     ELIF = 335,
     ELSE = 336,
     WHILE = 337,
     BREAK = 338,
     CONTINUE = 339,
     TRY = 340,
     CATCH = 341,
     THROW = 342,
     ASSERT_T = 343,
     PRE_DEC = 344,
     PRE_INC = 345,
     QUOTE = 346,
     POST_DEC = 347,
     POST_INC = 348,
     FUNCCALL = 349,
     REF = 350,
     POSITIVE = 351,
     NEGATIVE = 352,
     FORM_TYPE = 353
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
#define INTERFACE 318
#define CLASS 319
#define ENUM 320
#define PUBLIC 321
#define PRIVATE 322
#define PROTECTED 323
#define STATIC 324
#define NATIVE 325
#define NEW 326
#define IN 327
#define OUT 328
#define CTOR 329
#define DEF 330
#define ARROW 331
#define NAMESPACE 332
#define RETURN 333
#define IF 334
#define ELIF 335
#define ELSE 336
#define WHILE 337
#define BREAK 338
#define CONTINUE 339
#define TRY 340
#define CATCH 341
#define THROW 342
#define ASSERT_T 343
#define PRE_DEC 344
#define PRE_INC 345
#define QUOTE 346
#define POST_DEC 347
#define POST_INC 348
#define FUNCCALL 349
#define REF 350
#define POSITIVE 351
#define NEGATIVE 352
#define FORM_TYPE 353




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
	modifier_type modifier_type_value;
	access_level access_level_value;
}
/* Line 193 of yacc.c.  */
#line 317 "beacon.tab.c"
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
#line 342 "beacon.tab.c"

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
#define YYLAST   1053

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  101
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  176
/* YYNRULES -- Number of states.  */
#define YYNSTATES  343

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   353

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     100,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      95,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      96,    97,    98,    99
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    13,    15,    17,    19,
      21,    25,    29,    33,    35,    37,    39,    41,    44,    45,
      47,    49,    53,    55,    58,    61,    64,    65,    69,    71,
      75,    78,    82,    86,    87,    91,    97,   105,   111,   118,
     124,   132,   133,   135,   137,   140,   144,   146,   149,   151,
     153,   155,   163,   170,   176,   181,   183,   185,   186,   188,
     197,   205,   216,   226,   231,   232,   235,   238,   240,   242,
     244,   246,   248,   250,   254,   257,   262,   264,   268,   269,
     273,   275,   279,   282,   284,   288,   292,   294,   296,   299,
     302,   306,   310,   314,   318,   322,   326,   330,   334,   338,
     342,   346,   350,   354,   358,   362,   366,   370,   374,   378,
     382,   386,   390,   394,   398,   402,   406,   410,   414,   418,
     422,   425,   428,   433,   437,   444,   450,   452,   454,   456,
     459,   464,   466,   468,   470,   472,   474,   476,   478,   480,
     483,   486,   488,   490,   492,   494,   496,   498,   500,   502,
     504,   506,   508,   512,   518,   524,   528,   534,   539,   546,
     548,   551,   555,   559,   562,   565,   569,   573,   577,   579,
     582,   589,   595,   599,   602,   604,   606
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     102,     0,    -1,   103,   104,    -1,   102,   104,    -1,     1,
     100,    -1,    -1,   111,    -1,   147,    -1,   105,    -1,   130,
      -1,    77,   110,   106,    -1,    48,   109,    49,    -1,    77,
     110,   106,    -1,   118,    -1,   120,    -1,   119,    -1,   107,
      -1,   108,   107,    -1,    -1,   108,    -1,     7,    -1,   110,
       8,     7,    -1,   112,    -1,   111,   112,    -1,    55,     4,
      -1,     7,   114,    -1,    -1,    28,   115,    29,    -1,   116,
      -1,   115,     9,   116,    -1,     7,   117,    -1,    72,     7,
     117,    -1,    73,     7,   117,    -1,    -1,    50,   139,    51,
      -1,    64,   113,    48,   121,    49,    -1,    64,   113,    10,
     139,    48,   121,    49,    -1,    65,     7,    48,   135,    49,
      -1,    65,     7,    48,   135,     9,    49,    -1,    63,   113,
      48,   121,    49,    -1,    63,   113,    10,   139,    48,   121,
      49,    -1,    -1,   122,    -1,   123,    -1,   122,   123,    -1,
     134,    10,   124,    -1,   125,    -1,   124,   125,    -1,   126,
      -1,   131,    -1,   132,    -1,    74,    71,    50,   136,    51,
     129,   164,    -1,    74,    71,    50,    51,   129,   164,    -1,
      10,   128,    50,   137,    51,    -1,    10,   128,    50,    51,
      -1,    58,    -1,    57,    -1,    -1,   127,    -1,    75,     7,
      50,   136,    51,    76,   140,   164,    -1,    75,     7,    50,
      51,    76,   140,   164,    -1,   133,    75,     7,   114,    50,
     136,    51,    76,   140,   164,    -1,   133,    75,     7,   114,
      50,    51,    76,   140,   164,    -1,   133,   140,     7,    54,
      -1,    -1,    69,    70,    -1,    70,    69,    -1,    69,    -1,
      70,    -1,    66,    -1,    67,    -1,    68,    -1,     7,    -1,
     135,     9,     7,    -1,   140,     7,    -1,   136,     9,   140,
       7,    -1,   142,    -1,   137,     9,   142,    -1,    -1,    28,
     139,    29,    -1,   140,    -1,   139,     9,   140,    -1,   141,
     138,    -1,     7,    -1,   141,    11,     7,    -1,    50,   142,
      51,    -1,   145,    -1,   143,    -1,    13,   142,    -1,    14,
     142,    -1,   142,    13,   142,    -1,   142,    14,   142,    -1,
     142,    15,   142,    -1,   142,    16,   142,    -1,   142,    17,
     142,    -1,   142,    32,   142,    -1,   142,    22,   142,    -1,
     142,    23,   142,    -1,   142,    30,   142,    -1,   142,    47,
     142,    -1,   142,    33,   142,    -1,   142,    31,   142,    -1,
     144,    34,   142,    -1,   144,    35,   142,    -1,   144,    36,
     142,    -1,   144,    37,   142,    -1,   144,    38,   142,    -1,
     144,    39,   142,    -1,   144,    40,   142,    -1,   144,    41,
     142,    -1,   144,    44,   142,    -1,   144,    42,   142,    -1,
     144,    43,   142,    -1,   142,    24,   142,    -1,   142,    25,
     142,    -1,   142,    26,   142,    -1,   142,    27,   142,    -1,
     142,    19,   142,    -1,   142,    20,   142,    -1,   142,    62,
     140,    -1,    21,   142,    -1,    18,   142,    -1,   143,    50,
     137,    51,    -1,   143,    50,    51,    -1,    71,   141,   138,
      50,   137,    51,    -1,    71,   141,   138,    50,    51,    -1,
      57,    -1,    58,    -1,   144,    -1,   141,   138,    -1,   142,
       8,     7,   138,    -1,     5,    -1,     6,    -1,     3,    -1,
       4,    -1,    59,    -1,    60,    -1,    61,    -1,   147,    -1,
     146,   147,    -1,   142,   165,    -1,   148,    -1,   149,    -1,
     150,    -1,   151,    -1,   154,    -1,   155,    -1,   156,    -1,
     157,    -1,   158,    -1,   159,    -1,   162,    -1,   140,     7,
      54,    -1,   140,     7,    34,   142,   165,    -1,    56,     7,
      34,   142,   165,    -1,    79,   142,   163,    -1,    79,   142,
     163,    81,   163,    -1,    79,   142,   163,   152,    -1,    79,
     142,   163,   152,    81,   163,    -1,   153,    -1,   152,   153,
      -1,    80,   142,   163,    -1,    82,   142,   164,    -1,    83,
     165,    -1,    84,   165,    -1,    78,   142,   165,    -1,    87,
     142,   165,    -1,    85,   163,   160,    -1,   161,    -1,   160,
     161,    -1,    86,    50,   140,     7,    51,   163,    -1,    88,
     142,    10,   142,    54,    -1,    48,   146,    49,    -1,    48,
      49,    -1,    54,    -1,   163,    -1,    54,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   140,   140,   141,   142,   148,   150,   156,   160,   164,
     170,   177,   184,   188,   189,   190,   194,   198,   206,   209,
     213,   217,   224,   225,   232,   239,   247,   250,   257,   261,
     268,   272,   276,   284,   287,   294,   298,   305,   309,   316,
     320,   328,   331,   335,   336,   343,   350,   354,   361,   362,
     363,   367,   371,   378,   382,   389,   393,   401,   404,   408,
     412,   419,   423,   430,   438,   441,   445,   449,   453,   460,
     464,   468,   475,   479,   486,   490,   497,   501,   509,   512,
     519,   523,   530,   537,   541,   550,   554,   555,   558,   562,
     566,   570,   574,   578,   582,   586,   590,   594,   598,   602,
     606,   610,   614,   618,   622,   626,   630,   634,   638,   642,
     646,   650,   654,   658,   662,   666,   670,   674,   678,   682,
     686,   690,   694,   698,   702,   706,   710,   714,   718,   721,
     725,   731,   732,   733,   734,   735,   739,   743,   752,   756,
     762,   766,   767,   768,   769,   770,   771,   772,   773,   774,
     775,   776,   779,   785,   791,   797,   801,   805,   809,   815,
     816,   822,   828,   834,   840,   846,   852,   858,   864,   868,
     874,   880,   887,   891,   897,   901,   904
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
  "AS", "INTERFACE", "CLASS", "ENUM", "PUBLIC", "PRIVATE", "PROTECTED",
  "STATIC", "NATIVE", "NEW", "IN", "OUT", "CTOR", "DEF", "ARROW",
  "NAMESPACE", "RETURN", "IF", "ELIF", "ELSE", "WHILE", "BREAK",
  "CONTINUE", "TRY", "CATCH", "THROW", "ASSERT_T", "PRE_DEC", "PRE_INC",
  "QUOTE", "POST_DEC", "POST_INC", "FUNCCALL", "'<'", "REF", "POSITIVE",
  "NEGATIVE", "FORM_TYPE", "'\\n'", "$accept", "compilation_unit",
  "init_decl", "body_decl", "namespace_decl", "namespace_body",
  "namespace_member_decl", "namespace_member_decl_list",
  "namespace_member_decl_optional", "namespace_path", "import_list",
  "import", "parameterized_typename", "type_parameter_group",
  "type_parameter_list", "type_parameter", "type_parameter_rule_list",
  "class_decl", "enum_decl", "interface_decl", "access_member_tree_opt",
  "access_member_tree", "access_member_list", "member_define_list",
  "member_define", "constructor_define", "constructor_chain",
  "constructor_chain_type_T", "constructor_chain_optional",
  "function_define", "method_define", "field_define", "modifier_type_T",
  "access_level_T", "ident_list", "parameter_list", "argument_list",
  "typename_group", "typename_list", "typename_T", "fqcn_part",
  "expression", "expression_nobrace", "lhs", "primary", "stmt_list",
  "stmt", "variable_decl_stmt", "variable_init_stmt",
  "inferenced_type_init_stmt", "if_stmt", "elif_list", "elif",
  "while_stmt", "break_stmt", "continue_stmt", "return_stmt", "throw_stmt",
  "try_stmt", "catch_stmt_list", "catch_stmt", "assert_stmt", "scope",
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
     345,   346,   347,   348,   349,    60,   350,   351,   352,   353,
      10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   101,   102,   102,   102,   103,   103,   104,   104,   104,
     105,   106,   107,   107,   107,   107,   108,   108,   109,   109,
     110,   110,   111,   111,   112,   113,   114,   114,   115,   115,
     116,   116,   116,   117,   117,   118,   118,   119,   119,   120,
     120,   121,   121,   122,   122,   123,   124,   124,   125,   125,
     125,   126,   126,   127,   127,   128,   128,   129,   129,   130,
     130,   131,   131,   132,   133,   133,   133,   133,   133,   134,
     134,   134,   135,   135,   136,   136,   137,   137,   138,   138,
     139,   139,   140,   141,   141,   142,   142,   142,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   144,
     144,   145,   145,   145,   145,   145,   145,   145,   146,   146,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   148,   149,   150,   151,   151,   151,   151,   152,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   160,
     161,   162,   163,   163,   164,   164,   165
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     1,     1,     1,     1,
       3,     3,     3,     1,     1,     1,     1,     2,     0,     1,
       1,     3,     1,     2,     2,     2,     0,     3,     1,     3,
       2,     3,     3,     0,     3,     5,     7,     5,     6,     5,
       7,     0,     1,     1,     2,     3,     1,     2,     1,     1,
       1,     7,     6,     5,     4,     1,     1,     0,     1,     8,
       7,    10,     9,     4,     0,     2,     2,     1,     1,     1,
       1,     1,     1,     3,     2,     4,     1,     3,     0,     3,
       1,     3,     2,     1,     3,     3,     1,     1,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     3,     6,     5,     1,     1,     1,     2,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     5,     5,     3,     5,     4,     6,     1,
       2,     3,     3,     2,     2,     3,     3,     3,     1,     2,
       6,     5,     3,     2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,    22,     4,    24,     1,
     133,   134,   131,   132,    83,     0,     0,     0,     0,     0,
       0,   126,   127,   135,   136,   137,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     3,     8,     9,
       0,    78,     0,    87,   128,    86,     7,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,     2,    23,
      78,    88,    89,   121,   120,     0,     0,    78,     0,    20,
       0,     0,     0,     0,   176,   163,   164,     0,     0,     0,
       0,     0,     0,     0,   129,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   140,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   129,    85,
       0,     0,     0,     0,    18,    10,   165,   155,   174,   175,
     162,   173,     0,   138,     0,   167,   168,   166,     0,     0,
     152,    84,     0,    80,    78,    78,    90,    91,    92,    93,
      94,   117,   118,    96,    97,   113,   114,   115,   116,    98,
     101,    95,   100,    99,   119,   123,     0,    76,   102,   103,
     104,   105,   106,   107,   108,   109,   111,   112,   110,     0,
       0,     0,     0,     0,    21,     0,     0,     0,     0,    16,
      19,     0,    13,    15,    14,     0,     0,   157,   159,   172,
     139,     0,   169,     0,     0,     0,    79,    82,   130,     0,
     122,   154,   125,     0,     0,     0,     0,    74,    26,     0,
       0,     0,     0,    17,    11,     0,   156,     0,   160,     0,
     171,   153,    81,    77,   124,     0,     0,     0,     0,    25,
       0,    41,     0,    41,     0,    12,   161,   158,     0,    60,
      75,     0,    33,     0,     0,     0,    28,     0,    69,    70,
      71,     0,    42,    43,     0,     0,     0,    72,     0,     0,
      59,     0,    30,    33,    33,     0,    27,    41,    39,    44,
      64,    41,    35,     0,    37,   170,     0,    31,    32,    29,
       0,    67,    68,     0,    45,    46,    48,    49,    50,     0,
       0,    73,    38,    34,    40,    65,    66,     0,    47,     0,
       0,    36,     0,    26,     0,    57,     0,     0,    63,     0,
      58,     0,    57,     0,    56,    55,     0,    52,     0,     0,
       0,     0,    51,     0,     0,    54,     0,     0,     0,    53,
      62,     0,    61
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    37,    38,   125,   189,   190,   191,    70,
       5,     6,   219,   239,   255,   256,   272,   192,   193,   194,
     261,   262,   263,   294,   295,   296,   320,   326,   321,    39,
     297,   298,   299,   264,   268,   182,   166,    84,   142,    40,
      60,    42,    43,    44,    45,   132,    46,    47,    48,    49,
      50,   197,   198,    51,    52,    53,    54,    55,    56,   135,
     136,    57,   129,   130,    75
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -277
static const yytype_int16 yypact[] =
{
     310,   -59,    39,   215,   396,    14,  -277,  -277,  -277,  -277,
    -277,  -277,  -277,  -277,  -277,   676,   676,   676,   676,   676,
      44,  -277,  -277,  -277,  -277,  -277,    47,   125,   138,   676,
     676,   676,    97,    97,   121,   676,   676,  -277,  -277,  -277,
     165,   150,   779,   131,   538,  -277,  -277,  -277,  -277,  -277,
    -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,
     150,   130,   130,   130,   130,   805,   153,   150,   154,  -277,
     112,   779,   846,   735,  -277,  -277,  -277,   482,   114,   779,
     887,   -12,   210,    47,   216,   217,   676,   676,   676,   676,
     676,   676,   676,   676,   676,   676,   676,   676,   676,   676,
     676,   676,   676,   676,    47,  -277,   600,   676,   676,   676,
     676,   676,   676,   676,   676,   676,   676,   676,  -277,  -277,
     676,   176,    -1,   220,    73,  -277,  -277,    94,  -277,  -277,
    -277,  -277,   541,  -277,   180,   114,  -277,  -277,   676,   676,
    -277,  -277,    26,  -277,   150,   204,    62,    62,     2,     2,
       2,   509,   509,   965,   965,   141,   141,   141,   141,   415,
     329,   169,   991,   494,  -277,  -277,    -6,   939,   939,   939,
     939,   939,   939,   939,   939,   939,   939,   939,   939,   779,
     627,   159,    11,   233,  -277,   234,   234,   235,   138,  -277,
      73,   195,  -277,  -277,  -277,   676,   121,    99,  -277,  -277,
    -277,    47,  -277,   913,   779,    47,  -277,  -277,  -277,   676,
    -277,  -277,  -277,    12,    47,    47,   170,  -277,   219,   111,
     123,   197,   112,  -277,  -277,   846,  -277,   121,  -277,   241,
    -277,  -277,  -277,   939,  -277,   -10,   243,    47,    42,  -277,
      47,   140,    47,   140,   244,  -277,  -277,  -277,   201,  -277,
    -277,   -10,   203,   247,   248,   117,  -277,   116,  -277,  -277,
    -277,   207,   140,  -277,   250,   119,   208,  -277,   113,   121,
    -277,    47,  -277,   203,   203,    42,  -277,   140,  -277,  -277,
      78,   140,  -277,    17,  -277,  -277,    20,  -277,  -277,  -277,
     209,   191,   193,   192,    -2,  -277,  -277,  -277,  -277,     0,
     218,  -277,  -277,  -277,  -277,  -277,  -277,   227,  -277,   259,
     262,  -277,     9,   219,   224,   260,    25,   229,  -277,   152,
    -277,   -10,   260,    10,  -277,  -277,   230,  -277,   -10,   205,
      30,   649,  -277,    47,   206,  -277,    49,   -10,    47,  -277,
    -277,   -10,  -277
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -277,  -277,  -277,   279,  -277,    63,    98,  -277,  -277,    96,
    -277,   282,   103,   -22,  -277,    29,   -60,  -277,  -277,  -277,
    -225,  -277,    33,  -277,     7,  -277,  -277,  -277,   -17,  -277,
    -277,  -277,  -277,  -277,  -277,  -276,  -178,   -27,   -98,   -74,
      -3,    -4,  -277,  -277,  -277,  -277,   -73,  -277,  -277,  -277,
    -277,  -277,   109,  -277,  -277,  -277,  -277,  -277,  -277,  -277,
     172,  -277,   -26,  -198,   -14
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -83
static const yytype_int16 yytable[] =
{
      41,    41,   213,   209,   133,   -64,    14,    14,    78,   143,
      85,    61,    62,    63,    64,    65,    14,    14,   266,    76,
     215,   209,   139,    67,   301,    71,    72,    73,   105,   205,
     164,    79,    80,   118,   215,   205,   316,   249,    77,   215,
     121,     7,   140,     8,   128,   210,   127,   330,   183,   252,
     181,    66,   290,   270,    14,   206,   300,   126,   209,   200,
     315,   329,   216,   234,   104,   137,   302,   291,   292,     2,
      85,   303,   293,   -64,    41,   309,   322,    88,    89,    90,
     144,   334,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     339,   144,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   253,   254,   179,   207,   208,   144,
     123,   240,   283,   327,   104,   205,   275,   229,   205,    41,
     332,   232,    68,   242,   203,   204,   185,   186,   187,   340,
     235,   236,   257,   342,   265,    69,   276,   291,   292,    85,
     188,    74,   293,   336,    86,    87,    88,    89,    90,   241,
     124,    82,   284,   251,   277,   211,   143,   281,   143,    77,
     226,   243,    81,   286,   195,   196,   167,    85,    83,   195,
     227,   106,    86,    87,    88,    89,    90,   120,    91,    92,
     231,   225,   104,    95,    96,    97,    98,   143,   144,   246,
     134,   247,   144,   104,   122,   233,   258,   259,   260,   324,
     325,   144,   144,   287,   288,     9,   103,   141,    10,    11,
      12,    13,    14,   -82,   145,   310,   180,   184,    15,    16,
     201,   104,    83,    17,   144,   214,    18,   144,   183,   144,
     217,   218,   221,   285,   224,   244,   237,   238,   248,   183,
     250,   267,   269,   271,   273,   274,   278,   282,   304,   337,
     280,   305,   306,   307,   341,    19,   313,   311,   144,   314,
     319,    20,    21,    22,    23,    24,    25,   312,   318,   323,
     331,   333,   338,    58,   222,   245,    26,    59,   223,   220,
      27,   317,    28,    29,    30,   279,   144,    31,    32,    33,
      34,   308,    35,    36,   289,   328,   228,   202,     0,   144,
       0,     1,     0,    -5,    -5,    -5,    -5,    -5,     0,     0,
     144,     0,     0,    -5,    -5,     0,     0,   167,    -5,     0,
     144,    -5,     0,     0,     0,   144,     0,    85,     0,     0,
       0,     0,    86,    87,    88,    89,    90,     0,    91,    92,
       0,     0,     0,    95,    96,    97,    98,     0,     0,    99,
      -5,   101,     0,     0,     0,     2,    -5,    -5,    -5,    -5,
      -5,    -5,     0,     0,     0,     0,   103,     0,     0,     0,
       0,    -5,     0,     0,     0,    -5,     0,    -5,    -5,    -5,
       0,   104,    -5,    -5,    -5,    -5,     0,    -5,    -5,    10,
      11,    12,    13,    14,     0,     0,     0,     0,     0,    15,
      16,     0,     0,     0,    17,     0,     0,    18,     0,     0,
       0,     0,     0,    85,     0,     0,     0,     0,    86,    87,
      88,    89,    90,     0,    91,    92,     0,     0,     0,    95,
      96,    97,    98,     0,     0,     0,    19,   101,     0,     0,
       0,     0,    20,    21,    22,    23,    24,    25,     0,     0,
       0,     0,   103,     0,     0,     0,     0,    26,     0,     0,
       0,    27,     0,    28,    29,    30,     0,   104,    31,    32,
      33,    34,     0,    35,    36,    10,    11,    12,    13,    14,
       0,     0,     0,     0,     0,    15,    16,     0,     0,     0,
      17,     0,    85,    18,     0,     0,     0,    86,    87,    88,
      89,    90,     0,    91,    92,     0,     0,    85,    95,    96,
      97,    98,    86,    87,    88,    89,    90,     0,     0,     0,
       0,   131,    19,    95,    96,    97,    98,     0,    20,    21,
      22,    23,    24,    25,    10,    11,    12,    13,    14,     0,
       0,     0,     0,    26,    15,    16,   104,     0,     0,    17,
      29,    30,    18,     0,    31,    32,    33,    34,     0,    35,
      36,   104,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,     0,     0,     0,     0,     0,     0,     0,
     199,    19,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    10,    11,    12,    13,    14,     0,     0,
       0,     0,    26,    15,    16,     0,     0,     0,    17,    29,
      30,    18,     0,    31,    32,    33,    34,     0,    35,    36,
      10,    11,    12,    13,    14,     0,     0,     0,     0,     0,
      15,    16,     0,     0,     0,    17,     0,     0,    18,     0,
      19,   165,    10,    11,    12,    13,    14,    21,    22,    23,
      24,    25,    15,    16,     0,     0,     0,    17,     0,     0,
      18,    26,     0,     0,     0,     0,     0,    19,   212,    10,
      11,    12,    13,    14,    21,    22,    23,    24,    25,    15,
      16,     0,     0,     0,    17,     0,     0,    18,    26,    19,
     335,     0,     0,     0,     0,     0,    21,    22,    23,    24,
      25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26,     0,     0,     0,     0,     0,    19,     0,     0,     0,
       0,     0,     0,    21,    22,    23,    24,    25,     0,     0,
       0,     0,     0,    85,     0,     0,     0,    26,    86,    87,
      88,    89,    90,     0,    91,    92,     0,    93,    94,    95,
      96,    97,    98,     0,     0,    99,   100,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   103,    77,     0,     0,     0,    85,     0,   128,
       0,     0,    86,    87,    88,    89,    90,   104,    91,    92,
       0,    93,    94,    95,    96,    97,    98,     0,     0,    99,
     100,   101,   102,    85,     0,     0,     0,     0,    86,    87,
      88,    89,    90,     0,    91,    92,   103,    93,    94,    95,
      96,    97,    98,    74,     0,    99,   100,   101,   102,     0,
       0,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   103,     0,    85,     0,   119,     0,     0,    86,
      87,    88,    89,    90,     0,    91,    92,   104,    93,    94,
      95,    96,    97,    98,     0,     0,    99,   100,   101,   102,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   103,    77,    85,     0,   138,     0,     0,
      86,    87,    88,    89,    90,     0,    91,    92,   104,    93,
      94,    95,    96,    97,    98,     0,     0,    99,   100,   101,
     102,    85,     0,     0,     0,     0,    86,    87,    88,    89,
      90,     0,    91,    92,   103,    93,    94,    95,    96,    97,
      98,     0,     0,    99,   100,   101,   102,    85,     0,   104,
       0,     0,    86,    87,    88,    89,    90,     0,    91,    92,
     103,    93,    94,    95,    96,    97,    98,   230,     0,    99,
     100,   101,   102,    85,     0,   104,     0,     0,    86,    87,
      88,    89,    90,     0,    91,    92,   103,     0,     0,    95,
      96,    97,    98,     0,     0,    99,   100,   101,   102,    85,
       0,   104,     0,     0,    86,    87,    88,    89,    90,     0,
      91,    92,   103,     0,     0,    95,    96,    97,    98,     0,
       0,    99,   100,   101,     0,     0,     0,   104,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   103,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   104
};

static const yytype_int16 yycheck[] =
{
       3,     4,   180,     9,    77,     7,     7,     7,    34,    83,
       8,    15,    16,    17,    18,    19,     7,     7,   243,    33,
       9,     9,    34,    26,     7,    29,    30,    31,    42,     9,
     104,    35,    36,    60,     9,     9,   312,   235,    48,     9,
      67,   100,    54,     4,    54,    51,    72,   323,   122,     7,
      51,     7,   277,   251,     7,    29,   281,    71,     9,   132,
      51,    51,    51,    51,    62,    79,    49,    69,    70,    55,
       8,    51,    74,    75,    77,    75,    51,    15,    16,    17,
      83,    51,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      51,   104,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,    72,    73,   120,   144,   145,   122,
       8,    10,     9,   321,    62,     9,     9,   201,     9,   132,
     328,   205,     7,    10,   138,   139,    63,    64,    65,   337,
     214,   215,   240,   341,   242,     7,    29,    69,    70,     8,
      77,    54,    74,   331,    13,    14,    15,    16,    17,    48,
      48,    11,    49,   237,    48,   179,   240,    48,   242,    48,
     196,    48,     7,   271,    80,    81,   180,     8,    28,    80,
      81,    50,    13,    14,    15,    16,    17,    34,    19,    20,
     204,   195,    62,    24,    25,    26,    27,   271,   201,   225,
      86,   227,   205,    62,    50,   209,    66,    67,    68,    57,
      58,   214,   215,   273,   274,     0,    47,     7,     3,     4,
       5,     6,     7,     7,     7,   299,    50,     7,    13,    14,
      50,    62,    28,    18,   237,    76,    21,   240,   312,   242,
       7,     7,     7,   269,    49,    48,    76,    28,     7,   323,
       7,     7,    51,    50,     7,     7,    49,    49,    49,   333,
      10,    70,    69,    71,   338,    50,     7,    49,   271,     7,
      10,    56,    57,    58,    59,    60,    61,    50,    54,    50,
      50,    76,    76,     4,   188,   222,    71,     5,   190,   186,
      75,   313,    77,    78,    79,   262,   299,    82,    83,    84,
      85,   294,    87,    88,   275,   322,   197,   135,    -1,   312,
      -1,     1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
     323,    -1,    -1,    13,    14,    -1,    -1,   331,    18,    -1,
     333,    21,    -1,    -1,    -1,   338,    -1,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    -1,    -1,    24,    25,    26,    27,    -1,    -1,    30,
      50,    32,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    71,    -1,    -1,    -1,    75,    -1,    77,    78,    79,
      -1,    62,    82,    83,    84,    85,    -1,    87,    88,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,
      14,    -1,    -1,    -1,    18,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    -1,    -1,    -1,    24,
      25,    26,    27,    -1,    -1,    -1,    50,    32,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    71,    -1,    -1,
      -1,    75,    -1,    77,    78,    79,    -1,    62,    82,    83,
      84,    85,    -1,    87,    88,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    -1,    -1,    13,    14,    -1,    -1,    -1,
      18,    -1,     8,    21,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    -1,    19,    20,    -1,    -1,     8,    24,    25,
      26,    27,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    49,    50,    24,    25,    26,    27,    -1,    56,    57,
      58,    59,    60,    61,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    71,    13,    14,    62,    -1,    -1,    18,
      78,    79,    21,    -1,    82,    83,    84,    85,    -1,    87,
      88,    62,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      49,    50,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    71,    13,    14,    -1,    -1,    -1,    18,    78,
      79,    21,    -1,    82,    83,    84,    85,    -1,    87,    88,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,
      13,    14,    -1,    -1,    -1,    18,    -1,    -1,    21,    -1,
      50,    51,     3,     4,     5,     6,     7,    57,    58,    59,
      60,    61,    13,    14,    -1,    -1,    -1,    18,    -1,    -1,
      21,    71,    -1,    -1,    -1,    -1,    -1,    50,    51,     3,
       4,     5,     6,     7,    57,    58,    59,    60,    61,    13,
      14,    -1,    -1,    -1,    18,    -1,    -1,    21,    71,    50,
      51,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,     8,    -1,    -1,    -1,    71,    13,    14,
      15,    16,    17,    -1,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,     8,    -1,    54,
      -1,    -1,    13,    14,    15,    16,    17,    62,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    47,    22,    23,    24,
      25,    26,    27,    54,    -1,    30,    31,    32,    33,    -1,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    -1,     8,    -1,    51,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    62,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,     8,    -1,    10,    -1,    -1,
      13,    14,    15,    16,    17,    -1,    19,    20,    62,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    -1,    19,    20,    47,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,     8,    -1,    62,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    19,    20,
      47,    22,    23,    24,    25,    26,    27,    54,    -1,    30,
      31,    32,    33,     8,    -1,    62,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    47,    -1,    -1,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,     8,
      -1,    62,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    47,    -1,    -1,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    -1,    -1,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    55,   102,   103,   111,   112,   100,     4,     0,
       3,     4,     5,     6,     7,    13,    14,    18,    21,    50,
      56,    57,    58,    59,    60,    61,    71,    75,    77,    78,
      79,    82,    83,    84,    85,    87,    88,   104,   105,   130,
     140,   141,   142,   143,   144,   145,   147,   148,   149,   150,
     151,   154,   155,   156,   157,   158,   159,   162,   104,   112,
     141,   142,   142,   142,   142,   142,     7,   141,     7,     7,
     110,   142,   142,   142,    54,   165,   165,    48,   163,   142,
     142,     7,    11,    28,   138,     8,    13,    14,    15,    16,
      17,    19,    20,    22,    23,    24,    25,    26,    27,    30,
      31,    32,    33,    47,    62,   165,    50,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,   138,    51,
      34,   138,    50,     8,    48,   106,   165,   163,    54,   163,
     164,    49,   146,   147,    86,   160,   161,   165,    10,    34,
      54,     7,   139,   140,   141,     7,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   140,    51,   137,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
      50,    51,   136,   140,     7,    63,    64,    65,    77,   107,
     108,   109,   118,   119,   120,    80,    81,   152,   153,    49,
     147,    50,   161,   142,   142,     9,    29,   138,   138,     9,
      51,   165,    51,   137,    76,     9,    51,     7,     7,   113,
     113,     7,   110,   107,    49,   142,   163,    81,   153,   140,
      54,   165,   140,   142,    51,   140,   140,    76,    28,   114,
      10,    48,    10,    48,    48,   106,   163,   163,     7,   164,
       7,   140,     7,    72,    73,   115,   116,   139,    66,    67,
      68,   121,   122,   123,   134,   139,   121,     7,   135,    51,
     164,    50,   117,     7,     7,     9,    29,    48,    49,   123,
      10,    48,    49,     9,    49,   163,   139,   117,   117,   116,
     121,    69,    70,    74,   124,   125,   126,   131,   132,   133,
     121,     7,    49,    51,    49,    70,    69,    71,   125,    75,
     140,    49,    50,     7,     7,    51,   136,   114,    54,    10,
     127,   129,    51,    50,    57,    58,   128,   164,   129,    51,
     136,    50,   164,    76,    51,    51,   137,   140,    76,    51,
     164,   140,   164
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
#line 143 "beacon.y"
    {
		yyclearin;
	;}
    break;

  case 6:
#line 151 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 7:
#line 157 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 8:
#line 161 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 9:
#line 165 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 10:
#line 171 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 11:
#line 178 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value)
	;}
    break;

  case 12:
#line 185 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 16:
#line 195 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 17:
#line 199 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 18:
#line 206 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 20:
#line 214 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 21:
#line 218 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 23:
#line 226 "beacon.y"
    {
		(yyval.ast_value) = ast_new_import_decl_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 24:
#line 233 "beacon.y"
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 25:
#line 240 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameterized_typename((yyvsp[(1) - (2)].string_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 26:
#line 247 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 27:
#line 251 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 28:
#line 258 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 29:
#line 262 "beacon.y"
    {
		(yyval.ast_value) = ast_new_type_parameter_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 30:
#line 269 "beacon.y"
    {
		(yyval.ast_value) = ast_new_type_parameter((yyvsp[(1) - (2)].string_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 31:
#line 273 "beacon.y"
    {
		(yyval.ast_value) = ast_new_type_in_parameter((yyvsp[(2) - (3)].string_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 32:
#line 277 "beacon.y"
    {
		(yyval.ast_value) = ast_new_type_out_parameter((yyvsp[(2) - (3)].string_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 33:
#line 284 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 34:
#line 288 "beacon.y"
    {
		(yyval.ast_value) = ast_new_type_parameter_rule_list((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 35:
#line 295 "beacon.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 36:
#line 299 "beacon.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 37:
#line 306 "beacon.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 38:
#line 310 "beacon.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (6)].string_value), (yyvsp[(4) - (6)].ast_value));
	;}
    break;

  case 39:
#line 317 "beacon.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 40:
#line 321 "beacon.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 41:
#line 328 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 44:
#line 337 "beacon.y"
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 45:
#line 344 "beacon.y"
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[(1) - (3)].access_level_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 46:
#line 351 "beacon.y"
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 47:
#line 355 "beacon.y"
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[(1) - (2)].ast_value), ast_new_member_decl((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 51:
#line 368 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 52:
#line 372 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 53:
#line 379 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (5)].chain_type_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 54:
#line 383 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (4)].chain_type_value), ast_new_blank());
	;}
    break;

  case 55:
#line 390 "beacon.y"
    {
		(yyval.chain_type_value) = chain_type_super;
	;}
    break;

  case 56:
#line 394 "beacon.y"
    {
		(yyval.chain_type_value) = chain_type_this;
	;}
    break;

  case 57:
#line 401 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 59:
#line 409 "beacon.y"
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[(2) - (8)].string_value), (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 60:
#line 413 "beacon.y"
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[(2) - (7)].string_value), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 61:
#line 420 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl((yyvsp[(1) - (10)].modifier_type_value), (yyvsp[(3) - (10)].string_value), (yyvsp[(4) - (10)].ast_value), (yyvsp[(6) - (10)].ast_value), (yyvsp[(10) - (10)].ast_value), (yyvsp[(9) - (10)].ast_value));
	;}
    break;

  case 62:
#line 424 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[(1) - (9)].modifier_type_value), (yyvsp[(3) - (9)].string_value), (yyvsp[(4) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 63:
#line 431 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[(1) - (4)].modifier_type_value), (yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].string_value));
	;}
    break;

  case 64:
#line 438 "beacon.y"
    {
		(yyval.modifier_type_value) = modifier_none;
	;}
    break;

  case 65:
#line 442 "beacon.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 66:
#line 446 "beacon.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 67:
#line 450 "beacon.y"
    {
		(yyval.modifier_type_value) = modifier_static;
	;}
    break;

  case 68:
#line 454 "beacon.y"
    {
		(yyval.modifier_type_value) = modifier_native;
	;}
    break;

  case 69:
#line 461 "beacon.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 70:
#line 465 "beacon.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 71:
#line 469 "beacon.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 72:
#line 476 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 73:
#line 480 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[(3) - (3)].string_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 74:
#line 487 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].string_value));
	;}
    break;

  case 75:
#line 491 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].string_value), (yyvsp[(1) - (4)].ast_value))
	;}
    break;

  case 76:
#line 498 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 77:
#line 502 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(3) - (3)].ast_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 78:
#line 509 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 79:
#line 513 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 80:
#line 520 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 81:
#line 524 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 82:
#line 531 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 83:
#line 538 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 84:
#line 542 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(3) - (3)].string_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 85:
#line 551 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 88:
#line 559 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_pos, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 89:
#line 563 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_neg, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 90:
#line 567 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 91:
#line 571 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 92:
#line 575 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 93:
#line 579 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 94:
#line 583 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 95:
#line 587 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 96:
#line 591 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_equal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 97:
#line 595 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_notequal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 98:
#line 599 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 99:
#line 603 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 100:
#line 607 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 101:
#line 611 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 102:
#line 615 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 103:
#line 619 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 104:
#line 623 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 105:
#line 627 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 106:
#line 631 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 107:
#line 635 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 108:
#line 639 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_and_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 109:
#line 643 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 110:
#line 647 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 111:
#line 651 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 112:
#line 655 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 113:
#line 659 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_gt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 114:
#line 663 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_ge, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 115:
#line 667 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 116:
#line 671 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_le, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 117:
#line 675 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 118:
#line 679 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 119:
#line 683 "beacon.y"
    {
		(yyval.ast_value) = ast_new_as((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 120:
#line 687 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_childa, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 121:
#line 691 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_not, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 122:
#line 695 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 123:
#line 699 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 124:
#line 703 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 125:
#line 707 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), ast_new_blank());
	;}
    break;

  case 126:
#line 711 "beacon.y"
    {
		(yyval.ast_value) = ast_new_this();
	;}
    break;

  case 127:
#line 715 "beacon.y"
    {
		(yyval.ast_value) = ast_new_super();
	;}
    break;

  case 129:
#line 722 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 130:
#line 726 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].string_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 135:
#line 736 "beacon.y"
    {
		(yyval.ast_value) = ast_new_true();
	;}
    break;

  case 136:
#line 740 "beacon.y"
    {
		(yyval.ast_value) = ast_new_false();
	;}
    break;

  case 137:
#line 744 "beacon.y"
    {
		(yyval.ast_value) = ast_new_null();
	;}
    break;

  case 138:
#line 753 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 139:
#line 757 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 140:
#line 763 "beacon.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 152:
#line 780 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].string_value));
	;}
    break;

  case 153:
#line 786 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 154:
#line 792 "beacon.y"
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 155:
#line 798 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 156:
#line 802 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 157:
#line 806 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 158:
#line 810 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 160:
#line 817 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 161:
#line 823 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 162:
#line 829 "beacon.y"
    {
		(yyval.ast_value) = ast_new_while((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 163:
#line 835 "beacon.y"
    {
		(yyval.ast_value) = ast_new_break();
	;}
    break;

  case 164:
#line 841 "beacon.y"
    {
		(yyval.ast_value) = ast_new_continue();
	;}
    break;

  case 165:
#line 847 "beacon.y"
    {
		(yyval.ast_value) = ast_new_return((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 166:
#line 853 "beacon.y"
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 167:
#line 859 "beacon.y"
    {
		(yyval.ast_value) = ast_new_try((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 168:
#line 865 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 169:
#line 869 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 170:
#line 875 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].string_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 171:
#line 881 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (5)].ast_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 172:
#line 888 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 173:
#line 892 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 174:
#line 898 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3028 "beacon.tab.c"
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


#line 906 "beacon.y"





