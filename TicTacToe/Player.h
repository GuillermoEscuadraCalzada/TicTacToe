#pragma once
#include <iostream>
#include "Items.h"
#include "Door.h"
#include <typeinfo>
#include "Key.h"
#include "HealthPotion.h"
#include "Room.h"
#include <algorithm>
#include "SumaDeVida.h"
#include <map>

using std::map; using std::pair; using std::cout;

class Player
{
public:
	Player();
	Player(int maxHealth, int strgth, int defnse, vector<Key>& plKV) : maximumHealth(maxHealth), damage(strgth), defense(defnse), newKeyVector(plKV) {  }
	~Player();

	
	HWND  TextBox;
	//se necesita un contenedor para las llaves, ya que el jugador tendra dos llaves
	vector<Key> newKeyVector;

	vector<HealthPotion> potionVector;


	vector<Items> itemsVector;

	forward_list<string> recetario;

	//obtener datos del jugador, daño, defensa, cuarto actual, etc.
	void setCurrentRoom(int room);
	int getCurrentRoom();
	int getPreviousRoom();

	int getDamage();
	void setDamage(int d);

	void setDefense(int d);
	int getDefense();

	int getCurrentHealth();
	int getMaximumHealth();

	void setMaximumHealth(int maxH);
	void setCurrentHealth(int h);


	//Acciones del jugador
	void openDoor(map<int, Room>, int, int, HWND hWnd);
	int choice;
	void unlockDoor(map<int, Room>&, int, int);
	void openInventory();

	//levantar objetos============================================
	void pickUpSword(map<int, Room>&, int);
	void pickUpShield(map<int, Room>&, int);
	void pickUpKey(map<int, Room>&, int);
	void pickUpPotion(map<int, Room>&, int);

	//tirar objetos===============================================
	void dropSword(map<int, Room>&, int);
	void dropShield(map<int, Room>&, int);
	void dropKey(map<int, Room>&, int);
	void dropPotion(map<int, Room>&, int);


	//Pelear con enemigos=========================================
	void fightingMinions(map<int, Room>&, int);
	void fightingBosses(map<int, Room>&, int);
	void fightingFinalBoss(map<int, Room>&, int);


	void heal();
	void openStats();
	void revealCurrentRoom(map<int, Room>&, int);

	template <class V>
	V damageInFight(V const& t1, V const& t2);

	bool gameIsActive = true;




	/*========================================================
	  ========================Crafting========================
	  ========================================================*/

	void crafting();
	void recipeBook();
	void diccionario(string);
	void particionDeString(map<int, vector<string>>, string);
	void switchForWeapons(int);
private:
	int currentRoom = 0, previousRoom, damage, defense, currentHealth, maximumHealth;
};

template<class V>
V Player::damageInFight(V const & t1, V const & t2)
{
	V value;
	value = t1 - t2;
	return value;
}
