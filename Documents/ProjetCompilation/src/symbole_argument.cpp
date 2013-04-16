#include "symbole_argument.hpp"
#include <iostream>
using namespace std;

SymboleArgument::SymboleArgument()
{
    maPosition = 0;
    monType = NULL;
    monTypeSymbole = sy_argument;
    constant = true;
}

SymboleArgument::SymboleArgument(Type * type, const int & position, bool constant, int id)
{
    maPosition = position;
    monType = type;
    monTypeSymbole = sy_argument;
    this->constant = constant;
    monId = id;
}

SymboleArgument::~SymboleArgument()
{

}

void SymboleArgument::afficher() const
{
    cout << "Ceci est un symbole argument. Position :" << maPosition
        << " Type passage :" << (constant ? "constant" : "par adresse") << endl;
    monType->afficher();
}
