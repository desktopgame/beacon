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
     CONTINUE = 324,
     TRY = 325,
     CATCH = 326,
     THROW = 327
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
#define TRY 325
#define CATCH 326
#define THROW 327




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
#line 265 "signal.tab.c"
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
#line 290 "signal.tab.c"

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
#define YYFINAL  93
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   686

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  167
/* YYNRULES -- Number of states.  */
#define YYNSTATES  314

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   327

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      73,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72
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
     462,   464,   466,   468,   470,   472,   476,   482,   488,   494,
     502,   509,   518,   520,   523,   529,   535,   538,   541,   545,
     549,   553,   555,   558,   565,   569,   572,   574
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      75,     0,    -1,    76,    -1,    75,    76,    -1,     1,    73,
      -1,   119,    -1,    83,    -1,    77,    -1,    95,    -1,    62,
      82,    78,    -1,    37,    81,    38,    -1,    62,    82,    78,
      -1,    84,    -1,    86,    -1,    85,    -1,    79,    -1,    80,
      79,    -1,    -1,    80,    -1,     7,    -1,    82,     8,     7,
      -1,    44,     4,    -1,    51,     7,    37,    87,    38,    -1,
      51,     7,    11,   103,    37,    87,    38,    -1,    52,     7,
      37,   100,    38,    -1,    52,     7,    37,   100,     9,    38,
      -1,    50,     7,    37,    87,    38,    -1,    50,     7,    11,
     103,    37,    87,    38,    -1,    -1,    88,    -1,    87,    88,
      -1,    -1,    99,    11,    89,    -1,    -1,    90,    -1,    89,
      90,    -1,    91,    -1,    96,    -1,    97,    -1,    59,    58,
      39,   101,    40,    94,   136,    -1,    59,    58,    39,    40,
      94,   136,    -1,    11,    93,    39,   102,    40,    -1,    11,
      93,    39,    40,    -1,    47,    -1,    46,    -1,    -1,    92,
      -1,    60,     7,    39,   101,    40,    61,   104,   136,    -1,
      60,     7,    39,    40,    61,   104,   136,    -1,    98,    60,
       7,    39,   101,    40,    61,   104,   136,    -1,    98,    60,
       7,    39,    40,    61,   104,   136,    -1,    98,   104,     7,
      43,    -1,    -1,    56,    57,    -1,    57,    56,    -1,    56,
      -1,    57,    -1,    53,    -1,    54,    -1,    55,    -1,     7,
      -1,     7,     9,   100,    -1,   104,     7,    -1,   104,     7,
       9,   101,    -1,   106,    -1,   106,     9,   102,    -1,   104,
      -1,   104,     9,   103,    -1,   105,    -1,     7,    -1,     7,
      12,   105,    -1,   107,    -1,   109,    -1,   109,   108,   107,
      -1,     7,   108,   107,    -1,    19,    -1,    20,    -1,    21,
      -1,    22,    -1,    23,    -1,    24,    -1,   110,    -1,   109,
      35,   110,    -1,   109,    36,   110,    -1,   111,    -1,   110,
      33,   111,    -1,   110,    34,   111,    -1,   112,    -1,   111,
      25,   112,    -1,   111,    26,   112,    -1,   113,    -1,   112,
      29,   113,    -1,   112,    30,   113,    -1,   112,    31,   113,
      -1,   112,    32,   113,    -1,   114,    -1,   113,    13,   114,
      -1,   113,    14,   114,    -1,   115,    -1,   114,    15,   115,
      -1,   114,    16,   115,    -1,   114,    17,   115,    -1,   116,
      -1,    18,   115,    -1,    14,   115,    -1,   117,    -1,    27,
     117,    -1,    28,   117,    -1,   118,    -1,   117,     8,     7,
      -1,   117,     8,     7,    39,    40,    -1,   117,     8,     7,
      39,   102,    40,    -1,   117,    27,    -1,   117,    28,    -1,
       5,    -1,     6,    -1,     3,    -1,     4,    -1,    48,    -1,
      49,    -1,     7,    -1,     7,    39,    40,    -1,     7,    39,
     102,    40,    -1,    39,   106,    40,    -1,    39,   104,    40,
     106,    -1,   105,     8,     7,    39,    40,    -1,   105,     8,
       7,    39,   102,    40,    -1,   105,     8,     7,    -1,    46,
      -1,    47,    -1,    58,   104,    39,   102,    40,    -1,    58,
     104,    39,    40,    -1,   120,    -1,   119,   120,    -1,   106,
      43,    -1,   121,    -1,   122,    -1,   123,    -1,   124,    -1,
     127,    -1,   128,    -1,   129,    -1,   130,    -1,   131,    -1,
     132,    -1,   104,     7,    43,    -1,   104,     7,    19,   106,
      43,    -1,    45,     7,    19,   106,    43,    -1,    64,    39,
     106,    40,   135,    -1,    64,    39,   106,    40,   135,    66,
     135,    -1,    64,    39,   106,    40,   135,   125,    -1,    64,
      39,   106,    40,   135,   125,    66,   135,    -1,   126,    -1,
     125,   126,    -1,    65,    39,   106,    40,   135,    -1,    67,
      39,   106,    40,   136,    -1,    68,    43,    -1,    69,    43,
      -1,    63,   106,    43,    -1,    72,   106,    43,    -1,    70,
     135,   133,    -1,   134,    -1,   133,   134,    -1,    71,    39,
       7,     7,    40,   135,    -1,    37,   119,    38,    -1,    37,
      38,    -1,    43,    -1,   135,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   107,   107,   108,   109,   115,   119,   123,   127,   133,
     139,   145,   149,   153,   157,   163,   167,   174,   177,   183,
     187,   193,   199,   203,   209,   213,   219,   223,   230,   233,
     237,   244,   247,   254,   257,   261,   267,   268,   269,   272,
     276,   282,   286,   292,   296,   303,   306,   309,   313,   319,
     323,   329,   336,   339,   343,   347,   351,   357,   361,   365,
     371,   375,   381,   385,   391,   395,   401,   405,   411,   417,
     421,   427,   430,   431,   435,   441,   445,   449,   453,   457,
     461,   467,   468,   472,   478,   479,   483,   489,   490,   494,
     500,   501,   505,   509,   513,   519,   520,   524,   530,   531,
     535,   539,   545,   546,   550,   556,   557,   561,   567,   568,
     572,   576,   580,   584,   590,   591,   592,   593,   594,   598,
     602,   606,   610,   614,   618,   622,   626,   630,   634,   638,
     642,   646,   652,   656,   662,   666,   667,   668,   669,   670,
     671,   672,   673,   674,   675,   678,   684,   690,   696,   700,
     704,   708,   714,   715,   721,   727,   733,   739,   745,   751,
     757,   763,   767,   773,   779,   783,   789,   793
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
  "WHILE", "BREAK", "CONTINUE", "TRY", "CATCH", "THROW", "'\\n'",
  "$accept", "root", "top_level", "namespace_decl", "namespace_body",
  "namespace_member_decl", "namespace_member_decl_list",
  "namespace_member_decl_optional", "namespace_path", "import",
  "class_decl", "enum_decl", "interface_decl", "access_member_tree",
  "access_member_list", "member_define_list", "member_define",
  "constructor_define", "constructor_chain", "constructor_chain_type_T",
  "constructor_chain_optional", "function_define", "method_define",
  "field_define", "modifier_type_T", "access_level_T", "ident_list",
  "parameter_list", "argument_list", "typename_list", "typename_T",
  "fqcn_part", "expression", "assign", "assign_type_T", "or", "and",
  "equal", "compare", "addsub", "muldiv", "unary", "prefix", "postfix",
  "primary", "stmt_list", "stmt", "variable_decl_stmt",
  "variable_init_stmt", "inferenced_type_init_stmt", "if_stmt",
  "elif_list", "elif", "while_stmt", "break_stmt", "continue_stmt",
  "return_stmt", "throw_stmt", "try_stmt", "catch_stmt_list", "catch_stmt",
  "scope", "scope_optional", 0
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
     325,   326,   327,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    75,    76,    76,    76,    76,    77,
      78,    79,    79,    79,    79,    80,    80,    81,    81,    82,
      82,    83,    84,    84,    85,    85,    86,    86,    87,    87,
      87,    88,    88,    89,    89,    89,    90,    90,    90,    91,
      91,    92,    92,    93,    93,    94,    94,    95,    95,    96,
      96,    97,    98,    98,    98,    98,    98,    99,    99,    99,
     100,   100,   101,   101,   102,   102,   103,   103,   104,   105,
     105,   106,   107,   107,   107,   108,   108,   108,   108,   108,
     108,   109,   109,   109,   110,   110,   110,   111,   111,   111,
     112,   112,   112,   112,   112,   113,   113,   113,   114,   114,
     114,   114,   115,   115,   115,   116,   116,   116,   117,   117,
     117,   117,   117,   117,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   119,   119,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   121,   122,   123,   124,   124,
     124,   124,   125,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   133,   134,   135,   135,   136,   136
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
       1,     1,     1,     1,     1,     3,     5,     5,     5,     7,
       6,     8,     1,     2,     5,     5,     2,     2,     3,     3,
       3,     1,     2,     6,     3,     2,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,   116,   117,   114,   115,   120,     0,     0,     0,
       0,     0,     0,     0,   128,   129,   118,   119,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       7,     6,     8,     0,    68,     0,    71,    72,    81,    84,
      87,    90,    95,    98,   102,   105,   108,     5,   132,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,     4,
       0,    75,    76,    77,    78,    79,    80,     0,     0,   120,
       0,   104,   103,   106,   107,     0,     0,    21,     0,    69,
       0,    68,     0,    19,     0,     0,     0,     0,   156,   157,
       0,     0,     0,     1,     3,     0,     0,   134,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   133,    70,   121,
       0,    64,    74,     0,   123,     0,     0,     0,     0,    17,
       9,   158,     0,     0,   165,     0,     0,   160,   161,   159,
       0,   145,   127,    82,    83,    73,    85,    86,    88,    89,
      91,    92,    93,    94,    96,    97,    99,   100,   101,   109,
     122,     0,   124,     0,   131,     0,     0,     0,     0,    20,
       0,     0,     0,     0,    15,    18,     0,    12,    14,    13,
       0,     0,   164,     0,   162,     0,     0,     0,    65,   147,
     130,     0,     0,    62,     0,     0,     0,     0,    16,    10,
     148,   166,   167,   155,     0,   146,   125,     0,   110,     0,
       0,     0,     0,     0,    28,     0,    28,     0,    11,     0,
       0,   150,   152,     0,   126,   111,    48,     0,    63,     0,
      66,    57,    58,    59,     0,    29,     0,     0,     0,    60,
       0,     0,   149,     0,   153,     0,    47,    28,     0,    26,
      30,    33,    28,    22,     0,     0,    24,     0,   151,   163,
       0,    67,    55,    56,     0,    32,    34,    36,    37,    38,
       0,     0,    61,    25,     0,    27,    53,    54,     0,    35,
       0,     0,    23,   154,     0,     0,     0,    45,     0,     0,
      51,     0,    46,     0,    45,     0,     0,    44,    43,     0,
      40,     0,     0,     0,     0,    39,     0,     0,    42,     0,
      50,     0,    41,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    28,    29,    30,   130,   174,   175,   176,    84,    31,
     177,   178,   179,   234,   235,   265,   266,   267,   292,   299,
     293,    32,   268,   269,   270,   236,   240,   167,   120,   229,
      33,    70,   121,    36,    68,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,   221,   222,    53,    54,    55,    56,    57,    58,   137,
     138,   202,   203
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -218
static const yytype_int16 yypact[] =
{
     375,   -31,  -218,  -218,  -218,  -218,   306,   181,   181,   102,
     102,   628,    46,    67,  -218,  -218,  -218,  -218,    86,    89,
      91,   628,    14,    44,   101,   110,    97,   628,   305,  -218,
    -218,  -218,  -218,   116,   172,   140,  -218,   364,    35,    77,
     222,   118,   122,  -218,  -218,    73,  -218,   516,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
      86,  -218,  -218,  -218,  -218,  -218,  -218,    31,   628,    76,
     172,  -218,  -218,    73,    73,   160,   164,  -218,   187,   198,
     175,  -218,   179,  -218,    11,   188,   628,   628,  -218,  -218,
     422,   166,   197,  -218,  -218,    42,   234,  -218,   181,   181,
     628,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   235,  -218,  -218,  -218,  -218,  -218,
     204,   236,  -218,   628,  -218,   628,   115,    15,   242,    74,
    -218,  -218,   215,   218,  -218,   469,   220,   166,  -218,  -218,
     628,  -218,   226,    35,    35,  -218,    77,    77,   222,   222,
     118,   118,   118,   118,   122,   122,  -218,  -218,  -218,   227,
    -218,   628,  -218,   224,  -218,   231,   211,   233,   273,  -218,
     274,   275,   276,    91,  -218,    74,   247,  -218,  -218,  -218,
      97,   -12,  -218,   279,  -218,   245,   229,   563,  -218,  -218,
    -218,    86,   230,   281,     3,    30,   256,    11,  -218,  -218,
      81,  -218,  -218,  -218,   287,  -218,  -218,   255,  -218,   258,
     -12,    86,    86,    86,   117,    86,   117,   289,  -218,   260,
      97,    92,  -218,   261,  -218,  -218,  -218,   -12,  -218,   263,
     294,  -218,  -218,  -218,   114,  -218,   293,   269,   121,   307,
      18,   628,  -218,    97,  -218,    97,  -218,   117,    86,  -218,
    -218,    57,   117,  -218,   289,   277,  -218,   280,  -218,  -218,
     139,  -218,   264,   266,   259,    16,  -218,  -218,  -218,  -218,
       6,   169,  -218,  -218,    97,  -218,  -218,  -218,   285,  -218,
     324,   327,  -218,  -218,    17,   296,   295,   325,   297,    22,
    -218,   119,  -218,   -12,   325,   278,   300,  -218,  -218,   302,
    -218,   -12,    86,   282,   590,  -218,   -12,    86,  -218,   308,
    -218,   -12,  -218,  -218
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -218,  -218,   314,  -218,   150,   180,  -218,  -218,   183,  -218,
    -218,  -218,  -218,  -201,  -217,  -218,    93,  -218,  -218,  -218,
      63,  -218,  -218,  -218,  -218,  -218,   105,  -202,  -122,  -185,
     -10,     0,     5,   -56,   323,  -218,    80,    88,    94,   156,
     107,    -1,  -218,   216,  -218,   271,   -38,  -218,  -218,  -218,
    -218,  -218,   141,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
     253,   -24,  -207
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -70
static const yytype_int16 yytable[] =
{
      34,    75,    91,   226,   165,    35,    71,    72,    80,   117,
     228,    34,   122,    79,   213,   238,    76,   250,    81,   128,
     246,   250,    79,   -52,    79,    90,    85,   255,    34,    79,
     237,   201,    92,    35,     2,     3,     4,     5,     6,   188,
     214,   215,    59,   250,   145,     7,   260,    34,   129,     8,
      77,   271,    35,    86,   250,   166,   256,   287,     9,    10,
     118,   140,   295,   261,   207,   209,   280,   216,   101,   102,
      11,   119,   262,   263,    78,   264,   -52,    14,    15,    16,
      17,   114,   288,    87,   -69,   141,   300,   296,    60,    18,
      34,   132,   133,    79,   305,    35,    82,   117,    83,   310,
     115,   116,   103,   104,   313,     2,     3,     4,     5,    69,
     156,   157,   158,   262,   263,    67,   264,   168,     2,     3,
       4,     5,     6,    95,   170,   171,   172,    81,   162,     7,
     163,   109,   110,     8,    90,    34,   173,   111,   112,   113,
      35,    11,     9,    10,    88,   185,   219,   220,    14,    15,
      16,    17,   249,    89,    11,   164,   200,   219,   243,   253,
      18,    14,    15,    16,    17,   297,   298,   231,   232,   233,
     231,   232,   233,    18,   231,   232,   233,   275,   143,   144,
      96,   210,   309,    97,     2,     3,     4,     5,    69,   146,
     147,    81,   231,   232,   233,     7,   242,   148,   149,     8,
     123,   227,   168,   230,   124,   230,   125,   282,     9,    10,
      60,    81,    81,    81,   126,    81,   154,   155,   127,   258,
      11,   259,   231,   232,   233,    73,    74,    14,    15,    16,
      17,   131,     2,     3,     4,     5,     6,   136,   230,    18,
     139,   142,   159,     7,   160,   161,   257,     8,    81,   169,
     283,   105,   106,   107,   108,   180,     9,    10,   181,   183,
     281,   150,   151,   152,   153,   186,   187,   189,    11,   206,
      81,   190,   191,   192,   168,    14,    15,    16,    17,   168,
     193,   194,   195,   196,    81,   199,   204,    18,   205,    81,
     212,   211,   306,   217,   223,   224,   239,   311,   225,   241,
     247,   245,    81,   248,   251,    93,   252,    81,     2,     3,
       4,     5,     6,   -69,   -69,   273,   254,   278,    60,     7,
     274,   276,   277,     8,   284,    61,    62,    63,    64,    65,
      66,   285,     9,    10,   286,   289,   291,   294,   290,   302,
     303,   304,    94,   307,    11,    67,   -69,   218,   312,    12,
      13,    14,    15,    16,    17,   198,   197,   301,   279,   272,
     100,   135,   244,    18,     0,    19,     0,    20,    21,    22,
       0,     0,    23,    24,    25,    26,     1,    27,     2,     3,
       4,     5,     6,    61,    62,    63,    64,    65,    66,     7,
     184,     0,     0,     8,     0,     0,     0,     0,     0,    98,
      99,     0,     9,    10,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    11,     0,     0,     0,     0,    12,
      13,    14,    15,    16,    17,     2,     3,     4,     5,     6,
       0,     0,     0,    18,     0,    19,     7,    20,    21,    22,
       8,     0,    23,    24,    25,    26,     0,    27,     0,     9,
      10,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     134,    11,     0,     0,     0,     0,     0,    13,    14,    15,
      16,    17,     2,     3,     4,     5,     6,     0,     0,     0,
      18,     0,     0,     7,     0,    21,    22,     8,     0,    23,
      24,    25,    26,     0,    27,     0,     9,    10,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   182,    11,     0,
       0,     0,     0,     0,    13,    14,    15,    16,    17,     2,
       3,     4,     5,     6,     0,     0,     0,    18,     0,     0,
       7,     0,    21,    22,     8,     0,    23,    24,    25,    26,
       0,    27,     0,     9,    10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    11,     0,     0,     0,     0,
       0,    13,    14,    15,    16,    17,     2,     3,     4,     5,
       6,     0,     0,     0,    18,     0,     0,     7,     0,    21,
      22,     8,     0,    23,    24,    25,    26,     0,    27,     0,
       9,    10,     0,     2,     3,     4,     5,     6,     0,     0,
       0,     0,    11,   208,     7,     0,     0,     0,     8,    14,
      15,    16,    17,     0,     0,     0,     0,     9,    10,     0,
       0,    18,     0,     0,     0,     0,     0,     0,     0,    11,
     308,     2,     3,     4,     5,     6,    14,    15,    16,    17,
       0,     0,     7,     0,     0,     0,     8,     0,    18,     0,
       0,     0,     0,     0,     0,     9,    10,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    11,     0,     0,
       0,     0,     0,     0,    14,    15,    16,    17,     0,     0,
       0,     0,     0,     0,     0,     0,    18
};

static const yytype_int16 yycheck[] =
{
       0,    11,    26,   210,   126,     0,     7,     8,    18,    47,
     212,    11,    68,     7,    11,   216,    11,   234,    18,     8,
     227,   238,     7,     7,     7,    37,    21,     9,    28,     7,
     215,    43,    27,    28,     3,     4,     5,     6,     7,   161,
      37,    11,    73,   260,   100,    14,   247,    47,    37,    18,
       4,   252,    47,    39,   271,    40,    38,    40,    27,    28,
      60,    19,    40,   248,   186,   187,    60,    37,    33,    34,
      39,    40,    56,    57,     7,    59,    60,    46,    47,    48,
      49,     8,   284,    39,     8,    43,   293,   289,    12,    58,
      90,    86,    87,     7,   301,    90,     7,   135,     7,   306,
      27,    28,    25,    26,   311,     3,     4,     5,     6,     7,
     111,   112,   113,    56,    57,    39,    59,   127,     3,     4,
       5,     6,     7,     7,    50,    51,    52,   127,   123,    14,
     125,    13,    14,    18,    37,   135,    62,    15,    16,    17,
     135,    39,    27,    28,    43,   140,    65,    66,    46,    47,
      48,    49,    38,    43,    39,    40,   180,    65,    66,    38,
      58,    46,    47,    48,    49,    46,    47,    53,    54,    55,
      53,    54,    55,    58,    53,    54,    55,    38,    98,    99,
       8,   191,   304,    43,     3,     4,     5,     6,     7,   101,
     102,   191,    53,    54,    55,    14,   220,   103,   104,    18,
      40,   211,   212,   213,    40,   215,    19,    38,    27,    28,
      12,   211,   212,   213,    39,   215,   109,   110,    39,   243,
      39,   245,    53,    54,    55,     9,    10,    46,    47,    48,
      49,    43,     3,     4,     5,     6,     7,    71,   248,    58,
      43,     7,     7,    14,    40,     9,   241,    18,   248,     7,
     274,    29,    30,    31,    32,    40,    27,    28,    40,    39,
     270,   105,   106,   107,   108,    39,    39,    43,    39,    40,
     270,    40,    61,    40,   284,    46,    47,    48,    49,   289,
       7,     7,     7,     7,   284,    38,     7,    58,    43,   289,
       9,    61,   302,    37,     7,    40,     7,   307,    40,    39,
      37,    40,   302,     9,    11,     0,    37,   307,     3,     4,
       5,     6,     7,     7,     8,    38,     9,    58,    12,    14,
      40,    57,    56,    18,    39,    19,    20,    21,    22,    23,
      24,     7,    27,    28,     7,    39,    11,    40,    43,    61,
      40,    39,    28,    61,    39,    39,    40,   197,    40,    44,
      45,    46,    47,    48,    49,   175,   173,   294,   265,   254,
      37,    90,   221,    58,    -1,    60,    -1,    62,    63,    64,
      -1,    -1,    67,    68,    69,    70,     1,    72,     3,     4,
       5,     6,     7,    19,    20,    21,    22,    23,    24,    14,
     137,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,    35,
      36,    -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    44,
      45,    46,    47,    48,    49,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    58,    -1,    60,    14,    62,    63,    64,
      18,    -1,    67,    68,    69,    70,    -1,    72,    -1,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      58,    -1,    -1,    14,    -1,    63,    64,    18,    -1,    67,
      68,    69,    70,    -1,    72,    -1,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    58,    -1,    -1,
      14,    -1,    63,    64,    18,    -1,    67,    68,    69,    70,
      -1,    72,    -1,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    58,    -1,    -1,    14,    -1,    63,
      64,    18,    -1,    67,    68,    69,    70,    -1,    72,    -1,
      27,    28,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    39,    40,    14,    -1,    -1,    -1,    18,    46,
      47,    48,    49,    -1,    -1,    -1,    -1,    27,    28,    -1,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,     3,     4,     5,     6,     7,    46,    47,    48,    49,
      -1,    -1,    14,    -1,    -1,    -1,    18,    -1,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,    14,    18,    27,
      28,    39,    44,    45,    46,    47,    48,    49,    58,    60,
      62,    63,    64,    67,    68,    69,    70,    72,    75,    76,
      77,    83,    95,   104,   105,   106,   107,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   127,   128,   129,   130,   131,   132,    73,
      12,    19,    20,    21,    22,    23,    24,    39,   108,     7,
     105,   115,   115,   117,   117,   104,   106,     4,     7,     7,
     104,   105,     7,     7,    82,   106,    39,    39,    43,    43,
      37,   135,   106,     0,    76,     7,     8,    43,    35,    36,
     108,    33,    34,    25,    26,    29,    30,    31,    32,    13,
      14,    15,    16,    17,     8,    27,    28,   120,   105,    40,
     102,   106,   107,    40,    40,    19,    39,    39,     8,    37,
      78,    43,   106,   106,    38,   119,    71,   133,   134,    43,
      19,    43,     7,   110,   110,   107,   111,   111,   112,   112,
     113,   113,   113,   113,   114,   114,   115,   115,   115,     7,
      40,     9,   106,   106,    40,   102,    40,   101,   104,     7,
      50,    51,    52,    62,    79,    80,    81,    84,    85,    86,
      40,    40,    38,    39,   134,   106,    39,    39,   102,    43,
      40,    61,    40,     7,     7,     7,     7,    82,    79,    38,
     135,    43,   135,   136,     7,    43,    40,   102,    40,   102,
     104,    61,     9,    11,    37,    11,    37,    37,    78,    65,
      66,   125,   126,     7,    40,    40,   136,   104,   101,   103,
     104,    53,    54,    55,    87,    88,    99,   103,    87,     7,
     100,    39,   135,    66,   126,    40,   136,    37,     9,    38,
      88,    11,    37,    38,     9,     9,    38,   106,   135,   135,
      87,   103,    56,    57,    59,    89,    90,    91,    96,    97,
      98,    87,   100,    38,    40,    38,    57,    56,    58,    90,
      60,   104,    38,   135,    39,     7,     7,    40,   101,    39,
      43,    11,    92,    94,    40,    40,   101,    46,    47,    93,
     136,    94,    61,    40,    39,   136,   104,    61,    40,   102,
     136,   104,    40,   136
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
#line 110 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 5:
#line 116 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 6:
#line 120 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 7:
#line 124 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 8:
#line 128 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		ast_compile_entry((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 9:
#line 134 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 10:
#line 140 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value)
	;}
    break;

  case 11:
#line 146 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 12:
#line 150 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 13:
#line 154 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 14:
#line 158 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 15:
#line 164 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 16:
#line 168 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 17:
#line 174 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 18:
#line 178 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value)
	;}
    break;

  case 19:
