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

            for (Nurse* n : other:nurses) {
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
            for (Doctor* d : doctors) delete d;
            for (Nurse* n : nurses) delete n;
        }                                      
    
        // void admitPatient(Patient* p);
        // void dischargePatient(int patientID);
        // void assignDoctor(Doctor* d);
        // void assignNurse(Nurse* n);
        // void displayHospitalInfo();
};