#pragma once

int sqlinput_execfile(sqlite3* db, const char *filename, void* first, char **errMsg);
static int callback(void* NotUsed, int argc, char** argv, char** azColName);