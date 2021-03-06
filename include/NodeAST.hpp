#ifndef NODEAST_HPP
#define NODEAST_HPP

#include<string>
#include<vector>
#include<iostream>
#include<sstream>


class NodeAST
{
public:
  NodeAST(std::string);
  NodeAST();
  NodeAST(const NodeAST&);
  ~NodeAST();

  void addChild(NodeAST*);
  std::string getLexem();
  std::string getInfo();
  std::string show();
  int getNbChildren();
  NodeAST* getChild(int);
  void addEntry(int);
  void addType(std::string);
 
private:
  
 std::vector<NodeAST*> children;
 std::string lexem;
 int entry;
 std::string type;
};

#endif //NODEAST_HPP
