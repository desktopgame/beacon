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
     INTERFACE = 319,
     CLASS = 320,
     ENUM = 321,
     PUBLIC = 322,
     PRIVATE = 323,
     PROTECTED = 324,
     STATIC = 325,
     NATIVE = 326,
     NEW = 327,
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
     ASSERT_T = 341,
     DEFER = 342,
     INSTANCEOF = 343,
     BOUNDS_EXTENDS = 344,
     BOUNDS_SUPER = 345,
     PRE_DEC = 346,
     PRE_INC = 347,
     QUOTE = 348,
     POST_DEC = 349,
     POST_INC = 350,
     FUNCCALL = 351,
     REF = 352,
     POSITIVE = 353,
     NEGATIVE = 354,
     FORM_TYPE = 355
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
#define INTERFACE 319
#define CLASS 320
#define ENUM 321
#define PUBLIC 322
#define PRIVATE 323
#define PROTECTED 324
#define STATIC 325
#define NATIVE 326
#define NEW 327
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
#define ASSERT_T 341
#define DEFER 342
#define INSTANCEOF 343
#define BOUNDS_EXTENDS 344
#define BOUNDS_SUPER 345
#define PRE_DEC 346
#define PRE_INC 347
#define QUOTE 348
#define POST_DEC 349
#define POST_INC 350
#define FUNCCALL 351
#define REF 352
#define POSITIVE 353
#define NEGATIVE 354
#define FORM_TYPE 355




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
#line 321 "beacon.tab.c"
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
#line 346 "beacon.tab.c"

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
#define YYLAST   1196

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  103
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  179
/* YYNRULES -- Number of states.  */
#define YYNSTATES  351

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   355

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     102,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      97,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      95,    96,    98,    99,   100,   101
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
     159,   167,   174,   180,   185,   187,   189,   190,   192,   201,
     209,   220,   230,   235,   236,   239,   242,   244,   246,   248,
     250,   252,   254,   258,   261,   266,   268,   272,   273,   277,
     279,   283,   286,   288,   292,   296,   298,   300,   303,   306,
     310,   314,   318,   322,   326,   330,   334,   338,   342,   346,
     350,   354,   358,   362,   366,   370,   374,   378,   382,   386,
     390,   394,   398,   402,   406,   410,   414,   418,   422,   426,
     430,   433,   436,   441,   445,   452,   458,   460,   462,   464,
     467,   472,   474,   476,   478,   480,   482,   484,   486,   488,
     491,   494,   496,   498,   500,   502,   504,   506,   508,   510,
     512,   514,   516,   518,   522,   528,   534,   538,   544,   549,
     556,   558,   561,   565,   569,   572,   575,   579,   583,   587,
     589,   592,   599,   605,   609,   612,   616,   619,   621,   623
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     104,     0,    -1,   105,   106,    -1,   104,   106,    -1,     1,
     102,    -1,    -1,   113,    -1,   149,    -1,   107,    -1,   132,
      -1,    75,   112,   108,    -1,    48,   111,    49,    -1,    75,
     112,   108,    -1,   119,    -1,   120,    -1,   122,    -1,   121,
      -1,   109,    -1,   110,   109,    -1,    -1,   110,    -1,     7,
      -1,   112,     8,     7,    -1,   114,    -1,   113,   114,    -1,
      55,     4,    -1,     7,   116,    -1,    -1,    52,   117,    53,
      -1,   118,    -1,   117,     9,   118,    -1,     7,    -1,    63,
      65,   115,    48,   123,    49,    -1,    63,    65,   115,    10,
     141,    48,   123,    49,    -1,    65,   115,    48,   123,    49,
      -1,    65,   115,    10,   141,    48,   123,    49,    -1,    66,
       7,    48,   137,    49,    -1,    66,     7,    48,   137,     9,
      49,    -1,    64,   115,    48,   123,    49,    -1,    64,   115,
      10,   141,    48,   123,    49,    -1,    -1,   124,    -1,   125,
      -1,   124,   125,    -1,   136,    10,   126,    -1,   127,    -1,
     126,   127,    -1,   128,    -1,   133,    -1,   134,    -1,    73,
      72,    50,   138,    51,   131,   167,    -1,    73,    72,    50,
      51,   131,   167,    -1,    10,   130,    50,   139,    51,    -1,
      10,   130,    50,    51,    -1,    58,    -1,    57,    -1,    -1,
     129,    -1,    73,     7,    50,   138,    51,    74,   142,   167,
      -1,    73,     7,    50,    51,    74,   142,   167,    -1,    73,
     135,     7,   116,    50,   138,    51,    74,   142,   167,    -1,
      73,   135,     7,   116,    50,    51,    74,   142,   167,    -1,
     135,   142,     7,    54,    -1,    -1,    70,    71,    -1,    71,
      70,    -1,    70,    -1,    71,    -1,    67,    -1,    68,    -1,
      69,    -1,     7,    -1,   137,     9,     7,    -1,   142,     7,
      -1,   138,     9,   142,     7,    -1,   144,    -1,   139,     9,
     144,    -1,    -1,    52,   141,    53,    -1,   142,    -1,   141,
       9,   142,    -1,   143,   140,    -1,     7,    -1,   143,    11,
       7,    -1,    50,   144,    51,    -1,   147,    -1,   145,    -1,
      13,   144,    -1,    14,   144,    -1,   144,    13,   144,    -1,
     144,    14,   144,    -1,   144,    15,   144,    -1,   144,    16,
     144,    -1,   144,    17,   144,    -1,   144,    32,   144,    -1,
     144,    22,   144,    -1,   144,    23,   144,    -1,   144,    30,
     144,    -1,   144,    47,   144,    -1,   144,    33,   144,    -1,
     144,    31,   144,    -1,   146,    34,   144,    -1,   146,    35,
     144,    -1,   146,    36,   144,    -1,   146,    37,   144,    -1,
     146,    38,   144,    -1,   146,    39,   144,    -1,   146,    40,
     144,    -1,   146,    41,   144,    -1,   146,    44,   144,    -1,
     146,    42,   144,    -1,   146,    43,   144,    -1,   144,    24,
     144,    -1,   144,    25,   144,    -1,   144,    26,   144,    -1,
     144,    27,   144,    -1,   144,    19,   144,    -1,   144,    20,
     144,    -1,   144,    88,   142,    -1,   144,    62,   142,    -1,
      21,   144,    -1,    18,   144,    -1,   145,    50,   139,    51,
      -1,   145,    50,    51,    -1,    72,   143,   140,    50,   139,
      51,    -1,    72,   143,   140,    50,    51,    -1,    57,    -1,
      58,    -1,   146,    -1,   143,   140,    -1,   144,     8,     7,
     140,    -1,     5,    -1,     6,    -1,     3,    -1,     4,    -1,
      59,    -1,    60,    -1,    61,    -1,   149,    -1,   148,   149,
      -1,   144,   168,    -1,   150,    -1,   151,    -1,   152,    -1,
     153,    -1,   156,    -1,   157,    -1,   158,    -1,   159,    -1,
     160,    -1,   161,    -1,   164,    -1,   165,    -1,   142,     7,
      54,    -1,   142,     7,    34,   144,   168,    -1,    56,     7,
      34,   144,   168,    -1,    77,   144,   166,    -1,    77,   144,
     166,    79,   166,    -1,    77,   144,   166,   154,    -1,    77,
     144,   166,   154,    79,   166,    -1,   155,    -1,   154,   155,
      -1,    78,   144,   166,    -1,    80,   144,   167,    -1,    81,
     168,    -1,    82,   168,    -1,    76,   144,   168,    -1,    85,
     144,   168,    -1,    83,   166,   162,    -1,   163,    -1,   162,
     163,    -1,    84,    50,   142,     7,    51,   166,    -1,    86,
     144,    10,   144,    54,    -1,    86,   144,    54,    -1,    87,
     149,    -1,    48,   148,    49,    -1,    48,    49,    -1,    54,
      -1,   166,    -1,    54,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   141,   141,   142,   143,   149,   151,   157,   161,   165,
     171,   178,   185,   189,   190,   191,   192,   196,   200,   208,
     211,   215,   219,   226,   227,   234,   241,   249,   252,   259,
     263,   270,   276,   280,   286,   290,   297,   301,   308,   312,
     320,   323,   327,   328,   335,   342,   346,   353,   354,   355,
     359,   363,   370,   374,   381,   385,   393,   396,   400,   404,
     411,   415,   422,   430,   433,   437,   441,   445,   452,   456,
     460,   467,   471,   478,   482,   489,   493,   501,   504,   511,
     515,   522,   529,   533,   542,   546,   547,   550,   554,   558,
     562,   566,   570,   574,   578,   582,   586,   590,   594,   598,
     602,   606,   610,   614,   618,   622,   626,   630,   634,   638,
     642,   646,   650,   654,   658,   662,   666,   670,   674,   678,
     682,   686,   690,   694,   698,   702,   706,   710,   714,   717,
     721,   727,   728,   729,   730,   731,   735,   739,   748,   752,
     758,   762,   763,   764,   765,   766,   767,   768,   769,   770,
     771,   772,   773,   776,   782,   788,   794,   798,   802,   806,
     812,   813,   819,   825,   831,   837,   843,   849,   855,   861,
     865,   871,   877,   881,   887,   894,   898,   904,   908,   911
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
  "AS", "ABSTRACT", "INTERFACE", "CLASS", "ENUM", "PUBLIC", "PRIVATE",
  "PROTECTED", "STATIC", "NATIVE", "NEW", "DEF", "ARROW", "NAMESPACE",
  "RETURN", "IF", "ELIF", "ELSE", "WHILE", "BREAK", "CONTINUE", "TRY",
  "CATCH", "THROW", "ASSERT_T", "DEFER", "INSTANCEOF", "BOUNDS_EXTENDS",
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
  "field_define", "modifier_type_T", "access_level_T", "ident_list",
  "parameter_list", "argument_list", "typename_group", "typename_list",
  "typename_T", "fqcn_part", "expression", "expression_nobrace", "lhs",
  "primary", "stmt_list", "stmt", "variable_decl_stmt",
  "variable_init_stmt", "inferenced_type_init_stmt", "if_stmt",
  "elif_list", "elif", "while_stmt", "break_stmt", "continue_stmt",
  "return_stmt", "throw_stmt", "try_stmt", "catch_stmt_list", "catch_stmt",
  "assert_stmt", "defer_stmt", "scope", "scope_optional", "stmt_term", 0
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
     345,   346,   347,   348,   349,   350,   351,    60,   352,   353,
     354,   355,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   103,   104,   104,   104,   105,   105,   106,   106,   106,
     107,   108,   109,   109,   109,   109,   109,   110,   110,   111,
     111,   112,   112,   113,   113,   114,   115,   116,   116,   117,
     117,   118,   119,   119,   120,   120,   121,   121,   122,   122,
     123,   123,   124,   124,   125,   126,   126,   127,   127,   127,
     128,   128,   129,   129,   130,   130,   131,   131,   132,   132,
     133,   133,   134,   135,   135,   135,   135,   135,   136,   136,
     136,   137,   137,   138,   138,   139,   139,   140,   140,   141,
     141,   142,   143,   143,   144,   144,   144,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   146,
     146,   147,   147,   147,   147,   147,   147,   147,   148,   148,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   150,   151,   152,   153,   153,   153,   153,
     154,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     162,   163,   164,   164,   165,   166,   166,   167,   167,   168
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     1,     1,     1,     1,
       3,     3,     3,     1,     1,     1,     1,     1,     2,     0,
       1,     1,     3,     1,     2,     2,     2,     0,     3,     1,
       3,     1,     6,     8,     5,     7,     5,     6,     5,     7,
       0,     1,     1,     2,     3,     1,     2,     1,     1,     1,
       7,     6,     5,     4,     1,     1,     0,     1,     8,     7,
      10,     9,     4,     0,     2,     2,     1,     1,     1,     1,
       1,     1,     3,     2,     4,     1,     3,     0,     3,     1,
       3,     2,     1,     3,     3,     1,     1,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     3,     6,     5,     1,     1,     1,     2,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     5,     5,     3,     5,     4,     6,
       1,     2,     3,     3,     2,     2,     3,     3,     3,     1,
       2,     6,     5,     3,     2,     3,     2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,    23,     4,    25,     1,
     133,   134,   131,   132,    82,     0,     0,     0,     0,     0,
       0,   126,   127,   135,   136,   137,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     8,
       9,     0,    77,     0,    86,   128,    85,     7,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
       2,    24,    77,    87,    88,   121,   120,     0,     0,    77,
       0,    21,     0,     0,     0,     0,   179,   164,   165,     0,
       0,     0,     0,   174,     0,     0,     0,   129,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   140,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,    84,     0,     0,     0,     0,    19,    10,
     166,   156,   177,   178,   163,   176,     0,   138,     0,   168,
     169,   167,     0,   173,     0,   153,    83,     0,    79,    77,
      77,    89,    90,    91,    92,    93,   116,   117,    95,    96,
     112,   113,   114,   115,    97,   100,    94,    99,    98,   119,
     118,   123,     0,    75,   101,   102,   103,   104,   105,   106,
     107,   108,   110,   111,   109,     0,     0,     0,     0,     0,
      22,     0,     0,     0,     0,     0,    17,    20,     0,    13,
      14,    16,    15,     0,     0,   158,   160,   175,   139,     0,
     170,     0,     0,     0,    78,    81,   130,     0,   122,   155,
     125,     0,     0,     0,     0,    73,     0,    27,     0,     0,
       0,     0,    18,    11,     0,   157,     0,   161,     0,   172,
     154,    80,    76,   124,     0,     0,     0,     0,     0,    26,
       0,    40,     0,    40,     0,    12,   162,   159,     0,    59,
      74,     0,     0,    40,    31,     0,    29,     0,    68,    69,
      70,     0,    41,    42,     0,     0,     0,    71,     0,     0,
      58,     0,     0,     0,    28,    40,    38,    43,    63,    40,
      34,     0,    36,   171,    40,    32,    30,     0,    66,    67,
      63,    44,    45,    47,    48,    49,     0,     0,    72,    37,
       0,    39,    64,    65,     0,     0,    46,     0,    35,    33,
       0,    27,     0,    56,     0,     0,    62,     0,    57,     0,
      56,     0,    55,    54,     0,    51,     0,     0,     0,     0,
      50,     0,     0,    53,     0,     0,     0,    52,    61,     0,
      60
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    38,    39,   129,   196,   197,   198,    72,
       5,     6,   228,   249,   265,   266,   199,   200,   201,   202,
     271,   272,   273,   301,   302,   303,   328,   334,   329,    40,
     304,   305,   306,   274,   278,   188,   172,    87,   147,    41,
      62,    43,    44,    45,    46,   136,    47,    48,    49,    50,
      51,   205,   206,    52,    53,    54,    55,    56,    57,   139,
     140,    58,    59,   133,   134,    77
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -282
static const yytype_int16 yypact[] =
{
     360,   -64,    37,   273,   445,     5,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,  -282,   211,   211,   211,   211,   211,
      45,  -282,  -282,  -282,  -282,  -282,    48,    56,    60,   211,
     211,   211,    78,    78,    21,   211,   211,   649,  -282,  -282,
    -282,   142,   118,   725,   106,   726,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,
    -282,  -282,   118,    97,    97,    97,    97,   769,   129,   118,
     131,  -282,    22,   725,   813,   376,  -282,  -282,  -282,   530,
      92,   725,   461,  -282,   -14,   172,    48,   181,   187,   211,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,    48,    48,  -282,
    1050,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,  -282,  -282,   211,   154,    11,   202,    87,  -282,
    -282,   119,  -282,  -282,  -282,  -282,   615,  -282,   178,    92,
    -282,  -282,   211,  -282,   211,  -282,  -282,    -5,  -282,   118,
     185,    41,    41,     2,     2,     2,   624,   624,   941,   941,
      65,    65,    65,    65,   176,   985,  1025,   546,   282,  -282,
    -282,  -282,     0,   901,   901,   901,   901,   901,   901,   901,
     901,   901,   901,   901,   901,   725,  1075,   152,     8,   232,
    -282,   175,   235,   235,   241,    60,  -282,    87,   204,  -282,
    -282,  -282,  -282,   211,    21,   133,  -282,  -282,  -282,    48,
    -282,   857,   725,    48,  -282,  -282,  -282,   211,  -282,  -282,
    -282,    24,    48,    48,   177,  -282,   235,   203,   121,   132,
     206,    22,  -282,  -282,   813,  -282,    21,  -282,   249,  -282,
    -282,  -282,   901,  -282,   112,   250,    48,   138,   251,  -282,
      48,   167,    48,   167,   253,  -282,  -282,  -282,   212,  -282,
    -282,   112,    48,   167,  -282,    12,  -282,   117,  -282,  -282,
    -282,   216,   167,  -282,   256,   126,   225,  -282,    -6,    21,
    -282,   130,   226,   251,  -282,   167,  -282,  -282,   160,   167,
    -282,    28,  -282,  -282,   167,  -282,  -282,   233,   210,   214,
     174,     1,  -282,  -282,  -282,  -282,    48,   236,  -282,  -282,
     239,  -282,  -282,  -282,   242,   286,  -282,   293,  -282,  -282,
      15,   203,   257,   279,    33,   254,  -282,   164,  -282,   112,
     279,    17,  -282,  -282,   255,  -282,   112,   238,   110,  1124,
    -282,    48,   240,  -282,   113,   112,    48,  -282,  -282,   112,
    -282
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -282,  -282,  -282,   306,  -282,    82,   122,  -282,  -282,   120,
    -282,   311,   -39,    -1,  -282,    35,  -282,  -282,  -282,  -282,
    -117,  -282,    49,  -282,    23,  -282,  -282,  -282,    -8,  -282,
    -282,  -282,    25,  -282,  -282,  -281,  -184,   -25,  -105,   -79,
      -3,    -4,  -282,  -282,  -282,  -282,   -18,  -282,  -282,  -282,
    -282,  -282,   134,  -282,  -282,  -282,  -282,  -282,  -282,  -282,
     188,  -282,  -282,   -29,  -208,   -27
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -82
static const yytype_int16 yytable[] =
{
      42,    42,   221,   291,   213,    80,    78,   148,   -63,   217,
      88,    63,    64,    65,    66,    67,   109,   223,    14,    83,
     144,   283,    14,    69,    14,    73,    74,    75,   169,   170,
     127,    81,    82,   217,    42,   308,   259,   122,     7,   324,
     145,     8,   223,   292,   125,   131,   130,   189,   214,    88,
     338,   218,    68,   280,   141,    14,    91,    92,    93,   224,
       2,   137,   187,    70,   107,   284,   323,    71,   337,    79,
     128,   298,   299,    88,   300,   243,    42,   309,    89,    90,
      91,    92,    93,   149,   330,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   107,   149,   149,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   208,   223,
     185,   335,   217,   149,   215,   216,   213,   107,   340,    85,
     238,   250,    76,    42,   241,   213,   276,   348,   211,   213,
     212,   350,   252,   244,   245,   267,   282,   275,   262,    84,
     191,   192,   193,   194,   229,   344,   110,   281,   219,   107,
      79,   342,   195,   124,   347,   285,   132,   261,   297,   251,
      86,   148,   307,   148,   289,   235,   138,   310,   294,   146,
     253,   126,   173,   148,    88,   240,   263,   247,   -81,    89,
      90,    91,    92,    93,   150,    94,    95,   203,   204,   234,
      98,    99,   100,   101,   186,   256,   149,   257,   104,   190,
     149,   203,   236,   242,    10,    11,    12,    13,    14,   149,
     149,   332,   333,   106,    15,    16,   222,   317,   209,    17,
     298,   299,    18,   300,   268,   269,   270,    86,   107,   225,
     226,   189,   227,   149,   298,   299,   314,   149,   230,   149,
     293,   246,   189,   233,   254,   248,   258,   260,   264,   149,
     277,    19,   345,   279,   108,   286,   288,   349,    21,    22,
      23,    24,    25,     9,   290,   295,    10,    11,    12,    13,
      14,   312,   311,    26,   313,   318,    15,    16,   319,   327,
      88,    17,   320,   321,    18,    89,    90,    91,    92,    93,
     322,    94,    95,   149,   331,   339,    98,    99,   100,   101,
      60,   326,   341,   255,   346,   231,    61,   149,   296,   232,
     325,   287,   336,    19,   316,   315,     0,   210,   149,    20,
      21,    22,    23,    24,    25,   173,     0,     0,   149,   237,
       0,     0,     0,   149,   107,    26,    27,     0,    28,    29,
      30,     0,     0,    31,    32,    33,    34,     0,    35,    36,
      37,     1,     0,    -5,    -5,    -5,    -5,    -5,     0,     0,
     108,     0,     0,    -5,    -5,     0,     0,     0,    -5,     0,
       0,    -5,     0,     0,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,     0,    94,    95,     0,    96,    97,
      98,    99,   100,   101,     0,     0,   102,   103,   104,   105,
      -5,     0,     0,     0,     0,     2,    -5,    -5,    -5,    -5,
      -5,    -5,     0,   106,    79,     0,     0,     0,     0,     0,
     132,     0,    -5,    -5,     0,    -5,    -5,    -5,   107,     0,
      -5,    -5,    -5,    -5,     0,    -5,    -5,    -5,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,    15,    16,
       0,     0,     0,    17,   108,     0,    18,     0,     0,    88,
       0,   142,     0,     0,    89,    90,    91,    92,    93,     0,
      94,    95,     0,    96,    97,    98,    99,   100,   101,     0,
       0,   102,   103,   104,   105,    19,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,     0,   106,     0,
       0,     0,     0,     0,     0,   143,     0,    26,    27,     0,
      28,    29,    30,   107,     0,    31,    32,    33,    34,     0,
      35,    36,    37,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,    15,    16,     0,     0,     0,    17,   108,
       0,    18,     0,     0,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,     0,    94,    95,     0,     0,     0,
      98,    99,   100,   101,     0,     0,   102,   103,   104,   135,
      19,     0,     0,     0,     0,     0,    20,    21,    22,    23,
      24,    25,     0,   106,     0,     0,     0,     0,     0,     0,
       0,     0,    26,     0,     0,     0,    29,    30,   107,     0,
      31,    32,    33,    34,     0,    35,    36,    37,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,    15,    16,
       0,     0,    88,    17,   108,     0,    18,    89,    90,    91,
      92,    93,     0,     0,     0,     0,     0,     0,    98,    99,
     100,   101,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,    15,    16,   207,    19,     0,    17,     0,     0,
      18,    20,    21,    22,    23,    24,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   107,    26,     0,     0,
       0,    29,    30,     0,     0,    31,    32,    33,    34,    19,
      35,    36,    37,     0,     0,    20,    21,    22,    23,    24,
      25,     0,   108,     0,     0,     0,     0,     0,     0,     0,
       0,    26,     0,     0,     0,    29,    30,     0,     0,    31,
      32,    33,    34,    88,    35,    36,    37,     0,    89,    90,
      91,    92,    93,     0,    94,    95,     0,    96,    97,    98,
      99,   100,   101,     0,     0,   102,   103,   104,   105,     0,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,     0,   106,     0,     0,     0,     0,    88,     0,    76,
       0,     0,    89,    90,    91,    92,    93,   107,    94,    95,
       0,    96,    97,    98,    99,   100,   101,     0,     0,   102,
     103,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,     0,     0,   106,     0,     0,     0,
     123,    88,     0,     0,     0,     0,    89,    90,    91,    92,
      93,   107,    94,    95,     0,    96,    97,    98,    99,   100,
     101,     0,     0,   102,   103,   104,   105,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,     0,     0,
     106,    79,     0,     0,     0,    88,     0,     0,     0,     0,
      89,    90,    91,    92,    93,   107,    94,    95,     0,    96,
      97,    98,    99,   100,   101,     0,     0,   102,   103,   104,
     105,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,     0,     0,   106,     0,     0,     0,     0,    88,
       0,   239,     0,     0,    89,    90,    91,    92,    93,   107,
      94,    95,     0,    96,    97,    98,    99,   100,   101,     0,
       0,   102,   103,   104,   105,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,     0,     0,   106,    88,
       0,     0,     0,     0,    89,    90,    91,    92,    93,     0,
      94,    95,     0,   107,     0,    98,    99,   100,   101,     0,
       0,   102,   103,   104,   105,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   106,   108,
       0,     0,     0,    88,     0,     0,     0,     0,    89,    90,
      91,    92,    93,   107,    94,    95,     0,     0,     0,    98,
      99,   100,   101,     0,     0,   102,     0,   104,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
       0,     0,   106,    88,     0,     0,     0,     0,    89,    90,
      91,    92,    93,     0,    94,    95,     0,   107,     0,    98,
      99,   100,   101,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,    15,    16,     0,     0,     0,    17,     0,
       0,    18,   106,   108,     0,     0,     0,     0,    10,    11,
      12,    13,    14,     0,     0,     0,     0,   107,    15,    16,
       0,     0,     0,    17,     0,     0,    18,     0,     0,     0,
      19,   171,     0,     0,     0,     0,     0,    21,    22,    23,
      24,    25,     0,   108,     0,     0,     0,     0,     0,     0,
       0,     0,    26,     0,     0,    19,   220,    10,    11,    12,
      13,    14,    21,    22,    23,    24,    25,    15,    16,     0,
       0,     0,    17,     0,     0,    18,     0,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    19,   343,     0,     0,     0,     0,
       0,    21,    22,    23,    24,    25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26
};

static const yytype_int16 yycheck[] =
{
       3,     4,   186,     9,     9,    34,    33,    86,     7,     9,
       8,    15,    16,    17,    18,    19,    43,     9,     7,    37,
      34,     9,     7,    26,     7,    29,    30,    31,   107,   108,
       8,    35,    36,     9,    37,     7,   244,    62,   102,   320,
      54,     4,     9,    49,    69,    74,    73,   126,    53,     8,
     331,    51,     7,   261,    81,     7,    15,    16,    17,    51,
      55,    79,    51,     7,    62,    53,    51,     7,    51,    48,
      48,    70,    71,     8,    73,    51,    79,    49,    13,    14,
      15,    16,    17,    86,    51,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,    62,   107,   108,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   136,     9,
     124,   329,     9,   126,   149,   150,     9,    62,   336,    11,
     209,    10,    54,   136,   213,     9,   253,   345,   142,     9,
     144,   349,    10,   222,   223,   250,   263,   252,    10,     7,
      63,    64,    65,    66,   193,   339,    50,   262,   185,    62,
      48,    51,    75,    34,    51,    48,    54,   246,   285,    48,
      52,   250,   289,   252,    48,   204,    84,   294,    48,     7,
      48,    50,   186,   262,     8,   212,    48,   226,     7,    13,
      14,    15,    16,    17,     7,    19,    20,    78,    79,   203,
      24,    25,    26,    27,    50,   234,   209,   236,    32,     7,
     213,    78,    79,   217,     3,     4,     5,     6,     7,   222,
     223,    57,    58,    47,    13,    14,    74,   306,    50,    18,
      70,    71,    21,    73,    67,    68,    69,    52,    62,     7,
      65,   320,     7,   246,    70,    71,    72,   250,     7,   252,
     279,    74,   331,    49,    48,    52,     7,     7,     7,   262,
       7,    50,   341,    51,    88,    49,    10,   346,    57,    58,
      59,    60,    61,     0,    49,    49,     3,     4,     5,     6,
       7,    71,    49,    72,    70,    49,    13,    14,    49,    10,
       8,    18,    50,     7,    21,    13,    14,    15,    16,    17,
       7,    19,    20,   306,    50,    50,    24,    25,    26,    27,
       4,    54,    74,   231,    74,   195,     5,   320,   283,   197,
     321,   272,   330,    50,   301,   300,    -1,   139,   331,    56,
      57,    58,    59,    60,    61,   339,    -1,    -1,   341,   205,
      -1,    -1,    -1,   346,    62,    72,    73,    -1,    75,    76,
      77,    -1,    -1,    80,    81,    82,    83,    -1,    85,    86,
      87,     1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      88,    -1,    -1,    13,    14,    -1,    -1,    -1,    18,    -1,
      -1,    21,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      50,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    61,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    72,    73,    -1,    75,    76,    77,    62,    -1,
      80,    81,    82,    83,    -1,    85,    86,    87,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,
      -1,    -1,    -1,    18,    88,    -1,    21,    -1,    -1,     8,
      -1,    10,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    50,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    72,    73,    -1,
      75,    76,    77,    62,    -1,    80,    81,    82,    83,    -1,
      85,    86,    87,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    13,    14,    -1,    -1,    -1,    18,    88,
      -1,    21,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    -1,    -1,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    49,
      50,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    -1,    -1,    76,    77,    62,    -1,
      80,    81,    82,    83,    -1,    85,    86,    87,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,
      -1,    -1,     8,    18,    88,    -1,    21,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,
      26,    27,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    13,    14,    49,    50,    -1,    18,    -1,    -1,
      21,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    72,    -1,    -1,
      -1,    76,    77,    -1,    -1,    80,    81,    82,    83,    50,
      85,    86,    87,    -1,    -1,    56,    57,    58,    59,    60,
      61,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    -1,    -1,    -1,    76,    77,    -1,    -1,    80,
      81,    82,    83,     8,    85,    86,    87,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    47,    -1,    -1,    -1,    -1,     8,    -1,    54,
      -1,    -1,    13,    14,    15,    16,    17,    62,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    47,    -1,    -1,    -1,
      51,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    62,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      47,    48,    -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    62,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    47,    -1,    -1,    -1,    -1,     8,
      -1,    54,    -1,    -1,    13,    14,    15,    16,    17,    62,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    47,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    -1,    62,    -1,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    88,
      -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    62,    19,    20,    -1,    -1,    -1,    24,
      25,    26,    27,    -1,    -1,    30,    -1,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    47,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    -1,    62,    -1,    24,
      25,    26,    27,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    13,    14,    -1,    -1,    -1,    18,    -1,
      -1,    21,    47,    88,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    62,    13,    14,
      -1,    -1,    -1,    18,    -1,    -1,    21,    -1,    -1,    -1,
      50,    51,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    61,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    -1,    50,    51,     3,     4,     5,
       6,     7,    57,    58,    59,    60,    61,    13,    14,    -1,
      -1,    -1,    18,    -1,    -1,    21,    -1,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,
      -1,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    55,   104,   105,   113,   114,   102,     4,     0,
       3,     4,     5,     6,     7,    13,    14,    18,    21,    50,
      56,    57,    58,    59,    60,    61,    72,    73,    75,    76,
      77,    80,    81,    82,    83,    85,    86,    87,   106,   107,
     132,   142,   143,   144,   145,   146,   147,   149,   150,   151,
     152,   153,   156,   157,   158,   159,   160,   161,   164,   165,
     106,   114,   143,   144,   144,   144,   144,   144,     7,   143,
       7,     7,   112,   144,   144,   144,    54,   168,   168,    48,
     166,   144,   144,   149,     7,    11,    52,   140,     8,    13,
      14,    15,    16,    17,    19,    20,    22,    23,    24,    25,
      26,    27,    30,    31,    32,    33,    47,    62,    88,   168,
      50,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,   140,    51,    34,   140,    50,     8,    48,   108,
     168,   166,    54,   166,   167,    49,   148,   149,    84,   162,
     163,   168,    10,    54,    34,    54,     7,   141,   142,   143,
       7,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   142,
     142,    51,   139,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,    50,    51,   138,   142,
       7,    63,    64,    65,    66,    75,   109,   110,   111,   119,
     120,   121,   122,    78,    79,   154,   155,    49,   149,    50,
     163,   144,   144,     9,    53,   140,   140,     9,    51,   168,
      51,   139,    74,     9,    51,     7,    65,     7,   115,   115,
       7,   112,   109,    49,   144,   166,    79,   155,   142,    54,
     168,   142,   144,    51,   142,   142,    74,   115,    52,   116,
      10,    48,    10,    48,    48,   108,   166,   166,     7,   167,
       7,   142,    10,    48,     7,   117,   118,   141,    67,    68,
      69,   123,   124,   125,   136,   141,   123,     7,   137,    51,
     167,   141,   123,     9,    53,    48,    49,   125,    10,    48,
      49,     9,    49,   166,    48,    49,   118,   123,    70,    71,
      73,   126,   127,   128,   133,   134,   135,   123,     7,    49,
     123,    49,    71,    70,    72,   135,   127,   142,    49,    49,
      50,     7,     7,    51,   138,   116,    54,    10,   129,   131,
      51,    50,    57,    58,   130,   167,   131,    51,   138,    50,
     167,    74,    51,    51,   139,   142,    74,    51,   167,   142,
     167
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
#line 144 "beacon.y"
    {
		yyclearin;
	;}
    break;

  case 6:
#line 152 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 7:
#line 158 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 8:
#line 162 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 9:
#line 166 "beacon.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 10:
#line 172 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 11:
#line 179 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value)
	;}
    break;

  case 12:
#line 186 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 17:
#line 197 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 18:
#line 201 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 19:
#line 208 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 21:
#line 216 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 22:
#line 220 "beacon.y"
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 24:
#line 228 "beacon.y"
    {
		(yyval.ast_value) = ast_new_import_decl_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 25:
#line 235 "beacon.y"
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 26:
#line 242 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameterized_typename((yyvsp[(1) - (2)].string_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 27:
#line 249 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 28:
#line 253 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 29:
#line 260 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 30:
#line 264 "beacon.y"
    {
		(yyval.ast_value) = ast_new_type_parameter_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 31:
#line 271 "beacon.y"
    {
		(yyval.ast_value) = ast_new_type_parameter((yyvsp[(1) - (1)].string_value), ast_new_blank());
	;}
    break;

  case 32:
#line 277 "beacon.y"
    {
		(yyval.ast_value) = ast_new_abstract_class_decl((yyvsp[(3) - (6)].ast_value), ast_new_blank(), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 33:
#line 281 "beacon.y"
    {
		(yyval.ast_value) = ast_new_abstract_class_decl((yyvsp[(3) - (8)].ast_value), (yyvsp[(5) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 34:
#line 287 "beacon.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 35:
#line 291 "beacon.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 36:
#line 298 "beacon.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 37:
#line 302 "beacon.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (6)].string_value), (yyvsp[(4) - (6)].ast_value));
	;}
    break;

  case 38:
#line 309 "beacon.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 39:
#line 313 "beacon.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 40:
#line 320 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 43:
#line 329 "beacon.y"
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 44:
#line 336 "beacon.y"
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[(1) - (3)].access_level_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 45:
#line 343 "beacon.y"
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 46:
#line 347 "beacon.y"
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[(1) - (2)].ast_value), ast_new_member_decl((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 50:
#line 360 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 51:
#line 364 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 52:
#line 371 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (5)].chain_type_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 53:
#line 375 "beacon.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (4)].chain_type_value), ast_new_blank());
	;}
    break;

  case 54:
#line 382 "beacon.y"
    {
		(yyval.chain_type_value) = chain_type_super;
	;}
    break;

  case 55:
#line 386 "beacon.y"
    {
		(yyval.chain_type_value) = chain_type_this;
	;}
    break;

  case 56:
#line 393 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 58:
#line 401 "beacon.y"
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[(2) - (8)].string_value), (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 59:
#line 405 "beacon.y"
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[(2) - (7)].string_value), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 60:
#line 412 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl((yyvsp[(2) - (10)].modifier_type_value), (yyvsp[(3) - (10)].string_value), (yyvsp[(4) - (10)].ast_value), (yyvsp[(6) - (10)].ast_value), (yyvsp[(10) - (10)].ast_value), (yyvsp[(9) - (10)].ast_value));
	;}
    break;

  case 61:
#line 416 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[(2) - (9)].modifier_type_value), (yyvsp[(3) - (9)].string_value), (yyvsp[(4) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 62:
#line 423 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[(1) - (4)].modifier_type_value), (yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].string_value));
	;}
    break;

  case 63:
#line 430 "beacon.y"
    {
		(yyval.modifier_type_value) = modifier_none;
	;}
    break;

  case 64:
#line 434 "beacon.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 65:
#line 438 "beacon.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 66:
#line 442 "beacon.y"
    {
		(yyval.modifier_type_value) = modifier_static;
	;}
    break;

  case 67:
#line 446 "beacon.y"
    {
		(yyval.modifier_type_value) = modifier_native;
	;}
    break;

  case 68:
#line 453 "beacon.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 69:
#line 457 "beacon.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 70:
#line 461 "beacon.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 71:
#line 468 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 72:
#line 472 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[(3) - (3)].string_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 73:
#line 479 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].string_value));
	;}
    break;

  case 74:
#line 483 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].string_value), (yyvsp[(1) - (4)].ast_value))
	;}
    break;

  case 75:
#line 490 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 76:
#line 494 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(3) - (3)].ast_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 77:
#line 501 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 78:
#line 505 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 79:
#line 512 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 80:
#line 516 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 81:
#line 523 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 82:
#line 530 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 83:
#line 534 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(3) - (3)].string_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 84:
#line 543 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 87:
#line 551 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_pos, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 88:
#line 555 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_neg, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 89:
#line 559 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 90:
#line 563 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 91:
#line 567 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 92:
#line 571 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 93:
#line 575 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 94:
#line 579 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 95:
#line 583 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_equal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 96:
#line 587 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_notequal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 97:
#line 591 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 98:
#line 595 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 99:
#line 599 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 100:
#line 603 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 101:
#line 607 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 102:
#line 611 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 103:
#line 615 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 104:
#line 619 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 105:
#line 623 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 106:
#line 627 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 107:
#line 631 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_and_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 108:
#line 635 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 109:
#line 639 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 110:
#line 643 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 111:
#line 647 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 112:
#line 651 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_gt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 113:
#line 655 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_ge, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 114:
#line 659 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 115:
#line 663 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_le, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 116:
#line 667 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 117:
#line 671 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 118:
#line 675 "beacon.y"
    {
		(yyval.ast_value) = ast_new_instanceof((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 119:
#line 679 "beacon.y"
    {
		(yyval.ast_value) = ast_new_as((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 120:
#line 683 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_childa, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 121:
#line 687 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_not, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 122:
#line 691 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 123:
#line 695 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 124:
#line 699 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 125:
#line 703 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), ast_new_blank());
	;}
    break;

  case 126:
#line 707 "beacon.y"
    {
		(yyval.ast_value) = ast_new_this();
	;}
    break;

  case 127:
#line 711 "beacon.y"
    {
		(yyval.ast_value) = ast_new_super();
	;}
    break;

  case 129:
#line 718 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 130:
#line 722 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].string_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 135:
#line 732 "beacon.y"
    {
		(yyval.ast_value) = ast_new_true();
	;}
    break;

  case 136:
#line 736 "beacon.y"
    {
		(yyval.ast_value) = ast_new_false();
	;}
    break;

  case 137:
#line 740 "beacon.y"
    {
		(yyval.ast_value) = ast_new_null();
	;}
    break;

  case 138:
#line 749 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 139:
#line 753 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 140:
#line 759 "beacon.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 153:
#line 777 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].string_value));
	;}
    break;

  case 154:
#line 783 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 155:
#line 789 "beacon.y"
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 156:
#line 795 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 157:
#line 799 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 158:
#line 803 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 159:
#line 807 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 161:
#line 814 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 162:
#line 820 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 163:
#line 826 "beacon.y"
    {
		(yyval.ast_value) = ast_new_while((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 164:
#line 832 "beacon.y"
    {
		(yyval.ast_value) = ast_new_break();
	;}
    break;

  case 165:
#line 838 "beacon.y"
    {
		(yyval.ast_value) = ast_new_continue();
	;}
    break;

  case 166:
#line 844 "beacon.y"
    {
		(yyval.ast_value) = ast_new_return((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 167:
#line 850 "beacon.y"
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 168:
#line 856 "beacon.y"
    {
		(yyval.ast_value) = ast_new_try((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 169:
#line 862 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 170:
#line 866 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 171:
#line 872 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].string_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 172:
#line 878 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (5)].ast_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 173:
#line 882 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 174:
#line 888 "beacon.y"
    {
		(yyval.ast_value) = ast_new_defer((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 175:
#line 895 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 176:
#line 899 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 177:
#line 905 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3072 "beacon.tab.c"
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


#line 913 "beacon.y"





