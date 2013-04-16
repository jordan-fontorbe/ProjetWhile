/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef INSTRUCTION_HPP
#   define INSTRUCTION_HPP


#include <string>

#include "Code3ad.hpp"
#include "operande.hpp"
#include "tab_ids.hpp"


using namespace std;



/**
 * Une instruction du code trois adresses.
 */
class Instruction
{
    /** Le type d'instruction. */
    CodeInstruction typeIns;

    /** Opeerandes. NULL si non utilises
     * (les operations ont de 0 a 3 operandes). */
    Operande* x;
    Operande* y;
    Operande* z;

    /** Etiquette (label) pour les sauts. Chaine vide si
     * aucune etiquette n'est presente pour cette instruction. */
    string etiquette;

public:
    Instruction(CodeInstruction typeInsInit);
    Instruction(CodeInstruction typeInsInit,
                Operande* xInit);
    Instruction(CodeInstruction typeInsInit,
                Operande* xInit,
                Operande* yInit);
    Instruction(CodeInstruction typeInsInit,
                Operande* xInit,
                Operande* yInit,
                Operande* zInit);

    Operande* getX() { return x; }
    Operande* getY() { return y; }
    Operande* getZ() { return z; }
    
    void setX(Operande* nouvOp) { x = nouvOp; }
    void setY(Operande* nouvOp) { y = nouvOp; }
    void setZ(Operande* nouvOp) { z = nouvOp; }

    /** @return La chaine contenant l'instruction en code trois adresses.
     * Exemple : "x := y + y".
     * @warning La chaine retournee ne contiendra pas l'eventuelle etiquette
     * associee a l'instruction. */
    string getStr(TabIds* tab_ident);

    /** Rappel : Vide si pas d'etiquette. On peut donc eventuellement faire
     * un affichage de getEtiquette() pour chaque instruction. */
    string getEtiquette() { return etiquette; }
    void setEtiquette(string str) { etiquette = str; }
};


#endif /* INSTRUCTION_HPP */
