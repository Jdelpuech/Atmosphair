/**************************************************************************************
 User  -  Réalisation
 -------------------
 début                : 20/11/2018
 copyright            : (C)2018 par Atmosph'Air
 
 ***************************************************************************************/

//------------------ Réalisation de la classe <User> (fichier User.cpp) ------------

//------------------------------------------------------------------------------ INCLUDE
//---------------------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//--------------------------------------------------------------------- Include personnel
#include "User.h"

//-------------------------------------------------------------------------------- PUBLIC
int User::getUserID(){
    return userID ;
}//---Fin de getUserID

string User::getMdp(){
    return mdp ;
}//---Fin de getMdp

string User::getLogin(){
    return login ;
}

string User::getNom(){
    return name ; 
}

string User::toString(){
    string rep = to_string(userID)+";"+login+";"+mdp+";"+name ; 
    return rep ; 
}
//----------------------------------------------------------- Constructeurs - destructeur
int User::id = 1;
User::User(string login, string mdp, string name):userID(id++),login(login),mdp(mdp),name(name){
}

User::~User(){
    
}