#line 184 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 20:
#line 188 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 21:
#line 194 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 22:
#line 200 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (5)].string_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 23:
#line 204 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[(2) - (7)].string_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 24:
#line 210 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 25:
#line 214 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[(2) - (6)].string_value), (yyvsp[(4) - (6)].ast_value));
	;}
    break;

  case 26:
#line 220 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (5)].string_value), ast_new_blank(), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 27:
#line 224 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[(2) - (7)].string_value), (yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 28:
#line 230 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 29:
#line 234 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 30:
#line 238 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 31:
#line 244 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 32:
#line 248 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[(1) - (3)].access_level_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 33:
#line 254 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 34:
#line 258 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 35:
#line 262 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[(1) - (2)].ast_value), ast_new_member_decl((yyvsp[(2) - (2)].ast_value)));
	;}
    break;

  case 39:
#line 273 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[(4) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 40:
#line 277 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 41:
#line 283 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (5)].chain_type_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 42:
#line 287 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[(2) - (4)].chain_type_value), ast_new_blank());
	;}
    break;

  case 43:
#line 293 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.chain_type_value) = chain_type_super;
	;}
    break;

  case 44:
#line 297 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.chain_type_value) = chain_type_this;
	;}
    break;

  case 45:
#line 303 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;

  case 47:
