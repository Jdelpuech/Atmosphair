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

#include <string.h>
#include <time.h>
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
    // Mode d'emploi : calcul l'indice ATMO à une date donnée selon les calculs indiqués
    //dans notre livrable.
    // Contrat : aucun
    
    bool dysfonction();
    // Mode d'emploi : renvoie l'état de fonctionnement du capteur
    // Contrat : aucun
    
    string getDescription();
    // Mode d'emploi : renvoie la description du capteur.
    // Contrat : aucun
    
    int getSensorID();
    // Mode d'emploi : renvoie l'identifiant du capteur.
    // Contrat : aucun
    
    double getLongitude();
    // Mode d'emploi : renvoie la longitude du capteur.
    // Contrat : aucun
    
    double getLatitude();
    // Mode d'emploi : renvoie la latitude du capteur.
    // Contrat : aucun
    

    
    //---------------------------------------------------- Constructeurs - destructeur
    Sensor (int sensorID, long lat, long lon, string description, bool dysfonctionning);
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
    int sensorID ;
    double lon ;
    double lat ;
    string description ;
    bool dysfonctionning ;
};



#endif // Sensor_H

