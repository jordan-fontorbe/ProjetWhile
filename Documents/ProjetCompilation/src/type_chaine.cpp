#include <iostream>
#include "type_chaine.hpp"
#include "type.hpp"

TypeChaine::TypeChaine()
{
    monType = chaine;
}


bool TypeChaine::operator== (Type& typeA)
{
    //TODO A completer en regardant le contenu du tableau

    return (getType() == typeA.getType() );
}

TypeChaine::~TypeChaine()
{

}

void TypeChaine::afficher() const
{
    cout << "chaine de caractere" << endl;
}

bool TypeChaine::estDeType(typeVariable type)
{
    return getType() == type;
}
