/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/

#ifndef SYMBOLE_TYPE_HPP
#   define SYMBOLE_TYPE_HPP

#include "symbole.hpp"
#include "type.hpp"

/**
* Une variable est définie par son type
*/
class SymboleType : public Symbole
{
    Type * monType;

public:

    SymboleType();

    SymboleType(Type * type);

    virtual ~SymboleType();

    virtual void afficher() const;

    Type* getType() { return monType; }
};

#endif
