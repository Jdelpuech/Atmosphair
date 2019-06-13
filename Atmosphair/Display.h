/*************************************************************************
						   Display  -  interface
							 -------------------
 debut                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
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
// Role de la classe <Display>
//enveloppe toutes les methodes d'affichages du menu principal
//d'Atmosph'Air
//------------------------------------------------------------------------

class Display
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Methodes publiques

	void ShowMenuPrincipal();
	// Mode d'emploi : aucun
	// Contrat : aucun
	

	void ShowChargementFichiers();
	// Mode d'emploi : aucun
	// Contrat : aucun 

	void ShowMenu2();
	// Mode d'emploi : aucun
	// Contrat : aucun 


	void ShowMenu3();
	// Mode d'emploi : aucun
	// Contrat : aucun 

	void ShowValues(DataSet d,time_t t1, time_t t2,Sensor * s); 
	// Mode d'emploi : aucun
	// Contrat : aucun 

	void ShowMenu3MessageChoix();
	// Mode d'emploi : aucun
	// Contrat : aucun 

	void ShowMenuInspectionZone(); 
	// Mode d'emploi : aucun
	// Contrat : aucun 

	void ShowMenu4SelectionSeuil(int substance);
	// Mode d'emploi : aucun
	// Contrat : aucun 

	time_t incrementDate(time_t t1, time_t t2);
	// Mode d'emploi : incrémente la date t1 jusqu'a arriver a la date t2
	// Contrat : t1 est une date précédent t2 

	time_t getDate();
	// Mode d'emploi : aucun
	// Contrat : aucun 

	//------------------------------------------------- Surcharge d'operateurs


//-------------------------------------------- Constructeurs - destructeur
	Display(const Display & unDisplay);
	// Mode d'emploi (constructeur de copie) : aucun
	//
	// Contrat : aucun
	//

	Display();
	// Mode d'emploi : aucun
	//
	// Contrat : aucun
	//

	virtual ~Display();
	// Mode d'emploi : aucun
	//
	// Contrat : aucun
	//

//------------------------------------------------------------------ PRIVE

protected:
	//----------------------------------------------------- Methodes protegees

	//----------------------------------------------------- Attributs proteges

};

//-------------------------------- Autres definitions dependantes de <Display>

#endif // Display_H

