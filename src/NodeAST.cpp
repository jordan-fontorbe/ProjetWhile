#include "NodeAST.hpp"

using namespace std;

NodeAST::NodeAST(string lexemName)
{
  lexem = lexemName;
  this->entry = -1;
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
	string info = this->lexem;
	if (this->entry > -1)
	{
		ostringstream oss;
		oss << this->entry;
		info += "\\n entry : " + oss.str(); 
	}
	if (this->type.length() > 0)
	{
		info += "\\n type : " + this->type;
	}
	return info;
}

int NodeAST::getNbChildren()
{
	return this->children.size();
}

NodeAST* NodeAST::getChild(int i)
{
	return this->children[i];
}

void NodeAST::addEntry(int e)
{
	this->entry = e;
}

void NodeAST::addType(string t)
{
	this->type = t;
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
