/* Main.cpp: Currently contains test code for SQLite
 */

#include <sqlite3.h>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "sqlfunctions.h"

using namespace std;

int main(int argn, char** argv)
{
    sqlite3* db;
    int rc;

    rc = sqlSetupMusicDatabase(&db);
    if (rc) {
        return(1);
    }

    rc = sqlPrintTable(db, "jobs");
    rc = sqlPrintTable(db, "locations");

    // Exit
    sqlite3_close(db);
    return(0);
}
