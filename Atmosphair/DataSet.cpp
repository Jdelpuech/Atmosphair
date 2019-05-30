/**************************************************************************************
 DataSet  -  R�alisation
 -------------------
 d�but                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air

 ***************************************************************************************/

 //-- R�alisation de la classe <DataSet> (fichier DataSet.cpp) ----

 //------------------------------------------------------------------------------ INCLUDE
 //---------------------------------------------------------------------- Include syst�me
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
//----------------------------------------------------- M�thodes publiques
void DataSet::addSensor(Sensor *sensor) 
{
	liSensor.push_back(sensor);
}

void DataSet::addDataType(DataType *dataType) 
{
	liDataType.push_back(dataType);
}

Sensor  DataSet::getSensorById(string id) {
    Sensor * res = NULL ;
    listSensor::iterator it = liSensor.begin();
    while (it != liSensor.end()) {
        if ((**it).getSensorID().compare(id)==0){
            * res = (Sensor) (**it);
        }
        
        it++;
    }
    
    return *res;
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

//A TESTER
list<int> generateResultAtmo(list<Sensor*> l, time_t t){
    list<int> results ;
    list<Sensor*>::iterator it;
    it = l.begin();
    while (it != l.end()) {
        results.push_back((**it).calculateAtmo(t));
        ++it;
    }
    return results ; 
}
//A TESTER
list<int> generateResultAtmo(list<Sensor*> l, time_t t1, time_t t2){
    list<int> results ;
    //dates
    struct tm format_t1 = *localtime(&t1);
    int day_t1 = format_t1.tm_mday;
    int month_t1 = format_t1.tm_mon ;
    int year_t1 = format_t1.tm_year;
    
    struct tm format_t2 = *localtime(&t2);
    int day_t2 = format_t2.tm_mday;
    int month_t2 = format_t2.tm_mon ;
    int year_t2 = format_t2.tm_year;
    
    //variable
    
    struct tm format_t ;
    format_t.tm_mon= month_t1 ;
    format_t.tm_mday= day_t1 ;
    format_t.tm_year= year_t1;
    format_t.tm_hour = 0 ;
    format_t.tm_min = 0 ;
    time_t t = mktime(&format_t);
   
    
    list<Sensor*>::iterator it;
    it = l.begin();
    while (it != l.end()) {
        int moyenne = 0 ;
        int nbrJours = 0 ;
        while (format_t.tm_mday!=day_t2 || format_t.tm_mon!=month_t2 || format_t.tm_year!=year_t2){
               moyenne +=(**it).calculateAtmo(t);
               nbrJours ++ ;
               if (format_t.tm_mday!=31)
                 format_t.tm_mday += 1 ;
               else {
                   format_t.tm_mday = 0 ;
                   if (format_t.tm_mon!=11){
                      format_t.tm_mon += 1;
                   }
                   else {
                       format_t.tm_mon = 0 ;
                       format_t.tm_year +=1;
                   }
               }
        }
        results.push_back((int)(moyenne/nbrJours));
        ++it;
    }
    return results ;
}
//-------------------------------------------- Constructeurs - destructeur
DataSet::DataSet() {

}

DataSet::~DataSet() {

}
