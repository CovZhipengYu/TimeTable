#include "rooms.h"

Room::Room(sqlite3* ndb)
{
db = ndb;
}

Room::Room(string nam, string cod, string buil)
{
	name = nam;
	code = cod;
	build = buil;
}

int Room::manageTable()
{
	int option;
	BasicObject::showTable("student");
	std::cout << "Enter option:";
	std::cin >> option;
	return option;
}

void Room::createTable()
{
	std::string sql;
	char* zErrMsg = 0;
	int result;
	sql = "CREATE TABLE rooms ("  \
		"ID INTEGER  PRIMARY KEY  autoincrement," \
		"NAME CHAR(50) NOT NULL," \
		"CODE CHAR(50) NOT NULL," \
		"BUILD CHAR(50) ," \
		"TIMETABLE TEXT );";
	result = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
	if (result != SQLITE_OK) {
		std::cout << "SQL error: " << zErrMsg<<endl;
		sqlite3_free(zErrMsg);
	}
	else {
		std::cout << "Rooms table created successfully\n";
	}
}
