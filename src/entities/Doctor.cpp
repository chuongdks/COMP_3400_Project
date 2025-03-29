#ifndef DOCTOR_CPP
#define DOCTOR_CPP
#include <iostream>
#include <vector>
#include "../database/Database.cpp"
#include "./Patient.cpp"

class Patient;

// Doctor also has-a Patient. 
class Doctor {
    private:
    int id;
    std::string name;
    std::string role;
    std::string hospitalAdmitted;
    int hospitalId; 

    std::vector<Patient*> patients; // Doctor take cares of many patients
    Database& db; 

    public: 
    // Constructor
    Doctor(std::string name, std::string role, Database& database)
        : name{ name }
        , role{ role }
        , db{ database }
    {}

    // Getter methods
    int getId() const { return id; }
    std::string getName() { return name; }    
    std::string getRole() { return role; }    
    int getHospitalId() const { return hospitalId; }
    std::vector<Patient*> getPatients() const { return patients; }

    // Setter methods
    void setId(int id) { this->id = id; }
    void setHospitalId(int hid) { hospitalId = hid; hospitalAdmitted = std::to_string(hid); }
    
    /* Other methods */
    // add patients to Doctor
    void addPatientToDoctor(Patient* patient, bool isPrimary) { 
        patients.push_back(patient); 
    }

    // Display patients treated by this doctor
    void displayPatients() {
        std::cout << "Doctor: " << this->name << " is treating: \n";
        for (auto patient : patients) {
            std::cout << "- " << patient->getName() << "\n";
        }
    }
    
};

#endif