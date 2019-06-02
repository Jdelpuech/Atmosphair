/**************************************************************************************
 DataSet  -  Realisation
 -------------------
 debut                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air

 ***************************************************************************************/

 //-- Realisation de la classe <DataSet> (fichier DataSet.cpp) ----

 //------------------------------------------------------------------------------ INCLUDE
 //---------------------------------------------------------------------- Include systeme
#include <iostream>
using namespace std;
//--------------------------------------------------------------------- Include personnel
#include "LogManager.h"
#include "User.h"
#include <ctime>
//-------------------------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Methodes publiques



void LogManager::writeLog(std::string logtxt, User user)
{
	time_t actualTime;
	time(&actualTime);
	string sTime = ctime(&actualTime);
	sTime.erase(sTime.size() - 1);
	logFile << sTime << ";" << user.getNom() << ";" << logtxt<<";"<<endl;
}


//-------------------------------------------- Constructeurs - destructeur
LogManager::LogManager() : logFile(logPath,ios::app){
	if (!logFile) cout << "erreur pendant l'ouverture du fichier de log" << endl; 
}

LogManager::~LogManager() {
	if (logFile) logFile.close();
}
