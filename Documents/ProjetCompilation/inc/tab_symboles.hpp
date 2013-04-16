/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef TAB_SYMBOLES_HPP
#   define TAB_SYMBOLES_HPP


#include <vector>

#include "symbole.hpp"
#include "tab_ids.hpp"


using namespace std;


/**
 * Un tuple d'une table des symboles.
 */
typedef struct
{
    /** Numero du symbole dans la table des identificateurs. */
    int num;
    /** Type et proprietes du symbole. */
    Symbole* symb;
} tupleTabSymboles;


class TabSymboles
{
    /* Id, dans la table des identificateurs, du programme ou de la fonction
     * ou de la procedure auquel cette table des symboles appartient. */
    int idEntite;

    vector<tupleTabSymboles> tab;
    TabSymboles* tableMere;

    public:
        /**
         * Passer NULL en premier parametre si la table n'a pas
         * de mere (typiquement, pour le programme).
         * Dans ce cas, passer egalement -1 en premier parametre pour signaler que l'entite
         * dont cette table est la table n'est pas dans la table des ids.
         */
        TabSymboles(TabSymboles*, int _idEntite);
        
         ~TabSymboles();
        
        /** Ajout d'un tuple.
         * @return -1 si l'id est deja utilise dans cette table de symboles,
         * 0 si tout se passe bien. */
        int add(int id, Symbole* symb);
        /** Acces a un tuple par indice. */
        tupleTabSymboles* get(int index);
        /** Acces a un tuple par id du symbole.
         * @return NULL si l'id n'est pas present dans la table. */
        tupleTabSymboles* getParId(int id);
        
        /**
         * Renvoie un pointeur vers la table mere de cette table de symboles.
         * Renvoie null si la table n'a pas de mere. */
        TabSymboles* getMere();
        int getIdEntite() { return idEntite; }
        void setIdEntite(int _idEntite) { idEntite = _idEntite; }
        /** Affiche le contenu de la table des symboles, puis des tables filles
         * (tables de symboles des fonctions de la mere, etc). */
        void afficher(TabIds* tableIds);
        
        Type * getTypeParId(int id);
        
        Symbole * getSymboleParId(int id);
};



void afficherCaracteristiquesSymbole(Symbole* symb);



#endif /* TAB_SYMBOLES_HPP */
