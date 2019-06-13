/**************************************************************************************
 DataType  -  Interface
 -------------------
 debut                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //---------- Interface de la classe <Catalogue> (fichier DataType.h) ----------------
#if !defined ( DataType_H )
#define DataType_H
//---------------------------------------------------------------- Interfaces utilisees

#include <string>
#include <ctime>
class DataType;
using namespace std;
//-------------------------------------------------------------------------------------
// Role de la classe <DataType>
/*Les fichiers .csv definissant les mesures et les types de mesures seront modelises
respectivement par les classes DataType et DataTypeType avec les memes attributs que ceux
stipules dans les fichiers.
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
	// Mode d'emploi : renvoie l'identifiant de l'attribut du type de donnees. 
	// Contrat : aucun

	inline string getUnit() {
		return unit;
	}
	// Mode d'emploi : renvoie l'unite du type de donnee
	// Contrat : aucun

	inline string getDescription() {
		return description;
	}
	// Mode d'emploi : renvoie la description d'un type de donnée
	// Contrat : aucun

	string toString();
	// Mode d'emploi : renvoie une chaine de caracteres avec tous les 
	//attributs definissant le type de donnees. 
	// Contrat : aucun

	//---------------------------------------------------- Constructeurs - destructeur
	DataType(string attributeId, string unit, string description);
	// Mode d'emploi : a partir des donnees fournies par une ligne d'un fichier .csv
	//decrivant une donnee, le constructeur permet de modeliser ce dernier a travers
	//la construction d'un objet DataType.
	// Contrat : le fichier .csv est aux normes.


	virtual ~DataType();
	// Mode d'emploi : aucun
	// Contrat : aucun

//------------------------------------------------------------------------------ PRIVE
private:


	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ Methodes protegees

	//------------------------------------------------------------ Attributs proteges
	string attributeId; 
	string unit; 
	string description; 
	

};
#endif // DataType_H
