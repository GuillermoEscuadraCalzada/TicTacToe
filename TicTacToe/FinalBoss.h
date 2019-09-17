#pragma once
#include "Enemy.h"
class FinalBoss :
	public Enemy
{
public:
	FinalBoss(string name, int health, int strength, int defense) :
		Enemy(name, health, strength, defense) {}
	~FinalBoss();
};
