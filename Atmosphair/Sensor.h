/**************************************************************************************
 Sensor  -  Interface
 -------------------
 début                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Sensor.h) ----------------
#if !defined ( Sensor_H )
#define Sensor_H
//---------------------------------------------------------------- Interfaces utilisées
#include <string>
#include <ctime>
#include <list>

class Data;
//-------------------------------------------------------------------------------Types
typedef std::list<Data *> listData; 
//-------------------------------------------------------------------------------------
// Rôle de la classe <Sensor>
/*La classe User modélise un utilisateur lambda de l’organisation. Ainsi, il se définit par son login, son mot de passe, ainsi que son nom. Lors du lancement de l’application, une méthode init() permet d’initialiser la base de données des utilisateurs pouvant se connecter à l’application : cette méthode appartient à la classe Dataset. Elle prend en entrée un fichier .txt contenant les informations sur tous les utilisateurs. 
 */
//-------------------------------------------------------------------------------------
class Sensor
{
//------------------------------------------------------------------------------ PUBLIC
    
public:
    //------------------------------------------------------------- Méthodes publiques
    int calculateAtmo(time_t t);
    // Mode d'emploi : calcule l'indice ATMO à une date donnée selon les calculs indiqués
    //dans notre livrable.
    // Contrat : aucun

    float calculateMoyenneGaz(time_t t, string type);
	float calculateMoyenneGaz(time_t t1, time_t t2, string type);

    //Mode d'emploi : calcule la moyenne du gaz de type type a la date t.
    //contrat : aucun 

    int dysfonction();
    // Mode d'emploi : calcul l'état du capteur : renvoie  : 
    //- 0 pour un fonctionnement normal
    //- 1 pour un dysfonctionnement de depassement de periode d'echantillonage
    //- 2 pouru n dysfonctionnement de mauvaise données
    //- 3 pour absence de données 

    // Contrat : aucun
    
    bool getDysfonctionning(); 
    // Mode d'emploi : renvoie l'état de fonctionnement du capteur
    // Contrat : aucun
    std::string getDescription();
    // Mode d'emploi : renvoie la description du capteur.
    // Contrat : aucun
    
    string getSensorID();
    // Mode d'emploi : renvoie l'identifiant du capteur.
    // Contrat : aucun
    
    float getLongitude();
    // Mode d'emploi : renvoie la longitude du capteur.
    // Contrat : aucun
    
    float getLatitude();
    // Mode d'emploi : renvoie la latitude du capteur.
    // Contrat : aucun
    
	void addData(Data* data);
    // Mode d'emploi : ajoute une donnée a la liste des données du capteur.
    // Contrat : aucun
    
    listData getData();
    // Mode d'emploi : renvoie la liste des données du capteur
    // Contrat : aucun

	void dropData();
    
	string toString();

    //---------------------------------------------------- Constructeurs - destructeur
    Sensor () {} ; 
    // Mode d'emploi : constructeur par défaut
    Sensor (string sensorID, float lat, float lon, std::string description);
    // Mode d'emploi : à partir des données fournies par une ligne d'un fichier .csv
    //décrivant les capteurs, le constructeur permet de modéliser ce dernier à travers
    //la construction d'un objet Sensor.
    // Contrat : le fichier .csv est aux normes.
    
    
    virtual ~Sensor ( );
    // Mode d'emploi : aucun
    // Contrat : aucun
 
//------------------------------------------------------------------------------ PRIVE
private :
    

//-----------------------------------------------------------------------------PROTEGE
protected:
    //------------------------------------------------------------ Méthodes protégées
    
    //------------------------------------------------------------ Attributs protégés
    string sensorID ;
    float lon ;
    float lat ;
    std::string description ;
    bool dysfonctionning ;
	listData data; 
};



#endif // Sensor_H

