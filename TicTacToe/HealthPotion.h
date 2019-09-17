#pragma once
#include"Items.h"
class HealthPotion : public Items
{
public:

	HealthPotion(string name, int points) : Items(name, points) { }

	int getPoints() {
		return pointsToAdd;
	}
	~HealthPotion();

private:
	int pointsToAdd;
};