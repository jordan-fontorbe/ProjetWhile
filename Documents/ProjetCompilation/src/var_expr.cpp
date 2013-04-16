#include <stdlib.h>

#include "var_expr.hpp"


VarExpr::VarExpr(int _id, typeVarExpr _type)
{
    id = _id;
    monTypeVarExpr = _type;
}


VarExpr::~VarExpr() {}
