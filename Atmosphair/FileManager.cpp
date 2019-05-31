#include "FileManager.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
using namespace std;


FileManager::FileManager()
{
	
}


FileManager::~FileManager()
{
}

bool FileManager::openSave(string path, DataSet dataS)
{
	bool ok = false;
	ifstream f(path.c_str());
	while (f)
	{
		cout << "1";
		string tmp;
		string type;
		cout << "2";
		getline(f, tmp, ';');
		cout << tmp;
		cout << "3";
		type = tmp.c_str();
		cout << type;
		tmp = "";

		string fpath;
		getline(f, tmp);
		cout << "4";
		fpath = tmp.c_str();
		tmp = "";
		
		switch (atoi(type.c_str()))
		{
			case 0:
				ok=importDataFromFile(dataS, fpath, 0);
				type = "";
				break;
			case 1:
				ok=importDataFromFile(dataS, fpath, 1);
				type = "";
				break;
			case 2:
				ok=importDataFromFile(dataS, fpath, 2);
				type = "";
				break;
			default:
				cout << "invalid type";
				type = "";
				break;
		}
	}
	f.close();
	return ok;
}

bool FileManager::importDataFromFile(DataSet dataS, string path, int type) {
	ifstream f(path.c_str());
	bool ok = false;
	switch (type)
	{
	case 0:/*fichier de Sensors*/
		while (f)
		{
			string id;
			double lon;
			double lat;
			string descr;
			string tmp;

			getline(f, tmp, ';');
			id= tmp.c_str();
			tmp = "";
			getline(f, tmp, ';');
			lon = atol(tmp.c_str());
			tmp = "";
			getline(f, tmp, ';');
			lat = atol(tmp.c_str());
			tmp = "";
			getline(f, tmp, ';');
			descr = tmp;

			Sensor *toAdd=NULL;
			*toAdd= Sensor(id, lat, lon, descr, false);

			/*ajout au dataset*/
			dataS.addSensor(toAdd);
			
			ok = true;
		}
		break;
	case 1: /*data*/
		while (f)
		{
			/*Timestamp;SensoTrID;AttributeID;Value;*/
			static int id;
			struct tm *timestamp=NULL;/*timestamp*/
			double value;/*value*/
			string sensorId;/*sensorID*/
			string dataTypeId;/*attributeID*/
			string tmp;
  
			/*getline(f, tmp, ';');
			id = tmp.c_str();
			tmp = "";*/
            id++;
			getline(f, tmp, '"');
			tmp="";/*pour enlèver le guimet initial*/
			getline(f, tmp, '-');/* strptime(tmp, sizeof(tmp), , timestamp.);*/
			timestamp->tm_year = atoi(tmp.c_str());
			tmp = "";
			getline(f, tmp, '-');
			timestamp->tm_mon = atoi(tmp.c_str())+1;
			tmp = "";
			getline(f, tmp, 'T');
			timestamp->tm_mday= atoi(tmp.c_str());
			tmp = "";
			getline(f, tmp, ':');
			timestamp->tm_hour = atoi(tmp.c_str());
			tmp = "";
			getline(f, tmp, ':');
			timestamp->tm_min = atoi(tmp.c_str());
			tmp = "";
			getline(f, tmp, '.');
			timestamp->tm_sec = atoi(tmp.c_str());
			tmp = "";
			getline(f, tmp);
			tmp = "";

			getline(f, tmp, ';');
			value= atof(tmp.c_str());
			tmp = "";

			getline(f, tmp, ';');
			sensorId = tmp;
			tmp = "";

			getline(f, tmp, ';');
			dataTypeId = tmp;
			tmp = "";

			time_t finalTime=mktime(timestamp);
			Data *d=NULL;
			*d = Data(id,finalTime, value, sensorId, dataTypeId);
			/*ajout au sensor*/
			(dataS.getSensorById(sensorId)).addData(d);
			ok = true;
		}
		break;
	case 2: /*dataType*/
		while (f)
		{
			string attributeId;
			string unit;
			string description;
			string tmp;

			getline(f, tmp, ';');
			attributeId = tmp.c_str() ;
			tmp = "";
			getline(f, tmp, ';');
			unit = tmp;
			tmp = "";
			getline(f, tmp, ';');
			description = tmp;
			tmp = "";

			DataType*dT=NULL;
			*dT = DataType(attributeId, unit, description);
			/*ajout au dataset*/
			dataS.addDataType(dT);
			ok = true;
		}
		break;
	default:
		cout << "invalid type"  ;
		break;
	}
	f.close();
	return ok;
}


