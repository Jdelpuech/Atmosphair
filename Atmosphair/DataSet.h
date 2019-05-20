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
#include "Sensor.h"
#include "User.h"
//-------------------------------------------------------------------------------------
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

	//---------------------------------------------------- Constructeurs - destructeur
	DataSet();
	//------------------------------------------------------------------------------ PRIVE
private:
	//------------------------------------------------------------ Attributs priv�
	

	//-----------------------------------------------------------------------------PROTEGE
protected:
	//------------------------------------------------------------ M�thodes prot�g�es

	//------------------------------------------------------------ Attributs prot�g�s

};

#endif // DataSet_H