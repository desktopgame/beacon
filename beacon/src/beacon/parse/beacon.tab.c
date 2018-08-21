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
    QUOTE = 355,
    FUNCCALL = 356,
    ARRAY_SUBSCRIPT = 357,
    NEGATIVE = 358,
    POSITIVE = 359,
    REF = 360,
    FORM_TYPE = 361
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

#line 239 "beacon.tab.c" /* yacc.c:355  */
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

#line 270 "beacon.tab.c" /* yacc.c:358  */

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
#define YYLAST   2510

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  108
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  248
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  658

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   361

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     107,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
     105,   106
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
     866,   871,   875,   879,   883,   887,   891,   895,   899,   903,
     907,   911,   915,   919,   923,   927,   931,   935,   939,   943,
     947,   951,   955,   959,   963,   967,   971,   975,   979,   983,
     987,   990,   994,   998,  1002,  1008,  1009,  1010,  1011,  1012,
    1016,  1020,  1029,  1033,  1039,  1043,  1044,  1045,  1046,  1047,
    1048,  1049,  1050,  1051,  1052,  1053,  1054,  1055,  1056,  1059,
    1065,  1071,  1077,  1081,  1085,  1089,  1095,  1096,  1102,  1108,
    1114,  1120,  1126,  1130,  1136,  1142,  1148,  1152,  1158,  1164,
    1168,  1174,  1180,  1186,  1192,  1196,  1202,  1206,  1209
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
  "BOUNDS_SUPER", "SUBSCRIPT_SET", "SUBSCRIPT_GET", "QUOTE", "FUNCCALL",
  "ARRAY_SUBSCRIPT", "NEGATIVE", "POSITIVE", "REF", "FORM_TYPE", "'\\n'",
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
  "operator_define", "field_define", "prop_set", "prop_get", "prop_define",
  "modifier_type_T_list", "modifier_type_T", "access_level_T",
  "ident_list", "parameter_list", "argument_list", "typename_group",
  "typename_list", "typename_T", "fqcn_part", "expression",
  "expression_nobrace", "lhs", "primary", "stmt_list", "stmt",
  "variable_decl_stmt", "variable_init_stmt", "inferenced_type_init_stmt",
  "if_stmt", "elif_list", "elif", "while_stmt", "break_stmt",
  "continue_stmt", "return_stmt", "throw_stmt", "try_stmt",
  "catch_stmt_list", "catch_stmt", "assert_stmt", "defer_stmt",
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
     355,   356,   357,   358,   359,   360,   361,    10
};
# endif

#define YYPACT_NINF -463

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-463)))

