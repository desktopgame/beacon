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
     TRUE = 303,
     FALSE = 304,
     INTERFACE = 305,
     CLASS = 306,
     ENUM = 307,
     PUBLIC = 308,
     PRIVATE = 309,
     PROTECTED = 310,
     STATIC = 311,
     NATIVE = 312,
     NEW = 313,
     CTOR = 314,
     DEF = 315,
     ARROW = 316,
     NAMESPACE = 317,
     RETURN = 318,
     IF = 319,
     ELIF = 320,
     ELSE = 321,
     WHILE = 322,
     BREAK = 323,
     CONTINUE = 324
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
#define TRUE 303
#define FALSE 304
#define INTERFACE 305
#define CLASS 306
#define ENUM 307
#define PUBLIC 308
#define PRIVATE 309
#define PROTECTED 310
#define STATIC 311
#define NATIVE 312
#define NEW 313
#define CTOR 314
#define DEF 315
#define ARROW 316
#define NAMESPACE 317
#define RETURN 318
#define IF 319
#define ELIF 320
#define ELSE 321
#define WHILE 322
#define BREAK 323
#define CONTINUE 324




/* Copy the first part of user declarations.  */
#line 1 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"

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
#line 15 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
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
#line 259 "signal.tab.c"
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
#line 284 "signal.tab.c"

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
#define YYFINAL  86
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   661

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  160
/* YYNRULES -- Number of states.  */
#define YYNSTATES  298

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   324

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      70,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    13,    15,    17,    19,
      23,    27,    31,    33,    35,    37,    39,    42,    43,    45,
      47,    51,    54,    60,    68,    74,    81,    87,    95,    96,
      98,   101,   102,   106,   107,   109,   112,   114,   116,   118,
     126,   133,   139,   144,   146,   148,   149,   151,   160,   168,
     178,   187,   192,   193,   196,   199,   201,   203,   205,   207,
     209,   211,   215,   218,   223,   225,   229,   231,   235,   237,
     239,   243,   245,   247,   251,   255,   257,   259,   261,   263,
     265,   267,   269,   273,   277,   279,   283,   287,   289,   293,
     297,   299,   303,   307,   311,   315,   317,   321,   325,   327,
     331,   335,   339,   341,   344,   347,   349,   352,   355,   357,
     361,   367,   374,   377,   380,   382,   384,   386,   388,   390,
     392,   394,   398,   403,   407,   412,   418,   425,   429,   431,
     433,   439,   444,   446,   449,   452,   454,   456,   458,   460,
     462,   464,   466,   468,   472,   478,   484,   490,   498,   505,
     514,   516,   519,   525,   531,   534,   537,   541,   545,   548,
     550
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      72,     0,    -1,    73,    -1,    72,    73,    -1,     1,    70,
      -1,   116,    -1,    80,    -1,    74,    -1,    92,    -1,    62,
      79,    75,    -1,    37,    78,    38,    -1,    62,    79,    75,
      -1,    81,    -1,    83,    -1,    82,    -1,    76,    -1,    77,
      76,    -1,    -1,    77,    -1,     7,    -1,    79,     8,     7,
      -1,    44,     4,    -1,    51,     7,    37,    84,    38,    -1,
      51,     7,    11,   100,    37,    84,    38,    -1,    52,     7,
      37,    97,    38,    -1,    52,     7,    37,    97,     9,    38,
      -1,    50,     7,    37,    84,    38,    -1,    50,     7,    11,
     100,    37,    84,    38,    -1,    -1,    85,    -1,    84,    85,
      -1,    -1,    96,    11,    86,    -1,    -1,    87,    -1,    86,
      87,    -1,    88,    -1,    93,    -1,    94,    -1,    59,    58,
      39,    98,    40,    91,   129,    -1,    59,    58,    39,    40,
      91,   129,    -1,    11,    90,    39,    99,    40,    -1,    11,
      90,    39,    40,    -1,    47,    -1,    46,    -1,    -1,    89,
      -1,    60,     7,    39,    98,    40,    61,   101,   129,    -1,
      60,     7,    39,    40,    61,   101,   129,    -1,    95,    60,
       7,    39,    98,    40,    61,   101,   129,    -1,    95,    60,
       7,    39,    40,    61,   101,   129,    -1,    95,   101,     7,
      43,    -1,    -1,    56,    57,    -1,    57,    56,    -1,    56,
      -1,    57,    -1,    53,    -1,    54,    -1,    55,    -1,     7,
      -1,     7,     9,    97,    -1,   101,     7,    -1,   101,     7,
       9,    98,    -1,   103,    -1,   103,     9,    99,    -1,   101,
      -1,   101,     9,   100,    -1,   102,    -1,     7,    -1,     7,
      12,   102,    -1,   104,    -1,   106,    -1,   106,   105,   104,
      -1,     7,   105,   104,    -1,    19,    -1,    20,    -1,    21,
      -1,    22,    -1,    23,    -1,    24,    -1,   107,    -1,   106,
      35,   107,    -1,   106,    36,   107,    -1,   108,    -1,   107,
      33,   108,    -1,   107,    34,   108,    -1,   109,    -1,   108,
      25,   109,    -1,   108,    26,   109,    -1,   110,    -1,   109,
      29,   110,    -1,   109,    30,   110,    -1,   109,    31,   110,
      -1,   109,    32,   110,    -1,   111,    -1,   110,    13,   111,
      -1,   110,    14,   111,    -1,   112,    -1,   111,    15,   112,
      -1,   111,    16,   112,    -1,   111,    17,   112,    -1,   113,
      -1,    18,   112,    -1,    14,   112,    -1,   114,    -1,    27,
     114,    -1,    28,   114,    -1,   115,    -1,   114,     8,     7,
      -1,   114,     8,     7,    39,    40,    -1,   114,     8,     7,
      39,    99,    40,    -1,   114,    27,    -1,   114,    28,    -1,
       5,    -1,     6,    -1,     3,    -1,     4,    -1,    48,    -1,
      49,    -1,     7,    -1,     7,    39,    40,    -1,     7,    39,
      99,    40,    -1,    39,   103,    40,    -1,    39,   101,    40,
     103,    -1,   102,     8,     7,    39,    40,    -1,   102,     8,
       7,    39,    99,    40,    -1,   102,     8,     7,    -1,    46,
      -1,    47,    -1,    58,   101,    39,    99,    40,    -1,    58,
     101,    39,    40,    -1,   117,    -1,   116,   117,    -1,   103,
      43,    -1,   118,    -1,   119,    -1,   120,    -1,   121,    -1,
     124,    -1,   125,    -1,   126,    -1,   127,    -1,   101,     7,
      43,    -1,   101,     7,    19,   103,    43,    -1,    45,     7,
      19,   103,    43,    -1,    64,    39,   103,    40,   128,    -1,
      64,    39,   103,    40,   128,    66,   128,    -1,    64,    39,
     103,    40,   128,   122,    -1,    64,    39,   103,    40,   128,
     122,    66,   128,    -1,   123,    -1,   122,   123,    -1,    65,
      39,   103,    40,   128,    -1,    67,    39,   103,    40,   129,
      -1,    68,    43,    -1,    69,    43,    -1,    63,   103,    43,
      -1,    37,   116,    38,    -1,    37,    38,    -1,    43,    -1,
     128,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   103,   103,   104,   105,   111,   115,   119,   123,   129,
     135,   141,   145,   149,   153,   159,   163,   170,   173,   179,
     183,   189,   195,   199,   205,   209,   215,   219,   226,   229,
     233,   240,   243,   250,   253,   257,   263,   264,   265,   268,
     272,   278,   282,   288,   292,   299,   302,   305,   309,   315,
     319,   325,   332,   335,   339,   343,   347,   353,   357,   361,
     367,   371,   377,   381,   387,   391,   397,   401,   407,   413,
     417,   423,   426,   427,   431,   437,   441,   445,   449,   453,
     457,   463,   464,   468,   474,   475,   479,   485,   486,   490,
     496,   497,   501,   505,   509,   515,   516,   520,   526,   527,
     531,   535,   541,   542,   546,   552,   553,   557,   563,   564,
     568,   572,   576,   580,   586,   587,   588,   589,   590,   594,
     598,   602,   606,   610,   614,   618,   622,   626,   630,   634,
     638,   642,   648,   652,   658,   662,   663,   664,   665,   666,
     667,   668,   669,   672,   678,   684,   690,   694,   698,   702,
     708,   709,   715,   721,   727,   733,   739,   745,   749,   755,
     759
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
  "IMPORT", "VAR", "THIS", "SUPER", "TRUE", "FALSE", "INTERFACE", "CLASS",
  "ENUM", "PUBLIC", "PRIVATE", "PROTECTED", "STATIC", "NATIVE", "NEW",
  "CTOR", "DEF", "ARROW", "NAMESPACE", "RETURN", "IF", "ELIF", "ELSE",
  "WHILE", "BREAK", "CONTINUE", "'\\n'", "$accept", "root", "top_level",
  "namespace_decl", "namespace_body", "namespace_member_decl",
  "namespace_member_decl_list", "namespace_member_decl_optional",
  "namespace_path", "import", "class_decl", "enum_decl", "interface_decl",
  "access_member_tree", "access_member_list", "member_define_list",
  "member_define", "constructor_define", "constructor_chain",
  "constructor_chain_type_T", "constructor_chain_optional",
  "function_define", "method_define", "field_define", "modifier_type_T",
  "access_level_T", "ident_list", "parameter_list", "argument_list",
  "typename_list", "typename_T", "fqcn_part", "expression", "assign",
  "assign_type_T", "or", "and", "equal", "compare", "addsub", "muldiv",
  "unary", "prefix", "postfix", "primary", "stmt_list", "stmt",
  "variable_decl_stmt", "variable_init_stmt", "inferenced_type_init_stmt",
  "if_stmt", "elif_list", "elif", "while_stmt", "break_stmt",
  "continue_stmt", "return_stmt", "scope", "scope_optional", 0
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
      10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    72,    72,    73,    73,    73,    73,    74,
      75,    76,    76,    76,    76,    77,    77,    78,    78,    79,
      79,    80,    81,    81,    82,    82,    83,    83,    84,    84,
      84,    85,    85,    86,    86,    86,    87,    87,    87,    88,
      88,    89,    89,    90,    90,    91,    91,    92,    92,    93,
      93,    94,    95,    95,    95,    95,    95,    96,    96,    96,
      97,    97,    98,    98,    99,    99,   100,   100,   101,   102,
     102,   103,   104,   104,   104,   105,   105,   105,   105,   105,
     105,   106,   106,   106,   107,   107,   107,   108,   108,   108,
     109,   109,   109,   109,   109,   110,   110,   110,   111,   111,
     111,   111,   112,   112,   112,   113,   113,   113,   114,   114,
     114,   114,   114,   114,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   116,   116,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   118,   119,   120,   121,   121,   121,   121,
     122,   122,   123,   124,   125,   126,   127,   128,   128,   129,
     129
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     1,     1,     3,
       3,     3,     1,     1,     1,     1,     2,     0,     1,     1,
       3,     2,     5,     7,     5,     6,     5,     7,     0,     1,
       2,     0,     3,     0,     1,     2,     1,     1,     1,     7,
       6,     5,     4,     1,     1,     0,     1,     8,     7,     9,
       8,     4,     0,     2,     2,     1,     1,     1,     1,     1,
       1,     3,     2,     4,     1,     3,     1,     3,     1,     1,
       3,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     2,     2,     1,     2,     2,     1,     3,
       5,     6,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     4,     3,     4,     5,     6,     3,     1,     1,
       5,     4,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     5,     5,     5,     7,     6,     8,
       1,     2,     5,     5,     2,     2,     3,     3,     2,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,   116,   117,   114,   115,   120,     0,     0,     0,
       0,     0,     0,     0,   128,   129,   118,   119,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     2,     7,     6,
       8,     0,    68,     0,    71,    72,    81,    84,    87,    90,
      95,    98,   102,   105,   108,     5,   132,   135,   136,   137,
     138,   139,   140,   141,   142,     4,     0,    75,    76,    77,
      78,    79,    80,     0,     0,   120,     0,   104,   103,   106,
     107,     0,     0,    21,     0,    69,     0,    68,     0,    19,
       0,     0,     0,     0,   154,   155,     1,     3,     0,     0,
     134,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   113,
     133,    70,   121,     0,    64,    74,     0,   123,     0,     0,
       0,     0,    17,     9,   156,     0,     0,     0,   143,   127,
      82,    83,    73,    85,    86,    88,    89,    91,    92,    93,
      94,    96,    97,    99,   100,   101,   109,   122,     0,   124,
       0,   131,     0,     0,     0,     0,    20,     0,     0,     0,
       0,    15,    18,     0,    12,    14,    13,     0,     0,     0,
       0,     0,    65,   145,   130,     0,     0,    62,     0,     0,
       0,     0,    16,    10,     0,   146,   159,   160,   153,   144,
     125,     0,   110,     0,     0,     0,     0,     0,    28,     0,
      28,     0,    11,   158,     0,     0,     0,   148,   150,   126,
     111,    48,     0,    63,     0,    66,    57,    58,    59,     0,
      29,     0,     0,     0,    60,     0,   157,     0,   147,     0,
     151,    47,    28,     0,    26,    30,    33,    28,    22,     0,
       0,    24,     0,   149,     0,    67,    55,    56,     0,    32,
      34,    36,    37,    38,     0,     0,    61,    25,     0,    27,
      53,    54,     0,    35,     0,     0,    23,   152,     0,     0,
       0,    45,     0,     0,    51,     0,    46,     0,    45,     0,
       0,    44,    43,     0,    40,     0,     0,     0,     0,    39,
       0,     0,    42,     0,    50,     0,    41,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,    28,   123,   161,   162,   163,    80,    29,
     164,   165,   166,   219,   220,   249,   250,   251,   276,   283,
     277,    30,   252,   253,   254,   221,   225,   154,   113,   214,
      31,    66,   114,    34,    64,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,   207,   208,    51,    52,    53,    54,   187,   188
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -207
static const yytype_int16 yypact[] =
{
     110,   -42,  -207,  -207,  -207,  -207,   111,   566,   566,   597,
     597,   603,    35,    39,  -207,  -207,  -207,  -207,    59,    77,
      83,   603,    54,    56,    55,    57,   202,  -207,  -207,  -207,
    -207,   105,   100,   117,  -207,   278,   106,    96,     2,   139,
     165,  -207,  -207,    69,  -207,   362,  -207,  -207,  -207,  -207,
    -207,  -207,  -207,  -207,  -207,  -207,    59,  -207,  -207,  -207,
    -207,  -207,  -207,   409,   603,    29,   100,  -207,  -207,    69,
      69,   108,   129,  -207,   152,   171,   149,  -207,   155,  -207,
      11,   160,   603,   603,  -207,  -207,  -207,  -207,    24,   191,
    -207,   566,   566,   603,   566,   566,   566,   566,   566,   566,
     566,   566,   566,   566,   566,   566,   566,   205,  -207,  -207,
    -207,  -207,  -207,   177,   219,  -207,   603,  -207,   603,   436,
      15,   224,    23,  -207,  -207,   192,   194,   603,  -207,   196,
     106,   106,  -207,    96,    96,     2,     2,   139,   139,   139,
     139,   165,   165,  -207,  -207,  -207,   198,  -207,   603,  -207,
     195,  -207,   199,   179,   203,   235,  -207,   238,   245,   246,
      83,  -207,    23,   218,  -207,  -207,  -207,   220,   -14,   212,
     474,   501,  -207,  -207,  -207,    59,   200,   250,    14,    33,
     230,    11,  -207,  -207,   289,   101,  -207,  -207,  -207,  -207,
    -207,   232,  -207,   234,   -14,    59,    59,    59,   137,    59,
     137,   268,  -207,  -207,   336,   239,   220,   135,  -207,  -207,
    -207,  -207,   -14,  -207,   240,   270,  -207,  -207,  -207,    34,
    -207,   269,   247,    88,   273,    31,  -207,   603,  -207,   220,
    -207,  -207,   137,    59,  -207,  -207,    50,   137,  -207,   268,
     249,  -207,   243,  -207,    91,  -207,   228,   233,   248,     5,
    -207,  -207,  -207,  -207,     3,   109,  -207,  -207,   220,  -207,
    -207,  -207,   251,  -207,   281,   297,  -207,  -207,    17,   266,
     265,   298,   271,    20,  -207,   164,  -207,   -14,   298,   254,
     272,  -207,  -207,   279,  -207,   -14,    59,   258,   539,  -207,
     -14,    59,  -207,   280,  -207,   -14,  -207,  -207
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -207,  -207,   284,  -207,   140,   161,  -207,  -207,   162,  -207,
    -207,  -207,  -207,  -185,  -206,  -207,    75,  -207,  -207,  -207,
      47,  -207,  -207,  -207,  -207,  -207,    87,  -190,  -112,  -183,
     -10,     0,     9,   -22,   294,  -207,   123,   124,   125,   -19,
     122,    -3,  -207,   217,  -207,   146,   -43,  -207,  -207,  -207,
    -207,  -207,   126,  -207,  -207,  -207,  -207,  -153,  -191
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -70
static const yytype_int16 yytable[] =
{
      32,    71,   110,   211,    67,    68,   213,   152,    76,    33,
      75,    32,   -52,   235,   185,   223,   222,   235,    77,   121,
      72,   231,    75,   184,    75,   197,    32,    75,    55,   186,
      81,    98,    99,   100,   101,    33,   172,   -69,   235,    73,
     240,    56,   115,   127,   199,    32,    74,   244,   122,   235,
     245,   198,   255,   228,    33,   153,   111,   271,   191,   193,
     279,   246,   247,   264,   248,   -52,    75,   128,    63,   241,
     200,   132,   234,   157,   158,   159,   243,   107,   272,   137,
     138,   139,   140,   280,    78,   160,   284,   216,   217,   218,
      79,   125,   126,    82,   289,    83,   108,   109,    84,   294,
      85,   143,   144,   145,   297,   267,   246,   247,    89,   248,
     155,     1,    88,     2,     3,     4,     5,     6,   -69,   -69,
      77,    96,    97,    56,     7,   149,   238,   150,     8,   259,
      57,    58,    59,    60,    61,    62,   169,     9,    10,    94,
      95,   216,   217,   218,   216,   217,   218,   266,   116,    11,
      63,   -69,   102,   103,    12,    13,    14,    15,    16,    17,
      90,   110,   216,   217,   218,   194,   205,   206,    18,   117,
      19,   118,    20,    21,    22,    77,   293,    23,    24,    25,
     104,   105,   106,    56,    32,   212,   155,   215,   119,   215,
     216,   217,   218,    33,   120,    77,    77,    77,   129,    77,
     205,   229,    86,   124,    32,     2,     3,     4,     5,     6,
     281,   282,   146,    33,   130,   131,     7,   147,   133,   134,
       8,   135,   136,   215,   141,   142,    69,    70,   148,     9,
      10,   156,   167,    77,   168,   170,   242,   171,   173,   174,
     175,    11,   177,   176,   265,   178,    12,    13,    14,    15,
      16,    17,   179,   180,    77,   189,   183,   184,   155,   196,
      18,   195,    19,   155,    20,    21,    22,   201,    77,    23,
      24,    25,   209,    77,   210,   224,   290,   232,   227,   233,
     236,   295,   239,   258,   237,   260,    77,   257,   269,   261,
     268,    77,     2,     3,     4,     5,     6,    57,    58,    59,
      60,    61,    62,     7,   270,   273,   262,     8,   274,   275,
      87,   278,   287,    91,    92,   286,     9,    10,   288,   291,
     296,   202,   181,   182,   263,   285,   256,   203,    11,    93,
     204,     0,     0,   230,    13,    14,    15,    16,    17,     2,
       3,     4,     5,     6,     0,     0,     0,    18,     0,     0,
       7,     0,    21,    22,     8,     0,    23,    24,    25,     0,
       0,     0,     0,     9,    10,     2,     3,     4,     5,     6,
       0,     0,     0,     0,   226,    11,     7,     0,     0,     0,
       8,    13,    14,    15,    16,    17,     0,     0,     0,     9,
      10,     0,     0,     0,    18,     0,     0,     0,     0,    21,
      22,    11,     0,    23,    24,    25,     0,    13,    14,    15,
      16,    17,     2,     3,     4,     5,     6,     0,     0,     0,
      18,     0,     0,     7,     0,    21,    22,     8,     0,    23,
      24,    25,     0,     0,     0,     0,     9,    10,     0,     2,
       3,     4,     5,     6,     0,     0,     0,     0,    11,   112,
       7,     0,     0,     0,     8,    14,    15,    16,    17,     0,
       0,     0,     0,     9,    10,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,    11,   151,     2,     3,     4,
       5,     6,    14,    15,    16,    17,     0,     0,     7,     0,
       0,     0,     8,     0,    18,     0,     0,     0,     0,     0,
       0,     9,    10,     0,     2,     3,     4,     5,     6,     0,
       0,     0,     0,    11,   190,     7,     0,     0,     0,     8,
      14,    15,    16,    17,     0,     0,     0,     0,     9,    10,
       0,     0,    18,     0,     0,     0,     0,     0,     0,     0,
      11,   192,     2,     3,     4,     5,     6,    14,    15,    16,
      17,     0,     0,     7,     0,     0,     0,     8,     0,    18,
       0,     0,     0,     0,     0,     0,     9,    10,     0,     2,
       3,     4,     5,    65,     0,     0,     0,     0,    11,   292,
       7,     0,     0,     0,     8,    14,    15,    16,    17,     0,
       0,     0,     0,     9,    10,     0,     0,    18,     0,     0,
       2,     3,     4,     5,    65,    11,     2,     3,     4,     5,
       6,     0,    14,    15,    16,    17,     0,     7,     0,     0,
       0,     8,     0,     0,    18,     0,     0,     0,     0,     0,
       9,    10,     0,     0,     0,     0,    11,     0,     0,     0,
       0,     0,    11,    14,    15,    16,    17,     0,     0,    14,
      15,    16,    17,     0,     0,    18,     0,     0,     0,     0,
       0,    18
};

static const yytype_int16 yycheck[] =
{
       0,    11,    45,   194,     7,     8,   196,   119,    18,     0,
       7,    11,     7,   219,   167,   200,   199,   223,    18,     8,
      11,   212,     7,    37,     7,    11,    26,     7,    70,    43,
      21,    29,    30,    31,    32,    26,   148,     8,   244,     4,
       9,    12,    64,    19,    11,    45,     7,   232,    37,   255,
     233,    37,   237,   206,    45,    40,    56,    40,   170,   171,
      40,    56,    57,    60,    59,    60,     7,    43,    39,    38,
      37,    93,    38,    50,    51,    52,   229,     8,   268,    98,
      99,   100,   101,   273,     7,    62,   277,    53,    54,    55,
       7,    82,    83,    39,   285,    39,    27,    28,    43,   290,
      43,   104,   105,   106,   295,   258,    56,    57,     8,    59,
     120,     1,     7,     3,     4,     5,     6,     7,     7,     8,
     120,    25,    26,    12,    14,   116,    38,   118,    18,    38,
      19,    20,    21,    22,    23,    24,   127,    27,    28,    33,
      34,    53,    54,    55,    53,    54,    55,    38,    40,    39,
      39,    40,    13,    14,    44,    45,    46,    47,    48,    49,
      43,   204,    53,    54,    55,   175,    65,    66,    58,    40,
      60,    19,    62,    63,    64,   175,   288,    67,    68,    69,
      15,    16,    17,    12,   184,   195,   196,   197,    39,   199,
      53,    54,    55,   184,    39,   195,   196,   197,     7,   199,
      65,    66,     0,    43,   204,     3,     4,     5,     6,     7,
      46,    47,     7,   204,    91,    92,    14,    40,    94,    95,
      18,    96,    97,   233,   102,   103,     9,    10,     9,    27,
      28,     7,    40,   233,    40,    39,   227,    39,    43,    40,
      61,    39,     7,    40,   254,     7,    44,    45,    46,    47,
      48,    49,     7,     7,   254,    43,    38,    37,   268,     9,
      58,    61,    60,   273,    62,    63,    64,    37,   268,    67,
      68,    69,    40,   273,    40,     7,   286,    37,    39,     9,
      11,   291,     9,    40,    37,    57,   286,    38,     7,    56,
      39,   291,     3,     4,     5,     6,     7,    19,    20,    21,
      22,    23,    24,    14,     7,    39,    58,    18,    43,    11,
      26,    40,    40,    35,    36,    61,    27,    28,    39,    61,
      40,   181,   160,   162,   249,   278,   239,    38,    39,    35,
     184,    -1,    -1,   207,    45,    46,    47,    48,    49,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    58,    -1,    -1,
      14,    -1,    63,    64,    18,    -1,    67,    68,    69,    -1,
      -1,    -1,    -1,    27,    28,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    -1,    38,    39,    14,    -1,    -1,    -1,
      18,    45,    46,    47,    48,    49,    -1,    -1,    -1,    27,
      28,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    63,
      64,    39,    -1,    67,    68,    69,    -1,    45,    46,    47,
      48,    49,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      58,    -1,    -1,    14,    -1,    63,    64,    18,    -1,    67,
      68,    69,    -1,    -1,    -1,    -1,    27,    28,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    39,    40,
      14,    -1,    -1,    -1,    18,    46,    47,    48,    49,    -1,
      -1,    -1,    -1,    27,    28,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    40,     3,     4,     5,
       6,     7,    46,    47,    48,    49,    -1,    -1,    14,    -1,
      -1,    -1,    18,    -1,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    28,    -1,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    39,    40,    14,    -1,    -1,    -1,    18,
      46,    47,    48,    49,    -1,    -1,    -1,    -1,    27,    28,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    40,     3,     4,     5,     6,     7,    46,    47,    48,
      49,    -1,    -1,    14,    -1,    -1,    -1,    18,    -1,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    39,    40,
      14,    -1,    -1,    -1,    18,    46,    47,    48,    49,    -1,
      -1,    -1,    -1,    27,    28,    -1,    -1,    58,    -1,    -1,
       3,     4,     5,     6,     7,    39,     3,     4,     5,     6,
       7,    -1,    46,    47,    48,    49,    -1,    14,    -1,    -1,
      -1,    18,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,
      27,    28,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    39,    46,    47,    48,    49,    -1,    -1,    46,
      47,    48,    49,    -1,    -1,    58,    -1,    -1,    -1,    -1,
      -1,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,    14,    18,    27,
      28,    39,    44,    45,    46,    47,    48,    49,    58,    60,
      62,    63,    64,    67,    68,    69,    72,    73,    74,    80,
      92,   101,   102,   103,   104,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   124,   125,   126,   127,    70,    12,    19,    20,    21,
      22,    23,    24,    39,   105,     7,   102,   112,   112,   114,
     114,   101,   103,     4,     7,     7,   101,   102,     7,     7,
      79,   103,    39,    39,    43,    43,     0,    73,     7,     8,
      43,    35,    36,   105,    33,    34,    25,    26,    29,    30,
      31,    32,    13,    14,    15,    16,    17,     8,    27,    28,
     117,   102,    40,    99,   103,   104,    40,    40,    19,    39,
      39,     8,    37,    75,    43,   103,   103,    19,    43,     7,
     107,   107,   104,   108,   108,   109,   109,   110,   110,   110,
     110,   111,   111,   112,   112,   112,     7,    40,     9,   103,
     103,    40,    99,    40,    98,   101,     7,    50,    51,    52,
      62,    76,    77,    78,    81,    82,    83,    40,    40,   103,
      39,    39,    99,    43,    40,    61,    40,     7,     7,     7,
       7,    79,    76,    38,    37,   128,    43,   128,   129,    43,
      40,    99,    40,    99,   101,    61,     9,    11,    37,    11,
      37,    37,    75,    38,   116,    65,    66,   122,   123,    40,
      40,   129,   101,    98,   100,   101,    53,    54,    55,    84,
      85,    96,   100,    84,     7,    97,    38,    39,   128,    66,
     123,   129,    37,     9,    38,    85,    11,    37,    38,     9,
       9,    38,   103,   128,    84,   100,    56,    57,    59,    86,
      87,    88,    93,    94,    95,    84,    97,    38,    40,    38,
      57,    56,    58,    87,    60,   101,    38,   128,    39,     7,
       7,    40,    98,    39,    43,    11,    89,    91,    40,    40,
      98,    46,    47,    90,   129,    91,    61,    40,    39,   129,
     101,    61,    40,    99,   129,   101,    40,   129
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
#line 106 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 5:
#line 112 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 6:
#line 116 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 7:
#line 120 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 8:
#line 124 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 9:
#line 130 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 10:
#line 136 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value)
	;}
    break;

  case 11:
#line 142 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 12:
#line 146 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 13:
#line 150 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 14:
#line 154 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 15:
#line 160 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 16:
#line 164 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 17:
#line 170 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 18:
#line 174 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 19:
#line 180 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 20:
#line 184 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 21:
#line 190 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 22:
#line 196 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (5)].string_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 23:
#line 200 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (7)].string_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 24:
#line 206 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 25:
#line 210 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (6)].string_value), (yyvsp[(4) - (6)].ast_value));
	;}
    break;

  case 26:
