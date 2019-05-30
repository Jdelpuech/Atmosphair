/**************************************************************************************
 ApplicationManager  -  Réalisation
 -------------------
 début                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air
 
 ***************************************************************************************/

//-- Réalisation de la classe <ApplicationManager> (fichier ApplicationManager.cpp) ----

//------------------------------------------------------------------------------ INCLUDE
//---------------------------------------------------------------------- Include système
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

//--------------------------------------------------------------------- Include personnel
#include "ApplicationManager.h"
#include "Sensor.h"
#include "User.h"
#include "DataType.h"
#include "Data.h"
#include "DataSet.h"


//-------------------------------------------------------------------------------- PUBLIC
int main(){
    struct tm * instant;
    instant->tm_mon= 1 ;
    instant->tm_mday= 1 ;
    instant->tm_year= 2017;
    instant->tm_hour = 1 ;
    instant->tm_min = 0 ;
    time_t time = mktime(instant);
    
    //créations type de données
    DataType type_O3 = DataType("O3","µg/m3","concentration d'ozone");
    DataType type_NO2 = DataType("NO2","µg/m3","concentration de dioxyde d'azote");
    DataType type_SO2 = DataType("SO2","µg/m3","concentration de dioxyde de soufre");
    DataType type_PM10 = DataType("PM10","µg/m3","concentration de particules fines");
    
    //création sensors
    Sensor sensor_0 = Sensor("Sensor0",(long)-8.15758888291083,(long)-34.7692487876719,"",false);
    Sensor sensor_1= Sensor("Sensor1",(long)-30.0647387677174,(long)-76.3439147576429,"",false);
    
    //une vague de données
    Data data_0 = Data(0,time,67.9284748555273,"Sensor0","O3");
    Data data_1 = Data(1,time,98.979984192197,"Sensor0","NO2");
    Data data_2 = Data(2,time,119.423041339039,"Sensor0","SO2");
    Data data_3 = Data(3,time,16.7564963001065,"Sensor0","PM10");
    
    double result = DataSet::calculateDistance(-8.157588883, -34.76924879, -30.06473877, -76.34391476);
    std::cout << result;
	return 0; 
}
