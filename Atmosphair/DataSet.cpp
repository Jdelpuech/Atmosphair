/**************************************************************************************
 DataSet  -  Réalisation
 -------------------
 début                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air

 ***************************************************************************************/

 //-- Réalisation de la classe <DataSet> (fichier DataSet.cpp) ----

 //------------------------------------------------------------------------------ INCLUDE
 //---------------------------------------------------------------------- Include système
#define _USE_MATH_DEFINES
#include <iostream>
#include <ctime>
#include <math.h>
#include <cmath> 
using namespace std;
//--------------------------------------------------------------------- Include personnel
#include "DataSet.h"
#include "User.h"
#include "Sensor.h"
#include "DataType.h"
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

void DataSet::addUser(User *user)
{
	liUser.push_back(user);
}

// Cette fonction converti les degres en radiant
double deg2rad(double deg) {
	return (deg * M_PI / 180);
}

double DataSet::calculateDistance(double lat1, double lon1, double lat2, double lon2){
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat1);
	lon1r = deg2rad(lon1);
	lat2r = deg2rad(lat2);
	lon2r = deg2rad(lon2);
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	return 2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
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