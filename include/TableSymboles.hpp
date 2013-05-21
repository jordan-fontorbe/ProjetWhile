#ifndef TABLESYMBOLES_HPP
#define TABLESYMBOLES_HPP

#include <stack>
#include <map>
#include <string>



class TableSymboles
{
public:
  TableSymboles();
  ~TableSymboles();
  
  void push(std::map<int, std::string>);
  void pop();
  void ajouterSymbole(int, std::string);

private:
  std::stack<std::map<int, std::string> > table;
};

#endif //TABLESYMBOLES_HPP
