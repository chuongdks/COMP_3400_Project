#ifndef NURSE_H
#define NURSE_H

#include <iostream>
#include <vector>

class Patient; // Forward declaration

class Nurse {
private:
    int id;
    std::string name;
    std::string hospitalAdmitted;
    int hospitalId; 
    std::vector<Patient*> patients; 

public:
    // Constructor
    Nurse(std::string name);

    // Getter methods
    int getId() const;
    std::string getName() const;
    int getHospitalId() const;
    std::vector<Patient*> getPatients() const;

    // Setter methods
    void setId(int id);
    void setHospitalId(int hid);
    
    /* Other methods */ 
    // add patients to nurse
    void addPatientToNurse(Patient* patient);

    // Display patients treated by this nurse
    void displayPatients();
};

#endif