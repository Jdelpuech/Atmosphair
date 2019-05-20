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


//-------------------------------------------------------------------------------- PUBLIC

//----------------------------------------------------------- Constructeurs - destructeur

Data::Data(int mesureId, time_t timestamp, double value, Sensor sensor,DataType type) {
	this->mesureId = mesureId;
	this->timestamp = timestamp;
	this->value = value;
	this->sensor = sensor;
	this->type = type; 
}

Data::~Data() {

}
