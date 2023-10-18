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
#line 1 "alfa.y" /* yacc.c:339  */

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "alfa.h"
    #include "generacion.h"
    #include "tablaSimbolos.h"
    void yyerror(char * s);
    int yylex(void);
    extern int line, col;
    extern int yyleng;
    extern char* yytext;
    extern int morph_error;
    extern FILE *out;
    extern TablaSimbolos *ts;
    
    int tipo_actual;
    int clase_actual;
    int tamanio_vector_actual;
    int pos_variable_local_actual;
    int num_parametros_actual;
    int pos_parametro_actual;
    int num_variables_locales_actual;
    
    int en_explist;
    int num_parametros_llamada_actual;

    int etiqueta = 0, etiq_actual = 0;
    int retorno = 0;

    // Array auxiliar
    char aux_lex[2*BUFFER_SIZE], aux_vector_index[2*BUFFER_SIZE];
    

#line 101 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    TOK_MAIN = 258,
    TOK_INT = 259,
    TOK_BOOLEAN = 260,
    TOK_ARRAY = 261,
    TOK_FUNCTION = 262,
    TOK_IF = 263,
    TOK_ELSE = 264,
    TOK_WHILE = 265,
    TOK_SCANF = 266,
    TOK_PRINTF = 267,
    TOK_RETURN = 268,
    TOK_PUNTOYCOMA = 269,
    TOK_COMA = 270,
    TOK_PARENTESISIZQUIERDO = 271,
    TOK_PARENTESISDERECHO = 272,
    TOK_CORCHETEIZQUIERDO = 273,
    TOK_CORCHETEDERECHO = 274,
    TOK_LLAVEIZQUIERDA = 275,
    TOK_LLAVEDERECHA = 276,
    TOK_ASIGNACION = 277,
    TOK_MAS = 278,
    TOK_MENOS = 279,
    TOK_DIVISION = 280,
    TOK_ASTERISCO = 281,
    TOK_AND = 282,
    TOK_OR = 283,
    TOK_NOT = 284,
    TOK_IGUAL = 285,
    TOK_DISTINTO = 286,
    TOK_MENORIGUAL = 287,
    TOK_MAYORIGUAL = 288,
    TOK_MENOR = 289,
    TOK_MAYOR = 290,
    TOK_DO = 291,
    TOK_IDENTIFICADOR = 292,
    TOK_CONSTANTE_ENTERA = 293,
    TOK_TRUE = 294,
    TOK_FALSE = 295,
    TOK_ERROR = 296
  };
#endif
/* Tokens.  */
#define TOK_MAIN 258
#define TOK_INT 259
#define TOK_BOOLEAN 260
#define TOK_ARRAY 261
#define TOK_FUNCTION 262
#define TOK_IF 263
#define TOK_ELSE 264
#define TOK_WHILE 265
#define TOK_SCANF 266
#define TOK_PRINTF 267
#define TOK_RETURN 268
#define TOK_PUNTOYCOMA 269
#define TOK_COMA 270
#define TOK_PARENTESISIZQUIERDO 271
#define TOK_PARENTESISDERECHO 272
#define TOK_CORCHETEIZQUIERDO 273
#define TOK_CORCHETEDERECHO 274
#define TOK_LLAVEIZQUIERDA 275
#define TOK_LLAVEDERECHA 276
#define TOK_ASIGNACION 277
#define TOK_MAS 278
#define TOK_MENOS 279
#define TOK_DIVISION 280
#define TOK_ASTERISCO 281
#define TOK_AND 282
#define TOK_OR 283
#define TOK_NOT 284
#define TOK_IGUAL 285
#define TOK_DISTINTO 286
#define TOK_MENORIGUAL 287
#define TOK_MAYORIGUAL 288
#define TOK_MENOR 289
#define TOK_MAYOR 290
#define TOK_DO 291
#define TOK_IDENTIFICADOR 292
#define TOK_CONSTANTE_ENTERA 293
#define TOK_TRUE 294
#define TOK_FALSE 295
#define TOK_ERROR 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 36 "alfa.y" /* yacc.c:355  */
 tipo_atributos atributos; 

#line 226 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 243 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   167

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  165

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   121,   121,   130,   138,   145,   150,   151,   152,   154,
     159,   165,   167,   172,   179,   184,   185,   187,   188,   191,
     229,   254,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   294,   295,   297,
     328,   360,   396,   408,   415,   422,   430,   437,   448,   454,
     470,   477,   485,   537,   542,   553,   564,   575,   586,   597,
     608,   619,   630,   643,   685,   694,   703,   712,   724,   754,
     790,   795,   797,   802,   804,   818,   832,   846,   860,   874,
     889,   898,   908,   915,   923,   931,   936,   938,   979
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_MAIN", "TOK_INT", "TOK_BOOLEAN",
  "TOK_ARRAY", "TOK_FUNCTION", "TOK_IF", "TOK_ELSE", "TOK_WHILE",
  "TOK_SCANF", "TOK_PRINTF", "TOK_RETURN", "TOK_PUNTOYCOMA", "TOK_COMA",
  "TOK_PARENTESISIZQUIERDO", "TOK_PARENTESISDERECHO",
  "TOK_CORCHETEIZQUIERDO", "TOK_CORCHETEDERECHO", "TOK_LLAVEIZQUIERDA",
  "TOK_LLAVEDERECHA", "TOK_ASIGNACION", "TOK_MAS", "TOK_MENOS",
  "TOK_DIVISION", "TOK_ASTERISCO", "TOK_AND", "TOK_OR", "TOK_NOT",
  "TOK_IGUAL", "TOK_DISTINTO", "TOK_MENORIGUAL", "TOK_MAYORIGUAL",
  "TOK_MENOR", "TOK_MAYOR", "TOK_DO", "TOK_IDENTIFICADOR",
  "TOK_CONSTANTE_ENTERA", "TOK_TRUE", "TOK_FALSE", "TOK_ERROR", "$accept",
  "programa", "init_ts", "escritura1", "escritura2", "declaraciones",
  "declaracion", "clase", "clase_escalar", "tipo", "clase_vector",
  "identificadores", "funciones", "fn_name", "fn_declaration", "funcion",
  "parametros_funcion", "resto_parametros_funcion", "parametro_funcion",
  "declaraciones_funcion", "sentencias", "sentencia", "sentencia_simple",
  "bloque", "asignacion", "elemento_vector", "if_exp", "if_else",
  "condicional", "bucle_inicio", "bucle_exp", "bucle", "bucle_do_inicio",
  "bucle_do_sentencia", "lectura", "escritura", "retorno_funcion", "exp",
  "idf_llamada_funcion", "lista_expresiones", "resto_lista_expresiones",
  "comparacion", "constante", "constante_logica", "constante_entera",
  "numero", "identificador", "idpf", YY_NULLPTR
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
     295,   296
};
# endif