#define YYTABLE_NINF -125

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     832,   -99,    92,   739,   923,   -34,  -463,  -463,  -463,  -463,
    -463,  -463,  -463,  -463,  -463,  2433,  2433,  2433,  2433,  2433,
     101,  -463,  -463,  -463,  -463,  -463,   155,   157,   158,   371,
      18,  2433,  2433,   120,   120,   134,  2433,  2433,  1196,  -463,
    -463,  -463,   178,   160,  1117,   184,   562,  -463,  -463,  -463,
    -463,  -463,  -463,  -463,  -463,  -463,  -463,  -463,  -463,  -463,
    -463,  -463,  -463,  -463,  -463,   160,   171,   171,   171,   171,
    1315,   209,   160,   183,  -463,   222,  -463,  1117,  -463,  2433,
     120,  1363,  1278,  -463,  -463,  1014,   177,  1117,  1026,  -463,
     -23,   241,   155,   263,  1206,  2433,  2433,  2433,  2433,  2433,
    2433,  2433,  2433,  2433,  2433,  2433,  2433,  2433,  2433,  2433,
    2433,  2433,  2433,   155,   155,  -463,   163,  2433,  2433,  2433,
    2433,  2433,  2433,  2433,  2433,  2433,  2433,  2433,  -463,  -463,
    2433,   270,   322,   301,   358,   389,  -463,  -463,  1117,  -463,
     -44,  -463,  -463,  -463,  -463,  1105,  -463,   330,   177,  -463,
    -463,  2433,  -463,  2433,  -463,  -463,     1,  -463,   160,   314,
     339,   342,   350,   355,   367,   368,   369,   376,   387,   396,
     398,   399,   400,   406,   410,   412,   413,   414,   415,   416,
      53,    53,     5,     5,     5,    12,    12,   768,   768,   464,
     464,   464,   464,   932,  2349,  2386,  2329,   841,  -463,  -463,
    -463,   417,    -4,  2292,  2292,  2292,  2292,  2292,  2292,  2292,
    2292,  2292,  2292,  2292,  2292,  1117,   295,  -463,     6,  -463,
      10,  -463,   333,   434,   434,   463,   158,  -463,   389,   423,
    -463,  -463,  -463,  -463,  -463,  2433,   134,    19,  -463,  -463,
    -463,   155,  -463,  1117,  1117,   155,  -463,  -463,  -463,  2433,
    2414,  2433,  2433,  2433,   422,  2433,  2433,   430,  2433,  2433,
    2433,  2433,  2433,  2433,  2433,  2433,  2433,  2433,  2433,   155,
    2433,  -463,  -463,  -463,    29,   322,  -463,   407,   108,   468,
     434,   183,   201,   210,   436,   222,  -463,  -463,  1363,  -463,
     134,  -463,   499,  -463,  -463,  -463,  1400,  -463,  1445,  1490,
    1535,  1580,  -463,  1625,  1670,  -463,  1715,  1760,  1805,  1850,
    1895,  1940,  1985,  2030,  2075,  2120,  2165,   111,  2292,  -463,
    -463,   155,   155,   428,  -463,   224,  -463,   155,   232,   155,
     232,   513,  -463,  -463,  -463,   471,  -463,  -463,  -463,  -463,
    -463,  -463,  -463,  -463,  -463,  -463,  -463,  -463,  -463,  -463,
    -463,  -463,  -463,  -463,   445,   190,   518,   155,   155,   232,
       0,  -463,  -463,  -463,   477,   232,  -463,   521,    30,   478,
    -463,   147,   134,   155,  -463,  -463,   190,   170,   482,   232,
    -463,  -463,    -1,   232,  -463,   167,  -463,  -463,   134,  -463,
     232,  -463,   483,  -463,    17,  -463,  -463,  -463,  -463,   154,
     318,    -1,  -463,  -463,  -463,  -463,  -463,  -463,    17,  -463,
     527,   485,  -463,  -463,  -463,   487,  -463,    17,   531,   183,
     488,   247,   489,   490,   491,   493,   495,   496,   497,   498,
     500,   502,   503,   504,   505,   506,   507,   508,   509,   511,
     516,   519,   533,   534,  -463,  -463,   543,   -21,  -463,  -463,
     579,   539,   538,    66,   183,   155,    69,   155,   155,   155,
     540,   155,   155,   542,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,    52,  2433,  -463,
     541,   380,    88,   581,   214,   544,   223,   530,   244,   251,
     255,   259,   532,   260,   265,   535,   275,   311,   316,   319,
     321,   344,   352,   360,   373,   378,   379,   385,   388,  2433,
    -463,  2210,   380,   200,    28,   551,   536,   390,    54,  -463,
     190,   581,   106,   537,   155,   547,   552,   553,   554,   155,
     555,   556,   155,   557,   558,   559,   560,   561,   567,   570,
     584,   585,   588,   589,   590,   592,  2247,  -463,    28,  -463,
    -463,   202,   563,   612,   203,   155,   595,  -463,  -463,   566,
    -463,   190,   596,   391,   155,   190,   155,   155,   155,   155,
     190,   155,   155,   190,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,  -463,   568,  -463,
    -463,  -463,   331,  -463,  -463,   190,   155,   673,  -463,   155,
     602,   190,  -463,   190,   190,   190,   190,  -463,   190,   190,
    -463,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,  -463,  -463,  -463,  -463,   190,  -463,
     393,   190,   155,  -463,  -463,  -463,  -463,  -463,  -463,  -463,
    -463,  -463,  -463,  -463,  -463,  -463,  -463,  -463,  -463,  -463,
    -463,  -463,  -463,  -463,  -463,  -463,   190,  -463
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,    23,     4,    25,     1,
     197,   198,   195,   196,   125,     0,     0,     0,     0,     0,
       0,   188,   189,   199,   200,   201,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       8,     9,     0,   120,     0,   129,   190,   128,     7,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,     2,    24,   120,   130,   131,   185,   184,
       0,     0,   120,    27,    21,     0,   248,     0,   233,     0,
       0,     0,     0,   230,   231,     0,     0,     0,     0,   241,
       0,     0,     0,   191,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   204,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   191,   127,
       0,     0,     0,     0,     0,    19,    10,   232,     0,   243,
     222,   246,   247,   229,   245,     0,   202,     0,   235,   236,
     234,     0,   240,     0,   219,   126,     0,   122,   120,   120,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     132,   133,   134,   135,   136,   159,   160,   138,   139,   155,
     156,   157,   158,   140,   143,   137,   142,   141,   183,   182,
     194,     0,     0,   117,   144,   145,   146,   147,   148,   149,
     150,   151,   153,   154,   152,     0,     0,    31,     0,    29,
       0,    22,     0,     0,     0,     0,     0,    17,    20,     0,
      13,    14,    16,    15,   242,     0,     0,   224,   226,   244,
     203,     0,   237,     0,     0,     0,   121,   124,   192,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   193,   221,   187,     0,     0,    28,     0,     0,     0,
       0,    27,     0,     0,     0,     0,    18,    11,     0,   223,
       0,   227,     0,   239,   220,   123,     0,   181,     0,     0,
       0,     0,   179,     0,     0,   180,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,   186,
      30,     0,     0,     0,   115,     0,    26,     0,    40,     0,
      40,     0,    12,   228,   225,     0,   161,   162,   163,   164,
     165,   176,   177,   170,   171,   166,   167,   168,   169,   173,
     175,   172,   174,   178,     0,     0,     0,     0,     0,    40,
       0,   110,   111,   112,     0,    41,    42,     0,     0,     0,
     113,     0,     0,     0,    61,   116,     0,     0,     0,    40,
      38,    43,     0,    40,    34,     0,    36,   238,     0,    60,
      40,    32,     0,   109,     0,   107,   108,   105,   106,     0,
       0,    44,    45,    47,    48,    49,    50,    51,     0,   103,
       0,     0,   114,    37,   118,     0,    39,     0,     0,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,   104,     0,     0,    35,    33,
       0,     0,     0,     0,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    90,
       0,     0,     0,    58,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89,     0,     0,     0,     0,     0,     0,     0,     0,    59,
       0,    58,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,     0,    93,
      94,     0,     0,     0,     0,     0,     0,    57,    56,     0,
      53,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    91,     0,    97,
      98,   102,     0,    95,    96,     0,     0,     0,    52,     0,
       0,     0,    86,     0,     0,     0,     0,    84,     0,     0,
      85,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   101,    99,   100,    65,     0,    55,
       0,     0,     0,    66,    67,    68,    69,    70,    81,    82,
      75,    76,    71,    72,    73,    74,    78,    80,    77,    79,
      83,    88,    87,    64,    54,    63,     0,    62
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -463,  -463,  -463,   608,  -463,   334,   394,  -463,  -463,   395,
    -463,   618,  -208,  -260,  -463,   408,  -463,  -463,  -463,  -463,
    -118,  -463,   317,  -463,   229,  -463,  -463,  -463,   164,  -463,
    -463,  -463,  -463,   172,   140,  -463,  -376,  -235,  -462,  -463,
    -266,  -214,   -61,    86,    -3,    27,   392,  -463,  -463,  -463,
    -463,   -31,  -463,  -463,  -463,  -463,  -463,   452,  -463,  -463,
    -463,  -463,  -463,  -463,  -463,   545,  -463,  -463,  -463,  -463,
      74,   100,     3
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    39,    40,   136,   227,   228,   229,    75,
       5,     6,   282,   133,   218,   219,   230,   231,   232,   233,
     364,   365,   366,   401,   402,   403,   519,   559,   520,    41,
     404,   405,   406,   514,   552,   407,   408,   409,   367,   371,
     278,   202,    93,   156,   279,   158,    44,    45,    46,    47,
     145,    48,    49,    50,    51,    52,   237,   238,    53,    54,
      55,    56,    57,    58,   148,   149,    59,    60,    61,    62,
     142,   143,    78
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,    42,   274,   317,   128,   270,    14,    89,     7,   245,
     245,   131,   153,    94,   478,   275,   283,    14,   417,   515,
      94,   326,     2,   421,    14,    95,    96,    97,    98,    99,
      43,    43,   154,   393,   479,    42,    83,    84,   270,   245,
     235,   236,    65,    65,    65,    65,    65,   115,   271,   379,
     515,   393,   553,    72,   146,   246,    65,   394,    65,    65,
     276,    94,   277,    65,    65,    43,   395,   396,    97,    98,
      99,   113,   325,    14,   397,   398,    14,   399,   113,   383,
     137,   319,    42,   139,   395,   396,   553,   509,   551,   157,
     150,   152,   397,   398,   400,    14,     8,   247,   248,    79,
     361,   362,   363,   235,   290,    80,    65,   510,    71,    86,
     198,   199,    43,    14,   240,   557,   558,   322,   483,   113,
     322,   487,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
     516,   234,    42,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,   140,   385,    65,   562,   452,
     323,   419,    14,   354,    73,    74,    10,    11,    12,    13,
      14,    91,    43,   445,   412,    76,    15,    16,    65,   245,
      65,    17,   445,    85,    18,    90,   445,   484,   393,   486,
     488,   489,   490,   491,   485,   493,   494,   386,   496,   497,
     498,   499,   500,   501,   502,   503,   504,   505,   506,   507,
     508,   327,   369,    92,    19,   200,   517,   413,   272,   390,
     329,   395,   396,   322,    21,    22,    23,    24,    25,   397,
     398,   420,   322,   134,   358,   116,   132,   113,   292,    85,
      26,   378,   295,    65,   130,   141,   293,   294,   155,    85,
     328,    85,    85,   322,   454,   549,   563,   589,   593,   330,
     322,   392,    65,   201,   322,   411,   521,   147,   322,   322,
    -124,   135,   415,   359,   322,   523,    65,    65,    65,    65,
      65,   393,    65,    65,   322,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,   525,    65,    10,    11,
      12,    13,    14,   526,   361,   362,   363,   527,    15,    16,
     289,   528,   530,    17,   395,   396,    18,   531,   355,   356,
     322,   216,   397,   398,   157,   322,   157,   533,   322,   217,
     322,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,   435,   436,    19,   273,   437,   438,
     439,   440,   220,   322,   376,   157,    21,    22,    23,    24,
      25,   322,   333,   534,   334,   221,   441,    92,   535,   322,
     388,   536,    26,   537,    10,    11,    12,    13,    14,   410,
      85,   241,   322,   630,    15,    16,   625,   322,   322,    17,
     249,   418,    18,   250,   322,   201,   538,   322,   410,   322,
     322,   251,   270,   280,   539,   446,   252,    66,    67,    68,
      69,    70,   540,   360,   450,   368,   442,   443,   253,   254,
     255,    77,    19,    81,    82,   541,    76,   256,    87,    88,
     542,   543,    21,    22,    23,    24,    25,   544,   257,   513,
     545,   281,   556,   600,   377,   654,   387,   258,    26,   259,
     260,   261,   361,   362,   363,   374,   222,   262,   223,   224,
     225,   263,   414,   264,   265,   266,   267,   268,   269,   226,
     284,   138,    94,   287,   302,   324,   389,    95,    96,    97,
      98,    99,   305,   100,   101,   331,   321,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,    65,   335,   357,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     370,   565,   215,   372,   373,   375,   570,   380,   384,   573,
     113,   382,   391,   416,   447,   448,    65,   449,   451,   453,
     455,   456,   457,   243,   458,   244,   459,   460,   461,   462,
     477,   463,   595,   464,   465,   466,   467,   468,   469,   470,
     471,   601,   472,   603,   604,   605,   606,   473,   608,   609,
     474,   611,   612,   613,   614,   615,   616,   617,   618,   619,
     620,   621,   622,   623,   475,   476,   480,   550,   481,   482,
     512,   518,   492,   628,   495,   522,   631,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   203,   524,
     554,   529,    63,   591,   532,   555,   564,   597,   624,   332,
     560,   285,   286,    64,    65,   590,   566,   288,   594,   656,
     444,   567,   568,   569,   571,   572,   574,   575,   576,   577,
     578,   296,   298,   299,   300,   301,   579,   303,   304,   580,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   598,   318,   581,   582,   602,   626,   583,   584,   585,
     607,   586,   592,   610,   596,   599,    10,    11,    12,    13,
      14,   632,   381,   320,   548,   561,    15,    16,   588,   291,
       0,    17,     0,   242,    18,   627,     0,     0,     0,     0,
       0,   633,     0,   634,   635,   636,   637,     0,   638,   639,
       0,   640,   641,   642,   643,   644,   645,   646,   647,   648,
     649,   650,   651,   652,    19,   629,     0,     0,   653,     0,
       0,   655,     0,     0,    21,    22,    23,    24,    25,     9,
       0,     0,    10,    11,    12,    13,    14,     0,     0,     0,
      26,     0,    15,    16,     0,     0,   657,    17,     0,     0,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   201,     0,     0,    94,     0,     0,     0,
       0,    95,    96,    97,    98,    99,     0,   100,   101,     0,
      19,     0,   104,   105,   106,   107,    20,     0,     0,     0,
      21,    22,    23,    24,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,    27,     0,    28,
      29,    30,    31,     0,     0,    32,    33,    34,    35,     0,
      36,    37,    38,     1,   113,    -5,    -5,    -5,    -5,    -5,
       0,     0,     0,     0,     0,    -5,    -5,     0,     0,    94,
      -5,     0,     0,    -5,    95,    96,    97,    98,    99,     0,
     100,   101,   114,   102,   103,   104,   105,   106,   107,     0,
     511,   108,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    -5,     0,     0,     0,     0,     2,    -5,
       0,     0,     0,    -5,    -5,    -5,    -5,    -5,     0,     0,
       0,   546,     0,     0,     0,     0,     0,   113,     0,    -5,
      -5,     0,    -5,    -5,    -5,    -5,     0,     0,    -5,    -5,
      -5,    -5,     0,    -5,    -5,    -5,    10,    11,    12,    13,
      14,     0,     0,     0,     0,   114,    15,    16,     0,     0,
      94,    17,     0,     0,    18,    95,    96,    97,    98,    99,
       0,   100,   101,     0,   102,   103,   104,   105,   106,   107,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    19,     0,     0,     0,     0,     0,
      20,     0,     0,     0,    21,    22,    23,    24,    25,   203,
       0,     0,     0,     0,     0,     0,     0,     0,   113,     0,
      26,    27,     0,    28,    29,    30,    31,     0,     0,    32,
      33,    34,    35,     0,    36,    37,    38,    10,    11,    12,
      13,    14,     0,     0,     0,     0,   114,    15,    16,     0,
       0,     0,    17,     0,    94,    18,   151,     0,     0,    95,
      96,    97,    98,    99,     0,   100,   101,     0,   102,   103,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,   144,    19,     0,     0,     0,     0,
       0,    20,     0,     0,   112,    21,    22,    23,    24,    25,
       0,    76,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    26,   113,     0,     0,    29,    30,    31,     0,     0,
      32,    33,    34,    35,     0,    36,    37,    38,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,    15,    16,
     114,     0,     0,    17,     0,    94,    18,     0,     0,     0,
      95,    96,    97,    98,    99,     0,   100,   101,     0,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,   239,    19,     0,     0,     0,
       0,     0,    20,     0,     0,   112,    21,    22,    23,    24,
      25,     0,    76,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    26,   113,     0,     0,    29,    30,    31,     0,
       0,    32,    33,    34,    35,     0,    36,    37,    38,    10,
      11,    12,    13,    14,     0,     0,     0,     0,     0,    15,
      16,   114,     0,   159,    17,     0,     0,    18,     0,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,     0,     0,   175,   176,   177,   178,
       0,     0,     0,     0,     0,     0,     0,    19,     0,     0,
       0,     0,     0,    20,   179,     0,     0,    21,    22,    23,
      24,    25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    26,     0,     0,     0,    29,    30,    31,
       0,     0,    32,    33,    34,    35,    94,    36,    37,    38,
       0,    95,    96,    97,    98,    99,     0,   100,   101,     0,
     102,   103,   104,   105,   106,   107,     0,     0,   108,   109,
     110,   111,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    94,     0,     0,   112,    85,    95,    96,
      97,    98,    99,   141,   100,   101,     0,   102,   103,   104,
     105,   106,   107,     0,   113,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,     0,     0,     0,   129,     0,     0,
       0,    94,   114,     0,     0,     0,    95,    96,    97,    98,
      99,   113,   100,   101,     0,   102,   103,   104,   105,   106,
     107,     0,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,   114,
       0,   112,    85,    95,    96,    97,    98,    99,     0,   100,
     101,     0,   102,   103,   104,   105,   106,   107,     0,   113,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,     0,
       0,     0,   336,    94,     0,     0,     0,   114,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   337,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   338,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   339,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   340,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   341,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   342,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   343,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   344,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   345,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   346,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   347,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   348,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   349,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   350,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   351,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,     0,   352,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   113,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   114,     0,     0,   353,    94,     0,
       0,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   113,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,   112,   114,
      95,    96,    97,    98,    99,   547,   100,   101,     0,   102,
     103,   104,   105,   106,   107,     0,   113,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,     0,     0,     0,     0,
      94,     0,   587,     0,   114,    95,    96,    97,    98,    99,
       0,   100,   101,   113,   102,   103,   104,   105,   106,   107,
       0,     0,   108,   109,   110,   111,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94,     0,     0,
     112,   114,    95,    96,    97,    98,    99,     0,   100,   101,
       0,   102,   103,   104,   105,   106,   107,    94,   113,   108,
     109,   110,    95,    96,    97,    98,    99,     0,   100,   101,
       0,   102,   103,   104,   105,   106,   107,   112,     0,   108,
       0,   110,     0,     0,     0,     0,   114,     0,     0,     0,
       0,     0,     0,     0,    94,   113,     0,   112,     0,    95,
      96,    97,    98,    99,     0,   100,   101,     0,   102,   103,
     104,   105,   106,   107,     0,   113,   108,    10,    11,    12,
      13,    14,     0,   114,     0,     0,     0,    15,    16,     0,
       0,     0,    17,     0,   112,    18,    10,    11,    12,    13,
      14,     0,     0,   114,     0,     0,    15,    16,     0,     0,
       0,    17,   113,     0,    18,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    19,   297,     0,     0,     0,
       0,     0,     0,     0,     0,    21,    22,    23,    24,    25,
     114,     0,     0,     0,    19,     0,     0,     0,     0,     0,
       0,    26,     0,     0,    21,    22,    23,    24,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26
};

