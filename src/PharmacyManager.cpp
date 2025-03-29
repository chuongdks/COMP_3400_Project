#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include "./entities/Pharmacy.cpp"
#include "./database/Database.cpp"

class PharmacyManager {
private:
    std::vector<Pharmacy*> pharmacies;
    Database& db;  // Reference to the Database class

public:
    // Constructor
    PharmacyManager(Database& database)
        : db{ database }
    {
        // Load existing pharmacies from the database
        loadPharmaciesFromDB();
    }

    // Destructor
    ~PharmacyManager() {
        for (Pharmacy* p : pharmacies) delete p;
        pharmacies.clear();
    }

    // Load all pharmacies from the database
    void loadPharmaciesFromDB() {
        std::string sql = "SELECT id, name FROM Pharmacy;";
        sqlite3_stmt* stmt;
        sqlite3* dbPtr = db.getDbPointer();

        if (sqlite3_prepare_v2(dbPtr, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                int id = sqlite3_column_int(stmt, 0);
                const unsigned char* name = sqlite3_column_text(stmt, 1);
                std::string pharmName = name ? reinterpret_cast<const char*>(name) : "";
                
                Pharmacy* pharmacy = new Pharmacy(id, pharmName);
                pharmacies.push_back(pharmacy);
            }
        } else {
            std::cerr << "Error loading pharmacies: " << sqlite3_errmsg(dbPtr) << std::endl;
        }
        sqlite3_finalize(stmt);
    }

    // Add a new pharmacy
    int addPharmacy(std::string name, std::string address = "", std::string contactNumber = "") {
        std::string sql = "INSERT INTO Pharmacy (name) VALUES ('" + name + "');";
        
        if (db.executeSQL(sql) == SQLITE_OK) {
            int id = db.getLastInsertedID();
            Pharmacy* pharmacy = new Pharmacy(id, name, address, contactNumber);
            pharmacies.push_back(pharmacy);
            std::cout << "Pharmacy added with ID: " << id << std::endl;
            return id;
        } else {
            std::cerr << "Failed to add pharmacy" << std::endl;
            return -1;
        }
    }

    // Remove a pharmacy by ID
    bool removePharmacy(int id) {
        std::string sql = "DELETE FROM Pharmacy WHERE id = " + std::to_string(id) + ";";
        
        if (db.executeSQL(sql) == SQLITE_OK) {
            // Remove from our local list
            for (auto it = pharmacies.begin(); it != pharmacies.end(); ++it) {
                if ((*it)->getId() == id) {
                    delete *it;
                    pharmacies.erase(it);
                    std::cout << "Pharmacy removed with ID: " << id << std::endl;
                    return true;
                }
            }
        }
        std::cout << "Failed to remove pharmacy with ID: " << id << std::endl;
        return false;
    }

    // Get pharmacy by ID
    Pharmacy* getPharmacyById(int id) {
        for (Pharmacy* p : pharmacies) {
            if (p->getId() == id) {
                return p;
            }
        }
        return nullptr;
    }

    // Get all pharmacies
    std::vector<Pharmacy*>& getPharmacies() {
        return pharmacies;
    }

    // Display all pharmacies
    void displayAllPharmacies() {
        if (pharmacies.empty()) {
            std::cout << "No pharmacies found." << std::endl;
            return;
        }

        std::cout << "\n== All Pharmacies ==" << std::endl;
        for (Pharmacy* p : pharmacies) {
            std::cout << "ID: " << p->getId() 
                      << ", Name: " << p->getName() 
                      << ", Address: " << p->getAddress() 
                      << ", Contact: " << p->getContactNumber() << std::endl;
        }
    }

    // Process medicine delivery from a pharmacy to a hospital
    bool deliverMedicine(int pharmacyId, int hospitalId, std::string medicine, double cost) {
        Pharmacy* pharmacy = getPharmacyById(pharmacyId);
        if (!pharmacy) {
            std::cout << "Pharmacy not found with ID: " << pharmacyId << std::endl;
            return false;
        }

        pharmacy->deliverMedicine(hospitalId, medicine, cost);
        return true;
    }

    // Get total bill for a hospital from a specific pharmacy
    double getHospitalBill(int pharmacyId, int hospitalId) {
        Pharmacy* pharmacy = getPharmacyById(pharmacyId);
        if (!pharmacy) {
            std::cout << "Pharmacy not found with ID: " << pharmacyId << std::endl;
            return 0.0;
        }

        return pharmacy->getHospitalBill(hospitalId);
    }

    // Clear bill for a hospital from a specific pharmacy
    bool clearHospitalBill(int pharmacyId, int hospitalId) {
        Pharmacy* pharmacy = getPharmacyById(pharmacyId);
        if (!pharmacy) {
            std::cout << "Pharmacy not found with ID: " << pharmacyId << std::endl;
            return false;
        }

        pharmacy->clearHospitalBill(hospitalId);
        return true;
    }
}; 