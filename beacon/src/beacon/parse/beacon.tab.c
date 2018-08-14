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
    FINAL = 289,
    ASSIGN = 290,
    ADD_ASSIGN = 291,
    SUB_ASSIGN = 292,
    MUL_ASSIGN = 293,
    DIV_ASSIGN = 294,
    MOD_ASSIGN = 295,
    AND_ASSIGN = 296,
    OR_ASSIGN = 297,
    LSHIFT_ASSIGN = 298,
    RSHIFT_ASSIGN = 299,
    EXC_OR_ASSIGN = 300,
    INC = 301,
    DEC = 302,
    EXC_OR = 303,
    LCB = 304,
    RCB = 305,
    LRB = 306,
    RRB = 307,
    LSB = 308,
    RSB = 309,
    SEMI = 310,
    IMPORT = 311,
    VAR = 312,
    PROPERTY = 313,
    DEFSET = 314,
    DEFGET = 315,
    THIS_TOK = 316,
    SUPER_TOK = 317,
    TRUE_TOK = 318,
    FALSE_TOK = 319,
    NULL_TOK = 320,
    AS = 321,
    ABSTRACT = 322,
    OVERRIDE = 323,
    INTERFACE = 324,
    CLASS = 325,
    ENUM = 326,
    PUBLIC = 327,
    PRIVATE = 328,
    PROTECTED = 329,
    STATIC = 330,
    NATIVE = 331,
    NEW = 332,
    DEF = 333,
    ARROW = 334,
    NAMESPACE = 335,
    RETURN = 336,
    YIELD = 337,
    IF = 338,
    ELIF = 339,
    ELSE = 340,
    WHILE = 341,
    BREAK = 342,
    CONTINUE = 343,
    TRY = 344,
    CATCH = 345,
    THROW = 346,
    ASSERT_T = 347,
    DEFER = 348,
    INSTANCEOF = 349,
    OPERATOR = 350,
    BOUNDS_EXTENDS = 351,
    BOUNDS_SUPER = 352,
    SUBSCRIPT_SET = 353,
    SUBSCRIPT_GET = 354,
    PRE_INC = 355,
    PRE_DEC = 356,
    QUOTE = 357,
    FUNCCALL = 358,
    POST_INC = 359,
    POST_DEC = 360,
    ARRAY_SUBSCRIPT = 361,
    NEGATIVE = 362,
    POSITIVE = 363,
    REF = 364,
    FORM_TYPE = 365
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "beacon.y" /* yacc.c:355  */

	char char_value;
	string_view stringv_value;
	ast* ast_value;
	assign_operator_type assign_otype_value;
	constructor_chain_type chain_type_value;
	access_level access_level_value;

#line 243 "beacon.tab.c" /* yacc.c:355  */
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

#line 274 "beacon.tab.c" /* yacc.c:358  */

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
#define YYLAST   2890

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  112
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  249
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  661

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   365

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     111,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
     105,   106,   107,   108,   109,   110
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   147,   147,   148,   149,   155,   157,   163,   167,   171,
     177,   184,   191,   195,   196,   197,   198,   202,   206,   214,
     217,   221,   225,   232,   233,   240,   247,   255,   258,   265,
     269,   276,   282,   286,   292,   296,   303,   307,   314,   318,
     326,   329,   333,   334,   341,   348,   352,   359,   360,   361,
     362,   363,   367,   371,   378,   382,   389,   393,   401,   404,
     408,   412,   419,   423,   427,   431,   438,   442,   446,   450,
     454,   458,   462,   466,   470,   475,   479,   484,   488,   493,
     497,   502,   506,   511,   516,   521,   525,   530,   535,   542,
     546,   550,   554,   561,   565,   569,   573,   580,   584,   588,
     592,   599,   603,   610,   614,   621,   625,   629,   633,   637,
     644,   648,   652,   659,   663,   670,   674,   681,   685,   689,
     697,   700,   707,   711,   718,   725,   729,   738,   742,   743,
     746,   750,   754,   758,   762,   766,   770,   774,   778,   782,
     786,   790,   794,   798,   802,   806,   810,   814,   818,   822,
     826,   830,   834,   838,   842,   846,   850,   854,   858,   862,
     866,   870,   874,   878,   882,   886,   890,   894,   898,   902,
     906,   910,   913,   917,   921,   925,   929,   933,   937,   941,
     945,   949,   953,   957,   961,   965,   969,   973,   977,   981,
     985,   989,   993,   997,  1001,  1005,  1011,  1012,  1013,  1014,
    1015,  1019,  1023,  1032,  1036,  1042,  1046,  1047,  1048,  1049,
    1050,  1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,
    1062,  1068,  1074,  1080,  1084,  1088,  1092,  1098,  1099,  1105,
    1111,  1117,  1123,  1129,  1133,  1139,  1145,  1151,  1155,  1161,
    1167,  1171,  1177,  1183,  1189,  1195,  1199,  1205,  1209,  1212
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR_LITERAL", "STRING_LITERAL", "INT",
  "DOUBLE", "IDENT", "DOT", "COMMA", "COLON", "COLO_COLO", "LINE", "ADD",
  "SUB", "MUL", "DIV", "MOD", "NOT", "LSHIFT", "RSHIFT", "CHILDA", "EQUAL",
  "NOTEQUAL", "GT", "GE", "LT", "LE", "LGEN", "RGEN", "BIT_AND",
  "LOGIC_AND", "BIT_OR", "LOGIC_OR", "FINAL", "ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "AND_ASSIGN",
  "OR_ASSIGN", "LSHIFT_ASSIGN", "RSHIFT_ASSIGN", "EXC_OR_ASSIGN", "INC",
  "DEC", "EXC_OR", "LCB", "RCB", "LRB", "RRB", "LSB", "RSB", "SEMI",
  "IMPORT", "VAR", "PROPERTY", "DEFSET", "DEFGET", "THIS_TOK", "SUPER_TOK",
  "TRUE_TOK", "FALSE_TOK", "NULL_TOK", "AS", "ABSTRACT", "OVERRIDE",
  "INTERFACE", "CLASS", "ENUM", "PUBLIC", "PRIVATE", "PROTECTED", "STATIC",
  "NATIVE", "NEW", "DEF", "ARROW", "NAMESPACE", "RETURN", "YIELD", "IF",
  "ELIF", "ELSE", "WHILE", "BREAK", "CONTINUE", "TRY", "CATCH", "THROW",
  "ASSERT_T", "DEFER", "INSTANCEOF", "OPERATOR", "BOUNDS_EXTENDS",
  "BOUNDS_SUPER", "SUBSCRIPT_SET", "SUBSCRIPT_GET", "PRE_INC", "PRE_DEC",
  "QUOTE", "FUNCCALL", "POST_INC", "POST_DEC", "ARRAY_SUBSCRIPT",
  "NEGATIVE", "POSITIVE", "REF", "FORM_TYPE", "'\\n'", "$accept",
  "compilation_unit", "init_decl", "body_decl", "namespace_decl",
  "namespace_body", "namespace_member_decl", "namespace_member_decl_list",
  "namespace_member_decl_optional", "namespace_path", "import_list",
  "import", "parameterized_typename", "type_parameter_group",
  "type_parameter_list", "type_parameter", "abstract_class_decl",
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
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,    10
};
# endif

#define YYPACT_NINF -402

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-402)))

