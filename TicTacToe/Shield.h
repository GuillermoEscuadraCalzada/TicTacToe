#pragma once
#include "Items.h"
class Shield :
	public Items
{
public:
	Shield(string name, int  DEF) : Items(name, DEF) {}
	//Shield(string name, int  DEF) : defense(DEF), Items(name) {}

	~Shield();
	int getDefense();

private:
	int defense;
};


