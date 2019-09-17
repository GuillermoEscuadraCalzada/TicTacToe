#pragma once
#include <iostream>
#include <vector>
#include "Items.h"
using std::string; using std::vector;
class Enemy
{
public:
	vector<Items> droppedItems;
	Enemy();
	Enemy(string name, int health, int strength, int defense) :
		text(name), health(health), strength(strength), defense(defense) {}
	virtual ~Enemy();

	int getEnemyHealth();
	int getEnemyStrength();
	int getEnemyDefense();
	string getEnemyName();
	void setMinionHealth(int newValue);

	void dropItems();

private:
	int health, strength, defense;
	string text;
};