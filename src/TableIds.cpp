#include "TableIds.hpp"

using namespace std;

TableIds::TableIds()
{
}
TableIds::~TableIds()
{
}

int TableIds::ajouter(char* str)
{
  int id = getId(str);
  if (id == -1)
    {
      int size = table.size();
      table[size] = str;
      return size;
    }
  else
    {
      return id;
    }
}
int TableIds::getId(std::string str)
{
  std::map<int, std::string>::iterator it;
  for (it = table.begin(); it != table.end(); it++)
    {
      if (str == it->second) 
	{
	  return it->first;
	}
    }
  return -1;
}
