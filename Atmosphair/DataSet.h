/**************************************************************************************
 DataSet  -  Interface
 -------------------
 dÈbut                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //- Interface de la classe <DataSet> (fichier DataSet.h) ---------
#if !defined ( DataSet_H )
#define DataSet_H
//---------------------------------------------------------------- Interfaces utilisÈes
#include <ctime>
#include <list>
class Sensor;
class Data;
class DataType;
class User;

using namespace std ; 
//------------------------------------------------------------------ Types
typedef std::list<User*> listUser;
typedef std::list<DataType*> listDataType;
typedef std::list<Sensor*> listSensor;

// RÙle de la classe <DataSet>
/*Application Manager est le noyau de notre application. En tant que dispatcher, il gËrera
 líappel aux mÈthodes de chaque classe afin de rÈpondre aux attentes de l'utilisateur.
 */
 //-------------------------------------------------------------------------------------
class DataSet
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------------ MÈthodes publiques
	void addSensor(Sensor *sensor);
    // Mode d'emploi : ajoute un sensor à notre ensemble de données.
    // Contrat : aucun
    
	void addDataType(DataType *dataType);
    // Mode d'emploi : ajoute un type de donnée à notre ensemble de données.
    // Contrat : aucun
    
	void addUser(User *user);
    // Mode d'emploi : ajoute un utilisateur à notre ensemble de données.
    // Contrat : aucun
    
	bool connectionRequest(std::string user, std::string password);
    // Mode d'emploi : vérifie la connection d'un utilisateur : si l'utilisateur et le mot de
    //passe correspondent, alors la fonction renvoie vrai. Sinon, la méthode renvoie faux.
    // Contrat : aucun
    
	static double calculateDistance(double lat1, double lon1,double lat2, double lon2);
    // Mode d'emploi : méthode calculant la distance entre deux points géolocalisés de latitude
    //et longitude connu. Elle renvoie un nombre à virgule correspondant au nombre de km.
    // Contrat : aucun
    
	Sensor getSensorById(string id);
    // Mode d'emploi : méthode permettant de renvoyer l'objec sensor correspondant a l'id passé
    //en parametre.
    // Contrat : l'id existe.
    
	std::list<Sensor*> getListSensorsInZone(double lat, double lon, double rayon);
    // Mode d'emploi : renvoie une liste de pointeurs vers des capteurs étant dans la zone
    //géographique se défissant par un point (centre) et un rayon (en km).
    // Contrat : aucun
    
    std::list<int> generateResultAtmo(std::list<Sensor*> l, time_t t);
    // Mode d'emploi : renvoie la liste de tous les indices atmos correspondant aux sensors
    //de la liste l a la date t.
    // Contrat : aucun
    
	std::list<int> generateResultAtmo(std::list<Sensor*> l, time_t t1, time_t t2);
    // Mode d'emploi : renvoie la liste de tous les indices atmos correspondant aux sensors
    //de la liste l, moyennes des indices entre les dates t1 et t2.
    // Contrat : aucun
    
	std::list<Data> generateResultGas(std::list<Sensor*> l, time_t t, int choix);
    // Mode d'emploi : renvoie la liste des résultats des moyennes demandées par l'utilisateur
    // Contrat : aucun
    
	std::list<Data> generateDataSensor(int id, time_t t1, time_t t2);
    // Mode d'emploi : renvoie toutes les données brutes entre t1 et t2 du capteur d'identifiant
    //id. 
    // Contrat : aucun

	std::list<Sensor> getListDysfonctionningSensors();
    // Mode d'emploi : renvoie une liste de l'ensemble des sensors dysfonctionnants
    // Contrat : aucun
    
	std::list<Sensor*> getListSensors();
    // Mode d'emploi : renvoie une liste de l'ensemble des sensors
    // Contrat : aucun

	std::list<DataType*> getListDataType();
	//--------------------------------------------------------- Constructeurs - destructeur
	DataSet();
	// Mode d'emploi : aucun
	// Contrat : aucun

	virtual ~DataSet();
	// Mode d'emploi : aucun
	// Contrat : aucun
	//------------------------------------------------------------------------------ PRIVE
private:
	//-------------------------------------------------------------------- Attributs privés
	listUser liUser;
	listDataType liDataType;
	listSensor liSensor;

	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------------ Méthodes protégées

	//---------------------------------------------------------------- Attributs protégés

};

#endif // DataSet_H
