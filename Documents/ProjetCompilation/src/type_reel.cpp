#include <iostream>

#include "type_reel.hpp"


TypeReel::TypeReel()
{
    monType = reel;
}

TypeReel::~TypeReel()
{

}

bool TypeReel::operator== (Type& typeA)
{
    return getType() == typeA.getType();
}


void TypeReel::afficher() const
{
    cout << "Ceci est un reel." << endl;
}

bool TypeReel::estDeType(typeVariable type)
{
    return getType() == type;
}
