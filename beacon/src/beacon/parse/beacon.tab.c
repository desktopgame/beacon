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
    INTERFACE = 323,
    CLASS = 324,
    ENUM = 325,
    PUBLIC = 326,
    PRIVATE = 327,
    PROTECTED = 328,
    STATIC = 329,
    NATIVE = 330,
    NEW = 331,
    DEF = 332,
    ARROW = 333,
    NAMESPACE = 334,
    RETURN = 335,
    YIELD = 336,
    IF = 337,
    ELIF = 338,
    ELSE = 339,
    WHILE = 340,
    BREAK = 341,
    CONTINUE = 342,
    TRY = 343,
    CATCH = 344,
    THROW = 345,
    ASSER_T = 346,
    DEFER = 347,
    INSTANCEOF = 348,
    OPERATOR = 349,
    BOUNDS_EXTENDS = 350,
    BOUNDS_SUPER = 351,
    SUBSCRIPT_SET = 352,
    SUBSCRIPT_GET = 353,
    QUOTE = 354,
    NEGATIVE = 355,
    POSITIVE = 356,
    REF = 357,
    FUNCCALL = 358,
    ARRAY_SUBSCRIPT = 359,
    FORM_TYPE = 360
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "beacon.y" /* yacc.c:355  */

	char char_value;
	StringView stringv_value;
	AST* ast_value;
	assign_operator_type assign_otype_value;
	constructor_chain_type chain_type_value;
	AccessLevel access_level_value;

#line 238 "beacon.tab.c" /* yacc.c:355  */
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

#line 269 "beacon.tab.c" /* yacc.c:358  */

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
#define YYLAST   2606

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  246
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  650

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   360

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     106,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
     105
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
     592,   599,   603,   610,   614,   621,   625,   629,   633,   640,
     644,   648,   655,   659,   666,   670,   677,   681,   689,   692,
     699,   703,   710,   717,   721,   730,   734,   735,   738,   742,
     746,   750,   754,   758,   762,   766,   770,   774,   778,   782,
     786,   790,   794,   798,   802,   806,   810,   814,   818,   822,
     826,   830,   834,   838,   842,   846,   850,   854,   858,   863,
     867,   871,   875,   879,   883,   887,   891,   895,   899,   903,
     907,   911,   915,   919,   923,   927,   931,   935,   939,   943,
     947,   951,   955,   959,   963,   967,   971,   975,   979,   982,
     986,   990,   994,  1000,  1001,  1002,  1003,  1004,  1008,  1012,
    1021,  1025,  1031,  1035,  1036,  1037,  1038,  1039,  1040,  1041,
    1042,  1043,  1044,  1045,  1046,  1047,  1048,  1051,  1057,  1063,
    1069,  1073,  1077,  1081,  1087,  1088,  1094,  1100,  1106,  1112,
    1118,  1122,  1128,  1134,  1140,  1144,  1150,  1156,  1160,  1166,
    1172,  1178,  1184,  1188,  1194,  1198,  1201
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
  "TRUE_TOK", "FALSE_TOK", "NULL_TOK", "AS", "ABSTRACT", "INTERFACE",
  "CLASS", "ENUM", "PUBLIC", "PRIVATE", "PROTECTED", "STATIC", "NATIVE",
  "NEW", "DEF", "ARROW", "NAMESPACE", "RETURN", "YIELD", "IF", "ELIF",
  "ELSE", "WHILE", "BREAK", "CONTINUE", "TRY", "CATCH", "THROW", "ASSER_T",
  "DEFER", "INSTANCEOF", "OPERATOR", "BOUNDS_EXTENDS", "BOUNDS_SUPER",
  "SUBSCRIPT_SET", "SUBSCRIPT_GET", "QUOTE", "NEGATIVE", "POSITIVE", "REF",
  "FUNCCALL", "ARRAY_SUBSCRIPT", "FORM_TYPE", "'\\n'", "$accept",
  "compilation_unit", "init_decl", "body_decl", "namespace_decl",
  "namespace_body", "namespace_member_decl", "namespace_member_decl_list",
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
     355,   356,   357,   358,   359,   360,    10
};
# endif

#define YYPACT_NINF -456

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-456)))

