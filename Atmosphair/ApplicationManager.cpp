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
#include "ApplicationManager.h"
#include "FileManager.h"
#include "Sensor.h"
#include "User.h"
#include "DataType.h"
#include "Data.h"
#include "DataSet.h"
#include "Display.h"


//-------------------------------------------------------------------------------- PUBLIC
int main() {

	Display myDisplay;
	int navigation, selFonction;
	string login, pwd;
	string fileSensor, fileMeasure, fileLinks;
	string inspectionZone, jour, date, choix;
	string dateDebut, dateFin;
	char entree = 'a';

	cout << "---------------------------------------------------------------------";
	cout << "Bienvenue chez Atmosph'Air! Afin d’obtenir l'accès à nos services, veuillez vous authentifier.";
	cout << "Login : ";
	cin >> login;
	cout << "Mot de passe : ";
	cin >> pwd;

	myDisplay.ShowMenuPrincipal();
	cin >> navigation;
	//si l'utilisatuer entre 6, il souhaite quitter l'application
	while (navigation != 6)
	{
		switch ((int)navigation)
		{
		case 0:
			// Chargement de fichiers
			myDisplay.ShowChargementFichiers();
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
			// Affichage des capteurs disfonctionnants : appel de la méthode correspondante


			break;
		case 2:
			// Inspection d'une zone
			cout << "2-Inspecter une zone.";
			cout << "Veuillez sélectionner la zone. Une zone se définit par les coordonnées d’un point GPS sous le format lat;long;rayon : ";
			cin >> inspectionZone;
			myDisplay.ShowMenuInspectionZone();
			cin >> selFonction;
			//on a selectionné l'action que l'on souhaite effectuer sur la zone
			//si selFonction est 4, l'utilisateur souhiate revenir au ùenu principal
			while (selFonction != 4)
			{
				switch (selFonction)
				{
				case 1:
					//la date est demandée à l'utilisateur
					//myDisplay.ShowZoneIndiceAtmoJournee(); //peut etre pas utile pour 2 lignes
					cout << "2.1 Indice Atmo dans une journée.";
					cout << "Veuillez entrer la date souhaitée[yyyy - MM - dd] : ";
					//on récupère le jour entré par l'utilisateur
					cin >> jour;

					cout << "Appuyez sur q pour revenir à l'inspection de la zone";
					while (entree != 'q')
					{
						cin >> entree;
					}
					entree = 'a';
					break;
				case 2:
					cout << "2.2-Indice Atmo moyen entre t1 et t2.";
					cout << "Veuillez entrer les deux dates sous la forme[yyyy - MM - dd]; [yyyy - MM - dd]";
					cin >> date;

					//decoupage de la date en 2 dates
					

					//Appel de la méthode correspondante
					cout << "Indice ATMO moyen correspondant : ";
					cout << "Souhaitez vous visualiser toutes les valeurs de l’indice ATMO dans l’intervalle choisi? oui/non.";
					cin >> choix;
					while ((choix != "oui") && (choix != "non"))
					{
						cout << "Veuillez entrer oui ou non";
						cin >> choix;
					}
					if (choix == "oui")
					{
						//Appel au calcul de l'indice ATMO pour chaque jour compris dans l'intervalle
						//Format :
						//Date : yyyy-MM-dd ATMO:X


					}
					cout << "Appuyez sur q pour revenir à l'inspection de la zone";
					while (entree != 'q')
					{
						cin >> entree;
					}
					entree = 'a';
					break;

				case 3 :
					cout << "2.3-Taux moyen de substances dans une journée";
					cout << "Veuillez entrer la date souhaitée [yyyy-MM-dd] : ";
					cin >> date;
					cout << "Veuillez choisir parmis les choix  :  1- O3 |  2- SO2 | 3- NO2 | 4- PM10";
					cout << "Pour visualiser plusieurs taux, veuillez concaténer les chiffres.Exemple :";
					cout << "134";
					cout << "Choix : ";
					cin >> choix;
					//Appel a la methode de calcul du taux moyen de chaque substance

					//Taux moyen de [substance] dans la journée : xxx

					cout << "Appuyez sur q pour revenir à l'inspection de la zone";
					while (entree != 'q')
					{
						cin >> entree;
					}
					entree = 'a';
					break;
				default:
					break;
				}//fin du switch du menu Zone
			
			}//on quitte le menu "Zone"

			break;
		case 3:
			myDisplay.ShowMenu3();
			cin >> selFonction;

			if (selFonction == 1)
			{
				//Affichage de la liste des capteurs existants

			}

			cout << "Veuillez saisir l’ID du capteur souhaité (ex. Sensor9) : ";
			cin >> choix;
			myDisplay.ShowMenu3MessageChoix();
			cout << "Saisissez une date de début (yyyy-MM-dd) : ";
			cin >> dateDebut;
			cout << "Saisissez une date de fin(yyyy - MM - dd) : ";
			cin >> dateFin;
			if ((dateDebut != "") && (dateFin != ""))
			{
				//Appel de la méthode d'affichage des données du capteur
				/* ( format : )
				======================Données du capteur[xxx] ================================ =
					Statistiques correspondant à la période aaaa - bbbb
					[Si période inférieure à une journée : message d’avertissement concernant la                  non - fiabilité des résultats]
				Latitude : xxx Longitude : xxx
					Description : xxx
					10 derniers indices ATMO : [n1 | … | n10] --->moyenne : m1min : a max : b
					10 derniers taux de O3 : [n1 | … | n10]   --->moyenne : m2 min : a max : b
					10 derniers taux de SO2 : [n1 | … | n10]  --->moyenne : m3min : a max : b
					10 derniers taux de NO2 : [n1 | … | n10]  --->moyenne : m4min : a max : b
					10 derniers taux de PM10 : [n1 | … | n10]  --->moyenne : m5min : a max : b
				===============================================================================
				*/

				cout << "Appuyez sur q pour revenir au menu précédent";
				while (entree != 'q')
				{
					cin >> entree;
				}
				entree = 'a';
			}

			break;
		case 4:
			//Affichage des zones a risque
			myDisplay.ShowMenu4();
			cin >> selFonction;
			myDisplay.ShowMenu4SelectionSeuil(selFonction);
			
			cout << "Appuyez sur q pour revenir au choix du facteur";
			while (entree != 'q')
			{
				cin >> entree;
			}
			entree = 'a';

			break;
		case 5:
			cout << "5-Visualiser les similarités détectées.";
			//appel de la fonction qui affiche les similiarités entre les capteurs

			cout << "Appuyez sur q pour revenir au menu principal.";
			while (entree != 'q')
			{
				cin >> entree;
			}
			entree = 'a';
			break;
		case 6:
			break;
		default:
			break;
		}//fin du switch de menu principal

		//on affiche a nouveau le menu principal
		myDisplay.ShowMenuPrincipal();
		cin >> navigation;
	}
	return 0; 
}


