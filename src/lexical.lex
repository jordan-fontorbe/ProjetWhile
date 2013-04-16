%{
  #include<stdio.h>
  int ligne = 1;
  int chr = 1;
%}

%option noyywrap
type			"int"[[:blank:]]+|"decimal"[[:blank:]]+
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
operateurUnaire		"-"
operateurBinaire	"+"|"-"|"*"|"/"
comparateur		"<"|">"|"<="|">="|"="|"<>"
non			"!"
et			"&&"
ou			"||"
vrai			"true"
faux			"false"
parentheseOuvrante	"("
parentheseFermante	")"
programme		"program"
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
{type}			{chr+=yyleng;}
{retour}		{chr+=yyleng;}
{si}			{chr+=yyleng;}
{alors}			{chr+=yyleng;}
{sinon}			{chr+=yyleng;}
{tantQue}		{chr+=yyleng;}
{faire}			{chr+=yyleng;}
{fonction}		{chr+=yyleng;}
{procedure}		{chr+=yyleng;}
{est}			{chr+=yyleng;}
{blockDebut}		{chr+=yyleng;}
{blockFin}		{chr+=yyleng;}
{affectation} 		{chr+=yyleng;}
{entier}		{chr+=yyleng;}
{decimal}		{chr+=yyleng;}
{operateurUnaire}	{chr+=yyleng;}
{operateurBinaire}	{chr+=yyleng;}
{comparateur}		{chr+=yyleng;}
{non}			{chr+=yyleng;}
{et}			{chr+=yyleng;}
{ou}			{chr+=yyleng;}
{vrai}			{chr+=yyleng;}
{faux}			{chr+=yyleng;}
{parentheseOuvrante}	{chr+=yyleng;}
{parentheseFermante}	{chr+=yyleng;}
{programme}		{chr+=yyleng;}
{allouer}		{chr+=yyleng;}
{desallouer}		{chr+=yyleng;}
{crochetOuvrant}	{chr+=yyleng;}
{crochetFermant}	{chr+=yyleng;}
{variable}		{chr+=yyleng;}
{finInstruction}	{chr+=yyleng;}
{finLigne}		{chr=1; ligne++;}
{virgule}		{chr+=yyleng;}
{deuxpoints}	{chr+=yyleng;}
[[:blank:]]+		{chr+=yyleng;}
<<EOF>> 	      {printf("[Fichier analysée lexicalement]\n"); return 0;}
.			{ printf("Erreur lexical : ligne %d caractère %d (caractère %c du mot %s)\n", ligne, chr, yytext[0], yytext); return 1;}
%%
/** Code C **/
int main(int argc, char** argv) {
	if (argc > 1)yyin = fopen(argv[1], "r");
	if (!yylex()) return printf("Programme ok lexicalement parlant ... :) \n");
return 0;
}

