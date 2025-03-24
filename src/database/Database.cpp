#ifndef DATABASE_H
#define DATABASE_H
#include <sqlite3.h>
#include <iostream>
#include <string>

using namespace std;

class Database {
    private:
    sqlite3* db;            // keep the same database connection for some methods
    const char* filename;

    // Callback function for SELECT queries (Do we need this thing?)
    static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
        for (int i = 0; i < argc; i++) {
            cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
        }
        cout << endl;
        return 0;
    }

    public:
    // Constructor for Database object
    Database(const char* dbFilename) 
        : filename{ dbFilename } 
        , db{ nullptr }
    {
        if (sqlite3_open(filename, &db) != SQLITE_OK) {
            cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        }
    }

    // Destructor
    ~Database() {
        if (db) {
            sqlite3_close(db);
        }
    }

    // Get the database pointer for direct access
    sqlite3* getDbPointer() const {
        return db;
    }

    // Create database (No need for this anymore since we have db as an object and it close on destructor)
    int createDB() {
        sqlite3* DB;
        int exit = sqlite3_open(filename, &DB);
        sqlite3_close(DB);
        return exit;
    }

    int createTable() {
        std::string sql = R"(
            CREATE TABLE IF NOT EXISTS Hospital (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL
            );

            CREATE TABLE IF NOT EXISTS Patient (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                disease TEXT NOT NULL,
                bill INTEGER NOT NULL,
                daysInHospital INTEGER DEFAULT 0,
                status INTEGER DEFAULT 1 
            );
    
            CREATE TABLE IF NOT EXISTS Doctor (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                role TEXT NOT NULL
            );
    
            CREATE TABLE IF NOT EXISTS Nurse (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL
            );
    
            CREATE TABLE IF NOT EXISTS Pharmacy (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL
            );
        )";

        return executeSQL(sql);
    }

    int executeSQL(const string& sql) {
        char* messageError = nullptr;
        
        int exit = sqlite3_exec(db, sql.c_str(), callback, NULL, &messageError);

        if (exit != SQLITE_OK) {
            cerr << "SQL error: " << messageError << endl;
            sqlite3_free(messageError);
        } else {
            cout << "SQL executed successfully!" << endl;
        }
        return exit;
    }

    // Fetch last inserted row ID
    int getLastInsertedID() {
        return sqlite3_last_insert_rowid(db);
    }

    // Fetch all hospitals
    std::vector<std::pair<int, std::string>> getAllHospitals() {
        std::vector<std::pair<int, std::string>> hospitals;
        std::string sql = "SELECT id, name FROM Hospital;";
        char* messageError = nullptr;

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                int id = sqlite3_column_int(stmt, 0);
                const unsigned char* name = sqlite3_column_text(stmt, 1);
                hospitals.emplace_back(id, name ? reinterpret_cast<const char*>(name) : "");
            }
        } else {
            std::cerr << "Error: " << sqlite3_errmsg(db) << std::endl;
        }
        sqlite3_finalize(stmt);
        return hospitals;
    }
};


#endif