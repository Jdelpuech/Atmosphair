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
#include <vector>
#include <cmath> 
using namespace std;
//--------------------------------------------------------------------- Include personnel
#include "DataSet.h"
#include "User.h"
#include "Sensor.h"
#include "DataType.h"
#include "Data.h"
//-------------------------------------------------------------------------------- PUBLIC
//----------------------------------------------------- M�thodes publiques

std::list<Data*> DataSet::generateDataSensor(Sensor * s, time_t t1, time_t t2)
{
	//Sensor* s = getSensorById(id);
	list<Data*> result;
    list<Data*> all = s->getData(); 
	listData::iterator it;
	it = all.begin(); 
	while (it != all.end()) {
		if ((difftime(t1, (**it).getTimeStamp()) <= 0) && (difftime(t2, (**it).getTimeStamp()) >= 0)) {
			result.push_back(*it);
		}
		++it;
	}
	return result;
}

vector<Data *> DataSet::generateResultGas(Sensor * s, time_t t1,time_t t2){
	vector<Data*> resultats;
    list<Data*> dataGas = generateDataSensor(s,t1,t2); 
	int nbrSO2 = 0;
    int nbrO3 = 0 ;
	int nbrNO2 = 0;
    int nbrPM10 = 0 ; 
     
    std::list<Data*>::iterator it;
	it = dataGas.begin();
	while (it != dataGas.end()) {
		if (nbrSO2 != 10 && ((**it).getDataTypeId().compare("SO2") == 0)) {
			
			resultats.push_back(*it);
			nbrSO2++;
		}
		if (nbrO3 != 10 && ((**it).getDataTypeId().compare("O3") == 0)) {
			
			resultats.push_back(*it);
			nbrO3++;
		}
		if (nbrNO2 != 10 && ((**it).getDataTypeId().compare("NO2") == 0)) {
			
			resultats.push_back(*it);
			nbrNO2++;
		}
		if (nbrPM10 != 10 && ((**it).getDataTypeId().compare("PM10") == 0)) {
			
			resultats.push_back(*it);
			nbrPM10++;
		}
		it++;
	}
    return resultats; 
}

std::list<pair<Sensor*, Sensor*> > DataSet::generateSimilarity(time_t t1, time_t t2)
{	
	std::list<pair<Sensor*, Sensor*> > result;
	struct tm instant1 = *localtime(&t1);

	listSensor liSensor = getListSensors();
	listSensor::iterator it1;
	it1 = liSensor.begin();

	while (difftime(t2, t1) > 0) {
		while (it1 != liSensor.end()) {
			int atmo1 = (**it1).calculateAtmo(t1);
			listSensor::iterator it2;
			it2 = it1;
			it2++;
			time_t t3 = t1;
			while (difftime(t2, t3)>0){
				while (it2 != liSensor.end()) {
					int atmo2 = (**it2).calculateAtmo(t3);
					if (atmo1 == atmo2) {
						result.push_back(make_pair((*it1), (*it2)));
					}
					it2++;
				}
				struct tm instant2 = *localtime(&t3);
				instant2.tm_mday++;
				t3 = mktime(&instant2);
			}
			it1++;
		}
		struct tm instant1 = *localtime(&t1);
		instant1.tm_mday++;
		t1 = mktime(&instant1);
	}
	return result;
}

listSensor DataSet::getListDysfonctionningSensors()
{
	listSensor result;
	listSensor::iterator it;
	it = liSensor.begin();
	while (it != liSensor.end()) {
		if ((**it).getDysfonctionning() == true) {
			result.push_back((*it));
		}
		++it;
	}
	return result;
}

listSensor DataSet::getListSensors() 
{
    return liSensor ;
}

void DataSet::addSensor(Sensor *sensor) 
{
	liSensor.push_back(sensor);
}

void DataSet::addDataType(DataType *dataType) 
{
	liDataType.push_back(dataType);
}

Sensor* DataSet::getSensorById(string id) {
    Sensor * res = nullptr;
    listSensor::iterator it = liSensor.begin();
    while (it != liSensor.end()) {
        if ((**it).getSensorID().compare(id)==0){
            res =*it;
        }
        
        it++;
    }
    
    return res;
}

void DataSet::addUser(User *user)
{
	liUser.push_back(user);
}

// Cette fonction converti les degres en radiant
float deg2rad(float deg) {
	return (deg * M_PI / 180);
}


float DataSet::calculateDistance(float lat1, float lon1, float lat2, float lon2){
	float lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat1);
	lon1r = deg2rad(lon1);
	lat2r = deg2rad(lat2);
	lon2r = deg2rad(lon2);
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	return 2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

User * DataSet::connectionRequest(string user, string password) {
	listUser::iterator it;
	it = liUser.begin();
	while (it != liUser.end()) {

		if ((**it).getLogin()==user && (**it).getMdp()==password) {
			return (*it);
		}
		++it;
	}
	return nullptr;
}

