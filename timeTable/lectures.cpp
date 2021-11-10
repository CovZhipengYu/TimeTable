#include "lectures.h"

int Lectures::manageTable()
{
	int option;
	BasicObject::showTable("Lectures");
	std::cout << "Enter option:";
	std::cin >> option;
	return option;
}

Lectures::Lectures()
{
	
}

Lectures::Lectures(sqlite3* ndb)
{
	db = ndb;
}

Lectures::Lectures(int lid, std::string nam, std::string cod, std::string mobil)
{
	id = lid;
	name = nam;
	code = cod;
	mobile = mobil;
}

bool Lectures::processOption(int option)
{
	bool result;

	switch (option)
	{
	case 1:
		createTable();
		break;
	case 2:
		CODE : std::cout << "\nEnter lecture's code:";
		std::cin >> code;
		result = BasicObject::searchByCode("lectures");
		if (result) {
			std::cout << "This code has been used please enter another one:";
			goto CODE;
		}
		else {
			std::cout << "Enter lectures name:";
			std::cin >> name;
			std::cout << "Enter lectures tel number :";
			std::cin >> mobile;
			creaateOne();
			return true;
		}
		break;
	case 3:
		std::cout << "1.Search by code.\n";
		std::cout << "2.Search by name.\nEnter option:";
		std::cin >> option;
		if (option == 1) {
			std::cout << "\nEnter code:";
			std::cin >> code;
			return BasicObject::searchByCode("lectures");
		}
		else if (option == 2) {
			std::cout << "\nEnter name:";
			std::cin >> name;
			return BasicObject::searchByCode("lectures");
		}
		break;
	case 4:
		std::cout << "Enter code:";
		std::cin >> code;
		return BasicObject::deleteByCode("lectures");
	case 5:
		return ("lectures");
	default:
		break;
	}
	return false;
}

void Lectures::createTable()
{
	std::string sql;
	char* zErrMsg = 0;
	int result;
	sql = "CREATE TABLE lectures ("  \
		"ID INTEGER  PRIMARY KEY  autoincrement," \
		"NAME CHAR(50) NOT NULL," \
		"CODE CHAR(50) NOT NULL," \
		"MOBILE CHAR(50) NOT NULL ," \
		"TIMETABLE TEXT );";
	result = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
	if (result != SQLITE_OK) {
		std::cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	else {
		std::cout << "Lectures table created successfully\n";
	}
}

void Lectures::creaateOne()
{
	std::string sql, isList;
	char* zErrMsg = 0;
	int result;
	sql = "INSERT INTO lectures ("  \
		"NAME,CODE,MOBILE,TIMETABLE)" \
		"VALUES ('" + name + "','" + code + "'," + mobile + " , '" + map2string(timeTable) + "');";
	result = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
	if (result != SQLITE_OK) {
		std::cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	else {
		std::cout << "Add success !" << endl;
	}
}

vector<Lectures> Lectures::listLectures(sqlite3* db)
{
	const char* sqlSentence = "SELECT * FROM lectures ;";
	sqlite3_stmt* stmt = NULL;    
	vector<Lectures> lecturesList;
	int result = sqlite3_prepare_v2( db , sqlSentence, -1, &stmt, NULL);
	int i = 1;

	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			Lectures lectures( sqlite3_column_int(stmt, 0) , (char*)sqlite3_column_text(stmt, 1), (char*)sqlite3_column_text(stmt, 2), (char*)sqlite3_column_text(stmt, 3));
			std::cout << "Lecture "<< to_string(i) <<" : name = " << lectures.name << ", code = " << lectures.code << ", Id = " << to_string(lectures.id) << endl;
			lecturesList.push_back(lectures);
			i++;
		}
	}
	else {
		std::cout << "Sql error";
	}
	
	sqlite3_finalize(stmt);
	return lecturesList;
}

bool Lectures::editeOne()
{
	vector< Lectures > lecturesList;
	int option;
	bool result;

	std::cout << "Select lecturers to edite :\n";
	lecturesList = listLectures(db);
SELECT: std::cout << "Enter Option :";
	std::cin >> option;
	if (option < 0 || option > lecturesList.size() ) {
		std::cout << "Wrong Option !\n";
		goto SELECT;
	}
	Lectures nowLectures = lecturesList[option];

	ENTERCODE : std::cout << "Enter lecture's code:";
	std::cin >> nowLectures.code;
	result = nowLectures.searchByCode("lectures");
	if (result) {
		std::cout << "\nThis code has been used please enter another one:";
		goto ENTERCODE;
	}
	else {
		std::cout << "\nEnter lectures name:";
		std::cin >> nowLectures.name;
		std::cout << "\nEnter lectures tel number :";
		std::cin >> nowLectures.mobile;
		return nowLectures.updateSelf();
	}
}

bool Lectures::updateSelf() {
	std::string sql, isList;
	char* zErrMsg = 0;
	int result;
	sql = "UPDATE lectures SET "  \
		"NAME = '" + name + "' " \
		"CODE = '" + code + "' " \
		"MOBILE = '" + mobile + "' " \
		"WHERE id = " + to_string(id) + ";";
	result = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
	if (result != SQLITE_OK) {
		std::cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
		return false;
	}
	else {
		std::cout << "Update success !" << endl;
		return true;
	}
}
