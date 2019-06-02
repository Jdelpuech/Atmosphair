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

using namespace std ; 
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
    // Mode d'emploi : ajoute un sensor � notre ensemble de donnees.
    // Contrat : aucun
    
	void addDataType(DataType *dataType);
    // Mode d'emploi : ajoute un type de donnee � notre ensemble de donnees.
    // Contrat : aucun
    
	void addUser(User *user);
    // Mode d'emploi : ajoute un utilisateur � notre ensemble de donnees.
    // Contrat : aucun
    
	User * connectionRequest(std::string user, std::string password);
    // Mode d'emploi : verifie la connection d'un utilisateur : si l'utilisateur et le mot de
    //passe correspondent, alors la fonction renvoie vrai. Sinon, la methode renvoie faux.
    // Contrat : aucun
    
	static double calculateDistance(double lat1, double lon1,double lat2, double lon2);
    // Mode d'emploi : methode calculant la distance entre deux points geolocalises de latitude
    //et longitude connu. Elle renvoie un nombre � virgule correspondant au nombre de km.
    // Contrat : aucun
    
	Sensor * getSensorById(string id);
    // Mode d'emploi : methode permettant de renvoyer l'objec sensor correspondant a l'id passe
    //en parametre.
    // Contrat : l'id existe.
    
	listSensor getListSensorsInZone(double lat, double lon, double rayon);
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
    
	std::list<double> generateResultGas(listSensor l, time_t t, string choix);
    // Mode d'emploi : renvoie la liste des resultats des moyennes demandees par l'utilisateur
    // Contrat : aucun
    
	std::list<Data*> generateDataSensor(std::string id, time_t t1, time_t t2);
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
