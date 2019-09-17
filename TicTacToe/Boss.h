#pragma once
#include "Enemy.h"
class Boss : public Enemy
{
public:
	Boss(string name, int health, int strength, int defense) :
		Enemy(name, health, strength, defense) {}
	~Boss();
};