int test(){

	std::cout << "Test Julie" << endl;
    struct tm instant ;
    instant.tm_mon= 1-1 ;
    instant.tm_mday= 1 ;
    instant.tm_year= 2017-1900;
    instant.tm_hour = 1 ;
    instant.tm_min = 0 ;
	instant.tm_sec = 0;
    time_t time = mktime(&instant);
    
    //créations type de données
    DataType type_O3 = DataType("O3","µg/m3","concentration d'ozone");
    DataType type_NO2 = DataType("NO2","µg/m3","concentration de dioxyde d'azote");
    DataType type_SO2 = DataType("SO2","µg/m3","concentration de dioxyde de soufre");
    DataType type_PM10 = DataType("PM10","µg/m3","concentration de particules fines");
    
    
    //création sensors
    Sensor sensor_0 = Sensor("Sensor0",(double)-8.15758888291083,(double)-34.7692487876719,"0");
    Sensor sensor_1= Sensor("Sensor1",(double)-30.0647387677174,(double)-76.3439147576429,"1");
	Sensor sensor_2 = Sensor("Sensor2", (double)-8.0647387677174, (double)-34.3439147576429, "2");
	Sensor sensor_3 = Sensor("Sensor3", (double)-30.1, (double)-76.1, "3");
    
    //une vague de données
    Data * data_0 = new Data(time,67.9284748555273,"Sensor0","O3");
    Data * data_1 = new Data(time,98.979984192197,"Sensor0","NO2");
    Data * data_2 = new Data(time,119.423041339039,"Sensor0","SO2");
    Data * data_3 = new Data(time,16.7564963001065,"Sensor0","PM10");
    instant.tm_hour += 1 ;
    time = mktime(&instant);
    Data * data_4 = new Data(time,36.7797600526823,"Sensor0","O3");
    Data * data_5 = new Data(time,80.2280346451481,"Sensor0","NO2");
    Data * data_6 = new Data(time,38.151540049253,"Sensor0","SO2");
    Data * data_7 = new Data(time,1.99603267330184,"Sensor0","PM10");
    sensor_0.addData(data_0);
    sensor_0.addData(data_1);
    sensor_0.addData(data_2);
    sensor_0.addData(data_3);
    sensor_0.addData(data_4);
    sensor_0.addData(data_5);
    sensor_0.addData(data_6);
    sensor_0.addData(data_7);

	sensor_2.addData(data_0);
	sensor_2.addData(data_1);
	sensor_2.addData(data_2);
	sensor_2.addData(data_3);
	sensor_2.addData(data_4);
	sensor_2.addData(data_5);
	sensor_2.addData(data_6);
	sensor_2.addData(data_7);
    std::list<Data *> listeDonnees = sensor_0.getData();

    int indice = sensor_0.calculateAtmo(time);
    std::cout <<"ATMO : "<<indice << endl ;
    
    double result = DataSet::calculateDistance(-8.157588883, -34.76924879, -8.0647387677174,-34.3439147576429);
    std::cout << result << endl <<endl;

	std::cout << "Test Grazia" << endl;
	DataSet d = DataSet();
	FileManager fm = FileManager();

	/*string s = "./sauvegardes.txt";*/
	fm.openSave("sauvegardes.txt",&d);

	listSensor liSensor =d.getListSensors();
	std::cout << "DATA" << endl;
	listSensor::iterator it;
	it = liSensor.begin();
	while (it != liSensor.end()) {
		cout << (**it).toString()<< endl;
		++it;
	}
	cout << endl;
	listData liD = d.getSensorById("Sensor0")->getData();
	listData::iterator itD;
	itD = liD.begin();

	while (itD != liD.end()) {
		cout << (**itD).toString() << endl;
		++itD;
	}
	
	listDataType liDT = d.getListDataType();
	listDataType::iterator itT;
	itT = liDT.begin();

	while (itT != liDT.end()) {
		cout << (**itT).toString() << endl;
		++itT;
	}

	cout << endl << "Test Hugo" << endl;

	DataSet d1 = DataSet();

	d1.addSensor(&sensor_0);
	d1.addSensor(&sensor_1);
	d1.addSensor(&sensor_2);
	d1.addSensor(&sensor_3);

	listSensor liSen= d1.getListSensorsInZone((double)-8.15758888291083, (double)-34.7692487876719, (double)100);
	listSensor::iterator it1;
	it1 = liSen.begin();
	while (it1 != liSen.end()) {
		cout << (**it1).getDescription()<<endl;
		++it1;
	}

	list<int> atmo = d1.generateResultAtmo(liSen, time);
	list<int>::iterator it2;
	it2 = atmo.begin();
	while (it2 != atmo.end()) {
		cout << *it2 << endl;
		++it2;
	}

	return 0;
}
