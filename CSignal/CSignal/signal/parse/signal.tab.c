
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
#define YYFINAL  50
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   290

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNRULES -- Number of states.  */
#define YYNSTATES  216

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
     152,   154,   156,   159,   164,   166,   170,   172,   176,   178,
     180,   184,   186,   188,   190,   192,   194,   196,   198,   202,
     206,   208,   212,   216,   218,   222,   226,   228,   232,   236,
     240,   244,   246,   250,   254,   256,   260,   264,   268,   270,
     273,   276,   278,   281,   284,   286,   292,   299,   302,   305,
     307,   309,   311,   313,   315,   319,   324,   328,   334,   341,
     343,   346,   349,   351,   353,   359,   365,   373,   380,   389,
     391,   394,   400,   404,   407,   409
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      61,     0,    -1,    62,    -1,    61,    62,    -1,     1,    59,
      -1,   100,    -1,    69,    -1,    63,    -1,    55,    68,    64,
      -1,    36,    67,    37,    -1,    55,    68,    64,    -1,    70,
      -1,    65,    -1,    66,    65,    -1,    -1,    66,    -1,     7,
      -1,    68,     8,     7,    -1,    43,     4,    -1,    46,     7,
      71,    36,    72,    37,    -1,    -1,    10,     7,    -1,    -1,
      73,    -1,    72,    73,    -1,    -1,    83,    10,    74,    -1,
      -1,    75,    -1,    74,    75,    -1,    76,    -1,    80,    -1,
      81,    -1,    53,    52,    38,    84,    39,    79,   107,    -1,
      53,    52,    38,    39,    79,   107,    -1,    10,    78,    38,
      85,    39,    -1,    10,    78,    38,    39,    -1,    45,    -1,
      44,    -1,    -1,    77,    -1,    82,    53,     7,    38,    84,
      39,    54,     7,   107,    -1,    82,    53,     7,    38,    39,
      54,     7,   107,    -1,    82,     7,     7,    42,    -1,    -1,
      50,    51,    -1,    51,    50,    -1,    50,    -1,    51,    -1,
      47,    -1,    48,    -1,    49,    -1,     7,     7,    -1,     7,
       7,     9,    84,    -1,    87,    -1,    87,     9,    85,    -1,
       7,    -1,     7,    11,    86,    -1,    88,    -1,    90,    -1,
      90,    89,    88,    -1,    18,    -1,    19,    -1,    20,    -1,
      21,    -1,    22,    -1,    23,    -1,    91,    -1,    90,    34,
      91,    -1,    90,    35,    91,    -1,    92,    -1,    91,    32,
      92,    -1,    91,    33,    92,    -1,    93,    -1,    92,    24,
      93,    -1,    92,    25,    93,    -1,    94,    -1,    93,    28,
      94,    -1,    93,    29,    94,    -1,    93,    30,    94,    -1,
      93,    31,    94,    -1,    95,    -1,    94,    12,    95,    -1,
      94,    13,    95,    -1,    96,    -1,    95,    14,    96,    -1,
      95,    15,    96,    -1,    95,    16,    96,    -1,    97,    -1,
      17,    96,    -1,    13,    96,    -1,    98,    -1,    26,    98,
      -1,    27,    98,    -1,    99,    -1,    98,     8,     7,    38,
      39,    -1,    98,     8,     7,    38,    85,    39,    -1,    98,
      26,    -1,    98,    27,    -1,     5,    -1,     6,    -1,     3,
      -1,     4,    -1,     7,    -1,     7,    38,    39,    -1,     7,
      38,    85,    39,    -1,    38,    87,    39,    -1,    86,     8,
       7,    38,    39,    -1,    86,     8,     7,    38,    85,    39,
      -1,   101,    -1,   100,   101,    -1,    87,    42,    -1,   102,
      -1,   103,    -1,     7,     7,    18,    87,    42,    -1,    56,
      38,    87,    39,   106,    -1,    56,    38,    87,    39,   106,
      58,   106,    -1,    56,    38,    87,    39,   106,   104,    -1,
      56,    38,    87,    39,   106,   104,    58,   106,    -1,   105,
      -1,   104,   105,    -1,    57,    38,    87,    39,   106,    -1,
      36,   100,    37,    -1,    36,    37,    -1,    42,    -1,   106,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    91,    91,    92,    93,    99,   103,   107,   113,   119,
     125,   129,   135,   139,   146,   149,   155,   159,   165,   171,
     178,   181,   188,   191,   195,   202,   205,   212,   215,   219,
     225,   226,   227,   230,   234,   240,   244,   250,   254,   261,
     264,   267,   271,   277,   284,   287,   291,   295,   299,   305,
     309,   313,   319,   323,   329,   333,   339,   343,   349,   352,
     353,   359,   363,   367,   371,   375,   379,   385,   386,   390,
     396,   397,   401,   407,   408,   412,   418,   419,   423,   427,
     431,   437,   438,   442,   448,   449,   453,   457,   463,   464,
     468,   474,   475,   479,   485,   486,   490,   494,   498,   504,
     505,   506,   507,   508,   512,   516,   520,   524,   528,   534,
     538,   544,   548,   549,   552,   558,   562,   566,   570,   576,
     577,   583,   589,   593,   599,   603
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
  "fqcn_part", "expression", "assign", "assign_type_T", "or", "and",
  "equal", "compare", "addsub", "muldiv", "unary", "prefix", "postfix",
  "primary", "stmt_list", "stmt", "variable_stmt", "if_stmt", "elif_list",
  "elif", "scope", "scope_optional", 0
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
      83,    83,    84,    84,    85,    85,    86,    86,    87,    88,
      88,    89,    89,    89,    89,    89,    89,    90,    90,    90,
      91,    91,    91,    92,    92,    92,    93,    93,    93,    93,
      93,    94,    94,    94,    95,    95,    95,    95,    96,    96,
      96,    97,    97,    97,    98,    98,    98,    98,    98,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,   100,
     100,   101,   101,   101,   102,   103,   103,   103,   103,   104,
     104,   105,   106,   106,   107,   107
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     1,     3,     3,
       3,     1,     1,     2,     0,     1,     1,     3,     2,     6,
       0,     2,     0,     1,     2,     0,     3,     0,     1,     2,
       1,     1,     1,     7,     6,     5,     4,     1,     1,     0,
       1,     9,     8,     4,     0,     2,     2,     1,     1,     1,
       1,     1,     2,     4,     1,     3,     1,     3,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     1,     2,     2,     1,     5,     6,     2,     2,     1,
       1,     1,     1,     1,     3,     4,     3,     5,     6,     1,
       2,     2,     1,     1,     5,     5,     7,     6,     8,     1,
       2,     5,     3,     2,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,   101,   102,    99,   100,   103,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     7,     6,     0,
       0,    58,    59,    67,    70,    73,    76,    81,    84,    88,
      91,    94,     5,   109,   112,   113,     4,     0,     0,     0,
     103,    90,    89,    92,    93,     0,    18,    16,     0,     0,
       1,     3,     0,   111,    61,    62,    63,    64,    65,    66,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    97,    98,   110,
       0,    56,    57,   104,     0,    54,   106,     0,    14,     8,
       0,     0,    68,    69,    60,    71,    72,    74,    75,    77,
      78,    79,    80,    82,    83,    85,    86,    87,     0,     0,
     105,     0,    17,     0,     0,    12,    15,     0,    11,     0,
       0,     0,   114,    55,    20,     0,    13,     9,     0,   115,
     107,     0,    95,     0,     0,     0,    10,   123,     0,     0,
       0,   117,   119,   108,    96,    21,    22,   122,     0,   116,
       0,   120,    49,    50,    51,     0,    23,     0,     0,   118,
      19,    24,    27,     0,    47,    48,     0,    26,    28,    30,
      31,    32,     0,   121,    45,    46,     0,    29,     0,     0,
       0,     0,     0,     0,    39,     0,    43,     0,    52,     0,
      40,     0,    39,     0,     0,     0,    38,    37,     0,   124,
     125,    34,     0,     0,     0,    53,     0,    33,     0,     0,
      36,     0,    42,     0,    35,    41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    15,    16,    17,    89,   115,   116,   117,    48,    18,
     118,   135,   155,   156,   167,   168,   169,   190,   198,   191,
     170,   171,   172,   157,   185,    84,    19,    20,    21,    62,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,   141,   142,   200,   201
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -166
static const yytype_int16 yypact[] =
{
      18,   -46,  -166,  -166,  -166,  -166,    88,   237,   237,    47,
      47,   237,    29,    58,    -2,     3,  -166,  -166,  -166,    69,
      45,  -166,   238,    35,   103,   123,   164,   126,  -166,  -166,
      49,  -166,   117,  -166,  -166,  -166,  -166,    80,    96,   153,
      55,  -166,  -166,    49,    49,    97,  -166,  -166,    19,   237,
    -166,  -166,   104,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   160,  -166,  -166,  -166,
     237,   161,  -166,  -166,   130,   165,  -166,   171,   -29,  -166,
     151,   145,    35,    35,  -166,   103,   103,   123,   123,   164,
     164,   164,   164,   126,   126,  -166,  -166,  -166,   173,   174,
    -166,   237,  -166,   213,    58,  -166,   -29,   188,  -166,   192,
     158,   195,  -166,  -166,   219,    19,  -166,  -166,    75,   124,
    -166,   191,  -166,   193,   224,   199,  -166,  -166,   112,   198,
     192,   129,  -166,  -166,  -166,  -166,    42,  -166,   237,  -166,
     192,  -166,  -166,  -166,  -166,    57,  -166,   227,   206,  -166,
    -166,  -166,    82,   192,   196,   201,   194,    33,  -166,  -166,
    -166,  -166,     7,  -166,  -166,  -166,   210,  -166,   242,   245,
       8,   211,   217,   255,   256,   226,  -166,    25,   258,   144,
    -166,    72,   256,   215,   229,   263,  -166,  -166,   233,  -166,
    -166,  -166,    72,   267,   222,  -166,   200,  -166,    72,   270,
    -166,   239,  -166,    72,  -166,  -166
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -166,  -166,   264,  -166,   155,   166,  -166,  -166,   167,  -166,
    -166,  -166,  -166,   128,  -166,   118,  -166,  -166,  -166,    92,
    -166,  -166,  -166,  -166,  -153,  -109,   248,   -11,   225,  -166,
    -166,   133,   146,   149,    78,   147,    -3,  -166,   214,  -166,
     162,   -31,  -166,  -166,  -166,   148,  -101,  -165
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -57
static const yytype_int16 yytable[] =
{
      45,    79,   123,    50,    41,    42,     2,     3,     4,     5,
       6,   131,   133,    36,   178,   183,     7,   113,   129,     1,
       8,     2,     3,     4,     5,     6,   114,    87,    85,     9,
      10,     7,   183,    46,   194,     8,    49,   207,    90,   149,
     -44,    11,   205,   212,     9,    10,    12,   184,   215,   159,
       2,     3,     4,     5,    40,    88,    11,    76,    13,    14,
     179,    12,   173,   -56,   193,    47,    38,    63,    64,   109,
     105,   106,   107,    13,    14,    77,    78,    52,     2,     3,
       4,     5,     6,   164,   165,    11,   166,    53,     7,   152,
     153,   154,     8,    39,   160,    37,   -56,   211,    80,    38,
      85,     9,    10,    81,   152,   153,   154,    79,   128,    85,
      85,    91,   137,    11,   199,     2,     3,     4,     5,     6,
       2,     3,     4,     5,     6,     7,    39,    65,    66,     8,
       7,    14,   164,   165,     8,   166,    86,   158,     9,    10,
      73,    74,    75,     9,    10,    99,   100,   101,   102,   147,
      11,    67,    68,    69,    70,    11,     2,     3,     4,     5,
      40,     2,     3,     4,     5,    40,     7,   108,    14,   110,
       8,     7,    38,    14,   111,     8,    71,    72,   112,     9,
      10,   139,   140,   120,     9,    10,   139,   150,   196,   197,
     119,    11,    83,    92,    93,    85,    11,   130,     2,     3,
       4,     5,    40,     2,     3,     4,     5,    40,     7,    95,
      96,   121,     8,     7,    97,    98,   122,     8,   103,   104,
     124,     9,    10,    43,    44,   127,     9,    10,   128,   134,
     143,   145,   144,    11,   132,   146,   148,   162,    11,   210,
       2,     3,     4,     5,    40,   163,   176,   174,   180,   181,
       7,   175,   182,   186,     8,   187,    54,    55,    56,    57,
      58,    59,   188,     9,    10,   192,   189,   195,   204,   203,
     183,   206,    60,    61,   208,    11,   209,   213,   214,    51,
     136,   125,   126,   161,   202,   177,    82,    94,     0,   151,
     138
};

static const yytype_int16 yycheck[] =
{
      11,    32,   111,     0,     7,     8,     3,     4,     5,     6,
       7,   120,   121,    59,     7,     7,    13,    46,   119,     1,
      17,     3,     4,     5,     6,     7,    55,     8,    39,    26,
      27,    13,     7,     4,   187,    17,    38,   202,    49,   140,
       7,    38,   195,   208,    26,    27,    43,    39,   213,   150,
       3,     4,     5,     6,     7,    36,    38,     8,    55,    56,
      53,    43,   163,     8,    39,     7,    11,    32,    33,    80,
      73,    74,    75,    55,    56,    26,    27,     8,     3,     4,
       5,     6,     7,    50,    51,    38,    53,    42,    13,    47,
      48,    49,    17,    38,    37,     7,     8,   206,    18,    11,
     111,    26,    27,     7,    47,    48,    49,   138,    36,   120,
     121,     7,    37,    38,    42,     3,     4,     5,     6,     7,
       3,     4,     5,     6,     7,    13,    38,    24,    25,    17,
      13,    56,    50,    51,    17,    53,    39,   148,    26,    27,
      14,    15,    16,    26,    27,    67,    68,    69,    70,    37,
      38,    28,    29,    30,    31,    38,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,    13,     7,    56,    39,
      17,    13,    11,    56,     9,    17,    12,    13,     7,    26,
      27,    57,    58,    38,    26,    27,    57,    58,    44,    45,
      39,    38,    39,    60,    61,   206,    38,    39,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,    13,    63,
      64,    38,    17,    13,    65,    66,    42,    17,    71,    72,
       7,    26,    27,     9,    10,    37,    26,    27,    36,    10,
      39,     7,    39,    38,    39,    36,    38,    10,    38,    39,
       3,     4,     5,     6,     7,    39,    52,    51,    38,     7,
      13,    50,     7,    42,    17,    38,    18,    19,    20,    21,
      22,    23,     7,    26,    27,    39,    10,     9,    39,    54,
       7,    38,    34,    35,     7,    38,    54,     7,    39,    15,
     125,   114,   116,   155,   192,   167,    38,    62,    -1,   141,
     128
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,    13,    17,    26,
      27,    38,    43,    55,    56,    61,    62,    63,    69,    86,
      87,    88,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,    59,     7,    11,    38,
       7,    96,    96,    98,    98,    87,     4,     7,    68,    38,
       0,    62,     8,    42,    18,    19,    20,    21,    22,    23,
      34,    35,    89,    32,    33,    24,    25,    28,    29,    30,
      31,    12,    13,    14,    15,    16,     8,    26,    27,   101,
      18,     7,    86,    39,    85,    87,    39,     8,    36,    64,
      87,     7,    91,    91,    88,    92,    92,    93,    93,    94,
      94,    94,    94,    95,    95,    96,    96,    96,     7,    87,
      39,     9,     7,    46,    55,    65,    66,    67,    70,    39,
      38,    38,    42,    85,     7,    68,    65,    37,    36,   106,
      39,    85,    39,    85,    10,    71,    64,    37,   100,    57,
      58,   104,   105,    39,    39,     7,    36,    37,    38,   106,
      58,   105,    47,    48,    49,    72,    73,    83,    87,   106,
      37,    73,    10,    39,    50,    51,    53,    74,    75,    76,
      80,    81,    82,   106,    51,    50,    52,    75,     7,    53,
      38,     7,     7,     7,    39,    84,    42,    38,     7,    10,
      77,    79,    39,    39,    84,     9,    44,    45,    78,    42,
     106,   107,    79,    54,    39,    84,    38,   107,     7,    54,
      39,    85,   107,     7,    39,   107
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
#line 94 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 100 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 104 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 108 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 114 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 120 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value)
	;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 126 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 130 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 136 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 140 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 146 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 150 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 156 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 160 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 166 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 172 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (6)].string_value), (yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 178 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 182 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_superclass((yyvsp[(2) - (2)].string_value));
	;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 188 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 192 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 196 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 202 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 206 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[(1) - (3)].access_level_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 212 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 216 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 220 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[(1) - (2)].ast_value), ast_new_member_decl((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 231 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 235 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 241 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (5)].chain_type_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 245 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (4)].chain_type_value), ast_new_blank());
	;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 251 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.chain_type_value) = chain_type_super;
	;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 255 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.chain_type_value) = chain_type_this;
	;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 261 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 268 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[(1) - (9)].modifier_type_value), (yyvsp[(3) - (9)].string_value), (yyvsp[(5) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].string_value));
	;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 272 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[(1) - (8)].modifier_type_value), (yyvsp[(3) - (8)].string_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].string_value));
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 278 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[(1) - (4)].modifier_type_value), (yyvsp[(2) - (4)].string_value), (yyvsp[(3) - (4)].string_value));
	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 284 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_none;
	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 288 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 292 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 296 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_static;
	;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 300 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.modifier_type_value) = modifier_native;
	;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 306 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 310 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 314 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 320 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].string_value), (yyvsp[(2) - (2)].string_value));
	;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 324 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(1) - (4)].string_value), (yyvsp[(2) - (4)].string_value), (yyvsp[(4) - (4)].ast_value))
	;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 330 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 334 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(1) - (3)].ast_value)), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 340 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 344 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(1) - (3)].string_value)), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 354 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_generic_assign((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].assign_otype_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 360 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_def;
	;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 364 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_add;
	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 368 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_sub;
	;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 372 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_mul;
	;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 376 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_div;
	;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 380 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_mod;
	;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 387 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_bit_or((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 391 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_logic_or((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 398 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_bit_and((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 402 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_logic_and((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 409 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_equal((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 413 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_notequal((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 420 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_gt((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 424 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_ge((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 428 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_lt((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 432 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_le((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 439 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_add((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 443 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_sub((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 450 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_mul((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 454 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_div((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 458 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_mod((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 465 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_not((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 469 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_neg((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 476 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_pre_inc((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 480 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_pre_dec((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 487 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_invoke((yyvsp[(1) - (5)].ast_value), (yyvsp[(3) - (5)].string_value), ast_new_blank());
	;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 491 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_invoke((yyvsp[(1) - (6)].ast_value), (yyvsp[(3) - (6)].string_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 495 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_post_inc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 499 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_post_dec((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 509 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 513 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_call((yyvsp[(1) - (3)].string_value), ast_new_blank());
	;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 517 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_call((yyvsp[(1) - (4)].string_value), (yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 521 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 525 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_static_invoke((yyvsp[(1) - (5)].ast_value), (yyvsp[(3) - (5)].string_value), ast_new_blank());
	;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 529 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_static_invoke((yyvsp[(1) - (6)].ast_value), (yyvsp[(3) - (6)].string_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 535 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 539 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 545 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 553 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_variable_decl(ast_new_typename((yyvsp[(1) - (5)].string_value)), ast_new_identifier((yyvsp[(2) - (5)].string_value)), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 559 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 563 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(3) - (7)].ast_value), (yyvsp[(5) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 567 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 571 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(3) - (8)].ast_value), (yyvsp[(5) - (8)].ast_value), (yyvsp[(6) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value));
	;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 578 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 584 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 590 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 594 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 600 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;



/* Line 1455 of yacc.c  */
#line 2571 "signal.tab.c"
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
#line 605 "C:\\Users\\Koya\\Documents\\GitHub\\CSignal\\CSignal\\CSignal\\signal\\parse\\signal.y"

