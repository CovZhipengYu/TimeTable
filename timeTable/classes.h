#pragma once
#include < vector> 
#include "basicObject.h"
#include "modules.h"


class Classes : public BasicObject
{
	public:
		Grade grade;
		vector<Modules> modulesList;
		int  manageTable();
		Classes();
		Classes(sqlite3* ndb);
		Classes(int lid, string nam, string cod, Grade grade, string mList, sqlite3* ndb);
		bool processOption(int option);
		void createTable();
		void creaateOne();
		bool editeOne();
		bool updateSelf();
		static vector<Classes > listClasses(sqlite3* db);
		void addModules(Modules modules);
		void deleteModules(vector<Modules>::iterator index );
		void updateModules();


};