static const yytype_int16 yycheck[] =
{
       3,     4,   216,   269,    65,     9,     7,    38,   107,     9,
       9,    72,    35,     8,    35,     9,   224,     7,   394,   481,
       8,   281,    56,   399,     7,    13,    14,    15,    16,    17,
       3,     4,    55,    34,    55,    38,    33,    34,     9,     9,
      84,    85,    15,    16,    17,    18,    19,    44,    52,    49,
     512,    34,   514,    26,    85,    54,    29,    58,    31,    32,
      54,     8,    52,    36,    37,    38,    67,    68,    15,    16,
      17,    66,   280,     7,    75,    76,     7,    78,    66,    49,
      77,    52,    85,    80,    67,    68,   548,    35,    60,    92,
      87,    88,    75,    76,    95,     7,     4,   158,   159,    81,
      72,    73,    74,    84,    85,    87,    79,    55,     7,    35,
     113,   114,    85,     7,   145,    61,    62,     9,    52,    66,
       9,    52,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
      52,   138,   145,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,    81,     9,   130,    52,   419,
      52,     7,     7,    52,     7,     7,     3,     4,     5,     6,
       7,    11,   145,   408,     7,    55,    13,    14,   151,     9,
     153,    18,   417,    49,    21,     7,   421,   453,    34,   455,
     456,   457,   458,   459,   454,   461,   462,    50,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,    10,   330,    53,    51,    52,   482,    50,   215,    49,
      10,    67,    68,     9,    61,    62,    63,    64,    65,    75,
      76,    77,     9,    11,    10,    51,    53,    66,   241,    49,
      77,   359,   245,   216,    35,    55,   243,   244,     7,    49,
      49,    49,    49,     9,     7,    55,   522,    55,    55,    49,
       9,   379,   235,   100,     9,   383,    52,    90,     9,     9,
       7,    49,   390,    49,     9,    52,   249,   250,   251,   252,
     253,    34,   255,   256,     9,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,    52,   270,     3,     4,
       5,     6,     7,    52,    72,    73,    74,    52,    13,    14,
     236,    52,    52,    18,    67,    68,    21,    52,   321,   322,
       9,    51,    75,    76,   327,     9,   329,    52,     9,     7,
       9,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    51,    52,    30,    31,
      32,    33,    51,     9,   357,   358,    61,    62,    63,    64,
      65,     9,   288,    52,   290,     7,    48,    53,    52,     9,
     373,    52,    77,    52,     3,     4,     5,     6,     7,   382,
      49,    51,     9,   597,    13,    14,    55,     9,     9,    18,
      51,   394,    21,    51,     9,   100,    52,     9,   401,     9,
       9,    51,     9,    70,    52,   408,    51,    15,    16,    17,
      18,    19,    52,   327,   417,   329,    98,    99,    51,    51,
      51,    29,    51,    31,    32,    52,    55,    51,    36,    37,
      52,    52,    61,    62,    63,    64,    65,    52,    51,    59,
      52,     7,    52,    52,   358,    52,   372,    51,    77,    51,
      51,    51,    72,    73,    74,   355,    67,    51,    69,    70,
      71,    51,   388,    51,    51,    51,    51,    51,    51,    80,
       7,    79,     8,    50,    52,     7,   376,    13,    14,    15,
      16,    17,    52,    19,    20,    49,    79,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   478,     7,    79,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
       7,   524,   130,    52,    79,     7,   529,    50,    50,   532,
      66,    10,    50,    50,     7,    50,   509,    50,     7,    51,
      51,    51,    51,   151,    51,   153,    51,    51,    51,    51,
       7,    51,   555,    51,    51,    51,    51,    51,    51,    51,
      51,   564,    51,   566,   567,   568,   569,    51,   571,   572,
      51,   574,   575,   576,   577,   578,   579,   580,   581,   582,
     583,   584,   585,   586,    51,    51,     7,   513,    49,    51,
      49,    10,    52,   596,    52,    51,   599,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,   216,    79,
      59,    79,     4,    50,    79,    79,    79,    51,    50,   285,
     520,   226,   228,     5,   597,   551,    79,   235,   554,   632,
     401,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,   249,   250,   251,   252,   253,    79,   255,   256,    79,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   561,   270,    79,    79,   565,   592,    79,    79,    79,
     570,    79,    60,   573,    79,    79,     3,     4,     5,     6,
       7,    79,   365,   275,   512,   521,    13,    14,   548,   237,
      -1,    18,    -1,   148,    21,   595,    -1,    -1,    -1,    -1,
      -1,   601,    -1,   603,   604,   605,   606,    -1,   608,   609,
      -1,   611,   612,   613,   614,   615,   616,   617,   618,   619,
     620,   621,   622,   623,    51,    52,    -1,    -1,   628,    -1,
      -1,   631,    -1,    -1,    61,    62,    63,    64,    65,     0,
      -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      77,    -1,    13,    14,    -1,    -1,   656,    18,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   100,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    13,    14,    15,    16,    17,    -1,    19,    20,    -1,
      51,    -1,    24,    25,    26,    27,    57,    -1,    -1,    -1,
      61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    -1,    80,
      81,    82,    83,    -1,    -1,    86,    87,    88,    89,    -1,
      91,    92,    93,     1,    66,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    -1,    -1,    13,    14,    -1,    -1,     8,
      18,    -1,    -1,    21,    13,    14,    15,    16,    17,    -1,
      19,    20,    94,    22,    23,    24,    25,    26,    27,    -1,
     478,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    56,    57,
      -1,    -1,    -1,    61,    62,    63,    64,    65,    -1,    -1,
      -1,   509,    -1,    -1,    -1,    -1,    -1,    66,    -1,    77,
      78,    -1,    80,    81,    82,    83,    -1,    -1,    86,    87,
      88,    89,    -1,    91,    92,    93,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    94,    13,    14,    -1,    -1,
       8,    18,    -1,    -1,    21,    13,    14,    15,    16,    17,
      -1,    19,    20,    -1,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      57,    -1,    -1,    -1,    61,    62,    63,    64,    65,   597,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      77,    78,    -1,    80,    81,    82,    83,    -1,    -1,    86,
      87,    88,    89,    -1,    91,    92,    93,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    94,    13,    14,    -1,
      -1,    -1,    18,    -1,     8,    21,    10,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,
      -1,    57,    -1,    -1,    48,    61,    62,    63,    64,    65,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    66,    -1,    -1,    81,    82,    83,    -1,    -1,
      86,    87,    88,    89,    -1,    91,    92,    93,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,
      94,    -1,    -1,    18,    -1,     8,    21,    -1,    -1,    -1,
      13,    14,    15,    16,    17,    -1,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    50,    51,    -1,    -1,    -1,
      -1,    -1,    57,    -1,    -1,    48,    61,    62,    63,    64,
      65,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    66,    -1,    -1,    81,    82,    83,    -1,
      -1,    86,    87,    88,    89,    -1,    91,    92,    93,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,
      14,    94,    -1,     7,    18,    -1,    -1,    21,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    57,    48,    -1,    -1,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    82,    83,
      -1,    -1,    86,    87,    88,    89,     8,    91,    92,    93,
      -1,    13,    14,    15,    16,    17,    -1,    19,    20,    -1,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     8,    -1,    -1,    48,    49,    13,    14,
      15,    16,    17,    55,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    66,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    52,    -1,    -1,
      -1,     8,    94,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    66,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    94,
      -1,    48,    49,    13,    14,    15,    16,    17,    -1,    19,
      20,    -1,    22,    23,    24,    25,    26,    27,    -1,    66,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    52,     8,    -1,    -1,    -1,    94,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    94,
      -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    66,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,    19,
      20,    66,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    48,    94,
      13,    14,    15,    16,    17,    55,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    66,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
       8,    -1,    55,    -1,    94,    13,    14,    15,    16,    17,
      -1,    19,    20,    66,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,
      48,    94,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,     8,    66,    30,
      31,    32,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    48,    -1,    30,
      -1,    32,    -1,    -1,    -1,    -1,    94,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     8,    66,    -1,    48,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    22,    23,
      24,    25,    26,    27,    -1,    66,    30,     3,     4,     5,
       6,     7,    -1,    94,    -1,    -1,    -1,    13,    14,    -1,
      -1,    -1,    18,    -1,    48,    21,     3,     4,     5,     6,
       7,    -1,    -1,    94,    -1,    -1,    13,    14,    -1,    -1,
      -1,    18,    66,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      94,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    61,    62,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    56,   109,   110,   118,   119,   107,     4,     0,
       3,     4,     5,     6,     7,    13,    14,    18,    21,    51,
      57,    61,    62,    63,    64,    65,    77,    78,    80,    81,
      82,    83,    86,    87,    88,    89,    91,    92,    93,   111,
     112,   137,   152,   153,   154,   155,   156,   157,   159,   160,
     161,   162,   163,   166,   167,   168,   169,   170,   171,   174,
     175,   176,   177,   111,   119,   153,   154,   154,   154,   154,
     154,     7,   153,     7,     7,   117,    55,   154,   180,    81,
      87,   154,   154,   180,   180,    49,   178,   154,   154,   159,
       7,    11,    53,   150,     8,    13,    14,    15,    16,    17,
      19,    20,    22,    23,    24,    25,    26,    27,    30,    31,
      32,    33,    48,    66,    94,   180,    51,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,   150,    52,
      35,   150,    53,   121,    11,    49,   113,   180,   154,   180,
     178,    55,   178,   179,    50,   158,   159,    90,   172,   173,
     180,    10,   180,    35,    55,     7,   151,   152,   153,     7,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    30,    31,    32,    33,    48,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   152,   152,
      52,   100,   149,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,    51,     7,   122,   123,
      51,     7,    67,    69,    70,    71,    80,   114,   115,   116,
     124,   125,   126,   127,   180,    84,    85,   164,   165,    50,
     159,    51,   173,   154,   154,     9,    54,   150,   150,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
       9,    52,   180,    52,   149,     9,    54,    52,   148,   152,
      70,     7,   120,   120,     7,   117,   114,    50,   154,   178,
      85,   165,   152,   180,   180,   152,   154,    52,   154,   154,
     154,   154,    52,   154,   154,    52,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   148,   154,    52,
     123,    79,     9,    52,     7,   120,   121,    10,    49,    10,
      49,    49,   113,   178,   178,     7,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,   152,   152,    79,    10,    49,
     151,    72,    73,    74,   128,   129,   130,   146,   151,   128,
       7,   147,    52,    79,   179,     7,   152,   151,   128,    49,
      50,   130,    10,    49,    50,     9,    50,   178,   152,   179,
      49,    50,   128,    34,    58,    67,    68,    75,    76,    78,
      95,   131,   132,   133,   138,   139,   140,   143,   144,   145,
     152,   128,     7,    50,   178,   128,    50,   144,   152,     7,
      77,   144,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    30,    31,    32,
      33,    48,    98,    99,   132,   145,   152,     7,    50,    50,
     152,     7,   121,    51,     7,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,     7,    35,    55,
       7,    49,    51,    52,   148,   121,   148,    52,   148,   148,
     148,   148,    52,   148,   148,    52,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,    35,
      55,   154,    49,    59,   141,   146,    52,   148,    10,   134,
     136,    52,    51,    52,    79,    52,    52,    52,    52,    79,
      52,    52,    79,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,   154,    55,   141,    55,
     178,    60,   142,   146,    59,    79,    52,    61,    62,   135,
     179,   136,    52,   148,    79,   152,    79,    79,    79,    79,
     152,    79,    79,   152,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    55,   142,    55,
     178,    50,    60,    55,   178,   152,    79,    51,   179,    79,
      52,   152,   179,   152,   152,   152,   152,   179,   152,   152,
     179,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,    50,    55,   178,   179,   152,    52,
     149,   152,    79,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,    52,   179,   152,   179
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   108,   109,   109,   109,   110,   110,   111,   111,   111,
     112,   113,   114,   114,   114,   114,   114,   115,   115,   116,
     116,   117,   117,   118,   118,   119,   120,   121,   121,   122,
     122,   123,   124,   124,   125,   125,   126,   126,   127,   127,
     128,   128,   129,   129,   130,   131,   131,   132,   132,   132,
     132,   132,   133,   133,   134,   134,   135,   135,   136,   136,
     137,   137,   138,   138,   138,   138,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   140,
     140,   140,   140,   141,   141,   141,   141,   142,   142,   142,
     142,   143,   143,   144,   144,   145,   145,   145,   145,   145,
     146,   146,   146,   147,   147,   148,   148,   149,   149,   149,
     150,   150,   151,   151,   152,   153,   153,   154,   154,   154,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   156,   156,   156,   156,   157,   157,   157,   157,   157,
     157,   157,   158,   158,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   160,
     161,   162,   163,   163,   163,   163,   164,   164,   165,   166,
     167,   168,   169,   169,   170,   171,   172,   172,   173,   174,
     174,   175,   176,   177,   178,   178,   179,   179,   180
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
       3,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     5,
       5,     5,     3,     3,     2,     2,     6,     5,     1,     1,
       1,     2,     4,     4,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       5,     5,     3,     5,     4,     6,     1,     2,     3,     3,
       2,     2,     3,     2,     3,     3,     1,     2,     6,     5,
       3,     2,     4,     3,     3,     2,     1,     1,     1
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
#line 2273 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 6:
#line 158 "beacon.y" /* yacc.c:1663  */
    {
		ast_compile_entry((yyvsp[0].ast_value));
	}
#line 2281 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 7:
#line 164 "beacon.y" /* yacc.c:1663  */
    {
		ast_compile_entry((yyvsp[0].ast_value));
	}
#line 2289 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 8:
#line 168 "beacon.y" /* yacc.c:1663  */
    {
		ast_compile_entry((yyvsp[0].ast_value));
	}
#line 2297 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 9:
#line 172 "beacon.y" /* yacc.c:1663  */
    {
		ast_compile_entry((yyvsp[0].ast_value));
	}
#line 2305 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 10:
#line 178 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2313 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 11:
#line 185 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 2321 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 12:
#line 192 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2329 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 17:
#line 203 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 2337 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 18:
#line 207 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2345 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 19:
#line 214 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 2353 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 21:
#line 222 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[0].stringv_value));
	}
