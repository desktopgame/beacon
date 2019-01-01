/* A Bison parser, made by GNU Bison 3.0.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "beacon.y" /* yacc.c:339  */

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
#include "../util/string_pool.h"

#define YYDEBUG 1
#define YYERROR_VERBOSE 1

#line 83 "beacon.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "beacon.tab.h".  */
#ifndef YY_YY_BEACON_TAB_H_INCLUDED
# define YY_YY_BEACON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHAR_LITERAL = 258,
    STRING_LITERAL = 259,
    SHORT = 260,
    INT = 261,
    LONG = 262,
    FLOAT = 263,
    DOUBLE = 264,
    IDENT = 265,
    DOT = 266,
    COMMA = 267,
    COLON = 268,
    COLO_COLO = 269,
    LINE = 270,
    ADD = 271,
    SUB = 272,
    MUL = 273,
    DIV = 274,
    MOD = 275,
    NOT = 276,
    LSHIFT = 277,
    RSHIFT = 278,
    CHILDA = 279,
    EQUAL = 280,
    NOTEQUAL = 281,
    GT = 282,
    GE = 283,
    LT = 284,
    LE = 285,
    LGEN = 286,
    RGEN = 287,
    BIT_AND = 288,
    LOGIC_AND = 289,
    BIT_OR = 290,
    LOGIC_OR = 291,
    FINAL = 292,
    ASSIGN = 293,
    ADD_ASSIGN = 294,
    SUB_ASSIGN = 295,
    MUL_ASSIGN = 296,
    DIV_ASSIGN = 297,
    MOD_ASSIGN = 298,
    AND_ASSIGN = 299,
    OR_ASSIGN = 300,
    LSHIFT_ASSIGN = 301,
    RSHIFT_ASSIGN = 302,
    EXC_OR_ASSIGN = 303,
    INC = 304,
    DEC = 305,
    EXC_OR = 306,
    LCB = 307,
    RCB = 308,
    LRB = 309,
    RRB = 310,
    LSB = 311,
    RSB = 312,
    SEMI = 313,
    IMPORT = 314,
    VAR = 315,
    PROPERTY = 316,
    DEFSET = 317,
    DEFGET = 318,
    THIS_TOK = 319,
    SUPER_TOK = 320,
    TRUE_TOK = 321,
    FALSE_TOK = 322,
    NULL_TOK = 323,
    AS = 324,
    ABSTRACT = 325,
    INTERFACE = 326,
    CLASS = 327,
    ENUM = 328,
    PUBLIC = 329,
    PRIVATE = 330,
    PROTECTED = 331,
    STATIC = 332,
    NATIVE = 333,
    NEW = 334,
    DEF = 335,
    ARROW = 336,
    NAMESPACE = 337,
    RETURN = 338,
    YIELD = 339,
    IF = 340,
    ELIF = 341,
    ELSE = 342,
    WHILE = 343,
    BREAK = 344,
    CONTINUE = 345,
    TRY = 346,
    CATCH = 347,
    THROW = 348,
    ASSER_T = 349,
    DEFER = 350,
    INSTANCEOF = 351,
    OPERATOR = 352,
    BOUNDS_EXTENDS = 353,
    BOUNDS_SUPER = 354,
    SUBSCRIPT_SET = 355,
    SUBSCRIPT_GET = 356,
    QUOTE = 357,
    NEGATIVE = 358,
    POSITIVE = 359,
    REF = 360,
    FUNCCALL = 361,
    ARRAY_SUBSCRIPT = 362,
    FORM_TYPE = 363
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "beacon.y" /* yacc.c:355  */

	char char_value;
	bc_StringView stringv_value;
	bc_AST* ast_value;
	bc_AssignOperatorType assign_otype_value;
	bc_ConstructorChainType chain_type_value;
	bc_AccessLevel access_level_value;

#line 241 "beacon.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_BEACON_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 272 "beacon.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2618

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  110
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  249
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  653

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   363

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     109,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   150,   150,   151,   152,   158,   160,   166,   170,   174,
     180,   187,   194,   198,   199,   200,   201,   205,   209,   217,
     220,   224,   228,   235,   236,   243,   250,   258,   261,   268,
     272,   279,   285,   289,   295,   299,   306,   310,   317,   321,
     329,   332,   336,   337,   344,   351,   355,   362,   363,   364,
     365,   366,   370,   374,   381,   385,   392,   396,   404,   407,
     411,   415,   422,   426,   430,   434,   441,   445,   449,   453,
     457,   461,   465,   469,   473,   478,   482,   487,   491,   496,
     500,   505,   509,   514,   519,   524,   528,   533,   538,   545,
     549,   553,   557,   564,   568,   572,   576,   583,   587,   591,
     595,   602,   606,   613,   617,   624,   628,   632,   636,   643,
     647,   651,   658,   662,   669,   673,   680,   684,   692,   695,
     702,   706,   713,   720,   724,   733,   737,   738,   741,   745,
     749,   753,   757,   761,   765,   769,   773,   777,   781,   785,
     789,   793,   797,   801,   805,   809,   813,   817,   821,   825,
     829,   833,   837,   841,   845,   849,   853,   857,   861,   866,
     870,   874,   878,   882,   886,   890,   894,   898,   902,   906,
     910,   914,   918,   922,   926,   930,   934,   938,   942,   946,
     950,   954,   958,   962,   966,   970,   974,   978,   982,   985,
     989,   993,   997,  1003,  1004,  1005,  1006,  1007,  1008,  1009,
    1010,  1014,  1018,  1027,  1031,  1037,  1041,  1042,  1043,  1044,
    1045,  1046,  1047,  1048,  1049,  1050,  1051,  1052,  1053,  1054,
    1057,  1063,  1069,  1075,  1079,  1083,  1087,  1093,  1094,  1100,
    1106,  1112,  1118,  1124,  1128,  1134,  1140,  1146,  1150,  1156,
    1162,  1166,  1172,  1178,  1184,  1190,  1194,  1200,  1204,  1207
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR_LITERAL", "STRING_LITERAL",
  "SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "IDENT", "DOT", "COMMA",
  "COLON", "COLO_COLO", "LINE", "ADD", "SUB", "MUL", "DIV", "MOD", "NOT",
  "LSHIFT", "RSHIFT", "CHILDA", "EQUAL", "NOTEQUAL", "GT", "GE", "LT",
  "LE", "LGEN", "RGEN", "BIT_AND", "LOGIC_AND", "BIT_OR", "LOGIC_OR",
  "FINAL", "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "AND_ASSIGN", "OR_ASSIGN", "LSHIFT_ASSIGN",
  "RSHIFT_ASSIGN", "EXC_OR_ASSIGN", "INC", "DEC", "EXC_OR", "LCB", "RCB",
  "LRB", "RRB", "LSB", "RSB", "SEMI", "IMPORT", "VAR", "PROPERTY",
  "DEFSET", "DEFGET", "THIS_TOK", "SUPER_TOK", "TRUE_TOK", "FALSE_TOK",
  "NULL_TOK", "AS", "ABSTRACT", "INTERFACE", "CLASS", "ENUM", "PUBLIC",
  "PRIVATE", "PROTECTED", "STATIC", "NATIVE", "NEW", "DEF", "ARROW",
  "NAMESPACE", "RETURN", "YIELD", "IF", "ELIF", "ELSE", "WHILE", "BREAK",
  "CONTINUE", "TRY", "CATCH", "THROW", "ASSER_T", "DEFER", "INSTANCEOF",
  "OPERATOR", "BOUNDS_EXTENDS", "BOUNDS_SUPER", "SUBSCRIPT_SET",
  "SUBSCRIPT_GET", "QUOTE", "NEGATIVE", "POSITIVE", "REF", "FUNCCALL",
  "ARRAY_SUBSCRIPT", "FORM_TYPE", "'\\n'", "$accept", "compilation_unit",
  "init_decl", "body_decl", "namespace_decl", "namespace_body",
  "namespace_member_decl", "namespace_member_decl_list",
  "namespace_member_decl_optional", "namespace_path", "import_list",
  "import", "parameterized_typename", "type_parameter_group",
  "GetParameterListType", "type_parameter", "abstract_class_decl",
  "class_decl", "enum_decl", "interface_decl", "access_member_tree_opt",
  "access_member_tree", "access_member_list", "member_define_list",
  "member_define", "constructor_define", "constructor_chain",
  "constructor_chain_type_T", "constructor_chain_optional",
  "function_define", "method_define", "operator_define", "field_define",
  "prop_set", "prop_get", "prop_define", "modifier_type_T_list",
  "modifier_type_T", "access_level_T", "ident_list", "parameter_list",
  "argument_list", "typename_group", "typename_list", "typename_T",
  "fqcn_part", "expression", "expression_nobrace", "lhs", "primary",
  "stmt_list", "stmt", "variable_decl_stmt", "variable_init_stmt",
  "inferenced_type_init_stmt", "if_stmt", "elif_list", "elif",
  "while_stmt", "break_stmt", "continue_stmt", "return_stmt", "throw_stmt",
  "try_stmt", "catch_stmt_list", "catch_stmt", "assert_stmt", "defer_stmt",
  "yield_return_stmt", "yield_break_stmt", "scope", "scope_optional",
  "stmt_term", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
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
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,    10
};
# endif

