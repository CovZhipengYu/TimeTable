#include "classes.h"

int Classes::manageTable()
{
	int option = -1;
	BasicObject::showTable("classes");

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
	vector<Classes> classesList;
	Classes nowClasses;
	switch (option)
	{
	case 1:
		createTable( );
		break;
	case 2:
		CODE : std::cout << "Enter class code:";
		std::cin >> code;
		result = BasicObject::searchByCode("classes");
		if (result) {
			std::cout << "\nThis code has been used please enter another one:";
			goto CODE;
		}
		else {
			std::cout << "Enter class name:";
			std::cin >>  name ;
			std::cout << "Choose class grade:0 -> grade1 , 1 -> grade2 , 2 -> grade3 ";
			std::cin >> option;
			grade = (Grade) option;
			return creaateOne();
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
	case 5:
		classesList = listClasses(db);
		std::cout << "Select one to edite:";
		std::cin >> option;
		if (option < classesList.size() ) {
			nowClasses = classesList[option];
			return nowClasses.editeOne();
		}else{
			return false;
		}
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

bool Classes::creaateOne()
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
		return false;
	}
	else {
		std::cout << "Add success !" << endl;
		return true;
	}
}

bool Classes::addModules(Modules modules )
{
	modulesList.push_back(modules);
	return updateModules();
}

bool Classes::editeOne()
{
	int option = -1;
	bool  result;
	vector<Modules> List;


	std::cout << "0.return.\n";
	std::cout << "1.Change name.\n";
	std::cout << "2.Change code.\n";
	std::cout << "3.Add modules.\n";
	std::cout << "4.Delete modules.\n";
	std::cout << "5.List students.\n";
	std::cout << "Enter option:";
	std::cin >> option;

	switch (option)
	{
	case 0:
		return false;
	case 1:
		std::cout << "\nEnter class name:";
		std::cin >> name;
		return updateSelf();
	case 2:
	CODE: std::cout << "Enter class code:";
		std::cin >> code;
		result = BasicObject::searchByCode("classes");
		if (result) {
			std::cout << "\nThis code has been used please enter another one:";
			goto CODE;
		}
		else {
			return updateSelf();
		}
	case 3:
		std::cout << "\nSelect one module to add:";
		List = Modules::listModules(db);
		std::cout << "Enter option:";
		std::cin >> option;
		return addModules( List[option]);
	case 4:
		std::cout << "\nSelect one module to delete:";
		showModules();
		std::cout << "Enter option:";
		std::cin >> option;
		return deleteModules( modulesList.begin() + option);

	default:
		break;
	}
	return false;
}

bool Classes::deleteModules(vector<Modules>::iterator index)
{
	modulesList.erase(index);
	return updateModules();
}

bool Classes::updateSelf()
{
	std::string sql, isList;
	char* zErrMsg = 0;
	int result;
	sql = "UPDATE classes SET "  \
		"NAME = '" + name + "' " \
		"CODE = '" + code + "' " \
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

bool Classes::updateModules()
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
		return false;
	}
	return true;
}

void Classes::showModules()
{
	int index = 0;
	for (vector<Modules>::iterator it = modulesList.begin(); it != modulesList.end(); it++) {
		Modules modules = *it;
		std::cout << "Modules " << to_string(index) << " : name = " << modules.name << ", code = " << modules.code << ", Id = " << to_string(modules.id) << endl;
		index++;
		
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
			std::cout << "Classes" << to_string(i) << " : name = " << classes.name << ", code = " << classes.code << ", Id = " << to_string(classes.id) << endl;
			classesList.push_back(classes);
		}
	}
	else {
		std::cout << "Sql error";
	}

	sqlite3_finalize(stmt);
	return classesList;
}
