/**************************************************************************************
 DataType  -  Interface
 -------------------
 d�but                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //---------- Interface de la classe <Catalogue> (fichier DataType.h) ----------------
#if !defined ( DataType_H )
#define DataType_H
//---------------------------------------------------------------- Interfaces utilis�es

#include <string>
#include <ctime>
#include "Sensor.h"
using namespace std;
//-------------------------------------------------------------------------------------
// R�le de la classe <DataType>
/*Les fichiers .csv d�finissant les mesures et les types de mesures seront mod�lis�s
respectivement par les classes DataType et DataTypeType avec les m�mes attributs que ceux
stipul�s dans les fichiers.
 */

 //-------------------------------------------------------------------------------------
class DataType
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------- M�thodes publiques
	inline string getAttributeId() {
		return attributeId;
	}

	inline string getUnit() {
		return unit;
	}

	inline string getDescription() {
		return description;
	}



	//---------------------------------------------------- Constructeurs - destructeur
	DataType(string attributeId, string unit, string description);
	// Mode d'emploi : � partir des donn�es fournies par une ligne d'un fichier .csv
	//d�crivant une donn�e, le constructeur permet de mod�liser ce dernier � travers
	//la construction d'un objet DataType.
	// Contrat : le fichier .csv est aux normes.


	virtual ~DataType();
	// Mode d'emploi : aucun
	// Contrat : aucun

//------------------------------------------------------------------------------ PRIVE
private:


	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ M�thodes prot�g�es

	//------------------------------------------------------------ Attributs prot�g�s
	string attributeId; 
	string unit; 
	string description; 
	

};



#endif // DataType_H
