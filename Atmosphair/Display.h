/*************************************************************************
						   Display  -  description
							 -------------------
	d�but                : $DATE$
	copyright            : (C) $YEAR$ par $AUTHOR$
	e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Display> (fichier Display.h) ----------------
#if ! defined ( Display_H )
#define Display_H

//--------------------------------------------------- Interfaces utilis�es
#include <ctime>
#include "DataSet.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// R�le de la classe <Display>
//
//
//------------------------------------------------------------------------

class Display
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- M�thodes publiques
		// type M�thode ( liste des param�tres );
		// Mode d'emploi :
		//
		// Contrat :
		//
	
	void ShowMenuPrincipal();
	// Mode d'emploi :
	//
	// Contrat :
	//

	void ShowChargementFichiers();
	// Mode d'emploi :
	//
	// Contrat :
	//

	void ShowMenu2();
	// Mode d'emploi :
	//
	// Contrat :
	//

	void ShowZoneIndiceAtmoJournee(); //peut etre pas trop utile

	void ShowMenu3();

	void ShowValues(DataSet d); 

	void ShowMenu3MessageChoix();

	void ShowMenu4();

	void ShowMenuInspectionZone(); 

	void ShowMenu4SelectionSeuil(int substance);

	time_t incrementDate(time_t t1, time_t t2);

	time_t getDate();

	//------------------------------------------------- Surcharge d'op�rateurs


//-------------------------------------------- Constructeurs - destructeur
	Display(const Display & unDisplay);
	// Mode d'emploi (constructeur de copie) :
	//
	// Contrat :
	//

	Display();
	// Mode d'emploi :
	//
	// Contrat :
	//

	virtual ~Display();
	// Mode d'emploi :
	//
	// Contrat :
	//

//------------------------------------------------------------------ PRIVE

protected:
	//----------------------------------------------------- M�thodes prot�g�es

	//----------------------------------------------------- Attributs prot�g�s

};

//-------------------------------- Autres d�finitions d�pendantes de <Display>

#endif // Display_H

