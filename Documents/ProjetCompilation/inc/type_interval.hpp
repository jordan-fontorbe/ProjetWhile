/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef TYPE_INTERVAL_HPP
#   define TYPE_INTERVAL_HPP

#include <string>
#include "type.hpp"

using namespace std;

class TypeInterval : public Type
{
    private:
        Type * debutType;
        Type * finType;
        string debut;
        string fin;

    public:
        TypeInterval();

        TypeInterval(Type* debutType, Type* finType, string debut, string fin);

        virtual ~TypeInterval();

        virtual bool operator== (Type& typeA);

        virtual void afficher() const;

        virtual bool estDeType(typeVariable type);

        Type* getDebutType() { return debutType; }
        Type* getFinType() { return finType; }

        string getStr();
};

#endif /* TYPE_INTERVAL_HPP */
