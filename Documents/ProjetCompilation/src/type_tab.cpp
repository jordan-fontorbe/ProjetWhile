#include <iostream>
#include <sstream>
#include "type_tab.hpp"
#include "type.hpp"


TypeTab::TypeTab( Type * contenu, Type * range, int t)
{
    monType = tableau;
    contenuType = contenu;
    rangeType = range;
    taille = t;
}


bool TypeTab::operator== (Type& typeA)
{
    //TODO A completer en regardant le contenu du tableau

    if( getType() == typeA.getType() )
        {
            return((contenuType ==  ((TypeTab&)typeA).getContenuType()) && (rangeType ==  ((TypeTab&)typeA).getRangeType()));
        }
    return false;
}

TypeTab::~TypeTab()
{

}

void TypeTab::afficher() const
{
    cout << "tableau de [";  contenuType->afficher(); cout << "] of "; rangeType->afficher(); cout << endl;
}

string TypeTab::getStr() 
{
	string tailleStr = static_cast<ostringstream*>( &(ostringstream() << taille) )->str();
	return "tableau de " + this->getContenuType()->getStr() + " de " + tailleStr + " " + this->getRangeType()->getStr();
}
