/**************************************************************************************
 DataSet  -  Interface
 -------------------
 début                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //- Interface de la classe <DataSet> (fichier DataSet.h) ---------
#if !defined ( DataSet_H )
#define DataSet_H
//---------------------------------------------------------------- Interfaces utilisées
#include "Sensor.h"
#include "User.h"
#include "DataType.h"
#include <list>
//------------------------------------------------------------------ Types
typedef std::list<User> listUser;
typedef std::list<DataType> listDataType;
typedef std::list<Sensor> listSensor;

// Rôle de la classe <DataSet>
/*Application Manager est le noyau de notre application. En tant que dispatcher, il gèrera
 l’appel aux méthodes de chaque classe afin de répondre aux attentes de l'utilisateur.
 */
 //-------------------------------------------------------------------------------------
class DataSet
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------------ Méthodes publiques
	void addSensor(Sensor &sensor);
	void addDataType(DataType &dataType);
	bool connect(std::string user, std::string password);
	//---------------------------------------------------- Constructeurs - destructeur
	DataSet();
	//------------------------------------------------------------------------------ PRIVE
private:
	//------------------------------------------------------------ Attributs privé
	listUser liUser;
	listDataType liDataType;
	listSensor liSensor;

	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ Méthodes protégées

	//------------------------------------------------------------ Attributs protégés

};

#endif // DataSet_H