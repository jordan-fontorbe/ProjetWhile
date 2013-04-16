/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef SYMBOLE_HPP
#   define SYMBOLE_HPP


#include <string>


#include "type.hpp"


using namespace std;


enum typeSymbole
{
    sy_programme,
    sy_argument,
    sy_variable,
    sy_fonction,
    sy_procedure,
    sy_constante,
    sy_type
};


class Symbole
{
    protected:
        typeSymbole monTypeSymbole;

    public:
        Symbole();

        virtual ~Symbole();

        virtual void afficher() const = 0;

        typeSymbole getTypeSymbole() { return monTypeSymbole; }

        string getStr();
};

#endif