#line 2361 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 22:
#line 226 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[-2].ast_value), (yyvsp[0].stringv_value));
	}
#line 2369 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 24:
#line 234 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_import_decl_list((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2377 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 25:
#line 241 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[0].ast_value)));
	}
#line 2385 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 26:
#line 248 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_parameterized_typename((yyvsp[-1].stringv_value), (yyvsp[0].ast_value));
	}
#line 2393 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 27:
#line 255 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 2401 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 28:
#line 259 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 2409 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 29:
#line 266 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 2417 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 30:
#line 270 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_type_parameter_list((yyvsp[0].ast_value), (yyvsp[-2].ast_value));
	}
#line 2425 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 31:
#line 277 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_type_parameter((yyvsp[0].stringv_value), ast_new_blank());
	}
#line 2433 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 32:
#line 283 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_abstract_class_decl((yyvsp[-3].ast_value), ast_new_blank(), (yyvsp[-1].ast_value));
	}
#line 2441 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 33:
#line 287 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_abstract_class_decl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2449 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 34:
#line 293 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[-3].ast_value), ast_new_blank(), (yyvsp[-1].ast_value));
	}
#line 2457 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 35:
#line 297 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2465 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 36:
#line 304 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2473 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 37:
#line 308 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[-4].stringv_value), (yyvsp[-2].ast_value));
	}
