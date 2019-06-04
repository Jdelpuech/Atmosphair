/*************************************************************************
						   Display  -  description
							 -------------------
	debut                : $DATE$
	copyright            : (C) $YEAR$ par $AUTHOR$
	e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Display> (fichier Display.h) ----------------
#if ! defined ( Display_H )
#define Display_H

//--------------------------------------------------- Interfaces utilisees
#include <ctime>
#include "DataSet.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rele de la classe <Display>
//
//
//------------------------------------------------------------------------

class Display
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Methodes publiques
		// type Methode ( liste des parametres );
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

	void ShowValues(DataSet d,time_t t1, time_t t2,Sensor * s); 

	void ShowMenu3MessageChoix();


	void ShowMenuInspectionZone(); 

	void ShowMenu4SelectionSeuil(int substance);

	time_t incrementDate(time_t t1, time_t t2);

	time_t getDate();

	//------------------------------------------------- Surcharge d'operateurs


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
	//----------------------------------------------------- Methodes protegees

	//----------------------------------------------------- Attributs proteges

};

//-------------------------------- Autres definitions dependantes de <Display>

#endif // Display_H

