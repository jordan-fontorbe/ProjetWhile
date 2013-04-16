#include <iostream>
#include "type_char.hpp"
using namespace std;

TypeCaractere::TypeCaractere()
{
    monType = caractere;
}

TypeCaractere::~TypeCaractere()
{}

bool TypeCaractere::operator== (Type& typeA)
{
    return getType() == typeA.getType();
}

void TypeCaractere::afficher() const
{
    cout << "Ceci est un caractere" << endl;
}

bool TypeCaractere::estDeType(typeVariable type)
{
    return getType() == type;
}
