/**************************************************************************************
 FileManager  -  Interface
 -------------------
 début                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //- Interface de la classe <FileManager> (fichier FileManager.h) ---------
#if !defined ( FileManager_H )
#define FileManager_H
//---------------------------------------------------------------- Interfaces utilisées

#include <string>
#include <time.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include "DataSet.h"
#include "DataType.h"
#include "Data.h"
#include "Sensor.h"

using namespace std;

//-------------------------------------------------------------------------------------
// Rôle de la classe <FileManager>
/*
 */
 //-------------------------------------------------------------------------------------
class FileManager
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------------ Méthodes publiques


	//---------------------------------------------------- Constructeurs - destructeur
	FileManager();

	virtual ~FileManager(); 
	// Mode d'emploi : aucun
    // Contrat : aucun

	bool importDataFromFile(DataSet data, string path, int type);
	bool openSave(string path, DataSet dataS);


	//------------------------------------------------------------------------------ PRIVE
private:


	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ Méthodes protégées
	/*FILE * fileSave;*/


	//------------------------------------------------------------ Attributs protégés

};



#endif // FileManager_H


