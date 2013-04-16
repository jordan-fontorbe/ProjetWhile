/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef SYMBOLE_PROCEDURE_HPP
#   define SYMBOLE_PROCEDURE_HPP


#include "symbole.hpp"
#include "tab_symboles.hpp"


using namespace std;


/**
 * Une procedure est definie par :
 * - son arite (nb args) : entier positif ou nul
 * - son code trois adresses
 * - l'adresse de sa table des symboles
 */
class SymboleProcedure : public Symbole
{
    int arite;
    /* TO DO / a faire : code3@ */
    TabSymboles* ts;

public:
    SymboleProcedure();

    virtual ~SymboleProcedure();

    virtual void afficher() const;
    
    void setTs (TabSymboles * table);
    
    TabSymboles* getTs() { return ts; }
    
    int getArite();
    
    void setArite (int a);
};


#endif
