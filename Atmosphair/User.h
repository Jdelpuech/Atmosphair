/**************************************************************************************
 User  -  Interface
 -------------------
 début                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

//---------- Interface de la classe <User> (fichier User.h) ----------------
#if !defined ( User_H )
#define User_H
//---------------------------------------------------------------- Interfaces utilisées

#include <string>
#include <ctime>
//-------------------------------------------------------------------------------------
// Rôle de la classe <User>
/*Modelise un utilisateur. 
 */
//-------------------------------------------------------------------------------------
class User
{
    //------------------------------------------------------------------------------ PUBLIC
    
public:
    //------------------------------------------------------------- Méthodes publiques
    static int id; 
    
    int getUserID();
    // Mode d'emploi : renvoie l'identifiant de l'utilisateur.
    // Contrat : aucun
    
    std::string getLogin();
    // Mode d'emploi : renvoie le login de l'utilisateur.
    // Contrat : aucun
    
    std::string getMdp();
    // Mode d'emploi : renvoie le mot de passe de l'utilisateur.
    // Contrat : aucun
    
    std::string getNom();
    // Mode d'emploi : renvoie le nom de l'utilisateur.
    // Contrat : aucun
    
    std::string toString(); 
    //Mode d'emploi : renvoie la description de l'objet. 
    //Contrat : aucun 
    
    
    //---------------------------------------------------------- Constructeurs - destructeur
    User (std::string login, std::string mdp, std::string name);
    // Mode d'emploi :informations tirees des donnees fournies par une methode d'initialisation. 
    // Contrat : aucun
    
    
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
    std::string login ;
    std::string mdp ;
    std::string name ;
};



#endif // Sensor_H


