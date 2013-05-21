#ifndef TABLEIDS_HPP
#define TABLEIDS_HPP

#include <map>
#include <string>

class TableIds
{
private:
  std::map<int, std::string> table;

public:
  TableIds();
  ~TableIds();

  int ajouter(char* str);
  int getId(std::string str);
  
};

#endif //TABLEIDS_HPP
