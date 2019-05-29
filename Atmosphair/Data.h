/**************************************************************************************
 Data  -  Interface
 -------------------
 d�but                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //---------- Interface de la classe <Catalogue> (fichier Data.h) ----------------
#if !defined ( Data_H )
#define Data_H
//---------------------------------------------------------------- Interfaces utilis�es
#include <string>
#include <ctime>
class Sensor;
class DataType;
using namespace std;
//-------------------------------------------------------------------------------------
// R�le de la classe <Data>
/*Les fichiers .csv d�finissant les mesures et les types de mesures seront mod�lis�s 
respectivement par les classes Data et DataType avec les m�mes attributs que ceux 
stipul�s dans les fichiers. 
 */

 //-------------------------------------------------------------------------------------
class Data
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------- M�thodes publiques
	inline int getMesureID() {
		return mesureId; 
	}

	inline time_t getTimeStamp() {
		return timestamp; 
	}

	inline double getValue() {
		return value; 
	}

	inline Sensor* getSensor() {
		return sensor; 
	}

	inline DataType* getDataType() {
		return type; 
	}

	//---------------------------------------------------- Constructeurs - destructeur
	Data(int mesureIdD,time_t timestamp,double value,Sensor *sensor, DataType *type);
	// Mode d'emploi : � partir des donn�es fournies par une ligne d'un fichier .csv
	//d�crivant une donn�e, le constructeur permet de mod�liser ce dernier � travers
	//la construction d'un objet Data.
	// Contrat : le fichier .csv est aux normes.


	virtual ~Data();
	// Mode d'emploi : aucun
	// Contrat : aucun

//------------------------------------------------------------------------------ PRIVE
private:
	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ M�thodes prot�g�es

	//------------------------------------------------------------ Attributs prot�g�s
	int mesureId; 
	time_t timestamp; 
	double value; 
	Sensor* sensor; 
	DataType* type;

};



#endif // Data_H

