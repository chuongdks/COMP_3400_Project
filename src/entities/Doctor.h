#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <vector>

class Patient; // Forward declaration

class Doctor {
private:
    int id;
    std::string name;
    std::string role;
    int hospitalId;
    std::vector<Patient*> patients;

public:
    Doctor(std::string name, std::string role);

    // Getter methods
    int getId() const;
    std::string getName() const;
    std::string getRole() const;
    int getHospitalId() const;
    std::vector<Patient*> getPatients() const;

    // Setter methods
    void setId(int id);
    void setHospitalId(int hid);

    // Other methods
    void addPatientToDoctor(Patient* patient);
    void displayPatients();
};

#endif
