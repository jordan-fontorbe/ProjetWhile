#include "symbole_constante.hpp"
#include <iostream>
using namespace std;


SymboleConstante::SymboleConstante()
{
    monType = NULL;
    monTypeSymbole = sy_constante;
}

SymboleConstante::SymboleConstante(Type * type)
{
    monType = type;
    monTypeSymbole = sy_constante;
}

SymboleConstante::~SymboleConstante()
{
}

Type* SymboleConstante::get_type()
{
    return monType;
}


void SymboleConstante::afficher() const
{
    cout << "Ceci est un symbole constante : " << endl;
    monType->afficher();
}

int SymboleConstante::getValInt()
{
    return valInt;
}


double SymboleConstante::getValReel()
{
    return valReel;
}


bool SymboleConstante::getValBool()
{
    return valBool;
}

string* SymboleConstante::getValChaine()
{
    return valChaine;
}

void SymboleConstante::setValInt(int val)
{
    valInt = val;
}


void SymboleConstante::setValReel(double val)
{
    valReel = val;
}


void SymboleConstante::setValBool(bool val)
{
    valBool = val;
}

void SymboleConstante::setValChaine(string* val)
{
    valChaine = val;
}
