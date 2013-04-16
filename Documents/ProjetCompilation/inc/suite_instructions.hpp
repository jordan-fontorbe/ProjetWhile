/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef SUITE_INSTRUCTIONS_HPP
#   define SUITE_INSTRUCTIONS_HPP


#include <vector>

#include "instruction.hpp"
#include "tab_ids.hpp"


using namespace std;


/**
 * Une instruction du code trois adresses.
 */
class SuiteIns
{
    /** Succession d'instructions, dans l'ordre d'execution. */
    vector<Instruction*> tabIns;

    /** Numero, dans la table des identificateurs, de la variable
     * contenant le resultat de la succession d'instruction. */
    int idRes;

public:
    SuiteIns();
    ~SuiteIns();

    void add(Instruction* nouvIns) { tabIns.push_back(nouvIns); }
    void add(SuiteIns* suiteNouvIns)
    {
        tabIns.insert(
                tabIns.end(),
                suiteNouvIns->getTabIns()->begin(),
                suiteNouvIns->getTabIns()->end());
    }

    /** Ajoute une instruction en premiere position de la suite d'instructions.
     * Les instructions suivantes seront décalées. */
    void addDebut(Instruction* nouvIns) { tabIns.insert(tabIns.begin(), nouvIns); }

    vector<Instruction*>* getTabIns() { return &tabIns; }

    void setIdRes(int id) { idRes = id; }
    int getIdRes() { return idRes; }

    string getStr(TabIds* tab_ident);
    
    /** Vrai si et seulement si aucune instruction
     * dans la suite d'instructions. */
    bool empty() { return tabIns.empty(); }
    
    /** Renvoie la premiere instruction si la suite d'instructions n'est pas
     * vide, renvoie NULL sinon. */
    Instruction* getPremiere() { return tabIns.empty() ? NULL : tabIns[0]; }
};


#endif /* SUITE_INSTRUCTIONS_HPP */
