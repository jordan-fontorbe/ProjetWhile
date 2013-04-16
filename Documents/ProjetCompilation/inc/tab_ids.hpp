/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef TAB_IDS_HPP
#   define TAB_IDS_HPP


#include <string>
#include <map>

using namespace std;


class TabIds
{
	map<string, int> tab_hach;

	public:
		~TabIds();
        /* Ajoute un element dans la table si il n'y est pas deja et
         * renvoie l'identifiant qui lui avait ou a ete affecte. */
		int inserer(string str);

        /* Renvoie l'id d'un element a partir de son nom.
         * Renvoie -1 si l'element est introuvable.*/
		int get_id(string str);

	    /* Renvoie le nom de l'identificateur dont
	     * le numero est passe en parametre. Si le numero est introuvable,
         * une chaine vide est renvoyee. */
		string get_nom(int id);

	    /*
	     *Affiche sur la sortie standard sous la forme de couple comme voulu par l'enonce.
	     */
		void afficher();

		void afficher_debug();
};


#endif /* TAB_IDS_HPP */
