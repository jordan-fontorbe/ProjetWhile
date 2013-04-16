#include <stdlib.h>

#include "operande.hpp"


Operande::Operande(int _idVar)
{
    idVar = _idVar;
}


Operande::Operande(typeVariable _typeVal)
{
    typeVal = _typeVal;
    idVar = -1;
}


Operande::Operande(string * _valStr)
{
	valStr = _valStr;
	idVar = -1;
	typeVal = chaine;
}
