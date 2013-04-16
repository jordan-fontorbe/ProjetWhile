#include "expression.hpp"
#include <iostream>
#include <sstream>
#include "math.h"
#include "tab_symboles.hpp"
#include "tab_ids.hpp"
#include "temporaire.hpp"
#include "type_booleen.hpp"

using namespace std;

Expression::Expression()
{
   id = -1;
   monType = NULL;
   calculee = false;
}


Expression::~Expression()
{

}


Expression::Expression(Type* type)
{
    monType = type;
    id = -1;
    calculee = false;
}


void Expression::setType( Type* type)
{
   monType = type;
}

/* cree une operande depuis l expression */
Operande * Expression::createOperande( TabIds * tabIdent)
{
	Operande * res = NULL;
	if(this->getCalculee())
	{
		res = new Operande( this->get_type()->getType() );
		switch(this->get_type()->getType())
		{
		  case entier	: res->setValInt(this->getValInt()); break;
		  case reel 	: res->setValReel(this->getValReel()); break;
		  case booleen 	: res->setValBool(this->getValBool()); break;
		  default : break; // N apparait jamais normalement : (gestion erreur en amont)
				   // En effet, setCalculee est en le cas d'un calcul. Donc d'un des trois types ci dessus.
		}
		return res;
	}
	else
	{
		int tempId = -1;
		string * res2;
		res = new Operande( this->get_type()->getType() );

	        if(this->getId() == -1)
	        {
	  	    res2 = getNomTempSuivant(tabIdent);
	  	    tempId = tabIdent->inserer(*res2);
   	        }
	        else
	        {
	    	     tempId = this->getId();
	        }
		res->setIdVar( tempId );
		return res;
	}

}


bool Expression::getCalculee()
{
    return calculee;
}

Type* Expression::get_type() //TODO : Cohérence syntaxe pour les getter
{
    return monType;
}


int Expression::getValInt()
{
    return valInt;
}


int Expression::getId()
{
    return id;
}

double Expression::getValReel()
{
    return valReel;
}


bool Expression::getValBool()
{
    return valBool;
}

string* Expression::getValChaine()
{
    return valChaine;
}

void Expression::setId( int i )
{
  id = i;
}

void Expression::setCalculee( bool calc )
{
  calculee = calc;
}

void Expression::setValInt(int val)
{
    valInt = val;
}


void Expression::setValReel(double val)
{
    valReel = val;
}


void Expression::setValBool(bool val)
{
    valBool = val;
}

void Expression::setValChaine(string* val)
{
    valChaine = val;
}


Expression * Expression::calculNumerique(Expression * ex2, OperatorNumerique comparator, int &codeErreur
					, TabIds * tabIdent, int & nbOpBr )
{
	Expression * res = NULL;
	int typeExpr1 = 0;
	int typeExpr2 = 0;
	Expression * temp = NULL;

	/*
	 plus : integer ou entier  + integer ou entier
	 moins : integer ou entier - integer ou entier
	 fois : integer ou entier  + integer ou entier
	 slash : integer ou entier / integer ou entier
	 mod : integer % integer
	 div : integer , integer
	*/
	if( this->get_type()->estDeType( entier) )
		typeExpr1 = 1;
	else if( this->get_type()->estDeType(reel))
		typeExpr1 = 2;

	if( ex2->get_type()->estDeType( entier) )
		typeExpr2 = 1;
	else if( ex2->get_type()->estDeType(reel))
		typeExpr2 = 2;

	if( ((typeExpr1 != 2) && (typeExpr1 != 1)) ||
	    ((typeExpr2 != 2) && (typeExpr2 != 1))
	  )
	{
		codeErreur = 2;
		return NULL;
	}

	/* L'un des deux n'est pas du meme type */
	if( (typeExpr1 == 2) && (typeExpr2 == 1) )
	{
		temp = new Expression( this->get_type() );
		temp->setValReel( (double)ex2->getValInt() );
		temp->setCalculee(true);
		//temp->ajouterSuiteIns( ex2);
		res = this->calculReel(temp, comparator, codeErreur, tabIdent);
		delete temp;
	}
	else if((typeExpr2 == 2) && (typeExpr1 == 1))
	{
		temp = new Expression( ex2->get_type() );
		temp->setValReel( (double)this->getValInt() );
		temp->setCalculee(true);
		//temp->ajouterSuiteIns(this);
		res = temp->calculReel(ex2, comparator, codeErreur, tabIdent);
		delete temp;
	}
	// Le meme type
	else if( typeExpr1 == 1)
	{
		res = this->calculEntier( ex2, comparator, codeErreur, tabIdent, nbOpBr);
	}
	else
	{
		res = this->calculReel( ex2, comparator, codeErreur, tabIdent);
	}

	return res;
}