#line 216 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (5)].string_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 27:
#line 220 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (7)].string_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 28:
#line 226 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 29:
#line 230 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 30:
#line 234 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 31:
#line 240 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 32:
#line 244 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[(1) - (3)].access_level_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 33:
#line 250 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 34:
#line 254 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 35:
#line 258 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[(1) - (2)].ast_value), ast_new_member_decl((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 39:
#line 269 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 40:
#line 273 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 41:
#line 279 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (5)].chain_type_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 42:
#line 283 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (4)].chain_type_value), ast_new_blank());
	;}
    break;

  case 43:
#line 289 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.chain_type_value) = chain_type_super;
	;}
    break;

  case 44:
#line 293 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.chain_type_value) = chain_type_this;
	;}
    break;

  case 45:
#line 299 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 47:
#line 306 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[(2) - (8)].string_value), (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 48:
#line 310 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[(2) - (7)].string_value), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 49:
#line 316 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_method_decl((yyvsp[(1) - (9)].modifier_type_value), (yyvsp[(3) - (9)].string_value), (yyvsp[(5) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 50:
#line 320 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[(1) - (8)].modifier_type_value), (yyvsp[(3) - (8)].string_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 51:
#line 326 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[(1) - (4)].modifier_type_value), (yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].string_value));
	;}
    break;

  case 52:
