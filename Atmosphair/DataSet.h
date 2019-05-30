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
    // Mode d'emploi : ajoute un sensor � notre ensemble de donn�es.
    // Contrat : aucun
    
	void addDataType(DataType *dataType);
    // Mode d'emploi : ajoute un type de donn�e � notre ensemble de donn�es.
    // Contrat : aucun
    
	void addUser(User *user);
    // Mode d'emploi : ajoute un utilisateur � notre ensemble de donn�es.
    // Contrat : aucun
    
	bool connectionRequest(std::string user, std::string password);
    // Mode d'emploi : v�rifie la connection d'un utilisateur : si l'utilisateur et le mot de
    //passe correspondent, alors la fonction renvoie vrai. Sinon, la m�thode renvoie faux.
    // Contrat : aucun
    
	static double calculateDistance(double lat1, double lon1,double lat2, double lon2);
    // Mode d'emploi : m�thode calculant la distance entre deux points g�olocalis�s de latitude
    //et longitude connu. Elle renvoie un nombre � virgule correspondant au nombre de km.
    // Contrat : aucun
    
	Sensor getSensorById(string id);
    // Mode d'emploi : m�thode permettant de renvoyer l'objec sensor correspondant a l'id pass�
    //en parametre.
    // Contrat : l'id existe.
    
	std::list<Sensor*> getListSensorsInZone(double lat, double lon, double rayon);
    // Mode d'emploi : renvoie une liste de pointeurs vers des capteurs �tant dans la zone
    //g�ographique se d�fissant par un point (centre) et un rayon (en km).
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
    // Mode d'emploi : renvoie la liste des r�sultats des moyennes demand�es par l'utilisateur
    // Contrat : aucun
    
	std::list<Data> generateDataSensor(int id, time_t t1, time_t t2);
    // Mode d'emploi : renvoie toutes les donn�es brutes entre t1 et t2 du capteur d'identifiant
    //id. 
    // Contrat : aucun

	std::list<Sensor> getListDysfonctionningSensors();
    // Mode d'emploi : renvoie une liste de l'ensemble des sensors dysfonctionnants
    // Contrat : aucun
    
	std::list<Sensor> getListSensors();
    // Mode d'emploi : renvoie une liste de l'ensemble des sensors
    // Contrat : aucun

	//--------------------------------------------------------- Constructeurs - destructeur
	DataSet();
	// Mode d'emploi : aucun
	// Contrat : aucun

	virtual ~DataSet();
	// Mode d'emploi : aucun
	// Contrat : aucun
	//------------------------------------------------------------------------------ PRIVE
private:
	//-------------------------------------------------------------------- Attributs priv�s
	listUser liUser;
	listDataType liDataType;
	listSensor liSensor;

	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------------ M�thodes prot�g�es

	//---------------------------------------------------------------- Attributs prot�g�s

};

#endif // DataSet_H
