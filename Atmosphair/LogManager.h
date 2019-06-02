/**************************************************************************************
 LogManager  -  Interface
 -------------------
 d�but                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //- Interface de la classe <LogManager> (fichier LogManager.h) ---------
#if !defined ( LogManager_H )
#define LogManager_H
//---------------------------------------------------------------- Interfaces utilis�es
#include <string>
#include <fstream>
using namespace std;
class User;
//-------------------------------------------------------------------------------------
// R�le de la classe <LogManager>
/*
 */
 //-------------------------------------------------------------------------------------
class LogManager
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------------ M�thodes publiques
	void writeLog(std::string logtxt, User user);

	//---------------------------------------------------- Constructeurs - destructeur
	LogManager();
	virtual ~LogManager();
	// Mode d'emploi : aucun
	// Contrat : aucun

	//------------------------------------------------------------------------------ PRIVE
private:


	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ M�thodes prot�g�es
	std::string const logPath = "atmoLog.log";
	std::ofstream logFile;
	//------------------------------------------------------------ Attributs prot�g�s

};



#endif // LogManager_H


