#include <stdlib.h>
#include <iostream>

#include "symbole_procedure.hpp"


using namespace std;


void SymboleProcedure::afficher() const
{
    cout << "Ceci est un symbole procedure." << endl;
}


SymboleProcedure::SymboleProcedure()
{
    monTypeSymbole = sy_procedure;
}


SymboleProcedure::~SymboleProcedure()
{

}

void SymboleProcedure::setTs (TabSymboles * table)
{
   ts = table;
}

int SymboleProcedure::getArite()
{
   return arite;
}

void SymboleProcedure::setArite (int a)
{
   arite = a;
}
