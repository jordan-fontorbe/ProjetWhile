%{
  #include<stdio.h>
  int chr = 1;
  extern int ligne;
void yyerror(const char* msg);
#include "syntsem.h"
%}

%option noyywrap
type			"integer"[[:blank:]]*|"decimal"[[:blank:]]*
retour 			"return"
si			"if"
alors			"then"
sinon			"else"
tantQue			"while"
faire			"do"
fonction		"function"
procedure		"procedure"
est			"is"
blockDebut		"begin"
blockFin		"end"
affectation 		":="
entier			[0-9]+
decimal			[0-9]+(\.[0-9]+)?
moins			"-"
plus			"+"
mul				"*"
div				"/"
comparateur		"<"|">"|"<="|">="|"="|"<>"
non			"!"
et			"&&"
ou			"||"
vrai			"true"
faux			"false"
parentheseOuvrante	"("
parentheseFermante	")"
programme		"Program"
allouer			"new"
desallouer		"free"
crochetOuvrant		"["
crochetFermant		"]"
variable		[a-z][a-zA-Z0-9]*
finInstruction		";"
finLigne		\n
virgule			","
deuxpoints		":"
%%
{type}			{chr+=yyleng; return(TYPE);}
{retour}		{chr+=yyleng; return(RETOUR);}
{si}			{chr+=yyleng; return(SI);}
{alors}			{chr+=yyleng; return(ALORS);}
{sinon}			{chr+=yyleng; return(SINON);}
{tantQue}		{chr+=yyleng; return(TANTQUE);}
{faire}			{chr+=yyleng; return(FAIRE);}
{fonction}		{chr+=yyleng; return(FONCTION);}
{procedure}		{chr+=yyleng; return(PROCEDURE);}
{est}			{chr+=yyleng; return(EST);}
{blockDebut}	{chr+=yyleng; return(BLOCKDEBUT);}
{blockFin}		{chr+=yyleng; return(BLOCKFIN);}
{affectation} 	{chr+=yyleng; return(AFFECTATION);}
{entier}		{chr+=yyleng; return(ENTIER);}
{decimal}		{chr+=yyleng; return(DECIMAL);}
{moins}			{chr+=yyleng; return(MOINS);}
{plus}			{chr+=yyleng; return(PLUS);}
{mul}			{chr+=yyleng; return(MUL);}
{div}			{chr+=yyleng; return(DIV);}
{comparateur}	{chr+=yyleng; return(COMPARATEUR);}
{non}			{chr+=yyleng; return(NON);}
{et}			{chr+=yyleng; return(ET);}
{ou}			{chr+=yyleng; return(OU);}
{vrai}			{chr+=yyleng; return(VRAI);}
{faux}			{chr+=yyleng; return(FAUX);}
{parentheseOuvrante}	{chr+=yyleng; return(PARENTHESEOUVRANTE);}
{parentheseFermante}	{chr+=yyleng; return(PARENTHESEFERMANTE);}
{programme}		{chr+=yyleng; return(PROGRAMME);}
{allouer}		{chr+=yyleng; return(ALLOUER);}
{desallouer}		{chr+=yyleng; return(DESALLOUER);}
{crochetOuvrant}	{chr+=yyleng; return(CROCHETOUVRANT);}
{crochetFermant}	{chr+=yyleng; return(CROCHETFERMANT);}
{variable}		{chr+=yyleng; return(VARIABLE);}
{finInstruction}	{chr+=yyleng; return(FININSTRUCTION);}
{finLigne}		{chr=1; ligne++;}
{virgule}		{chr+=yyleng; return(VIRGULE);}
{deuxpoints}		{chr+=yyleng; return(DEUXPOINTS);}
[[:blank:]]+		{chr+=yyleng;}
<<EOF>> 	      {printf("[Fichier analysée lexicalement]\n"); return 0;}
.			{ char msg[150]; sprintf(msg,"Erreur lexical : ligne %d caractère %d (caractère %c du mot %s)\n", ligne, chr, yytext[0], yytext); yyerror(msg); return 1;}
%%

