%{
	#include <stdio.h>
	#include <iostream>
	#include <Operande.hpp>
	#include <TableIds.hpp>
	#include <TableSymboles.hpp>
	#include <queue>
	#include <NodeAST.hpp>
	#include <NodeASTList.hpp>
	#include <sstream>
	#include <GeneratorDOTFile.hpp>
	
	using namespace std;
	int yylex(void);
	void yyerror(const char* msg);
	int ligne=1;
	TableIds *tableIdsCourante = new TableIds();
	TableSymboles *tableSymbolesCourante = new TableSymboles();
	std::queue<int> fileIdTemp;
	std::vector<std::string> lstFils;
	NodeAST* root;
		
	extern FILE* yyin;

%}

%union{
	int intW;
	float decimalW;
	char* stringW;
	Operande *operandeW;
	int idW;
	char* typeW;
	NodeAST *nodeW;
	NodeASTList *nodeListW;
}

%token TYPE RETOUR SI ALORS SINON TANTQUE FAIRE FONCTION PROCEDURE
%token EST BLOCKDEBUT BLOCKFIN AFFECTATION ENTIER DECIMAL
%token MOINS PLUS MUL DIV COMPARATEUR NON ET OU
%token VRAI FAUX  PARENTHESEOUVRANTE PARENTHESEFERMANTE PROGRAMME
%token ALLOUER DESALLOUER CROCHETOUVRANT CROCHETFERMANT VARIABLE
%token FININSTRUCTION VIRGULE DEUXPOINTS

%type <idW> VARIABLE
%type <intW> ENTIER
%type <decimalW> DECIMAL
%type <typeW> TYPE
%type <stringW> COMPARATEUR

%type <nodeW> arithmeticExpression statement instruction block booleanExpression ifblock whileblock
%type <idW> lhs
%type <nodeListW> statementList


%nonassoc AFFECTATION COMPARATEUR NON
%left MUL DIV
%left PLUS MOINS
%right NEG
%left ET OU 
/* %right NON */
%start program
%%

program					:	PROGRAMME BLOCKFIN { root = new NodeAST("Program"); } | 
							pdecl PROGRAMME statementList BLOCKFIN 
							{ 
								root = new NodeAST("Program");
								NodeASTList* lstFils = $3;
								for (unsigned int i = 0; i < lstFils->size(); i++)
								{
									root->addChild(lstFils->get(i));
								}
							} 
							| 
							PROGRAMME statementList BLOCKFIN 
							{
								root = new NodeAST("Program");
								NodeASTList* lstFils = $2;
								for (unsigned int i = 0; i < lstFils->size(); i++)
								{
									root->addChild(lstFils->get(i));
								}
							};

lhs						:	VARIABLE { $$ = $1;} | 
							VARIABLE CROCHETOUVRANT arithmeticExpression CROCHETFERMANT { $$ = -1; /* Pour l'instant on ne gère pas les tableaux */};


arithmeticExpression	:	lhs 
							{ 
								std::ostringstream oss;
								oss << $1;
								$$ = new NodeAST(oss.str());
							}
							| 
							ENTIER 
							{ 
								std::ostringstream oss;
								oss << $1;
								$$ = new NodeAST(oss.str());
							}
							| 
							DECIMAL 
							{
								std::ostringstream oss;
								oss << $1;
								$$ = new NodeAST(oss.str());
							} 
							|
							MOINS arithmeticExpression %prec NEG { $$ = 0; /* Non géré pour l'instant */} | 
							arithmeticExpression MUL arithmeticExpression 
							{
								$$ = new NodeAST("*");
								$$->addChild($1);
								$$->addChild($3);
							} 
							| 
							arithmeticExpression DIV arithmeticExpression 
							{
								$$ = new NodeAST("/");
								$$->addChild($1);
								$$->addChild($3);
							}
							| 
							arithmeticExpression PLUS arithmeticExpression 
							{ 
								$$ = new NodeAST("+");
								$$->addChild($1);
								$$->addChild($3);
							}
							| 
							arithmeticExpression MOINS arithmeticExpression 
							{
								$$ = new NodeAST("-");
								$$->addChild($1);
								$$->addChild($3);
							}
							| 
							PARENTHESEOUVRANTE arithmeticExpression PARENTHESEFERMANTE 
							{ 
								$$ = $2;
							}; 

booleanExpression		:	VRAI
							{
								$$ = new NodeAST("TRUE");
							} 
							| 
							FAUX 
							{
								$$ = new NodeAST("FALSE");
							}
							| 
							arithmeticExpression COMPARATEUR arithmeticExpression
							{
								$$ = new NodeAST($2);
								$$->addChild($1);
								$$->addChild($3);
							}
							| 
							NON booleanExpression 
							{
								$$ = new NodeAST("!");
								$$->addChild($2);
							}
							| 
							booleanExpression ET booleanExpression
							{
								$$ = new NodeAST("&&");
								$$->addChild($1);
								$$->addChild($3);
							}
							| 
							booleanExpression OU booleanExpression
							{
								$$ = new NodeAST("||");
								$$->addChild($1);
								$$->addChild($3);
							}
							| 
							PARENTHESEOUVRANTE booleanExpression PARENTHESEFERMANTE
							{
								$$ = $2;
							};
							
