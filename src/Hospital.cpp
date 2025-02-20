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
        std::string name;
        std::vector<Patient*> patients;
        std::vector<Doctor*> doctors;
        std::vector<Nurse*> nurses;
        Database& db;  // Reference to the Database class

        static const int MAX_PATIENT_CAPACITY = 20;
        static const int MAX_DOCTOR_CAPACITY = 10;
        static const int MAX_NURSE_CAPACITY = 12;
    
    public:
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

        // Setter methods
        void setId(int id) {
            this->id = id;
        }

        /* Methods for Hospital */
        // Add Patient to Hospital
        void admitPatient(Patient* p) {
            // check size of Patient Vector
            if (patients.size() < 5) {   
                // Push to Vector
                patients.push_back(new Patient(*p));

                // Database Insert query
                std::string sql = "INSERT INTO Patient (name, disease, bill) VALUES ('"
                                    + p->getName() + "', '"
                                    + p->getDisease()+"', "
                                    + std::to_string(p->getCostPerDay()) + ");"; // (1, 'John Foo', 'Flu', 50)
                db.executeSQL(sql);

                std::cout << "Patient: " << p->getName() << " added to Hospital " << name << std::endl;
            }
            else {
                std::cout << "Maximum number of patient is 20. Please come back later even if you have life threatening disease.\n";
            }
        }

        // Remove patient from hospital using patient ID
        void dischargePatient(int patientID) {
            for (auto patient = patients.begin(); patient != patients.end(); ++patient) {
                // Content of the patient iterator is a pointer to Patient object
                if ((*patient)->getId() == patientID) {
                    std::cout << "Patient " << (*patient)->getName() << " is dischared from Hospital " << name << std::endl;
                    
                    // Database Delete query
                    std::string sql = "DELETE FROM Patient WHERE id = " + std::to_string(patientID) + ";";
                    db.executeSQL(sql);

                    // Delete it in memory and Vector
                    delete *patient;
                    patients.erase(patient);

                    return;
                }
            }
            std::cout << "Patient is not found. Please check the Patient ID again \n";
        }

        // Add Doctor to Hospital
        void assignDoctor(Doctor* d) {
            // check size of Doctors Vector
            if (doctors.size() < 5) {   
                // Push to Vector
                doctors.push_back(new Doctor(*d));       // Hospital can add lots of doctors. Might change this

                // Database Insert query
                std::string sql = "INSERT INTO Doctor (name, role) VALUES ('" 
                                    + d->getName() + "', '" 
                                    + d->getRole() + "');";
                db.executeSQL(sql);

                std::cout << "Doctor " << d->getName() << " assigned to Hospital " << name << std::endl;
            }
            else {
                std::cout << "Maximum number of doctor is 10. Please come back later even if you have life threatening disease.\n";
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
            std::cout << "Doctor is not found. Please check the Patient ID again.\n";
        }

        // Add nurse to Hospital
        void assignNurse(Nurse* n) {
            // check size of Doctors Vector
            if (nurses.size() < 5) {   
                // Push to Vector
                nurses.push_back(new Nurse(*n));       // Hospital can add lots of nurses. Might change this

                // Database Insert query
                std::string sql = "INSERT INTO Nurse (name) VALUES ('" + n->getName() + "');";
                db.executeSQL(sql);

                std::cout << "Nurse " << n->getName() << " assigned to Hospital " << name << std::endl;
            }
            else {
                std::cout << "Maximum number of nurse is 12. Please come back later even if you have life threatening disease.\n";
            }
        }

        // Remove Nurse from hospital using Nurse ID
        void removeNurse(int nurseID) {
            for (auto nurse = nurses.begin(); nurse != nurses.end(); ++nurse) {
                // Content of the nurse iterator is a pointer to Doctor object
                if ((*nurse)->getId() == nurseID) {
                    std::cout << "Doctor " << (*nurse)->getName() << " is removed from Hospital " << name << std::endl;

                    // Database Delete query
                    std::string sql = "DELETE FROM Doctor WHERE id = " + std::to_string(nurseID) + ";";
                    db.executeSQL(sql);

                    // Delete it in memory and Vector
                    delete *nurse;
                    nurses.erase(nurse);
                    return;
                }
            }
            std::cout << "Nurse is not found. Please check the Nurse's ID again.\n";
        }

        // Display the info of current Hospital
        void displayHospitalInfo() {
            std::cout << "Hospital id: " << id << std::endl;
            std::cout << "Hospital name: " << name << std::endl;
            std::cout << "Number of patients: " << patients.size() << std::endl;
            std::cout << "Number of doctors: " << doctors.size() << std::endl;
            std::cout << "Number of nurses: " << nurses.size() << std::endl;
        }
};