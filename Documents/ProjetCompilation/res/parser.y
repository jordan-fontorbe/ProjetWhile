/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
%{
#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "tab_ids.hpp"
#include "tab_symboles.hpp"
#include "expression.hpp"
#include "gener_type.hpp"
#include "temporaire.hpp"
#include "suite_instructions.hpp"
#include "var_expr.hpp"

#include "Code3ad.hpp"

/* ======= Types ======= */
#include "type.hpp"
#include "type_entier.hpp"
#include "type_reel.hpp"
#include "type_pointeur.hpp"
#include "type_char.hpp"
#include "type_booleen.hpp"
#include "type_interval.hpp"


/* ======= Symboles ======= */
#include "symbole.hpp"
#include "symbole_type.hpp"
#include "symbole_constante.hpp"
#include "symbole_programme.hpp"
#include "symbole_procedure.hpp"
#include "symbole_fonction.hpp"
#include "symbole_argument.hpp"
#include "symbole_variable.hpp"
#include "symbole_argument.hpp"
#include "type_record.hpp"

/* ====== Autres ====== */
#include "tuple_interval.hpp"
#include "tuple_array.hpp"
#include "tuple_record.hpp"

using namespace std;


/* ===== Variables globales ===== */

extern int yyerror (string);
extern int yylex ();

/* Generateur de types */
extern GenerType* genType;

/* Table des identificateurs */
extern TabIds* tab_ident;
/* Bryan : Ici, probleme avec les variables temporaire. Ces dernieres, selon l affichage du prof
	,n apparaissent pas dans la liste des ID et des TS, hors, on les rajoute Faut il une liste table des identifiants temporaires ?*/

/* Table des symboles du programme*/
extern TabSymboles* tab_symb;

extern int nbOpBr;

/* Le code trois adresses genere. */
extern string codeProgramme;

/* ===== Fin variables globales ===== */

%}


/* ================================= UNION ================================= */

%union{
    
    /* Type pour les variables */
    Type* pType;

    /* Valeur pour constante entiere */
    int valCteInt;

    /* Valeur pour constante reelle */
    double valCteReel;

    /* Valeur pour constante booleenne */
    bool valCteBool;

    /* Valeur pour constante chaine */
    string* valCteChaine;

    /* Id d'identificateur */
    int id;
    
    /* Arguments d'une fonction/procedure. On les fait remonter jusqu'a la
     * declaration de la fonction, puis on les ajoute a la table des symboles
     * de la fonction. */
    vector<SymboleArgument*>* lArgs;

    /* Donnees pour une expression */
    Expression*  expr;
    
    /* Liste d'identificateurs */
    vector<int>* listeIds;
    
    /* Succession d'operations en code trois adresses. */
    SuiteIns* code;
    
    /* Donnes du symbole ! terminal VarExp*/
    VarExpr* varExpr;
    
    /* Utilitaire pour l'array*/
    TupleArray * tupleA;
    vector<TupleArray> * vectorTuples;
    
    /* Utiltaire pour Intervalle*/
    TupleInterval * tupleI;
    
    /* Données pour les enum */
    vector<string> * listEnum;
    
    /* Liste de parametres */
    vector<Expression*> * listeParam;
    
    /* Données pour les struct */
    TupleRecord * tupleR;
    vector<TupleRecord> * vectorRecord;
}

%token KW_PROGRAM
%token KW_CONST
%token KW_TYPE
%token KW_VAR
%token KW_ARRAY
%token KW_OF
%token KW_RECORD
%token KW_BEGIN
%token KW_END
%token KW_DIV
%token KW_MOD
%token KW_AND
%token KW_OR
%token KW_XOR
%token KW_NOT
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_DO
%token KW_REPEAT
%token KW_UNTIL
%token KW_FOR
%token KW_TO
%token KW_DOWNTO
%token KW_PROC
%token KW_FUNC
%token KW_NIL
%token KW_INTEGER
%token KW_REAL
%token KW_BOOLEAN
%token KW_CHAR
%token KW_STRING

%token SEP_SCOL
%token SEP_DOT
%token SEP_DOTS
%token SEP_DOTDOT
%token SEP_COMMA
%token SEP_CO
%token SEP_CF
%token SEP_PO
%token SEP_PF

%token OP_EQ
%token OP_NEQ
%token OP_LT
%token OP_LTE
%token OP_GT
%token OP_GTE
%token OP_ADD
%token OP_SUB
%token OP_MUL
%token OP_SLASH
%token OP_EXP
%token OP_PTR
%token OP_AFFECT

%token <id> TOK_IDENT

%token <valCteInt> TOK_INTEGER
%token <valCteReel> TOK_REAL
%token <valCteBool> TOK_BOOLEAN
%token <valCteChaine> TOK_STRING


%type <listeIds> ListIdent
%type <vectorTuples> ListArrayIndex
%type <tupleA> ArrayIndex

%type <tupleI> InterBase
%type <tupleI> NSInterBase

%type <listEnum> ListEnumValue

%type <tupleR> RecordField
%type <vectorRecord> RecordFields

%type <expr> Expression
%type <expr> CompExpr
%type <expr> BoolExpr
%type <expr> AtomExpr
%type <expr> MathExpr

%type <varExpr> VarExpr

%type <pType> Type
%type <pType> UserType
%type <pType> BaseType
%type <pType> PointerType
%type <pType> FuncResult
%type <pType> ArrayType
%type <pType> InterType
%type <pType> EnumType
%type <pType> RecordType

%type <id> ProcIdent
%type <id> FuncIdent
%type <id> ProcHeader
%type <id> FuncHeader

%type <lArgs> FormalArgs
%type <lArgs> FormalArg
%type <lArgs> ListFormalArgs
%type <lArgs> ValFormalArg
%type <lArgs> VarFormalArg

