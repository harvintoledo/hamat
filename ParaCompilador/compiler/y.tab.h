/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     APAR = 258,
     CPAR = 259,
     NL = 260,
     CONSTENTERA = 261,
     IDENTIFICADOR = 262,
     FNCT = 263,
     OPAS = 264,
     MAS = 265,
     MENOS = 266,
     ENTRE = 267,
     POR = 268,
     NEG = 269,
     POTENCIA = 270
   };
#endif
/* Tokens.  */
#define APAR 258
#define CPAR 259
#define NL 260
#define CONSTENTERA 261
#define IDENTIFICADOR 262
#define FNCT 263
#define OPAS 264
#define MAS 265
#define MENOS 266
#define ENTRE 267
#define POR 268
#define NEG 269
#define POTENCIA 270




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 11 "mathabstraction.y"

    double val;   /* For returning numbers. */
    symrec *tptr; /* For returning symbol-table pointers. */



/* Line 2068 of yacc.c  */
#line 87 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