Expression * Expression::calculEntier(Expression * ex2, OperatorNumerique comparator, int &codeErreur
				     , TabIds * tabIdent, int &nbOpBr )
{
	bool valide = false;
	int tempId = 0;

	if( ex2 != NULL)
	{
		valide = ( this->get_type() == ex2->get_type() );
		if(valide)
			valide = (this->get_type()->estDeType(entier));
	}
	Expression * res = new Expression( this->get_type());

	if(!valide)
	{
		codeErreur = 1;
	}
	else
	{
	  if(this->getCalculee() and ex2->getCalculee())
		{
			res->setCalculee(true);
			switch( comparator)
			{
			  case Operator_plus 	:  res->setValInt( this->getValInt() + ex2->getValInt() );
						   break;
			  case Operator_moins   :  res->setValInt( this->getValInt() - ex2->getValInt() );
						   break;
			  case Operator_fois 	:  res->setValInt( this->getValInt() * ex2->getValInt() );
						   break;
			  case Operator_slash	:  if(ex2->getValInt() == 0) {codeErreur = 3;}
						   res->setValInt( this->getValInt() / ex2->getValInt() );
						   break;
			  case Operator_puis 	:  res->setValInt( pow( this->getValInt(), ex2->getValInt() ) );
						   break;
			  case Operator_mod	:  res->setValInt( this->getValInt() % ex2->getValInt()  );
						   break;
			  case Operator_div	:  if(ex2->getValInt() == 0) {codeErreur = 3;}
						   res->setValInt( (this->getValInt()
								   -(this->getValInt()%ex2->getValInt()))/ex2->getValInt() );
						   break;
			  default : codeErreur = 2; break;

			}
		}
	  else
		{
			res->setCalculee(false);
			Operande * op1 = NULL;
			Operande * op2 = NULL;
			Operande * op3 = NULL;
			Operande * op4 = NULL;
			Operande * op5 = NULL;
			Expression  *temp;
			string * res2 = getNomTempSuivant(tabIdent);
			tempId = tabIdent->inserer(*res2);
			res->setId(tempId);
			op1 = new Operande(tempId);

			/* Operande 1 */
			if( this->getCalculee())
			{
			  op2 = new Operande( this->get_type()->getType() );
			  op2->setValInt( this->getValInt() );
			}
			else
			{
			  res->ajouterSuiteIns(this);
			  if(this->getId() == -1)
			  {
			  	res2 = getNomTempSuivant(tabIdent);
			  	tempId = tabIdent->inserer(*res2);
		   	  }
			  else
			  {
				tempId = this->getId();
			  }
			  op2 = new Operande(tempId);
			}

			if( ex2->getCalculee())
			{
			  op3 = new Operande( this->get_type()->getType() );
			  op3->setValInt( this->getValInt() );
			}
			else
			{
			  res->ajouterSuiteIns( ex2 );
			  if(ex2->getId() == -1)
			  {
			  	res2 = getNomTempSuivant(tabIdent);
			  	tempId = tabIdent->inserer(*res2);
		   	  }
			  else
			  {
				tempId = ex2->getId();
			  }
			  op3 = new Operande(tempId);
			}

			Instruction * ins = NULL;
			SuiteIns * suite = NULL;
			string nbOpBrStr;
			CodeInstruction typeIns = OPCODE_NONE;
			switch( comparator)
			{
			  case Operator_plus 	:  typeIns =  OPCODE_ADD;
						   ins = new Instruction(typeIns, op1, op2, op3  );
						   res->ajouterIns( ins );
						   res->code.setIdRes( op1->getIdVar());
						   break;
			  case Operator_moins   :  typeIns =  OPCODE_SUB;
						   ins = new Instruction(typeIns, op1, op2, op3  );
						   res->ajouterIns( ins );
						   res->code.setIdRes( op1->getIdVar());
						   break;
			  case Operator_fois 	:  typeIns =  OPCODE_MUL;
						   ins = new Instruction(typeIns, op1, op2, op3  );
						   res->ajouterIns( ins );
						   res->code.setIdRes( op1->getIdVar());
						   break;
			  case Operator_slash	:  if(ex2->getValInt() == 0) {codeErreur = 3;}
						   typeIns =  OPCODE_DIV;
						   ins = new Instruction(typeIns, op1, op2, op3  );
						   res->ajouterIns( ins );
						   res->code.setIdRes( op1->getIdVar());
						   break;
			  case Operator_puis 	:  //Non Traite
						   ins = new Instruction(typeIns, op1, op2, op3  );
						   res->ajouterIns( ins );
						   res->code.setIdRes( op1->getIdVar());
						   break;
			  case Operator_mod	:  //On genere un while
						   nbOpBr++;
                           nbOpBrStr = static_cast<ostringstream*>( &(ostringstream() << nbOpBr) )->str();
                           suite = new SuiteIns();
                           suite->addDebut( new Instruction(OPCODE_NONE) );
                           suite->getPremiere()->setEtiquette("condWhile" + nbOpBrStr);
                           //Creation du conditionnel
                           res2 = getNomTempSuivant(tabIdent);
                           tempId = tabIdent->inserer(*res2);
                           op4 = new Operande( tempId );
                           suite->add( new Instruction( OPCODE_LT, op4, op2, op3 ) );
                           //Creation des jumps
                           suite->add( new Instruction( OPCODE_JMPC, op4, new Operande( new string("bouWhile" + nbOpBrStr))));
                           suite->add( new Instruction( OPCODE_JMP, new Operande( new string("finWhile" + nbOpBrStr))));

                           //Creation de la boucle
                           ins = new Instruction( OPCODE_SUB, op2, op2, op3 );
                           ins->setEtiquette("bouWhile" + nbOpBrStr);
                           suite->add( ins );

                           //Fin de la boucle
                           suite->add(new Instruction(OPCODE_JMP, new Operande(new string("condWhile" + nbOpBrStr))));
                           ins = new Instruction( OPCODE_NONE );
                           ins->setEtiquette("finWhile" + nbOpBrStr );
                           suite->add(ins);

                           suite->add( new Instruction(OPCODE_CPY, op1, op2) );
                           res->code.add(suite);
						   res->code.setIdRes( op1->getIdVar());
						   break;
			  case Operator_div	:  //On genere un while
						   nbOpBr++;
                           nbOpBrStr = static_cast<ostringstream*>( &(ostringstream() << nbOpBr) )->str();
                           suite = new SuiteIns();
                           suite->addDebut( new Instruction(OPCODE_NONE) );
                           suite->getPremiere()->setEtiquette("condWhile" + nbOpBrStr);
                           //Creation de deux conditionnels
                           res2 = getNomTempSuivant(tabIdent);
                           tempId = tabIdent->inserer(*res2);
                           op4 = new Operande( tempId );
                           res2 = getNomTempSuivant(tabIdent);
                           tempId = tabIdent->inserer(*res2);
                           op5 = new Operande( tempId );
                           temp = new Expression( this->get_type() );
                           temp->setValInt(0);
                           temp->setCalculee(true);
                           suite->addDebut( new Instruction( OPCODE_CPY, op5, temp->createOperande(tabIdent) ) );
                           delete temp;

                           suite->add( new Instruction( OPCODE_LT, op4, op2, op3 ) );
                           //Creation des jumps
                           suite->add( new Instruction( OPCODE_JMPC, op4, new Operande( new string("bouWhile" + nbOpBrStr))));
                           suite->add( new Instruction( OPCODE_JMP, new Operande( new string("finWhile" + nbOpBrStr))));

                           //Creation de la boucle
                           ins = new Instruction( OPCODE_SUB, op2, op2, op3 );
                           ins->setEtiquette("bouWhile" + nbOpBrStr);
                           suite->add( ins );
                           temp = new Expression( this->get_type() );
                           temp->setValInt(1);
                           temp->setCalculee(true);
                           suite->add( new Instruction( OPCODE_ADD, op5, temp->createOperande(tabIdent), op5 ) );

                           //Fin de la boucle
                           suite->add(new Instruction(OPCODE_JMP, new Operande(new string("condWhile" + nbOpBrStr))));
                           ins = new Instruction( OPCODE_NONE );
                           ins->setEtiquette("finWhile" + nbOpBrStr );
                           suite->add(ins);

                           suite->add( new Instruction(OPCODE_CPY, op1, op5) );
                           res->code.add(suite);
						   res->code.setIdRes( op1->getIdVar());
						   break;
			  default : codeErreur = 2; break;

			}

			/* Les instructions plus compliquees (div, puis, mod... sont faites apres) */
			//Instruction * ins = new Instruction(typeIns, op1, op2, op3  );
			//res->ajouterIns( ins );
			//res->code.setIdRes( op1->getIdVar());
			//Suite d instructions generees par l operation en cour
			//SuiteIns * ins = NULL;

		}
	}

	return res;


}



