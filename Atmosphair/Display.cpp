/*************************************************************************
						   Display  -  description
							 -------------------
	d�but                : $DATE$
	copyright            : (C) $YEAR$ par $AUTHOR$
	e-mail               : $EMAIL$
*************************************************************************/

//---------- R�alisation de la classe <Display> (fichier Display.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Display.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques
// type Display::M�thode ( liste des param�tres )
// Algorithme :
//
//{
//} //----- Fin de M�thode

void AfficherMenuPrincipal()
{
	cout << "--------------------------------------------------------------------";
	cout << "Bienvenue chez Atmosph�Air!";
	cout << "Tapez [n] pour choisir une action:";
	cout << "0-Charger de nouveaux fichiers.";
	cout << "1-Visualiser les capteur dysfonctionnants.";
	cout << "2-Inspecter une zone.";
	cout << "3-Interroger un capteur.";
	cout << "4-Visualiser les zones � risque.";
	cout << "5-Visualiser les similarit�s d�tect�es par notre algorithme";
	cout << "6-Quitter.";
	cout << "--------------------------------------------------------------------";



}

void AfficherChargementFichiers() 
{
	cout << "Quels fichiers souhaitez-vous qu�Atmosph�Air utilise? Rentrez leurs noms (extension incluse), s�par�s par des points-virgules et appuyez sur entr�e.";
	cout << "Attention : \t- Les donn�es pr�c�demment utilis�es seront �cras�es";
	cout << "\t- Seul les fichiers .csv sont autoris�s.";
	
}

void AfficherMenuInspectionZone()
{
	cout << "Que souhaitez-vous savoir sur cette zone?";
	cout << "1-Indice Atmo dans une journ�e.";
	cout << "2-Indice Atmo entre t1 et t2.";
	cout << "3-Taux moyen de substances dans une journ�e.";
	cout << "4-Revenir au menu principal.";
}


//------------------------------------------------- Surcharge d'op�rateurs
Display & Display::operator = (const Display & unDisplay)
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Display::Display(const Display & unDisplay)
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au constructeur de copie de <Display>" << endl;
#endif
} //----- Fin de Display (constructeur de copie)


Display::Display()
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au constructeur de <Display>" << endl;
#endif
} //----- Fin de Display


Display::~Display()
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au destructeur de <Display>" << endl;
#endif
} //----- Fin de ~Display


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes prot�g�es