#define YYTABLE_NINF -123

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     900,   -94,    49,   808,   990,   -27,  -456,  -456,  -456,  -456,
    -456,  -456,  -456,  -456,  -456,  2471,  2471,  2471,  2471,  2471,
     141,  -456,  -456,  -456,  -456,  -456,   236,   239,   243,  2323,
     156,  2471,  2471,    57,    57,    92,  2471,  2471,  1264,  -456,
    -456,  -456,   248,    97,   461,   124,   614,  -456,  -456,  -456,
    -456,  -456,  -456,  -456,  -456,  -456,  -456,  -456,  -456,  -456,
    -456,  -456,  -456,  -456,  -456,    97,     5,     5,     5,     5,
     831,   198,    97,   200,  -456,   237,  -456,   461,  -456,  2471,
      57,   582,   107,  -456,  -456,  1080,   175,   461,   314,  -456,
      -9,   253,   236,   262,  2554,  2471,  2471,  2471,  2471,  2471,
    2471,  2471,  2471,  2471,  2471,  2471,  2471,  2471,  2471,  2471,
    2471,  2471,  2471,   236,   236,  -456,  2344,  2471,  2471,  2471,
    2471,  2471,  2471,  2471,  2471,  2471,  2471,  2471,  -456,  -456,
    2471,   219,   282,   260,   297,   296,  -456,  -456,   461,  -456,
     -39,  -456,  -456,  -456,  -456,  1170,  -456,   274,   175,  -456,
    -456,  2471,  -456,  2471,  -456,  -456,     6,  -456,    97,   279,
     291,   298,   301,   316,   317,   319,   320,   321,   322,   326,
     327,   328,   330,   331,   332,   333,   335,   336,   337,   338,
      25,    25,     5,     5,     5,   193,   193,   402,   402,    86,
      86,    86,    86,   168,  2290,  1188,  2253,   725,  -456,  -456,
    -456,    16,  2215,  2215,  2215,  2215,  2215,  2215,  2215,  2215,
    2215,  2215,  2215,  2215,   461,  2397,  -456,    12,  -456,     7,
    -456,   197,   306,   306,   341,   243,  -456,   296,   340,  -456,
    -456,  -456,  -456,  -456,  2471,    92,    80,  -456,  -456,  -456,
     236,  -456,   461,   461,   236,  -456,  -456,  -456,  2471,  2418,
    2471,  2471,  2471,   342,  2471,  2471,   343,  2471,  2471,  2471,
    2471,  2471,  2471,  2471,  2471,  2471,  2471,  2471,  2471,  -456,
    -456,  -456,    55,   282,  -456,   315,    95,   385,   306,   200,
     109,   228,   347,   237,  -456,  -456,   582,  -456,    92,  -456,
     390,  -456,  -456,  -456,  1013,  -456,  1287,  1351,  1399,  1447,
    -456,  1495,  1543,  -456,  1591,  1639,  1687,  1735,  1783,  1831,
    1879,  1927,  1975,  2023,  2071,  2215,  -456,  -456,   236,   236,
     323,  -456,   229,  -456,   236,   287,   236,   287,   392,  -456,
    -456,  -456,   348,  -456,  -456,  -456,  -456,  -456,  -456,  -456,
    -456,  -456,  -456,  -456,  -456,  -456,  -456,  -456,  -456,  -456,
    -456,   196,   395,   236,   236,   287,     8,  -456,  -456,  -456,
     353,   287,  -456,   394,   100,   355,  -456,   226,    92,  -456,
    -456,   196,   222,   358,   287,  -456,  -456,    -2,   287,  -456,
     111,  -456,  -456,  -456,   287,  -456,   359,  -456,     9,  -456,
    -456,  -456,     3,  1102,    -2,  -456,  -456,  -456,  -456,  -456,
    -456,     9,  -456,   404,   362,  -456,  -456,   363,  -456,     9,
     407,   200,   369,    13,   372,   373,   374,   379,   382,   383,
     384,   387,   389,   398,   401,   419,   421,   422,   428,   431,
     438,   445,   446,   448,   449,   451,  -456,  -456,   429,   110,
    -456,  -456,   434,   454,   453,    17,   200,   236,    29,   236,
     236,   236,   391,   236,   236,   456,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   122,
    2471,  -456,   457,   246,    41,   495,   116,   459,   119,   437,
     127,   134,   144,   145,   439,   150,   151,   441,   160,   163,
     169,   171,   195,   202,   204,   205,   210,   211,   213,   215,
     216,  2471,  -456,  2119,   246,   254,   283,   464,   442,   220,
     105,  -456,   196,   495,    43,   447,   236,   450,   452,   455,
     460,   236,   462,   463,   236,   465,   467,   468,   469,   470,
     471,   472,   473,   474,   481,   484,   498,   500,  2167,  -456,
     283,  -456,  -456,   257,   476,   475,   259,   236,   501,  -456,
    -456,   478,  -456,   196,   502,   221,   236,   196,   236,   236,
     236,   236,   196,   236,   236,   196,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,  -456,
     482,  -456,  -456,  -456,   271,  -456,  -456,   196,   236,  2450,
    -456,   236,   503,   196,  -456,   196,   196,   196,   196,  -456,
     196,   196,  -456,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   196,  -456,  -456,  -456,  -456,
     196,  -456,   223,   196,   236,  -456,  -456,  -456,  -456,  -456,
    -456,  -456,  -456,  -456,  -456,  -456,  -456,  -456,  -456,  -456,
    -456,  -456,  -456,  -456,  -456,  -456,  -456,  -456,   196,  -456
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,    23,     4,    25,     1,
     195,   196,   193,   194,   123,     0,     0,     0,     0,     0,
       0,   186,   187,   197,   198,   199,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       8,     9,     0,   118,     0,   127,   188,   126,     7,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,     2,    24,   118,   128,   129,   183,   182,
       0,     0,   118,    27,    21,     0,   246,     0,   231,     0,
       0,     0,     0,   228,   229,     0,     0,     0,     0,   239,
       0,     0,     0,   189,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   202,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   189,   125,
       0,     0,     0,     0,     0,    19,    10,   230,     0,   241,
     220,   244,   245,   227,   243,     0,   200,     0,   233,   234,
     232,     0,   238,     0,   217,   124,     0,   120,   118,   118,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     130,   131,   132,   133,   134,   157,   158,   136,   137,   153,
     154,   155,   156,   138,   141,   135,   140,   139,   181,   180,
     192,     0,   116,   142,   143,   144,   145,   146,   147,   148,
     149,   151,   152,   150,     0,     0,    31,     0,    29,     0,
      22,     0,     0,     0,     0,     0,    17,    20,     0,    13,
      14,    16,    15,   240,     0,     0,   222,   224,   242,   201,
       0,   235,     0,     0,     0,   119,   122,   190,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   191,
     219,   185,     0,     0,    28,     0,     0,     0,     0,    27,
       0,     0,     0,     0,    18,    11,     0,   221,     0,   225,
       0,   237,   218,   121,     0,   179,     0,     0,     0,     0,
     177,     0,     0,   178,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   117,   184,    30,     0,     0,
       0,   114,     0,    26,     0,    40,     0,    40,     0,    12,
     226,   223,     0,   159,   160,   161,   162,   163,   174,   175,
     168,   169,   164,   165,   166,   167,   171,   173,   170,   172,
     176,     0,     0,     0,     0,    40,     0,   109,   110,   111,
       0,    41,    42,     0,     0,     0,   112,     0,     0,    61,
     115,     0,     0,     0,    40,    38,    43,     0,    40,    34,
       0,    36,   236,    60,    40,    32,     0,   108,     0,   107,
     105,   106,     0,     0,    44,    45,    47,    48,    49,    50,
      51,     0,   103,     0,     0,   113,    37,     0,    39,     0,
       0,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    46,   104,     0,     0,
      35,    33,     0,     0,     0,     0,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    90,     0,     0,     0,    58,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,     0,     0,     0,     0,     0,     0,     0,
       0,    59,     0,    58,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    92,
       0,    93,    94,     0,     0,     0,     0,     0,     0,    57,
      56,     0,    53,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    91,
       0,    97,    98,   102,     0,    95,    96,     0,     0,     0,
      52,     0,     0,     0,    86,     0,     0,     0,     0,    84,
       0,     0,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   101,    99,   100,    65,
       0,    55,     0,     0,     0,    66,    67,    68,    69,    70,
      81,    82,    75,    76,    71,    72,    73,    74,    78,    80,
      77,    79,    83,    88,    87,    64,    54,    63,     0,    62
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -456,  -456,  -456,   508,  -456,   241,   304,  -456,  -456,   309,
    -456,   532,  -217,  -276,  -456,   269,  -456,  -456,  -456,  -456,
    -288,  -456,   225,  -456,   188,  -456,  -456,  -456,    70,  -456,
    -456,  -456,  -456,    83,    44,  -456,  -361,  -379,  -455,  -456,
    2092,  -213,   -61,  -180,   113,    -3,   677,  -456,  -456,  -456,
    -456,   -31,  -456,  -456,  -456,  -456,  -456,   356,  -456,  -456,
    -456,  -456,  -456,  -456,  -456,   443,  -456,  -456,  -456,  -456,
      -7,  -313,   -25
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    39,    40,   136,   226,   227,   228,    75,
       5,     6,   280,   133,   217,   218,   229,   230,   231,   232,
     360,   361,   362,   394,   395,   396,   511,   551,   512,    41,
     397,   398,   399,   506,   544,   400,   401,   402,   363,   367,
     276,   201,    93,   156,   277,    65,    44,    45,    46,    47,
     145,    48,    49,    50,    51,    52,   236,   237,    53,    54,
      55,    56,    57,    58,   148,   149,    59,    60,    61,    62,
     142,   143,    78
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,    43,   272,   323,   128,    14,   281,    89,    83,    84,
     411,   131,     7,    94,    14,   244,    14,   244,   507,   115,
     446,   273,   437,    72,    14,   268,   153,   409,    86,     2,
     437,   413,   387,    94,   437,    43,    14,   387,   369,   365,
      97,    98,    99,   387,   234,   235,   154,   387,    14,   507,
      14,   545,   137,     8,   146,   139,   388,   374,   383,   275,
     245,   322,   150,   152,   268,   389,   274,   373,   269,   475,
     389,   113,   390,   391,   140,   392,   389,   390,   391,   412,
     389,   479,    43,   390,   391,   545,   386,   390,   391,   158,
     404,   113,   393,   508,    94,   554,   407,   246,   247,    95,
      96,    97,    98,    99,   319,   100,   101,   316,    91,   244,
     158,   158,    76,   233,   239,    94,    42,    42,   405,   324,
      95,    96,    97,    98,    99,   319,   100,   101,   319,   102,
     103,   104,   105,   106,   107,   444,   319,   108,   109,   110,
     111,    85,    43,   319,   356,   470,   364,   320,    71,   378,
      92,    42,   113,   319,   319,   112,    85,   501,   325,   319,
     319,   406,   141,   234,   288,   471,   549,   550,   513,   319,
     477,   515,   319,   113,   372,   116,    94,   502,   319,   517,
     319,    95,    96,    97,    98,    99,   518,   100,   101,   270,
     102,   103,   104,   105,   106,   107,   519,   520,    42,   552,
     114,    94,   522,   523,   319,   157,    95,    96,    97,    98,
      99,   319,   525,   319,   319,   526,   158,   291,   292,   319,
     319,   527,   319,   528,   319,   319,   198,   199,   287,   319,
     319,   244,   268,   130,   113,   380,    79,   158,   326,   354,
     590,   158,    80,    14,   594,    85,    73,   529,   134,   599,
      74,   141,   602,   132,   530,    90,   531,   532,    42,   113,
     155,   114,   533,   534,   147,   535,   278,   536,   537,  -122,
     215,   384,   548,   592,   619,   646,   381,   327,   355,   330,
     625,   331,   626,   627,   628,   629,   135,   630,   631,   216,
     632,   633,   634,   635,   636,   637,   638,   639,   640,   641,
     642,   643,   644,    85,   220,   505,    85,   645,    85,   541,
     647,   219,   581,   279,   585,   158,   158,   357,   358,   359,
      85,   158,    94,   158,   151,   240,   617,    95,    96,    97,
      98,    99,    92,   100,   101,   649,   102,   103,   104,   105,
     106,   107,   248,   543,   108,   109,   110,   111,   282,   249,
     158,   158,   250,   290,   357,   358,   359,   293,   357,   358,
     359,   382,   112,   221,   222,   223,   224,   251,   252,    76,
     253,   254,   255,   256,   158,   225,   622,   257,   258,   259,
     113,   260,   261,   262,   263,   158,   264,   265,   266,   267,
     285,   158,   321,   318,   300,   303,   328,   332,   158,   366,
     368,   353,   370,   375,   377,   379,   158,   114,   385,   408,
      94,   439,   440,   441,   443,    95,    96,    97,    98,    99,
     445,   100,   101,   447,   448,   449,   104,   105,   106,   107,
     450,   351,   352,   451,   452,   453,   469,   157,   454,   157,
     455,   472,   158,   484,   158,   158,   158,   158,   158,   456,
     158,   158,   457,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   371,   157,   113,    94,
     458,   158,   459,   460,    95,    96,    97,    98,    99,   461,
     100,   101,   462,   102,   103,   104,   105,   106,   107,   463,
     403,   108,   109,   110,   111,   114,   464,   465,   542,   466,
     467,   410,   468,   473,   474,   510,   504,   403,   487,   112,
     514,   158,    63,   158,   438,   516,    76,   521,   158,   524,
     547,   158,   442,   546,   329,   556,   583,   113,   558,   589,
     559,   284,   616,   560,   283,   584,   582,    64,   561,   586,
     563,   564,   317,   566,   158,   567,   568,   569,   570,   571,
     572,   573,   574,   158,   114,   158,   158,   158,   158,   575,
     158,   158,   576,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   577,   618,   578,   588,
     591,   624,   436,   553,   580,   158,   376,   540,   158,     0,
      94,   241,   289,     0,     0,    95,    96,    97,    98,    99,
       0,   100,   101,     0,   102,   103,   104,   105,   106,   107,
       0,     0,   108,   109,   110,   111,     0,     0,     0,     0,
       0,   158,     0,     0,     0,     0,     0,     0,     0,   557,
     112,    85,     0,     0,   562,     0,     0,   565,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     587,     0,     0,     0,     0,     0,     0,     0,     0,   593,
       0,   595,   596,   597,   598,   114,   600,   601,     0,   603,
     604,   605,   606,   607,   608,   609,   610,   611,   612,   613,
     614,   615,    66,    67,    68,    69,    70,     0,     0,     0,
       0,   620,     0,     0,   623,     0,    77,     0,    81,    82,
       0,     0,     0,    87,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    94,     0,     0,     0,   648,    95,    96,
      97,    98,    99,     0,   100,   101,     0,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   138,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
       0,   113,     0,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,     0,     0,   214,     9,     0,
       0,    10,    11,    12,    13,    14,     0,     0,   114,     0,
       0,    15,    16,     0,     0,     0,    17,     0,   242,    18,
     243,     0,     0,     0,     0,     0,     0,     0,     0,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,     0,
     100,   101,     0,   102,   103,   104,   105,   106,   107,    19,
       0,   108,   109,   110,   111,    20,     0,     0,     0,    21,
      22,    23,    24,    25,     0,     0,     0,     0,     0,   112,
       0,     0,     0,   129,    26,    27,     0,    28,    29,    30,
      31,     0,   202,    32,    33,    34,    35,   113,    36,    37,
      38,     1,     0,    -5,    -5,    -5,    -5,    -5,     0,     0,
       0,   286,     0,    -5,    -5,     0,     0,     0,    -5,     0,
       0,    -5,     0,     0,   114,   294,   296,   297,   298,   299,
       0,   301,   302,     0,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,     0,     0,     0,     0,
       0,    -5,     0,     0,     0,     0,     2,    -5,     0,     0,
       0,    -5,    -5,    -5,    -5,    -5,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    -5,    -5,     0,    -5,
      -5,    -5,    -5,     0,     0,    -5,    -5,    -5,    -5,     0,
      -5,    -5,    -5,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,    15,    16,     0,     0,     0,    17,     0,
       0,    18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,     0,     0,     0,     0,    95,    96,    97,    98,
      99,     0,   100,   101,     0,   102,   103,   104,   105,   106,
     107,    19,     0,   108,   109,   110,   111,    20,     0,     0,
       0,    21,    22,    23,    24,    25,     0,     0,     0,     0,
       0,   112,     0,     0,     0,   333,    26,    27,     0,    28,
      29,    30,    31,     0,     0,    32,    33,    34,    35,   113,
      36,    37,    38,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,    15,    16,     0,     0,     0,    17,     0,
       0,    18,     0,     0,     0,     0,   114,     0,     0,     0,
       0,     0,     0,     0,     0,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
     144,    19,   429,   430,   431,   432,     0,    20,     0,     0,
       0,    21,    22,    23,    24,    25,     0,   503,     0,     0,
     433,     0,     0,     0,     0,     0,    26,     0,     0,     0,
      29,    30,    31,     0,     0,    32,    33,    34,    35,     0,
      36,    37,    38,    10,    11,    12,    13,    14,   538,     0,
       0,     0,     0,    15,    16,     0,     0,     0,    17,     0,
       0,    18,     0,     0,     0,     0,    94,     0,     0,   434,
     435,    95,    96,    97,    98,    99,     0,   100,   101,     0,
     102,   103,   104,   105,   106,   107,     0,     0,   108,     0,
     238,    19,     0,     0,     0,     0,     0,    20,     0,     0,
       0,    21,    22,    23,    24,    25,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,     0,     0,     0,
      29,    30,    31,     0,   113,    32,    33,    34,    35,     0,
      36,    37,    38,     0,     0,     0,   202,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,    15,    16,     0,
       0,   114,    17,     0,     0,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
      95,    96,    97,    98,    99,     0,   100,   101,     0,   102,
     103,   104,   105,   106,   107,    19,     0,   108,   109,   110,
     111,    20,     0,     0,     0,    21,    22,    23,    24,    25,
       0,     0,     0,     0,     0,   112,     0,     0,     0,   334,
      26,     0,     0,     0,    29,    30,    31,     0,     0,    32,
      33,    34,    35,   113,    36,    37,    38,     0,     0,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,     0,
     100,   101,     0,   102,   103,   104,   105,   106,   107,     0,
     114,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
       0,     0,     0,   335,     0,     0,     0,    94,     0,     0,
       0,     0,    95,    96,    97,    98,    99,   113,   100,   101,
       0,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   114,     0,     0,   112,     0,     0,
       0,   336,     0,     0,     0,    94,     0,     0,     0,     0,
      95,    96,    97,    98,    99,   113,   100,   101,     0,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   114,     0,     0,   112,     0,     0,     0,   337,
       0,     0,     0,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,   113,   100,   101,     0,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     114,     0,     0,   112,     0,     0,     0,   338,     0,     0,
       0,    94,     0,     0,     0,     0,    95,    96,    97,    98,
      99,   113,   100,   101,     0,   102,   103,   104,   105,   106,
     107,     0,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   114,     0,
       0,   112,     0,     0,     0,   339,     0,     0,     0,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,   113,
     100,   101,     0,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   114,     0,     0,   112,
       0,     0,     0,   340,     0,     0,     0,    94,     0,     0,
       0,     0,    95,    96,    97,    98,    99,   113,   100,   101,
       0,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   114,     0,     0,   112,     0,     0,
       0,   341,     0,     0,     0,    94,     0,     0,     0,     0,
      95,    96,    97,    98,    99,   113,   100,   101,     0,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   114,     0,     0,   112,     0,     0,     0,   342,
       0,     0,     0,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,   113,   100,   101,     0,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     114,     0,     0,   112,     0,     0,     0,   343,     0,     0,
       0,    94,     0,     0,     0,     0,    95,    96,    97,    98,
      99,   113,   100,   101,     0,   102,   103,   104,   105,   106,
     107,     0,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   114,     0,
       0,   112,     0,     0,     0,   344,     0,     0,     0,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,   113,
     100,   101,     0,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   114,     0,     0,   112,
       0,     0,     0,   345,     0,     0,     0,    94,     0,     0,
       0,     0,    95,    96,    97,    98,    99,   113,   100,   101,
       0,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   114,     0,     0,   112,     0,     0,
       0,   346,     0,     0,     0,    94,     0,     0,     0,     0,
      95,    96,    97,    98,    99,   113,   100,   101,     0,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   114,     0,     0,   112,     0,     0,     0,   347,
       0,     0,     0,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,   113,   100,   101,     0,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     114,     0,     0,   112,     0,     0,     0,   348,     0,     0,
       0,    94,     0,     0,     0,     0,    95,    96,    97,    98,
      99,   113,   100,   101,     0,   102,   103,   104,   105,   106,
     107,     0,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   114,     0,
       0,   112,     0,     0,     0,   349,     0,     0,     0,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,   113,
     100,   101,     0,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   114,     0,     0,   112,
       0,     0,     0,   350,     0,     0,     0,    94,     0,     0,
       0,     0,    95,    96,    97,    98,    99,   113,   100,   101,
       0,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   114,     0,     0,   112,     0,     0,
       0,     0,     0,     0,   539,    94,     0,     0,     0,     0,
      95,    96,    97,    98,    99,   113,   100,   101,     0,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   114,     0,     0,   112,     0,     0,     0,     0,
       0,     0,   579,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,   113,   100,   101,     0,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     114,    94,     0,   112,     0,     0,    95,    96,    97,    98,
      99,     0,   100,   101,     0,   102,   103,   104,   105,   106,
     107,   113,     0,   108,   109,   110,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,     0,
       0,   112,     0,    95,    96,    97,    98,    99,   114,   100,
     101,     0,   102,   103,   104,   105,   106,   107,     0,   113,
     108,     0,   110,     0,     0,     0,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,    15,    16,   112,     0,
       0,    17,     0,     0,    18,     0,   114,    10,    11,    12,
      13,    14,     0,     0,     0,     0,   113,    15,    16,     0,
       0,     0,    17,     0,     0,    18,     0,     0,     0,     0,
       0,     0,     0,     0,    19,     0,     0,     0,    76,     0,
       0,     0,     0,   114,    21,    22,    23,    24,    25,     0,
       0,     0,     0,     0,     0,    19,   200,     0,     0,    26,
      10,    11,    12,    13,    14,    21,    22,    23,    24,    25,
      15,    16,     0,     0,     0,    17,     0,     0,    18,     0,
      26,    10,    11,    12,    13,    14,     0,     0,     0,     0,
       0,    15,    16,     0,     0,     0,    17,     0,     0,    18,
       0,     0,     0,     0,     0,     0,     0,     0,    19,   271,
       0,     0,     0,    10,    11,    12,    13,    14,    21,    22,
      23,    24,    25,    15,    16,     0,     0,     0,    17,    19,
     295,    18,     0,    26,    10,    11,    12,    13,    14,    21,
      22,    23,    24,    25,    15,    16,     0,     0,     0,    17,
       0,     0,    18,     0,    26,     0,     0,     0,     0,     0,
       0,    19,   621,     0,     0,     0,     0,     0,     0,     0,
       0,    21,    22,    23,    24,    25,     0,     0,     0,     0,
       0,     0,    19,     0,     0,     0,    26,     0,     0,     0,
       0,     0,    21,    22,    23,    24,    25,   476,     0,   478,
     480,   481,   482,   483,     0,   485,   486,    26,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   159,     0,     0,     0,     0,   509,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,     0,     0,   175,   176,   177,   178,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   179,     0,     0,     0,   555
};

