#include "Patient.h"
#include "Doctor.h"
#include "Nurse.h"

// Default constructor
Patient::Patient(std::string name, std::string disease, int costPerDay)
    : name{ name }
    , disease{ disease }
    , costPerDay{ costPerDay }
    , daysInHospital{0}
{}
    
// Getter methods
int Patient::getId() const { return id; }
std::string Patient::getName() const{  return name; }
std::string Patient::getDisease() const { return disease; }
int Patient::getCostPerDay() const { return costPerDay; }
int Patient::getDaysInHospital() const { return daysInHospital; }
int Patient::getBill() const { return daysInHospital * costPerDay; }
int Patient::getHospitalId() const { return hospitalId; }
std::vector<Doctor*> Patient::getDoctors() const { return doctors; }
std::vector<Nurse*> Patient::getNurses() const { return nurses; }
Patient::Status Patient::getStatus() const { return status; }

// Setter methods
void Patient::setId(int id) { this->id = id; }
void Patient::setDaysInHospital(int days) { this->daysInHospital = days; }
void Patient::setHospitalId(int hid) { hospitalId = hid; hospitalAdmitted = std::to_string(hid); }
void Patient::setStatus(Status s) { status = s; }
void Patient::incrementDays() { daysInHospital++; }

/* Other methods */
// Assign a primary doctor
void Patient::setPrimaryDoctor(Doctor* doctor) {
    primaryDoctor = doctor;
}

// Add doctors to Patient
void Patient::addDoctorToPatient(Doctor* doctor) {
    doctors.push_back(doctor);
}

// Display all doctors treating this patient
void Patient::displayDoctors() {
    std::cout << "Patient: " << this->name << " is being treated by:\n";
    if (primaryDoctor) {
        std::cout << "- Primary Doctor: " << primaryDoctor->getName() << "\n";
    }
    for (auto doctor : doctors) {
        if (doctor != primaryDoctor) {
            std::cout << "- " << doctor->getName() << "\n";
        }
    }
}

// Add nurses to Patient
void Patient::addNurseToPatient(Nurse* nurse) {
    nurses.push_back(nurse);
}

// Display all nurses treating this patient
void Patient::displayNurses() {
    std::cout << "Patient: " << this->name << " is being treated by:\n";
    for (auto nurse : nurses) {
        std::cout << "- " << nurse->getName() << "\n";
    }
}
