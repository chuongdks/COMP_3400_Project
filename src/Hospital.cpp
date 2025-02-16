#include <iostream>
#include <utility>
#include <vector>
#include "Patient.cpp"
#include "Doctor.cpp"
#include "Nurse.cpp"

// Hospital has-a Patients, Doctors and Nurses
class Hospital {
    private:
        int id;
        std::string name;
        std::vector<Patient*> patients;
        std::vector<Doctor*> doctors;
        std::vector<Nurse*> nurses;
        static const int MAX_CAPACITY = 20;
    
    public:
        // Constructor
        Hospital(int id, std::string name)
            : id{ id }, name{ name }
        {}
    
        /* Rule of Five */
        // Copy Constructor
        Hospital(const Hospital& other)
            : id{ other.id }
            , name{ other.name }
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
            if (this == &other) return *this;  // Handle self-assignment

            // Step 1: Free old dynamically allocated memory
            for (Patient* p : patients) delete p;
            for (Doctor* d : doctors) delete d;
            for (Nurse* n : nurses) delete n;
        
            // Step 2: Clear the vectors to avoid dangling pointers
            patients.clear();
            doctors.clear();
            nurses.clear();
        
            // Step 3: Copy new data
            id = other.id;
            name = other.name;
        
            for (Patient* p : other.patients) {
                patients.push_back(new Patient(*p)); // Deep copy
            }
            for (Doctor* d : other.doctors) {
                doctors.push_back(new Doctor(*d));
            }
            for (Nurse* n : other.nurses) {
                nurses.push_back(new Nurse(*n));
            }
        
            return *this;
        }    

        // Move Constructor
        Hospital(Hospital&& other)
            : id{ std::exchange(other.id, 0) } // https://en.cppreference.com/w/cpp/language/move_constructor
            , name{ std::move(other.name) }
            , patients{ std::move(other.patients) }
            , doctors{ std::move(other.doctors) }
            , nurses{ std::move(other.nurses) }
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
    
        /*Methods for Hospital*/
        // Add Patient to Hospital
        void admitPatient(Patient* p) {
            // check size of Patient Vector
            if (patients.size() < MAX_CAPACITY) {   
                // patients.push_back(p);
                patients.push_back(new Patient(*p));
                std::cout << "Patient: " << p->getName() << " added to Hospital " << name << std::endl;
            }
            else {
                std::cout << "Maximum number of patient is 20. Please come back later even if you have life threatening disease. \n";
            }
        }

        // Remove patient from hospital using patient ID
        void dischargePatient(int patientID) {
            for (auto patient = patients.begin(); patient != patients.end(); ++patient) {
                if ((*patient)->getId() == patientID) {
                    std::cout << "Patient " << (*patient)->getName() << " is dischared from Hospital " << name << std::endl;
                    patients.erase(patient);
                    return;
                }
            }
            std::cout << "Patient is not found. Please check the Patient ID again \n";
        }

        // Add Doctor to Hospital
        void assignDoctor(Doctor* d) {
            doctors.push_back(new Doctor(*d));       // Hospital can add lots of doctors. Might change this
        }

        // Remove Doctor from hospital using Doctor ID

        // Add nurse to Hospital
        void assignNurse(Nurse* n) {
            nurses.push_back(new Nurse(*n));       // Hospital can add lots of nurses. Might change this
        }

        // Remove Nurse from hospital using Nurse ID

        // Display the info of current Hospital
        void displayHospitalInfo() {
            std::cout << "Hospital name: " << name << std::endl;
            std::cout << "Number of patients: " << patients.size() << std::endl;
            std::cout << "Number of doctors: " << doctors.size() << std::endl;
            std::cout << "Number of nurses: " << nurses.size() << std::endl;
        }
};