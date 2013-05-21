#include "GeneratorDOTFile.hpp"

using namespace std;


GeneratorDotFile::GeneratorDotFile(NodeAST * node)
{
	this->root = node;
}

GeneratorDotFile::~GeneratorDotFile()
{
}

void GeneratorDotFile::GenerateDotFile(const char* path)
{
	int i = 1;
	string res = "graph AST {\n";
	res += GenerateDotFileAux(this->root, i);
	res += "}\n";
	ofstream myfile (path);
	if (myfile.is_open())
	{
		myfile << res;
		myfile.close();
	}
	else cout << "Unable to open file";
}

string GeneratorDotFile::GenerateDotFileAux(NodeAST *myNode, int &i)
{
	if (myNode != NULL)
	{
	ostringstream oss;
	oss << i;
	string res = "Node" + oss.str() + " [label=\"" + myNode->getInfo() + "\"] ;\n";
	if (myNode->getNbChildren() > 0)
	{
		for (int j = 0; j < myNode->getNbChildren(); j++)
		{
			res += "Node" + oss.str() + " -- ";
			i++;
			ostringstream oss2;
			oss2 << i;
			res += "Node" + oss2.str() + " ;\n";
			res += GenerateDotFileAux(myNode->getChild(j), i);
		}
	}
	
	return res;
	}
	else
	{
		return "";
	}
}
