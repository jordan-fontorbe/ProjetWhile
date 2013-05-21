#include "TableSymboles.hpp"

using namespace std;

TableSymboles::TableSymboles()
{
}

TableSymboles::~TableSymboles()
{
}

void TableSymboles::push(map<int, string> m)
{
  table.push(m);
}

void TableSymboles::pop()
{
  table.pop();
}

void TableSymboles::ajouterSymbole(int id, string t)
{
  table.top()[id] = t;
}
