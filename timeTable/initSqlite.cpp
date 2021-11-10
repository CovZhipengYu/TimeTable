#include <iostream>
#include <stdlib.h>

#include "sqlite3.h"


sqlite3* initSplite3() {

    sqlite3* sql = NULL;
    const char* path = "../timeTable.db";

    int result = sqlite3_open_v2(path, &sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);

    if (result == SQLITE_OK) {
        std::cout << "Open databases success ." << std::endl;
    }
    else {
        std::cout << "Open databases failed !" << std::endl;
    }

    return sql;
}