#define YYPACT_NINF -466

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-466)))

#define YYTABLE_NINF -123

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     903,  -100,    45,   808,   996,    48,  -466,  -466,  -466,  -466,
    -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  2503,  2503,
    2503,  2503,  2503,   101,  -466,  -466,  -466,  -466,  -466,   118,
     166,   232,  2358,   -50,  2503,  2503,   188,   188,   145,  2503,
    2503,  1275,  -466,  -466,  -466,   239,   210,   461,   208,   614,
    -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,
    -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,   210,    -4,
      -4,    -4,    -4,  1019,   215,   210,   233,  -466,   211,  -466,
     461,  -466,  2503,   188,   582,   130,  -466,  -466,  1089,   200,
     461,   314,  -466,   -18,   297,   118,   301,  2567,  2503,  2503,
    2503,  2503,  2503,  2503,  2503,  2503,  2503,  2503,  2503,  2503,
    2503,  2503,  2503,  2503,  2503,  2503,   118,   118,  -466,  2397,
    2503,  2503,  2503,  2503,  2503,  2503,  2503,  2503,  2503,  2503,
    2503,  -466,  -466,  2503,   269,   325,   291,   336,   197,  -466,
    -466,   461,  -466,   -51,  -466,  -466,  -466,  -466,  1182,  -466,
     298,   200,  -466,  -466,  2503,  -466,  2503,  -466,  -466,     3,
    -466,   210,   299,   303,   304,   307,   308,   312,   313,   315,
     316,   317,   319,   320,   321,   324,   326,   327,   328,   330,
     331,   332,   333,    -1,    -1,    -4,    -4,    -4,   151,   151,
     402,   402,   187,   187,   187,   187,   104,  2301,  2321,  2264,
     725,  -466,  -466,  -466,    54,  2226,  2226,  2226,  2226,  2226,
    2226,  2226,  2226,  2226,  2226,  2226,  2226,   461,  2424,  -466,
      12,  -466,    18,  -466,   296,   369,   369,   379,   232,  -466,
     197,   337,  -466,  -466,  -466,  -466,  -466,  2503,   145,   -31,
    -466,  -466,  -466,   118,  -466,   461,   461,   118,  -466,  -466,
    -466,  2503,  2450,  2503,  2503,  2503,   338,  2503,  2503,   340,
    2503,  2503,  2503,  2503,  2503,  2503,  2503,  2503,  2503,  2503,
    2503,  2503,  -466,  -466,  -466,    70,   325,  -466,   310,    81,
     382,   369,   233,   125,   224,   344,   211,  -466,  -466,   582,
    -466,   145,  -466,   387,  -466,  -466,  -466,  1298,  -466,  1362,
    1410,  1458,  1506,  -466,  1554,  1602,  -466,  1650,  1698,  1746,
    1794,  1842,  1890,  1938,  1986,  2034,  2082,  2130,  2226,  -466,
    -466,   118,   118,   318,  -466,   228,  -466,   118,   241,   118,
     241,   390,  -466,  -466,  -466,   343,  -466,  -466,  -466,  -466,
    -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,
    -466,  -466,  -466,  -466,   193,   392,   118,   118,   241,    10,
    -466,  -466,  -466,   350,   241,  -466,   391,    90,   352,  -466,
      59,   145,  -466,  -466,   193,   175,   353,   241,  -466,  -466,
       6,   241,  -466,    19,  -466,  -466,  -466,   241,  -466,   354,
    -466,    17,  -466,  -466,  -466,    11,  1100,     6,  -466,  -466,
    -466,  -466,  -466,  -466,    17,  -466,   398,   358,  -466,  -466,
     359,  -466,    17,   404,   233,   361,    27,   362,   363,   372,
     373,   374,   383,   384,   385,   389,   401,   419,   421,   422,
     428,   431,   438,   445,   446,   448,   449,   451,   452,  -466,
    -466,   413,   -13,  -466,  -466,   423,   394,   453,    20,   233,
     118,    24,   118,   118,   118,   381,   118,   118,   386,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,    -6,  2503,  -466,   400,   198,    36,   495,    84,
     455,    89,   430,   106,   123,   128,   131,   432,   139,   162,
     434,   163,   167,   168,   173,   177,   178,   179,   180,   181,
     183,   184,   199,   202,  2503,  -466,  1193,   198,   213,   246,
     456,   439,   203,   264,  -466,   193,   495,    43,   441,   118,
     442,   447,   450,   454,   118,   457,   459,   118,   460,   462,
     463,   464,   465,   467,   468,   469,   470,   471,   472,   473,
     474,  2178,  -466,   246,  -466,  -466,   223,   476,   499,   254,
     118,   484,  -466,  -466,   478,  -466,   193,   498,   204,   118,
     193,   118,   118,   118,   118,   193,   118,   118,   193,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,  -466,   480,  -466,  -466,  -466,   256,  -466,  -466,
     193,   118,  2477,  -466,   118,   500,   193,  -466,   193,   193,
     193,   193,  -466,   193,   193,  -466,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,  -466,
    -466,  -466,  -466,   193,  -466,   209,   193,   118,  -466,  -466,
    -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,
    -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,
    -466,   193,  -466
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,    23,     4,    25,     1,
     198,   199,   193,   194,   195,   196,   197,   123,     0,     0,
       0,     0,     0,     0,   186,   187,   200,   201,   202,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     8,     9,     0,   118,     0,   127,   188,
     126,     7,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,     2,    24,   118,   128,
     129,   183,   182,     0,     0,   118,    27,    21,     0,   249,
       0,   234,     0,     0,     0,     0,   231,   232,     0,     0,
       0,     0,   242,     0,     0,     0,   189,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   205,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   189,   125,     0,     0,     0,     0,     0,    19,    10,
     233,     0,   244,   223,   247,   248,   230,   246,     0,   203,
       0,   236,   237,   235,     0,   241,     0,   220,   124,     0,
     120,   118,   118,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   130,   131,   132,   133,   134,   157,   158,
     136,   137,   153,   154,   155,   156,   138,   141,   135,   140,
     139,   181,   180,   192,     0,   116,   142,   143,   144,   145,
     146,   147,   148,   149,   151,   152,   150,     0,     0,    31,
       0,    29,     0,    22,     0,     0,     0,     0,     0,    17,
      20,     0,    13,    14,    16,    15,   243,     0,     0,   225,
     227,   245,   204,     0,   238,     0,     0,     0,   119,   122,
     190,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   191,   222,   185,     0,     0,    28,     0,     0,
       0,     0,    27,     0,     0,     0,     0,    18,    11,     0,
     224,     0,   228,     0,   240,   221,   121,     0,   179,     0,
       0,     0,     0,   177,     0,     0,   178,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,   184,
      30,     0,     0,     0,   114,     0,    26,     0,    40,     0,
      40,     0,    12,   229,   226,     0,   159,   160,   161,   162,
     163,   174,   175,   168,   169,   164,   165,   166,   167,   171,
     173,   170,   172,   176,     0,     0,     0,     0,    40,     0,
     109,   110,   111,     0,    41,    42,     0,     0,     0,   112,
       0,     0,    61,   115,     0,     0,     0,    40,    38,    43,
       0,    40,    34,     0,    36,   239,    60,    40,    32,     0,
     108,     0,   107,   105,   106,     0,     0,    44,    45,    47,
      48,    49,    50,    51,     0,   103,     0,     0,   113,    37,
       0,    39,     0,     0,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
     104,     0,     0,    35,    33,     0,     0,     0,     0,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    90,     0,     0,     0,    58,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    89,     0,     0,     0,     0,
       0,     0,     0,     0,    59,     0,    58,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    92,     0,    93,    94,     0,     0,     0,     0,
       0,     0,    57,    56,     0,    53,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    91,     0,    97,    98,   102,     0,    95,    96,
       0,     0,     0,    52,     0,     0,     0,    86,     0,     0,
       0,     0,    84,     0,     0,    85,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   101,
      99,   100,    65,     0,    55,     0,     0,     0,    66,    67,
      68,    69,    70,    81,    82,    75,    76,    71,    72,    73,
      74,    78,    80,    77,    79,    83,    88,    87,    64,    54,
      63,     0,    62
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -466,  -466,  -466,   440,  -466,   240,   306,  -466,  -466,   309,
    -466,   522,  -218,  -277,  -466,   258,  -466,  -466,  -466,  -466,
    -307,  -466,   218,  -466,   186,  -466,  -466,  -466,    68,  -466,
    -466,  -466,  -466,    78,    44,  -466,  -285,   -53,  -465,  -466,
     388,  -216,   -62,   -79,   113,    -3,   677,  -466,  -466,  -466,
    -466,   -29,  -466,  -466,  -466,  -466,  -466,   347,  -466,  -466,
    -466,  -466,  -466,  -466,  -466,   443,  -466,  -466,  -466,  -466,
      -7,  -313,   -33
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    42,    43,   139,   229,   230,   231,    78,
       5,     6,   283,   136,   220,   221,   232,   233,   234,   235,
     363,   364,   365,   397,   398,   399,   514,   554,   515,    44,
     400,   401,   402,   509,   547,   403,   404,   405,   366,   370,
     279,   204,    96,   159,   280,    68,    47,    48,    49,    50,
     148,    51,    52,    53,    54,    55,   239,   240,    56,    57,
      58,    59,    60,    61,   151,   152,    62,    63,    64,    65,
     145,   146,    81
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      46,    46,   275,    86,    87,   326,   131,    97,   284,     7,
      97,   510,    92,   134,   118,   247,    17,   100,   101,   102,
     156,   414,   247,   368,   276,   473,    75,    17,    17,   408,
      17,    89,   504,    82,    17,   237,   238,   449,    46,    83,
     157,   372,   510,   390,   548,   474,    17,   140,   390,     8,
     142,   376,   505,    17,   390,   237,   291,   153,   155,   149,
     248,   386,   377,   325,   390,   116,   271,   391,   116,   277,
     389,   383,   409,   278,   407,   478,   392,   143,   548,   482,
     410,   392,   271,   393,   394,    46,   395,   392,   393,   394,
     415,   511,   161,   322,   393,   394,   322,   392,   557,   249,
     250,   322,   247,   396,   393,   394,   412,     2,   236,   272,
     416,    74,   384,   161,   161,    97,    45,    45,   322,   242,
      98,    99,   100,   101,   102,   319,   103,   104,    17,   105,
     106,   107,   108,   109,   110,   322,   323,   447,   327,   516,
     322,    97,   381,   322,   518,    46,    98,    99,   100,   101,
     102,   322,   103,   104,    45,   105,   106,   107,   108,   109,
     110,   520,    97,   111,   112,   113,   114,    98,    99,   100,
     101,   102,   480,   116,   322,   322,    76,   328,   521,   322,
     322,   115,    88,   522,   273,   322,   523,   247,   144,   322,
     322,   322,   322,   322,   525,   322,   322,    88,    97,   116,
     117,    45,   555,    98,    99,   100,   101,   102,   160,   103,
     104,   322,   294,   295,   322,   322,   322,   526,   528,   161,
     116,   271,   529,   530,    94,   137,   117,   387,   531,   201,
     202,   290,   532,   533,   534,   535,   536,   329,   537,   538,
     161,   357,    77,   593,   161,    88,    79,   597,   359,    93,
     367,   144,   602,   133,   539,   605,   116,   540,   551,   595,
     508,    45,   119,   138,   649,    88,    95,   224,   225,   226,
     227,   544,   360,   361,   362,    88,   330,   622,   375,   228,
     358,   584,   333,   628,   334,   629,   630,   631,   632,   135,
     633,   634,   150,   635,   636,   637,   638,   639,   640,   641,
     642,   643,   644,   645,   646,   647,    88,   158,    88,   546,
     648,  -122,   588,   650,   620,   360,   361,   362,   161,   161,
     360,   361,   362,   218,   161,    97,   161,   154,   552,   553,
      98,    99,   100,   101,   102,   219,   103,   104,   652,   105,
     106,   107,   108,   109,   110,   222,   223,   111,   112,   113,
     114,   440,   243,   161,   161,    95,   293,   251,   252,   440,
     296,   253,   254,   440,   385,   115,   255,   256,   281,   257,
     258,   259,    79,   260,   261,   262,   625,   161,   263,   282,
     264,   265,   266,   116,   267,   268,   269,   270,   161,   285,
     288,   321,   324,   303,   161,   306,   331,   335,   371,   356,
     369,   161,   373,   378,   380,   382,   388,   411,   442,   161,
     117,   443,   444,    97,   446,   448,   450,   451,    98,    99,
     100,   101,   102,   472,   103,   104,   452,   453,   454,   107,
     108,   109,   110,   475,   354,   355,   487,   455,   456,   457,
     160,   490,   160,   458,    66,   161,   476,   161,   161,   161,
     161,   161,   507,   161,   161,   459,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   374,
     160,   116,    97,   460,   161,   461,   462,    98,    99,   100,
     101,   102,   463,   103,   104,   464,   105,   106,   107,   108,
     109,   110,   465,   406,   111,   112,   113,   114,   117,   466,
     467,   545,   468,   469,   413,   470,   471,   477,   513,   517,
     406,   519,   115,   524,   161,   527,   161,   441,   549,    79,
     550,   161,   559,   561,   161,   445,   332,    67,   562,   586,
     116,   563,   592,   619,   320,   564,   287,   286,   566,   585,
     567,   569,   589,   570,   571,   572,   573,   161,   574,   575,
     576,   577,   578,   579,   580,   581,   161,   117,   161,   161,
     161,   161,   587,   161,   161,   591,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   594,
     621,   627,   379,   439,   556,   543,   292,   583,   161,     0,
       0,   161,     0,    97,   244,     0,     0,     0,    98,    99,
     100,   101,   102,     0,   103,   104,     0,   105,   106,   107,
     108,   109,   110,     0,     0,   111,   112,   113,   114,     0,
       0,     0,     0,     0,   161,     0,     0,     0,     0,     0,
       0,     0,   560,   115,    88,     0,     0,   565,     0,     0,
     568,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   116,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   590,     0,     0,     0,     0,     0,     0,
       0,     0,   596,     0,   598,   599,   600,   601,   117,   603,
     604,     0,   606,   607,   608,   609,   610,   611,   612,   613,
     614,   615,   616,   617,   618,    69,    70,    71,    72,    73,
       0,     0,     0,     0,   623,     0,     0,   626,     0,    80,
       0,    84,    85,     0,     0,     0,    90,    91,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    97,     0,     0,     0,
     651,    98,    99,   100,   101,   102,     0,   103,   104,     0,
     105,   106,   107,   108,   109,   110,     0,     0,   111,   141,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,     0,   116,     0,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,     9,     0,
     217,    10,    11,    12,    13,    14,    15,    16,    17,     0,
       0,   117,     0,     0,    18,    19,     0,     0,     0,    20,
       0,   245,    21,   246,     0,     0,   479,     0,   481,   483,
     484,   485,   486,     0,   488,   489,     0,   491,   492,   493,
     494,   495,   496,   497,   498,   499,   500,   501,   502,   503,
       0,     0,    22,     0,     0,   512,     0,     0,    23,     0,
       0,     0,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,    30,     0,
      31,    32,    33,    34,     0,   205,    35,    36,    37,    38,
       0,    39,    40,    41,     1,   558,    -5,    -5,    -5,    -5,
      -5,    -5,    -5,    -5,   289,     0,     0,     0,     0,    -5,
      -5,     0,     0,     0,    -5,     0,     0,    -5,   297,   299,
     300,   301,   302,     0,   304,   305,     0,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,     0,
       0,     0,     0,     0,     0,     0,     0,    -5,     0,     0,
       0,     0,     2,    -5,     0,     0,     0,    -5,    -5,    -5,
      -5,    -5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    -5,    -5,     0,    -5,    -5,    -5,    -5,     0,
       0,    -5,    -5,    -5,    -5,     0,    -5,    -5,    -5,    10,
      11,    12,    13,    14,    15,    16,    17,     0,     0,     0,
       0,     0,    18,    19,     0,     0,     0,    20,     0,     0,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      97,     0,     0,     0,     0,    98,    99,   100,   101,   102,
       0,   103,   104,     0,   105,   106,   107,   108,   109,   110,
      22,     0,   111,   112,   113,   114,    23,     0,     0,     0,
      24,    25,    26,    27,    28,     0,     0,     0,     0,     0,
     115,     0,     0,     0,   132,    29,    30,     0,    31,    32,
      33,    34,     0,     0,    35,    36,    37,    38,   116,    39,
      40,    41,    10,    11,    12,    13,    14,    15,    16,    17,
       0,     0,     0,     0,     0,    18,    19,     0,     0,     0,
      20,     0,     0,    21,     0,   117,   417,   418,   419,   420,
     421,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,     0,     0,   432,   433,   434,   435,     0,     0,     0,
       0,     0,   147,    22,     0,     0,     0,     0,     0,    23,
     506,   436,     0,    24,    25,    26,    27,    28,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,     0,
       0,     0,    32,    33,    34,     0,     0,    35,    36,    37,
      38,   541,    39,    40,    41,    10,    11,    12,    13,    14,
      15,    16,    17,     0,     0,     0,     0,     0,    18,    19,
     437,   438,     0,    20,    97,     0,    21,     0,     0,    98,
      99,   100,   101,   102,     0,   103,   104,     0,   105,   106,
     107,   108,   109,   110,     0,     0,   111,   112,   113,   114,
       0,     0,     0,     0,     0,   241,    22,     0,     0,     0,
       0,     0,    23,     0,   115,     0,    24,    25,    26,    27,
      28,   542,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    29,   116,     0,     0,    32,    33,    34,     0,   205,
      35,    36,    37,    38,     0,    39,    40,    41,    10,    11,
      12,    13,    14,    15,    16,    17,     0,     0,     0,   117,
       0,    18,    19,     0,     0,     0,    20,     0,     0,    21,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    97,
       0,     0,     0,     0,    98,    99,   100,   101,   102,     0,
     103,   104,     0,   105,   106,   107,   108,   109,   110,    22,
       0,   111,   112,   113,   114,    23,     0,     0,     0,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,   115,
       0,     0,     0,   336,    29,     0,     0,     0,    32,    33,
      34,     0,     0,    35,    36,    37,    38,   116,    39,    40,
      41,     0,     0,    97,     0,     0,     0,     0,    98,    99,
     100,   101,   102,     0,   103,   104,     0,   105,   106,   107,
     108,   109,   110,     0,   117,   111,   112,   113,   114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,     0,     0,     0,   337,     0,     0,
       0,    97,     0,     0,     0,     0,    98,    99,   100,   101,
     102,   116,   103,   104,     0,   105,   106,   107,   108,   109,
     110,     0,     0,   111,   112,   113,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,     0,
       0,   115,     0,     0,     0,   338,     0,     0,     0,    97,
       0,     0,     0,     0,    98,    99,   100,   101,   102,   116,
     103,   104,     0,   105,   106,   107,   108,   109,   110,     0,
       0,   111,   112,   113,   114,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   117,     0,     0,   115,
       0,     0,     0,   339,     0,     0,     0,    97,     0,     0,
       0,     0,    98,    99,   100,   101,   102,   116,   103,   104,
       0,   105,   106,   107,   108,   109,   110,     0,     0,   111,
     112,   113,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,     0,     0,   115,     0,     0,
       0,   340,     0,     0,     0,    97,     0,     0,     0,     0,
      98,    99,   100,   101,   102,   116,   103,   104,     0,   105,
     106,   107,   108,   109,   110,     0,     0,   111,   112,   113,
     114,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,     0,     0,   115,     0,     0,     0,   341,
       0,     0,     0,    97,     0,     0,     0,     0,    98,    99,
     100,   101,   102,   116,   103,   104,     0,   105,   106,   107,
     108,   109,   110,     0,     0,   111,   112,   113,   114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,     0,     0,   115,     0,     0,     0,   342,     0,     0,
       0,    97,     0,     0,     0,     0,    98,    99,   100,   101,
     102,   116,   103,   104,     0,   105,   106,   107,   108,   109,
     110,     0,     0,   111,   112,   113,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,     0,
       0,   115,     0,     0,     0,   343,     0,     0,     0,    97,
       0,     0,     0,     0,    98,    99,   100,   101,   102,   116,
     103,   104,     0,   105,   106,   107,   108,   109,   110,     0,
       0,   111,   112,   113,   114,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   117,     0,     0,   115,
       0,     0,     0,   344,     0,     0,     0,    97,     0,     0,
       0,     0,    98,    99,   100,   101,   102,   116,   103,   104,
       0,   105,   106,   107,   108,   109,   110,     0,     0,   111,
     112,   113,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,     0,     0,   115,     0,     0,
       0,   345,     0,     0,     0,    97,     0,     0,     0,     0,
      98,    99,   100,   101,   102,   116,   103,   104,     0,   105,
     106,   107,   108,   109,   110,     0,     0,   111,   112,   113,
     114,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,     0,     0,   115,     0,     0,     0,   346,
       0,     0,     0,    97,     0,     0,     0,     0,    98,    99,
     100,   101,   102,   116,   103,   104,     0,   105,   106,   107,
     108,   109,   110,     0,     0,   111,   112,   113,   114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,     0,     0,   115,     0,     0,     0,   347,     0,     0,
       0,    97,     0,     0,     0,     0,    98,    99,   100,   101,
     102,   116,   103,   104,     0,   105,   106,   107,   108,   109,
     110,     0,     0,   111,   112,   113,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,     0,
       0,   115,     0,     0,     0,   348,     0,     0,     0,    97,
       0,     0,     0,     0,    98,    99,   100,   101,   102,   116,
     103,   104,     0,   105,   106,   107,   108,   109,   110,     0,
       0,   111,   112,   113,   114,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   117,     0,     0,   115,
       0,     0,     0,   349,     0,     0,     0,    97,     0,     0,
       0,     0,    98,    99,   100,   101,   102,   116,   103,   104,
       0,   105,   106,   107,   108,   109,   110,     0,     0,   111,
     112,   113,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,     0,     0,   115,     0,     0,
       0,   350,     0,     0,     0,    97,     0,     0,     0,     0,
      98,    99,   100,   101,   102,   116,   103,   104,     0,   105,
     106,   107,   108,   109,   110,     0,     0,   111,   112,   113,
     114,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,     0,     0,   115,     0,     0,     0,   351,
       0,     0,     0,    97,     0,     0,     0,     0,    98,    99,
     100,   101,   102,   116,   103,   104,     0,   105,   106,   107,
     108,   109,   110,     0,     0,   111,   112,   113,   114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,     0,     0,   115,     0,     0,     0,   352,     0,     0,
       0,    97,     0,     0,     0,     0,    98,    99,   100,   101,
     102,   116,   103,   104,     0,   105,   106,   107,   108,   109,
     110,     0,     0,   111,   112,   113,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,     0,
       0,   115,     0,     0,     0,   353,     0,     0,     0,    97,
       0,     0,     0,     0,    98,    99,   100,   101,   102,   116,
     103,   104,     0,   105,   106,   107,   108,   109,   110,     0,
       0,   111,   112,   113,   114,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   117,     0,     0,   115,
       0,     0,     0,     0,     0,     0,   582,    97,     0,     0,
       0,     0,    98,    99,   100,   101,   102,   116,   103,   104,
       0,   105,   106,   107,   108,   109,   110,     0,     0,   111,
     112,   113,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,    97,     0,   115,     0,     0,
      98,    99,   100,   101,   102,     0,   103,   104,     0,   105,
     106,   107,   108,   109,   110,   116,     0,   111,   112,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    97,     0,     0,   115,     0,    98,    99,   100,
     101,   102,   117,   103,   104,     0,   105,   106,   107,   108,
     109,   110,    97,   116,   111,     0,   113,    98,    99,   100,
     101,   102,     0,   103,   104,     0,   105,   106,   107,   108,
     109,   110,   115,     0,   111,     0,     0,     0,     0,     0,
     117,    10,    11,    12,    13,    14,    15,    16,    17,     0,
     116,     0,   115,     0,    18,    19,     0,     0,     0,    20,
       0,     0,    21,     0,     0,     0,     0,     0,     0,     0,
     116,     0,     0,     0,     0,     0,     0,   117,     0,     0,
      10,    11,    12,    13,    14,    15,    16,    17,     0,     0,
       0,     0,    22,    18,    19,     0,    79,   117,    20,     0,
       0,    21,    24,    25,    26,    27,    28,    10,    11,    12,
      13,    14,    15,    16,    17,     0,     0,    29,     0,     0,
      18,    19,     0,     0,     0,    20,     0,     0,    21,     0,
       0,    22,   203,    10,    11,    12,    13,    14,    15,    16,
      17,    24,    25,    26,    27,    28,    18,    19,     0,     0,
       0,    20,     0,     0,    21,     0,    29,     0,    22,   274,
      10,    11,    12,    13,    14,    15,    16,    17,    24,    25,
      26,    27,    28,    18,    19,     0,     0,     0,    20,     0,
       0,    21,     0,    29,    22,   298,    10,    11,    12,    13,
      14,    15,    16,    17,    24,    25,    26,    27,    28,    18,
      19,     0,     0,     0,    20,     0,     0,    21,     0,    29,
       0,    22,   624,     0,     0,     0,     0,     0,     0,     0,
       0,    24,    25,    26,    27,    28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    29,    22,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    24,    25,    26,
      27,    28,     0,     0,     0,     0,     0,   162,     0,     0,
       0,     0,    29,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,     0,     0,
     178,   179,   180,   181,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   182
};

