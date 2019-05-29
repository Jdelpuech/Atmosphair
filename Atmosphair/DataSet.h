/**************************************************************************************
 DataSet  -  Interface
 -------------------
 d�but                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //- Interface de la classe <DataSet> (fichier DataSet.h) ---------
#if !defined ( DataSet_H )
#define DataSet_H
//---------------------------------------------------------------- Interfaces utilis�es
#include "Sensor.h"
#include "User.h"
#include "DataType.h"
#include <list>
//------------------------------------------------------------------ Types
typedef std::list<User> listUser;
typedef std::list<DataType> listDataType;
typedef std::list<Sensor> listSensor;

// R�le de la classe <DataSet>
/*Application Manager est le noyau de notre application. En tant que dispatcher, il g�rera
 l�appel aux m�thodes de chaque classe afin de r�pondre aux attentes de l'utilisateur.
 */
 //-------------------------------------------------------------------------------------
class DataSet
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------------ M�thodes publiques
	void addSensor(Sensor &sensor);
	void addDataType(DataType &dataType);
	bool connect(std::string user, std::string password);
	//---------------------------------------------------- Constructeurs - destructeur
	DataSet();
	//------------------------------------------------------------------------------ PRIVE
private:
	//------------------------------------------------------------ Attributs priv�
	listUser liUser;
	listDataType liDataType;
	listSensor liSensor;

	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ M�thodes prot�g�es

	//------------------------------------------------------------ Attributs prot�g�s

};

#endif // DataSet_H