static const yytype_int16 yycheck[] =
{
       3,     4,   215,   279,    65,     7,   223,    38,    33,    34,
       7,    72,   106,     8,     7,     9,     7,     9,   473,    44,
       7,     9,   401,    26,     7,     9,    35,   388,    35,    56,
     409,   392,    34,     8,   413,    38,     7,    34,   351,   327,
      15,    16,    17,    34,    83,    84,    55,    34,     7,   504,
       7,   506,    77,     4,    85,    80,    58,    49,   371,    52,
      54,   278,    87,    88,     9,    67,    54,   355,    52,    52,
      67,    66,    74,    75,    81,    77,    67,    74,    75,    76,
      67,    52,    85,    74,    75,   540,   374,    74,    75,    92,
     378,    66,    94,    52,     8,    52,   384,   158,   159,    13,
      14,    15,    16,    17,     9,    19,    20,    52,    11,     9,
     113,   114,    55,   138,   145,     8,     3,     4,     7,    10,
      13,    14,    15,    16,    17,     9,    19,    20,     9,    22,
      23,    24,    25,    26,    27,   411,     9,    30,    31,    32,
      33,    49,   145,     9,   324,    35,   326,    52,     7,    49,
      53,    38,    66,     9,     9,    48,    49,    35,    49,     9,
       9,    50,    55,    83,    84,    55,    61,    62,    52,     9,
     446,    52,     9,    66,   354,    51,     8,    55,     9,    52,
       9,    13,    14,    15,    16,    17,    52,    19,    20,   214,
      22,    23,    24,    25,    26,    27,    52,    52,    85,   512,
      93,     8,    52,    52,     9,    92,    13,    14,    15,    16,
      17,     9,    52,     9,     9,    52,   219,   242,   243,     9,
       9,    52,     9,    52,     9,     9,   113,   114,   235,     9,
       9,     9,     9,    35,    66,     9,    80,   240,    10,    10,
     553,   244,    86,     7,   557,    49,     7,    52,    11,   562,
       7,    55,   565,    53,    52,     7,    52,    52,   145,    66,
       7,    93,    52,    52,    89,    52,    69,    52,    52,     7,
      51,    49,    52,    52,   587,    52,    50,    49,    49,   286,
     593,   288,   595,   596,   597,   598,    49,   600,   601,     7,
     603,   604,   605,   606,   607,   608,   609,   610,   611,   612,
     613,   614,   615,    49,     7,    59,    49,   620,    49,    55,
     623,    51,    55,     7,    55,   318,   319,    71,    72,    73,
      49,   324,     8,   326,    10,    51,    55,    13,    14,    15,
      16,    17,    53,    19,    20,   648,    22,    23,    24,    25,
      26,    27,    51,    60,    30,    31,    32,    33,     7,    51,
     353,   354,    51,   240,    71,    72,    73,   244,    71,    72,
      73,   368,    48,    67,    68,    69,    70,    51,    51,    55,
      51,    51,    51,    51,   377,    79,   589,    51,    51,    51,
      66,    51,    51,    51,    51,   388,    51,    51,    51,    51,
      50,   394,     7,    78,    52,    52,    49,     7,   401,     7,
      52,    78,     7,    50,    10,    50,   409,    93,    50,    50,
       8,     7,    50,    50,     7,    13,    14,    15,    16,    17,
      51,    19,    20,    51,    51,    51,    24,    25,    26,    27,
      51,   318,   319,    51,    51,    51,     7,   324,    51,   326,
      51,     7,   445,    52,   447,   448,   449,   450,   451,    51,
     453,   454,    51,   456,   457,   458,   459,   460,   461,   462,
     463,   464,   465,   466,   467,   468,   353,   354,    66,     8,
      51,   474,    51,    51,    13,    14,    15,    16,    17,    51,
      19,    20,    51,    22,    23,    24,    25,    26,    27,    51,
     377,    30,    31,    32,    33,    93,    51,    51,   505,    51,
      51,   388,    51,    49,    51,    10,    49,   394,    52,    48,
      51,   514,     4,   516,   401,    78,    55,    78,   521,    78,
      78,   524,   409,    59,   283,    78,    50,    66,    78,    51,
      78,   227,    50,    78,   225,    60,   543,     5,    78,   546,
      78,    78,   273,    78,   547,    78,    78,    78,    78,    78,
      78,    78,    78,   556,    93,   558,   559,   560,   561,    78,
     563,   564,    78,   566,   567,   568,   569,   570,   571,   572,
     573,   574,   575,   576,   577,   578,    78,   584,    78,    78,
      78,    78,   394,   513,   540,   588,   361,   504,   591,    -1,
       8,   148,   236,    -1,    -1,    13,    14,    15,    16,    17,
      -1,    19,    20,    -1,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,
      -1,   624,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   516,
      48,    49,    -1,    -1,   521,    -1,    -1,   524,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
     547,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   556,
      -1,   558,   559,   560,   561,    93,   563,   564,    -1,   566,
     567,   568,   569,   570,   571,   572,   573,   574,   575,   576,
     577,   578,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,   588,    -1,    -1,   591,    -1,    29,    -1,    31,    32,
      -1,    -1,    -1,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     8,    -1,    -1,    -1,   624,    13,    14,
      15,    16,    17,    -1,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    79,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
      -1,    66,    -1,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,    -1,    -1,   130,     0,    -1,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    93,    -1,
      -1,    13,    14,    -1,    -1,    -1,    18,    -1,   151,    21,
     153,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    51,
      -1,    30,    31,    32,    33,    57,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    52,    76,    77,    -1,    79,    80,    81,
      82,    -1,   215,    85,    86,    87,    88,    66,    90,    91,
      92,     1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,   234,    -1,    13,    14,    -1,    -1,    -1,    18,    -1,
      -1,    21,    -1,    -1,    93,   248,   249,   250,   251,   252,
      -1,   254,   255,    -1,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    56,    57,    -1,    -1,
      -1,    61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    79,
      80,    81,    82,    -1,    -1,    85,    86,    87,    88,    -1,
      90,    91,    92,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    13,    14,    -1,    -1,    -1,    18,    -1,
      -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    -1,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    51,    -1,    30,    31,    32,    33,    57,    -1,    -1,
      -1,    61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    52,    76,    77,    -1,    79,
      80,    81,    82,    -1,    -1,    85,    86,    87,    88,    66,
      90,    91,    92,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    13,    14,    -1,    -1,    -1,    18,    -1,
      -1,    21,    -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      50,    51,    30,    31,    32,    33,    -1,    57,    -1,    -1,
      -1,    61,    62,    63,    64,    65,    -1,   470,    -1,    -1,
      48,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      80,    81,    82,    -1,    -1,    85,    86,    87,    88,    -1,
      90,    91,    92,     3,     4,     5,     6,     7,   501,    -1,
      -1,    -1,    -1,    13,    14,    -1,    -1,    -1,    18,    -1,
      -1,    21,    -1,    -1,    -1,    -1,     8,    -1,    -1,    97,
      98,    13,    14,    15,    16,    17,    -1,    19,    20,    -1,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    -1,
      50,    51,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    61,    62,    63,    64,    65,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      80,    81,    82,    -1,    66,    85,    86,    87,    88,    -1,
      90,    91,    92,    -1,    -1,    -1,   589,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,    -1,
      -1,    93,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    -1,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    51,    -1,    30,    31,    32,
      33,    57,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    52,
      76,    -1,    -1,    -1,    80,    81,    82,    -1,    -1,    85,
      86,    87,    88,    66,    90,    91,    92,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      93,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    52,    -1,    -1,    -1,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    66,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    48,    -1,    -1,
      -1,    52,    -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    66,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    -1,    -1,    48,    -1,    -1,    -1,    52,
      -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    66,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      93,    -1,    -1,    48,    -1,    -1,    -1,    52,    -1,    -1,
      -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    66,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,
      -1,    48,    -1,    -1,    -1,    52,    -1,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    66,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,    48,
      -1,    -1,    -1,    52,    -1,    -1,    -1,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    66,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    48,    -1,    -1,
      -1,    52,    -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    66,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    -1,    -1,    48,    -1,    -1,    -1,    52,
      -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    66,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      93,    -1,    -1,    48,    -1,    -1,    -1,    52,    -1,    -1,
      -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    66,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,
      -1,    48,    -1,    -1,    -1,    52,    -1,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    66,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,    48,
      -1,    -1,    -1,    52,    -1,    -1,    -1,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    66,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    48,    -1,    -1,
      -1,    52,    -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    66,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    -1,    -1,    48,    -1,    -1,    -1,    52,
      -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    66,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      93,    -1,    -1,    48,    -1,    -1,    -1,    52,    -1,    -1,
      -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    66,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,
      -1,    48,    -1,    -1,    -1,    52,    -1,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    66,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,    48,
      -1,    -1,    -1,    52,    -1,    -1,    -1,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    66,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    55,     8,    -1,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    66,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    55,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    66,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      93,     8,    -1,    48,    -1,    -1,    13,    14,    15,    16,
      17,    -1,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    66,    -1,    30,    31,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,
      -1,    48,    -1,    13,    14,    15,    16,    17,    93,    19,
      20,    -1,    22,    23,    24,    25,    26,    27,    -1,    66,
      30,    -1,    32,    -1,    -1,    -1,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    13,    14,    48,    -1,
      -1,    18,    -1,    -1,    21,    -1,    93,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    66,    13,    14,    -1,
      -1,    -1,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    93,    61,    62,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    76,
       3,     4,     5,     6,     7,    61,    62,    63,    64,    65,
      13,    14,    -1,    -1,    -1,    18,    -1,    -1,    21,    -1,
      76,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      -1,    13,    14,    -1,    -1,    -1,    18,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,
      -1,    -1,    -1,     3,     4,     5,     6,     7,    61,    62,
      63,    64,    65,    13,    14,    -1,    -1,    -1,    18,    51,
      52,    21,    -1,    76,     3,     4,     5,     6,     7,    61,
      62,    63,    64,    65,    13,    14,    -1,    -1,    -1,    18,
      -1,    -1,    21,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    61,    62,    63,    64,    65,   445,    -1,   447,
     448,   449,   450,   451,    -1,   453,   454,    76,   456,   457,
     458,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     468,     7,    -1,    -1,    -1,    -1,   474,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    -1,    -1,   514
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    56,   108,   109,   117,   118,   106,     4,     0,
       3,     4,     5,     6,     7,    13,    14,    18,    21,    51,
      57,    61,    62,    63,    64,    65,    76,    77,    79,    80,
      81,    82,    85,    86,    87,    88,    90,    91,    92,   110,
     111,   136,   151,   152,   153,   154,   155,   156,   158,   159,
     160,   161,   162,   165,   166,   167,   168,   169,   170,   173,
     174,   175,   176,   110,   118,   152,   153,   153,   153,   153,
     153,     7,   152,     7,     7,   116,    55,   153,   179,    80,
      86,   153,   153,   179,   179,    49,   177,   153,   153,   158,
       7,    11,    53,   149,     8,    13,    14,    15,    16,    17,
      19,    20,    22,    23,    24,    25,    26,    27,    30,    31,
      32,    33,    48,    66,    93,   179,    51,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,   149,    52,
      35,   149,    53,   120,    11,    49,   112,   179,   153,   179,
     177,    55,   177,   178,    50,   157,   158,    89,   171,   172,
     179,    10,   179,    35,    55,     7,   150,   151,   152,     7,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    30,    31,    32,    33,    48,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   151,   151,
      52,   148,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,    51,     7,   121,   122,    51,
       7,    67,    68,    69,    70,    79,   113,   114,   115,   123,
     124,   125,   126,   179,    83,    84,   163,   164,    50,   158,
      51,   172,   153,   153,     9,    54,   149,   149,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,     9,    52,
     179,    52,   148,     9,    54,    52,   147,   151,    69,     7,
     119,   119,     7,   116,   113,    50,   153,   177,    84,   164,
     151,   179,   179,   151,   153,    52,   153,   153,   153,   153,
      52,   153,   153,    52,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,    52,   122,    78,     9,
      52,     7,   119,   120,    10,    49,    10,    49,    49,   112,
     177,   177,     7,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,   151,   151,    78,    10,    49,   150,    71,    72,    73,
     127,   128,   129,   145,   150,   127,     7,   146,    52,   178,
       7,   151,   150,   127,    49,    50,   129,    10,    49,    50,
       9,    50,   177,   178,    49,    50,   127,    34,    58,    67,
      74,    75,    77,    94,   130,   131,   132,   137,   138,   139,
     142,   143,   144,   151,   127,     7,    50,   127,    50,   143,
     151,     7,    76,   143,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    30,
      31,    32,    33,    48,    97,    98,   131,   144,   151,     7,
      50,    50,   151,     7,   120,    51,     7,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,     7,
      35,    55,     7,    49,    51,    52,   147,   120,   147,    52,
     147,   147,   147,   147,    52,   147,   147,    52,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,    35,    55,   153,    49,    59,   140,   145,    52,   147,
      10,   133,   135,    52,    51,    52,    78,    52,    52,    52,
      52,    78,    52,    52,    78,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,   153,    55,
     140,    55,   177,    60,   141,   145,    59,    78,    52,    61,
      62,   134,   178,   135,    52,   147,    78,   151,    78,    78,
      78,    78,   151,    78,    78,   151,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    55,
     141,    55,   177,    50,    60,    55,   177,   151,    78,    51,
     178,    78,    52,   151,   178,   151,   151,   151,   151,   178,
     151,   151,   178,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,    50,    55,   177,   178,
     151,    52,   148,   151,    78,   178,   178,   178,   178,   178,
     178,   178,   178,   178,   178,   178,   178,   178,   178,   178,
     178,   178,   178,   178,   178,   178,    52,   178,   151,   178
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   107,   108,   108,   108,   109,   109,   110,   110,   110,
     111,   112,   113,   113,   113,   113,   113,   114,   114,   115,
     115,   116,   116,   117,   117,   118,   119,   120,   120,   121,
     121,   122,   123,   123,   124,   124,   125,   125,   126,   126,
     127,   127,   128,   128,   129,   130,   130,   131,   131,   131,
     131,   131,   132,   132,   133,   133,   134,   134,   135,   135,
     136,   136,   137,   137,   137,   137,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   139,
     139,   139,   139,   140,   140,   140,   140,   141,   141,   141,
     141,   142,   142,   143,   143,   144,   144,   144,   144,   145,
     145,   145,   146,   146,   147,   147,   148,   148,   149,   149,
     150,   150,   151,   152,   152,   153,   153,   153,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   155,
     155,   155,   155,   156,   156,   156,   156,   156,   156,   156,
     157,   157,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   159,   160,   161,
     162,   162,   162,   162,   163,   163,   164,   165,   166,   167,
     168,   168,   169,   170,   171,   171,   172,   173,   173,   174,
     175,   176,   177,   177,   178,   178,   179
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
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     5,     5,
       3,     5,     4,     6,     1,     2,     3,     3,     2,     2,
       3,     2,     3,     3,     1,     2,     6,     5,     3,     2,
       4,     3,     3,     2,     1,     1,     1
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
#line 2286 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 6:
#line 158 "beacon.y" /* yacc.c:1663  */
    {
		CompileEntryAST((yyvsp[0].ast_value));
	}
#line 2294 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 7:
#line 164 "beacon.y" /* yacc.c:1663  */
    {
		CompileEntryAST((yyvsp[0].ast_value));
	}
#line 2302 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 8:
#line 168 "beacon.y" /* yacc.c:1663  */
    {
		CompileEntryAST((yyvsp[0].ast_value));
	}
#line 2310 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 9:
#line 172 "beacon.y" /* yacc.c:1663  */
    {
		CompileEntryAST((yyvsp[0].ast_value));
	}
#line 2318 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 10:
#line 178 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTNamespaceDecl((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2326 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 11:
#line 185 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 2334 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 12:
#line 192 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTNamespaceNamespaceDecl((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2342 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 17:
#line 203 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 2350 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 18:
#line 207 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTNamespaceMemberDeclList((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2358 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 19:
#line 214 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBlank();
	}
