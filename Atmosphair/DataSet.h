/**************************************************************************************
 DataSet  -  Interface
 -------------------
 debut                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

 //- Interface de la classe <DataSet> (fichier DataSet.h) ---------
#if !defined ( DataSet_H )
#define DataSet_H
//---------------------------------------------------------------- Interfaces utilisees
#include <ctime>
#include <list>
#include <vector>
#define _CRT_SECURE_NO_WARNINGS
class Sensor;
class Data;
class DataType;
class User;

using namespace std ; 
//------------------------------------------------------------------ Types
typedef std::list<User*> listUser;
typedef std::list<DataType*> listDataType;
typedef std::list<Sensor*> listSensor;

// Rele de la classe <DataSet>
/*Application Manager est le noyau de notre application. En tant que dispatcher, il gerera
 leappel aux methodes de chaque classe afin de repondre aux attentes de l'utilisateur.
 */
 //-------------------------------------------------------------------------------------
class DataSet
{
	//------------------------------------------------------------------------------ PUBLIC

public:
	//------------------------------------------------------------------ Methodes publiques
	void addSensor(Sensor *sensor);
    // Mode d'emploi : ajoute un sensor e notre ensemble de donnees.
    // Contrat : aucun
    
	void addDataType(DataType *dataType);
    // Mode d'emploi : ajoute un type de donnee e notre ensemble de donnees.
    // Contrat : aucun
    
	void addUser(User *user);
    // Mode d'emploi : ajoute un utilisateur e notre ensemble de donnees.
    // Contrat : aucun
    
	User * connectionRequest(std::string user, std::string password);
    // Mode d'emploi : verifie la connection d'un utilisateur : si l'utilisateur et le mot de
    //passe correspondent, alors la fonction renvoie vrai. Sinon, la methode renvoie faux.
    // Contrat : aucun
    
	static float calculateDistance(float lat1, float lon1,float lat2, float lon2);
    // Mode d'emploi : methode calculant la distance entre deux points geolocalises de latitude
    //et longitude connu. Elle renvoie un nombre e virgule correspondant au nombre de km.
    // Contrat : aucun
    
	Sensor * getSensorById(string id);
    // Mode d'emploi : methode permettant de renvoyer l'objec sensor correspondant a l'id passe
    //en parametre.
    // Contrat : l'id existe.
    
	listSensor getListSensorsInZone(float lat, float lon, float rayon);
    // Mode d'emploi : renvoie une liste de pointeurs vers des capteurs etant dans la zone
    //geographique se defissant par un point (centre) et un rayon (en km).
    // Contrat : aucun
    
    std::list<int> generateResultAtmo(listSensor l, time_t t);
    // Mode d'emploi : renvoie la liste de tous les indices atmos correspondant aux sensors
    //de la liste l a la date t.
    // Contrat : aucun
    
	std::list<int> generateResultAtmo(listSensor l, time_t t1, time_t t2);
    // Mode d'emploi : renvoie la liste de tous les indices atmos correspondant aux sensors
    //de la liste l, moyennes des indices entre les dates t1 et t2.
    // Contrat : aucun
    
	std::vector<float> generateResultGas(listSensor l, time_t t, string choix);
    // Mode d'emploi : renvoie un vecteur des resultats des moyennes demandees par l'utilisateur
    // Contrat : aucun

    vector<Data *> generateResultGas(Sensor * s, time_t t1,time_t t2); 
    //Mode d'emploi : renvoie un vecteur des resultats des moyennes de tous les gaz. 
    //Contrat : aucun 
    
	std::list<Data*> generateDataSensor(Sensor * s, time_t t1, time_t t2);
    // Mode d'emploi : renvoie toutes les donnees brutes entre t1 et t2 du capteur d'identifiant
    //id. 
    // Contrat : aucun

	listSensor getListDysfonctionningSensors();
    // Mode d'emploi : renvoie une liste de l'ensemble des sensors dysfonctionnants
    // Contrat : aucun
    
	listSensor getListSensors();
    // Mode d'emploi : renvoie une liste de l'ensemble des sensors
    // Contrat : aucun

	listDataType getListDataType();
     // Mode d'emploi : renvoie une liste de l'ensemble des types de données
    // Contrat : aucun

    listUser getListUsers(); 
     // Mode d'emploi : renvoie une liste de l'ensemble des users
    // Contrat : aucun

	void dropListSensors();

	void dropData();

	void dropDataType();

	//--------------------------------------------------------- Constructeurs - destructeur
	DataSet();
	// Mode d'emploi : aucun
	// Contrat : aucun

	virtual ~DataSet();
	// Mode d'emploi : aucun
	// Contrat : aucun
	//------------------------------------------------------------------------------ PRIVE
private:
	//-------------------------------------------------------------------- Attributs prives
	listUser liUser;
	listDataType liDataType;
	listSensor liSensor;

	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------------ Methodes protegees

	//---------------------------------------------------------------- Attributs proteges

};

#endif // DataSet_H
