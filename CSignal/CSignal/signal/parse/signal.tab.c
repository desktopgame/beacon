
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
#include "../ast/ast_new_operator.h"
#include "../ast/ast_new_stmt.h"
#include "../ast/ast_new_decl.h"
#include "../ast/constructor_chain_type.h"
#include "../ast/assign_operator_type.h"
#include "../ast/modifier_type.h"
#include "../ast/access_level.h"
#define YYDEBUG 1
#define YYERROR_VERBOSE 1


/* Line 189 of yacc.c  */
#line 88 "signal.tab.c"

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
     COLON = 265,
     COLO_COLO = 266,
     ADD = 267,
     SUB = 268,
     MUL = 269,
     DIV = 270,
     MOD = 271,
     NOT = 272,
     ASSIGN = 273,
     ADD_ASSIGN = 274,
     SUB_ASSIGN = 275,
     MUL_ASSIGN = 276,
     DIV_ASSIGN = 277,
     MOD_ASSIGN = 278,
     EQUAL = 279,
     NOTEQUAL = 280,
     INC = 281,
     DEC = 282,
     GT = 283,
     GE = 284,
     LT = 285,
     LE = 286,
     BIT_AND = 287,
     LOGIC_AND = 288,
     BIT_OR = 289,
     LOGIC_OR = 290,
     LCB = 291,
     RCB = 292,
     LRB = 293,
     RRB = 294,
     LSB = 295,
     RSB = 296,
     SEMI = 297,
     IMPORT = 298,
     THIS = 299,
     SUPER = 300,
     CLASS = 301,
     PUBLIC = 302,
     PRIVATE = 303,
     PROTECTED = 304,
     STATIC = 305,
     NATIVE = 306,
     NEW = 307,
     DEF = 308,
     ARROW = 309,
     NAMESPACE = 310,
     IF = 311,
     ELIF = 312,
     ELSE = 313
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 14 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"

	char char_value;
	const char* string_value;
	ast* ast_value;
	assign_operator_type assign_otype_value;
	constructor_chain_type chain_type_value;
	modifier_type modifier_type_value;
	access_level access_level_value;



