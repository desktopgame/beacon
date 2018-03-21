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
     ASSIGN = 274,
     ADD_ASSIGN = 275,
     SUB_ASSIGN = 276,
     MUL_ASSIGN = 277,
     DIV_ASSIGN = 278,
     MOD_ASSIGN = 279,
     EQUAL = 280,
     NOTEQUAL = 281,
     INC = 282,
     DEC = 283,
     GT = 284,
     GE = 285,
     LT = 286,
     LE = 287,
     BIT_AND = 288,
     LOGIC_AND = 289,
     BIT_OR = 290,
     LOGIC_OR = 291,
     LCB = 292,
     RCB = 293,
     LRB = 294,
     RRB = 295,
     LSB = 296,
     RSB = 297,
     SEMI = 298,
     IMPORT = 299,
     VAR = 300,
     THIS = 301,
     SUPER = 302,
     TRUE_TOK = 303,
     FALSE_TOK = 304,
     NULL_TOK = 305,
     AS = 306,
     INTERFACE = 307,
     CLASS = 308,
     ENUM = 309,
     PUBLIC = 310,
     PRIVATE = 311,
     PROTECTED = 312,
     STATIC = 313,
     NATIVE = 314,
     NEW = 315,
     IN = 316,
     OUT = 317,
     CTOR = 318,
     DEF = 319,
     ARROW = 320,
     NAMESPACE = 321,
     RETURN = 322,
     IF = 323,
     ELIF = 324,
     ELSE = 325,
     WHILE = 326,
     BREAK = 327,
     CONTINUE = 328,
     TRY = 329,
     CATCH = 330,
     THROW = 331,
     UMINUS = 332,
     NONAME = 333
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
#define ASSIGN 274
#define ADD_ASSIGN 275
#define SUB_ASSIGN 276
#define MUL_ASSIGN 277
#define DIV_ASSIGN 278
#define MOD_ASSIGN 279
#define EQUAL 280
#define NOTEQUAL 281
#define INC 282
#define DEC 283
#define GT 284
#define GE 285
#define LT 286
#define LE 287
#define BIT_AND 288
#define LOGIC_AND 289
#define BIT_OR 290
#define LOGIC_OR 291
#define LCB 292
#define RCB 293
#define LRB 294
#define RRB 295
#define LSB 296
#define RSB 297
#define SEMI 298
#define IMPORT 299
#define VAR 300
#define THIS 301
#define SUPER 302
#define TRUE_TOK 303
#define FALSE_TOK 304
#define NULL_TOK 305
#define AS 306
#define INTERFACE 307
#define CLASS 308
#define ENUM 309
#define PUBLIC 310
#define PRIVATE 311
#define PROTECTED 312
#define STATIC 313
#define NATIVE 314
#define NEW 315
#define IN 316
#define OUT 317
#define CTOR 318
#define DEF 319
#define ARROW 320
#define NAMESPACE 321
#define RETURN 322
#define IF 323
#define ELIF 324
#define ELSE 325
#define WHILE 326
#define BREAK 327
#define CONTINUE 328
#define TRY 329
#define CATCH 330
#define THROW 331
#define UMINUS 332
#define NONAME 333




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
#line 277 "signal.tab.c"
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
#line 302 "signal.tab.c"

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
#define YYFINAL  88
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   588

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  177
/* YYNRULES -- Number of states.  */
#define YYNSTATES  327

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   333

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      79,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      83,    84,     2,     2,     2,    82,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      80,     2,    81,     2,     2,     2,     2,     2,     2,     2,
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
      75,    76,    77,    78
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
     274,   278,   280,   282,   286,   288,   290,   292,   294,   296,
     298,   300,   304,   306,   310,   312,   316,   320,   322,   326,
     330,   334,   338,   340,   344,   348,   350,   354,   358,   362,
     364,   367,   370,   372,   375,   378,   380,   383,   386,   390,
     392,   396,   398,   400,   402,   404,   410,   415,   417,   419,
     421,   423,   425,   427,   429,   431,   433,   437,   443,   448,
     450,   452,   455,   458,   460,   462,   464,   466,   468,   470,
     472,   474,   476,   478,   482,   488,   494,   500,   508,   515,
     524,   526,   529,   535,   541,   544,   547,   551,   555,   559,
     561,   564,   571,   575,   578,   580,   582,   584
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      86,     0,    -1,    87,    -1,     1,    79,    -1,   143,    -1,
      94,    -1,    88,    -1,   112,    -1,    66,    93,    89,    -1,
      37,    92,    38,    -1,    66,    93,    89,    -1,   100,    -1,
     102,    -1,   101,    -1,    90,    -1,    91,    90,    -1,    -1,
      91,    -1,     7,    -1,    93,     8,     7,    -1,    44,     4,
      -1,     7,    96,    -1,    -1,    31,    97,    29,    -1,    98,
      -1,    97,     9,    98,    -1,     7,    99,    -1,    61,     7,
      99,    -1,    62,     7,    99,    -1,    -1,    39,   121,    40,
      -1,    53,    95,    37,   103,    38,    -1,    53,    95,    11,
     121,    37,   103,    38,    -1,    54,     7,    37,   117,    38,
      -1,    54,     7,    37,   117,     9,    38,    -1,    52,    95,
      37,   103,    38,    -1,    52,    95,    11,   121,    37,   103,
      38,    -1,    -1,   104,    -1,   105,    -1,   104,   105,    -1,
     116,    11,   106,    -1,   107,    -1,   106,   107,    -1,   108,
      -1,   113,    -1,   114,    -1,    63,    60,    39,   118,    40,
     111,   160,    -1,    63,    60,    39,    40,   111,   160,    -1,
      11,   110,    39,   119,    40,    -1,    11,   110,    39,    40,
      -1,    47,    -1,    46,    -1,    -1,   109,    -1,    64,     7,
      39,   118,    40,    65,   122,   160,    -1,    64,     7,    39,
      40,    65,   122,   160,    -1,   115,    64,     7,    96,    39,
     118,    40,    65,   122,   160,    -1,   115,    64,     7,    96,
      39,    40,    65,   122,   160,    -1,   115,   122,     7,    43,
      -1,    -1,    58,    59,    -1,    59,    58,    -1,    58,    -1,
      59,    -1,    55,    -1,    56,    -1,    57,    -1,     7,    -1,
     117,     9,     7,    -1,   122,     7,    -1,   118,     9,   122,
       7,    -1,   124,    -1,   119,     9,   124,    -1,    -1,    80,
     121,    81,    -1,   122,    -1,   121,     9,   122,    -1,   123,
     120,    -1,     7,    -1,   123,    12,     7,    -1,   125,    -1,
     127,    -1,   136,   126,   125,    -1,    19,    -1,    20,    -1,
      21,    -1,    22,    -1,    23,    -1,    24,    -1,   128,    -1,
     127,    36,   128,    -1,   129,    -1,   128,    34,   129,    -1,
     130,    -1,   129,    25,   130,    -1,   129,    26,   130,    -1,
     131,    -1,   130,    29,   131,    -1,   130,    30,   131,    -1,
     130,    31,   131,    -1,   130,    32,   131,    -1,   132,    -1,
     131,    13,   132,    -1,   131,    14,   132,    -1,   133,    -1,
     132,    15,   133,    -1,   132,    16,   133,    -1,   132,    17,
     133,    -1,   134,    -1,    18,   133,    -1,    82,   133,    -1,
     135,    -1,    27,   135,    -1,    28,   135,    -1,   136,    -1,
     136,    27,    -1,   136,    28,    -1,   136,    51,   122,    -1,
     137,    -1,    83,   124,    84,    -1,   138,    -1,   139,    -1,
      46,    -1,    47,    -1,    60,   122,    39,   119,    40,    -1,
      60,   122,    39,    40,    -1,     5,    -1,     6,    -1,     3,
      -1,     4,    -1,    48,    -1,    49,    -1,    50,    -1,   140,
      -1,   141,    -1,   136,     8,     7,    -1,   142,   120,    39,
     119,    40,    -1,   142,   120,    39,    40,    -1,   137,    -1,
     144,    -1,   143,   144,    -1,   124,   161,    -1,   145,    -1,
     146,    -1,   147,    -1,   148,    -1,   151,    -1,   152,    -1,
     153,    -1,   154,    -1,   155,    -1,   156,    -1,   122,     7,
      43,    -1,   122,     7,    19,   124,   161,    -1,    45,     7,
      19,   124,   161,    -1,    68,    39,   124,    40,   159,    -1,
      68,    39,   124,    40,   159,    70,   159,    -1,    68,    39,
     124,    40,   159,   149,    -1,    68,    39,   124,    40,   159,
     149,    70,   159,    -1,   150,    -1,   149,   150,    -1,    69,
      39,   124,    40,   159,    -1,    71,    39,   124,    40,   160,
      -1,    72,   161,    -1,    73,   161,    -1,    67,   124,   161,
      -1,    76,   124,   161,    -1,    74,   159,   157,    -1,   158,
      -1,   157,   158,    -1,    75,    39,   122,     7,    40,   159,
      -1,    37,   143,    38,    -1,    37,    38,    -1,    43,    -1,
     159,    -1,    43,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   127,   127,   128,   135,   139,   143,   147,   154,   161,
     168,   172,   173,   174,   178,   182,   190,   193,   197,   201,
     208,   215,   223,   226,   233,   237,   244,   248,   252,   260,
     263,   270,   274,   281,   285,   292,   296,   304,   307,   311,
     312,   319,   326,   330,   337,   338,   339,   343,   347,   354,
     358,   365,   369,   377,   380,   384,   388,   395,   399,   406,
     414,   417,   421,   425,   429,   436,   440,   444,   451,   455,
     462,   466,   473,   477,   485,   488,   495,   499,   506,   513,
     517,   529,   532,   533,   539,   543,   547,   551,   555,   559,
     565,   566,   572,   573,   579,   580,   584,   590,   591,   595,
     599,   603,   609,   610,   614,   620,   621,   625,   629,   635,
     636,   640,   646,   647,   651,   657,   658,   662,   666,   672,
     673,   679,   680,   681,   685,   689,   693,   700,   701,   702,
     703,   704,   708,   712,   718,   719,   726,   733,   737,   743,
     748,   752,   758,   762,   763,   764,   765,   766,   767,   768,
     769,   770,   771,   774,   780,   786,   792,   796,   800,   804,
     810,   811,   817,   823,   829,   835,   841,   847,   853,   859,
     863,   869,   880,   884,   890,   894,   897,   898
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR_LITERAL", "STRING_LITERAL", "INT",
  "DOUBLE", "IDENT", "DOT", "COMMA", "COMMA_OPT", "COLON", "COLO_COLO",
  "ADD", "SUB", "MUL", "DIV", "MOD", "NOT", "ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "EQUAL",
  "NOTEQUAL", "INC", "DEC", "GT", "GE", "LT", "LE", "BIT_AND", "LOGIC_AND",
  "BIT_OR", "LOGIC_OR", "LCB", "RCB", "LRB", "RRB", "LSB", "RSB", "SEMI",
  "IMPORT", "VAR", "THIS", "SUPER", "TRUE_TOK", "FALSE_TOK", "NULL_TOK",
  "AS", "INTERFACE", "CLASS", "ENUM", "PUBLIC", "PRIVATE", "PROTECTED",
  "STATIC", "NATIVE", "NEW", "IN", "OUT", "CTOR", "DEF", "ARROW",
  "NAMESPACE", "RETURN", "IF", "ELIF", "ELSE", "WHILE", "BREAK",
  "CONTINUE", "TRY", "CATCH", "THROW", "UMINUS", "NONAME", "'\\n'", "'<'",
  "'>'", "'-'", "'('", "')'", "$accept", "compilation_unit", "program",
  "namespace_decl", "namespace_body", "namespace_member_decl",
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
  "typename_T", "fqcn_part", "expression", "assign", "assign_type_T", "or",
  "and", "equal", "compare", "addsub", "muldiv", "unary", "prefix",
  "postfix", "primary", "primary_nobrace", "primary_literal",
  "primary_assoc", "primary_faccess", "primary_mcall", "primary_maccess",
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,    10,
      60,    62,    45,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    86,    87,    87,    87,    87,    88,    89,
      90,    90,    90,    90,    91,    91,    92,    92,    93,    93,
      94,    95,    96,    96,    97,    97,    98,    98,    98,    99,
      99,   100,   100,   101,   101,   102,   102,   103,   103,   104,
     104,   105,   106,   106,   107,   107,   107,   108,   108,   109,
     109,   110,   110,   111,   111,   112,   112,   113,   113,   114,
     115,   115,   115,   115,   115,   116,   116,   116,   117,   117,
     118,   118,   119,   119,   120,   120,   121,   121,   122,   123,
     123,   124,   125,   125,   126,   126,   126,   126,   126,   126,
     127,   127,   128,   128,   129,   129,   129,   130,   130,   130,
     130,   130,   131,   131,   131,   132,   132,   132,   132,   133,
     133,   133,   134,   134,   134,   135,   135,   135,   135,   136,
     136,   137,   137,   137,   137,   137,   137,   138,   138,   138,
     138,   138,   138,   138,   139,   139,   140,   141,   141,   142,
     143,   143,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   145,   146,   147,   148,   148,   148,   148,
     149,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     157,   158,   159,   159,   160,   160,   161,   161
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
       3,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     1,     2,     2,     1,     2,     2,     3,     1,
       3,     1,     1,     1,     1,     5,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     5,     4,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     5,     5,     5,     7,     6,     8,
       1,     2,     5,     5,     2,     2,     3,     3,     3,     1,
       2,     6,     3,     2,     1,     1,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,   129,   130,   127,   128,    79,     0,     0,     0,
       0,     0,   123,   124,   131,   132,   133,     0,     0,     0,
       0,     0,     0,   177,   177,     0,     0,     0,     0,     0,
       2,     6,     5,     7,     0,    74,   177,    81,    82,    90,
      92,    94,    97,   102,   105,   109,   112,   115,   119,   121,
     122,   134,   135,    74,     4,   140,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,     3,   110,   115,   113,
     114,    20,     0,     0,     0,    18,     0,   177,     0,     0,
     176,   164,   165,     0,     0,   177,   111,     0,     1,     0,
       0,     0,    78,   142,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    84,    85,
      86,    87,    88,    89,   116,   117,     0,     0,     0,   141,
       0,     0,     0,     0,    16,     8,   166,     0,     0,   173,
       0,     0,   168,   169,   167,   120,     0,   153,    80,     0,
      76,    91,    93,    95,    96,    98,    99,   100,   101,   103,
     104,   106,   107,   108,   136,   118,    83,     0,   177,   126,
       0,    72,     0,     0,     0,    19,     0,     0,     0,     0,
      14,    17,     0,    11,    13,    12,     0,     0,   172,     0,
     170,   177,     0,    75,   138,     0,   155,     0,   125,     0,
       0,     0,    70,    22,     0,     0,     0,     0,    15,     9,
     156,   174,   175,   163,     0,   154,    77,   137,    73,     0,
       0,     0,     0,    21,     0,    37,     0,    37,     0,    10,
       0,     0,   158,   160,     0,    56,    71,     0,    29,     0,
       0,     0,    24,     0,    65,    66,    67,     0,    38,    39,
       0,     0,     0,    68,     0,     0,   157,     0,   161,     0,
      55,     0,    26,    29,    29,     0,    23,    37,    35,    40,
      60,    37,    31,     0,    33,     0,   159,   171,     0,    27,
      28,    25,     0,    63,    64,     0,    41,    42,    44,    45,
      46,     0,     0,    69,    34,     0,    30,    36,    61,    62,
       0,    43,     0,     0,    32,   162,     0,    22,     0,    53,
       0,     0,    59,     0,    54,     0,    53,     0,    52,    51,
       0,    48,     0,     0,     0,     0,    47,     0,     0,    50,
       0,     0,     0,    49,    58,     0,    57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    29,    30,    31,   125,   170,   171,   172,    76,    32,
     194,   213,   231,   232,   252,   173,   174,   175,   237,   238,
     239,   276,   277,   278,   304,   310,   305,    33,   279,   280,
     281,   240,   244,   163,   160,    92,   139,    34,    35,    36,
      37,   117,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,   222,   223,    60,    61,    62,    63,
      64,    65,   132,   133,   202,   203,    81
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -267
static const yytype_int16 yypact[] =
{
     175,   -43,  -267,  -267,  -267,  -267,  -267,   505,    29,    29,
      94,    87,  -267,  -267,  -267,  -267,  -267,   109,   159,   170,
     505,    64,   122,   148,   148,    63,   505,   505,   505,   192,
    -267,  -267,  -267,  -267,   189,     1,   148,  -267,   162,   166,
       2,   154,    32,   135,  -267,  -267,  -267,   187,   -25,  -267,
    -267,  -267,  -267,   124,   366,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,    34,  -267,
    -267,  -267,   186,   173,   174,  -267,    85,   148,   505,   505,
    -267,  -267,  -267,   264,   141,   148,  -267,   133,  -267,     5,
     211,   109,  -267,  -267,   505,   505,   505,   505,   505,   505,
     505,   505,   505,   505,   505,   505,   505,   221,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,   109,   505,   191,  -267,
     505,   404,    11,   224,    93,  -267,  -267,   193,   196,  -267,
     315,   198,   141,  -267,  -267,  -267,   505,  -267,  -267,     3,
    -267,   166,     2,   154,   154,    32,    32,    32,    32,   135,
     135,  -267,  -267,  -267,  -267,  -267,  -267,   452,   148,  -267,
      -3,  -267,   167,    12,   233,  -267,   237,   237,   238,   170,
    -267,    93,   212,  -267,  -267,  -267,    63,     7,  -267,   109,
    -267,   148,   109,  -267,  -267,    48,  -267,   505,  -267,   109,
     109,   188,  -267,   223,    55,    86,   215,    85,  -267,  -267,
      37,  -267,  -267,  -267,   248,  -267,  -267,  -267,  -267,     7,
     249,   109,     8,  -267,   109,   114,   109,   114,   252,  -267,
     222,    63,    70,  -267,   220,  -267,  -267,     7,   227,   255,
     256,    20,  -267,    82,  -267,  -267,  -267,   234,   114,  -267,
     262,   104,   236,  -267,    77,   505,  -267,    63,  -267,    63,
    -267,   109,  -267,   227,   227,     8,  -267,   114,  -267,  -267,
      90,   114,  -267,    57,  -267,   235,  -267,  -267,    56,  -267,
    -267,  -267,   239,   217,   225,   218,     9,  -267,  -267,  -267,
    -267,    18,   242,  -267,  -267,    63,  -267,  -267,  -267,  -267,
     245,  -267,   274,   278,  -267,  -267,    13,   223,   243,   276,
      74,   250,  -267,    96,  -267,     7,   276,    16,  -267,  -267,
     254,  -267,     7,   229,    78,   457,  -267,   109,   230,  -267,
      81,     7,   109,  -267,  -267,     7,  -267
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -267,  -267,  -267,  -267,    91,   126,  -267,  -267,   129,  -267,
     132,     6,  -267,    46,   -99,  -267,  -267,  -267,  -214,  -267,
      66,  -267,    30,  -267,  -267,  -267,    10,  -267,  -267,  -267,
    -267,  -267,  -267,  -266,  -155,   270,  -197,   -17,  -267,   -19,
     190,  -267,  -267,   214,   231,    61,    89,    72,     4,  -267,
     155,    31,  -267,  -267,  -267,  -267,  -267,  -267,   232,   -50,
    -267,  -267,  -267,  -267,  -267,    95,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,   195,   -20,  -201,   -14
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -140
static const yytype_int16 yytable[] =
{
      73,    77,   185,   242,   119,    84,   187,    85,   225,    87,
      82,    67,   182,    90,  -139,   228,   -60,   233,     6,   241,
       6,   190,    93,     6,   136,     6,   250,    96,    97,   255,
     300,    86,     2,     3,     4,     5,    66,   188,    68,    68,
      68,   314,   107,   272,    83,   102,   103,   282,   137,   256,
     201,   162,   191,   299,   268,  -139,   313,   187,    68,   127,
     128,   114,   115,   126,   283,   182,   214,   273,   274,   229,
     230,   134,   275,   -60,   140,    12,    13,    14,    15,    16,
     119,    91,   292,   190,   183,   116,   263,   190,   207,    17,
     187,   182,   215,   123,    72,   284,   286,   216,    71,   155,
      83,   158,   161,    78,   311,   164,   220,   221,   151,   152,
     153,   316,    28,   182,   306,   264,     6,   181,   318,   257,
     324,   323,   124,   217,   326,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,   161,   220,
     247,   261,   308,   309,   186,   166,   167,   168,   273,   274,
     104,   105,   106,   275,   269,   270,   200,   143,   144,   169,
     320,    79,   204,    69,    70,   206,    74,   205,   208,   234,
     235,   236,   209,   210,   149,   150,     1,    75,     2,     3,
       4,     5,     6,    98,    99,   100,   101,   145,   146,   147,
     148,    80,    88,     7,   227,   107,    89,   140,    94,   140,
      95,   246,     8,     9,    91,   120,   108,   109,   110,   111,
     112,   113,   121,   122,   114,   115,   131,   135,   138,    10,
      11,    12,    13,    14,    15,    16,   265,   266,   154,   267,
     157,   165,   189,   176,   140,    17,   177,   179,   116,    18,
     192,    19,    20,    21,   193,   196,    22,    23,    24,    25,
     199,    26,   218,   211,   212,   224,   226,    27,    28,   243,
     249,   245,   253,   254,   293,   295,   251,     2,     3,     4,
       5,     6,   258,   260,   262,   285,   288,   287,   290,   164,
     294,   297,     7,   289,   296,   298,   302,   303,   219,   307,
     164,     8,     9,   315,   317,   322,   161,   198,   197,   195,
     321,   271,   129,   301,   259,   325,   291,   156,   141,    11,
      12,    13,    14,    15,    16,   130,   312,   248,     2,     3,
       4,     5,     6,   118,    17,     0,   142,   180,     0,     0,
       0,    20,    21,     7,     0,    22,    23,    24,    25,     0,
      26,     0,     8,     9,     0,     0,    27,    28,     0,     0,
       0,     0,     0,   178,     0,     0,     0,     0,     0,     0,
      11,    12,    13,    14,    15,    16,     0,     0,     0,     2,
       3,     4,     5,     6,     0,    17,     0,     0,     0,     0,
       0,     0,    20,    21,     7,     0,    22,    23,    24,    25,
       0,    26,     0,     8,     9,     0,     0,    27,    28,     0,
       0,     0,     0,     0,     0,     0,     0,     2,     3,     4,
       5,    11,    12,    13,    14,    15,    16,     0,     0,     0,
       0,     0,     7,     0,     0,     0,    17,     0,     0,     0,
       0,     8,     9,    20,    21,     0,     0,    22,    23,    24,
      25,     0,    26,     0,   159,     0,     0,     0,    27,    28,
      12,    13,    14,    15,    16,     2,     3,     4,     5,     0,
       2,     3,     4,     5,    17,     0,     0,     0,     0,     0,
       7,     0,     0,     0,     0,     7,     0,     0,     0,     8,
       9,     0,     0,     0,     8,     9,    27,    28,     0,     0,
       0,     0,   184,     0,     0,     0,     0,   319,    12,    13,
      14,    15,    16,    12,    13,    14,    15,    16,     2,     3,
       4,     5,    17,     0,     0,     0,     0,    17,     0,     0,
       0,     0,     0,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     8,     9,    27,    28,     0,     0,     0,    27,
      28,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,    13,    14,    15,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    27,    28
};

static const yytype_int16 yycheck[] =
{
      17,    20,   157,   217,    54,    25,     9,    26,   209,    28,
      24,     7,     9,    12,    39,     7,     7,   214,     7,   216,
       7,     9,    36,     7,    19,     7,   227,    25,    26,     9,
     296,    27,     3,     4,     5,     6,    79,    40,     7,     8,
       9,   307,     8,   257,    37,    13,    14,   261,    43,    29,
      43,    40,    40,    40,   251,    80,    40,     9,    27,    78,
      79,    27,    28,    77,     7,     9,    11,    58,    59,    61,
      62,    85,    63,    64,    91,    46,    47,    48,    49,    50,
     130,    80,    64,     9,    81,    51,     9,     9,    40,    60,
       9,     9,    37,     8,     7,    38,    40,    11,     4,   116,
      37,   120,   121,    39,   305,   122,    69,    70,   104,   105,
     106,   312,    83,     9,    40,    38,     7,   136,    40,    37,
     321,    40,    37,    37,   325,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   157,    69,
      70,    37,    46,    47,   158,    52,    53,    54,    58,    59,
      15,    16,    17,    63,   253,   254,   176,    96,    97,    66,
     315,    39,   179,     8,     9,   182,     7,   181,   187,    55,
      56,    57,   189,   190,   102,   103,     1,     7,     3,     4,
       5,     6,     7,    29,    30,    31,    32,    98,    99,   100,
     101,    43,     0,    18,   211,     8,     7,   214,    36,   216,
      34,   221,    27,    28,    80,    19,    19,    20,    21,    22,
      23,    24,    39,    39,    27,    28,    75,    84,     7,    44,
      45,    46,    47,    48,    49,    50,   245,   247,     7,   249,
      39,     7,    65,    40,   251,    60,    40,    39,    51,    64,
       7,    66,    67,    68,     7,     7,    71,    72,    73,    74,
      38,    76,    37,    65,    31,     7,     7,    82,    83,     7,
      40,    39,     7,     7,   281,   285,    39,     3,     4,     5,
       6,     7,    38,    11,    38,    40,    59,    38,    60,   296,
      38,     7,    18,    58,    39,     7,    43,    11,   197,    39,
     307,    27,    28,    39,    65,    65,   315,   171,   169,   167,
     317,   255,    38,   297,   238,   322,   276,   117,    94,    45,
      46,    47,    48,    49,    50,    83,   306,   222,     3,     4,
       5,     6,     7,    53,    60,    -1,    95,   132,    -1,    -1,
      -1,    67,    68,    18,    -1,    71,    72,    73,    74,    -1,
      76,    -1,    27,    28,    -1,    -1,    82,    83,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    -1,    -1,    -1,     3,
       4,     5,     6,     7,    -1,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    18,    -1,    71,    72,    73,    74,
      -1,    76,    -1,    27,    28,    -1,    -1,    82,    83,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      -1,    -1,    18,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    27,    28,    67,    68,    -1,    -1,    71,    72,    73,
      74,    -1,    76,    -1,    40,    -1,    -1,    -1,    82,    83,
      46,    47,    48,    49,    50,     3,     4,     5,     6,    -1,
       3,     4,     5,     6,    60,    -1,    -1,    -1,    -1,    -1,
      18,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    27,
      28,    -1,    -1,    -1,    27,    28,    82,    83,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    40,    46,    47,
      48,    49,    50,    46,    47,    48,    49,    50,     3,     4,
       5,     6,    60,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    28,    82,    83,    -1,    -1,    -1,    82,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    83
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,    18,    27,    28,
      44,    45,    46,    47,    48,    49,    50,    60,    64,    66,
      67,    68,    71,    72,    73,    74,    76,    82,    83,    86,
      87,    88,    94,   112,   122,   123,   124,   125,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     151,   152,   153,   154,   155,   156,    79,   133,   136,   135,
     135,     4,     7,   122,     7,     7,    93,   124,    39,    39,
      43,   161,   161,    37,   159,   124,   133,   124,     0,     7,
      12,    80,   120,   161,    36,    34,    25,    26,    29,    30,
      31,    32,    13,    14,    15,    16,    17,     8,    19,    20,
      21,    22,    23,    24,    27,    28,    51,   126,   120,   144,
      19,    39,    39,     8,    37,    89,   161,   124,   124,    38,
     143,    75,   157,   158,   161,    84,    19,    43,     7,   121,
     122,   128,   129,   130,   130,   131,   131,   131,   131,   132,
     132,   133,   133,   133,     7,   122,   125,    39,   124,    40,
     119,   124,    40,   118,   122,     7,    52,    53,    54,    66,
      90,    91,    92,   100,   101,   102,    40,    40,    38,    39,
     158,   124,     9,    81,    40,   119,   161,     9,    40,    65,
       9,    40,     7,     7,    95,    95,     7,    93,    90,    38,
     159,    43,   159,   160,   122,   161,   122,    40,   124,   122,
     122,    65,    31,    96,    11,    37,    11,    37,    37,    89,
      69,    70,   149,   150,     7,   160,     7,   122,     7,    61,
      62,    97,    98,   121,    55,    56,    57,   103,   104,   105,
     116,   121,   103,     7,   117,    39,   159,    70,   150,    40,
     160,    39,    99,     7,     7,     9,    29,    37,    38,   105,
      11,    37,    38,     9,    38,   124,   159,   159,   121,    99,
      99,    98,   103,    58,    59,    63,   106,   107,   108,   113,
     114,   115,   103,     7,    38,    40,    40,    38,    59,    58,
      60,   107,    64,   122,    38,   159,    39,     7,     7,    40,
     118,    96,    43,    11,   109,   111,    40,    39,    46,    47,
     110,   160,   111,    40,   118,    39,   160,    65,    40,    40,
     119,   122,    65,    40,   160,   122,   160
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
#line 129 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 4:
#line 136 "signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 5:
#line 140 "signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 6:
#line 144 "signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 7:
#line 148 "signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 8:
#line 155 "signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 9:
#line 162 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value)
	;}
    break;

  case 10:
#line 169 "signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 14:
#line 179 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 15:
#line 183 "signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 16:
#line 190 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 18:
#line 198 "signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 19:
#line 202 "signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 20:
#line 209 "signal.y"
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 21:
#line 216 "signal.y"
    {
		(yyval.ast_value) = ast_new_parameterized_typename((yyvsp[(1) - (2)].string_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 22:
#line 223 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 23:
#line 227 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 24:
#line 234 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 25:
#line 238 "signal.y"
    {
		(yyval.ast_value) = ast_new_type_parameter_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 26:
#line 245 "signal.y"
    {
		(yyval.ast_value) = ast_new_type_parameter((yyvsp[(1) - (2)].string_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 27:
#line 249 "signal.y"
    {
		(yyval.ast_value) = ast_new_type_in_parameter((yyvsp[(2) - (3)].string_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 28:
#line 253 "signal.y"
    {
		(yyval.ast_value) = ast_new_type_out_parameter((yyvsp[(2) - (3)].string_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 29:
#line 260 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 30:
#line 264 "signal.y"
    {
		(yyval.ast_value) = ast_new_type_parameter_rule_list((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 31:
#line 271 "signal.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 32:
#line 275 "signal.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 33:
#line 282 "signal.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 34:
#line 286 "signal.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (6)].string_value), (yyvsp[(4) - (6)].ast_value));
	;}
    break;

  case 35:
#line 293 "signal.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 36:
#line 297 "signal.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 37:
#line 304 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 40:
#line 313 "signal.y"
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 41:
#line 320 "signal.y"
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[(1) - (3)].access_level_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 42:
#line 327 "signal.y"
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 43:
#line 331 "signal.y"
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[(1) - (2)].ast_value), ast_new_member_decl((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 47:
#line 344 "signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 48:
#line 348 "signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 49:
#line 355 "signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (5)].chain_type_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 50:
#line 359 "signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (4)].chain_type_value), ast_new_blank());
	;}
    break;

  case 51:
#line 366 "signal.y"
    {
		(yyval.chain_type_value) = chain_type_super;
	;}
    break;

  case 52:
#line 370 "signal.y"
    {
		(yyval.chain_type_value) = chain_type_this;
	;}
    break;

  case 53:
#line 377 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 55:
#line 385 "signal.y"
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[(2) - (8)].string_value), (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 56:
#line 389 "signal.y"
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[(2) - (7)].string_value), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 57:
#line 396 "signal.y"
    {
		(yyval.ast_value) = ast_new_method_decl((yyvsp[(1) - (10)].modifier_type_value), (yyvsp[(3) - (10)].string_value), (yyvsp[(4) - (10)].ast_value), (yyvsp[(6) - (10)].ast_value), (yyvsp[(10) - (10)].ast_value), (yyvsp[(9) - (10)].ast_value));
	;}
    break;

  case 58:
#line 400 "signal.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[(1) - (9)].modifier_type_value), (yyvsp[(3) - (9)].string_value), (yyvsp[(4) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 59:
#line 407 "signal.y"
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[(1) - (4)].modifier_type_value), (yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].string_value));
	;}
    break;

  case 60:
#line 414 "signal.y"
    {
		(yyval.modifier_type_value) = modifier_none;
	;}
    break;

  case 61:
#line 418 "signal.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 62:
#line 422 "signal.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 63:
#line 426 "signal.y"
    {
		(yyval.modifier_type_value) = modifier_static;
	;}
    break;

  case 64:
#line 430 "signal.y"
    {
		(yyval.modifier_type_value) = modifier_native;
	;}
    break;

  case 65:
#line 437 "signal.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 66:
#line 441 "signal.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 67:
#line 445 "signal.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 68:
#line 452 "signal.y"
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 69:
#line 456 "signal.y"
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[(3) - (3)].string_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 70:
#line 463 "signal.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].string_value));
	;}
    break;

  case 71:
#line 467 "signal.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].string_value), (yyvsp[(1) - (4)].ast_value))
	;}
    break;

  case 72:
#line 474 "signal.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 73:
#line 478 "signal.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(3) - (3)].ast_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 74:
#line 485 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 75:
#line 489 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 76:
#line 496 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 77:
#line 500 "signal.y"
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 78:
#line 507 "signal.y"
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 79:
#line 514 "signal.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 80:
#line 518 "signal.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(3) - (3)].string_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 83:
#line 534 "signal.y"
    {
		(yyval.ast_value) = ast_new_generic_assign((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].assign_otype_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 84:
#line 540 "signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_def;
	;}
    break;

  case 85:
#line 544 "signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_add;
	;}
    break;

  case 86:
#line 548 "signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_sub;
	;}
    break;

  case 87:
#line 552 "signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_mul;
	;}
    break;

  case 88:
#line 556 "signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_div;
	;}
    break;

  case 89:
#line 560 "signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_mod;
	;}
    break;

  case 91:
#line 567 "signal.y"
    {
		(yyval.ast_value) = ast_new_logic_or((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 93:
#line 574 "signal.y"
    {
		(yyval.ast_value) = ast_new_logic_and((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 95:
#line 581 "signal.y"
    {
		(yyval.ast_value) = ast_new_equal((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 96:
#line 585 "signal.y"
    {
		(yyval.ast_value) = ast_new_notequal((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 98:
#line 592 "signal.y"
    {
		(yyval.ast_value) = ast_new_gt((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 99:
#line 596 "signal.y"
    {
		(yyval.ast_value) = ast_new_ge((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 100:
#line 600 "signal.y"
    {
		(yyval.ast_value) = ast_new_lt((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 101:
#line 604 "signal.y"
    {
		(yyval.ast_value) = ast_new_le((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 103:
#line 611 "signal.y"
    {
		(yyval.ast_value) = ast_new_add((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 104:
#line 615 "signal.y"
    {
		(yyval.ast_value) = ast_new_sub((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 106:
#line 622 "signal.y"
    {
		(yyval.ast_value) = ast_new_mul((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 107:
#line 626 "signal.y"
    {
		(yyval.ast_value) = ast_new_div((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 108:
#line 630 "signal.y"
    {
		(yyval.ast_value) = ast_new_mod((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 110:
#line 637 "signal.y"
    {
		(yyval.ast_value) = ast_new_not((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 111:
#line 641 "signal.y"
    {
		(yyval.ast_value) = ast_new_neg((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 113:
#line 648 "signal.y"
    {
		(yyval.ast_value) = ast_new_pre_inc((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 114:
#line 652 "signal.y"
    {
		(yyval.ast_value) = ast_new_pre_dec((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 116:
#line 659 "signal.y"
    {
		(yyval.ast_value) = ast_new_post_inc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 117:
#line 663 "signal.y"
    {
		(yyval.ast_value) = ast_new_post_dec((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 118:
#line 667 "signal.y"
    {
		(yyval.ast_value) = ast_new_as((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 120:
#line 674 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 123:
#line 682 "signal.y"
    {
		(yyval.ast_value) = ast_new_this();
	;}
    break;

  case 124:
#line 686 "signal.y"
    {
		(yyval.ast_value) = ast_new_super();
	;}
    break;

  case 125:
#line 690 "signal.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (5)].ast_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 126:
#line 694 "signal.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (4)].ast_value), ast_new_blank());
	;}
    break;

  case 131:
#line 705 "signal.y"
    {
		(yyval.ast_value) = ast_new_true();
	;}
    break;

  case 132:
#line 709 "signal.y"
    {
		(yyval.ast_value) = ast_new_false();
	;}
    break;

  case 133:
#line 713 "signal.y"
    {
		(yyval.ast_value) = ast_new_null();
	;}
    break;

  case 135:
#line 720 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 136:
#line 727 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 137:
#line 734 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 138:
#line 738 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 140:
#line 749 "signal.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 141:
#line 753 "signal.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 142:
#line 759 "signal.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 153:
#line 775 "signal.y"
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].string_value));
	;}
    break;

  case 154:
#line 781 "signal.y"
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 155:
#line 787 "signal.y"
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 156:
#line 793 "signal.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 157:
#line 797 "signal.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(3) - (7)].ast_value), (yyvsp[(5) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 158:
#line 801 "signal.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 159:
#line 805 "signal.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(3) - (8)].ast_value), (yyvsp[(5) - (8)].ast_value), (yyvsp[(6) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value));
	;}
    break;

  case 161:
#line 812 "signal.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 162:
#line 818 "signal.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 163:
#line 824 "signal.y"
    {
		(yyval.ast_value) = ast_new_while((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 164:
#line 830 "signal.y"
    {
		(yyval.ast_value) = ast_new_break();
	;}
    break;

  case 165:
#line 836 "signal.y"
    {
		(yyval.ast_value) = ast_new_continue();
	;}
    break;

  case 166:
#line 842 "signal.y"
    {
		(yyval.ast_value) = ast_new_return((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 167:
#line 848 "signal.y"
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 168:
#line 854 "signal.y"
    {
		(yyval.ast_value) = ast_new_try((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 169:
#line 860 "signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 170:
#line 864 "signal.y"
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 171:
#line 870 "signal.y"
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].string_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 172:
#line 881 "signal.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 173:
#line 885 "signal.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 174:
#line 891 "signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 2820 "signal.tab.c"
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


#line 900 "signal.y"