arithmeticExpressionList :	arithmeticExpression | 
							arithmeticExpression VIRGULE arithmeticExpressionList;

instruction				:	RETOUR 
							{ 
								$$ = new NodeAST("RETURN");
							} 
							| 
							RETOUR arithmeticExpression 
							{ 
								$$ = new NodeAST("RETURN");
								$$->addChild($2);
							} 
							| 
							lhs AFFECTATION arithmeticExpression 
							{
								$$ = new NodeAST(":=");
								std::ostringstream oss;
								oss << $1;
								$$->addChild(new NodeAST(oss.str()));
								$$->addChild($3);
							}| 
							lhs AFFECTATION ALLOUER TYPE CROCHETOUVRANT arithmeticExpression CROCHETFERMANT 
							{
								$$ = 0; /* Non géré pour l'instant */
							}
							| 
							DESALLOUER PARENTHESEOUVRANTE VARIABLE PARENTHESEFERMANTE  
							{ 
								$$ = 0; /* Non géré pour l'instant */
							}
							| 
							procedureCall 	
							{ 
								$$ = 0; /* Non géré pour l'instant */ 
							}
							| 
							functionCall 
							{ 
								$$ = 0; /* Non géré pour l'instant */ 
							};

procedureCall			:	VARIABLE PARENTHESEOUVRANTE PARENTHESEFERMANTE | 
							VARIABLE PARENTHESEOUVRANTE arithmeticExpressionList PARENTHESEFERMANTE;

functionCall			:	lhs AFFECTATION VARIABLE PARENTHESEOUVRANTE PARENTHESEFERMANTE | 
							lhs AFFECTATION VARIABLE PARENTHESEOUVRANTE arithmeticExpressionList PARENTHESEFERMANTE;


variableList			:	lhs 
							{ 
								fileIdTemp.push($1);
							} 
							| 
							lhs VIRGULE variableList 
							{
								fileIdTemp.push($1);
							};

vdeclList 				: 	vdecl | vdecl vdeclList;

vdecl					:	TYPE variableList FININSTRUCTION
							{ 
								while(!fileIdTemp.empty())
								{
									tableSymbolesCourante->ajouterSymbole(fileIdTemp.front(), $1);
									fileIdTemp.pop();
								}
							};

ifblock					: 	SI booleanExpression ALORS statement SINON statement
							{
								$$ = new NodeAST("IF");
								$$->addChild($2);
								$$->addChild($4);
								$$->addChild($6);
							};

whileblock				:	TANTQUE booleanExpression FAIRE statement
							{
								$$ = new NodeAST("WHILE");
								$$->addChild($2);
								$$->addChild($4);
							};

blockDeb				: 	BLOCKDEBUT
							{
								std::map<int, std::string> mTemp;
								tableSymbolesCourante->push(mTemp);
							}

block					:	blockDeb statementList BLOCKFIN 
							{
								$$ = new NodeAST("block");
								NodeASTList *lstTemp = $2;
								for (unsigned int i = 0; i < lstTemp->size(); i++)
								{
									$$->addChild(lstTemp->get(i));
								}
								tableSymbolesCourante->pop(); 
							}
							| 
							blockDeb vdeclList statementList BLOCKFIN
							{
								$$ = new NodeAST("block");
								NodeASTList *lstTemp = $3;
								for (unsigned int i = 0; i < lstTemp->size(); i++)
								{
									$$->addChild(lstTemp->get(i));
								}
								tableSymbolesCourante->pop();
							};

statement				:	ifblock { $$ = $1;}| 
							whileblock { $$ = $1;}| 
							block { $$ = $1; } | 
							instruction FININSTRUCTION { $$ = $1;};

statementList			:	statement
							{
								NodeASTList *lstTemp = new NodeASTList();
								lstTemp->addNode($1);
								$$ = lstTemp;
							}
							|
							statement statementList
							{
								NodeASTList *lstTemp = new NodeASTList();
								lstTemp->addNode($1);
								NodeASTList *lstList = $2;
								for (unsigned int i = 0; i < lstList->size(); i++)
								{
									lstTemp->addNode(lstList->get(i));
								}
								$$ = lstTemp;
							};

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
	
	if (!yyparse()) 
	{
		if (root != NULL)
		{
			GeneratorDotFile *myDot = new GeneratorDotFile(root);
			myDot->GenerateDotFile("AST.dot");
		}
		else
		{
			printf("Root is NULL \n");
		}
		return printf("Analyse syntaxique réussie sans encombres !!!\n");
	}
	
	return 1;
}
