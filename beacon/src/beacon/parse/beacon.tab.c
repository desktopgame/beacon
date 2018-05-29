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
	access_level access_level_value;
}
/* Line 193 of yacc.c.  */
#line 320 "beacon.tab.c"
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
#line 345 "beacon.tab.c"

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
#define YYLAST   1239

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  103
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  182
/* YYNRULES -- Number of states.  */
#define YYNSTATES  367

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
     209,   220,   230,   240,   249,   254,   258,   260,   263,   265,
     267,   269,   271,   273,   275,   277,   281,   284,   289,   291,
     295,   296,   300,   302,   306,   309,   311,   315,   319,   321,
     323,   326,   329,   333,   337,   341,   345,   349,   353,   357,
     361,   365,   369,   373,   377,   381,   385,   389,   393,   397,
     401,   405,   409,   413,   417,   421,   425,   429,   433,   437,
     441,   445,   449,   453,   456,   459,   464,   468,   475,   481,
     483,   485,   487,   490,   495,   497,   499,   501,   503,   505,
     507,   509,   511,   514,   517,   519,   521,   523,   525,   527,
     529,   531,   533,   535,   537,   539,   541,   545,   551,   557,
     561,   567,   572,   579,   581,   584,   588,   592,   595,   598,
     602,   606,   610,   612,   615,   622,   628,   632,   635,   639,
     642,   644,   646
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     104,     0,    -1,   105,   106,    -1,   104,   106,    -1,     1,
     102,    -1,    -1,   113,    -1,   150,    -1,   107,    -1,   132,
      -1,    75,   112,   108,    -1,    48,   111,    49,    -1,    75,
     112,   108,    -1,   119,    -1,   120,    -1,   122,    -1,   121,
      -1,   109,    -1,   110,   109,    -1,    -1,   110,    -1,     7,
      -1,   112,     8,     7,    -1,   114,    -1,   113,   114,    -1,
      55,     4,    -1,     7,   116,    -1,    -1,    52,   117,    53,
      -1,   118,    -1,   117,     9,   118,    -1,     7,    -1,    63,
      65,   115,    48,   123,    49,    -1,    63,    65,   115,    10,
     142,    48,   123,    49,    -1,    65,   115,    48,   123,    49,
      -1,    65,   115,    10,   142,    48,   123,    49,    -1,    66,
       7,    48,   138,    49,    -1,    66,     7,    48,   138,     9,
      49,    -1,    64,   115,    48,   123,    49,    -1,    64,   115,
      10,   142,    48,   123,    49,    -1,    -1,   124,    -1,   125,
      -1,   124,   125,    -1,   137,    10,   126,    -1,   127,    -1,
     126,   127,    -1,   128,    -1,   133,    -1,   134,    -1,    73,
      72,    50,   139,    51,   131,   168,    -1,    73,    72,    50,
      51,   131,   168,    -1,    10,   130,    50,   140,    51,    -1,
      10,   130,    50,    51,    -1,    58,    -1,    57,    -1,    -1,
     129,    -1,    73,     7,    50,   139,    51,    74,   143,   168,
      -1,    73,     7,    50,    51,    74,   143,   168,    -1,    73,
     135,     7,   116,    50,   139,    51,    74,   143,   168,    -1,
      73,   135,     7,   116,    50,    51,    74,   143,   168,    -1,
      73,     7,   116,    50,   139,    51,    74,   143,   168,    -1,
      73,     7,   116,    50,    51,    74,   143,   168,    -1,   136,
     143,     7,    54,    -1,   143,     7,    54,    -1,   136,    -1,
     135,   136,    -1,    70,    -1,    71,    -1,    63,    -1,    67,
      -1,    68,    -1,    69,    -1,     7,    -1,   138,     9,     7,
      -1,   143,     7,    -1,   139,     9,   143,     7,    -1,   145,
      -1,   140,     9,   145,    -1,    -1,    52,   142,    53,    -1,
     143,    -1,   142,     9,   143,    -1,   144,   141,    -1,     7,
      -1,   144,    11,     7,    -1,    50,   145,    51,    -1,   148,
      -1,   146,    -1,    13,   145,    -1,    14,   145,    -1,   145,
      13,   145,    -1,   145,    14,   145,    -1,   145,    15,   145,
      -1,   145,    16,   145,    -1,   145,    17,   145,    -1,   145,
      32,   145,    -1,   145,    22,   145,    -1,   145,    23,   145,
      -1,   145,    30,   145,    -1,   145,    47,   145,    -1,   145,
      33,   145,    -1,   145,    31,   145,    -1,   147,    34,   145,
      -1,   147,    35,   145,    -1,   147,    36,   145,    -1,   147,
      37,   145,    -1,   147,    38,   145,    -1,   147,    39,   145,
      -1,   147,    40,   145,    -1,   147,    41,   145,    -1,   147,
      44,   145,    -1,   147,    42,   145,    -1,   147,    43,   145,
      -1,   145,    24,   145,    -1,   145,    25,   145,    -1,   145,
      26,   145,    -1,   145,    27,   145,    -1,   145,    19,   145,
      -1,   145,    20,   145,    -1,   145,    88,   143,    -1,   145,
      62,   143,    -1,    21,   145,    -1,    18,   145,    -1,   146,
      50,   140,    51,    -1,   146,    50,    51,    -1,    72,   144,
     141,    50,   140,    51,    -1,    72,   144,   141,    50,    51,
      -1,    57,    -1,    58,    -1,   147,    -1,   144,   141,    -1,
     145,     8,     7,   141,    -1,     5,    -1,     6,    -1,     3,
      -1,     4,    -1,    59,    -1,    60,    -1,    61,    -1,   150,
      -1,   149,   150,    -1,   145,   169,    -1,   151,    -1,   152,
      -1,   153,    -1,   154,    -1,   157,    -1,   158,    -1,   159,
      -1,   160,    -1,   161,    -1,   162,    -1,   165,    -1,   166,
      -1,   143,     7,    54,    -1,   143,     7,    34,   145,   169,
      -1,    56,     7,    34,   145,   169,    -1,    77,   145,   167,
      -1,    77,   145,   167,    79,   167,    -1,    77,   145,   167,
     155,    -1,    77,   145,   167,   155,    79,   167,    -1,   156,
      -1,   155,   156,    -1,    78,   145,   167,    -1,    80,   145,
     168,    -1,    81,   169,    -1,    82,   169,    -1,    76,   145,
     169,    -1,    85,   145,   169,    -1,    83,   167,   163,    -1,
     164,    -1,   163,   164,    -1,    84,    50,   143,     7,    51,
     167,    -1,    86,   145,    10,   145,    54,    -1,    86,   145,
      54,    -1,    87,   150,    -1,    48,   149,    49,    -1,    48,
      49,    -1,    54,    -1,   167,    -1,    54,    -1
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
     411,   415,   419,   423,   430,   434,   441,   445,   452,   456,
     460,   467,   471,   475,   482,   486,   493,   497,   504,   508,
     516,   519,   526,   530,   537,   544,   548,   557,   561,   562,
     565,   569,   573,   577,   581,   585,   589,   593,   597,   601,
     605,   609,   613,   617,   621,   625,   629,   633,   637,   641,
     645,   649,   653,   657,   661,   665,   669,   673,   677,   681,
     685,   689,   693,   697,   701,   705,   709,   713,   717,   721,
     725,   729,   732,   736,   742,   743,   744,   745,   746,   750,
     754,   763,   767,   773,   777,   778,   779,   780,   781,   782,
     783,   784,   785,   786,   787,   788,   791,   797,   803,   809,
     813,   817,   821,   827,   828,   834,   840,   846,   852,   858,
     864,   870,   876,   880,   886,   892,   896,   902,   909,   913,
     919,   923,   926
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
  "field_define", "modifier_type_T_list", "modifier_type_T",
  "access_level_T", "ident_list", "parameter_list", "argument_list",
  "typename_group", "typename_list", "typename_T", "fqcn_part",
  "expression", "expression_nobrace", "lhs", "primary", "stmt_list",
  "stmt", "variable_decl_stmt", "variable_init_stmt",
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
     133,   133,   133,   133,   134,   134,   135,   135,   136,   136,
     136,   137,   137,   137,   138,   138,   139,   139,   140,   140,
     141,   141,   142,   142,   143,   144,   144,   145,   145,   145,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   147,   147,   148,   148,   148,   148,   148,   148,
     148,   149,   149,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   151,   152,   153,   154,
     154,   154,   154,   155,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   163,   164,   165,   165,   166,   167,   167,
     168,   168,   169
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
      10,     9,     9,     8,     4,     3,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     4,     1,     3,
       0,     3,     1,     3,     2,     1,     3,     3,     1,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     4,     3,     6,     5,     1,
       1,     1,     2,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     5,     5,     3,
       5,     4,     6,     1,     2,     3,     3,     2,     2,     3,
       3,     3,     1,     2,     6,     5,     3,     2,     3,     2,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,    23,     4,    25,     1,
     136,   137,   134,   135,    85,     0,     0,     0,     0,     0,
       0,   129,   130,   138,   139,   140,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     8,
       9,     0,    80,     0,    89,   131,    88,     7,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
       2,    24,    80,    90,    91,   124,   123,     0,     0,    80,
       0,    21,     0,     0,     0,     0,   182,   167,   168,     0,
       0,     0,     0,   177,     0,     0,     0,   132,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   143,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   132,    87,     0,     0,     0,     0,    19,    10,
     169,   159,   180,   181,   166,   179,     0,   141,     0,   171,
     172,   170,     0,   176,     0,   156,    86,     0,    82,    80,
      80,    92,    93,    94,    95,    96,   119,   120,    98,    99,
     115,   116,   117,   118,   100,   103,    97,   102,   101,   122,
     121,   126,     0,    78,   104,   105,   106,   107,   108,   109,
     110,   111,   113,   114,   112,     0,     0,     0,     0,     0,
      22,     0,     0,     0,     0,     0,    17,    20,     0,    13,
      14,    16,    15,     0,     0,   161,   163,   178,   142,     0,
     173,     0,     0,     0,    81,    84,   133,     0,   125,   158,
     128,     0,     0,     0,     0,    76,     0,    27,     0,     0,
       0,     0,    18,    11,     0,   160,     0,   164,     0,   175,
     157,    83,    79,   127,     0,     0,     0,     0,     0,    26,
       0,    40,     0,    40,     0,    12,   165,   162,     0,    59,
      77,     0,     0,    40,    31,     0,    29,     0,    71,    72,
      73,     0,    41,    42,     0,     0,     0,    74,     0,     0,
      58,     0,     0,     0,    28,    40,    38,    43,     0,    40,
      34,     0,    36,   174,    40,    32,    30,     0,    70,    68,
      69,     0,    44,    45,    47,    48,    49,     0,     0,     0,
      75,    37,     0,    39,    27,     0,     0,    66,    46,     0,
       0,    35,    33,     0,     0,    27,    67,     0,    65,     0,
      56,     0,     0,    64,     0,     0,     0,    57,     0,    56,
       0,     0,     0,    55,    54,     0,    51,     0,     0,     0,
       0,     0,     0,    50,     0,     0,    63,     0,    53,     0,
       0,     0,    62,    52,    61,     0,    60
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    38,    39,   129,   196,   197,   198,    72,
       5,     6,   228,   249,   265,   266,   199,   200,   201,   202,
     271,   272,   273,   302,   303,   304,   337,   345,   338,    40,
     305,   306,   316,   307,   274,   278,   188,   172,    87,   147,
      41,    62,    43,    44,    45,    46,   136,    47,    48,    49,
      50,    51,   205,   206,    52,    53,    54,    55,    56,    57,
     139,   140,    58,    59,   133,   134,    77
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -305
static const yytype_int16 yypact[] =
{
     370,   -87,    71,   336,   455,   -10,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  1167,  1167,  1167,  1167,  1167,
     105,  -305,  -305,  -305,  -305,  -305,   118,   181,   183,  1167,
    1167,  1167,   141,   141,   144,  1167,  1167,   659,  -305,  -305,
    -305,   211,    29,   783,   191,   325,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,    29,   174,   174,   174,   174,   827,   197,    29,
     192,  -305,    -1,   783,   871,   471,  -305,  -305,  -305,   540,
     160,   783,   739,  -305,   153,   244,   118,   246,   248,  1167,
    1167,  1167,  1167,  1167,  1167,  1167,  1167,  1167,  1167,  1167,
    1167,  1167,  1167,  1167,  1167,  1167,  1167,   118,   118,  -305,
    1068,  1167,  1167,  1167,  1167,  1167,  1167,  1167,  1167,  1167,
    1167,  1167,  -305,  -305,  1167,   206,    26,   250,   138,  -305,
    -305,   -61,  -305,  -305,  -305,  -305,   625,  -305,   212,   160,
    -305,  -305,  1167,  -305,  1167,  -305,  -305,    41,  -305,    29,
     209,    74,    74,    -6,    -6,    -6,   634,   634,   999,   999,
      46,    46,    46,    46,   213,   556,  1043,    11,   257,  -305,
    -305,  -305,     4,   959,   959,   959,   959,   959,   959,   959,
     959,   959,   959,   959,   959,   783,  1088,   189,    20,   260,
    -305,   203,   271,   271,   272,   183,  -305,   138,   231,  -305,
    -305,  -305,  -305,  1167,   144,    22,  -305,  -305,  -305,   118,
    -305,   915,   783,   118,  -305,  -305,  -305,  1167,  -305,  -305,
    -305,   126,   118,   118,   215,  -305,   271,   235,    -2,    86,
     242,    -1,  -305,  -305,   871,  -305,   144,  -305,   285,  -305,
    -305,  -305,   959,  -305,   -32,   286,   118,   186,   287,  -305,
     118,    60,   118,    60,   288,  -305,  -305,  -305,   245,  -305,
    -305,   -32,   118,    60,  -305,    65,  -305,    89,  -305,  -305,
    -305,   251,    60,  -305,   295,   169,   258,  -305,    23,   144,
    -305,   177,   259,   287,  -305,    60,  -305,  -305,    44,    60,
    -305,   150,  -305,  -305,    60,  -305,  -305,   261,  -305,  -305,
    -305,    50,    44,  -305,  -305,  -305,  -305,   118,   290,   262,
    -305,  -305,   263,  -305,   235,   256,    32,  -305,  -305,   302,
     264,  -305,  -305,   265,    79,   235,  -305,   268,  -305,    80,
     304,   149,   267,  -305,   253,   165,   140,  -305,   -32,   304,
     125,   118,   254,  -305,  -305,   275,  -305,   -32,   270,   171,
     -32,   118,  1148,  -305,   118,   273,  -305,   -32,  -305,   172,
     -32,   118,  -305,  -305,  -305,   -32,  -305
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -305,  -305,  -305,   326,  -305,   100,   135,  -305,  -305,   139,
    -305,   328,   -11,  -304,  -305,    52,  -305,  -305,  -305,  -305,
      35,  -305,    81,  -305,    53,  -305,  -305,  -305,     7,  -305,
    -305,  -305,  -305,  -190,  -305,  -305,  -135,  -180,   -57,    -4,
     -38,    -3,    49,  -305,  -305,  -305,  -305,   -26,  -305,  -305,
    -305,  -305,  -305,   147,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,   217,  -305,  -305,   -25,  -241,   -29
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -85
static const yytype_int16 yytable[] =
{
      42,    42,    88,   259,    78,   122,   221,   127,   250,    80,
     323,    83,   125,   217,   109,     7,    79,   203,   204,    88,
     280,   332,   132,    69,    89,    90,    91,    92,    93,   223,
      94,    95,   291,    14,    42,    98,    99,   100,   101,   325,
      85,   102,   103,   104,   130,     2,   251,   128,   148,   131,
     213,    14,   141,   137,    88,   218,   107,   314,   106,    89,
      90,    91,    92,    93,    63,    64,    65,    66,    67,   169,
     170,   224,   292,   107,   283,     8,    42,   187,    73,    74,
      75,    86,    88,   149,    81,    82,    14,    14,   189,    91,
      92,    93,   215,   216,   214,   298,   252,   346,   213,   108,
     203,   236,   299,   300,   149,   149,   353,   298,   107,   356,
     208,   317,    68,   298,   299,   300,   362,   301,   284,   364,
     299,   300,   315,   149,   366,    14,   326,   268,   269,   270,
     330,   334,    14,    42,   253,   217,   107,   285,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   219,   310,   223,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   238,   359,   185,   223,   241,   348,   243,   213,   235,
     223,   217,   229,   240,   244,   245,   213,   144,    70,   331,
      71,   211,    79,   212,   335,    76,   262,   343,   344,   311,
     339,   191,   192,   193,   194,   349,   149,   145,   261,   256,
     149,   257,   148,   195,   148,   247,   342,   289,    84,   149,
     149,    88,   355,   363,   148,   294,    89,    90,    91,    92,
      93,   124,    94,    95,   263,   173,   107,    98,    99,   100,
     101,   110,   126,   149,   138,   104,   267,   149,   275,   149,
     308,   146,   234,   -84,   293,   150,   186,   190,   281,   149,
     106,    86,   209,   222,   308,    88,   242,   225,   226,   319,
      89,    90,    91,    92,    93,   107,    94,    95,   227,   230,
     233,    98,    99,   100,   101,   149,   189,   248,   276,   246,
     254,   189,   258,   260,   264,   277,   279,   320,   282,   149,
     286,   108,   189,   350,   149,   288,   324,   290,   295,   327,
     313,   321,   322,   357,   336,   329,   360,   340,   328,   107,
     297,   149,   333,   365,   309,   352,   149,   341,   351,   312,
      60,   255,   232,    61,   231,   296,     9,   149,   149,    10,
      11,    12,    13,    14,   354,   108,   347,   361,   149,    15,
      16,   149,   237,   287,    17,   318,   210,    18,   149,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
       0,     1,     0,    -5,    -5,    -5,    -5,    -5,     0,     0,
       0,     0,     0,    -5,    -5,     0,    19,     0,    -5,     0,
       0,    -5,    20,    21,    22,    23,    24,    25,     0,     0,
       0,   173,     0,     0,     0,     0,     0,     0,    26,    27,
       0,    28,    29,    30,     0,     0,    31,    32,    33,    34,
      -5,    35,    36,    37,     0,     2,    -5,    -5,    -5,    -5,
      -5,    -5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    -5,    -5,     0,    -5,    -5,    -5,     0,     0,
      -5,    -5,    -5,    -5,     0,    -5,    -5,    -5,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,    15,    16,
       0,     0,     0,    17,     0,     0,    18,     0,     0,    88,
       0,     0,     0,     0,    89,    90,    91,    92,    93,     0,
      94,    95,     0,    96,    97,    98,    99,   100,   101,     0,
       0,   102,   103,   104,   105,    19,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,     0,   106,    79,
       0,     0,     0,     0,     0,   132,     0,    26,    27,     0,
      28,    29,    30,   107,     0,    31,    32,    33,    34,     0,
      35,    36,    37,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,    15,    16,     0,     0,     0,    17,   108,
       0,    18,     0,     0,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,     0,    94,    95,     0,     0,     0,
      98,    99,   100,   101,     0,     0,   102,     0,   104,   135,
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
      32,    33,    34,     0,    35,    36,    37,    88,     0,   142,
       0,     0,    89,    90,    91,    92,    93,     0,    94,    95,
       0,    96,    97,    98,    99,   100,   101,     0,     0,   102,
     103,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   106,     0,     0,     0,
       0,    88,     0,   143,     0,     0,    89,    90,    91,    92,
      93,   107,    94,    95,     0,    96,    97,    98,    99,   100,
     101,     0,     0,   102,   103,   104,   105,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,     0,     0,
     106,     0,     0,     0,     0,    88,     0,    76,     0,     0,
      89,    90,    91,    92,    93,   107,    94,    95,     0,    96,
      97,    98,    99,   100,   101,     0,     0,   102,   103,   104,
     105,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,     0,     0,   106,     0,     0,     0,   123,    88,
       0,     0,     0,     0,    89,    90,    91,    92,    93,   107,
      94,    95,     0,    96,    97,    98,    99,   100,   101,     0,
       0,   102,   103,   104,   105,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,     0,     0,   106,    79,
       0,     0,     0,    88,     0,     0,     0,     0,    89,    90,
      91,    92,    93,   107,    94,    95,     0,    96,    97,    98,
      99,   100,   101,     0,     0,   102,   103,   104,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
       0,     0,   106,     0,     0,     0,     0,    88,     0,   239,
       0,     0,    89,    90,    91,    92,    93,   107,    94,    95,
       0,    96,    97,    98,    99,   100,   101,     0,     0,   102,
     103,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,     0,     0,   106,    88,     0,     0,
       0,     0,    89,    90,    91,    92,    93,     0,    94,    95,
       0,   107,     0,    98,    99,   100,   101,     0,     0,   102,
     103,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   106,   108,     0,     0,
       0,    88,     0,     0,     0,     0,    89,    90,    91,    92,
      93,   107,    94,    95,     0,     0,     0,    98,    99,   100,
     101,    10,    11,    12,    13,    14,     0,     0,     0,     0,
       0,    15,    16,     0,     0,     0,    17,   108,     0,    18,
     106,    10,    11,    12,    13,    14,     0,     0,     0,     0,
       0,    15,    16,     0,     0,   107,    17,     0,     0,    18,
       0,     0,     0,     0,     0,     0,     0,     0,    19,   171,
       0,     0,     0,     0,     0,    21,    22,    23,    24,    25,
       0,   108,     0,     0,     0,     0,     0,     0,    19,   220,
      26,     0,     0,     0,     0,    21,    22,    23,    24,    25,
       0,    10,    11,    12,    13,    14,     0,     0,     0,     0,
      26,    15,    16,     0,     0,     0,    17,     0,     0,    18,
      10,    11,    12,    13,    14,     0,     0,     0,     0,     0,
      15,    16,     0,     0,     0,    17,     0,     0,    18,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    19,   358,
       0,     0,     0,     0,     0,    21,    22,    23,    24,    25,
       0,     0,     0,     0,     0,     0,     0,    19,     0,     0,
      26,     0,     0,     0,    21,    22,    23,    24,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    26
};

static const yytype_int16 yycheck[] =
{
       3,     4,     8,   244,    33,    62,   186,     8,    10,    34,
     314,    37,    69,     9,    43,   102,    48,    78,    79,     8,
     261,   325,    54,    26,    13,    14,    15,    16,    17,     9,
      19,    20,     9,     7,    37,    24,    25,    26,    27,     7,
      11,    30,    31,    32,    73,    55,    48,    48,    86,    74,
       9,     7,    81,    79,     8,    51,    62,     7,    47,    13,
      14,    15,    16,    17,    15,    16,    17,    18,    19,   107,
     108,    51,    49,    62,     9,     4,    79,    51,    29,    30,
      31,    52,     8,    86,    35,    36,     7,     7,   126,    15,
      16,    17,   149,   150,    53,    63,    10,   338,     9,    88,
      78,    79,    70,    71,   107,   108,   347,    63,    62,   350,
     136,   301,     7,    63,    70,    71,   357,    73,    53,   360,
      70,    71,    72,   126,   365,     7,   316,    67,    68,    69,
      51,    51,     7,   136,    48,     9,    62,    48,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   185,     7,     9,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   209,   352,   124,     9,   213,    51,    51,     9,   204,
       9,     9,   193,   212,   222,   223,     9,    34,     7,   324,
       7,   142,    48,   144,   329,    54,    10,    57,    58,    49,
      51,    63,    64,    65,    66,   340,   209,    54,   246,   234,
     213,   236,   250,    75,   252,   226,    51,    48,     7,   222,
     223,     8,    51,    51,   262,    48,    13,    14,    15,    16,
      17,    34,    19,    20,    48,   186,    62,    24,    25,    26,
      27,    50,    50,   246,    84,    32,   250,   250,   252,   252,
     288,     7,   203,     7,   279,     7,    50,     7,   262,   262,
      47,    52,    50,    74,   302,     8,   217,     7,    65,   307,
      13,    14,    15,    16,    17,    62,    19,    20,     7,     7,
      49,    24,    25,    26,    27,   288,   324,    52,   253,    74,
      48,   329,     7,     7,     7,     7,    51,     7,   263,   302,
      49,    88,   340,   341,   307,    10,    50,    49,    49,     7,
      49,    49,    49,   351,    10,    50,   354,    50,    54,    62,
     285,   324,    54,   361,   289,    50,   329,    74,    74,   294,
       4,   231,   197,     5,   195,   283,     0,   340,   341,     3,
       4,     5,     6,     7,    74,    88,   339,    74,   351,    13,
      14,   354,   205,   272,    18,   302,   139,    21,   361,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,     1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    13,    14,    -1,    50,    -1,    18,    -1,
      -1,    21,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,   352,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      -1,    75,    76,    77,    -1,    -1,    80,    81,    82,    83,
      50,    85,    86,    87,    -1,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    -1,    75,    76,    77,    -1,    -1,
      80,    81,    82,    83,    -1,    85,    86,    87,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,
      -1,    -1,    -1,    18,    -1,    -1,    21,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    50,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    72,    73,    -1,
      75,    76,    77,    62,    -1,    80,    81,    82,    83,    -1,
      85,    86,    87,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    13,    14,    -1,    -1,    -1,    18,    88,
      -1,    21,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    -1,    -1,
      24,    25,    26,    27,    -1,    -1,    30,    -1,    32,    49,
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
      81,    82,    83,    -1,    85,    86,    87,     8,    -1,    10,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,     8,    -1,    54,    -1,    -1,    13,    14,    15,    16,
      17,    62,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      47,    -1,    -1,    -1,    -1,     8,    -1,    54,    -1,    -1,
      13,    14,    15,    16,    17,    62,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    47,    -1,    -1,    -1,    51,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    62,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    47,    48,
      -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    62,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    47,    -1,    -1,    -1,    -1,     8,    -1,    54,
      -1,    -1,    13,    14,    15,    16,    17,    62,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    47,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    62,    -1,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    88,    -1,    -1,
      -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    62,    19,    20,    -1,    -1,    -1,    24,    25,    26,
      27,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      -1,    13,    14,    -1,    -1,    -1,    18,    88,    -1,    21,
      47,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      -1,    13,    14,    -1,    -1,    62,    18,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      72,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      72,    13,    14,    -1,    -1,    -1,    18,    -1,    -1,    21,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,
      13,    14,    -1,    -1,    -1,    18,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      72,    -1,    -1,    -1,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    55,   104,   105,   113,   114,   102,     4,     0,
       3,     4,     5,     6,     7,    13,    14,    18,    21,    50,
      56,    57,    58,    59,    60,    61,    72,    73,    75,    76,
      77,    80,    81,    82,    83,    85,    86,    87,   106,   107,
     132,   143,   144,   145,   146,   147,   148,   150,   151,   152,
     153,   154,   157,   158,   159,   160,   161,   162,   165,   166,
     106,   114,   144,   145,   145,   145,   145,   145,     7,   144,
       7,     7,   112,   145,   145,   145,    54,   169,   169,    48,
     167,   145,   145,   150,     7,    11,    52,   141,     8,    13,
      14,    15,    16,    17,    19,    20,    22,    23,    24,    25,
      26,    27,    30,    31,    32,    33,    47,    62,    88,   169,
      50,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,   141,    51,    34,   141,    50,     8,    48,   108,
     169,   167,    54,   167,   168,    49,   149,   150,    84,   163,
     164,   169,    10,    54,    34,    54,     7,   142,   143,   144,
       7,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   143,
     143,    51,   140,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,    50,    51,   139,   143,
       7,    63,    64,    65,    66,    75,   109,   110,   111,   119,
     120,   121,   122,    78,    79,   155,   156,    49,   150,    50,
     164,   145,   145,     9,    53,   141,   141,     9,    51,   169,
      51,   140,    74,     9,    51,     7,    65,     7,   115,   115,
       7,   112,   109,    49,   145,   167,    79,   156,   143,    54,
     169,   143,   145,    51,   143,   143,    74,   115,    52,   116,
      10,    48,    10,    48,    48,   108,   167,   167,     7,   168,
       7,   143,    10,    48,     7,   117,   118,   142,    67,    68,
      69,   123,   124,   125,   137,   142,   123,     7,   138,    51,
     168,   142,   123,     9,    53,    48,    49,   125,    10,    48,
      49,     9,    49,   167,    48,    49,   118,   123,    63,    70,
      71,    73,   126,   127,   128,   133,   134,   136,   143,   123,
       7,    49,   123,    49,     7,    72,   135,   136,   127,   143,
       7,    49,    49,   116,    50,     7,   136,     7,    54,    50,
      51,   139,   116,    54,    51,   139,    10,   129,   131,    51,
      50,    74,    51,    57,    58,   130,   168,   131,    51,   139,
     143,    74,    50,   168,    74,    51,   168,   143,    51,   140,
     143,    74,   168,    51,   168,   143,   168
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
		(yyval.ast_value) = ast_new_method_decl((yyvsp[(2) - (10)].ast_value), (yyvsp[(3) - (10)].string_value), (yyvsp[(4) - (10)].ast_value), (yyvsp[(6) - (10)].ast_value), (yyvsp[(10) - (10)].ast_value), (yyvsp[(9) - (10)].ast_value));
	;}
    break;

  case 61:
#line 416 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[(2) - (9)].ast_value), (yyvsp[(3) - (9)].string_value), (yyvsp[(4) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 62:
#line 420 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl(ast_new_modifier(modifier_none), (yyvsp[(2) - (9)].string_value), (yyvsp[(3) - (9)].ast_value), (yyvsp[(5) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 63:
#line 424 "beacon.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params(ast_new_modifier(modifier_none), (yyvsp[(2) - (8)].string_value), (yyvsp[(3) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 64:
#line 431 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[(1) - (4)].ast_value), (yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].string_value));
	;}
    break;

  case 65:
#line 435 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_decl(ast_new_modifier(modifier_none), (yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].string_value));
	;}
    break;

  case 66:
#line 442 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 67:
#line 446 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 68:
#line 453 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_static);
	;}
    break;

  case 69:
#line 457 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_native);
	;}
    break;

  case 70:
#line 461 "beacon.y"
    {
		(yyval.ast_value) = ast_new_modifier(modifier_abstract);
	;}
    break;

  case 71:
#line 468 "beacon.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 72:
#line 472 "beacon.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 73:
#line 476 "beacon.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 74:
#line 483 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 75:
#line 487 "beacon.y"
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[(3) - (3)].string_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 76:
#line 494 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].string_value));
	;}
    break;

  case 77:
#line 498 "beacon.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].string_value), (yyvsp[(1) - (4)].ast_value))
	;}
    break;

  case 78:
#line 505 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 79:
#line 509 "beacon.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(3) - (3)].ast_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 80:
#line 516 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 81:
#line 520 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 82:
#line 527 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 83:
#line 531 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[(3) - (3)].ast_value), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 84:
#line 538 "beacon.y"
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 85:
#line 545 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 86:
#line 549 "beacon.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(3) - (3)].string_value)), (yyvsp[(1) - (3)].ast_value));
	;}
    break;

  case 87:
#line 558 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 90:
#line 566 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_pos, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 91:
#line 570 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_neg, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 92:
#line 574 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 93:
#line 578 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 94:
#line 582 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 95:
#line 586 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 96:
#line 590 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 97:
#line 594 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 98:
#line 598 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_equal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 99:
#line 602 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_notequal, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 100:
#line 606 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 101:
#line 610 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 102:
#line 614 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_or, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 103:
#line 618 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_and, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 104:
#line 622 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 105:
#line 626 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_add_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 106:
#line 630 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_sub_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 107:
#line 634 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mul_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 108:
#line 638 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_div_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 109:
#line 642 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_mod_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 110:
#line 646 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_and_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 111:
#line 650 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 112:
#line 654 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 113:
#line 658 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 114:
#line 662 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift_assign, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 115:
#line 666 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_gt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 116:
#line 670 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_ge, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 117:
#line 674 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lt, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 118:
#line 678 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_le, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 119:
#line 682 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 120:
#line 686 "beacon.y"
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift, (yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 121:
#line 690 "beacon.y"
    {
		(yyval.ast_value) = ast_new_instanceof((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 122:
#line 694 "beacon.y"
    {
		(yyval.ast_value) = ast_new_as((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 123:
#line 698 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_childa, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 124:
#line 702 "beacon.y"
    {
		(yyval.ast_value) = ast_new_unary(ast_not, (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 125:
#line 706 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 126:
#line 710 "beacon.y"
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[(1) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 127:
#line 714 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 128:
#line 718 "beacon.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), ast_new_blank());
	;}
    break;

  case 129:
#line 722 "beacon.y"
    {
		(yyval.ast_value) = ast_new_this();
	;}
    break;

  case 130:
#line 726 "beacon.y"
    {
		(yyval.ast_value) = ast_new_super();
	;}
    break;

  case 132:
#line 733 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 133:
#line 737 "beacon.y"
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[(1) - (4)].ast_value), (yyvsp[(3) - (4)].string_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 138:
#line 747 "beacon.y"
    {
		(yyval.ast_value) = ast_new_true();
	;}
    break;

  case 139:
#line 751 "beacon.y"
    {
		(yyval.ast_value) = ast_new_false();
	;}
    break;

  case 140:
#line 755 "beacon.y"
    {
		(yyval.ast_value) = ast_new_null();
	;}
    break;

  case 141:
#line 764 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 142:
#line 768 "beacon.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 143:
#line 774 "beacon.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 156:
#line 792 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].string_value));
	;}
    break;

  case 157:
#line 798 "beacon.y"
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 158:
#line 804 "beacon.y"
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 159:
#line 810 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 160:
#line 814 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(2) - (5)].ast_value), (yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 161:
#line 818 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].ast_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 162:
#line 822 "beacon.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(2) - (6)].ast_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 164:
#line 829 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 165:
#line 835 "beacon.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 166:
#line 841 "beacon.y"
    {
		(yyval.ast_value) = ast_new_while((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 167:
#line 847 "beacon.y"
    {
		(yyval.ast_value) = ast_new_break();
	;}
    break;

  case 168:
#line 853 "beacon.y"
    {
		(yyval.ast_value) = ast_new_continue();
	;}
    break;

  case 169:
#line 859 "beacon.y"
    {
		(yyval.ast_value) = ast_new_return((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 170:
#line 865 "beacon.y"
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 171:
#line 871 "beacon.y"
    {
		(yyval.ast_value) = ast_new_try((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 172:
#line 877 "beacon.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 173:
#line 881 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 174:
#line 887 "beacon.y"
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].string_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 175:
#line 893 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (5)].ast_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 176:
#line 897 "beacon.y"
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[(2) - (3)].ast_value), ast_new_blank());
	;}
    break;

  case 177:
#line 903 "beacon.y"
    {
		(yyval.ast_value) = ast_new_defer((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 178:
#line 910 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 179:
#line 914 "beacon.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 180:
#line 920 "beacon.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3110 "beacon.tab.c"
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


#line 928 "beacon.y"





