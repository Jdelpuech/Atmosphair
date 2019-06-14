/**************************************************************************************
 ApplicationManager  -  Realisation
 -------------------
 debut                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air
 
 ***************************************************************************************/

//-- Realisation de la classe <ApplicationManager> (fichier ApplicationManager.cpp) ----

//------------------------------------------------------------------------------ INCLUDE
//---------------------------------------------------------------------- Include systeme
#include <iostream>
#include <string>
#include <ctime>
#include <regex>

using namespace std;

//--------------------------------------------------------------------- Include personnel
#include "ApplicationManager.h"
#include "FileManager.h"
#include "Sensor.h"
#include "User.h"
#include "DataType.h"
#include "Data.h"
#include "Display.h"
#include "LogManager.h"
#include "DataSet.h"	

//-------------------------------------------------------------------------------- PUBLIC
bool ApplicationManager::init(DataSet * d, FileManager * fm) {
	(*fm).openSave(d);
	User * user_1 = new User("user", "123", "user Atmosph'air");
	(*d).addUser(user_1);
	return true;
}

int main() {
	DataSet dataSet; 
	FileManager fm;
	Display myDisplay;

	User * user=nullptr;
	
	char choice;

	 
	float latitude,longitude,rayon; 
	
	char entree = 'a';
	
	
	listSensor listeSensor ; 
	listSensor::iterator itSensor; 
	listData listeData ; 
	listData::iterator itData ;
	list<pair<Sensor *, Sensor *> > sensorPair;
	list<pair<Sensor *, Sensor *> >::iterator itPairSensor;
	list<int> valeursI;
	list<int>::iterator it_valI;
	list<float> valeursF;
	list<float>::iterator it_valF;
	vector<float> resultsGaz ;

	bool valid, connection=false;
	string s_tmp1="", s_tmp2="", choix="",s_sousMenu="",s_capteur="";
	string lat, lon, r;
	time_t date1, date2;
	int navigation = 0, sousMenu = 0, seuil = 0, atmo=0;
	int i_tmp = 0, nbr=0;
	float moyenne = 0.;
	char c_tmp = 'a',back = 'a'; 

	regex patternCSV(".*\\.csv$");
	regex pattern0_6("[0-6]");
	regex pattern1_4("[1-4]");
	regex pattern1_3("[1-3]");
	regex pattern1_2("[1-2]");
	regex patternOuiNon("oui|non");
	regex patternSensor("Sensor[0-9]+");
	regex patternLess10("[0-9]|10");

	if(regex_match("sensor88", patternSensor)){
		cout << "ok" << endl;
	}

	ApplicationManager::init(&dataSet, &fm);

	while (!connection){
		cout << "---------------------------------------------------------------------"<<endl; ;
		cout << "Bienvenue chez Atmosph'Air! Afin d'obtenir l'acces a nos services," <<endl ;
		cout <<"veuillez vous authentifier."<<endl;
		cout << "Login : ";
		cin >> s_tmp1;
		cout << "Mot de passe : ";
		cin >> s_tmp2;
		user = dataSet.connectionRequest(s_tmp1, s_tmp2);
		if (user!=nullptr){
			connection = true ; 
		} else {
			cout<<"Erreur : veuillez reessayer."<<endl; 
		} 

	}

	LogManager lm(user);
	lm.writeLog("Connection de " + user->getNom());

	//inutile en l'etat actuelle
	valid = false; 


	//si l'utilisatuer entre 6, il souhaite quitter l'application
	while (navigation != 6)
	{
		//on affiche a nouveau le menu principal
		myDisplay.ShowMenuPrincipal();
		cin >> s_tmp1;
		while (!regex_match(s_tmp1, pattern0_6)) {
			cout << "Veuillez entrer une valeur entre 0 et 6 : ";
			cin >> s_tmp1;
		}
		navigation = stoi(s_tmp1);
		switch (navigation)
		{
		case 0:
			// Chargement de fichiers
			myDisplay.ShowChargementFichiers();
			capteur:
			cout << "Fichier relatif aux capteurs: ";
			cin >> s_tmp1;
			if (s_tmp1 != "0") {
				if (regex_match(s_tmp1, patternCSV)&& fm.save(&dataSet, s_tmp1, 0)) {
					lm.writeLog("modification sauvegarde capteurs : " + s_tmp1);
				}
				else {
					cout << "mauvais format" << endl;
					goto capteur;
				}
			}
			measure:
			cout << "Fichier relatif aux mesures : ";
			cin >> s_tmp1;
			if (s_tmp1 != "0") {
				if (regex_match(s_tmp1, patternCSV) && fm.save(&dataSet, s_tmp1, 1)) {
					lm.writeLog("modification sauvegarde mesures : " + s_tmp1);
				}
				else {
					cout << "mauvais format" << endl;
					goto measure;
				}
			}
			link:
			cout << "Fichier relatif au type de mesures : ";
			cin >> s_tmp1;
			if (s_tmp1 != "0") {
				if (regex_match(s_tmp1, patternCSV)&& fm.save(&dataSet, s_tmp1, 2)) {
					lm.writeLog("modification sauvegarde type de mesures : " + s_tmp1);
				}
				else {
					cout << "mauvais format" << endl;
					goto link;
				}
			}
			cout << "Merci! Bon travail!"<<endl;

			// Charger les fichiers correspondants

			break;
		case 1:
			// Affichage des capteurs disfonctionnants : appel de la methode correspondante
			listeSensor = dataSet.getListDysfonctionningSensors(); 
			itSensor = listeSensor.begin(); 
			cout << "--------------------------------------------------------------------"<<endl;
			while(itSensor!=listeSensor.end()){
				cout <<"IDCapteur : "<<(**itSensor).getSensorID()<<" | Dysfonctionnement : "; 
				if ((**itSensor).dysfonction()==1){
					cout<<"periode d'echantillonage depassee"; 
				}else if ((**itSensor).dysfonction()==2){
					cout<<"Donnees incoherentes"; 
				}else if ((**itSensor).dysfonction()==3){
					cout<<"Donnees manquantes";
				}
				cout << endl ; 
				++itSensor ; 
			}

			lm.writeLog("Affichage des capteurs disfonctionnants");

			cout << "Appuyez sur enter pour revenir au menu principal." << endl;
			cin.get();
			cin.get();
			break;
		case 2:
			// Inspection d'une zone
			valid = false;
			while (!valid) {
				cout << "--------------------------------------------------------------------" << endl;
				cout << "2-Inspecter une zone." << endl;
				cout << "Veuillez selectionner la zone. Une zone se definit par les coordonnees d'un point GPS  " << endl;
				cout << "et d'un rayon. " << endl;
				cout << "Latitude : ";
				cin >> lat;
				cout << "Longitude : ";
				cin >> lon;
				cout << "Rayon (km) :";
				cin >> r;

				try {
					latitude = stod(lat);
					longitude = stod(lon);
					rayon = stod(r);
					valid = true;
				}
				catch (const std::invalid_argument) {
					cerr << "argument(s) invalide(s) : reessayez" << "\n";
				}
			}

			listeSensor = dataSet.getListSensorsInZone(latitude, longitude, rayon);
			while (sousMenu != 4)
			{
				myDisplay.ShowMenuInspectionZone();
				cin >> s_sousMenu;
				while (!regex_match(s_sousMenu, pattern1_4)) {
					cout << "Veuillez entrer une valeur entre 1 et 4 : " ;
					cin >> s_sousMenu;
				}
				sousMenu = stoi(s_sousMenu);
				//on a selectionne l'action que l'on souhaite effectuer sur la zone
				//si selFonction est 4, l'utilisateur souhiate revenir au ùenu principal
			
				switch (sousMenu)
				{
				case 1:
					//la date est demandee a l'utilisateur
					cout << "--------------------------------------------------------------------"<<endl;
					cout << "2.1 Indice Atmo dans une journee."<<endl;
					cout << "Veuillez entrer la date souhaitee. "<<endl;
					date1 = myDisplay.getDate();
					valeursI.clear();
					valeursI = dataSet.generateResultAtmo(listeSensor,date1) ; 

					it_valI = valeursI.begin() ; 
					moyenne = 0 ; 
					nbr = 0 ; 
					while(it_valI!=valeursI.end()){
						moyenne+=(*it_valI); 
						nbr++ ; 
						it_valI++; 
					}
					if (nbr!=0)
						moyenne = (float) (moyenne/(float)nbr) ; 
					cout <<"indice ATMO :"<< moyenne <<endl ;
					s_tmp1 = ctime(&date1);
					s_tmp1.erase(s_tmp1.size() - 1);
					lm.writeLog("Consultation indice Atmo dans une journee des capteur de la zone " + lat + ":" + lon + "/" + r + " date : " + s_tmp1);
					break;
				case 2:
					cout << "--------------------------------------------------------------------"<<endl;
					cout << "2.2-Indice Atmo moyen entre t1 et t2."<<endl;
					cout << "Veuillez entrer la premiere date. "<<endl;
					//recuperation des 2 dates
					date1 = myDisplay.getDate();
					cout << "Veuillez entrer la deuxieme date. "<<endl;
					date2 = myDisplay.getDate();
					

					//Appel de la methode correspondante
					
					valeursF.clear();
					valeursF = dataSet.generateResultAtmo(listeSensor,date1,date2); 
					it_valF = valeursF.begin() ; 
					moyenne = 0 ; 
					nbr = 0 ; 
					while(it_valF!=valeursF.end()){
						moyenne+=(*it_valF); 
						nbr++ ; 
						it_valF++; 
					}
					if (nbr!=0)
						moyenne = (float) (moyenne/(float)nbr) ; 
					cout <<"Moyenne des indices ATMO sur la periode :"<< moyenne << endl ; 
					cout << "Souhaitez vous visualiser toutes les valeurs de l'indice ATMO dans l'intervalle choisi? oui/non."<<endl;
					cin >> choix;
					while (!regex_match(choix,patternOuiNon))
					{
						cout << "Veuillez entrer oui ou non"<<endl;
						cin >> choix;
					}
					if (choix == "oui")
					{
						it_valF = valeursF.begin();
						itSensor = listeSensor.begin();
						while (it_valF!=valeursF.end())
						{
							struct tm format_t1 = *localtime(&date1);
							cout << (**itSensor).getSensorID()<<" | ATMO : "<< (*it_valF)<<endl ; 
							++it_valF; 
							date1 = myDisplay.incrementDate(date1,date2); 
						}

					}
					s_tmp1 = ctime(&date1);
					s_tmp1.erase(s_tmp1.size() - 1);
					s_tmp2 = ctime(&date1);
					s_tmp2.erase(s_tmp2.size() - 1);
					lm.writeLog("Consultation indice Atmo des capteur de la zone " + lat + ":" + lon + "/" + r + " entre le : " + s_tmp1+" et le : "+ s_tmp2);
					break;

				case 3 :
					cout << "--------------------------------------------------------------------"<<endl;
					cout << "2.3-Taux moyen de substances dans une journee"<<endl;
					cout << "Veuillez entrer la date souhaitee : "<<endl;
					date1 = myDisplay.getDate();
					cout << "Veuillez choisir parmis les choix  :  1- O3 |  2- SO2 | 3- NO2 | 4- PM10"<<endl;
					cout << "Pour visualiser plusieurs taux, veuillez concatener les chiffres."<<endl;
					cout << "Exemple : 134"<< endl;
					cout << "Choix : ";
					cin >> choix;
					//Appel a la methode de calcul du taux moyen de chaque substance
					resultsGaz = dataSet.generateResultGas(listeSensor,date1,choix); 
					
					if (resultsGaz[0]!=0){
						cout << "Taux moyen de O3 dans la journee : "<<resultsGaz[0]<<endl ; 
					}
					if (resultsGaz[1]!=0){
						cout << "Taux moyen de SO2 dans la journee : "<<resultsGaz[1]<<endl ; 
					}
					if (resultsGaz[2]!=0){
						cout << "Taux moyen de NO3 dans la journee : "<<resultsGaz[2]<<endl ; 
					}
					if (resultsGaz[3]!=0){
						cout << "Taux moyen de PM10 dans la journee : "<<resultsGaz[3]<<endl ; 
					}
					s_tmp1 = ctime(&date1);
					s_tmp1.erase(s_tmp1.size() - 1);
					lm.writeLog("Consultation taux moyen de substances ("+choix+") dans une journee des capteur de la zone " + lat + ":" + lon + "/" + r + " date : " + s_tmp1);
					break;
				default:
					break;
				}//fin du switch du menu Zone
				if (sousMenu != 4) {
					cout << "Appuyez sur enter pour revenir au menu precedent." << endl;
					cin.get();
					cin.get();
				}
			}//on quitte le menu "Zone"
			sousMenu = 0;
			break;
		case 3: //interroger un capteur
			myDisplay.ShowMenu3();
			cin >> s_sousMenu;
			while (!regex_match(s_sousMenu, pattern1_3)) {
				cout << "Veuillez entrer une valeur entre 1 et 3 : ";
				cin >> s_sousMenu;
			}
			sousMenu = stoi(s_sousMenu);
            if (sousMenu ==3){
				break ; 
			}
			if (sousMenu == 1 )
			{
				//Affichage de la liste des capteurs existants
				cout << "SensorID | Latitude | Longitude | Description"<<endl ; 
				listeSensor.clear(); 
				listeSensor = dataSet.getListSensors(); 
				itSensor = listeSensor.begin() ; 
				while (itSensor!=listeSensor.end()){
					cout<<(**itSensor).toString() << endl ; 
					itSensor++; 
				}

			}
             
			cout << "Veuillez saisir l'ID du capteur souhaite (ex. Sensor9) : ";
			cin >> s_capteur;
			while (!regex_match(s_capteur, patternSensor)) {
				cout << "Veuillez saisir l'ID du capteur souhaite (ex. Sensor9) : " ;
				cin >> s_capteur;
			}
			myDisplay.ShowMenu3MessageChoix();
			cin >> s_tmp1;
			while (!regex_match(s_tmp1, pattern1_2)) {
				cout << "Veuillez entrer une valeur entre 1 et 2 : ";
				cin >> s_tmp1;
			}
			if (stoi(s_tmp1) == 2) {
				cout << endl << "Saisissez une date de debut. " << endl;
				date1 = myDisplay.getDate();
				cout << endl << "Saisissez une date de fin. " << endl;
				date2 = myDisplay.getDate();
				if (difftime(date1, date2) != 0)
				{
					myDisplay.ShowValues(dataSet, date1, date2, dataSet.getSensorById(s_capteur));
					cout << "Appuyez sur enter pour revenir au menu precedent " << endl;
					cin.get();
					cin.get();
					s_tmp1 = ctime(&date1);
					s_tmp1.erase(s_tmp1.size() - 1);
					s_tmp2 = ctime(&date1);
					s_tmp2.erase(s_tmp2.size() - 1);
					lm.writeLog("Consultation capteur " + s_tmp1 + "entre le : " + s_tmp1 + " et le : " + s_tmp2);
				}
				else {
					cout << "Vous avez entrez deux fois la même date" << endl;
				}
				
			}
			else {
				cout << endl << "Saisissez une date : " << endl;
				date1 = myDisplay.getDate();
				myDisplay.ShowValues(dataSet, date1, date1, dataSet.getSensorById(s_capteur));
				cout << "Appuyez sur enter pour revenir au menu precedent " << endl;
				cin.get();
				cin.get();
				s_tmp1 = ctime(&date1);
				s_tmp1.erase(s_tmp1.size() - 1);
				lm.writeLog("Consultation capteur " + s_tmp1 + " le : " + s_tmp1);
			}
			break;
		case 4:
			//Affichage des zones a risque
			cout << "--------------------------------------------------------------------"<<endl;
			cout << "4-Visualiser les zones a risque."<<endl;
			cout << "Veuillez entrer la valeur seuil souhaitee pour l'indice ATMO."<<endl ; 
			cout << "ATMO : "; 
			cin >> s_tmp1 ; 
			while (!regex_match(s_tmp1, patternLess10)) {
				cout<< "veuillez entrer une valeur entre 0 et 10";
				cin >> s_tmp1;
			}
			seuil = stoi(s_tmp1);
			cout << "entrer la date." <<endl; 
			date1 = myDisplay.getDate(); 
			cout << "--------------------------------------------------------------------"<<endl;			

		    listeSensor = dataSet.getListSensors();

			itSensor = listeSensor.begin(); 
			cout <<"SensorID | latitude | longitude | description | ATMO "<<endl; 
			while (itSensor!=listeSensor.end()){
					atmo = (**itSensor).calculateAtmo(date1); 
					if (atmo<=seuil){
						cout << (**itSensor).toString() << " | ATMO : " << atmo << endl ; 
					}
					++itSensor; 
			}
			cout << "--------------------------------------------------------------------"<<endl;
			s_tmp1 = ctime(&date1);
			s_tmp1.erase(s_tmp1.size() - 1);
			lm.writeLog("Consulatation zone a risque seuil : " + to_string(seuil) + " date : " + s_tmp1);
			cout << "Appuyez sur enter pour revenir au menu principal " << endl;
			cin.get();
			cin.get();

			break;
		case 5:
			cout << "5-Visualiser les similarites detectees.";
			//appel de la fonction qui affiche les similiarites entre les capteurs
			cout << "Selection de la periode :" << endl;
			cout << "Veuillez entrer la premiere date. " << endl;
			date1 = myDisplay.getDate();
			cout <<endl<< "Veuillez entrer la deuxieme date. " << endl;
			date2 = myDisplay.getDate();

			sensorPair = dataSet.generateSimilarity(date1,date2);
			itPairSensor = sensorPair.begin();
			while (itPairSensor != sensorPair.end()) {
				cout << (*itPairSensor).first->getSensorID() << " similaire au capteur " << (*itPairSensor).second->getSensorID() << endl;
				itPairSensor++;
			}
			s_tmp1 = ctime(&date1);
			s_tmp1.erase(s_tmp1.size() - 1);
			s_tmp2 = ctime(&date1);
			s_tmp2.erase(s_tmp2.size() - 1);
			lm.writeLog("Consultation des similarite entre les capteurs de : " + s_tmp1 + " à : " + s_tmp2);
			cout << "Appuyez sur enter pour revenir au menu principal " << endl;
			cin.get();
			cin.get();
			break;
		default:
			break;
		}//fin du switch de menu principal

		
	}
	return 0; 
}