#define YYPACT_NINF -38

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-38)))

#define YYTABLE_NINF -70

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -38,    22,    21,   -38,     5,     3,   -38,   -38,    -1,   -38,
       3,   -11,   -38,   -38,   -38,    17,    29,   -38,   -38,    23,
      25,     6,    -1,   -38,    27,     2,    29,   -38,   -11,    30,
       4,     2,    -1,    32,   -38,    15,    18,    18,   -38,   -16,
      33,     2,    51,   -38,   -38,    44,    50,    56,   -38,    61,
      62,   -38,    60,    64,   -38,   -38,   -38,   -38,   -38,   -38,
     -38,    65,    45,    66,    80,    18,   -38,    18,    18,    18,
       0,   -38,   -38,   -38,   -38,    73,    71,   -38,   -38,   -38,
      68,    73,    18,    18,   -38,   -38,   -38,    18,    83,     2,
      18,    84,     2,    99,   -38,   -38,   -38,    90,    -1,   -38,
      73,    95,    97,    -5,   -38,    18,    18,    18,    18,    18,
      18,    18,   -38,   124,    73,    73,     2,    94,    73,     2,
     -38,   100,     3,    80,   -38,    18,    18,    18,    18,    18,
      18,   -38,    -5,    -5,   -38,   -38,   130,   109,    36,   107,
     -38,   123,   -38,   125,    18,   -38,   -38,   -38,    73,    73,
      73,    73,    73,    73,    18,   -38,   -38,   136,   -38,   114,
      36,   -38,   143,   -38,   -38
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,    12,    13,     0,     4,
       6,     0,     9,    11,    10,     0,    18,     7,    87,     0,
      15,     0,     0,     5,     0,     0,    18,     8,     0,     0,
       0,     0,    23,     0,    46,     0,     0,     0,    50,     0,
       0,    29,     0,    32,    33,     0,     0,     0,    37,     0,
       0,    38,     0,     0,    34,    35,    36,    17,    16,    14,
      19,     0,     0,     0,    25,     0,    52,     0,     0,     0,
      63,    85,    82,    83,    67,    53,     0,    64,    80,    81,
      84,    54,     0,     0,    21,    30,    31,     0,     0,     0,
       0,     0,     0,     0,     2,    88,    26,     0,     0,    22,
      42,     0,     0,    59,    62,     0,     0,     0,     0,     0,
       0,    71,    86,     0,    39,    40,     0,     0,    47,     0,
      51,     0,    28,    25,    65,     0,     0,     0,     0,     0,
       0,    66,    55,    56,    57,    58,    60,    61,    73,     0,
      41,     0,    45,     0,     0,    27,    20,    24,    74,    75,
      76,    77,    78,    79,     0,    70,    68,    44,    48,     0,
      73,    43,     0,    72,    49
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -38,   -38,   -38,   -38,   -38,    -9,   -38,   -38,   -38,    -3,
     -38,   131,   132,   -38,   -38,   -38,   -38,    37,    63,   -38,
      -8,   -38,   -38,   -38,   -38,   -14,   -38,   -38,   -38,   -38,
     -38,   -38,   -38,   -38,   -38,   -38,   -38,   -37,   -38,   -38,
       7,   -38,   -38,   -38,   -38,   -38,   -38,   -38
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    16,    31,     9,    10,    11,    12,    13,
      14,    19,    23,    24,    25,    26,    63,    99,    64,   146,
      40,    41,    42,    43,    44,    74,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    75,    76,   139,
     155,   102,    77,    78,    79,    80,    20,    96
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      81,    17,    82,     6,     7,    15,    83,     6,     7,     8,
      33,    45,    34,    35,    36,    37,   -69,    45,    82,    30,
     107,   108,     3,    61,     4,     5,    18,    45,   100,    62,
     101,   103,   104,    85,    67,    21,    22,    27,    38,    39,
      28,    60,    68,    32,    29,   113,   114,    69,    65,    59,
     115,   154,    66,   118,    84,    70,    71,    72,    73,   105,
     106,   107,   108,   109,   110,    86,    87,    88,   132,   133,
     134,   135,   136,   137,   138,    45,    89,    90,    45,    91,
      92,   117,    95,    97,   120,    93,    94,   111,   148,   149,
     150,   151,   152,   153,    98,    62,   105,   106,   107,   108,
     109,   110,    45,   116,   119,    45,   112,   159,   141,   121,
     122,   143,   124,   145,   131,   142,   144,   160,   105,   106,
     107,   108,   109,   110,   156,   125,   126,   127,   128,   129,
     130,   162,   105,   106,   107,   108,   109,   105,   106,   107,
     108,   109,   110,   140,   157,   161,   158,   105,   106,   107,
     108,   109,   110,   105,   106,   107,   108,   164,    57,    58,
     147,   123,     0,     0,     0,     0,     0,   163
};

