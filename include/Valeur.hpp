#ifndef VALEUR_HPP
#define	VALEUR_HPP

#define TYPE_INTEGER 0
#define TYPE_DECIMAL 1

class Valeur {
public:
    Valeur();
    Valeur(int valeur);
    Valeur(float valeur);
    virtual ~Valeur();
private:
    int type;
    union {
        int integerValeur;
        float decimalValeur;
    };
};

#endif	/* VALEUR_HPP */