%type <listeParam> ListParameters
%type <listeParam> Parameters

%type <code> Program
%type <code> Block
%type <code> BlockBis
%type <code> BlockDeclFunc
%type <code> BlockCode
%type <code> ListInstr
%type <code> Instr
%type <code> ListDeclFunc
%type <code> DeclFunc
%type <code> FuncDecl
%type <code> ProcDecl
%type <code> Call

%start Program

%nonassoc OP_EQ OP_NEQ OP_GT OP_LT OP_GTE OP_LTE
%left OP_ADD OP_SUB KW_OR KW_XOR
%left OP_MUL OP_SLASH KW_AND KW_DIV KW_MOD
%right KW_NOT OP_NEG OP_POS
%left OP_EXP
%nonassoc OP_PTR
%nonassoc OP_DOT
%left SEP_CO

%nonassoc KW_IFX
%nonassoc KW_ELSE


%%


/* ============================== PROGRAMME ============================== */

Program			:	ProgramHeader SEP_SCOL Block SEP_DOT {
    $$ = $3;
    
    codeProgramme = $$->getStr(tab_ident);
}
                ;

ProgramHeader	:	KW_PROGRAM TOK_IDENT {
    /* Si le programme est bien ecrit, la table de symbole courante est la racine
     * du programme lorsqu'on arrive au "program header". On recupere l'id de
     * l'identificateur du programme. */
    if(tab_symb->getMere() == NULL)
        tab_symb->setIdEntite($2);
    else
        yyerror("Debut de programme apres d'autres instructions");

    tab_symb->add($2, new SymboleProgramme);
}
				;

Block			:	BlockDeclConst BlockDeclType BlockDeclVar BlockDeclFunc BlockCode {
    /* <Code main>
     * end
     * <Code fonctions> */
    $$ = $5;
    $$->add(new Instruction(OPCODE_END));
    $$->add($4);
    
    delete $4;
    
    $$->getPremiere()->setEtiquette("__main_");
}
				;

BlockBis		:	BlockDeclConst BlockDeclType BlockDeclVar BlockCode { $$ = $4; }
				;


/* ============================== CONST ============================== */

BlockDeclConst	:	KW_CONST ListDeclConst {}
			 	|
			 	;

ListDeclConst	:	ListDeclConst DeclConst	{}
			 	|	DeclConst {}
			 	;

DeclConst		:	TOK_IDENT OP_EQ Expression SEP_SCOL {
    SymboleConstante* symboleConst = new SymboleConstante($3->get_type());
    Type* typeConst = $3->get_type();

    if(typeConst->estDeType(entier))
    {
        symboleConst->setValInt($3->getValInt());
    }
    else if(typeConst->estDeType(reel))
    {
        symboleConst->setValReel($3->getValReel());
    }
    else if(typeConst->estDeType(booleen))
    {
        symboleConst->setValBool($3->getValBool());
    }
	else if(typeConst->estDeType(chaine))
	{
		symboleConst->setValChaine($3->getValChaine());
	}

    tab_symb->add($1, symboleConst);
}
			 	;


/* ============================== TYPE ============================== */
//TODO Recuperer le vrai type du type redefini pour le stocker dans la table des symboles

BlockDeclType	:	KW_TYPE ListDeclType {}
			 	|
			 	;

ListDeclType	:	ListDeclType DeclType
			 	|	DeclType
			 	;

DeclType		:	TOK_IDENT OP_EQ Type SEP_SCOL {
	/* Récupération du type */
	SymboleType* symboleType = new SymboleType($3);
	tab_symb->add($1, symboleType);
}
			 	;

/* ============================== VAR ============================== */


BlockDeclVar	:	KW_VAR ListDeclVar {}
			 	|
			 	;

ListDeclVar		:	ListDeclVar DeclVar
			 	|	DeclVar
			 	;

DeclVar			:	ListIdent SEP_DOTS BaseType SEP_SCOL {
	/* Parcour la liste la listIdent pour les ajouter avec leur type correspondant */
	unsigned int i = 0;
	for(i = 0; i < $1->size(); i++)
	{
		tab_symb->add($1->at(i), new SymboleVariable($3));
	}
}
			 	;


ListIdent		:	ListIdent SEP_COMMA TOK_IDENT { 
	$$ = $1;
	$$->push_back($3); 
}
			 	|	TOK_IDENT {
	$$ = new vector<int>; 
	$$->push_back($1);
}
			 	;

/* ============================== FONCTION ============================== */

BlockDeclFunc	:	ListDeclFunc SEP_SCOL /* Action par defaut ok. */
			 	| { $$ = new SuiteIns; } /* Aucune declaration. */
			 	;

ListDeclFunc	:	ListDeclFunc SEP_SCOL DeclFunc {
    $$ = $1;
    $$->add($3);
}
			 	|	DeclFunc /* Action par defaut ok. */
			 	;

DeclFunc		:	ProcDecl 
			 	|	FuncDecl  
			 	;

/* ============================== PROCEDURE ============================== */

