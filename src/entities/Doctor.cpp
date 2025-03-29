#include "Doctor.h"
#include "Patient.h"

// Default Constructor
Doctor::Doctor(std::string name, std::string role)
    : name{ name }
    , role{ role }
{}

// Getter methods
int Doctor::getId() const { return id; }
std::string Doctor::getName() const { return name; }    
std::string Doctor::getRole() const { return role; }    
int Doctor::getHospitalId() const { return hospitalId; }
std::vector<Patient*> Doctor::getPatients() const { return patients; }

// Setter methods
void Doctor::setId(int id) { this->id = id; }
void Doctor::setHospitalId(int hid) { hospitalId = hid;}
    
/* Other methods */
// add patients to Doctor
void Doctor::addPatientToDoctor(Patient* patient) { 
    patients.push_back(patient); 
}

// Display patients treated by this doctor
void Doctor::displayPatients() {
    std::cout << "Doctor: " << this->name << " is treating:\n";
    for (auto patient : patients) {
        std::cout << "- " << patient->getName() << "\n";
    }
}