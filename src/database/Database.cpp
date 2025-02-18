#include <iostream>
#include <sqlite3.h>

// Helper class for query database stuff
class Database {
    private:
    sqlite3* db;
    char* errMsg = 0;

    public:
    Database(const char* filename) {
        if (sqlite3_open(filename, &db)) {
            std::cerr << "Cant open database: " << sqlite3_errmsg(db) << std::endl;
        }
        else {
            std::cout << "Database open successfully\n";
        }
    }

    ~Database() {
        sqlite3_close(db);
    }

    void executeQuery(const char* query) {
        int rc = sqlite3_exec(db, query, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
        else {
            std::cout << "Query executed successfully.\n";
        }
    }
}