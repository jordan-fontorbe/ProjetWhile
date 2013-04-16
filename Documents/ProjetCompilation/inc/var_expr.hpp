/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef VAR_EXPR_HPP
#   define VAR_EXPR_HPP



using namespace std;



/** Permet de differencier les types de VarExpr,
 * correspondant aux regles de la grammaire :
 * TOK_IDENT
 * TOK_IDENT SEP_CO ListIndices SEP_CF
 * TOK_IDENT SEP_DOT TOK_IDENT %prec OP_DOT
 * TOK_IDENT OP_PTR
 * (dans le meme ordre) */
enum typeVarExpr
{
    tve_idSimple,
    tve_tableau,
    tve_trucAvecPrec,
    tve_pointeur
};



/**
 * Informations du symbole nnon terminal VarExpr de la grammaire.
 */
class VarExpr
{
    /** Id, dans la table des identificateurs, de la variable. */
    int id;
    typeVarExpr monTypeVarExpr;

public:
    VarExpr(int _id, typeVarExpr _type);
    ~VarExpr();

    int getId() { return id; }
    typeVarExpr getType() { return monTypeVarExpr; }
};


#endif /* VAR_EXPR_HPP */