#line 2366 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 21:
#line 222 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTNamespacePath((yyvsp[0].stringv_value));
	}
#line 2374 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 22:
#line 226 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTNamespacePathList((yyvsp[-2].ast_value), (yyvsp[0].stringv_value));
	}
#line 2382 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 24:
#line 234 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTImportDeclList((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2390 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 25:
#line 241 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTImportDecl(NewASTImportPath((yyvsp[0].ast_value)));
	}
#line 2398 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 26:
#line 248 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTParameterizedTypename((yyvsp[-1].stringv_value), (yyvsp[0].ast_value));
	}
#line 2406 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 27:
#line 255 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBlank();
	}
#line 2414 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 28:
#line 259 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 2422 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 29:
#line 266 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 2430 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 30:
#line 270 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTTypeParameterList((yyvsp[0].ast_value), (yyvsp[-2].ast_value));
	}
#line 2438 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 31:
#line 277 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTTypeParameter((yyvsp[0].stringv_value), NewASTBlank());
	}
#line 2446 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 32:
#line 283 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTAbstractClassDecl((yyvsp[-3].ast_value), NewASTBlank(), (yyvsp[-1].ast_value));
	}
#line 2454 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 33:
#line 287 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTAbstractClassDecl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2462 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 34:
#line 293 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTClassDecl((yyvsp[-3].ast_value), NewASTBlank(), (yyvsp[-1].ast_value));
	}
