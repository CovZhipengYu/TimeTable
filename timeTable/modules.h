#pragma once
#include "basicObject.h"
#include "lectures.h"

class Modules : public BasicObject
{
	public:
		int weekTimes = 0;
		int lectureId = 0;
		Modules(sqlite3* ndb);
		Modules(int lid , string nam ,string cod ,int times , int lecture );
		int  manageTable();
		void createTable();
		void creaateOne();
		bool processOption(int option);
		static vector<Modules > listModules(sqlite3* db);
		static vector<Modules > selectModulesByIds(sqlite3* db , string idStr);
};