Expression * Expression::calculReel(Expression * ex2, OperatorNumerique comparator, int &codeErreur
				   , TabIds * tabIdent )
{
	//Test égalite sur type.
	bool valide = false;
	//Suite d instructions generees par l operation en cour
	int tempId;

	if( ex2 != NULL)
	{
		valide = ( this->get_type() == ex2->get_type() );
		if(valide)
			valide =  (this->get_type()->estDeType(reel));
	}
	Expression * res = new Expression( this->get_type());

	if(!valide)
	{
		codeErreur = 1;
	}
	else
	{
	  if(this->getCalculee() and ex2->getCalculee())
		{
			res->setCalculee(true);
			//Calcul selon l'opérateur. Vérifications selon l'opérateur
			// Reel dispose des opérateurs suivants : Plus, Moins, Fois, Div, Exp
			switch( comparator)
			{
			  case Operator_plus 	:  res->setValReel( this->getValReel() + ex2->getValReel() );
						   break;
			  case Operator_moins   :  res->setValReel( this->getValReel() - ex2->getValReel() );
						   break;
			  case Operator_fois 	:  res->setValReel( this->getValReel() * ex2->getValReel() );
						   break;
			  case Operator_slash	:  if(ex2->getValReel() == 0) {codeErreur = 3;}
						   res->setValReel( this->getValReel()/ex2->getValReel() );
						   break;
			  case Operator_puis 	:  res->setValReel( pow( this->getValReel(), ex2->getValReel() ) );
						   break;
			  default : codeErreur = 2; break;

			}
		}
		else
		{
			res->setCalculee(false);
			Operande * op1 = NULL;
			Operande * op2 = NULL;
			Operande * op3 = NULL;
			string * res2 = getNomTempSuivant(tabIdent);
			tempId = tabIdent->inserer(*res2);
			res->setId(tempId);
			op1 = new Operande(tempId);
			/* Operande 1 */
			if( this->getCalculee())
			{
			  op2 = new Operande( this->get_type()->getType() );
			  op2->setValReel( this->getValReel() );
			}
			else
			{
			  res->ajouterSuiteIns(this);
			  if(this->getId() == -1)
			  {
			  	res2 = getNomTempSuivant(tabIdent);
			  	tempId = tabIdent->inserer(*res2);
		   	  }
			  else
			  {
				tempId = this->getId();
			  }
			  op2 = new Operande(tempId);
			}

			if( ex2->getCalculee())
			{
			  op3 = new Operande( this->get_type()->getType() );
			  op3->setValReel( this->getValReel() );
			}
			else
			{
			  res->ajouterSuiteIns( ex2 );
			  if(ex2->getId() == -1)
			  {
			  	res2 = getNomTempSuivant(tabIdent);
			  	tempId = tabIdent->inserer(*res2);
		   	  }
			  else
			  {
				tempId = ex2->getId();
			  }
			  op3 = new Operande(tempId);
			}

			CodeInstruction typeIns = OPCODE_NONE;
			switch( comparator)
			{
			  case Operator_plus 	:  typeIns =  OPCODE_ADD;
						   break;
			  case Operator_moins   :  typeIns =  OPCODE_SUB;
						   break;
			  case Operator_fois 	:  typeIns =  OPCODE_MUL;
						   break;
			  case Operator_slash	:  if(ex2->getValInt() == 0) {codeErreur = 3;}
						   typeIns =  OPCODE_DIV;
						   break;
			  case Operator_puis 	:  //codeErreur = 2;
						   break;
			  case Operator_mod	:  codeErreur=2;
						   break;
			  case Operator_div	:  codeErreur=2;
						   break;
			  default : codeErreur = 2; break;

			}

			/* Les instructions plus compliquees (puis... sont faites apres) */
			Instruction * ins = new Instruction(typeIns, op1, op2, op3  );
			res->ajouterIns( ins );
			res->code.setIdRes( op1->getIdVar());
			//Suite d instructions generees par l operation en cour
			//SuiteIns * ins = NULL;

		}
	}
	// Recuperation des listes d instructions
	/*if((res != NULL) && !(res->getCalculee()))
	{
		res->ajouterSuiteIns( this );
		res->ajouterSuiteIns( ex2 );*/
		//res->ajouterIns();
	//}
	return res;
}

