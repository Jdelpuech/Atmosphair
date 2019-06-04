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
	int selFonction = 0;
	string date, choix;
	string lat,lon,r; 
	list<int> valeurs ;
	int moyenne, nbr ; 
	list<int>::iterator it_1; 
	float latitude,longitude,rayon; 
	
	char entree = 'a';
	
	
	listSensor listeSensor ; 
	listSensor::iterator itSensor; 
	listData listeData ; 
	listData::iterator itData ;
	list<pair<Sensor *, Sensor *> > sensorPair;
	list<pair<Sensor *, Sensor *> >::iterator itPairSensor;
	vector<float> resultsGaz ;

	bool valid, connection=false;
	string s_tmp1="", s_tmp2="",s_navigation="";
	time_t date1, date2;
	int navigation = 0;
	int i_tmp = 0;
	char c_tmp = 'a',back = 'a';
	

	string seuil; 
	int atmo ; 
	int valSeuil ; 

	regex patternCSV(".*\\.csv$");
	regex patternNum("[0-6]");
	regex patternYear("201[0-9]");
	regex patternMonth("[1-9]|1[0-2]");
	regex patternDay("[1-9]|[1-2][0-9]|3[0-1]");

	if(regex_match("32", patternDay)){
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


	/*while (!valid){
		std::cin >> choice;
    	navigation = choice - '0'; 
		if (navigation<10 && navigation>=0){
			valid = true ; 
		}
	}*/ 

	//si l'utilisatuer entre 6, il souhaite quitter l'application
	while (navigation != 6)
	{
		//on affiche a nouveau le menu principal
		myDisplay.ShowMenuPrincipal();
		s_navigation = "";
		while (!regex_match(s_navigation, patternNum)) {
			cin >> s_navigation;
		}
		switch (stoi(s_navigation))
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

			while (back!='q'){
				cout << "Appuyez sur q pour revenir au menu principal."<<endl ; 
				cin >> back ; 
				if (back!='q'){
					cout << "Attention, cette entree ne correspond a aucune action"<<endl; 
				}
			}
			break;
		case 2:
			cout << "here";
			cout << "selfonction" << selFonction << endl;
			while (selFonction != 4)
			{
				// Inspection d'une zone
				valid = false  ; 
				while (!valid){
					cout << "--------------------------------------------------------------------"<<endl;
					cout << "2-Inspecter une zone."<<endl;
					cout << "Veuillez selectionner la zone. Une zone se definit par les coordonnees d’un point GPS  "<<endl;
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
     
				listeSensor = dataSet.getListSensorsInZone(latitude,longitude,rayon); 
				myDisplay.ShowMenuInspectionZone();
				cin >> selFonction;
				//on a selectionne l'action que l'on souhaite effectuer sur la zone
				//si selFonction est 4, l'utilisateur souhiate revenir au ùenu principal
			
				switch (selFonction)
				{
				case 1:
					//la date est demandee a l'utilisateur
					cout << "--------------------------------------------------------------------"<<endl;
					cout << "2.1 Indice Atmo dans une journee."<<endl;
					cout << "Veuillez entrer la date souhaitee. "<<endl;
					date1 = myDisplay.getDate();
					valeurs = dataSet.generateResultAtmo(listeSensor,date1) ; 
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
					cout << "Appuyez sur q pour revenir a l'inspection de la zone"<<endl;
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
					

					//Appel de la methode correspondante
					cout << "Indice ATMO moyen correspondant : "; 
					valeurs.clear(); 
					listeSensor = dataSet.getListSensorsInZone(latitude,longitude,rayon); 
					valeurs = dataSet.generateResultAtmo(listeSensor,date1,date2); 
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
						while (it_1!=valeurs.end())
						{
							struct tm format_t1 = *localtime(&date1);
							cout << "Date : "<<(format_t1.tm_year + 1900)<<"-"<<(format_t1.tm_mon +1)<<"-"<<(format_t1.tm_mday)<<" | ATMO : "<< (*it_1)<<endl ; 
							++it_1; 
							date1 = myDisplay.incrementDate(date1,date2); 

						}

					}
					cout << "Appuyez sur q pour revenir a l'inspection de la zone"<<endl;
					while (entree != 'q')
					{
						cin >> entree;
					}
					
					entree = 'a';
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

					cout << "Appuyez sur q pour revenir a l'inspection de la zone. "<<endl;
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
			selFonction = 0;
			break;
		case 3:
			myDisplay.ShowMenu3();
			cin >> i_tmp;
            if (i_tmp==3){
				break ; 
			}
			if (i_tmp == 1 )
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
             
			cout << "Veuillez saisir l'ID du capteur souhaite (ex. Sensor9) : "<<endl;
			cin >> s_tmp1;
			myDisplay.ShowMenu3MessageChoix();
			cout <<endl<< "Saisissez une date de debut. "<<endl;
			date1 = myDisplay.getDate();
			cout <<endl<< "Saisissez une date de fin. "<<endl;
			date2 = myDisplay.getDate();
			if (difftime(date1,date2)!=0)
			{
				myDisplay.ShowValues(dataSet, date1,date2,dataSet.getSensorById(s_tmp1));
				cout << "Appuyez sur q pour revenir au menu precedent "<<endl;
				while (entree != 'q')
				{
					cin >> entree;
				}
				entree = 'a';
			}

			break;
		case 4:
			//Affichage des zones a risque
			cout << "--------------------------------------------------------------------"<<endl;
			cout << "4-Visualiser les zones a risque."<<endl;
			cout << "Veuillez entrer la valeur seuil souhaitee pour l'indice ATMO."<<endl ; 
			cout << "ATMO : "; 
			cin >> seuil ; 
			cout << "entrer la date." <<endl; 
			date1 = myDisplay.getDate(); 
			cout << "--------------------------------------------------------------------"<<endl;
            valSeuil = stoi(seuil); 
			while (valSeuil>10 ||valSeuil<0){
				cout << "Veuillez entrer la valeur seuil souhaitee pour le facteur selectionnee"<<endl ; 
				cout << "ATMO :"; 
				cin >> seuil ; 
				valSeuil = stoi(seuil);
			}

		    listeSensor = dataSet.getListSensors();

			itSensor = listeSensor.begin(); 
			cout <<"SensorID | latitude | longitude | description | ATMO "<<endl; 
			while (itSensor!=listeSensor.end()){
					atmo = (**itSensor).calculateAtmo(date1); 
					if (atmo>=valSeuil){
						cout << (**itSensor).toString() << " | ATMO : " << atmo << endl ; 
					}
					++itSensor; 
			}
			cout << "--------------------------------------------------------------------"<<endl;
			cout << "Appuyez sur q pour revenir au choix du facteur";
			while (entree != 'q')
			{
				cin >> entree;
			}
			entree = 'a';

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
    
    //creations type de donnees
    DataType type_O3 = DataType("O3","µg/m3","concentration d'ozone");
    DataType type_NO2 = DataType("NO2","µg/m3","concentration de dioxyde d'azote");
    DataType type_SO2 = DataType("SO2","µg/m3","concentration de dioxyde de soufre");
    DataType type_PM10 = DataType("PM10","µg/m3","concentration de particules fines");
    
    
    //creation sensors
    Sensor sensor_0 = Sensor("Sensor0",(float)-8.15758888291083,(float)-34.7692487876719,"0");
    Sensor sensor_1= Sensor("Sensor1",(float)-30.0647387677174,(float)-76.3439147576429,"1");
	Sensor sensor_2 = Sensor("Sensor2", (float)-8.0647387677174, (float)-34.3439147576429, "2");
	Sensor sensor_3 = Sensor("Sensor3", (float)-30.1, (float)-76.1, "3");
    
    //une vague de donnees
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
    
    float result = DataSet::calculateDistance(-8.157588883, -34.76924879, -8.0647387677174,-34.3439147576429);
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

	listSensor liSen= d1.getListSensorsInZone((float)-8.15758888291083, (float)-34.7692487876719, (float)100);
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

	//creations type de donnees
	DataType type_O3 = DataType("O3", "µg/m3", "concentration d'ozone");
	DataType type_NO2 = DataType("NO2", "µg/m3", "concentration de dioxyde d'azote");
	DataType type_SO2 = DataType("SO2", "µg/m3", "concentration de dioxyde de soufre");
	DataType type_PM10 = DataType("PM10", "µg/m3", "concentration de particules fines");


	//creation sensors
	Sensor * sensor_0 = new Sensor("Sensor0", (float)-8.15758888291083, (float)-34.7692487876719, "0");
	Sensor * sensor_2 = new Sensor("Sensor2", (float)-30.0647387677174, (float)-76.3439147576429, "1");

	//une vague de donnees
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
