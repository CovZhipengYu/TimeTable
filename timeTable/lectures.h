#pragma once
#include "basicObject.h"
#include "modules.h"

class Lectures : public BasicObject
{	
	public:
		int  manageTable();
		std::string mobile;
		Lectures();
		Lectures(sqlite3* ndb);
		Lectures(int lid ,std::string nam, std::string cod, std::string mobil);
		bool processOption(int option);
		void createTable();
		void creaateOne();
		bool editeOne();
		bool updateSelf();
		static vector<Lectures > listLectures(sqlite3* db);
};