#define YYTABLE_NINF -125

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     963,   -81,    30,   834,  1054,    -5,  -402,  -402,  -402,  -402,
    -402,  -402,  -402,  -402,  -402,  2813,  2813,  2813,  2813,  2813,
      85,  -402,  -402,  -402,  -402,  -402,   111,   144,   169,  2760,
     -48,  2813,  2813,    71,    71,   129,  2813,  2813,  1327,  -402,
    -402,  -402,   174,    92,  1461,   161,   586,  -402,  -402,  -402,
    -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,
    -402,  -402,  -402,  -402,  -402,    92,   -21,   -21,   -21,   -21,
    1509,   224,    92,   201,  -402,    13,  -402,  1461,  -402,  2813,
      71,  1557,   587,  -402,  -402,  1145,   185,  1461,  1413,  -402,
     -14,   305,   111,   310,   718,  2813,  2813,  2813,  2813,  2813,
    2813,  2813,  2813,  2813,  2813,  2813,  2813,  2813,  2813,  2813,
    2813,  2813,  2813,  2813,   111,   111,  -402,     4,  2813,  2813,
    2813,  2813,  2813,  2813,  2813,  2813,  2813,  2813,  2813,  -402,
    -402,  2813,   213,   327,   228,   338,   292,  -402,  -402,  1461,
    -402,    45,  -402,  -402,  -402,  -402,  1236,  -402,   298,   185,
    -402,  -402,  2813,  -402,  2813,  -402,  -402,    10,  -402,    92,
     312,   315,   317,   325,   326,   328,   329,   330,   334,   335,
     336,   337,   339,   340,   341,   342,   344,   345,   346,   347,
     348,   303,   303,    21,    21,    21,   175,   175,  2734,  2734,
     257,   257,   257,   257,  1255,  2709,  1073,  2661,  1164,  1605,
    -402,  -402,  -402,   349,     7,  2613,  2613,  2613,  2613,  2613,
    2613,  2613,  2613,  2613,  2613,  2613,  2613,  1461,    72,  -402,
      34,  -402,    42,  -402,   308,   363,   363,   382,   169,  -402,
     292,   301,  -402,  -402,  -402,  -402,  -402,  2813,   129,   230,
    -402,  -402,  -402,   111,  -402,  1461,  1461,   111,  -402,  -402,
    -402,  2813,  2788,  2813,  2813,  2813,   350,  2813,  2813,   351,
    2813,  2813,  2813,  2813,  2813,  2813,  2813,  2813,  2813,  2813,
    2813,  -402,   111,  2813,  -402,  -402,  -402,    86,   327,  -402,
     332,   101,   397,   363,   201,   188,   219,   356,    13,  -402,
    -402,  1557,  -402,   129,  -402,   399,  -402,  -402,  -402,  1653,
    -402,  1701,  1749,  1797,  1845,  -402,  1893,  1941,  -402,  1989,
    2037,  2085,  2133,  2181,  2229,  2277,  2325,  2373,  2421,  2469,
     119,  2613,  -402,  -402,   111,   111,   355,  -402,   235,  -402,
     111,   281,   111,   281,   400,  -402,  -402,  -402,   357,  -402,
    -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,
    -402,  -402,  -402,  -402,  -402,  -402,  -402,   358,   -11,   413,
     111,   111,   281,   158,  -402,  -402,  -402,   385,   281,  -402,
     426,   194,   388,  -402,     3,   129,   111,  -402,  -402,   -11,
     218,   390,   281,  -402,  -402,    64,   281,  -402,   134,  -402,
    -402,   129,  -402,   281,  -402,   393,  -402,    29,  -402,  -402,
    -402,  -402,    93,   975,    64,  -402,  -402,  -402,  -402,  -402,
    -402,    29,  -402,   437,   395,  -402,  -402,  -402,   396,  -402,
      29,   441,   201,   401,   118,   403,   409,   412,   429,   430,
     432,   433,   434,   435,   436,   438,   439,   440,   443,   444,
     445,   446,   447,   448,   449,   450,   452,  -402,  -402,   481,
      -9,  -402,  -402,   485,   402,   453,    47,   201,   111,    63,
     111,   111,   111,   398,   111,   111,   454,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
      -7,  2813,  -402,   456,   274,    94,   497,   145,   458,   147,
     431,   148,   149,   166,   173,   451,   186,   187,   455,   195,
     197,   199,   204,   205,   208,   226,   243,   272,   273,   278,
     283,   300,  2813,  -402,  2517,   274,   193,   266,   457,   459,
     319,   172,  -402,   -11,   497,    95,   460,   111,   461,   462,
     463,   464,   111,   465,   466,   111,   468,   469,   471,   472,
     473,   474,   475,   477,   478,   479,   480,   482,   483,  2565,
    -402,   266,  -402,  -402,   287,   467,   476,   288,   111,   484,
    -402,  -402,   509,  -402,   -11,   486,   322,   111,   -11,   111,
     111,   111,   111,   -11,   111,   111,   -11,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
    -402,   470,  -402,  -402,  -402,   295,  -402,  -402,   -11,   111,
     159,  -402,   111,   491,   -11,  -402,   -11,   -11,   -11,   -11,
    -402,   -11,   -11,  -402,   -11,   -11,   -11,   -11,   -11,   -11,
     -11,   -11,   -11,   -11,   -11,   -11,   -11,  -402,  -402,  -402,
    -402,   -11,  -402,   323,   -11,   111,  -402,  -402,  -402,  -402,
    -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,
    -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,   -11,
    -402
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,    23,     4,    25,     1,
     198,   199,   196,   197,   125,     0,     0,     0,     0,     0,
       0,   169,   170,   200,   201,   202,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       8,     9,     0,   120,     0,   129,   171,   128,     7,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,     2,    24,   120,   130,   131,   164,   163,
       0,     0,   120,    27,    21,     0,   249,     0,   234,     0,
       0,     0,     0,   231,   232,     0,     0,     0,     0,   242,
       0,     0,     0,   172,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   205,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   172,
     127,     0,     0,     0,     0,     0,    19,    10,   233,     0,
     244,   223,   247,   248,   230,   246,     0,   203,     0,   236,
     237,   235,     0,   241,     0,   220,   126,     0,   122,   120,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   159,   160,   138,   139,
     155,   156,   157,   158,   140,   143,   137,   142,   141,     0,
     162,   161,   166,     0,     0,   117,   144,   145,   146,   147,
     148,   149,   150,   151,   153,   154,   152,     0,     0,    31,
       0,    29,     0,    22,     0,     0,     0,     0,     0,    17,
      20,     0,    13,    14,    16,    15,   243,     0,     0,   225,
     227,   245,   204,     0,   238,     0,     0,     0,   121,   124,
     173,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   174,     0,     0,   165,   222,   168,     0,     0,    28,
       0,     0,     0,     0,    27,     0,     0,     0,     0,    18,
      11,     0,   224,     0,   228,     0,   240,   221,   123,     0,
     195,     0,     0,     0,     0,   193,     0,     0,   194,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   119,   167,    30,     0,     0,     0,   115,     0,    26,
       0,    40,     0,    40,     0,    12,   229,   226,     0,   175,
     176,   177,   178,   179,   190,   191,   184,   185,   180,   181,
     182,   183,   187,   189,   186,   188,   192,     0,     0,     0,
       0,     0,    40,     0,   110,   111,   112,     0,    41,    42,
       0,     0,     0,   113,     0,     0,     0,    61,   116,     0,
       0,     0,    40,    38,    43,     0,    40,    34,     0,    36,
     239,     0,    60,    40,    32,     0,   109,     0,   107,   108,
     105,   106,     0,     0,    44,    45,    47,    48,    49,    50,
      51,     0,   103,     0,     0,   114,    37,   118,     0,    39,
       0,     0,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,   104,     0,
       0,    35,    33,     0,     0,     0,     0,    27,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    90,     0,     0,     0,    58,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    89,     0,     0,     0,     0,     0,     0,
       0,     0,    59,     0,    58,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      92,     0,    93,    94,     0,     0,     0,     0,     0,     0,
      57,    56,     0,    53,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,     0,    97,    98,   102,     0,    95,    96,     0,     0,
       0,    52,     0,     0,     0,    86,     0,     0,     0,     0,
      84,     0,     0,    85,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,    99,   100,
      65,     0,    55,     0,     0,     0,    66,    67,    68,    69,
      70,    81,    82,    75,    76,    71,    72,    73,    74,    78,
      80,    77,    79,    83,    88,    87,    64,    54,    63,     0,
      62
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -402,  -402,  -402,   507,  -402,   225,   282,  -402,  -402,   290,
    -402,   510,  -211,  -278,  -402,   241,  -402,  -402,  -402,  -402,
    -302,  -402,   155,  -402,   121,  -402,  -402,  -402,     2,  -402,
    -402,  -402,  -402,    12,   -20,  -402,  -360,  -158,  -401,  -402,
     -46,  -216,   -52,  -213,   117,    -3,   692,  -402,  -402,  -402,
    -402,   -33,  -402,  -402,  -402,  -402,  -402,   294,  -402,  -402,
    -402,  -402,  -402,  -402,  -402,   386,  -402,  -402,  -402,  -402,
      -8,  -318,   -30
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    39,    40,   137,   229,   230,   231,    75,
       5,     6,   285,   134,   220,   221,   232,   233,   234,   235,
     367,   368,   369,   404,   405,   406,   522,   562,   523,    41,
     407,   408,   409,   517,   555,   410,   411,   412,   370,   374,
     281,   204,    93,   157,   282,    65,    44,    45,    46,    47,
     146,    48,    49,    50,    51,    52,   239,   240,    53,    54,
      55,    56,    57,    58,   149,   150,    59,    60,    61,    62,
     143,   144,    78
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,    43,   277,    83,    84,    89,   329,    10,    11,    12,
      13,    14,   388,   129,   116,   286,   273,    15,    16,   247,
     132,   154,    17,    72,   135,    18,   481,    86,   512,    94,
       7,   372,   113,    79,     8,    43,    14,   420,    85,    80,
     377,   155,   424,   278,   142,   114,   482,   138,   513,    14,
     140,     2,   147,   389,    14,    19,   202,   151,   153,   274,
     381,   392,   136,   396,   248,    21,    22,    23,    24,    25,
      14,    14,   328,   141,   113,    10,    11,    12,    13,    14,
     395,    26,    43,   518,   414,    15,    16,   114,   279,   159,
      17,   418,    71,    18,   280,   273,   398,   399,   396,   486,
     422,    14,    14,    91,   400,   401,   203,   249,   250,   236,
     325,   159,   159,   242,   518,   490,   556,   363,    14,   371,
      42,    42,   397,    19,   276,   457,    76,   396,   325,   237,
     238,   398,   399,    21,    22,    23,    24,    25,   322,   400,
     401,   415,   402,    43,   455,    92,   519,   565,   380,    26,
     556,    73,   396,   326,   325,    42,   325,   325,   325,   403,
     398,   399,    10,    11,    12,    13,    14,   247,   400,   401,
     423,   357,    15,    16,   203,   325,    74,    17,    85,   488,
      18,    90,   325,    94,   416,   398,   399,   275,    95,    96,
      97,    98,    99,   400,   401,   325,   325,   524,   330,   526,
     528,   529,    42,   247,   325,   563,   325,   382,   325,   158,
      19,   632,   117,   325,   325,   296,   297,   325,   530,   159,
      21,    22,    23,    24,    25,   531,   320,   247,   113,   332,
     292,   200,   201,   560,   561,   325,    26,   331,   533,   534,
     159,   114,    85,   386,   159,   361,   601,   536,   552,   537,
     605,   538,   325,   448,   133,   610,   539,   540,   613,   131,
     541,   203,   448,    42,   218,    94,   448,   393,   333,   159,
      95,    96,    97,    98,    99,   148,   100,   101,   542,   222,
     630,   325,   325,   336,   362,   337,   636,   325,   637,   638,
     639,   640,   325,   641,   642,   543,   643,   644,   645,   646,
     647,   648,   649,   650,   651,   652,   653,   654,   655,   325,
     113,    94,   156,   656,   237,   293,   658,  -124,    97,    98,
      99,   159,   159,   114,   544,   545,   554,   159,   325,   159,
     546,   325,   273,   516,   219,   547,    85,    85,   364,   365,
     366,   660,   592,   596,    85,   223,   364,   365,   366,   243,
     628,   290,   548,   364,   365,   366,   113,   159,   159,   224,
     295,   225,   226,   227,   298,    92,   251,   390,   252,   114,
     284,   559,   228,   159,   603,   657,   253,   254,   283,   255,
     256,   257,   159,   417,   633,   258,   259,   260,   261,   287,
     262,   263,   264,   265,   159,   266,   267,   268,   269,   270,
     272,   159,   305,   308,   327,   334,   338,   373,   159,   375,
     487,   324,   489,   491,   492,   493,   494,   159,   496,   497,
     378,   499,   500,   501,   502,   503,   504,   505,   506,   507,
     508,   509,   510,   511,   360,   383,   385,   376,   387,   520,
     394,   358,   359,   419,   450,   451,   452,   158,   454,   158,
     495,   484,   456,   159,   458,   159,   159,   159,   159,   159,
     459,   159,   159,   460,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   379,   158,   566,
     461,   462,   159,   463,   464,   465,   466,   467,   480,   468,
     469,   470,   483,   391,   471,   472,   473,   474,   475,   476,
     477,   478,   413,   479,   485,   515,   498,   521,   553,   525,
     527,    63,   289,   335,   421,    64,   557,   594,   288,   323,
     627,   413,   159,   384,   159,   447,   564,   551,   449,   159,
     532,   591,   159,   294,   535,   244,   595,   453,   558,   567,
     569,   570,   571,   572,   574,   575,   593,   577,   578,   597,
     579,   580,   581,   582,   583,   159,   584,   585,   586,   587,
     600,   588,   589,   599,   159,   602,   159,   159,   159,   159,
     635,   159,   159,     0,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   629,     0,     0,
       0,     0,     0,     0,     0,    94,   159,     0,     0,   159,
      95,    96,    97,    98,    99,     0,   100,   101,     0,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   159,     0,     0,   112,    85,     0,     0,     0,
     113,     0,   142,     0,   568,     0,     0,     0,     0,   573,
       0,     0,   576,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   598,     0,     0,     0,     0,
       0,   115,     0,     0,   604,     0,   606,   607,   608,   609,
       0,   611,   612,     0,   614,   615,   616,   617,   618,   619,
     620,   621,   622,   623,   624,   625,   626,    66,    67,    68,
      69,    70,     0,     0,     0,     0,   631,     0,     0,   634,
       0,    77,     0,    81,    82,   160,     0,     0,    87,    88,
       0,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,     0,     0,   176,   177,
     178,   179,   659,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   180,     0,     0,     0,
       0,   139,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,     0,     0,     0,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,     0,     0,   217,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     9,     0,     0,    10,    11,    12,
      13,    14,     0,     0,   245,     0,   246,    15,    16,     0,
       0,     0,    17,     0,     0,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    19,     0,     0,     0,     0,
       0,    20,     0,     0,     0,    21,    22,    23,    24,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     205,    26,    27,     0,    28,    29,    30,    31,     0,     0,
      32,    33,    34,    35,     0,    36,    37,    38,     0,   291,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   299,   301,   302,   303,   304,     0,   306,
     307,     0,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,     0,     1,   321,    -5,    -5,    -5,    -5,
      -5,     0,     0,     0,     0,     0,    -5,    -5,     0,     0,
       0,    -5,     0,     0,    -5,     0,     0,     0,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,     0,     0,   440,   441,   442,   443,     0,
       0,     0,     0,     0,    -5,     0,     0,     0,     0,     2,
      -5,     0,     0,   444,    -5,    -5,    -5,    -5,    -5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      -5,    -5,     0,    -5,    -5,    -5,    -5,     0,     0,    -5,
      -5,    -5,    -5,     0,    -5,    -5,    -5,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,    15,    16,     0,
       0,     0,    17,   445,   446,    18,     0,     0,     0,     0,
       0,    94,     0,     0,     0,     0,    95,    96,    97,    98,
      99,     0,   100,   101,     0,   102,   103,   104,   105,   106,
     107,     0,     0,   108,     0,    19,     0,     0,     0,     0,
       0,    20,     0,     0,     0,    21,    22,    23,    24,    25,
       0,   112,     0,     0,     0,     0,   113,     0,     0,     0,
       0,    26,    27,     0,    28,    29,    30,    31,     0,   114,
      32,    33,    34,    35,     0,    36,    37,    38,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,    15,    16,
       0,     0,     0,    17,     0,     0,    18,   115,     0,     0,
       0,     0,    94,   514,     0,     0,     0,    95,    96,    97,
      98,    99,     0,   100,   101,     0,   102,   103,   104,   105,
     106,   107,     0,     0,   108,   145,    19,     0,     0,     0,
       0,     0,    20,     0,   549,     0,    21,    22,    23,    24,
      25,     0,     0,     0,     0,     0,     0,   113,     0,     0,
       0,     0,    26,     0,     0,     0,    29,    30,    31,     0,
     114,    32,    33,    34,    35,     0,    36,    37,    38,    10,
      11,    12,    13,    14,     0,     0,     0,     0,     0,    15,
      16,     0,     0,     0,    17,     0,     0,    18,   115,     0,
       0,     0,     0,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,     0,   102,   103,   104,
     105,   106,   107,     0,     0,     0,   241,    19,     0,     0,
       0,     0,   205,    20,     0,     0,     0,    21,    22,    23,
      24,    25,     0,     0,     0,     0,     0,     0,   113,     0,
       0,     0,     0,    26,     0,     0,     0,    29,    30,    31,
       0,   114,    32,    33,    34,    35,     0,    36,    37,    38,
      10,    11,    12,    13,    14,     0,     0,     0,     0,     0,
      15,    16,     0,     0,     0,    17,     0,     0,    18,   115,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    19,     0,
       0,     0,     0,     0,    20,     0,     0,     0,    21,    22,
      23,    24,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    26,     0,     0,     0,    29,    30,
      31,     0,     0,    32,    33,    34,    35,     0,    36,    37,
      38,    94,     0,   152,     0,     0,    95,    96,    97,    98,
      99,     0,   100,   101,     0,   102,   103,   104,   105,   106,
     107,     0,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,     0,     0,     0,     0,   113,     0,    76,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,   114,
     100,   101,     0,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,     0,   112,
       0,     0,     0,     0,   113,     0,    76,    94,     0,     0,
       0,     0,    95,    96,    97,    98,    99,   114,   100,   101,
       0,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,     0,   112,     0,     0,
       0,   130,   113,     0,     0,    94,     0,     0,     0,     0,
      95,    96,    97,    98,    99,   114,   100,   101,     0,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,     0,   112,    85,     0,     0,     0,
     113,     0,     0,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,   114,   100,   101,     0,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,     0,   112,     0,     0,     0,     0,   113,   271,
       0,    94,     0,     0,     0,     0,    95,    96,    97,    98,
      99,   114,   100,   101,     0,   102,   103,   104,   105,   106,
     107,     0,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
       0,   112,     0,     0,     0,   339,   113,     0,     0,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,   114,
     100,   101,     0,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,     0,   112,
       0,     0,     0,   340,   113,     0,     0,    94,     0,     0,
       0,     0,    95,    96,    97,    98,    99,   114,   100,   101,
       0,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,     0,   112,     0,     0,
       0,   341,   113,     0,     0,    94,     0,     0,     0,     0,
      95,    96,    97,    98,    99,   114,   100,   101,     0,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,     0,   112,     0,     0,     0,   342,
     113,     0,     0,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,   114,   100,   101,     0,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,     0,   112,     0,     0,     0,   343,   113,     0,
       0,    94,     0,     0,     0,     0,    95,    96,    97,    98,
      99,   114,   100,   101,     0,   102,   103,   104,   105,   106,
     107,     0,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
       0,   112,     0,     0,     0,   344,   113,     0,     0,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,   114,
     100,   101,     0,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,     0,   112,
       0,     0,     0,   345,   113,     0,     0,    94,     0,     0,
       0,     0,    95,    96,    97,    98,    99,   114,   100,   101,
       0,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,     0,   112,     0,     0,
       0,   346,   113,     0,     0,    94,     0,     0,     0,     0,
      95,    96,    97,    98,    99,   114,   100,   101,     0,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,     0,   112,     0,     0,     0,   347,
     113,     0,     0,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,   114,   100,   101,     0,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,     0,   112,     0,     0,     0,   348,   113,     0,
       0,    94,     0,     0,     0,     0,    95,    96,    97,    98,
      99,   114,   100,   101,     0,   102,   103,   104,   105,   106,
     107,     0,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
       0,   112,     0,     0,     0,   349,   113,     0,     0,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,   114,
     100,   101,     0,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,     0,   112,
       0,     0,     0,   350,   113,     0,     0,    94,     0,     0,
       0,     0,    95,    96,    97,    98,    99,   114,   100,   101,
       0,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,     0,   112,     0,     0,
       0,   351,   113,     0,     0,    94,     0,     0,     0,     0,
      95,    96,    97,    98,    99,   114,   100,   101,     0,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,     0,   112,     0,     0,     0,   352,
     113,     0,     0,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,   114,   100,   101,     0,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,     0,   112,     0,     0,     0,   353,   113,     0,
       0,    94,     0,     0,     0,     0,    95,    96,    97,    98,
      99,   114,   100,   101,     0,   102,   103,   104,   105,   106,
     107,     0,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
       0,   112,     0,     0,     0,   354,   113,     0,     0,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,   114,
     100,   101,     0,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,     0,   112,
       0,     0,     0,   355,   113,     0,     0,    94,     0,     0,
       0,     0,    95,    96,    97,    98,    99,   114,   100,   101,
       0,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,     0,   112,     0,     0,
       0,   356,   113,     0,     0,    94,     0,     0,     0,     0,
      95,    96,    97,    98,    99,   114,   100,   101,     0,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,     0,   112,     0,     0,     0,     0,
     113,     0,   550,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,   114,   100,   101,     0,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,     0,   112,     0,     0,     0,     0,   113,     0,
     590,    94,     0,     0,     0,     0,    95,    96,    97,    98,
      99,   114,   100,   101,     0,   102,   103,   104,   105,   106,
     107,     0,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
       0,   112,     0,     0,     0,     0,   113,     0,     0,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,   114,
     100,   101,     0,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,     0,   112,
       0,     0,     0,     0,   113,     0,     0,    94,     0,     0,
       0,     0,    95,    96,    97,    98,    99,   114,   100,   101,
       0,   102,   103,   104,   105,   106,   107,     0,     0,   108,
       0,   110,    94,     0,     0,     0,     0,    95,    96,    97,
      98,    99,     0,   100,   101,   115,     0,   112,   104,   105,
     106,   107,   113,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,    15,    16,   114,     0,     0,    17,     0,
       0,    18,     0,     0,     0,     0,     0,   113,     0,     0,
       0,    10,    11,    12,    13,    14,     0,     0,     0,     0,
     114,    15,    16,   115,     0,     0,    17,     0,     0,    18,
       0,    19,     0,     0,     0,    76,    10,    11,    12,    13,
      14,    21,    22,    23,    24,    25,    15,    16,   115,     0,
       0,    17,     0,     0,    18,     0,     0,    26,     0,    19,
     300,     0,     0,     0,     0,     0,     0,     0,     0,    21,
      22,    23,    24,    25,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    19,    26,     0,     0,     0,     0,
       0,     0,     0,     0,    21,    22,    23,    24,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26
};

