#include <iostream>
#include <vector>

#include "type_enum.hpp"

using namespace std;

TypeEnum::TypeEnum(vector<string>* v)
{
    monType = enumeration;
    list = v;
}

bool TypeEnum::operator== (Type& typeA)
{
    return (getType() == typeA.getType() );
}

TypeEnum::~TypeEnum()
{

}

void TypeEnum::afficher() const
{
    cout << "type enumere : (";
}

bool TypeEnum::estDeType(typeVariable type)
{
    return getType() == type;
}

vector<string>* TypeEnum::getList()
{
    return list;
}

string TypeEnum::getStr()
{
    unsigned int i;
    string res;
    for(i = 0; i < list->size() - 1; i++)
    {
        res += (*list)[i] + ", ";
    }
    return "enumeration : (" + res + list->back() + ")";
}
