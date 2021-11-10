#include "basicObject.h"


void BasicObject::showTable(string objectName )
{
    cout << "******   Coventry University timeTable manage " << objectName << "   ******\n";
    cout << "Input number to choose option:\n";
    cout << "0.Return\n";
    cout << "1.Create table for " << objectName << endl;
    cout << "2.Add " << objectName << endl;
    cout << "3.Search " << objectName << endl;
    cout << "4.Delete " << objectName << endl;
    cout << "5.Editer " << objectName << endl;
}

BasicObject::BasicObject()
{
	initTimeTable();
}

BasicObject::BasicObject(string nam, string cod)
{
    name = nam;
    code = cod;
}

void BasicObject::initTimeTable()
{
	map<string, string> oneDayLesson;
	oneDayLesson.insert(pair<string, string>("0", "       "));
	oneDayLesson.insert(pair<string, string>("1", "       "));
	oneDayLesson.insert(pair<string, string>("2", "       "));
	oneDayLesson.insert(pair<string, string>("3", "       "));
	oneDayLesson.insert(pair<string, string>("4", "       "));
	oneDayLesson.insert(pair<string, string>("5", "       "));

	timeTable.insert(pair<string, map<string, string>>("Monday", oneDayLesson));
	timeTable.insert(pair<string, map<string, string>>("Tuesday", oneDayLesson));
	timeTable.insert(pair<string, map<string, string>>("Wednesday", oneDayLesson));
	timeTable.insert(pair<string, map<string, string>>("Thursday", oneDayLesson));
	timeTable.insert(pair<string, map<string, string>>("Friday", oneDayLesson));
	timeTable.insert(pair<string, map<string, string>>("Saturday", oneDayLesson));

}

void BasicObject::showTimeTable()
{
	map<string, map<string, string>>::iterator p2;
	map<string, string>::iterator p3;
	cout << "              |  Monday  |  Tuesday  |  Wednesday  |  Thursday  |  Friday  |  Saturday  \n";
	cout << " First lesson |  " + timeTable["Monday"]["0"] + "  |  " + timeTable["Tuesday"]["0"] + "  |  " + timeTable["Wednesday"]["0"] + "  |  " + timeTable["Thursday"]["0"] + "  |  " + timeTable["Friday"]["0"] + "  |  " + timeTable["Saturday"]["0"] + "  \n";
	cout << " Second lesson|  " + timeTable["Monday"]["1"] + "  |  " + timeTable["Tuesday"]["1"] + "  |  " + timeTable["Wednesday"]["1"] + "  |  " + timeTable["Thursday"]["1"] + "  |  " + timeTable["Friday"]["1"] + "  |  " + timeTable["Saturday"]["1"] + "  \n";
	cout << " Third lesson |  " + timeTable["Monday"]["2"] + "  |  " + timeTable["Tuesday"]["2"] + "  |  " + timeTable["Wednesday"]["2"] + "  |  " + timeTable["Thursday"]["2"] + "  |  " + timeTable["Friday"]["2"] + "  |  " + timeTable["Saturday"]["2"] + "  \n";
	cout << " Fourth lesson|  " + timeTable["Monday"]["3"] + "  |  " + timeTable["Tuesday"]["3"] + "  |  " + timeTable["Wednesday"]["3"] + "  |  " + timeTable["Thursday"]["3"] + "  |  " + timeTable["Friday"]["3"] + "  |  " + timeTable["Saturday"]["3"] + "  \n";
	cout << " Fifth lesson |  " + timeTable["Monday"]["4"] + "  |  " + timeTable["Tuesday"]["4"] + "  |  " + timeTable["Wednesday"]["4"] + "  |  " + timeTable["Thursday"]["4"] + "  |  " + timeTable["Friday"]["4"] + "  |  " + timeTable["Saturday"]["4"] + "  \n";
	cout << " Sixth lesson |  " + timeTable["Monday"]["5"] + "  |  " + timeTable["Tuesday"]["5"] + "  |  " + timeTable["Wednesday"]["5"] + "  |  " + timeTable["Thursday"]["5"] + "  |  " + timeTable["Friday"]["5"] + "  |  " + timeTable["Saturday"]["5"] + "  \n";

}

int BasicObject::manageTable()
{
    return 0;
}

bool BasicObject::processOption(int option)
{
    return false;
}

void BasicObject::createTable()
{
}

