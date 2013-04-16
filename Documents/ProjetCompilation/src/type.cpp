#include "type.hpp"

Type::Type()
{

}


Type::~Type()
{

}


string Type::getStr()
{
    switch(monType)
    {
        case entier:
            return "entier";
            break;
        case reel:
            return "reel";
            break;
        case booleen:
            return "booleen";
            break;
        case caractere:
            return "caractere";
            break;
        case chaine:
            return "chaine";
            break;
        case tableau:
            return "tableau";
            break;
        case pointeur:
            return "pointeur";
            break;
        case structure:
            return "structure";
            break;
        case intervalle:
            return "intervalle";
            break;
        case enumeration:
            return "enumeration";
            break;
        default:
            return "type inconnu";
            break;
    }
}
