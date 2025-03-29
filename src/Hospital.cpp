#include <iostream>
#include <utility>
#include <vector>
#include "./entities/Patient.cpp"
#include "./entities/Doctor.cpp"
#include "./entities/Nurse.cpp"
#include "./database/Database.cpp"

// Hospital has-a Patients, Doctors and Nurses. Manage them too
class Hospital {
    private:
        int id;
        Database& db;  // Reference to the Database class

        static const int MAX_PATIENT_CAPACITY = 20;
        static const int MAX_DOCTOR_CAPACITY = 10;
        static const int MAX_NURSE_CAPACITY = 12;
    
    public:
        std::string name;
        std::vector<Patient*> patients;
        std::vector<Doctor*> doctors;
        std::vector<Nurse*> nurses;

        // Constructor
        Hospital(std::string name, Database& database)
            : name{ name }
            , db{ database }
        {}
    
        /* Rule of Five */
        // Copy Constructor
        Hospital(const Hospital& other)
            : id{ other.id }
            , name{ other.name }
            , db{ other.db }
        {
            for (Patient* p : other.patients) {
                patients.push_back(new Patient(*p));
            }

            for (Doctor* d : other.doctors) {
                doctors.push_back(new Doctor(*d));
            }

            for (Nurse* n : other.nurses) {
                nurses.push_back(new Nurse(*n));
            }
        }

        // Copy Assignment
        Hospital& operator=(const Hospital& other)
        {
            if (this != &other) {               // Handle self-assignment
                Hospital local{other};          // Copy Constructor
                std::swap(id, local.id);
                std::swap(name, local.name);
                std::swap(patients, local.patients);
                std::swap(doctors, local.doctors);
                std::swap(nurses, local.nurses);
            }
        
            return *this;
        }    

        // Move Constructor
        Hospital(Hospital&& other)
            : id{ std::exchange(other.id, 0) } // https://en.cppreference.com/w/cpp/language/move_constructor
            , name{ std::move(other.name) }
            , patients{ std::move(other.patients) } // this works for move but patients{ other.patients } doesnt for copy constructor
            , doctors{ std::move(other.doctors) }
            , nurses{ std::move(other.nurses) }
            , db{ other.db }
        {}

        // Move Assignment
        Hospital& operator=(Hospital&& other)
        {
            if (this != &other) {                           // Handle self-assignment
                Hospital local{std::move(other)};           // Move Constructor
                std::swap(id, local.id);
                std::swap(name, local.name);
                std::swap(patients, local.patients);
                std::swap(doctors, local.doctors);
                std::swap(nurses, local.nurses);
            }
            return *this;
        }   

        // Destructor
        ~Hospital() 
        {
            for (Patient* p : patients) delete p;
            patients.clear(); 
            for (Doctor* d : doctors) delete d;
            doctors.clear();
            for (Nurse* n : nurses) delete n;
            nurses.clear();
        }                                      
    
        /* Getter, Setter method for Hospital */
        // Getter methods
        int getId() const {
            return id;
        }

        std::string getName() {
            return name;
        }

        std::vector<Doctor*>& getDoctors() { return doctors; } 
        std::vector<Nurse*>& getNurses() { return nurses; }    

        // Setter methods
        void setId(int id) {
            this->id = id;
        }

        /* Methods for Hospital */
    /*Patients related methods*/
        // Add Patient to Hospital
        void admitPatient(Patient* p) {
            // check size of Patient Vector
            if (patients.size() < MAX_PATIENT_CAPACITY) {
                Patient* newPatient = new Patient(*p);
                patients.push_back(newPatient);
                std::string sql = "INSERT INTO Patient (name, disease, bill, status) VALUES ('"
                                  + newPatient->getName() + "', '"
                                  + newPatient->getDisease() + "', "
                                  + std::to_string(newPatient->getCostPerDay()) + ", "
                                  + std::to_string(static_cast<int>(newPatient->getStatus())) + ");"; 
                db.executeSQL(sql);
                newPatient->setId(db.getLastInsertedID());
                newPatient->setHospitalId(id);
                std::cout << "Patient: " << newPatient->getName() << " added to Hospital " << name << " (ID: " << newPatient->getId() << ")" << std::endl;
            }
            else {
                std::cout << "Maximum number of patient is 20. Please come back later even if you have life threatening disease.\n";
            }
        }

        // Discharge Patient from Hospital
        void dischargePatient(int patientID, int doctorID) {
            for (Doctor* d : doctors) {
                if (d->getId() == doctorID) {
                    for (auto patient = patients.begin(); patient != patients.end(); ++patient) {
                        if ((*patient)->getId() == patientID) {
                            std::cout << "Patient " << (*patient)->getName() << " discharged by Doctor " << d->getName() << std::endl;
                            std::string sql = "DELETE FROM Patient WHERE id = " + std::to_string(patientID) + ";";
                            db.executeSQL(sql);
                            delete *patient;
                            patients.erase(patient);
                            return;
                        }
                    }
                    std::cout << "Patient not found.\n";
                    return;
                }
            }
            std::cout << "Doctor not found or not authorized.\n";
        }

        // Change Patient admitted days by hand
        void updatePatientDays() {
            for (Patient* p : patients) {
                p->incrementDays();
                std::string sql = "UPDATE Patient SET daysInHospital = " + std::to_string(p->getDaysInHospital()) + 
                                  " WHERE id = " + std::to_string(p->getId()) + ";";
                db.executeSQL(sql);
            }
        }

        // Helper method to find a Patient by ID
        Patient* findPatientById(int patientID) {
            for (Patient* patient : patients) {
                if (patient->getId() == patientID) {
                    return patient;
                }
            }
            return nullptr;
        }