bool BasicObject::searchByCode(string objectName)
{
	string sql;
	sqlite3_stmt* stmt = NULL;
	const char* zErrMsg = 0;
	int result;

	sql = "SELECT * FROM "+ objectName +" WHERE CODE = '" + code + "' LIMIT 1";
	result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, &zErrMsg);
	if (result == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW) {

			id = sqlite3_column_int(stmt, 0);
			const unsigned char* value = sqlite3_column_text(stmt, 1);
			name = (char*)value;
			value = sqlite3_column_text(stmt, 2);
			code = (char*)value;
			cout << objectName << "info : name = " << name << ", code = " << code << endl;
			int index = 0;
			if (objectName.compare("classes") || objectName.compare("lectures") ) {
				index = 4;
			}
			else if (objectName.compare("students")) {
				index = 6;
			}
			if (index != 0) {
				timeTable = string2map((char*)sqlite3_column_text(stmt, index));
				showTimeTable();
			}
			sqlite3_finalize(stmt);
			return true;
	}
	else if (result != SQLITE_OK) {
		cout << "Sql string error:" << zErrMsg;
	}
	sqlite3_finalize(stmt);
	return false;

}

bool BasicObject::searchByName(string objectName)
{
	string sql;
	sqlite3_stmt* stmt = NULL;
	int result;
	const char* zErrMsg = 0;
	sql = "SELECT * FROM " + objectName + " WHERE `NAME` = '%" + name + "%' LIMIT 1";
	result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, &zErrMsg);

	if (result == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW ) {		
			id = sqlite3_column_int(stmt, 0);
			const unsigned char* value = sqlite3_column_text(stmt, 1);
			name = (char*)value;
			value = sqlite3_column_text(stmt, 2);
			code = (char*)value;
			cout << objectName << "info : name = " << name << ", code = " << code;

			int index = 0;
			if (objectName.compare("classes") || objectName.compare("lectures")) {
				index = 4;
			}
			else if (objectName.compare("students")) {
				index = 6;
			}
			if (index != 0) {
				timeTable = string2map((char*)sqlite3_column_text(stmt, index));
				showTimeTable();
			} 
			sqlite3_finalize(stmt);
			return true;
	}
	else if(result != SQLITE_OK){
		cout << "Sql string error:"<< zErrMsg ;
	}
	
	sqlite3_finalize(stmt);
	return false;
}

bool BasicObject::deleteByCode(string objectName)
{
	string sql;
	sqlite3_stmt* stmt = NULL;
	int result;
	char* zErrMsg = 0;
	sql = "DELETE  FROM " + objectName + " WHERE `code` = '" + code + "' LIMIT 1";

	result = sqlite3_exec(db, sql.c_str(), NULL , NULL , &zErrMsg);
	if (result != SQLITE_OK) {
		cout << "Sql string error:" << zErrMsg;
		sqlite3_free(zErrMsg);
	}
	else {
		cout << "Delete data success." << zErrMsg;
	}
	return true;
}

string BasicObject::map2string(map<string, map<string, string>> Map )
{
	Json::Value jObject;

	map<string, map<string, string>>::iterator p2;
	map<string, string>::iterator p3;

	for (p2 = Map.begin(); p2 != Map.end(); p2++)
	{
		Json::Value jObject2;
		for (p3 = p2->second.begin(); p3 != p2->second.end(); p3++) {
			jObject2[p3->first] = p3->second;
		}
		jObject[p2->first] = jObject2;
	}
	return jObject.toStyledString();
}

map<string, map<string, string>> BasicObject::string2map(string jsonStr)
{
	Json::CharReaderBuilder b;
	Json::CharReader* reader(b.newCharReader());
	Json::Value value;
	JSONCPP_STRING errs;
	map<string, map<string, string>> maps;

	if (jsonStr.length() > 0 )
	{
		if (reader->parse( jsonStr.data(), jsonStr.data() + std::strlen(jsonStr.data()) , &value , &errs ))
		{
			Json::Value::Members members = value.getMemberNames();

			for (Json::Value::Members::iterator it = members.begin(); it != members.end(); it++)
			{
				Json::CharReaderBuilder c;
				Json::CharReader* innerReader(c.newCharReader());
				Json::Value innerValue = value[*it];
				map<string, string> innerMap;

				Json::Value::Members innerMembers = innerValue.getMemberNames();

				for (Json::Value::Members::iterator it2 = innerMembers.begin(); it2 != innerMembers.end(); it2++) {
					innerMap.insert(pair<string, string>(*it2, innerValue[*it2].asString()));
				}
				maps.insert(pair<string, map<string, string>> (*it, innerMap) );

			}
		}
	}

	return maps;
}
