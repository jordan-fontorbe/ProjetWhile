#include "NodeAST.hpp"

using namespace std;

NodeAST::NodeAST(string lexemName)
{
  lexem = lexemName;
}

NodeAST::NodeAST()
{
}

NodeAST::NodeAST(const NodeAST& orig)
{
}

NodeAST::~NodeAST()
{
}

void NodeAST::addChild(NodeAST* child)
{
  this->children.push_back(child);
}

string NodeAST::getLexem()
{
	return this->lexem;
}

string NodeAST::getInfo()
{
	return this->lexem;
}

int NodeAST::getNbChildren()
{
	return this->children.size();
}

NodeAST* NodeAST::getChild(int i)
{
	return this->children[i];
}

string NodeAST::show()
{
	string res = this->lexem;
	for (unsigned int i = 0; i < this->children.size(); i++)
	{
		res += this->children[i]->show();
	}
	return res;
}
