/**************************************************************************************
 FileManager  -  Interface
 -------------------
 debut                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //- Interface de la classe <FileManager> (fichier FileManager.h) ---------
#if !defined ( FileManager_H )
#define FileManager_H
//---------------------------------------------------------------- Interfaces utilisees
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>

#include "DataSet.h"
#include "DataType.h"
#include "Data.h"
#include "Sensor.h"

//-------------------------------------------------------------------------------------
// Role de la classe <FileManager>
/* La classe FileManager s'occupe de la lecture/ecriture de fichiers sources et fichiers 
historiques. 
 */
 //-------------------------------------------------------------------------------------
class FileManager
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------------ Methodes publiques
    bool importDataFromFile(DataSet* dataS, std::string path, int type);
	// Mode d'emploi : importe les donnees d'un fichier path d'un type (Sensor,DatType,Data)
	//et les ajoute au dataSet dataS. 
    // Contrat : aucun

	bool openSave(DataSet* dataS);
	// Mode d'emploi : recopie en memoire l'ensemble de donnees dernierement ajoute. modifie le 
	//dataset passe en parametre afin qu'il integre ces donnees.
    // Contrat : aucun

	bool save(DataSet* dataS,std::string path, int type);
	// Mode d'emploi : supprime en memoire un ensemble de donnees de type type 
	// (0 : sensors, 1 : Data, 2 : DataType) afin de charger ces donnees depuis le fichier path
	//fait une sauvegarde de ce nouveau ensemble de donnees. 
	
    // Contrat : les fichiers correspondent. Aucune verification n'est faite notamment sur les liens entre 
	//fichiers. (les sensors de Data doivent exister dans Sensors par exemple)

	//---------------------------------------------------- Constructeurs - destructeur
	FileManager();
	// Mode d'emploi : aucun
    // Contrat : aucun

	virtual ~FileManager(); 
	// Mode d'emploi : aucun
    // Contrat : aucun

	

	//------------------------------------------------------------------------------ PRIVE
private:


	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ Methodes protegees
	std::string const savePath="sauvegardes.txt";

	//------------------------------------------------------------ Attributs proteges

};
#endif // FileManager_H