Expression * Expression::calculBool(Expression* ex2, OperatorBooleen comparator, int &codeErreur, TabIds * tabIdent)
{
	// Test egalite des types
	bool valide = false;

    if(ex2 != NULL)
    {
        valide = (this->get_type() == ex2->get_type());

        // Si les types sont equivalents, on verifie que this est de type booleen
        if(valide == true)
            valide = this->get_type()->estDeType(booleen);
    }
    if( ( ex2 == NULL ) && ( comparator == Operator_not ))
	{
	  valide = true;
	}

	Expression * res = new Expression( this->get_type() );

	// Si ce n'est pas valide on remonte au parser une erreur au niveau du calcul des boolean avec une incompatibilité de type
	if(!valide)
	{
		codeErreur = 1;
	}
	else
	{
        if(this->getCalculee() and ex2->getCalculee())
        {
            bool valEx1 = this->getValBool();
            bool valEx2 = false;
            if(ex2 != NULL)
                valEx2 = ex2->getValBool();

            bool valRes = false;
            switch(comparator)
            {
                case Operator_and : valRes = valEx1 and valEx2;
                break;
                case Operator_or : valRes = valEx1 or valEx2;
                break;
                case Operator_xor : valRes = valEx1 xor valEx2;
                break;
                case Operator_not : valRes = not valEx1;
                break;
                default : codeErreur = 2;
                break;
            }

            res->setValBool(valRes);
            res->setCalculee(true);
        }
        else
        {
            res->setCalculee(false);
	    Operande * op1 = NULL;
	    Operande * op2 = NULL;
	    Operande * op3 = NULL;
	    //Pour le XOR
	    Operande * op4 = NULL;
	    Operande * op5 = NULL;
	    Operande * op6 = NULL;
	    Operande * op7 = NULL;
	    string * res2 = getNomTempSuivant(tabIdent);
	    int tempId = tabIdent->inserer(*res2);
	    res->setId(tempId);
	    op1 = new Operande(tempId);
	    /* Operande 1 */
	    op2 = this->createOperande(tabIdent);
	    if( !( this->getCalculee()))
	    {
	      res->ajouterSuiteIns(this);
	    }

	    // Gestion du cas particulier du Not
	    if(ex2 != NULL)
	    {
	      op3 = ex2->createOperande(tabIdent);
	      if( !(ex2->getCalculee()) )
	      {
	        res->ajouterSuiteIns(ex2);
	      }
	    }

	    CodeInstruction typeIns = OPCODE_NONE;

            switch(comparator)
            {
                case Operator_and : typeIns = OPCODE_ADD;
			   	    res->ajouterIns( new Instruction(typeIns, op1, op2, op3) );
				    res->code.setIdRes( op1->getIdVar());
                break;
                case Operator_or : typeIns = OPCODE_OR;
			   	    res->ajouterIns( new Instruction(typeIns, op1, op2, op3) );
				    res->code.setIdRes( op1->getIdVar());
                break;
                case Operator_xor : //Creation via (a \/ b) /\ (-a \/ -b)
		//Generation des variables
		//Var 1
		 res2 = getNomTempSuivant(tabIdent);
	   	 tempId = tabIdent->inserer(*res2);
	    	 op4 = new Operande(tempId);
		//Var 2
		 res2 = getNomTempSuivant(tabIdent);
	   	 tempId = tabIdent->inserer(*res2);
	    	 op5 = new Operande(tempId);
		//Var 3
		 res2 = getNomTempSuivant(tabIdent);
	   	 tempId = tabIdent->inserer(*res2);
	    	 op6 = new Operande(tempId);
		//Var 4
		 res2 = getNomTempSuivant(tabIdent);
	   	 tempId = tabIdent->inserer(*res2);
	    	 op7 = new Operande(tempId);
		//Generation des instructions
		 res->ajouterIns( new Instruction( OPCODE_NOT, op4, op2) );
		 res->ajouterIns( new Instruction( OPCODE_NOT, op5, op3) );
		 res->ajouterIns( new Instruction( OPCODE_OR, op6, op2, op3) );
		 res->ajouterIns( new Instruction( OPCODE_OR, op7, op4, op5) );
		 res->ajouterIns( new Instruction( OPCODE_AND, op1, op6, op7) );
                break;
                case Operator_not : typeIns = OPCODE_NOT;
			   	    res->ajouterIns( new Instruction(typeIns, op1, op2) );
				    res->code.setIdRes( op1->getIdVar());
                break;
                default : codeErreur = 2;
                break;
            }


        }
    }


	return res;
}




