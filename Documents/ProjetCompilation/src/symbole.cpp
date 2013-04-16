#include "symbole.hpp"


Symbole::Symbole()
{

}


Symbole::~Symbole()
{

}


string Symbole::getStr()
{
    switch(monTypeSymbole)
    {
        case sy_programme:
            return "programme";
            break;
        case sy_argument:
            return "argument";
            break;
        case sy_variable:
            return "variable";
            break;
        case sy_fonction:
            return "fonction";
            break;
        case sy_procedure:
            return "procedure";
            break;
        case sy_constante:
            return "constante";
            break;
        case sy_type:
            return "type";
            break;
        default:
            return "";
            break;
    }
}

