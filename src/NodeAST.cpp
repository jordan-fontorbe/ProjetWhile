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

string NodeAST::getType()
{
	return this->type;
}

bool NodeAST::checkType()
{
	bool res = true;
	if (this->getType() == "")
	{
		string tmpType = "";
		for (int i = 0; i < this->getNbChildren(); i++)
		{
			NodeAST* fils = this->getChild(i);
			if (fils->getType() == "")
				res = fils->checkType();
				
			if (res == false)
				break;
				
			if (tmpType == "")
				tmpType = fils->getType();
			else
			{
				if (tmpType != fils->getType())
				{
					res = false;
					break;
				}
			}
		}
		if (res == true)
		{
			this->addType(tmpType);
		}
	}
	else
	{
		res = true;
	}
	
	return res;
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
