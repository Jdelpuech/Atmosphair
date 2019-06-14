/**************************************************************************************
 Sensor  -  Réalisation
 -------------------
 début                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air

 ***************************************************************************************/

//------------------ Réalisation de la classe <Sensor> (fichier Sensor.cpp) ------------

//------------------------------------------------------------------------------ INCLUDE

//---------------------------------------------------------------------- Include système
#include <iostream>
#include <ctime>
using namespace std;

//--------------------------------------------------------------------- Include personnel
#include "Sensor.h"
#include "Data.h"
#include "DataType.h"

//-------------------------------------------------------------------------------- PUBLIC
int Sensor::calculateAtmo(time_t t){
    
    //moyennes
    float moySO2 = 0 ;
    float moyO3 = 0 ;
    float moyParticules = 0 ;
    float moyNO2 = 0 ;

    //tableaux stockant valeurs intermediaires pour les calculs de moyenne
    float maxsSO2[24] = {0};
    float maxsNO2[24] = {0};
    float maxsO3[24] = {0};
    float particules[24]={0};
    
    listData::iterator it = data.begin();

    //extraction des données sur la date
    struct tm format_t = *localtime(&t);
    int day_t = format_t.tm_mday;
    int month_t = format_t.tm_mon ;
    int year_t = format_t.tm_year;

    while (it != data.end()) {
        time_t time1 = (**it).getTimeStamp();
        string type = (**it).getDataTypeId();
        struct tm format = *localtime(&time1);
        int day = format.tm_mday;
        int month = format.tm_mon ;
        int year = format.tm_year;
        int hour = format.tm_hour;
		//std::cout << ctime(&time1);
        //cout <<"date :"<<day<<"/"<<month<<"/"<<year<<" hour :"<<hour<<endl;
        if (day_t==day && month_t==month && year_t==year) {
            //std::cout<<"condition verified"<<endl; 
            if (type.compare("O3")==0) {
                if ((**it).getValue() > maxsO3[hour]) {
                    maxsO3[hour] += (**it).getValue();
                }
            }
            else if (type.compare("NO2")==0) {
                if ((**it).getValue() > maxsNO2[hour]) {
                    maxsNO2[hour] += (**it).getValue();
                }
            }
            else if (type.compare("SO2")==0) {
                if ((**it).getValue() > maxsSO2[hour]) {
                    maxsSO2[hour] += (**it).getValue();
                }
            }
            else if (type.compare("PM10")==0){
                if ((**it).getValue() > particules[hour]) {
                    particules[hour] += (**it).getValue();
                }
            }
        }
        it++;
    }
    
	/*std::cout <<"valeurs O3 : [" ;
    for (int i = 0 ; i<23 ; i++){
		std::cout <<maxsO3[i]<<";";
    }
	std::cout <<maxsO3[23]<<"]"<<endl ; ;
    
	std::cout <<"valeurs NO2 : [" ;
    for (int i = 0 ; i<23 ; i++){
		std::cout <<maxsNO2[i]<<";";
    }
	std::cout <<maxsNO2[23]<<"]"<<endl; */ 
    
    int nbP=0 ;
    int nbS=0 ;
    int nbO=0 ;
    int nbN=0 ;
    for (int i=0 ; i<24 ;i++){
        if (particules[i]!=0){
            moyParticules+=particules[i];
            nbP++;
        }
        if (maxsSO2[i]!=0){
            moySO2+=maxsSO2[i];
            nbS++;
        }
        if (maxsNO2[i]!=0){
            moyNO2+=maxsNO2[i];
            nbN++;
        }
        if (maxsO3[i]!=0){
            moyO3+=maxsO3[i];
            nbO++;
        }
    }
    //calculs des moyennes

	if (nbO == 0 && nbN == 0 && nbP == 0 && nbS == 0) {
		cout << "ok" << endl;
		return -1; //detecte si aucune valeurs disponible pour calculer l'indice
	}

    if (nbO!=0)
        moyO3=moyO3/nbO;
    else 
        cout <<"Attention : aucune valeur de O3 prise en compte lors de ce calcul"<<endl; 
    if (nbN!=0)
        moyNO2=moyNO2/nbN;
    else 
        cout <<"Attention : aucune valeur de NO2 prise en compte lors de ce calcul"<<endl;
    if (nbP!=0)
        moyParticules=moyParticules/nbP;
    else 
        cout <<"Attention : aucune valeur de PM10 prise en compte lors de ce calcul"<<endl;
    if (nbS!=0)
        moySO2=moySO2/nbS;
    else 
        cout <<"Attention : aucune valeur de SO2 prise en compte lors de ce calcul"<<endl;

	
    
    //calcul du max des moyennes
    int max1 ;
    int max2 ;
    int max ;
    
    string type1 ;
    string type2 ;
    string type ;
    
    if (moyO3>moyNO2){
        max1 = (int) moyO3 ;
        type1 = "O3";
        
    }else {
        max1 = (int) moyNO2 ;
        type1 = "NO2";
    }
    
    if (moyParticules>moySO2){
        max2 = moyParticules ;
        type2 = "PM10";
        
    }else {
        max2=moySO2 ;
        type2 = "SO2";
    }
    
    if (max1>max2){
        max = max1 ;
        type = type1;
        
    }else {
        max = max2 ;
        type =type2;
    }
    

    //valeurs des intervalles
    
    int values[9];
    int O3[]={29,54,79,104,129,149,179,209,239};
    int SO2[]={39,79,119,159,199,249,299,399,499};
    int NO2[]={29,54,84,109,134,164,199,274,399};
    int PM10[]={6,13,20,27,34,41,49,64,79};
    
    if (type.compare("O3")==0){
        copy(begin(O3), end(O3), begin(values));
    }else if (type.compare("SO2")==0){
        copy(begin(SO2), end(SO2), begin(values));
    }else if (type.compare("NO2")==0){
        copy(begin(NO2), end(NO2), begin(values));
    }else if (type.compare("PM10")==0){
        copy(begin(PM10), end(PM10), begin(values));
    }
 
    int indiceAtmo = 0 ;
    
    if (max<values[0]){
        indiceAtmo = 1;
    } else if (max<values[1]){
        indiceAtmo=2;
    }else if (max<values[2]){
        indiceAtmo = 3;
    }else if (max<values[3]){
        indiceAtmo=4;
    }else if(max<values[4]){
        indiceAtmo = 5;
    }else if (max<values[5]){
        indiceAtmo=6;
    }else if (max<values[6]){
        indiceAtmo = 7;
    }else if (max<values[7]){
        indiceAtmo=8;
    }else if (max<values[8]){
        indiceAtmo = 9;
    }else {
        indiceAtmo=10;
    }
    
    return indiceAtmo ;
}

