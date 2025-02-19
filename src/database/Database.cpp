#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <string>

class Database {
    private:
    sqlite3* db;  // Database connection pointer
    std::string dbName;

    public:
    // Create Database
    Database(const std::string& filename) 
        : dbName(filename) 
    {
        if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
            std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        } 
        else {
            std::cout << "Database connected: " << dbName << std::endl;
        }
    }

    // Creates tables if they don’t exist
    void createTables() {
        char* errorMessage = nullptr;

        std::string sql = R"(
            CREATE TABLE IF NOT EXISTS Hospital (
                id INTEGER PRIMARY KEY,
                name TEXT NOT NULL
            );

            CREATE TABLE IF NOT EXISTS Patient (
                id INTEGER PRIMARY KEY,
                name TEXT NOT NULL,
                disease TEXT NOT NULL,
                bill INTEGER NOT NULL
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

        // if (!executeQuery(sql)) {
        //     std::cerr << "Failed to create tables." << std::endl;
        // }

        try
        {
            int exit = 0;
            /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
            exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &errorMessage);
            if (exit != SQLITE_OK) {
                std::cerr << "Error in createTable function." << std::endl;
                sqlite3_free(errorMessage);
            }
            else
                std::cout << "Table created Successfully" << std::endl;
                sqlite3_close(db);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what();
        }
    }

    // Destructor
    ~Database() 
    {
        sqlite3_close(db);
    }

    // Executes INSERT, DELETE, UPDATE queries
    bool executeQuery(const std::string& sql) {
        char* errorMessage = nullptr;
        int exit = sqlite3_exec(db, sql.c_str(), nullptr, 0, &errorMessage);

        if (exit != SQLITE_OK) {
            std::cerr << "SQL error: " << errorMessage << std::endl;
            sqlite3_free(errorMessage);
            return false;
        }
        return true;
    }

    // Fetches results for SELECT queries
    std::vector<std::vector<std::string>> fetchQuery(const std::string& sql) {
        std::vector<std::vector<std::string>> results;
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            int columnCount = sqlite3_column_count(stmt);

            while (sqlite3_step(stmt) == SQLITE_ROW) {
                std::vector<std::string> row;
                for (int i = 0; i < columnCount; ++i) {
                    const char* data = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                    row.push_back(data ? data : "NULL");
                }
                results.push_back(row);
            }
        } else {
            std::cerr << "Failed to execute SELECT query." << std::endl;
        }

        sqlite3_finalize(stmt);
        return results;
    }
};