#line 2481 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 38:
#line 315 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[-3].ast_value), ast_new_blank(), (yyvsp[-1].ast_value));
	}
#line 2489 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 39:
#line 319 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2497 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 40:
#line 326 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 2505 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 43:
#line 335 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2513 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 44:
#line 342 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[-2].access_level_value), (yyvsp[0].ast_value));
	}
#line 2521 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 45:
#line 349 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[0].ast_value));
	}
#line 2529 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 46:
#line 353 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[-1].ast_value), ast_new_member_decl((yyvsp[0].ast_value)));
	}
#line 2537 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 52:
#line 368 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[-3].ast_value), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2545 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 53:
#line 372 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2553 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 54:
#line 379 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[-3].chain_type_value), (yyvsp[-1].ast_value));
	}
#line 2561 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 55:
#line 383 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[-2].chain_type_value), ast_new_blank());
	}
#line 2569 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 56:
#line 390 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.chain_type_value) = chain_type_super;
	}
#line 2577 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 57:
#line 394 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.chain_type_value) = chain_type_this;
	}
#line 2585 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 58:
#line 401 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 2593 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 60:
#line 409 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2601 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 61:
#line 413 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2609 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 62:
#line 420 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_method_decl((yyvsp[-8].ast_value), (yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2617 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 63:
#line 424 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[-7].ast_value), (yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2625 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 64:
#line 428 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_method_decl(ast_new_modifier(modifier_none_T), (yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2633 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 65:
#line 432 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params(ast_new_modifier(modifier_none_T), (yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2641 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 66:
#line 439 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_add, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2649 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 67:
#line 443 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_sub, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2657 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 68:
#line 447 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_mul, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2665 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 69:
#line 451 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_div, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2673 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 70:
#line 455 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_mod, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2681 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 71:
#line 459 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_gt, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2689 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 72:
#line 463 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_ge, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2697 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 73:
#line 467 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_lt, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2705 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 74:
#line 471 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_le, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2713 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 75:
#line 476 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_eq, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2721 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 76:
#line 480 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_noteq, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2729 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 77:
#line 485 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_bit_or, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2737 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 78:
#line 489 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_bit_and, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2745 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 79:
#line 494 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_logic_or, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2753 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 80:
#line 498 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_logic_and, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2761 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 81:
#line 503 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_lshift, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2769 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 82:
#line 507 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_rshift, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2777 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 83:
#line 512 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_excor, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2785 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 84:
#line 517 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_not, ast_new_blank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2793 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 85:
#line 522 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_childa, ast_new_blank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2801 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 86:
#line 526 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_negative, ast_new_blank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2809 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 87:
#line 531 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_subscript_get, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2817 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 88:
#line 536 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_subscript_set, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2825 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 89:
#line 543 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[-1].stringv_value), ast_new_blank());
	}
