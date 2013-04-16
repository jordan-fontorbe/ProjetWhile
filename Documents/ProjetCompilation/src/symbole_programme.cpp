#include <stdlib.h>
#include <iostream>

#include "symbole_programme.hpp"


using namespace std;


void SymboleProgramme::afficher() const
{
    cout << "Ceci est un symbole programme." << endl;
}


SymboleProgramme::SymboleProgramme()
{
    monTypeSymbole = sy_programme;
}


SymboleProgramme::~SymboleProgramme()
{

}