static const yytype_int16 yycheck[] =
{
      37,    10,    18,     4,     5,     8,    22,     4,     5,     6,
       8,    25,    10,    11,    12,    13,    16,    31,    18,    22,
      25,    26,     0,    31,     3,    20,    37,    41,    65,    32,
      67,    68,    69,    41,    16,    18,     7,    14,    36,    37,
      15,    37,    24,    16,    38,    82,    83,    29,    16,    19,
      87,    15,    37,    90,    21,    37,    38,    39,    40,    23,
      24,    25,    26,    27,    28,    14,    22,    17,   105,   106,
     107,   108,   109,   110,   111,    89,    20,    16,    92,    17,
      20,    89,    37,    17,    92,    21,    21,    16,   125,   126,
     127,   128,   129,   130,    14,    98,    23,    24,    25,    26,
      27,    28,   116,    20,    20,   119,    38,   144,   116,    10,
      20,   119,    17,   122,    17,    21,    16,   154,    23,    24,
      25,    26,    27,    28,    17,    30,    31,    32,    33,    34,
      35,    17,    23,    24,    25,    26,    27,    23,    24,    25,
      26,    27,    28,    19,    21,     9,    21,    23,    24,    25,
      26,    27,    28,    23,    24,    25,    26,    14,    26,    28,
     123,    98,    -1,    -1,    -1,    -1,    -1,   160
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    43,    44,     0,     3,    20,     4,     5,     6,    47,
      48,    49,    50,    51,    52,    51,    45,    47,    37,    53,
      88,    18,     7,    54,    55,    56,    57,    14,    15,    38,
      51,    46,    16,     8,    10,    11,    12,    13,    36,    37,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    54,    53,    19,
      37,    62,    51,    58,    60,    16,    37,    16,    24,    29,
      37,    38,    39,    40,    67,    79,    80,    84,    85,    86,
      87,    79,    18,    22,    21,    62,    14,    22,    17,    20,
      16,    17,    20,    21,    21,    37,    89,    17,    14,    59,
      79,    79,    83,    79,    79,    23,    24,    25,    26,    27,
      28,    16,    38,    79,    79,    79,    20,    62,    79,    20,
      62,    10,    20,    60,    17,    30,    31,    32,    33,    34,
      35,    17,    79,    79,    79,    79,    79,    79,    79,    81,
      19,    62,    21,    62,    16,    47,    61,    59,    79,    79,
      79,    79,    79,    79,    15,    82,    17,    21,    21,    79,
      79,     9,    17,    82,    14
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    45,    46,    47,    47,    48,    49,
      49,    50,    51,    51,    52,    53,    53,    54,    54,    55,
      56,    57,    58,    58,    59,    59,    60,    61,    61,    62,
      62,    63,    63,    64,    64,    64,    64,    65,    65,    66,
      66,    67,    68,    69,    70,    70,    71,    72,    73,    73,
      74,    75,    76,    77,    78,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    80,
      81,    81,    82,    82,    83,    83,    83,    83,    83,    83,
      84,    84,    85,    85,    86,    87,    87,    88,    89
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     9,     0,     0,     0,     1,     2,     3,     1,
       1,     1,     1,     1,     5,     1,     3,     2,     0,     3,
       6,     3,     2,     0,     3,     0,     2,     1,     0,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     4,     3,     6,     5,     4,     1,     3,     5,     7,
       1,     3,     2,     2,     2,     3,     3,     3,     3,     2,
       3,     3,     2,     1,     1,     3,     3,     1,     4,     1,
       2,     0,     3,     0,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     2,     1,     1
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
  YYUSE (yytype);
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
#line 122 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(out, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> }\n");

        /*Llamada a funciones para escribir el fin del fichero fichero_ensamblador*/
        escribir_fin(out);
    }
#line 1452 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 130 "alfa.y" /* yacc.c:1646  */
    { 
        /* Regla auxiliar para inicializar tabla y subseccion data/bss */
        ts = initTablaSimbolos();
        escribir_subseccion_data(out);
        escribir_cabecera_bss(out);
    }
#line 1463 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 138 "alfa.y" /* yacc.c:1646  */
    {
        /*Llamada a funciones para escribir la sección data con los mensajes generales, y la tabla de símbolos así como todo lo necesario para que
          lo siguiente que haya que escribirse sea "main:"*/
        escribir_segmento_codigo(out);
    }
#line 1473 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 145 "alfa.y" /* yacc.c:1646  */
    {
        /*Llamar a funcion que escribe inicio main*/
        escribir_inicio_main(out);
    }
#line 1482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 150 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R2:\t<declaraciones> ::= <declaracion>\n");}
#line 1488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 151 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n");}
#line 1494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 152 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R4:\t<declaracion> ::= <clase> <identificadores> ;\n");}
#line 1500 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 155 "alfa.y" /* yacc.c:1646  */
    {
        clase_actual = ESCALAR;
        fprintf(out, ";R5:\t<clase> ::= <clase_escalar>\n");
    }
#line 1509 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 160 "alfa.y" /* yacc.c:1646  */
    {
        clase_actual = VECTOR;
        fprintf(out, ";R7:\t<clase> ::= <clase_vector>\n");
    }
#line 1518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 165 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R9:\t<clase_escalar> ::= <tipo>\n");}
#line 1524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 168 "alfa.y" /* yacc.c:1646  */
    {
        tipo_actual = INT;
        fprintf(out, ";R10:\t<tipo> ::= int\n");
    }
#line 1533 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 173 "alfa.y" /* yacc.c:1646  */
    {
        tipo_actual = BOOLEAN;
        fprintf(out, ";R11:\t<tipo> ::= boolean\n");
        
    }
#line 1543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 180 "alfa.y" /* yacc.c:1646  */
    {
        tamanio_vector_actual = (yyvsp[-1].atributos).valor_entero;
        fprintf(out, ";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ]\n");
    }
#line 1552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 184 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R18:\t<identificadores> ::= <identificador>\n");}
#line 1558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 185 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n");}
#line 1564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 187 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R20:\t<funciones> ::= <funcion> <funciones>\n");}
#line 1570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 188 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R21:\t<funciones> ::=\n");}
#line 1576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 192 "alfa.y" /* yacc.c:1646  */
    {
        /* Buscar el identificador en el ámbito actual (el exterior a la función). Generar un error  */
        if (buscarTablaSimbolosAmbitoActual(ts, (yyvsp[0].atributos).lexema) != NULL) {
            yyerror("Declaracion duplicada.");
            return -1;
        }
        /*
        Si no ha habido error, abrir un ámbito nuevo. Esta operación implica: 
        insertar el identificador de la función en el ámbito actual (el exterior a la función) 
        crear un nuevo ámbito (el de la función) e insertar en él el identificador de la función.
        */
        if (insertarTablaSimbolosAmbitos(ts, (yyvsp[0].atributos).lexema, FUNCION, clase_actual, tipo_actual, -1, -1, -1, -1, -1) == ERROR) {
            yyerror(NULL);
            return -1;
        }

        if (abrirAmbito(ts) == ERROR) {
            yyerror(NULL);
            return -1;
        }
        // Si esto da fallos en el futuro, tener en cuenta que puede devolver un vector y que ahora mismo no estamos especificando su tamaño
        if (insertarTablaSimbolosAmbitos(ts, (yyvsp[0].atributos).lexema, FUNCION, clase_actual, tipo_actual, -1, -1, -1, -1, -1) == ERROR) {
            yyerror(NULL);
            return -1;
        }
        num_variables_locales_actual = 0;
        pos_variable_local_actual = 1;
        num_parametros_actual = 0;
        pos_parametro_actual = 0;

        /* Propagar a la parte izquierda de la regla el lexema del identificador de la función para su posterior uso en la acción del punto marcado como (2) */
        strcpy((yyval.atributos).lexema, (yyvsp[0].atributos).lexema);

        fprintf(out, ";R23:\t<fn_name> ::= function <tipo> <identificador>\n");

    }
