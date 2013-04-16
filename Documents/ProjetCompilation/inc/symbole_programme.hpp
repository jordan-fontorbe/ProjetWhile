/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef SYMBOLE_PROGRAMME_HPP
#   define SYMBOLE_PROGRAMME_HPP


#include "symbole.hpp"
#include "tab_symboles.hpp"


using namespace std;


/**
 * Un programme est defini par rien.
 */
class SymboleProgramme : public Symbole
{

public:
    SymboleProgramme();

    virtual ~SymboleProgramme();

    virtual void afficher() const;
};


#endif
