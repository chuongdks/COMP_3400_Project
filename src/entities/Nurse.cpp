#include "Nurse.h"
#include "Patient.h"

// Constructor
Nurse::Nurse(std::string name)
    : name{ name }
{}

// Getter methods
int Nurse::getId() const { return id; }
std::string Nurse::getName() const { return name; }    
int Nurse::getHospitalId() const { return hospitalId; }
std::vector<Patient*> Nurse::getPatients() const { return patients; }

// Setter methods
void Nurse::setId(int id) { this->id = id; }
void Nurse::setHospitalId(int hid) { hospitalId = hid; hospitalAdmitted = std::to_string(hid); }

/* Other methods */ 
// add patients to nurse
void Nurse::addPatientToNurse(Patient* patient) { 
    if (patients.size() < 2) {
        patients.push_back(patient); 
    }
}

// Display patients treated by this nurse
void Nurse::displayPatients() {
    std::cout << "Doctor: " << this->name << " is treating:\n";
    for (auto patient : patients) {
        std::cout << "- " << patient->getName() << "\n";
    }
}
