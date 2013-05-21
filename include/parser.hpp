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
     TYPE = 258,
     RETOUR = 259,
     SI = 260,
     ALORS = 261,
     SINON = 262,
     TANTQUE = 263,
     FAIRE = 264,
     FONCTION = 265,
     PROCEDURE = 266,
     EST = 267,
     BLOCKDEBUT = 268,
     BLOCKFIN = 269,
     AFFECTATION = 270,
     ENTIER = 271,
     DECIMAL = 272,
     MOINS = 273,
     PLUS = 274,
     MUL = 275,
     DIV = 276,
     COMPARATEUR = 277,
     NON = 278,
     ET = 279,
     OU = 280,
     VRAI = 281,
     FAUX = 282,
     PARENTHESEOUVRANTE = 283,
     PARENTHESEFERMANTE = 284,
     PROGRAMME = 285,
     ALLOUER = 286,
     DESALLOUER = 287,
     CROCHETOUVRANT = 288,
     CROCHETFERMANT = 289,
     VARIABLE = 290,
     FININSTRUCTION = 291,
     VIRGULE = 292,
     DEUXPOINTS = 293,
     NEG = 294
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 27 "src/parser.y"

	int intW;
	float decimalW;
	char* stringW;
	Operande *operandeW;
	int idW;
	char* typeW;
	NodeAST *nodeW;
	NodeASTList *nodeListW;



/* Line 2068 of yacc.c  */
#line 102 "src/parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