#line 1617 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 230 "alfa.y" /* yacc.c:1646  */
    {
        /*
        Acceder al identificador de la función en el ámbito actual (el de la función) y actualizar la 
        información correspondiente al número de parámetros. 
        El acceso al identificador se puede realizar haciendo uso del lexema guardado como 
        atributo del no terminal fn_name que se propagó en la acción . 
        Propagar a la parte izquierda de la regla el lexema del identificador de la función para su 
        posterior uso en la acción del punto marcado como
        */
        elementoTablaSimbolos *elemento = NULL;
        elemento = buscarTablaSimbolosAmbitoActual(ts, (yyvsp[-5].atributos).lexema);
        if (elemento == NULL) {
            sprintf(aux_lex, "Acceso a función no declarada (%s).", (yyvsp[-5].atributos).lexema);
            yyerror(aux_lex);
            return -1;
        }
        elemento->n_param = num_parametros_actual;
        strcpy((yyval.atributos).lexema, (yyvsp[-5].atributos).lexema);

        declararFuncion(out, (yyvsp[-5].atributos).lexema, num_variables_locales_actual);

        fprintf(out, ";R22.1:\t<fn_declaracion> ::= <fn_nombre> ( <parametros_funcion> ) { <declaraciones_funcion>\n");

    }
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 255 "alfa.y" /* yacc.c:1646  */
    {
        if (cerrarAmbito(ts) == ERROR) {
            yyerror(NULL);
            return -1;
        }
        if (!retorno) {
            sprintf(aux_lex, "Funcion %s sin sentencia de retorno.", (yyvsp[-2].atributos).lexema);
            yyerror(aux_lex);
            return -1;
        }
        elementoTablaSimbolos *elemento = NULL;
        elemento = buscarTablaSimbolosAmbitoActual(ts, (yyvsp[-2].atributos).lexema);
        if (elemento == NULL) {
            sprintf(aux_lex, "Acceso a función no declarada (%s).", (yyvsp[-2].atributos).lexema);
            yyerror(aux_lex);
            return -1;
        }
        elemento->n_param = num_parametros_actual;
        strcpy((yyval.atributos).lexema, (yyvsp[-2].atributos).lexema);

        retorno = 0;
        fprintf(out, ";R22:\t<funcion> ::=  <declaraciones_funcion> <sentencias> }\n");
    }
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 278 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n");}
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 279 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R24:\t<parametros_funcion> ::= \n");}
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 280 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>\n");}
#line 1692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 281 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R26:\t<resto_parametros_funcion> ::=\n");}
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 282 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R27:\t<parametro_funcion> ::= <tipo> <idpf>\n");}
#line 1704 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 283 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R28:\t<declaraciones_funcion> ::= <tipo> <identificador>\n");}
#line 1710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 284 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R29:\t<declaraciones_funcion> ::=\n");}
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 285 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R30:\t<sentencias> ::= <sentencia>\n");}
#line 1722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 286 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R31:\t<sentencias> ::= <sentencia> <sentencias>\n");}
#line 1728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 287 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R32:\t<sentencia> ::= <sentencia_simple> ;\n");}
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 288 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R33:\t<sentencia> ::= <bloque>\n");}
#line 1740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 289 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R34:\t<sentencia_simple> ::= <asignacion>\n");}
#line 1746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 290 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R35:\t<sentencia_simple> ::= <lectura>\n");}
#line 1752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 291 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R36:\t<sentencia_simple> ::= <escritura>\n");}
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 292 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R38:\t<sentencia_simple> ::= <retorno_funcion>\n");}
#line 1764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 294 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R40:\t<bloque> ::= <condicional>\n");}
#line 1770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 295 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R41:\t<bloque> ::= <bucle>\n");}
#line 1776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 298 "alfa.y" /* yacc.c:1646  */
    {
        elementoTablaSimbolos *p_s = NULL;
        if ((p_s = buscarTablaSimbolosAmbitoActual(ts, (yyvsp[-2].atributos).lexema)) == NULL)
        {
            if ((p_s = buscarTablaSimbolosAmbitoGlobal(ts, (yyvsp[-2].atributos).lexema)) == NULL)
            {
                sprintf(aux_lex, "Acceso a variable no declarada (%s).", (yyvsp[-2].atributos).lexema);
                yyerror(aux_lex);
                return -1;
            }
        }

        if (p_s->categoria == FUNCION || p_s->clase == VECTOR) {
            yyerror("Asignacion incompatible.");
            return -1;
        }

        if (p_s->tipo != (yyvsp[0].atributos).tipo) {
            yyerror("Asignacion incompatible.");
            return -1;
        }
        if (estoyEnAmbitoGlobal(ts))
            asignar(out, (yyvsp[-2].atributos).lexema, (yyvsp[0].atributos).es_direccion);
        else {
            escribirVariableLocal(out, p_s->local_position);
            asignarDestinoEnPila(out, (yyvsp[0].atributos).es_direccion);
        }            

        fprintf(out, ";R43:\t<asignacion> ::= <identificador> = <exp> \n");
    }