static const yytype_int16 yycheck[] =
{
       3,     4,   218,    33,    34,    38,   284,     3,     4,     5,
       6,     7,     9,    65,    44,   226,     9,    13,    14,     9,
      72,    35,    18,    26,    11,    21,    35,    35,    35,     8,
     111,   333,    53,    81,     4,    38,     7,   397,    49,    87,
     358,    55,   402,     9,    55,    66,    55,    77,    55,     7,
      80,    56,    85,    50,     7,    51,    52,    87,    88,    52,
     362,   379,    49,    34,    54,    61,    62,    63,    64,    65,
       7,     7,   283,    81,    53,     3,     4,     5,     6,     7,
     382,    77,    85,   484,   386,    13,    14,    66,    54,    92,
      18,   393,     7,    21,    52,     9,    67,    68,    34,    52,
       7,     7,     7,    11,    75,    76,   102,   159,   160,   139,
       9,   114,   115,   146,   515,    52,   517,   330,     7,   332,
       3,     4,    58,    51,    52,     7,    55,    34,     9,    84,
      85,    67,    68,    61,    62,    63,    64,    65,    52,    75,
      76,     7,    78,   146,   422,    53,    52,    52,   361,    77,
     551,     7,    34,    52,     9,    38,     9,     9,     9,    95,
      67,    68,     3,     4,     5,     6,     7,     9,    75,    76,
      77,    52,    13,    14,   102,     9,     7,    18,    49,   457,
      21,     7,     9,     8,    50,    67,    68,   217,    13,    14,
      15,    16,    17,    75,    76,     9,     9,    52,    10,    52,
      52,    52,    85,     9,     9,   523,     9,    49,     9,    92,
      51,    52,    51,     9,     9,   245,   246,     9,    52,   222,
      61,    62,    63,    64,    65,    52,   272,     9,    53,    10,
     238,   114,   115,    61,    62,     9,    77,    49,    52,    52,
     243,    66,    49,    49,   247,    10,   564,    52,    55,    52,
     568,    52,     9,   411,    53,   573,    52,    52,   576,    35,
      52,   102,   420,   146,    51,     8,   424,    49,    49,   272,
      13,    14,    15,    16,    17,    90,    19,    20,    52,    51,
     598,     9,     9,   291,    49,   293,   604,     9,   606,   607,
     608,   609,     9,   611,   612,    52,   614,   615,   616,   617,
     618,   619,   620,   621,   622,   623,   624,   625,   626,     9,
      53,     8,     7,   631,    84,    85,   634,     7,    15,    16,
      17,   324,   325,    66,    52,    52,    60,   330,     9,   332,
      52,     9,     9,    59,     7,    52,    49,    49,    72,    73,
      74,   659,    55,    55,    49,     7,    72,    73,    74,    51,
      55,    50,    52,    72,    73,    74,    53,   360,   361,    67,
     243,    69,    70,    71,   247,    53,    51,   375,    51,    66,
       7,    52,    80,   376,    52,    52,    51,    51,    70,    51,
      51,    51,   385,   391,   600,    51,    51,    51,    51,     7,
      51,    51,    51,    51,   397,    51,    51,    51,    51,    51,
      51,   404,    52,    52,     7,    49,     7,     7,   411,    52,
     456,    79,   458,   459,   460,   461,   462,   420,   464,   465,
       7,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,    79,    50,    10,    79,    50,   485,
      50,   324,   325,    50,     7,    50,    50,   330,     7,   332,
      52,    49,    51,   456,    51,   458,   459,   460,   461,   462,
      51,   464,   465,    51,   467,   468,   469,   470,   471,   472,
     473,   474,   475,   476,   477,   478,   479,   360,   361,   525,
      51,    51,   485,    51,    51,    51,    51,    51,     7,    51,
      51,    51,     7,   376,    51,    51,    51,    51,    51,    51,
      51,    51,   385,    51,    51,    49,    52,    10,   516,    51,
      79,     4,   230,   288,   397,     5,    59,    50,   228,   278,
      50,   404,   525,   368,   527,   404,   524,   515,   411,   532,
      79,   551,   535,   239,    79,   149,    60,   420,    79,    79,
      79,    79,    79,    79,    79,    79,   554,    79,    79,   557,
      79,    79,    79,    79,    79,   558,    79,    79,    79,    79,
      51,    79,    79,    79,   567,    79,   569,   570,   571,   572,
      79,   574,   575,    -1,   577,   578,   579,   580,   581,   582,
     583,   584,   585,   586,   587,   588,   589,   595,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,   599,    -1,    -1,   602,
      13,    14,    15,    16,    17,    -1,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,   635,    -1,    -1,    48,    49,    -1,    -1,    -1,
      53,    -1,    55,    -1,   527,    -1,    -1,    -1,    -1,   532,
      -1,    -1,   535,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   558,    -1,    -1,    -1,    -1,
      -1,    94,    -1,    -1,   567,    -1,   569,   570,   571,   572,
      -1,   574,   575,    -1,   577,   578,   579,   580,   581,   582,
     583,   584,   585,   586,   587,   588,   589,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,   599,    -1,    -1,   602,
      -1,    29,    -1,    31,    32,     7,    -1,    -1,    36,    37,
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    33,   635,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,    -1,    -1,    -1,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,    -1,    -1,   131,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     0,    -1,    -1,     3,     4,     5,
       6,     7,    -1,    -1,   152,    -1,   154,    13,    14,    -1,
      -1,    -1,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     218,    77,    78,    -1,    80,    81,    82,    83,    -1,    -1,
      86,    87,    88,    89,    -1,    91,    92,    93,    -1,   237,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   251,   252,   253,   254,   255,    -1,   257,
     258,    -1,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,    -1,     1,   273,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    13,    14,    -1,    -1,
      -1,    18,    -1,    -1,    21,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    56,
      57,    -1,    -1,    48,    61,    62,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    78,    -1,    80,    81,    82,    83,    -1,    -1,    86,
      87,    88,    89,    -1,    91,    92,    93,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,    -1,
      -1,    -1,    18,    98,    99,    21,    -1,    -1,    -1,    -1,
      -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    -1,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      -1,    48,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    77,    78,    -1,    80,    81,    82,    83,    -1,    66,
      86,    87,    88,    89,    -1,    91,    92,    93,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,
      -1,    -1,    -1,    18,    -1,    -1,    21,    94,    -1,    -1,
      -1,    -1,     8,   481,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    -1,    19,    20,    -1,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    50,    51,    -1,    -1,    -1,
      -1,    -1,    57,    -1,   512,    -1,    61,    62,    63,    64,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    81,    82,    83,    -1,
      66,    86,    87,    88,    89,    -1,    91,    92,    93,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,
      14,    -1,    -1,    -1,    18,    -1,    -1,    21,    94,    -1,
      -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    -1,    50,    51,    -1,    -1,
      -1,    -1,   600,    57,    -1,    -1,    -1,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    82,    83,
      -1,    66,    86,    87,    88,    89,    -1,    91,    92,    93,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,
      13,    14,    -1,    -1,    -1,    18,    -1,    -1,    21,    94,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    61,    62,
      63,    64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    -1,    -1,    86,    87,    88,    89,    -1,    91,    92,
      93,     8,    -1,    10,    -1,    -1,    13,    14,    15,    16,
      17,    -1,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    53,    -1,    55,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    66,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,    48,
      -1,    -1,    -1,    -1,    53,    -1,    55,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    66,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    94,    -1,    48,    -1,    -1,
      -1,    52,    53,    -1,    -1,     8,    -1,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    66,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    94,    -1,    48,    49,    -1,    -1,    -1,
      53,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    66,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    -1,    48,    -1,    -1,    -1,    -1,    53,    54,
      -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    66,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,
      -1,    48,    -1,    -1,    -1,    52,    53,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    66,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,    48,
      -1,    -1,    -1,    52,    53,    -1,    -1,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    66,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    94,    -1,    48,    -1,    -1,
      -1,    52,    53,    -1,    -1,     8,    -1,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    66,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    94,    -1,    48,    -1,    -1,    -1,    52,
      53,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    66,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    -1,    48,    -1,    -1,    -1,    52,    53,    -1,
      -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    66,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,
      -1,    48,    -1,    -1,    -1,    52,    53,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    66,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,    48,
      -1,    -1,    -1,    52,    53,    -1,    -1,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    66,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    94,    -1,    48,    -1,    -1,
      -1,    52,    53,    -1,    -1,     8,    -1,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    66,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    94,    -1,    48,    -1,    -1,    -1,    52,
      53,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    66,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    -1,    48,    -1,    -1,    -1,    52,    53,    -1,
      -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    66,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,
      -1,    48,    -1,    -1,    -1,    52,    53,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    66,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,    48,
      -1,    -1,    -1,    52,    53,    -1,    -1,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    66,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    94,    -1,    48,    -1,    -1,
      -1,    52,    53,    -1,    -1,     8,    -1,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    66,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    94,    -1,    48,    -1,    -1,    -1,    52,
      53,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    66,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    -1,    48,    -1,    -1,    -1,    52,    53,    -1,
      -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    66,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,
      -1,    48,    -1,    -1,    -1,    52,    53,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    66,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,    48,
      -1,    -1,    -1,    52,    53,    -1,    -1,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    66,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    94,    -1,    48,    -1,    -1,
      -1,    52,    53,    -1,    -1,     8,    -1,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    66,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    94,    -1,    48,    -1,    -1,    -1,    -1,
      53,    -1,    55,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    66,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    -1,    48,    -1,    -1,    -1,    -1,    53,    -1,
      55,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    66,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,
      -1,    48,    -1,    -1,    -1,    -1,    53,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    66,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,    48,
      -1,    -1,    -1,    -1,    53,    -1,    -1,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    66,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      -1,    32,     8,    -1,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    -1,    19,    20,    94,    -1,    48,    24,    25,
      26,    27,    53,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    13,    14,    66,    -1,    -1,    18,    -1,
      -1,    21,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      66,    13,    14,    94,    -1,    -1,    18,    -1,    -1,    21,
      -1,    51,    -1,    -1,    -1,    55,     3,     4,     5,     6,
       7,    61,    62,    63,    64,    65,    13,    14,    94,    -1,
      -1,    18,    -1,    -1,    21,    -1,    -1,    77,    -1,    51,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    56,   113,   114,   122,   123,   111,     4,     0,
       3,     4,     5,     6,     7,    13,    14,    18,    21,    51,
      57,    61,    62,    63,    64,    65,    77,    78,    80,    81,
      82,    83,    86,    87,    88,    89,    91,    92,    93,   115,
     116,   141,   156,   157,   158,   159,   160,   161,   163,   164,
     165,   166,   167,   170,   171,   172,   173,   174,   175,   178,
     179,   180,   181,   115,   123,   157,   158,   158,   158,   158,
     158,     7,   157,     7,     7,   121,    55,   158,   184,    81,
      87,   158,   158,   184,   184,    49,   182,   158,   158,   163,
       7,    11,    53,   154,     8,    13,    14,    15,    16,    17,
      19,    20,    22,    23,    24,    25,    26,    27,    30,    31,
      32,    33,    48,    53,    66,    94,   184,    51,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,   154,
      52,    35,   154,    53,   125,    11,    49,   117,   184,   158,
     184,   182,    55,   182,   183,    50,   162,   163,    90,   176,
     177,   184,    10,   184,    35,    55,     7,   155,   156,   157,
       7,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    30,    31,    32,    33,
      48,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     156,   156,    52,   102,   153,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,    51,     7,
     126,   127,    51,     7,    67,    69,    70,    71,    80,   118,
     119,   120,   128,   129,   130,   131,   184,    84,    85,   168,
     169,    50,   163,    51,   177,   158,   158,     9,    54,   154,
     154,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    54,    51,     9,    52,   184,    52,   153,     9,    54,
      52,   152,   156,    70,     7,   124,   124,     7,   121,   118,
      50,   158,   182,    85,   169,   156,   184,   184,   156,   158,
      52,   158,   158,   158,   158,    52,   158,   158,    52,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     152,   158,    52,   127,    79,     9,    52,     7,   124,   125,
      10,    49,    10,    49,    49,   117,   182,   182,     7,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,   156,   156,
      79,    10,    49,   155,    72,    73,    74,   132,   133,   134,
     150,   155,   132,     7,   151,    52,    79,   183,     7,   156,
     155,   132,    49,    50,   134,    10,    49,    50,     9,    50,
     182,   156,   183,    49,    50,   132,    34,    58,    67,    68,
      75,    76,    78,    95,   135,   136,   137,   142,   143,   144,
     147,   148,   149,   156,   132,     7,    50,   182,   132,    50,
     148,   156,     7,    77,   148,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      30,    31,    32,    33,    48,    98,    99,   136,   149,   156,
       7,    50,    50,   156,     7,   125,    51,     7,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
       7,    35,    55,     7,    49,    51,    52,   152,   125,   152,
      52,   152,   152,   152,   152,    52,   152,   152,    52,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,    35,    55,   158,    49,    59,   145,   150,    52,
     152,    10,   138,   140,    52,    51,    52,    79,    52,    52,
      52,    52,    79,    52,    52,    79,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,   158,
      55,   145,    55,   182,    60,   146,   150,    59,    79,    52,
      61,    62,   139,   183,   140,    52,   152,    79,   156,    79,
      79,    79,    79,   156,    79,    79,   156,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      55,   146,    55,   182,    50,    60,    55,   182,   156,    79,
      51,   183,    79,    52,   156,   183,   156,   156,   156,   156,
     183,   156,   156,   183,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,    50,    55,   182,
     183,   156,    52,   153,   156,    79,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,    52,   183,   156,
     183
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   112,   113,   113,   113,   114,   114,   115,   115,   115,
     116,   117,   118,   118,   118,   118,   118,   119,   119,   120,
     120,   121,   121,   122,   122,   123,   124,   125,   125,   126,
     126,   127,   128,   128,   129,   129,   130,   130,   131,   131,
     132,   132,   133,   133,   134,   135,   135,   136,   136,   136,
     136,   136,   137,   137,   138,   138,   139,   139,   140,   140,
     141,   141,   142,   142,   142,   142,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   144,
     144,   144,   144,   145,   145,   145,   145,   146,   146,   146,
     146,   147,   147,   148,   148,   149,   149,   149,   149,   149,
     150,   150,   150,   151,   151,   152,   152,   153,   153,   153,
     154,   154,   155,   155,   156,   157,   157,   158,   158,   158,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   161,   161,   161,   161,
     161,   161,   161,   162,   162,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     164,   165,   166,   167,   167,   167,   167,   168,   168,   169,
     170,   171,   172,   173,   173,   174,   175,   176,   176,   177,
     178,   178,   179,   180,   181,   182,   182,   183,   183,   184
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
       1,     1,     1,     1,     3,     2,     4,     1,     7,     3,
       0,     3,     1,     3,     2,     1,     3,     3,     1,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     4,     3,     6,     5,     1,
       1,     1,     2,     4,     4,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     5,     5,     5,     1,     1,     1,     1,
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
#line 150 "beacon.y" /* yacc.c:1663  */
    {
		yyclearin;
	}
#line 2357 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 6:
#line 158 "beacon.y" /* yacc.c:1663  */
    {
		ast_compile_entry((yyvsp[0].ast_value));
	}
#line 2365 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 7:
#line 164 "beacon.y" /* yacc.c:1663  */
    {
		ast_compile_entry((yyvsp[0].ast_value));
	}
#line 2373 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 8:
#line 168 "beacon.y" /* yacc.c:1663  */
    {
		ast_compile_entry((yyvsp[0].ast_value));
	}
#line 2381 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 9:
#line 172 "beacon.y" /* yacc.c:1663  */
    {
		ast_compile_entry((yyvsp[0].ast_value));
	}
#line 2389 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 10:
#line 178 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2397 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 11:
#line 185 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 2405 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 12:
#line 192 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2413 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 17:
#line 203 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 2421 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 18:
#line 207 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2429 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 19:
#line 214 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 2437 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 21:
#line 222 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[0].stringv_value));
	}
