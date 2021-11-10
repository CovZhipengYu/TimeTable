#pragma once
#include "basicObject.h"

class Room : public BasicObject
{
public:
	string build;
	Room(sqlite3* ndb);
	Room(string nam, string cod, string buil);
	int  manageTable();
	void createTable();
};