Expression * Expression::calculComp(Expression * ex2, OperatorComp comparator, int &codeErreur
					, TabIds * tabIdent)
{
	Expression * res = NULL;
	int typeExpr1 = 0;
	int typeExpr2 = 0;
	TypeBooleen * tempType = new TypeBooleen();
	Expression * temp = NULL;

	if( this->get_type()->estDeType( entier) )
		typeExpr1 = 1;
	else if( this->get_type()->estDeType(reel))
		typeExpr1 = 2;
    else if( this->get_type()->estDeType(booleen) )
        typeExpr1 = 3;

	if( ex2->get_type()->estDeType( entier) )
		typeExpr2 = 1;
	else if( ex2->get_type()->estDeType(reel))
		typeExpr2 = 2;
    else if( ex2->get_type()->estDeType(booleen))
        typeExpr2 = 3;

	if( (((typeExpr1 != 2) && (typeExpr1 != 1)) ||
	    ((typeExpr2 != 2) && (typeExpr2 != 1)) ) &&
        ((typeExpr1 != 3) && (typeExpr2 != 3) )
	  )
	{
	    cout << "Sortie Derobee par la porte de shtroumpf" <<endl;
		codeErreur = 2;
		return NULL;
	}

    if(typeExpr1 != 3)
    {
        /* L'un des deux n'est pas du meme type */
        if( (typeExpr1 == 2) && (typeExpr2 == 1) )
        {
            temp = new Expression( this->get_type() );
            temp->setValReel( (double)ex2->getValInt() );
            temp->setCalculee(true);
            //temp->ajouterSuiteIns( ex2);
            res = this->calculCompReel(temp, comparator, codeErreur, tabIdent);
            delete temp;
        }
        else if((typeExpr2 == 2) && (typeExpr1 == 1))
        {
            temp = new Expression( ex2->get_type() );
            temp->setValReel( (double)this->getValInt() );
            temp->setCalculee(true);
            //temp->ajouterSuiteIns(this);
            res = temp->calculCompReel(ex2, comparator, codeErreur, tabIdent);
            delete temp;
        }
        // Le meme type
        else if( typeExpr1 == 1)
        {
            res = this->calculCompEntier( ex2, comparator, codeErreur, tabIdent);
        }
        else
        {
            res = this->calculCompReel( ex2, comparator, codeErreur, tabIdent);
        }

    }
    else
    {
        /*
            Dans tout les cas, nous créons un Booleen.
        */
        res = new Expression( tempType );
        delete tempType;
        bool valEx1 = this->getValBool();
        bool valEx2 = ex2->getValBool();
        bool valRes = false;
        //Gestion de 2 booleens
        if( (this->getCalculee()) && (ex2->getCalculee()) )
        {
            res->setCalculee(true);
            switch(comparator)
               {
                  case Operator_eq : valRes = (valEx1 == valEx2);
                  break;
                  case Operator_neq : valRes = (valEx1 != valEx2);
                  break;
                  default : codeErreur = 2;
                  break;
                }
            res->setValBool( valRes );
        }
        else
        {
            res->setCalculee(false);
            //Generation des Operandes
            Operande * op1 = NULL;
            Operande * op2 = NULL;
            Operande * op3 = NULL;
            string * res2 = getNomTempSuivant(tabIdent);
            int tempId = tabIdent->inserer(*res2);
            res->setId(tempId);
            op1 = new Operande(tempId);

            op2 = this->createOperande( tabIdent);
            if( !(this->getCalculee()) )
            {
                res->ajouterSuiteIns(this);
            }

            op3 = ex2->createOperande(tabIdent);
            if( !(ex2->getCalculee()) )
            {
                res->ajouterSuiteIns(ex2);
            }


            switch(comparator)
               {
                  case Operator_eq : res->ajouterIns( new Instruction(OPCODE_EQ, op1, op2, op3)  );
                  break;
                  case Operator_neq : res->ajouterIns( new Instruction(OPCODE_NEQ, op1, op2, op3) );
                  break;
                  default : codeErreur = 2;
                  break;
                }

            res->code.setIdRes( op1->getIdVar());
        }
    }

	return res;
}