#line 2470 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 35:
#line 297 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTClassDecl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2478 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 36:
#line 304 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTEnumDecl((yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2486 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 37:
#line 308 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTEnumDecl((yyvsp[-4].stringv_value), (yyvsp[-2].ast_value));
	}
#line 2494 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 38:
#line 315 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTInterfaceDecl((yyvsp[-3].ast_value), NewASTBlank(), (yyvsp[-1].ast_value));
	}
#line 2502 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 39:
#line 319 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTInterfaceDecl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2510 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 40:
#line 326 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBlank();
	}
#line 2518 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 43:
#line 335 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTAccessMemberTree((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2526 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 44:
#line 342 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTAccessMemberList((yyvsp[-2].access_level_value), (yyvsp[0].ast_value));
	}
#line 2534 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 45:
#line 349 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTMemberDecl((yyvsp[0].ast_value));
	}
#line 2542 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 46:
#line 353 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTMemberDeclList((yyvsp[-1].ast_value), NewASTMemberDecl((yyvsp[0].ast_value)));
	}
#line 2550 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 52:
#line 368 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTConstructorDecl((yyvsp[-3].ast_value), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2558 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 53:
#line 372 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTConstructorDecl(NewASTBlank(), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2566 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 54:
#line 379 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTConstructorChain((yyvsp[-3].chain_type_value), (yyvsp[-1].ast_value));
	}
