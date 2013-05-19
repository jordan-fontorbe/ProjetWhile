#ifndef OPERANDE_HPP
#define	OPERANDE_HPP

#include "Valeur.hpp"

class Operande {
public:
    Operande(int identificateur);
    Operande(Valeur* valeur);
    Operande(Operande& orig);
    virtual ~Operande();
private:
    bool OperandeEstValeur;
    union {
        Valeur* valeur;
        int identificateur;
    };
};

#endif	/* OPERANDE_HPP */