Expression * Expression::calculCompReel(Expression* ex2, OperatorComp comparator, int &codeErreur, TabIds * tabIdent)
{
    Expression * res = NULL;
    TypeBooleen * tempType = new TypeBooleen();
	/*
        Dans tout les cas, nous créons un Booleen.
    */
    res = new Expression( tempType );
    delete tempType;
        // On verifie si l'expression est à calculer
        if(this->getCalculee() and ex2->getCalculee())
        {
            bool valRes;
            if(this->get_type()->estDeType(reel))
            {
                double valEx1 = this->getValReel();
                double valEx2 = ex2->getValReel();
                switch(comparator)
                {
                    case Operator_eq : valRes = (valEx1 == valEx2);
                    break;
                    case Operator_neq : valRes = (valEx1 != valEx2);
                    break;
                    case Operator_inf : valRes = (valEx1 < valEx2);
                    break;
                    case Operator_infeq : valRes = (valEx1 <= valEx2);
                    break;
                    case Operator_sup : valRes = (valEx1 > valEx2);
                    break;
                    case Operator_supeq : valRes = (valEx1 >= valEx2);
                    break;
                    default : codeErreur = 2;
                    break;
                }
            }
            res->setValBool(valRes);
            res->setCalculee(true);
        }
        else
        {
            res->setCalculee(false);
            //Generations des operandes
            Operande * op1 = NULL;
            Operande * op2 = NULL;
            Operande * op3 = NULL;
            string * res2 = getNomTempSuivant(tabIdent);;
            res->setCalculee(false);
            int tempId = tabIdent->inserer(*res2);
            res->setId(tempId);
            op1 = new Operande(tempId);

            op2 = this->createOperande( tabIdent);
            if( !(this->getCalculee()) )
            {
                res->ajouterSuiteIns(this);
            }

            op3 = ex2->createOperande(tabIdent);
            if( !(ex2->getCalculee()) )
            {
                res->ajouterSuiteIns(ex2);
            }

            switch(comparator)
                {
                    case Operator_eq : res->ajouterIns( new Instruction(OPCODE_EQ, op1, op2, op3)  );
                    break;
                    case Operator_neq : res->ajouterIns( new Instruction(OPCODE_NEQ, op1, op2, op3)  );
                    break;
                    case Operator_inf : res->ajouterIns( new Instruction(OPCODE_LT, op1, op2, op3)  );
                    break;
                    case Operator_infeq : res->ajouterIns( new Instruction(OPCODE_LE, op1, op2, op3)  );
                    break;
                    case Operator_sup : res->ajouterIns( new Instruction(OPCODE_GT, op1, op2, op3)  );
                    break;
                    case Operator_supeq : res->ajouterIns( new Instruction(OPCODE_GE, op1, op2, op3)  );
                    break;
                    default : codeErreur = 2;
                    break;
                }

            res->code.setIdRes( op1->getIdVar());


        }



    return res;
}

