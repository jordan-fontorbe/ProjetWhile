#include <stdlib.h>
#include <iostream>

#include "symbole_fonction.hpp"


void SymboleFonction::afficher() const
{
    cout << "Ceci est un symbole fonction." << endl;
}


SymboleFonction::SymboleFonction()
{
    monTypeSymbole = sy_fonction;
}


SymboleFonction::~SymboleFonction()
{

}

void SymboleFonction::setTs (TabSymboles * table)
{
   ts = table;
}

Type * SymboleFonction::getRetour()
{
   return retour;
}

void SymboleFonction::setRetour(Type * r)
{
   retour = r;
}

int SymboleFonction::getArite()
{
   return arite;
}

void SymboleFonction::setArite (int a)
{
   arite = a;
}
