/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef TUPLE_INTERVAL_HPP
#   define TUPLE_INTERVAL_HPP

#include <string>

#include "type.hpp"

using namespace std;

class TupleInterval
{
    protected:
    	string nom;
    	Type * t;
    	int val;
    	bool estVar;

    public:
        TupleInterval(Type * type, string nomDonne, int v, bool estV) { t = type; nom = nomDonne; val = v; estVar = estV; }
        Type* getType() { return t; }
        string getNom() { return nom; }
        int getVal() { return val; }
        void setVal(int v) { val = v; }
        bool getEstVar() { return estVar; }
};

#endif /* TUPLE_ARRAY */
