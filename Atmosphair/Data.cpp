/**************************************************************************************
 Data  -  R�alisation
 -------------------
 d�but                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air

 ***************************************************************************************/

 //------------------ R�alisation de la classe <Data> (fichier Data.cpp) ------------

 //------------------------------------------------------------------------------ INCLUDE
 //---------------------------------------------------------------------- Include syst�me
#include <iostream>
using namespace std;
//--------------------------------------------------------------------- Include personnel
#include "Data.h"
#include "Sensor.h"
#include "DataType.h"
//-------------------------------------------------------------------------------- PUBLIC

//----------------------------------------------------------- Constructeurs - destructeur

Data::Data(int mesureId, time_t timestamp, double value, Sensor *sensor,DataType *type){
	mesureId = mesureId;
	timestamp = timestamp;
	value = value;
	sensor = sensor;
	type = type; 
}

Data::Data(int mesureId, time_t timestamp, double value, string sensorId, string dataTypeId) {
	mesureId = mesureId;
	timestamp = timestamp;
	value = value;
	sensorId = sensorId;
	dataTypeId = dataTypeId;
}

Data::~Data() {

}