#line 2574 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 55:
#line 383 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTConstructorChain((yyvsp[-2].chain_type_value), NewASTBlank());
	}
#line 2582 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 56:
#line 390 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.chain_type_value) = CHAIN_TYPE_SUPER_T;
	}
#line 2590 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 57:
#line 394 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.chain_type_value) = CHAIN_TYPE_THIS_T;
	}
#line 2598 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 58:
#line 401 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBlank();
	}
#line 2606 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 60:
#line 409 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTFunctionDecl((yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2614 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 61:
#line 413 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTFunctionDeclEmptyParams((yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2622 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 62:
#line 420 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTMethodDecl((yyvsp[-8].ast_value), (yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2630 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 63:
#line 424 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTMethodDeclEmptyParams((yyvsp[-7].ast_value), (yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2638 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 64:
#line 428 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTMethodDecl(NewASTModifier(MODIFIER_NONE_T), (yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2646 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 65:
#line 432 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTMethodDeclEmptyParams(NewASTModifier(MODIFIER_NONE_T), (yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2654 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 66:
#line 439 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_ADD_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2662 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 67:
#line 443 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_SUB_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2670 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 68:
#line 447 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_MUL_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2678 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 69:
#line 451 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_DIV_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2686 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 70:
#line 455 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_MOD_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2694 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 71:
#line 459 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_GT_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2702 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 72:
#line 463 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_GE_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2710 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 73:
#line 467 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_LT_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2718 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 74:
#line 471 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_LE_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2726 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 75:
#line 476 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_EQ_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2734 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 76:
#line 480 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_NOT_EQ_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2742 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 77:
#line 485 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_BIT_OR_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2750 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 78:
#line 489 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_BIT_AND_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2758 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 79:
#line 494 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_LOGIC_OR_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2766 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 80:
#line 498 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_LOGIC_AND_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2774 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 81:
#line 503 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_LSHIFT_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2782 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 82:
#line 507 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_RSHIFT_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2790 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 83:
#line 512 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_EXCOR_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2798 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 84:
#line 517 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_NOT_T, NewASTBlank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2806 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 85:
#line 522 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_CHILDA_T, NewASTBlank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2814 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 86:
#line 526 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_NEGATIVE_T, NewASTBlank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2822 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 87:
#line 531 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_SUB_SCRIPT_GET_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2830 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 88:
#line 536 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOperatorOverload(OPERATOR_SUB_SCRIPT_SET_T, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2838 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 89:
#line 543 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTFieldDecl((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[-1].stringv_value), NewASTBlank());
	}
