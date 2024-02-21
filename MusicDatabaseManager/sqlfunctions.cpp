#include <sqlite3.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <format>
#include <vector>

#include "config.h"
#include "sqlfunctions.h"

/* Globals */
int sqlPrintTablePrintHeader = 0;

using namespace std;

int sqlSetupMusicDatabase(sqlite3** db)
{
    namespace fs = filesystem;

    int rc;
    char* zErrMsg = 0;

    // Find path to database
    fs::path databaseLocation = fs::current_path() / databaseDirectory;
    if (!fs::exists(databaseLocation)) {
        fs::create_directories(databaseLocation);
    }

    // Get database object
    // If database doesn't exist, creates the database
    fs::path databaseFile = databaseLocation / musicDatabaseName;
    rc = sqlite3_open(databaseFile.string().c_str(), db);
    if (rc != SQLITE_OK) {
        cerr << "Error: sqlSetupMusicDatabase: Can't open database.\n";
        cerr << format("\t{}\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        return(rc);
    }

    // SQL Commands to check Database Tables
    // If tables don't exist, make them
    /* TODO */

    return(rc);
}

int sqlPrintTable(sqlite3* db, const char* tablename)
{
    int rc = 0;
    char* zErrMsg;
    string sql = format("Select * from {};", tablename);
    vector<int> colSize;

    rc = sqlite3_exec(db, sql.c_str(), sqlPrintTableCallbackSetup, (void*)&colSize, &zErrMsg);
    if (rc != SQLITE_OK) {
        cerr << format("Error: sqlPrintTableCallbackSetup: SQL Error = {}\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return(rc);
    }

    sqlPrintTablePrintHeader = 1;   // Global
    rc = sqlite3_exec(db, sql.c_str(), sqlPrintTableCallbackPrint, (void*)&colSize, &zErrMsg);
    if (rc != SQLITE_OK) {
        cerr << format("Error: sqlPrintTableCallbackPrint: SQL Error = {}\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        cout << endl;
    }
    

    return(rc);
}

static int sqlPrintTableCallbackSetup(void* special, int argc, char** argv, char** azColName)
{
    int i, j;
    vector<int>* colSize = (vector<int> *)special;

    // Create initial sizes of columns based on column names
    if (colSize->size() == 0) {
        for (i = 0; i < argc; i++) {
            for (j = 0; azColName[i][j] != '\0'; j++);
            colSize->push_back(j);
        }
    }

    // Iterate through fields value, find if a column value is larger
    for (i = 0; i < argc; i++) {
        if (argv[i]) {
            for (j = 0; argv[i][j] != '\0'; j++);
            if (j > (*colSize)[i]) {
                (*colSize)[i] = j;
            }
        }
    }

    return(0);
}

static int sqlPrintTableCallbackPrint(void* special, int argc, char** argv, char** azColName)
{
    vector<int>* colSize = (vector<int>*)special;

    if (sqlPrintTablePrintHeader) {
        int bar = 1;
        for (int i = 0; i < argc; i++) {
            printf("| %-*s ", (*colSize)[i], azColName[i]); 
            bar += (*colSize)[i] + 3;
        }
        printf("|\n");
        for (int i = 0; i < bar; i++) {
            printf("=");
        }
        printf("\n");

        sqlPrintTablePrintHeader = 0;
    }

    // Print field values of table
    for (int i = 0; i < argc; i++) {
        printf("| %-*s ", (*colSize)[i], argv[i] ? argv[i] : "NULL");
    }
    printf("|\n");

    return(0);
}


// Defunc (needs update)
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
        cout << "\n";
    }

    ifs.close();
    return(rc);
}


// Prints Table (Change function name!)
static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++) {
        cout << format("{}", argv[i] ? argv[i] : NULL);
    }

    return(0);
}