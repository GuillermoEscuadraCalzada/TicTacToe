#pragma once
class Door
{
public:


	Door(int id, bool c) : ID(id), closed(c) {}
	bool getStatus() {
		return closed;
	}
	void setStatus(bool t) {
		closed = t;
	}
	int getID() {
		return ID;
	}
	~Door();

private:
	int ID;
	bool closed;
};