static const yytype_int16 yycheck[] =
{
       3,     4,   218,    36,    37,   282,    68,    11,   226,   109,
      11,   476,    41,    75,    47,    12,    10,    18,    19,    20,
      38,    10,    12,   330,    12,    38,    29,    10,    10,    10,
      10,    38,    38,    83,    10,    86,    87,    10,    41,    89,
      58,   354,   507,    37,   509,    58,    10,    80,    37,     4,
      83,   358,    58,    10,    37,    86,    87,    90,    91,    88,
      57,   374,    52,   281,    37,    69,    12,    61,    69,    57,
     377,    12,    53,    55,   381,    55,    70,    84,   543,    55,
     387,    70,    12,    77,    78,    88,    80,    70,    77,    78,
      79,    55,    95,    12,    77,    78,    12,    70,    55,   161,
     162,    12,    12,    97,    77,    78,   391,    59,   141,    55,
     395,    10,    53,   116,   117,    11,     3,     4,    12,   148,
      16,    17,    18,    19,    20,    55,    22,    23,    10,    25,
      26,    27,    28,    29,    30,    12,    55,   414,    13,    55,
      12,    11,    52,    12,    55,   148,    16,    17,    18,    19,
      20,    12,    22,    23,    41,    25,    26,    27,    28,    29,
      30,    55,    11,    33,    34,    35,    36,    16,    17,    18,
      19,    20,   449,    69,    12,    12,    10,    52,    55,    12,
      12,    51,    52,    55,   217,    12,    55,    12,    58,    12,
      12,    12,    12,    12,    55,    12,    12,    52,    11,    69,
      96,    88,   515,    16,    17,    18,    19,    20,    95,    22,
      23,    12,   245,   246,    12,    12,    12,    55,    55,   222,
      69,    12,    55,    55,    14,    14,    96,    52,    55,   116,
     117,   238,    55,    55,    55,    55,    55,    13,    55,    55,
     243,    13,    10,   556,   247,    52,    58,   560,   327,    10,
     329,    58,   565,    38,    55,   568,    69,    55,    55,    55,
      62,   148,    54,    52,    55,    52,    56,    70,    71,    72,
      73,    58,    74,    75,    76,    52,    52,   590,   357,    82,
      52,    58,   289,   596,   291,   598,   599,   600,   601,    56,
     603,   604,    92,   606,   607,   608,   609,   610,   611,   612,
     613,   614,   615,   616,   617,   618,    52,    10,    52,    63,
     623,    10,    58,   626,    58,    74,    75,    76,   321,   322,
      74,    75,    76,    54,   327,    11,   329,    13,    64,    65,
      16,    17,    18,    19,    20,    10,    22,    23,   651,    25,
      26,    27,    28,    29,    30,    54,    10,    33,    34,    35,
      36,   404,    54,   356,   357,    56,   243,    54,    54,   412,
     247,    54,    54,   416,   371,    51,    54,    54,    72,    54,
      54,    54,    58,    54,    54,    54,   592,   380,    54,    10,
      54,    54,    54,    69,    54,    54,    54,    54,   391,    10,
      53,    81,    10,    55,   397,    55,    52,    10,    55,    81,
      10,   404,    10,    53,    13,    53,    53,    53,    10,   412,
      96,    53,    53,    11,    10,    54,    54,    54,    16,    17,
      18,    19,    20,    10,    22,    23,    54,    54,    54,    27,
      28,    29,    30,    10,   321,   322,    55,    54,    54,    54,
     327,    55,   329,    54,     4,   448,    52,   450,   451,   452,
     453,   454,    52,   456,   457,    54,   459,   460,   461,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   356,
     357,    69,    11,    54,   477,    54,    54,    16,    17,    18,
      19,    20,    54,    22,    23,    54,    25,    26,    27,    28,
      29,    30,    54,   380,    33,    34,    35,    36,    96,    54,
      54,   508,    54,    54,   391,    54,    54,    54,    13,    54,
     397,    81,    51,    81,   517,    81,   519,   404,    62,    58,
      81,   524,    81,    81,   527,   412,   286,     5,    81,    53,
      69,    81,    54,    53,   276,    81,   230,   228,    81,   546,
      81,    81,   549,    81,    81,    81,    81,   550,    81,    81,
      81,    81,    81,    81,    81,    81,   559,    96,   561,   562,
     563,   564,    63,   566,   567,    81,   569,   570,   571,   572,
     573,   574,   575,   576,   577,   578,   579,   580,   581,    81,
     587,    81,   364,   397,   516,   507,   239,   543,   591,    -1,
      -1,   594,    -1,    11,   151,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    -1,    22,    23,    -1,    25,    26,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,   627,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   519,    51,    52,    -1,    -1,   524,    -1,    -1,
     527,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,   550,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   559,    -1,   561,   562,   563,   564,    96,   566,
     567,    -1,   569,   570,   571,   572,   573,   574,   575,   576,
     577,   578,   579,   580,   581,    18,    19,    20,    21,    22,
      -1,    -1,    -1,    -1,   591,    -1,    -1,   594,    -1,    32,
      -1,    34,    35,    -1,    -1,    -1,    39,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,
     627,    16,    17,    18,    19,    20,    -1,    22,    23,    -1,
      25,    26,    27,    28,    29,    30,    -1,    -1,    33,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,    -1,    69,    -1,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,     0,    -1,
     133,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    96,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,
      -1,   154,    24,   156,    -1,    -1,   448,    -1,   450,   451,
     452,   453,   454,    -1,   456,   457,    -1,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
      -1,    -1,    54,    -1,    -1,   477,    -1,    -1,    60,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    -1,
      82,    83,    84,    85,    -1,   218,    88,    89,    90,    91,
      -1,    93,    94,    95,     1,   517,     3,     4,     5,     6,
       7,     8,     9,    10,   237,    -1,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    21,    -1,    -1,    24,   251,   252,
     253,   254,   255,    -1,   257,   258,    -1,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    59,    60,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    80,    -1,    82,    83,    84,    85,    -1,
      -1,    88,    89,    90,    91,    -1,    93,    94,    95,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,
      -1,    22,    23,    -1,    25,    26,    27,    28,    29,    30,
      54,    -1,    33,    34,    35,    36,    60,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    55,    79,    80,    -1,    82,    83,
      84,    85,    -1,    -1,    88,    89,    90,    91,    69,    93,
      94,    95,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      21,    -1,    -1,    24,    -1,    96,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    60,
     473,    51,    -1,    64,    65,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      -1,    -1,    83,    84,    85,    -1,    -1,    88,    89,    90,
      91,   504,    93,    94,    95,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
     100,   101,    -1,    21,    11,    -1,    24,    -1,    -1,    16,
      17,    18,    19,    20,    -1,    22,    23,    -1,    25,    26,
      27,    28,    29,    30,    -1,    -1,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    53,    54,    -1,    -1,    -1,
      -1,    -1,    60,    -1,    51,    -1,    64,    65,    66,    67,
      68,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    69,    -1,    -1,    83,    84,    85,    -1,   592,
      88,    89,    90,    91,    -1,    93,    94,    95,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    96,
      -1,    16,    17,    -1,    -1,    -1,    21,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,    -1,
      22,    23,    -1,    25,    26,    27,    28,    29,    30,    54,
      -1,    33,    34,    35,    36,    60,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    55,    79,    -1,    -1,    -1,    83,    84,
      85,    -1,    -1,    88,    89,    90,    91,    69,    93,    94,
      95,    -1,    -1,    11,    -1,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    -1,    22,    23,    -1,    25,    26,    27,
      28,    29,    30,    -1,    96,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    69,    22,    23,    -1,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,    69,
      22,    23,    -1,    25,    26,    27,    28,    29,    30,    -1,
      -1,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    51,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    16,    17,    18,    19,    20,    69,    22,    23,
      -1,    25,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    51,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      16,    17,    18,    19,    20,    69,    22,    23,    -1,    25,
      26,    27,    28,    29,    30,    -1,    -1,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    69,    22,    23,    -1,    25,    26,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    69,    22,    23,    -1,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,    69,
      22,    23,    -1,    25,    26,    27,    28,    29,    30,    -1,
      -1,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    51,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    16,    17,    18,    19,    20,    69,    22,    23,
      -1,    25,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    51,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      16,    17,    18,    19,    20,    69,    22,    23,    -1,    25,
      26,    27,    28,    29,    30,    -1,    -1,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    69,    22,    23,    -1,    25,    26,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    69,    22,    23,    -1,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,    69,
      22,    23,    -1,    25,    26,    27,    28,    29,    30,    -1,
      -1,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    51,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    16,    17,    18,    19,    20,    69,    22,    23,
      -1,    25,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    51,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      16,    17,    18,    19,    20,    69,    22,    23,    -1,    25,
      26,    27,    28,    29,    30,    -1,    -1,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    69,    22,    23,    -1,    25,    26,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    69,    22,    23,    -1,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,    69,
      22,    23,    -1,    25,    26,    27,    28,    29,    30,    -1,
      -1,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    11,    -1,    -1,
      -1,    -1,    16,    17,    18,    19,    20,    69,    22,    23,
      -1,    25,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    96,    11,    -1,    51,    -1,    -1,
      16,    17,    18,    19,    20,    -1,    22,    23,    -1,    25,
      26,    27,    28,    29,    30,    69,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    11,    -1,    -1,    51,    -1,    16,    17,    18,
      19,    20,    96,    22,    23,    -1,    25,    26,    27,    28,
      29,    30,    11,    69,    33,    -1,    35,    16,    17,    18,
      19,    20,    -1,    22,    23,    -1,    25,    26,    27,    28,
      29,    30,    51,    -1,    33,    -1,    -1,    -1,    -1,    -1,
      96,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      69,    -1,    51,    -1,    16,    17,    -1,    -1,    -1,    21,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    -1,    54,    16,    17,    -1,    58,    96,    21,    -1,
      -1,    24,    64,    65,    66,    67,    68,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    79,    -1,    -1,
      16,    17,    -1,    -1,    -1,    21,    -1,    -1,    24,    -1,
      -1,    54,    55,     3,     4,     5,     6,     7,     8,     9,
      10,    64,    65,    66,    67,    68,    16,    17,    -1,    -1,
      -1,    21,    -1,    -1,    24,    -1,    79,    -1,    54,    55,
       3,     4,     5,     6,     7,     8,     9,    10,    64,    65,
      66,    67,    68,    16,    17,    -1,    -1,    -1,    21,    -1,
      -1,    24,    -1,    79,    54,    55,     3,     4,     5,     6,
       7,     8,     9,    10,    64,    65,    66,    67,    68,    16,
      17,    -1,    -1,    -1,    21,    -1,    -1,    24,    -1,    79,
      -1,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    10,    -1,    -1,
      -1,    -1,    79,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    59,   111,   112,   120,   121,   109,     4,     0,
       3,     4,     5,     6,     7,     8,     9,    10,    16,    17,
      21,    24,    54,    60,    64,    65,    66,    67,    68,    79,
      80,    82,    83,    84,    85,    88,    89,    90,    91,    93,
      94,    95,   113,   114,   139,   154,   155,   156,   157,   158,
     159,   161,   162,   163,   164,   165,   168,   169,   170,   171,
     172,   173,   176,   177,   178,   179,   113,   121,   155,   156,
     156,   156,   156,   156,    10,   155,    10,    10,   119,    58,
     156,   182,    83,    89,   156,   156,   182,   182,    52,   180,
     156,   156,   161,    10,    14,    56,   152,    11,    16,    17,
      18,    19,    20,    22,    23,    25,    26,    27,    28,    29,
      30,    33,    34,    35,    36,    51,    69,    96,   182,    54,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,   152,    55,    38,   152,    56,   123,    14,    52,   115,
     182,   156,   182,   180,    58,   180,   181,    53,   160,   161,
      92,   174,   175,   182,    13,   182,    38,    58,    10,   153,
     154,   155,    10,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    33,    34,
      35,    36,    51,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   154,   154,    55,   151,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,    54,    10,
     124,   125,    54,    10,    70,    71,    72,    73,    82,   116,
     117,   118,   126,   127,   128,   129,   182,    86,    87,   166,
     167,    53,   161,    54,   175,   156,   156,    12,    57,   152,
     152,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    12,    55,   182,    55,   151,    12,    57,    55,   150,
     154,    72,    10,   122,   122,    10,   119,   116,    53,   156,
     180,    87,   167,   154,   182,   182,   154,   156,    55,   156,
     156,   156,   156,    55,   156,   156,    55,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,    55,
     125,    81,    12,    55,    10,   122,   123,    13,    52,    13,
      52,    52,   115,   180,   180,    10,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,   154,   154,    81,    13,    52,   153,
      74,    75,    76,   130,   131,   132,   148,   153,   130,    10,
     149,    55,   181,    10,   154,   153,   130,    52,    53,   132,
      13,    52,    53,    12,    53,   180,   181,    52,    53,   130,
      37,    61,    70,    77,    78,    80,    97,   133,   134,   135,
     140,   141,   142,   145,   146,   147,   154,   130,    10,    53,
     130,    53,   146,   154,    10,    79,   146,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    33,    34,    35,    36,    51,   100,   101,   134,
     147,   154,    10,    53,    53,   154,    10,   123,    54,    10,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    10,    38,    58,    10,    52,    54,    55,   150,
     123,   150,    55,   150,   150,   150,   150,    55,   150,   150,
      55,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,    38,    58,   156,    52,    62,   143,
     148,    55,   150,    13,   136,   138,    55,    54,    55,    81,
      55,    55,    55,    55,    81,    55,    55,    81,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,   156,    58,   143,    58,   180,    63,   144,   148,    62,
      81,    55,    64,    65,   137,   181,   138,    55,   150,    81,
     154,    81,    81,    81,    81,   154,    81,    81,   154,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    58,   144,    58,   180,    53,    63,    58,   180,
     154,    81,    54,   181,    81,    55,   154,   181,   154,   154,
     154,   154,   181,   154,   154,   181,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,    53,
      58,   180,   181,   154,    55,   151,   154,    81,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,    55,
     181,   154,   181
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   110,   111,   111,   111,   112,   112,   113,   113,   113,
     114,   115,   116,   116,   116,   116,   116,   117,   117,   118,
     118,   119,   119,   120,   120,   121,   122,   123,   123,   124,
     124,   125,   126,   126,   127,   127,   128,   128,   129,   129,
     130,   130,   131,   131,   132,   133,   133,   134,   134,   134,
     134,   134,   135,   135,   136,   136,   137,   137,   138,   138,
     139,   139,   140,   140,   140,   140,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   142,
     142,   142,   142,   143,   143,   143,   143,   144,   144,   144,
     144,   145,   145,   146,   146,   147,   147,   147,   147,   148,
     148,   148,   149,   149,   150,   150,   151,   151,   152,   152,
     153,   153,   154,   155,   155,   156,   156,   156,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   158,
     158,   158,   158,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   160,   160,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     162,   163,   164,   165,   165,   165,   165,   166,   166,   167,
     168,   169,   170,   171,   171,   172,   173,   174,   174,   175,
     176,   176,   177,   178,   179,   180,   180,   181,   181,   182
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     1,     1,     1,     1,
       3,     3,     3,     1,     1,     1,     1,     1,     2,     0,
       1,     1,     3,     1,     2,     2,     2,     0,     3,     1,
       3,     1,     6,     8,     5,     7,     5,     6,     5,     7,
       0,     1,     1,     2,     3,     1,     2,     1,     1,     1,
       1,     1,     7,     6,     5,     4,     1,     1,     0,     1,
       9,     8,    10,     9,     9,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     7,     7,     7,     8,     8,     4,
       3,     6,     5,     2,     2,     3,     3,     2,     2,     3,
       3,     8,     7,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     4,     1,     3,     0,     3,
       1,     3,     2,     1,     3,     3,     1,     1,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     5,     5,     5,
       3,     3,     2,     2,     6,     5,     1,     1,     1,     2,
       4,     4,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     5,     5,     3,     5,     4,     6,     1,     2,     3,
       3,     2,     2,     3,     2,     3,     3,     1,     2,     6,
       5,     3,     2,     4,     3,     3,     2,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 153 "beacon.y" /* yacc.c:1663  */
    {
		yyclearin;
	}
#line 2295 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 6:
#line 161 "beacon.y" /* yacc.c:1663  */
    {
		bc_CompileEntryAST((yyvsp[0].ast_value));
	}
#line 2303 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 7:
#line 167 "beacon.y" /* yacc.c:1663  */
    {
		bc_CompileEntryAST((yyvsp[0].ast_value));
	}
#line 2311 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 8:
#line 171 "beacon.y" /* yacc.c:1663  */
    {
		bc_CompileEntryAST((yyvsp[0].ast_value));
	}
#line 2319 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 9:
#line 175 "beacon.y" /* yacc.c:1663  */
    {
		bc_CompileEntryAST((yyvsp[0].ast_value));
	}
#line 2327 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 10:
#line 181 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTNamespaceDecl((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2335 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 11:
#line 188 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 2343 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 12:
#line 195 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTNamespaceNamespaceDecl((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2351 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 17:
#line 206 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 2359 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 18:
#line 210 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTNamespaceMemberDeclList((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2367 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 19:
#line 217 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBlank();
	}