#line 2833 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 90:
#line 547 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_decl(ast_new_modifier(modifier_none_T), (yyvsp[-2].ast_value), (yyvsp[-1].stringv_value), ast_new_blank());
	}
#line 2841 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 91:
#line 551 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[-5].ast_value), (yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2849 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 92:
#line 555 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_decl(ast_new_modifier(modifier_none_T), (yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2857 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 93:
#line 562 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_blank(), ast_new_blank());
	}
#line 2865 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 94:
#line 566 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_blank(), (yyvsp[0].ast_value));
	}
#line 2873 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 95:
#line 570 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_access((yyvsp[-2].access_level_value)), ast_new_blank());
	}
#line 2881 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 96:
#line 574 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_access((yyvsp[-2].access_level_value)), ast_new_blank());
	}
#line 2889 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 97:
#line 581 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_blank(), ast_new_blank());
	}
#line 2897 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 98:
#line 585 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_blank(), (yyvsp[0].ast_value));
	}
#line 2905 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 99:
#line 589 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_access((yyvsp[-2].access_level_value)), ast_new_blank());
	}
#line 2913 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 100:
#line 593 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_access((yyvsp[-2].access_level_value)), ast_new_blank());
	}
#line 2921 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 101:
#line 600 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_decl((yyvsp[-6].ast_value), (yyvsp[-5].ast_value), (yyvsp[-4].stringv_value), (yyvsp[-2].ast_value), (yyvsp[-1].ast_value));
	}
