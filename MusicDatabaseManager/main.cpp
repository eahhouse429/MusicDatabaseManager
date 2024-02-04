/* Main.cpp: Currently contains test code for SQLite
 */

#include <sqlite3.h>
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace std;

static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return(0);
}

int main(int argn, char** argv)
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    const char dbLocation[] = "db/TestDatabase.db";
    const char sqlStatement[] = "select * from jobs;\n";

    filesystem::path cwd = filesystem::current_path();
    cout << format("cwd: {}\n", cwd.string());

    // Open Database based on name given
    if (!filesystem::exists("db")) {
        cerr << format("Database directory does not exist at \"{}\"\n", cwd.string());
        return(1);
    }
    rc = sqlite3_open(dbLocation, &db);
    if (rc) {
        cerr << format("Can't open database: {}\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(1);
    }

    // Evaluate SQL statement given as string argument. Capable of running multiple SQL statement
    rc = sqlite3_exec(db, sqlStatement, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        cerr << format("SQL error: {}\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    // Exit
    sqlite3_close(db);
    return(0);

    // Test Commit
}
