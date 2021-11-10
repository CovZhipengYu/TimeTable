#include "classes.h"

int Classes::manageTable()
{
	int option = -1;
	BasicObject::showTable("classes");
	std::cout << "6.List students.\n";
	std::cout << "7.List modules.\n";
	std::cout << "8.Add modules.\n";
	std::cout << "Enter option:";
	std::cin >> option;
	return option;
	
}

Classes::Classes()
{
	grade = Grade::grade1;
}

Classes::Classes(sqlite3* ndb)
{
	db = ndb;
	grade = Grade::grade1;
}

Classes::Classes(int lid ,string nam, string cod, Grade grad ,string mList, sqlite3* ndb)
{
	id = lid;
	name = nam;
	code = cod;
	db = ndb;
	grade = grad;
	modulesList = Modules::selectModulesByIds(db, mList);
}

bool Classes::processOption(int option )
{	
	bool result;

	switch (option)
	{
	case 1:
		createTable( );
		break;
	case 2:
		std::cout << "Enter class code:";
		std::cin >> code;
		result = BasicObject::searchByCode("classes");
		if (result) {
			std::cout << "\nThis code has been used please enter another one:";
			return false;
		}
		else {
			std::cout << "\nEnter class name:";
			std::cin >>  name ;
			std::cout << "\nChoose class grade:0 -> grade1 , 1 -> grade2 , 2 -> grade3 ";
			std::cin >> option;
			grade = (Grade) option;
			creaateOne();
			return true;
		}
		break;
	case 3:
		std::cout << "1.Search by code.\n";
		std::cout << "2.Search by name"<< endl <<"Enter option:";
		std::cin >> option;
		if (option == 1) {
			std::cout << "Enter code:";
			std::cin >> code;
			return BasicObject::searchByCode("classes");
		}
		else if (option == 2) {
			std::cout << "Enter name:";
			std::cin >> name;
			return BasicObject::searchByCode("classes");
		}
		break;
	case 4:
		std::cout << "Enter code:";
		std::cin >> code;
		return BasicObject::deleteByCode("classes");
	default:
		break;
	}
	return false;
}

void Classes::createTable()
{
	std::string sql;
	char* zErrMsg = 0;
	int result;
	sql = "CREATE TABLE classes ( "  \
		"ID INTEGER  PRIMARY KEY  autoincrement ," \
		"NAME CHAR(50) NOT NULL ," \
		"CODE CHAR(50) NOT NULL ," \
		"GRADE TINYINT ," \
		"TIMETABLE TEXT ," \
		"MODULESID TEXT );";
	result = sqlite3_exec( db , sql.c_str() ,0, 0, &zErrMsg);
	if (result != SQLITE_OK) {
		std::cout <<  "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}

void Classes::creaateOne()
{
	std::string sql,isList;
	char* zErrMsg = 0;
	int result;
	for (vector<Modules>::iterator it = modulesList.begin(); it != modulesList.end(); it++) {
		Modules modules = *it;
		isList += to_string(modules.id) + ",";
	}

	sql = "INSERT INTO classes ("  \
		"NAME,CODE,GRADE,TIMETABLE, MODULESID )" \
		"VALUES ('" + name + "','" + code + "',"+ to_string((int)grade)+" , '"+ map2string(timeTable)  +"','"+ isList +"');";
	result = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
	if (result != SQLITE_OK) {
		std::cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	else {
		std::cout << "Add success !" << endl;
	}
}

void Classes::addModules(Modules modules )
{
	modulesList.push_back(modules);
	updateModules();
}

void Classes::deleteModules(vector<Modules>::iterator index)
{
	modulesList.erase(index);
	updateModules();
}

void Classes::updateModules()
{
	std::string sql, isList;
	char* zErrMsg = 0;
	int result;
	for (vector<Modules>::iterator it = modulesList.begin(); it != modulesList.end(); it++) {
		Modules modules = *it;
		isList += to_string(modules.id) + ",";
	}

	sql = "UPDATE classes SET "  \
		"MODULESID = '" + isList + "' "\
		"WHERE code = '"  + code + "';";
	result = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
	if (result != SQLITE_OK) {
		std::cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}

vector<Classes> Classes::listClasses(sqlite3* db)
{
	const char* sqlSentence = "SELECT * FROM classes ;";
	sqlite3_stmt* stmt = NULL;
	vector<Classes> classesList;
	int result = sqlite3_prepare_v2(db, sqlSentence, -1, &stmt, NULL);
	int i = 1;

	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			Classes classes( sqlite3_column_int(stmt, 0), (char*)sqlite3_column_text(stmt, 1), (char*)sqlite3_column_text(stmt, 2), (Grade)sqlite3_column_int(stmt, 3) , (char*)sqlite3_column_text(stmt, 4),db);
			int age = sqlite3_column_int(stmt, 1);
			std::cout << "Lecture" << to_string(i) << " : name = " << classes.name << ", code = " << classes.code << ", Id = " << to_string(classes.id) << endl;
			classesList.push_back(classes);
		}
	}
	else {
		std::cout << "Sql error";
	}

	sqlite3_finalize(stmt);
	return classesList;
}
