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
	mesureId = mesureId;
	timestamp = timestamp;
	value = value;
	sensor = sensor;
	type = type; 
}

Data::~Data() {

}
