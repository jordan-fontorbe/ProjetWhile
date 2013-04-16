#include <iostream>
#include "type_booleen.hpp"

using namespace std;

TypeBooleen::TypeBooleen()
{
    monType = booleen;
}

TypeBooleen::~TypeBooleen()
{

}

bool TypeBooleen::operator== (Type& typeA)
{
    return getType() == typeA.getType();
}


void TypeBooleen::afficher() const
{
    cout << "Ceci est un booleen." << endl;
}

bool TypeBooleen::estDeType(typeVariable type)
{
    return getType() == type;
}