#line 332 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.modifier_type_value) = modifier_none;
	;}
    break;

  case 53:
#line 336 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 54:
#line 340 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 55:
#line 344 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.modifier_type_value) = modifier_static;
	;}
    break;

  case 56:
#line 348 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.modifier_type_value) = modifier_native;
	;}
    break;

  case 57:
#line 354 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 58:
#line 358 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 59:
#line 362 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 60:
#line 368 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 61:
#line 372 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[(1) - (3)].string_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 62:
#line 378 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].string_value));
	;}
    break;

  case 63:
#line 382 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(1) - (4)].ast_value), (yyvsp[(2) - (4)].string_value), (yyvsp[(4) - (4)].ast_value))
	;}
    break;

  case 64:
#line 388 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 65:
#line 392 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(1) - (3)].ast_value)), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 66:
#line 398 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 67:
#line 402 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 68:
#line 408 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 69:
#line 414 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 70:
#line 418 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(1) - (3)].string_value)), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 73:
#line 428 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_generic_assign((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].assign_otype_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 74:
#line 432 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_generic_assign(ast_new_variable((yyvsp[(1) - (3)].string_value)), (yyvsp[(2) - (3)].assign_otype_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 75:
#line 438 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_def;
	;}
    break;

  case 76:
#line 442 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_add;
	;}
    break;

  case 77:
