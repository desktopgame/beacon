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
     COMMA_OPT = 265,
     COLON = 266,
     COLO_COLO = 267,
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
     POSITIVE = 341,
     NEGATIVE = 342
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
#define POSITIVE 341
#define NEGATIVE 342




/* Copy the first part of user declarations.  */
#line 1 "signal.y"

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
/* Line 193 of yacc.c.  */
#line 295 "signal.tab.c"
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
#line 320 "signal.tab.c"

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
#define YYFINAL  68
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   939

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  158
/* YYNRULES -- Number of states.  */
#define YYNSTATES  312

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   342

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      88,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      89,     2,    90,     2,     2,     2,     2,     2,     2,     2,
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
      85,    86,    87
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    20,
      24,    28,    30,    32,    34,    36,    39,    40,    42,    44,
      48,    51,    54,    55,    59,    61,    65,    68,    72,    76,
      77,    81,    87,    95,   101,   108,   114,   122,   123,   125,
     127,   130,   134,   136,   139,   141,   143,   145,   153,   160,
     166,   171,   173,   175,   176,   178,   187,   195,   206,   216,
     221,   222,   225,   228,   230,   232,   234,   236,   238,   240,
     244,   247,   252,   254,   258,   259,   263,   265,   269,   272,
     274,   277,   280,   284,   288,   292,   296,   300,   304,   308,
     312,   316,   320,   324,   328,   332,   336,   340,   344,   348,
     352,   356,   360,   364,   368,   372,   376,   380,   384,   388,
     392,   396,   399,   402,   406,   408,   410,   412,   414,   416,
     418,   420,   422,   425,   428,   430,   432,   434,   436,   438,
     440,   442,   444,   446,   448,   452,   458,   464,   470,   478,
     485,   494,   496,   499,   505,   511,   514,   517,   521,   525,
     529,   531,   534,   541,   545,   548,   550,   552,   554
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      92,     0,    -1,    93,    -1,     1,    88,    -1,   131,    -1,
     100,    -1,    94,    -1,   118,    -1,    75,    99,    95,    -1,
      46,    98,    47,    -1,    75,    99,    95,    -1,   106,    -1,
     108,    -1,   107,    -1,    96,    -1,    97,    96,    -1,    -1,
      97,    -1,     7,    -1,    99,     8,     7,    -1,    53,     4,
      -1,     7,   102,    -1,    -1,    26,   103,    24,    -1,   104,
      -1,   103,     9,   104,    -1,     7,   105,    -1,    70,     7,
     105,    -1,    71,     7,   105,    -1,    -1,    48,   127,    49,
      -1,    62,   101,    46,   109,    47,    -1,    62,   101,    11,
     127,    46,   109,    47,    -1,    63,     7,    46,   123,    47,
      -1,    63,     7,    46,   123,     9,    47,    -1,    61,   101,
      46,   109,    47,    -1,    61,   101,    11,   127,    46,   109,
      47,    -1,    -1,   110,    -1,   111,    -1,   110,   111,    -1,
     122,    11,   112,    -1,   113,    -1,   112,   113,    -1,   114,
      -1,   119,    -1,   120,    -1,    72,    69,    48,   124,    49,
     117,   148,    -1,    72,    69,    48,    49,   117,   148,    -1,
      11,   116,    48,   125,    49,    -1,    11,   116,    48,    49,
      -1,    56,    -1,    55,    -1,    -1,   115,    -1,    73,     7,
      48,   124,    49,    74,   128,   148,    -1,    73,     7,    48,
      49,    74,   128,   148,    -1,   121,    73,     7,   102,    48,
     124,    49,    74,   128,   148,    -1,   121,    73,     7,   102,
      48,    49,    74,   128,   148,    -1,   121,   128,     7,    52,
      -1,    -1,    67,    68,    -1,    68,    67,    -1,    67,    -1,
      68,    -1,    64,    -1,    65,    -1,    66,    -1,     7,    -1,
     123,     9,     7,    -1,   128,     7,    -1,   124,     9,   128,
       7,    -1,   129,    -1,   125,     9,   129,    -1,    -1,    89,
     127,    90,    -1,   128,    -1,   127,     9,   128,    -1,     7,
     126,    -1,   130,    -1,    13,   129,    -1,    14,   129,    -1,
     129,    13,   129,    -1,   129,    14,   129,    -1,   129,    15,
     129,    -1,   129,    16,   129,    -1,   129,    17,   129,    -1,
     129,    30,   129,    -1,   129,    22,   129,    -1,   129,    23,
     129,    -1,   129,    28,   129,    -1,   129,    45,   129,    -1,
     129,    31,   129,    -1,   129,    29,   129,    -1,   129,    32,
     129,    -1,   129,    33,   129,    -1,   129,    34,   129,    -1,
     129,    35,   129,    -1,   129,    36,   129,    -1,   129,    37,
     129,    -1,   129,    38,   129,    -1,   129,    39,   129,    -1,
     129,    42,   129,    -1,   129,    40,   129,    -1,   129,    41,
     129,    -1,   129,    24,   129,    -1,   129,    25,   129,    -1,
     129,    26,   129,    -1,   129,    27,   129,    -1,   129,    19,
     129,    -1,   129,    20,   129,    -1,    21,   129,    -1,    18,
     129,    -1,    48,   129,    49,    -1,     5,    -1,     6,    -1,
       3,    -1,     4,    -1,    57,    -1,    58,    -1,    59,    -1,
     132,    -1,   131,   132,    -1,   129,   149,    -1,   133,    -1,
     134,    -1,   135,    -1,   136,    -1,   139,    -1,   140,    -1,
     141,    -1,   142,    -1,   143,    -1,   144,    -1,   128,     7,
      52,    -1,   128,     7,    32,   129,   149,    -1,    54,     7,
      32,   129,   149,    -1,    77,    48,   129,    49,   147,    -1,
      77,    48,   129,    49,   147,    79,   147,    -1,    77,    48,
     129,    49,   147,   137,    -1,    77,    48,   129,    49,   147,
     137,    79,   147,    -1,   138,    -1,   137,   138,    -1,    78,
      48,   129,    49,   147,    -1,    80,    48,   129,    49,   148,
      -1,    81,   149,    -1,    82,   149,    -1,    76,   129,   149,
      -1,    85,   129,   149,    -1,    83,   147,   145,    -1,   146,
      -1,   145,   146,    -1,    84,    48,   128,     7,    49,   147,
      -1,    46,   131,    47,    -1,    46,    47,    -1,    52,    -1,
     147,    -1,    52,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   126,   126,   127,   134,   138,   142,   146,   153,   160,
     167,   171,   172,   173,   177,   181,   189,   192,   196,   200,
     207,   214,   222,   225,   232,   236,   243,   247,   251,   259,
     262,   269,   273,   280,   284,   291,   295,   303,   306,   310,
     311,   318,   325,   329,   336,   337,   338,   342,   346,   353,
     357,   364,   368,   376,   379,   383,   387,   394,   398,   405,
     413,   416,   420,   424,   428,   435,   439,   443,   450,   454,
     461,   465,   472,   476,   484,   487,   494,   498,   505,   515,
     516,   520,   524,   528,   532,   536,   540,   544,   548,   552,
     556,   560,   564,   568,   572,   576,   580,   584,   588,   592,
     596,   600,   604,   608,   612,   616,   620,   624,   628,   632,
     635,   638,   642,   646,   652,   653,   654,   655,   656,   660,
     664,   673,   677,   683,   687,   688,   689,   690,   691,   692,
     693,   694,   695,   696,   699,   705,   711,   717,   721,   725,
     729,   735,   736,   742,   748,   754,   760,   766,   772,   778,
     784,   788,   794,   805,   809,   815,   819,   822,   823
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR_LITERAL", "STRING_LITERAL", "INT",
  "DOUBLE", "IDENT", "DOT", "COMMA", "COMMA_OPT", "COLON", "COLO_COLO",
  "ADD", "SUB", "MUL", "DIV", "MOD", "NOT", "LSHIFT", "RSHIFT", "CHILDA",
  "EQUAL", "NOTEQUAL", "GT", "GE", "LT", "LE", "BIT_AND", "LOGIC_AND",
  "BIT_OR", "LOGIC_OR", "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "AND_ASSIGN", "OR_ASSIGN", "LSHIFT_ASSIGN",
  "RSHIFT_ASSIGN", "EXC_OR_ASSIGN", "INC", "DEC", "EXC_OR", "LCB", "RCB",
  "LRB", "RRB", "LSB", "RSB", "SEMI", "IMPORT", "VAR", "THIS", "SUPER",
  "TRUE_TOK", "FALSE_TOK", "NULL_TOK", "AS", "INTERFACE", "CLASS", "ENUM",
  "PUBLIC", "PRIVATE", "PROTECTED", "STATIC", "NATIVE", "NEW", "IN", "OUT",
  "CTOR", "DEF", "ARROW", "NAMESPACE", "RETURN", "IF", "ELIF", "ELSE",
  "WHILE", "BREAK", "CONTINUE", "TRY", "CATCH", "THROW", "POSITIVE",
  "NEGATIVE", "'\\n'", "'<'", "'>'", "$accept", "compilation_unit",
  "program", "namespace_decl", "namespace_body", "namespace_member_decl",
  "namespace_member_decl_list", "namespace_member_decl_optional",
  "namespace_path", "import", "parameterized_typename",
  "type_parameter_group", "type_parameter_list", "type_parameter",
  "type_parameter_rule_list", "class_decl", "enum_decl", "interface_decl",
  "access_member_tree_opt", "access_member_tree", "access_member_list",
  "member_define_list", "member_define", "constructor_define",
  "constructor_chain", "constructor_chain_type_T",
  "constructor_chain_optional", "function_define", "method_define",
  "field_define", "modifier_type_T", "access_level_T", "ident_list",
  "parameter_list", "argument_list", "typename_group", "typename_list",
  "typename_T", "expression", "primary", "stmt_list", "stmt",
  "variable_decl_stmt", "variable_init_stmt", "inferenced_type_init_stmt",
  "if_stmt", "elif_list", "elif", "while_stmt", "break_stmt",
  "continue_stmt", "return_stmt", "throw_stmt", "try_stmt",
  "catch_stmt_list", "catch_stmt", "scope", "scope_optional", "stmt_term", 0
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
     335,   336,   337,   338,   339,   340,   341,   342,    10,    60,
      62
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    92,    93,    93,    93,    93,    94,    95,
      96,    96,    96,    96,    97,    97,    98,    98,    99,    99,
     100,   101,   102,   102,   103,   103,   104,   104,   104,   105,
     105,   106,   106,   107,   107,   108,   108,   109,   109,   110,
     110,   111,   112,   112,   113,   113,   113,   114,   114,   115,
     115,   116,   116,   117,   117,   118,   118,   119,   119,   120,
     121,   121,   121,   121,   121,   122,   122,   122,   123,   123,
     124,   124,   125,   125,   126,   126,   127,   127,   128,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   130,   130,   130,   130,   130,   130,
     130,   131,   131,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   133,   134,   135,   136,   136,   136,
     136,   137,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   145,   146,   147,   147,   148,   148,   149,   149
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     3,
       3,     1,     1,     1,     1,     2,     0,     1,     1,     3,
       2,     2,     0,     3,     1,     3,     2,     3,     3,     0,
       3,     5,     7,     5,     6,     5,     7,     0,     1,     1,
       2,     3,     1,     2,     1,     1,     1,     7,     6,     5,
       4,     1,     1,     0,     1,     8,     7,    10,     9,     4,
       0,     2,     2,     1,     1,     1,     1,     1,     1,     3,
       2,     4,     1,     3,     0,     3,     1,     3,     2,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     5,     5,     5,     7,     6,
       8,     1,     2,     5,     5,     2,     2,     3,     3,     3,
       1,     2,     6,     3,     2,     1,     1,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,   116,   117,   114,   115,    74,     0,     0,     0,
       0,     0,     0,     0,   118,   119,   120,     0,     0,     0,
       0,     0,   158,   158,     0,     0,     0,     2,     6,     5,
       7,     0,   158,    79,     4,   121,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,     3,     0,    78,    80,
      81,   112,   111,     0,    20,     0,     0,    18,     0,   158,
       0,     0,   157,   145,   146,     0,     0,   158,     1,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   123,
     122,     0,    76,   113,     0,     0,     0,    16,     8,   147,
       0,     0,   154,     0,     0,   149,   150,   148,     0,   134,
      82,    83,    84,    85,    86,   109,   110,    88,    89,   105,
     106,   107,   108,    90,    93,    87,    92,    94,    95,    96,
      97,    98,    99,   100,   101,   103,   104,   102,    91,     0,
      75,   158,     0,     0,     0,    19,     0,     0,     0,     0,
      14,    17,     0,    11,    13,    12,     0,     0,   153,     0,
     151,   158,    77,   136,     0,     0,     0,    70,    22,     0,
       0,     0,     0,    15,     9,   137,   155,   156,   144,     0,
     135,     0,     0,     0,     0,    21,     0,    37,     0,    37,
       0,    10,     0,     0,   139,   141,     0,    56,    71,     0,
      29,     0,     0,     0,    24,     0,    65,    66,    67,     0,
      38,    39,     0,     0,     0,    68,     0,     0,   138,     0,
     142,     0,    55,     0,    26,    29,    29,     0,    23,    37,
      35,    40,    60,    37,    31,     0,    33,     0,   140,   152,
       0,    27,    28,    25,     0,    63,    64,     0,    41,    42,
      44,    45,    46,     0,     0,    69,    34,     0,    30,    36,
      61,    62,     0,    43,     0,     0,    32,   143,     0,    22,
       0,    53,     0,     0,    59,     0,    54,     0,    53,     0,
      52,    51,     0,    48,     0,     0,     0,     0,    47,     0,
       0,    50,     0,    72,     0,     0,     0,    49,    58,     0,
      73,    57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,    28,   108,   160,   161,   162,    58,    29,
     179,   195,   213,   214,   234,   163,   164,   165,   219,   220,
     221,   258,   259,   260,   286,   292,   287,    30,   261,   262,
     263,   222,   226,   153,   302,    48,   101,    31,    32,    33,
      34,    35,    36,    37,    38,    39,   204,   205,    40,    41,
      42,    43,    44,    45,   115,   116,   187,   188,    63
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -253
static const yytype_int16 yypact[] =
{
     187,   -64,  -253,  -253,  -253,  -253,   -53,   270,   270,   270,
     270,   270,   109,   113,  -253,  -253,  -253,   115,   121,   270,
      82,    85,    94,    94,    88,   270,   139,  -253,  -253,  -253,
    -253,   138,   478,  -253,   405,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,  -253,   143,  -253,   190,
     190,  -253,  -253,   512,  -253,   119,   104,  -253,    92,   478,
     270,   270,  -253,  -253,  -253,   291,    69,   478,  -253,   -13,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,  -253,
    -253,     2,  -253,  -253,   270,     6,   151,   -31,  -253,  -253,
     549,   586,  -253,   348,   116,    69,  -253,  -253,   270,  -253,
     897,   897,   190,   190,   190,   869,   869,   693,   693,   726,
     726,   726,   726,   435,   759,   825,   792,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   858,   143,
    -253,   478,    91,     0,   154,  -253,   159,   159,   160,   121,
    -253,   -31,   124,  -253,  -253,  -253,    88,    -5,  -253,   143,
    -253,   478,  -253,  -253,   143,   143,    98,  -253,   147,   108,
     110,   128,    92,  -253,  -253,   -51,  -253,  -253,  -253,   168,
    -253,    -5,   169,   143,    35,  -253,   143,    77,   143,    77,
     170,  -253,   130,    88,   -45,  -253,   131,  -253,  -253,    -5,
     134,   172,   176,    16,  -253,   101,  -253,  -253,  -253,   140,
      77,  -253,   178,   103,   148,  -253,    93,   270,  -253,    88,
    -253,    88,  -253,   143,  -253,   134,   134,    35,  -253,    77,
    -253,  -253,    59,    77,  -253,     3,  -253,   623,  -253,  -253,
      11,  -253,  -253,  -253,   149,   129,   132,   133,    31,  -253,
    -253,  -253,  -253,    22,   156,  -253,  -253,    88,  -253,  -253,
    -253,  -253,   150,  -253,   197,   199,  -253,  -253,     7,   147,
     155,   198,    12,   162,  -253,   -10,  -253,    -5,   198,    10,
    -253,  -253,   164,  -253,    -5,   141,    13,   111,  -253,   143,
     142,  -253,    87,   660,    -5,   143,   270,  -253,  -253,    -5,
     660,  -253
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -253,  -253,  -253,  -253,    32,    56,  -253,  -253,    60,  -253,
      61,   -46,  -253,    -3,  -178,  -253,  -253,  -253,  -191,  -253,
      17,  -253,   -22,  -253,  -253,  -253,   -50,  -253,  -253,  -253,
    -253,  -253,  -253,  -252,  -253,  -253,   -89,   -12,    -7,  -253,
     174,   -19,  -253,  -253,  -253,  -253,  -253,    38,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,   135,   -18,  -186,   -16
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -61
static const yytype_int16 yytable[] =
{
      49,    50,    51,    52,    53,   207,    66,    64,   224,   175,
     265,   149,    59,     6,     6,   100,    99,     6,    67,   118,
     149,   175,   175,   232,    46,   237,   282,   202,   203,     6,
     156,   157,   158,   202,   229,   102,    47,   296,   -60,   119,
     238,    65,   210,   109,   159,   290,   291,   186,   254,   176,
     266,   117,   264,   110,   111,   152,   281,   251,   252,   295,
     268,   288,   300,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   150,   154,   100,   274,   306,   151,   255,   256,
     106,   293,   245,   257,   -60,   211,   212,   215,   298,   223,
     149,   171,   149,    54,     2,     3,     4,     5,   308,   196,
      55,   198,    56,   311,     7,     8,   255,   256,    57,     9,
      60,   257,    10,    61,    65,   173,   307,   172,   107,    68,
     246,   216,   217,   218,   250,    69,    62,   239,   185,   243,
       6,   104,   105,   114,   197,   190,   199,   189,   155,    11,
     301,   177,   191,   192,   169,   174,   178,   181,    14,    15,
      16,   184,   193,   194,   200,   206,   208,   225,   227,   235,
     231,   209,   233,   236,   102,   228,   102,   240,     1,   242,
       2,     3,     4,     5,     6,   244,   269,   270,   278,   271,
       7,     8,   272,   276,   279,     9,   280,   284,    10,   285,
     289,   248,   297,   249,   201,   299,   305,   183,   180,   182,
     247,   102,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,   283,   253,    11,   273,   241,   294,   113,
      12,    13,   230,     0,    14,    15,    16,     0,     0,   277,
     170,   275,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,    18,    19,    20,     0,   154,    21,    22,    23,
      24,     0,    25,     2,     3,     4,     5,   154,     0,     0,
       0,     0,     0,     7,     8,     0,     0,   304,     9,     0,
     303,    10,     0,   309,     2,     3,     4,     5,     6,   310,
       0,     0,     0,     0,     7,     8,     0,     0,     0,     9,
       0,     0,    10,     0,     0,     0,     0,     0,    11,     0,
       0,     0,     0,     0,     0,     0,     0,    14,    15,    16,
       0,     0,     0,     0,     0,     0,     0,     0,   112,    11,
       0,     0,     0,     0,     0,    13,     0,     0,    14,    15,
      16,     2,     3,     4,     5,     6,     0,     0,     0,     0,
       0,     7,     8,     0,     0,     0,     9,    19,    20,    10,
       0,    21,    22,    23,    24,     0,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   168,    11,     0,     0,     0,
       0,     0,    13,     0,     0,    14,    15,    16,     2,     3,
       4,     5,     6,     0,     0,     0,     0,     0,     7,     8,
       0,     0,     0,     9,    19,    20,    10,     0,    21,    22,
      23,    24,     0,    25,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    11,    75,    76,     0,     0,     0,    13,
       0,     0,    14,    15,    16,    85,     0,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,     0,     0,
      98,    19,    20,     0,     0,    21,    22,    23,    24,     0,
      25,    70,    71,    72,    73,    74,     0,    75,    76,     0,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,     0,     0,    98,     0,    70,    71,    72,    73,    74,
      62,    75,    76,     0,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,     0,     0,    98,     0,     0,
       0,   103,    70,    71,    72,    73,    74,     0,    75,    76,
       0,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,     0,     0,    98,     0,     0,     0,   166,    70,
      71,    72,    73,    74,     0,    75,    76,     0,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,     0,
       0,    98,     0,     0,     0,   167,    70,    71,    72,    73,
      74,     0,    75,    76,     0,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,     0,     0,    98,     0,
       0,     0,   267,    70,    71,    72,    73,    74,     0,    75,
      76,     0,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,     0,     0,    98,    70,    71,    72,    73,
      74,     0,    75,    76,     0,     0,     0,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,     0,     0,    98,    70,
      71,    72,    73,    74,     0,    75,    76,     0,     0,     0,
       0,     0,     0,     0,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,     0,
       0,    98,    70,    71,    72,    73,    74,     0,    75,    76,
       0,     0,     0,     0,     0,     0,     0,    83,     0,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,     0,     0,    98,    70,    71,    72,    73,    74,
       0,    75,    76,     0,     0,     0,     0,     0,     0,     0,
      83,     0,    85,     0,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,     0,     0,    98,    70,    71,
      72,    73,    74,     0,    75,    76,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,     0,     0,
      98,    70,    71,    72,    73,    74,     0,    75,    76,     0,
       0,     0,    70,    71,    72,    73,    74,     0,     0,     0,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    72,    73,    74,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97
};

static const yytype_int16 yycheck[] =
{
       7,     8,     9,    10,    11,   191,    24,    23,   199,     9,
       7,     9,    19,     7,     7,    34,    32,     7,    25,    32,
       9,     9,     9,   209,    88,     9,   278,    78,    79,     7,
      61,    62,    63,    78,    79,    47,    89,   289,     7,    52,
      24,    46,     7,    59,    75,    55,    56,    52,   239,    49,
      47,    67,   243,    60,    61,    49,    49,   235,   236,    49,
      49,    49,    49,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    90,   105,   113,    73,     9,   104,    67,    68,
       8,   287,     9,    72,    73,    70,    71,   196,   294,   198,
       9,   118,     9,     4,     3,     4,     5,     6,   304,    11,
       7,    11,     7,   309,    13,    14,    67,    68,     7,    18,
      48,    72,    21,    48,    46,   151,    49,   149,    46,     0,
      47,    64,    65,    66,   233,     7,    52,    46,   166,    46,
       7,    32,    48,    84,    46,   171,    46,   169,     7,    48,
      49,     7,   174,   175,    48,    74,     7,     7,    57,    58,
      59,    47,    74,    26,    46,     7,     7,     7,    48,     7,
      49,   193,    48,     7,   196,   203,   198,    47,     1,    11,
       3,     4,     5,     6,     7,    47,    47,    68,    48,    67,
      13,    14,    69,    47,     7,    18,     7,    52,    21,    11,
      48,   229,    48,   231,   182,    74,    74,   161,   157,   159,
     227,   233,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,   279,   237,    48,   258,   220,   288,    65,
      53,    54,   204,    -1,    57,    58,    59,    -1,    -1,   267,
     115,   263,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    -1,    75,    76,    77,    -1,   278,    80,    81,    82,
      83,    -1,    85,     3,     4,     5,     6,   289,    -1,    -1,
      -1,    -1,    -1,    13,    14,    -1,    -1,   299,    18,    -1,
     297,    21,    -1,   305,     3,     4,     5,     6,     7,   306,
      -1,    -1,    -1,    -1,    13,    14,    -1,    -1,    -1,    18,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    57,    58,
      59,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      -1,    13,    14,    -1,    -1,    -1,    18,    76,    77,    21,
      -1,    80,    81,    82,    83,    -1,    85,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    -1,    -1,    57,    58,    59,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,
      -1,    -1,    -1,    18,    76,    77,    21,    -1,    80,    81,
      82,    83,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    48,    19,    20,    -1,    -1,    -1,    54,
      -1,    -1,    57,    58,    59,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    -1,
      45,    76,    77,    -1,    -1,    80,    81,    82,    83,    -1,
      85,    13,    14,    15,    16,    17,    -1,    19,    20,    -1,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    -1,    45,    -1,    13,    14,    15,    16,    17,
      52,    19,    20,    -1,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    -1,    45,    -1,    -1,
      -1,    49,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    -1,    45,    -1,    -1,    -1,    49,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      -1,    45,    -1,    -1,    -1,    49,    13,    14,    15,    16,
      17,    -1,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    -1,    45,    -1,
      -1,    -1,    49,    13,    14,    15,    16,    17,    -1,    19,
      20,    -1,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    -1,    45,    13,    14,    15,    16,
      17,    -1,    19,    20,    -1,    -1,    -1,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    -1,    45,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      -1,    45,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    -1,    45,    13,    14,    15,    16,    17,
      -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    30,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    -1,    45,    13,    14,
      15,    16,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    -1,
      45,    13,    14,    15,    16,    17,    -1,    19,    20,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,    13,    14,    18,
      21,    48,    53,    54,    57,    58,    59,    73,    75,    76,
      77,    80,    81,    82,    83,    85,    92,    93,    94,   100,
     118,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     139,   140,   141,   142,   143,   144,    88,    89,   126,   129,
     129,   129,   129,   129,     4,     7,     7,     7,    99,   129,
      48,    48,    52,   149,   149,    46,   147,   129,     0,     7,
      13,    14,    15,    16,    17,    19,    20,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    45,   149,
     132,   127,   128,    49,    32,    48,     8,    46,    95,   149,
     129,   129,    47,   131,    84,   145,   146,   149,    32,    52,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,     9,
      90,   129,    49,   124,   128,     7,    61,    62,    63,    75,
      96,    97,    98,   106,   107,   108,    49,    49,    47,    48,
     146,   129,   128,   149,    74,     9,    49,     7,     7,   101,
     101,     7,    99,    96,    47,   147,    52,   147,   148,   128,
     149,   128,   128,    74,    26,   102,    11,    46,    11,    46,
      46,    95,    78,    79,   137,   138,     7,   148,     7,   128,
       7,    70,    71,   103,   104,   127,    64,    65,    66,   109,
     110,   111,   122,   127,   109,     7,   123,    48,   147,    79,
     138,    49,   148,    48,   105,     7,     7,     9,    24,    46,
      47,   111,    11,    46,    47,     9,    47,   129,   147,   147,
     127,   105,   105,   104,   109,    67,    68,    72,   112,   113,
     114,   119,   120,   121,   109,     7,    47,    49,    49,    47,
      68,    67,    69,   113,    73,   128,    47,   147,    48,     7,
       7,    49,   124,   102,    52,    11,   115,   117,    49,    48,
      55,    56,   116,   148,   117,    49,   124,    48,   148,    74,
      49,    49,   125,   129,   128,    74,     9,    49,   148,   128,
     129,   148
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
        case 3:
#line 128 "signal.y"
    {
(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 4:
#line 135 "signal.y"
    {
ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 5:
#line 139 "signal.y"
    {
ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 6:
#line 143 "signal.y"
    {
ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 7:
#line 147 "signal.y"
    {
ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 8:
#line 154 "signal.y"
    {
(yyval.ast_value) = ast_new_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 9:
#line 161 "signal.y"
    {
(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value)
	;}
    break;

  case 10:
#line 168 "signal.y"
    {
(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 14:
#line 178 "signal.y"
    {
(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 15:
#line 182 "signal.y"
    {
(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 16:
#line 189 "signal.y"
    {
(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 18:
#line 197 "signal.y"
    {
(yyval.ast_value) = ast_new_namespace_path((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 19:
#line 201 "signal.y"
    {
(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 20:
#line 208 "signal.y"
    {
(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 21:
#line 215 "signal.y"
    {
(yyval.ast_value) = ast_new_parameterized_typename((yyvsp[(1) - (2)].string_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 22:
#line 222 "signal.y"
    {
(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 23:
#line 226 "signal.y"
    {
(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 24:
#line 233 "signal.y"
    {
(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 25:
#line 237 "signal.y"
    {
(yyval.ast_value) = ast_new_type_parameter_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 26:
#line 244 "signal.y"
    {
(yyval.ast_value) = ast_new_type_parameter((yyvsp[(1) - (2)].string_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 27:
#line 248 "signal.y"
    {
(yyval.ast_value) = ast_new_type_in_parameter((yyvsp[(2) - (3)].string_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 28:
#line 252 "signal.y"
    {
(yyval.ast_value) = ast_new_type_out_parameter((yyvsp[(2) - (3)].string_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 29:
#line 259 "signal.y"
    {
(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 30:
#line 263 "signal.y"
    {
(yyval.ast_value) = ast_new_type_parameter_rule_list((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 31:
#line 270 "signal.y"
    {
(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 32:
#line 274 "signal.y"
    {
(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 33:
#line 281 "signal.y"
    {
(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 34:
#line 285 "signal.y"
    {
(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (6)].string_value), (yyvsp[(4) - (6)].ast_value));
	;}
    break;

  case 35:
#line 292 "signal.y"
    {
(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 36:
#line 296 "signal.y"
    {
(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 37:
#line 303 "signal.y"
    {
(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 40:
#line 312 "signal.y"
    {
(yyval.ast_value) = ast_new_access_member_tree((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 41:
#line 319 "signal.y"
    {
(yyval.ast_value) = ast_new_access_member_list((yyvsp[(1) - (3)].access_level_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 42:
#line 326 "signal.y"
    {
(yyval.ast_value) = ast_new_member_decl((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 43:
#line 330 "signal.y"
    {
(yyval.ast_value) = ast_new_member_decl_list((yyvsp[(1) - (2)].ast_value), ast_new_member_decl((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 47:
#line 343 "signal.y"
    {
(yyval.ast_value) = ast_new_constructor_decl((yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 48:
#line 347 "signal.y"
    {
(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 49:
#line 354 "signal.y"
    {
(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (5)].chain_type_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 50:
#line 358 "signal.y"
    {
(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (4)].chain_type_value), ast_new_blank());
	;}
    break;

  case 51:
#line 365 "signal.y"
    {
(yyval.chain_type_value) = chain_type_super;
	;}
    break;

  case 52:
#line 369 "signal.y"
    {
(yyval.chain_type_value) = chain_type_this;
	;}
    break;

  case 53:
#line 376 "signal.y"
    {
(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 55:
#line 384 "signal.y"
    {
(yyval.ast_value) = ast_new_function_decl((yyvsp[(2) - (8)].string_value), (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 56:
#line 388 "signal.y"
    {
(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[(2) - (7)].string_value), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 57:
#line 395 "signal.y"
    {
(yyval.ast_value) = ast_new_method_decl((yyvsp[(1) - (10)].modifier_type_value), (yyvsp[(3) - (10)].string_value), (yyvsp[(4) - (10)].ast_value), (yyvsp[(6) - (10)].ast_value), (yyvsp[(10) - (10)].ast_value), (yyvsp[(9) - (10)].ast_value));
	;}
    break;

  case 58:
#line 399 "signal.y"
    {
(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[(1) - (9)].modifier_type_value), (yyvsp[(3) - (9)].string_value), (yyvsp[(4) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 59:
#line 406 "signal.y"
    {
(yyval.ast_value) = ast_new_field_decl((yyvsp[(1) - (4)].modifier_type_value), (yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].string_value));
	;}
    break;

  case 60:
#line 413 "signal.y"
    {
(yyval.modifier_type_value) = modifier_none;
	;}
    break;

  case 61:
#line 417 "signal.y"
    {
(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 62:
#line 421 "signal.y"
    {
(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 63:
#line 425 "signal.y"
    {
(yyval.modifier_type_value) = modifier_static;
	;}
    break;

  case 64:
#line 429 "signal.y"
    {
(yyval.modifier_type_value) = modifier_native;
	;}
    break;

  case 65:
#line 436 "signal.y"
    {
(yyval.access_level_value) = access_public;
	;}
    break;

  case 66:
#line 440 "signal.y"
    {
(yyval.access_level_value) = access_private;
	;}
    break;

  case 67:
#line 444 "signal.y"
    {
(yyval.access_level_value) = access_protected;
	;}
    break;

  case 68:
#line 451 "signal.y"
    {
(yyval.ast_value) = ast_new_identifier((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 69:
#line 455 "signal.y"
    {
(yyval.ast_value) = ast_new_identifier_list((yyvsp[(3) - (3)].string_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 70:
#line 462 "signal.y"
    {
(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].string_value));
	;}
    break;

  case 71:
#line 466 "signal.y"
    {
(yyval.ast_value) = ast_new_parameter_list((yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].string_value), (yyvsp[(1) - (4)].ast_value))
	;}
    break;

  case 72:
#line 473 "signal.y"
    {
(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 73:
#line 477 "signal.y"
    {
(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(3) - (3)].ast_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 74:
#line 484 "signal.y"
    {
(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 75:
#line 488 "signal.y"
    {
(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 76:
#line 495 "signal.y"
    {
(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 77:
#line 499 "signal.y"
    {
(yyval.ast_value) = ast_new_typename_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 78:
#line 506 "signal.y"
    {
(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 80:
#line 517 "signal.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_pos, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 81:
#line 521 "signal.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_neg, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 82:
#line 525 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 83:
#line 529 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 84:
#line 533 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 85:
#line 537 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 86:
#line 541 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 87:
#line 545 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 88:
#line 549 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_equal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 89:
#line 553 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_notequal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 90:
#line 557 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 91:
#line 561 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 92:
#line 565 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 93:
#line 569 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 94:
#line 573 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 95:
#line 577 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 96:
#line 581 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 97:
#line 585 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 98:
#line 589 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 99:
#line 593 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 100:
#line 597 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_and_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 101:
#line 601 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 102:
#line 605 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 103:
#line 609 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 104:
#line 613 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 105:
#line 617 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_gt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 106:
#line 621 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_ge, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 107:
#line 625 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 108:
#line 629 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_le, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 109:
#line 632 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 110:
#line 635 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 111:
#line 639 "signal.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_childa, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 112:
#line 643 "signal.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_not, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 113:
#line 647 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 118:
#line 657 "signal.y"
    {
		(yyval.ast_value) = ast_new_true();
	;}
    break;

  case 119:
#line 661 "signal.y"
    {
		(yyval.ast_value) = ast_new_false();
	;}
    break;

  case 120:
#line 665 "signal.y"
    {
		(yyval.ast_value) = ast_new_null();
	;}
    break;

  case 121:
#line 674 "signal.y"
    {
(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 122:
#line 678 "signal.y"
    {
(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 123:
#line 684 "signal.y"
    {
(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 134:
#line 700 "signal.y"
    {
(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].string_value));
	;}
    break;

  case 135:
#line 706 "signal.y"
    {
(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 136:
#line 712 "signal.y"
    {
(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 137:
#line 718 "signal.y"
    {
(yyval.ast_value) = ast_new_if((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 138:
#line 722 "signal.y"
    {
(yyval.ast_value) = ast_new_if_else((yyvsp[(3) - (7)].ast_value), (yyvsp[(5) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 139:
#line 726 "signal.y"
    {
(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 140:
#line 730 "signal.y"
    {
(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(3) - (8)].ast_value), (yyvsp[(5) - (8)].ast_value), (yyvsp[(6) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value));
	;}
    break;

  case 142:
#line 737 "signal.y"
    {
(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 143:
#line 743 "signal.y"
    {
(yyval.ast_value) = ast_new_elif((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 144:
#line 749 "signal.y"
    {
(yyval.ast_value) = ast_new_while((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 145:
#line 755 "signal.y"
    {
(yyval.ast_value) = ast_new_break();
	;}
    break;

  case 146:
#line 761 "signal.y"
    {
(yyval.ast_value) = ast_new_continue();
	;}
    break;

  case 147:
#line 767 "signal.y"
    {
(yyval.ast_value) = ast_new_return((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 148:
#line 773 "signal.y"
    {
(yyval.ast_value) = ast_new_throw((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 149:
#line 779 "signal.y"
    {
(yyval.ast_value) = ast_new_try((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 150:
#line 785 "signal.y"
    {
(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 151:
#line 789 "signal.y"
    {
(yyval.ast_value) = ast_new_catch_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 152:
#line 795 "signal.y"
    {
(yyval.ast_value) = ast_new_catch((yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].string_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 153:
#line 806 "signal.y"
    {
(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 154:
#line 810 "signal.y"
    {
(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 155:
#line 816 "signal.y"
    {
(yyval.ast_value) = ast_new_blank();
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 2861 "signal.tab.c"
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


#line 825 "signal.y"





