#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

int Enemy::getEnemyHealth()
{
	return health;
}

int Enemy::getEnemyStrength()
{
	return strength;
}

int Enemy::getEnemyDefense()
{
	return defense;
}

string Enemy::getEnemyName()
{

	return text;
}

void Enemy::setMinionHealth(int newValue) {
	health = newValue;
}

void Enemy::dropItems() {

}
