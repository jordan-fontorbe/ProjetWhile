%{
	#include <stdio.h>
	#include <iostream>
	#include <TableIds.hpp>
	#include <TableSymboles.hpp>
	#include <queue>
	#include <NodeAST.hpp>
	#include <NodeASTList.hpp>
	#include <sstream>
	#include <GeneratorDOTFile.hpp>
	#include <cstring>
	
	using namespace std;
	
	int yylex(void);
	void yyerror(const char* msg);
	int ligne=1;
	TableIds *tableIdsCourante = new TableIds();
	TableIds *tableIds = new TableIds();
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
%start program
%%

program					:	PROGRAMME BLOCKFIN 
							{ 
								// On crée un noeud seul ...
								root = new NodeAST("Program"); 
							} 
							| 
							pdecl PROGRAMME statementList BLOCKFIN 
							{ 
								// On ne met pas les déclaration dans l'arbre
								root = new NodeAST("Program");
								NodeASTList* lstFils = $3;
								// on ajoute chaque fils a l'arbre
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
								// on ajoute chaque fils a l'arbre
								for (unsigned int i = 0; i < lstFils->size(); i++)
								{
									root->addChild(lstFils->get(i));
								}
							};

lhs						:	VARIABLE 
							{ 
								$$ = $1;
							} 
							| 
							VARIABLE CROCHETOUVRANT arithmeticExpression CROCHETFERMANT { $$ = 0; /* Pour l'instant on ne gère pas les tableaux */};


arithmeticExpression	:	lhs 
							{ 
								// lhs c'est une feuille de l'arbre
								std::string nom = tableIds->getNom($1);
								if (nom == "")
									yyerror("Variable undefined\n");
								$$ = new NodeAST(nom);
								$$->addEntry($1);
								$$->addType(tableSymbolesCourante->getType($1));
							}
							| 
							ENTIER 
							{ 
								// ENTIER c'est une feuille de l'arbre
								std::ostringstream oss;
								oss << $1;
								$$ = new NodeAST(oss.str());
								$$->addType("integer");
							}
							| 
							DECIMAL 
							{
								// DECIMAL c'est une feuille de l'arbre
								std::ostringstream oss;
								oss << $1;
								$$ = new NodeAST(oss.str());
								$$->addType("decimal");
							} 
							|
							MOINS arithmeticExpression %prec NEG { $$ = 0; /* Non géré pour l'instant */} 
							| 
							arithmeticExpression MUL arithmeticExpression 
							{
								$$ = new NodeAST("*");
								$$->addChild($1);
								$$->addChild($3);
								// Si le type a droite n'est pas le meme qu'a gauche on envoie une erreur
								if (!$$->checkType())
									yyerror("Incompatibles types\n");
							} 
							| 
							arithmeticExpression DIV arithmeticExpression 
							{
								$$ = new NodeAST("/");
								$$->addChild($1);
								$$->addChild($3);
								// Si le type a droite n'est pas le meme qu'a gauche on envoie une erreur
								if (!$$->checkType())
									yyerror("Incompatibles types\n");
							}
							| 
							arithmeticExpression PLUS arithmeticExpression 
							{ 
								$$ = new NodeAST("+");
								$$->addChild($1);
								$$->addChild($3);
								// Si le type a droite n'est pas le meme qu'a gauche on envoie une erreur
								if (!$$->checkType())
									yyerror("Incompatibles types\n");
							}
							| 
							arithmeticExpression MOINS arithmeticExpression 
							{
								$$ = new NodeAST("-");
								$$->addChild($1);
								$$->addChild($3);
								// Si le type a droite n'est pas le meme qu'a gauche on envoie une erreur
								if (!$$->checkType())
									yyerror("Incompatibles types\n");
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
								std::string s = $2;
								if(s[0] == '>')
								{
									if(s[1] == '=')
										$$ = new NodeAST(">=");
									else
										$$ = new NodeAST(">");
								}
								else if(s[0] == '<')
								{
									if(s[1] == '=')
										$$ = new NodeAST("<=");
									else 
									{
										if(s[1] == '>')
											$$ = new NodeAST("<>");
										else
											$$ = new NodeAST("<");
									}
								}
								else if(s[0] == '=')
									$$ = new NodeAST("=");
								
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
							
arithmeticExpressionList :	arithmeticExpression 
							| 
							arithmeticExpression VIRGULE arithmeticExpressionList;

instruction				 :	RETOUR 
							{ 
								// C'est une feuille
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
								std::string nom = tableIds->getNom($1);
								// l'Id n'est pas dans la table donc on envoie une erreur
								if (nom == "")
									yyerror("Variable undefined\n");
								
								// Création du noeud
								$$ = new NodeAST(":=");
								NodeAST *nodeLHS = new NodeAST(nom);
								nodeLHS->addEntry($1);
								nodeLHS->addType(tableSymbolesCourante->getType($1));
								$$->addChild(nodeLHS);
								$$->addChild($3);
								
								// Types différents donc on renvoie une erreur
								if (!$$->checkType())
									yyerror("Incompatibles types\n");
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

procedureCall			:	VARIABLE PARENTHESEOUVRANTE PARENTHESEFERMANTE 
							| 
							VARIABLE PARENTHESEOUVRANTE arithmeticExpressionList PARENTHESEFERMANTE;

functionCall			:	lhs AFFECTATION VARIABLE PARENTHESEOUVRANTE PARENTHESEFERMANTE 
							| 
							lhs AFFECTATION VARIABLE PARENTHESEOUVRANTE arithmeticExpressionList PARENTHESEFERMANTE;


variableList			:	lhs 
							{
								// On stock temporairement les Id des déclarations de variables pour gérer
								// les déclaration multiples sur une ligne (ex : "integer x, y, z;")
								fileIdTemp.push($1);
							} 
							| 
							lhs VIRGULE variableList 
							{
								// On stock temporairement les Id des déclarations de variables pour gérer
								// les déclaration multiples sur une ligne (ex : "integer x, y, z;")
								fileIdTemp.push($1);
							};

vdeclList 				: 	vdecl | vdecl vdeclList;

vdecl					:	TYPE variableList FININSTRUCTION
							{ 
								char* nom;
								while(!fileIdTemp.empty())
								{
									int i = fileIdTemp.front();
									string aux = tableIdsCourante->getNom(i);
									nom =(char *) malloc(aux.length());
									strcpy(nom, aux.c_str());
									
									// Il y a une déclaration donc on ajoute cet identifiant à la table
									tableIds->ajouter(nom);
									
									// On ajoute aussi le type à la table des symboles
									tableSymbolesCourante->ajouterSymbole(i, $1);
									
									fileIdTemp.pop();
									
								}
							
							};

ifblock					: 	SI booleanExpression ALORS statement SINON statement
							{
								//Création du noeud
								$$ = new NodeAST("IF");
								$$->addChild($2);
								$$->addChild($4);
								$$->addChild($6);
							};

whileblock				:	TANTQUE booleanExpression FAIRE statement
							{
								//Création du noeud
								$$ = new NodeAST("WHILE");
								$$->addChild($2);
								$$->addChild($4);
							};

blockDeb				: 	BLOCKDEBUT
							{
								// Nouveau block donc nouveau haut de pile
								std::map<int, std::string> mTemp;
								tableSymbolesCourante->push(mTemp);
							}

block					:	blockDeb statementList BLOCKFIN 
							{
								// Création du noeud
								$$ = new NodeAST("block");
								NodeASTList *lstTemp = $2;
								for (unsigned int i = 0; i < lstTemp->size(); i++)
								{
									$$->addChild(lstTemp->get(i));
								}
								
								// Fin du block donc on fait un pop sur la pile
								tableSymbolesCourante->pop(); 
							}
							| 
							blockDeb vdeclList statementList BLOCKFIN
							{
								// Création du noeud
								$$ = new NodeAST("block");
								NodeASTList *lstTemp = $3;
								for (unsigned int i = 0; i < lstTemp->size(); i++)
								{
									$$->addChild(lstTemp->get(i));
								}
								
								// Fin du block donc on fait un pop sur la pile
								tableSymbolesCourante->pop();
							};

statement				:	ifblock { $$ = $1;}
							| 
							whileblock { $$ = $1;}
							| 
							block { $$ = $1; } 
							| 
							instruction FININSTRUCTION { $$ = $1;};

statementList			:	statement
							{
								// Création de la liste des noeuds
								NodeASTList *lstTemp = new NodeASTList();
								lstTemp->addNode($1);
								$$ = lstTemp;
							}
							|
							statement statementList
							{
								// Création de la liste des noeuds, on récupère aussi les précédents ...
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
	fprintf(stderr, "Error line %d : %s \n", ligne, msg);
}
int main(int argc, char** argv) {
	if (argc>1) yyin = fopen(argv[1],"r");
	ligne = 1;
	
	if (!yyparse()) 
	{
		// Génération du DOT
		if (root != NULL)
		{
			GeneratorDotFile *myDot = new GeneratorDotFile(root);
			myDot->GenerateDotFile("AST.dot");
		}
	}
	
	return 1;
}
