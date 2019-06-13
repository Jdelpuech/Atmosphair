/**************************************************************************************
 DataType  -  Realisation
 -------------------
 debut                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air

 ***************************************************************************************/

 //------------------ Realisation de la classe <DataType> (fichier DataType.cpp) ------------

 //------------------------------------------------------------------------------ INCLUDE
 //---------------------------------------------------------------------- Include systeme
#include <iostream>
using namespace std;

//--------------------------------------------------------------------- Include personnel
#include "DataType.h"
#include "Sensor.h"
//-------------------------------------------------------------------------------- PUBLIC

//----------------------------------------------------------- Constructeurs - destructeur

 string DataType::toString()
 {
	 return string(attributeId+";"+unit + ";" + description);
 }
 // Mode d'emploi : renvoie la description du type 
 // Contrat : aucun

 DataType::DataType(string attributeId, string unit, string description) {
	this->attributeId = attributeId;
	this->unit = unit;
	this->description = description;
}
// Mode d'emploi : aucun
// Contrat : aucun

DataType::~DataType() {

}
// Mode d'emploi : aucun
// Contrat : aucun
