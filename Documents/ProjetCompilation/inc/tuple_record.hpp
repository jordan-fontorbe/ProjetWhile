/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef TUPLE_RECORD_HPP
#   define TUPLE_RECORD_HPP

#include <string>
#include <vector>

#include "type.hpp"

using namespace std;

class TupleRecord
{
    protected:
    	vector<string>* list;
    	Type * type;

    public:
        TupleRecord(vector<string>* l, Type * t) { type = t; list = l; }
        Type* getType() { return type; }
        vector<string>* getList() { return list; }
        bool operator== (TupleRecord t) { return (type == t.getType() && list == t.getList()); }
};

#endif /* TUPLE_RECORD */
