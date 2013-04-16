/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef TYPE_ENUM_HPP
#   define TYPE_ENUM_HPP


#include "type.hpp"
#include <vector>

using namespace std;

class TypeEnum : public Type
{

    vector<string>* list;

    public:
        TypeEnum(vector<string>* v);

        virtual ~TypeEnum();

        virtual bool operator== (Type& typeA);

        virtual void afficher() const;

        virtual bool estDeType(typeVariable type);

        vector<string>* getList();

        string getStr();
};

#endif /* TYPE_ENUM_HPP */
