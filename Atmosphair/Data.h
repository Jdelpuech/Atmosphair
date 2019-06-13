/**************************************************************************************
 Data  -  Interface
 -------------------
 debut                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //---------- Interface de la classe <Catalogue> (fichier Data.h) ----------------
#if !defined ( Data_H )
#define Data_H
//---------------------------------------------------------------- Interfaces utilisees
#include <string>
#include <ctime>
class Sensor;
class DataType;
using namespace std;
//-------------------------------------------------------------------------------------
// Role de la classe <Data>
/*Les fichiers .csv definissant les mesures et les types de mesures seront modelises 
respectivement par les classes Data et DataType avec les memes attributs que ceux 
stipules dans les fichiers. 
 */

 //-------------------------------------------------------------------------------------
class Data
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------- Methodes publiques

	inline time_t getTimeStamp() {
		return timestamp; 
	}
	// Mode d'emploi : renvoie la date de prise de la donnée 
	// Contrat : aucun

	inline float getValue() {
		return value; 
	}
	// Mode d'emploi : renvoie la valeur de la donnée
	// Contrat : aucun

    
    inline string getSensorId(){
        return sensorId; 
    }
	// Mode d'emploi : renvoie l'identifiant du sensor
	// Contrat : aucun

	inline string getDataTypeId() {
		return dataTypeId;
	}
	// Mode d'emploi : renvoie le type de données
	// Contrat : aucun

	string toString();
	// Mode d'emploi : renvoie une chaine de caracteres avec toute la description de 
	//l'objet formaté pour la sortie
	// Contrat : aucun

	//---------------------------------------------------- Constructeurs - destructeur
	Data(time_t timestamp, float value, string sensorId, string dataTypeId);
	// Mode d'emploi : a partir des donnees fournies par une ligne d'un fichier .csv
	//decrivant une donnee, le constructeur permet de modeliser ce dernier a travers
	//la construction d'un objet Data.
	// Contrat : le fichier .csv est aux normes.

	virtual ~Data();
	// Mode d'emploi : aucun
	// Contrat : aucun

//------------------------------------------------------------------------------ PRIVE
private:
	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ Methodes protegees

	//------------------------------------------------------------ Attributs proteges
	time_t timestamp; 
	float value; 
	string sensorId;
	string dataTypeId;

};



#endif // Data_H

