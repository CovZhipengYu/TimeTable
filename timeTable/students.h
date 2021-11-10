#pragma once
#include "basicObject.h"
#include "classes.h"


class Student : public BasicObject
{
	public:
		std::string mobile;
		Classes classes;
		Grade grade;
		int  manageTable();
		Student();
		Student(sqlite3* ndb);
		Student(int lid, std::string nam, std::string cod , std::string mobile , Grade grade , int classId);
		void createTable();
		bool processOption(int option);
		bool creaateOne();
		bool editeOne();
		bool updateSelf();
		static vector<Student> listStudents(sqlite3* ndb);
};