listSensor DataSet::getListSensorsInZone(float lat, float lon, float rayon) {
	listSensor result = listSensor();
	listSensor::iterator it;
	it = liSensor.begin();
	while (it != liSensor.end()) {
		float distance = calculateDistance(lat, lon, (**it).getLatitude(), (**it).getLongitude());
        if (distance <= rayon) {
			result.push_back((*it));
		}
		++it;
	}
	return result;
}

//A TESTER 
vector<float> DataSet::generateResultGas(listSensor l, time_t t, string choix){
    vector<float> results(4) ;
    if (choix.find('1') != string::npos){
        listSensor::iterator it;
        it = l.begin();
        float sum = 0 ; 
        int nbrData = 0 ; 
        while (it != l.end()) {
           sum+= (**it).calculateMoyenneGaz(t,"O3"); 
           nbrData++ ; 
           it++; 
        }
        if (nbrData!=0)
            results[0]= (sum/nbrData); 
        else 
            results[0]= 0;
    }
    if (choix.find('2') != string::npos){
        listSensor::iterator it;
        it = l.begin();
        float sum = 0 ; 
        int nbrData = 0 ; 
        while (it != l.end()) {
           sum+= (**it).calculateMoyenneGaz(t,"SO2"); 
           nbrData++ ; 
           it++; 
        }
        if (nbrData!=0)
            results[1]= (sum/nbrData);
        else 
            results[1]= 0;
    }
    if (choix.find('3') != string::npos){
        listSensor::iterator it;
        it = l.begin();
        float sum = 0 ; 
        int nbrData = 0 ; 
        while (it != l.end()) {
           sum+= (**it).calculateMoyenneGaz(t,"NO2"); 
           nbrData++ ; 
           it++; 
        }
        if (nbrData!=0)
            results[2]= (sum/nbrData);
        else 
            results[2]= 0;
    }
    if (choix.find('4') != string::npos){
        listSensor::iterator it;
        it = l.begin();
        float sum = 0 ; 
        int nbrData = 0 ; 
        while (it != l.end()) {
           sum+= (**it).calculateMoyenneGaz(t,"PM10"); 
           nbrData++ ; 
           it++; 
        }
        if (nbrData!=0)
            results[3]= (sum/nbrData);
        else 
            results[3]= 0;
    }

    return results ; 
}

//A TESTER -> OK
list<int> DataSet::generateResultAtmo(listSensor l, time_t t){
    list<int> results ;
	listSensor::iterator it;
    it = l.begin();
    while (it != l.end()) {
        results.push_back((**it).calculateAtmo(t));
        ++it;
    }
    return results ; 
}
//A TESTER
list<float> DataSet::generateResultAtmo(listSensor l, time_t t1, time_t t2){
    list<float> results ;
    //dates
    struct tm format_tmp = *localtime(&t1);
    
	listSensor::iterator it;
    it = l.begin();
    while (it != l.end()) {
        float moyenne = 0 ;
        int nbrJours = 0 ;
        //cout << difftime(t2,t1) << endl ; 
		struct tm format_tmp = *localtime(&t1);
		time_t t_tmp = mktime(&format_tmp);
        while (difftime(t2,t_tmp)>=0){
			int tmp = (**it).calculateAtmo(t1);
			if (tmp > 0) {
				moyenne += tmp;
				nbrJours++;
			}
			if (format_tmp.tm_mday!=31)
				format_tmp.tm_mday += 1 ;
			else {
				format_tmp.tm_mday = 0 ;
                if (format_tmp.tm_mon!=11){
				    format_tmp.tm_mon += 1;
                }
                else {
			 	    format_tmp.tm_mon = 0 ;
			 	    format_tmp.tm_year +=1;
                }
            }
            t_tmp = mktime(&format_tmp);
        }
        int m = -1 ;
        if (nbrJours!=0){
            m = (float)(moyenne/(float)nbrJours) ; 
        }
        results.push_back(m); 
        ++it;
    }
    return results ;
}

listUser DataSet::getListUsers()
{
    return liUser;
}

listDataType DataSet::getListDataType()
{
	return liDataType;
}

void DataSet::dropListSensors() {
	listSensor::iterator it;
	it = liSensor.begin();
	while (it != liSensor.end()) {
		(*it)->dropData();
		delete((*it));
		it++;
	}
	liSensor.clear();
}

void DataSet::dropData() {
	listSensor::iterator it;
	it = liSensor.begin();
	while (it != liSensor.end()) {
		(*it)->dropData();
		it++;
	}
}

void DataSet::dropDataType() {
	listDataType::iterator it;
	it = liDataType.begin();
	while (it != liDataType.end()) {
		delete (*it);
		it++;
	}
	liDataType.clear();
}

//-------------------------------------------- Constructeurs - destructeur
DataSet::DataSet() {

}

DataSet::~DataSet() {

}
