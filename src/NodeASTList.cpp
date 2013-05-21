#include "NodeASTList.hpp"

using namespace std;

NodeASTList::NodeASTList()
{
}

NodeASTList::~NodeASTList()
{
}

void NodeASTList::addNode(NodeAST* newNode)
{
  this->list.push_back(newNode);
}

NodeAST* NodeASTList::get(int i)
{
	return this->list[i];
}

unsigned int NodeASTList::size()
{
	return this->list.size();
}
