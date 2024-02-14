#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <format>

#include "sqlinput.h"

using namespace std;

int sqlinput_execfile(sqlite3* db, const char* filename, void* first, char** errMsg)
{
    int rc = 0;
    ifstream ifs;   // Filestream for sql statements
    char sqlline[256] = "\0";

    ifs.open(filename, ifstream::in);

    while (ifs.good()) {
        ifs.getline(sqlline, 256);
        if (ifs.bad()) {
            cout << format("sqlinput_execfile: bad character read.\n");
            break;
        }
        rc = sqlite3_exec(db, sqlline, callback, 0, errMsg);
    }

    ifs.close();
    return(rc);
}


static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return(0);
}