#line 2445 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 22:
#line 226 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[-2].ast_value), (yyvsp[0].stringv_value));
	}
#line 2453 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 24:
#line 234 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_import_decl_list((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2461 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 25:
#line 241 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[0].ast_value)));
	}
#line 2469 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 26:
#line 248 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_parameterized_typename((yyvsp[-1].stringv_value), (yyvsp[0].ast_value));
	}
#line 2477 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 27:
#line 255 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 2485 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 28:
#line 259 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 2493 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 29:
#line 266 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 2501 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 30:
#line 270 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_type_parameter_list((yyvsp[0].ast_value), (yyvsp[-2].ast_value));
	}
#line 2509 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 31:
#line 277 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_type_parameter((yyvsp[0].stringv_value), ast_new_blank());
	}
#line 2517 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 32:
#line 283 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_abstract_class_decl((yyvsp[-3].ast_value), ast_new_blank(), (yyvsp[-1].ast_value));
	}
#line 2525 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 33:
#line 287 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_abstract_class_decl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2533 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 34:
#line 293 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[-3].ast_value), ast_new_blank(), (yyvsp[-1].ast_value));
	}
#line 2541 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 35:
#line 297 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2549 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 36:
#line 304 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2557 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 37:
#line 308 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[-4].stringv_value), (yyvsp[-2].ast_value));
	}