ProcDecl		:	ProcHeader SEP_SCOL BlockBis {
	int arite = ((SymboleProcedure*) tab_symb->getMere()->getParId($1)->symb)->getArite();
	int nbPop = 0;
	int iRecherche = 0;
	SymboleArgument* syArg;
	CodeInstruction nouvOperation;
	
	$$ = $3;
	
	while(nbPop < arite) {
	
	    while(tab_symb->get(iRecherche)->symb->getTypeSymbole() != sy_argument)
	        iRecherche++;
	    
	    syArg = (SymboleArgument*) tab_symb->get(iRecherche)->symb;
	    if(syArg->estConstant())
	    {
	        /* Argument passe par valeur. */
	        nouvOperation = OPCODE_POP;
	    }
	    else
	    {
	        /* Argument passe par adresse. */
	        if(syArg->getType()->getType() == tableau)
	            nouvOperation = OPCODE_PPA;
	        else
	            nouvOperation = OPCODE_PPR;
	    }
	    
	    $$->addDebut(new Instruction(
	            nouvOperation,
	            new Operande(syArg->getId())));
	    
	    /* Les pop et push de tableaux ont un operande supplémentaire ! */
	    if(nouvOperation == OPCODE_PPA) {
	        $$->getPremiere()->setY(new Operande(entier));
	        $$->getPremiere()->getY()->setValInt(((TypeTab*) syArg->getType())->getTaille());
	    }
	    
	    nbPop++;
	    iRecherche++;
	}
	
	/* === Ajout de l'etiquette et du return === */
	
	/* Il faut etre sur qu'il y a au moins une instruction. */
	if($$->empty())
	    $$->add(new Instruction(OPCODE_NONE));
	$$->getPremiere()->setEtiquette(tab_ident->get_nom(tab_symb->getIdEntite()));
	
	$$->add(new Instruction(OPCODE_RET));
	
	tab_symb = tab_symb->getMere();
}
			 	;

ProcHeader		:	ProcIdent {
	TabSymboles* tab_symb_temp = new TabSymboles(tab_symb, $1);
	SymboleProcedure * sp = new SymboleProcedure();
	sp->setTs(tab_symb_temp);
	tab_symb->add($1, sp);
	
	tab_symb = tab_symb_temp;
	
	$$ = $1;
}

			 	|	ProcIdent FormalArgs {
	TabSymboles* tab_symb_temp = new TabSymboles(tab_symb, $1);
	SymboleProcedure * sp = new SymboleProcedure();
	unsigned int i;
	
	sp->setTs(tab_symb_temp);
	sp->setArite($2->size());
	tab_symb->add($1, sp);
	
	tab_symb = tab_symb_temp;
	
	/* Recopie des arguments dans la TS de la procedure. */
	for(i = 0;  i < $2->size();  i++) {
	    $2->at(i)->setPosition(i + 1);
	    tab_symb->add($2->at(i)->getId(), $2->at(i));
	}
	
	$$ = $1;
}
			 	;

ProcIdent		:	KW_PROC TOK_IDENT { $$ = $2; }
			 	;

/* Declaration des arguments de fonc ou proc. */
FormalArgs		:	SEP_PO ListFormalArgs SEP_PF { $$ = $2; }
			 	;

/* Liste d'args de fonc ou proc. */
ListFormalArgs	:	ListFormalArgs SEP_SCOL FormalArg {
    /* Concatenation des arguments de $1 et de $3. */
    $1->insert($1->end(), $3->begin(), $3->end());
    $$ = $1;
}
			 	|	FormalArg
			 	;

/* Un arg de la liste des args de fonc ou proc. */
FormalArg		:	ValFormalArg
			 	|	VarFormalArg
			 	;

/* Args constants. */
ValFormalArg	:	ListIdent SEP_DOTS BaseType {
    unsigned int i;
    
    $$ = new vector<SymboleArgument*>;
    
    for(i = 0;  i < $1->size();  i++)
        $$->push_back(new SymboleArgument($3, $$->size() + 1, true, $1->at(i)));
}
			 	;

/* Args variables. */
VarFormalArg	:	KW_VAR ListIdent SEP_DOTS BaseType {
    unsigned int i;
    
    $$ = new vector<SymboleArgument*>;
    
    for(i = 0;  i < $2->size();  i++)
        $$->push_back(new SymboleArgument($4, $$->size() + 1, false, $2->at(i)));
}
			 	;

FuncDecl		:	FuncHeader SEP_SCOL BlockBis { 
	int arite = ((SymboleFonction*) tab_symb->getMere()->getParId($1)->symb)->getArite();
	int nbPop = 0;
	int iRecherche = 0;
	SymboleArgument* syArg;
	CodeInstruction nouvOperation;
	
	$$ = $3;
	
	while(nbPop < arite) {
	
	    while(tab_symb->get(iRecherche)->symb->getTypeSymbole() != sy_argument)
	        iRecherche++;
	    
	    syArg = (SymboleArgument*) tab_symb->get(iRecherche)->symb;
	    if(syArg->estConstant())
	    {
	        /* Argument passe par valeur. */
	        nouvOperation = OPCODE_POP;
	    }
	    else
	    {
	        /* Argument passe par adresse. */
	        if(syArg->getType()->getType() == tableau)
	            nouvOperation = OPCODE_PPA;
	        else
	            nouvOperation = OPCODE_PPR;
	    }
	    
	    $$->addDebut(new Instruction(
	            nouvOperation,
	            new Operande(syArg->getId())));
	    
	    /* Les pop et push de tableaux ont un operande supplémentaire ! */
	    if(nouvOperation == OPCODE_PPA) {
	        $$->getPremiere()->setY(new Operande(entier));
	        $$->getPremiere()->getY()->setValInt(((TypeTab*) syArg->getType())->getTaille());
	    }
	    
	    nbPop++;
	    iRecherche++;
	}
	
	/* === Ajout de l'etiquette et du return === */
	
	/* Il faut etre sur qu'il y a au moins une instruction. */
	if($$->empty())
	    $$->add(new Instruction(OPCODE_NONE));
	$$->getPremiere()->setEtiquette(tab_ident->get_nom(tab_symb->getIdEntite()));
	
	$$->add(new Instruction(OPCODE_RETV, new Operande(tab_symb->getIdEntite())));
	
	tab_symb = tab_symb->getMere();
}
			 	;

