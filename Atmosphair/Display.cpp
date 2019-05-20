/*************************************************************************
						   Display  -  description
							 -------------------
	début                : $DATE$
	copyright            : (C) $YEAR$ par $AUTHOR$
	e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Display> (fichier Display.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Display.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Display::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void AfficherMenuPrincipal()
{
	cout << "--------------------------------------------------------------------";
	cout << "Bienvenue chez Atmosph’Air!";
	cout << "Tapez [n] pour choisir une action:";
	cout << "0-Charger de nouveaux fichiers.";
	cout << "1-Visualiser les capteur dysfonctionnants.";
	cout << "2-Inspecter une zone.";
	cout << "3-Interroger un capteur.";
	cout << "4-Visualiser les zones à risque.";
	cout << "5-Visualiser les similarités détectées par notre algorithme";
	cout << "6-Quitter.";
	cout << "--------------------------------------------------------------------";



}

void AfficherChargementFichiers() 
{
	cout << "Quels fichiers souhaitez-vous qu’Atmosph’Air utilise? Rentrez leurs noms (extension incluse), séparés par des points-virgules et appuyez sur entrée.";
	cout << "Attention : \t- Les données précédemment utilisées seront écrasées";
	cout << "\t- Seul les fichiers .csv sont autorisés.";
	
}

void AfficherMenuInspectionZone()
{
	cout << "Que souhaitez-vous savoir sur cette zone?";
	cout << "1-Indice Atmo dans une journée.";
	cout << "2-Indice Atmo entre t1 et t2.";
	cout << "3-Taux moyen de substances dans une journée.";
	cout << "4-Revenir au menu principal.";
}


//------------------------------------------------- Surcharge d'opérateurs
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

//----------------------------------------------------- Méthodes protégées

