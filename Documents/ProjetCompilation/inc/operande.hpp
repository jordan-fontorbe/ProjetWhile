#ifndef OPERANDE_HPP
#   define OPERANDE_HPP
/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#include <string>

#include "type.hpp"


using namespace std;


/**
 * Un operande d'une instruction en code trois adresses.
 * Voir la classe Instruction dans instruction.hpp. */
class Operande
{
    /** Id de l'operande dans la table des identificateurs.
     * A utiliser si l'operande est un symbole et non une valeur calculee.
     * -1 sinon. */
    int idVar;

    /** A utiliser si et seulement si la valeur de l'operande est calculee. */
    typeVariable typeVal;
    union
    {
        int valInt;
        double valReel;
        bool valBool;
        string * valStr;
    };

public:
    /** Constructeur pour operateur non calcule. */
    Operande(int _idVar);
    /** Constructeur pour operateur dont la valeur a ete calculee. */
    Operande(typeVariable _typeVal);
    
    Operande(string * _valStr);

    /** Mutateurs pour mettre la valeur a jour.
     * A utiliser imperativement pour les operandes dont la valeur
     * a ete calculee car le constructeur ne peut pas le faire ! */
    void setValInt(int val) { valInt = val; }
    void setValReel(double val) { valReel = val; }
    void setValBool(bool val) { valBool = val; }
    /** Les accesseurs qui vont avec. */
    int getValInt() { return valInt; }
    double getValReel() { return valReel; }
    bool getValBool() { return valBool; }
    string * getValStr() { return valStr; }

    typeVariable getType() { return typeVal; }
    int getIdVar() { return idVar; }
    void setIdVar( int id ){ idVar = id;  }
};


#endif /* OPERANDE_HPP */
