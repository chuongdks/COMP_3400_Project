#include <vector>
#include "Hospital.cpp"

// Manage the Hospital class
class HospitalManager {
    private:
    Database& db;
    static const int MAX_HOSPITALS = 5;

    public:
    std::vector<Hospital*> hospitals;
    // Constructor, program read data from hospital.db to fill the vector first
    HospitalManager(Database& database) 
        : db(database) 
    {auto hospitalsData = db.getAllHospitals();
        for (const auto& [id, name] : hospitalsData) {
            Hospital* hospital = new Hospital(name, db);
            hospital->setId(id);
            hospitals.push_back(hospital);
        }}

    // Destructor
    ~HospitalManager() {
        for (Hospital* h : hospitals) delete h;
        hospitals.clear();
    }

    /* Getter, Setter method for Hospital Manager */


    /* 
        Hospital Manager methods 
    */
/*Hospital related methods*/
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
            std::cout << "Maximum number of hospitals is " << MAX_HOSPITALS << ".\n";
        }
    }

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
        std::cout << "Hospital is not found.\n";        
    }

    // Return Hospital pointer by Hospital ID
    Hospital* getHospitalById(int hospitalID) {
        for (Hospital* hospital : hospitals) {
            if (hospital->getId() == hospitalID) {
                return hospital;
            }
        }
        std::cout << "Hospital is not found. \n";      
        return nullptr;
    }

/*Patient related methods*/
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

    void dischargePatientFromHospital(int hospitalID, int patientID, int doctorID) {
        for (Hospital* hospital : hospitals) {
            if (hospital->getId() == hospitalID) {
                hospital->dischargePatient(patientID, doctorID);
                return;
            }
        }
        std::cout << "Hospital with ID " << hospitalID << " not found.\n";
    }

/*Doctor related methods*/
    // Add Doctor to a Specific Hospital
    void assignDoctorToHospital(int hospitalID, Doctor* doctor) {
        for (Hospital* hospital : hospitals) {
            if (hospital->getId() == hospitalID) {
                hospital->assignDoctor(doctor);        // Use the Hospital's method assignDoctor()
                return;
            }
        }
        std::cout << "Hospital with ID " << hospitalID << " not found.\n";
    }

    // Remove a Doctor from a specific hospital
    void removeDoctorFromHospital(int hospitalID, int doctorID) {
        for (Hospital* hospital : hospitals) {
            if (hospital->getId() == hospitalID) {
                hospital->removeDoctor(doctorID);      // Use the Hospital's method removeDoctor()
                return;
            }
        }
        std::cout << "Hospital with ID " << hospitalID << " not found.\n";
    }

/*Nurse related methods*/
    // Add Nurse to a Specific Hospital
    void assignNurseToHospital(int hospitalID, Nurse* nurse) {
        for (Hospital* hospital : hospitals) {
            if (hospital->getId() == hospitalID) {
                hospital->assignNurse(nurse);           // Use the Hospital's method assignNurse()
                return;
            }
        }
        std::cout << "Hospital with ID " << hospitalID << " not found.\n";
    }

    // Remove a Nurse from a specific hospital
    void removeNurseFromHospital(int hospitalID, int nurseID) {
        for (Hospital* hospital : hospitals) {
            if (hospital->getId() == hospitalID) {
                hospital->removeNurse(nurseID);  // Use the Hospital's method removeNurse()
                return;
            }
        }
        std::cout << "Hospital with ID " << hospitalID << " not found.\n";
    }
    
    std::vector<Hospital*>& getHospitals() {
        return hospitals;
    }

/*Display method*/
    // Display all hospitals
    void displayAllHospitals() {
        for (Hospital* h : hospitals) {
            h->displayHospitalInfo();
            std::cout << std::endl;
        }
    }
    void displayAllDoctors() {
        std::cout << "\nAll Doctors:\n";
        bool found = false;
        for (Hospital* hospital : hospitals) {
            for (Doctor* doctor : hospital->doctors) { 
                std::cout << "Hospital ID: " << hospital->getId() 
                          << ", Doctor ID: " << doctor->getId() 
                          << ", Name: " << doctor->getName() 
                          << ", Role: " << doctor->getRole() << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "No doctors found.\n";
        }
    }

    void displayAllNurses() {
        std::cout << "\nAll Nurses:\n";
        bool found = false;
        for (Hospital* hospital : hospitals) {
            for (Nurse* nurse : hospital->nurses) { 
                std::cout << "Hospital ID: " << hospital->getId() 
                          << ", Nurse ID: " << nurse->getId() 
                          << ", Name: " << nurse->getName() << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "No nurses found.\n";
        }
    }
};