#line 446 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_sub;
	;}
    break;

  case 78:
#line 450 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_mul;
	;}
    break;

  case 79:
#line 454 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_div;
	;}
    break;

  case 80:
#line 458 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_mod;
	;}
    break;

  case 82:
#line 465 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_bit_or((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 83:
#line 469 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_logic_or((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 85:
#line 476 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_bit_and((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 86:
#line 480 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_logic_and((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 88:
#line 487 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_equal((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 89:
#line 491 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_notequal((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 91:
#line 498 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_gt((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 92:
#line 502 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_ge((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 93:
#line 506 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_lt((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 94:
#line 510 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_le((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 96:
#line 517 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_add((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 97:
#line 521 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_sub((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 99:
#line 528 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_mul((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 100:
#line 532 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_div((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 101:
#line 536 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_mod((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 103:
#line 543 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_not((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 104:
#line 547 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_neg((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 106:
#line 554 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_pre_inc((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 107:
#line 558 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_pre_dec((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 109:
#line 565 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 110:
#line 569 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_invoke((yyvsp[(1) - (5)].ast_value), (yyvsp[(3) - (5)].string_value), ast_new_blank());
	;}
    break;

  case 111:
#line 573 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_invoke((yyvsp[(1) - (6)].ast_value), (yyvsp[(3) - (6)].string_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 112:
#line 577 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_post_inc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 113:
#line 581 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_post_dec((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 118:
#line 591 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_true();
	;}
    break;

  case 119:
