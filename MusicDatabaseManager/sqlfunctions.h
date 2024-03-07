#pragma once

/* Setup Database
 *	- Check if Music Database exists
 *  - If it doesn't exist, create a new database
 *  - Return sqlite3 object to database
 */
int sqlSetupMusicDatabase(sqlite3** db);

int sqlPrintTable(sqlite3* db, const char* tablename);
static int sqlPrintTableCallbackSetup(void* special, int argc, char** argv, char** azColName);
static int sqlPrintTableCallbackPrint(void* special, int argc, char** argv, char** azColName);

int sqlExecFile(sqlite3* db, const char* filename);

// Defunc
int sqlinput_execfile(sqlite3* db, const char *filename, void* first, char **errMsg);
static int callback(void* NotUsed, int argc, char** argv, char** azColName);
