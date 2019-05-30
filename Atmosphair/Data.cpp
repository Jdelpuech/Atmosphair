/**************************************************************************************
 Data  -  Réalisation
 -------------------
 début                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air

 ***************************************************************************************/

 //------------------ Réalisation de la classe <Data> (fichier Data.cpp) ------------

 //------------------------------------------------------------------------------ INCLUDE
 //---------------------------------------------------------------------- Include système
#include <iostream>
using namespace std;
//--------------------------------------------------------------------- Include personnel
#include "Data.h"
#include "Sensor.h"
#include "DataType.h"
//-------------------------------------------------------------------------------- PUBLIC

//----------------------------------------------------------- Constructeurs - destructeur

Data::Data(int mesureId, time_t timestamp, double value, Sensor *sensor,DataType *type){
	this->mesureId = mesureId;
	this->timestamp = timestamp;
	this->value = value;
	this->sensor = sensor;
	this->type = type;
}

Data::Data(int mesureId, time_t timestamp, double value, string sensorId, string dataTypeId) {
	this->mesureId = mesureId;
	this->timestamp = timestamp;
	this->value = value;
	this->sensorId = sensorId;
	this->dataTypeId = dataTypeId;
}

Data::~Data() {

}
