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
#include "User.h"
#include "Sensor.h"
#include "DataType.h"
using namespace std;
//--------------------------------------------------------------------- Include personnel

//-------------------------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques
void DataSet::addSensor(Sensor *sensor) 
{
	liSensor.push_back(sensor);
}

void DataSet::addDataType(DataType *dataType) 
{
	liDataType.push_back(dataType);
}

Sensor DataSet::getSensorById(string id) {
	Sensor res = NULL;
	for (Sensor s : liSensor) {
		if (s.getSensorID==id) {
			res = s;
		}
	}
	return res;
}


bool DataSet::connectionRequest(string user, string password) {
	listUser::iterator it;
	it = liUser.begin();
	while (it != liUser.end()) {
		if ((**it).getLogin() == user && (**it).getMdp() == password) {
			return true;
		}
		++it;
	}
	return false;
}
//-------------------------------------------- Constructeurs - destructeur
DataSet::DataSet() {

}

DataSet::~DataSet() {

}