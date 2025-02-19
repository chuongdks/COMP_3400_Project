#include <sqlite3.h>
#include <iostream>
#include <string>

using namespace std;

class Database {
    private:
    const char* filename;
    
    // Callback function for SELECT queries
    static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
        for (int i = 0; i < argc; i++) {
            cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
        }
        cout << endl;
        return 0;
    }

    public:
    Database(const char* dbFilename) 
        : filename { dbFilename } 
    {}

    int createDB() {
        sqlite3* DB;
        int exit = sqlite3_open(filename, &DB);
        sqlite3_close(DB);
        return exit;
    }

    int createTable() {
        std::string sql = R"(
            CREATE TABLE IF NOT EXISTS Hospital (
                id INTEGER PRIMARY KEY,
                name TEXT NOT NULL
            );
    
            CREATE TABLE IF NOT EXISTS Patient (
                id INTEGER PRIMARY KEY,
                name TEXT NOT NULL,
                disease TEXT NOT NULL,
                bill INTEGER NOT NULL,
                daysInHospital INTEGER DEFAULT 0
            );
    
            CREATE TABLE IF NOT EXISTS Doctor (
                id INTEGER PRIMARY KEY,
                name TEXT NOT NULL,
                role TEXT NOT NULL
            );
    
            CREATE TABLE IF NOT EXISTS Nurse (
                id INTEGER PRIMARY KEY,
                name TEXT NOT NULL
            );
    
            CREATE TABLE IF NOT EXISTS Pharmacy (
                id INTEGER PRIMARY KEY,
                name TEXT NOT NULL
            );
        )";

        return executeSQL(sql);
    }

    int executeSQL(const string& sql) {
        sqlite3* DB;
        char* messageError;
        
        int exit = sqlite3_open(filename, &DB);
        exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

        if (exit != SQLITE_OK) {
            cerr << "SQL error: " << messageError << endl;
            sqlite3_free(messageError);
        } else {
            cout << "SQL executed successfully!" << endl;
        }

        sqlite3_close(DB);
        return exit;
    }
};


