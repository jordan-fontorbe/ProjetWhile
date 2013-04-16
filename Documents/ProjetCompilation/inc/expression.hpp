#ifndef EXPRESSION_HPP
#   define EXPRESSION_HPP
/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/

#include <string>

#include "type.hpp"
#include "suite_instructions.hpp"
#include "tab_symboles.hpp"
#include "tab_ids.hpp"


using namespace std;


/* Enum d'operations possibles sur des variables numériques */
enum OperatorNumerique {Operator_plus, Operator_moins, Operator_fois, Operator_slash ,Operator_div, Operator_puis, Operator_mod};

/* Enum d'operations possibles sur les bool*/
enum OperatorBooleen {Operator_and, Operator_or, Operator_xor, Operator_not};

enum OperatorComp {Operator_eq, Operator_neq, Operator_sup, Operator_supeq, Operator_inf, Operator_infeq};

class Expression
{
    /* Type de l'expression. A mettre a jour au fil des calculs. */
    Type* monType;

    /* Vrai si et seulement si on a pu calculer
     * l'expression (que des constantes, etc). */
    bool calculee;

    SuiteIns code;

    /* Valeur de l'expression.
     * Pris en compte si et seulement si "calculee" est a vrai. */
	union
	{
	    /* Valeur pour expression calculee entiere. */
        int valInt;

	/* Id valable uniquement si expression non calculee */
	int id;

        /* Valeur pour expression calculee reelle. */
        double valReel;

        /* Valeur pour expression calculee booleenne. */
        bool valBool;

        string* valChaine;
        /* A FAIRE : Un appel de fonction est une expression. Il faudrait donc
         * un truc pour savoir quelle est la fonction appelee et quels sont
         * ses parametres etc ! */
	};

	public:
        Expression();
        Expression(Type* type);
        ~Expression();
        Type* get_type();
        void setType( Type* type);

        bool getCalculee();
        int getValInt();
        double getValReel();
        bool getValBool();
        string* getValChaine();
	int getId();

        void setCalculee(bool calc);
        void setValInt(int val);
        void setValReel(double val);
        void setValBool(bool val);
        void setValChaine(string* val);
	void setId(int i);

	/**
	 *   Crée une opérande à partir de l'expression
	**/
	Operande * createOperande(TabIds * tabIdent);

        /**
         *   Va evaluer le resultat de la comparaison boolean entre deux expressions
         *   Cela va retourner une expression initialisee avec un type Boolean et la valeur
         *   codeErreur = 0 // Tout va bien
         *   codeErreur = 1 // Types incompatibles
         *   codeErreur = 2 // OperatorBoolean invalide
         */
        Expression * calculBool(Expression* ex2, OperatorBooleen comparator, int &codeErreur
				  , TabIds * tabIdent);


	/**
	*    Retourne l'expression composante de deux expressions de type Reel ou entier
	*
	*/
	Expression * calculNumerique( Expression * ex2, OperatorNumerique comparator, int &codeErreur
					, TabIds * tabIdent, int &nbOpBr);

        /**
         *   Retourne l'expression composante de deux expressions de type Reel.
         *   Cela va retourner une expression initialisee avec un type Reel et un code d'erreur
         *   codeErreur = 0 // Tout va bien
         *   codeErreur = 1 // Types incompatibles
         *   codeErreur = 2 // OperatorNumerique incompatible
	 *   codeErreur = 3 // Division par zero.
         */
	Expression * calculReel( Expression * ex2, OperatorNumerique comparator, int &codeErreur
					, TabIds * tabIdent);

	/**
         *   Retourne l'expression composante de deux expressions de type Reel.
         *   Cela va retourner une expression initialisee avec un type Reel et un code d'erreur
         *   codeErreur = 0 // Tout va bien
         *   codeErreur = 1 // Types incompatibles
         *   codeErreur = 2 // OperatorNumerique incompatible
	 *   codeErreur = 3 // Division par zero.
	*/
	Expression * calculEntier( Expression * ex2, OperatorNumerique comparator, int &codeErreur
					, TabIds * tabIdent, int &nbOpBr );


        /* Renvoie un booleen de comparaison. */
        //Ancienne version
        Expression * calculComp(Expression* ex2, OperatorComp comparator, int &codeErreur);
        Expression * calculComp(Expression* ex2, OperatorComp comparator, int &codeErreur, TabIds * tabIdent);
        Expression * calculCompReel(Expression* ex2, OperatorComp comparator, int &codeErreur, TabIds * tabIdent);
        Expression * calculCompEntier(Expression* ex2, OperatorComp comparator, int &codeErreur, TabIds * tabIdent);



        SuiteIns* getCode() { return &code; }
        void setCode(SuiteIns* _code) { code = *_code; }
        void setCode(SuiteIns _code) { code = _code; }

        /** Ajoute une instruction a la fin de la
         * suite d'instruction du code de l'expression. */
        void ajouterIns(Instruction* nouvIns) { code.add(nouvIns); }
        /** Ajoute toutes les instructions du code d'une expression a la fin de la suite
         * d'instructions du code de "this". */
        void ajouterSuiteIns(Expression* expr);
};


#endif /* EXPRESSION_HPP */
