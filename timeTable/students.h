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
		Student(sqlite3* ndb);
		Student(std::string nam, std::string cod , std::string mobile , Grade grade );
		void createTable();
};

