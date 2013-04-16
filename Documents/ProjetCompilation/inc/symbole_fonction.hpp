/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef SYMBOLE_FONCTION
#   define SYMBOLE_FONCTION


#include "symbole.hpp"
#include "tab_symboles.hpp"


using namespace std;


/**
 * Une fonction est definie par :
 * - son arite (nb args) : entier positif ou nul
 * - son type de retour (obligatoire car "procedure" est un autre type)
 * - son code trois adresses
 * - l'adresse de sa table des symboles
 */
class SymboleFonction : public Symbole
{
    int arite;
    Type* retour;
    /* TO DO / a faire : code3@ */
    TabSymboles* ts;

public:
    SymboleFonction();

    virtual ~SymboleFonction();

    virtual void afficher() const;

    void setTs (TabSymboles * table);

    TabSymboles* getTs() { return ts; }

    Type* getRetour();

    void setRetour(Type * r);

    int getArite();

    void setArite(int a);
};



#endif /* SYMBOLE_FONCTION */
