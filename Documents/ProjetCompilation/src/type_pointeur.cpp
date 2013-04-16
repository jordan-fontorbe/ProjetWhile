#include <iostream>

#include "type_pointeur.hpp"


TypePointeur::TypePointeur(Type* pointeSurInit)
{
    monType = pointeur;
    pointeSur = pointeSurInit;
}


TypePointeur::~TypePointeur()
{

}


bool TypePointeur::operator== (Type& typeA)
{
    if(getType() == typeA.getType())
    {
        /* Il faut verifier que ce sont des pointeurs vers le meme type. */
        return (*getPointeSur() == *(((TypePointeur*) &typeA)->getPointeSur()));
    }
    else
        return false;
}


void TypePointeur::afficher() const
{
    cout << "Ceci est un Pointeur." << endl;
}


Type* TypePointeur::getPointeSur()
{
    return pointeSur;
}

bool TypePointeur::estDeType(typeVariable type)
{
    return getType() == type;
}

string TypePointeur::getStr()
{
	return "pointeur sur " + this->getPointeSur()->getStr();
}

