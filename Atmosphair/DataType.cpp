/**************************************************************************************
 DataType  -  R�alisation
 -------------------
 d�but                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air

 ***************************************************************************************/

 //------------------ R�alisation de la classe <DataType> (fichier DataType.cpp) ------------

 //------------------------------------------------------------------------------ INCLUDE
 //---------------------------------------------------------------------- Include syst�me
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