#line 2375 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 21:
#line 225 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTNamespacePath((yyvsp[0].stringv_value));
	}
#line 2383 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 22:
#line 229 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTNamespacePathList((yyvsp[-2].ast_value), (yyvsp[0].stringv_value));
	}
#line 2391 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 24:
#line 237 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTImportDeclList((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2399 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 25:
#line 244 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTImportDecl(bc_NewASTImportPath((yyvsp[0].ast_value)));
	}
#line 2407 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 26:
#line 251 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTParameterizedTypename((yyvsp[-1].stringv_value), (yyvsp[0].ast_value));
	}
#line 2415 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 27:
#line 258 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBlank();
	}
#line 2423 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 28:
#line 262 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 2431 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 29:
#line 269 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 2439 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 30:
#line 273 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTTypeParameterList((yyvsp[0].ast_value), (yyvsp[-2].ast_value));
	}
#line 2447 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 31:
#line 280 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTTypeParameter((yyvsp[0].stringv_value), bc_NewASTBlank());
	}
#line 2455 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 32:
#line 286 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTAbstractClassDecl((yyvsp[-3].ast_value), bc_NewASTBlank(), (yyvsp[-1].ast_value));
	}
#line 2463 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 33:
#line 290 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTAbstractClassDecl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2471 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 34:
#line 296 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTClassDecl((yyvsp[-3].ast_value), bc_NewASTBlank(), (yyvsp[-1].ast_value));
	}
