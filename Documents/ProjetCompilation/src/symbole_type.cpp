#include "symbole_type.hpp"
#include <iostream>
using namespace std;


void SymboleType::afficher() const
{
    cout << "Ceci est un symbole type : " << endl;
    monType->afficher();
}


SymboleType::SymboleType()
{
    monType = NULL;
    monTypeSymbole = sy_type;
}


SymboleType::SymboleType(Type * type)
{
    monType = type;
    monTypeSymbole = sy_type;
}


SymboleType::~SymboleType()
{

}
