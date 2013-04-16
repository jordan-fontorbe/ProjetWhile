#include <iostream>
#include "type_interval.hpp"
#include "type.hpp"

TypeInterval::TypeInterval()
{
    monType = intervalle;
}

TypeInterval::TypeInterval(Type* debutT, Type* finT, string d, string f)
{
    monType = intervalle;
    debutType = debutT;
    finType = finT;
    debut = d;
    fin = f;
}

bool TypeInterval::operator== (Type& typeA)
{
    return (getType() == typeA.getType() );
}

TypeInterval::~TypeInterval()
{

}

void TypeInterval::afficher() const
{
    cout << "type : interval de " << debut << " à " << fin << endl;
}

bool TypeInterval::estDeType(typeVariable type)
{
    return getType() == type;
}

string TypeInterval::getStr()
{
	return "type : intervalle de " + debut + " à " + fin;
}
