/**************************************************************************************
 LogManager  -  Interface
 -------------------
 d�but                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //- Interface de la classe <LogManager> (fichier LogManager.h) ---------
#if !defined ( LogManager_H )
#define LogManager_H
//---------------------------------------------------------------- Interfaces utilisees
#include <string>
#include <fstream>
using namespace std;
class User;
//-------------------------------------------------------------------------------------
// Role de la classe <LogManager>
/* gere les ecritures des logs dans l'historique
 */
 //-------------------------------------------------------------------------------------
class LogManager
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------------ Methodes publiques
	void writeLog(std::string logtxt);

	//---------------------------------------------------- Constructeurs - destructeur
	LogManager(User * u);
	virtual ~LogManager();
	// Mode d'emploi : aucun
	// Contrat : aucun

	//------------------------------------------------------------------------------ PRIVE
private:


	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ Methodes protegees
	std::string const logPath = "atmoLog.log";
	std::ofstream logFile;
	User * user;
	//------------------------------------------------------------ Attributs proteges

};



#endif // LogManager_H


