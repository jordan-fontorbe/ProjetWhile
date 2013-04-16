#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <string>

#include "symbole.hpp"
#include "tab_symboles.hpp"
#include "symbole_type.hpp"
#include "symbole_programme.hpp"
#include "symbole_fonction.hpp"
#include "symbole_procedure.hpp"
#include "symbole_variable.hpp"
#include "symbole_constante.hpp"
#include "symbole_argument.hpp"


using namespace std;


TabSymboles::TabSymboles(TabSymboles* tableMereInit, int _idEntite)
{
    tableMere = tableMereInit;
    idEntite = _idEntite;
}


int TabSymboles::add(int id, Symbole* symb)
{
    tupleTabSymboles nouveau;

    if(getParId(id) == NULL)
    {
        nouveau.num = id;
        nouveau.symb = symb;
        tab.push_back(nouveau);

        return 0;
    }
    else
        return -1;
}

TabSymboles::~TabSymboles()
{
 	unsigned int i;
    /* File contenant les tables filles de la table. */
    queue<TabSymboles*> fileFilles;
    tupleTabSymboles* tup;
    typeSymbole typeSymb;

    for(i = 0;  i < tab.size();  i++)
    {
        tup = &(tab[i]);

        typeSymb = tup->symb->getTypeSymbole();
        if(typeSymb == sy_procedure)
            fileFilles.push(((SymboleProcedure*) tup->symb)->getTs());
        if(typeSymb == sy_fonction)
            fileFilles.push(((SymboleFonction*) tup->symb)->getTs());
    }

    while(! fileFilles.empty()) {
        delete fileFilles.front();
        fileFilles.pop();
    }
}

tupleTabSymboles* TabSymboles::get(int index)
{
    return &tab[index];
}


tupleTabSymboles* TabSymboles::getParId(int id)
{
    unsigned int i;

    for(i = 0;  i < tab.size();  i++)
        if(tab[i].num == id)
            return &tab[i];

    return NULL;
}


TabSymboles* TabSymboles::getMere()
{
    return tableMere;
}


/* PAS methode de la classe. */
void afficherCaracteristiquesSymbole(Symbole* symb)
{
    Type* typeSymb;
    SymboleArgument* symbArg;
    SymboleFonction* symbFonc;

    switch(symb->getTypeSymbole())
    {
        case sy_programme:
            break;
        case sy_argument:
            symbArg = (SymboleArgument*) symb;
            cout << '#' << symbArg->getPosition()
                    << ", " << (symbArg->estConstant() ? "const " : "var ")
                    << symbArg->getType()->getStr();
            break;
        case sy_variable:
            cout << ((SymboleVariable*) symb)->getType()->getStr();
            break;
        case sy_fonction:
            symbFonc = (SymboleFonction*) symb;
            cout << symbFonc->getRetour()->getStr() << ", " << symbFonc->getArite() << " arg(s)";
            break;
        case sy_procedure:
            cout << ((SymboleProcedure*) symb)->getArite() << " arg(s)";
            break;
        case sy_constante:
            typeSymb = ((SymboleConstante*) symb)->get_type();

            cout << typeSymb->getStr();

            if(typeSymb->estDeType(entier))
                cout << " : " << ((SymboleConstante*) symb)->getValInt();
            else if(typeSymb->estDeType(reel))
                cout << " : " << ((SymboleConstante*) symb)->getValReel();
            else if(typeSymb->estDeType(booleen))
                cout << " : " << (((SymboleConstante*) symb)->getValBool() ? "vrai" : "faux");
            else if(typeSymb->estDeType(chaine))
                cout << " : " << *((SymboleConstante*) symb)->getValChaine();
            break;
        case sy_type:
            cout << '\t' << ((SymboleType*) symb)->getType()->getStr();
            break;
        default:
            cout << "<non implemente>";
            break;
    }
}

Type * TabSymboles::getTypeParId(int id)
{
	Symbole * tmp = getSymboleParId(id);
	
	if(tmp == NULL)
	{	
		if(this->getMere() != NULL)
		{
			return this->getMere()->getTypeParId(id);
		}
	}
	
	switch(tmp->getTypeSymbole())
	{
		 case sy_constante:
		 	return ((SymboleConstante*) tmp)->get_type();
			break;
		
		case sy_variable :
			return ((SymboleVariable*) tmp)->getType();
			break;
		
		case sy_argument :
			return ((SymboleArgument*) tmp)->getType();
			break;
		
		case sy_type : 
			return ((SymboleType*) tmp)->getType();
			break;
	
		default :
			return NULL;
			break;
	}
}

Symbole * TabSymboles::getSymboleParId(int id)
{
	tupleTabSymboles * t = getParId(id);
	if(t == NULL)
	{
		if(this->getMere() != NULL)
			return this->getMere()->getSymboleParId(id);
		else
			return NULL;
	}
	else
		return t->symb;
		
	return NULL;
}

void TabSymboles::afficher(TabIds* tableIds)
{
    unsigned int i;
    /* File contenant les tables filles de la table. */
    queue<TabSymboles*> fileFilles;
    tupleTabSymboles* tup;
    typeSymbole typeSymb;

    cout << "** Table des symboles (";
    if(idEntite >= 0) {
        /* Nom du contexte */
        cout << tableIds->get_nom(idEntite);

        /* Nom du contexte pere */
        if(getMere() != NULL && getMere()->getIdEntite() >= 0)
            cout << ", " << tableIds->get_nom(getMere()->getIdEntite());
    }
    cout << ")" << endl;

    for(i = 0;  i < tab.size();  i++)
    {
        tup = &(tab[i]);

        typeSymb = tup->symb->getTypeSymbole();
        if(typeSymb == sy_procedure)
            fileFilles.push(((SymboleProcedure*) tup->symb)->getTs());
        if(typeSymb == sy_fonction)
            fileFilles.push(((SymboleFonction*) tup->symb)->getTs());

        cout << tup->num << '\t' << tup->symb->getStr() << '\t';

        afficherCaracteristiquesSymbole(tup->symb);

        putchar('\n');
    }

    putchar('\n');

    while(! fileFilles.empty()) {
        fileFilles.front()->afficher(tableIds);
        fileFilles.pop();
    }
}

