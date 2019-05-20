/*************************************************************************
						   Display  -  description
							 -------------------
	début                : $DATE$
	copyright            : (C) $YEAR$ par $AUTHOR$
	e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Display> (fichier Display.h) ----------------
#if ! defined ( Display_H )
#define Display_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Display>
//
//
//------------------------------------------------------------------------

class Display
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Méthodes publiques
		// type Méthode ( liste des paramètres );
		// Mode d'emploi :
		//
		// Contrat :
		//

	void AfficherMenuPrincipal();
	// Mode d'emploi :
	//
	// Contrat :
	//

	void AfficherChargementFichiers();
	// Mode d'emploi :
	//
	// Contrat :
	//

	void AfficherMenuInspectionZone();
	// Mode d'emploi :
	//
	// Contrat :
	//



	//------------------------------------------------- Surcharge d'opérateurs
	Display & operator = (const Display & unDisplay);
	// Mode d'emploi :
	//
	// Contrat :
	//


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
	//----------------------------------------------------- Méthodes protégées

	//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Display>

#endif // Display_H

