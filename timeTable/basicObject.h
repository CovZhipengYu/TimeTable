#pragma once
#include <string>
#include <iostream>
#include <map>

#include "sqlite/sqlite3.h"
#include "json/json.h"


using namespace std;

#define enum_to_string(x) #x

sqlite3* initSplite3();


enum class Grade
{
	grade1, grade2, grade3
};

class BasicObject
{
	public:
		sqlite3* db;
		int id;
		string name;
		string code;
		map<string, map<string, string>> timeTable;
		static void showTable(string objectName);
		BasicObject();
		BasicObject(string nam, string cod);
		void initTimeTable();
		void showTimeTable();
		virtual int manageTable();
		virtual bool processOption(int option);
		virtual void createTable();
		bool searchByCode( string objectName );
		bool searchByName( string objectName );
		bool deleteByCode(string objectName);
		string map2string(map<string, map<string, string>> Map );
		map<string, map<string, string>> string2map(string jsonStr);
};

