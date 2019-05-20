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
//----------------------------------------------------------- Constructeurs - destructeur

User::User(int userID, string login, string mdp, string name){
    this->userID = userID ;
    this->login = login ;
    this->mdp = mdp ;
    this->name = name ;
}

User::~User(){
    
}
