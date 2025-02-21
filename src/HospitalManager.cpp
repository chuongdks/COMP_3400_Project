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

    // Destructor
    ~HospitalManager() {
        for (Hospital* h : hospitals) delete h;
        hospitals.clear();
    }

    /* Getter, Setter method for Hospital Manager */


    /* Hospital Manager methods */
    // Add Hospital to Management System
    void addHospital(std::string hospitalName) {
        // check size of Hospital
        if (hospitals.size() < MAX_HOSPITALS) {
            // push to Hospital vector
            Hospital* newHospital = new Hospital(hospitalName, db);
            hospitals.push_back(newHospital);

            // Database Insert query
            std::string sql = "INSERT INTO Hospital (name) VALUES ('" + newHospital->getName() + "');";
            db.executeSQL(sql);

            // Fetch last inserted ID
            newHospital->setId(db.getLastInsertedID());
            std::cout << "Hospital created: " <<  newHospital->getName() << " (ID: " << newHospital->getId() << ")\n";
        }
        else {
            std::cout << "Maximum number of hospitals is " << MAX_HOSPITALS << ". Cannot add more hospitals.\n";
        }
    }

    // // Add Hospital to Management System (Overload method, argunment is pointer to Hospital. Need Fix)
    // void addHospital(Hospital* h) {
    //     // check size of Hospital
    //     if (hospitals.size() < MAX_HOSPITALS) {
    //         // push to Hospital vector
    //         hospitals.push_back(new Hospital(*h, db));

    //         // Database Insert query
    //         std::string sql = "INSERT INTO Hospital (name) VALUES ('" + h->getName() + "');";
    //         db.executeSQL(sql);

    //         // Fetch last inserted ID (Does not work)
    //         h->setId(db.getLastInsertedID());
    //         std::cout << "Hospital created: " <<  h->getName() << " (ID: " << h->getId() << ")\n";
    //     }
    //     else {
    //         std::cout << "Maximum number of hospitals is " << MAX_HOSPITALS << ". Cannot add more hospitals.\n";
    //     }
    // }

    // Remove a hospital based on Hospital ID
    void removeHospital(int hospitalID) {
        for (auto hospital = hospitals.begin(); hospital != hospitals.end(); ++hospital) {
            // Content of the patient iterator is a pointer to Hospital object
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

    // Return Hospital pointer by Hospital ID
    Hospital* getHospitalById(int hospitalID) {
        for (Hospital* hospital : hospitals) {
            if (hospital->getId() == hospitalID) {
                return hospital;
            }
        }
        std::cout << "Hospital is not found. Please check the Hospital ID again \n";      
        return nullptr;
    }

    // Add Patient to a Specific Hospital
    void admitPatientToHospital(int hospitalID, Patient* patient) {
        for (Hospital* hospital : hospitals) {
            if (hospital->getId() == hospitalID) {
                hospital->admitPatient(patient);        // Use the Hospital's method admitPatient()
                return;
            }
        }
        std::cout << "Hospital with ID " << hospitalID << " not found.\n";
    }

    // Remove a patient from a specific hospital
    void dischargePatientFromHospital(int hospitalID, int patientID) {
        for (Hospital* hospital : hospitals) {
            if (hospital->getId() == hospitalID) {
                hospital->dischargePatient(patientID);  // Use the Hospital's method dischargePatient()
                return;
            }
        }
        std::cout << "Hospital with ID " << hospitalID << " not found.\n";
    }

    // Display all hospitals
    void displayAllHospitals() {
        for (Hospital* h : hospitals) {
            h->displayHospitalInfo();
            std::cout << std::endl;
        }
    }
};
