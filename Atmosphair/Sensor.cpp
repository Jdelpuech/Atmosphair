/**************************************************************************************
 Sensor  -  Réalisation
 -------------------
 début                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air

 ***************************************************************************************/

//------------------ Réalisation de la classe <Sensor> (fichier Sensor.cpp) ------------

//------------------------------------------------------------------------------ INCLUDE
#pragma warning(disable : 4996)
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
    double moySO2 = 0 ;
    double moyO3 = 0 ;
    double moyParticules = 0 ;
    double moyNO2 = 0 ;

    //tableaux stockant valeurs intermediaires pour les calculs de moyenne
    int maxsSO2[24] = {0};
    int maxsNO2[24] = {0};
    int maxsO3[24] = {0};
    int particules[24]={0};
    
    listData::iterator it = data.begin();

    //extraction des données sur la date
    struct tm format_t = *localtime(&t);
    int day_t = format_t.tm_mday;
    int month_t = format_t.tm_mon ;
    int year_t = format_t.tm_year;

    while (it != data.end()) {
        time_t time1 = (**it).getTimeStamp();
        string type = (**it).getDataType();
        struct tm format = *localtime(&time1);
        int day = format.tm_mday;
        int month = format.tm_mon ;
        int year = format.tm_year;
        int hour = format.tm_hour;
        cout <<"date :"<<day<<"/"<<month<<"/"<<year<<" hour :"<<hour<<endl;
        if (day_t==day && month_t==month && year_t==year) {
            cout<<"condition verified"<<endl; 
            if (type.compare("O3")==0) {
                if ((**it).getValue() > maxsO3[hour]) {
                    maxsO3[hour] = (**it).getValue();
                }
            }
            else if (type.compare("NO2")==0) {
                if ((**it).getValue() > maxsNO2[hour]) {
                    maxsNO2[hour] = (**it).getValue();
                }
            }
            else if (type.compare("SO2")==0) {
                if ((**it).getValue() > maxsSO2[hour]) {
                    maxsSO2[hour] = (**it).getValue();
                }
            }
            else if (type.compare("PM10")==0){
                if ((**it).getValue() > particules[hour]) {
                    particules[hour] = (**it).getValue();
                }
            }
        }
        it++;
    }
    
    cout <<"valeurs O3 : [" ;
    for (int i = 0 ; i<23 ; i++){
        cout <<maxsO3[i]<<";";
    }
    cout<<maxsO3[23]<<"]"<<endl ; ;
    
    cout <<"valeurs NO2 : [" ;
    for (int i = 0 ; i<23 ; i++){
        cout <<maxsNO2[i]<<";";
    }
    cout<<maxsNO2[23]<<"]"<<endl;
    
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
    moyO3=moyO3/nbO;
    moyNO2=moyNO2/nbN;
    moyParticules=moyParticules/nbP;
    moySO2=moySO2/nbS;
    
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

string Sensor::getSensorID(){
    return sensorID ;
}

double Sensor::getLatitude(){
    return lat ;
}

double Sensor::getLongitude(){
    return lon ;
}

string Sensor::getDescription(){
    return description ;
}

bool Sensor::dysfonction(){
    return dysfonctionning ;
}

void Sensor::addData(Data * dataE)
{
	data.push_back(dataE);
}

listData Sensor::getData()
{
    return data;
}

//----------------------------------------------------------- Constructeurs - destructeur
Sensor::Sensor(string sensorID, double lat, double lon, string description, bool dysfonctionning){
    this->sensorID = sensorID ;
    this->lat = lat ;
    this->lon = lon ;
    this->description = description ;
    this->dysfonctionning = dysfonctionning ;
    
}

Sensor::~Sensor(){
    
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