#line 2479 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 35:
#line 300 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTClassDecl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2487 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 36:
#line 307 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTEnumDecl((yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2495 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 37:
#line 311 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTEnumDecl((yyvsp[-4].stringv_value), (yyvsp[-2].ast_value));
	}
#line 2503 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 38:
#line 318 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTInterfaceDecl((yyvsp[-3].ast_value), bc_NewASTBlank(), (yyvsp[-1].ast_value));
	}
#line 2511 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 39:
#line 322 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTInterfaceDecl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2519 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 40:
#line 329 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBlank();
	}
#line 2527 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 43:
#line 338 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTAccessMemberTree((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2535 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 44:
#line 345 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTAccessMemberList((yyvsp[-2].access_level_value), (yyvsp[0].ast_value));
	}
#line 2543 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 45:
#line 352 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTMemberDecl((yyvsp[0].ast_value));
	}
#line 2551 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 46:
#line 356 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTMemberDeclList((yyvsp[-1].ast_value), bc_NewASTMemberDecl((yyvsp[0].ast_value)));
	}
#line 2559 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 52:
#line 371 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTConstructorDecl((yyvsp[-3].ast_value), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2567 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 53:
#line 375 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTConstructorDecl(bc_NewASTBlank(), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2575 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 54:
#line 382 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTConstructorChain((yyvsp[-3].chain_type_value), (yyvsp[-1].ast_value));
	}
