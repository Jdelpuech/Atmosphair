/**************************************************************************************
 ApplicationManager  -  Réalisation
 -------------------
 début                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air
 
 ***************************************************************************************/

//-- Réalisation de la classe <ApplicationManager> (fichier ApplicationManager.cpp) ----

//------------------------------------------------------------------------------ INCLUDE
//---------------------------------------------------------------------- Include système
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

//--------------------------------------------------------------------- Include personnel
#include "ApplicationManager.h"
#include "Sensor.h"
#include "User.h"
#include "DataSet.h"

//-------------------------------------------------------------------------------- PUBLIC
int main(){
	double result = DataSet::calculateDistance(-8.157588883, -34.76924879, -30.06473877, -76.34391476);
	std::cout << result;
	return 0; 
}
