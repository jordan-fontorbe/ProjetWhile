/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef TYPE_BOOLEEN_HPP
#   define TYPE_BOOLEEN_HPP
#include "type.hpp"


class TypeBooleen: public Type
{

    public:
	TypeBooleen();

        virtual ~TypeBooleen();

        virtual bool operator== (Type& typeA);

        virtual void afficher() const;

        virtual bool estDeType(typeVariable type);
};

#endif