/* Fonction sans arguments. */
FuncHeader		:	FuncIdent FuncResult {

	TabSymboles* tab_symb_temp = new TabSymboles(tab_symb, $1);
	SymboleFonction* sp = new SymboleFonction();

	sp->setTs(tab_symb_temp);
	sp->setRetour($2);
	sp->setArite(0);
	tab_symb->add($1, sp);
	
	tab_symb = tab_symb_temp;
	
	$$ = $1;
}
/* Fonction avec arguments. */
			 	|	FuncIdent FormalArgs FuncResult	{
			 	
	TabSymboles* tab_symb_temp = new TabSymboles(tab_symb, $1);
	SymboleFonction* sp = new SymboleFonction();
	unsigned int i;
	
	sp->setTs(tab_symb_temp);
	sp->setRetour($3);
	sp->setArite($2->size());
	tab_symb->add($1, sp);
	
	tab_symb = tab_symb_temp;
	
	/* Recopie des arguments dans la TS de la fonction. */
	for(i = 0;  i < $2->size();  i++) {
	    $2->at(i)->setPosition(i + 1);
	    tab_symb->add($2->at(i)->getId(), $2->at(i));
	}
	
	$$ = $1;
}	
			 	;

FuncIdent		:	KW_FUNC TOK_IDENT { $$ = $2; }
			 	;

FuncResult		:	SEP_DOTS BaseType { $$ = $2; }
			 	;

/* ============================== TYPE ============================== */

Type			:	UserType  /* L'action par defaut convient. */
			 	|	BaseType  /* L'action par defaut convient. */
			 	;

UserType		:	EnumType /* L'action par defaut convient. */
			 	|	InterType /* L'action par defaut convient. */
			 	|	ArrayType /* L'action par defaut convient. */
			 	|	RecordType /* L'action par defaut convient. */
			 	|	PointerType /* L'action par defaut convient. */
			 	;

BaseType		:	TOK_IDENT { $$ = tab_symb->getTypeParId($1); }
				|   KW_INTEGER { $$ = genType->creerTypeEntier(); }
				|	KW_REAL { $$ = genType->creerTypeReel(); }
				|	KW_BOOLEAN { $$ = genType->creerTypeBooleen(); }
				|	KW_CHAR { $$ = genType->creerTypeCaractere(); }
				|	KW_STRING { $$ = genType->creerTypeChaine(); }
				;

/* ============================== ENUM ============================== */

EnumType		:	SEP_PO ListEnumValue SEP_PF { $$ = genType->creerTypeEnum($2); }
			 	;

ListEnumValue	:	ListEnumValue SEP_COMMA TOK_IDENT { $$ = $1; $$->push_back(tab_ident->get_nom($3)); }
			 	|	TOK_IDENT { $$ = new vector<string>(); $$->push_back(tab_ident->get_nom($1)); }
			 	;

/* ============================== INTERVALLE ============================== */

InterType		:	InterBase SEP_DOTDOT InterBase { 
	if($1->getType() == $3->getType())
	{
		$$ = genType->creerTypeInterval($1->getType(), $3->getType(), $1->getNom(), $3->getNom()); 
	}
	else
		yyerror("Les types de l'intervalle ne sont pas compatibles");
}
			 	;

InterBase		:	NSInterBase  /* L'action par defaut convient. */
			 	|	OP_SUB NSInterBase { 
	if ($2->getEstVar() == false)
		$2->setVal(- $2->getEstVar());
	$$ = $2;

}
			 	;

NSInterBase		:	TOK_IDENT { 
	$$ = new TupleInterval(tab_symb->getTypeParId($1), tab_ident->get_nom($1), $1, true);
}

			 	|	TOK_INTEGER {
	string nom = static_cast<ostringstream*>( &(ostringstream() << $1) )->str();
	$$ = new TupleInterval(genType->creerTypeEntier(), nom, $1, false);
}
			 	;

/* ============================== ARRAY ============================== */

ArrayType		:	KW_ARRAY SEP_CO ListArrayIndex SEP_CF KW_OF BaseType {
	
	// Verifier que tout est du meme type
	Type * referenceType;

	if($3->at(0).getEstId())
	{
		referenceType = tab_symb->getTypeParId($3->at(0).getVal());
		if(referenceType == NULL)
			yyerror("0 ne respecte pas le bon type");
	}
	else
		referenceType = genType->creerTypeEntier();
	
	unsigned int i;
	for(i = 1; i < $3->size(); i++)
	{
		if($3->at(i).getEstId())
		{
			if(tab_symb->getTypeParId($3->at(i).getVal()) != referenceType)
				yyerror(i + " ne respecte pas le bon type");
		}
		else
			if(referenceType->estDeType(entier))
				yyerror(i + " ne respecte pas le bon type");
	}
	
	/* Creation du tableau */
	int taille = $3->size();
	if(taille == 1 && $3->at(0).getVal() != 0 )
		taille = $3->at(0).getVal() + 1;
	$$ = genType->creerTypeTab($6,referenceType, taille);
}
			 	;

ListArrayIndex	:	ListArrayIndex SEP_COMMA ArrayIndex {
	$$ = $1;
	$$->push_back(*$3);
}

				|	ArrayIndex {
	$$ = new vector<TupleArray>();
	$$->push_back(*$1);
}
				;

ArrayIndex		:	TOK_IDENT { $$ = new TupleArray(true,$1); }
			 	|	TOK_INTEGER { $$ = new TupleArray(false,$1); }
			 	;

/* ============================== RECORD ============================== */

RecordType		:	KW_RECORD RecordFields KW_END { $$ = genType->creerTypeRecord($2); }
			 	;

RecordFields	:	RecordFields SEP_SCOL RecordField { $$ = $1; $$->push_back(*$3); }
			 	|	RecordField { $$ = new vector<TupleRecord>(); $$->push_back(*$1); }
			 	;

