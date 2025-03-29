#include <sqlite3.h>
#include <iostream>
#include <string>

using namespace std;

class Database {
private:
    const char* filename;

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

    int insertData() {
        string sql = "INSERT INTO Patient (NAME, DISEASE, BILL) VALUES "
                     "('John Doe', 'Flu', 50), "
                     "('Jane Smith', 'Cold', 30), "
                     "('Alice Brown', 'Fever', 40);";

        return executeSQL(sql);
    }

    int updateData() {
        string sql = "UPDATE Patient SET BILL = 60 WHERE NAME = 'John Doe';";
        return executeSQL(sql);
    }

    int deleteData() {
        string sql = "DELETE FROM Patient;";
        return executeSQL(sql);
    }

    int selectData() {
        string sql = "SELECT * FROM Patient;";
        return executeSQL(sql);
    }
};

// Callback function for SELECT queries
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
    }
    cout << endl;
    return 0;
}

int main() {
    const char* dbPath = "../db/hospital.db";
    Database db(dbPath);

    db.createDB();
    db.createTable();
    db.deleteData();
    db.insertData();
    db.updateData();
    db.selectData();

    return 0;
}
