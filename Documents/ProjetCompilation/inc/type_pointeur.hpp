/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef TYPE_POINTEUR_HPP
#   define TYPE_POINTEUR_HPP


#include "type.hpp"


using namespace std;


class TypePointeur : public Type
{

    Type* pointeSur;

    public:
        TypePointeur(Type* pointeSurInit);

        virtual ~TypePointeur();

        virtual bool operator== (Type& typeA);

        virtual void afficher() const;

        virtual bool estDeType(typeVariable type);

        Type* getPointeSur();
        
        string getStr();
};

#endif /* TYPE_POINTEUR_HPP */