#line 1811 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 329 "alfa.y" /* yacc.c:1646  */
    {
        elementoTablaSimbolos *p_s = NULL;
        if ((p_s = buscarTablaSimbolosAmbitoActual(ts, (yyvsp[-2].atributos).lexema)) == NULL)
        {
            if ((p_s = buscarTablaSimbolosAmbitoGlobal(ts, (yyvsp[-2].atributos).lexema)) == NULL)
            {
                sprintf(aux_lex, "Acceso a variable no declarada (%s).", (yyvsp[-2].atributos).lexema);
                yyerror(aux_lex);
                return -1;
            }
        }
        
        if (p_s->tipo != (yyvsp[0].atributos).tipo) {
            yyerror("Asignacion incompatible.");
            return -1;
        }
        if ((yyvsp[-2].atributos).valor_entero != -1) {
            sprintf(aux_lex, "%d", (yyvsp[-2].atributos).valor_entero);
            // Push index
            escribir_operando(out, aux_lex, 0);
        } else
            // Index is variable
            escribir_operando(out, aux_vector_index, 1);

        // Pop index and push address
        escribir_elemento_vector(out, (yyvsp[-2].atributos).lexema, p_s->size, (yyvsp[-2].atributos).es_direccion);
        asignarDestinoEnPila(out, (yyvsp[0].atributos).es_direccion);
        
        fprintf(out, ";R44:\t<asignación> ::= <elemento_vector> = <exp>\n");
    }
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 361 "alfa.y" /* yacc.c:1646  */
    {
        elementoTablaSimbolos *p_s = NULL;
        if ((p_s = buscarTablaSimbolosAmbitoActual(ts, (yyvsp[-3].atributos).lexema)) == NULL)
        {
            if ((p_s = buscarTablaSimbolosAmbitoGlobal(ts, (yyvsp[-3].atributos).lexema)) == NULL)
            {
                sprintf(aux_lex, "Acceso a variable no declarada (%s).", (yyvsp[-3].atributos).lexema);
                yyerror(aux_lex);
                return -1;
            }
        }

        if (p_s->clase != VECTOR) {
            yyerror("Intento de indexacion de una variable que no es de tipo vector.");
            return -1;
        }
        
        if (INT != (yyvsp[-1].atributos).tipo) {
            yyerror("El indice en una operacion de indexacion tiene que ser de tipo entero.");
            return -1;
        }

        (yyval.atributos).tipo = p_s->tipo;
        (yyval.atributos).es_direccion = (yyvsp[-1].atributos).es_direccion;
        (yyval.atributos).valor_entero = (yyvsp[-1].atributos).valor_entero;
        // Index is variable
        if ((yyval.atributos).valor_entero == -1)
            strcpy(aux_vector_index, (yyvsp[-1].atributos).lexema);
        strcpy((yyval.atributos).lexema, (yyvsp[-3].atributos).lexema);
        
        // Check index (?)
        escribir_elemento_vector(out, (yyvsp[-3].atributos).lexema, p_s->size, (yyvsp[-1].atributos).es_direccion);
        fprintf(out,";R48:\t<elemento_vector> ::= <identificador> [ <exp> ] \n");
    }
#line 1885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 397 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].atributos).tipo == INT) {
            yyerror("Condicional con condicion de tipo int.");
            return -1;
        }
        etiq_actual = etiqueta++;
        (yyval.atributos).etiqueta = etiq_actual;
        (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
        ifthen_inicio(out, (yyvsp[0].atributos).es_direccion, (yyval.atributos).etiqueta);
    }
#line 1900 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 409 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).etiqueta = (yyvsp[-5].atributos).etiqueta;
        (yyval.atributos).tipo = (yyvsp[-5].atributos).tipo;
        ifthenelse_fin_then(out, (yyvsp[-5].atributos).etiqueta);
    }
#line 1910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 416 "alfa.y" /* yacc.c:1646  */
    {
        ifthen_fin(out, (yyvsp[-4].atributos).etiqueta);
        (yyval.atributos).etiqueta = (yyvsp[-4].atributos).etiqueta;
        (yyval.atributos).tipo = (yyvsp[-4].atributos).tipo;
        fprintf(out, ";R50:\tcondicional ::= if ( <exp> ) { <sentencias> } \n");
    }
#line 1921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 423 "alfa.y" /* yacc.c:1646  */
    {
        ifthenelse_fin(out, (yyvsp[-3].atributos).etiqueta);
        (yyval.atributos).etiqueta = (yyvsp[-3].atributos).etiqueta;
        (yyval.atributos).tipo = (yyvsp[-3].atributos).tipo;
        fprintf(out, ";R51:\tcondicional ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n");
    }
#line 1932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 431 "alfa.y" /* yacc.c:1646  */
    {
        etiq_actual = etiqueta++;
        (yyval.atributos).etiqueta = etiq_actual;
        while_inicio(out, etiq_actual);
    }
#line 1942 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 438 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].atributos).tipo == INT) {
            yyerror("Bucle con condicion de tipo int.");
            return -1;
        }
        (yyval.atributos).etiqueta = (yyvsp[-2].atributos).etiqueta;
        (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
        while_exp_pila(out, (yyvsp[0].atributos).es_direccion, (yyvsp[-2].atributos).etiqueta);
    }
#line 1956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 449 "alfa.y" /* yacc.c:1646  */
    {
        while_fin(out, (yyvsp[-4].atributos).etiqueta);
        fprintf(out, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n");
    }
#line 1965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 455 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].atributos).tipo == INT) {
            yyerror("a boolean expression needed"); // ARREGLAR ESTO JEJE
            //fprintf(stdout, "****Error sintactico en [lin %d, col %d]\n", line, col);
            return -1;
        }
        while_exp_pila(out, (yyvsp[-2].atributos).es_direccion, (yyvsp[-6].atributos).etiqueta);
        while_fin(out, (yyvsp[-6].atributos).etiqueta);
        fprintf(out, ";R52:\t<bucle>::= do{ <sentencias> } while (<exp>)\n");

    }
#line 1981 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 471 "alfa.y" /* yacc.c:1646  */
    {
        etiq_actual = etiqueta++;
        (yyval.atributos).etiqueta = etiq_actual;
        while_inicio(out, etiq_actual);
    }
#line 1991 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 478 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).etiqueta = (yyvsp[-2].atributos).etiqueta;
    }
#line 1999 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 486 "alfa.y" /* yacc.c:1646  */
    {
        // Buscar en la tabla de símbolos (todos los ámbitos abiertos) el identificador $2.lexema
        // Si no existe
        //     MOSTRAR MENSAJE ERROR SEMÁNTICO
        //     TERMINAR CON ERROR
        elementoTablaSimbolos *elemento = NULL;
        int isGlobal = 0;
        if ((elemento = buscarTablaSimbolosAmbitoActual(ts, (yyvsp[0].atributos).lexema)) == NULL)
        {
            isGlobal = 1;
            if ((elemento = buscarTablaSimbolosAmbitoGlobal(ts, (yyvsp[0].atributos).lexema)) == NULL)
            {
                sprintf(aux_lex, "Acceso a variable no declarada (%s).", (yyvsp[0].atributos).lexema);
                yyerror(aux_lex);
                return -1;
            }
        }
        else
            isGlobal = estoyEnAmbitoGlobal(ts);
        // En caso contrario hacer lo correspondiente a la producción
        //     COMPROBACIONES SEMÁNTICAS
        //         Si el identificador es una función → ERROR SEMÁNTICO
        //         Si el identificador es un vector → ERROR SEMÁNTICO
        if (elemento->categoria == FUNCION || elemento->clase == VECTOR)
        {
            sprintf(aux_lex, "No esta permitido el uso de vectores o llamadas o funciones como parametro de lectura (%s).", (yyvsp[0].atributos).lexema);
            yyerror(aux_lex);
            return -1;
        }
        //     GENERACIÓN DE CÓDIGO: APILAR LA DIRECCIÓN DEL IDENTIFICADOR
        //         Si el identificador en una variable global , su dirección es su lexema
        //         Si el identificador es un parámetro o una variable local, su dirección se expresa en función de ebp y la posición del parámetro o variable local
        if (isGlobal)
            leer(out, elemento->lexema, elemento->tipo);
        else {
            if (elemento->categoria == PARAMETRO) {
                escribirParametro(out, elemento->param_position, num_parametros_actual);
            }
            else {
                escribirVariableLocal(out, elemento->local_position);
            }
            llamarFuncion(out, elemento->tipo == INT ? "scan_int" : "scan_boolean", 1);
        }
        //     GENERACIÓN DE CÓDIGO: LLAMAR A LA FUNCIÓN DE LA LIBRERÍA ALFALIB.O
        //         Si el identificador es de tipo entero llamar a scan_int
        //         Si el identificador es de tipo lógico llamar a scan_boolean
        //         Restaurar la pila

        fprintf(out, ";R54:\t<lectura> ::= scanf <identificador>\n");
    }
