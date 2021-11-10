#include <iostream>
#include <stdlib.h>


#include "sqlite/sqlite3.h"
#include "basicObject.h"

#include "modules.h"
#include "classes.h"
#include "students.h"
#include "lectures.h"
#include "rooms.h"


int main()
{
    int option = -1;
    std::string objectName;
    sqlite3* db = initSplite3();
    bool result = false;


    BasicObject *object = new BasicObject();
    Modules *modules = new Modules(db);
    Classes *classes = new Classes(db);
    Student *student = new Student(db);
    Lectures *lectures = new Lectures(db);
    Room *room = new Room(db);
    

    START: std::cout << "******   Coventry University timeTable!   ******\n";
    std::cout << "Input number to choose option:\n";
    std::cout << "1.Manage modules.\n";
    std::cout << "2.Manager classes\n";
    std::cout << "3.Manage students.\n";
    std::cout << "4.Manager lectures\n";
    std::cout << "5.Manager rooms\n";
    std::cout << "6.Initialize database.\n";
    std::cout << "7.Exit.\n";
    std::cout << "Enter option:";
    std::cin >> option;

    if (option == 0 || option > 7) {
        std::cout << "Wrong option with: "<< option << std::endl;
        goto START;
    }

    switch (option)
    {
        case 1:
            objectName = "modules";
            object = modules;
            break;
        case 2:
            objectName = "classes";
            object = classes;
            break;
        case 3:
            objectName = "students";
            object = student;
            break;
        case 4:
            objectName = "lectures";
            object = lectures;
            break;
        case 5:
            objectName = "rooms";
            object = room;
            break;
        case 6:
            modules->createTable();
            classes->createTable();
            student->createTable();
            lectures->createTable();
            room->createTable();
            goto START;
        case 7:
            sqlite3_close(db);
            exit(0);
            break;
        default:
            break;
    }
   
NewOption: option = object->manageTable();
   

    if (option == 0 ) {
        goto START;
    }else if(option > 6){
        std::cout << "Wrong option with: " << option << std::endl;
        goto NewOption;
    }

    result = object->processOption(option);
    goto NewOption;
    
    sqlite3_close(db);
}

