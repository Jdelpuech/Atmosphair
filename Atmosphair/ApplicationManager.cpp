/**************************************************************************************
 ApplicationManager  -  Réalisation
 -------------------
 début                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air
 
 ***************************************************************************************/

//-- Réalisation de la classe <ApplicationManager> (fichier ApplicationManager.cpp) ----

//------------------------------------------------------------------------------ INCLUDE
//---------------------------------------------------------------------- Include système
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

//--------------------------------------------------------------------- Include personnel
#include "Display.h"

//-------------------------------------------------------------------------------- PUBLIC
int main(){

	Display myDisplay;
	int navigation;
	string login, pwd;
	string fileSensor, fileMeasure, fileLinks;
	string inspectionZone, selFonction;

	cout << "---------------------------------------------------------------------";
	cout << "Bienvenue chez Atmosph'Air!Afin d’obtenir l'accès à nos services, veuillez vous authentifier.";
	cout << "Login : ";
	cin >> login;
	cout << "Mot de passe : ";
	cin >> pwd;

	myDisplay.AfficherMenuPrincipal();
	cin >> navigation;
	
	switch ((int)navigation)
	{
	case 0 :
		// Chargement de fichiers
		myDisplay.AfficherChargementFichiers();
		cout << "Fichiers relatifs aux capteurs: ";
		cin >> fileSensor;
		cout << "Fichiers relatifs aux mesures : ";
		cin >> fileMeasure;
		cout << "Fichiers de lien : ";
		cin >> fileLinks;
		cout << "Merci! Bon travail!";

		// Charger les fichiers correspondants


		break;
	case 1:
		// Affichage des capteurs disfonctionnants

		break;
	case 2:
		// Inspection d'une zone
		cout << "2-Inspecter une zone.";
		cout << "Veuillez sélectionner la zone. Une zone se définit par les coordonnées d’un point GPS sous le format lat;long;rayon : ";
		cin >> inspectionZone;
		myDisplay.AfficherMenuInspectionZone();
		cin >> selFonction;

		break;
	case 3:

		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	default:
		break;
	}
	

	return 0; 
}
