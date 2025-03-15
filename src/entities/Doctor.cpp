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
    Doctor(std::string name, std::string role)
        : name{ name }
        , role{ role }
    {}


    int getId() const {
        return id;
    }

    std::string getName() {
        return name;
    }    

    std::string getRole() {
        return role;
    }    

    void setId(int id) {
        this->id = id;
    }

    void setHospitalId(int hid) { hospitalId = hid; hospitalAdmitted = std::to_string(hid); }
    int getHospitalId() const { return hospitalId; }
    void addPatient(Patient* p) { patients.push_back(p); }
    std::vector<Patient*> getPatients() const { return patients; }

};

#endif