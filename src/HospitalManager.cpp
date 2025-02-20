#include <vector>
#include "Hospital.cpp"

// Manage the Hospital class
class HospitalManager {
    private:
    std::vector<Hospital*> hospitals;
    Database& db;
    static const int MAX_HOSPITALS = 5;

    public:
    HospitalManager(Database& database) 
        : db(database) 
    {}

    // Add Hospital to Management System
    void addHospital(Hospital* h) {
        // check size of Hospital
        if (hospitals.size() < MAX_HOSPITALS) {
            // push to Hospital vector
            hospitals.push_back(new Hospital(*h));

            // Database Insert query
            std::string sql = "INSERT INTO Hospital (name) VALUES ('" + h->getName() + "');";
            db.executeSQL(sql);

            // Fetch last inserted ID (Does not work)
            h->setId(db.getLastInsertedID());
            std::cout << "Hospital created: " <<  h->getName() << " (ID: " << h->getId() << ")\n";
        }
        else {
            std::cout << "Maximum number of hospitals is " << MAX_HOSPITALS << ". Cannot add more hospitals.\n";
        }
    }

    // Remove a hospital based on Hospital ID
    void removeHospital(int hospitalID) {
        for (auto hospital = hospitals.begin(); hospital != hospitals.end(); ++hospital) {
            // Content of the patient iterator is a pointer to Patient object
            if ((*hospital)->getId() == hospitalID) {
                std::cout << "Hospital " << (*hospital)->getName() << " is removed" << std::endl;
                
                // Database Delete query
                std::string sql = "DELETE FROM Hospital WHERE id = " + std::to_string(hospitalID) + ";";
                db.executeSQL(sql);

                // Delete it in memory and Vector
                delete *hospital;
                hospitals.erase(hospital);

                return;
            }
        }
        std::cout << "Hospital is not found. Please check the Hospital ID again \n";        
    }

    // Display all hospitals
    void displayAllHospitals() {
        for (Hospital* h : hospitals) {
            h->displayHospitalInfo();
            std::cout << std::endl;
        }
    }

    // Destructor
    ~HospitalManager() {
        for (Hospital* h : hospitals) delete h;
        hospitals.clear();
    }
};
