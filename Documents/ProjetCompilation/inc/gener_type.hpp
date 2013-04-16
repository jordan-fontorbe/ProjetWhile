#ifndef GENER_TYPE_HPP
#   define GENER_TYPE_HPP

/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/

#include <vector>
#include <stdlib.h>

#include "type.hpp"
#include "type_reel.hpp"
#include "type_entier.hpp"
#include "type_booleen.hpp"
#include "type_char.hpp"
#include "type_tab.hpp"
#include "type_pointeur.hpp"
#include "type_chaine.hpp"
#include "type_interval.hpp"
#include "type_enum.hpp"
#include "type_record.hpp"

#include "tuple_record.hpp"


using namespace std;


class GenerType
{
    private:
        /* Nb de types crees par l'utilisateur. */
        int nb_types_crees;
        vector<Type*> tab_types;

    public:
        void init_nb_type_crees() { nb_types_crees = 0; }

        /* Renvoie l'adresse d'un descripteur de type entier. Si un tel type
         * avait deja ete genere, il est simplement recupere dans tab_types.
         * Sinon, on en cree un nouveau (et on la repertorie dans
         * tab_types). */
        TypeEntier* creerTypeEntier();
        /* Idem pour caracteres. */
        TypeCaractere* creerTypeCaractere();
        /* Idem pour reels. */
        TypeReel* creerTypeReel();
        /* Idem pour booleens. */
        TypeBooleen* creerTypeBooleen();
        /* Idem pour chaines de caracteres. */
        TypeChaine* creerTypeChaine();
        /* Idem pour pointeurs. Notez qu'un pointeur sur un type A sera
         * considere comme un autre type qu'une pointeur sur un type B. */
        TypePointeur* creerTypePointeur(Type* pointeSur);
        /* Idem pour les intervalles */
        TypeInterval* creerTypeInterval(Type* debutType, Type* finType, string debut, string fin);
        /* Idem pour les enum */
        TypeEnum* creerTypeEnum(vector<string>* v);
        /* Idemn pour les structures */
        TypeRecord* creerTypeRecord(vector<TupleRecord>* v);


	TypeTab * creerTypeTab(Type * contenu, Type * range, int taille);
	/*
	* Verifie recursivement le contenu au bout de 2 pointeurs et retourne
	* vrai si ils sont équivalents
	* faux sinon
	*/
	bool verifierTypePointeurExiste(TypePointeur* t1, TypePointeur* t2);

        /* Renvoie l'adresse du descripteur du type recherche si il est
         * present dans tab_types, renvoie NULL sinon.
         *
         * Arg surOuDe : Par exemple, si on recherche un pointeur sur
         * entier, passer l'adresse du type Entier (le recuperer si
         * besoin avec un autre appel a getTypeSiExiste) via ce parametre.
         * Meme fonctionnement pour les tableaux. */
        Type* getTypeSiExiste(typeVariable type, Type* sur = NULL, Type* de = NULL, int taille = 0);
        Type* getTypeSiExiste(typeVariable type, vector<string>* v);
        Type* getTypeSiExiste(typeVariable type, vector<TupleRecord>* v);
        int getNbTypes() { return tab_types.size(); }
};


#endif /* GENER_TYPE_HPP */