#line 2565 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 38:
#line 315 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[-3].ast_value), ast_new_blank(), (yyvsp[-1].ast_value));
	}
#line 2573 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 39:
#line 319 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2581 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 40:
#line 326 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 2589 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 43:
#line 335 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2597 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 44:
#line 342 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[-2].access_level_value), (yyvsp[0].ast_value));
	}
#line 2605 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 45:
#line 349 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[0].ast_value));
	}
#line 2613 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 46:
#line 353 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[-1].ast_value), ast_new_member_decl((yyvsp[0].ast_value)));
	}
#line 2621 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 52:
#line 368 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[-3].ast_value), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2629 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 53:
#line 372 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2637 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 54:
#line 379 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[-3].chain_type_value), (yyvsp[-1].ast_value));
	}
#line 2645 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 55:
#line 383 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[-2].chain_type_value), ast_new_blank());
	}
#line 2653 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 56:
#line 390 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.chain_type_value) = chain_type_super;
	}
#line 2661 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 57:
#line 394 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.chain_type_value) = chain_type_this;
	}
#line 2669 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 58:
#line 401 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 2677 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 60:
#line 409 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2685 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 61:
#line 413 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), 8, (yyvsp[-1].ast_value));
	}
#line 2693 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 62:
#line 420 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_method_decl((yyvsp[-8].ast_value), (yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2701 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 63:
#line 424 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[-7].ast_value), (yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2709 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 64:
#line 428 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_method_decl(ast_new_modifier(modifier_none), (yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2717 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 65:
#line 432 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params(ast_new_modifier(modifier_none), (yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2725 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 66:
#line 439 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_add, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2733 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 67:
#line 443 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_sub, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2741 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 68:
#line 447 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_mul, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2749 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 69:
#line 451 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_div, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2757 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 70:
#line 455 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_mod, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2765 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 71:
#line 459 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_gt, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2773 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 72:
#line 463 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_ge, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2781 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 73:
#line 467 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_lt, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2789 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 74:
#line 471 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_le, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2797 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 75:
#line 476 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_eq, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2805 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 76:
#line 480 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_noteq, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2813 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 77:
#line 485 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_bit_or, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2821 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 78:
#line 489 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_bit_and, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2829 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 79:
#line 494 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_logic_or, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2837 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 80:
#line 498 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_logic_and, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2845 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 81:
#line 503 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_lshift, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2853 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 82:
#line 507 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_rshift, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2861 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 83:
#line 512 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_excor, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2869 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 84:
#line 517 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_not, ast_new_blank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2877 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 85:
#line 522 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_childa, ast_new_blank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2885 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 86:
#line 526 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_negative, ast_new_blank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2893 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 87:
#line 531 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_subscript_get, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2901 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 88:
#line 536 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_subscript_set, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2909 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 89:
#line 543 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[-1].stringv_value), ast_new_blank());
	}
