/*************************************************************************
						   Display  -  description
							 -------------------
	debut                : $DATE$
	copyright            : (C) $YEAR$ par $AUTHOR$
	e-mail               : $EMAIL$
*************************************************************************/

//---------- Realisation de la classe <Display> (fichier Display.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
#include <iostream>
#include <vector>
#include <list>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Display.h"
#include "Sensor.h"
#include "Data.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques
// type Display::Methode ( liste des parametres )
// Algorithme :
//
//{
//} //----- Fin de Methode

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
void Display::ShowValues(DataSet d, time_t t1, time_t t2, Sensor * s){
	struct tm format_t1 = *localtime(&t1);
	struct tm format_t2 = *localtime(&t2);
	cout <<"======================Donnees du capteur["<<s->getSensorID()<<"] ================================="<<endl ; 
	cout <<"Statistiques correspondant a la periode "<<format_t1.tm_mday<<"-"<<format_t1.tm_mon+1<<"-"
	<<format_t1.tm_year+1900<<" a "<<format_t2.tm_mday<<"-"<<format_t2.tm_mon+1<<"-"
	<<format_t2.tm_year+1900<<endl ; 
	cout<<s->toString() <<endl ; 
	listSensor liste; 
	liste.push_back(s); 
	list<int> valeurs = d.generateResultAtmo(liste,t1,t2); 
	if (valeurs.size()<10){
		cout<<valeurs.size()<<" derniers indices ATMO : ["; 
	}
	else {
		cout<<"10 derniers indices ATMO : ["; 
	}
	list<int>::iterator it ; 
	it = valeurs.begin(); 
	int moyenne = 0 ; 
	int nbr = 0 ; 
	int max = -1 ; 
	int min = 11 ;
	while (it!=valeurs.end()){

		cout << (*it);//<<(it++==valeurs.end() ? "|" : "") ; 
		//it-- ; 
		if ((*it)<min){
			min = (*it);
		}
		if ((*it)>max){
			max = (*it); 
		}
		moyenne += (*it); 
		nbr++; 
		it++;
		if (it != valeurs.end()) {
			cout << "|";
		}
	}
	cout<<"] -> moyenne : "<< moyenne/valeurs.size() <<" min : "<< min <<" max : "<< max << endl<<endl ; 

	vector<Data*> values = d.generateResultGas(s,t1,t2); 
	cout << "derniers indice par molecule (max 10 valeurs par molecule)" << endl;

	string resultSO2 = "";
	string resultNO2 = "";
	string resultO3 = "";
	string resultPM10 = "";

	float minV = 1000;
	float maxV = -1;
	float minN = 1000;
	float maxN = -1;
  float minO = 1000;
	float maxO = -1;
	float minP = 1000;
	float maxP = -1;
	vector<Data *>::iterator itResultat;
	itResultat = values.begin();
	while (itResultat != values.end()) {
		if ((**itResultat).getDataTypeId().compare("SO2") == 0) {
			resultSO2 += to_string((**itResultat).getValue())+"|" ;
			if ((**itResultat).getValue() < minV)
				minV = (**itResultat).getValue();
			if ((**itResultat).getValue() > maxV) {
				maxV = (**itResultat).getValue();
			}
		}
	
	  if ((**itResultat).getDataTypeId().compare("O3") == 0) {
			resultO3 += to_string((**itResultat).getValue())+"|" ;
			if ((**itResultat).getValue() < minO)
				minO = (**itResultat).getValue();
			if ((**itResultat).getValue() > maxO) {
				maxO = (**itResultat).getValue();
			}
		}
		if ((**itResultat).getDataTypeId().compare("PM10") == 0) {
			resultPM10 += to_string((**itResultat).getValue())+"|" ;
			if ((**itResultat).getValue() < minP)
				minP = (**itResultat).getValue();
			if ((**itResultat).getValue() > maxP) {
				maxP = (**itResultat).getValue();
			}
		}

		if ((**itResultat).getDataTypeId().compare("NO2") == 0) {
			resultNO2 += to_string((**itResultat).getValue()) +"|" ;
			if ((**itResultat).getValue() < minN)
				minN = (**itResultat).getValue();
			if ((**itResultat).getValue() > maxN) {
				maxN = (**itResultat).getValue();
			}
		}
		itResultat++; 
	}

	resultNO2 = resultNO2.substr(0, resultNO2.size()-1);	
	resultSO2 = resultSO2.substr(0, resultSO2.size()-1);
	resultO3 = resultO3.substr(0, resultO3.size()-1);		
	resultPM10 = resultPM10.substr(0, resultPM10.size()-1);	 

	cout << "SO2 : [" << resultSO2;
	cout << "] -> moyenne : " << s->calculateMoyenneGaz(t1,t2,"SO2") << " min : " << minV << " max : " << maxV << endl ;

	cout << "NO2 : [" << resultNO2;
	cout << "] -> moyenne : " << s->calculateMoyenneGaz(t1,t2,"NO2") << " min : " << minN << " max : " << maxN << endl ;

	

	cout << "NO2 : [" << resultO3;
	cout << "] -> moyenne : " << s->calculateMoyenneGaz(t1,t2,"O3") << " min : " << minO << " max : " << maxO << endl ;

	cout << "PM10 : [" << resultO3;
	cout << "] -> moyenne : " << s->calculateMoyenneGaz(t1,t2,"PM10") << " min : " << minP << " max : " << maxP << endl ;

  cout <<"==============================================================================="<<endl ; 
	
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
	cout << "--------------------------------------------------------------------"<<endl;
	cout << "choix : "; 
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
	cout << "--------------------------------------------------------------------"<<endl;
	cout << "choix : "; 
}

void Display::ShowMenu3MessageChoix()
{
	cout << "Si vous souhaitez obtenir les valeurs issus d'une periode precise," <<endl
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
	cout << "--------------------------------------------------------------------"<<endl;
	cout << "choix : " ; 

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
	cout << "Entrer l'annee souhaitee : ";
	cin >> tmp;
	date.tm_year = tmp - 1900;

	cout << "Entrer le mois souhaitee : ";
	cin >> tmp;
	date.tm_mon = tmp - 1 ;

	cout << "Entrer le jour souhaitee : ";
	cin >> tmp;
	date.tm_mday = tmp;

	date.tm_hour = 0;
	date.tm_min = 0;
	date.tm_sec = 0;
	time_t temps = mktime(&date);
	return temps;
}

time_t Display::incrementDate(time_t t1, time_t t2){

	struct tm format_t1 = *localtime(&t1);
	if (difftime(t2,t1)>0){
               if (format_t1.tm_mday!=31)
                 format_t1.tm_mday += 1 ;
               else {
                   format_t1.tm_mday = 0 ;
                   if (format_t1.tm_mon!=11){
                      format_t1.tm_mon += 1;
                   }
                   else {
                       format_t1.tm_mon = 0 ;
                       format_t1.tm_year +=1;
                   }
            }
            t1 = mktime(&format_t1); 
        }
	return t1; 

}
//------------------------------------------------- Surcharge d'operateurs

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

//----------------------------------------------------- Methodes protegees

