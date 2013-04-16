#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>

#include "instruction.hpp"



string intToStr(const int n)
{
    string res;

    ostringstream convertisseur;

    convertisseur << n;

    res = convertisseur.str();

    return res;
}


string reaToStr(const double r)
{
    string res;

    ostringstream convertisseur;

    convertisseur << r;

    res = convertisseur.str();

    return res;
}


string booToStr(const bool b)
{
    return b ? "true" : "false";
}



Instruction::Instruction(CodeInstruction typeInsInit)
{
    typeIns = typeInsInit;
    x = NULL;
    y = NULL;
    z = NULL;
}


Instruction::Instruction(CodeInstruction typeInsInit,
                         Operande* xInit)
{
    typeIns = typeInsInit;
    x = xInit;
    y = NULL;
    z = NULL;
}


Instruction::Instruction(CodeInstruction typeInsInit,
                         Operande* xInit,
                         Operande* yInit)
{
    typeIns = typeInsInit;
    x = xInit;
    y = yInit;
    z = NULL;
}


Instruction::Instruction(CodeInstruction typeInsInit,
                         Operande* xInit,
                         Operande* yInit,
                         Operande* zInit)
{
    typeIns = typeInsInit;
    x = xInit;
    y = yInit;
    z = zInit;
}

string Instruction::getStr(TabIds* tab_ident)
{
    string res;
    string nomX = "<Erreur>", nomY = "<Erreur>", nomZ = "<Erreur>";

    if(x != NULL)
    {
        if(x->getIdVar() >= 0)
            nomX = tab_ident->get_nom(x->getIdVar());
        else
        {
            switch(x->getType())
            {
                case entier:
                    nomX = intToStr(x->getValInt());
                    break;
                case reel:
                    nomX = reaToStr(x->getValReel());
                    break;
                case booleen:
                    nomX = booToStr(x->getValBool());
                    break;
                case chaine:
                	nomX = *(x->getValStr());
                	break;
                default:
                    break;
            }
        }
    }

    if(y != NULL)
    {
        if(y->getIdVar() >= 0)
            nomY = tab_ident->get_nom(y->getIdVar());
        else
        {
            switch(y->getType())
            {
                case entier:
                    nomY = intToStr(y->getValInt());
                    break;
                case reel:
                    nomY = reaToStr(y->getValReel());
                    break;
                case booleen:
                    nomY = booToStr(y->getValBool());
                    break;
                case chaine:
                	nomY = *(y->getValStr());
                	break;
                default:
                    break;
            }
        }
    }

    if(z != NULL)
    {
        if(z->getIdVar() >= 0)
            nomZ = tab_ident->get_nom(z->getIdVar());
        else
        {
            switch(z->getType())
            {
                case entier:
                    nomZ = intToStr(z->getValInt());
                    break;
                case reel:
                    nomZ = reaToStr(z->getValReel());
                    break;
                case booleen:
                    nomZ = booToStr(z->getValBool());
                    break;
                case chaine:
                	nomZ = *(z->getValStr());
                	break;
                default:
                    break;
            }
        }
    }


    switch(typeIns)
    {
        case OPCODE_NONE :
            res = "nop";
            break;

        case OPCODE_ADD :
            res = nomX + " := " + nomY + " + " + nomZ;
            break;

        case OPCODE_SUB :
            res = nomX + " := " + nomY + " - " + nomZ;
            break;

        case OPCODE_MUL :
            res = nomX + " := " + nomY + " * " + nomZ;
            break;

        case OPCODE_DIV :
            res = nomX + " := " + nomY + " / " + nomZ;
            break;

        case OPCODE_NEG :
            res = nomX + " := - " + nomY;
            break;

        case OPCODE_AND :
            res = nomX + " := " + nomY + " & " + nomZ;
            break;

        case OPCODE_OR :
            res = nomX + " := " + nomY + " | " + nomZ;
            break;

        case OPCODE_NOT :
            res = nomX + " :=  !" + nomY;
            break;

        case OPCODE_CPY :
            res = nomX + " := " + nomY;
            break;

        case OPCODE_LT :
            res = nomX + " := " + nomY + " < " + nomZ;
            break;

        case OPCODE_GT :
            res = nomX + " := " + nomY + " > " + nomZ;
            break;

        case OPCODE_LE :
            res = nomX + " := " + nomY + " <= " + nomZ;
            break;

        case OPCODE_GE :
            res = nomX + " := " + nomY + " >= " + nomZ;
            break;

        case OPCODE_EQ :
            res = nomX + " := " + nomY + " == " + nomZ;
            break;

        case OPCODE_NEQ :
            res = nomX + " := " + nomY + " != " + nomZ;
            break;

        case OPCODE_JMP :
            res = "aller a " + nomX;
            break;

        case OPCODE_JMPC :
            res = "si " + nomX + " aller a " + nomY;
            break;

        case OPCODE_ART :
            res = nomX + " := " + nomY + " [ " + nomZ + " ]";
            break;

        case OPCODE_ALT :
            res = nomX + " [ " + nomY + " ] := " + nomZ;
            break;

        case OPCODE_PTR :
            res = nomX + " := " + nomY;
            break;

        case OPCODE_RRT :
            res = nomX + " := * " + nomY;
            break;

        case OPCODE_RLT :
            res = "* " + nomX + " := " + nomY;
            break;

        case OPCODE_PSH :
            res = "push " + nomX;
            break;

        case OPCODE_PSA :
            res = "push " + nomX + " [ " + nomY + " ] ";
            break;

        case OPCODE_PSP :
            res = "push & " + nomX;
            break;

        case OPCODE_PSR :
            res = "push * " + nomX;
            break;

        case OPCODE_POP :
            res = "pop " + nomX;
            break;

        case OPCODE_PPA :
            res = "pop " + nomX + " [ " + nomY + " ] ";
            break;

        case OPCODE_PPR :
            res = "pop * " + nomX;
            break;

        case OPCODE_CLL :
            res = "call " + nomX;
            break;

        case OPCODE_RET :
            res = "return";
            break;

        case OPCODE_RETV :
            res = "return " + nomX;
            break;

        case OPCODE_END :
            res = "end";
            break;

        default :
            res = "type instruction non reference par CodeInstruction (Code3Ad.hpp)";
            break;
    }

    return res;
}