#line 2929 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 102:
#line 604 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_decl(ast_new_modifier(modifier_none_T), (yyvsp[-5].ast_value), (yyvsp[-4].stringv_value), (yyvsp[-2].ast_value), (yyvsp[-1].ast_value));
	}
#line 2937 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 103:
#line 611 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 2945 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 104:
#line 615 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier_list((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2953 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 105:
#line 622 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_static_T);
	}
#line 2961 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 106:
#line 626 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_native_T);
	}
#line 2969 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 107:
#line 630 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_abstract_T);
	}
#line 2977 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 108:
#line 634 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_override_T);
	}
#line 2985 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 109:
#line 638 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_final_T);
	}
#line 2993 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 110:
#line 645 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = access_public_T;
	}
#line 3001 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 111:
#line 649 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = access_private_T;
	}
#line 3009 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 112:
#line 653 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = access_protected_T;
	}
#line 3017 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 113:
#line 660 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[0].stringv_value));
	}
#line 3025 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 114:
#line 664 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[0].stringv_value), (yyvsp[-2].ast_value));
	}
#line 3033 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 115:
#line 671 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[-1].ast_value), (yyvsp[0].stringv_value));
	}
#line 3041 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 116:
#line 675 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[-1].ast_value), (yyvsp[0].stringv_value), (yyvsp[-3].ast_value));
	}
#line 3049 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 117:
#line 682 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[0].ast_value));
	}
#line 3057 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 118:
#line 686 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_lambda((yyvsp[-4].ast_value), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3065 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 119:
#line 690 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[0].ast_value)), (yyvsp[-2].ast_value));
	}
#line 3073 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 120:
#line 697 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 3081 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 121:
#line 701 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 3089 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 122:
#line 708 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 3097 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 123:
#line 712 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[0].ast_value), (yyvsp[-2].ast_value));
	}
#line 3105 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 124:
#line 719 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3113 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 125:
#line 726 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[0].stringv_value));
	}
#line 3121 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 126:
#line 730 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[0].stringv_value)), (yyvsp[-2].ast_value));
	}
#line 3129 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 127:
#line 739 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 3137 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 130:
#line 747 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_unary(ast_pos_T, (yyvsp[0].ast_value));
	}
#line 3145 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 131:
#line 751 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_unary(ast_neg_T, (yyvsp[0].ast_value));
	}
