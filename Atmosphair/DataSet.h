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
#include <ctime>
#include <list>
class Sensor;
class Data;
class DataType;
class User;
//------------------------------------------------------------------ Types
typedef std::list<User*> listUser;
typedef std::list<DataType*> listDataType;
typedef std::list<Sensor*> listSensor;

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
	void addSensor(Sensor *sensor);
	void addDataType(DataType *dataType);
	void addData(Data *data);
	bool connectionRequest(std::string user, std::string password);
	long calculateDisatance(Sensor s1, Sensor s2)const;
	std::list<Sensor*> getListSensorsInZone(double lat, double lon, double rayon);

	int generateResultAtmo(std::list<Sensor*> l, time_t t);
	std::list<int> generateResultAtmo(std::list<Sensor*> l, time_t t1, time_t t2);
	std::list<Data> generateResultGas(std::list<Sensor*> l, time_t t, int choix);
	std::list<Data> generateDataSensor(int id, time_t t1, time_t t2);

	std::list<Sensor> getListDysfonctionningSensors();
	std::list<Sensor> getListSensors();

	//---------------------------------------------------- Constructeurs - destructeur
	DataSet();
	// Mode d'emploi : 
	// Contrat : 

	virtual ~DataSet();
	// Mode d'emploi : aucun
	// Contrat : aucun
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