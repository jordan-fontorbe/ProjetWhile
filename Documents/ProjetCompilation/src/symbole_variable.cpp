#include "symbole_variable.hpp"
#include <iostream>
using namespace std;


void SymboleVariable::afficher() const
{
    cout << "Ceci est un symbole variable : " << endl;
    monType->afficher();
}


SymboleVariable::SymboleVariable()
{
    monType = NULL;
    monTypeSymbole = sy_variable;
}


SymboleVariable::SymboleVariable(Type * type)
{
    monType = type;
    monTypeSymbole = sy_variable;
}


SymboleVariable::~SymboleVariable()
{

}
