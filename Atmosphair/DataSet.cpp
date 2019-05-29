/**************************************************************************************
 DataSet  -  Réalisation
 -------------------
 début                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air

 ***************************************************************************************/

 //-- Réalisation de la classe <DataSet> (fichier DataSet.cpp) ----

 //------------------------------------------------------------------------------ INCLUDE
 //---------------------------------------------------------------------- Include système
#include <iostream>
#include <ctime>
#include "DataSet.h"
using namespace std;
//--------------------------------------------------------------------- Include personnel

//-------------------------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques
void DataSet::addSensor(Sensor &sensor) 
{
	liSensor.insert(sensor);
}

void DataSet::addDataType(DataType &dataType) 
{

}
//-------------------------------------------- Constructeurs - destructeur
DataSet::DataSet() {

}



