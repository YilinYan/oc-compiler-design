/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

// $Id: parser.y,v 1.7 2018-11-12 14:02:13-08 - - $
// Dummy parser for scanner project.

#include <cassert>

#include "lyutils.h"
#include "astree.h"


#line 77 "yyparse.cpp" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yyparse.h".  */
#ifndef YY_YY_YYPARSE_H_INCLUDED
# define YY_YY_YYPARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_VOID = 258,
    TOK_CHAR = 259,
    TOK_INT = 260,
    TOK_STRING = 261,
    TOK_IF = 262,
    TOK_ELSE = 263,
    TOK_WHILE = 264,
    TOK_RETURN = 265,
    TOK_STRUCT = 266,
    TOK_NULL = 267,
    TOK_NEW = 268,
    TOK_ARRAY = 269,
    TOK_ARROW = 270,
    TOK_EQ = 271,
    TOK_NE = 272,
    TOK_LT = 273,
    TOK_LE = 274,
    TOK_GT = 275,
    TOK_GE = 276,
    TOK_NOT = 277,
    TOK_IDENT = 278,
    TOK_INTCON = 279,
    TOK_CHARCON = 280,
    TOK_STRINGCON = 281,
    TOK_ROOT = 282,
    TOK_BLOCK = 283,
    TOK_CALL = 284,
    TOK_IFELSE = 285,
    TOK_INITDECL = 286,
    TOK_POS = 287,
    TOK_NEG = 288,
    TOK_NEWARRAY = 289,
    TOK_TYPEID = 290,
    TOK_FIELD = 291,
    TOK_FUNCTION = 292,
    TOK_PARAM = 293,
    TOK_PROTO = 294,
    TOK_DECLID = 295,
    TOK_NEWSTR = 296,
    TOK_INDEX = 297,
    TOK_VARDECL = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YYPARSE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 172 "yyparse.cpp" /* yacc.c:358  */

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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   594

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  156

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    51,     2,     2,
      56,    57,    49,    47,    58,    48,     2,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    54,
      45,    44,    46,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    59,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,     2,    53,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    47,    47,    50,    51,    52,    53,    54,    55,    58,
      63,    65,    70,    71,    74,    76,    80,    81,    82,    83,
      87,    89,    91,    93,    97,    98,   102,   104,   108,   109,
     110,   113,   114,   117,   118,   119,   122,   127,   129,   132,
     133,   137,   138,   139,   140,   141,   142,   145,   149,   151,
     157,   158,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   175,   177,   178,   179,   180,
     181,   182,   185,   187,   190,   195,   197,   200,   201,   206,
     207,   210,   214,   215,   216,   217
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_VOID", "TOK_CHAR", "TOK_INT",
  "TOK_STRING", "TOK_IF", "TOK_ELSE", "TOK_WHILE", "TOK_RETURN",
  "TOK_STRUCT", "TOK_NULL", "TOK_NEW", "TOK_ARRAY", "TOK_ARROW", "TOK_EQ",
  "TOK_NE", "TOK_LT", "TOK_LE", "TOK_GT", "TOK_GE", "TOK_NOT", "TOK_IDENT",
  "TOK_INTCON", "TOK_CHARCON", "TOK_STRINGCON", "TOK_ROOT", "TOK_BLOCK",
  "TOK_CALL", "TOK_IFELSE", "TOK_INITDECL", "TOK_POS", "TOK_NEG",
  "TOK_NEWARRAY", "TOK_TYPEID", "TOK_FIELD", "TOK_FUNCTION", "TOK_PARAM",
  "TOK_PROTO", "TOK_DECLID", "TOK_NEWSTR", "TOK_INDEX", "TOK_VARDECL",
  "'='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'['", "'}'",
  "';'", "'{'", "'('", "')'", "','", "']'", "$accept", "start", "program",
  "globaldecl", "structdef", "structhaf", "fielddecl", "basetype",
  "function", "param", "identdecl", "fnbody", "fnbodya", "fnbodyb",
  "localdecl", "block", "blockhaf", "statement", "while", "ifelse",
  "return", "expr", "allocation", "call", "callhaf", "variable",
  "constant", YY_NULLPTR
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
     295,   296,   297,   298,    61,    60,    62,    43,    45,    42,
      47,    37,    91,   125,    59,   123,    40,    41,    44,    93
};
# endif

