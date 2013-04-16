/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef SYMBOLE_ARGUMENT_HPP
#   define SYMBOLE_ARGUMENT_HPP

#include "symbole.hpp"
#include "type.hpp"


/**
* Un argument est defini par :
* - mode passe (constant ou variable)
* - type
* - position dans la liste
*/
class SymboleArgument : public Symbole
{
    Type * monType;
    int maPosition;
    bool constant;
    /* Identifiant de l'argument dans la table des
     * identificateurs. */
    int monId;

public:

    SymboleArgument();

    SymboleArgument(Type * type, const int & position, bool constant, int id);

    virtual ~SymboleArgument();

    virtual void afficher() const;

    Type* getType() { return monType; }
    void setType(Type* t) { monType = t; }

    int getPosition() { return maPosition; }
    void setPosition(int p) { maPosition = p; }

    bool estConstant() { return constant; }
    void setConstant(bool ct) { constant = ct; }

    int getId() { return monId; }
    void setId(int id) { monId = id; }
};

#endif
