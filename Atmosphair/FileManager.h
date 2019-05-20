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
#include <cstring>
#include <fstream>
using namespace std;

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
	FileManager(FILE *fileSave);

	virtual ~FileManager(); 
	// Mode d'emploi : aucun
    // Contrat : aucun



	//------------------------------------------------------------------------------ PRIVE
private:


	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ M�thodes prot�g�es
	FILE * fileSave;

	//------------------------------------------------------------ Attributs prot�g�s

};



#endif // FileManager_H


