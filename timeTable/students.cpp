#include "students.h"

int Student::manageTable()
{	
	int option;
	BasicObject::showTable("student");
	std::cout << "Enter option:";
	std::cin >> option;
	return option;
}

Student::Student(sqlite3* ndb)
{
	db = ndb;
	grade = (Grade)0;
}

Student::Student(std::string nam, std::string cod, std::string mobil, Grade grad)
{	
	name = nam;
	code = cod;
	mobile = mobil;
	grade = grad;
}

void Student::createTable()
{
	std::string sql;
	char* zErrMsg = 0;
	int result;
	sql = "CREATE TABLE students ("  \
		"ID INTEGER  PRIMARY KEY  autoincrement ," \
		"NAME CHAR(50) NOT NULL ," \
		"CODE CHAR(50) NOT NULL ," \
		"MOBILE CHAR(50)  ," \
		"CLASSES_ID INT ," \
		"GRADE TINYINT ," \
		"TIMETABLE TEXT );";
	result = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
	if (result != SQLITE_OK) {
		std::cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	else {
		std::cout << "Students table created successfully\n";
	}
}