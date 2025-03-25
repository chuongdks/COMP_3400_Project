#ifndef DOCTOR_CPP
#define DOCTOR_CPP
#include <iostream>
#include <vector>

class Patient;

// Doctor also has-a Patient. 
class Doctor {
    private:
    int id;
    std::string name;
    std::string role;
    std::string hospitalAdmitted;
    int hospitalId; 
    std::vector<Patient*> patients; 

    public: 
    // Constructor
    Doctor(std::string name, std::string role)
        : name{ name }
        , role{ role }
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
    // add patients for Doctor
    void addPatient(Patient* p) { patients.push_back(p); }
    

};

#endif