#line 2054 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 538 "alfa.y" /* yacc.c:1646  */
    {
        escribir(out, (yyvsp[0].atributos).es_direccion, (yyvsp[0].atributos).tipo);
    }
#line 2062 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 543 "alfa.y" /* yacc.c:1646  */
    {
        if (estoyEnAmbitoGlobal(ts)) {
            yyerror("Sentencia de retorno fuera del cuerpo de una función.");
            return -1;
        }
        retornarFuncion(out, (yyvsp[0].atributos).es_direccion);
        retorno = 1;
        fprintf(out, ";R61:\t<retorno_funcion> ::= return <exp>\n");
    }
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 554 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].atributos).tipo != INT || (yyvsp[0].atributos).tipo != INT) {
            yyerror("Operacion aritmetica con operandos boolean.");
            return -1;
        }
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        sumar(out, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(out, ";R72:\t<exp> ::= <exp> + <exp>\n");
    }
#line 2091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 565 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].atributos).tipo != INT || (yyvsp[0].atributos).tipo != INT) {
            yyerror("Operacion aritmetica con operandos boolean.");
            return -1;
        }
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        restar(out, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(out, ";R73:\t<exp> ::= <exp> - <exp>\n");
    }
#line 2106 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 576 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].atributos).tipo != INT || (yyvsp[0].atributos).tipo != INT) {
            yyerror("Operacion aritmetica con operandos boolean.");
            return -1;
        }
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        dividir(out, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(out, ";R74:\t<exp> ::= <exp> / <exp>\n");
    }
#line 2121 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 587 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].atributos).tipo != INT || (yyvsp[0].atributos).tipo != INT) {
            yyerror("Operacion aritmetica con operandos boolean.");
            return -1;
        }
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        multiplicar(out, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(out, ";R75:\t<exp> ::= <exp> * <exp>\n");
    }
#line 2136 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 598 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].atributos).tipo != INT) {
            yyerror("Operacion aritmetica con operandos boolean.");
            return -1;
        }
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        cambiar_signo(out, (yyvsp[0].atributos).es_direccion);
        fprintf(out, ";R76:\t<exp> ::= - <exp>\n");
    }
#line 2151 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 609 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].atributos).tipo != BOOLEAN || (yyvsp[0].atributos).tipo != BOOLEAN) {
            yyerror("Operacion logica con operandos int.");
            return -1;
        }
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;
        y(out, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(out, ";R77:\t<exp> ::= <exp> && <exp>\n");
    }
#line 2166 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 620 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].atributos).tipo != BOOLEAN || (yyvsp[0].atributos).tipo != BOOLEAN) {
            yyerror("Operacion logica con operandos int.");
            return -1;
        }
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;
        o(out, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(out, ";R78:\t<exp> ::= <exp> || <exp>\n");
    }
#line 2181 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 631 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].atributos).tipo != BOOLEAN) {
            yyerror("Operacion logica con operandos int.");
            return -1;
        }
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;
        etiq_actual = etiqueta++;
        (yyval.atributos).etiqueta = etiq_actual;
        no(out, (yyvsp[0].atributos).es_direccion, etiq_actual);
        fprintf(out, ";R79:\t<exp> ::= ! <exp>\n");
    }
#line 2198 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 644 "alfa.y" /* yacc.c:1646  */
    {   
        elementoTablaSimbolos * p_s = NULL;
        if ((p_s = buscarTablaSimbolosAmbitoActual(ts, (yyvsp[0].atributos).lexema)) == NULL)
        {
            if ((p_s = buscarTablaSimbolosAmbitoGlobal(ts, (yyvsp[0].atributos).lexema)) == NULL)
            {
                sprintf(aux_lex, "Acceso a variable no declarada (%s).", (yyvsp[0].atributos).lexema);
                yyerror(aux_lex);
                return -1;
            }
        }

        if (p_s->categoria == FUNCION) {
            yyerror("No esta permitido el uso de llamadas a funciones como parametros de otras funciones.");
            return -1;
        }
        if (p_s->clase == VECTOR) {
            yyerror("Expresion no puede ser vector.");
            return -1;
        }

        (yyval.atributos).es_direccion = 1;
        (yyval.atributos).tipo = p_s->tipo;
        (yyval.atributos).valor_entero = -1;
        
        if (estoyEnAmbitoGlobal(ts)) {
            escribir_operando(out, (yyvsp[0].atributos).lexema, 1);
            if (en_explist) {
                operandoEnPilaAArgumento(out, 1);
                (yyval.atributos).es_direccion = 0;
            }
        }
        else if (p_s->categoria == PARAMETRO)
            escribirParametro(out, p_s->param_position, num_parametros_actual);
        else
            escribirVariableLocal(out, p_s->local_position);
            
        strcpy((yyval.atributos).lexema, (yyvsp[0].atributos).lexema);
        
        fprintf(out, ";R80:\t<exp> ::= <identificador>\n");
    }
