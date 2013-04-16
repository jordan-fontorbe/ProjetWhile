/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef TYPE_ENTIER_HPP
#   define TYPE_ENTIER_HPP


#include "type.hpp"


using namespace std;


class TypeEntier : public Type
{

    public:
	TypeEntier();

        virtual ~TypeEntier();

        virtual bool operator== (Type& typeA);

        virtual void afficher() const;

        virtual bool estDeType(typeVariable type);
};

#endif /* TYPE_ENTIER_HPP */
