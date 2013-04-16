#include <iostream>
#include <sstream>
#include "type_record.hpp"
#include "type.hpp"
#include "tuple_record.hpp"


TypeRecord::TypeRecord(vector<TupleRecord>* v)
{
    monType = structure;
    vect = v;
}

TypeRecord::~TypeRecord()
{

}

void TypeRecord::afficher() const
{
    cout << "structure";
}

string TypeRecord::getStr()
{
	string res;
	for (unsigned int i = 0; i < vect->size() - 1; i++)
	{
	    for (unsigned int j = 0; j < (*vect)[i].getList()->size(); j++)
        res += "[" + (*(*vect)[i].getList())[j] + ":" + (*vect)[i].getType()->getStr() + "], ";
	}
	for (unsigned int j = 0; j < vect->back().getList()->size() - 1; j++)
	{
        res += "[" + (*(vect->back()).getList())[j] + ":" + (vect->back()).getType()->getStr() + "], ";
	}
	string resf = "[" + (vect->back()).getList()->back() + ":" + (vect->back()).getType()->getStr() + "]";
	return "structure : {" + res + resf + "}";
}
