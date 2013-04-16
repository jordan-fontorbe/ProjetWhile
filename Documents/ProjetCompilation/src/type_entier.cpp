#include <iostream>

#include "type_entier.hpp"


TypeEntier::TypeEntier()
{
    monType = entier;
}

TypeEntier::~TypeEntier()
{

}

bool TypeEntier::operator== (Type& typeA)
{
    return getType() == typeA.getType();
}


void TypeEntier::afficher() const
{
    cout << "Ceci est un Entier." << endl;
}


bool TypeEntier::estDeType(typeVariable type)
{
    return getType() == type;
}
