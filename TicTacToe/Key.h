#pragma once
#include "Items.h"
class Key : public Items
{
public:
	//Key(string str,int idDrr)  : idDoor(idDrr), Items(str){}
	Key(string str, int idDrr) : Items(str, idDrr) {
		setDoorID(idDrr);
	}

	int getDoorID();

	void setDoorID(int t) {
		idDoor = t;
	}
	int getType() {
		return type;
	}
	~Key();
private:
	int type = 1;
	int idDoor;

};