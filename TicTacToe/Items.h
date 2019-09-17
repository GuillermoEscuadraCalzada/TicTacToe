#pragma once
#include <iostream>
#include <string>
#include <vector>
using std::vector; using std::string;

class Items
{
public:
	Items(string str, int id, int a) : nombre(str), ID(id), atribute(a) { }
	Items(string str, int ATRIBUTE) : nombre(str), atribute(ATRIBUTE) { }

	Items(string str) : nombre(str) { }

	string getName();
	int getAtribute();
	int getType() {
		return type;
	}


	virtual ~Items();
private:
	int ID, atribute, type;
	string nombre;
};

inline bool operator==(const Items& a, const Items& b)
{
	return true;
}
