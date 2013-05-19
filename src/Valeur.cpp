#include "Valeur.hpp"

Valeur::Valeur() {
}

Valeur::Valeur(int valeur)
{
    integerValeur = valeur;
    type = TYPE_INTEGER;
}

Valeur::Valeur(float valeur)
{
    decimalValeur = valeur;
	type = TYPE_DECIMAL;
}

Valeur::~Valeur() {
}
