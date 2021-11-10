#include "modules.h"


Modules::Modules(sqlite3* ndb)
{
	db = ndb;
}

Modules::Modules(int lid, string nam, string cod, int times , int lecture)
{
	id = lid;
	name = nam;
	code = cod;
	weekTimes = times;
	lectureId = lecture;
}

int Modules::manageTable()
{
	int option;
	BasicObject::showTable("modules");
	std::cout << "Enter option:";
	std::cin >> option;
	return option;
}

bool Modules::processOption(int option)
{
	bool result;
	vector< Lectures > lecturesList;
	vector<Lectures>::iterator it;
	switch (option)
	{
	case 1:
		createTable();
		break;
	case 2:
		std::cout << "Enter module's code:";
		std::cin >> code;
		result = BasicObject::searchByCode("modules");
		if (result) {
			std::cout << "\nThis code has been used please enter another one:";
			return false;
		}
		else {
			std::cout << "\nEnter module's name:";
			std::cin >> name;
			std::cout << "How many classes are there in the modules a week :";
			std::cin >> weekTimes;
			std::cout << "Select lecturers :\n";
			lecturesList = Lectures::listLectures(db);
			SELECT : std::cout << "Enter Option :";
			std::cin >> option;
			
			if (option < 0 || option > lecturesList.size() ) {
				std::cout << "Wrong Option !\n";
				goto SELECT;
			}
			lectureId = lecturesList[option].id;
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
			return BasicObject::searchByCode("modules");
		}
		else if (option == 2) {
			std::cout << "\nEnter name:";
			std::cin >> name;
			return BasicObject::searchByCode("modules");
		}
		break;
	case 4:
		std::cout << "Enter code:";
		std::cin >> code;
		return BasicObject::deleteByCode("modules");

	default:
		break;
	}
	return false;
}

vector<Modules> Modules::listModules(sqlite3* db)
{
	const char* sqlSentence = "SELECT * FROM modules ;";
	sqlite3_stmt* stmt = NULL;
	vector<Modules> modulesList;
	int result = sqlite3_prepare_v2(db, sqlSentence, -1, &stmt, NULL);
	int i = 1;

	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			Modules modules(sqlite3_column_int(stmt, 0), (char*)sqlite3_column_text(stmt, 1), (char*)sqlite3_column_text(stmt, 2), sqlite3_column_int(stmt, 3) , sqlite3_column_int(stmt, 4));
			std::cout << "Modules " << to_string(i) << " : name = " << modules.name << ", code = " << modules.code << ", Id = " << to_string(modules.id) << endl;
			modulesList.push_back(modules);
			i++;
		}
	}
	else {
		std::cout << "Sql error";
	}

	sqlite3_finalize(stmt);
	return modulesList;
}

vector<Modules> Modules::selectModulesByIds(sqlite3* db, string idStr)
{
	string sqlSentence = "SELECT * FROM modules WHERE id IN ( "+idStr+" );";
	sqlite3_stmt* stmt = NULL;
	vector<Modules> modulesList;
	int result = sqlite3_prepare_v2(db,sqlSentence.c_str(), -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			Modules modules(sqlite3_column_int(stmt, 0), (char*)sqlite3_column_text(stmt, 1), (char*)sqlite3_column_text(stmt, 2), sqlite3_column_int(stmt, 3), sqlite3_column_int(stmt, 4));
			modulesList.push_back(modules);
		}
	}
	else {
		std::cout << "Sql error";
	}

	sqlite3_finalize(stmt);
	return modulesList;
}

void Modules::createTable()
{
	std::string sql;
	char* zErrMsg = 0;
	int result;
	sql = "CREATE TABLE modules ("  \
		"ID INTEGER  PRIMARY KEY  autoincrement," \
		"NAME CHAR(50) NOT NULL," \
		"CODE CHAR(50) NOT NULL," \
		"WEEKTIMES INT DEFAULT 0 ," \
		"LECTURE_ID INT DEFAULT 0 );";
	result = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
	if (result != SQLITE_OK) {
		std::cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	else {
		std::cout << "Modules table created successfully\n";
	}
}

void Modules::creaateOne()
{
	std::string sql;
	char* zErrMsg = 0;
	int result;
	sql = "INSERT INTO modules "  \
		"(NAME,CODE ,WEEKTIMES ,LECTURE_ID )" \
		"VALUES ('"+name+"','"+code+"','"+ to_string(weekTimes) +"','" + to_string(lectureId) + "')";
	result = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
	if (result != SQLITE_OK) {
		std::cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	else {
		std::cout << "Add success !" << endl;
	}
}
