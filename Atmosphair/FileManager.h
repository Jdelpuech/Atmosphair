/**************************************************************************************
 FileManager  -  Interface
 -------------------
 d�but                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //- Interface de la classe <FileManager> (fichier FileManager.h) ---------
#if !defined ( FileManager_H )
#define FileManager_H
//---------------------------------------------------------------- Interfaces utilis�es

#include <string>
#include <time.h>
#include <iostream>
#include <fstream>
#include "DataSet.h"
#include "DataType.h"
#include "Data.h"
#include "Sensor.h"

//-------------------------------------------------------------------------------------
// R�le de la classe <FileManager>
/*
 */
 //-------------------------------------------------------------------------------------
class FileManager
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------------ M�thodes publiques


	//---------------------------------------------------- Constructeurs - destructeur
	FileManager();
	virtual ~FileManager(); 
	// Mode d'emploi : aucun
    // Contrat : aucun

	bool importDataFromFile(DataSet* dataS, std::string path, int type);
	bool openSave(DataSet* dataS);
	bool save(std::string path, int type);

	//------------------------------------------------------------------------------ PRIVE
private:


	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ M�thodes prot�g�es
	std::string const savePath="sauvegardes.txt";

	//------------------------------------------------------------ Attributs prot�g�s

};
#endif // FileManager_H