#line 2917 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 90:
#line 547 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_decl(ast_new_modifier(modifier_none), (yyvsp[-2].ast_value), (yyvsp[-1].stringv_value), ast_new_blank());
	}
#line 2925 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 91:
#line 551 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[-5].ast_value), (yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2933 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 92:
#line 555 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_decl(ast_new_modifier(modifier_none), (yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2941 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 93:
#line 562 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_blank(), ast_new_blank());
	}
#line 2949 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 94:
#line 566 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_blank(), (yyvsp[0].ast_value));
	}
#line 2957 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 95:
#line 570 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_access((yyvsp[-2].access_level_value)), ast_new_blank());
	}
#line 2965 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 96:
#line 574 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_access((yyvsp[-2].access_level_value)), ast_new_blank());
	}
#line 2973 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 97:
#line 581 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_blank(), ast_new_blank());
	}
#line 2981 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 98:
#line 585 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_blank(), (yyvsp[0].ast_value));
	}
#line 2989 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 99:
#line 589 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_access((yyvsp[-2].access_level_value)), ast_new_blank());
	}
#line 2997 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 100:
#line 593 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_access((yyvsp[-2].access_level_value)), ast_new_blank());
	}
#line 3005 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 101:
#line 600 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_decl((yyvsp[-6].ast_value), (yyvsp[-5].ast_value), (yyvsp[-4].stringv_value), (yyvsp[-2].ast_value), (yyvsp[-1].ast_value));
	}
