#ifndef NURSE_CPP
#define NURSE_CPP
#include <iostream>
#include <vector>

class Patient;

class Nurse {
    private:
    int id;
    std::string name;
    std::string hospitalAdmitted;
    int hospitalId; 
    
    std::vector<Patient*> patients; 

    public:
    // Constructor
    Nurse(std::string name)
        : name{ name }
    {}

    // Getter methods
    int getId() const { return id; }
    std::string getName() { return name; }    
    int getHospitalId() const { return hospitalId; }
    std::vector<Patient*> getPatients() const { return patients; }

    // Setter methods
    void setId(int id) { this->id = id; }
    void setHospitalId(int hid) { hospitalId = hid; hospitalAdmitted = std::to_string(hid); }
    
    /* Other methods */ 
    // Add patient for a Nurse
    bool addPatient(Patient* p) {
        if (patients.size() < 2) {
            patients.push_back(p);
            return true;
        }
        return false;
    }
    
};

#endif