#define YYPACT_NINF -54

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-54)))

#define YYTABLE_NINF -20

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -54,     9,   108,   -54,    36,   -54,   -54,   -54,    -9,   -54,
     -54,   -54,    73,   -54,   -28,   -54,   -54,    -5,    23,   -54,
      -4,     7,    41,    12,    20,   -54,   -54,   -54,   -54,   -54,
      14,    52,   -54,    66,    26,   -54,    30,    74,   -54,    48,
     -54,   -54,    69,   -54,   123,   143,   -54,   -54,   -54,   -54,
      81,   -54,   -54,    56,    59,   331,    80,   336,    13,   336,
     336,   -54,   -54,   193,   336,    83,   -54,   -54,   213,   -54,
     -54,   -54,   -54,   480,   -54,   -54,    86,   -54,   -54,   -54,
     -54,   -54,    62,   -54,   -54,   -54,   336,   336,   -54,   491,
      78,    99,   102,   -10,   268,   -10,   -10,   -54,   -54,   374,
     336,   -54,   -54,   134,   336,   336,   336,   336,   336,   336,
     336,   336,   336,   336,   336,   336,   336,   -54,   -54,   336,
     388,   427,   -54,   336,   336,   -54,   542,   -54,   502,   -54,
      90,    90,    90,    90,   542,    90,    90,   -12,   -12,   -10,
     -10,   -10,   282,   542,   263,   263,   441,   321,   -54,   -54,
     150,   -54,   -54,   -54,   263,   -54
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       8,     0,     0,     1,     0,    16,    17,    18,     0,    19,
       5,     3,     0,     4,     0,     6,     7,     0,     0,    26,
       0,     0,     0,     0,     0,    27,    85,    82,    83,    84,
       0,     0,    25,     0,     0,    10,     0,     0,    11,     0,
       9,    22,     0,    20,     0,     0,    23,    21,    24,    12,
       0,    14,    13,     0,     0,     0,     0,     0,    79,     0,
       0,    28,    46,     0,     0,     0,    31,    41,     0,    33,
      42,    43,    44,     0,    71,    67,     0,    69,    70,    30,
      32,    35,    79,    29,    34,    15,     0,     0,    51,     0,
      18,    72,     0,    66,     0,    64,    65,    37,    40,     0,
       0,    38,    39,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    45,    76,     0,
       0,     0,    50,     0,     0,    75,    78,    68,     0,    81,
      53,    54,    55,    56,    52,    57,    58,    59,    60,    61,
      62,    63,     0,    77,     0,     0,     0,     0,    36,    80,
      48,    47,    73,    74,     0,    49
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -54,   -54,   -54,   -54,   -54,   -54,   135,    21,   -54,   -54,
      46,   127,   -54,   -54,   117,   -54,   -54,   -44,   -54,   -54,
     -54,   -53,   -54,   -54,   -54,   -54,   142
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    10,    11,    24,    36,    12,    13,    22,
      65,    43,    44,    45,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      81,    84,    89,   103,    93,   103,    95,    96,    26,     3,
       5,    99,     6,     7,    17,     5,    20,     6,     7,    98,
      27,    28,    29,     5,   102,     6,     7,   -19,    21,     5,
       9,     6,     7,   120,   121,     9,   -19,   113,   114,   115,
     116,   126,   116,     9,    37,    37,    25,   128,    14,     9,
      23,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,    31,    35,   143,    32,    40,    94,
     146,   147,     5,    38,     6,     7,    53,    92,    54,    55,
      48,    26,    56,     5,    49,     6,    90,    18,    50,    15,
      16,    57,    58,    27,    28,    29,    19,    51,    33,    34,
     150,   151,    52,    91,    85,   103,    41,    42,    -2,     4,
     155,     5,    86,     6,     7,    87,    59,    60,    94,     8,
      46,    42,    61,    62,    63,    64,     5,   100,     6,     7,
      53,     9,    54,    55,   123,    26,    56,   111,   112,   113,
     114,   115,   116,   118,   119,    57,    58,    27,    28,    29,
      53,   -19,    54,    55,   124,    26,    56,   129,   154,    39,
      47,    80,    30,     0,     0,    57,    82,    27,    28,    29,
      59,    60,     0,     0,     0,     0,    79,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      59,    60,     0,     0,     0,     0,    83,    62,    63,    64,
      53,     0,    54,    55,     0,    26,    56,     0,     0,     0,
       0,     0,     0,     0,     0,    57,    82,    27,    28,    29,
      53,     0,    54,    55,     0,    26,    56,     0,     0,     0,
       0,     0,     0,     0,     0,    57,    82,    27,    28,    29,
      59,    60,     0,     0,     0,     0,    97,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      59,    60,     0,     0,     0,     0,   101,    62,    63,    64,
      53,     0,    54,    55,     0,    26,    56,     0,     0,     0,
      26,    56,     0,     0,     0,    57,    82,    27,    28,    29,
      57,    82,    27,    28,    29,     0,     0,   103,   104,   105,
       0,   106,     0,   107,     0,     0,     0,     0,     0,     0,
      59,    60,     0,     0,     0,    59,    60,    62,    63,    64,
       0,     0,     0,     0,    64,   125,   108,   109,   110,   111,
     112,   113,   114,   115,   116,     0,   103,   104,   105,     0,
     106,   149,   107,    26,    56,     0,     0,     0,    26,    56,
       0,     0,     0,    57,    82,    27,    28,    29,    57,    82,
      27,    28,    29,     0,     0,   108,   109,   110,   111,   112,
     113,   114,   115,   116,     0,     0,     0,     0,    59,    60,
     153,     0,     0,    59,    60,    88,     0,    64,     0,   103,
     104,   105,    64,   106,     0,   107,     0,     0,     0,     0,
       0,     0,     0,   103,   104,   105,     0,   106,     0,   107,
       0,     0,     0,     0,     0,     0,     0,     0,   108,   109,
     110,   111,   112,   113,   114,   115,   116,     0,     0,     0,
       0,   127,   108,   109,   110,   111,   112,   113,   114,   115,
     116,     0,   103,   104,   105,   144,   106,     0,   107,     0,
       0,     0,     0,     0,     0,     0,   103,   104,   105,     0,
     106,     0,   107,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,   114,   115,   116,
       0,     0,     0,     0,   145,   108,   109,   110,   111,   112,
     113,   114,   115,   116,     0,   103,   104,   105,   152,   106,
       0,   107,     0,     0,     0,     0,   103,   104,   105,     0,
     106,     0,   107,     0,     0,     0,     0,   103,   104,   105,
       0,   106,     0,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,     0,   117,   108,   109,   110,   111,   112,
     113,   114,   115,   116,     0,   122,   108,   109,   110,   111,
     112,   113,   114,   115,   116,     0,   148,   103,   104,   105,
       0,   106,     0,   107,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,   114,   115,   116
};