RecordField		:	ListIdent SEP_DOTS BaseType { vector<string>* v = new vector<string>();
    for (unsigned int i = 0; i < $1->size(); i++)
    {
        v->push_back(tab_ident->get_nom((*$1)[i]));
    }
    $$ = new TupleRecord(v, $3);
}
			 	;

/* ============================== POINTEUR ============================== */

PointerType		:	OP_PTR BaseType { $$ = genType->creerTypePointeur($2); }
			 	;

/* ============================== INSTRUCTIONS ============================== */

BlockCode		:	KW_BEGIN ListInstr KW_END { $$ = $2; }
				|	KW_BEGIN ListInstr SEP_SCOL KW_END { $$ = $2; }
				|	KW_BEGIN KW_END { $$ = new SuiteIns; }
			 	;

ListInstr		:	ListInstr SEP_SCOL Instr {
    $$ = $1;
    $$->add($3);
}
			 	|	Instr {
    $$ = new SuiteIns;
    $$->add($1);
}
			 	;

Instr			:	KW_WHILE Expression KW_DO Instr {

    nbOpBr++;
    string nbOpBrStr = static_cast<ostringstream*>( &(ostringstream() << nbOpBr) )->str();
    $$ = $2->getCode();
    
    $$->addDebut(new Instruction(OPCODE_NONE));
    /* Debut de la boucle*/
    $$->getPremiere()->setEtiquette("condWhile" + nbOpBrStr);
    $$->add(new Instruction(OPCODE_JMPC, new Operande($$->getIdRes()), new Operande(new string("bouWhile" + nbOpBrStr))));
    $$->add(new Instruction(OPCODE_JMP, new Operande(new string("finWhile" + nbOpBrStr))));
    
    /* Boucle */
    if($4->empty())
		$4->add(new Instruction(OPCODE_NONE));
		
	$4->getPremiere()->setEtiquette("bouWhile" + nbOpBrStr);
	
	/* Retour a la cond boucle */
	$$->add($4);
	$$->add(new Instruction(OPCODE_JMP, new Operande(new string("condWhile" + nbOpBrStr))));
	
	/* Fin du while */
	Instruction* instrFinSi = new Instruction(OPCODE_NONE);
	instrFinSi->setEtiquette("finWhile" + nbOpBrStr);
	$$->add(instrFinSi);
    
}
			 	|	KW_REPEAT ListInstr KW_UNTIL Expression {
	nbOpBr++;
    string nbOpBrStr = static_cast<ostringstream*>( &(ostringstream() << nbOpBr) )->str();  
    
    $$ = $2;
    
    /* Contenu de la boucle */
    if($$->empty())
    	$$->add(new Instruction(OPCODE_NONE));
    
    $$->getPremiere()->setEtiquette("debRepeat" + nbOpBrStr);
    
    /* Condition d'arret */
    $$->add($4->getCode());
    $$->add(new Instruction(
    		OPCODE_JMPC,
    		new Operande($4->getCode()->getIdRes()),
    		new Operande(new string("finRepeat" + nbOpBrStr))));
    
    /* Bouclage */
    $$->add(new Instruction(OPCODE_JMP, new Operande(new string("debRepeat" + nbOpBrStr))));
    
    /* Fin de la boucle */
    Instruction* instrFinRepeat = new Instruction(OPCODE_NONE);
	instrFinRepeat->setEtiquette("finRepeat" + nbOpBrStr);
	$$->add(instrFinRepeat);
}

			 	|	KW_FOR TOK_IDENT OP_AFFECT Expression ForDirection Expression KW_DO Instr {
    /* TO DO / a faire / TODO */
    /* Creation d un VarExpr pour la variable. */
    //VarExpr * tempEx = new VarExpr($2, tve_idSimple);
    $$ = new SuiteIns;
}
			 	|	KW_IF Expression KW_THEN Instr %prec KW_IFX {
    
    nbOpBr++;
    
    $$ = $2->getCode();
    
    string nbOpBrStr = static_cast<ostringstream*>( &(ostringstream() << nbOpBr) )->str();
    
    $$->add(new Instruction(OPCODE_JMPC, new Operande($$->getIdRes()), new Operande (new string("then" + nbOpBrStr))));
    $$->add(new Instruction(OPCODE_JMP, new Operande(new string("ifend" + nbOpBrStr))));
	
    /* Bloc then */
    if($4->empty())
    	$4->add(new Instruction(OPCODE_NONE));
    
	$4->getPremiere()->setEtiquette("then" + nbOpBrStr);
	$$->add($4);
	$$->add(new Instruction(OPCODE_JMP, new Operande(new string("ifend" + nbOpBrStr))));
	
	/* Fin si */
	Instruction* instrFinSi = new Instruction(OPCODE_NONE);
	instrFinSi->setEtiquette("ifend" + nbOpBrStr);
	$$->add(instrFinSi);
}
			 	|	KW_IF Expression KW_THEN Instr KW_ELSE Instr {
    
    nbOpBr++;
    
    $$ = $2->getCode();
    
    string nbOpBrStr = static_cast<ostringstream*>( &(ostringstream() << nbOpBr) )->str();
    
    $$->add(new Instruction(OPCODE_JMPC, new Operande($2->getCode()->getIdRes()), new Operande (new string("then" + nbOpBrStr ))));
    $$->add(new Instruction(OPCODE_JMP, new Operande(new string("else" + nbOpBrStr))));
    
    /* Bloc then */
    if($4->empty())
    	$4->add(new Instruction(OPCODE_NONE));

	$4->getPremiere()->setEtiquette("then" + nbOpBrStr);
	$$->add($4);
	$$->add(new Instruction(OPCODE_JMP, new Operande(new string("ifend" + nbOpBrStr))));
	
    /* Bloc else */
    if($6->empty())
    	$6->add(new Instruction(OPCODE_NONE));
    
	$6->getPremiere()->setEtiquette("else" + nbOpBrStr);
	$$->add($6);
	$$->add(new Instruction(OPCODE_JMP, new Operande(new string("ifend" + nbOpBrStr))));
	
	/* Fin si */
	Instruction* instrFinSi = new Instruction(OPCODE_NONE);
	instrFinSi->setEtiquette("ifend" + nbOpBrStr);
	$$->add(instrFinSi);
}
			 	|	VarExpr OP_AFFECT Expression {
    Operande* op1;
    Operande* op2;
    
    $$ = $3->getCode();
    
    switch($1->getType())
    {
        case tve_idSimple:
            op1 = new Operande($1->getId());
            break;
        case tve_tableau:
            /* TO DO / a faire / TODO */
            op1 = new Operande($1->getId());
            break;
        case tve_trucAvecPrec:
            /* TO DO / a faire / TODO */
            op1 = new Operande($1->getId());
            break;
        case tve_pointeur:
            /* TO DO / a faire / TODO */
            op1 = new Operande($1->getId());
            break;
        default:
            break;
    }
    
    if($3->getCalculee())
    {
        op2 = new Operande($3->get_type()->getType());
        switch($3->get_type()->getType())
        {
            case entier:
                op2->setValInt($3->getValInt());
                break;
            case reel:
                op2->setValReel($3->getValReel());
                break;
            case booleen:
                op2->setValBool($3->getValBool());
                break;
            default:
                yyerror("Erreur : expression calculee de type ne pouvant avoir ete calcule");
                break;
        }
    } else {
        /* Expression non calculee. */
        op2 = new Operande($3->getCode()->getIdRes());
    }
    
    $$->add(new Instruction(OPCODE_CPY, op1, op2));
}
			 	|	Call /* L'action par defaut convient. */
			 	|	BlockCode /* L'action par defaut convient. */
			 	;

