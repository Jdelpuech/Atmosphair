/**************************************************************************************
 DataSet  -  R�alisation
 -------------------
 d�but                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air

 ***************************************************************************************/

 //-- R�alisation de la classe <DataSet> (fichier DataSet.cpp) ----

 //------------------------------------------------------------------------------ INCLUDE
 //---------------------------------------------------------------------- Include syst�me
#include <iostream>
#include <ctime>
#include "DataSet.h"
using namespace std;
//--------------------------------------------------------------------- Include personnel

//-------------------------------------------------------------------------------- PUBLIC
//----------------------------------------------------- M�thodes publiques
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