#line 2583 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 55:
#line 386 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTConstructorChain((yyvsp[-2].chain_type_value), bc_NewASTBlank());
	}
#line 2591 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 56:
#line 393 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.chain_type_value) = CHAIN_TYPE_SUPER_T;
	}
#line 2599 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 57:
#line 397 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.chain_type_value) = CHAIN_TYPE_THIS_T;
	}
#line 2607 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 58:
#line 404 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBlank();
	}
#line 2615 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 60:
#line 412 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTFunctionDecl((yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2623 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 61:
#line 416 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTFunctionDeclEmptyParams((yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2631 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 62:
#line 423 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTMethodDecl((yyvsp[-8].ast_value), (yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2639 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 63:
#line 427 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTMethodDeclEmptyParams((yyvsp[-7].ast_value), (yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2647 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 64:
#line 431 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTMethodDecl(bc_NewASTModifier(MODIFIER_NONE_T), (yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2655 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 65:
#line 435 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTMethodDeclEmptyParams(bc_NewASTModifier(MODIFIER_NONE_T), (yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2663 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 66:
#line 442 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_ADD_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2671 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 67:
#line 446 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_SUB_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2679 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 68:
#line 450 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_MUL_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2687 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 69:
#line 454 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_DIV_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2695 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 70:
#line 458 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_MOD_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2703 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 71:
#line 462 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_GT_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2711 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 72:
#line 466 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_GE_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2719 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 73:
#line 470 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_LT_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2727 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 74:
#line 474 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_LE_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2735 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 75:
#line 479 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_EQ_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2743 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 76:
#line 483 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_NOT_EQ_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2751 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 77:
#line 488 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_BIT_OR_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2759 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 78:
#line 492 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_BIT_AND_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2767 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 79:
#line 497 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_LOGIC_OR_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2775 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 80:
#line 501 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_LOGIC_AND_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2783 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 81:
#line 506 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_LSHIFT_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2791 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 82:
#line 510 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_RSHIFT_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2799 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 83:
#line 515 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_EXCOR_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2807 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 84:
#line 520 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_NOT_T, bc_NewASTBlank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2815 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 85:
#line 525 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_CHILDA_T, bc_NewASTBlank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2823 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 86:
#line 529 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_NEGATIVE_T, bc_NewASTBlank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2831 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 87:
#line 534 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_SUB_SCRIPT_GET_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2839 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 88:
#line 539 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOperatorOverload(OPERATOR_SUB_SCRIPT_SET_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2847 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 89:
#line 546 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTFieldDecl((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[-1].stringv_value), bc_NewASTBlank());
	}
