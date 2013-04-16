/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef TYPE_CHAINE_HPP
#   define TYPE_CHAINE_HPP

#include "type.hpp"
#include "type_char.hpp"


using namespace std;



class TypeChaine : public Type
{
    public:
        TypeChaine();

        virtual ~TypeChaine();

        virtual bool operator== (Type& typeA);

        virtual void afficher() const;

        virtual bool estDeType(typeVariable type);
};

#endif /* TYPE_CHAINE_HPP */
