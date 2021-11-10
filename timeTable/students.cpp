#include "students.h"

int Student::manageTable()
{	
	int option;
	BasicObject::showTable("student");
	std::cout << "Enter option:";
	std::cin >> option;
	return option;
}

Student::Student()
{
}

Student::Student(sqlite3* ndb)
{
	db = ndb;
	grade = (Grade)0;
}

Student::Student(int lid, std::string nam, std::string cod, std::string mobil, Grade grad, int classId)
{	
	id = lid;
	name = nam;
	code = cod;
	mobile = mobil;
	grade = grad;
	classes.id = classId;
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

bool Student::processOption(int option)
{
	bool result;
	vector<Student> studentList;
	Student nowStudent;
	switch (option)
	{
	case 1:
		createTable();
		break;
	case 2:
	CODE: std::cout << "Enter student code:";
		std::cin >> code;
		result = BasicObject::searchByCode("student");
		if (result) {
			std::cout << "\nThis code has been used please enter another one:";
			goto CODE;
		}
		else {
			std::cout << "Enter student name:";
			std::cin >> name;
			std::cout << "Enter student mobile:";
			std::cin >> mobile;
			std::cout << "Choose class grade:0 -> grade1 , 1 -> grade2 , 2 -> grade3 ";
			std::cin >> option;
			grade = (Grade)option;
			return creaateOne();
		}
		break;
	case 3:
		std::cout << "1.Search by code.\n";
		std::cout << "2.Search by name" << endl << "Enter option:";
		std::cin >> option;
		if (option == 1) {
			std::cout << "Enter code:";
			std::cin >> code;
			return BasicObject::searchByCode("student");
		}
		else if (option == 2) {
			std::cout << "Enter name:";
			std::cin >> name;
			return BasicObject::searchByCode("student");
		}
		break;
	case 4:
		std::cout << "Enter code:";
		std::cin >> code;
		return BasicObject::deleteByCode("student");
	case 5:
		studentList = listStudents(db);
		std::cout << "Select one to edite:";
		std::cin >> option;
		if (option < studentList.size()) {
			nowStudent = studentList[option];
			return nowStudent.editeOne();
		}
		else {
			return false;
		}
	default:
		break;
	}
	return false;
}

bool Student::creaateOne()
{
	std::string sql, isList;
	char* zErrMsg = 0;
	int result;
	sql = "INSERT INTO students ("  \
		"NAME,CODE,MOBILE,CLASSES_ID,GRADE,TIMETABLE)" \
		"VALUES ('" + name + "','" + code + "','"+mobile+"',"+ to_string(classes.id) +"," + to_string((int)grade) + " , '" + map2string(timeTable) + "');";
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

bool Student::editeOne()
{
	return false;
}

bool Student::updateSelf()
{
	return false;
}

vector<Student> Student::listStudents(sqlite3* ndb)
{
	const char* sqlSentence = "SELECT * FROM students ;";
	sqlite3_stmt* stmt = NULL;
	vector<Student> studentList;
	int result = sqlite3_prepare_v2(ndb, sqlSentence, -1, &stmt, NULL);
	int i = 1;

	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			Student student(sqlite3_column_int(stmt, 0), (char*)sqlite3_column_text(stmt, 1), (char*)sqlite3_column_text(stmt, 2), (char*)sqlite3_column_text(stmt, 3), (Grade)sqlite3_column_int(stmt, 3),sqlite3_column_int(stmt, 4));
			std::cout << "Classes" << to_string(i) << " : name = " << student.name << ", code = " << student.code << ", Id = " << to_string(student.id) << endl;
			studentList.push_back(student);
		}
	}
	else {
		std::cout << "Sql error";
	}

	sqlite3_finalize(stmt);
	return studentList;
}
