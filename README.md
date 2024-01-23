# MusicDatabaseManager
A personal project for an organized database of music collected, listened to, or need to be listened to. The objective of this project is not to provide a thorough database on all music, but to create a database based on personal listening habits and statistics, which is updated manual by the user.

All music information is stored in a SQL database, accessed with the SQLite3 library. SQLite is an open-source, self-contained SQL database engine for C and C++, and may be downloaded from the [official SQLite home page](https://www.sqlite.org/index.html).

## Current Features
None. Still in early development and testing.

## Planned Features
Primary
- Function to create new music database with necessary tables.
- Function to link to
- Function to add new artists and album information to database.
- Function to updates personal listening habits.
  -  Total times listened to album, times listened to artist, total listening hours, times listened to genre.
- Tokenizer to read command line options for inputs to call functions.

Future
- Function to recommend album to listen to.
  - Ex. If you want something new, find an album in database that has 0 listens
- Function to return listening statistics
- Automatically download statistics on artists from online database.
  - Investigate online music databases.