Expression * Expression::calculCompEntier(Expression* ex2, OperatorComp comparator, int &codeErreur, TabIds * tabIdent)
{
   Expression * res = NULL;
   TypeBooleen * tempType = new TypeBooleen();
	/*
        Dans tout les cas, nous créons un Booleen.
    */
   res = new Expression( tempType );
   delete tempType;
        // On verifie si l'expression est à calculer
        if(this->getCalculee() and ex2->getCalculee())
        {
            bool valRes;
            if(this->get_type()->estDeType(reel))
            {
                double valEx1 = this->getValInt();
                double valEx2 = ex2->getValInt();
                switch(comparator)
                {
                    case Operator_eq : valRes = (valEx1 == valEx2);
                    break;
                    case Operator_neq : valRes = (valEx1 != valEx2);
                    break;
                    case Operator_inf : valRes = (valEx1 < valEx2);
                    break;
                    case Operator_infeq : valRes = (valEx1 <= valEx2);
                    break;
                    case Operator_sup : valRes = (valEx1 > valEx2);
                    break;
                    case Operator_supeq : valRes = (valEx1 >= valEx2);
                    break;
                    default : codeErreur = 2;
                    break;
                }
            }
            res->setValBool(valRes);
            res->setCalculee(true);
        }
        else
        {
            res->setCalculee(false);
            //Generations des operandes
            Operande * op1 = NULL;
            Operande * op2 = NULL;
            Operande * op3 = NULL;
            string * res2 = getNomTempSuivant(tabIdent);;
            res->setCalculee(false);
            int tempId = tabIdent->inserer(*res2);
            res->setId(tempId);
            op1 = new Operande(tempId);

            op2 = this->createOperande( tabIdent);
            if( !(this->getCalculee()) )
            {
                res->ajouterSuiteIns(this);
            }

            op3 = ex2->createOperande(tabIdent);
            if( !(ex2->getCalculee()) )
            {
                res->ajouterSuiteIns(ex2);
            }

            switch(comparator)
                {
                    case Operator_eq : res->ajouterIns( new Instruction(OPCODE_EQ, op1, op2, op3)  );
                    break;
                    case Operator_neq : res->ajouterIns( new Instruction(OPCODE_NEQ, op1, op2, op3)  );
                    break;
                    case Operator_inf : res->ajouterIns( new Instruction(OPCODE_LT, op1, op2, op3)  );
                    break;
                    case Operator_infeq : res->ajouterIns( new Instruction(OPCODE_LE, op1, op2, op3)  );
                    break;
                    case Operator_sup : res->ajouterIns( new Instruction(OPCODE_GT, op1, op2, op3)  );
                    break;
                    case Operator_supeq : res->ajouterIns( new Instruction(OPCODE_GE, op1, op2, op3)  );
                    break;
                    default : codeErreur = 2;
                    break;
                }

            res->code.setIdRes( op1->getIdVar());


        }



    return res;
}