#line 3153 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 132:
#line 755 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_add_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3161 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 133:
#line 759 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_sub_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3169 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 134:
#line 763 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_mul_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3177 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 135:
#line 767 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_div_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3185 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 136:
#line 771 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_mod_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3193 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 137:
#line 775 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_or_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3201 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 138:
#line 779 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_equal_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3209 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 139:
#line 783 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_not_Tequal_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3217 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 140:
#line 787 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_and_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3225 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 141:
#line 791 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3233 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 142:
#line 795 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_or_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3241 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 143:
#line 799 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_and_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3249 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 144:
#line 803 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_as_Tsign_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3257 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 145:
#line 807 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_add_assign_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3265 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 146:
#line 811 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_sub_assign_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3273 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 147:
#line 815 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_mul_assign_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3281 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 148:
#line 819 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_div_assign_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3289 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 149:
#line 823 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_mod_assign_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3297 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 150:
#line 827 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_and_assign_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3305 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 151:
#line 831 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_or_assign_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3313 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 152:
#line 835 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or_assign_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3321 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 153:
#line 839 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift_assign_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3329 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 154:
#line 843 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift_assign_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3337 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 155:
#line 847 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_gt_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3345 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 156:
#line 851 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_ge_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3353 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 157:
#line 855 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_lt_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3361 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 158:
#line 859 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_le_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3369 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 159:
#line 863 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3377 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 160:
#line 867 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift_T, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3385 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 161:
#line 872 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_add, (yyvsp[-1].ast_value));
	}
#line 3393 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 162:
#line 876 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_sub, (yyvsp[-1].ast_value));
	}
#line 3401 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 163:
#line 880 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_mul, (yyvsp[-1].ast_value));
	}
#line 3409 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 164:
#line 884 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_div, (yyvsp[-1].ast_value));
	}
#line 3417 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 165:
#line 888 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_mod, (yyvsp[-1].ast_value));
	}
#line 3425 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 166:
#line 892 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_gt, (yyvsp[-1].ast_value));
	}
#line 3433 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 167:
#line 896 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_ge, (yyvsp[-1].ast_value));
	}
#line 3441 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 168:
#line 900 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_lt, (yyvsp[-1].ast_value));
	}
#line 3449 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 169:
#line 904 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_le, (yyvsp[-1].ast_value));
	}
#line 3457 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 170:
#line 908 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_eq, (yyvsp[-1].ast_value));
	}
#line 3465 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 171:
#line 912 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_noteq, (yyvsp[-1].ast_value));
	}
#line 3473 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 172:
#line 916 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_bit_or, (yyvsp[-1].ast_value));
	}
#line 3481 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 173:
#line 920 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_bit_and, (yyvsp[-1].ast_value));
	}
#line 3489 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 174:
#line 924 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_logic_or, (yyvsp[-1].ast_value));
	}
#line 3497 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 175:
#line 928 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_logic_and, (yyvsp[-1].ast_value));
	}
#line 3505 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 176:
#line 932 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_lshift, (yyvsp[-1].ast_value));
	}
#line 3513 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 177:
#line 936 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_rshift, (yyvsp[-1].ast_value));
	}
#line 3521 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 178:
#line 940 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_excor, (yyvsp[-1].ast_value));
	}
#line 3529 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 179:
#line 944 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[-4].ast_value), operator_not);
	}
#line 3537 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 180:
#line 948 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[-4].ast_value), operator_childa);
	}
#line 3545 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 181:
#line 952 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[-4].ast_value), operator_negative);
	}
#line 3553 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 182:
#line 956 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_instance_Tof((yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3561 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 183:
#line 960 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_as((yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3569 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 184:
#line 964 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_unary(ast_childa_T, (yyvsp[0].ast_value));
	}
#line 3577 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 185:
#line 968 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_unary(ast_not_T, (yyvsp[0].ast_value));
	}
#line 3585 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 186:
#line 972 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[-4].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3593 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 187:
#line 976 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), ast_new_blank());
	}
#line 3601 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 188:
#line 980 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_this();
	}
#line 3609 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 189:
#line 984 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_super();
	}
#line 3617 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 191:
#line 991 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3625 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 192:
#line 995 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[-3].ast_value), (yyvsp[-1].stringv_value), (yyvsp[0].ast_value));
	}
#line 3633 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 193:
#line 999 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3641 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 194:
#line 1003 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[-2].ast_value), ast_new_blank());
	}
#line 3649 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 199:
#line 1013 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_true();
	}
#line 3657 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 200:
#line 1017 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_false();
	}
#line 3665 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 201:
#line 1021 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_null();
	}
#line 3673 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 202:
#line 1030 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[0].ast_value));
	}
#line 3681 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 203:
#line 1034 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3689 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 204:
#line 1040 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[-1].ast_value));
	}
#line 3697 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 219:
#line 1060 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[-2].ast_value), (yyvsp[-1].stringv_value));
	}
#line 3705 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 220:
#line 1066 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 3713 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 221:
#line 1072 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 3721 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 222:
#line 1078 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_if((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3729 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 223:
#line 1082 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3737 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 224:
#line 1086 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[-2].ast_value), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3745 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 225:
#line 1090 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[-4].ast_value), (yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3753 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 227:
#line 1097 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3761 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 228:
#line 1103 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3769 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 229:
#line 1109 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_while((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3777 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 230:
#line 1115 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_break();
	}
#line 3785 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 231:
#line 1121 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_continue();
	}
#line 3793 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 232:
#line 1127 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_return((yyvsp[-1].ast_value));
	}
#line 3801 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 233:
#line 1131 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_return_empty();
	}
#line 3809 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 234:
#line 1137 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[-1].ast_value));
	}
#line 3817 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 235:
#line 1143 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_try((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3825 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 236:
#line 1149 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 3833 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 237:
#line 1153 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 3841 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 238:
#line 1159 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[-3].ast_value), (yyvsp[-2].stringv_value), (yyvsp[0].ast_value));
	}
#line 3849 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 239:
#line 1165 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3857 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 240:
#line 1169 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[-1].ast_value), ast_new_blank());
	}
#line 3865 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 241:
#line 1175 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_defer((yyvsp[0].ast_value));
	}
#line 3873 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 242:
#line 1181 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_yield_return((yyvsp[-1].ast_value));
	}
#line 3881 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 243:
#line 1187 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_yield_break();
	}
#line 3889 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 244:
#line 1193 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[-1].ast_value));
	}
#line 3897 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 245:
#line 1197 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_scope_empty();
	}
#line 3905 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 246:
#line 1203 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 3913 "beacon.tab.c" /* yacc.c:1663  */
    break;


#line 3917 "beacon.tab.c" /* yacc.c:1663  */
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
#line 1211 "beacon.y" /* yacc.c:1907  */




