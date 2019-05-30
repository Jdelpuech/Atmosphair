/**************************************************************************************
 DataType  -  RŽalisation
 -------------------
 début                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air

 ***************************************************************************************/

 //------------------ RŽalisation de la classe <DataType> (fichier DataType.cpp) ------------

 //------------------------------------------------------------------------------ INCLUDE
 //---------------------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//--------------------------------------------------------------------- Include personnel
#include "DataType.h"
#include "Sensor.h"
//-------------------------------------------------------------------------------- PUBLIC

//----------------------------------------------------------- Constructeurs - destructeur

DataType::DataType(string attributeId, string unit, string description) {
	this->attributeId = attributeId;
	this->unit = unit;
	this->description = description;
}

DataType::~DataType() {

}
