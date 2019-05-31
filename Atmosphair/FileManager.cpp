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
	if (f) {
		while (f)
		{
			string tmp;
			string type;

			getline(f, type, ';');
			cout << "type :" << type << endl;

			string fpath;
			getline(f, fpath);
			cout << "path :" << fpath << endl;


			switch (atoi(type.c_str()))
			{
			case 0:
				cout << "ok" << endl;
				ok = importDataFromFile(dataS, fpath, 0);

				break;
			case 1:
				cout << "ok" << endl;
				ok = importDataFromFile(dataS, fpath, 1);

				break;
			case 2:
				cout << "ok" << endl;
				ok = importDataFromFile(dataS, fpath, 2);

				break;
			default:
				cout << "ok" << endl;
				cout << "invalid type";

				break;
			}
		}
	}
	else {
		cout << "erreur ouverture fichier : " << path << endl;
	}
	f.close();
	return ok;
}

bool FileManager::importDataFromFile(DataSet dataS, string path, int type) {
	ifstream f(path.c_str());
	bool ok = false;
	if (f) {
		switch (type)
		{
		case 0:/*fichier de Sensors*/
			while (f)
			{
				string id;
				string sLat;
				double lat;
				string sLon;
				double lon;
				string descr;
				string flush;

				getline(f, id, ';');
				cout <<"id : "<<id << endl;
				getline(f, sLat, ';');
				lat = stod(sLat);
				cout << "lat : " << lat << endl;
				getline(f, sLon, ';');
				lon = stod(sLon);
				cout << "lon : " << lon << endl;
				getline(f, descr, ';');
				cout << "descr : " << descr << endl;
				getline(f, flush);
				Sensor *s = new Sensor(id, lat, lon, descr);

				/*ajout au dataset*/
				dataS.addSensor(s);

				ok = true;
			}
			break;
		case 1: /*data*/
			while (f)
			{
				/*Timestamp;SensoTrID;AttributeID;Value;*/
				static int id;
				struct tm *timestamp = NULL;/*timestamp*/
				double value;/*value*/
				string sensorId;/*sensorID*/
				string dataTypeId;/*attributeID*/
				string tmp;

				/*getline(f, tmp, ';');
				id = tmp.c_str();
				tmp = "";*/
				id++;
				getline(f, tmp, '"');
				tmp = "";/*pour enl�ver le guimet initial*/
				getline(f, tmp, '-');/* strptime(tmp, sizeof(tmp), , timestamp.);*/
				timestamp->tm_year = atoi(tmp.c_str());
				tmp = "";
				getline(f, tmp, '-');
				timestamp->tm_mon = atoi(tmp.c_str()) + 1;
				tmp = "";
				getline(f, tmp, 'T');
				timestamp->tm_mday = atoi(tmp.c_str());
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
				value = atof(tmp.c_str());
				tmp = "";

				getline(f, tmp, ';');
				sensorId = tmp;
				tmp = "";

				getline(f, tmp, ';');
				dataTypeId = tmp;
				tmp = "";

				time_t finalTime = mktime(timestamp);
				Data *d = NULL;
				*d = Data(id, finalTime, value, sensorId, dataTypeId);
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
				attributeId = tmp.c_str();
				tmp = "";
				getline(f, tmp, ';');
				unit = tmp;
				tmp = "";
				getline(f, tmp, ';');
				description = tmp;
				tmp = "";

				DataType*dT = NULL;
				*dT = DataType(attributeId, unit, description);
				/*ajout au dataset*/
				dataS.addDataType(dT);
				ok = true;
			}
			break;
		default:
			cout << "invalid type";
			break;
		}
	}else{
		cout << "erreur ouverture fichier : " << path << endl;
	}
	f.close();
	return ok;
}


