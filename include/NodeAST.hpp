#ifndef NODEAST_HPP
#define NODEAST_HPP

#include<string>
#include<vector>
#include<iostream>


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
 
private:
  
 std::vector<NodeAST*> children;
 std::string lexem;
};

#endif //NODEAST_HPP
