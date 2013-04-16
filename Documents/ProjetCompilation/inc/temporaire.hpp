/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef TEMPORAIRE_H
#   define TEMPORAIRE_H


#include <string>

#include "tab_ids.hpp"


using namespace std;


/** Obtient le nom du symbole temporaire suivant et incremente
 * le nombre de symboles temporaires crees (nbTempCrees).
 * @param tids Une table d'identificateurs, pour eviter les doublons. */
string* getNomTempSuivant(TabIds* tIds);


#endif /* TEMPORAIRE_H */
