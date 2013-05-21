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

string TableSymboles::getType(int id)
{
	stack<map<int,string> > st(table);
	while(!st.empty()) 
	{
		string s = st.top()[id];
		if(s.length() > 0)
			return s;
		st.pop();
	}
	return "";
}