static const yytype_int16 yycheck[] =
{
      44,    45,    55,    15,    57,    15,    59,    60,    12,     0,
       3,    64,     5,     6,    23,     3,    44,     5,     6,    63,
      24,    25,    26,     3,    68,     5,     6,    14,    56,     3,
      23,     5,     6,    86,    87,    23,    23,    49,    50,    51,
      52,    94,    52,    23,    23,    24,    23,   100,     2,    23,
      55,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,    57,    53,   119,    21,    54,    56,
     123,   124,     3,    53,     5,     6,     7,    56,     9,    10,
      34,    12,    13,     3,    54,     5,     6,    14,    14,    53,
      54,    22,    23,    24,    25,    26,    23,    23,    57,    58,
     144,   145,    54,    23,    23,    15,    54,    55,     0,     1,
     154,     3,    56,     5,     6,    56,    47,    48,    56,    11,
      54,    55,    53,    54,    55,    56,     3,    44,     5,     6,
       7,    23,     9,    10,    56,    12,    13,    47,    48,    49,
      50,    51,    52,    57,    58,    22,    23,    24,    25,    26,
       7,    52,     9,    10,    52,    12,    13,    23,     8,    24,
      33,    44,    20,    -1,    -1,    22,    23,    24,    25,    26,
      47,    48,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
       7,    -1,     9,    10,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,
       7,    -1,     9,    10,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,
      47,    48,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
       7,    -1,     9,    10,    -1,    12,    13,    -1,    -1,    -1,
      12,    13,    -1,    -1,    -1,    22,    23,    24,    25,    26,
      22,    23,    24,    25,    26,    -1,    -1,    15,    16,    17,
      -1,    19,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    47,    48,    54,    55,    56,
      -1,    -1,    -1,    -1,    56,    57,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    -1,    15,    16,    17,    -1,
      19,    59,    21,    12,    13,    -1,    -1,    -1,    12,    13,
      -1,    -1,    -1,    22,    23,    24,    25,    26,    22,    23,
      24,    25,    26,    -1,    -1,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    47,    48,
      59,    -1,    -1,    47,    48,    54,    -1,    56,    -1,    15,
      16,    17,    56,    19,    -1,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    16,    17,    -1,    19,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    -1,    -1,
      -1,    57,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    -1,    15,    16,    17,    57,    19,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,    -1,
      19,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    -1,    57,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    15,    16,    17,    57,    19,
      -1,    21,    -1,    -1,    -1,    -1,    15,    16,    17,    -1,
      19,    -1,    21,    -1,    -1,    -1,    -1,    15,    16,    17,
      -1,    19,    -1,    21,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    54,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    54,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    -1,    54,    15,    16,    17,
      -1,    19,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,
      48,    49,    50,    51,    52
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    61,    62,     0,     1,     3,     5,     6,    11,    23,
      63,    64,    67,    68,    70,    53,    54,    23,    14,    23,
      44,    56,    69,    55,    65,    23,    12,    24,    25,    26,
      86,    57,    70,    57,    58,    53,    66,    67,    53,    66,
      54,    54,    55,    71,    72,    73,    54,    71,    70,    54,
      14,    23,    54,     7,     9,    10,    13,    22,    23,    47,
      48,    53,    54,    55,    56,    70,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    53,
      74,    77,    23,    53,    77,    23,    56,    56,    54,    81,
       6,    23,    67,    81,    56,    81,    81,    53,    77,    81,
      44,    53,    77,    15,    16,    17,    19,    21,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    54,    57,    58,
      81,    81,    54,    56,    52,    57,    81,    57,    81,    23,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    57,    57,    81,    81,    54,    59,
      77,    77,    57,    59,     8,    77
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    62,    62,    62,    62,    62,    62,    63,
      64,    64,    65,    65,    66,    66,    67,    67,    67,    67,
      68,    68,    68,    68,    69,    69,    70,    70,    71,    71,
      71,    72,    72,    73,    73,    73,    74,    75,    75,    76,
      76,    77,    77,    77,    77,    77,    77,    78,    79,    79,
      80,    80,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    82,    82,    82,    83,    83,    84,    84,    85,
      85,    85,    86,    86,    86,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     3,     3,     0,     4,
       4,     4,     3,     3,     2,     3,     1,     1,     1,     1,
       4,     4,     4,     4,     3,     2,     2,     3,     2,     2,
       2,     2,     2,     2,     2,     2,     4,     2,     2,     2,
       2,     1,     1,     1,     1,     2,     1,     5,     5,     7,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     1,     3,     1,
       1,     1,     2,     5,     5,     3,     2,     3,     3,     1,
       4,     3,     1,     1,     1,     1
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
          case 3: /* TOK_VOID  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 862 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 4: /* TOK_CHAR  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 868 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 5: /* TOK_INT  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 874 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 6: /* TOK_STRING  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 880 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 7: /* TOK_IF  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 886 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 8: /* TOK_ELSE  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 892 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 9: /* TOK_WHILE  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 898 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 10: /* TOK_RETURN  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 904 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 11: /* TOK_STRUCT  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 910 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 12: /* TOK_NULL  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 916 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 13: /* TOK_NEW  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 922 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 14: /* TOK_ARRAY  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 928 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 15: /* TOK_ARROW  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 934 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 16: /* TOK_EQ  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 940 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 17: /* TOK_NE  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 946 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 18: /* TOK_LT  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 952 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 19: /* TOK_LE  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 958 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 20: /* TOK_GT  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 964 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 21: /* TOK_GE  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 970 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 22: /* TOK_NOT  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 976 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 23: /* TOK_IDENT  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 982 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 24: /* TOK_INTCON  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 988 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 25: /* TOK_CHARCON  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 994 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 26: /* TOK_STRINGCON  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1000 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 27: /* TOK_ROOT  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1006 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 28: /* TOK_BLOCK  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1012 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 29: /* TOK_CALL  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1018 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 30: /* TOK_IFELSE  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1024 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 31: /* TOK_INITDECL  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1030 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 32: /* TOK_POS  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1036 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 33: /* TOK_NEG  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1042 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 34: /* TOK_NEWARRAY  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1048 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 35: /* TOK_TYPEID  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1054 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 36: /* TOK_FIELD  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1060 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 37: /* TOK_FUNCTION  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1066 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 38: /* TOK_PARAM  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1072 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 39: /* TOK_PROTO  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1078 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 40: /* TOK_DECLID  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1084 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 41: /* TOK_NEWSTR  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1090 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 42: /* TOK_INDEX  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1096 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 43: /* TOK_VARDECL  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1102 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 44: /* '='  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1108 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 45: /* '<'  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1114 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 46: /* '>'  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1120 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 47: /* '+'  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1126 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 48: /* '-'  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1132 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 49: /* '*'  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1138 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 50: /* '/'  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1144 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 51: /* '%'  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1150 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 52: /* '['  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1156 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 53: /* '}'  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1162 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 54: /* ';'  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1168 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 55: /* '{'  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1174 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 56: /* '('  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1180 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 57: /* ')'  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1186 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 58: /* ','  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1192 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 59: /* ']'  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1198 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 61: /* start  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1204 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 62: /* program  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1210 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 63: /* globaldecl  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1216 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 64: /* structdef  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1222 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 65: /* structhaf  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1228 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 66: /* fielddecl  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1234 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 67: /* basetype  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1240 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 68: /* function  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1246 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 69: /* param  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1252 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 70: /* identdecl  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1258 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 71: /* fnbody  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1264 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 72: /* fnbodya  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1270 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 73: /* fnbodyb  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1276 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 74: /* localdecl  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1282 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 75: /* block  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1288 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 76: /* blockhaf  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1294 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 77: /* statement  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1300 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 78: /* while  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1306 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 79: /* ifelse  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1312 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 80: /* return  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1318 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 81: /* expr  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1324 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 82: /* allocation  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1330 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 83: /* call  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1336 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 84: /* callhaf  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1342 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 85: /* variable  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1348 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 86: /* constant  */
#line 18 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1354 "yyparse.cpp" /* yacc.c:684  */
        break;


      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

/* User initialization code.  */
#line 19 "parser.y" /* yacc.c:1429  */
{
   parser::root = new astree (TOK_ROOT, {0, 0, 0}, "");
}

#line 1779 "yyparse.cpp" /* yacc.c:1429  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 47 "parser.y" /* yacc.c:1646  */
    { yyparse_astree = (yyvsp[0]); }
#line 1961 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 50 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 1967 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 51 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 1973 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 52 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 1979 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 53 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2]); }
#line 1985 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 54 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2]); }
#line 1991 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 55 "parser.y" /* yacc.c:1646  */
    { (yyval) = parser::root; }
#line 1997 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 58 "parser.y" /* yacc.c:1646  */
    { (yyval) = ((yyvsp[-2])->change_sym(
                                           TOK_VARDECL))->
                                           adopt((yyvsp[-3]), (yyvsp[-1])); }
#line 2005 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 63 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-3])->adopt_new((yyvsp[-2]), 
                                           TOK_TYPEID); }
