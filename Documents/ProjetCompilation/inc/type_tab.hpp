/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef TYPE_TAB_HPP
#   define TYPE_TAB_HPP


#include "type.hpp"


using namespace std;



class TypeTab : public Type
{
    private:
	Type * contenuType;
	Type * rangeType;
	int taille;

    public:

	TypeTab(Type * contenu, Type * range, int t);

        virtual ~TypeTab();

        virtual bool operator== (Type& typeA);

        virtual void afficher() const;

        virtual bool estDeType(typeVariable type) { return getType() == type; }

        virtual string getStr();

        Type * getContenuType() { return contenuType; }
        Type * getRangeType() { return rangeType; }
        int getTaille() { return taille; };
};

#endif /* TYPE_TAB_HPP */
