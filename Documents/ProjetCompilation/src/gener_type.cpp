#include <vector>

#include "gener_type.hpp"


using namespace std;



TypeEntier* GenerType::creerTypeEntier()
{
    TypeEntier* resultat;

    resultat = (TypeEntier*) getTypeSiExiste(entier);

    if(resultat != NULL)
        return resultat;
    else
    {
	TypeEntier * nouv = new TypeEntier();
        tab_types.push_back(nouv);
        return nouv;
    }
}


TypeCaractere* GenerType::creerTypeCaractere()
{
    TypeCaractere* resultat;

    resultat = (TypeCaractere*) getTypeSiExiste(caractere);

    if(resultat != NULL)
        return resultat;
    else
    {
	TypeCaractere * nouv = new TypeCaractere();
        tab_types.push_back(nouv);
        return nouv;
    }
}


TypeReel* GenerType::creerTypeReel()
{
    TypeReel* resultat;

    resultat = (TypeReel*) getTypeSiExiste(reel);

    if(resultat != NULL)
        return resultat;
    else
    {
        TypeReel * nouv = new TypeReel();
        tab_types.push_back(nouv);
        return nouv;
    }
}


TypeBooleen* GenerType::creerTypeBooleen()
{
    TypeBooleen* resultat;

    resultat = (TypeBooleen*) getTypeSiExiste(booleen);

    if(resultat != NULL)
        return resultat;
    else
    {
        TypeBooleen * nouv = new TypeBooleen();
        tab_types.push_back(nouv);
        return nouv;
    }
}

TypeChaine* GenerType::creerTypeChaine()
{
    TypeChaine* resultat;

    resultat = (TypeChaine*) getTypeSiExiste(chaine);

    if(resultat != NULL)
        return resultat;
    else
    {
		TypeChaine * nouv = new TypeChaine();
        tab_types.push_back(nouv);
        return nouv;
    }
}



TypePointeur* GenerType::creerTypePointeur(Type* pointeSur)
{
	TypePointeur* resultat;

    resultat = (TypePointeur*) getTypeSiExiste(pointeur, pointeSur);

	if(resultat != NULL)
		return resultat;
	else
	{
		TypePointeur * nouv = new TypePointeur(pointeSur);
        tab_types.push_back(nouv);
        return nouv;
	}
}

TypeTab * GenerType::creerTypeTab(Type * contenu, Type * range, int taille)
{
	TypeTab * resultat;

	resultat = (TypeTab*) getTypeSiExiste(tableau, range, contenu, taille);

	if(resultat != NULL)
		return resultat;
	else
	{
		TypeTab * nouv = new TypeTab(contenu,range, taille);
        tab_types.push_back(nouv);
        return nouv;
	}
}

TypeInterval* GenerType::creerTypeInterval(Type* debutType, Type* finType, string debut, string fin)
{
    TypeInterval * resultat;

    resultat = (TypeInterval*) getTypeSiExiste(intervalle, debutType, finType);

    if(resultat != NULL)
		return resultat;
	else
	{
		TypeInterval * nouv = new TypeInterval(debutType, finType, debut, fin);
        tab_types.push_back(nouv);
        return nouv;
	}
}

TypeEnum* GenerType::creerTypeEnum(vector<string>* v)
{
    TypeEnum * resultat;

    resultat = (TypeEnum*) getTypeSiExiste(enumeration, v);

    if(resultat != NULL)
		return resultat;
	else
	{
		TypeEnum * nouv = new TypeEnum(v);
        tab_types.push_back(nouv);
        return nouv;
	}
}

TypeRecord* GenerType::creerTypeRecord(vector<TupleRecord>* v)
{
    TypeRecord * resultat;

    resultat = (TypeRecord*) getTypeSiExiste(structure, v);

    if(resultat != NULL)
		return resultat;
	else
	{
		TypeRecord * nouv = new TypeRecord(v);
        tab_types.push_back(nouv);
        return nouv;
	}
}

Type* GenerType::getTypeSiExiste(typeVariable type, Type* sur, Type* de, int taille)
{
    unsigned int i;

    for(i = 0;  i < tab_types.size();  i++)
    {
        if(tab_types[i]->getType() == type)
        {
        	if(sur == NULL && de == NULL)
        	{
        		return tab_types[i];
	        }
    		else if (type == pointeur)
    		{
    			if(verifierTypePointeurExiste((TypePointeur*)sur, (TypePointeur*)tab_types[i]->getType()))
					return tab_types[i];
				else
					return NULL;
			}
			else if (type == tableau)
			{
				TypeTab * tmp = (TypeTab*) tab_types[i];
				if(tmp->getContenuType() == sur && tmp->getRangeType() == de && tmp->getTaille() == taille)
					return tab_types[i];
				else
					return NULL;
			}
			else if (type == intervalle)
			{
                TypeInterval * tmp = (TypeInterval*) tab_types[i];
				if(tmp->getDebutType() == sur && tmp->getFinType() == de)
					return tab_types[i];
				else
					return NULL;
			}
        }
    }

    return NULL;
}

Type* GenerType::getTypeSiExiste(typeVariable type, vector<string>* v)
{
    unsigned int i;

    for(i = 0;  i < tab_types.size();  i++)
    {
        if(tab_types[i]->getType() == type)
        {
        	if(v == NULL)
        	{
        		return tab_types[i];
	        }
	        else
	        {
	            TypeEnum * tmp = (TypeEnum*) tab_types[i];
                if(*v == *(tmp->getList()))
                {
                    return tab_types[i];
                }
                else
                    return NULL;
	        }
        }
    }
    return NULL;
}

Type* GenerType::getTypeSiExiste(typeVariable type, vector<TupleRecord>* v)
{
    unsigned int i;

    for(i = 0;  i < tab_types.size();  i++)
    {
        if(tab_types[i]->getType() == type)
        {
        	if(v == NULL)
        	{
        		return tab_types[i];
	        }
	        else
	        {   // A faire un jour la vérification stricte de 2 structures
	            /*TypeRecord * tmp = (TypeRecord*) tab_types[i];
                if(*v == *(tmp->getVect()))
                {
                    return tab_types[i];
                }
                else*/
                    return NULL;
	        }
        }
    }
    return NULL;
}

bool GenerType::verifierTypePointeurExiste(TypePointeur* t1, TypePointeur* t2)
{
	if(t1->estDeType(pointeur) and t2->estDeType(pointeur))
		return verifierTypePointeurExiste((TypePointeur*)t1->getPointeSur(), (TypePointeur*)t2->getPointeSur());
	else if (t1->getPointeSur() == t2->getPointeSur())
		return true;
	else
		return false;
}

