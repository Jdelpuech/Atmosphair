#include "FileManager.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
using namespace std;


FileManager::FileManager()
{
	fileSave= nullptr;
}


FileManager::~FileManager()
{
}

bool FileManager::openSave(string path, DataSet dataS)
{
	bool ok = false;
	ifstream f(path.c_str());
	while (!f)
	{
		string type;
		getline(f, type, ';');

		string fpath;
		string tmp;
		getline(f, tmp);
		fpath = tmp.c_str();

		switch (atoi(type.c_str()))
		{
			case 0:
				importDataFromFile(dataS, fpath, 0);
				break;
			case 1:
				importDataFromFile(dataS, fpath, 1);
				break;
			case 2:
				importDataFromFile(dataS, fpath, 2);
				break;
			default:
				cout << "invalid type";
				break;
		}
	}
	return ok;
}

bool FileManager::importDataFromFile(DataSet dataS, string path, int type) {
	ifstream f(path.c_str());
	bool ok = false;
	switch (type)
	{
	case 0:/*fichier de Sensors*/
		while (!f)
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
		while (!f)
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
		while (!f)
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
	return ok;
}