//  OPCODE_LT ,      /*        x := y < z          */
//  OPCODE_GT ,      /*        x := y > z          */
//  OPCODE_LE ,      /*        x := y <= z         */
//  OPCODE_GE ,      /*        x := y >= z         */
//  OPCODE_EQ ,      /*        x := y == z         */
//  OPCODE_NEQ ,     /*        x := y != z         */


Expression * Expression::calculComp(Expression* ex2, OperatorComp comparator, int &codeErreur)
{
    //Test egalite des types
    bool valide;

    valide = (this->get_type() == ex2->get_type());

    Expression * res = new Expression();

    // Si pas valide on rend une erreur de comparaison de type
    if(!valide)
    {
        codeErreur = 1;
    }
    else
    {
        // On verifie si l'expression est à calculer
        if(this->getCalculee() and ex2->getCalculee())
        {
            bool valRes;
            if(this->get_type()->estDeType(entier))
            {
                int valEx1 = this->getValInt();
                int valEx2 = ex2->getValInt();
                switch(comparator)
                {
                    case Operator_eq : valRes = (valEx1 == valEx2);
                    break;
                    case Operator_neq : valRes = (valEx1 != valEx2);
                    break;
                    case Operator_inf : valRes = (valEx1 < valEx2);
                    break;
                    case Operator_infeq : valRes = (valEx1 <= valEx2);
                    break;
                    case Operator_sup : valRes = (valEx1 > valEx2);
                    break;
                    case Operator_supeq : valRes = (valEx1 >= valEx2);
                    break;
                    default : codeErreur = 2;
                    break;
                }
            }
            if(this->get_type()->estDeType(reel))
            {
                double valEx1 = this->getValReel();
                double valEx2 = ex2->getValReel();
                switch(comparator)
                {
                    case Operator_eq : valRes = (valEx1 == valEx2);
                    break;
                    case Operator_neq : valRes = (valEx1 != valEx2);
                    break;
                    case Operator_inf : valRes = (valEx1 < valEx2);
                    break;
                    case Operator_infeq : valRes = (valEx1 <= valEx2);
                    break;
                    case Operator_sup : valRes = (valEx1 > valEx2);
                    break;
                    case Operator_supeq : valRes = (valEx1 >= valEx2);
                    break;
                    default : codeErreur = 2;
                    break;
                }
            }
            if(this->get_type()->estDeType(booleen))
            {
                bool valEx1 = this->getValReel();
                bool valEx2 = ex2->getValReel();
                switch(comparator)
                {
                    case Operator_eq : valRes = (valEx1 == valEx2);
                    break;
                    case Operator_neq : valRes = (valEx1 != valEx2);
                    break;
                    default : codeErreur = 2;
                    break;
                }
            }
            res->setValBool(valRes);
            res->setCalculee(true);
        }
        else
        {
            res->setCalculee(false);
        }
    }

    return res;
}



void Expression::ajouterSuiteIns(Expression* expr)
{
    code.add(expr->getCode());
}

