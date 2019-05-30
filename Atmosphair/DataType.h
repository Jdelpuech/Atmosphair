/**************************************************************************************
 DataType  -  Interface
 -------------------
 début                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //---------- Interface de la classe <Catalogue> (fichier DataType.h) ----------------
#if !defined ( DataType_H )
#define DataType_H
//---------------------------------------------------------------- Interfaces utilisées

#include <string>
#include <ctime>
class DataType;
using namespace std;
//-------------------------------------------------------------------------------------
// Rôle de la classe <DataType>
/*Les fichiers .csv définissant les mesures et les types de mesures seront modélisés
respectivement par les classes DataType et DataTypeType avec les mêmes attributs que ceux
stipulés dans les fichiers.
 */

 //-------------------------------------------------------------------------------------
class DataType
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------- Méthodes publiques
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
	// Mode d'emploi : à partir des données fournies par une ligne d'un fichier .csv
	//décrivant une donnée, le constructeur permet de modéliser ce dernier à travers
	//la construction d'un objet DataType.
	// Contrat : le fichier .csv est aux normes.


	virtual ~DataType();
	// Mode d'emploi : aucun
	// Contrat : aucun

//------------------------------------------------------------------------------ PRIVE
private:


	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ Méthodes protégées

	//------------------------------------------------------------ Attributs protégés
	string attributeId; 
	string unit; 
	string description; 
	

};
#endif // DataType_H