ForDirection	:	KW_TO
			 	|	KW_DOWNTO
			 	;

/* ============================== EXPRESSION ============================== */

Expression		:	MathExpr /* L'action par defaut convient. */
			 	|	CompExpr /* L'action par defaut convient. */
			 	|	BoolExpr /* L'action par defaut convient. */
			 	|	AtomExpr /* L'action par defaut convient. */
			 	|	VarExpr {
	Expression * res = NULL;
	int ident = $1->getId();
	if($1->getType() ==tve_idSimple)
	{
		
		res = new Expression();
		res->setCalculee(false);
		tupleTabSymboles* tp = tab_symb->getParId( ident);
		if( tp == 0)
		{
			string sterror = "Erreur :  Utilisation de variable non déclarée : " + tab_ident->get_nom(ident);
			yyerror(sterror);
			return -1; //Fin du parsing, on ne peut continuer
		}
		Symbole * symb = (Symbole*)tab_symb->getParId( ident)->symb;		
		SymboleVariable * symbType = NULL;
		SymboleConstante * symbConst = NULL;
		SymboleArgument * symbArg = NULL;
		switch( symb->getTypeSymbole())
		{
			case sy_variable : symbType= (SymboleVariable*) symb; 
					   res->setType(symbType->getType());
					   res->setId( ident );
					   break;
			case sy_constante : symbConst= (SymboleConstante*)symb;
					    res->setType(symbConst->get_type());
					    res->setId(ident);
					    break;
			case sy_programme : break;
			case sy_argument : symbArg= (SymboleArgument*)symb;
					    res->setType(symbArg->getType());
					    res->setId(ident);
					    break;
			case sy_fonction :
			case sy_procedure :
			case sy_type :
			default : break;
		}
		$$ = res;
	}
}
				|	Call {
	$$ = new Expression;
	$$->setCode(*$1);
}
			 	;

MathExpr		:	Expression OP_ADD Expression {  

	int codeErreur = 0;
	Expression * res = NULL;
	res = $1->calculNumerique( $3, Operator_plus, codeErreur, tab_ident, nbOpBr);
	switch(codeErreur)
	{
		case 0 : $$ = res; break;
		case 1 : yyerror("Type incompatible calculNumerique - Operator_add"); break;
		case 2 : yyerror("Operator '+' invalide avec type"); break;
	}
}
			 	|	Expression OP_SUB Expression {  
	int codeErreur = 0;
	Expression * res = NULL;
	res = $1->calculNumerique( $3, Operator_moins, codeErreur, tab_ident, nbOpBr);
	switch(codeErreur)
	{
		case 0 : $$ = res; break;
		case 1 : yyerror("Type incompatible calculNumerique - Operator_moins"); break;
		case 2 : yyerror("Operator '-' invalide avec type"); break;
	}
}
			 	|	Expression OP_MUL Expression {  
	int codeErreur = 0;
	Expression * res = NULL;
	res = $1->calculNumerique( $3, Operator_fois, codeErreur, tab_ident, nbOpBr);
	switch(codeErreur)
	{
		case 0 : $$ = res; break;
		case 1 : yyerror("Type incompatible calculNumerique - Operator_mult"); break;
		case 2 : yyerror("Operator '*' invalide avec type"); break;
		case 3 : yyerror("Division par zero"); break;
	}
}
			 	|	Expression OP_SLASH Expression {
	int codeErreur = 0;
	Expression * res = NULL;
	res = $1->calculNumerique( $3, Operator_slash, codeErreur, tab_ident, nbOpBr);
	switch(codeErreur)
	{
		case 0 : $$ = res; break;
		case 1 : yyerror("Type incompatible calculNumerique - Operator_slash"); break;
		case 2 : yyerror("Operator '/' invalide avec type"); break;
		case 3 : yyerror("Division par zero"); break;
	}
}
			 	|	Expression KW_DIV Expression {
	int codeErreur = 0;
	Expression * res = NULL;
	res = $1->calculNumerique( $3, Operator_div, codeErreur, tab_ident, nbOpBr);
	switch(codeErreur)
	{
		case 0 : $$ = res; break;
		case 1 : yyerror("Type incompatible calculNumerique - Operator_DIV"); break;
		case 2 : yyerror("Operator 'div' invalide avec type"); break;
		case 3 : yyerror("Division par zero"); break;
	}
}
			 	|	Expression KW_MOD Expression {
	int codeErreur = 0;
	Expression * res = NULL;
	res = $1->calculNumerique( $3, Operator_mod, codeErreur, tab_ident, nbOpBr);
	switch(codeErreur)
	{
		case 0 : $$ = res; break;
		case 1 : yyerror("Type incompatible calculNumerique - Operator_MOD"); break;
		case 2 : yyerror("Operator 'mod' invalide avec type"); break;
		case 3 : yyerror("Division par zero"); break;
	}
}
			 	|	Expression OP_EXP Expression {
	int codeErreur = 0;
	Expression * res = NULL;
	res = $1->calculNumerique( $3, Operator_puis, codeErreur, tab_ident, nbOpBr);
	switch(codeErreur)
	{
		case 0 : $$ = res; break;
		case 1 : yyerror("Type incompatible calculNumerique - Operator_Exp"); break;
		case 2 : yyerror("Operator '**' invalide avec type"); break;
		case 3 : yyerror("Division par zero"); break;
	}
}
			 	|	OP_SUB Expression %prec OP_NEG {}
			 	|	OP_ADD Expression %prec OP_POS {}
			 	;