#line 2855 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 90:
#line 550 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTFieldDecl(bc_NewASTModifier(MODIFIER_NONE_T), (yyvsp[-2].ast_value), (yyvsp[-1].stringv_value), bc_NewASTBlank());
	}
#line 2863 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 91:
#line 554 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTFieldDecl((yyvsp[-5].ast_value), (yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2871 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 92:
#line 558 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTFieldDecl(bc_NewASTModifier(MODIFIER_NONE_T), (yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2879 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 93:
#line 565 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTPropSet(bc_NewASTBlank(), bc_NewASTBlank());
	}
#line 2887 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 94:
#line 569 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTPropSet(bc_NewASTBlank(), (yyvsp[0].ast_value));
	}
#line 2895 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 95:
#line 573 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTPropSet(bc_NewASTAccess((yyvsp[-2].access_level_value)), bc_NewASTBlank());
	}
#line 2903 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 96:
#line 577 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTPropSet(bc_NewASTAccess((yyvsp[-2].access_level_value)), bc_NewASTBlank());
	}
#line 2911 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 97:
#line 584 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTPropGet(bc_NewASTBlank(), bc_NewASTBlank());
	}
#line 2919 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 98:
#line 588 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTPropGet(bc_NewASTBlank(), (yyvsp[0].ast_value));
	}
#line 2927 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 99:
#line 592 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTPropGet(bc_NewASTAccess((yyvsp[-2].access_level_value)), bc_NewASTBlank());
	}
#line 2935 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 100:
#line 596 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTPropGet(bc_NewASTAccess((yyvsp[-2].access_level_value)), bc_NewASTBlank());
	}
#line 2943 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 101:
#line 603 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTPropDecl((yyvsp[-6].ast_value), (yyvsp[-5].ast_value), (yyvsp[-4].stringv_value), (yyvsp[-2].ast_value), (yyvsp[-1].ast_value));
	}
#line 2951 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 102:
#line 607 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTPropDecl(bc_NewASTModifier(MODIFIER_NONE_T), (yyvsp[-5].ast_value), (yyvsp[-4].stringv_value), (yyvsp[-2].ast_value), (yyvsp[-1].ast_value));
	}
#line 2959 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 103:
#line 614 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 2967 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 104:
#line 618 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTModifierList((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2975 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 105:
#line 625 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTModifier(MODIFIER_STATIC_T);
	}
#line 2983 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 106:
#line 629 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTModifier(MODIFIER_NATIVE_T);
	}
#line 2991 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 107:
#line 633 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTModifier(MODIFIER_ABSTRACT_T);
	}
#line 2999 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 108:
#line 637 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTModifier(MODIFIER_FINAL_T);
	}
#line 3007 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 109:
#line 644 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = ACCESS_PUBLIC_T;
	}
#line 3015 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 110:
#line 648 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = ACCESS_PRIVATE_T;
	}
#line 3023 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 111:
#line 652 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = ACCESS_PROTECTED_T;
	}
#line 3031 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 112:
#line 659 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTIdentifier((yyvsp[0].stringv_value));
	}
#line 3039 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 113:
#line 663 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTIdentifierList((yyvsp[0].stringv_value), (yyvsp[-2].ast_value));
	}
#line 3047 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 114:
#line 670 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTParameter((yyvsp[-1].ast_value), (yyvsp[0].stringv_value));
	}
#line 3055 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 115:
#line 674 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTParameterList((yyvsp[-1].ast_value), (yyvsp[0].stringv_value), (yyvsp[-3].ast_value));
	}
#line 3063 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 116:
#line 681 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTArgument((yyvsp[0].ast_value));
	}
#line 3071 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 117:
#line 685 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTArgumentList(bc_NewASTArgument((yyvsp[0].ast_value)), (yyvsp[-2].ast_value));
	}
