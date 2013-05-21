#ifndef NODEASTLIST_HPP
#define NODEASTLIST_HPP

#include<string>
#include<vector>
#include<iostream>
#include "NodeAST.hpp"


class NodeASTList
{
public:
  NodeASTList();
  ~NodeASTList();

  void addNode(NodeAST*);
  NodeAST* get(int);
  unsigned int size();
 
private:
  
	std::vector<NodeAST*> list;
};

#endif //NODEAST_HPP
