/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef TYPE_H
#   define TYPE_H


#include <string>


using namespace std;


/**
 * Liste des types de variables.
 */
enum typeVariable
{
    entier,
    reel,
    booleen,
    caractere,
    chaine,
    tableau,
    pointeur,
    structure,
    intervalle,
    enumeration
};

/*!
    classe virtuelle de type
*/
class Type
{
    protected:
        typeVariable monType;

    public:
        /* constructeur */
        Type();
        /* destructeur */
        virtual ~Type();
        /*
         * Surcharge operateur egalite
         * Operateur donné comme this
         */
        virtual bool operator== (Type& typeA) = 0;

        virtual void afficher() const = 0;

        virtual bool estDeType(typeVariable type) = 0;

        typeVariable getType() { return monType; }

        virtual string getStr();
};

#endif /* TYPE_H */