#line 2012 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 66 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-3])->adopt((yyvsp[-2])->change_sym
                                           (TOK_TYPEID), (yyvsp[-1])); }
#line 2019 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 70 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2])->adopt((yyvsp[-1])); }
#line 2025 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 71 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2])->adopt((yyvsp[-1])); }
#line 2031 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 74 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt_new((yyvsp[0]), 
                                           TOK_FIELD); }
#line 2038 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 76 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), 
                                           (yyvsp[0])->change_sym(TOK_FIELD));}
#line 2045 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 80 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2051 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 81 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2057 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 82 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2063 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 83 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0])->change_sym(
                                           TOK_TYPEID); }
#line 2070 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 87 "parser.y" /* yacc.c:1646  */
    { (yyval) = astree::function_(
                                           (yyvsp[-3]), (yyvsp[-2]), (yyvsp[0])); }
#line 2077 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 89 "parser.y" /* yacc.c:1646  */
    { (yyval) = astree::function_(
                                           (yyvsp[-3]), (yyvsp[-2]), (yyvsp[0])); }
#line 2084 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 91 "parser.y" /* yacc.c:1646  */
    { (yyval) = astree::function_(
                                           (yyvsp[-3]), (yyvsp[-2])); }
#line 2091 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 93 "parser.y" /* yacc.c:1646  */
    { (yyval) = astree::function_(
                                           (yyvsp[-3]), (yyvsp[-2])); }