CompExpr		:	Expression OP_EQ Expression { 	int codeErreur = 0;
								Expression * res = $1->calculComp($3, Operator_eq, codeErreur, tab_ident);
								switch(codeErreur)
								{
									case 0 : $$ = res; break;
									case 1 : yyerror("Type incompatible calculComp - Operator_eq"); break;
									case 2 : yyerror("Operator invalide avec type"); break;
								}
}
			 	|	Expression OP_NEQ Expression { 	int codeErreur = 0;
								Expression * res = $1->calculComp($3, Operator_neq, codeErreur, tab_ident);
								switch(codeErreur)
								{
									case 0 : $$ = res; break;
									case 1 : yyerror("Type incompatible calculComp - Operator_neq"); break;
									case 2 : yyerror("Operator invalide avec type"); break;
								}
}
			 	|	Expression OP_LT Expression { 	int codeErreur = 0;
								Expression * res = $1->calculComp($3, Operator_inf, codeErreur, tab_ident);
								switch(codeErreur)
								{
									case 0 : $$ = res; break;
									case 1 : yyerror("Type incompatible calculComp - Operator_inf"); break;
									case 2 : yyerror("Operator invalide avec type"); break;
								}
}
			 	|	Expression OP_LTE Expression { 	int codeErreur = 0;
								Expression * res = $1->calculComp($3, Operator_infeq, codeErreur, tab_ident);
								switch(codeErreur)
								{
									case 0 : $$ = res; break;
									case 1 : yyerror("Type incompatible calculComp - Operator_infeq"); break;
									case 2 : yyerror("Operator invalide avec type"); break;
								}
}
			 	|	Expression OP_GT Expression { 	int codeErreur = 0;
								Expression * res = $1->calculComp($3, Operator_sup, codeErreur, tab_ident);
								switch(codeErreur)
								{
									case 0 : $$ = res; break;
									case 1 : yyerror("Type incompatible calculComp - Operator_sup"); break;
									case 2 : yyerror("Operator invalide avec type"); break;
								}
}
			 	|	Expression OP_GTE Expression { 	int codeErreur = 0;
								Expression * res = $1->calculComp($3, Operator_supeq, codeErreur, tab_ident);
								switch(codeErreur)
								{
									case 0 : $$ = res; break;
									case 1 : yyerror("Type incompatible calculComp - Operator_supeq"); break;
									case 2 : yyerror("Operator invalide avec type"); break;
								}
}
			 	;

BoolExpr		:	Expression KW_AND Expression {
												int codeErreur = 0;
												Expression * res = $1->calculBool($3, Operator_and, codeErreur, tab_ident);
												switch(codeErreur)
												{
													case 0 : $$ = res; break;
													case 1 : yyerror("Type incompatible calculBool - Operator_and"); break;
													case 2 : yyerror("Operator invalide"); break;
												}
}
			 	|	Expression KW_OR Expression {
											  int codeErreur = 0;
											  Expression * res = $1->calculBool($3, Operator_or, codeErreur, tab_ident);
											  switch(codeErreur)
											  {
											     case 0 : $$ = res; break;
											     case 1 : yyerror("Type incompatible calculBool - Operator_or"); break;
											     case 2 : yyerror("Operator invalide"); break;
											  }
}
			 	|	Expression KW_XOR Expression {
											  int codeErreur = 0;
											  Expression * res = $1->calculBool($3, Operator_xor, codeErreur, tab_ident);
											  switch(codeErreur)
											  {
											     case 0 : $$ = res; break;
											     case 1 : yyerror("Type incompatible calculBool - Operator_xor"); break;
											     case 2 : yyerror("Operator invalide"); break;
											  }
}
			 	|	KW_NOT Expression {
											  int codeErreur = 0;
											  Expression * res = $2->calculBool(NULL, Operator_not, codeErreur, tab_ident);
											  switch(codeErreur)
											  {
											     case 0 : $$ = res; break;
											     case 1 : yyerror("Type incompatible calculBool - Operator_not"); break;
											     case 2 : yyerror("Operator invalide"); break;
											  }
}
			 	;