#line 310 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[(2) - (8)].string_value), (yyvsp[(4) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 48:
#line 314 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[(2) - (7)].string_value), (yyvsp[(7) - (7)].ast_value), (yyvsp[(6) - (7)].ast_value));
	;}
    break;

  case 49:
#line 320 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_method_decl((yyvsp[(1) - (9)].modifier_type_value), (yyvsp[(3) - (9)].string_value), (yyvsp[(5) - (9)].ast_value), (yyvsp[(9) - (9)].ast_value), (yyvsp[(8) - (9)].ast_value));
	;}
    break;

  case 50:
#line 324 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[(1) - (8)].modifier_type_value), (yyvsp[(3) - (8)].string_value), (yyvsp[(8) - (8)].ast_value), (yyvsp[(7) - (8)].ast_value));
	;}
    break;

  case 51:
#line 330 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[(1) - (4)].modifier_type_value), (yyvsp[(2) - (4)].ast_value), (yyvsp[(3) - (4)].string_value));
	;}
    break;

  case 52:
#line 336 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.modifier_type_value) = modifier_none;
	;}
    break;

  case 53:
#line 340 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 54:
#line 344 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.modifier_type_value) = modifier_static_native();
	;}
    break;

  case 55:
#line 348 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.modifier_type_value) = modifier_static;
	;}
    break;

  case 56:
