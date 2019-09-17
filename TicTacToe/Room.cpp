#include "stdafx.h"
#include "Room.h"

//Constructor vacío
Room::Room()
{
}

/*==========================================================
  =====================Cuarto vacio=========================
  ==========================================================*/


  /*Cuarto con puerta y string
	  @param contenedor de puertas, informacion del cuarto.
	  @return numero de puertas, informacion del cuarto.*/
Room::Room(forward_list<Door> dd, string str)
{
	bool read = false;
	informacionDelCuarto = str;
	for (Door &a : dd) {
		dd.push_front(a);
	}
	if (read == false) {
		cout << informacionDelCuarto << "\n";
		read = true;
	}

}


/*==========================================================
  =====================Cuarto con enemigos==================
  ==========================================================*/

  /*Cuarto con puerta, enemigos
	  @param contenedor de puertas y contenedor de enemigos
	  @return numero de puertas y numero de enemigos*/
Room::Room(forward_list<Door> dl, vector<Enemy*> enemyV)
{
	doorList = dl;
	enemyVector = enemyV;

	for (Door &a : dl) {
		dl.push_front(a);

	}
	for (Enemy *a : enemyV) {
		enemyV.push_back(a);
	}
}


/*Cuarto con puerta, enemigos y string
	@param contenedor de puertas, contenedor de enemigos e informacion del cuarto.
	@return numero de puertas, numero de enemigos y sus nombres,informacion del cuarto.*/
Room::Room(forward_list<Door> dl, vector<Enemy*> enemyV, string str) {
	doorList = dl;
	enemyVector = enemyV;

	for (Door &a : dl) {
		dl.push_front(a);

	}
	for (Enemy *a : enemyV) {
		enemyV.push_back(a);
	}

	bool read = false;
	informacionDelCuarto = str;
	if (read == false) {
		cout << informacionDelCuarto << "\n";
		read = true;
	}

}


/*==========================================================
  =====================Cuarto con enemigos e items==========
  ==========================================================*/

  /*Cuarto con puerta, items
	  @param contenedor de puertas, contenedor de objetos
	  @return numero de puertas, numero de objetos y enemigos junto con sus nombres,informacion del cuarto.*/
Room::Room(forward_list<Door> d, vector<Enemy*> enemyV, vector<Items*> itemsV)
{
	doorList = d;
	enemyVector = enemyV;
	itemsVector = itemsV;

	//recorrer todos los contenedores de puertas, enemigos y objetosS
	for (Door &a : d) {
		d.push_front(a);
	}

	for (Enemy *a : enemyV) {
		enemyV.push_back(a);
	}

	for (Items* a : itemsV) {
		itemsV.push_back(a);
	}


}


/*Cuarto con puerta, enemigos y string
	@param contenedor de puertas, contenedor de objetos e informacion del cuarto.
	@return numero de puertas, numero de objetos y enemigos junto con sus nombres,informacion del cuarto.*/
Room::Room(forward_list<Door> d, vector<Enemy*> enemyV, vector<Items*> itemsV, string roomString)
{
	bool read = false;
	informacionDelCuarto = roomString;
	doorList = d;
	enemyVector = enemyV;
	itemsVector = itemsV;

	for (Door &a : d) {
		d.push_front(a);
	}

	for (Enemy *a : enemyV) {
		enemyV.push_back(a);
	}

	for (Items* a : itemsV) {
		itemsV.push_back(a);
	}
	if (read == false) {
		cout << informacionDelCuarto << "\n";
		read = true;
	}

}


/*==========================================================
  =====================Cuarto con items=====================
  ==========================================================*/


  /*Cuarto con puerta, objetos
	  @param contenedor de puertas, contenedor de objetos
	  @return numero de puertas, numero de objetos y sus nombres*/
Room::Room(forward_list<Door> dd, vector<Items* >itemV) {
	doorList = dd;
	itemsVector = itemV;
	for (Door &a : dd) {
		dd.push_front(a);
	}

	for (Items* a : itemV) {
		itemV.push_back(a);
	}


}


/*Cuarto con puerta, objetos y string
	@param contenedor de puertas, contenedor de objetos e informacion del cuarto.
	@return numero de puertas, numero de objetos y sus nombres,informacion del cuarto.*/
Room::Room(forward_list<Door> dd, vector<Items* >itemV, string str) {
	doorList = dd;
	itemsVector = itemV;
	for (Door &a : dd) {
		dd.push_front(a);
	}

	for (Items* a : itemV) {
		itemV.push_back(a);
	}

	bool read = false;
	informacionDelCuarto = str;
	if (read == false) {
		cout << informacionDelCuarto << "\n";
		read = true;
	}
}


//Destructor
Room::~Room()
{
}
