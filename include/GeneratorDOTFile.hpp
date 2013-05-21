#ifndef GENERATORDOTFILE_HPP
#define GENERATORDOTFILE_HPP

#include "NodeAST.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>


class GeneratorDotFile
{
public:
  GeneratorDotFile(NodeAST *);
  ~GeneratorDotFile();

  void GenerateDotFile(const char*);
  std::string GenerateDotFileAux(NodeAST* , int &i);
 
private:
  
	NodeAST *root;
};

#endif //GENERATORDOTFILE_HPP
