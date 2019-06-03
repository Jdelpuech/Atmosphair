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

std::list<Data*> DataSet::generateDataSensor(Sensor s, time_t t1, time_t t2)
{
	//Sensor* s = getSensorById(id);
	list<Data*> result;
    list<Data*> all = s.getData(); 
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
std::vector<double> DataSet::generateResultGas(Sensor s, time_t t1,time_t t2){
    vector<double> resultats ; 
    list<Data*> dataGas = generateDataSensor(s,t1,t2); 
    int NO2[10] ={0}; 
    int O3[10]={0};
    int PM10[10]={0};
    int SO2[10]={0} ; 
    int nbrNO2 = 0 ; 
    int nbrO3 = 0 ; 
    int nbrPM10 = 0 ; 
    int nbrSO2 = 0 ; 
    std::list<Data*>::const_reverse_iterator it; 
    for (it = dataGas.rbegin(); it != dataGas.rend(); ++it){
        if (nbrSO2!=10 && ((**it).getDataTypeId().compare("SO2")==0)){
            cout<<"1"<<endl ; 
            SO2[nbrSO2]=(**it).getValue(); 
            nbrSO2++; 
        }
        if (nbrO3!=10 && ((**it).getDataTypeId().compare("O3")==0)){
            cout<<"1"<<endl ; 
            O3[nbrO3]=(**it).getValue();
            nbrO3++;  
        }
        if (nbrNO2!=10 && ((**it).getDataTypeId().compare("NO2")==0)){
            cout<<"1"<<endl ; 
            NO2[nbrNO2]=(**it).getValue(); 
            nbrNO2++; 
        }
        if (nbrPM10!=10 && ((**it).getDataTypeId().compare("PM10")==0)){
            cout<<"1"<<endl ; 
            PM10[nbrPM10]=(**it).getValue(); 
            nbrPM10++; 
        }
    }

    for (int i=0 ; i<10 ; i++){
        cout<<i<< endl ;
        resultats[i]=SO2[i]; 
    }
    for (int i=10 ; i<20 ; i++){
        resultats[i]=O3[i]; 
    }
    for (int i=20 ; i<30 ; i++){
        resultats[i]=NO2[i]; 
    }
    for (int i=30 ; i<40 ; i++){
        resultats[i]=PM10[i]; 
    }
    cout << "FIN"<< endl ; 
    return resultats; 
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

User * DataSet::connectionRequest(string user, string password) {
	listUser::iterator it;
	it = liUser.begin();
	while (it != liUser.end()) {
		cout << (**it).getLogin() << " ; " << (**it).getMdp() << endl;
		if ((**it).getLogin()==user && (**it).getMdp()==password) {
			return (*it);
		}
		++it;
	}
	return nullptr;
}

listSensor DataSet::getListSensorsInZone(double lat, double lon, double rayon) {
	listSensor result = listSensor();
	listSensor::iterator it;
	it = liSensor.begin();
	while (it != liSensor.end()) {
		double distance = calculateDistance(lat, lon, (**it).getLatitude(), (**it).getLongitude());
        if (distance <= rayon) {
			result.push_back((*it));
		}
		++it;
	}
	return result;
}

//A TESTER 
vector<double> DataSet::generateResultGas(listSensor l, time_t t, string choix){
    vector<double> results(4) ;
    if (choix.find('1') != string::npos){
        listSensor::iterator it;
        it = l.begin();
        double sum = 0 ; 
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
        double sum = 0 ; 
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
        double sum = 0 ; 
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
        double sum = 0 ; 
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
list<int> DataSet::generateResultAtmo(listSensor l, time_t t1, time_t t2){
    list<int> results ;
    //dates
    struct tm format_t1 = *localtime(&t1);
    
	listSensor::iterator it;
    it = l.begin();
    while (it != l.end()) {
        int moyenne = 0 ;
        int nbrJours = 0 ;
        int nbrIncrementation = 0 ; 
        //cout << difftime(t2,t1) << endl ; 
        while (difftime(t2,t1)>0){
               ++nbrIncrementation ; 
               moyenne +=(**it).calculateAtmo(t1);
               nbrJours ++ ;
               if (format_t1.tm_mday!=31)
                 format_t1.tm_mday += 1 ;
               else {
                   format_t1.tm_mday = 0 ;
                   if (format_t1.tm_mon!=11){
                      format_t1.tm_mon += 1;
                   }
                   else {
                       format_t1.tm_mon = 0 ;
                       format_t1.tm_year +=1;
                   }
            }
            t1 = mktime(&format_t1); 
        }
        //cout <<"nombre incrémentation : "<<nbrIncrementation << endl ; 
        results.push_back((int)(moyenne/nbrJours));
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
