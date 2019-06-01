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

void Display::ShowMenuPrincipal()
{
	cout << "--------------------------------------------------------------------";
	cout << "Bienvenue chez Atmosph'Air!";
	cout << "Tapez [n] pour choisir une action:";
	cout << "0-Charger de nouveaux fichiers.";
	cout << "1-Visualiser les capteur dysfonctionnants.";
	cout << "2-Inspecter une zone.";
	cout << "3-Interroger un capteur.";
	cout << "4-Visualiser les zones a risque.";
	cout << "5-Visualiser les similarites detectees par notre algorithme";
	cout << "6-Quitter.";
	cout << "--------------------------------------------------------------------";



}

void Display::ShowChargementFichiers()
{
	cout << "Quels fichiers souhaitez-vous qu'Atmosph'Air utilise? Rentrez leurs noms (extension incluse), separes par des points-virgules et appuyez sur entree.";
	cout << "Attention : \t- Les donnees precedemment utilisees seront ecrasees";
	cout << "\t- Seul les fichiers .csv sont autorises.";
	
}

void Display::ShowMenuInspectionZone()
{
	cout << "Que souhaitez-vous savoir sur cette zone?";
	cout << "1-Indice Atmo dans une journee.";
	cout << "2-Indice Atmo entre t1 et t2.";
	cout << "3-Taux moyen de substances dans une journee.";
	cout << "4-Revenir au menu principal.";
}

void Display::ShowZoneIndiceAtmoJournee() //sert a pas grand chose
{
	cout << "2.1 Indice Atmo dans une journee.";
	cout << "Veuillez entrer la date souhaitee [yyyy - MM - dd] : ";
	
}

void Display::ShowMenu3()
{
	cout << "3 - Interroger un capteur";
	cout << "Tapez[n] pour selectionner l'action.";
	cout << "1 - Afficher la liste des capteurs existants.";
	cout << "2 - Interroger directement un capteur par son identifiant.";
	cout << "3 - Retour au menu principal.";
}

void Display::ShowMenu3MessageChoix()
{
	cout << "Si vous souhaitez obtenir les valeurs issus d'une période précise,"
		<< "veuillez preciser une date de debut et une date de fin dans les champs ci-dessous."
		<< "Sinon, laissez-les vide et tapez entree (return).";
}

void Display::ShowMenu4()
{
	cout << "4-Visualiser les zones a risque.";
	cout << "Quel facteur souhaitez - vous examiner ?";
	cout << "1 - Indice ATMO";
	cout << "2 - Taux de O3";
	cout << "3 - Taux de SO2";
	cout << "4 - Taux de NO2";
	cout << "5 - Taux de PM10";
	cout << "6 - Revenir au menu principal.";

}

void Display::ShowMenu4SelectionSeuil(int substance)
{
	switch (substance)
	{
	case 1:
		cout << "4.1-Indice ATMO";
		break;
	case 2: 
		cout << "2-Taux de O3";
		break;
	case 3 :
		cout << "3-Taux de SO2";
		break;
	case 4 :
		cout << "4-Taux de NO2";
		break;
	case 5 :
		cout << "5-Taux de PM10";
		break;
	default:
		break;
	}
	cout<< "Veuillez entrer la valeur seuil souhaitee pour le facteur semalectionne :";
}

//------------------------------------------------- Surcharge d'op�rateurs

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