#line 352 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.modifier_type_value) = modifier_native;
	;}
    break;

  case 57:
#line 358 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.access_level_value) = access_public;
	;}
    break;

  case 58:
#line 362 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.access_level_value) = access_private;
	;}
    break;

  case 59:
#line 366 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.access_level_value) = access_protected;
	;}
    break;

  case 60:
#line 372 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 61:
#line 376 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[(1) - (3)].string_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 62:
#line 382 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].string_value));
	;}
    break;

  case 63:
#line 386 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[(1) - (4)].ast_value), (yyvsp[(2) - (4)].string_value), (yyvsp[(4) - (4)].ast_value))
	;}
    break;

  case 64:
#line 392 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 65:
#line 396 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[(1) - (3)].ast_value)), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 66:
#line 402 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 67:
#line 406 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 68:
#line 412 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 69:
#line 418 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 70:
#line 422 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[(1) - (3)].string_value)), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 73:
#line 432 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_generic_assign((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].assign_otype_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 74:
#line 436 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_generic_assign(ast_new_variable((yyvsp[(1) - (3)].string_value)), (yyvsp[(2) - (3)].assign_otype_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 75:
#line 442 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_def;
	;}
    break;

  case 76:
#line 446 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_add;
	;}
    break;

  case 77:
#line 450 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_sub;
	;}
    break;

  case 78:
