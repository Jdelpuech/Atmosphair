#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
using namespace std;

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

bool FileManager::save(DataSet *d,  string path, int type)
{
	bool ok = false;
	if (type == 0) {
		d->dropListSensors();
	}
	else if (type == 1) {
		d->dropData();
	}
	else if (type == 2) {
		d->dropDataType();
	}
	if (importDataFromFile(d, path, type)) {
		ifstream f(savePath.c_str());//ouvre sauvegarde
		string complete0 = "";//sensors
		string complete1 = "";//data
		string complete2 = "";//datatype
		if (f) {
			while (!f.eof())
			{
				/*memorise les 3 lignes en substituant celle du meme type que celle en parametre*/
				string oldType;
				getline(f, oldType, ';');

				string oldPath;
				getline(f, oldPath);

				string newPath = oldPath;
				if (stoi(oldType) == type) {
					newPath = path;
				}
				switch (stoi(oldType)) {
				case 0:
					complete0 = oldType + ";" + newPath;
				case 1:
					complete1 = oldType + ";" + newPath;
				case 2:
					complete2 = oldType + ";" + newPath;
				}
			}
		}

		/*reouvre et ecrit les bonnes lignes*/
		ofstream o(savePath.c_str(), ios::trunc);
		if (o)
		{
			o << complete0 << endl;
			o << complete1 << endl;
			o << complete2;
			o.close();
		}
		ok = true;
	}
	return ok;
}


bool FileManager::openSave(DataSet* dataS)
{
	bool ok = false;
	ifstream f(savePath);
	if (f) {
		while (!f.eof())
		{
			string tmp;
			string type;

			getline(f, type, ';');
			//cout << "type :" << type << endl;

			string fpath;
			getline(f, fpath);
			//cout << "path :" << fpath << endl;


			switch (atoi(type.c_str()))
			{
			case 0:
				//cout << "ok" << endl;
				ok = importDataFromFile(dataS, fpath, 0);

				break;
			case 1:
				//cout << "ok" << endl;
				ok = importDataFromFile(dataS, fpath, 1);

				break;
			case 2:
				//cout << "ok" << endl;
				ok = importDataFromFile(dataS, fpath, 2);

				break;
			default:
				//cout << "ok" << endl;
				cout << "invalid type";

				break;
			}
		}
	}
	else {
		cout << "erreur ouverture fichier : " << savePath << endl;
	}
	f.close();
	return ok;
}



bool FileManager::importDataFromFile(DataSet* dataS, string path, int type) {
	ifstream f(path.c_str());
	bool ok = false;
	if (f) {
		switch (type)
		{
		case 0:/*fichier de Sensors*/
			try {
				while (f)
				{
					string id;
					string sLat;
					float lat;
					string sLon;
					float lon;
					string descr;
					string flush;

					getline(f, id, ';');
					//cout <<"id : "<<id << endl;
					getline(f, sLat, ';');
					lat = stod(sLat);
					//cout << "lat : " << lat << endl;
					getline(f, sLon, ';');
					lon = stod(sLon);
					//cout << "lon : " << lon << endl;
					getline(f, descr, ';');
					//cout << "descr : " << descr << endl;
					getline(f, flush);
					Sensor *s = new Sensor(id, lat, lon, descr);

					/*ajout au dataset*/
					dataS->addSensor(s);
					ok = true;
				}
			}
			catch(...){
				cout << "erreur chargement fichier de capteurs" << endl;
			}
			break;
		case 1: /*data*/
			try {
				while (f)
				{
					/*Timestamp;SensoTrID;AttributeID;Value;*/
					struct tm timestamp;
					string sensorId;/*sensorID*/
					string dataTypeId;/*attributeID*/
					float value;/*value*/
					string tmp;

					//debut recuperation temps
					getline(f, tmp, '-');
					timestamp.tm_year = stoi(tmp) - 1900; //year
					getline(f, tmp, '-');
					timestamp.tm_mon = stoi(tmp) - 1;
					getline(f, tmp, 'T');
					timestamp.tm_mday = stoi(tmp);
					getline(f, tmp, ':');
					timestamp.tm_hour = stoi(tmp);
					getline(f, tmp, ':');
					timestamp.tm_min = stoi(tmp);
					getline(f, tmp, '.');
					timestamp.tm_sec = stoi(tmp);
					getline(f, tmp, ';');
					//fin recuperation temps
					time_t finalTime = mktime(&timestamp);
					//std::cout << ctime(&finalTime);

					getline(f, tmp, ';');
					sensorId = tmp;
					//cout << "sensorId : " << sensorId << endl;

					getline(f, tmp, ';');
					dataTypeId = tmp;
					//cout << "dataTypeId : " << dataTypeId << endl;

					getline(f, tmp, ';');
					value = stof(tmp);
					//cout << "value : " << value << endl;

					getline(f, tmp);

					Data *d = new Data(finalTime, value, sensorId, dataTypeId);
					/*ajout au sensor*/
					dataS->getSensorById(sensorId)->addData(d);
					ok = true;
				}
			}
			catch (...) {
				cout << "erreur chargement fichier de données" << endl;
			}
			break;
		case 2: /*dataType*/
			try {
				while (f)
				{
					string attributeId;
					string unit;
					string description;
					string flush;

					getline(f, attributeId, ';');

					getline(f, unit, ';');

					getline(f, description, ';');
					getline(f, flush);

					DataType*dT = new DataType(attributeId, unit, description);
					/*ajout au dataset*/
					dataS->addDataType(dT);
					ok = true;
				}
			}
			catch (...) {
				cout << "erreur chargement fichier de type de données" << endl;
			}
			break;
		default:
			cout << "invalid type"<<endl;
			break;
		}
	}else{
		cout << "erreur ouverture fichier : " << path << endl;
	}
	f.close();
	return ok;
}


