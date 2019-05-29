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
	int maxsSO2[24] = {0};
	int maxsNO2[24] = {0};
	int maxsO3[24] = {0};
	listData::iterator it = data.begin(); 
	
	while (it != data.end()) {
		time_t time = (**it).getTimeStamp(); 
		DataType type = *(**it).getDataType(); 
		//revoir pour comparer deux dates 
		if (time == t) {
			struct tm * format = localtime(&time);
			int hour = format->tm_hour; 
			if (type.getAttributeId().compare("O3")) {
				if ((**it).getValue() > maxsO3[hour]) {
					maxsO3[hour] = (**it).getValue();
				}
			}
			else if (type.getAttributeId().compare("NO2")) {
				if ((**it).getValue() > maxsNO2[hour]) {
					maxsNO2[hour] = (**it).getValue();
				}
			}
			else if (type.getAttributeId().compare("SO2")) {
				if ((**it).getValue() > maxsSO2[hour]) {
					maxsSO2[hour] = (**it).getValue();
				}
			}

		}

		it++;
	}
	return 0; 
}

int Sensor::getSensorID(){
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

//----------------------------------------------------------- Constructeurs - destructeur
Sensor::Sensor(int sensorID, long lat, long lon, string description, bool dysfonctionning){
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

