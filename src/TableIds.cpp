#include "TableIds.hpp"
#include <iostream>
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

int TableIds::potentialId(std::string str)
{
	int res = getId(str);
	if (res == -1)
		res = this->table.size();
	
	return res;
}

std::string TableIds::getNom(int id)
{
	std::map<int, std::string>::iterator it;
	  for (it = table.begin(); it != table.end(); it++)
    {
      if (id == it->first) 
	{
	  return it->second;
	}
    }
  return "";
}