#line 2846 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 90:
#line 547 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTFieldDecl(NewASTModifier(MODIFIER_NONE_T), (yyvsp[-2].ast_value), (yyvsp[-1].stringv_value), NewASTBlank());
	}
#line 2854 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 91:
#line 551 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTFieldDecl((yyvsp[-5].ast_value), (yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2862 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 92:
#line 555 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTFieldDecl(NewASTModifier(MODIFIER_NONE_T), (yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2870 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 93:
#line 562 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTPropSet(NewASTBlank(), NewASTBlank());
	}
#line 2878 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 94:
#line 566 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTPropSet(NewASTBlank(), (yyvsp[0].ast_value));
	}
#line 2886 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 95:
#line 570 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTPropSet(NewASTAccess((yyvsp[-2].access_level_value)), NewASTBlank());
	}
#line 2894 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 96:
#line 574 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTPropSet(NewASTAccess((yyvsp[-2].access_level_value)), NewASTBlank());
	}
#line 2902 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 97:
#line 581 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTPropGet(NewASTBlank(), NewASTBlank());
	}
#line 2910 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 98:
#line 585 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTPropGet(NewASTBlank(), (yyvsp[0].ast_value));
	}
#line 2918 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 99:
#line 589 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTPropGet(NewASTAccess((yyvsp[-2].access_level_value)), NewASTBlank());
	}
#line 2926 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 100:
#line 593 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTPropGet(NewASTAccess((yyvsp[-2].access_level_value)), NewASTBlank());
	}
#line 2934 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 101:
#line 600 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTPropDecl((yyvsp[-6].ast_value), (yyvsp[-5].ast_value), (yyvsp[-4].stringv_value), (yyvsp[-2].ast_value), (yyvsp[-1].ast_value));
	}
#line 2942 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 102:
#line 604 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTPropDecl(NewASTModifier(MODIFIER_NONE_T), (yyvsp[-5].ast_value), (yyvsp[-4].stringv_value), (yyvsp[-2].ast_value), (yyvsp[-1].ast_value));
	}
#line 2950 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 103:
#line 611 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 2958 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 104:
#line 615 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTModifierList((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2966 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 105:
#line 622 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTModifier(MODIFIER_STATIC_T);
	}
#line 2974 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 106:
#line 626 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTModifier(MODIFIER_NATIVE_T);
	}
#line 2982 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 107:
#line 630 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTModifier(MODIFIER_ABSTRACT_T);
	}
#line 2990 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 108:
#line 634 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTModifier(MODIFIER_FINAL_T);
	}
#line 2998 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 109:
#line 641 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = ACCESS_PUBLIC_T;
	}
#line 3006 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 110:
#line 645 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = ACCESS_PRIVATE_T;
	}
#line 3014 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 111:
#line 649 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = ACCESS_PROTECTED_T;
	}
#line 3022 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 112:
#line 656 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTIdentifier((yyvsp[0].stringv_value));
	}
#line 3030 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 113:
#line 660 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTIdentifierList((yyvsp[0].stringv_value), (yyvsp[-2].ast_value));
	}
#line 3038 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 114:
#line 667 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTParameter((yyvsp[-1].ast_value), (yyvsp[0].stringv_value));
	}
#line 3046 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 115:
#line 671 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTParameterList((yyvsp[-1].ast_value), (yyvsp[0].stringv_value), (yyvsp[-3].ast_value));
	}
#line 3054 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 116:
#line 678 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTArgument((yyvsp[0].ast_value));
	}
#line 3062 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 117:
#line 682 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTArgumentList(NewASTArgument((yyvsp[0].ast_value)), (yyvsp[-2].ast_value));
	}
#line 3070 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 118:
#line 689 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBlank();
	}
#line 3078 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 119:
#line 693 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 3086 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 120:
#line 700 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 3094 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 121:
#line 704 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTTypenameList((yyvsp[0].ast_value), (yyvsp[-2].ast_value));
	}
#line 3102 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 122:
#line 711 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTTypename((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3110 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 123:
#line 718 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTFQCN_part((yyvsp[0].stringv_value));
	}
#line 3118 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 124:
#line 722 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTFQCNPartList(NewASTFQCN_part((yyvsp[0].stringv_value)), (yyvsp[-2].ast_value));
	}
#line 3126 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 125:
#line 731 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 3134 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 128:
#line 739 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTUnary(AST_POS_T, (yyvsp[0].ast_value));
	}
#line 3142 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 129:
#line 743 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTUnary(AST_NEG_T, (yyvsp[0].ast_value));
	}
