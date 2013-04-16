/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef SYMBOLE_CONSTANTE_HPP
#   define SYMBOLE_CONSTANTE_HPP

#include "symbole.hpp"
#include "type.hpp"
#include <string>

/**
* Une constante est définie par :
* - type
* - valeur
*/
class SymboleConstante : public Symbole
{
    Type * monType;

    /* Valeur du symbole constant */
	union
	{
	    /* Valeur pour constante entiere */
        int valInt;

        /* Valeur pour constante reelle */
        double valReel;

        /* Valeur pour constante booleenne */
        bool valBool;

        /* Valeur pour constante chaine */
        string* valChaine;
        /* A FAIRE : Un appel de fonction est une expression. Il faudrait donc
         * un truc pour savoir quelle est la fonction appelee et quels sont
         * ses parametres etc ! */
	};

public:

    SymboleConstante();

    SymboleConstante(Type * type);

    virtual ~SymboleConstante();

    virtual void afficher() const;

    Type* get_type();

    int getValInt();
    double getValReel();
    bool getValBool();
    string* getValChaine();

    void setValInt(int val);
    void setValReel(double val);
    void setValBool(bool val);
    void setValChaine(string* val);
};

#endif
