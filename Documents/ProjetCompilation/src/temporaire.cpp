#include <stdlib.h>
#include <iomanip>
#include <locale>
#include <sstream>

#include "temporaire.hpp"


using namespace std;




string intToStrTemp(const int n)
{
    string res;

    ostringstream convertisseur;

    convertisseur << n;

    res = convertisseur.str();

    return res;
}



string* getNomTempSuivant(TabIds* tIds)
{
    string* res;
    int numEssai = 0;

    res = new string;

    *res = "_t";

    if(tIds->get_id(*res) < 0)
        return res;

    /* Nom deja pris ! */
    do
    {
        numEssai++;
        *res = "_t" + intToStrTemp(numEssai);
    } while(tIds->get_id(*res) >= 0);

    return res;
}
