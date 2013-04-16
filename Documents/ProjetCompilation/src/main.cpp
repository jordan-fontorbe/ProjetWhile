#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "tab_ids.hpp"
#include "type_reel.hpp"
#include "type_entier.hpp"
#include "type_booleen.hpp"
#include "type_char.hpp"
#include "type.hpp"
#include "type_tab.hpp"
#include "var_expr.hpp"
#include "Code3ad.hpp"

#include "gener_type.hpp"
#include "tab_symboles.hpp"
#include "expression.hpp"


#include "symbole_argument.hpp"
#include "symbole_constante.hpp"


#include "tuple_interval.hpp"
#include "tuple_array.hpp"
#include "tuple_record.hpp"

#include "parser.hpp"


using namespace std;


/* Pour pouvoir utiliser les fonctions du parser */
extern int yyparse();
extern int yylex();
extern FILE *yyin;

/* Generateur de types */
GenerType* genType;
/* Table des identificateurs */
TabIds* tab_ident;
/* Table des symboles courante */
TabSymboles* tab_symb;

/* numero d'operation de branchement */
int nbOpBr = 0;

/* Le code trois adresses genere. */
string codeProgramme;


int main(int argc, char* argv[])
{
    FILE * a_parser;

    if(argc > 1)
    {
        cout << "Ouverture de " << argv[1] << "... ";
        a_parser = fopen(argv[1] ,"r");
        if(a_parser == NULL)
        {
            cout << endl << "Ouverture impossible. Fin du programme." << endl;
            return EXIT_FAILURE;
        }
        else
        {
            cout << "Ok." << endl << endl;
        }
        yyin = a_parser;
    }

    tab_ident = new TabIds;
    tab_symb = new TabSymboles(NULL, 0);
    genType = new GenerType;

    yyparse();

    fclose(a_parser);

    tab_ident->afficher();
    putchar('\n');

    /* On remonte a la table de symboles "racine". */
    while(tab_symb->getMere() != NULL)
        tab_symb = tab_symb->getMere();

    tab_symb->afficher(tab_ident);

    cout << "** Code trois adresses" << endl;
    cout << (codeProgramme.empty() ? "<Vide>\n" : codeProgramme) << endl;


    delete tab_ident;
    delete tab_symb;
    delete genType;

    //cout << "Nb types crees : " << genType->getNbTypes() << endl;

    //Fonctions pour l'analyse;
    //Pour le moment la fonction prend l'entrée standard, soit un fichier input par exemple par cat en entrée
    // Ainsi, pas d'entrée implique pour le moment un bug du programme.
    //cout << yyparse() << endl;
    //cout << yylex() << endl;

    /*
    int id1 = tab_ident.inserer("Tulipe");
    int id2 = tab_ident.inserer("Macaron");

    TypeEntier test;
    TypeEntier test2;
    TypeReel typereal;
    TypeReel typereal2;
    TypeBooleen typeBool;
    TypeBooleen typeBool2;
    TypeCaractere typeCar;
    TypeCaractere typeCar2;

    cout<<"Test de comparaisons de type"<<endl;
    cout<<"==== Test d'entiers ===="<<endl;
    cout<<"	** Avec entier ****"<<endl;
    if( test==test2 )
    {
        cout<<"	Fonctionnel "<<endl;
    }
    else
    {
        cout<<"	Erreur durant la comparaison"<<endl;
    }

    cout<<"	** Avec réel à gauche ****"<<endl;
    if( typereal==test)
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    else
    {
        cout <<"	Fonctionnel"<<endl;
    }

    cout<<"	** Avec booleen à droite ****"<<endl;
    if( test==typeBool)
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    else
    {
        cout <<"	Fonctionnel"<<endl;
    }

    cout<<"	** Avec booleen à gauche ****"<<endl;
    if( typeBool==test)
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    else
    {
        cout <<"	Fonctionnel"<<endl;
    }

    cout<<"	** Avec réel à droite ****"<<endl;
    if( test==typereal)
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    else
    {
        cout <<"	Fonctionnel"<<endl;
    }
    */

    /*
    cout<<"==== Test de reel ===="<<endl;
    cout<<"	** Avec reel ****"<<endl;
    if( typereal==typereal2)
    {
        cout <<"	Fonctionnel"<<endl;
    }
    else
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    */

    /*
    cout<<"==== Test de Booleen ===="<<endl;
    cout<<"	** Avec Booleen ****"<<endl;
    if( typeBool==typeBool2)
    {
        cout <<"	Fonctionnel"<<endl;
    }
    else
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    */

    /*
    cout<<"==== Test de caractères ===="<<endl;
    cout<<"	** Avec Caractère ****"<<endl;
    if( typeCar==typeCar2)
    {
        cout <<"	Fonctionnel"<<endl;
    }
    else
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    cout<<"	** Avec entier ****"<<endl;
    cout<<"	** Avec Caractère à gauche ****"<<endl;
    if( typeCar==test2 )
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    else
    {
        cout <<"	Fonctionnel"<<endl;
    }
    cout<<"	** Avec Caractère à droite ****"<<endl;
    if( test2==typeCar )
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    else
    {
        cout <<"	Fonctionnel"<<endl;
    }
    cout<<"	** Avec Reel à droite ****"<<endl;
    if( typeCar==typereal2)
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    else
    {
        cout <<"	Fonctionnel"<<endl;
    }
    cout<<"	** Avec Reel à gauche ****"<<endl;
    if( typereal==typeCar2)
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    else
    {
        cout <<"	Fonctionnel"<<endl;
    }

    cout<<"	** Avec entier ****"<<endl;
    cout<<"	** Avec Booleen à droite ****"<<endl;
    if( typeCar==typeBool2)
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    else
    {
        cout <<"	Fonctionnel"<<endl;
    }
    cout<<"	** Avec Booleen à gauche ****"<<endl;
    if( typeBool==typeCar2)
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    else
    {
        cout <<"	Fonctionnel"<<endl;
    }
    */


    /* Test sur les comparaisons de tableaux */
    /*
    TypeTab tab1( &test  );
    TypeTab tab2( &test );
    TypeTab tab3( (Type*)&tab1  );
    */

    /* Test sur les tableau : On affiche */
    /*
    tab1.afficher();
    tab2.afficher();
    tab3.afficher();
    */

    /* On compare */
    /*
    cout<<"==== Test de Tableau ===="<<endl;
    cout<<"	** Avec Tableau identique ****"<<endl;
    if( tab1 == (Type&)tab2)
    {
        cout <<"	Fonctionnel"<<endl;
    }
    else
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }

    cout<<"	** Avec Tableau différent à gauche ****"<<endl;
    if( tab3 == (Type&)tab2)
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    else
    {
        cout <<"	Fonctionnel"<<endl;
    }


    cout<<"	** Avec Tableau différent à droit ****"<<endl;
    if( tab2 == (Type&)tab3 )
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    else
    {
        cout <<"	Fonctionnel"<<endl;
    }


    cout<<"	** Avec Tableau  et entier à gauche ****"<<endl;
    if( test == (Type&)tab2)
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    else
    {
        cout <<"	Fonctionnel"<<endl;
    }

    cout<<"	** Avec Tableau  et entier à droite ****"<<endl;
    if( tab1 == test)
    {
        cout <<"	Erreur durant la comparaison"<<endl;
    }
    else
    {
        cout <<"	Fonctionnel"<<endl;
    }
    */



    //cout << "id1 = " << id1 << ", id2 = " << id2 << endl;
    /*
     * cout << "tab[\"Macaron\"] = " << tab_ident.get_id("Macaron")
            << ", tab[\"Tulipe\"] = " << tab_ident.get_id("Tulipe") << endl;
     *
     */
    /*
    tab_ident.afficher();

    cout << tab_ident.get_nom(id1) << endl;

    cout << "Plume" << tab_ident.get_nom(42) << "Poire" << endl;



    cout << "========== Tests Minot ==========" << endl;

    TabSymboles ts(NULL);
    SymboleConstante* p_nouvSymb;

    p_nouvSymb = new SymboleConstante;

    cout << "Premier add (ok (0)) : " << ts.add(42, p_nouvSymb) << endl;
    cout << "Get par index de ce qui vient d'etre add : " << ts.get(0) << endl;
    cout << "Second add (ok (0)) : " << ts.add(12, p_nouvSymb) << endl;
    cout << "Get par id de ce qui vient d'etre add : " << ts.getParId(12) << endl;
    cout << "Get par id de truc inexistant (doit renvoyer NULL (0)) : " << ts.getParId(99) << endl;
    cout << "Troisieme add (foire car id deja pris) : " << ts.add(42, p_nouvSymb) << endl;
    */


    return EXIT_SUCCESS;
}

