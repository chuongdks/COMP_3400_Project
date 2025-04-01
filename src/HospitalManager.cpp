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
    {
        auto hospitalsData = db.getAllHospitals();
        for (const auto& [id, name] : hospitalsData) {
            Hospital* hospital = new Hospital(name, db);
            hospital->setId(id);
            hospitals.push_back(hospital);
        }
    }

    // Destructor
    ~HospitalManager() {
        for (Hospital* h : hospitals) delete h;
        hospitals.clear();
    }

    /* Getter, Setter method for Hospital Manager */
    // Getter for hospitals Vector
    std::vector<Hospital*>& getHospitals() {
        return hospitals;
    }

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
            // If Hospital id is found
            if (hospital->getId() == hospitalID) {
                // Use the Hospital's method admitPatient()
                hospital->admitPatient(patient);        

                // Execute the query
                std::string sql = "INSERT INTO Hospital_Patient (hospital_id, patient_id) VALUES ("
                                + std::to_string(hospitalID) + ", "
                                + std::to_string(patient->getId()) + ");";
                db.executeSQL(sql);

                return;
            }
        }
        std::cout << "Hospital with ID " << hospitalID << " not found.\n";
    }

    // Remove Patient from a Specific Hospital
    void dischargePatientFromHospital(int hospitalID, int patientID, int doctorID) {
        for (Hospital* hospital : hospitals) {
            // If Hospital id is found
            if (hospital->getId() == hospitalID) {
                // execute the code part
                hospital->dischargePatient(patientID, doctorID);

                // Execute the query
                std::string sql = "DELETE FROM Hospital_Patient WHERE hospital_id = "
                                + std::to_string(hospitalID) + " AND patient_id = "
                                + std::to_string(patientID) + ";";
                db.executeSQL(sql);

                return;
            }
        }
        std::cout << "Hospital with ID " << hospitalID << " not found.\n";
    }

/*Doctor related methods*/
    // Add Doctor to a Specific Hospital
    void assignDoctorToHospital(int hospitalID, Doctor* doctor) {
        for (Hospital* hospital : hospitals) {
            // If Hospital id is found
            if (hospital->getId() == hospitalID) {
                // Use the Hospital's method assignDoctor()
                hospital->assignDoctor(doctor);       
                
                // Execute the query
                std::string sql = "INSERT INTO Hospital_Doctor (hospital_id, doctor_id) VALUES ("
                                + std::to_string(hospitalID) + ", "
                                + std::to_string(doctor->getId()) + ");";
                db.executeSQL(sql);

                return;
            }
        }
        std::cout << "Hospital with ID " << hospitalID << " not found.\n";
    }

    // Remove a Doctor from a specific hospital
    void removeDoctorFromHospital(int hospitalID, int doctorID) {
        for (Hospital* hospital : hospitals) {
            // If Hospital id is found
            if (hospital->getId() == hospitalID) {
                // Use the Hospital's method removeDoctor()
                hospital->removeDoctor(doctorID);      

                // Execute the query
                std::string sql = "DELETE FROM Hospital_Doctor WHERE hospital_id = "
                                + std::to_string(hospitalID) + " AND doctor_id = "
                                + std::to_string(doctorID) + ";";
                db.executeSQL(sql);

                return;
            }
        }
        std::cout << "Hospital with ID " << hospitalID << " not found.\n";
    }

/*Nurse related methods*/
    // Add Nurse to a Specific Hospital
    void assignNurseToHospital(int hospitalID, Nurse* nurse) {
        for (Hospital* hospital : hospitals) {
            // If Hospital id is found
            if (hospital->getId() == hospitalID) {
                // Use the Hospital's method assignNurse()
                hospital->assignNurse(nurse);        
                
                // Execute the query
                std::string sql = "INSERT INTO Hospital_Nurse (hospital_id, nurse_id) VALUES ("
                                + std::to_string(hospitalID) + ", "
                                + std::to_string(nurse->getId()) + ");";
                db.executeSQL(sql);

                return;
            }
        }
        std::cout << "Hospital with ID " << hospitalID << " not found.\n";
    }

    // Remove a Nurse from a specific hospital
    void removeNurseFromHospital(int hospitalID, int nurseID) {
        for (Hospital* hospital : hospitals) {
            // If Hospital id is found
            if (hospital->getId() == hospitalID) {
                // Use the Hospital's method removeNurse()
                hospital->removeNurse(nurseID);  

                std::string sql = "DELETE FROM Hospital_Nurse WHERE hospital_id = "
                                + std::to_string(hospitalID) + " AND nurse_id = "
                                + std::to_string(nurseID) + ";";
                db.executeSQL(sql);
                return;
            }
        }
        std::cout << "Hospital with ID " << hospitalID << " not found.\n";
    }
    
/* Doctors-Patients Relationshiop */
    // Assign Doctor to Patients
    void assignDoctorToPatient(int hospitalId, int doctorId, int patientId, bool isPrimary) {
        // Find the hospital
        Hospital* hospital = getHospitalById(hospitalId);
        if (!hospital) {
            cout << "Error: Hospital not found.\n";
            return;
        }
    
        // Find the doctor
        Doctor* doctor = hospital->findDoctorById(doctorId);
        if (!doctor) {
            cout << "Error: Doctor not found in hospital.\n";
            return;
        }
    
        // Find the patient
        Patient* patient = hospital->findPatientById(patientId);
        if (!patient) {
            cout << "Error: Patient not found in hospital.\n";
            return;
        }
    
        // Assign doctor to patient
        hospital->assignDoctorToPatient_Hospital(doctorId, patientId, isPrimary);
        cout << "Doctor assigned to patient successfully.\n";
    }

    // Assign Nurse to Patients
    void assignNurseToPatient(int hospitalId, int nurseId, int patientId) {
        // Find the hospital
        Hospital* hospital = getHospitalById(hospitalId);
        if (!hospital) {
            cout << "Error: Hospital not found.\n";
            return;
        }
    
        // Find the nurse
        Nurse* nurse = hospital->findNurseById(nurseId);
        if (!nurse) {
            std::cout << "Error: Nurse with ID " << nurseId << " not found.\n";
            return;
        }
    
        // Find the patient
        Patient* patient = hospital->findPatientById(patientId);
        if (!patient) {
            cout << "Error: Patient not found in hospital.\n";
            return;
        }
    
        // Assign doctor to patient
        hospital->assignNurseToPatient_Hospital(nurseId, patientId);
        cout << "Nurse assigned to patient successfully.\n";
    }
    
/*Display method*/
    // Display all hospitals
    void displayAllHospitals() {
        for (Hospital* h : hospitals) {
            h->displayHospitalInfo();
            std::cout << std::endl;
        }
    }

    void displayAllPatients() {
        std::cout << "\nAll Patients:\n";
        bool found = false;
        for (Hospital* hospital : hospitals) {
            for (Patient* patient : hospital->patients) { 
                std::cout << "Hospital ID: " << hospital->getId() 
                          << ", Doctor ID: " << patient->getId() 
                          << ", Name: " << patient->getName() << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "No patient is found.\n";
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
            std::cout << "No doctor is found.\n";
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
            std::cout << "No nurse is found.\n";
        }
    }
};
