/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef SYMBOLE_VARIABLE_HPP
#   define SYMBOLE_VARIABLE_HPP

#include "symbole.hpp"
#include "type.hpp"

/**
* Une variable est définie par son type
*/
class SymboleVariable : public Symbole
{
    Type * monType;

public:

    SymboleVariable();

    SymboleVariable(Type * type);

    virtual ~SymboleVariable();

    virtual void afficher() const;

    Type* getType() { return monType; }
};

#endif