#line 595 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_false();
	;}
    break;

  case 120:
#line 599 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 121:
#line 603 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_call((yyvsp[(1) - (3)].string_value), ast_new_blank());
	;}
    break;

  case 122:
#line 607 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_call((yyvsp[(1) - (4)].string_value), (yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 123:
#line 611 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 124:
#line 615 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_cast((yyvsp[(2) - (4)].ast_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 125:
#line 619 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_static_invoke((yyvsp[(1) - (5)].ast_value), (yyvsp[(3) - (5)].string_value), ast_new_blank());
	;}
    break;

  case 126:
#line 623 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_static_invoke((yyvsp[(1) - (6)].ast_value), (yyvsp[(3) - (6)].string_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 127:
#line 627 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_field_access_fqcn((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 128:
#line 631 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_this();
	;}
    break;

  case 129:
#line 635 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_super();
	;}
    break;

  case 130:
#line 639 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (5)].ast_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 131:
#line 643 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (4)].ast_value), ast_new_blank());
	;}
    break;

  case 132:
#line 649 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 133:
#line 653 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 134:
#line 659 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 143:
#line 673 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].string_value));
	;}
    break;

  case 144:
#line 679 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 145:
#line 685 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 146:
#line 691 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 147:
#line 695 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(3) - (7)].ast_value), (yyvsp[(5) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 148:
#line 699 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 149:
#line 703 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(3) - (8)].ast_value), (yyvsp[(5) - (8)].ast_value), (yyvsp[(6) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value));
	;}
    break;

  case 151:
#line 710 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 152:
#line 716 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 153:
#line 722 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_while((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 154:
#line 728 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_break();
	;}
    break;

  case 155:
#line 734 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_continue();
	;}
    break;

  case 156:
#line 740 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_return((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 157:
#line 746 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 158:
#line 750 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 159:
#line 756 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 2767 "signal.tab.c"
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


#line 761 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"

