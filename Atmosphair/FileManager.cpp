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

bool FileManager::importDataFromFile(DataSet dataS, string path, int type) {
	ifstream f(path.c_str());
	bool ok = false;
	switch (type)
	{
	case 0:/*fichier de Sensors*/
		while (!f)
		{
			int id;
			long lon;
			long lat;
			string descr;
			string tmp;

			getline(f, tmp, ';');
			id= atoi(tmp.c_str());
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
			int id;
			struct tm *timestamp=NULL;/*timestamp*/
			double value;/*value*/
			string sensorId;/*sensorID*/
			string dataTypeId;/*attributeID*/
			string tmp;

			getline(f, tmp, ';');
			id = atoi(tmp.c_str());
			tmp = "";

			getline(f, tmp, '-');/* strptime(tmp, sizeof(tmp), , timestamp.);*/
			timestamp->tm_year = atoi(tmp.c_str());
			tmp = "";
			getline(f, tmp, '-');
			timestamp->tm_mon = atoi(tmp.c_str());
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
			dataS.getSensorById(id).addData(d);
			ok = true;
		}
		break;
	case 2: /*dataType*/
		while (!f)
		{
			int attributeId;
			string unit;
			string description;
			string tmp;

			getline(f, tmp, ';');
			attributeId = atoi(tmp.c_str()); ;
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