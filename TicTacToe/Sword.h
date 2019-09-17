#pragma once
#include "Items.h"
class Sword :
	public Items
{
public:

	//Sword(string name, int Strength) : /*strength(Strength)*/Items(name), strength(Strength) {}
	Sword(string name, int Strength) : /*strength(Strength)*/Items(name, Strength) {}


	~Sword();
	int getStrength();
private:
	int strength;
};