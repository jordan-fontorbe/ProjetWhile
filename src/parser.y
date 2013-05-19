%{
	#include <stdio.h>
	#include <iostream>
	#include <Operande.hpp>

	int yylex(void);
	void yyerror(const char* msg);
	int ligne=1;
	extern FILE* yyin;
%}

%union{
	int intW;
	float decimalW;
	Operande *operandeW;
}

%token TYPE RETOUR SI ALORS SINON TANTQUE FAIRE FONCTION PROCEDURE
%token EST BLOCKDEBUT BLOCKFIN AFFECTATION ENTIER DECIMAL
%token MOINS PLUS MUL DIV COMPARATEUR NON ET OU
%token VRAI FAUX  PARENTHESEOUVRANTE PARENTHESEFERMANTE PROGRAMME
%token ALLOUER DESALLOUER CROCHETOUVRANT CROCHETFERMANT VARIABLE
%token FININSTRUCTION VIRGULE DEUXPOINTS

/*
%type <intW> ENTIER
%type <decimalW> DECIMAL
%type <statementW> TYPE RETOUR SI ALORS SINON TANTQUE FAIRE FONCTION PROCEDURE EST BLOCKDEBUT BLOCKFIN AFFECTATION PLUS MOINS MUL DIV COMPARATEUR NON ET OU VRAI FAUX  PARENTHESEOUVRANTE PARENTHESEFERMANTE PROGRAMME ALLOUER DESALLOUER CROCHETOUVRANT CROCHETFERMANT VARIABLE FININSTRUCTION VIRGULE DEUXPOINTS

%type <statementW> lhs procedureCall functionCall variableList vdecl ifblock whileblock block statement	instruction statementList typeVariableList functionDeclaration	procedureDeclaration pdecl	program
*/

%type <intW> ENTIER
%type <decimalW> DECIMAL
%type <operandeW> arithmeticExpression



%nonassoc AFFECTATION COMPARATEUR NON
%left MUL DIV
%left PLUS MOINS
%right NEG
%left ET OU 
/* %right NON */
%start program
%%

program					:	PROGRAMME BLOCKFIN | 
							pdecl PROGRAMME statementList BLOCKFIN | 
							PROGRAMME statementList BLOCKFIN;

lhs						:	VARIABLE | 
							VARIABLE CROCHETOUVRANT arithmeticExpression CROCHETFERMANT;


arithmeticExpression	:	lhs { $$ = 0;}| 
							ENTIER { $$ = new Operande(new Valeur($1)); }| 
							DECIMAL { $$ = new Operande(new Valeur($1)); } |
							MOINS arithmeticExpression %prec NEG { $$ = 0;} | 
							arithmeticExpression MUL arithmeticExpression { $$ = 0;} | 
							arithmeticExpression DIV arithmeticExpression { $$ = 0;}| 
							arithmeticExpression PLUS arithmeticExpression { $$ = 0;}| 
							arithmeticExpression MOINS arithmeticExpression { $$ = 0;}| 
							PARENTHESEOUVRANTE arithmeticExpression PARENTHESEFERMANTE { $$ = 0;}; 

booleanExpression		:	VRAI | 
							FAUX | 
							arithmeticExpression COMPARATEUR arithmeticExpression | 
							NON booleanExpression | 
							booleanExpression ET booleanExpression | 
							booleanExpression OU booleanExpression | 
							PARENTHESEOUVRANTE booleanExpression PARENTHESEFERMANTE;
							
arithmeticExpressionList :	arithmeticExpression | 
							arithmeticExpression VIRGULE arithmeticExpressionList;

instruction				:	RETOUR | 
							RETOUR arithmeticExpression | 
							lhs AFFECTATION arithmeticExpression | 
							lhs AFFECTATION ALLOUER TYPE CROCHETOUVRANT arithmeticExpression CROCHETFERMANT | 
							DESALLOUER PARENTHESEOUVRANTE VARIABLE PARENTHESEFERMANTE | 
							procedureCall | 
							functionCall;

procedureCall			:	VARIABLE PARENTHESEOUVRANTE PARENTHESEFERMANTE | 
							VARIABLE PARENTHESEOUVRANTE arithmeticExpressionList PARENTHESEFERMANTE;

functionCall			:	lhs AFFECTATION VARIABLE PARENTHESEOUVRANTE PARENTHESEFERMANTE | 
							lhs AFFECTATION VARIABLE PARENTHESEOUVRANTE arithmeticExpressionList PARENTHESEFERMANTE;


variableList			:	lhs | 
							lhs VIRGULE variableList;

vdeclList 				: 	vdecl | vdecl vdeclList;

vdecl					:	TYPE variableList FININSTRUCTION;

ifblock					: 	SI booleanExpression ALORS statement SINON statement;

whileblock				:	TANTQUE booleanExpression FAIRE statement;

block					:	BLOCKDEBUT statementList BLOCKFIN | BLOCKDEBUT vdeclList statementList BLOCKFIN;

statement				:	ifblock | 
							whileblock | 
							block | 
							instruction FININSTRUCTION;

statementList			:	statement | statement statementList;

typeVariableList		:	VARIABLE DEUXPOINTS TYPE | 
							VARIABLE DEUXPOINTS TYPE VIRGULE typeVariableList;

functionDeclaration		:	FONCTION VARIABLE PARENTHESEOUVRANTE PARENTHESEFERMANTE DEUXPOINTS TYPE EST statement | 
							FONCTION VARIABLE PARENTHESEOUVRANTE typeVariableList PARENTHESEFERMANTE DEUXPOINTS TYPE EST statement;

procedureDeclaration	:	PROCEDURE VARIABLE PARENTHESEOUVRANTE PARENTHESEFERMANTE EST statement | 
							PROCEDURE VARIABLE PARENTHESEOUVRANTE typeVariableList PARENTHESEFERMANTE EST statement;

pdecl					:	functionDeclaration | 
							functionDeclaration pdecl | 
							procedureDeclaration | 
							procedureDeclaration pdecl ;


%%
void yyerror(const char* msg) {
	fprintf(stderr, "Erreur syntaxique : ligne %d \n", ligne);
}
int main(int argc, char** argv) {
	if (argc>1) yyin = fopen(argv[1],"r");
	ligne = 1;
	if (!yyparse()) return printf("Analyse syntaxique réussie sans encombres !!!\n");
	return 1;
}
