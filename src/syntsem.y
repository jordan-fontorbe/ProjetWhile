%{
	#include <stdio.h>
	int yylex(void);
	void yyerror(const char* msg);
	int ligne;
	extern FILE* yyin;
%}

%union{
	int intW;
	float decimalW;
	char* statementW;
}

%token TYPE RETOUR SI ALORS SINON TANTQUE FAIRE FONCTION PROCEDURE
%token EST BLOCKDEBUT BLOCKFIN AFFECTATION ENTIER DECIMAL
%token OPERATEURUNAIRE OPERATEURBINAIRE COMPARATEUR NON ET OU
%token VRAI FAUX  PARENTHESEOUVRANTE PARENTHESEFERMANTE PROGRAMME
%token ALLOUER DESALLOUER CROCHETOUVRANT CROCHETFERMANT VARIABLE
%token FININSTRUCTION FINLIGNE VIRGULE DEUXPOINTS

%type <intW> ENTIER
%type <decimalW> DECIMAL
%type <statementW> TYPE RETOUR SI ALORS SINON TANTQUE FAIRE FONCTION PROCEDURE EST BLOCKDEBUT BLOCKFIN AFFECTATION OPERATEURUNAIRE OPERATEURBINAIRE COMPARATEUR NON ET OU VRAI FAUX  PARENTHESEOUVRANTE PARENTHESEFERMANTE PROGRAMME ALLOUER DESALLOUER CROCHETOUVRANT CROCHETFERMANT VARIABLE FININSTRUCTION FINLIGNE VIRGULE DEUXPOINTS

%type <statementW> lhs procedureCall functionCall variableList vdecl ifblock whileblock block statement	instruction statementList typeVariableList functionDeclaration	procedureDeclaration pdecl	program
%start program
%%

program					:	PROGRAMME BLOCKFIN | 
							pdecl PROGRAMME statementList BLOCKFIN | 
							PROGRAMME statementList BLOCKFIN;

lhs						:	VARIABLE | 
							VARIABLE CROCHETOUVRANT arithmeticExpression CROCHETFERMANT;


arithmeticExpression	:	lhs | 
							ENTIER | 
							DECIMAL |
							OPERATEURUNAIRE arithmeticExpression | 
							arithmeticExpression OPERATEURBINAIRE arithmeticExpression | 
							PARENTHESEOUVRANTE arithmeticExpression PARENTHESEFERMANTE; 

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

vdecl					:	TYPE variableList FININSTRUCTION;

ifblock					: 	SI booleanExpression ALORS statement SINON statement;

whileblock				:	TANTQUE booleanExpression FAIRE statement;

block					:	BLOCKDEBUT statementList BLOCKFIN | BLOCKDEBUT vdecl statementList BLOCKFIN;

statement				:	ifblock | 
							whileblock | 
							block | 
							instruction FININSTRUCTION;

statementList			:	statement | 
							statement statementList;

typeVariableList		:	VARIABLE DEUXPOINTS TYPE | 
							VARIABLE DEUXPOINTS TYPE VIRGULE typeVariableList;

functionDeclaration		:	FONCTION VARIABLE PARENTHESEOUVRANTE PARENTHESEFERMANTE DEUXPOINTS TYPE EST statement | 
							FONCTION VARIABLE PARENTHESEOUVRANTE typeVariableList PARENTHESEFERMANTE DEUXPOINTS TYPE EST statement;

procedureDeclaration	:	PROCEDURE VARIABLE PARENTHESEOUVRANTE PARENTHESEFERMANTE EST statement | 
							PROCEDURE VARIABLE PARENTHESEOUVRANTE typeVariableList PARENTHESEFERMANTE EST statement;

pdecl					:	functionDeclaration | 
							functionDeclaration | 
							procedureDeclaration | 
							procedureDeclaration pdecl ;


%%
void yyerror(const char* msg) {
	fprintf(stderr, "Erreur syntaxique : ligne %d \n", ligne - 1);
}
int main(int argc, char** argv) {
	if (argc>1) yyin = fopen(argv[1],"r");
	ligne = 0;
	if (!yyparse()) return printf("Analyse syntaxique réussie sans encombres !!!\n");
	return 1;
}
