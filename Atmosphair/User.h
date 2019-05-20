/**************************************************************************************
 User  -  Interface
 -------------------
 début                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if !defined ( User_H )
#define User_H
//---------------------------------------------------------------- Interfaces utilisées

#include <string>
#include <ctime>
//-------------------------------------------------------------------------------------
// Rôle de la classe <User>
/*La classe Sensor modélise les capteurs ici utilisés. Un capteur se définit donc par sa localisation 
(latitude, longitude, description ainsi qu’un id permettant de l’identifier). Cette classe est pourvue 
d’une méthode permettant de calculer l’indice Atmo à une date donnée (alors les données utilisées sont
celle de ce même capteur). Cette méthode est surchargée pour permettre de calculer une variante de l’indice 
Atmo en utilisant deux dates.
 */
//-------------------------------------------------------------------------------------
class User
{
    //------------------------------------------------------------------------------ PUBLIC
    
public:
    //------------------------------------------------------------- Méthodes publiques
 
    
    int getUserID();
    // Mode d'emploi : renvoie l'identifiant de l'utilisateur.
    // Contrat : aucun
    
    string getLogin();
    // Mode d'emploi : renvoie le login de l'utilisateur.
    // Contrat : aucun
    
    string getMdp();
    // Mode d'emploi : renvoie le mot de passe de l'utilisateur.
    // Contrat : aucun
    
    string getNom();
    // Mode d'emploi : renvoie le nom de l'utilisateur.
    // Contrat : aucun
    
    
    
    //---------------------------------------------------------- Constructeurs - destructeur
    User (int userID, string login, string mdp, string name);
    // Mode d'emploi : à partir des données fournies par une ligne d'un fichier .csv
    //décrivant les utilisateurs, le constructeur permet de modéliser ce dernier à travers
    //la construction d'un objet User.
    // Contrat : le fichier .csv est aux normes.
    
    
    virtual ~User ( );
    // Mode d'emploi : aucun
    // Contrat : aucun
    
    //------------------------------------------------------------------------------ PRIVE
    private :
    
    
    //-----------------------------------------------------------------------------PROTEGE
protected:
    //------------------------------------------------------------ Méthodes protégées
    
    //------------------------------------------------------------ Attributs protégés
    int userID;
    string login ;
    string mdp ;
    string name ;
};



#endif // Sensor_H


