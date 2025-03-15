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
    Nurse(std::string name)
        : name{ name }
    {}

    int getId() const {
        return id;
    }

    std::string getName() {
        return name;
    }    

    void setId(int id) {
        this->id = id;
    }

    void setHospitalId(int hid) { hospitalId = hid; hospitalAdmitted = std::to_string(hid); }
    int getHospitalId() const { return hospitalId; }
    bool addPatient(Patient* p) {
        if (patients.size() < 2) {
            patients.push_back(p);
            return true;
        }
        return false;
    }
    std::vector<Patient*> getPatients() const { return patients; }
};

#endif