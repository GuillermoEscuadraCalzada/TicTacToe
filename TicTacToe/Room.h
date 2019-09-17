#pragma once

#include "Enemy.h"
#include "FinalBoss.h"
#include "Minion.h"
#include "Boss.h"
#include "Items.h"
#include "Door.h"
#include "Room.h"
#include "Sword.h"
#include "Shield.h"
#include <forward_list>


using std::forward_list; using std::cout; using std::string;

class Room
{
public:
	Room();
	string informacionPuertas, informacionEnemigos, informacionObjetos, informacionDelCuarto;
	forward_list<Door> doorList;

	vector<Enemy*> enemyVector;

	vector<Items*> itemsVector;
	vector<Sword*> swordVector;


	/*==========================================================
	  =====================Cuarto vacio=========================
	  ==========================================================*/

	Room(forward_list<Door> dd, string str);

	/*Cuarto con sólo puertas
		@param contenedor de puertas
		@return identificacion de puertas*/
	Room(forward_list<Door> dd) : doorList(dd) {

		for (Door &a : dd) {
			dd.push_front(a);
		}


	}

	/*==========================================================
	  =====================Cuarto con enemigos==================
	  ==========================================================*/
	Room(forward_list<Door> dl, vector<Enemy*> enemyV);
	Room(forward_list<Door> dl, vector<Enemy*> enemyV, string);


	/*==========================================================
	  =====================Cuarto con enemigos e items==========
	  ==========================================================*/

	Room(forward_list<Door>, vector<Enemy*>, vector<Items*>);
	Room(forward_list<Door>, vector<Enemy*>, vector<Items*>, string);


	/*==========================================================
	  =====================Cuarto con items=====================
	  ==========================================================*/

	Room(forward_list<Door>, vector<Items*>);
	Room(forward_list<Door>, vector<Items*>, string);

	~Room();
};