#line 2098 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 97 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2])->adopt((yyvsp[0])); }
#line 2104 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 98 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt_sym((yyvsp[0]), 
                                           TOK_PARAM); }
#line 2111 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 102 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt_new((yyvsp[0]), 
                                           TOK_DECLID); }
#line 2118 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 104 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])->
                                           change_sym(TOK_DECLID));}
#line 2125 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 108 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 2131 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 109 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 2137 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 110 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 2143 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 113 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 2149 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 114 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 2155 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 117 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 2161 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 118 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 2167 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 119 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 2173 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 122 "parser.y" /* yacc.c:1646  */
    { (yyval) = ((yyvsp[-2])->change_sym(
                                           TOK_VARDECL))->
                                           adopt((yyvsp[-3]), (yyvsp[-1])); }
#line 2181 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 127 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->change_sym(
                                           TOK_BLOCK); }
#line 2188 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 129 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 2194 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 132 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 2200 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 133 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt_sym((yyvsp[0]), 
                                           TOK_BLOCK); }
#line 2207 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 137 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2213 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 138 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2219 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 139 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2225 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 140 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2231 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 141 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 2237 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 142 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2243 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 146 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-4])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2249 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 149 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-4])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2255 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 152 "parser.y" /* yacc.c:1646  */
    { (yyval) = ((yyvsp[-6])->adopt((yyvsp[-4]), (yyvsp[-2])))->
                                           adopt((yyvsp[0])); }