#line 2244 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 686 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
        (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
        (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
        strcpy((yyval.atributos).lexema, (yyvsp[0].atributos).lexema);
        escribir_operando(out, (yyvsp[0].atributos).lexema, 0);
        fprintf(out, ";R81:\t<exp> ::= <constante_entera>\n");
    }
#line 2257 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 695 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).tipo = (yyvsp[-1].atributos).tipo;
        (yyval.atributos).valor_entero = (yyvsp[-1].atributos).valor_entero;
        (yyval.atributos).es_direccion = (yyvsp[-1].atributos).es_direccion;
        (yyval.atributos).etiqueta = (yyvsp[-1].atributos).etiqueta;
        strcpy((yyval.atributos).lexema, (yyvsp[-1].atributos).lexema);
        fprintf(out, ";R82:\t<exp> ::= ( <exp> )\n");
    }
#line 2270 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 704 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).tipo = (yyvsp[-1].atributos).tipo;
        (yyval.atributos).valor_entero = (yyvsp[-1].atributos).valor_entero;
        (yyval.atributos).es_direccion = (yyvsp[-1].atributos).es_direccion;
        (yyval.atributos).etiqueta = (yyvsp[-1].atributos).etiqueta;
        strcpy((yyval.atributos).lexema, (yyvsp[-1].atributos).lexema);
        fprintf(out, ";R83:\t<exp> ::= ( <comparacion> )\n");
    }
#line 2283 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 713 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).es_direccion = 1;
        (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
        (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
        strcpy((yyval.atributos).lexema, (yyvsp[0].atributos).lexema);

        if (en_explist) {
            operandoEnPilaAArgumento(out, (yyval.atributos).es_direccion);
        }
        fprintf(out, ";R85:\t<exp> ::= <elemento_vector>\n");
    }
#line 2299 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 725 "alfa.y" /* yacc.c:1646  */
    {
        /* Comprobar que el numero de parametros de la llamada es correcto
        comprobando el valor de la variable num_parametros_llamada_actual con la informacion
        almacenada en la tabla de simbolos */
        elementoTablaSimbolos * p_s = NULL;
        p_s = buscarTablaSimbolosAmbitoActual(ts ,(yyvsp[-3].atributos).lexema);
        if (p_s == NULL) {
            sprintf(aux_lex, "Acceso a variable no declarada (%s).", (yyvsp[-3].atributos).lexema);
            yyerror(aux_lex);
            return -1;
        }
        if (p_s->n_param != num_parametros_llamada_actual) {
            yyerror("Numero incorrecto de parametros en llamada a funcion.");
            return -1;
        }
        /* Resetear a 0 la variable en_explist */
        en_explist = 0;

        /* Propagar el tipo del retorno de la funcion almacenada en la tabla de simbolos */
        (yyval.atributos).tipo = p_s->tipo;

        /* Propagar direccion a 0 */
        (yyval.atributos).es_direccion = 0;

        llamarFuncion(out, (yyvsp[-3].atributos).lexema, num_parametros_llamada_actual);

        fprintf(out, ";R88:\t<exp> ::= <identificador> ( <lista_expresiones> )\n");
    }
#line 2332 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 755 "alfa.y" /* yacc.c:1646  */
    {
        /* buscar identificador en la tabla simbolos*/
        elementoTablaSimbolos * p_s = NULL;
        p_s = buscarTablaSimbolosAmbitoActual(ts, (yyvsp[0].atributos).lexema);
        if (p_s == NULL) {
            sprintf(aux_lex, "Acceso a variable no declarada (%s).", (yyvsp[0].atributos).lexema);
            yyerror(aux_lex);
            return -1;
        }
        /* Comprobar que el identificador es de categoria funcion */
        if (p_s->categoria != FUNCION) {
            sprintf(aux_lex, "Intento de llamada a variable que no es función (%s).", (yyvsp[0].atributos).lexema);
            yyerror(aux_lex);
            return -1;
        }
        /* Comprobar que la variable en_explist no valga 1 para asegurar que la actual
            llamada a la funcion no es un parametro de la llamada a funcion */
        if (en_explist == 1) { 
            sprintf(aux_lex, "No esta permitido el uso de llamadas a funciones como parametros de otras funciones. (%s).", (yyvsp[0].atributos).lexema);
            yyerror(aux_lex);
            return -1;
        }
        /*
        Iniciar a 0 num_parametros_llamada_actual
        Iniciar a 1 la variable en_explist
        */
        num_parametros_actual = p_s->n_param;
        num_parametros_llamada_actual = 0;
        en_explist = 1;
        /*
        Propagar el lexema del identifiacdor 
        */
        strcpy((yyval.atributos).lexema, (yyvsp[0].atributos).lexema);
    }
#line 2371 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 791 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(out, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones>\n");
        num_parametros_llamada_actual++;
    }
#line 2380 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 795 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R90:\t<lista_expresiones> ::= \n");}
#line 2386 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 798 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(out, ";R91:\t<resto_lista_expresiones> ::= <exp> <resto_lista_expresiones\n");
        num_parametros_llamada_actual++;
    }
#line 2395 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 802 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R92:\t<resto_lista_expresiones> ::= \n");}
#line 2401 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 805 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].atributos).tipo == BOOLEAN || (yyvsp[0].atributos).tipo == BOOLEAN) {
            yyerror("Comparacion con operandos boolean.");
            return -1;
        }

        (yyval.atributos).tipo = BOOLEAN;
        etiq_actual = etiqueta++;
        (yyval.atributos).es_direccion = 0;
        (yyval.atributos).etiqueta = etiq_actual;
        igual(out, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiq_actual);
        fprintf(out, ";R93:\t<comparacion> ::= <exp> == <exp>\n");
    }
#line 2419 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 819 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].atributos).tipo == BOOLEAN || (yyvsp[0].atributos).tipo == BOOLEAN) {
            yyerror("Comparacion con operandos boolean.");
            return -1;
        }

        (yyval.atributos).tipo = BOOLEAN;
        etiq_actual = etiqueta++;
        (yyval.atributos).es_direccion = 0;
        (yyval.atributos).etiqueta = etiq_actual;
        distinto(out, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiq_actual);
        fprintf(out, ";R94:\t<comparacion> ::= <exp> != <exp>\n");
    }
#line 2437 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 833 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].atributos).tipo == BOOLEAN || (yyvsp[0].atributos).tipo == BOOLEAN) {
            yyerror("Comparacion con operandos boolean.");
            return -1;
        }

        (yyval.atributos).tipo = BOOLEAN;
        etiq_actual = etiqueta++;
        (yyval.atributos).es_direccion = 0;
        (yyval.atributos).etiqueta = etiq_actual;
        menor_igual(out, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiq_actual);
        fprintf(out, ";R95:\t<comparacion> ::= <exp> <= <exp>\n");
    }
