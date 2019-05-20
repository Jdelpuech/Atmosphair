/**************************************************************************************
 ApplicationManager  -  Interface
 -------------------
 début                : 10/05/2019
 copyright            : (C)2019 par Atmosph'Air
 ***************************************************************************************/

//- Interface de la classe <ApplicationManager> (fichier ApplicationManager.h) ---------
#if !defined ( ApplicationManager_H )
#define ApplicationManager_H
//---------------------------------------------------------------- Interfaces utilisées

#include <string.h>
#include <time.h>
#include "User.h"
//-------------------------------------------------------------------------------------
// Rôle de la classe <ApplicationManager>
/*Application Manager est le noyau de notre application. En tant que dispatcher, il gèrera
 l’appel aux méthodes de chaque classe afin de répondre aux attentes de l'utilisateur.
 */
//-------------------------------------------------------------------------------------
class ApplicationManager
{
    //------------------------------------------------------------------------------ PUBLIC
    
public:
    //------------------------------------------------------------------ Méthodes publiques
    
    int Main() ;
    
    
    
    
    //------------------------------------------------------------------------------ PRIVE
    private :
    
    
    //-----------------------------------------------------------------------------PROTEGE
protected:
    //------------------------------------------------------------ Méthodes protégées
    
    //------------------------------------------------------------ Attributs protégés
    
};



#endif // ApplicationManager_H


