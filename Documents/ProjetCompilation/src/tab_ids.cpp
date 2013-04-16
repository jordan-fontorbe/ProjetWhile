#include <iostream>

#include "tab_ids.hpp"

using namespace std;


TabIds::~TabIds()
{
	tab_hach.erase(tab_hach.begin(), tab_hach.end());
}
int TabIds::inserer(string str)
{
    pair<map<string,int>::iterator, bool> ret_insert;

    ret_insert = tab_hach.insert(pair<string, int>(str, tab_hach.size()));

    if(ret_insert.second)
        return ret_insert.first->second;
    else
        return this->get_id(str);
}


int TabIds::get_id(string str)
{
    if(tab_hach.count(str) > 0)
        return tab_hach[str];
    else
        return -1;
}


string TabIds::get_nom(int id)
{
    map<string, int>::iterator it;

    for(it = tab_hach.begin(); it != tab_hach.end(); ++it)
    {
        if(it->second == id)
            return it->first;
    }

    return "";
}


void TabIds::afficher_debug()
{
    map<string,int>::iterator iter;
    for(iter = tab_hach.begin(); iter != tab_hach.end(); iter++)
    {
        cout << "Value: " << iter->first << ", key: " << iter->second << endl;
    }
}

void TabIds::afficher()
{
    //unsigned int i;

    cout << endl << "** Table des identificateurs" << endl;

    // Version par ordre alphabetique
    map<string,int>::iterator iter;
    for(iter = tab_hach.begin(); iter != tab_hach.end(); iter++)
    {
        cout<< iter->second << '\t' << iter->first << endl;
    }


/*    for(i = 0;  i < tab_hach.size();  i++)
        cout << i << '\t' << get_nom(i) << endl;*/
}



