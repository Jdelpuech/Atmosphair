/**************************************************************************************
 LogManager  -  Interface
 -------------------
 début                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //- Interface de la classe <LogManager> (fichier LogManager.h) ---------
#if !defined ( LogManager_H )
#define LogManager_H
//---------------------------------------------------------------- Interfaces utilisées
#include <string>
#include <fstream>
using namespace std;
class User;
//-------------------------------------------------------------------------------------
// Rôle de la classe <LogManager>
/*
 */
 //-------------------------------------------------------------------------------------
class LogManager
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------------ Méthodes publiques
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
	//------------------------------------------------------------ Méthodes protégées
	std::string const logPath = "atmoLog.log";
	std::ofstream logFile;
	//------------------------------------------------------------ Attributs protégés

};



#endif // LogManager_H