#line 3079 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 118:
#line 692 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBlank();
	}
#line 3087 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 119:
#line 696 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 3095 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 120:
#line 703 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 3103 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 121:
#line 707 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTTypenameList((yyvsp[0].ast_value), (yyvsp[-2].ast_value));
	}
#line 3111 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 122:
#line 714 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTTypename((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3119 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 123:
#line 721 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTFQCNPart((yyvsp[0].stringv_value));
	}
#line 3127 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 124:
#line 725 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTFQCNPartList(bc_NewASTFQCNPart((yyvsp[0].stringv_value)), (yyvsp[-2].ast_value));
	}
#line 3135 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 125:
#line 734 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 3143 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 128:
#line 742 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTUnary(AST_POS_T, (yyvsp[0].ast_value));
	}
#line 3151 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 129:
#line 746 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTUnary(AST_NEG_T, (yyvsp[0].ast_value));
	}
#line 3159 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 130:
#line 750 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_ADD_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3167 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 131:
#line 754 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_SUB_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3175 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 132:
#line 758 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_MUL_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3183 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 133:
#line 762 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_DIV_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3191 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 134:
#line 766 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_MOD_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3199 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 135:
#line 770 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_BIT_OR_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3207 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 136:
#line 774 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_EQUAL_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3215 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 137:
#line 778 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_NOT_TEQUAL_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3223 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 138:
#line 782 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_BIT_AND_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3231 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 139:
#line 786 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_EXC_OR_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3239 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 140:
#line 790 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_LOGIC_OR_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3247 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 141:
#line 794 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_LOGIC_AND_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3255 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 142:
#line 798 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_AS_TSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3263 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 143:
#line 802 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_ADD_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3271 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 144:
#line 806 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_SUB_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3279 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 145:
#line 810 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_MUL_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3287 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 146:
#line 814 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_DIV_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3295 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 147:
#line 818 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_MOD_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3303 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 148:
#line 822 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_AND_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3311 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 149:
#line 826 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_OR_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3319 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 150:
#line 830 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_EXC_OR_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3327 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 151:
#line 834 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_LSHIFT_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3335 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 152:
#line 838 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_RSHIFT_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3343 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 153:
#line 842 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_GT_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3351 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 154:
#line 846 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_GE_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3359 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 155:
#line 850 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_LT_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3367 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 156:
#line 854 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_LE_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3375 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 157:
#line 858 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_LSHIFT_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3383 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 158:
#line 862 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBinary(AST_RSHIFT_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3391 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 159:
#line 867 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_ADD_T, (yyvsp[-1].ast_value));
	}
#line 3399 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 160:
#line 871 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_SUB_T, (yyvsp[-1].ast_value));
	}
#line 3407 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 161:
#line 875 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_MUL_T, (yyvsp[-1].ast_value));
	}
#line 3415 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 162:
#line 879 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_DIV_T, (yyvsp[-1].ast_value));
	}
#line 3423 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 163:
#line 883 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_MOD_T, (yyvsp[-1].ast_value));
	}
#line 3431 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 164:
#line 887 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_GT_T, (yyvsp[-1].ast_value));
	}
#line 3439 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 165:
#line 891 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_GE_T, (yyvsp[-1].ast_value));
	}
#line 3447 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 166:
#line 895 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_LT_T, (yyvsp[-1].ast_value));
	}
#line 3455 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 167:
#line 899 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_LE_T, (yyvsp[-1].ast_value));
	}
#line 3463 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 168:
#line 903 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_EQ_T, (yyvsp[-1].ast_value));
	}
#line 3471 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 169:
#line 907 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_NOT_EQ_T, (yyvsp[-1].ast_value));
	}
#line 3479 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 170:
#line 911 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_BIT_OR_T, (yyvsp[-1].ast_value));
	}
#line 3487 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 171:
#line 915 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_BIT_AND_T, (yyvsp[-1].ast_value));
	}
#line 3495 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 172:
#line 919 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_LOGIC_OR_T, (yyvsp[-1].ast_value));
	}
#line 3503 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 173:
#line 923 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_LOGIC_AND_T, (yyvsp[-1].ast_value));
	}
#line 3511 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 174:
#line 927 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_LSHIFT_T, (yyvsp[-1].ast_value));
	}
#line 3519 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 175:
#line 931 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_RSHIFT_T, (yyvsp[-1].ast_value));
	}
#line 3527 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 176:
#line 935 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_EXCOR_T, (yyvsp[-1].ast_value));
	}
#line 3535 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 177:
#line 939 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitUOperator((yyvsp[-4].ast_value), OPERATOR_NOT_T);
	}
#line 3543 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 178:
#line 943 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitUOperator((yyvsp[-4].ast_value), OPERATOR_CHILDA_T);
	}
#line 3551 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 179:
#line 947 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTExplicitUOperator((yyvsp[-4].ast_value), OPERATOR_NEGATIVE_T);
	}
#line 3559 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 180:
#line 951 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTInstanceTof((yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3567 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 181:
#line 955 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTAs((yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3575 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 182:
#line 959 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTUnary(AST_CHILDA_T, (yyvsp[0].ast_value));
	}
#line 3583 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 183:
#line 963 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTUnary(AST_NOT_T, (yyvsp[0].ast_value));
	}
#line 3591 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 184:
#line 967 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTNewInstance((yyvsp[-4].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3599 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 185:
#line 971 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTNewInstance((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), bc_NewASTBlank());
	}
#line 3607 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 186:
#line 975 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTThis();
	}
#line 3615 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 187:
#line 979 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTSuper();
	}
#line 3623 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 189:
#line 986 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTVariable((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3631 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 190:
#line 990 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTFieldAccess((yyvsp[-3].ast_value), (yyvsp[-1].stringv_value), (yyvsp[0].ast_value));
	}
#line 3639 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 191:
#line 994 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOpCall((yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3647 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 192:
#line 998 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTOpCall((yyvsp[-2].ast_value), bc_NewASTBlank());
	}
#line 3655 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 200:
#line 1011 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTTrue();
	}
#line 3663 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 201:
#line 1015 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTFalse();
	}
#line 3671 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 202:
#line 1019 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTNull();
	}
#line 3679 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 203:
#line 1028 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTStmt((yyvsp[0].ast_value));
	}
#line 3687 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 204:
#line 1032 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTStmtList((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3695 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 205:
#line 1038 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTProc((yyvsp[-1].ast_value));
	}
#line 3703 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 220:
#line 1058 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTVariableDecl((yyvsp[-2].ast_value), (yyvsp[-1].stringv_value));
	}
#line 3711 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 221:
#line 1064 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTVariableInit((yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 3719 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 222:
#line 1070 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTInferencedTypeInit((yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 3727 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 223:
#line 1076 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTIf((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3735 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 224:
#line 1080 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTIfElse((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3743 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 225:
#line 1084 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTIfElifList((yyvsp[-2].ast_value), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3751 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 226:
#line 1088 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTIfElifListElse((yyvsp[-4].ast_value), (yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3759 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 228:
#line 1095 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTElifList((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3767 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 229:
#line 1101 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTElif((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3775 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 230:
#line 1107 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTWhile((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3783 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 231:
#line 1113 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBreak();
	}
#line 3791 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 232:
#line 1119 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTContinue();
	}
#line 3799 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 233:
#line 1125 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTReturn((yyvsp[-1].ast_value));
	}
#line 3807 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 234:
#line 1129 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTReturnEmpty();
	}
#line 3815 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 235:
#line 1135 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTThrow((yyvsp[-1].ast_value));
	}
#line 3823 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 236:
#line 1141 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTTry((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3831 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 237:
#line 1147 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 3839 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 238:
#line 1151 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTCatchList((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 3847 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 239:
#line 1157 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTCatch((yyvsp[-3].ast_value), (yyvsp[-2].stringv_value), (yyvsp[0].ast_value));
	}
#line 3855 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 240:
#line 1163 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTAssert((yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3863 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 241:
#line 1167 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTAssert((yyvsp[-1].ast_value), bc_NewASTBlank());
	}
#line 3871 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 242:
#line 1173 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTDefer((yyvsp[0].ast_value));
	}
#line 3879 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 243:
#line 1179 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTYieldReturn((yyvsp[-1].ast_value));
	}
#line 3887 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 244:
#line 1185 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTYieldBreak();
	}
#line 3895 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 245:
#line 1191 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTScope((yyvsp[-1].ast_value));
	}
#line 3903 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 246:
#line 1195 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTScopeEmpty();
	}
#line 3911 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 247:
#line 1201 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = bc_NewASTBlank();
	}
#line 3919 "beacon.tab.c" /* yacc.c:1663  */
    break;


#line 3923 "beacon.tab.c" /* yacc.c:1663  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 1209 "beacon.y" /* yacc.c:1907  */