#line 454 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_mul;
	;}
    break;

  case 79:
#line 458 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_div;
	;}
    break;

  case 80:
#line 462 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.assign_otype_value) = assign_otype_mod;
	;}
    break;

  case 82:
#line 469 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_bit_or((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 83:
#line 473 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_logic_or((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 85:
#line 480 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_bit_and((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 86:
#line 484 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_logic_and((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 88:
#line 491 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_equal((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 89:
#line 495 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_notequal((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 91:
#line 502 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_gt((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 92:
#line 506 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_ge((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 93:
#line 510 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_lt((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 94:
#line 514 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_le((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 96:
#line 521 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_add((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 97:
#line 525 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_sub((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 99:
#line 532 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_mul((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 100:
#line 536 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_div((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 101:
#line 540 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_mod((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 103:
#line 547 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_not((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 104:
#line 551 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_neg((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 106:
#line 558 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_pre_inc((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 107:
#line 562 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_pre_dec((yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 109:
#line 569 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 110:
#line 573 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_invoke((yyvsp[(1) - (5)].ast_value), (yyvsp[(3) - (5)].string_value), ast_new_blank());
	;}
    break;

  case 111:
#line 577 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_invoke((yyvsp[(1) - (6)].ast_value), (yyvsp[(3) - (6)].string_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 112:
#line 581 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_post_inc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 113:
#line 585 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_post_dec((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 118:
#line 595 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_true();
	;}
    break;

  case 119:
