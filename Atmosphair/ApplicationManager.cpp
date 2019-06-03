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
	User * user=nullptr;
	Display myDisplay;
	char choice, back; 
	int selFonction;
	string login, pwd;
	string fileSensor, fileMeasure, fileLinks;
	string date, choix;
	string lat,lon,r; 
	list<int> valeurs ;
	int moyenne, nbr ; 
	list<int>::iterator it_1; 
	double latitude,longitude,rayon; 
	time_t date1, date2;
	char entree = 'a';
	bool connection = false ;
	regex patternCSV(".*\\.csv$");
	listSensor liste ; 
	listSensor::iterator it; 
	listData listeData ; 
	listData::iterator itData ; 


	ApplicationManager::init(&dataSet, &fm);

	while (!connection){
		cout << "---------------------------------------------------------------------"<<endl; ;
		cout << "Bienvenue chez Atmosph'Air! Afin d’obtenir l'acces à nos services, veuillez vous authentifier."<<endl;
		cout << "Login : ";
		cin >> login;
		cout << "Mot de passe : ";
		cin >> pwd;
		user = dataSet.connectionRequest(login, pwd);
		if (user!=nullptr){
			connection = true ; 
		} else {
			cout<<"Erreur : veuillez reessayer."<<endl; 
		} 

	}

	LogManager lm(user);
	lm.writeLog("Connection de " + user->getNom());

	myDisplay.ShowMenuPrincipal();
	int navigation = 0 ; 
	bool  valid = false ; 
	while (!valid){
		std::cin >> choice;
    	navigation = choice - '0'; 
		if (navigation<10 && navigation>=0){
			valid = true ; 
		}
	}
	//si l'utilisatuer entre 6, il souhaite quitter l'application
	while (navigation != 6)
	{
		switch ((int)navigation)
		{
		case 0:
			// Chargement de fichiers
			myDisplay.ShowChargementFichiers();
			cout << "Fichiers relatifs aux capteurs: ";
			capteur:
			cin >> fileSensor;
			if (fileSensor != "0") {
				if (regex_match(fileSensor, patternCSV)) {
					lm.writeLog("modification sauvegarde capteurs : " + fileSensor);
					fm.save(fileSensor, 0);
					fm.importDataFromFile(&dataSet, fileSensor, 0);
				}
				else {
					cout << "mauvais format" << endl;
					goto capteur;
				}
			}
			cout << "Fichiers relatifs aux mesures : ";
			measure:
			cin >> fileMeasure;
			if (fileMeasure != "0") {
				if (regex_match(fileMeasure, patternCSV)) {
					lm.writeLog("modification sauvegarde mesures : " + fileMeasure);
					fm.save(fileMeasure, 1);
					fm.importDataFromFile(&dataSet, fileMeasure, 1);
				}
				else {
					cout << "mauvais format" << endl;
					goto measure;
				}
			}
			cout << "Fichiers relatifs au type de mesures : ";
			link:
			cin >> fileLinks;
			if (fileLinks != "0") {
				if (regex_match(fileLinks, patternCSV)) {
					lm.writeLog("modification sauvegarde type de mesures : " + fileLinks);
					fm.save(fileLinks, 2);
					fm.importDataFromFile(&dataSet, fileLinks, 2);
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
			// Affichage des capteurs disfonctionnants : appel de la méthode correspondante
			liste = dataSet.getListDysfonctionningSensors(); 
			it = liste.begin(); 
			cout << "--------------------------------------------------------------------"<<endl;
			while(it!=liste.end()){
				cout <<"IDCapteur : "<<(**it).getSensorID()<<" | Dysfonctionnement : "; 
				if ((**it).dysfonction()==1){
					cout<<"période d'échantillonage dépassée"; 
				}else if ((**it).dysfonction()==2){
					cout<<"Données incohérentes"; 
				}else if ((**it).dysfonction()==3){
					cout<<"Données manquantes";
				}
				cout << endl ; 
				++it ; 
			}

			while (back!='q'){
				cout << "Appuyez sur q pour revenir au menu principal."<<endl ; 
				cin >> back ; 
				if (back!='q'){
					cout << "Attention, cette entrée ne correspond a aucune action"<<endl; 
				}
			}
			break;
		case 2:
		while (selFonction != 4)
			{
			// Inspection d'une zone
			valid = false  ; 
			while (!valid){
				cout << "--------------------------------------------------------------------"<<endl;
				cout << "2-Inspecter une zone."<<endl;
				cout << "Veuillez sélectionner la zone. Une zone se définit par les coordonnées d’un point GPS  "<<endl;
				cout << "et d'un rayon. " ;
				cout<< endl ; 
				cout <<"Latitude : " ; 
				cin >> lat ; 
				cout<<"Longitude : "; 
				cin >> lon ; 
				cout <<"Rayon (km) :"; 
				cin >> r ; 

				try{
					latitude = stod(lat);
					longitude = stod(lon); 
					rayon = stod(r); 
					valid = true ; 
				}catch(const std::invalid_argument){ 
        			cerr << "argument invalide : reessayez" << "\n"; 
				}
			}
     
			liste = dataSet.getListSensorsInZone(latitude,longitude,rayon); 
			myDisplay.ShowMenuInspectionZone();
			cin >> selFonction;
			//on a selectionné l'action que l'on souhaite effectuer sur la zone
			//si selFonction est 4, l'utilisateur souhiate revenir au ùenu principal
			
				switch (selFonction)
				{
				case 1:
					//la date est demandée à l'utilisateur
					cout << "--------------------------------------------------------------------"<<endl;
					cout << "2.1 Indice Atmo dans une journée."<<endl;
					cout << "Veuillez entrer la date souhaitée. "<<endl;
					date1 = myDisplay.getDate();
					valeurs = dataSet.generateResultAtmo(liste,date1) ; 
                    it_1 = valeurs.begin() ; 
                    moyenne = 0 ; 
					nbr = 0 ; 
					while(it_1!=valeurs.end()){
						moyenne+=(*it_1); 
						nbr++ ; 
						it_1++; 
					}
					if (nbr!=0)
						moyenne = (int) (moyenne/nbr) ; 
					cout <<"indice ATMO :"<< moyenne <<endl ;  
					cout << "Appuyez sur q pour revenir à l'inspection de la zone"<<endl;
					while (entree != 'q')
					{ 
						cin >> entree;
					}
					//selFonction=4; 
					entree = 'a';
					break;
				case 2:
				    cout << "--------------------------------------------------------------------"<<endl;
					cout << "2.2-Indice Atmo moyen entre t1 et t2."<<endl;
					cout << "Veuillez entrer la premiere date. "<<endl;
					//recuperation des 2 dates
					date1 = myDisplay.getDate();
					cout << "Veuillez entrer la deuxieme date. "<<endl;
					date2 = myDisplay.getDate();
					

					//Appel de la méthode correspondante
					cout << "Indice ATMO moyen correspondant : "; 
					valeurs.clear(); 
					liste = dataSet.getListSensorsInZone(latitude,longitude,rayon); 
					valeurs = dataSet.generateResultAtmo(liste,date1,date2); 
					it_1 = valeurs.begin() ; 
                    moyenne = 0 ; 
					nbr = 0 ; 
					while(it_1!=valeurs.end()){
						moyenne+=(*it_1); 
						nbr++ ; 
						it_1++; 
					}
					if (nbr!=0)
						moyenne = (int) (moyenne/nbr) ; 
				    cout << moyenne << endl ; 
					cout << "Souhaitez vous visualiser toutes les valeurs de l’indice ATMO dans l’intervalle choisi? oui/non."<<endl;
					cin >> choix;
					while ((choix != "oui") && (choix != "non"))
					{
						cout << "Veuillez entrer oui ou non"<<endl;
						cin >> choix;
					}
					if (choix == "oui")
					{
						it_1 = valeurs.begin(); 
						while (it_1!=valeurs.end()){
								struct tm format_t1 = *localtime(&date1);
								cout << "Date : "<<(format_t1.tm_year + 1900)<<"-"<<(format_t1.tm_mon +1)<<"-"<<(format_t1.tm_mday)<<" | ATMO :"<< (*it_1)<<endl ; 
								++it_1; 
								date1 = myDisplay.incrementDate(date1,date2); 

							}

					}
					cout << "Appuyez sur q pour revenir à l'inspection de la zone"<<endl;
					while (entree != 'q')
					{
						cin >> entree;
					}
					selFonction=4; 
					entree = 'a';
					break;

				case 3 :
				    cout << "--------------------------------------------------------------------"<<endl;
					cout << "2.3-Taux moyen de substances dans une journée"<<endl;
					cout << "Veuillez entrer la date souhaitée [yyyy-MM-dd] : "<<endl;
					cin >> date;
					cout << "Veuillez choisir parmis les choix  :  1- O3 |  2- SO2 | 3- NO2 | 4- PM10"<<endl;
					cout << "Pour visualiser plusieurs taux, veuillez concaténer les chiffres."<<endl;
					cout << "Exemple : 134"<< endl;
					cout << "Choix : ";
					cin >> choix;
					//Appel a la methode de calcul du taux moyen de chaque substance

					//Taux moyen de [substance] dans la journée : xxx

					cout << "Appuyez sur q pour revenir à l'inspection de la zone"<<endl;
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

			cout << "Veuillez saisir l’ID du capteur souhaité (ex. Sensor9) : "<<endl;
			cin >> choix;
			myDisplay.ShowMenu3MessageChoix();
			cout << "Saisissez une date de début (yyyy-MM-dd) : "<<endl;
			date1 = myDisplay.getDate();
			cout << "Saisissez une date de fin(yyyy - MM - dd) : "<<endl;
			date2 = myDisplay.getDate();
			if (difftime(date1,date2)!=0)
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

				cout << "Appuyez sur q pour revenir au menu précédent"<<endl;
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

	/*std::cout << "Test Julie" << endl;
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

	//cout << endl << "Test Save" << endl;
	FileManager fmSave = FileManager("sauvegardes.txt");
	DataSet dSave= DataSet();
	fm.openSave("sauvegardes.txt", &dSave);

	cout << endl << "Debut Test Save" << endl;
	fm.save(&dSave, "sensors2.txt", 0);
	cout << endl << "Fin Test Save" << endl;

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
	*/

	
	/*User * user_1 = new User("jdelpuech@atmosphair.com", "123", "Julie Delpuech");
	LogManager logM(user_1);
	logM.writeLog("nom de l'action");
	FileManager fm;
	fm.save("test", 0);*/

	struct tm instant;
	instant.tm_mon = 1 - 1;
	instant.tm_mday = 1;
	instant.tm_year = 2017 - 1900;
	instant.tm_hour = 1;
	instant.tm_min = 0;
	instant.tm_sec = 0;
	time_t time = mktime(&instant);

	//créations type de données
	DataType type_O3 = DataType("O3", "µg/m3", "concentration d'ozone");
	DataType type_NO2 = DataType("NO2", "µg/m3", "concentration de dioxyde d'azote");
	DataType type_SO2 = DataType("SO2", "µg/m3", "concentration de dioxyde de soufre");
	DataType type_PM10 = DataType("PM10", "µg/m3", "concentration de particules fines");


	//création sensors
	Sensor * sensor_0 = new Sensor("Sensor0", (double)-8.15758888291083, (double)-34.7692487876719, "0");
	Sensor * sensor_2 = new Sensor("Sensor2", (double)-30.0647387677174, (double)-76.3439147576429, "1");

	//une vague de données
	Data * data_0 = new Data(time, 67.9284748555273, "Sensor0", "O3");
	Data * data_1 = new Data(time, 98.979984192197, "Sensor0", "NO2");
	Data * data_2 = new Data(time, 119.423041339039, "Sensor0", "SO2");
	Data * data_3 = new Data(time, 16.7564963001065, "Sensor0", "PM10");
	instant.tm_hour += 1;
	time = mktime(&instant);
	Data * data_4 = new Data(time, 36.7797600526823, "Sensor0", "O3");
	Data * data_5 = new Data(time, 80.2280346451481, "Sensor0", "NO2");
	Data * data_6 = new Data(time, 38.151540049253, "Sensor0", "SO2");
	Data * data_7 = new Data(time, 1.99603267330184, "Sensor0", "PM10");
	sensor_0->addData(data_0);
	sensor_0->addData(data_1);
	sensor_0->addData(data_2);
	sensor_0->addData(data_3);
	sensor_0->addData(data_4);
	sensor_0->addData(data_5);
	sensor_0->addData(data_6);
	sensor_0->addData(data_7);

	sensor_2->addData(data_0);
	sensor_2->addData(data_1);
	sensor_2->addData(data_2);
	sensor_2->addData(data_3);
	sensor_2->addData(data_4);
	sensor_2->addData(data_5);
	sensor_2->addData(data_6);
	sensor_2->addData(data_7);

	DataSet d;
	d.addSensor(sensor_0);

	d.dropListSensors();

	return 0;
}