AtomExpr		:	SEP_PO Expression SEP_PF { $$ = $2; }
			 	|	TOK_INTEGER {
	$$ = new Expression(genType->creerTypeEntier());
	$$->setValInt($1);
	$$->setCalculee(true);
}
			 	|	TOK_REAL {
	$$ = new Expression(genType->creerTypeReel());
	$$->setValReel($1);
	$$->setCalculee(true);
}
			 	|	TOK_BOOLEAN {
	$$ = new Expression(genType->creerTypeBooleen());
	$$->setValBool($1);
	$$->setCalculee(true);
}
			 	|	KW_NIL {
	$$ = new Expression(genType->creerTypeEntier());
	$$->setValInt(0);
	$$->setCalculee(true);
}
			 	|	TOK_STRING {
	$$ = new Expression(genType->creerTypeChaine());
	$$->setValChaine($1);
	$$->setCalculee(true);
}
			 	;

VarExpr			:	TOK_IDENT {
    $$ = new VarExpr($1, tve_idSimple);
}
				|	TOK_IDENT SEP_CO ListIndices SEP_CF {
    /* TO DO / a faire */
    /* Temporaire !! */
    $$ = new VarExpr($1, tve_tableau);
}
				|	TOK_IDENT SEP_DOT TOK_IDENT %prec OP_DOT {
    /* TO DO / a faire */
    /* Temporaire !! */
    $$ = new VarExpr($1, tve_trucAvecPrec);
}
				|	TOK_IDENT OP_PTR {
    /* TO DO / a faire */
    /* Temporaire !! */
    $$ = new VarExpr($1, tve_pointeur);
}
				;

Call			:	TOK_IDENT Parameters {

	Symbole* syProcOuFonc;
	SymboleProcedure* syProc;
	SymboleFonction* syFonc;
	/* La TS de la fonction ou de la procedure appelee. */
	TabSymboles* tabSymbTrucAppele;
	int arite;
	
	/* Recuperation des infos sur la fonction on procedure appelee. */
	syProcOuFonc = tab_symb->getSymboleParId($1);
	
	$$ = new SuiteIns;
	
	if(syProcOuFonc == NULL)
		yyerror("Appel de " + tab_ident->get_nom($1) + " : aucun symbole ne porte ce nom");
	else
	{
		switch(syProcOuFonc->getTypeSymbole())
		{
			case sy_fonction : 
				syFonc = (SymboleFonction*) syProcOuFonc;
				tabSymbTrucAppele = syFonc->getTs();
				arite = syFonc->getArite();
				break;
			case sy_procedure :
				syProc = (SymboleProcedure*) syProcOuFonc;
				tabSymbTrucAppele = syProc->getTs();
				arite = syProc->getArite();
				break;
			default :
				yyerror("Appel de " + tab_ident->get_nom($1) + ", qui n'est ni une fonction ni une procedure");
				break;
		}
	
		/* Verification du nombre de parametres. */
		if(arite != (int) $2->size())
			yyerror("Mauvais nombre de parametres pour " + tab_ident->get_nom($1));
	
		/* Placement des parametres sur la pile. */
		int iRecherche = 0;
		int nbPush = 0;
		SymboleArgument* syArg;
		CodeInstruction nouvOperation;
	
		while(nbPush < arite)
		{
			while(tabSymbTrucAppele->get(iRecherche)->symb->getTypeSymbole() != sy_argument)
				iRecherche++;
		
			syArg = (SymboleArgument*) tabSymbTrucAppele->get(iRecherche)->symb;
		
			if(syArg->estConstant())
			{
			    /* Argument passe par valeur. */
			    nouvOperation = OPCODE_PSH;
			}
			else
			{
			    /* Argument passe par adresse. */
			    if(syArg->getType()->getType() == tableau)
			        nouvOperation = OPCODE_PSA;
			    else
			        nouvOperation = OPCODE_PSP;
			}
		
			/* Insertion du code de la n-ieme expression. */
			$$->add($2->at(nbPush)->getCode());
		
			/* Ajout du push. */
			if($2->at(nbPush)->getCalculee())
			{
				/* Push de valeur calculee */
				string * strOperande;
				string strOperandeTmp;
				switch($2->at(nbPush)->get_type()->getType())
				{
					case entier:
						strOperandeTmp = static_cast<ostringstream*>( &(ostringstream() << $2->at(nbPush)->getValInt()) )->str();
						break;
					case reel:
						strOperandeTmp = static_cast<ostringstream*>( &(ostringstream() << $2->at(nbPush)->getValReel()) )->str();
						break;
					case booleen:
						strOperandeTmp = $2->at(nbPush)->getValBool() ? "true" : "false";
						break;
					case chaine:
						strOperandeTmp = *($2->at(nbPush)->getValChaine());
						break;
					default:
						break;
				}
				strOperande = new string(strOperandeTmp);
				
				$$->add(new Instruction(
					    nouvOperation,
					    new Operande(strOperande)));
			}
			else
			{
				/* Push de variable */
				$$->add(new Instruction(
					    nouvOperation,
					    new Operande($2->at(nbPush)->getCode()->getIdRes())));
		    }
			
			/* Les pop et push de tableaux ont un operande supplémentaire ! */
			if(nouvOperation == OPCODE_PSA) {
			    $$->getPremiere()->setY(new Operande(entier));
			    $$->getPremiere()->getY()->setValInt(((TypeTab*) syArg->getType())->getTaille());
			}
		
			nbPush++;
		}
	
		$$->add(new Instruction(OPCODE_CLL, new Operande($1)));
	}
}
				;

Parameters		:	SEP_PO ListParameters SEP_PF { $$ = $2; }
				|	SEP_PO SEP_PF { $$ = new vector<Expression*>; }
				;

ListIndices		:	ListIndices SEP_COMMA Expression
				|	Expression
				;

ListParameters	:	ListParameters SEP_COMMA Expression { $$ = $1; $$->push_back($3); }
				|	Expression { $$ = new vector<Expression*>; $$->push_back($1); }
				;

%%