#line 3013 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 102:
#line 604 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_decl(ast_new_modifier(modifier_none), (yyvsp[-5].ast_value), (yyvsp[-4].stringv_value), (yyvsp[-2].ast_value), (yyvsp[-1].ast_value));
	}
#line 3021 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 103:
#line 611 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 3029 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 104:
#line 615 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier_list((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 3037 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 105:
#line 622 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_static);
	}
#line 3045 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 106:
#line 626 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_native);
	}
#line 3053 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 107:
#line 630 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_abstract);
	}
#line 3061 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 108:
#line 634 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_override);
	}
#line 3069 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 109:
#line 638 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_final);
	}
#line 3077 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 110:
#line 645 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = access_public;
	}
#line 3085 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 111:
#line 649 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = access_private;
	}
#line 3093 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 112:
#line 653 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = access_protected;
	}
#line 3101 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 113:
#line 660 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[0].stringv_value));
	}
#line 3109 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 114:
#line 664 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[0].stringv_value), (yyvsp[-2].ast_value));
	}
#line 3117 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 115:
#line 671 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[-1].ast_value), (yyvsp[0].stringv_value));
	}
#line 3125 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 116:
#line 675 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[-1].ast_value), (yyvsp[0].stringv_value), (yyvsp[-3].ast_value));
	}
