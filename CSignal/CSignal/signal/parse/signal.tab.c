
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"

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
//#define YYDEBUG 1
//#define YYERROR_VERBOSE 1


/* Line 189 of yacc.c  */
#line 89 "signal.tab.c"

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
     THROW = 331
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 15 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"

	char char_value;
	const char* string_value;
	ast* ast_value;
	assign_operator_type assign_otype_value;
	constructor_chain_type chain_type_value;
	modifier_type modifier_type_value;
	access_level access_level_value;



/* Line 214 of yacc.c  */
#line 213 "signal.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
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


/* Line 264 of yacc.c  */
#line 238 "signal.tab.c"

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
# if YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  95
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   770

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  69
/* YYNRULES -- Number of rules.  */
#define YYNRULES  181
/* YYNRULES -- Number of states.  */
#define YYNSTATES  338

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   331

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      77,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    13,    15,    17,    19,
      23,    27,    31,    33,    35,    37,    39,    42,    43,    45,
      47,    51,    54,    57,    58,    62,    64,    68,    71,    75,
      79,    80,    84,    90,    98,   104,   111,   117,   125,   126,
     128,   131,   132,   136,   137,   139,   142,   144,   146,   148,
     156,   163,   169,   174,   176,   178,   179,   181,   190,   198,
     209,   219,   224,   225,   228,   231,   233,   235,   237,   239,
     241,   243,   247,   250,   255,   257,   261,   263,   267,   269,
     271,   275,   277,   279,   283,   287,   289,   291,   293,   295,
     297,   299,   301,   305,   309,   311,   315,   319,   321,   325,
     329,   331,   335,   339,   343,   347,   349,   353,   357,   359,
     363,   367,   371,   373,   376,   379,   381,   384,   387,   389,
     393,   399,   406,   409,   412,   416,   418,   420,   422,   424,
     426,   428,   430,   432,   436,   441,   445,   450,   456,   463,
     467,   469,   471,   477,   482,   484,   487,   490,   492,   494,
     496,   498,   500,   502,   504,   506,   508,   510,   514,   520,
     526,   532,   540,   547,   556,   558,   561,   567,   573,   576,
     579,   583,   587,   591,   593,   596,   603,   607,   610,   612,
     614,   616
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      79,     0,    -1,    80,    -1,    79,    80,    -1,     1,    77,
      -1,   128,    -1,    87,    -1,    81,    -1,   104,    -1,    66,
      86,    82,    -1,    37,    85,    38,    -1,    66,    86,    82,
      -1,    93,    -1,    95,    -1,    94,    -1,    83,    -1,    84,
      83,    -1,    -1,    84,    -1,     7,    -1,    86,     8,     7,
      -1,    44,     4,    -1,     7,    89,    -1,    -1,    31,    90,
      29,    -1,    91,    -1,    91,     9,    90,    -1,     7,    92,
      -1,    61,     7,    92,    -1,    62,     7,    92,    -1,    -1,
      39,   112,    40,    -1,    53,    88,    37,    96,    38,    -1,
      53,    88,    11,   112,    37,    96,    38,    -1,    54,     7,
      37,   109,    38,    -1,    54,     7,    37,   109,     9,    38,
      -1,    52,    88,    37,    96,    38,    -1,    52,    88,    11,
     112,    37,    96,    38,    -1,    -1,    97,    -1,    96,    97,
      -1,    -1,   108,    11,    98,    -1,    -1,    99,    -1,    98,
      99,    -1,   100,    -1,   105,    -1,   106,    -1,    63,    60,
      39,   110,    40,   103,   145,    -1,    63,    60,    39,    40,
     103,   145,    -1,    11,   102,    39,   111,    40,    -1,    11,
     102,    39,    40,    -1,    47,    -1,    46,    -1,    -1,   101,
      -1,    64,     7,    39,   110,    40,    65,   113,   145,    -1,
      64,     7,    39,    40,    65,   113,   145,    -1,   107,    64,
       7,    89,    39,   110,    40,    65,   113,   145,    -1,   107,
      64,     7,    89,    39,    40,    65,   113,   145,    -1,   107,
     113,     7,    43,    -1,    -1,    58,    59,    -1,    59,    58,
      -1,    58,    -1,    59,    -1,    55,    -1,    56,    -1,    57,
      -1,     7,    -1,     7,     9,   109,    -1,   113,     7,    -1,
     113,     7,     9,   110,    -1,   115,    -1,   115,     9,   111,
      -1,   113,    -1,   113,     9,   112,    -1,   114,    -1,     7,
      -1,     7,    12,   114,    -1,   116,    -1,   118,    -1,   118,
     117,   116,    -1,     7,   117,   116,    -1,    19,    -1,    20,
      -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1,   119,
      -1,   118,    35,   119,    -1,   118,    36,   119,    -1,   120,
      -1,   119,    33,   120,    -1,   119,    34,   120,    -1,   121,
      -1,   120,    25,   121,    -1,   120,    26,   121,    -1,   122,
      -1,   121,    29,   122,    -1,   121,    30,   122,    -1,   121,
      31,   122,    -1,   121,    32,   122,    -1,   123,    -1,   122,
      13,   123,    -1,   122,    14,   123,    -1,   124,    -1,   123,
      15,   124,    -1,   123,    16,   124,    -1,   123,    17,   124,
      -1,   125,    -1,    18,   124,    -1,    14,   124,    -1,   126,
      -1,    27,   126,    -1,    28,   126,    -1,   127,    -1,   126,
       8,     7,    -1,   126,     8,     7,    39,    40,    -1,   126,
       8,     7,    39,   111,    40,    -1,   126,    27,    -1,   126,
      28,    -1,   126,    51,   113,    -1,     5,    -1,     6,    -1,
       3,    -1,     4,    -1,    48,    -1,    49,    -1,    50,    -1,
     114,    -1,     7,    39,    40,    -1,     7,    39,   111,    40,
      -1,    39,   115,    40,    -1,    39,   113,    40,   115,    -1,
     114,     8,     7,    39,    40,    -1,   114,     8,     7,    39,
     111,    40,    -1,   114,     8,     7,    -1,    46,    -1,    47,
      -1,    60,   113,    39,   111,    40,    -1,    60,   113,    39,
      40,    -1,   129,    -1,   128,   129,    -1,   115,   146,    -1,
     130,    -1,   131,    -1,   132,    -1,   133,    -1,   136,    -1,
     137,    -1,   138,    -1,   139,    -1,   140,    -1,   141,    -1,
     113,     7,    43,    -1,   113,     7,    19,   115,   146,    -1,
      45,     7,    19,   115,   146,    -1,    68,    39,   115,    40,
     144,    -1,    68,    39,   115,    40,   144,    70,   144,    -1,
      68,    39,   115,    40,   144,   134,    -1,    68,    39,   115,
      40,   144,   134,    70,   144,    -1,   135,    -1,   134,   135,
      -1,    69,    39,   115,    40,   144,    -1,    71,    39,   115,
      40,   145,    -1,    72,   146,    -1,    73,   146,    -1,    67,
     115,   146,    -1,    76,   115,   146,    -1,    74,   144,   142,
      -1,   143,    -1,   142,   143,    -1,    75,    39,   113,     7,
      40,   144,    -1,    37,   128,    38,    -1,    37,    38,    -1,
      43,    -1,   144,    -1,    43,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   118,   118,   119,   120,   127,   131,   135,   139,   146,
     153,   160,   164,   168,   172,   179,   183,   191,   194,   201,
     205,   212,   219,   227,   230,   237,   241,   248,   252,   256,
     264,   267,   274,   278,   285,   289,   296,   300,   308,   311,
     315,   323,   326,   334,   337,   341,   348,   349,   350,   354,
     358,   365,   369,   376,   380,   388,   391,   395,   399,   406,
     410,   417,   425,   428,   432,   436,   440,   447,   451,   455,
     462,   466,   473,   477,   484,   488,   495,   499,   506,   513,
     517,   529,   532,   533,   537,   543,   547,   551,   555,   559,
     563,   569,   570,   574,   580,   581,   585,   591,   592,   596,
     602,   603,   607,   611,   615,   621,   622,   626,   632,   633,
     637,   641,   647,   648,   652,   658,   659,   663,   669,   670,
     674,   678,   682,   686,   690,   696,   697,   698,   699,   700,
     704,   708,   712,   716,   720,   724,   728,   732,   736,   740,
     744,   748,   752,   756,   767,   771,   777,   781,   782,   783,
     784,   785,   786,   787,   788,   789,   790,   793,   799,   805,
     811,   815,   819,   823,   829,   830,   836,   842,   848,   854,
     860,   866,   872,   878,   882,   888,   899,   903,   909,   913,
     916,   917
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
  "IMPORT", "VAR", "THIS", "SUPER", "TRUE", "FALSE", "NULL_TOK", "AS",
  "INTERFACE", "CLASS", "ENUM", "PUBLIC", "PRIVATE", "PROTECTED", "STATIC",
  "NATIVE", "NEW", "IN", "OUT", "CTOR", "DEF", "ARROW", "NAMESPACE",
  "RETURN", "IF", "ELIF", "ELSE", "WHILE", "BREAK", "CONTINUE", "TRY",
  "CATCH", "THROW", "'\\n'", "$accept", "root", "top_level",
  "namespace_decl", "namespace_body", "namespace_member_decl",
  "namespace_member_decl_list", "namespace_member_decl_optional",
  "namespace_path", "import", "parameterized_typename",
  "type_parameter_group", "type_parameter_list", "type_parameter",
  "type_parameter_rule_list", "class_decl", "enum_decl", "interface_decl",
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
     325,   326,   327,   328,   329,   330,   331,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    79,    79,    79,    80,    80,    80,    80,    81,
      82,    83,    83,    83,    83,    84,    84,    85,    85,    86,
      86,    87,    88,    89,    89,    90,    90,    91,    91,    91,
      92,    92,    93,    93,    94,    94,    95,    95,    96,    96,
      96,    97,    97,    98,    98,    98,    99,    99,    99,   100,
     100,   101,   101,   102,   102,   103,   103,   104,   104,   105,
     105,   106,   107,   107,   107,   107,   107,   108,   108,   108,
     109,   109,   110,   110,   111,   111,   112,   112,   113,   114,
     114,   115,   116,   116,   116,   117,   117,   117,   117,   117,
     117,   118,   118,   118,   119,   119,   119,   120,   120,   120,
     121,   121,   121,   121,   121,   122,   122,   122,   123,   123,
     123,   123,   124,   124,   124,   125,   125,   125,   126,   126,
     126,   126,   126,   126,   126,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   128,   128,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   130,   131,   132,
     133,   133,   133,   133,   134,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   142,   143,   144,   144,   145,   145,
     146,   146
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     1,     1,     3,
       3,     3,     1,     1,     1,     1,     2,     0,     1,     1,
       3,     2,     2,     0,     3,     1,     3,     2,     3,     3,
       0,     3,     5,     7,     5,     6,     5,     7,     0,     1,
       2,     0,     3,     0,     1,     2,     1,     1,     1,     7,
       6,     5,     4,     1,     1,     0,     1,     8,     7,    10,
       9,     4,     0,     2,     2,     1,     1,     1,     1,     1,
       1,     3,     2,     4,     1,     3,     1,     3,     1,     1,
       3,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     2,     2,     1,     2,     2,     1,     3,
       5,     6,     2,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     4,     3,     4,     5,     6,     3,
       1,     1,     5,     4,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     5,     5,
       5,     7,     6,     8,     1,     2,     5,     5,     2,     2,
       3,     3,     3,     1,     2,     6,     3,     2,     1,     1,
       1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,   127,   128,   125,   126,    79,     0,     0,     0,
       0,     0,     0,     0,   140,   141,   129,   130,   131,     0,
       0,     0,     0,     0,     0,   181,   181,     0,     0,     0,
       2,     7,     6,     8,     0,   132,   181,    81,    82,    91,
      94,    97,   100,   105,   108,   112,   115,   118,     5,   144,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
       4,     0,    85,    86,    87,    88,    89,    90,     0,     0,
      79,   132,   114,   113,   116,   117,     0,     0,    21,     0,
      79,     0,    78,     0,    19,     0,   181,     0,     0,   180,
     168,   169,     0,     0,   181,     1,     3,     0,     0,   146,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   122,   123,     0,
     145,    80,   133,     0,    74,    84,     0,   135,     0,     0,
       0,     0,    17,     9,   170,     0,     0,   177,     0,     0,
     172,   173,   171,     0,   157,   139,    92,    93,    83,    95,
      96,    98,    99,   101,   102,   103,   104,   106,   107,   109,
     110,   111,   119,   124,   134,     0,   136,   181,   143,     0,
       0,     0,     0,    20,     0,     0,     0,     0,    15,    18,
       0,    12,    14,    13,     0,     0,   176,     0,   174,   181,
       0,     0,    75,   159,   142,     0,     0,    72,    23,     0,
       0,     0,     0,    16,    10,   160,   178,   179,   167,     0,
     158,   137,     0,   120,     0,     0,     0,     0,     0,    22,
       0,    38,     0,    38,     0,    11,     0,     0,   162,   164,
       0,   138,   121,    58,     0,    73,    30,     0,     0,     0,
      25,     0,    76,    67,    68,    69,     0,    39,     0,     0,
       0,    70,     0,     0,   161,     0,   165,     0,    57,     0,
      27,    30,    30,    24,     0,    38,     0,    36,    40,    43,
      38,    32,     0,     0,    34,     0,   163,   175,     0,    28,
      29,    26,     0,    77,    65,    66,     0,    42,    44,    46,
      47,    48,     0,     0,    71,    35,     0,    31,    37,    63,
      64,     0,    45,     0,     0,    33,   166,     0,    23,     0,
      55,     0,     0,    61,     0,    56,     0,    55,     0,    54,
      53,     0,    50,     0,     0,     0,     0,    49,     0,     0,
      52,     0,     0,     0,    51,    60,     0,    59
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    29,    30,    31,   133,   178,   179,   180,    85,    32,
     199,   219,   239,   240,   260,   181,   182,   183,   246,   247,
     287,   288,   289,   315,   321,   316,    33,   290,   291,   292,
     248,   252,   171,   123,   241,    34,    71,   124,    37,    69,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,   228,   229,    54,    55,
      56,    57,    58,    59,   140,   141,   207,   208,    90
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -214
static const yytype_int16 yypact[] =
{
     350,   -68,  -214,  -214,  -214,  -214,   131,   684,   684,    33,
      33,   710,    39,    40,  -214,  -214,  -214,  -214,  -214,    42,
      81,   100,   710,    70,    72,    71,    71,    95,   710,   299,
    -214,  -214,  -214,  -214,   113,    15,    71,  -214,   153,    19,
      97,   136,   123,   166,  -214,  -214,     7,  -214,   503,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,    42,  -214,  -214,  -214,  -214,  -214,  -214,   240,   710,
      59,   132,  -214,  -214,     7,     7,   129,   145,  -214,   125,
     182,   173,  -214,   186,  -214,    25,    71,   710,   710,  -214,
    -214,  -214,   401,   146,    71,  -214,  -214,     2,   219,  -214,
     684,   684,   710,   684,   684,   684,   684,   684,   684,   684,
     684,   684,   684,   684,   684,   684,   220,  -214,  -214,    42,
    -214,  -214,  -214,   188,   221,  -214,   710,  -214,   710,   554,
      10,   225,    73,  -214,  -214,   193,   194,  -214,   452,   196,
     146,  -214,  -214,   710,  -214,   197,    19,    19,  -214,    97,
      97,   136,   136,   123,   123,   123,   123,   166,   166,  -214,
    -214,  -214,   198,  -214,  -214,   710,  -214,    71,  -214,   199,
     175,   201,   231,  -214,   235,   235,   241,   100,  -214,    73,
     211,  -214,  -214,  -214,    95,    63,  -214,    42,  -214,    71,
     581,   619,  -214,  -214,  -214,    42,   187,   242,   222,    75,
      76,   218,    25,  -214,  -214,    78,  -214,  -214,  -214,   253,
    -214,  -214,   223,  -214,   224,    63,    42,    42,    13,  -214,
      42,   141,    42,   141,   254,  -214,   226,    95,    87,  -214,
     229,  -214,  -214,  -214,    63,  -214,   232,   255,   265,   244,
     266,   237,   267,  -214,  -214,  -214,    46,  -214,   270,   245,
      61,   268,    47,   710,  -214,    95,  -214,    95,  -214,    42,
    -214,   232,   232,  -214,    13,   141,    42,  -214,  -214,   121,
     141,  -214,   254,   246,  -214,   238,  -214,  -214,   251,  -214,
    -214,  -214,   104,  -214,   234,   227,   236,     6,  -214,  -214,
    -214,  -214,     9,   107,  -214,  -214,    95,  -214,  -214,  -214,
    -214,   256,  -214,   287,   290,  -214,  -214,    17,   222,   258,
     297,   271,   273,  -214,   157,  -214,    63,   297,    23,  -214,
    -214,   275,  -214,    63,   250,   276,   646,  -214,    42,   257,
    -214,   280,    63,    42,  -214,  -214,    63,  -214
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -214,  -214,   281,  -214,   119,   144,  -214,  -214,   148,  -214,
     154,    22,    67,  -214,   -62,  -214,  -214,  -214,  -211,  -204,
    -214,    45,  -214,  -214,  -214,    18,  -214,  -214,  -214,  -214,
    -214,    62,  -213,  -124,  -162,    -9,     0,     3,   -25,   298,
    -214,   105,   106,   109,    83,   112,    20,  -214,   209,  -214,
     247,   -42,  -214,  -214,  -214,  -214,  -214,   114,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,   200,   -26,  -208,   -18
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -79
static const yytype_int16 yytable[] =
{
      35,    93,    76,    36,   235,   169,   120,   233,    91,    60,
      81,    35,   250,   -62,    77,   116,    80,    80,    99,    82,
     236,   143,   -78,    98,    80,    86,   258,    72,    73,    35,
      80,    94,    36,   131,   117,   118,     2,     3,     4,     5,
      70,   192,   268,    78,   125,   144,   268,    79,    35,    80,
     170,    36,   103,   104,   282,   -78,   273,   310,   119,   293,
     249,   121,   132,   324,   284,   285,   212,   214,   134,   286,
     -62,    61,    11,   303,   237,   238,   142,   148,   268,    14,
      15,    16,    17,    18,   267,   274,   220,   222,    83,   268,
     135,   136,    35,    19,   311,    36,   120,   278,    68,   271,
      92,   243,   244,   245,   283,   325,   206,    84,   322,    87,
     163,    88,   221,   223,    89,   327,   243,   244,   245,    82,
      97,   172,   105,   106,   335,   174,   175,   176,   337,   166,
      82,   167,    92,   159,   160,   161,   111,   112,    35,   177,
      98,    36,   298,    61,   128,   305,   189,   226,   227,   193,
      62,    63,    64,    65,    66,    67,   226,   255,   205,   243,
     244,   245,   243,   244,   245,   107,   108,   109,   110,   126,
      68,   210,    62,    63,    64,    65,    66,    67,   209,   284,
     285,   113,   114,   115,   286,   127,   215,    82,   100,   101,
     153,   154,   155,   156,    61,    82,   243,   244,   245,   279,
     280,   254,   331,   319,   320,   146,   147,   234,   172,   149,
     150,   242,   129,   242,   151,   152,    82,    82,    74,    75,
      82,   139,    82,   157,   158,   130,   145,   162,   164,   276,
     165,   277,   173,   184,   185,   187,   190,   191,   197,   194,
     195,   196,   198,     2,     3,     4,     5,     6,   201,   204,
     242,   217,   216,   218,     7,   224,   275,   242,     8,    82,
     230,   251,   261,   231,   232,   253,    82,     9,    10,   257,
     306,   259,   262,   263,   265,   264,   266,   272,   296,    11,
     122,   269,   270,   304,   295,   300,    14,    15,    16,    17,
      18,   297,    82,   299,   308,   307,   301,   309,   172,    95,
      19,   313,     2,     3,     4,     5,     6,    82,   314,   172,
      96,   317,   318,     7,   326,   328,   329,     8,    82,   332,
     334,   225,   333,   203,   336,   202,     9,    10,    82,   200,
     312,   281,   302,    82,   294,   323,   102,     0,    11,   138,
     188,     0,   256,    12,    13,    14,    15,    16,    17,    18,
       0,     1,     0,     2,     3,     4,     5,     6,     0,    19,
       0,     0,     0,    20,     7,    21,    22,    23,     8,     0,
      24,    25,    26,    27,     0,    28,     0,     9,    10,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
       0,     0,     0,     0,    12,    13,    14,    15,    16,    17,
      18,     0,     0,     0,     2,     3,     4,     5,     6,     0,
      19,     0,     0,     0,    20,     7,    21,    22,    23,     8,
       0,    24,    25,    26,    27,     0,    28,     0,     9,    10,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   137,
      11,     0,     0,     0,     0,     0,    13,    14,    15,    16,
      17,    18,     0,     0,     0,     2,     3,     4,     5,     6,
       0,    19,     0,     0,     0,     0,     7,     0,    22,    23,
       8,     0,    24,    25,    26,    27,     0,    28,     0,     9,
      10,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     186,    11,     0,     0,     0,     0,     0,    13,    14,    15,
      16,    17,    18,     0,     0,     0,     2,     3,     4,     5,
       6,     0,    19,     0,     0,     0,     0,     7,     0,    22,
      23,     8,     0,    24,    25,    26,    27,     0,    28,     0,
       9,    10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    11,     0,     0,     0,     0,     0,    13,    14,
      15,    16,    17,    18,     0,     0,     0,     2,     3,     4,
       5,     6,     0,    19,     0,     0,     0,     0,     7,     0,
      22,    23,     8,     0,    24,    25,    26,    27,     0,    28,
       0,     9,    10,     0,     2,     3,     4,     5,     6,     0,
       0,     0,     0,    11,   168,     7,     0,     0,     0,     8,
      14,    15,    16,    17,    18,     0,     0,     0,     9,    10,
       0,     0,     0,     0,    19,     0,     0,     0,     0,     0,
      11,   211,     2,     3,     4,     5,     6,    14,    15,    16,
      17,    18,     0,     7,     0,     0,     0,     8,     0,     0,
       0,    19,     0,     0,     0,     0,     9,    10,     0,     2,
       3,     4,     5,     6,     0,     0,     0,     0,    11,   213,
       7,     0,     0,     0,     8,    14,    15,    16,    17,    18,
       0,     0,     0,     9,    10,     0,     0,     0,     0,    19,
       0,     0,     0,     0,     0,    11,   330,     2,     3,     4,
       5,    70,    14,    15,    16,    17,    18,     0,     7,     0,
       0,     0,     8,     0,     0,     0,    19,     0,     0,     0,
       0,     9,    10,     2,     3,     4,     5,     6,     0,     0,
       0,     0,     0,    11,     7,     0,     0,     0,     8,     0,
      14,    15,    16,    17,    18,     0,     0,     9,    10,     0,
       0,     0,     0,     0,    19,     0,     0,     0,     0,    11,
       0,     0,     0,     0,     0,     0,    14,    15,    16,    17,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      19
};

static const yytype_int16 yycheck[] =
{
       0,    27,    11,     0,   217,   129,    48,   215,    26,    77,
      19,    11,   223,     7,    11,     8,     7,     7,    36,    19,
       7,    19,     7,     8,     7,    22,   234,     7,     8,    29,
       7,    28,    29,     8,    27,    28,     3,     4,     5,     6,
       7,   165,   246,     4,    69,    43,   250,     7,    48,     7,
      40,    48,    33,    34,   265,    40,     9,    40,    51,   270,
     222,    61,    37,    40,    58,    59,   190,   191,    86,    63,
      64,    12,    39,    64,    61,    62,    94,   102,   282,    46,
      47,    48,    49,    50,    38,    38,    11,    11,     7,   293,
      87,    88,    92,    60,   307,    92,   138,   259,    39,    38,
      37,    55,    56,    57,   266,   318,    43,     7,   316,    39,
     119,    39,    37,    37,    43,   323,    55,    56,    57,   119,
       7,   130,    25,    26,   332,    52,    53,    54,   336,   126,
     130,   128,    37,   113,   114,   115,    13,    14,   138,    66,
       8,   138,    38,    12,    19,    38,   143,    69,    70,   167,
      19,    20,    21,    22,    23,    24,    69,    70,   184,    55,
      56,    57,    55,    56,    57,    29,    30,    31,    32,    40,
      39,   189,    19,    20,    21,    22,    23,    24,   187,    58,
      59,    15,    16,    17,    63,    40,   195,   187,    35,    36,
     107,   108,   109,   110,    12,   195,    55,    56,    57,   261,
     262,   227,   326,    46,    47,   100,   101,   216,   217,   103,
     104,   220,    39,   222,   105,   106,   216,   217,     9,    10,
     220,    75,   222,   111,   112,    39,     7,     7,    40,   255,
       9,   257,     7,    40,    40,    39,    39,    39,     7,    40,
      65,    40,     7,     3,     4,     5,     6,     7,     7,    38,
     259,     9,    65,    31,    14,    37,   253,   266,    18,   259,
       7,     7,     7,    40,    40,    39,   266,    27,    28,    40,
     296,    39,     7,    29,    37,     9,     9,     9,    40,    39,
      40,    11,    37,   292,    38,    58,    46,    47,    48,    49,
      50,    40,   292,    59,     7,    39,    60,     7,   307,     0,
      60,    43,     3,     4,     5,     6,     7,   307,    11,   318,
      29,    40,    39,    14,    39,    65,    40,    18,   318,   328,
      40,   202,    65,   179,   333,   177,    27,    28,   328,   175,
     308,   264,   287,   333,   272,   317,    38,    -1,    39,    92,
     140,    -1,   228,    44,    45,    46,    47,    48,    49,    50,
      -1,     1,    -1,     3,     4,     5,     6,     7,    -1,    60,
      -1,    -1,    -1,    64,    14,    66,    67,    68,    18,    -1,
      71,    72,    73,    74,    -1,    76,    -1,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,
      60,    -1,    -1,    -1,    64,    14,    66,    67,    68,    18,
      -1,    71,    72,    73,    74,    -1,    76,    -1,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    -1,    -1,    -1,     3,     4,     5,     6,     7,
      -1,    60,    -1,    -1,    -1,    -1,    14,    -1,    67,    68,
      18,    -1,    71,    72,    73,    74,    -1,    76,    -1,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    -1,    -1,    -1,     3,     4,     5,     6,
       7,    -1,    60,    -1,    -1,    -1,    -1,    14,    -1,    67,
      68,    18,    -1,    71,    72,    73,    74,    -1,    76,    -1,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    -1,    -1,    -1,     3,     4,     5,
       6,     7,    -1,    60,    -1,    -1,    -1,    -1,    14,    -1,
      67,    68,    18,    -1,    71,    72,    73,    74,    -1,    76,
      -1,    27,    28,    -1,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    39,    40,    14,    -1,    -1,    -1,    18,
      46,    47,    48,    49,    50,    -1,    -1,    -1,    27,    28,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,
      39,    40,     3,     4,     5,     6,     7,    46,    47,    48,
      49,    50,    -1,    14,    -1,    -1,    -1,    18,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    -1,    27,    28,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    39,    40,
      14,    -1,    -1,    -1,    18,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    60,
      -1,    -1,    -1,    -1,    -1,    39,    40,     3,     4,     5,
       6,     7,    46,    47,    48,    49,    50,    -1,    14,    -1,
      -1,    -1,    18,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    27,    28,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    39,    14,    -1,    -1,    -1,    18,    -1,
      46,    47,    48,    49,    50,    -1,    -1,    27,    28,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,    14,    18,    27,
      28,    39,    44,    45,    46,    47,    48,    49,    50,    60,
      64,    66,    67,    68,    71,    72,    73,    74,    76,    79,
      80,    81,    87,   104,   113,   114,   115,   116,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   136,   137,   138,   139,   140,   141,
      77,    12,    19,    20,    21,    22,    23,    24,    39,   117,
       7,   114,   124,   124,   126,   126,   113,   115,     4,     7,
       7,   113,   114,     7,     7,    86,   115,    39,    39,    43,
     146,   146,    37,   144,   115,     0,    80,     7,     8,   146,
      35,    36,   117,    33,    34,    25,    26,    29,    30,    31,
      32,    13,    14,    15,    16,    17,     8,    27,    28,    51,
     129,   114,    40,   111,   115,   116,    40,    40,    19,    39,
      39,     8,    37,    82,   146,   115,   115,    38,   128,    75,
     142,   143,   146,    19,    43,     7,   119,   119,   116,   120,
     120,   121,   121,   122,   122,   122,   122,   123,   123,   124,
     124,   124,     7,   113,    40,     9,   115,   115,    40,   111,
      40,   110,   113,     7,    52,    53,    54,    66,    83,    84,
      85,    93,    94,    95,    40,    40,    38,    39,   143,   115,
      39,    39,   111,   146,    40,    65,    40,     7,     7,    88,
      88,     7,    86,    83,    38,   144,    43,   144,   145,   113,
     146,    40,   111,    40,   111,   113,    65,     9,    31,    89,
      11,    37,    11,    37,    37,    82,    69,    70,   134,   135,
       7,    40,    40,   145,   113,   110,     7,    61,    62,    90,
      91,   112,   113,    55,    56,    57,    96,    97,   108,   112,
      96,     7,   109,    39,   144,    70,   135,    40,   145,    39,
      92,     7,     7,    29,     9,    37,     9,    38,    97,    11,
      37,    38,     9,     9,    38,   115,   144,   144,   112,    92,
      92,    90,    96,   112,    58,    59,    63,    98,    99,   100,
     105,   106,   107,    96,   109,    38,    40,    40,    38,    59,
      58,    60,    99,    64,   113,    38,   144,    39,     7,     7,
      40,   110,    89,    43,    11,   101,   103,    40,    39,    46,
      47,   102,   145,   103,    40,   110,    39,   145,    65,    40,
      40,   111,   113,    65,    40,   145,   113,   145
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
# if YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1455 of yacc.c  */
#line 121 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 128 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 132 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 136 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 140 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 147 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 154 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value)
	;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 161 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 165 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 169 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 173 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 180 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 184 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 191 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 195 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 202 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 206 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 213 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 220 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_parameterized_typename((yyvsp[(1) - (2)].string_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 227 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 231 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 238 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 242 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_type_parameter_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 249 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_type_parameter((yyvsp[(1) - (2)].string_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 253 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_type_in_parameter((yyvsp[(2) - (3)].string_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 257 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_type_out_parameter((yyvsp[(2) - (3)].string_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 264 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 268 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_type_parameter_rule_list((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 275 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 279 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 286 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 290 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (6)].string_value), (yyvsp[(4) - (6)].ast_value));
	;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 297 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (5)].ast_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 301 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (7)].ast_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 308 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 312 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 316 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 323 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 327 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[(1) - (3)].access_level_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 334 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 338 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 342 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[(1) - (2)].ast_value), ast_new_member_decl((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 355 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 359 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 366 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (5)].chain_type_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 370 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (4)].chain_type_value), ast_new_blank());
	;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 377 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.chain_type_value) = chain_type_super;
	;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 381 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.chain_type_value) = chain_type_this;
	;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 388 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 396 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[(2) - (8)].string_value), (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 400 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[(2) - (7)].string_value), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 407 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_method_decl((yyvsp[(1) - (10)].modifier_type_value), (yyvsp[(3) - (10)].string_value), (yyvsp[(4) - (10)].ast_value), (yyvsp[(6) - (10)].ast_value), (yyvsp[(10) - (10)].ast_value), (yyvsp[(9) - (10)].ast_value));
	;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 411 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[(1) - (9)].modifier_type_value), (yyvsp[(3) - (9)].string_value), (yyvsp[(4) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 418 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[(1) - (4)].modifier_type_value), (yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].string_value));
	;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 425 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_none;
	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 429 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 433 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 437 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_static;
	;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 441 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_native;
	;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 448 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 452 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 456 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 463 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 467 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[(1) - (3)].string_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 474 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].string_value));
	;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 478 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(1) - (4)].ast_value), (yyvsp[(2) - (4)].string_value), (yyvsp[(4) - (4)].ast_value))
	;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 485 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 489 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(1) - (3)].ast_value)), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 496 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 500 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 507 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 514 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 518 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(1) - (3)].string_value)), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 534 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_generic_assign((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].assign_otype_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 538 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_generic_assign(ast_new_variable_fromstr((yyvsp[(1) - (3)].string_value)), (yyvsp[(2) - (3)].assign_otype_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 544 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_def;
	;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 548 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_add;
	;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 552 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_sub;
	;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 556 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_mul;
	;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 560 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_div;
	;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 564 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_mod;
	;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 571 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_bit_or((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 575 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_logic_or((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 582 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_bit_and((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 586 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_logic_and((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 593 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_equal((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 597 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_notequal((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 604 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_gt((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 608 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_ge((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 612 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_lt((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 616 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_le((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 623 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_add((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 627 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_sub((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 634 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_mul((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 638 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_div((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 642 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_mod((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 649 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_not((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 653 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_neg((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 660 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_pre_inc((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 664 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_pre_dec((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 671 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 675 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_invoke((yyvsp[(1) - (5)].ast_value), (yyvsp[(3) - (5)].string_value), ast_new_blank());
	;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 679 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_invoke((yyvsp[(1) - (6)].ast_value), (yyvsp[(3) - (6)].string_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 683 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_post_inc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 687 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_post_dec((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 691 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_as((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 701 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_true();
	;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 705 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_false();
	;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 709 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_null();
	;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 713 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 717 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_call((yyvsp[(1) - (3)].string_value), ast_new_blank());
	;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 721 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_call((yyvsp[(1) - (4)].string_value), (yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 725 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 729 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_cast((yyvsp[(2) - (4)].ast_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 733 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_static_invoke((yyvsp[(1) - (5)].ast_value), (yyvsp[(3) - (5)].string_value), ast_new_blank());
	;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 737 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_static_invoke((yyvsp[(1) - (6)].ast_value), (yyvsp[(3) - (6)].string_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 741 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_field_access_fqcn((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 745 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_this();
	;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 749 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_super();
	;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 753 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (5)].ast_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 757 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (4)].ast_value), ast_new_blank());
	;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 768 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 772 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 778 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 794 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].string_value));
	;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 800 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 806 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 812 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 816 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(3) - (7)].ast_value), (yyvsp[(5) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 820 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 824 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(3) - (8)].ast_value), (yyvsp[(5) - (8)].ast_value), (yyvsp[(6) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value));
	;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 831 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 837 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 843 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_while((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 849 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_break();
	;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 855 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_continue();
	;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 861 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_return((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 867 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 873 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_try((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 879 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 883 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 889 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[(3) - (6)].ast_value), (yyvsp[(4) - (6)].string_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 900 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 904 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 910 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;



/* Line 1455 of yacc.c  */
#line 3196 "signal.tab.c"
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
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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



/* Line 1675 of yacc.c  */
#line 919 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"