#line 2455 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 847 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].atributos).tipo == BOOLEAN || (yyvsp[0].atributos).tipo == BOOLEAN) {
            yyerror("Comparacion con operandos boolean.");
            return -1;
        }

        (yyval.atributos).tipo = BOOLEAN;
        etiq_actual = etiqueta++;
        (yyval.atributos).es_direccion = 0;
        (yyval.atributos).etiqueta = etiq_actual;
        mayor_igual(out, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiq_actual);
        fprintf(out, ";R96:\t<comparacion> ::= <exp> >= <exp>\n");
    }
#line 2473 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 861 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].atributos).tipo == BOOLEAN || (yyvsp[0].atributos).tipo == BOOLEAN) {
            yyerror("Comparacion con operandos boolean.");
            return -1;
        }

        (yyval.atributos).tipo = BOOLEAN;
        etiq_actual = etiqueta++;
        (yyval.atributos).es_direccion = 0;
        (yyval.atributos).etiqueta = etiq_actual;
        menor(out, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiq_actual);
        fprintf(out, ";R97:\t<comparacion> ::= <exp> < <exp>\n");
    }
#line 2491 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 875 "alfa.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].atributos).tipo == BOOLEAN || (yyvsp[0].atributos).tipo == BOOLEAN) {
            yyerror("Comparacion con operandos boolean.");
            return -1;
        }

        (yyval.atributos).tipo = BOOLEAN;
        etiq_actual = etiqueta++;
        (yyval.atributos).es_direccion = 0;
        (yyval.atributos).etiqueta = etiq_actual;
        mayor(out, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, etiq_actual);
        fprintf(out, ";R98:\t<comparacion> ::= <exp> > <exp>\n");
    }
#line 2509 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 890 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
        (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
        (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
        sprintf(aux_lex, "%d", (yyval.atributos).valor_entero);
        strcpy((yyval.atributos).lexema, aux_lex);
        fprintf(out, ";R99:\t<constante> ::= <constante_logica>\n");
    }
#line 2522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 899 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
        (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
        (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
        sprintf(aux_lex, "%d", (yyval.atributos).valor_entero);
        strcpy((yyval.atributos).lexema, aux_lex);
        fprintf(out, ";R100:\t<constante> ::= <constante_entera>\n");
    }
#line 2535 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 909 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).valor_entero = 1;
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;
        fprintf(out, ";R102:\t<constante_logica> ::= true\n");
    }
#line 2546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 916 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).valor_entero = 0;
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;
        fprintf(out, ";R103:\t<constante_logica> ::= false\n");
    }
#line 2557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 924 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        fprintf(out, ";R104:\t<constante_entera> ::= <numero>\n");
    }
#line 2568 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 932 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
        fprintf(out, ";R105:\t<numero> ::= <digito>\n");
    }
#line 2577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 936 "alfa.y" /* yacc.c:1646  */
    {fprintf(out, ";R106:\t<numero> ::= <numero> <digito>\n");}
#line 2583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 939 "alfa.y" /* yacc.c:1646  */
    {
        if (buscarTablaSimbolosAmbitoActual(ts, (yyvsp[0].atributos).lexema) != NULL)
        {
            yyerror("Declaracion duplicada.");
            return -1;
        } else
        {
            if (clase_actual == VECTOR && ((tamanio_vector_actual < 1 ) || (tamanio_vector_actual > MAX_TAMANIO_VECTOR))) {
                // Semantic error vector size
                sprintf(aux_lex, "El tamanio del vector %s[%d] excede los limites permitidos (1,64).", (yyvsp[0].atributos).lexema, tamanio_vector_actual);
                yyerror(aux_lex);
                return -1;
            }

            if (!estoyEnAmbitoGlobal(ts)) {

                if (clase_actual != ESCALAR) {
                    yyerror("Variable local de tipo no escalar.");
                    return -1;
                }

                insertarTablaSimbolosAmbitos(ts, (yyvsp[0].atributos).lexema, VARIABLE, clase_actual, tipo_actual, -1, -1, pos_variable_local_actual, -1, -1);
                pos_variable_local_actual++;
                num_variables_locales_actual++;
            }
            else {
                int size = (clase_actual == VECTOR ? tamanio_vector_actual : 1);
                insertarTablaSimbolosAmbitos(ts, (yyvsp[0].atributos).lexema, VARIABLE, clase_actual, tipo_actual, size, -1, -1, -1, -1);
                declarar_variable(out, (yyvsp[0].atributos).lexema, tipo_actual, size);
            }


            fprintf(out, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n");
            (yyval.atributos).tipo = tipo_actual;
            (yyval.atributos).es_direccion = 1;
            strcpy((yyval.atributos).lexema, (yyvsp[0].atributos).lexema);

        }
    }
#line 2627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 980 "alfa.y" /* yacc.c:1646  */
    {
    fprintf(out, ";R109:\t<idpf> ::= TOK_IDENTIFICADOR\n");
    /* Se comprueba que el identificador no exista en el ámbito actual (el de la función). Si 
    existiera, se genera un mensaje de error semántico y se termina el proceso de compilación 
    con error. */
    if (buscarTablaSimbolosAmbitoActual(ts, (yyvsp[0].atributos).lexema) != NULL) 
    {
        yyerror("Declaracion duplicada.");
        return -1;
    }
    
    /* Si no hay error semántico se realiza la inserción sin olvidar el uso de la variable global 
    pos_parametro_actual. */
    insertarTablaSimbolosAmbitos(ts, (yyvsp[0].atributos).lexema, PARAMETRO, ESCALAR, tipo_actual, -1, -1, -1, -1, pos_parametro_actual++);
    /*
    Se incrementa en uno el valor de las siguientes variables globales:  */
    /*num_parametros_actual (esta variable almacena el número de parámetros de una función) */
    num_parametros_actual++;
    /*Se asume que estas variables son correctamente inicializadas (consultar documentación de la gestión 
    de identificadores de funciones) */
    }
#line 2653 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2657 "y.tab.c" /* yacc.c:1646  */
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
#line 1003 "alfa.y" /* yacc.c:1906  */


void yyerror(char *s)
{
    col -= yyleng;
    if (!morph_error) {
        if (!strcmp(s, "syntax error"))
            fprintf(stdout, "****Error sintactico en [lin %d, col %d]\n", line, col);
        else
            fprintf(stdout, "****Error semantico en [lin %d, col %d]: %s\n", line, col, s);
    }
}