#line 3133 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 117:
#line 682 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[0].ast_value));
	}
#line 3141 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 118:
#line 686 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_lambda((yyvsp[-4].ast_value), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3149 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 119:
#line 690 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[0].ast_value)), (yyvsp[-2].ast_value));
	}
#line 3157 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 120:
#line 697 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 3165 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 121:
#line 701 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 3173 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 122:
#line 708 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 3181 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 123:
#line 712 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[0].ast_value), (yyvsp[-2].ast_value));
	}
#line 3189 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 124:
#line 719 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3197 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 125:
#line 726 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[0].stringv_value));
	}
#line 3205 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 126:
#line 730 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[0].stringv_value)), (yyvsp[-2].ast_value));
	}
#line 3213 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 127:
#line 739 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 3221 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 130:
#line 747 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_unary(ast_pos, (yyvsp[0].ast_value));
	}
#line 3229 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 131:
#line 751 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_unary(ast_neg, (yyvsp[0].ast_value));
	}
#line 3237 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 132:
#line 755 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_add, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3245 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 133:
#line 759 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_sub, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3253 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 134:
#line 763 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_mul, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3261 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 135:
#line 767 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_div, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3269 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 136:
#line 771 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_mod, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3277 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 137:
#line 775 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_or, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3285 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 138:
#line 779 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_equal, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3293 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 139:
#line 783 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_notequal, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3301 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 140:
#line 787 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_and, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3309 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 141:
#line 791 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3317 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 142:
#line 795 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_or, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3325 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 143:
#line 799 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_and, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3333 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 144:
#line 803 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3341 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 145:
#line 807 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_add_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3349 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 146:
#line 811 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_sub_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3357 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 147:
#line 815 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_mul_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3365 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 148:
#line 819 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_div_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3373 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 149:
#line 823 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_mod_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3381 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 150:
#line 827 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_and_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3389 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 151:
#line 831 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_or_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3397 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 152:
#line 835 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3405 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 153:
#line 839 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3413 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 154:
#line 843 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3421 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 155:
#line 847 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_gt, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3429 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 156:
#line 851 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_ge, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3437 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 157:
#line 855 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_lt, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3445 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 158:
#line 859 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_le, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3453 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 159:
#line 863 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3461 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 160:
#line 867 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3469 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 161:
#line 871 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_instanceof((yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3477 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 162:
#line 875 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_as((yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3485 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 163:
#line 879 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_unary(ast_childa, (yyvsp[0].ast_value));
	}
#line 3493 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 164:
#line 883 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_unary(ast_not, (yyvsp[0].ast_value));
	}
#line 3501 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 165:
#line 887 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3509 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 166:
#line 891 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[-2].ast_value), ast_new_blank());
	}
#line 3517 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 167:
#line 895 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[-4].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3525 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 168:
#line 899 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), ast_new_blank());
	}
#line 3533 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 169:
#line 903 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_this();
	}
#line 3541 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 170:
#line 907 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_super();
	}
#line 3549 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 172:
#line 914 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3557 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 173:
#line 918 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[-3].ast_value), (yyvsp[-1].stringv_value), (yyvsp[0].ast_value));
	}
#line 3565 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 174:
#line 922 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_subscript_access((yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3573 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 175:
#line 926 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_add, (yyvsp[-1].ast_value));
	}
#line 3581 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 176:
#line 930 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_sub, (yyvsp[-1].ast_value));
	}
#line 3589 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 177:
#line 934 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_mul, (yyvsp[-1].ast_value));
	}
#line 3597 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 178:
#line 938 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_div, (yyvsp[-1].ast_value));
	}
#line 3605 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 179:
#line 942 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_mod, (yyvsp[-1].ast_value));
	}
#line 3613 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 180:
#line 946 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_gt, (yyvsp[-1].ast_value));
	}
#line 3621 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 181:
#line 950 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_ge, (yyvsp[-1].ast_value));
	}
#line 3629 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 182:
#line 954 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_lt, (yyvsp[-1].ast_value));
	}
#line 3637 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 183:
#line 958 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_le, (yyvsp[-1].ast_value));
	}
#line 3645 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 184:
#line 962 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_eq, (yyvsp[-1].ast_value));
	}
#line 3653 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 185:
#line 966 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_noteq, (yyvsp[-1].ast_value));
	}
#line 3661 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 186:
#line 970 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_bit_or, (yyvsp[-1].ast_value));
	}
#line 3669 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 187:
#line 974 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_bit_and, (yyvsp[-1].ast_value));
	}
#line 3677 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 188:
#line 978 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_logic_or, (yyvsp[-1].ast_value));
	}
#line 3685 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 189:
#line 982 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_logic_and, (yyvsp[-1].ast_value));
	}
#line 3693 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 190:
#line 986 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_lshift, (yyvsp[-1].ast_value));
	}
#line 3701 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 191:
#line 990 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_rshift, (yyvsp[-1].ast_value));
	}
#line 3709 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 192:
#line 994 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_excor, (yyvsp[-1].ast_value));
	}
#line 3717 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 193:
#line 998 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[-4].ast_value), operator_not);
	}
#line 3725 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 194:
#line 1002 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[-4].ast_value), operator_childa);
	}
#line 3733 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 195:
#line 1006 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[-4].ast_value), operator_negative);
	}
#line 3741 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 200:
#line 1016 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_true();
	}
#line 3749 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 201:
#line 1020 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_false();
	}
#line 3757 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 202:
#line 1024 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_null();
	}
#line 3765 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 203:
#line 1033 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[0].ast_value));
	}
#line 3773 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 204:
#line 1037 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3781 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 205:
#line 1043 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[-1].ast_value));
	}
#line 3789 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 220:
#line 1063 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[-2].ast_value), (yyvsp[-1].stringv_value));
	}
#line 3797 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 221:
#line 1069 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 3805 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 222:
#line 1075 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 3813 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 223:
#line 1081 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_if((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3821 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 224:
#line 1085 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3829 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 225:
#line 1089 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[-2].ast_value), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3837 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 226:
#line 1093 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[-4].ast_value), (yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3845 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 228:
#line 1100 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3853 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 229:
#line 1106 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3861 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 230:
#line 1112 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_while((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3869 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 231:
#line 1118 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_break();
	}
#line 3877 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 232:
#line 1124 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_continue();
	}
#line 3885 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 233:
#line 1130 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_return((yyvsp[-1].ast_value));
	}
#line 3893 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 234:
#line 1134 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_return_empty();
	}
#line 3901 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 235:
#line 1140 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[-1].ast_value));
	}
#line 3909 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 236:
#line 1146 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_try((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3917 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 237:
#line 1152 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 3925 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 238:
#line 1156 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 3933 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 239:
#line 1162 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[-3].ast_value), (yyvsp[-2].stringv_value), (yyvsp[0].ast_value));
	}
#line 3941 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 240:
#line 1168 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3949 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 241:
#line 1172 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[-1].ast_value), ast_new_blank());
	}
#line 3957 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 242:
#line 1178 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_defer((yyvsp[0].ast_value));
	}
#line 3965 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 243:
#line 1184 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_yield_return((yyvsp[-1].ast_value));
	}
#line 3973 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 244:
#line 1190 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_yield_break();
	}
#line 3981 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 245:
#line 1196 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[-1].ast_value));
	}
#line 3989 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 246:
#line 1200 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_scope_empty();
	}
#line 3997 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 247:
#line 1206 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 4005 "beacon.tab.c" /* yacc.c:1663  */
    break;


#line 4009 "beacon.tab.c" /* yacc.c:1663  */
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
#line 1214 "beacon.y" /* yacc.c:1907  */