#line 2262 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 157 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2])->adopt((yyvsp[-1])); }
#line 2268 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 158 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 2274 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 161 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2280 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 162 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2286 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 163 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2292 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 164 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2298 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 165 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2304 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 166 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2310 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 167 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2316 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 168 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2322 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 169 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2328 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 170 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2334 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 171 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2340 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 172 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2346 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 173 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt_sym((yyvsp[0]), 
                                           TOK_POS); }
#line 2353 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 175 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt_sym((yyvsp[0]), 
                                           TOK_NEG); }
#line 2360 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 177 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 2366 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 178 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2372 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 179 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 2378 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 180 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2384 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 181 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2390 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 182 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2396 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 185 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt_new((yyvsp[0]), 
                                           TOK_TYPEID); }
#line 2403 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 188 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-4])->adopt_sym((yyvsp[-1]), 
                                           TOK_NEWSTR); }
#line 2410 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 190 "parser.y" /* yacc.c:1646  */
    { (yyval) = ((yyvsp[-4])->change_sym(
                                           TOK_NEWARRAY))->
                                           adopt((yyvsp[-3]), (yyvsp[-1])); }
#line 2418 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 195 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt_sym((yyvsp[-2]), 
                                           TOK_CALL); }
#line 2425 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 197 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 2431 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 200 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2])->adopt((yyvsp[0])); }
#line 2437 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 201 "parser.y" /* yacc.c:1646  */
    { (yyval) = ((yyvsp[-1])->change_sym(
                                           TOK_CALL))->
                                           adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2445 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 206 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2451 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 207 "parser.y" /* yacc.c:1646  */
    { (yyval) = ((yyvsp[-2])->change_sym(
                                           TOK_INDEX))->
                                           adopt((yyvsp[-3]), (yyvsp[-1])); }
#line 2459 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 210 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])->
                                           change_sym(TOK_FIELD)); }
#line 2466 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 214 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2472 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 215 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2478 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 216 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2484 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 217 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2490 "yyparse.cpp" /* yacc.c:1646  */
    break;


#line 2494 "yyparse.cpp" /* yacc.c:1646  */
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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
#line 219 "parser.y" /* yacc.c:1906  */


const char *parser::get_tname (int symbol) {
   return yytname [YYTRANSLATE (symbol)];
}

bool is_defined_token (int symbol) {
   return YYTRANSLATE (symbol) > YYUNDEFTOK;
}

astree* astree::function_ (astree* a, astree* b, astree *c) {
    astree* func = new astree(TOK_PROTO, a->lloc, "");
    b->change_sym(TOK_PARAM);
    func->adopt(a, b);
    if(c != nullptr) {
        func->change_sym(TOK_FUNCTION);
        func->adopt_new(c, TOK_BLOCK);
    }
    return func;
}
