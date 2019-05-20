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



	//------------------------------------------------- Surcharge d'op�rateurs
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
	//----------------------------------------------------- M�thodes prot�g�es

	//----------------------------------------------------- Attributs prot�g�s

};

//-------------------------------- Autres d�finitions d�pendantes de <Display>

#endif // Display_H

