#include "suite_instructions.hpp"


SuiteIns::SuiteIns()
{

}


SuiteIns::~SuiteIns()
{

}

string SuiteIns::getStr(TabIds* tab_ident)
{
	string res, etiquette;
	unsigned int i;

	for(i = 0; i < tabIns.size(); i++)
	{
        etiquette = tabIns[i]->getEtiquette();
	
	    /* Etiquette, deux tabulations, instruction, retour a la ligne. */
		res += etiquette
		        + (etiquette.length() < 8 ? "\t\t" : "\t")
		        + tabIns[i]->getStr(tab_ident) + '\n';
	}

	return res;
}