/* Line 214 of yacc.c  */
#line 194 "signal.tab.c"
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
#line 219 "signal.tab.c"

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
#define YYFINAL  53
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   371

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  130
/* YYNRULES -- Number of states.  */
#define YYNSTATES  222

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   313

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      59,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      55,    56,    57,    58
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    13,    15,    17,    21,
      25,    29,    31,    33,    36,    37,    39,    41,    45,    48,
      55,    56,    59,    60,    62,    65,    66,    70,    71,    73,
      76,    78,    80,    82,    90,    97,   103,   108,   110,   112,
     113,   115,   125,   134,   139,   140,   143,   146,   148,   150,
     152,   154,   156,   159,   164,   166,   170,   172,   174,   178,
     180,   182,   186,   188,   190,   192,   194,   196,   198,   200,
     204,   208,   210,   214,   218,   220,   224,   228,   230,   234,
     238,   242,   246,   248,   252,   256,   258,   262,   266,   270,
     272,   275,   278,   280,   283,   286,   288,   294,   301,   304,
     307,   309,   311,   313,   315,   317,   321,   326,   330,   336,
     343,   345,   347,   349,   352,   355,   357,   359,   361,   365,
     371,   377,   385,   392,   401,   403,   406,   412,   416,   419,
     421
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      61,     0,    -1,    62,    -1,    61,    62,    -1,     1,    59,
      -1,   101,    -1,    69,    -1,    63,    -1,    55,    68,    64,
      -1,    36,    67,    37,    -1,    55,    68,    64,    -1,    70,
      -1,    65,    -1,    66,    65,    -1,    -1,    66,    -1,     7,
      -1,    68,     8,     7,    -1,    43,     4,    -1,    46,     7,
      71,    36,    72,    37,    -1,    -1,    10,     7,    -1,    -1,
      73,    -1,    72,    73,    -1,    -1,    83,    10,    74,    -1,
      -1,    75,    -1,    74,    75,    -1,    76,    -1,    80,    -1,
      81,    -1,    53,    52,    38,    84,    39,    79,   109,    -1,
      53,    52,    38,    39,    79,   109,    -1,    10,    78,    38,
      85,    39,    -1,    10,    78,    38,    39,    -1,    45,    -1,
      44,    -1,    -1,    77,    -1,    82,    53,     7,    38,    84,
      39,    54,    86,   109,    -1,    82,    53,     7,    38,    39,
      54,    86,   109,    -1,    82,    86,     7,    42,    -1,    -1,
      50,    51,    -1,    51,    50,    -1,    50,    -1,    51,    -1,
      47,    -1,    48,    -1,    49,    -1,    86,     7,    -1,    86,
       7,     9,    84,    -1,    88,    -1,    88,     9,    85,    -1,
      87,    -1,     7,    -1,     7,    11,    87,    -1,    89,    -1,
      91,    -1,    91,    90,    89,    -1,    18,    -1,    19,    -1,
      20,    -1,    21,    -1,    22,    -1,    23,    -1,    92,    -1,
      91,    34,    92,    -1,    91,    35,    92,    -1,    93,    -1,
      92,    32,    93,    -1,    92,    33,    93,    -1,    94,    -1,
      93,    24,    94,    -1,    93,    25,    94,    -1,    95,    -1,
      94,    28,    95,    -1,    94,    29,    95,    -1,    94,    30,
      95,    -1,    94,    31,    95,    -1,    96,    -1,    95,    12,
      96,    -1,    95,    13,    96,    -1,    97,    -1,    96,    14,
      97,    -1,    96,    15,    97,    -1,    96,    16,    97,    -1,
      98,    -1,    17,    97,    -1,    13,    97,    -1,    99,    -1,
      26,    99,    -1,    27,    99,    -1,   100,    -1,    99,     8,
       7,    38,    39,    -1,    99,     8,     7,    38,    85,    39,
      -1,    99,    26,    -1,    99,    27,    -1,     5,    -1,     6,
      -1,     3,    -1,     4,    -1,     7,    -1,     7,    38,    39,
      -1,     7,    38,    85,    39,    -1,    38,    88,    39,    -1,
      87,     8,     7,    38,    39,    -1,    87,     8,     7,    38,
      85,    39,    -1,    44,    -1,    45,    -1,   102,    -1,   101,
     102,    -1,    88,    42,    -1,   103,    -1,   104,    -1,   105,
      -1,    86,     7,    42,    -1,    86,     7,    18,    88,    42,
      -1,    56,    38,    88,    39,   108,    -1,    56,    38,    88,
      39,   108,    58,   108,    -1,    56,    38,    88,    39,   108,
     106,    -1,    56,    38,    88,    39,   108,   106,    58,   108,
      -1,   107,    -1,   106,   107,    -1,    57,    38,    88,    39,
     108,    -1,    36,   101,    37,    -1,    36,    37,    -1,    42,
      -1,   108,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    93,    93,    94,    95,   101,   105,   109,   115,   121,
     127,   131,   137,   141,   148,   151,   157,   161,   167,   173,
     180,   183,   190,   193,   197,   204,   207,   214,   217,   221,
     227,   228,   229,   232,   236,   242,   246,   252,   256,   263,
     266,   269,   273,   279,   286,   289,   293,   297,   301,   307,
     311,   315,   321,   325,   331,   335,   341,   347,   351,   357,
     360,   361,   367,   371,   375,   379,   383,   387,   393,   394,
     398,   404,   405,   409,   415,   416,   420,   426,   427,   431,
     435,   439,   445,   446,   450,   456,   457,   461,   465,   471,
     472,   476,   482,   483,   487,   493,   494,   498,   502,   506,
     512,   513,   514,   515,   516,   520,   524,   528,   532,   536,
     540,   544,   550,   554,   560,   564,   565,   566,   569,   575,
     581,   585,   589,   593,   599,   600,   606,   612,   616,   622,
     626
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR_LITERAL", "STRING_LITERAL", "INT",
  "DOUBLE", "IDENT", "DOT", "COMMA", "COLON", "COLO_COLO", "ADD", "SUB",
  "MUL", "DIV", "MOD", "NOT", "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN",
  "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "EQUAL", "NOTEQUAL", "INC",
  "DEC", "GT", "GE", "LT", "LE", "BIT_AND", "LOGIC_AND", "BIT_OR",
  "LOGIC_OR", "LCB", "RCB", "LRB", "RRB", "LSB", "RSB", "SEMI", "IMPORT",
  "THIS", "SUPER", "CLASS", "PUBLIC", "PRIVATE", "PROTECTED", "STATIC",
  "NATIVE", "NEW", "DEF", "ARROW", "NAMESPACE", "IF", "ELIF", "ELSE",
  "'\\n'", "$accept", "root", "top_level", "namespace_decl",
  "namespace_body", "namespace_member_decl", "namespace_member_decl_list",
  "namespace_member_decl_optional", "namespace_path", "import",
  "class_decl", "class_super", "access_member_tree", "access_member_list",
  "member_define_list", "member_define", "constructor_define",
  "constructor_chain", "constructor_chain_type_T",
  "constructor_chain_optional", "func_define", "field_define",
  "modifier_type_T", "access_level_T", "parameter_list", "argument_list",
  "typename_T", "fqcn_part", "expression", "assign", "assign_type_T", "or",
  "and", "equal", "compare", "addsub", "muldiv", "unary", "prefix",
  "postfix", "primary", "stmt_list", "stmt", "variable_decl_stmt",
  "variable_init_stmt", "if_stmt", "elif_list", "elif", "scope",
  "scope_optional", 0
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    61,    61,    62,    62,    62,    63,    64,
      65,    65,    66,    66,    67,    67,    68,    68,    69,    70,
      71,    71,    72,    72,    72,    73,    73,    74,    74,    74,
      75,    75,    75,    76,    76,    77,    77,    78,    78,    79,
      79,    80,    80,    81,    82,    82,    82,    82,    82,    83,
      83,    83,    84,    84,    85,    85,    86,    87,    87,    88,
      89,    89,    90,    90,    90,    90,    90,    90,    91,    91,
      91,    92,    92,    92,    93,    93,    93,    94,    94,    94,
      94,    94,    95,    95,    95,    96,    96,    96,    96,    97,
      97,    97,    98,    98,    98,    99,    99,    99,    99,    99,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   101,   102,   102,   102,   102,   103,   104,
     105,   105,   105,   105,   106,   106,   107,   108,   108,   109,
     109
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     1,     3,     3,
       3,     1,     1,     2,     0,     1,     1,     3,     2,     6,
       0,     2,     0,     1,     2,     0,     3,     0,     1,     2,
       1,     1,     1,     7,     6,     5,     4,     1,     1,     0,
       1,     9,     8,     4,     0,     2,     2,     1,     1,     1,
       1,     1,     2,     4,     1,     3,     1,     1,     3,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     1,     2,     2,     1,     5,     6,     2,     2,
       1,     1,     1,     1,     1,     3,     4,     3,     5,     6,
       1,     1,     1,     2,     2,     1,     1,     1,     3,     5,
       5,     7,     6,     8,     1,     2,     5,     3,     2,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,   102,   103,   100,   101,   104,     0,     0,     0,
       0,     0,     0,   110,   111,     0,     0,     0,     2,     7,
       6,     0,    56,     0,    59,    60,    68,    71,    74,    77,
      82,    85,    89,    92,    95,     5,   112,   115,   116,   117,
       4,     0,     0,     0,    91,    90,    93,    94,     0,    18,
      16,     0,     0,     1,     3,     0,     0,   114,    62,    63,
      64,    65,    66,    67,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    98,    99,   113,    57,    58,   105,     0,    54,   107,
       0,    14,     8,     0,     0,   118,     0,    69,    70,    61,
      72,    73,    75,    76,    78,    79,    80,    81,    83,    84,
      86,    87,    88,     0,   106,     0,    17,     0,     0,    12,
      15,     0,    11,     0,     0,     0,     0,    55,    20,     0,
      13,     9,     0,   120,   119,   108,     0,    96,     0,     0,
       0,    10,   128,     0,     0,     0,   122,   124,   109,    97,
      21,    22,   127,     0,   121,     0,   125,    49,    50,    51,
       0,    23,     0,     0,   123,    19,    24,    27,     0,    47,
      48,     0,    26,    28,    30,    31,    32,     0,   126,    45,
      46,     0,    29,     0,     0,    56,     0,     0,     0,    39,
       0,     0,     0,    43,     0,    40,     0,    39,    52,     0,
       0,    38,    37,     0,   129,   130,    34,     0,     0,     0,
       0,     0,    33,    53,     0,     0,    36,     0,    42,     0,
      35,    41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    17,    18,    19,    92,   119,   120,   121,    51,    20,
     122,   140,   160,   161,   172,   173,   174,   195,   203,   196,
     175,   176,   177,   162,   190,    87,    21,    43,    23,    24,
      66,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,   146,   147,   205,   206
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -177
static const yytype_int16 yypact[] =
{
      85,   -48,  -177,  -177,  -177,  -177,    76,   326,   326,    15,
      15,   326,    21,  -177,  -177,    49,    20,    23,  -177,  -177,
    -177,    62,    31,    68,  -177,   144,    40,    71,    90,   124,
      32,  -177,  -177,    37,  -177,   216,  -177,  -177,  -177,  -177,
    -177,   108,   252,    31,  -177,  -177,    37,    37,    83,  -177,
    -177,    29,   326,  -177,  -177,   -11,   135,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,   326,   326,   326,   326,   326,   326,
     326,   326,   326,   326,   326,   326,   326,   326,   326,   326,
     138,  -177,  -177,  -177,   120,  -177,  -177,   116,   150,  -177,
     154,   -31,  -177,   129,   326,  -177,   151,    40,    40,  -177,
      71,    71,    90,    90,   124,   124,   124,   124,    32,    32,
    -177,  -177,  -177,   152,  -177,   326,  -177,   166,    49,  -177,
     -31,   139,  -177,   155,   156,   281,   296,  -177,   191,    29,
    -177,  -177,   143,    81,  -177,  -177,   161,  -177,   165,   198,
     170,  -177,  -177,   190,   172,   155,    94,  -177,  -177,  -177,
    -177,    86,  -177,   326,  -177,   155,  -177,  -177,  -177,  -177,
      33,  -177,   201,   173,  -177,  -177,  -177,    54,   155,   162,
     164,   174,     1,  -177,  -177,  -177,  -177,     2,  -177,  -177,
    -177,   180,  -177,   217,   218,  -177,    -1,   192,   189,   222,
     197,   230,     3,  -177,   109,  -177,    61,   222,   229,   185,
     202,  -177,  -177,   206,  -177,  -177,  -177,    61,   108,   108,
     186,   311,  -177,  -177,    61,   108,  -177,   208,  -177,    61,
    -177,  -177
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -177,  -177,   228,  -177,   119,   130,  -177,  -177,   131,  -177,
    -177,  -177,  -177,    91,  -177,    80,  -177,  -177,  -177,    56,
    -177,  -177,  -177,  -177,  -176,  -112,  -115,     0,    -9,   196,
    -177,  -177,    93,   104,   105,    53,   107,    -3,  -177,   175,
    -177,   132,   -34,  -177,  -177,  -177,  -177,   117,  -111,  -106
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -58
static const yytype_int16 yytable[] =
{
      22,    83,    48,   127,    44,    45,    84,    94,   -44,    84,
      84,    40,   133,   136,   138,   117,   200,    22,     2,     3,
       4,     5,     6,    53,   118,    49,     2,     3,     4,     5,
       6,    95,   213,    88,   154,    22,     7,    90,   189,    56,
       8,    85,   199,    93,   164,    80,    77,    78,    79,     9,
      10,   169,   170,    11,   171,   183,    50,   178,    52,    13,
      14,    11,   184,    81,    82,    91,    12,    13,    14,    55,
     165,   191,    67,    68,   110,   111,   112,   191,    15,    16,
     157,   158,   159,   -57,   -57,   124,     1,    41,     2,     3,
       4,     5,     6,   191,   214,    69,    70,   132,     7,   217,
     219,   212,     8,   204,   169,   170,    88,   171,   218,    83,
      57,     9,    10,   221,    42,    84,    88,    88,    71,    72,
      73,    74,    89,    11,   104,   105,   106,   107,    12,    13,
      14,    41,    22,   157,   158,   159,    75,    76,   144,   145,
      15,    16,    96,    22,   163,   113,     2,     3,     4,     5,
       6,   144,   155,   201,   202,   114,     7,    97,    98,   115,
       8,   116,    58,    59,    60,    61,    62,    63,   123,     9,
      10,   100,   101,   128,   102,   103,   131,   185,    64,    65,
     142,    11,   108,   109,    46,    47,   185,    13,    14,   125,
     126,   132,   185,     2,     3,     4,     5,     6,   134,    16,
     148,   139,    88,     7,   149,   150,   151,     8,   185,   185,
     153,   167,   168,   179,   180,   185,     9,    10,   186,     2,
       3,     4,     5,     6,   187,   188,   181,   152,    11,     7,
     192,   193,   194,     8,    13,    14,   197,   198,   208,   209,
     215,   210,     9,    10,   211,    54,    16,   220,   141,   129,
     130,   166,   182,   207,    11,     2,     3,     4,     5,     6,
      13,    14,    99,   156,   143,     7,     0,     0,     0,     8,
       0,     0,    16,     0,     0,     0,     0,     0,     9,    10,
       0,     0,     0,     0,     2,     3,     4,     5,     6,     0,
      11,    86,     0,     0,     7,     0,    13,    14,     8,     2,
       3,     4,     5,     6,     0,     0,     0,     9,    10,     7,
       0,     0,     0,     8,     2,     3,     4,     5,     6,    11,
     135,     0,     9,    10,     7,    13,    14,     0,     8,     2,
       3,     4,     5,     6,    11,   137,     0,     9,    10,     7,
      13,    14,     0,     8,     0,     0,     0,     0,     0,    11,
     216,     0,     9,    10,     0,    13,    14,     0,     0,     0,
       0,     0,     0,     0,    11,     0,     0,     0,     0,     0,
      13,    14
};

static const yytype_int16 yycheck[] =
{
       0,    35,    11,   115,     7,     8,     7,    18,     7,     7,
       7,    59,   123,   125,   126,    46,   192,    17,     3,     4,
       5,     6,     7,     0,    55,     4,     3,     4,     5,     6,
       7,    42,   208,    42,   145,    35,    13,     8,    39,     8,
      17,    41,    39,    52,   155,     8,    14,    15,    16,    26,
      27,    50,    51,    38,    53,    53,     7,   168,    38,    44,
      45,    38,   177,    26,    27,    36,    43,    44,    45,     7,
      37,   186,    32,    33,    77,    78,    79,   192,    55,    56,
      47,    48,    49,     7,     8,    94,     1,    11,     3,     4,
       5,     6,     7,   208,   209,    24,    25,    36,    13,   211,
     215,   207,    17,    42,    50,    51,   115,    53,   214,   143,
      42,    26,    27,   219,    38,     7,   125,   126,    28,    29,
      30,    31,    39,    38,    71,    72,    73,    74,    43,    44,
      45,    11,   132,    47,    48,    49,    12,    13,    57,    58,
      55,    56,     7,   143,   153,     7,     3,     4,     5,     6,
       7,    57,    58,    44,    45,    39,    13,    64,    65,     9,
      17,     7,    18,    19,    20,    21,    22,    23,    39,    26,
      27,    67,    68,     7,    69,    70,    37,   177,    34,    35,
      37,    38,    75,    76,     9,    10,   186,    44,    45,    38,
      38,    36,   192,     3,     4,     5,     6,     7,    42,    56,
      39,    10,   211,    13,    39,     7,    36,    17,   208,   209,
      38,    10,    39,    51,    50,   215,    26,    27,    38,     3,
       4,     5,     6,     7,     7,     7,    52,    37,    38,    13,
      38,    42,    10,    17,    44,    45,    39,     7,     9,    54,
      54,    39,    26,    27,    38,    17,    56,    39,   129,   118,
     120,   160,   172,   197,    38,     3,     4,     5,     6,     7,
      44,    45,    66,   146,   132,    13,    -1,    -1,    -1,    17,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    26,    27,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,
      38,    39,    -1,    -1,    13,    -1,    44,    45,    17,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    26,    27,    13,
      -1,    -1,    -1,    17,     3,     4,     5,     6,     7,    38,
      39,    -1,    26,    27,    13,    44,    45,    -1,    17,     3,
       4,     5,     6,     7,    38,    39,    -1,    26,    27,    13,
      44,    45,    -1,    17,    -1,    -1,    -1,    -1,    -1,    38,
      39,    -1,    26,    27,    -1,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      44,    45
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,    13,    17,    26,
      27,    38,    43,    44,    45,    55,    56,    61,    62,    63,
      69,    86,    87,    88,    89,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
      59,    11,    38,    87,    97,    97,    99,    99,    88,     4,
       7,    68,    38,     0,    62,     7,     8,    42,    18,    19,
      20,    21,    22,    23,    34,    35,    90,    32,    33,    24,
      25,    28,    29,    30,    31,    12,    13,    14,    15,    16,
       8,    26,    27,   102,     7,    87,    39,    85,    88,    39,
       8,    36,    64,    88,    18,    42,     7,    92,    92,    89,
      93,    93,    94,    94,    95,    95,    95,    95,    96,    96,
      97,    97,    97,     7,    39,     9,     7,    46,    55,    65,
      66,    67,    70,    39,    88,    38,    38,    85,     7,    68,
      65,    37,    36,   108,    42,    39,    85,    39,    85,    10,
      71,    64,    37,   101,    57,    58,   106,   107,    39,    39,
       7,    36,    37,    38,   108,    58,   107,    47,    48,    49,
      72,    73,    83,    88,   108,    37,    73,    10,    39,    50,
      51,    53,    74,    75,    76,    80,    81,    82,   108,    51,
      50,    52,    75,    53,    86,    87,    38,     7,     7,    39,
      84,    86,    38,    42,    10,    77,    79,    39,     7,    39,
      84,    44,    45,    78,    42,   108,   109,    79,     9,    54,
      39,    38,   109,    84,    86,    54,    39,    85,   109,    86,
      39,   109
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
#line 96 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 102 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 106 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 110 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 116 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 122 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value)
	;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 128 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 132 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 138 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 142 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 148 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 152 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 158 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 162 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 168 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 174 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (6)].string_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 180 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 184 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_superclass((yyvsp[(2) - (2)].string_value));
	;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 190 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 194 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 198 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 204 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 208 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[(1) - (3)].access_level_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 214 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 218 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 222 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[(1) - (2)].ast_value), ast_new_member_decl((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 233 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 237 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 243 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (5)].chain_type_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 247 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (4)].chain_type_value), ast_new_blank());
	;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 253 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.chain_type_value) = chain_type_super;
	;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 257 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.chain_type_value) = chain_type_this;
	;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 263 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 270 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[(1) - (9)].modifier_type_value), (yyvsp[(3) - (9)].string_value), (yyvsp[(5) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 274 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[(1) - (8)].modifier_type_value), (yyvsp[(3) - (8)].string_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 280 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[(1) - (4)].modifier_type_value), (yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].string_value));
	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 286 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_none;
	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 290 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 294 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 298 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_static;
	;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 302 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_native;
	;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 308 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 312 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 316 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 322 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].string_value));
	;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 326 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(1) - (4)].ast_value), (yyvsp[(2) - (4)].string_value), (yyvsp[(4) - (4)].ast_value))
	;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 332 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 336 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(1) - (3)].ast_value)), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 342 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 348 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 352 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(1) - (3)].string_value)), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 362 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_generic_assign((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].assign_otype_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 368 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_def;
	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 372 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_add;
	;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 376 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_sub;
	;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 380 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_mul;
	;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 384 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_div;
	;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 388 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_mod;
	;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 395 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_bit_or((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 399 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_logic_or((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 406 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_bit_and((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 410 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_logic_and((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 417 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_equal((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 421 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_notequal((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 428 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_gt((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 432 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_ge((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 436 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_lt((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 440 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_le((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 447 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_add((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 451 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_sub((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 458 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_mul((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 462 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_div((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 466 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_mod((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 473 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_not((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 477 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_neg((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 484 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_pre_inc((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 488 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_pre_dec((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 495 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_invoke((yyvsp[(1) - (5)].ast_value), (yyvsp[(3) - (5)].string_value), ast_new_blank());
	;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 499 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_invoke((yyvsp[(1) - (6)].ast_value), (yyvsp[(3) - (6)].string_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 503 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_post_inc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 507 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_post_dec((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 517 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 521 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_call((yyvsp[(1) - (3)].string_value), ast_new_blank());
	;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 525 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_call((yyvsp[(1) - (4)].string_value), (yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 529 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 533 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_static_invoke((yyvsp[(1) - (5)].ast_value), (yyvsp[(3) - (5)].string_value), ast_new_blank());
	;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 537 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_static_invoke((yyvsp[(1) - (6)].ast_value), (yyvsp[(3) - (6)].string_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 541 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_this();
	;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 545 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_super();
	;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 551 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 555 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 561 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 570 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].string_value));
	;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 576 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 582 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 586 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(3) - (7)].ast_value), (yyvsp[(5) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 590 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 594 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(3) - (8)].ast_value), (yyvsp[(5) - (8)].ast_value), (yyvsp[(6) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value));
	;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 601 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 607 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 613 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 617 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 623 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;



/* Line 1455 of yacc.c  */
#line 2632 "signal.tab.c"
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
#line 628 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"

