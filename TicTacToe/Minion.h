#pragma once
#include "Enemy.h"
class Minion :
	public Enemy
{
public:
	Minion(string name, int h, int s, int d) : Enemy(name, h, s, d) {}
	~Minion();
};

