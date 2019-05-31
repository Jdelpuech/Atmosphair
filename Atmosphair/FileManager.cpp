#include "FileManager.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
using namespace std;





FileManager::FileManager(string save)
{
	savef = save;
}

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

bool FileManager::save(DataSet* dataS, string path, int type)
{
	bool ok = true;
	ifstream f(savef.c_str());//ouvre sauvegarde
	if (f) {
		while (!f.eof())
		{
			/*memorise les 3 lignes en sostitunt cellle du meme type que celle en parametre*/
			string tmp;
			string typePrec;

			getline(f, typePrec, ';');
			cout << "type :" << typePrec << endl;

			string fpath;
			getline(f, fpath);
			cout << "path :" << fpath << endl;

			string complete1="";

			if (atoi(typePrec.c_str()) != type){
				complete1 =typePrec + ';' + fpath;
			}
			else 
			{
				complete1 = type + ';';
				complete1+=path;
			}

			typePrec = "";
			fpath = "";
			getline(f, typePrec, ';');
			cout << "type :" << typePrec << endl;

			
			getline(f, fpath);
			cout << "path :" << fpath << endl;

			string complete2 = "";

			if (atoi(typePrec.c_str()) != type) {
				complete2 = typePrec + ';' + fpath;
			}
			else
			{
				complete2 = type + ';';
				complete2+= path;
			}

			typePrec = "";
			fpath = "";
			getline(f, typePrec, ';');
			cout << "type :" << typePrec << endl;

			
			getline(f, fpath);
			cout << "path :" << fpath << endl;

			string complete3 = "";

			if (atoi(typePrec.c_str()) != type) {
				complete3 = typePrec + ';' + fpath;
			}
			else
			{
				complete3 = type + ';';
				complete3+=path;
				importDataFromFile(dataS, path, type);
			}

			/*efface le contenu*/
			f.clear();
			f.close();

			/*reouvre et ecrit les bonnes lignes*/
			ofstream o(savef.c_str());
			if (o.is_open())
			{
				o.write(complete1.c_str(), sizeof(complete1.c_str()));
				o.write(complete2.c_str(), sizeof(complete2.c_str()));
				o.write(complete3.c_str(), sizeof(complete3.c_str()));
			}
			o.close();
		}
	}
	return ok;
}


bool FileManager::openSave(string path, DataSet* dataS)
{
	bool ok = false;
	ifstream f(path.c_str());
	if (f) {
		while (!f.eof())
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



bool FileManager::importDataFromFile(DataSet* dataS, string path, int type) {
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
				dataS->addSensor(s);

				ok = true;
			}
			break;
		case 1: /*data*/
			while (f)
			{
				/*Timestamp;SensoTrID;AttributeID;Value;*/
				struct tm timestamp;
				string sensorId;/*sensorID*/
				string dataTypeId;/*attributeID*/
				double value;/*value*/
				string tmp;

				//debut recuperation temps
				getline(f, tmp, '-');
				timestamp.tm_year = stoi(tmp)-1900; //year
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
				getline(f, tmp,';');
				//fin recuperation temps
				time_t finalTime = mktime(&timestamp);
				std::cout << ctime(&finalTime);

				getline(f, tmp, ';');
				sensorId = tmp;
				cout << "sensorId : " << sensorId << endl;

				getline(f, tmp, ';');
				dataTypeId = tmp;
				cout << "dataTypeId : " << dataTypeId << endl;

				getline(f, tmp, ';');
				value = stof(tmp);
				cout << "value : " << value << endl;

				getline(f, tmp);
				
				Data *d = new Data(finalTime, value, sensorId, dataTypeId);
				/*ajout au sensor*/
				dataS->getSensorById(sensorId)->addData(d);
				ok = true;
			}
			break;
		case 2: /*dataType*/
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


