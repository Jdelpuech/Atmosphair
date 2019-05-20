/**************************************************************************************
 Data  -  Interface
 -------------------
 début                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //---------- Interface de la classe <Catalogue> (fichier Data.h) ----------------
#if !defined ( Data_H )
#define Data_H
//---------------------------------------------------------------- Interfaces utilisées

#include <string>
#include <ctime>

#include "Sensor.h"
//-------------------------------------------------------------------------------------
// Rôle de la classe <Data>
/*Les fichiers .csv définissant les mesures et les types de mesures seront modélisés 
respectivement par les classes Data et DataType avec les mêmes attributs que ceux 
stipulés dans les fichiers. 
 */

 //-------------------------------------------------------------------------------------
class Data
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------- Méthodes publiques


	//---------------------------------------------------- Constructeurs - destructeur
	Data(int DataImesureIdD,time_t timeStamp,double value,Sensor sensor);
	// Mode d'emploi : à partir des données fournies par une ligne d'un fichier .csv
	//décrivant une donnée, le constructeur permet de modéliser ce dernier à travers
	//la construction d'un objet Data.
	// Contrat : le fichier .csv est aux normes.


	virtual ~Data();
	// Mode d'emploi : aucun
	// Contrat : aucun

//------------------------------------------------------------------------------ PRIVE
private:


	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ Méthodes protégées

	//------------------------------------------------------------ Attributs protégés
	int DataID;
	double lon;
	double lat;
	string description;
	bool dysfonctionning;
};



#endif // Data_H