float Sensor::calculateMoyenneGaz(time_t t, string type){
    listData::iterator it = data.begin() ; 

    //extraction des données sur la date
    struct tm format_t = *localtime(&t);
    int day_t = format_t.tm_mday;
    int month_t = format_t.tm_mon ;
    int year_t = format_t.tm_year;

    //données 
    float sum = 0 ; 
    int nbrData = 0 ;  
    while (it != data.end()) {
        time_t time = (**it).getTimeStamp();
        string varType = (**it).getDataTypeId();
        struct tm format = *localtime(&time);
        int day = format.tm_mday;
        int month = format.tm_mon ;
        int year = format.tm_year;
        if (day_t==day && month_t==month && year_t==year && type.compare(varType)==0){
            sum+=(**it).getValue();
            nbrData ++ ;  
        }

        it++ ; 
    }
    return ((float)(sum/nbrData)); 
}

float Sensor::calculateMoyenneGaz(time_t t1, time_t t2, string type) {
	struct tm instant1 = *localtime(&t1);
	int day_t = instant1.tm_mday;
	int month_t = instant1.tm_mon;
	int year_t = instant1.tm_year;

	float sum=0.;
	int nbVal = 0;
	while (difftime(t2, t1) > 0) {
		float tmp = calculateMoyenneGaz(t1, type);
		if (tmp >= 0) {
			sum += calculateMoyenneGaz(t1, type);
			nbVal++;
		}
		

		struct tm instant1 = *localtime(&t1);
		instant1.tm_mday++;
		t1 = mktime(&instant1);
	}
	return ((float)(sum / (float)nbVal));
}

string Sensor::getSensorID(){
    return sensorID ;
}

float Sensor::getLatitude(){
    return lat ;
}

float Sensor::getLongitude(){
    return lon ;
}

string Sensor::getDescription(){
    return description ;
}

int Sensor::dysfonction(){
    bool working = true ; 
    int valeur = 0 ; 
    if (data.empty()){
        working = false ; 
        valeur = 3 ; 
        //cout << "no elements"<< endl ; 
    } else {
        listData::iterator it = data.begin();
	    time_t t1 = (**it).getTimeStamp();

        while (it!=data.end()){
            //test de cohérence
            if (it!=data.begin()){
                if ((difftime((**it).getTimeStamp(),t1) > 4000)){
					cout << ctime(&t1) << endl;
                    working = false ; 
                    valeur = 1 ; 
                }
            }
           
            if (((**it).getValue()<=0 || (**it).getValue()>100) && (**it).getDataTypeId()=="PM10"){
                working = false ; 
                valeur = 2 ;  
            }else if (((**it).getValue()<=0 ||(**it).getValue()>600) && (**it).getDataTypeId()=="SO2"){
                working = false ; 
                valeur = 2 ; 
            }else if (((**it).getValue()<=0 ||(**it).getValue()>500) && (**it).getDataTypeId()=="NO2"){
                working = false ; 
                valeur = 2 ; 
            }else if (((**it).getValue()<=0 ||(**it).getValue()>350) && (**it).getDataTypeId()=="O3"){
                working = false ; 
                valeur = 2 ; 
            }
            t1=(**it).getTimeStamp(); 
            it++ ; 
        }
    }
    dysfonctionning=!(working) ; 
    return valeur ; 
}

void Sensor::addData(Data * dataE)
{
	data.push_back(dataE);
}

listData Sensor::getData()
{
    return data;
}

bool Sensor::getDysfonctionning(){
    dysfonction(); 
    return dysfonctionning ; 
}

string Sensor::toString()
{
	return string(sensorID +" | "+ to_string(lon) +" | "+ to_string(lat) + " | "+description) ;
}

void Sensor::dropData() {
	listData::iterator it;
	it = data.begin();
	while (it != data.end()) {
		delete (*it);
		it++;
	}
	data.clear();
}

//----------------------------------------------------------- Constructeurs - destructeur
Sensor::Sensor(string sensorID, float lat, float lon, string description){
    this->sensorID = sensorID ;
    this->lat = lat ;
    this->lon = lon ;
    dysfonction() ;
    
}

Sensor::~Sensor(){
	listData::iterator it;
	it = data.begin();
	while (it != data.end()) {
		delete(*it);
		it++;
	}
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

