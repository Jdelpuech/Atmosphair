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
#include "FileManager.h"
#include "Sensor.h"
#include "User.h"
#include "DataType.h"
#include "Data.h"
#include "DataSet.h"


//-------------------------------------------------------------------------------- PUBLIC
int main(){

	std::cout << "Test Julie" << endl;
    struct tm instant ;
    instant.tm_mon= 1-1 ;
    instant.tm_mday= 1 ;
    instant.tm_year= 2017-1900;
    instant.tm_hour = 1 ;
    instant.tm_min = 0 ;
	instant.tm_sec = 0;
    time_t time = mktime(&instant);
    
    //créations type de données
    DataType type_O3 = DataType("O3","µg/m3","concentration d'ozone");
    DataType type_NO2 = DataType("NO2","µg/m3","concentration de dioxyde d'azote");
    DataType type_SO2 = DataType("SO2","µg/m3","concentration de dioxyde de soufre");
    DataType type_PM10 = DataType("PM10","µg/m3","concentration de particules fines");
    
    
    //création sensors
    Sensor sensor_0 = Sensor("Sensor0",(double)-8.15758888291083,(double)-34.7692487876719,"0",false);
    Sensor sensor_1= Sensor("Sensor1",(double)-30.0647387677174,(double)-76.3439147576429,"1",false);
	Sensor sensor_2 = Sensor("Sensor2", (double)-8.0647387677174, (double)-34.3439147576429, "2", false);
	Sensor sensor_3 = Sensor("Sensor3", (double)-30.1, (double)-76.1, "3", false);
    
    //une vague de données
    Data * data_0 = new Data(0,time,67.9284748555273,"Sensor0","O3");
    Data * data_1 = new Data(1,time,98.979984192197,"Sensor0","NO2");
    Data * data_2 = new Data(2,time,119.423041339039,"Sensor0","SO2");
    Data * data_3 = new Data(3,time,16.7564963001065,"Sensor0","PM10");
    instant.tm_hour += 1 ;
    time = mktime(&instant);
    Data * data_4 = new Data(4,time,36.7797600526823,"Sensor0","O3");
    Data * data_5 = new Data(5,time,80.2280346451481,"Sensor0","NO2");
    Data * data_6 = new Data(6,time,38.151540049253,"Sensor0","SO2");
    Data * data_7 = new Data(7,time,1.99603267330184,"Sensor0","PM10");
    sensor_0.addData(data_0);
    sensor_0.addData(data_1);
    sensor_0.addData(data_2);
    sensor_0.addData(data_3);
    sensor_0.addData(data_4);
    sensor_0.addData(data_5);
    sensor_0.addData(data_6);
    sensor_0.addData(data_7);

	sensor_2.addData(data_0);
	sensor_2.addData(data_1);
	sensor_2.addData(data_2);
	sensor_2.addData(data_3);
	sensor_2.addData(data_4);
	sensor_2.addData(data_5);
	sensor_2.addData(data_6);
	sensor_2.addData(data_7);
    std::list<Data *> listeDonnees = sensor_0.getData();

    int indice = sensor_0.calculateAtmo(time);
    std::cout <<"ATMO : "<<indice << endl ;
    
    double result = DataSet::calculateDistance(-8.157588883, -34.76924879, -8.0647387677174,-34.3439147576429);
    std::cout << result << endl <<endl;

	std::cout << "Test Grazia" << endl;
	DataSet d = DataSet();
	FileManager fm = FileManager();

	/*string s = "./sauvegardes.txt";*/

	fm.openSave("C:/Users/hcann/Documents/INSA/IF/GL-UML/Jdelpuech/Atmosphair/Atmosphair/sauvegardes.txt", d);

	listSensor liSensor =d.getListSensors();
	std::cout << "SENSORS" << endl;
	listSensor::iterator it;
	it = liSensor.begin();
	while (it != liSensor.end()) {
		cout << (**it).toString()<< endl;
		++it;
	}
	/*std::cout << "DATA" << endl;
	for (list<Sensor*>::iterator it = lS.begin(); it != lS.end(); ++it)
	{
		list<Data*> lD=(*(*it)).getData(); 
		for (listData::iterator it2 = lD.begin(); it2 != lD.end(); ++it)
		{
			cout << (*(*it2)).toString() << endl;
		}
	}

	list<DataType*> lDT = d.getListDataType();
	std::cout << "DATA_TYPE" << endl;
	for (list<DataType*>::iterator it = lDT.begin(); it != lDT.end(); ++it)
	{
		cout << (*(*it)).toString() << endl;
	}*/

	cout << endl << "Test Hugo" << endl;

	DataSet d1 = DataSet();

	d1.addSensor(&sensor_0);
	d1.addSensor(&sensor_1);
	d1.addSensor(&sensor_2);
	d1.addSensor(&sensor_3);

	listSensor liSen= d1.getListSensorsInZone((double)-8.15758888291083, (double)-34.7692487876719, (double)100);
	listSensor::iterator it1;
	it1 = liSen.begin();
	while (it1 != liSen.end()) {
		cout << (**it1).getDescription()<<endl;
		++it1;
	}

	list<int> atmo = d1.generateResultAtmo(liSen, time);
	list<int>::iterator it2;
	it2 = atmo.begin();
	while (it2 != atmo.end()) {
		cout << *it2 << endl;
		++it2;
	}

	return 0;
}