#line 599 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_false();
	;}
    break;

  case 120:
#line 603 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[(1) - (1)].string_value));
	;}
    break;

  case 121:
#line 607 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_call((yyvsp[(1) - (3)].string_value), ast_new_blank());
	;}
    break;

  case 122:
#line 611 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_call((yyvsp[(1) - (4)].string_value), (yyvsp[(3) - (4)].ast_value));
	;}
    break;

  case 123:
#line 615 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(2) - (3)].ast_value);
	;}
    break;

  case 124:
#line 619 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_cast((yyvsp[(2) - (4)].ast_value), (yyvsp[(4) - (4)].ast_value));
	;}
    break;

  case 125:
#line 623 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_static_invoke((yyvsp[(1) - (5)].ast_value), (yyvsp[(3) - (5)].string_value), ast_new_blank());
	;}
    break;

  case 126:
#line 627 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_static_invoke((yyvsp[(1) - (6)].ast_value), (yyvsp[(3) - (6)].string_value), (yyvsp[(5) - (6)].ast_value));
	;}
    break;

  case 127:
#line 631 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_field_access_fqcn((yyvsp[(1) - (3)].ast_value), (yyvsp[(3) - (3)].string_value));
	;}
    break;

  case 128:
#line 635 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_this();
	;}
    break;

  case 129:
#line 639 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_super();
	;}
    break;

  case 130:
#line 643 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (5)].ast_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 131:
#line 647 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[(2) - (4)].ast_value), ast_new_blank());
	;}
    break;

  case 132:
#line 653 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[(1) - (1)].ast_value));
	;}
    break;

  case 133:
#line 657 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 134:
#line 663 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 145:
#line 679 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[(1) - (3)].ast_value), (yyvsp[(2) - (3)].string_value));
	;}
    break;

  case 146:
#line 685 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[(1) - (5)].ast_value), (yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 147:
#line 691 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[(2) - (5)].string_value), (yyvsp[(4) - (5)].ast_value));
	;}
    break;

  case 148:
#line 697 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_if((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 149:
#line 701 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[(3) - (7)].ast_value), (yyvsp[(5) - (7)].ast_value), (yyvsp[(7) - (7)].ast_value));
	;}
    break;

  case 150:
#line 705 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[(3) - (6)].ast_value), (yyvsp[(5) - (6)].ast_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 151:
#line 709 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[(3) - (8)].ast_value), (yyvsp[(5) - (8)].ast_value), (yyvsp[(6) - (8)].ast_value), (yyvsp[(8) - (8)].ast_value));
	;}
    break;

  case 153:
#line 716 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[(1) - (2)].ast_value), (yyvsp[(2) - (2)].ast_value));
	;}
    break;

  case 154:
#line 722 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 155:
#line 728 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_while((yyvsp[(3) - (5)].ast_value), (yyvsp[(5) - (5)].ast_value));
	;}
    break;

  case 156:
#line 734 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_break();
	;}
    break;

  case 157:
#line 740 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_continue();
	;}
    break;

  case 158:
#line 746 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_return((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 159:
#line 752 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 160:
#line 758 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_try((yyvsp[(2) - (3)].ast_value), (yyvsp[(3) - (3)].ast_value));
	;}
    break;

  case 161:
#line 764 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = (yyvsp[(1) - (1)].ast_value);
	;}
    break;

  case 162:
#line 768 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[(2) - (2)].ast_value), (yyvsp[(1) - (2)].ast_value));
	;}
    break;

  case 163:
#line 774 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[(3) - (6)].string_value), (yyvsp[(4) - (6)].string_value), (yyvsp[(6) - (6)].ast_value));
	;}
    break;

  case 164:
#line 780 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[(2) - (3)].ast_value));
	;}
    break;

  case 165:
#line 784 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_scope_empty();
	;}
    break;

  case 166:
#line 790 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"
    {
		(yyval.ast_value) = ast_new_blank();
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 2824 "signal.tab.c"
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


#line 795 "/Users/koya/Desktop/VSCode/CSignal/CSignal/CSignal/CSignal/signal/parse/signal.y"

