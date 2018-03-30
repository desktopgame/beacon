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
#line 309 "signal.tab.c"
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
#line 334 "signal.tab.c"

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
#define YYFINAL  75
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1169

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNRULES -- Number of states.  */
#define YYNSTATES  338

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   349

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      96,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      90,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      85,    86,    87,    88,    89,    91,    92,    93,    94,    95
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
     274,   278,   282,   284,   286,   289,   292,   296,   300,   304,
     308,   312,   316,   320,   324,   328,   332,   336,   340,   344,
     348,   352,   356,   360,   364,   368,   372,   376,   380,   384,
     388,   392,   396,   400,   404,   408,   413,   417,   420,   423,
     428,   432,   438,   443,   445,   447,   449,   451,   453,   455,
     457,   460,   462,   464,   466,   469,   472,   474,   476,   478,
     480,   482,   484,   486,   488,   490,   492,   496,   502,   508,
     514,   522,   529,   538,   540,   543,   549,   555,   558,   561,
     565,   569,   573,   575,   578,   585,   589,   592,   594,   596,
     598
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      98,     0,    -1,    99,    -1,     1,    96,    -1,   139,    -1,
     106,    -1,   100,    -1,   124,    -1,    75,   105,   101,    -1,
      46,   104,    47,    -1,    75,   105,   101,    -1,   112,    -1,
     114,    -1,   113,    -1,   102,    -1,   103,   102,    -1,    -1,
     103,    -1,     7,    -1,   105,     8,     7,    -1,    53,     4,
      -1,     7,   108,    -1,    -1,    26,   109,    24,    -1,   110,
      -1,   109,     9,   110,    -1,     7,   111,    -1,    70,     7,
     111,    -1,    71,     7,   111,    -1,    -1,    48,   133,    49,
      -1,    62,   107,    46,   115,    47,    -1,    62,   107,    10,
     133,    46,   115,    47,    -1,    63,     7,    46,   129,    47,
      -1,    63,     7,    46,   129,     9,    47,    -1,    61,   107,
      46,   115,    47,    -1,    61,   107,    10,   133,    46,   115,
      47,    -1,    -1,   116,    -1,   117,    -1,   116,   117,    -1,
     128,    10,   118,    -1,   119,    -1,   118,   119,    -1,   120,
      -1,   125,    -1,   126,    -1,    72,    69,    48,   130,    49,
     123,   156,    -1,    72,    69,    48,    49,   123,   156,    -1,
      10,   122,    48,   131,    49,    -1,    10,   122,    48,    49,
      -1,    56,    -1,    55,    -1,    -1,   121,    -1,    73,     7,
      48,   130,    49,    74,   134,   156,    -1,    73,     7,    48,
      49,    74,   134,   156,    -1,   127,    73,     7,   108,    48,
     130,    49,    74,   134,   156,    -1,   127,    73,     7,   108,
      48,    49,    74,   134,   156,    -1,   127,   134,     7,    52,
      -1,    -1,    67,    68,    -1,    68,    67,    -1,    67,    -1,
      68,    -1,    64,    -1,    65,    -1,    66,    -1,     7,    -1,
     129,     9,     7,    -1,   134,     7,    -1,   130,     9,   134,
       7,    -1,   136,    -1,   131,     9,   136,    -1,    -1,    26,
     133,    24,    -1,   134,    -1,   133,     9,   134,    -1,   135,
     132,    -1,     7,    -1,   135,    11,     7,    -1,    48,   136,
      49,    -1,   137,    -1,   138,    -1,    13,   136,    -1,    14,
     136,    -1,   136,    13,   136,    -1,   136,    14,   136,    -1,
     136,    15,   136,    -1,   136,    16,   136,    -1,   136,    17,
     136,    -1,   136,    30,   136,    -1,   136,    22,   136,    -1,
     136,    23,   136,    -1,   136,    28,   136,    -1,   136,    45,
     136,    -1,   136,    31,   136,    -1,   136,    29,   136,    -1,
     136,    32,   136,    -1,   136,    33,   136,    -1,   136,    34,
     136,    -1,   136,    35,   136,    -1,   136,    36,   136,    -1,
     136,    37,   136,    -1,   136,    38,   136,    -1,   136,    39,
     136,    -1,   136,    42,   136,    -1,   136,    40,   136,    -1,
     136,    41,   136,    -1,   136,    24,   136,    -1,   136,    25,
     136,    -1,   136,    26,   136,    -1,   136,    27,   136,    -1,
     136,    19,   136,    -1,   136,    20,   136,    -1,   136,     8,
       7,   132,    -1,   136,    60,   134,    -1,    21,   136,    -1,
      18,   136,    -1,   137,    48,   131,    49,    -1,   137,    48,
      49,    -1,    69,   134,    48,   131,    49,    -1,    69,   134,
      48,    49,    -1,     5,    -1,     6,    -1,     3,    -1,     4,
      -1,    57,    -1,    58,    -1,    59,    -1,   135,   132,    -1,
      55,    -1,    56,    -1,   140,    -1,   139,   140,    -1,   136,
     157,    -1,   141,    -1,   142,    -1,   143,    -1,   144,    -1,
     147,    -1,   148,    -1,   149,    -1,   150,    -1,   151,    -1,
     152,    -1,   134,     7,    52,    -1,   134,     7,    32,   136,
     157,    -1,    54,     7,    32,   136,   157,    -1,    77,    48,
     136,    49,   155,    -1,    77,    48,   136,    49,   155,    79,
     155,    -1,    77,    48,   136,    49,   155,   145,    -1,    77,
      48,   136,    49,   155,   145,    79,   155,    -1,   146,    -1,
     145,   146,    -1,    78,    48,   136,    49,   155,    -1,    80,
      48,   136,    49,   156,    -1,    81,   157,    -1,    82,   157,
      -1,    76,   136,   157,    -1,    85,   136,   157,    -1,    83,
     155,   153,    -1,   154,    -1,   153,   154,    -1,    84,    48,
     134,     7,    49,   155,    -1,    46,   139,    47,    -1,    46,
      47,    -1,    52,    -1,   155,    -1,    52,    -1,    96,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   135,   135,   136,   143,   147,   151,   155,   162,   169,
     176,   180,   181,   182,   186,   190,   198,   201,   205,   209,
     216,   223,   231,   234,   241,   245,   252,   256,   260,   268,
     271,   278,   282,   289,   293,   300,   304,   312,   315,   319,
     320,   327,   334,   338,   345,   346,   347,   351,   355,   362,
     366,   373,   377,   385,   388,   392,   396,   403,   407,   414,
     422,   425,   429,   433,   437,   444,   448,   452,   459,   463,
     470,   474,   481,   485,   493,   496,   503,   507,   514,   521,
     525,   534,   538,   541,   542,   546,   550,   554,   558,   562,
     566,   570,   574,   578,   582,   586,   590,   594,   598,   602,
     606,   610,   614,   618,   622,   626,   630,   634,   638,   642,
     646,   650,   654,   658,   662,   666,   670,   674,   678,   682,
     686,   690,   694,   700,   701,   702,   703,   704,   708,   712,
     716,   720,   724,   733,   737,   743,   747,   748,   749,   750,
     751,   752,   753,   754,   755,   756,   759,   765,   771,   777,
     781,   785,   789,   795,   796,   802,   808,   814,   820,   826,
     832,   838,   844,   848,   854,   863,   867,   873,   877,   880,
     881
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
  "NOTEQUAL", "GT", "GE", "LT", "LE", "BIT_AND", "LOGIC_AND", "BIT_OR",
  "LOGIC_OR", "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "AND_ASSIGN", "OR_ASSIGN", "LSHIFT_ASSIGN",
  "RSHIFT_ASSIGN", "EXC_OR_ASSIGN", "INC", "DEC", "EXC_OR", "LCB", "RCB",
  "LRB", "RRB", "LSB", "RSB", "SEMI", "IMPORT", "VAR", "THIS", "SUPER",
  "TRUE_TOK", "FALSE_TOK", "NULL_TOK", "AS", "INTERFACE", "CLASS", "ENUM",
  "PUBLIC", "PRIVATE", "PROTECTED", "STATIC", "NATIVE", "NEW", "IN", "OUT",
  "CTOR", "DEF", "ARROW", "NAMESPACE", "RETURN", "IF", "ELIF", "ELSE",
  "WHILE", "BREAK", "CONTINUE", "TRY", "CATCH", "THROW", "QUOTE",
  "POST_DEC", "POST_INC", "FUNCCALL", "'<'", "POSITIVE", "NEGATIVE",
  "PRE_DEC", "PRE_INC", "FORM_TYPE", "'\\n'", "$accept",
  "compilation_unit", "program", "namespace_decl", "namespace_body",
  "namespace_member_decl", "namespace_member_decl_list",
  "namespace_member_decl_optional", "namespace_path", "import",
  "parameterized_typename", "type_parameter_group", "type_parameter_list",
  "type_parameter", "type_parameter_rule_list", "class_decl", "enum_decl",
  "interface_decl", "access_member_tree_opt", "access_member_tree",
  "access_member_list", "member_define_list", "member_define",
  "constructor_define", "constructor_chain", "constructor_chain_type_T",
  "constructor_chain_optional", "function_define", "method_define",
  "field_define", "modifier_type_T", "access_level_T", "ident_list",
  "parameter_list", "argument_list", "typename_group", "typename_list",
  "typename_T", "fqcn_part", "expression", "expression_nobrace", "primary",
  "stmt_list", "stmt", "variable_decl_stmt", "variable_init_stmt",
  "inferenced_type_init_stmt", "if_stmt", "elif_list", "elif",
  "while_stmt", "break_stmt", "continue_stmt", "return_stmt", "throw_stmt",
  "try_stmt", "catch_stmt_list", "catch_stmt", "scope", "scope_optional",
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
      60,   345,   346,   347,   348,   349,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    98,    99,    99,    99,    99,   100,   101,
     102,   102,   102,   102,   103,   103,   104,   104,   105,   105,
     106,   107,   108,   108,   109,   109,   110,   110,   110,   111,
     111,   112,   112,   113,   113,   114,   114,   115,   115,   116,
     116,   117,   118,   118,   119,   119,   119,   120,   120,   121,
     121,   122,   122,   123,   123,   124,   124,   125,   125,   126,
     127,   127,   127,   127,   127,   128,   128,   128,   129,   129,
     130,   130,   131,   131,   132,   132,   133,   133,   134,   135,
     135,   136,   136,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   139,   139,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   141,   142,   143,   144,
     144,   144,   144,   145,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   153,   154,   155,   155,   156,   156,   157,
     157
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
       3,     3,     1,     1,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     3,     2,     2,     4,
       3,     5,     4,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     5,     5,     5,
       7,     6,     8,     1,     2,     5,     5,     2,     2,     3,
       3,     3,     1,     2,     6,     3,     2,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,   125,   126,   123,   124,    79,     0,     0,     0,
       0,     0,     0,     0,   131,   132,   127,   128,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     6,     5,     7,     0,    74,     0,    82,    83,     4,
     133,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,     3,    74,    84,    85,   118,   117,     0,    20,     0,
       0,    74,     0,    18,     0,     0,     0,     0,   169,   170,
     157,   158,     0,     0,     0,     1,     0,     0,     0,   130,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   135,     0,   134,   130,    81,     0,     0,    78,     0,
       0,    16,     8,   159,     0,     0,   166,     0,     0,   161,
     162,   160,     0,   146,    80,     0,    76,    74,    86,    87,
      88,    89,    90,   113,   114,    92,    93,   109,   110,   111,
     112,    94,    97,    91,    96,    98,    99,   100,   101,   102,
     103,   104,   105,   107,   108,   106,    95,   116,   120,     0,
      72,     0,   122,     0,     0,     0,     0,    19,     0,     0,
       0,     0,    14,    17,     0,    11,    13,    12,     0,     0,
     165,     0,   163,     0,     0,    75,   115,     0,   119,   148,
     121,     0,     0,     0,    70,    22,     0,     0,     0,     0,
      15,     9,   149,   167,   168,   156,     0,   147,    77,    73,
       0,     0,     0,     0,    21,     0,    37,     0,    37,     0,
      10,     0,     0,   151,   153,     0,    56,    71,     0,    29,
       0,     0,     0,    24,     0,    65,    66,    67,     0,    38,
      39,     0,     0,     0,    68,     0,     0,   150,     0,   154,
       0,    55,     0,    26,    29,    29,     0,    23,    37,    35,
      40,    60,    37,    31,     0,    33,     0,   152,   164,     0,
      27,    28,    25,     0,    63,    64,     0,    41,    42,    44,
      45,    46,     0,     0,    69,    34,     0,    30,    36,    61,
      62,     0,    43,     0,     0,    32,   155,     0,    22,     0,
      53,     0,     0,    59,     0,    54,     0,    53,     0,    52,
      51,     0,    48,     0,     0,     0,     0,    47,     0,     0,
      50,     0,     0,     0,    49,    58,     0,    57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    29,    30,    31,   122,   182,   183,   184,    64,    32,
     206,   224,   242,   243,   263,   185,   186,   187,   248,   249,
     250,   287,   288,   289,   315,   321,   316,    33,   290,   291,
     292,   251,   255,   175,   169,    79,   135,    34,    52,    36,
      37,    38,    39,    40,    41,    42,    43,    44,   233,   234,
      45,    46,    47,    48,    49,    50,   129,   130,   214,   215,
      70
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -278
static const yytype_int16 yypact[] =
{
     162,   -74,  -278,  -278,  -278,  -278,  -278,   434,   434,   434,
     434,   434,    42,    43,  -278,  -278,  -278,  -278,  -278,    69,
     111,   116,   434,    99,   107,   -41,   -41,   125,   434,   153,
    -278,  -278,  -278,  -278,   154,    21,   360,   126,  -278,   517,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,    21,   393,   393,   393,   393,   657,  -278,   141,
     129,    21,   130,  -278,    18,   360,   434,   434,  -278,  -278,
    -278,  -278,   403,    95,   360,  -278,    -4,   174,    69,   175,
     177,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
      69,  -278,   281,  -278,  -278,  -278,   434,   574,  -278,     8,
     178,    75,  -278,  -278,   696,   735,  -278,   460,   138,    95,
    -278,  -278,   434,  -278,  -278,    25,  -278,   161,  1109,  1109,
     240,   240,   240,  1074,  1074,   851,   851,   886,   886,   886,
     886,   991,   921,  1026,   956,   514,   514,   514,   514,   514,
     514,   514,   514,   514,   514,   514,  1061,  -278,  -278,     5,
     813,   360,  -278,    14,   114,    22,   182,  -278,   183,   183,
     185,   116,  -278,    75,   146,  -278,  -278,  -278,   125,    76,
    -278,    69,  -278,   360,    69,  -278,  -278,   434,  -278,  -278,
    -278,    69,    69,   121,  -278,   171,    15,    33,   152,    18,
    -278,  -278,    66,  -278,  -278,  -278,   192,  -278,  -278,   813,
      76,   193,    69,    -2,  -278,    69,    77,    69,    77,   196,
    -278,   156,   125,    73,  -278,   158,  -278,  -278,    76,   157,
     201,   202,    35,  -278,     7,  -278,  -278,  -278,   165,    77,
    -278,   203,   100,   167,  -278,    20,   434,  -278,   125,  -278,
     125,  -278,    69,  -278,   157,   157,    -2,  -278,    77,  -278,
    -278,    58,    77,  -278,    26,  -278,   774,  -278,  -278,    28,
    -278,  -278,  -278,   176,   160,   159,   155,    67,  -278,  -278,
    -278,  -278,    -3,   189,  -278,  -278,   125,  -278,  -278,  -278,
    -278,   181,  -278,   239,   242,  -278,  -278,    11,   171,   198,
     241,   105,   204,  -278,   101,  -278,    76,   241,    13,  -278,
    -278,   205,  -278,    76,   180,   115,   600,  -278,    69,   184,
    -278,   123,    76,    69,  -278,  -278,    76,  -278
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -278,  -278,  -278,  -278,    47,    74,  -278,  -278,    78,  -278,
      81,   -45,  -278,     1,  -105,  -278,  -278,  -278,  -216,  -278,
      16,  -278,   -19,  -278,  -278,  -278,   -48,  -278,  -278,  -278,
    -278,  -278,  -278,  -277,  -115,   -16,  -187,    39,     0,    -1,
    -278,  -278,   199,   -15,  -278,  -278,  -278,  -278,  -278,    50,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,   164,   -26,  -203,
     -23
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -79
static const yytype_int16 yytable[] =
{
      35,    73,   173,    71,     6,   239,    53,    54,    55,    56,
      57,    68,   253,   111,   197,     6,   194,   236,     6,    61,
       6,    65,    51,   197,   113,   225,   120,    74,   132,   274,
     311,   202,    77,   294,   194,   261,   114,   194,   244,    35,
     252,   325,   123,   227,   266,   118,    58,    78,   133,   195,
      59,   131,   283,   268,   198,    69,   293,   174,    60,   267,
     310,   226,   324,   200,   121,   124,   125,   275,   240,   241,
     303,   203,    35,   295,   -60,   279,     6,   297,    61,   228,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   194,
      61,   170,   113,   322,   202,   171,   170,   136,    62,    61,
     327,   196,    72,    63,   202,   284,   285,    35,   213,   335,
     286,   193,   197,   337,   284,   285,   178,   179,   180,   286,
     -60,   245,   246,   247,   231,   232,   272,    66,   199,   167,
     181,   231,   258,    75,   317,    67,   319,   320,   176,   280,
     281,    76,   212,     1,   329,     2,     3,     4,     5,     6,
     217,    72,   334,   116,   112,     7,     8,   117,   119,   128,
       9,   134,   -78,    10,   137,   177,   191,    78,   201,   204,
     205,    61,   208,   211,    61,   222,   219,   223,   229,   235,
     237,    61,    61,   254,   256,   262,   257,   260,   264,   265,
      11,   331,   269,   271,   273,    12,    13,    14,    15,    16,
      17,    18,    61,   298,   301,    61,   300,    61,   299,   307,
     216,    19,   277,   218,   278,    20,   305,    21,    22,    23,
     220,   221,    24,    25,    26,    27,   308,    28,    80,   309,
     313,   314,   318,   326,   328,   276,   230,   210,   333,   209,
     207,   238,    61,   312,   136,   270,   136,   282,   302,   323,
     306,   127,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   259,     2,     3,     4,     5,     6,     0,
       0,     0,    61,   192,     7,     8,     0,     0,     0,     9,
     110,   136,    10,     0,     0,     0,     0,    61,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,     0,
       0,     0,     0,     0,     0,   170,     0,     0,    61,    11,
     168,   304,     0,    61,     0,     0,    14,    15,    16,    17,
      18,     0,     0,     0,     0,     0,   176,     0,     0,     0,
      19,     0,     0,     0,     0,     0,     0,   176,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   332,    80,     0,
       0,     0,   336,    81,    82,    83,    84,    85,     0,    86,
      87,     0,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,     0,     0,   109,     2,     3,     4,     5,
       6,     0,    68,     0,     0,     0,     7,     8,     0,     0,
     110,     9,     0,     0,    10,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,     0,     2,     3,     4,
       5,     6,     0,     0,     0,     0,     0,     7,     8,     0,
     126,    11,     9,   110,     0,    10,    69,    13,    14,    15,
      16,    17,    18,     2,     3,     4,     5,     6,     0,     0,
       0,     0,    19,     7,     8,     0,     0,     0,     9,    22,
      23,    10,    11,    24,    25,    26,    27,     0,    28,    14,
      15,    16,    17,    18,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,     0,   190,    11,     0,
       0,     0,     0,     0,    13,    14,    15,    16,    17,    18,
       2,     3,     4,     5,     6,     0,     0,     0,     0,    19,
       7,     8,     0,     0,     0,     9,    22,    23,    10,     0,
      24,    25,    26,    27,     0,    28,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,     0,     0,     0,
       0,     0,     0,     0,     0,    11,     0,     0,     0,     0,
       0,    13,    14,    15,    16,    17,    18,     2,     3,     4,
       5,     6,     0,     0,     0,     0,    19,     7,     8,     0,
       0,     0,     9,    22,    23,    10,     0,    24,    25,    26,
      27,     0,    28,     2,     3,     4,     5,     6,     0,     0,
       0,     0,     0,     7,     8,     0,     0,     0,     9,     0,
       0,    10,    11,   172,     0,     0,     0,     0,     0,    14,
      15,    16,    17,    18,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,     0,     0,    11,   330,
       0,     0,     0,     0,     0,    14,    15,    16,    17,    18,
       0,     0,     0,     0,     0,    80,     0,     0,     0,    19,
      81,    82,    83,    84,    85,     0,    86,    87,     0,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
       0,     0,   109,     0,    80,     0,   115,     0,     0,    81,
      82,    83,    84,    85,     0,    86,    87,   110,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,     0,
       0,   109,     0,    80,     0,   188,     0,     0,    81,    82,
      83,    84,    85,     0,    86,    87,   110,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,     0,     0,
     109,     0,    80,     0,   189,     0,     0,    81,    82,    83,
      84,    85,     0,    86,    87,   110,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,     0,     0,   109,
       0,    80,     0,   296,     0,     0,    81,    82,    83,    84,
      85,     0,    86,    87,   110,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,     0,     0,   109,    80,
       0,     0,     0,     0,    81,    82,    83,    84,    85,     0,
      86,    87,     0,   110,     0,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,    80,     0,   109,     0,     0,    81,
      82,    83,    84,    85,     0,    86,    87,     0,     0,     0,
       0,   110,     0,     0,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,    80,
       0,   109,     0,     0,    81,    82,    83,    84,    85,     0,
      86,    87,     0,     0,     0,     0,   110,     0,     0,    94,
       0,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,    80,     0,   109,     0,     0,    81,
      82,    83,    84,    85,     0,    86,    87,     0,     0,     0,
       0,   110,     0,     0,    94,     0,    96,     0,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,    80,
       0,   109,     0,     0,    81,    82,    83,    84,    85,     0,
      86,    87,     0,     0,     0,     0,   110,     0,     0,     0,
       0,    96,     0,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,    80,     0,   109,     0,     0,    81,
      82,    83,    84,    85,     0,    86,    87,     0,     0,     0,
       0,   110,     0,     0,     0,     0,     0,     0,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,    80,
       0,   109,     0,     0,    81,    82,    83,    84,    85,     0,
      86,    87,    80,     0,     0,     0,   110,    81,    82,    83,
      84,    85,     0,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,     0,     0,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,    80,     0,     0,
       0,   110,     0,     0,    83,    84,    85,     0,     0,     0,
       0,     0,     0,     0,   110,     0,     0,     0,     0,     0,
       0,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110
};

static const yytype_int16 yycheck[] =
{
       0,    27,   117,    26,     7,     7,     7,     8,     9,    10,
      11,    52,   228,    36,     9,     7,     9,   220,     7,    19,
       7,    22,    96,     9,    39,    10,     8,    28,    32,     9,
     307,     9,    11,     7,     9,   238,    52,     9,   225,    39,
     227,   318,    65,    10,     9,    61,     4,    26,    52,    24,
       7,    74,   268,    46,    49,    96,   272,    49,    19,    24,
      49,    46,    49,    49,    46,    66,    67,    47,    70,    71,
      73,    49,    72,    47,     7,   262,     7,    49,    78,    46,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,     9,
     110,   112,   127,   316,     9,   116,   117,    78,     7,   119,
     323,   137,    46,     7,     9,    67,    68,   127,    52,   332,
      72,   132,     9,   336,    67,    68,    61,    62,    63,    72,
      73,    64,    65,    66,    78,    79,    46,    48,   171,   110,
      75,    78,    79,     0,    49,    48,    55,    56,   119,   264,
     265,     7,   188,     1,    49,     3,     4,     5,     6,     7,
     193,    46,    49,    32,    48,    13,    14,    48,    48,    84,
      18,     7,     7,    21,     7,     7,    48,    26,    74,     7,
       7,   191,     7,    47,   194,    74,   197,    26,    46,     7,
       7,   201,   202,     7,    48,    48,   232,    49,     7,     7,
      48,   326,    47,    10,    47,    53,    54,    55,    56,    57,
      58,    59,   222,    47,    69,   225,    67,   227,    68,    48,
     191,    69,   258,   194,   260,    73,    47,    75,    76,    77,
     201,   202,    80,    81,    82,    83,     7,    85,     8,     7,
      52,    10,    48,    48,    74,   256,   209,   183,    74,   181,
     179,   222,   262,   308,   225,   249,   227,   266,   287,   317,
     296,    72,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,   233,     3,     4,     5,     6,     7,    -1,
      -1,    -1,   292,   129,    13,    14,    -1,    -1,    -1,    18,
      60,   262,    21,    -1,    -1,    -1,    -1,   307,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   318,    -1,
      -1,    -1,    -1,    -1,    -1,   326,    -1,    -1,   328,    48,
      49,   292,    -1,   333,    -1,    -1,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,   307,    -1,    -1,    -1,
      69,    -1,    -1,    -1,    -1,    -1,    -1,   318,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   328,     8,    -1,
      -1,    -1,   333,    13,    14,    15,    16,    17,    -1,    19,
      20,    -1,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    -1,    45,     3,     4,     5,     6,
       7,    -1,    52,    -1,    -1,    -1,    13,    14,    -1,    -1,
      60,    18,    -1,    -1,    21,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,    -1,
      47,    48,    18,    60,    -1,    21,    96,    54,    55,    56,
      57,    58,    59,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    69,    13,    14,    -1,    -1,    -1,    18,    76,
      77,    21,    48,    80,    81,    82,    83,    -1,    85,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    69,
      13,    14,    -1,    -1,    -1,    18,    76,    77,    21,    -1,
      80,    81,    82,    83,    -1,    85,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    69,    13,    14,    -1,
      -1,    -1,    18,    76,    77,    21,    -1,    80,    81,    82,
      83,    -1,    85,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    13,    14,    -1,    -1,    -1,    18,    -1,
      -1,    21,    48,    49,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    48,    49,
      -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,    69,
      13,    14,    15,    16,    17,    -1,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    -1,    45,    -1,     8,    -1,    49,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    60,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      -1,    45,    -1,     8,    -1,    49,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    60,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    -1,
      45,    -1,     8,    -1,    49,    -1,    -1,    13,    14,    15,
      16,    17,    -1,    19,    20,    60,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    -1,    45,
      -1,     8,    -1,    49,    -1,    -1,    13,    14,    15,    16,
      17,    -1,    19,    20,    60,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    -1,    45,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    -1,    60,    -1,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,     8,    -1,    45,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    -1,    -1,
      -1,    60,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,     8,
      -1,    45,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    -1,    -1,    -1,    -1,    60,    -1,    -1,    28,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,     8,    -1,    45,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    -1,    -1,
      -1,    60,    -1,    -1,    28,    -1,    30,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,     8,
      -1,    45,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,     8,    -1,    45,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,     8,
      -1,    45,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,     8,    -1,    -1,    -1,    60,    13,    14,    15,
      16,    17,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,     8,    -1,    -1,
      -1,    60,    -1,    -1,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,    13,    14,    18,
      21,    48,    53,    54,    55,    56,    57,    58,    59,    69,
      73,    75,    76,    77,    80,    81,    82,    83,    85,    98,
      99,   100,   106,   124,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   147,   148,   149,   150,   151,
     152,    96,   135,   136,   136,   136,   136,   136,     4,     7,
     134,   135,     7,     7,   105,   136,    48,    48,    52,    96,
     157,   157,    46,   155,   136,     0,     7,    11,    26,   132,
       8,    13,    14,    15,    16,    17,    19,    20,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    45,
      60,   157,    48,   140,   132,    49,    32,    48,   132,    48,
       8,    46,   101,   157,   136,   136,    47,   139,    84,   153,
     154,   157,    32,    52,     7,   133,   134,     7,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   134,    49,   131,
     136,   136,    49,   131,    49,   130,   134,     7,    61,    62,
      63,    75,   102,   103,   104,   112,   113,   114,    49,    49,
      47,    48,   154,   136,     9,    24,   132,     9,    49,   157,
      49,    74,     9,    49,     7,     7,   107,   107,     7,   105,
     102,    47,   155,    52,   155,   156,   134,   157,   134,   136,
     134,   134,    74,    26,   108,    10,    46,    10,    46,    46,
     101,    78,    79,   145,   146,     7,   156,     7,   134,     7,
      70,    71,   109,   110,   133,    64,    65,    66,   115,   116,
     117,   128,   133,   115,     7,   129,    48,   155,    79,   146,
      49,   156,    48,   111,     7,     7,     9,    24,    46,    47,
     117,    10,    46,    47,     9,    47,   136,   155,   155,   133,
     111,   111,   110,   115,    67,    68,    72,   118,   119,   120,
     125,   126,   127,   115,     7,    47,    49,    49,    47,    68,
      67,    69,   119,    73,   134,    47,   155,    48,     7,     7,
      49,   130,   108,    52,    10,   121,   123,    49,    48,    55,
      56,   122,   156,   123,    49,   130,    48,   156,    74,    49,
      49,   131,   134,    74,    49,   156,   134,   156
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
#line 137 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 4:
#line 144 "signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 5:
#line 148 "signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 6:
#line 152 "signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 7:
#line 156 "signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 8:
#line 163 "signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 9:
#line 170 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value)
	;}
    break;

  case 10:
#line 177 "signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 14:
#line 187 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 15:
#line 191 "signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 16:
#line 198 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 18:
#line 206 "signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 19:
#line 210 "signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 20:
#line 217 "signal.y"
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 21:
#line 224 "signal.y"
    {
		(yyval.ast_value) = ast_new_parameterized_typename((yyvsp[(1) - (2)].string_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 22:
#line 231 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 23:
#line 235 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 24:
#line 242 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 25:
#line 246 "signal.y"
    {
		(yyval.ast_value) = ast_new_type_parameter_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 26:
#line 253 "signal.y"
    {
		(yyval.ast_value) = ast_new_type_parameter((yyvsp[(1) - (2)].string_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 27:
#line 257 "signal.y"
    {
		(yyval.ast_value) = ast_new_type_in_parameter((yyvsp[(2) - (3)].string_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 28:
#line 261 "signal.y"
    {
		(yyval.ast_value) = ast_new_type_out_parameter((yyvsp[(2) - (3)].string_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 29:
#line 268 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 30:
#line 272 "signal.y"
    {
		(yyval.ast_value) = ast_new_type_parameter_rule_list((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 31:
#line 279 "signal.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 32:
#line 283 "signal.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 33:
#line 290 "signal.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 34:
#line 294 "signal.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (6)].string_value), (yyvsp[(4) - (6)].ast_value));
	;}
    break;

  case 35:
#line 301 "signal.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 36:
#line 305 "signal.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 37:
#line 312 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 40:
#line 321 "signal.y"
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 41:
#line 328 "signal.y"
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[(1) - (3)].access_level_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 42:
#line 335 "signal.y"
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 43:
#line 339 "signal.y"
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[(1) - (2)].ast_value), ast_new_member_decl((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 47:
#line 352 "signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 48:
#line 356 "signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 49:
#line 363 "signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (5)].chain_type_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 50:
#line 367 "signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (4)].chain_type_value), ast_new_blank());
	;}
    break;

  case 51:
#line 374 "signal.y"
    {
		(yyval.chain_type_value) = chain_type_super;
	;}
    break;

  case 52:
#line 378 "signal.y"
    {
		(yyval.chain_type_value) = chain_type_this;
	;}
    break;

  case 53:
#line 385 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 55:
#line 393 "signal.y"
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[(2) - (8)].string_value), (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 56:
#line 397 "signal.y"
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[(2) - (7)].string_value), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 57:
#line 404 "signal.y"
    {
		(yyval.ast_value) = ast_new_method_decl((yyvsp[(1) - (10)].modifier_type_value), (yyvsp[(3) - (10)].string_value), (yyvsp[(4) - (10)].ast_value), (yyvsp[(6) - (10)].ast_value), (yyvsp[(10) - (10)].ast_value), (yyvsp[(9) - (10)].ast_value));
	;}
    break;

  case 58:
#line 408 "signal.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[(1) - (9)].modifier_type_value), (yyvsp[(3) - (9)].string_value), (yyvsp[(4) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 59:
#line 415 "signal.y"
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[(1) - (4)].modifier_type_value), (yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].string_value));
	;}
    break;

  case 60:
#line 422 "signal.y"
    {
		(yyval.modifier_type_value) = modifier_none;
	;}
    break;

  case 61:
#line 426 "signal.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 62:
#line 430 "signal.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 63:
#line 434 "signal.y"
    {
		(yyval.modifier_type_value) = modifier_static;
	;}
    break;

  case 64:
#line 438 "signal.y"
    {
		(yyval.modifier_type_value) = modifier_native;
	;}
    break;

  case 65:
#line 445 "signal.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 66:
#line 449 "signal.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 67:
#line 453 "signal.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 68:
#line 460 "signal.y"
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 69:
#line 464 "signal.y"
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[(3) - (3)].string_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 70:
#line 471 "signal.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].string_value));
	;}
    break;

  case 71:
#line 475 "signal.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].string_value), (yyvsp[(1) - (4)].ast_value))
	;}
    break;

  case 72:
#line 482 "signal.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 73:
#line 486 "signal.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(3) - (3)].ast_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 74:
#line 493 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 75:
#line 497 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 76:
#line 504 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 77:
#line 508 "signal.y"
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 78:
#line 515 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 79:
#line 522 "signal.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 80:
#line 526 "signal.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(3) - (3)].string_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 81:
#line 535 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 84:
#line 543 "signal.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_pos, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 85:
#line 547 "signal.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_neg, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 86:
#line 551 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 87:
#line 555 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 88:
#line 559 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 89:
#line 563 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 90:
#line 567 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 91:
#line 571 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 92:
#line 575 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_equal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 93:
#line 579 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_notequal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 94:
#line 583 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 95:
#line 587 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 96:
#line 591 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 97:
#line 595 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 98:
#line 599 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 99:
#line 603 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 100:
#line 607 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 101:
#line 611 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 102:
#line 615 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 103:
#line 619 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 104:
#line 623 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_and_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 105:
#line 627 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 106:
#line 631 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 107:
#line 635 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 108:
#line 639 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 109:
#line 643 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_gt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 110:
#line 647 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_ge, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 111:
#line 651 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 112:
#line 655 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_le, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 113:
#line 659 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 114:
#line 663 "signal.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 115:
#line 667 "signal.y"
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].string_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 116:
#line 671 "signal.y"
    {
		(yyval.ast_value) = ast_new_as((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 117:
#line 675 "signal.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_childa, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 118:
#line 679 "signal.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_not, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 119:
#line 683 "signal.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 120:
#line 687 "signal.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 121:
#line 691 "signal.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (5)].ast_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 122:
#line 695 "signal.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (4)].ast_value), ast_new_blank());
	;}
    break;

  case 127:
#line 705 "signal.y"
    {
		(yyval.ast_value) = ast_new_true();
	;}
    break;

  case 128:
#line 709 "signal.y"
    {
		(yyval.ast_value) = ast_new_false();
	;}
    break;

  case 129:
#line 713 "signal.y"
    {
		(yyval.ast_value) = ast_new_null();
	;}
    break;

  case 130:
#line 717 "signal.y"
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 131:
#line 721 "signal.y"
    {
		(yyval.ast_value) = ast_new_this();
	;}
    break;

  case 132:
#line 725 "signal.y"
    {
		(yyval.ast_value) = ast_new_super();
	;}
    break;

  case 133:
#line 734 "signal.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 134:
#line 738 "signal.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 135:
#line 744 "signal.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 146:
#line 760 "signal.y"
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].string_value));
	;}
    break;

  case 147:
#line 766 "signal.y"
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 148:
#line 772 "signal.y"
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 149:
#line 778 "signal.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 150:
#line 782 "signal.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(3) - (7)].ast_value), (yyvsp[(5) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 151:
#line 786 "signal.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 152:
#line 790 "signal.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(3) - (8)].ast_value), (yyvsp[(5) - (8)].ast_value), (yyvsp[(6) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value));
	;}
    break;

  case 154:
#line 797 "signal.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 155:
#line 803 "signal.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 156:
#line 809 "signal.y"
    {
		(yyval.ast_value) = ast_new_while((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 157:
#line 815 "signal.y"
    {
		(yyval.ast_value) = ast_new_break();
	;}
    break;

  case 158:
#line 821 "signal.y"
    {
		(yyval.ast_value) = ast_new_continue();
	;}
    break;

  case 159:
#line 827 "signal.y"
    {
		(yyval.ast_value) = ast_new_return((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 160:
#line 833 "signal.y"
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 161:
#line 839 "signal.y"
    {
		(yyval.ast_value) = ast_new_try((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 162:
#line 845 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 163:
#line 849 "signal.y"
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 164:
#line 855 "signal.y"
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].string_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 165:
#line 864 "signal.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 166:
#line 868 "signal.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 167:
#line 874 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3020 "signal.tab.c"
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


#line 883 "signal.y"





