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
	cout << "--------------------------------------------------------------------"<<endl;
	cout << "Bienvenue chez Atmosph'Air!"<<endl;
	cout << "Tapez [n] pour choisir une action:"<<endl;
	cout << "0-Charger de nouveaux fichiers."<<endl;
	cout << "1-Visualiser les capteur dysfonctionnants."<<endl;
	cout << "2-Inspecter une zone."<<endl;
	cout << "3-Interroger un capteur."<<endl;
	cout << "4-Visualiser les zones a risque."<<endl;
	cout << "5-Visualiser les similarites detectees par notre algorithme"<<endl;
	cout << "6-Quitter."<<endl;
	cout << "--------------------------------------------------------------------"<<endl;



}

void Display::ShowChargementFichiers()
{
	cout << "--------------------------------------------------------------------"<<endl;
	cout << "Quels fichiers souhaitez-vous qu'Atmosph'Air utilise? Rentrez leurs noms (extension incluse), rentrer 0 pour ne pas modifier le chemin, et appuyez sur entree."<<endl;
	cout << "Attention : "<<endl ;
	cout <<" \t- Les donnees precedemment utilisees seront ecrasees"<<endl;
	cout << "\t- Seul les fichiers au format csv sont autorises."<<endl;
	
}

void Display::ShowMenuInspectionZone()
{
	cout << "--------------------------------------------------------------------"<<endl;
	cout << "Que souhaitez-vous savoir sur cette zone?"<<endl;
	cout << "1-Indice Atmo dans une journee."<<endl;
	cout << "2-Indice Atmo entre t1 et t2."<<endl;
	cout << "3-Taux moyen de substances dans une journee."<<endl;
	cout << "4-Revenir au menu principal."<<endl;
}

void Display::ShowZoneIndiceAtmoJournee() //sert a pas grand chose
{
	cout << "--------------------------------------------------------------------"<<endl;
	cout << "2.1 Indice Atmo dans une journee."<<endl;
	cout << "Veuillez entrer la date souhaitee [yyyy - MM - dd] : "<<endl;
	
}

void Display::ShowMenu3()
{
	cout << "--------------------------------------------------------------------"<<endl;
	cout << "3 - Interroger un capteur"<<endl;
	cout << "Tapez[n] pour selectionner l'action."<<endl;
	cout << "1 - Afficher la liste des capteurs existants."<<endl;
	cout << "2 - Interroger directement un capteur par son identifiant."<<endl;
	cout << "3 - Retour au menu principal."<<endl;
}

void Display::ShowMenu3MessageChoix()
{
	cout << "Si vous souhaitez obtenir les valeurs issus d'une période précise," <<endl
		<< "veuillez preciser une date de debut et une date de fin dans les champs ci-dessous."<<endl
		<< "Sinon, laissez-les vide et tapez entree (return)."<<endl;
}

void Display::ShowMenu4()
{
	cout << "--------------------------------------------------------------------"<<endl;
	cout << "4-Visualiser les zones a risque."<<endl;
	cout << "Quel facteur souhaitez - vous examiner ?"<<endl;
	cout << "1 - Indice ATMO"<<endl;
	cout << "2 - Taux de O3"<<endl;
	cout << "3 - Taux de SO2"<<endl;
	cout << "4 - Taux de NO2"<<endl;
	cout << "5 - Taux de PM10"<<endl;
	cout << "6 - Revenir au menu principal."<<endl;

}

void Display::ShowMenu4SelectionSeuil(int substance)
{
	switch (substance)
	{
	case 1:
		cout << "4.1-Indice ATMO"<<endl;
		break;
	case 2: 
		cout << "2-Taux de O3"<<endl;
		break;
	case 3 :
		cout << "3-Taux de SO2"<<endl;
		break;
	case 4 :
		cout << "4-Taux de NO2"<<endl;
		break;
	case 5 :
		cout << "5-Taux de PM10"<<endl;
		break;
	default:
		break;
	}
	cout<< "Veuillez entrer la valeur seuil souhaitee pour le facteur semalectionne :";
}

time_t Display::getDate() {
	struct tm date;
	unsigned int tmp;
	cout << "Entrer l'année souhaitée : ";
	cin >> tmp;
	date.tm_year = tmp - 1900;

	cout << "Entrer le mois souhaitée : ";
	cin >> tmp;
	date.tm_mon = tmp - 1 ;

	cout << "Entrer le jour souhaitée : ";
	cin >> tmp;
	date.tm_mday = tmp;

	date.tm_hour = 0;
	date.tm_min = 0;
	date.tm_sec = 0;
	time_t temps = mktime(&date);
	return temps;
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