    /*Doctor related methods*/
        // Add Doctor to Hospital
        void assignDoctor(Doctor* d) {
            // check size of Doctors Vector
            if (doctors.size() < MAX_DOCTOR_CAPACITY) {
                Doctor* newDoctor = new Doctor(*d);
                doctors.push_back(newDoctor);
                std::string sql = "INSERT INTO Doctor (name, role) VALUES ('"
                                  + newDoctor->getName() + "', '"
                                  + newDoctor->getRole() + "');";
                db.executeSQL(sql);
                newDoctor->setId(db.getLastInsertedID());
                newDoctor->setHospitalId(id); 
                std::cout << "Doctor " << newDoctor->getName() << " assigned to Hospital " << name << " (ID: " << newDoctor->getId() << ")" << std::endl;
            }
            else {
                std::cout << "Maximum number of doctor is 10. We dont have enough money to hire more doktor.\n";
            }
        }

        // Remove Doctor from hospital using Doctor ID
        void removeDoctor(int doctorID) {
            for (auto doctor = doctors.begin(); doctor != doctors.end(); ++doctor) {
                // Content of the doctor iterator is a pointer to Doctor object
                if ((*doctor)->getId() == doctorID) {
                    std::cout << "Doctor " << (*doctor)->getName() << " is removed from Hospital " << name << std::endl;

                    // Database Delete query
                    std::string sql = "DELETE FROM Doctor WHERE id = " + std::to_string(doctorID) + ";";
                    db.executeSQL(sql);

                    // Delete it in memory and Vector
                    delete *doctor;
                    doctors.erase(doctor);

                    return;
                }
            }
            std::cout << "Doctor is not found. Please check the Doctor ID again.\n";
        }

        // Helper method to find a Doctor by ID
        Doctor* findDoctorById(int doctorID) {
            for (Doctor* doctor : doctors) {
                if (doctor->getId() == doctorID) {
                    return doctor;
                }
            }
            return nullptr;
        }

    /*Nurses related methods*/
        // Add nurse to Hospital
        void assignNurse(Nurse* n) {
            // check size of Doctors Vector
            if (nurses.size() < MAX_NURSE_CAPACITY) {
                Nurse* newNurse = new Nurse(*n);
                nurses.push_back(newNurse);
                std::string sql = "INSERT INTO Nurse (name) VALUES ('" + newNurse->getName() + "');";
                db.executeSQL(sql);
                newNurse->setId(db.getLastInsertedID());
                newNurse->setHospitalId(id); 
                std::cout << "Nurse " << newNurse->getName() << " assigned to Hospital " << name << " (ID: " << newNurse->getId() << ")" << std::endl;
            }
            else {
                std::cout << "Maximum number of nurse is 12. Please come back later even if you have life threatening disease.\n";
            }
        }

        // Remove Nurse from hospital using Nurse ID
        void removeNurse(int nurseID) {
            for (auto nurse = nurses.begin(); nurse != nurses.end(); ++nurse) {
                // Content of the Nurse iterator is a pointer to Nurse object
                if ((*nurse)->getId() == nurseID) {
                    std::cout << "Nurse " << (*nurse)->getName() << " is removed from Hospital " << name << std::endl;

                    // Database Delete query
                    std::string sql = "DELETE FROM Nurse WHERE id = " + std::to_string(nurseID) + ";";
                    db.executeSQL(sql);

                    // Delete it in memory and Vector
                    delete *nurse;
                    nurses.erase(nurse);

                    return;
                }
            }
            std::cout << "Nurse is not found. Please check the Nurse's ID again.\n";
        }

        // Helper method to find a Nurse by ID
        Nurse* findNurseById(int nurseID) {
            for (Nurse* nurse : nurses) {
                if (nurse->getId() == nurseID) {
                    return nurse;
                }
            }
            return nullptr;
        }

    /*Other methods here*/
    
        // Display the info of current Hospital
        void displayHospitalInfo() {
            std::cout << "Hospital id: " << id << std::endl;
            std::cout << "Hospital name: " << name << std::endl;
            std::cout << "Number of patients: " << patients.size() << std::endl;
            std::cout << "Number of doctors: " << doctors.size() << std::endl;
            std::cout << "Number of nurses: " << nurses.size() << std::endl;
        }

        /*Patient, Doctors and Nurse Relationship methods*/
        // Assign Doctor to Patients and Vice Versa in db
        void assignDoctorToPatient(int doctorID, int patientID, bool isPrimary) {
            // Check if doctor and patient exist
            Doctor* doctor = findDoctorById(doctorID);
            Patient* patient = findPatientById(patientID);

            if (!doctor) {
                std::cout << "Error: Doctor with ID " << doctorID << " not found.\n";
                return;
            }
            if (!patient) {
                std::cout << "Error: Patient with ID " << patientID << " not found.\n";
                return;
            }
            // Update patient and doctor objects
            patient->addDoctorToPatient(doctor);
            doctor->addPatientToDoctor(patient);

            // Execute the query
            std::string sql = "INSERT INTO Doctor_Patient (doctor_id, patient_id, is_primary) VALUES ("
                            + std::to_string(doctorID) + ", "
                            + std::to_string(patientID) + ", "
                            + std::to_string(isPrimary) + ");";
            db.executeSQL(sql);
        
            // Print some info
            std::cout << "Doctor ID " << doctorID << " assigned to Patient ID " << patientID;
            if (isPrimary) {
                std::cout << " as Primary Doctor";
            }
            std::cout << std::endl;
        }
};