#line 3150 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 130:
#line 747 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_ADD_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3158 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 131:
#line 751 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_SUB_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3166 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 132:
#line 755 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_MUL_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3174 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 133:
#line 759 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_DIV_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3182 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 134:
#line 763 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_MOD_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3190 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 135:
#line 767 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_BIT_OR_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3198 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 136:
#line 771 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_EQUAL_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3206 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 137:
#line 775 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_NOT_TEQUAL_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3214 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 138:
#line 779 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_BIT_AND_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3222 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 139:
#line 783 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_EXC_OR_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3230 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 140:
#line 787 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_LOGIC_OR_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3238 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 141:
#line 791 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_LOGIC_AND_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3246 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 142:
#line 795 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_AS_TSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3254 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 143:
#line 799 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_ADD_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3262 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 144:
#line 803 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_SUB_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3270 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 145:
#line 807 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_MUL_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3278 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 146:
#line 811 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_DIV_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3286 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 147:
#line 815 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_MOD_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3294 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 148:
#line 819 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_AND_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3302 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 149:
#line 823 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_OR_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3310 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 150:
#line 827 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_EXC_OR_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3318 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 151:
#line 831 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_LSHIFT_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3326 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 152:
#line 835 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_RSHIFT_ASSIGN_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3334 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 153:
#line 839 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_GT_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3342 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 154:
#line 843 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_GE_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3350 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 155:
#line 847 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_LT_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3358 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 156:
#line 851 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_LE_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3366 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 157:
#line 855 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_LSHIFT_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3374 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 158:
#line 859 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBinary(AST_RSHIFT_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3382 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 159:
#line 864 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_ADD_T, (yyvsp[-1].ast_value));
	}
#line 3390 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 160:
#line 868 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_SUB_T, (yyvsp[-1].ast_value));
	}
#line 3398 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 161:
#line 872 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_MUL_T, (yyvsp[-1].ast_value));
	}
#line 3406 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 162:
#line 876 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_DIV_T, (yyvsp[-1].ast_value));
	}
#line 3414 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 163:
#line 880 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_MOD_T, (yyvsp[-1].ast_value));
	}
#line 3422 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 164:
#line 884 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_GT_T, (yyvsp[-1].ast_value));
	}
#line 3430 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 165:
#line 888 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_GE_T, (yyvsp[-1].ast_value));
	}
#line 3438 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 166:
#line 892 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_LT_T, (yyvsp[-1].ast_value));
	}
#line 3446 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 167:
#line 896 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_LE_T, (yyvsp[-1].ast_value));
	}
#line 3454 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 168:
#line 900 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_EQ_T, (yyvsp[-1].ast_value));
	}
#line 3462 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 169:
#line 904 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_NOT_EQ_T, (yyvsp[-1].ast_value));
	}
#line 3470 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 170:
#line 908 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_BIT_OR_T, (yyvsp[-1].ast_value));
	}
#line 3478 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 171:
#line 912 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_BIT_AND_T, (yyvsp[-1].ast_value));
	}
#line 3486 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 172:
#line 916 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_LOGIC_OR_T, (yyvsp[-1].ast_value));
	}
#line 3494 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 173:
#line 920 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_LOGIC_AND_T, (yyvsp[-1].ast_value));
	}
#line 3502 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 174:
#line 924 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_LSHIFT_T, (yyvsp[-1].ast_value));
	}
#line 3510 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 175:
#line 928 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_RSHIFT_T, (yyvsp[-1].ast_value));
	}
#line 3518 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 176:
#line 932 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitBiOperator((yyvsp[-5].ast_value), OPERATOR_EXCOR_T, (yyvsp[-1].ast_value));
	}
#line 3526 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 177:
#line 936 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitUOperator((yyvsp[-4].ast_value), OPERATOR_NOT_T);
	}
#line 3534 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 178:
#line 940 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitUOperator((yyvsp[-4].ast_value), OPERATOR_CHILDA_T);
	}
#line 3542 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 179:
#line 944 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTExplicitUOperator((yyvsp[-4].ast_value), OPERATOR_NEGATIVE_T);
	}
#line 3550 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 180:
#line 948 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTInstanceTof((yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3558 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 181:
#line 952 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTAs((yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3566 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 182:
#line 956 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTUnary(AST_CHILDA_T, (yyvsp[0].ast_value));
	}
#line 3574 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 183:
#line 960 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTUnary(AST_NOT_T, (yyvsp[0].ast_value));
	}
#line 3582 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 184:
#line 964 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTNewInstance((yyvsp[-4].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3590 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 185:
#line 968 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTNewInstance((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), NewASTBlank());
	}
#line 3598 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 186:
#line 972 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTThis();
	}
#line 3606 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 187:
#line 976 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTSuper();
	}
#line 3614 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 189:
#line 983 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTVariable((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3622 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 190:
#line 987 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTFieldAccess((yyvsp[-3].ast_value), (yyvsp[-1].stringv_value), (yyvsp[0].ast_value));
	}
#line 3630 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 191:
#line 991 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOpCall((yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3638 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 192:
#line 995 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTOpCall((yyvsp[-2].ast_value), NewASTBlank());
	}
#line 3646 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 197:
#line 1005 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTTrue();
	}
#line 3654 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 198:
#line 1009 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTFalse();
	}
#line 3662 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 199:
#line 1013 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTNull();
	}
#line 3670 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 200:
#line 1022 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[0].ast_value));
	}
#line 3678 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 201:
#line 1026 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTStmtList((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3686 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 202:
#line 1032 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTProc((yyvsp[-1].ast_value));
	}
#line 3694 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 217:
#line 1052 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTVariableDecl((yyvsp[-2].ast_value), (yyvsp[-1].stringv_value));
	}
#line 3702 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 218:
#line 1058 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTVariableInit((yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 3710 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 219:
#line 1064 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTInferencedTypeInit((yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 3718 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 220:
#line 1070 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTIf((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3726 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 221:
#line 1074 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTIfElse((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3734 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 222:
#line 1078 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTIfElifList((yyvsp[-2].ast_value), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3742 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 223:
#line 1082 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTIfElifListElse((yyvsp[-4].ast_value), (yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3750 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 225:
#line 1089 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTElifList((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3758 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 226:
#line 1095 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTElif((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3766 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 227:
#line 1101 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTWhile((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3774 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 228:
#line 1107 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBreak();
	}
#line 3782 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 229:
#line 1113 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTContinue();
	}
#line 3790 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 230:
#line 1119 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTReturn((yyvsp[-1].ast_value));
	}
#line 3798 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 231:
#line 1123 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTReturnEmpty();
	}
#line 3806 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 232:
#line 1129 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTThrow((yyvsp[-1].ast_value));
	}
#line 3814 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 233:
#line 1135 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTTry((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3822 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 234:
#line 1141 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 3830 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 235:
#line 1145 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTCatchList((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 3838 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 236:
#line 1151 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTCatch((yyvsp[-3].ast_value), (yyvsp[-2].stringv_value), (yyvsp[0].ast_value));
	}
#line 3846 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 237:
#line 1157 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTAssert((yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3854 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 238:
#line 1161 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTAssert((yyvsp[-1].ast_value), NewASTBlank());
	}
#line 3862 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 239:
#line 1167 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTDefer((yyvsp[0].ast_value));
	}
#line 3870 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 240:
#line 1173 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTYieldReturn((yyvsp[-1].ast_value));
	}
#line 3878 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 241:
#line 1179 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTYieldBreak();
	}
#line 3886 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 242:
#line 1185 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTScope((yyvsp[-1].ast_value));
	}
#line 3894 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 243:
#line 1189 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTScopeEmpty();
	}
#line 3902 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 244:
#line 1195 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = NewASTBlank();
	}
#line 3910 "beacon.tab.c" /* yacc.c:1663  */
    break;


#line 3914 "beacon.tab.c" /* yacc.c:1663  */
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
#line 1203 "beacon.y" /* yacc.c:1907  */




