/**************************************************************************************
 Data  -  Realisation
 -------------------
 debut                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air

 ***************************************************************************************/

 //------------------ Realisation de la classe <Data> (fichier Data.cpp) ------------

 //------------------------------------------------------------------------------ INCLUDE
 //---------------------------------------------------------------------- Include systeme
#include <iostream>
using namespace std;
//--------------------------------------------------------------------- Include personnel
#include "Data.h"
#include "Sensor.h"
#include "DataType.h"
//-------------------------------------------------------------------------------- PUBLIC

//----------------------------------------------------------- Constructeurs - destructeur

 string Data::toString()
 {
	 string time = ctime(&timestamp);
	 return string(time + ";" + to_string(value) +";"+ sensorId +";"+ dataTypeId);
 }

Data::Data(time_t timestamp, float value, string sensorId, string dataTypeId) {
	this->timestamp = timestamp;
	this->value = value;
	this->sensorId = sensorId;
	this->dataTypeId = dataTypeId;
}

Data::~Data() {

}
