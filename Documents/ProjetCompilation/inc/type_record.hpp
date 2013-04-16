/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/

#ifndef TYPE_RECORD_HPP
#   define TYPE_RECORD_HPP


#include "type.hpp"
#include "tuple_record.hpp"

using namespace std;



class TypeRecord : public Type
{
    private:
    vector<TupleRecord>* vect;

    public:

	TypeRecord(vector<TupleRecord>* v);

        virtual ~TypeRecord();

        virtual bool operator== (Type& typeA) { return getType() == typeA.getType(); }

        virtual void afficher() const;

        virtual bool estDeType(typeVariable type) { return getType() == type; }

        vector<TupleRecord>* getVect() { return vect; }

        virtual string getStr();
};

#endif /* TYPE_RECORD_HPP */
